// DBUserApi.cpp : Defines the entry point for the DLL application.
//
#include <stdio.h>
#include "DBUserApi.h"
#include "DBUserImpApi.h"

DBUserAPI::DBUserAPI()
{
	pDBUserImpAPI = new DBUserImpAPI();
}

DBUserAPI::~DBUserAPI()
{
	if(pDBUserImpAPI)
	{
		delete pDBUserImpAPI;
	}
	pDBUserImpAPI = NULL;
}

bool DBUserAPI::ConnectToDB(char* pIP, char* pUser, char* pPassword, char* pDBName)
{
    return pDBUserImpAPI->ConnectToDB(pIP, pUser, pPassword, pDBName);
}

//�ر����ݿ�����
void DBUserAPI::CloseDB()
{
	pDBUserImpAPI->CloseDB();
}



//��ʼ�����ݿ�
bool DBUserAPI::init_database_library()
{
	return DBUserImpAPI::init_database_library();
}



/*
 * ȡ���ݿ�ִ�д������
 * @return ����ִ�д�����
 */
int DBUserAPI::GetDBErrCode()
{
    return pDBUserImpAPI->GetDBErrCode();
}

/*
 * ȡ���ݿ�ִ�д�����Ϣ
 * @return ����ִ�д�����Ϣ
 */              
const char * DBUserAPI::GetDBErrInfo()
{
    return pDBUserImpAPI->GetDBErrInfo();
}


/*
 * ִ��SQL���
 * @param lpSqlBuf  SQL���
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int DBUserAPI::Execute(char const *lpSqlBuf)
{
    return pDBUserImpAPI->Execute(lpSqlBuf);
}

int DBUserAPI::GetAffactRow()
{
	return pDBUserImpAPI->GetAffactRow();
}


/*
 * �����ύ
 */
bool DBUserAPI::Commit()
{
    return pDBUserImpAPI->Commit();
}

/*
 * ����ع�
 */
bool DBUserAPI::RollBack()
{
    return pDBUserImpAPI->RollBack();
}
	

/*
 * ������ĸ���
 * @return ���������
 */
int DBUserAPI::GetFieldCount()
{
    return pDBUserImpAPI->GetFieldCount();
}

/*
 * ȡ�α���һ����¼
 * @return true��ʾ���б�ȡ�� false��ʾû���µ�����
 */
bool DBUserAPI::FetchNext()
{ 
    return pDBUserImpAPI->FetchNext();
}

int  DBUserAPI::GetByte(const char *lpFieldName, char& FieldData)
{
	return pDBUserImpAPI->GetByte(lpFieldName, FieldData);
}


/*
 * ��ȡ�ַ�������
 * @param lpFieldName ��������
 * @param FieldData   ��ȡ����������
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int  DBUserAPI::GetString(const char *lpFieldName, char* FieldData)
{
    return pDBUserImpAPI->GetString(lpFieldName, FieldData);
}  

/*
 * ��ȡ˫������
 * @param lpFieldName ��������
 * @param FieldData   ��ȡ����������
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int  DBUserAPI::GetDouble(const char *lpFieldName, double& lpFieldData)
{
    return pDBUserImpAPI->GetDouble(lpFieldName, lpFieldData);
}

/*
 * ��ȡ������
 * @param lpFieldName ��������
 * @param FieldData   ��ȡ����������
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int  DBUserAPI::GetLong(const char *lpFieldName, long& lpFieldData)
{
    return pDBUserImpAPI->GetLong(lpFieldName, lpFieldData);
}  

/*
 * ��ȡ��������
 * @param lpFieldName ��������
 * @param FieldData   ��ȡ����������
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int  DBUserAPI::GetInt(const char *lpFieldName, int& lpFieldData)
{
    return pDBUserImpAPI->GetInt(lpFieldName, lpFieldData);
} 


int  DBUserAPI::GetByte(unsigned int index, char& FieldData)
{
	return pDBUserImpAPI->GetByte(index, FieldData);
}

/*
 * ��ȡ�ֶ�����
 * @param index       ������˳��:��0��ʼ
 * @param fieldname   ��ȡ�ֶ�����
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int DBUserAPI::GetFieldName(unsigned int index, char* fieldname)
{
	return pDBUserImpAPI->GetFieldName(index, fieldname);
}


/*
 * ��ȡ�ַ�������
 * @param index       ������˳��
 * @param FieldData   ��ȡ����������
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int  DBUserAPI::GetString(unsigned int index, char* FieldData) 
{
    return pDBUserImpAPI->GetString(index, FieldData);
}  

/*
 * ��ȡ˫������
 * @param index       ������˳��
 * @param FieldData   ��ȡ����������
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int  DBUserAPI::GetDouble(unsigned int index, double& lpFieldData)
{
    return pDBUserImpAPI->GetDouble(index, lpFieldData);
}
/*
 * ��ȡ��������
 * @param index       ������˳��
 * @param FieldData   ��ȡ����������
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int  DBUserAPI::GetLong  (unsigned int index, long& lpFieldData)
{
    return pDBUserImpAPI->GetLong(index, lpFieldData);
}  
/*
 * ��ȡ������
 * @param index       ������˳��
 * @param FieldData   ��ȡ����������
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int  DBUserAPI::GetInt (unsigned int index, int& lpFieldData)
{
    return pDBUserImpAPI->GetInt(index, lpFieldData);
} 