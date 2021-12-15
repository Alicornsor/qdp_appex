// ISAClient.h: interface for the ISAClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISACLIENT_H__03CBE8D1_50AF_44A0_BC10_FA83E300D215__INCLUDED_)
#define AFX_ISACLIENT_H__03CBE8D1_50AF_44A0_BC10_FA83E300D215__INCLUDED_

#include <SQLAPI.h>

class ISAConnection;

// Helpers
// numeric support/conversions helpers
void LittleEndian10000BaseDivide(
	unsigned int LittleEndianSize,	// in shorts
	const unsigned short Devidend[],
	unsigned short Devisor,
	unsigned short Quotient[],
	unsigned short *pRemainder);
// Character sets conversion helpers
// returns number of Wide chars written
// can return character on which conversion was stopped
unsigned int SAMultiByteToWideChar(
	wchar_t *pchDataTgt,
	const char *lpch, int nLength, char **lppchStop = NULL);
// returns number of Multibyte chars written
// if pchDataTgt is NULL, function simply counts
unsigned int SAWideCharToMultiByte(
	char *pchDataTgt,
	const wchar_t *lpch, int nLength);

typedef void (SACommand::*DescribeFields_cb_t)(
	const SAString &sName,
	SADataType_t eFieldType,
	int nNativeType,
	int nFieldSize,
	int nFieldPrecision,
	int nFieldScale,
	bool bFieldRequired);

class ISACursor
{
	friend class SAField;
	friend class SAParam;

protected:
	ISAConnection *m_pISAConnection;
	SACommand *m_pCommand;

	void *m_pParamBuffer;
	unsigned int m_nParamIndSize;
	unsigned int m_nParamSizeSize;
	void IncParamBuffer(
		void *&pBuf,
		void *&pInd,
		void *&pSize,
		unsigned int &nDataBufSize,
		void *&pValue);
	static bool isInputParam(const SAParam& Param);
	static bool isOutputParam(const SAParam& Param);

	void *m_pSelectBuffer;
	unsigned int m_nIndSize;
	unsigned int m_nSizeSize;
	int m_nBulkReadingBufSize;
	void IncFieldBuffer(
		void *&pBuf,
		void *&pInd,
		void *&pSize,
		unsigned int &nDataBufSize,
		void *&pValue);

	typedef enum
	{
		ISA_FieldValue, ISA_ParamValue
	} ValueType_t;
	void ConvertValue(
		int nPos,	// 1 - based
		unsigned int nIndSize,
		void *pNull,
		unsigned int nSizeSize,
		void *pSize,
		unsigned int nBufSize,
		void *pValue,
		ValueType_t eValueType,
		SAValueRead &vr,
		int nBulkReadingBufPos);
	void WriteLongOrLobToInternalValue(
		SAValue &value);

	virtual bool IndicatorIsNull(
		int nPos,	// 1-based
		SAValueRead &vr,
		ValueType_t eValueType,
		void *pInd, unsigned int nIndSize,
		void *pSize, unsigned int nSizeSize,
		unsigned int &nRealSize,
		int nBulkReadingBufPos) const;
	virtual void ConvertString(
		SAString &String,
		const void *pData,
		unsigned int nRealSize);
	virtual void ConvertLongOrLOB(
		ValueType_t eValueType,
		SAValueRead &vr,
		void *pValue,
		unsigned int nFieldBufSize);
	// should return false if client binds output/return parameters
	// according to value type (coersing)
	// should return true if client binds output/return parameters
	// according to parameter type
	// defaults to false, should be overloaeded by client if this is not the intend
	virtual bool OutputBindingTypeIsParamType();

	virtual unsigned int InputBufferSize(
		const SAParam &Param) const;
	virtual unsigned int OutputBufferSize(
		SADataType_t eDataType,
		unsigned int nDataSize) const;

	void AllocBindBuffer(
		unsigned int nIndSize,
		unsigned int nSizeSize);
	void AllocBindBuffer(
		int nPlaceHolderCount,
		saPlaceHolder **ppPlaceHolders,
		unsigned int nIndSize,
		unsigned int nSizeSize,
		unsigned int nAddlSize = 0,
		void **ppAddl = NULL);
	short ParamDirCount(
		int nPlaceHolderCount,
		saPlaceHolder **ppPlaceHolders,
		int nCount, ...) const;
	void ConvertOutputParams();
	void GetParamBuffer(
		const SAParam &Param,
		void *&pValue, unsigned int &nParamBufSize);
	int OutputParamPos(int nParamPos);

