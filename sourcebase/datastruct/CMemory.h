/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CMemory.h
///@brief定义了类CMemory类和stringMemory全局变量
///@history 
///20020214	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CMEMORY_H
#define CMEMORY_H

#include "platform.h"
#include "CBaseObject.h"

///定义了缺省的每个内存块大小
#define BLOCK_SIZE 10240

/////////////////////////////////////////////////////////////////////////
///CMemory是一个负责内存管理的对象。它管理的内存区域是变长的，总大小只会单调增长，
///不会减少。适用于小规模的字符串内存空间管理
///@author	xuzh
///@version	1.0,20020214
/////////////////////////////////////////////////////////////////////////
class CMemory: public CBaseObject
{
public:
	///构造函数，按照指定的blockSize，开始从系统申请空间，以便提供服务
	///@param	blockSize	每个内存申请块的大小，这里的内存申请块是指
	///			已经申请的内存量不够是，本对象每次追加申请
	///			的块大小。本参数可以缺省为BLOCK_SIZE
	CMemory(int blockSize=BLOCK_SIZE);
	
	///析构函数，没有实质工作
	virtual ~CMemory(void);
	
	virtual int isA(char *objectType);
	virtual char *getType(void);
	virtual void output(CLogger *pLogger,int indent=0);

	///申请指定大小的一段空间
	///@param	size	要申请的空间大小，以byte计
	///@return	指向申请到的空间的首地址
	///@exception	CDesignError	如果本次申请的空间超过blockSize，那么抛出此异常
	char *alloc(int size);

	///复制一个字符串，会申请strlen(s)+1大小的空间
	///@param	s	要复制的字符串
	///@return	复制得到的字符串首地址
	char *dup(char *s);

	///复制一段空间，会申请size大小的空间
	///@param	buffer	要复制的空间的首地址
	///@param	size	要复制的空间的大小
	///@return	复制得到的空间首地址
	char *dup(char *buffer, int size);
private:
	///申请一块新的内存，其大小由blockSize指定。
	///@exception	CRuntimeError	在内存不够时抛出此异常
	void newBlock(void);
	
	///用于存储每个内存申请块的大小
	int blockSize;
	
	///用于存储当前内存申请块的首地址
	char *base;
	
	///用于存储当前申请块中还没有使用的空间的首地址
	char *current;
};

///全局变量，用于各个系统申请字符串空间
extern CMemory stringMemory;

#endif
