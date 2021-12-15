// dbf_file.h: interface for the CDbfFile class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBFFILE_H__EBE57BE4_8FC9_427D_B221_FF8D6C806731__INCLUDED_)
#define AFX_DBFFILE_H__EBE57BE4_8FC9_427D_B221_FF8D6C806731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dbf.h"

class CDbfFile
{
public:
	CDbfFile();
	~CDbfFile();
	//打开DBF文件
	int OpenDbfFile(char* pDbfFilePath);
	//创建新的DBF文件，建立表结构
	int CreateDbfFile(char* pDbfFilePath, int nFieldNum, TField* pDbfFieldStruct);
	//读DBF文件的某行记录
	void ReadDbfRecord(void* pDataBuffer);
	//Append方式在DBF文件中追加某行记录
	int WriteDbfRecord(void* pDataBuffer);
	//Append方式在DBF文件中追加一个空白行
	int WriteDbfBlank();
	//以空格初始化记录行
	int InitRecordBuffer();
    //定位在DBF文件某行记录上
    void LocateRecordLine(int nRecordLineNo);
	//取字段值，返回Double
	double GetDouble(char *fieldname);
	//取字段值，返回Int
    int GetInt(char *fieldname);
    //取字段值，返回Long
	long GetLong(char *fieldname);
    //取字段值，返回String
	char* GetString(char *fieldname);
    //取字段值，返回Date
    char* GetDate(char *fieldname);
    //取字段值，返回Binary
    void* GetBinary(char *fieldname);
	//修改字段值（字符串类型）
	int SetString(char *fieldname, char *pValue);
	//修改字段值（整数类型）
	int SetInt(char *fieldname, int data);
	//修改字段值（长整数类型）
	int SetLong(char *fieldname, long data);
	//修改字段值（浮点数类型）	
	int SetDouble(char *fieldname, double data);
	//设置字段值（日期类型）
	int SetDate(char *fieldname, char *pValue);
	//修改字段值（二进制类型）
    int SetBinary(char *fieldname, void *bin, int blen);
	//设置字段值（仅缓冲区）（字符串类型）
	int SetStringBuffer(char *fieldname,  const char *pValue);
	//设置字段值（仅缓冲区）（整数类型）
	int SetIntBuffer(char *fieldname, int data);
	//设置字段值（仅缓冲区）（长整数类型）
	int SetLongBuffer(char *fieldname, long data);
	//修改字段值（仅缓冲区）（浮点数类型）	
	int SetDoubleBuffer(char *fieldname, double data);
	//设置字段值（仅缓冲区）（日期类型）
	int SetDateBuffer(char *fieldname, char *pValue);
	//修改字段值（仅缓冲区）（二进制类型）
    int SetBinaryBuffer(char *fieldname, void *bin, int blen);
    //取一条记录内容放到缓冲区中
	void GetRecordBuffer(char* record_buf);
	//取DBF文件的记录数
    int GetRecordNum();
	//取DBF文件的记录的长度（固定值）
	int GetRecordLen();
   //取DBF文件的每行字段数
	int GetFieldCount();
    //取DBF文件的每行字段数信息
	TField * getFieldinfo(int fieldno);
    //关闭DBF文件
	int CloseDbfFile();
    //将N笔记录批量写入DBF文件
	int WriteBatchRecords(int from, int records, void *buf);
	//写入结束标记
    int WriteEndFlag();
private:
	CDBF m_dbf_handle;
	char *m_binaryBuffer;
};

#endif