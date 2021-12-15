/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file platform.h
///@brief �ϳ�ģ�飬����Ҫ�ͻ��ˣ�ֱ���ϳ���
///		  ֧���ļ�csv�ϳ�+tbcommand.batʵʱ�ϳ������ݿ��ϳ�+���ݿ��tbcommandʵʱ�ϳ�
///		  tinit -e �������ݿ��csv�ļ�
///		  tinit -d date �ļ��ϳ�
///		  tinit ���ݿ��ϳ�
///@history 
///20121214	���һ�		�������ļ�
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "FibPubApiManager.h"
#include "SelectReactor.h"
#include "TinitDataLoader.h"
#include "TinitServer.h"
#include "DbmtHandler.h"
#include "Config.h"
#include "CConfig.h"
#include "monitorIndex.h"
#include "FileInitReactor.h"
#include "version.h"
#include "CFilelogService.h"
#include "BaseFunction.h"


extern TTinitTableInfo g_DayTableInfo[];
const char *INI_FILE_NAME = "qdata.ini";
const char *APP_NAME = "qdata";
char *FLOW_FILE_NAME="qdata";
const char *CMDFILENAME="TBCommand.dat";

//��������tinit��SubjectID����uskernel��Ҫ�������ĸ�����tinit������
//��Ҫ��uskernel����
DWORD TINIT_SUBJECTID=0x00001121;


class CTinitReactor : public CSelectReactor
{
public:
	/**���캯��
	*/
	CTinitReactor();
	
	/**��ʼ��ʵ��
	* @reutrn true ��ʼ���ɹ�  false ��ʼ��ʧ��
	* @remark ��ʼ��ͨѶ�ӿڡ������������Ŷӷ����
	*/
	virtual bool InitInstance();

	/**����ʵ��
	* @remark ����ͨѶ�ӿڡ������������Ŷӷ����
	*/
	virtual void ExitInstance();

private:
	CTinitServer *m_pTinitServer;
};

CTinitReactor::CTinitReactor()
{
	m_pTinitServer = NULL;
}

bool CTinitReactor::InitInstance()
{
	char szBuffer[300];	
	m_pTinitServer = new CTinitServer(this);

	//�������ݿ�����


	char dbname[300];
	char dbpasswd[300];
	char dbuser[300];
	GetConfigString(INI_FILE_NAME, "dbname",szBuffer, sizeof(szBuffer));
	strncpy(dbname,szBuffer,sizeof(szBuffer));
	GetConfigString(INI_FILE_NAME, "dbuser",szBuffer, sizeof(szBuffer));
	strncpy(dbuser,szBuffer,sizeof(szBuffer));
	GetConfigString(INI_FILE_NAME, "dbpasswd",szBuffer, sizeof(szBuffer));
	strncpy(dbpasswd,szBuffer,sizeof(szBuffer));

	REPORT_EVENT(LOG_WARNING, "Database", "Connect to database ... %s/%s@%s",dbuser,"******",dbname);
	
	if(!m_pTinitServer->ConnectDB(dbname,dbuser,dbpasswd))
	{
		REPORT_EVENT(LOG_CRITICAL, "Database", "Connect database error %s/%s@%s",dbuser,"******",dbname);
		return false;
	}
	//�ϳ�
	m_pTinitServer->OnTradingDayInit();
	return true;
}

void CTinitReactor::ExitInstance()
{
	delete m_pTinitServer;
}

