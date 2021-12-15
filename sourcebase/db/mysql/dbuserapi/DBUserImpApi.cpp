// DBUserImpAPI.cpp : Defines the entry point for the DLL application.
//

#include "DBUserImpApi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//���ݿ��������
#define OPT_ADD 1
#define OPT_UPD 2
#define OPT_DEL 3

DBUserImpAPI::DBUserImpAPI()
{
	m_result = NULL;
}

DBUserImpAPI::~DBUserImpAPI()
{
	if(m_result)
	{
		mysql_free_result(m_result);
		m_result=NULL;
	}
}

bool DBUserImpAPI::ConnectToDB(char* pIP, char* pUser, char* pPassword, char* pDBName)
{
    try
    {
		//��ʼ�����ݽṹ
		if(NULL == mysql_init(&m_mydata))
		{
			printf("mysql_init failed\n");
			return false;
		}
		//���������ݿ�ǰ�����ö��������ѡ��
		//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
		if(0 != mysql_options(&m_mydata,MYSQL_SET_CHARSET_NAME,"gbk"))
		{
			printf("mysql_options failed\n");
			return false;
		}
		//�����Զ�����
		if(0 != mysql_options(&m_mydata,MYSQL_OPT_RECONNECT,"1"))
		{
			printf("mysql_options failed\n");
			return false;
		}
		//�������ݿ�
		if(NULL == mysql_real_connect(&m_mydata, pIP, pUser, pPassword, pDBName,3306,NULL,0))
		{
			printf("mysql_real_connect failed\n");
			return false;
		}
    }
    catch (...)
    {
        return false;
    }
    return true;
}

//�ر����ݿ�����
void DBUserImpAPI::CloseDB()
{
	mysql_close(&m_mydata);
}



//��ʼ�����ݿ�
bool DBUserImpAPI::init_database_library()
{
	//��ʼ�����ݿ�
	if(0 != mysql_library_init(0, NULL,NULL))
	{
		printf("mysql_library_init failed\n");
		return false;
	}
	return true;
}



/*
 * ȡ���ݿ�ִ�д������
 * @return ����ִ�д�����
 */
int DBUserImpAPI::GetDBErrCode()
{
    return mysql_errno(&m_mydata);
}

/*
 * ȡ���ݿ�ִ�д�����Ϣ
 * @return ����ִ�д�����Ϣ
 */              
const char * DBUserImpAPI::GetDBErrInfo()
{
    return mysql_error(&m_mydata);
}


/*
 * ִ��SQL���
 * @param lpSqlBuf  SQL���
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int DBUserImpAPI::Execute(char const *lpSqlBuf)
{
    try
    {
		try
		{
			if(NULL != m_result)
			{
				mysql_free_result(m_result);
				m_result = NULL;
			}
		}
		catch (...) 
		{
			m_result = NULL;
		}
		if(0 != mysql_query(&m_mydata,lpSqlBuf))
			return -1;
		//һ����ȡ�����ݼ���
		m_result = mysql_store_result(&m_mydata);
    }
    catch (...)
    {
        return -1;
    }
    
    return 0;
}

int DBUserImpAPI::GetAffactRow()
{
	try
    {
		return m_mydata.affected_rows;
    }
    catch (...)
    {
        return -1;
    }
    return 0;
}


/*
 * �����ύ
 */