	void AllocSelectBuffer(
		unsigned int nIndSize,
		unsigned int nSizeSize,
		int nBulkReadingBufSize = 1);
	void ConvertSelectBufferToFields(int nBulkReadingBufPos);
	void GetFieldBuffer(
		int nPos,	// 1- based
		void *&pValue, unsigned int &nFieldBufSize);
	int FieldCount(int nCount, ...) const;

	static bool isLong(SADataType_t eDataType);
	static bool isLob(SADataType_t eDataType);
	static bool isLongOrLob(SADataType_t eDataType);

public:
	ISACursor(
		ISAConnection *pISAConnection,
		SACommand *pCommand);
	virtual ~ISACursor();

	virtual bool IsOpened() = 0;
	virtual void Open() = 0;
	virtual void Close() = 0;

	// prepare statement (also convert to native format if needed)
	virtual void Prepare(
		const SAString &sStmt,
		SACommandType_t eCmdType,
		int nPlaceHolderCount,
		saPlaceHolder **ppPlaceHolders) = 0;
	// executes statement (also binds parameters if needed)
	virtual void Execute(
		int nPlaceHolderCount,
		saPlaceHolder **ppPlaceHolders) = 0;
	// cleans up after execute if needed, so the statement can be reexecuted
	virtual void UnExecute() = 0;
	virtual void Cancel() = 0;

	virtual bool ResultSetExists() = 0;
	virtual void DescribeFields(
		DescribeFields_cb_t fn) = 0;
	virtual void SetSelectBuffers() = 0;
	virtual void SetFieldBuffer(
		int nCol,	// 1-based
		void *pInd,
		unsigned int nIndSize,
		void *pSize,
		unsigned int nSizeSize,
		void *pValue,
		unsigned int nValueSize) = 0;
	virtual bool FetchNext() = 0;

	virtual long GetRowsAffected() = 0;

	virtual void ReadLongOrLOB(
		ValueType_t eValueType,
		SAValueRead &vr,
		void *pValue,
		unsigned int nFieldBufSize,
		saLongOrLobReader_t fnReader,
		unsigned int nReaderWantedPieceSize,
		void *pAddlData) = 0;

	virtual void DescribeParamSP() = 0;

	virtual saCommandHandles *NativeHandles() = 0;

	// Notifications
	virtual void OnConnectionAutoCommitChanged() {}

	// Options
	int BulkReadingBufSize() const;
};

class ISAConnection
{
protected:
	SAConnection *m_pSAConnection;

public:
	ISAConnection(SAConnection *pSAConnection);
	virtual ~ISAConnection();

	SAConnection *getSAConnection();
	void EnumCursors(EnumCursors_t fn, void *pAddlData);

	virtual void InitializeClient() = 0;
	virtual void UnInitializeClient() = 0;

	virtual long GetClientVersion() const = 0;
	virtual long GetServerVersion() const = 0;
	virtual SAString GetServerVersionString() const = 0;

	virtual bool IsConnected() const = 0;
	virtual void Connect(
		const SAString &sDBString,
		const SAString &sUserID,
		const SAString &sPassword) = 0;
	virtual void Disconnect() = 0;

	virtual void setIsolationLevel(
		SAIsolationLevel_t eIsolationLevel) = 0;
	virtual void setAutoCommit(
		SAAutoCommit_t eAutoCommit) = 0;
	virtual void Commit() = 0;
	virtual void Rollback() = 0;

	virtual saAPI *NativeAPI() const = 0;
	virtual saConnectionHandles *NativeHandles() = 0;

	virtual ISACursor *NewCursor(SACommand *pCommand) = 0;

	virtual void CnvtInternalToNumeric(
		SANumeric &numeric,
		const void *pInternal,
		int nInternalSize) = 0;
	virtual void CnvtInternalToDateTime(
		SADateTime &date_time,
		const void *pInternal,
		int nInternalSize) = 0;
	virtual void CnvtInternalToCursor(
		SACommand *pCursor,
		const void *pInternal) = 0;
};

class ISAClient
{
public:
	ISAClient();
	virtual ~ISAClient();