int WriteCSV(SACommand &saCommand, TTinitTableInfo *pTableInfo, const char *pszCSVPath)
{
	char *buf = new char[4096];

	sprintf(buf, "%s%s.csv", pszCSVPath, pTableInfo->pszTable);
	FILE *fpCSV = mfopen(buf, "wb");
	if (fpCSV == NULL)
	{
		REPORT_EVENT(LOG_CRITICAL, "ExportCSV","Can't open output file [%s]", buf);
		return -3;
	}

	REPORT_EVENT(LOG_CRITICAL, "ExportCSV","Exporting %s ...", pTableInfo->pszTable);
	
	CFieldDescribe *pFieldDesc = pTableInfo->pFieldDescribe;
	//�ļ�ͷ
	for (int i=0; i<pFieldDesc->GetMemberCount(); i++)
	{
		TMemberDesc *pMemberDesc=pFieldDesc->GetMemberDesc(i);
		fprintf(fpCSV, "\"%s\"",pMemberDesc->szName);
		if (i != pFieldDesc->GetMemberCount()-1)
		{
			fprintf(fpCSV, ",");
		}
	}
	fprintf(fpCSV, "\n");
	
	int nRowCount = 0;
	//�ļ�����
	while(saCommand.FetchNext())
	{
		int ret = CDbConnection::GetRow(&saCommand, buf, pFieldDesc);
		if (ret)
		{
			for (int i=0; i<pFieldDesc->GetMemberCount(); i++)
			{
				TMemberDesc *pMemberDesc=pFieldDesc->GetMemberDesc(i);
				char *pMember = buf+pMemberDesc->nStructOffset;
				switch(pMemberDesc->nType)
				{
				case FT_WORD:
					fprintf(fpCSV, "\"%d\"", *((WORD *)pMember)&0xFFFF);
					break;
				case FT_DWORD:			
					fprintf(fpCSV, "\"%d\"", *((DWORD *)pMember));
					break;
				case FT_BYTE:
					if (pMemberDesc->nSize == 1)
					{
						fprintf(fpCSV, "\"%c\"", *pMember&0xFF);
					}
					else
					{
						fprintf(fpCSV, "\"%s\"", pMember);
					}
					break;
				case FT_REAL4:
					fprintf(fpCSV, "\"%f\"",*((REAL4 *)pMember));
					break;
				case FT_REAL8:
					{
						double d;
						memcpy(&d, pMember, sizeof(REAL8));
						if (d == DOUBLE_NaN)
						{
							fprintf(fpCSV, "\"\"");
						}
						else
						{
							fprintf(fpCSV, "\"%lf\"",d);
						}
					}
					break;
				}
				if (i != pFieldDesc->GetMemberCount()-1)
				{
					fprintf(fpCSV, ",");
				}
			}
			fprintf(fpCSV, "\n");
			nRowCount++;
		}
	}
	delete buf;
	fclose(fpCSV);

	REPORT_EVENT(LOG_CRITICAL, "ExportCSV","Table %s : %d rows exported", pTableInfo->pszTable, nRowCount);
	return nRowCount;
}

int GetSystemID(CDbConnection *pDbConnection,char *systemid)
{
	typedef vector<string> CIPVec;
	CIPVec IPVect;
	IPVect.clear();
	bool ret =GetIPAddress(&IPVect);
	if (!ret || IPVect.size()==0)
	{
		REPORT_EVENT(LOG_CRITICAL, "GetSystemID", "��ȡ����IP��ַʧ��! ret=%d ip_size=%d",ret,IPVect.size());
		exit(-1);
	}
	
	typedef map<string,CSystemInfoField> CSystemMap;
	CSystemMap SystemMap;
	SystemMap.clear();
	CSystemInfoField SystemInfo;
	SACommand cmd(pDbConnection,"SELECT systemip,systemid,systemname FROM t_sync_systeminfo");
	cmd.Execute();
	while (cmd.FetchNext())
	{
		CDbConnection::GetRow(&cmd,(char *)&SystemInfo, &SystemInfo.m_Describe);
		SystemMap.insert(CSystemMap::value_type(SystemInfo.SystemIP.getValue(),SystemInfo));
	}
	
	if (SystemMap.size()==0)
	{
		REPORT_EVENT(LOG_CRITICAL, "GetSystemID", "�����ݿ��ȡ��������ʧ��!");
		exit(-1);
	}
	
	int len = IPVect.size();
	for (int i=0;i<len;i++)
	{
		for(CSystemMap::iterator pSysIter =SystemMap.begin();pSysIter!=SystemMap.end();pSysIter++)
		{
			if (strcmp(IPVect[i].c_str(),pSysIter->first.c_str())==0)
			{
				strcpy(systemid,pSysIter->second.SystemID.getValue());
				return 0;
			}
		}
	}
	REPORT_EVENT(LOG_CRITICAL, "GetSystemID", "�����ݿ��ȡƥ��Ľ�������ʧ��!");
	exit(-1);
}