bool DBUserImpAPI::Commit()
{
    try
    {
        //�ύ����
		mysql_commit(&m_mydata);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

/*
 * ����ع�
 */
bool DBUserImpAPI::RollBack()
{
    try
    {
		//�ع�����
        mysql_rollback(&m_mydata);
    }
    catch (...)
    {
        return false;
    }
    return true;
}
	

/*
 * ������ĸ���
 * @return ���������
 */
int DBUserImpAPI::GetFieldCount()
{
    return mysql_num_fields(m_result);;
}

/*
 * ȡ�α���һ����¼
 * @return true��ʾ���б�ȡ�� false��ʾû���µ�����
 */
bool DBUserImpAPI::FetchNext()
{
	m_row = mysql_fetch_row(m_result); 
    return NULL != m_row;
}


int  DBUserImpAPI::GetByte(const char *lpFieldName, char& FieldData)
{
    try
    {
		//ȡ�ò���ӡ���ֶε�����
		unsigned int i = 0; 
		unsigned int fieldcount = mysql_num_fields(m_result);
		MYSQL_FIELD* field = NULL;
		for(i = 0; i <fieldcount;i++)
		{
			field = mysql_fetch_field_direct(m_result,i);
			if(0 == strcmp(field->name, lpFieldName))
				break;
		}
		if(fieldcount+1 != i)
		{
			FieldData = m_row[i][0];
		}
    }
    catch (...)
    {
        return -1;
    }
    
    return 0;
}  

/*
 * ��ȡ�ַ�������
 * @param lpFieldName ��������
 * @param FieldData   ��ȡ����������
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int  DBUserImpAPI::GetString(const char *lpFieldName, char* FieldData)
{
    try
    {
		//ȡ�ò���ӡ���ֶε�����
		unsigned int i = 0; 
		unsigned int fieldcount = mysql_num_fields(m_result);
		MYSQL_FIELD* field = NULL;
		for(i = 0; i <fieldcount;i++)
		{
			field = mysql_fetch_field_direct(m_result,i);
			if(0 == strcmp(field->name, lpFieldName))
				break;
		}
		if(fieldcount+1 == i)
			*FieldData = 0;
		else
			sprintf(FieldData, "%s", m_row[i]);
    }
    catch (...)
    {
        return -1;
    }
    
    return 0;
}  

/*
 * ��ȡ�ֶ�����
 * @param index       ������˳��:��0��ʼ
 * @param fieldname   ��ȡ�ֶ�����
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int DBUserImpAPI::GetFieldName(unsigned int index, char* fieldname)
{
	try
    {
        //ȡ�ò���ӡ���ֶε�����
		unsigned int fieldcount = mysql_num_fields(m_result);
		if(fieldcount < index)
		{
			return -1;
		}
		MYSQL_FIELD* field = mysql_fetch_field_direct(m_result,index);
		sprintf(fieldname, "%s", field->name);
    }
    catch (...)
    {
        return -1;
    }
    return 0;
}

/*
 * ��ȡ˫������
 * @param lpFieldName ��������
 * @param FieldData   ��ȡ����������
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int  DBUserImpAPI::GetDouble(const char *lpFieldName, double& lpFieldData)
{
    try
    {
        //ȡ�ò���ӡ���ֶε�����
		unsigned int i = 0; 
		unsigned int fieldcount = mysql_num_fields(m_result);
		MYSQL_FIELD* field = NULL;
		for(i = 0; i <fieldcount;i++)
		{
			field = mysql_fetch_field_direct(m_result,i);
			if(0 == strcmp(field->name, lpFieldName))
				break;
		}
		if(fieldcount+1 == i)
			lpFieldData = 0.00;
		else
			lpFieldData = atof(m_row[i]);
    }
    catch (...)
    {
        return -1;
    }
    return 0;
}

/*
 * ��ȡ������
 * @param lpFieldName ��������
 * @param FieldData   ��ȡ����������
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int  DBUserImpAPI::GetLong(const char *lpFieldName, long& lpFieldData)
{
    try
    {
        //ȡ�ò���ӡ���ֶε�����
		unsigned int i = 0; 
		unsigned int fieldcount = mysql_num_fields(m_result);
		MYSQL_FIELD* field = NULL;
		for(i = 0; i <fieldcount;i++)
		{
			field = mysql_fetch_field_direct(m_result,i);
			if(0 == strcmp(field->name, lpFieldName))
				break;
		}
		if(fieldcount+1 == i)
			lpFieldData = 0;
		else
			lpFieldData = atol(m_row[i]);
    }
    
    catch (...)
    {
        return -1;
    }
    
    return 0;
}  

/*
 * ��ȡ��������
 * @param lpFieldName ��������
 * @param FieldData   ��ȡ����������
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int  DBUserImpAPI::GetInt(const char *lpFieldName, int& lpFieldData)
{
    try
    {
        //ȡ�ò���ӡ���ֶε�����
		unsigned int i = 0; 
		unsigned int fieldcount = mysql_num_fields(m_result);
		MYSQL_FIELD* field = NULL;
		for(i = 0; i <fieldcount;i++)
		{
			field = mysql_fetch_field_direct(m_result,i);
			if(0 == strcmp(field->name, lpFieldName))
				break;
		}
		if(fieldcount+1 == i)
			lpFieldData = 0;
		else
			lpFieldData = atoi(m_row[i]);
    }
    catch (...)
    {
        return -1;
    }
    return 0;
} 

int  DBUserImpAPI::GetByte(unsigned int index, char& FieldData) 
{
    try
    {
		//ȡ�ò���ӡ���ֶε�����
		unsigned int fieldcount = mysql_num_fields(m_result);
		if(fieldcount != index)
		{
			FieldData = m_row[index][0];
		}
    }
    catch (...)
    {
        return -1;
    }
    
    return 0;
}  

/*
 * ��ȡ�ַ�������
 * @param index       ������˳��
 * @param FieldData   ��ȡ����������
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int  DBUserImpAPI::GetString(unsigned int index, char* FieldData) 
{
    try
    {
		//ȡ�ò���ӡ���ֶε�����
		unsigned int fieldcount = mysql_num_fields(m_result);
		if(fieldcount == index)
			*FieldData = 0;
		else
			sprintf(FieldData, "%s", m_row[index]);
    }
    catch (...)
    {
        return -1;
    }
    
    return 0;
}  

/*
 * ��ȡ˫������
 * @param index       ������˳��
 * @param FieldData   ��ȡ����������
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int  DBUserImpAPI::GetDouble(unsigned int index, double& lpFieldData)
{
    try
    {
        //ȡ�ò���ӡ���ֶε�����
		unsigned int fieldcount = mysql_num_fields(m_result);
		if(fieldcount == index)
			lpFieldData = 0.00;
		else
			lpFieldData = atof(m_row[index]);
    }
    catch (...)
    {
        return -1;
    }
    return 0;
}
/*
 * ��ȡ��������
 * @param index       ������˳��
 * @param FieldData   ��ȡ����������
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int  DBUserImpAPI::GetLong  (unsigned int index, long& lpFieldData)
{
    try
    {
        //ȡ�ò���ӡ���ֶε�����
		unsigned int fieldcount = mysql_num_fields(m_result);
		if(fieldcount == index)
			lpFieldData = 0;
		else
			lpFieldData = atol(m_row[index]);
    }
    
    catch (...)
    {
        return -1;
    }
    
    return 0;
}  
/*
 * ��ȡ������
 * @param index       ������˳��
 * @param FieldData   ��ȡ����������
 * @return 0��ʾ����ɹ� -1��ʾ����ʧ��
 */
int  DBUserImpAPI::GetInt (unsigned int index, int& lpFieldData)
{
    try
    {
        //ȡ�ò���ӡ���ֶε�����
		unsigned int fieldcount = mysql_num_fields(m_result);
		if(fieldcount == index)
			lpFieldData = 0;
		else
			lpFieldData = atoi(m_row[index]);
    }
    catch (...)
    {
        return -1;
    }
    return 0;
} 
