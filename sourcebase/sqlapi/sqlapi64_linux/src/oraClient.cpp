// oraClient.cpp: implementation of the IibClient class.
//
//////////////////////////////////////////////////////////////////////

#include <SQLAPI.h>
#include "oraClient.h"

#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>	// strtol, atoi

#include "samisc.h"
#include "errmsg.h"

#include <oraAPI.h>
#include <ora7API.h>

typedef unsigned char OraDATE_t[7];
typedef unsigned char OraVARNUM_t[22];

//////////////////////////////////////////////////////////////////////
// IoraConnection Class
//////////////////////////////////////////////////////////////////////

class IoraConnection : public ISAConnection
{
protected:
	enum {
		MaxLongPiece = (unsigned int)0x7FFFFFFF
	};

	virtual ~IoraConnection();

	SAIsolationLevel_t m_eSwitchToIsolationLevelAfterCommit;
	void issueIsolationLevel(
		SAIsolationLevel_t eIsolationLevel);

public:
	IoraConnection(SAConnection *pSAConnection);

	virtual void setIsolationLevel(
		SAIsolationLevel_t eIsolationLevel);

	virtual void CnvtInternalToNumeric(
		SANumeric &numeric,
		const void *pInternal,
		int nInternalSize);

	virtual void CnvtInternalToDateTime(
		SADateTime &date_time,
		const void *pInternal,
		int nInternalSize);
	static void CnvtInternalToDateTime(
		SADateTime &date_time,
		const OraDATE_t *pInternal);
	static void CnvtDateTimeToInternal(
		const SADateTime &date_time,
		OraDATE_t *pInternal);
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


IoraConnection::IoraConnection(
	SAConnection *pSAConnection) : ISAConnection(pSAConnection)
{
	m_eSwitchToIsolationLevelAfterCommit = SA_LevelUnknown;
}

IoraConnection::~IoraConnection()
{
}

/*virtual */
void IoraConnection::CnvtInternalToDateTime(
	SADateTime &date_time,
	const void *pInternal,
	int nInternalSize)
{
	assert(nInternalSize == sizeof(OraDATE_t));
	if(nInternalSize != sizeof(OraDATE_t))
		return;
	CnvtInternalToDateTime(date_time, (const OraDATE_t*)pInternal);
}

/*static */
void IoraConnection::CnvtInternalToDateTime(
	SADateTime &date_time,
	const OraDATE_t *pInternal)
{
	date_time = SADateTime(
		((*pInternal)[0]-100)*100 + ((*pInternal)[1]-100),
		(*pInternal)[2],
		(*pInternal)[3],
		(*pInternal)[4] - 1,
		(*pInternal)[5] - 1,
		(*pInternal)[6] - 1);

	// no milli, micro or nano seconds in Oracle
}

/*static */
void IoraConnection::CnvtDateTimeToInternal(
	const SADateTime &date_time,
	OraDATE_t *pInternal)
{
	(*pInternal)[0] = (unsigned char)(((date_time.GetYear())/100) + 100);	// century in excess-100 notation
	(*pInternal)[1] = (unsigned char)(((date_time.GetYear())%100) + 100);	// year in excess-100 notation
	(*pInternal)[2] = (unsigned char)(date_time.GetMonth());				// month 1..12
	(*pInternal)[3] = (unsigned char)(date_time.GetDay());					// day 1..31
	(*pInternal)[4] = (unsigned char)(date_time.GetHour() + 1);				// hour 1..24
	(*pInternal)[5] = (unsigned char)(date_time.GetMinute() + 1);			// min 1..60
	(*pInternal)[6] = (unsigned char)(date_time.GetSecond() + 1);			// sec 1..60

	// no milli, micro or nano seconds in Oracle
}

//////////////////////////////////////////////////////////////////////
// Iora7Connection Class
//////////////////////////////////////////////////////////////////////

class Iora7Connection : public IoraConnection
{
	friend class Iora7Cursor;

	ora7ConnectionHandles m_handles;
	bool	m_bConnected;

	void Check(sword return_code, Cda_Def* pCda_Def);

	enum
	{
		MaxLongPortion = (unsigned int)0xFFFF
	};

protected:
	virtual ~Iora7Connection();

public:
	Iora7Connection(SAConnection *pSAConnection);

	virtual void InitializeClient();
	virtual void UnInitializeClient();

	virtual long GetClientVersion() const;
	virtual long GetServerVersion() const;
	virtual SAString GetServerVersionString() const;

	virtual bool IsConnected() const;
	virtual void Connect(
		const SAString &sDBString,
		const SAString &sUserID,
		const SAString &sPassword);
	virtual void Disconnect();

	virtual void setAutoCommit(
		SAAutoCommit_t eAutoCommit);
	virtual void Commit();
	virtual void Rollback();

	virtual saAPI *NativeAPI() const;
	virtual saConnectionHandles *NativeHandles();

	virtual ISACursor *NewCursor(SACommand *m_pCommand);

	virtual void CnvtInternalToCursor(
		SACommand *pCursor,
		const void *pInternal);
	static void CnvtInternalToCursor(
		SACommand &Cursor,
		const Cda_Def *pInternal);
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Iora7Connection::Iora7Connection(
	SAConnection *pSAConnection) : IoraConnection(pSAConnection)
{
	m_bConnected = false;
}

Iora7Connection::~Iora7Connection()
{
}

/*virtual */
void Iora7Connection::InitializeClient()
{
	::AddORA7Support();
}

/*virtual */
void Iora7Connection::UnInitializeClient()
{
	::ReleaseORA7Support();
}

/*virtual */
long Iora7Connection::GetClientVersion() const
{
	return g_nORA7DLLVersionLoaded;
}

/*virtual */
long Iora7Connection::GetServerVersion() const
{
	SACommand cmd(m_pSAConnection,
		"select VERSION from PRODUCT_COMPONENT_VERSION where PRODUCT like '%Oracle%'");
	cmd.Execute();
	cmd.FetchNext();
	SAString sVersion = cmd.Field(1).asString();
	cmd.Close();

	char *sPoint;
	short nMajor = (short)strtol(sVersion, &sPoint, 10);
	assert(*sPoint == '.');
	sPoint++;
	short nMinor = (short)strtol(sPoint, &sPoint, 10);
	return nMinor + (nMajor << 16);
}

/*virtual */
SAString Iora7Connection::GetServerVersionString() const
{
	SACommand cmd(m_pSAConnection,
		"select"
		" PRODUCT || ' Release ' || VERSION || ' - ' || STATUS "
		"from"
		" PRODUCT_COMPONENT_VERSION "
		"where"
		" PRODUCT like '%Oracle%'");
	cmd.Execute();
	cmd.FetchNext();
	SAString sVersion = cmd.Field(1).asString();
	cmd.Close();
	return sVersion;
}

void Iora7Connection::Check(sword result_code, Cda_Def* pCda_Def)
{
	if(!result_code)
		return;

	char sMsg[512];
	g_ora7API.oerhms(&m_handles.m_lda, (sb2)result_code, (text*)sMsg, (sword)sizeof(sMsg));

	ub2 peo = pCda_Def? pCda_Def->peo : m_handles.m_lda.peo;
	ub2 rc = pCda_Def? pCda_Def->rc : m_handles.m_lda.rc;
	throw SAException(
		SA_DBMS_API_Error,
		(int)rc, (int)peo,
		"%s", sMsg);
}

/*virtual */
bool Iora7Connection::IsConnected() const
{
	return m_bConnected;
}

/*virtual */
void Iora7Connection::Connect(
	const SAString &sDBString,
	const SAString &sUserID,
	const SAString &sPassword)
{
	assert(!m_bConnected);

	Check(
		g_ora7API.olog(&m_handles.m_lda, m_handles.m_hda,
		(text*)(const char*)sUserID, -1,
		(text*)(const char*)sPassword, -1,
		(text*)(const char*)sDBString, -1,
		OCI_LM_DEF), NULL);
	m_bConnected = true;
}

/*virtual */
void Iora7Connection::Disconnect()
{
	assert(m_bConnected);
	Check(g_ora7API.ologof(&m_handles.m_lda), NULL);
	m_bConnected = false;
}

/*virtual */
void Iora7Connection::Commit()
{
	SAIsolationLevel_t eIsolationLevel;
	if(m_eSwitchToIsolationLevelAfterCommit != SA_LevelUnknown)
	{
		eIsolationLevel = m_eSwitchToIsolationLevelAfterCommit;
		m_eSwitchToIsolationLevelAfterCommit = SA_LevelUnknown;
	}
	else
		eIsolationLevel = m_pSAConnection->IsolationLevel();

	Check(g_ora7API.ocom(&m_handles.m_lda), NULL);

	if(eIsolationLevel != SA_LevelUnknown)
		issueIsolationLevel(eIsolationLevel);
}

/*virtual */
void Iora7Connection::Rollback()
{
	Check(g_ora7API.orol(&m_handles.m_lda), NULL);

	SAIsolationLevel_t eIsolationLevel = m_pSAConnection->IsolationLevel();
	if(eIsolationLevel != SA_LevelUnknown)
		issueIsolationLevel(eIsolationLevel);
}

//////////////////////////////////////////////////////////////////////
// Iora8Connection Class
//////////////////////////////////////////////////////////////////////

typedef
enum
{
	SA_OCI8TempLobSupport_Unknown,
	SA_OCI8TempLobSupport_True,
	SA_OCI8TempLobSupport_False,
	_SA_OCI8TempLobSupport_Reserverd = (int)(((unsigned int)(-1))/2)
} SAOra8TempLobSupport_t;

class Iora8Connection : public IoraConnection
{
	friend class Iora8Cursor;

	ora8ConnectionHandles m_handles;

	static void Check(
		sword	status,
		dvoid	*hndlp,
		ub4		type,
		OCIStmt	*pOCIStmt = NULL);

	SAOra8TempLobSupport_t m_eOra8TempLobSupport;
	bool IsTemporaryLobSupported();

protected:
	virtual ~Iora8Connection();

public:
	Iora8Connection(SAConnection *pSAConnection);

	virtual void InitializeClient();
	virtual void UnInitializeClient();

	virtual long GetClientVersion() const;
	virtual long GetServerVersion() const;
	virtual SAString GetServerVersionString() const;

	virtual bool IsConnected() const;
	virtual void Connect(
		const SAString &sDBString,
		const SAString &sUserID,
		const SAString &sPassword);
	virtual void Disconnect();

	virtual void setAutoCommit(
		SAAutoCommit_t eAutoCommit);
	virtual void Commit();
	virtual void Rollback();

	virtual saAPI *NativeAPI() const;
	virtual saConnectionHandles *NativeHandles();

	virtual ISACursor *NewCursor(SACommand *m_pCommand);

