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

//关闭数据库连接
void DBUserAPI::CloseDB()
{
	pDBUserImpAPI->CloseDB();
}



//初始化数据库
bool DBUserAPI::init_database_library()
{
	return DBUserImpAPI::init_database_library();
}



/*
 * 取数据库执行错误代码
 * @return 返回执行错误码
 */
int DBUserAPI::GetDBErrCode()
{
    return pDBUserImpAPI->GetDBErrCode();
}

/*
 * 取数据库执行错误信息
 * @return 返回执行错误信息
 */              
const char * DBUserAPI::GetDBErrInfo()
{
    return pDBUserImpAPI->GetDBErrInfo();
}


/*
 * 执行SQL语句
 * @param lpSqlBuf  SQL语句
 * @return 0表示处理成功 -1表示处理失败
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
 * 事务提交
 */
bool DBUserAPI::Commit()
{
    return pDBUserImpAPI->Commit();
}

/*
 * 事务回滚
 */
bool DBUserAPI::RollBack()
{
    return pDBUserImpAPI->RollBack();
}
	

/*
 * 返回域的个数
 * @return 数据域个数
 */
int DBUserAPI::GetFieldCount()
{
    return pDBUserImpAPI->GetFieldCount();
}

/*
 * 取游标下一条记录
 * @return true表示新行被取到 false表示没有新的数据
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
 * 获取字符类型域
 * @param lpFieldName 数据域名
 * @param FieldData   获取的数据内容
 * @return 0表示处理成功 -1表示处理失败
 */
int  DBUserAPI::GetString(const char *lpFieldName, char* FieldData)
{
    return pDBUserImpAPI->GetString(lpFieldName, FieldData);
}  

/*
 * 获取双精度域
 * @param lpFieldName 数据域名
 * @param FieldData   获取的数据内容
 * @return 0表示处理成功 -1表示处理失败
 */
int  DBUserAPI::GetDouble(const char *lpFieldName, double& lpFieldData)
{
    return pDBUserImpAPI->GetDouble(lpFieldName, lpFieldData);
}

/*
 * 获取整型域
 * @param lpFieldName 数据域名
 * @param FieldData   获取的数据内容
 * @return 0表示处理成功 -1表示处理失败
 */
int  DBUserAPI::GetLong(const char *lpFieldName, long& lpFieldData)
{
    return pDBUserImpAPI->GetLong(lpFieldName, lpFieldData);
}  

/*
 * 获取短整型域
 * @param lpFieldName 数据域名
 * @param FieldData   获取的数据内容
 * @return 0表示处理成功 -1表示处理失败
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
 * 获取字段名称
 * @param index       数据域顺序:从0开始
 * @param fieldname   获取字段名称
 * @return 0表示处理成功 -1表示处理失败
 */
int DBUserAPI::GetFieldName(unsigned int index, char* fieldname)
{
	return pDBUserImpAPI->GetFieldName(index, fieldname);
}


/*
 * 获取字符类型域
 * @param index       数据域顺序
 * @param FieldData   获取的数据内容
 * @return 0表示处理成功 -1表示处理失败
 */
int  DBUserAPI::GetString(unsigned int index, char* FieldData) 
{
    return pDBUserImpAPI->GetString(index, FieldData);
}  

/*
 * 获取双精度域
 * @param index       数据域顺序
 * @param FieldData   获取的数据内容
 * @return 0表示处理成功 -1表示处理失败
 */
int  DBUserAPI::GetDouble(unsigned int index, double& lpFieldData)
{
    return pDBUserImpAPI->GetDouble(index, lpFieldData);
}
/*
 * 获取长整型域
 * @param index       数据域顺序
 * @param FieldData   获取的数据内容
 * @return 0表示处理成功 -1表示处理失败
 */
int  DBUserAPI::GetLong  (unsigned int index, long& lpFieldData)
{
    return pDBUserImpAPI->GetLong(index, lpFieldData);
}  
/*
 * 获取整型域
 * @param index       数据域顺序
 * @param FieldData   获取的数据内容
 * @return 0表示处理成功 -1表示处理失败
 */
int  DBUserAPI::GetInt (unsigned int index, int& lpFieldData)
{
    return pDBUserImpAPI->GetInt(index, lpFieldData);
} 