/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海期货信息技术有限公司
///@file CXML.h
///@brief定义了与DBF操作有关的类接口
///@history 
///20060104 王肇东	创建该文件
///20061113 王习平  增加了setDoubleField方法
///20100831 徐忠华  增加getField,rtrim,ltrim,void printAll方法
///20121114 徐忠华	增加readRecords,getRecWidth,getFieldCount方法
/////////////////////////////////////////////////////////////////////////

/* current ristriction
	1 can not write to dbf file with memo
	2 can not write to number field with decimal easily
	3 can not delete a field actually
	4 接口中提供的是对文件的操作，如果需要一次将文件读入内存，然后取字段需要使用readRecords,自己解析
*/

#ifndef DBF_H
#define DBF_H

#include "platform.h"
#include "system.h"

#define MAX_MEMO_FIELD 20480

const int fieldNameSize = 11;

class CFieldDefine
{
public:
	char name[fieldNameSize];
	char type;
	unsigned char length1;
	unsigned char length2;
	short length;
	int offset;
};

class CDBF
{
public:
	///构造函数
	CDBF(void);
	
	///析构函数，对于打开的数据库，会自动关闭
	~CDBF(void);
	
	///以只读方式打开DBF文件，目前支持DBASE和FOXPRO用的DBF文件
	///@param	database	DBF文件名
	///@return	1表示成功，0表示失败
	/// 打开文件之前关闭打开的文件，所以打开之后，不需要close
	int open(char *database);
	
	///以可写方式打开DBF文件，不能memo字段的写入
	///@param	database	DBF文件名
	///@return	1表示成功，0表示失败
	int openForWrite(char *database);

	///关闭DBF文件
	void close(void);

	///获取一个字段的值
	///@param	fieldName	字段名
	///@param	recno	记录号
	///@param	pLength	返回的长度
	///@return	得到的字段值，长度由pLength指出，同时以\0结尾，如果找不到字段，则返回NULL
	char *getField(char *fieldName,int recno,short *pLength);

	///获取一个字段的值
	///@param	fieldName	字段名
	///@param	recno	记录号
	///@param	pLength	返回的长度
	///@return	得到的字段值，长度由pLength指出，同时以\0结尾，如果找不到字段，则返回NULL
	char *getField(int fieldno,int recno,short *pLength);

	///获取一个字段的值
	///@param	fieldName	字段名
	///@param	recno	记录号
	///@return	得到的字段值，同时以\0结尾，如果找不到字段，则返回NULL
	char *getField(int fieldno,int recno);

	///获取一个字段的名字
	///@param	recno	记录号
	///@return	得到的字段属性名，如果找不到字段名，则返回NULL
	char *getFieldName(int recno);

	///获取一个字段的lenth1
	///@param	recno	记录号
	///@return	得到的字段length1，如果找不到字段名，则返回-1
	unsigned char getFieldLength1(int recno);

	///获取一个字段的lenth2
	///@param	recno	记录号
	///@return	得到的字段length2，如果找不到字段名，则返回-1
	unsigned char getFieldLength2(int recno);

	///获取一个字段的lenth
	///@param	recno	记录号
	///@return	得到的字段length，如果找不到字段名，则返回-1
	short getFieldLength(int recno);
	///获取字段的定义
	///@param	fieldName	字段名
	///@return	得到的字段定义，NULL表示没有找到该字段
	CFieldDefine *getFieldDefine(char *fieldName);
	
	///获取字段定义
	///@param	pFieldCount	用于存储返回的字段个数
	///@return	字段的定义数组，长度在pFieldCount中返回
	CFieldDefine *getFieldDefines(short *pFieldCount);
	
	///获取记录总数
	///@return	记录总数
	int getRecCount(void);
	
	///获取最后修改年份
	///@return	最后修改年份
	int getYear(void);
	
	///获取最后修改月份
	///@return	最后修改月份
	char getMonth(void);
	
	///获取最后修改日期
	///@return	最后修改天
	char getDay(void);

	///获取最后修改日期
	///@return	最后修改日期	
	int getDate();

	///获取记录宽度
	///@return	记录宽度
	int getRecWidth(void);
	