	virtual ISAConnection *QueryConnectionInterface(
		SAConnection *pSAConnection) = 0;
};

class ISADataConverter
{
public:
	// puts a piece of external data into converter
	// pExternalData is guaranteed to be valid on the next GetStream call
	virtual void PutStream(unsigned char *pExternalData, unsigned int nExternalDataSize, SAPieceType_t eExternalPieceType) = 0;
	// gets a piece of data (converted if necessary) from converter
	// returns false if converter is empty or it doesn't have enough data to return nWantedSize block
	// pData should be the same pointer that was used in PutStream (pExternalData)
	virtual bool GetStream(unsigned char *pData, unsigned int nWantedSize, unsigned int &nDataSize, SAPieceType_t &eCnvtPieceType) = 0;
	// checks if no data is waiting in converter
	virtual bool IsEmpty() const = 0;
};

// Does nothing, simply works as a repeater,
// no buffering/no conversions are made.
class SADummyConverter : public ISADataConverter
{
	unsigned char *m_pExternalData;
	unsigned int m_nExternalDataSize;
	SAPieceType_t m_eExternalPieceType;

	SAPieceType_t m_eCnvtPieceType;
	// converter should return true at least once
	// for the final external piece, even if there is no data
	bool m_bFinalPiecePending;

protected:
	bool StreamIsEnough(unsigned int nWantedSize, unsigned int nExternalDataSize) const;
	void FlushExternalData(unsigned char *pData, unsigned int &nDataSize);
	void SetExternalData(unsigned char *pExternalData, unsigned int nExternalDataSize);

public:
	SADummyConverter();

	virtual void PutStream(unsigned char *pExternalData, unsigned int nExternalDataSize, SAPieceType_t eExternalPieceType);
	virtual bool GetStream(unsigned char *pData, unsigned int nWantedSize, unsigned int &nDataSize, SAPieceType_t &eCnvtPieceType);
	virtual bool IsEmpty() const;
};

// Does the same as SADummyConverter (no conversion)
// but can also provide buffering if necessary
class SABufferConverter : public SADummyConverter
{
	int m_nBufferSizeAtGetAppendBufferCall;
	SAString m_Buffer;

protected:
	unsigned char *GetAppendBuffer(int nAppendBytesMaxCount);
	void ReleaseAppendBuffer(int nAppendBytesCount);

public:
	SABufferConverter();
	virtual ~SABufferConverter();

	virtual bool GetStream(unsigned char *pData, unsigned int nWantedSize, unsigned int &nDataSize, SAPieceType_t &eCnvtPieceType);
	virtual bool IsEmpty() const;
};

// Does the same as SABufferConverter (buffering)
// but also converts input data from Unicode to Multibyte
class SAUnicode2MultibyteConverter : public SABufferConverter
{
	// we assume that sizeof(wchar_t) > 1
	// if PutStream() size is not a multiply of sizeof(wchar_t)
	// (for example user reads Unicode data in sizeof(wchar_t)*n+1 pieces)
	// we will save the reminder here
	unsigned char m_chReminderBytes[sizeof(wchar_t)];
	unsigned int m_ReminderBytesCount;

public:
	SAUnicode2MultibyteConverter();
	virtual ~SAUnicode2MultibyteConverter();

public:
	virtual bool GetStream(unsigned char *pData, unsigned int nWantedSize, unsigned int &nDataSize, SAPieceType_t &eDataPieceType);
	virtual bool IsEmpty() const;
};

// Does the same as SABufferConverter (buffering)
// but also converts input data from Unicode to Multibyte
class SAMultibyte2UnicodeConverter : public SABufferConverter
{
	// multibyte sequence is invalid in current locale
	// no way to continue
	bool m_bFatalError;
	// we will save the reminder here
	char *m_chReminderBytes;	// = malloc(MB_CUR_MAX)
	unsigned int m_ReminderBytesCount;

public:
	SAMultibyte2UnicodeConverter();
	virtual ~SAMultibyte2UnicodeConverter();

public:
	virtual bool GetStream(unsigned char *pData, unsigned int nWantedSize, unsigned int &nDataSize, SAPieceType_t &eDataPieceType);
	virtual bool IsEmpty() const;
};

#endif // !defined(AFX_ISACLIENT_H__03CBE8D1_50AF_44A0_BC10_FA83E300D215__INCLUDED_)
