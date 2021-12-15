/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CConfig.h
///@brief定义了类CConfig和CConfigItem
///@history 
///20020214	xuzh		创建该文件
// 20070828 hwp		CConfig修改为继承CParameterMap
/////////////////////////////////////////////////////////////////////////

#ifndef CCONFIG_H
#define CCONFIG_H

#include "platform.h"
#include "CBaseObject.h"

/////////////////////////////////////////////////////////////////////////
///CConfigItem是一个内部使用类，只被CConfig使用，用于存储某一个配置项的内容。一个
///配置项是指在配置文件中的类似xxx=xxx的一行
///@author	xuzh
///@version	1.0,20020214
/////////////////////////////////////////////////////////////////////////
class CConfigItem: public CBaseObject
{
public:
	///构造函数，用于创建一个配置项
	///@param	name	配置项名，此参数不可以为NULL
	///@param	value	配置项值，此参数可以为NULL，表示其值为空
	///说明：本函数将复制这两个字符串，呼叫方在返回后不必保留空间
	CConfigItem(char *name, char *value);
	
	///析构函数
	virtual ~CConfigItem(void);
	
	virtual int isA(char *objectType);
	virtual char *getType(void);
	virtual void output(CLogger *pLogger,int indent=0);
	
	///获取名称
	///@return	本配置项的名称
	char *getName(void);
	
	///获取值
	///@return	本配置项的值，如果当初设置时为NULL，则返回""
	char *getValue(void);
	
	///设置名称
	///@参数	name	名称
	void setName(char *name);
	
	///设置值
	///@参数	value	值
	void setValue(char *value);
private:
	///用于存储本配置项的名称
	char *name;
	
	///用于存储本配置项的值
	char *value;
};

/////////////////////////////////////////////////////////////////////////
///CConfig是一个只读的配置文件对象。这里的配置文件是一个类似Windows的INI文件的结构
///全部是xxx=xxx的形式，可以使用#表示注释，可以有空行
///@author	xuzh
///@version	1.0,20020214
/////////////////////////////////////////////////////////////////////////
class CConfig: public CBaseObject, public CParameterMap
{
public:
	///构造函数，用于读取指定的配置文件，构造内部的所有CConfigItem的一个
	///CCollection
	///@param	configFilename	要读取的配置文件名
	///@exception	CRuntimeError	在三种情况下，会给出此异常
	///			<ol>
	///			<li>无法打开此文件，错误信息:can not open config file
	///			<li>内存不够，错误信息:insufficient memory space
	///			<li>配置文件错误，错误信息:error in config file
	///			</ol>
	CConfig(const char *configFilename);
	
	///析构函数，将会释放items的内存
	virtual ~CConfig(void);
	
	virtual int isA(char *objectType);
	virtual char *getType(void);
	virtual void output(CLogger *pLogger,int indent=0);

	///获取指定名称在配置文件中对应的值
	///@param	name	配置项名称
	///@param	pStartId	指向起始的编号，如果为NULL，则表示从头开始，
	///			否则将从指定处+1开始，并且返回找到的编号+1。如果设为0，
	///			则表示从头开始，以后反复使用此函数，可以取出所有的同名配置
	///@return	此配置项的值，如果有多项，则只返回第一项，如果没有，则返回""
	virtual char *getConfig(char *name, int *pStartId=NULL);
private:

	///用于存储所有配置项的集合，其元素类型为CConfigItem
	vector<CConfigItem *> items;
};

///当前的配置信息
extern CConfig *currentConfig;

#endif