int ExportCSV()
{
	char szBuffer[300];
	string strCSVPath;	

	GetConfigString(INI_FILE_NAME, "CSVPath",szBuffer, sizeof(szBuffer));
	strCSVPath = szBuffer;

	char dbname[300];
	char dbpasswd[300];
	char dbuser[300];
	GetConfigString(INI_FILE_NAME, "dbname",szBuffer, sizeof(szBuffer));
	strncpy(dbname,szBuffer,sizeof(szBuffer));
	GetConfigString(INI_FILE_NAME, "dbuser",szBuffer, sizeof(szBuffer));
	strncpy(dbuser,szBuffer,sizeof(szBuffer));
	GetConfigString(INI_FILE_NAME, "dbpasswd",szBuffer, sizeof(szBuffer));
	strncpy(dbpasswd,szBuffer,sizeof(szBuffer));
	

	REPORT_EVENT(LOG_CRITICAL, "ExportCSV", "Export CSV from [%s] to [%s]", dbname, strCSVPath.c_str());
	CDbConnection conn;
	if(!conn.ConnectDB(dbname, dbuser, dbpasswd))
	{
		REPORT_EVENT(LOG_CRITICAL, "Database", "Connect database error %s/%s@%s",dbuser,"******",dbname);
		return -1;
	}

	//��ȡ�������ĺ�
	char SystemID[10];
	memset(SystemID,0,sizeof(SystemID));
	GetSystemID(&conn,SystemID);

	SACommand saCommand(&conn);
	saCommand.setOption("PreFetchRows") = "1000";

	char szSQL[256];
	try
	{
		//���ƴװһ������ִ�е�SQL���
		TTinitTableInfo *pTableInfo = g_DayTableInfo;
		for (;pTableInfo->tid != 0; pTableInfo++)
		{
			memset(szSQL,0,sizeof(szSQL));
			strcpy(szSQL,"SELECT ");
			for (int i=0; i<pTableInfo->pFieldDescribe->GetMemberCount(); i++)
			{
				if (i != 0)
				{
					strcat(szSQL, ", ");
				}
				strcat(szSQL, pTableInfo->pFieldDescribe->GetMemberDesc(i)->szName);
			}
			if (pTableInfo->bHasSystemID)
			{
				sprintf(szSQL+strlen(szSQL)," FROM %s WHERE systemid=:1",pTableInfo->pszTable);
			}
			else
			{
				sprintf(szSQL+strlen(szSQL)," FROM %s",pTableInfo->pszTable);
			}

			saCommand.setCommandText(szSQL);
			if (pTableInfo->bHasSystemID)
			{
				saCommand.Param(1).setAsString() = SystemID;
			}
			saCommand.Execute();
			//conn.Commit();
			
			//����������ļ���
			if(WriteCSV(saCommand, pTableInfo, strCSVPath.c_str()) < 0)
			{
				return -2;
			}

		}
	}
	catch(SAException &x)
	{
		// longqy 2014-05-28 �޸�����һ���ǣ�Ϊ���� RHEL7 �������ͨ��	
		REPORT_EVENT(LOG_CRITICAL, "ExportCSV", "Database error:[%d][%s]",x.ErrNativeCode(), x.ErrText().GetBuffer(x.ErrText().GetLength()));
		return -4;
	}
	REPORT_EVENT(LOG_INFO, "ExportCSV", "Export CSV completed.");
	return 0;
}

void CmdLineArgError()
{
	printf("Useage: qdata (use database to upload )\n");
	printf("        qdata -d tradingday (use csv to upload)\n");
	printf("        qdata -e (dump database to csv)\n");
	exit(0);
}

int main(int argc, char *argv[])
{
//#ifdef UNIX
//	signal(SIGABRT, SIG_IGN);
//	signal(SIGPIPE, SIG_IGN);
//	signal(SIGINT, SIG_IGN);
//#endif
	showVersion(argc,argv);	

	//��ȡ������Ϣ
	CConfig *pConfig = new CConfig(INI_FILE_NAME);
	char *syslogFileName=pConfig->getConfig("SyslogPath");
	CMonitorIndex::init(CFilelogService::CreateInstance(argc,argv,syslogFileName),pConfig);
	delete pConfig;

	if (argc == 1)
	{
		//tinit
		CTinitReactor reactor;
		reactor.Create();
		reactor.Join();
	}
	else if (argc == 3)
	{
		//tinit -d 20121122
		CFileInitReactor freactor(argv[2]);
		freactor.Create();
		freactor.Join();
	}
	else if (argc == 2 && strcmp(argv[1], "-e")==0)
	{
		//tinit -e
		return ExportCSV();
	}
	else
	{
		CmdLineArgError();
	}
	return 0;
}