	///获取记录个数
	///@return	记录个数
	int getReccount(void);
	
	///获取字段个数
	///@return	字段个数
	int getFieldCount(void);


	///设置一个字段的值
	///@param	fieldName	字段名
	///@param	recno	记录号
	///@param	value	要设置的值，不要求以\0结尾
	///@param	length	要设置的值的长度,0表示使用字段定义中的缺省长度
	///@return	1表示成功，0表示失败
	int setField(char *fieldName,int recno,char *value,short length);

	///设置字符字段
	///@param	fieldName	字段名
	///@param	recno	记录号
	///@param	value	要设置的值，要求以\0结尾
	///@return	1表示成功，0表示失败
	int setCharacterField(char *fieldName,int recno,char *value);
	
	///设置整数字段
	///@param	fieldName	字段名
	///@param	recno	记录号
	///@param	value	要设置的值
	///@return	1表示成功，0表示失败
	int setIntField(char *fieldName,int recno,int value);
	
	
	///设置浮点数字段
	///@param	fieldName	字段名
	///@param	recno	记录号
	///@param	value	要设置的值
	///@return	1表示成功，0表示失败
	int setDoubleField(char *fieldName,int recno,double value);
	
	///设置日期字段
	///@param	fieldName	字段名
	///@param	recno	记录号
	///@param	value	要设置的值
	///@return	1表示成功，0表示失败
	int setDateField(char *fieldName,int recno,char *value);
	
	///设置任意字段
	///@param	fieldName	字段名
	///@param	recno	记录号
	///@param	value	要设置的值，要求以\0结尾
	///@return	1表示成功，0表示失败
	int setAnyField(char *fieldName,int recno,char *value);

	///删除一条记录，仅做软删除
	///@param	recno	记录号
	///@return	1表示成功，0表示失败
	int deleteRecord(int recno);

	///判断一条记录是否被删除了
	///@param	recno	记录号
	///@return	1表示已经删除，0表示没有删除，-1表示失败
	int isDeletedRecord(int recno);

	///恢复已经删除的记录
	///@param	recno	记录号
	///@return	1表示成功，0表示失败
	int recallRecord(int recno);

	///寻找某一个字段等于指定值的记录
	///@param	fieldName	字段名
	///@param	startRecno	开始寻找的记录号
	///@param	value	要满足的值，不需要以\0结尾
	///@param	length	值需要比较的长度，超出长度的部分，可以不相等
	///@return	找到的记录号，0表示没有找到
	int locateField(char *fieldName,int startRecno,char *value,short length);

	///寻找第一个字段大于等于指定值的记录，要求原DBF文件已经按照该字段排序，将使用二分查找法
	///@param	fieldName	字段名
	///@param	startRecno	开始寻找的记录号，0表示从头开始寻找
	///@param	endRecno	结束寻找的记录号，0表示一直找到底
	///@param	value	要满足的值，不需要以\0结尾
	///@param	length	值需要比较的长度
	///@return	找到的记录号，0表示没有找到
	int seekField(char *fieldName,int startRecno,int endRecno,char *value,short length);

	///在DBF文件的结束位置，增加一条空白的新记录
	///@return	1表示成功，0表示失败
	int appendRecord(void);
	
	///读取from到records的记录到buf中
	///@param	from	记录开始号
	///@param	records	记录结束号
	///@param	buf	存储的数组
	///@return	1表示成功，0表示失败
	int readRecords(DWORD from,int records,void *buf);

	///去除字符串尾的空格
	///@param	pstring	字段名
	///@return	得到无头尾空格 字段值
	char* rTrim(char * pstring);
	
	///去除字符串头部的空格
	///@param	pstring	字段名
	///@return	得到无头尾空格 字段值
	char* lTrim(char * pstring);

	///输出所有的记录
    ///@return 输出头属性和所有的记录情况
	void printAll(void);
	
private:
	int recCount;
	char year;
	char month;
	char day;
	int recWidth;
	short fieldCount;
	CFieldDefine *fieldDefines;

	bool opened;
	char id;
	int handle;
	//每条记录读入的内存
	char *recBuffer;
	short startPos;

	int memoHandle;
	int memoBlockLength;
	char *memoBuffer;
};

#endif