	virtual void CnvtInternalToCursor(
		SACommand *pCursor,
		const void *pInternal);
	static void CnvtInternalToCursor(
		SACommand &Cursor,
		const OCIStmt *pInternal);
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Iora8Connection::Iora8Connection(
	SAConnection *pSAConnection) : IoraConnection(pSAConnection)
{
	m_eOra8TempLobSupport = SA_OCI8TempLobSupport_Unknown;
}

Iora8Connection::~Iora8Connection()
{
}

/*virtual */
void Iora8Connection::InitializeClient()
{
	::AddORA8Support();
}

/*virtual */
void Iora8Connection::UnInitializeClient()
{
	::ReleaseORA8Support();
}

/*virtual */
long Iora8Connection::GetClientVersion() const
{
	return g_nORA8DLLVersionLoaded;
}

/*virtual */
long Iora8Connection::GetServerVersion() const
{
	return SAExtractVersionFromString(GetServerVersionString());
}

/*virtual */
SAString Iora8Connection::GetServerVersionString() const
{
	char sVersion[1024];

	Check(g_ora8API.OCIServerVersion(
		m_handles.m_pOCIServer,
		m_handles.m_pOCIError,
		(text*)sVersion,
		sizeof(sVersion)/sizeof(char),
		OCI_HTYPE_SERVER),
		m_handles.m_pOCIError, OCI_HTYPE_ERROR);

	return SAString(sVersion);
}

// based on OCIError or OCIEnv
/*static */
void Iora8Connection::Check(
	sword	status,
	dvoid	*hndlp,
	ub4		type,
	OCIStmt	*pOCIStmt/* = NULL*/)
{
	sb4 errcode, main_errcode = 0;
	char buf[512];
	SAString sErr;
	ub4 recordno = 1;
	sword ret;
	int nErrPos = -1;
	OCIError *pOCIError = NULL;
	if(type == OCI_HTYPE_ERROR)
		pOCIError = (OCIError *)hndlp;
	
	switch (status)
	{
	case OCI_SUCCESS:
		break;
	case OCI_SUCCESS_WITH_INFO:
		break;
	case OCI_NEED_DATA:
	case OCI_NO_DATA:
	case OCI_STILL_EXECUTING:
	case OCI_ERROR:
// According to Oracle Docs we should loop while ret == OCI_SUCCESS,
// but we can loop forever under some conditions if we will check 
// for OCI_SUCCESS. Oracle bug?
//		do
		{
			ret = g_ora8API.OCIErrorGet(hndlp, recordno, (text *)NULL, &errcode,
				(text*)buf, (ub4) sizeof(buf), type);

			if(ret == OCI_SUCCESS)
			{
//				if(recordno == 1)
					main_errcode = errcode;
//				if(recordno > 1)
//					sErr += "\n";
				sErr += buf;

//				++recordno;
			}
			else
				assert(ret == OCI_NO_DATA);
		}
//		while(ret == OCI_SUCCESS);

		if(pOCIStmt && pOCIError)
		{
			ub2 peo;
			ret = g_ora8API.OCIAttrGet(
				pOCIStmt, OCI_HTYPE_STMT,
				&peo, NULL,
				OCI_ATTR_PARSE_ERROR_OFFSET,
				pOCIError);
			if(ret == OCI_SUCCESS)
				nErrPos = (int)peo;
		}
	
		throw SAException(
			SA_DBMS_API_Error,
			main_errcode, nErrPos,
			sErr);
	case OCI_INVALID_HANDLE:
		assert(false);
		throw SAException(
			SA_DBMS_API_Error,
			main_errcode, nErrPos,
			"OCI_INVALID_HANDLE");
	default:
		assert(false);
	}
}

// tests if both client and server support Temporary Lobs
// test is very simple
// we try to create it
bool Iora8Connection::IsTemporaryLobSupported()
{
	if(m_eOra8TempLobSupport == SA_OCI8TempLobSupport_Unknown)
	{
		// client test
		if(!g_ora8API.OCILobCreateTemporary)
			m_eOra8TempLobSupport = SA_OCI8TempLobSupport_False;
		else
		{
			// server test
			OCILobLocator *pLoc = NULL;
			try
			{
				Check(g_ora8API.OCIDescriptorAlloc(
					m_handles.m_pOCIEnv,
					(dvoid **)&pLoc,
					OCI_DTYPE_LOB, 0,
					NULL), m_handles.m_pOCIEnv, OCI_HTYPE_ENV);

				Check(g_ora8API.OCILobCreateTemporary(
					m_handles.m_pOCISvcCtx,
					m_handles.m_pOCIError,
					pLoc,
					OCI_DEFAULT,
					OCI_DEFAULT,
					OCI_TEMP_BLOB,
					OCI_ATTR_NOCACHE,
					OCI_DURATION_SESSION), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

				m_eOra8TempLobSupport = SA_OCI8TempLobSupport_True;
			}
			catch(SAException &)
			{
				m_eOra8TempLobSupport = SA_OCI8TempLobSupport_False;
			}

			// clean up
			try
			{
				if(m_eOra8TempLobSupport == SA_OCI8TempLobSupport_True)
					Check(g_ora8API.OCILobFreeTemporary(
						m_handles.m_pOCISvcCtx,
						m_handles.m_pOCIError,
						pLoc), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			}
			catch(SAException &)
			{
				assert(false);
			}

			try
			{
				if(pLoc)
					Iora8Connection::Check(g_ora8API.OCIDescriptorFree(
						pLoc, OCI_DTYPE_LOB), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			}
			catch(SAException &)
			{
				assert(false);
			}
		}
	}

	assert(m_eOra8TempLobSupport != SA_OCI8TempLobSupport_Unknown);
	return m_eOra8TempLobSupport == SA_OCI8TempLobSupport_True;
}

/*virtual */
bool Iora8Connection::IsConnected() const
{
	return m_handles.m_pOCIEnv != NULL;
}

/*virtual */
void Iora8Connection::Connect(
	const SAString &sDBString,
	const SAString &sUserID,
	const SAString &sPassword)
{
	assert(m_handles.m_pOCIEnv		== NULL);
	assert(m_handles.m_pOCIError	== NULL);
	assert(m_handles.m_pOCISvcCtx	== NULL);
	assert(m_handles.m_pOCIServer	== NULL);
	assert(m_handles.m_pOCISession	== NULL);

	short bServerAttach = 0;
	short bSessionBegin = 0;
	try
	{
		if(g_ora8API.OCIEnvCreate == NULL)	// use 8.0.x method of initialization
		{
			Check(g_ora8API.OCIEnvInit(
				&m_handles.m_pOCIEnv,
				OCI_DEFAULT,
				0, (dvoid**)0), m_handles.m_pOCIEnv, OCI_HTYPE_ENV);
		}
		else
		{
			Check(g_ora8API.OCIEnvCreate(
				&m_handles.m_pOCIEnv,
				OCI_THREADED | OCI_OBJECT,
				NULL,
				NULL, NULL, NULL,
				0, (dvoid**)0),
				m_handles.m_pOCIEnv,
				OCI_HTYPE_ENV);
		}
		Check(g_ora8API.OCIHandleAlloc(m_handles.m_pOCIEnv, (dvoid**)&m_handles.m_pOCIError, OCI_HTYPE_ERROR, 0, (dvoid**)0), m_handles.m_pOCIEnv, OCI_HTYPE_ENV);
		Check(g_ora8API.OCIHandleAlloc(m_handles.m_pOCIEnv, (dvoid**)&m_handles.m_pOCISvcCtx, OCI_HTYPE_SVCCTX, 0, (dvoid**)0), m_handles.m_pOCIEnv, OCI_HTYPE_ENV);
		Check(g_ora8API.OCIHandleAlloc(m_handles.m_pOCIEnv, (dvoid**)&m_handles.m_pOCIServer, OCI_HTYPE_SERVER, 0, (dvoid**)0), m_handles.m_pOCIEnv, OCI_HTYPE_ENV);
		Check(g_ora8API.OCIHandleAlloc(m_handles.m_pOCIEnv, (dvoid**)&m_handles.m_pOCISession, OCI_HTYPE_SESSION, 0, (dvoid**)0), m_handles.m_pOCIEnv, OCI_HTYPE_ENV);

		Check(g_ora8API.OCIAttrSet(m_handles.m_pOCISession, OCI_HTYPE_SESSION, (dvoid*)(const char*)sUserID, (ub4)sUserID.GetLength(), OCI_ATTR_USERNAME, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
		Check(g_ora8API.OCIAttrSet(m_handles.m_pOCISession, OCI_HTYPE_SESSION, (dvoid*)(const char*)sPassword, (ub4)sPassword.GetLength(), OCI_ATTR_PASSWORD, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

		Check(g_ora8API.OCIServerAttach(m_handles.m_pOCIServer, m_handles.m_pOCIError, (CONST text *)(const char*)sDBString, (sb4)sDBString.GetLength(), OCI_DEFAULT), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
		bServerAttach = 1;
		Check(g_ora8API.OCIAttrSet(m_handles.m_pOCISvcCtx, OCI_HTYPE_SVCCTX, (dvoid*)m_handles.m_pOCIServer, (ub4)0, OCI_ATTR_SERVER, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

		Check(g_ora8API.OCISessionBegin(m_handles.m_pOCISvcCtx, m_handles.m_pOCIError, m_handles.m_pOCISession, OCI_CRED_RDBMS, OCI_DEFAULT), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
		bSessionBegin = 1;
		Check(g_ora8API.OCIAttrSet(m_handles.m_pOCISvcCtx, OCI_HTYPE_SVCCTX, (dvoid*)m_handles.m_pOCISession, (ub4)0, OCI_ATTR_SESSION, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
	}
	catch(...)
	{
		// clean up
		if(bSessionBegin)
			g_ora8API.OCISessionEnd(m_handles.m_pOCISvcCtx, m_handles.m_pOCIError, m_handles.m_pOCISession, OCI_DEFAULT);
		if(bServerAttach)
			g_ora8API.OCIServerDetach(m_handles.m_pOCIServer, m_handles.m_pOCIError, OCI_DEFAULT);
		if(m_handles.m_pOCIEnv != NULL)
		{
			// frees all child handles too
			g_ora8API.OCIHandleFree(m_handles.m_pOCIEnv, OCI_HTYPE_ENV);
			m_handles.m_pOCIEnv = NULL;
			m_handles.m_pOCIError = NULL;
			m_handles.m_pOCISvcCtx = NULL;
			m_handles.m_pOCIServer = NULL;
			m_handles.m_pOCISession = NULL;
		}

		throw;
	}
}

/*virtual */
void Iora8Connection::Disconnect()
{
	assert(m_handles.m_pOCIEnv		!= NULL);
	assert(m_handles.m_pOCIError	!= NULL);
	assert(m_handles.m_pOCISvcCtx	!= NULL);
	assert(m_handles.m_pOCIServer	!= NULL);
	assert(m_handles.m_pOCISession	!= NULL);

	Check(g_ora8API.OCISessionEnd(m_handles.m_pOCISvcCtx, m_handles.m_pOCIError, m_handles.m_pOCISession, OCI_DEFAULT), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
	Check(g_ora8API.OCIServerDetach(m_handles.m_pOCIServer, m_handles.m_pOCIError, OCI_DEFAULT), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

	// frees all child handles too
	Check(g_ora8API.OCIHandleFree(m_handles.m_pOCIEnv, OCI_HTYPE_ENV), m_handles.m_pOCIEnv, OCI_HTYPE_ENV);
	m_handles.m_pOCIEnv = NULL;
	m_handles.m_pOCIEnv = NULL;
	m_handles.m_pOCIError = NULL;
	m_handles.m_pOCISvcCtx = NULL;
	m_handles.m_pOCIServer = NULL;
	m_handles.m_pOCISession = NULL;

	m_eOra8TempLobSupport = SA_OCI8TempLobSupport_Unknown;
}

/*virtual */
void Iora8Connection::Commit()
{
	SAIsolationLevel_t eIsolationLevel;
	if(m_eSwitchToIsolationLevelAfterCommit != SA_LevelUnknown)
	{
		eIsolationLevel = m_eSwitchToIsolationLevelAfterCommit;
		m_eSwitchToIsolationLevelAfterCommit = SA_LevelUnknown;
	}
	else
		eIsolationLevel = m_pSAConnection->IsolationLevel();

	Check(g_ora8API.OCITransCommit(m_handles.m_pOCISvcCtx, m_handles.m_pOCIError, OCI_DEFAULT),
		m_handles.m_pOCIError, OCI_HTYPE_ERROR);

	if(eIsolationLevel != SA_LevelUnknown)
		issueIsolationLevel(eIsolationLevel);
}

/*virtual */
void Iora8Connection::Rollback()
{
	Check(g_ora8API.OCITransRollback(m_handles.m_pOCISvcCtx, m_handles.m_pOCIError, OCI_DEFAULT),
		m_handles.m_pOCIError, OCI_HTYPE_ERROR);

	SAIsolationLevel_t eIsolationLevel = m_pSAConnection->IsolationLevel();
	if(eIsolationLevel != SA_LevelUnknown)
		issueIsolationLevel(eIsolationLevel);
}

//////////////////////////////////////////////////////////////////////
// IoraClient Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IoraClient::IoraClient()
{
}

IoraClient::~IoraClient()
{
}

ISAConnection *IoraClient::QueryConnectionInterface(
	SAConnection *pSAConnection)
{
	SAString s = pSAConnection->Option("UseAPI");

	if(s.CompareNoCase("OCI7") == 0)
		return new Iora7Connection(pSAConnection);

	if(s.CompareNoCase("OCI8") == 0)
		return new Iora8Connection(pSAConnection);

	if(CanBeLoadedOCI8())
		return new Iora8Connection(pSAConnection);

	return new Iora7Connection(pSAConnection);
}

//////////////////////////////////////////////////////////////////////
// IoraCursor Class
//////////////////////////////////////////////////////////////////////

typedef enum
{
	LongContextNormal = 1,
	LongContextPiecewiseDefine = 2,
	LongContextPiecewiseBind = 4,
	LongContextPiecewise = LongContextPiecewiseDefine | LongContextPiecewiseBind,
	LongContextCallback = 8
} LongContextState_t;
typedef struct tagLongContext
{
	LongContextState_t eState;
	SAValueRead *pReader;
	SAValue *pWriter;
	sb2 *pInd;
	unsigned char *pBuf;
	ub4 Len;
} LongContext_t;

class IoraCursor : public ISACursor
{
protected:
	SAString m_sInternalPrepareStmt;
	SAString CallSubProgramSQL();

	unsigned char m_PiecewiseNullCheckPreFetch[1];
	bool m_bPiecewiseFetchPending;

	IoraCursor(
		IoraConnection *pIoraConnection,
		SACommand *pCommand);
	virtual ~IoraCursor();

	virtual unsigned int InputBufferSize(
		const SAParam &Param) const;
	virtual unsigned int OutputBufferSize(
		SADataType_t eDataType,
		unsigned int nDataSize) const;

	virtual SADataType_t CnvtNativeToStd(
		int nNativeType,
		int nNativeSubType,
		int nSize,
		int nPrec,
		int nScale) const;
};

IoraCursor::IoraCursor(
	IoraConnection *pIoraConnection,
	SACommand *pCommand) :
	ISACursor(pIoraConnection, pCommand)
{
	m_bPiecewiseFetchPending = false;
}

/*virtual */
IoraCursor::~IoraCursor()
{
}

SAString IoraCursor::CallSubProgramSQL()
{
	int nParams = m_pCommand->ParamCount();

	SAString sSQL = "begin\n";

	// check for Return parameter
	int i;
	for(i = 0; i < nParams; ++i)
	{
		SAParam &Param = m_pCommand->ParamByIndex(i);
		if(Param.ParamDirType() == SA_ParamReturn)
		{
			sSQL += ":";
			sSQL += Param.Name();
			sSQL += ":=";
			break;
		}
	}
	sSQL += m_pCommand->CommandText();
	// specify parameters
	sSQL += "(";
	SAString sParams;
	for(i = 0; i < nParams; ++i)
	{
		SAParam &Param = m_pCommand->ParamByIndex(i);
		if(Param.ParamDirType() == SA_ParamReturn)
			continue;

		if(!sParams.IsEmpty())
			sParams += ", ";
		sParams += Param.Name();
		sParams += "=>:";
		sParams += Param.Name();
	}
	sSQL += sParams;
	sSQL += ");\nend;";

	return sSQL;
}

/*virtual */
unsigned int IoraCursor::InputBufferSize(
	const SAParam &Param) const
{
	switch(Param.DataType())
	{
	case SA_dtBool:
		// there is no "native" boolean type in Oracle,
		// so treat boolean as 16-bit signed INTEGER in Oracle
		return sizeof(short);
	case SA_dtNumeric:
		return sizeof(OraVARNUM_t);
	case SA_dtDateTime:
		return sizeof(OraDATE_t);	// Oracle internal date/time representation
	case SA_dtLongBinary:
	case SA_dtLongChar:
		return sizeof(LongContext_t);
	default:
		break;
	}
	
	return ISACursor::InputBufferSize(Param);
}

/*virtual */
unsigned int IoraCursor::OutputBufferSize(
	SADataType_t eDataType,
	unsigned int nDataSize) const
{
	switch(eDataType)
	{
	case SA_dtNumeric:
		return sizeof(OraVARNUM_t);
	case SA_dtDateTime:
		return sizeof(OraDATE_t);
	case SA_dtBytes:
		// Oracle can report nDataSize = 0 for output parameters
		// under some conditions
		return ISACursor::OutputBufferSize(eDataType, nDataSize? nDataSize : 4000);
	case SA_dtString:
		// Oracle can report nDataSize = 0 for output parameters
		// under some conditions
		return ISACursor::OutputBufferSize(eDataType, nDataSize? nDataSize : 4000);
	case SA_dtLongBinary:
	case SA_dtLongChar:
		return sizeof(LongContext_t);
	default:
		break;
	}

	return ISACursor::OutputBufferSize(eDataType, nDataSize);
}

/*virtual */
SADataType_t IoraCursor::CnvtNativeToStd(
	int dbtype,
	int/* dbsubtype*/,
	int/* dbsize*/,
	int prec,
	int scale) const
{
	SADataType_t eDataType;

	switch(dbtype)
	{
	case 1:		// VARCHAR2	2000 (4000) bytes
		eDataType = SA_dtString;
		break;
	case 2:		// NUMBER	21 bytes
		// if selecting constant or formula
		if(prec == 0)	// prec unknown
			eDataType = SA_dtNumeric;
		else if(scale > 0)	// floating point exists?
			eDataType = SA_dtNumeric;
		else	// check for exact type
		{
			int ShiftetPrec = prec - scale;	// not to deal with negative scale if it is
			if(ShiftetPrec < 5)	// -9,999 : 9,999
				eDataType = SA_dtShort;
			else if(ShiftetPrec < 10)	// -999,999,999 : 999,999,999
				eDataType = SA_dtLong;
			else
				eDataType = SA_dtNumeric;
		}
		break;
	case 8:		// LONG		2^31-1 bytes
		eDataType = SA_dtLongChar;
		break;
	case 11:	// ROWID	6 (10) bytes
		eDataType = SA_dtString;
		break;
	case 12:	// DATE		7 bytes
		eDataType = SA_dtDateTime;
		break;
	case 23:	// RAW		255 bytes
		eDataType = SA_dtBytes;
		break;
	case 24:	// LONG RAW	2^31-2 bytes
		eDataType = SA_dtLongBinary;
		break;
	case 96:	// CHAR		255 (2000) bytes
		eDataType = SA_dtString;
		break;
	case 102:	// CURSOR VARIABLE
		eDataType = SA_dtCursor;
		break;
	case 105:	// MSLABEL	255 bytes
		eDataType = SA_dtString;
		break;
	default:
		assert(false);
		eDataType = SA_dtUnknown;
	}

	return eDataType;
}

//////////////////////////////////////////////////////////////////////
// Iora7Cursor Class
//////////////////////////////////////////////////////////////////////

class Iora7Cursor : public IoraCursor
{
	ora7CommandHandles	m_handles;

	bool m_bOpened;
	bool m_bResultSetExist;
	bool m_bResultSetCanBe;

	bool			m_bPiecewiseBindAllowed;
	bool			m_bPiecewiseFetchAllowed;
	void BindLongs();
	void DiscardPiecewiseFetch();
	void CheckPiecewiseNull(bool bAfterExecute = false);
	SAField *WhichFieldIsPiecewise() const;

protected:
	virtual unsigned int InputBufferSize(
		const SAParam &Param) const;
	virtual unsigned int OutputBufferSize(
		SADataType_t eDataType,
		unsigned int nDataSize) const;
	virtual void SetFieldBuffer(
		int nCol,	// 1-based
		void *pInd,
		unsigned int nIndSize,
		void *pSize,
		unsigned int nSizeSize,
		void *pValue,
		unsigned int nValueSize);

	virtual int CnvtStdToNative(SADataType_t eDataType) const;

public:
	Iora7Cursor(
		Iora7Connection *pIora7Connection,
		SACommand *pCommand);
	virtual ~Iora7Cursor();

	virtual bool IsOpened();
	virtual void Open();
	virtual void Close();

	virtual void Prepare(
		const SAString &sStmt,
		SACommandType_t eCmdType,
		int nPlaceHolderCount,
		saPlaceHolder **ppPlaceHolders);
	// binds parameters
	void Bind(
		int nPlaceHolderCount,
		saPlaceHolder **ppPlaceHolders);
	// executes statement
	virtual void Execute(
		int nPlaceHolderCount,
		saPlaceHolder **ppPlaceHolders);
	// cleans up after execute if needed, so the statement can be reexecuted
	virtual void UnExecute();
	virtual void Cancel();

	virtual bool ResultSetExists();
	virtual void DescribeFields(
		DescribeFields_cb_t fn);
	virtual void SetSelectBuffers();
	virtual bool FetchNext();

	virtual long GetRowsAffected();

	virtual void ReadLongOrLOB(
		ValueType_t eValueType,
		SAValueRead &vr,
		void *pValue,
		unsigned int nFieldBufSize,
		saLongOrLobReader_t fnReader,
		unsigned int nReaderWantedPieceSize,
		void *pAddlData);

	virtual void DescribeParamSP();

	virtual saCommandHandles *NativeHandles();
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Iora7Cursor::Iora7Cursor(
	Iora7Connection *pIora7Connection,
	SACommand *pCommand) :
	IoraCursor(pIora7Connection, pCommand)
{
	m_bOpened = false;
	m_bResultSetExist = false;

	m_bPiecewiseBindAllowed = true;
	m_bPiecewiseFetchAllowed = true;
}

/*virtual */
Iora7Cursor::~Iora7Cursor()
{
}

/*virtual */
unsigned int Iora7Cursor::InputBufferSize(
	const SAParam &Param) const
{
	switch(Param.DataType())
	{
		case SA_dtBLob:
		case SA_dtCLob:
			return sizeof(LongContext_t);
		case SA_dtCursor:
			return sizeof(Cda_Def);
		default:
			break;			
	}

	return IoraCursor::InputBufferSize(Param);
}

/*virtual */
unsigned int Iora7Cursor::OutputBufferSize(
	SADataType_t eDataType,
	unsigned int nDataSize) const
{
	switch(eDataType)
	{
	case SA_dtCursor:
		return sizeof(Cda_Def);
	default:
		break;
	}

	return IoraCursor::OutputBufferSize(eDataType, nDataSize);
}

/*virtual */
bool Iora7Cursor::IsOpened()
{
	return m_bOpened;
}

/*virtual */
void Iora7Cursor::Open()
{
	assert(m_bOpened == false);
	((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.oopen(
		&m_handles.m_cda,
		&((Iora7Connection*)m_pISAConnection)->m_handles.m_lda,
		NULL, -1, -1,
		NULL, -1), &m_handles.m_cda);
	m_bOpened = true;
}

/*virtual */
void Iora7Cursor::Close()
{
	assert(m_bOpened != 0);
	((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.oclose(
		&m_handles.m_cda), &m_handles.m_cda);
	m_bOpened = false;
}

//////////////////////////////////////////////////////////////////////
// Iora8Cursor Class
//////////////////////////////////////////////////////////////////////

// helper structures
typedef struct tagBlobReturningContext
{
	SAParam *pParam;
	OCIError *pOCIError;
	OCIEnv *pOCIEnv;
	OCILobLocator ***pppOCILobLocators;
	ub4 **ppLobLocatorsLens;
	int nLobLocatorCol;
	ub4 *pnLobReturnBindsColCount;
	ub4 *pnBLobBindsRowCount;
} BlobReturningContext_t;

class Iora8Cursor : public IoraCursor
{
	ora8CommandHandles	m_handles;

	ub2	m_nOraStmtType;
	bool m_bResultSetCanBe;

	ub2	*m_pDTY;	// array of bound parameters types

	void DiscardPiecewiseFetch();
	void ReadLong(
		LongContext_t *pLongContext,
		saLongOrLobReader_t fnReader,
		unsigned int nReaderWantedPieceSize,
		void *pAddlData);
	void CheckPiecewiseNull();
	SAField *WhichFieldIsPiecewise() const;
	void ReadLob(
		ValueType_t eValueType,
		SAValueRead &vr,
		OCILobLocator* pOCILobLocator,
		saLongOrLobReader_t fnReader,
		unsigned int nReaderWantedPieceSize,
		void *pAddlData);
	void CreateTemporaryLob(
		OCILobLocator **ppLob,
		SAParam &Param);
	// returns total size written
	ub4 BindLob(
		OCILobLocator *pLob,
		SAParam &Param);

	static sb4 LongInBind(
		dvoid *ictxp,
		OCIBind *bindp,
		ub4 iter,
		ub4 index,
		dvoid **bufpp,
		ub4 *alenp,
		ub1 *piecep,
		dvoid **indpp);
	static sb4 LongOutBind(
		dvoid *ictxp,
		OCIBind *bindp,
		ub4 iter,
		ub4 index,
		dvoid **bufpp,
		ub4 **alenp,
		ub1 *piecep,
		dvoid **indpp,
		ub2 **rcodep);
	static sb4 LongDefine(
		dvoid *octxp,
		OCIDefine *defnp,
		ub4 iter,
		dvoid **bufpp, ub4 **alenp, ub1 *piecep,
		dvoid **indp, ub2 **rcodep);

	static sb4 LongDefineOrOutBind(
		dvoid *octxp,
		dvoid **bufpp,
		ub4 **alenpp,
		ub1 *piecep,
		dvoid **indpp);

	// binding LOBs with not NULL values (add returning into clause)
	SAString m_sOriginalStmt;
	ub4 m_nLobReturnBindsColCount;
	ub4 m_nBLobBindsRowCount;
	saPlaceHolder **m_ppLobReturnPlaceHolders;	// m_ppLobReturnPlaceHolders[m_nLobReturnBindsColCount]
	OCILobLocator ***m_pppBLobReturningLocs;	// m_pppBLobReturningLocs[m_nLobReturnBindsColCount][m_nBLobBindsRowCount]
	ub4 **m_ppLobReturningLens;	// m_ppLobReturningLens[m_nLobReturnBindsColCount][m_nBLobBindsRowCount]
	void DestroyLobsReturnBinding();
	void CheckForReparseBeforeBinding(
		int nPlaceHolderCount,
		saPlaceHolder**	ppPlaceHolders);
	void InternalPrepare(
		const SAString &sStmt);
	static sb2 stat_m_BLobReturningNullInd;
	static sb4 LobReturningInBind(
		dvoid *ictxp,
		OCIBind *bindp,
		ub4 iter,
		ub4 index,
		dvoid **bufpp,
		ub4 *alenp,
		ub1 *piecep,
		dvoid **indpp);
	static sb4 LobReturningOutBind(
		dvoid *octxp,
		OCIBind *bindp,
		ub4 iter,
		ub4 index,
		dvoid **bufpp,
		ub4 **alenp,
		ub1 *piecep,
		dvoid **indp,
		ub2 **rcodep);
	void BindReturningLobs();

	// binding using temporary Lobs
	OCILobLocator **m_ppTempLobs;
	int m_cTempLobs;
	void FreeTemporaryLobsIfAny();

protected:
	virtual unsigned int InputBufferSize(
		const SAParam &Param) const;
	virtual unsigned int OutputBufferSize(
		SADataType_t eDataType,
		unsigned int nDataSize) const;
	virtual void SetFieldBuffer(
		int nCol,	// 1-based
		void *pInd,
		unsigned int nIndSize,
		void *pSize,
		unsigned int nSizeSize,
		void *pValue,
		unsigned int nValueSize);
	virtual void ConvertLongOrLOB(
		ValueType_t eValueType,
		SAValueRead &vr,
		void *pValue,
		unsigned int nFieldBufSize);

	virtual SADataType_t CnvtNativeToStd(
		int nNativeType,
		int nNativeSubType,
		int nSize,
		int nPrec,
		int nScale) const;
	virtual int CnvtStdToNative(SADataType_t eDataType) const;

public:
	Iora8Cursor(
		Iora8Connection *pIora8Connection,
		SACommand *pCommand);
	virtual ~Iora8Cursor();

	virtual bool IsOpened();
	virtual void Open();
	virtual void Close();

	virtual void Prepare(
		const SAString &sStmt,
		SACommandType_t eCmdType,
		int nPlaceHolderCount,
		saPlaceHolder **ppPlaceHolders);
	// binds parameters
	void Bind(
		int nPlaceHolderCount,
		saPlaceHolder **ppPlaceHolders);
	// executes statement
	virtual void Execute(
		int nPlaceHolderCount,
		saPlaceHolder **ppPlaceHolders);
	// cleans up after execute if needed, so the statement can be reexecuted
	virtual void UnExecute();
	virtual void Cancel();

	virtual bool ResultSetExists();
	virtual void DescribeFields(
		DescribeFields_cb_t fn);
	virtual void SetSelectBuffers();
	virtual bool FetchNext();

	virtual long GetRowsAffected();

	virtual void ReadLongOrLOB(
		ValueType_t eValueType,
		SAValueRead &vr,
		void *pValue,
		unsigned int nFieldBufSize,
		saLongOrLobReader_t fnReader,
		unsigned int nReaderWantedPieceSize,
		void *pAddlData);

	virtual void DescribeParamSP();

	virtual saCommandHandles *NativeHandles();
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*static */
sb2 Iora8Cursor::stat_m_BLobReturningNullInd = OCI_IND_NULL;

Iora8Cursor::Iora8Cursor(
	Iora8Connection *pIora8Connection,
	SACommand *pCommand) :
	IoraCursor(pIora8Connection, pCommand)
{
	m_nOraStmtType	= 0;	// unknown
	m_bResultSetCanBe = false;

	m_pDTY = NULL;

	m_nLobReturnBindsColCount = 0;
	m_nBLobBindsRowCount = 0;
	m_ppLobReturnPlaceHolders = NULL;
	m_pppBLobReturningLocs = NULL;
	m_ppLobReturningLens = NULL;

	m_ppTempLobs = NULL;
	m_cTempLobs = 0;
}

/*virtual */
Iora8Cursor::~Iora8Cursor()
{
	try
	{
		if(m_pDTY)
			::free(m_pDTY);
		DestroyLobsReturnBinding();
	}
	catch(SAException &)
	{
	}
}

/*virtual */
unsigned int Iora8Cursor::InputBufferSize(
	const SAParam &Param) const
{
	if(Param.DataType() == SA_dtCursor)
		return sizeof(OCIStmt *);
	
	if(!Param.isNull())
	{
		switch(Param.DataType())
		{
		case SA_dtBLob:
		case SA_dtCLob:
			return ((Iora8Connection*)m_pISAConnection)->IsTemporaryLobSupported()?
				sizeof(OCILobLocator *) :	// if binding using temporary Lob
			sizeof(BlobReturningContext_t);	// if binding 'returning into' clause
		default:
			break;
		}
	}
	
	return IoraCursor::InputBufferSize(Param);
}

/*virtual */
unsigned int Iora8Cursor::OutputBufferSize(
	SADataType_t eDataType,
	unsigned int nDataSize) const
{
	switch(eDataType)
	{
	case SA_dtBLob:
	case SA_dtCLob:
		return sizeof(OCILobLocator *);
	case SA_dtCursor:
		return sizeof(OCIStmt *);
	default:
		break;
	}

	return IoraCursor::OutputBufferSize(eDataType, nDataSize);
}

/*virtual */
bool Iora8Cursor::IsOpened()
{
	return m_handles.m_pOCIStmt != NULL;
}

/*virtual */
void Iora8Cursor::Open()
{
	assert(m_handles.m_pOCIStmt == NULL);
	assert(m_handles.m_pOCIError == NULL);

	Iora8Connection::Check(
		g_ora8API.OCIHandleAlloc(((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv, (dvoid**)&m_handles.m_pOCIError, OCI_HTYPE_ERROR, 0, (dvoid**)0),
		((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv, OCI_HTYPE_ENV);
	Iora8Connection::Check(
		g_ora8API.OCIHandleAlloc(((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv, (dvoid**)&m_handles.m_pOCIStmt, OCI_HTYPE_STMT, 0, NULL),
		((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv, OCI_HTYPE_ENV);

	assert(m_handles.m_pOCIStmt != NULL);
	assert(m_handles.m_pOCIError != NULL);
}

/*virtual */
void Iora8Cursor::Close()
{
	assert(m_handles.m_pOCIStmt != NULL);
	assert(m_handles.m_pOCIError != NULL);

	Iora8Connection::Check(
		g_ora8API.OCIHandleFree(m_handles.m_pOCIStmt, OCI_HTYPE_STMT), m_handles.m_pOCIStmt, OCI_HTYPE_STMT);
	Iora8Connection::Check(
		g_ora8API.OCIHandleFree(m_handles.m_pOCIError, OCI_HTYPE_ERROR), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
	m_handles.m_pOCIStmt = NULL;
	m_handles.m_pOCIError = NULL;
}

/*virtual */
ISACursor *Iora7Connection::NewCursor(SACommand *m_pCommand)
{
	return new Iora7Cursor(this, m_pCommand);
}

/*virtual */
ISACursor *Iora8Connection::NewCursor(SACommand *m_pCommand)
{
	return new Iora8Cursor(this, m_pCommand);
}

/*virtual */
void Iora7Cursor::Prepare(
	const SAString &sStmt,
	SACommandType_t eCmdType,
	int/* nPlaceHolderCount*/,
	saPlaceHolder**	/*ppPlaceHolders*/)
{
	SAString sStmtOra;
	switch(eCmdType)
	{
		case SA_CmdSQLStmt:
			sStmtOra = sStmt;
			break;
		case SA_CmdStoredProc:
			sStmtOra = CallSubProgramSQL();
			break;
		default:
			assert(false);
	}

	// save because (extraction from Oracle docs):
	// "The pointer to the text of the statement must be available
	// as long as the statement is
	// executed, or data is fetched from it."
	m_sInternalPrepareStmt = sStmtOra;

	((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.oparse(
		&m_handles.m_cda,
		(text*)(const char*)m_sInternalPrepareStmt, -1, 0, 1), &m_handles.m_cda);
}

void Iora7Cursor::BindLongs()
{
	assert(m_bPiecewiseBindAllowed);
	assert(m_handles.m_cda.rc == 3129);	// the next Piece to be inserted is required

	try
	{
		// it is a piecewise bind, so we can bind only one column
		sword rc = 0;
		SAPieceType_t ePieceType = SA_FirstPiece;
		while(m_handles.m_cda.rc == 3129)
		{
			ub1 piece;
			dvoid* ctxp;
			ub4 iter;
			ub4 index;
			((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.ogetpi(
				&m_handles.m_cda,
				&piece, &ctxp, &iter, &index), &m_handles.m_cda);

			LongContext_t *pLongContext = (LongContext_t *)ctxp;
			void *pBuf;
			ub4 nActualWrite =
				pLongContext->pWriter->InvokeWriter(ePieceType, Iora7Connection::MaxLongPiece, pBuf);
			if(!nActualWrite || ePieceType == SA_LastPiece || ePieceType == SA_OnePiece)
				piece = OCI_LAST_PIECE;
			if(!nActualWrite)
				pBuf = NULL;

			((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.osetpi(
				&m_handles.m_cda,
				piece, pBuf, &nActualWrite), &m_handles.m_cda);

			rc = g_ora7API.oexec(&m_handles.m_cda);
		}

		if(m_handles.m_cda.rc != 3130) // the buffer for the next Piece to be fetched is required
			((Iora7Connection*)m_pISAConnection)->Check(rc, &m_handles.m_cda);
	}

	catch(SAUserException &)	// clean up after user exception
	{
		ub4 nActualWrite = 0;
		g_ora7API.osetpi(&m_handles.m_cda, OCI_LAST_PIECE, NULL, &nActualWrite);
		g_ora7API.oexec(&m_handles.m_cda);
		throw;
	}
}

/*virtual */
void Iora7Cursor::UnExecute()
{
	m_bResultSetExist = false;
}

/*virtual */
void Iora7Cursor::Execute(
	int nPlaceHolderCount,
	saPlaceHolder **ppPlaceHolders)
{
	if(nPlaceHolderCount)
		Bind(nPlaceHolderCount, ppPlaceHolders);

	sword rc = g_ora7API.oexec(&m_handles.m_cda);
	ub2 ft = m_handles.m_cda.ft;

	if(m_handles.m_cda.rc != 3129	// the next Piece to be inserted is required
		&& m_handles.m_cda.rc != 3130) // the buffer for the next Piece to be fetched is required
		((Iora7Connection*)m_pISAConnection)->Check(rc, &m_handles.m_cda);

	// Oracle can return both 3129 and 3130 (f.ex. in PL/SQL block)
	// we will be ready
	if(m_handles.m_cda.rc == 3129)
		BindLongs();
	if(m_handles.m_cda.rc == 3130) // the buffer for the next Piece to be fetched is required
	{
		assert(m_bPiecewiseBindAllowed);
		m_bPiecewiseFetchPending = true;
		CheckPiecewiseNull(true);
	}

	m_bResultSetExist = (ft == 4);
	ConvertOutputParams();	// if any
}

/*virtual */
void Iora7Cursor::Cancel()
{
	((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.obreak(
		&((Iora7Connection*)m_pISAConnection)->m_handles.m_lda), NULL);
}

void Iora7Cursor::Bind(
		int nPlaceHolderCount,
		saPlaceHolder**	ppPlaceHolders)
{
	// we should bind all params, not place holders in Oracle
	// one exception: :a and :"a" are belong to the same parameter in SQLAPI
	// but Oracle treats them as different
	AllocBindBuffer(sizeof(sb2), sizeof(ub2));
	void *pBuf = m_pParamBuffer;

	for(int i = 0; i < m_pCommand->ParamCount(); ++i)
	{
		SAParam &Param = m_pCommand->ParamByIndex(i);

		void *pInd;
		void *pSize;

		unsigned int nDataBufSize;
		void *pValue;
		IncParamBuffer(pBuf, pInd, pSize, nDataBufSize, pValue);

		SADataType_t eDataType = Param.DataType();
		sword ftype = (sword)(eDataType == SA_dtUnknown?
			1 : // VARCHAR2, some type should be set
			CnvtStdToNative(eDataType));

		sb2 *indp = (sb2 *)pInd;	// bind null indicator
		ub1 *pvctx = (ub1 *)pValue;
		sword progvl = nDataBufSize;	// allocated
		ub2 *alenp = (ub2 *)pSize;

		// special code for ref cursors
		if(eDataType == SA_dtCursor)
		{
			*indp = 0;	// set indicator as if field is not null always, or Oracle can throw an error ("invalid cursor")

			assert(nDataBufSize == sizeof(Cda_Def));
			memset(pvctx, 0, nDataBufSize);
			*alenp = 0;

			if(!Param.isNull() && isInputParam(Param))
			{
				SACommand *pCursor = Param.asCursor();
				assert(pCursor);

				const ora7CommandHandles *pH = (ora7CommandHandles *)pCursor->NativeHandles();
				memcpy(pvctx, &pH->m_cda, sizeof(Cda_Def));

				*alenp = (ub2)InputBufferSize(Param);
			}
		}
		else
		{
			if(isInputParam(Param))
			{
				if(Param.isNull())
					*indp = -1;	// field is null
				else
					*indp = 0;	// field is not null

				*alenp = (ub2)InputBufferSize(Param);
				assert(progvl >= *alenp);

				if(Param.isNull())
				{
					if(progvl == 0)
						progvl = 1;	// dummy, because Oracle can hang when == 0
				}
				else
				{
					switch(eDataType)
					{
					case SA_dtUnknown:
						throw SAException(SA_Library_Error, -1, -1, IDS_UNKNOWN_PARAMETER_TYPE, (const char*)Param.Name());
					case SA_dtBool:
						// there is no "native" boolean type in Oracle,
						// so treat boolean as 16-bit signed INTEGER in Oracle
						assert(*alenp == sizeof(short));
						*(short*)pvctx = (short)Param.asBool();
						break;
					case SA_dtShort:
						assert(*alenp == sizeof(short));
						*(short*)pvctx = Param.asShort();
						break;
					case SA_dtLong:
						assert(*alenp == sizeof(long));
						*(long*)pvctx = Param.asLong();
						break;
					case SA_dtDouble:
						assert(*alenp == sizeof(double));
						*(double*)pvctx = Param.asDouble();
						break;
					case SA_dtDateTime:
						assert(*alenp == sizeof(OraDATE_t));
						IoraConnection::CnvtDateTimeToInternal(
							Param.asDateTime(),
							(OraDATE_t*)pvctx);
						break;
					case SA_dtString:
						assert(*alenp == (ub2)Param.asString().GetLength());
						memcpy(pvctx, (const char*)Param.asString(), *alenp);
						break;
					case SA_dtBytes:
						assert(*alenp == (ub2)Param.asBytes().GetLength());
						memcpy(pvctx, (const char*)Param.asBytes(), *alenp);
						break;
					case SA_dtLongBinary:
					case SA_dtBLob:
						assert(*alenp == sizeof(LongContext_t));
						break;
					case SA_dtLongChar:
					case SA_dtCLob:
						assert(*alenp == sizeof(LongContext_t));
						break;
					case SA_dtCursor:
						assert(false);	// already handled
						break;
					default:
						assert(false);
					}
				}
			}
		}

		bool bLong = isLongOrLob(eDataType);

		for(int j = 0; j < nPlaceHolderCount; ++j)
		{
			saPlaceHolder &PlaceHolder = *ppPlaceHolders[j];
			if(PlaceHolder.getParam() != &Param)
				continue;

			if(bLong)
			{
				LongContext_t *pLongContext = (LongContext_t *)pvctx;
				pLongContext->pReader = &Param;
				pLongContext->pWriter = &Param;
				pLongContext->pInd = (sb2*)pInd;

				if(m_bPiecewiseBindAllowed)
				{
					((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.obindps(
						&m_handles.m_cda,	0,
						(text*)(const char*)PlaceHolder.getFullName(), -1,
						pvctx, SB4MAXVAL, ftype,
						0,	// scale, not used
						indp, (ub2*)0,
						NULL, 0, 0, 0, 0, 0, NULL, NULL, 0, 0), &m_handles.m_cda);	// not used
					pLongContext->eState = LongContextPiecewiseBind;
				}
				else
				{
					((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.obndra(
						&m_handles.m_cda, 
						(text*)(const char*)Param.Name(), -1,
						pvctx, progvl, ftype,
						0,	// scale, not used
						indp, alenp,
						NULL, 0, NULL, NULL, 0, 0), &m_handles.m_cda);	// not used
					pLongContext->eState = LongContextNormal;
				}
			}
			else
			{
				if(m_bPiecewiseBindAllowed)
					((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.obindps(
						&m_handles.m_cda,	1,
						(text*)(const char*)PlaceHolder.getFullName(), -1,
						pvctx, progvl, ftype,
						0,	// scale, not used
						indp, alenp,
						NULL, 0, 0, 0, 0, 0, NULL, NULL, 0, 0), &m_handles.m_cda);	// not used
				else
				{
					((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.obndra(
						&m_handles.m_cda, 
						(text*)(const char*)Param.Name(), -1,
						pvctx, progvl, ftype,
						0,	// scale, not used
						indp, alenp,
						NULL, 0, NULL, NULL, 0, 0), &m_handles.m_cda);	// not used
				}
			}
		}
	}
}

/*virtual */
bool Iora7Cursor::ResultSetExists()
{
	return m_bResultSetExist;
}

void Iora7Cursor::DescribeFields(
	DescribeFields_cb_t fn)
{
	sword iField = 0;
	do
	{
		sb4 dbsize;
		sb2 dbtype;
		sb1 cbuf[1024];
		sb4 cbufl = sizeof(cbuf);
		sb4 dsize;
		sb2 prec;
		sb2 scale;
		sb2 nullok;

		sword rc = g_ora7API.odescr(
			&m_handles.m_cda, ++iField,
			&dbsize,
			&dbtype,
			cbuf,
			&cbufl,
			&dsize,
			&prec,
			&scale,
			&nullok);

		if(m_handles.m_cda.rc == 1007)
			break;
		((Iora7Connection*)m_pISAConnection)->Check(rc, &m_handles.m_cda);

		(m_pCommand->*fn)(
			SAString((const char*)cbuf, cbufl),
			CnvtNativeToStd(dbtype, 0, dbsize, prec, scale),
			(int)dbtype,
			dbsize,
			prec,
			scale,
			nullok == 0);
	}
	while(m_handles.m_cda.rc != 1007);
}

/*virtual */
long Iora7Cursor::GetRowsAffected()
{
	return m_handles.m_cda.rpc;
}

SAField *Iora7Cursor::WhichFieldIsPiecewise() const
{
	// field can be fetched piecewise if:
	// 1. it it Long*
	// 2. it is the last in select list
	// 3. it is the only Long* field in select list
	if(FieldCount(2,
		SA_dtLongBinary, SA_dtLongChar) == 1)
	{
		SAField &Field = m_pCommand->Field(m_pCommand->FieldCount());
		switch(Field.FieldType())
		{
		case SA_dtLongBinary:
		case SA_dtLongChar:
			return &Field;
		default:
			break;
		}
	}
	return 0;
}

/*virtual */
void Iora7Cursor::SetFieldBuffer(
	int nCol,	// 1-based
	void *pInd,
	unsigned int/* nIndSize*/,
	void *pSize,
	unsigned int/* nSizeSize*/,
	void *pValue,
	unsigned int nValueSize)
{
	SAField &Field = m_pCommand->Field(nCol);

	sword ftype;
	bool bLong = false;
	switch(Field.FieldType())
	{
		case SA_dtUnknown:
			throw SAException(SA_Library_Error, -1, -1, IDS_UNKNOWN_COLUMN_TYPE, (const char*)Field.Name());
		case SA_dtShort:
			ftype = 3;	// 16-bit signed integer
			break;
		case SA_dtLong:
			ftype = 3;	// 32-bit signed integer
			break;
		case SA_dtDouble:
			ftype = 4;	// FLOAT
			break;
		case SA_dtNumeric:
			ftype = 6;	// VARNUM
			break;
		case SA_dtDateTime:
			ftype = 12;	// DATE
			break;
		case SA_dtBytes:
			ftype = 23;	// RAW
			break;
		case SA_dtString:
			ftype = 1;	// VARCHAR2
			break;
		case SA_dtLongBinary:
			bLong = true;	// piecewise define
			ftype = 24;	// LONG RAW
			break;
		case SA_dtLongChar:
			bLong = true;	// piecewise define
			ftype = 8;	// LONG
			break;
		case SA_dtCursor:
			ftype = 102;	// CURSOR VARIABLE
			memset(pValue, 0, sizeof(Cda_Def));
			break;
		default:
			ftype = 0;
			assert(false);	// unknown type
	}

	if(bLong)
	{
		LongContext_t *pLongContext = (LongContext_t *)pValue;
		pLongContext->pReader = &Field;
		pLongContext->pWriter = 0;
		pLongContext->pInd = (sb2*)pInd;

		if(m_bPiecewiseFetchAllowed)
		{
			// use piecewise only if this long column is the last column and the only long column
			if(WhichFieldIsPiecewise() == &Field)
			{
				((Iora7Connection*)m_pISAConnection)->Check(
					g_ora7API.odefinps(&m_handles.m_cda, 0, nCol, (ub1*)pLongContext, SB4MAXVAL,
					ftype, 0, (sb2*)pInd,
					NULL, 0, 0,
					(ub2*)pSize,
					NULL, 0, 0, 0, 0), &m_handles.m_cda);
				pLongContext->eState = LongContextPiecewiseDefine;
			}
			else
			{
				((Iora7Connection*)m_pISAConnection)->Check(
					g_ora7API.odefinps(&m_handles.m_cda, 1, nCol, NULL, 0,
					ftype, 0, (sb2*)pInd,
					NULL, 0, 0,
					(ub2*)pSize,
					NULL, 0, 0, 0, 0), &m_handles.m_cda);
				pLongContext->eState = LongContextNormal;
			}
		}
		else
		{
			((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.odefin(&m_handles.m_cda, nCol,
				(ub1*)NULL, 0, ftype,
				0, // scale, not used
				(sb2*)pInd, 
				(text*)NULL, 0, 0, // fmt, fmtl, fmtt, not used
				(ub2*)pSize,
				NULL), &m_handles.m_cda);	// rcode not used
			pLongContext->eState = LongContextNormal;
		}
	}
	else
	{
		if(m_bPiecewiseFetchAllowed)
		{
			((Iora7Connection*)m_pISAConnection)->Check(
				g_ora7API.odefinps(&m_handles.m_cda, 1, nCol, (ub1*)pValue, nValueSize,
				ftype, 0, (sb2*)pInd,
				NULL, 0, 0,
				(ub2*)pSize,
				NULL, 0, 0, 0, 0), &m_handles.m_cda);
		}
		else
		{
			((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.odefin(&m_handles.m_cda, nCol,
				(ub1*)pValue, nValueSize, ftype,
				0, // scale, not used
				(sb2*)pInd, 
				(text*)NULL, 0, 0, // fmt, fmtl, fmtt, not used
				(ub2*)pSize,
				NULL), &m_handles.m_cda);	// rcode not used
		}
	}
}

/*virtual */
void Iora7Cursor::SetSelectBuffers()
{
	// use default helpers
	AllocSelectBuffer(sizeof(sb2), sizeof(ub2));
}

void Iora7Cursor::DiscardPiecewiseFetch()
{
	sword rc;
	do
	{
		ub1 piece;
		dvoid *ctxp;
		ub4 iter, index;
		char buf[0xFFFF];
		ub4 len = sizeof(buf);

		((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.ogetpi(
			&m_handles.m_cda,
			&piece, &ctxp, &iter, &index), &m_handles.m_cda);

		((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.osetpi(
			&m_handles.m_cda,
			piece, buf, &len), &m_handles.m_cda);

		rc = g_ora7API.ofetch(&m_handles.m_cda);
	}
	while(m_handles.m_cda.rc == 3130);
	((Iora7Connection*)m_pISAConnection)->Check(rc, &m_handles.m_cda);

	m_bPiecewiseFetchPending = false;
}

void Iora7Cursor::CheckPiecewiseNull(bool bAfterExecute)
{
	// to check if piecewise fetched column (output param) is null (or not)
	// we have to read at least one byte from piecewise stream
	ub1 piece;
	dvoid *ctxp;
	ub4 iter, index;

	sword rc;
	((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.ogetpi(
		&m_handles.m_cda,
		&piece, &ctxp, &iter, &index), &m_handles.m_cda);
	LongContext_t *pLongContext = (LongContext_t *)ctxp;
	pLongContext->Len = sizeof(m_PiecewiseNullCheckPreFetch);
	((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.osetpi(
		&m_handles.m_cda,
		piece, &m_PiecewiseNullCheckPreFetch[0], &pLongContext->Len), &m_handles.m_cda);

	if(bAfterExecute)
		rc = g_ora7API.oexec(&m_handles.m_cda);
	else
		rc = g_ora7API.ofetch(&m_handles.m_cda);

	if(m_handles.m_cda.rc != 3130)
	{
		((Iora7Connection*)m_pISAConnection)->Check(rc, &m_handles.m_cda);

		// cloumn was null or whole Long* was read
		m_bPiecewiseFetchPending = false;
	}

	// set null indicator manually
	// because Oracle set it only if null or whole read
	*(sb2*)pLongContext->pInd = (sb2)(pLongContext->Len? 0 : -1);

	// if column was not null then fetched piece is saved
	// in m_PiecewiseNullCheckPreFetch, it's len in pLongContext->Len
	// and we will use it when actual read request happen
}

/*virtual */
bool Iora7Cursor::FetchNext()
{
	if(m_bPiecewiseFetchPending)
		DiscardPiecewiseFetch();

	sword rc = g_ora7API.ofetch(&m_handles.m_cda);
	switch(m_handles.m_cda.rc)
	{
	case 1403:
		m_bResultSetExist = false;
		return false;
	case 3130:	// the buffer for the next Piece to be fetched is required
		assert(m_bPiecewiseFetchAllowed);
		m_bPiecewiseFetchPending = true;
		CheckPiecewiseNull();
		break;
	default:
		((Iora7Connection*)m_pISAConnection)->Check(rc, &m_handles.m_cda);
	}

	// use default helpers
	ConvertSelectBufferToFields(0);
	return true;
}

void Iora8Cursor::DestroyLobsReturnBinding()
{
	while(m_nLobReturnBindsColCount)
	{
		while(m_nBLobBindsRowCount)
		{
			OCILobLocator *&pLoc = m_pppBLobReturningLocs[m_nLobReturnBindsColCount-1][m_nBLobBindsRowCount-1];
			if(pLoc)
			{
				Iora8Connection::Check(g_ora8API.OCIDescriptorFree(
					pLoc, OCI_DTYPE_LOB), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
				pLoc = NULL;
			}
			--m_nBLobBindsRowCount;
		}

		delete m_pppBLobReturningLocs[--m_nLobReturnBindsColCount];
		delete m_ppLobReturningLens[m_nLobReturnBindsColCount];
	}
	if(m_ppLobReturnPlaceHolders)
	{
		free(m_ppLobReturnPlaceHolders);
		m_ppLobReturnPlaceHolders = NULL;
	}
	delete m_pppBLobReturningLocs;
	m_pppBLobReturningLocs = NULL;
	delete m_ppLobReturningLens;
	m_ppLobReturningLens = NULL;
}

// There are can be several reasons to reparse (Prepare again)
// already prepared statement:
// 1) if we bind Lobs for update or insert and
//		temporary Lobs are not supported by client or server
//		then we have to add 'returning' clause
// 2) if statement was executed and we rebind with
//		different bind variable datatype (see ORA-01475 error)
void Iora8Cursor::CheckForReparseBeforeBinding(
	int nPlaceHolderCount,
	saPlaceHolder **ppPlaceHolders)
{
	// first check if we have to modify SQL statement and reparse
	// due to Lobs operations and lack of temporary Lobs support

	// quick check, if stmt type is not
	// Insert or Update then nothing to check
	if(m_nOraStmtType == OCI_STMT_UPDATE ||
		m_nOraStmtType == OCI_STMT_INSERT)
	{
		SAString sModifiedStmt;
		SAString sReturning;
		SAString sInto;

		saPlaceHolder **ppLobReturnPlaceHolders = NULL;
		int nLobReturnBindsColCount = 0;
		int nPos = 0;
		for(int i = 0; i < nPlaceHolderCount; ++i)
		{
			sModifiedStmt += m_sOriginalStmt.Mid(nPos, ppPlaceHolders[i]->getStart()-nPos);

			bool bNull = ppPlaceHolders[i]->getParam()->isNull();
			if(!bNull 
				&& ppPlaceHolders[i]->getParam()->DataType() == SA_dtBLob
				&& !((Iora8Connection*)m_pISAConnection)->IsTemporaryLobSupported())
			{
				// replace param marker with empty_blob() function
				sModifiedStmt += "empty_blob()";
				if(!sReturning.IsEmpty())
					sReturning += ", ";
				sReturning += ppPlaceHolders[i]->getParam()->Name();
				if(!sInto.IsEmpty())
					sInto += ", ";
				sInto += ":";
				sInto += ppPlaceHolders[i]->getParam()->Name();

				ppLobReturnPlaceHolders = (saPlaceHolder **)realloc(ppLobReturnPlaceHolders, sizeof(SAParam*)*(nLobReturnBindsColCount+1));
				ppLobReturnPlaceHolders[nLobReturnBindsColCount] = ppPlaceHolders[i];
				++nLobReturnBindsColCount;
			}
			else if(!bNull 
				&& ppPlaceHolders[i]->getParam()->DataType() == SA_dtCLob
				&& !((Iora8Connection*)m_pISAConnection)->IsTemporaryLobSupported())
			{
				// replace param marker with empty_clob() function
				sModifiedStmt += "empty_clob()";
				if(!sReturning.IsEmpty())
					sReturning += ", ";
				sReturning += ppPlaceHolders[i]->getParam()->Name();
				if(!sInto.IsEmpty())
					sInto += ", ";
				sInto += ":";
				sInto += ppPlaceHolders[i]->getParam()->Name();

				ppLobReturnPlaceHolders = (saPlaceHolder **)realloc(ppLobReturnPlaceHolders, sizeof(SAParam*)*(nLobReturnBindsColCount+1));
				ppLobReturnPlaceHolders[nLobReturnBindsColCount] = ppPlaceHolders[i];
				++nLobReturnBindsColCount;
			}
			else	// remain unmodified
				sModifiedStmt += m_sOriginalStmt.Mid(ppPlaceHolders[i]->getStart(), ppPlaceHolders[i]->getEnd()-ppPlaceHolders[i]->getStart()+1);

			nPos = ppPlaceHolders[i]->getEnd() + 1;
		}
		// copy tail
		if(nPos < m_sOriginalStmt.GetLength())
			sModifiedStmt += m_sOriginalStmt.Mid(nPos);

		if(nLobReturnBindsColCount)
		{
			// add/alter returning into clauses
			bool bAdd = true;
			if(bAdd)	// add
			{
				sModifiedStmt += " returning ";
				sModifiedStmt += sReturning;
				sModifiedStmt += " into ";
				sModifiedStmt += sInto;
			}
			else	// modify
			{
			}
		}

		if(nLobReturnBindsColCount	// we have returning clause
			|| m_nLobReturnBindsColCount)	// we had returning clause
		{
			try
			{
				InternalPrepare(sModifiedStmt);
			}
			catch(SAException &)
			{
				if(ppLobReturnPlaceHolders)
					free(ppLobReturnPlaceHolders);
				throw;
			}
		}

		if(nLobReturnBindsColCount)
		{
			m_ppLobReturnPlaceHolders = ppLobReturnPlaceHolders;

			m_pppBLobReturningLocs = new OCILobLocator**[nLobReturnBindsColCount];
			memset(m_pppBLobReturningLocs, 0, sizeof(OCILobLocator**)*nLobReturnBindsColCount);
			m_ppLobReturningLens = new ub4*[nLobReturnBindsColCount];
			memset(m_ppLobReturningLens, 0, sizeof(ub4*)*nLobReturnBindsColCount);
			m_nLobReturnBindsColCount = nLobReturnBindsColCount;
		}
	}

	// then check if we need to reparse to avoid ORA-01475
	if(m_pDTY)	// we have bound before
	{
		for(int i = 0; i < m_pCommand->ParamCount(); ++i)
		{
			SAParam &Param = m_pCommand->ParamByIndex(i);

			SADataType_t eDataType = Param.DataType();
			ub2 dty = (ub2)(eDataType == SA_dtUnknown?
				SQLT_CHR : // VARCHAR2, some type should be set
				CnvtStdToNative(eDataType));

			if(m_pDTY[i] != dty)
			{
				InternalPrepare(m_sOriginalStmt);
				break;
			}
		}
	}
}

void Iora8Cursor::InternalPrepare(
	const SAString &sStmt)
{
	// save because (extraction from Oracle docs):
	// "The pointer to the text of the statement must be available
	// as long as the statement is
	// executed, or data is fetched from it."
	m_sInternalPrepareStmt = sStmt;

	Iora8Connection::Check(g_ora8API.OCIStmtPrepare(
		m_handles.m_pOCIStmt,
		m_handles.m_pOCIError,
		(CONST text*)(const char*)m_sInternalPrepareStmt,
		(ub4)m_sInternalPrepareStmt.GetLength(),
		OCI_NTV_SYNTAX,
		OCI_DEFAULT), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

	m_nOraStmtType = 0;	// unknown
	if(m_pDTY)
	{
		::free(m_pDTY);
		m_pDTY = NULL;
	}
	DestroyLobsReturnBinding();

	// readStmtType
	Iora8Connection::Check(g_ora8API.OCIAttrGet(
		m_handles.m_pOCIStmt, OCI_HTYPE_STMT, &m_nOraStmtType, NULL, OCI_ATTR_STMT_TYPE, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
}

/*virtual */
void Iora8Cursor::Prepare(
	const SAString &sStmt,
	SACommandType_t eCmdType,
	int /*nPlaceHolderCount*/,
	saPlaceHolder**	/*ppPlaceHolders*/)
{
	switch(eCmdType)
	{
		case SA_CmdSQLStmt:
			// save original, we will probably need to reprepare stmt
			// if BLOBs are bound in 8.0.x (not in 8i)
			// or if bind variables types have changed
			m_sOriginalStmt = sStmt;
			break;
		case SA_CmdStoredProc:
			// save original, we will probably need to reprepare stmt
			// if BLOBs are bound in 8.0.x (not in 8i)
			// or if bind variables types have changed
			m_sOriginalStmt = CallSubProgramSQL();
			break;
		default:
			assert(false);
	}

	// always compile original to check errors
	InternalPrepare(m_sOriginalStmt);
}

void Iora8Cursor::CreateTemporaryLob(
	OCILobLocator **ppLob,
	SAParam &Param)
{
	ub1 lobtype;
	switch(Param.DataType())
	{
	case SA_dtBLob:
		lobtype = OCI_TEMP_BLOB;
		break;
	case SA_dtCLob:
		lobtype = OCI_TEMP_CLOB;
		break;
	default:
		assert(false);
		return;
	}

	Iora8Connection::Check(g_ora8API.OCIDescriptorAlloc(
		((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv,
		(dvoid **)ppLob,
		OCI_DTYPE_LOB, 0,
		NULL), ((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv, OCI_HTYPE_ENV);

	Iora8Connection::Check(g_ora8API.OCILobCreateTemporary(
		((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCISvcCtx,
		m_handles.m_pOCIError,
		*ppLob,
		OCI_DEFAULT,
		OCI_DEFAULT,
		lobtype,
		OCI_ATTR_NOCACHE,
		OCI_DURATION_SESSION), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

	++m_cTempLobs;
	m_ppTempLobs = (OCILobLocator **)::realloc(m_ppTempLobs, m_cTempLobs * sizeof(OCILobLocator *));
	m_ppTempLobs[m_cTempLobs-1] = *ppLob;

	BindLob(*ppLob, Param);
}

void Iora8Cursor::Bind(
		int nPlaceHolderCount,
		saPlaceHolder**	ppPlaceHolders)
{
	CheckForReparseBeforeBinding(nPlaceHolderCount, ppPlaceHolders);

	m_pDTY = (ub2*)::realloc(m_pDTY, sizeof(ub2) * m_pCommand->ParamCount());

	// we should bind all params, not place holders in Oracle
	AllocBindBuffer(sizeof(sb2), sizeof(ub2));
	void *pBuf = m_pParamBuffer;

	ub4 nLobReturnBindsColCount = 0;

	for(int i = 0; i < m_pCommand->ParamCount(); ++i)
	{
		SAParam &Param = m_pCommand->ParamByIndex(i);

		void *pInd;
		void *pSize;
		unsigned int nDataBufSize;
		void *pValue;
		IncParamBuffer(pBuf, pInd, pSize, nDataBufSize, pValue);

		SADataType_t eDataType = Param.DataType();
		ub2 dty = (ub2)(eDataType == SA_dtUnknown?
			SQLT_CHR : // VARCHAR2, some type should be set
			CnvtStdToNative(eDataType));
		m_pDTY[i] = dty;

		sb2 *indp = (sb2 *)pInd;	// bind null indicator
		dvoid *valuep = pValue;
		sb4 value_sz = nDataBufSize;	// allocated
		ub2 *alenp = (ub2 *)pSize;

		// this will be adjusted if Param is input
		*alenp = (ub2)nDataBufSize;

		// special code for ref cursors
		if(eDataType == SA_dtCursor)
		{
			*indp = OCI_IND_NOTNULL;	// field is not null

			assert(nDataBufSize == sizeof(OCIStmt *));
			memset(valuep, 0, nDataBufSize);

			Iora8Connection::Check(
				g_ora8API.OCIHandleAlloc(((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv, (dvoid**)valuep, OCI_HTYPE_STMT, 0, NULL),
				((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv, OCI_HTYPE_ENV);

			if(!Param.isNull() && isInputParam(Param))
			{
				SACommand *pCursor = Param.asCursor();
				assert(pCursor);

				const ora8CommandHandles *pH = (ora8CommandHandles *)pCursor->NativeHandles();
				memcpy(valuep, &pH->m_pOCIStmt, sizeof(OCIStmt *));

				*alenp = (ub2)InputBufferSize(Param);
			}
		}
		else
		{
			*indp = OCI_IND_NULL;
			if(isInputParam(Param))
			{
				if(Param.isNull())
					*indp = OCI_IND_NULL;		// field is null
				else
					*indp = OCI_IND_NOTNULL;	// field is not null

				*alenp = (ub2)InputBufferSize(Param);
				assert(value_sz >= *alenp);

				if(!Param.isNull())
				{
					switch(eDataType)
					{
					case SA_dtUnknown:
						throw SAException(SA_Library_Error, -1, -1, IDS_UNKNOWN_PARAMETER_TYPE, (const char*)Param.Name());
					case SA_dtBool:
						// there is no "native" boolean type in Oracle,
						// so treat boolean as 16-bit signed INTEGER in Oracle
						assert(*alenp == sizeof(short));
						*(short*)valuep = (short)Param.asBool();
						break;
					case SA_dtShort:
						assert(*alenp == sizeof(short));
						*(short*)valuep = Param.asShort();
						break;
					case SA_dtLong:
						assert(*alenp == sizeof(long));
						*(long*)valuep = Param.asLong();
						break;
					case SA_dtDouble:
						assert(*alenp == sizeof(double));
						*(double*)valuep = Param.asDouble();
						break;
					case SA_dtDateTime:
						assert(*alenp == sizeof(OraDATE_t));	// Oracle internal date/time representation
						IoraConnection::CnvtDateTimeToInternal(
							Param.asDateTime(),
							(OraDATE_t*)valuep);
						break;
					case SA_dtString:
						assert(*alenp == (ub2)Param.asString().GetLength());
						memcpy(valuep, (const char*)Param.asString(), *alenp);
						break;
					case SA_dtBytes:
						assert(*alenp == (ub2)Param.asBytes().GetLength());
						memcpy(valuep, (const char*)Param.asBytes(), *alenp);
						break;
					case SA_dtLongBinary:
						assert(*alenp == sizeof(LongContext_t));
						break;
					case SA_dtLongChar:
						assert(*alenp == sizeof(LongContext_t));
						break;
					case SA_dtBLob:
					case SA_dtCLob:
						assert(*alenp == sizeof(OCILobLocator *)
							|| *alenp == sizeof(BlobReturningContext_t));
						break;
					case SA_dtCursor:
						assert(false);	// already handled
						break;
					default:
						assert(false);
					}
				}
			}
		}

		bool bLongPiecewise = isLong(eDataType);
		bool bLob = !Param.isNull() && isLob(eDataType);
		bool bLobReturning = bLob && !((Iora8Connection*)m_pISAConnection)->IsTemporaryLobSupported();

		OCIBind* pOCIBind = NULL;
		if(bLongPiecewise)
		{
			Iora8Connection::Check(g_ora8API.OCIBindByName(
				m_handles.m_pOCIStmt,
				&pOCIBind,
				m_handles.m_pOCIError,
				(CONST text*)(const char*)Param.Name(),
				Param.Name().GetLength(),
				valuep, SB4MAXVAL, dty,
				indp, NULL,
				NULL, 0, NULL, OCI_DATA_AT_EXEC), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

			LongContext_t *pLongContext = (LongContext_t *)pValue;
			pLongContext->pReader = &Param;
			pLongContext->pWriter = &Param;
			pLongContext->pInd = indp;

			OCICallbackInBind icbfp = LongInBind;	// always assign InBind, otherwise OutBind is not used and Oracle do piecewise instead of callbacks
			OCICallbackOutBind ocbfp = NULL;
			if(isOutputParam(Param))
				ocbfp = LongOutBind;
			Iora8Connection::Check(g_ora8API.OCIBindDynamic(
				pOCIBind,
				m_handles.m_pOCIError,
				pLongContext,
				icbfp,
				pLongContext,
				ocbfp), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			pLongContext->eState = LongContextCallback;
		}
		else if(bLob)
		{
			if(bLobReturning)
			{
				// bind Lobs returning into
				assert(m_nLobReturnBindsColCount);
				Iora8Connection::Check(g_ora8API.OCIBindByName(
					m_handles.m_pOCIStmt,
					&pOCIBind,
					m_handles.m_pOCIError,
					(CONST text*)(const char*)Param.Name(), Param.Name().GetLength(),
					NULL, sizeof(OCILobLocator*), dty,
					NULL, NULL,
					NULL, 0, NULL, OCI_DATA_AT_EXEC), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

				BlobReturningContext_t *pCtx = (BlobReturningContext_t *)valuep;
				pCtx->pParam = &Param;
				pCtx->pOCIError = m_handles.m_pOCIError;
				pCtx->pOCIEnv = ((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv;
				pCtx->pppOCILobLocators = m_pppBLobReturningLocs;
				pCtx->ppLobLocatorsLens = m_ppLobReturningLens;
				pCtx->nLobLocatorCol = nLobReturnBindsColCount++;
				pCtx->pnLobReturnBindsColCount = &m_nLobReturnBindsColCount;
				pCtx->pnBLobBindsRowCount = &m_nBLobBindsRowCount;
				Iora8Connection::Check(g_ora8API.OCIBindDynamic(
					pOCIBind,
					m_handles.m_pOCIError,
					NULL,
					LobReturningInBind,
					pCtx,
					LobReturningOutBind), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			}
			else
			{
				CreateTemporaryLob((OCILobLocator **)valuep, Param);
				Iora8Connection::Check(g_ora8API.OCIBindByName(
					m_handles.m_pOCIStmt,
					&pOCIBind,
					m_handles.m_pOCIError,
					(CONST text*)(const char*)Param.Name(),
					Param.Name().GetLength(),
					valuep, value_sz, dty,
					indp, alenp,
					NULL, 0, NULL, OCI_DEFAULT), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			}
		}
		else
		{
			switch(eDataType)
			{
			case SA_dtString:
			case SA_dtBytes:
				break;
			default:
				// to avoid Ora-03135 or Ora-01460
				value_sz = *alenp;
				alenp = NULL;
			}
			Iora8Connection::Check(g_ora8API.OCIBindByName(
				m_handles.m_pOCIStmt,
				&pOCIBind,
				m_handles.m_pOCIError,
				(CONST text*)(const char*)Param.Name(),
				Param.Name().GetLength(),
				valuep, value_sz, dty,
				indp, alenp,
				NULL, 0, NULL, OCI_DEFAULT), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
		}
	}

	assert(nLobReturnBindsColCount == m_nLobReturnBindsColCount);
}

/*virtual */
void Iora8Cursor::UnExecute()
{
	m_bResultSetCanBe = false;
}

/*virtual */
void Iora8Cursor::Execute(
	int nPlaceHolderCount,
	saPlaceHolder **ppPlaceHolders)
{
	if(nPlaceHolderCount)
		Bind(nPlaceHolderCount, ppPlaceHolders);

	try
	{
		// check for bulk reading
		SAString sOption = m_pCommand->Option(
			"PreFetchRows");

		if(!sOption.IsEmpty())
		{
			ub4   prefetch = (ub4)atoi(sOption);	// prefetch rows count
			Iora8Connection::Check(g_ora8API.OCIAttrSet(m_handles.m_pOCIStmt,
				OCI_HTYPE_STMT,
				&prefetch,
				0,
				OCI_ATTR_PREFETCH_ROWS,
				m_handles.m_pOCIError),
				m_handles.m_pOCIError, OCI_HTYPE_ERROR, m_handles.m_pOCIStmt);
		}

		ub4 mode = OCI_DEFAULT;
		if(m_pCommand->Connection()->AutoCommit() == SA_AutoCommitOn)
			mode |= OCI_COMMIT_ON_SUCCESS;
		sword rc = g_ora8API.OCIStmtExecute(
			((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCISvcCtx,
			m_handles.m_pOCIStmt,
			m_handles.m_pOCIError,
			m_nOraStmtType == OCI_STMT_SELECT? 0 : 1,
			0,
			(OCISnapshot*)NULL, (OCISnapshot*)NULL, mode);

		Iora8Connection::Check(rc, m_handles.m_pOCIError, OCI_HTYPE_ERROR, m_handles.m_pOCIStmt);

		if(m_nLobReturnBindsColCount)
			BindReturningLobs();

		m_bResultSetCanBe = true;

		ConvertOutputParams();	// if any

		FreeTemporaryLobsIfAny();
	}
	catch(SAException &)	// clean-up
	{
		try
		{
			FreeTemporaryLobsIfAny();
		}
		catch(SAException &)
		{
		}
		throw;
	}
}

/*virtual */
void Iora8Cursor::Cancel()
{
	Iora8Connection::Check(g_ora8API.OCIBreak(
		((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCISvcCtx,
		m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
}

// returns total size written
ub4 Iora8Cursor::BindLob(
		OCILobLocator *pLob,
		SAParam &Param)
{
	unsigned int nActualWrite;
	SAPieceType_t ePieceType = SA_FirstPiece;
	void *pBuf;

	ub4 offset = 1;

	while((nActualWrite = Param.InvokeWriter(
		ePieceType,
		SB4MAXVAL, pBuf)) != 0)
	{
		ub4 amt = nActualWrite;
		Iora8Connection::Check(g_ora8API.OCILobWrite(
			((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCISvcCtx,
			m_handles.m_pOCIError,
			pLob,
			&amt,
			offset,
			pBuf,
			nActualWrite,
			OCI_ONE_PIECE,
			NULL,
			NULL,
			0, SQLCS_IMPLICIT), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

		offset += nActualWrite;

		if(ePieceType == SA_LastPiece)
			break;
	}

	return offset - 1;
}

void Iora8Cursor::BindReturningLobs()
{
	for(unsigned int nCol = 0; nCol < m_nLobReturnBindsColCount; ++nCol)
	{
		SAParam &Param = *m_ppLobReturnPlaceHolders[nCol]->getParam();

		ub4 nLobSize = 0;

		for(unsigned int nRow = 0; nRow < m_nBLobBindsRowCount; ++nRow)
		{
			if(nRow == 0)
				nLobSize = BindLob(m_pppBLobReturningLocs[nCol][0], Param);
			else
			{
				Iora8Connection::Check(g_ora8API.OCILobCopy(
					((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCISvcCtx,
					m_handles.m_pOCIError,
					m_pppBLobReturningLocs[nCol][nRow],
					m_pppBLobReturningLocs[nCol][0],
					nLobSize,
					1, 1), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			}
		}
	}
}

/*static */
sb4 Iora8Cursor::LongInBind(
	dvoid *ictxp,
	OCIBind * /*bindp*/,
	ub4/* iter*/,
	ub4/* index*/,
	dvoid **bufpp,
	ub4 *alenp,
	ub1 *piecep,
	dvoid **indpp)
{
	LongContext_t *pLongContext = (LongContext_t*)ictxp;

	if(!isInputParam(*(SAParam*)pLongContext->pWriter))
	{
		*pLongContext->pInd = -1;
		*bufpp = NULL;
		*alenp = 0;
		*piecep = OCI_ONE_PIECE;
		*indpp = pLongContext->pInd;
		return OCI_CONTINUE;
	}

	SAPieceType_t ePieceType;
	if(*piecep == OCI_FIRST_PIECE)
		ePieceType = SA_FirstPiece;
	else if(*piecep == OCI_NEXT_PIECE)
		ePieceType = SA_NextPiece;
	else
		assert(false);

	*alenp =
		pLongContext->pWriter->InvokeWriter(ePieceType, Iora8Connection::MaxLongPiece, *bufpp);
	if(!*alenp || ePieceType == SA_LastPiece)
		*piecep = OCI_LAST_PIECE;
	if(!*alenp)
		*bufpp = NULL;

	return OCI_CONTINUE;
}

/*static */
sb4 Iora8Cursor::LongOutBind(
	dvoid *octxp,
	OCIBind * /*bindp*/,
	ub4/* iter*/,
	ub4/* index*/,
	dvoid **bufpp,
	ub4 **alenpp,
	ub1 *piecep,
	dvoid **indpp,
	ub2 ** /*rcodep*/)
{
	return LongDefineOrOutBind(
		octxp, bufpp, alenpp, piecep, indpp);
}

/*static */
sb4 Iora8Cursor::LobReturningInBind(
	dvoid * /*ictxp*/,
	OCIBind * /*bindp*/,
	ub4/* iter*/,
	ub4/* index*/,
	dvoid **bufpp,
	ub4 *alenp,
	ub1 *piecep,
	dvoid **indpp)
{
  *bufpp = NULL;
  *alenp = 0;
  *piecep = OCI_ONE_PIECE;
  *indpp = &stat_m_BLobReturningNullInd;

  return OCI_CONTINUE;
}

/*static */
sb4 Iora8Cursor::LobReturningOutBind(
	dvoid *octxp,
	OCIBind *bindp,
	ub4/* iter*/,
	ub4 index,
	dvoid **bufpp,
	ub4 **alenp,
	ub1 *piecep,
	dvoid ** /*indpp*/,
	ub2 ** /*rcodep*/)
{
	BlobReturningContext_t *pCtx = (BlobReturningContext_t *)octxp;
	if(index == 0 && pCtx->nLobLocatorCol == 0)
	{
		assert(*pCtx->pnBLobBindsRowCount == 0);
		Iora8Connection::Check(g_ora8API.OCIAttrGet(
			bindp, OCI_HTYPE_BIND, pCtx->pnBLobBindsRowCount, NULL, OCI_ATTR_ROWS_RETURNED, pCtx->pOCIError),
			pCtx->pOCIError, OCI_HTYPE_ERROR);

		for(unsigned int nCol = 0; nCol < *pCtx->pnLobReturnBindsColCount; ++nCol)
		{
			assert(pCtx->pppOCILobLocators[nCol] == NULL);
			pCtx->pppOCILobLocators[nCol] = new OCILobLocator*[*pCtx->pnBLobBindsRowCount];
			memset(pCtx->pppOCILobLocators[nCol], 0, sizeof(OCILobLocator*)* *pCtx->pnBLobBindsRowCount);
			assert(pCtx->ppLobLocatorsLens[nCol] == NULL);
			pCtx->ppLobLocatorsLens[nCol] = new ub4[*pCtx->pnBLobBindsRowCount];
			// allocate Lob locators for all rows in this bind
			for(unsigned int nRow = 0; nRow < *pCtx->pnBLobBindsRowCount; nRow++)
			{
				Iora8Connection::Check(g_ora8API.OCIDescriptorAlloc(
					pCtx->pOCIEnv,
					(dvoid**)&pCtx->pppOCILobLocators[nCol][nRow],
					OCI_DTYPE_LOB, 0, NULL), pCtx->pOCIEnv, OCI_HTYPE_ENV);
				pCtx->ppLobLocatorsLens[nCol][nRow] = sizeof(OCILobLocator*);
			}
		}
	}

	*bufpp	= pCtx->pppOCILobLocators[pCtx->nLobLocatorCol][index];
	*alenp	= &pCtx->ppLobLocatorsLens[pCtx->nLobLocatorCol][index];
	*piecep	= OCI_ONE_PIECE;

	return OCI_CONTINUE;
}

bool Iora8Cursor::ResultSetExists()
{
	if(!m_bResultSetCanBe)
		return false;

	switch(m_nOraStmtType)
	{
	case OCI_STMT_SELECT:
		return true;
	case OCI_STMT_UPDATE:
		return false;
	case OCI_STMT_DELETE:
		return false;
	case OCI_STMT_INSERT:
		return false;
	case OCI_STMT_CREATE:
	case OCI_STMT_DROP:
	case OCI_STMT_ALTER:
		return false;
	case OCI_STMT_BEGIN:
	case OCI_STMT_DECLARE:
		return false;
	}

	return false;
}

/*virtual */
SADataType_t Iora8Cursor::CnvtNativeToStd(
	int dbtype,
	int dbsubtype,
	int dbsize,
	int prec,
	int scale) const
{
	switch(dbtype)
	{
	case SQLT_CLOB:	// character lob
		return SA_dtCLob;
	case SQLT_BLOB:	// binary lob
		return SA_dtBLob;
	case SQLT_BFILEE:	// binary file lob
		return SA_dtBLob;
	case SQLT_CFILEE:	// character file lob
		return SA_dtCLob;
	case SQLT_RSET:	// result set type
		return SA_dtCursor;

	default:
		break;
	}

	return IoraCursor::CnvtNativeToStd(
		dbtype,
		dbsubtype,
		dbsize,
		prec,
		scale);
}

/*virtual */
void Iora8Cursor::DescribeFields(
	DescribeFields_cb_t fn)
{
	// get col count
	ub4 cFields;
	Iora8Connection::Check(g_ora8API.OCIAttrGet(m_handles.m_pOCIStmt, OCI_HTYPE_STMT, &cFields, NULL, OCI_ATTR_PARAM_COUNT, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

	for(ub4 iField = 1; iField <= cFields; ++iField)
	{
		OCIParam *pOCIParam = NULL;
		Iora8Connection::Check(g_ora8API.OCIParamGet(
			m_handles.m_pOCIStmt,
			OCI_HTYPE_STMT,
			m_handles.m_pOCIError,
			(dvoid**)&pOCIParam,
			iField), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

		char *sColName;
		ub4 nColNameLen;
		ub2 dbtype;
		ub2 dbsize;
		sb2 prec;
		sb1 scale;
		ub1 isnull;

		Iora8Connection::Check(g_ora8API.OCIAttrGet(pOCIParam, OCI_DTYPE_PARAM,
    				 (dvoid*)&sColName, &nColNameLen, OCI_ATTR_NAME, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
		Iora8Connection::Check(g_ora8API.OCIAttrGet(pOCIParam, OCI_DTYPE_PARAM,
    				 &dbtype, NULL, OCI_ATTR_DATA_TYPE, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
		Iora8Connection::Check(g_ora8API.OCIAttrGet(pOCIParam, OCI_DTYPE_PARAM,
    				 &dbsize, NULL, OCI_ATTR_DATA_SIZE, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
		Iora8Connection::Check(g_ora8API.OCIAttrGet(pOCIParam, OCI_DTYPE_PARAM,
    				 &prec, NULL, OCI_ATTR_PRECISION, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
		Iora8Connection::Check(g_ora8API.OCIAttrGet(pOCIParam, OCI_DTYPE_PARAM,
    				 &scale, NULL, OCI_ATTR_SCALE, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
		Iora8Connection::Check(g_ora8API.OCIAttrGet(pOCIParam, OCI_DTYPE_PARAM,
    				 &isnull, NULL, OCI_ATTR_IS_NULL, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

		(m_pCommand->*fn)(
			SAString(sColName, nColNameLen),
			CnvtNativeToStd(dbtype, 0, dbsize, prec, scale),
			(int)dbtype,
			dbsize,
			prec,
			scale,
			isnull == 0);
	}
}

/*
bool Iora8Cursor::DescribeField(
	unsigned int nField,	// 1-based
	SAString &sName,
	SADataType_t &eFieldType,
	int &nNativeType,
	int &nFieldSize,
	int &nFieldPrecision,
	int &nFieldScale,
	bool &bFieldRequired)
{
	// get col count
	ub4 nColCount;
	Iora8Connection::Check(g_ora8API.OCIAttrGet(m_handles.m_pOCIStmt, OCI_HTYPE_STMT, &nColCount, NULL, OCI_ATTR_PARAM_COUNT, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
	if(nColCount < nField)
		return false;

	OCIParam *pOCIParam = NULL;
	Iora8Connection::Check(g_ora8API.OCIParamGet(
		m_handles.m_pOCIStmt,
		OCI_HTYPE_STMT,
		m_handles.m_pOCIError,
		(dvoid**)&pOCIParam,
		nField), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

	char *sColName;
	ub4 nColNameLen;
	ub2 dbtype;
	ub2 dbsize;
	sb2 prec;
	sb1 scale;
	ub1 isnull;

    Iora8Connection::Check(g_ora8API.OCIAttrGet(pOCIParam, OCI_DTYPE_PARAM,
    			 (dvoid*)&sColName, &nColNameLen, OCI_ATTR_NAME, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
    Iora8Connection::Check(g_ora8API.OCIAttrGet(pOCIParam, OCI_DTYPE_PARAM,
    			 &dbtype, NULL, OCI_ATTR_DATA_TYPE, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
    Iora8Connection::Check(g_ora8API.OCIAttrGet(pOCIParam, OCI_DTYPE_PARAM,
    			 &dbsize, NULL, OCI_ATTR_DATA_SIZE, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
    Iora8Connection::Check(g_ora8API.OCIAttrGet(pOCIParam, OCI_DTYPE_PARAM,
    			 &prec, NULL, OCI_ATTR_PRECISION, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
    Iora8Connection::Check(g_ora8API.OCIAttrGet(pOCIParam, OCI_DTYPE_PARAM,
    			 &scale, NULL, OCI_ATTR_SCALE, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
    Iora8Connection::Check(g_ora8API.OCIAttrGet(pOCIParam, OCI_DTYPE_PARAM,
    			 &isnull, NULL, OCI_ATTR_IS_NULL, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

	sName = SAString(sColName, nColNameLen);
	eFieldType = CnvtNativeToStd(
		dbtype, 0, dbsize, prec, scale);
	nNativeType = (int)dbtype;
	nFieldSize = dbsize;
	nFieldPrecision = prec;
	nFieldScale = scale;
	bFieldRequired = isnull == 0;
	return true;
}
*/
/*virtual */
long Iora8Cursor::GetRowsAffected()
{
	ub4 rows;

	Iora8Connection::Check(g_ora8API.OCIAttrGet(
		m_handles.m_pOCIStmt, OCI_HTYPE_STMT, &rows, NULL, OCI_ATTR_ROW_COUNT, m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
	return rows;
}

SAField *Iora8Cursor::WhichFieldIsPiecewise() const
{
	// because of serious bug in 8i
	// with piecewise reading of LONG
	// we will not use it (piecewise reading of LONG)
	// will use callbacks instead
	return NULL;

//	// field can be fetched piecewise if:
//	// 1. it it Long*
//	// 2. it is the last in select list (else we will block fields after this)
//	// 3. there are no *Lob fields in select list (else we will block them until piecewise)
//	// 4. other Long* are allowed because they will be read by callbacks (no blocking)
//	if(FieldCount(2, SA_dtBLob, SA_dtCLob) == 0)
//	{
//		SAField &Field = m_pCommand->Field(m_pCommand->FieldCount());
//
//		switch(Field.FieldType())
//		{
//		case SA_dtLongBinary:
//		case SA_dtLongChar:
//			return &Field;
//		default:
//			break;
//		}
//	}
//
//	return NULL;
}

/*virtual */
void Iora8Cursor::SetFieldBuffer(
	int nCol,	// 1-based
	void *pInd,
	unsigned int nIndSize,
	void *pSize,
	unsigned int/* nSizeSize*/,
	void *pValue,
	unsigned int nValueSize)
{
	assert(nIndSize == sizeof(sb2));
	if(nIndSize != sizeof(sb2))
		return;

	SAField &Field = m_pCommand->Field(nCol);

	ub2 dty;
	bool bLong = false;
	switch(Field.FieldType())
	{
		case SA_dtUnknown:
			throw SAException(SA_Library_Error, -1, -1, IDS_UNKNOWN_COLUMN_TYPE, (const char*)Field.Name());
		case SA_dtShort:
			dty = SQLT_INT;	// 16-bit signed INTEGER
			break;
		case SA_dtLong:
			dty = SQLT_INT;	// 32-bit signed INTEGER
			break;
		case SA_dtDouble:
			dty = SQLT_FLT;	// FLOAT
			break;
		case SA_dtNumeric:
			dty = SQLT_VNU;	// VARNUM
			break;
		case SA_dtDateTime:
			dty = SQLT_DAT;	// DATE
			break;
		case SA_dtBytes:
			dty = SQLT_BIN;	// binary data(DTYBIN)
			break;
		case SA_dtString:
			dty = SQLT_CHR;	// VARCHAR2
			break;
		case SA_dtLongBinary:
			dty = SQLT_LBI;	// LONG RAW
			assert(nValueSize == sizeof(LongContext_t));
			bLong = true;
			break;
		case SA_dtLongChar:
			dty = SQLT_LNG;	// LONG
			assert(nValueSize == sizeof(LongContext_t));
			bLong = true;
			break;
		case SA_dtBLob:
			if(Field.FieldNativeType() == SQLT_BFILE)
			{
				dty = SQLT_BFILE;
				Iora8Connection::Check(g_ora8API.OCIDescriptorAlloc(
					((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv,
					(dvoid**)pValue, OCI_DTYPE_FILE, 0, NULL),
					((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv, OCI_HTYPE_ENV);
			}
			else
			{
				dty = SQLT_BLOB;	// Binary LOB
				Iora8Connection::Check(g_ora8API.OCIDescriptorAlloc(
					((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv,
					(dvoid**)pValue, OCI_DTYPE_LOB, 0, NULL),
					((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv, OCI_HTYPE_ENV);
			}
			break;
		case SA_dtCLob:
			dty = SQLT_CLOB;	// Character LOB
			Iora8Connection::Check(g_ora8API.OCIDescriptorAlloc(
				((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv,
				(dvoid**)pValue, OCI_DTYPE_LOB, 0, NULL),
				((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv, OCI_HTYPE_ENV);
			break;
		case SA_dtCursor:
			dty = SQLT_RSET;	// result set type
			Iora8Connection::Check(
				g_ora8API.OCIHandleAlloc(((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv, (dvoid**)pValue, OCI_HTYPE_STMT, 0, NULL),
				((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv, OCI_HTYPE_ENV);
			break;
		default:
			dty = 0;
			assert(false);	// unknown type
	}

	OCIDefine *pOCIDefine = NULL;
	if(bLong)
	{
		Iora8Connection::Check(g_ora8API.OCIDefineByPos(
			m_handles.m_pOCIStmt, &pOCIDefine, m_handles.m_pOCIError, nCol, NULL, SB4MAXVAL,
			dty, pInd, (ub2*)pSize, 
			NULL, OCI_DYNAMIC_FETCH), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

		LongContext_t *pLongContext = (LongContext_t *)pValue;
		pLongContext->pReader = &Field;
		pLongContext->pWriter = 0;
		pLongContext->pInd = (sb2*)pInd;

		// check if this long should be piecewised
		if(WhichFieldIsPiecewise() == &Field)
			pLongContext->eState = LongContextPiecewiseDefine;
		else	// if not then callbacks
		{
			Iora8Connection::Check(g_ora8API.OCIDefineDynamic(
					pOCIDefine,
					m_handles.m_pOCIError,
					(dvoid*)pLongContext,
					LongDefine), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			pLongContext->eState = LongContextCallback;
		}
	}
	else
	{
		Iora8Connection::Check(g_ora8API.OCIDefineByPos(
			m_handles.m_pOCIStmt, &pOCIDefine, m_handles.m_pOCIError, nCol, pValue, nValueSize,
			dty, pInd, (ub2*)pSize, 
			NULL, OCI_DEFAULT), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
	}
}

/*virtual */
void Iora8Cursor::SetSelectBuffers()
{
	// use default helpers
	AllocSelectBuffer(sizeof(sb2), sizeof(ub2));
}

void Iora8Cursor::CheckPiecewiseNull()
{
	// because of serious bug in 8i
	// with piecewise reading of LONG
	// we will not use it (piecewise reading of LONG)
	// will use callbacks instead
	// so this function will never be called
	assert(false);

	SAField *pField = WhichFieldIsPiecewise();
	assert(pField);
	void *pValue;
	unsigned int nFieldBufSize;
	GetFieldBuffer(pField->Pos(), pValue, nFieldBufSize);
	assert(nFieldBufSize == sizeof(LongContext_t));
	LongContext_t *pLongContext = (LongContext_t *)pValue;

	// to check if piecewise fetched column is null (or not)
	// we have to read at least one byte from piecewise stream
	OCIDefine *pOCIDefine;
	ub4 type;
	ub1 in_out;
	ub4 iter, idx;
	ub1 piece;

	sword rc;
	Iora8Connection::Check(g_ora8API.OCIStmtGetPieceInfo(
		m_handles.m_pOCIStmt,
		m_handles.m_pOCIError,
		(dvoid**)&pOCIDefine,
		&type,
		&in_out,
		&iter, &idx,
		&piece), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
	pLongContext->Len = sizeof(m_PiecewiseNullCheckPreFetch);
	Iora8Connection::Check(g_ora8API.OCIStmtSetPieceInfo(
		pOCIDefine,
		type,
		m_handles.m_pOCIError,
		&m_PiecewiseNullCheckPreFetch[0], &pLongContext->Len,
		piece,
		pLongContext->pInd,
		NULL), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

	rc = g_ora8API.OCIStmtFetch(m_handles.m_pOCIStmt, m_handles.m_pOCIError, 1, OCI_FETCH_NEXT, OCI_DEFAULT);

	if(rc != OCI_NEED_DATA)
	{
		Iora8Connection::Check(rc, m_handles.m_pOCIError, OCI_HTYPE_ERROR);

		// cloumn was null or whole Long* was read
		m_bPiecewiseFetchPending = false;
	}

	// set null indicator manually
	// because Oracle set it only if null or whole read
	*(sb2*)pLongContext->pInd = (sb2)(pLongContext->Len? 0 : -1);

	// if column was not null then fetched piece is saved
	// in m_PiecewiseNullCheckPreFetch, it's len in pLongContext->Len
	// and we will use it when actual read request happen
}

/*virtual */
bool Iora8Cursor::FetchNext()
{
	if(m_bPiecewiseFetchPending)
		DiscardPiecewiseFetch();

	sword rc = g_ora8API.OCIStmtFetch(m_handles.m_pOCIStmt, m_handles.m_pOCIError, 1, OCI_FETCH_NEXT, OCI_DEFAULT);
	if(rc != OCI_NO_DATA)
	{
		if(rc != OCI_NEED_DATA)
			Iora8Connection::Check(rc, m_handles.m_pOCIError, OCI_HTYPE_ERROR);
		else
		{
			m_bPiecewiseFetchPending = true;
			CheckPiecewiseNull();
		}

		// use default helpers
		ConvertSelectBufferToFields(0);
		return true;
	}
	else
		m_bResultSetCanBe = false;

	return false;
}

void Iora8Cursor::DiscardPiecewiseFetch()
{
	OCIDefine *pOCIDefine;
	ub4 type;
	ub1 in_out;
	ub4 iter, idx;
	ub1 piece;
	sb2 ind;
	char buf[0xFFFF];
	ub4 alen = sizeof(buf);

	sword rc;
	do
	{
		Iora8Connection::Check(g_ora8API.OCIStmtGetPieceInfo(
			m_handles.m_pOCIStmt,
			m_handles.m_pOCIError,
			(dvoid**)&pOCIDefine,
			&type,
			&in_out,
			&iter, &idx,
			&piece), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
		Iora8Connection::Check(g_ora8API.OCIStmtSetPieceInfo(
			pOCIDefine,
			type,
			m_handles.m_pOCIError,
			buf, &alen,
			piece,
			&ind,
			NULL), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

		rc = g_ora8API.OCIStmtFetch(m_handles.m_pOCIStmt, m_handles.m_pOCIError, 1, OCI_FETCH_NEXT, OCI_DEFAULT);
	}
	while(rc == OCI_NEED_DATA);
	Iora8Connection::Check(rc, m_handles.m_pOCIError, OCI_HTYPE_ERROR);

	m_bPiecewiseFetchPending = false;
}

/*virtual */
void Iora7Cursor::ReadLongOrLOB(
	ValueType_t eValueType,
	SAValueRead &vr,
	void *pValue,
	unsigned int/* nBufSize*/,
	saLongOrLobReader_t fnReader,
	unsigned int nReaderWantedPieceSize,
	void *pAddlData)
{
	LongContext_t *pLongContext = (LongContext_t *)pValue;
	unsigned int nLongSize = 0;	// no way to determine size before fetch
	unsigned char* pBuf;
	unsigned int nPortionSize = vr.PrepareReader(
		nLongSize,
		Iora7Connection::MaxLongPortion,
		pBuf,
		fnReader,
		nReaderWantedPieceSize,
		pAddlData);
	assert(nPortionSize <= Iora7Connection::MaxLongPortion);

	if(pLongContext->eState & LongContextPiecewise)
	{
		SAPieceType_t ePieceType = SA_FirstPiece;
		// for SQLAPI Callback prefetching should be transparent
		// so, first use prefetched (when checking for null) data
		// and send it as if it was just fetched from Oracle
		unsigned int nPrefetchedSent = 0;
		while(pLongContext->Len - nPrefetchedSent >= nPortionSize)
		{
			memcpy(pBuf, m_PiecewiseNullCheckPreFetch+nPrefetchedSent, nPortionSize);
			nPrefetchedSent += nPortionSize;

            if(!m_bPiecewiseFetchPending)	// all data was fetched during prefetch
			{
				if(pLongContext->Len == nPrefetchedSent)
				{
                    if(ePieceType == SA_NextPiece)
                        ePieceType = SA_LastPiece;
                    else    // the whole Long was read in one piece
                    {
                        assert(ePieceType == SA_FirstPiece);
                        ePieceType = SA_OnePiece;
                    }
				}
			}
			vr.InvokeReader(ePieceType, pBuf, nPortionSize);

			if(ePieceType == SA_FirstPiece)
				ePieceType = SA_NextPiece;
		}

		// then if needed fetch all remaining data
		if(m_bPiecewiseFetchPending)
		{
			sword rc = 0;
			do
			{
				ub1 piece;
				dvoid *ctxp;
				ub4 iter, index;
				ub4 len = nPortionSize;

				// a tail from prefetching buffer remains?
				unsigned int nPrefetchedTail = pLongContext->Len - nPrefetchedSent;
				assert(nPrefetchedTail < nPortionSize);
				if(nPrefetchedTail)
				{
					memcpy(pBuf, m_PiecewiseNullCheckPreFetch+nPrefetchedSent, nPrefetchedTail);
					nPrefetchedSent += nPrefetchedTail;
					// we will ask Oracle to read less during this piece
					len -= nPrefetchedTail;
				}
				assert(pLongContext->Len == nPrefetchedSent);

				((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.ogetpi(
					&m_handles.m_cda,
					&piece, &ctxp, &iter, &index), &m_handles.m_cda);
				((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.osetpi(
					&m_handles.m_cda,
					piece, pBuf+nPrefetchedTail, &len), &m_handles.m_cda);

				switch(pLongContext->eState)
				{
				case LongContextPiecewiseDefine:
					rc = g_ora7API.ofetch(&m_handles.m_cda);
					break;
				case LongContextPiecewiseBind:
					rc = g_ora7API.oexec(&m_handles.m_cda);
					break;
				default:
					assert(false);
				}

				if(m_handles.m_cda.rc != 3130)
				{
                    if(ePieceType == SA_NextPiece)
                        ePieceType = SA_LastPiece;
                    else    // the whole Long was read in one piece
                    {
                        assert(ePieceType == SA_FirstPiece);
                        ePieceType = SA_OnePiece;
                    }
				}
				vr.InvokeReader(ePieceType, pBuf, nPrefetchedTail+len);

				if(ePieceType == SA_FirstPiece)
					ePieceType = SA_NextPiece;
			}
			while(m_handles.m_cda.rc == 3130);
			((Iora7Connection*)m_pISAConnection)->Check(rc, &m_handles.m_cda);

			m_bPiecewiseFetchPending = false;
		}
	}
	else
	{
		assert(pLongContext->eState == LongContextNormal);
		if(eValueType == ISA_FieldValue)
		{
			SAField &Field = (SAField &)vr;

			SAPieceType_t ePieceType = SA_FirstPiece;
			ub4 retl;
			sb4 offset = 0;
			sword dtype;
			switch(Field.FieldType())
			{
			case SA_dtLongBinary:
				dtype = 24;	// LONG RAW
				break;
			case SA_dtLongChar:
				dtype = 8;	// LONG
				break;
			default:
				dtype = 0;
				assert(false);
			}
			do
			{
				((Iora7Connection*)m_pISAConnection)->Check(
					g_ora7API.oflng(&m_handles.m_cda, Field.Pos(), pBuf, nPortionSize,
					dtype,
					&retl, offset), &m_handles.m_cda);

                if(retl < nPortionSize)
                {
                    if(ePieceType == SA_NextPiece)
                        ePieceType = SA_LastPiece;
                    else    // the whole Long was read in one piece
                    {
                        assert(ePieceType == SA_FirstPiece);
                        ePieceType = SA_OnePiece;
                    }
                }
				vr.InvokeReader(ePieceType, pBuf, retl);

				offset += retl;

				if(ePieceType == SA_FirstPiece)
					ePieceType = SA_NextPiece;
			}
			while(retl == nPortionSize);
		}
		else
		{
			assert(false);
		}
	}
}

void Iora8Cursor::ReadLong(
	LongContext_t *pLongContext,
	saLongOrLobReader_t fnReader,
	unsigned int nReaderWantedPieceSize,
	void *pAddlData)
{
	if(pLongContext->eState & LongContextPiecewise)
	{
		assert(pLongContext->pReader == WhichFieldIsPiecewise());

		unsigned int nBlobSize = 0;	// no way to determine size before fetch

		unsigned char* pBuf;
		unsigned int nPortionSize = pLongContext->pReader->PrepareReader(
			nBlobSize,
			SB4MAXVAL,
			pBuf,
			fnReader,
			nReaderWantedPieceSize,
			pAddlData);

		SAPieceType_t ePieceType = SA_FirstPiece;
		// for SQLAPI Callback prefetching should be transparent
		// so, first use prefetched (when checking for null) data
		// and send it as if it was just fetched from Oracle
		unsigned int nPrefetchedSent = 0;
		while(pLongContext->Len - nPrefetchedSent >= nPortionSize)
		{
			memcpy(pBuf, m_PiecewiseNullCheckPreFetch+nPrefetchedSent, nPortionSize);
			nPrefetchedSent += nPortionSize;

            if(!m_bPiecewiseFetchPending)	// all data was fetched during prefetch
			{
				if(pLongContext->Len == nPrefetchedSent)
				{
                    if(ePieceType == SA_NextPiece)
                        ePieceType = SA_LastPiece;
                    else    // the whole Long was read in one piece
                    {
                        assert(ePieceType == SA_FirstPiece);
                        ePieceType = SA_OnePiece;
                    }
				}
			}
			pLongContext->pReader->InvokeReader(ePieceType, pBuf, nPortionSize);

			if(ePieceType == SA_FirstPiece)
				ePieceType = SA_NextPiece;
		}

		// then if needed fetch all remaining data
		if(m_bPiecewiseFetchPending)
		{
			sword rc;
			do
			{
				OCIDefine *pOCIDefine;
				ub4 type;
				ub1 in_out;
				ub4 iter, idx;
				ub1 piece;
				ub4 alen = nPortionSize;

				// a tail from prefetching buffer remains?
				unsigned int nPrefetchedTail = pLongContext->Len - nPrefetchedSent;
				assert(nPrefetchedTail < nPortionSize);
				if(nPrefetchedTail)
				{
					memcpy(pBuf, m_PiecewiseNullCheckPreFetch+nPrefetchedSent, nPrefetchedTail);
					nPrefetchedSent += nPrefetchedTail;
					// we will ask Oracle to read less during this piece
					alen -= nPrefetchedTail;
				}
				assert(pLongContext->Len == nPrefetchedSent);

				Iora8Connection::Check(g_ora8API.OCIStmtGetPieceInfo(
					m_handles.m_pOCIStmt,
					m_handles.m_pOCIError,
					(dvoid**)&pOCIDefine,
					&type,
					&in_out,
					&iter, &idx,
					&piece), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
				Iora8Connection::Check(g_ora8API.OCIStmtSetPieceInfo(
					pOCIDefine,
					type,
					m_handles.m_pOCIError,
					pBuf+nPrefetchedTail, &alen,
					piece,
					pLongContext->pInd,
					NULL), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

				rc = g_ora8API.OCIStmtFetch(m_handles.m_pOCIStmt, m_handles.m_pOCIError, 1, OCI_FETCH_NEXT, OCI_DEFAULT);

				if(rc != OCI_NEED_DATA)
				{
                    if(ePieceType == SA_NextPiece)
                        ePieceType = SA_LastPiece;
                    else    // the whole Long was read in one piece
                    {
                        assert(ePieceType == SA_FirstPiece);
                        ePieceType = SA_OnePiece;
                    }
				}
				pLongContext->pReader->InvokeReader(ePieceType, pBuf, nPrefetchedTail+alen);

				if(ePieceType == SA_FirstPiece)
					ePieceType = SA_NextPiece;
			}
			while(rc == OCI_NEED_DATA);
			Iora8Connection::Check(rc, m_handles.m_pOCIError, OCI_HTYPE_ERROR);

			m_bPiecewiseFetchPending = false;
		}
	}
	else
	{
		assert(pLongContext->eState == LongContextCallback);

		if(fnReader == NULL)
			return;	// data is alredy in internal buffer

		// simply send data from internal buffer to user callback
		SAString &sLong = *pLongContext->pReader->m_pString;
		const char *data = (const char *)sLong;
		unsigned int nLongSize = sLong.GetLength();

		unsigned char* pBuf;
		unsigned int nPortionSize = pLongContext->pReader->PrepareReader(
			nLongSize,
			SB4MAXVAL,
			pBuf,
			fnReader,
			nReaderWantedPieceSize,
			pAddlData);

		unsigned int nTotal = 0;
		SAPieceType_t ePieceType = SA_FirstPiece;
		do
		{
			unsigned int nLen = nPortionSize;
			unsigned char *piecedata = (unsigned char *)data + nTotal;

			if(nLongSize - nTotal < nLen)
				nLen = nLongSize - nTotal;
			nTotal += nLen;

            if(nTotal == nLongSize)
            {
                if(ePieceType == SA_NextPiece)
                    ePieceType = SA_LastPiece;
                else    // the whole Long was read in one piece
                {
                    assert(ePieceType == SA_FirstPiece);
                    ePieceType = SA_OnePiece;
                }
            }
			pLongContext->pReader->InvokeReader(ePieceType, piecedata, nLen);
			
			if(ePieceType == SA_FirstPiece)
				ePieceType = SA_NextPiece;
		}
		while(nTotal < nLongSize);
	}
}

void Iora8Cursor::ReadLob(
	ValueType_t eValueType,
	SAValueRead &vr,
	OCILobLocator* pOCILobLocator,
	saLongOrLobReader_t fnReader,
	unsigned int nReaderWantedPieceSize,
	void *pAddlData)
{
	ub4 nBlobSize;
	Iora8Connection::Check(g_ora8API.OCILobGetLength(
		((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCISvcCtx,
		m_handles.m_pOCIError,
		pOCILobLocator,
		&nBlobSize), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

	bool bFileLobOpen = false;
	if(eValueType == ISA_FieldValue)
	{
		if(((SAField&)vr).FieldNativeType() == SQLT_BFILE)
		{
			Iora8Connection::Check(g_ora8API.OCILobFileOpen(
				((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCISvcCtx,
				m_handles.m_pOCIError,
				pOCILobLocator,
				OCI_FILE_READONLY), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

			bFileLobOpen = true;
		}
	}
	unsigned char* pBuf;
	unsigned int nPortionSize = vr.PrepareReader(
		nBlobSize,
		UB4MAXVAL,
		pBuf,
		fnReader,
		nReaderWantedPieceSize,
		pAddlData);

	try
	{
		SAPieceType_t ePieceType = SA_FirstPiece;
		ub4 amt;
		sb4 offset = 0;
		do
		{
			amt = nPortionSize;
			Iora8Connection::Check(g_ora8API.OCILobRead(
				((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCISvcCtx,
				m_handles.m_pOCIError,
				pOCILobLocator,
				&amt,
				offset+1,
				pBuf,
				nPortionSize,
				NULL,
				NULL,
				0, SQLCS_IMPLICIT), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

			offset += amt;
			assert((ub4)offset <= nBlobSize);

			if((ub4)offset == nBlobSize)
			{
				if(ePieceType == SA_NextPiece)
					ePieceType = SA_LastPiece;
				else    // the whole Long was read in one piece
				{
					assert(ePieceType == SA_FirstPiece);
					ePieceType = SA_OnePiece;
				}
			}
			vr.InvokeReader(ePieceType, pBuf, amt);

			if(ePieceType == SA_FirstPiece)
				ePieceType = SA_NextPiece;
		}
		while((ub4)offset < nBlobSize);
	}
	catch(SAException &)
	{
		// try to clean up
		if(bFileLobOpen)
			g_ora8API.OCILobFileClose(
				((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCISvcCtx,
				m_handles.m_pOCIError,
				pOCILobLocator);
		throw;
	}

	if(bFileLobOpen)
		Iora8Connection::Check(g_ora8API.OCILobFileClose(
			((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCISvcCtx,
			m_handles.m_pOCIError,
			pOCILobLocator), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
}

/*virtual */
void Iora8Cursor::ReadLongOrLOB(
	ValueType_t eValueType,
	SAValueRead &vr,
	void *pValue,
	unsigned int nBufSize,
	saLongOrLobReader_t fnReader,
	unsigned int nReaderWantedPieceSize,
	void *pAddlData)
{
	SADataType_t eDataType;
	switch(eValueType)
	{
	case ISA_FieldValue:
		eDataType = ((SAField&)vr).FieldType();
		break;
	default:
		assert(eValueType == ISA_ParamValue);
		eDataType = ((SAParam&)vr).ParamType();
	}
	switch(eDataType)
	{
	case SA_dtLongBinary:
	case SA_dtLongChar:
		assert(nBufSize == sizeof(LongContext_t));
		if(nBufSize != sizeof(LongContext_t))
			return;
		ReadLong((LongContext_t *)pValue, fnReader, nReaderWantedPieceSize, pAddlData);
		break;
	case SA_dtBLob:
	case SA_dtCLob:
		assert(nBufSize == sizeof(OCILobLocator*));
		if(nBufSize != sizeof(OCILobLocator*))
			return;
		ReadLob(eValueType, vr, *(OCILobLocator**)pValue, fnReader, nReaderWantedPieceSize, pAddlData);
		break;
	default:
		assert(false);
	}
}

/*virtual */
void Iora8Cursor::ConvertLongOrLOB(
	ValueType_t eValueType,
	SAValueRead &vr,
	void *pValue,
	unsigned int nBufSize)
{
	LongContext_t *pLongContext;

	SADataType_t eDataType;
	switch(eValueType)
	{
	case ISA_FieldValue:
		eDataType = ((SAField&)vr).FieldType();
		break;
	default:
		assert(eValueType == ISA_ParamValue);
		eDataType = ((SAParam&)vr).ParamType();
	}
	switch(eDataType)
	{
	case SA_dtLongBinary:
	case SA_dtLongChar:
		pLongContext = (LongContext_t *)pValue;
		if(pLongContext->eState == LongContextCallback)
		{
			// after long fields callbacks last Piece is read but not
			// processed, do it now
            SAPieceType_t ePieceType = SA_LastPiece;
			vr.InvokeReader(
				ePieceType,
				pLongContext->pBuf,
				pLongContext->Len);
		}
		else
			ISACursor::ConvertLongOrLOB(eValueType, vr, pValue, nBufSize);
		break;
	default:
		ISACursor::ConvertLongOrLOB(eValueType, vr, pValue, nBufSize);
	}
}

/*static */
sb4 Iora8Cursor::LongDefine(
	dvoid *octxp,
	OCIDefine * /*defnp*/,
	ub4/* iter*/,
	dvoid **bufpp,
	ub4 **alenpp,
	ub1 *piecep,
	dvoid **indpp,
	ub2 ** /*rcodep*/)
{
	return LongDefineOrOutBind(
		octxp, bufpp, alenpp, piecep, indpp);
}

/*static */
sb4 Iora8Cursor::LongDefineOrOutBind(
	dvoid *octxp,
	dvoid **bufpp,
	ub4 **alenpp,
	ub1 *piecep,
	dvoid **indpp)
{
	LongContext_t *pLongContext = (LongContext_t*)octxp;

	if(*piecep == OCI_ONE_PIECE || *piecep == OCI_FIRST_PIECE)
	{
		*piecep = OCI_FIRST_PIECE;
		unsigned int nBlobSize = 0;	// no way to determine size before fetch

		// always read callback Longs into internal buffer
		// we will execute real Reader later after Execute() or FetchNext() has completed
		unsigned int nPortionSize = pLongContext->pReader->PrepareReader(
			nBlobSize,
			UB4MAXVAL,
			pLongContext->pBuf,
			NULL,
			pLongContext->pReader->m_nReaderWantedPieceSize,
			NULL);

		*bufpp = pLongContext->pBuf;
		*alenpp = &pLongContext->Len;
		**alenpp = nPortionSize;
		*indpp = pLongContext->pInd;
	}
	else
	{
		assert(*piecep == OCI_NEXT_PIECE);

        SAPieceType_t ePieceType = SA_NextPiece;
		pLongContext->pReader->InvokeReader(
			ePieceType,
			pLongContext->pBuf,
			pLongContext->Len);

		*bufpp = pLongContext->pBuf;
		*alenpp = &pLongContext->Len;
		*indpp = pLongContext->pInd;
	}

	return OCI_CONTINUE;
}

/*virtual */
void Iora7Cursor::DescribeParamSP()
{
	SAString sProcName = m_pCommand->CommandText();

	ub4 arrsiz = 1024;

	// An array indicating whether the procedure is overloaded. If the
	// procedure (or function) is not overloaded, 0 is returned. Overloaded
	// procedures return 1...n for n overloadings of the name.
	ub2 ovrld[1024];
	ub2 pos[1024];
	ub2 level[1024];
	text argnm[1024][30];
	ub2 arnlen[1024];
	ub2 dtype[1024];
	ub1 defsup[1024];
	ub1 mode[1024];
	ub4 dtsiz[1024];
	sb2 prec[1024];
	sb2 scale[1024];
	ub1 radix[1024];
	ub4 spare[1024];

	((Iora7Connection*)m_pISAConnection)->Check(g_ora7API.odessp(
		&((Iora7Connection*)m_pISAConnection)->m_handles.m_lda,
		(text*)(const char*)sProcName,
		sProcName.GetLength(),
		NULL, 0, NULL, 0,
		ovrld, pos, level,
		(text **)argnm, arnlen, dtype, defsup, mode,
		dtsiz, prec, scale, radix, spare,
		&arrsiz), &m_handles.m_cda);

	// if overloads are present we describe requested one
	ub2 nOverload = (ub2)sa_strtol(m_pCommand->Option(_SA("Overload")), NULL, 10);
	for(unsigned int i = 0; i < arrsiz; ++i)
	{
		if(ovrld[i] == 0)	// procedure is not overloaded
			nOverload = ovrld[i];	// ignore requested
		else if(nOverload == 0)	// procedure is overloaded, but needed overload is not specified
			nOverload = 1;	// default to the first one

		if(nOverload == ovrld[i])
		{
			SADataType_t eParamType = CnvtNativeToStd(
				dtype[i], 0, dtsiz[i], prec[i], scale[i]);
			int nNativeType = dtype[i];
			int nParamSize = dtsiz[i];
			SAParamDirType_t eDirType;
			if(pos[i] == 0)
			{
				eDirType = SA_ParamReturn;
				m_pCommand->CreateParam(
					"Result",
					eParamType, nNativeType, 
					nParamSize, prec[i], scale[i],
					eDirType);
			}
			else 
			{
				switch(mode[i])
				{
				case 0:
					eDirType = SA_ParamInput;
					break;
				case 1:
					eDirType = SA_ParamOutput;
					break;
				case 2:
					eDirType = SA_ParamInputOutput;
					break;
				default:
					assert(false);
					continue;
				}

				m_pCommand->CreateParam(
					SAString((const char*)argnm[i], arnlen[i]),
					eParamType, nNativeType,
					nParamSize, prec[i], scale[i],
					eDirType);
			}
		}
	}
}

/*virtual */
void Iora8Cursor::DescribeParamSP()
{
	enum
	{
		NameUnknown,
		NamePkg,
		NamePkgDescribed,
		NameMethod,
		NameProc,
		NameFunc
	} eNameType = NameUnknown;

	SAString sName = m_pCommand->CommandText();
	SAString sPkg, sMethod, sName1, sName2;
	// if name is in the form of
	// a) ddd - it is global method ddd
	// b) aaa.bbb.ccc - it is a package aaa.bbb with method ccc
	// c) eee.fff than it can be a package eee or user(schema) eee
	int pos1 = sName.Find('.');
	int pos2;
	if(pos1 == -1)	// a)
	{
		eNameType = NameMethod;
		sMethod = sName;
	}
	else
	{
		pos2 = sName.Find('.', pos1+1);
		if(pos2 != -1)	// b)
		{
			eNameType = NamePkg;
			sPkg = sName.Left(pos2);
			sMethod = sName.Mid(pos2+1);
		}
		else	// c)
		{
			sName1 = sName.Left(pos1);
			sName2 = sName.Mid(pos1+1);
		}
	}

	OCIDescribe *pDescr = NULL;
	Iora8Connection::Check(g_ora8API.OCIHandleAlloc(
		((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv,
		(dvoid**)&pDescr, OCI_HTYPE_DESCRIBE, 0, NULL),
		((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv, OCI_HTYPE_ENV);

	try
	{
		if(eNameType == NameUnknown)
		{
			// check package.method
			sword status = g_ora8API.OCIDescribeAny(
				((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCISvcCtx,
				m_handles.m_pOCIError,
				(dvoid*)(const char*)sName1,
				sName1.GetLength(),
				OCI_OTYPE_NAME,
				OCI_DEFAULT,
				OCI_PTYPE_PKG,
				pDescr);

			if(status == OCI_SUCCESS)
			{
				eNameType = NamePkgDescribed;
				sPkg = sName1;
				sMethod = sName2;
			}
			else
			{
				eNameType = NameMethod;
				sMethod = sName;
			}
		}
		assert(eNameType != NameUnknown);

		// describe as package
		if(eNameType == NamePkg)
		{
			Iora8Connection::Check(g_ora8API.OCIDescribeAny(
				((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCISvcCtx,
				m_handles.m_pOCIError,
				(dvoid*)(const char*)sPkg,
				sPkg.GetLength(),
				OCI_OTYPE_NAME,
				OCI_DEFAULT,
				OCI_PTYPE_PKG,
				pDescr), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

			eNameType = NamePkgDescribed;
		}

		OCIParam *parmh = NULL;
		OCIParam *sublisth = NULL;
		ub4 nSubs = 0, nSub;
		ub2 nOverload;

		sword status;

		switch(eNameType)
		{
		case NamePkgDescribed:
			// get the parameter handle
			Iora8Connection::Check(g_ora8API.OCIAttrGet(
				pDescr, OCI_HTYPE_DESCRIBE,
				&parmh, NULL, OCI_ATTR_PARAM,
				m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			// get parameter for list of subprograms
			Iora8Connection::Check(g_ora8API.OCIAttrGet(
				parmh, OCI_DTYPE_PARAM,
				&sublisth, NULL, OCI_ATTR_LIST_SUBPROGRAMS,
				m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			// How many subroutines are in this package?
			Iora8Connection::Check(g_ora8API.OCIAttrGet(
				sublisth, OCI_DTYPE_PARAM,
				&nSubs, NULL, OCI_ATTR_NUM_PARAMS,
				m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			// find our subprogram
			nOverload = (ub2)sa_strtol(m_pCommand->Option(_SA("Overload")), NULL, 10);
			if(!nOverload)
				nOverload = 1;	// first overload is the default one
			for(nSub = 0; nSub < nSubs; ++nSub)
			{
				Iora8Connection::Check(g_ora8API.OCIParamGet(
					sublisth, OCI_DTYPE_PARAM,
					m_handles.m_pOCIError,
					(dvoid**)&parmh, nSub), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

				// Get the routine type and name
				char *szName;
				ub4 nLen;
				Iora8Connection::Check(g_ora8API.OCIAttrGet(
					parmh, OCI_DTYPE_PARAM, &szName, &nLen, OCI_ATTR_NAME,
					m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
				if(sMethod.CompareNoCase(SAString(szName, nLen)) != 0)
					continue;
				if(--nOverload)
					continue;	// the name matches but we need higher overload

				ub1 nSubType;
				Iora8Connection::Check(g_ora8API.OCIAttrGet(
					parmh, OCI_DTYPE_PARAM, &nSubType, NULL, OCI_ATTR_PTYPE,
					m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
				switch(nSubType)
				{
				case OCI_PTYPE_PROC:
					eNameType = NameProc;
					break;
				case OCI_PTYPE_FUNC:
					eNameType = NameFunc;
					break;
				default:
					assert(false);
				}

				break;
			}

			if(eNameType == NamePkgDescribed)
			{
				// method was not found in the package
				// make next dummy call to get Oracle native error

				Iora8Connection::Check(g_ora8API.OCIDescribeAny(
					((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCISvcCtx,
					m_handles.m_pOCIError,
					(dvoid*)(const char*)sName, sName.GetLength(),
					OCI_OTYPE_NAME, OCI_DEFAULT, OCI_PTYPE_PROC,
					pDescr), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

				assert(false);
			}
			break;
		case NameMethod:
			// first check for procedure
			status = g_ora8API.OCIDescribeAny(
				((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCISvcCtx,
				m_handles.m_pOCIError,
				(dvoid*)(const char*)sMethod, sMethod.GetLength(),
				OCI_OTYPE_NAME, OCI_DEFAULT, OCI_PTYPE_PROC, pDescr);
			if(status != OCI_SUCCESS)
			{
				// if not procedure then must be function
				Iora8Connection::Check(g_ora8API.OCIDescribeAny(
					((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCISvcCtx,
					m_handles.m_pOCIError,
					(dvoid*)(const char*)sMethod, sMethod.GetLength(),
					OCI_OTYPE_NAME, OCI_DEFAULT, OCI_PTYPE_FUNC,
					pDescr), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
				eNameType = NameFunc;
			}
			else
				eNameType = NameProc;
			// get the parameter handle
			Iora8Connection::Check(g_ora8API.OCIAttrGet(
				pDescr, OCI_HTYPE_DESCRIBE,
				&parmh, NULL, OCI_ATTR_PARAM,
				m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			break;
		default:
			assert(false);
		}

		assert(eNameType == NameProc || eNameType == NameFunc);
		// now we can describe subprogram params
		OCIParam *phArgLst;
		ub2 nArgs;
		// Get the number of arguments and the arg list
		Iora8Connection::Check(g_ora8API.OCIAttrGet(
			parmh, OCI_DTYPE_PARAM, &phArgLst, NULL, OCI_ATTR_LIST_ARGUMENTS,
			m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
		Iora8Connection::Check(g_ora8API.OCIAttrGet(
			phArgLst, OCI_DTYPE_PARAM, &nArgs, NULL, OCI_ATTR_NUM_PARAMS,
			m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

		OCIParam *phArg;
		for(int i = 0; i <= nArgs; ++i)
		{
			if(i == 0 && eNameType != NameFunc)
				continue;
			if(i == nArgs && eNameType != NameProc)
				break;

			char *szName;
			ub4 nLen;
			ub2 dtype, dsize;
			OCITypeParamMode iomode;
			sb1 scale;
			ub1 prec;

			Iora8Connection::Check(g_ora8API.OCIParamGet(
				phArgLst, OCI_DTYPE_PARAM, m_handles.m_pOCIError, (dvoid**)&phArg, i),
				m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			Iora8Connection::Check(g_ora8API.OCIAttrGet(phArg, OCI_DTYPE_PARAM, &szName, &nLen, OCI_ATTR_NAME,
				m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			Iora8Connection::Check(g_ora8API.OCIAttrGet(phArg, OCI_DTYPE_PARAM, &dtype, NULL, OCI_ATTR_DATA_TYPE,
				m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			Iora8Connection::Check(g_ora8API.OCIAttrGet(phArg, OCI_DTYPE_PARAM, &dsize, NULL, OCI_ATTR_DATA_SIZE,
				m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			Iora8Connection::Check(g_ora8API.OCIAttrGet(phArg, OCI_DTYPE_PARAM, &iomode, NULL, OCI_ATTR_IOMODE,
				m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			Iora8Connection::Check(g_ora8API.OCIAttrGet(phArg, OCI_DTYPE_PARAM, &prec, NULL, OCI_ATTR_PRECISION,
				m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);
			Iora8Connection::Check(g_ora8API.OCIAttrGet(phArg, OCI_DTYPE_PARAM, &scale, NULL, OCI_ATTR_SCALE,
				m_handles.m_pOCIError), m_handles.m_pOCIError, OCI_HTYPE_ERROR);

			SADataType_t eParamType = CnvtNativeToStd(dtype, 0, dsize, prec, scale);
			int nNativeType = dtype;
			SAParamDirType_t eDirType;
			switch(iomode)
			{
			case OCI_TYPEPARAM_IN:
				eDirType = SA_ParamInput;
				break;
			case OCI_TYPEPARAM_OUT:
				eDirType = SA_ParamOutput;
				break;
			case OCI_TYPEPARAM_INOUT:
				eDirType = SA_ParamInputOutput;
				break;
			default:
				assert(false);
				continue;
			}

			SAString sParamName;
			if(i == 0)
			{
				assert(nLen == 0);
				assert(eDirType == SA_ParamOutput);
				eDirType = SA_ParamReturn;
				sParamName = "Result";
			}
			else
				sParamName = SAString(szName, nLen);

			m_pCommand->CreateParam(
				sParamName,
				eParamType,	nNativeType,
				dsize, prec, scale,
				eDirType);
		}

		try
		{
			Iora8Connection::Check(g_ora8API.OCIHandleFree(
				pDescr, OCI_HTYPE_DESCRIBE), ((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCIEnv, OCI_HTYPE_ENV);
		}
		catch(SAException &)
		{
		}
	}
	catch(SAException&)
	{	// clean up
		g_ora8API.OCIHandleFree(pDescr, OCI_HTYPE_DESCRIBE);
		throw;
	}
}

/*virtual */
int Iora7Cursor::CnvtStdToNative(SADataType_t eDataType) const
{
	sword ftype;

	switch(eDataType)
	{
	case SA_dtUnknown:
		throw SAException(SA_Library_Error, -1, -1, IDS_UNKNOWN_DATA_TYPE);
	case SA_dtBool:
		// there is no "native" boolean type in Oracle,
		// so treat boolean as 16-bit signed INTEGER in Oracle
		ftype = 3;	// 16-bit signed integer
		break;
	case SA_dtShort:
		ftype = 3;	// 16-bit signed integer
		break;
	case SA_dtLong:
		ftype = 3;	// 32-bit signed integer
		break;
	case SA_dtDouble:
		ftype = 4;	// FLOAT
		break;
	case SA_dtNumeric:
		ftype = 6;	// VARNUM
		break;
	case SA_dtDateTime:
		ftype = 12;	// DATE
		break;
	case SA_dtString:
		// using 1 can cause problems when binding CHAR(n) columns
		// like 'Select * from my_table where my_char_20 = :1'
		// if we use 1 we have to pad bind value with spaces
		//ftype = 1;	// VARCHAR2
		ftype = 96;	// CHAR
		break;
	case SA_dtBytes:
		ftype = 23;	// RAW
		break;
	case SA_dtLongBinary:
	case SA_dtBLob:
		ftype = 24;	// LONG RAW
		break;
	case SA_dtLongChar:
	case SA_dtCLob:
		ftype = 8;	// LONG
		break;
	case SA_dtCursor:
		ftype = 102;	// cursor  type
		break;
	default:
		ftype = 0;
		assert(false);
	}

	return ftype;
}

/*virtual */
int Iora8Cursor::CnvtStdToNative(SADataType_t eDataType) const
{
	ub2 dty;

	switch(eDataType)
	{
	case SA_dtUnknown:
		throw SAException(SA_Library_Error, -1, -1, IDS_UNKNOWN_DATA_TYPE);
	case SA_dtBool:
		// there is no "native" boolean type in Oracle,
		// so treat boolean as 16-bit signed INTEGER in Oracle
		dty = SQLT_INT;	// 16-bit signed integer
		break;
	case SA_dtShort:
		dty = SQLT_INT;	// 16-bit signed integer
		break;
	case SA_dtLong:
		dty = SQLT_INT;	// 32-bit signed integer
		break;
	case SA_dtDouble:
		dty = SQLT_FLT;	// FLOAT
		break;
	case SA_dtNumeric:
		dty = SQLT_VNU;	// VARNUM
		break;
	case SA_dtDateTime:
		dty = SQLT_DAT;	// DATE
		break;
	case SA_dtString:
		// using SQLT_CHR can cause problems when binding CHAR(n) columns
		// like 'Select * from my_table where my_char_20 = :1'
		// if we use SQLT_CHR we have to pad bind value with spaces
		//dty = SQLT_CHR;	// VARCHAR2
		dty = SQLT_AFC;	// CHAR
		break;
	case SA_dtBytes:
		dty = SQLT_BIN;	// RAW
		break;
	case SA_dtLongBinary:
		dty = SQLT_LBI;	// LONG RAW
		break;
	case SA_dtBLob:
		dty = SQLT_BLOB;// Binary LOB
		break;
	case SA_dtLongChar:
		dty = SQLT_LNG;	// LONG
		break;
	case SA_dtCLob:
		dty = SQLT_CLOB;	// Character LOB
		break;
	case SA_dtCursor:
		dty = SQLT_RSET;	// result set type
		break;
	default:
		dty = 0;
		assert(false);
	}

	return dty;
}

/*virtual */
saAPI *Iora7Connection::NativeAPI() const
{
	return &g_ora7API;
}

/*virtual */
saAPI *Iora8Connection::NativeAPI() const
{
	return &g_ora8API;
}

/*virtual */
saConnectionHandles *Iora7Connection::NativeHandles()
{
	return &m_handles;
}

/*virtual */
saConnectionHandles *Iora8Connection::NativeHandles()
{
	return &m_handles;
}

/*virtual */
saCommandHandles *Iora7Cursor::NativeHandles()
{
	return &m_handles;
}

/*virtual */
saCommandHandles *Iora8Cursor::NativeHandles()
{
	return &m_handles;
}

void IoraConnection::issueIsolationLevel(
	SAIsolationLevel_t eIsolationLevel)
{
	SAString sCmd("SET TRANSACTION ISOLATION LEVEL ");
	SACommand cmd(m_pSAConnection);

	switch(eIsolationLevel)
	{
	case SA_ReadUncommitted:
		sCmd += "READ COMMITTED";
		break;
	case SA_ReadCommitted:
		sCmd += "READ COMMITTED";
		break;
	case SA_RepeatableRead:
		sCmd += "SERIALIZABLE";
		break;
	case SA_Serializable:
		sCmd += "SERIALIZABLE";
		break;
	default:
		assert(false);
		return;
	}

	cmd.setCommandText(sCmd);
	cmd.Execute();
	cmd.Close();
}

/*virtual */
void IoraConnection::setIsolationLevel(
	SAIsolationLevel_t eIsolationLevel)
{
	m_eSwitchToIsolationLevelAfterCommit = eIsolationLevel;
	Commit();
}

/*virtual */
void Iora7Connection::setAutoCommit(
	SAAutoCommit_t eAutoCommit)
{
	switch(eAutoCommit)
	{
	case SA_AutoCommitOff:
		Check(g_ora7API.ocof(&m_handles.m_lda), NULL);
		break;
	case SA_AutoCommitOn:
		Check(g_ora7API.ocon(&m_handles.m_lda), NULL);
		break;
	default:
		assert(false);
		return;
	}
}

/*virtual */
void Iora8Connection::setAutoCommit(
	SAAutoCommit_t eAutoCommit)
{
	switch(eAutoCommit)
	{
	case SA_AutoCommitOff:
		break;
	case SA_AutoCommitOn:
		break;
	default:
		assert(false);
		return;
	}
}

/*static */
void Iora7Connection::CnvtInternalToCursor(
	SACommand &Cursor,
	const Cda_Def *pInternal)
{
	ora7CommandHandles *pH = (ora7CommandHandles *)Cursor.NativeHandles();
	pH->m_cda = *pInternal;
}

/*virtual */
void Iora7Connection::CnvtInternalToCursor(
	SACommand *pCursor,
	const void *pInternal)
{
	assert(pCursor);

	if(pCursor->Connection() == NULL)
		pCursor->setConnection(getSAConnection());

	// undescribe fields
	pCursor->setCommandText("");

	CnvtInternalToCursor(*pCursor, (const Cda_Def *)pInternal);
}


/*virtual */
void Iora8Connection::CnvtInternalToCursor(
	SACommand *pCursor,
	const void *pInternal)
{
	if(pCursor->Connection() == NULL)
		pCursor->setConnection(getSAConnection());

	// undescribe fields
	pCursor->setCommandText("");

	CnvtInternalToCursor(*pCursor, *(const OCIStmt **)pInternal);
}

/*static */
void Iora8Connection::CnvtInternalToCursor(
	SACommand &Cursor,
	const OCIStmt *pInternal)
{
	ora8CommandHandles *pH = (ora8CommandHandles *)Cursor.NativeHandles();

	memcpy(&pH->m_pOCIStmt, &pInternal, sizeof(OCIStmt *));
}

void Iora8Cursor::FreeTemporaryLobsIfAny()
{
	while(m_cTempLobs)
	{
		Iora8Connection::Check(g_ora8API.OCILobFreeTemporary(
			((Iora8Connection*)m_pISAConnection)->m_handles.m_pOCISvcCtx,
			m_handles.m_pOCIError,
			m_ppTempLobs[m_cTempLobs-1]),
			m_handles.m_pOCIError, OCI_HTYPE_ERROR);
		--m_cTempLobs;
	}

	::free(m_ppTempLobs);
	m_ppTempLobs = 0;
}

/*virtual */
void IoraConnection::CnvtInternalToNumeric(
	SANumeric &numeric,
	const void *pInternal,
	int/* nInternalSize*/)
{
	OraVARNUM_t &pOraVARNUM = *(OraVARNUM_t *)pInternal;

	unsigned int OraNumSize = pOraVARNUM[0];
	assert(OraNumSize > 0);	// at least exponent byte

	unsigned char ExponentByte = pOraVARNUM[1];
	bool PositiveBit = (ExponentByte & 0x80) != 0;
	unsigned char ExponentOffset65 = (unsigned char )(ExponentByte & 0x7F);
	unsigned int MantissaSize = OraNumSize - 1;	// minus exponent byte
	char Exponent;
	if(!PositiveBit && MantissaSize < 20)
	{
		--MantissaSize;	// ignore trailing 102 byte
		Exponent = (char)(62 - ExponentOffset65);	// ???, not found in Oracle docs, just expreriment
	}
	else
		Exponent = (char)(ExponentOffset65 - 65);

	unsigned char *pOracleCodedDigits = pOraVARNUM + 1 + 1;

	unsigned char OracleCodedDigits[128];	// this is enough for the biggest number Oracle can support
	memset(OracleCodedDigits, PositiveBit? 1 : 101, sizeof(OracleCodedDigits));
	memcpy(OracleCodedDigits, pOracleCodedDigits, MantissaSize);

	int OracleScale = MantissaSize - 1 - Exponent;

	// SANumeric class does not support
	// negative scale, so we have to adjust:
	// we will increase scale till zero and
	// at the same time "virtually" increase mantissa
	int AdjustedOracleScale = OracleScale;
	unsigned int AdjustedMantissaSize = MantissaSize;
	while(AdjustedOracleScale < 0)
	{
		++AdjustedMantissaSize;
		++AdjustedOracleScale;
	}

	unsigned char Precision10 = (unsigned char)(AdjustedMantissaSize * 2);
	unsigned char Scale10 = (unsigned char)((AdjustedMantissaSize - 1 - Exponent) * 2);

	// convert Oracle 100-based digits into little endian integer

	// to make conversion easier first convert
	// Oracle 100-based number into 10000-based little endian
	unsigned short Num10000[sizeof(OracleCodedDigits)/sizeof(short)];
	memset(Num10000, 0, sizeof(Num10000));
	int Num10000pos = 0;
	for(int i = AdjustedMantissaSize-1; i >= 0; i -= 2)
	{
		int Num100 = PositiveBit? OracleCodedDigits[i] - 1 : 101 - OracleCodedDigits[i];
		assert(Num100 >= 0 && Num100 < 100);
		Num10000[Num10000pos] = (unsigned char)Num100;
		if(i > 0)
		{
			Num100 = PositiveBit? OracleCodedDigits[i-1] - 1 : 101 - OracleCodedDigits[i-1];
			Num10000[Num10000pos] = (unsigned short)(Num10000[Num10000pos] + (Num100 * 100));
		}

		++Num10000pos;
	}

	numeric.precision = Precision10;
	numeric.scale = Scale10;
	// Now let us set sign
	// Oracle: The high-order bit of the exponent byte is the sign bit;
	// it is set for positive numbers.
	// SQLAPI++: numeric.sign is 1 for positive numbers, 0 for negative numbers
	numeric.sign = (unsigned char)(PositiveBit? 1:0);

	// convert mantissa
	unsigned short Zero[sizeof(Num10000)/sizeof(short)];
	memset(Zero, 0, sizeof(Zero));

	memset(numeric.val, 0, sizeof(numeric.val));
	int Num256pos = 0;
	while(memcmp(Num10000, Zero, sizeof(Num10000)) != 0)
	{
		unsigned short Reminder;
		LittleEndian10000BaseDivide(
			sizeof(Num10000)/sizeof(short),
			Num10000,
			256,
			Num10000,
			&Reminder);

		assert(Reminder == (unsigned char)Reminder);	// no truncation here
		numeric.val[Num256pos++] = (unsigned char)Reminder;
		if(Num256pos == sizeof(numeric.val))
			break;	// we have to truncate the number
	}
}
