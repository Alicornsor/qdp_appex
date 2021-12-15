//**********************************************************************
//文件名： 		DBUserAPI.h
//主要功能:		数据库使用接口
//作  者：      何显胜
//说    明：    
//用法说明：
//修改历史：
//**********************************************************************
#ifndef __DBUSERAPI_H__
#define __DBUSERAPI_H__


class DBUserImpAPI;

//数据库API
class  DBUserAPI
{
public:
    //构造函数,初始化SQLAPI
    DBUserAPI();
    
    //析构函数
	~DBUserAPI();

	//初始化数据库
	static bool init_database_library(); 

//基本操作
public:

	//连接数据库
	bool ConnectToDB(char* pIP, char* pUser, char* pPassword, char* pDBName);

	//关闭数据库
    void CloseDB();
	
	/*
	 * 取数据库执行错误代码
	 * @return 返回执行错误码
	 */
	int GetDBErrCode();
	
	/*
	 * 取数据库执行错误信息
	 * @return 返回执行错误信息
	 */              
	const char * GetDBErrInfo(); 


//输入方式
public:	
	/*
	 * 执行SQL语句
	 * @param lpSqlBuf  SQL语句
	 * @return 0表示处理成功 -1表示处理失败
	 */
	int Execute(char const *lpSqlBuf);
	
	/*
	 * 事务提交
	 */
	bool Commit(); 

	int GetAffactRow();
	
	/*
	 * 事务回滚
	 */
	bool RollBack();
		
	/*
	 * 返回域的个数
	 * @return 数据域个数
	 */
	int GetFieldCount();

	/*
	 * 取游标下一条记录
	 * @return true表示新行被取到 false表示没有新的数据
	 */
	bool FetchNext(); 
	
	/*
	 * 获取字符类型域
	 * @param lpFieldName 数据域名
	 * @param FieldData   获取的数据内容
	 * @return 0表示处理成功 -1表示处理失败
	 */
	int  GetString(const char *lpFieldName, char* FieldData);  
	
	/*
	 * 获取单字符类型域
	 * @param lpFieldName 数据域名
	 * @param FieldData   获取的数据内容
	 * @return 0表示处理成功 -1表示处理失败
	 */
	int  GetByte(const char *lpFieldName, char& FieldData);

	/*
	 * 获取双精度域
	 * @param lpFieldName 数据域名
	 * @param FieldData   获取的数据内容
	 * @return 0表示处理成功 -1表示处理失败
	 */
	int  GetDouble(const char *lpFieldName, double& lpFieldData);
	
	/*
	 * 获取长整型域
	 * @param lpFieldName 数据域名
	 * @param FieldData   获取的数据内容
	 * @return 0表示处理成功 -1表示处理失败
	 */
	int  GetLong  (const char *lpFieldName, long& lpFieldData);  
	
	/*
	 * 获取整型域
	 * @param lpFieldName 数据域名
	 * @param FieldData   获取的数据内容
	 * @return 0表示处理成功 -1表示处理失败
	 */
	int  GetInt (const char *lpFieldName, int& lpFieldData); 

	/*
	 * 获取字段名称
	 * @param index       数据域顺序:从0开始
	 * @param fieldname   获取字段名称
	 * @return 0表示处理成功 -1表示处理失败
	 */
	int GetFieldName(unsigned int index, char* fieldname);

	/*
	 * 获取单字符类型域
	 * @param index       数据域顺序:从0开始
	 * @param FieldData   获取的数据内容
	 * @return 0表示处理成功 -1表示处理失败
	 */
	int  GetByte(unsigned int index, char& FieldData);  

	/*
	 * 获取字符类型域
	 * @param index       数据域顺序:从0开始
	 * @param FieldData   获取的数据内容
	 * @return 0表示处理成功 -1表示处理失败
	 */
	int  GetString(unsigned int index, char* FieldData);  
	
	/*
	 * 获取双精度域
	 * @param index       数据域顺序:从0开始
	 * @param FieldData   获取的数据内容
	 * @return 0表示处理成功 -1表示处理失败
	 */
	int  GetDouble(unsigned int index, double& lpFieldData);
	
	/*
	 * 获取长整型域
	 * @param index       数据域顺序:从0开始
	 * @param FieldData   获取的数据内容
	 * @return 0表示处理成功 -1表示处理失败
	 */
	int  GetLong  (unsigned int index, long& lpFieldData);  
	
	/*
	 * 获取整型域
	 * @param index       数据域顺序:从0开始
	 * @param FieldData   获取的数据内容
	 * @return 0表示处理成功 -1表示处理失败
	 */
	int  GetInt (unsigned int index, int& lpFieldData); 

private:
	DBUserImpAPI* pDBUserImpAPI;
};

#endif

