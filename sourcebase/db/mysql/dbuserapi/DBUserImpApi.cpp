// DBUserImpAPI.cpp : Defines the entry point for the DLL application.
//

#include "DBUserImpApi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//数据库操作类型
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
		//初始化数据结构
		if(NULL == mysql_init(&m_mydata))
		{
			printf("mysql_init failed\n");
			return false;
		}
		//在连接数据库前，设置额外的连接选项
		//可以设置的选项很多，这里设置字符集，否则无法处理中文
		if(0 != mysql_options(&m_mydata,MYSQL_SET_CHARSET_NAME,"gbk"))
		{
			printf("mysql_options failed\n");
			return false;
		}
		//设置自动重连
		if(0 != mysql_options(&m_mydata,MYSQL_OPT_RECONNECT,"1"))
		{
			printf("mysql_options failed\n");
			return false;
		}
		//连接数据库
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

//关闭数据库连接
void DBUserImpAPI::CloseDB()
{
	mysql_close(&m_mydata);
}



//初始化数据库
bool DBUserImpAPI::init_database_library()
{
	//初始化数据库
	if(0 != mysql_library_init(0, NULL,NULL))
	{
		printf("mysql_library_init failed\n");
		return false;
	}
	return true;
}



/*
 * 取数据库执行错误代码
 * @return 返回执行错误码
 */
int DBUserImpAPI::GetDBErrCode()
{
    return mysql_errno(&m_mydata);
}

/*
 * 取数据库执行错误信息
 * @return 返回执行错误信息
 */              
const char * DBUserImpAPI::GetDBErrInfo()
{
    return mysql_error(&m_mydata);
}


/*
 * 执行SQL语句
 * @param lpSqlBuf  SQL语句
 * @return 0表示处理成功 -1表示处理失败
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
		//一次性取得数据集合
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
 * 事务提交
 */
bool DBUserImpAPI::Commit()
{
    try
    {
        //提交事务
		mysql_commit(&m_mydata);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

/*
 * 事务回滚
 */
bool DBUserImpAPI::RollBack()
{
    try
    {
		//回滚事务
        mysql_rollback(&m_mydata);
    }
    catch (...)
    {
        return false;
    }
    return true;
}
	

/*
 * 返回域的个数
 * @return 数据域个数
 */
int DBUserImpAPI::GetFieldCount()
{
    return mysql_num_fields(m_result);;
}

/*
 * 取游标下一条记录
 * @return true表示新行被取到 false表示没有新的数据
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
		//取得并打印各字段的名称
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
 * 获取字符类型域
 * @param lpFieldName 数据域名
 * @param FieldData   获取的数据内容
 * @return 0表示处理成功 -1表示处理失败
 */
int  DBUserImpAPI::GetString(const char *lpFieldName, char* FieldData)
{
    try
    {
		//取得并打印各字段的名称
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
 * 获取字段名称
 * @param index       数据域顺序:从0开始
 * @param fieldname   获取字段名称
 * @return 0表示处理成功 -1表示处理失败
 */
int DBUserImpAPI::GetFieldName(unsigned int index, char* fieldname)
{
	try
    {
        //取得并打印各字段的名称
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
 * 获取双精度域
 * @param lpFieldName 数据域名
 * @param FieldData   获取的数据内容
 * @return 0表示处理成功 -1表示处理失败
 */
int  DBUserImpAPI::GetDouble(const char *lpFieldName, double& lpFieldData)
{
    try
    {
        //取得并打印各字段的名称
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
 * 获取整型域
 * @param lpFieldName 数据域名
 * @param FieldData   获取的数据内容
 * @return 0表示处理成功 -1表示处理失败
 */
int  DBUserImpAPI::GetLong(const char *lpFieldName, long& lpFieldData)
{
    try
    {
        //取得并打印各字段的名称
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
 * 获取短整型域
 * @param lpFieldName 数据域名
 * @param FieldData   获取的数据内容
 * @return 0表示处理成功 -1表示处理失败
 */
int  DBUserImpAPI::GetInt(const char *lpFieldName, int& lpFieldData)
{
    try
    {
        //取得并打印各字段的名称
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
		//取得并打印各字段的名称
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
 * 获取字符类型域
 * @param index       数据域顺序
 * @param FieldData   获取的数据内容
 * @return 0表示处理成功 -1表示处理失败
 */
int  DBUserImpAPI::GetString(unsigned int index, char* FieldData) 
{
    try
    {
		//取得并打印各字段的名称
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
 * 获取双精度域
 * @param index       数据域顺序
 * @param FieldData   获取的数据内容
 * @return 0表示处理成功 -1表示处理失败
 */
int  DBUserImpAPI::GetDouble(unsigned int index, double& lpFieldData)
{
    try
    {
        //取得并打印各字段的名称
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
 * 获取长整型域
 * @param index       数据域顺序
 * @param FieldData   获取的数据内容
 * @return 0表示处理成功 -1表示处理失败
 */
int  DBUserImpAPI::GetLong  (unsigned int index, long& lpFieldData)
{
    try
    {
        //取得并打印各字段的名称
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
 * 获取整型域
 * @param index       数据域顺序
 * @param FieldData   获取的数据内容
 * @return 0表示处理成功 -1表示处理失败
 */
int  DBUserImpAPI::GetInt (unsigned int index, int& lpFieldData)
{
    try
    {
        //取得并打印各字段的名称
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
