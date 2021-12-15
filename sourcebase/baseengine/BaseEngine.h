/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file BaseEngine.h
///@brief定义了类CMemoryEngine
///@history 
///20060903	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef BASEENGINE_H
#define BASEENGINE_H

#include "CConfig.h"
#include "errorDefine.h"
#include "CMemoryDB.h"
#include "CDumpLog.h"
#include "monitorIndex.h"

/////////////////////////////////////////////////////////////////////////
///CBaseEngine是一个处理引擎的基类，管理了内存数据库，并完成了恢复操作
///@author	xuzh
///@version	1.0,20060903
/////////////////////////////////////////////////////////////////////////
class CBaseEngine
{
public:
	///构造函数
	///@param	pConfig	创建引擎需要使用的配置
	///@param	recovery	是否使用恢复模式
	///@param	verbose	true表示要输出结果，flase表示不要输出结果
	CBaseEngine(CConfig *pConfig,bool verbose=true);
	
	virtual ~CBaseEngine(void);

	///开始处理某个编号的消息
	///@param	seqID	要处理的消息的编号
	///@return	true表示正常，false表示要进行紧急处理
	virtual bool startProcess(int seqID);
	
	///结束处理某个编号的消息
	///@param	seqID	刚处理完的消息编号
	///@return	true表示正常，false表示要进行紧急处理
	virtual bool endProcess(int seqID);

protected:
	///读取下一个处理编号，进入时，文件指针在读入前的位置，
	///如果读入成功，则进入下一个读入前的位置，如果不成功，
	///则在原位不动
	///@return	下一个处理编号，如果没有了，则返回0
	virtual int getNextID(void);

	///设置下一个处理编号，处理完后，进入时，文件指针在写入
	///前的位置，返回时，文件指针不动
	///@param	下一个处理编号
	virtual void setNextID(int nextID);

	///进行应急处理
	///@param	seqID	序列号
	virtual void handleEmerge(int seqID);

	///共享内存文件初始化
	///@param	isInit	true：清空置零  false:恢复方式启动，取出其记录值
	///@param	processFileName	共享内存文件名
	///@return	返回映射的共享内存地址，NULL初始化失败
	char *initMmap(bool isInit,char *processFileName);

	bool m_verbose;
	CConfig *m_pConfig;
	CMemoryDB *m_pDB;
	CDumpLog *m_pDumpLog;
	CErrorEngine *m_pErrorEngine;
//	CIntTotalMonitorIndex *m_handleInputIndex;

	FILE *m_processFile;

	char *m_pProcess;
	int  m_CurrPos;
};

#endif
