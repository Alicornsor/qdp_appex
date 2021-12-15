/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CBaseObject.h
///@brief定义抽象的对象基类CBaseObject，让各个应用对象继承
///@history 
///20020212	xuzh		创建该文件
///20020214	xuzh		修改此文件，使checkType包含了文件名和行号
// 20070828 hwp		加入monitorIndex头文件
/////////////////////////////////////////////////////////////////////////

#ifndef CBASEOBJECT_H
#define CBASEOBJECT_H

#include "platform.h"
#include "DesignError.h"
#include "RuntimeError.h"

class CLogger;

/////////////////////////////////////////////////////////////////////////
///CBaseObject是所有应用对象的基类。这个类定义了一个对象基本的操作，同时
///给出了相应的检查的方法。CBaseObject是一个纯虚类，不能被实例化。
///@author	xuzh
///@version	1.0,20020214
/////////////////////////////////////////////////////////////////////////
class CBaseObject
{
public:
	///构造函数
	///	没有实质性的工作
	CBaseObject(void);

	///析构函数
	///	没有实质性的工作
	virtual ~CBaseObject(void);

	///判断一个对象的类型是否就是指定的对象类型。该函数是一个虚函数，各个继承
	///类需要重新定义这个函数。在检查对象类型时，即使objectType符合本对象的
	///某个祖先类，也认为是正确的，因为作为继承类，它也是祖先类的一种。
	///@param	objectType	要检查是否符合的类名，一般是以字符串形式出现
	///			的类名
	///@return	如果符合返回1，否则返回0
	///	在CBaseObject的继承类中，一般实现该函数的方法如下所示：
	///	<pre>
	///	if (!strcmp(objectType,"本类名"))
	///		return 1;
	///	return 父类一::isA(objectType)||父类二::isA(objectType);
	///	</pre>
	virtual int isA(char *objectType);

	///将本对象进行输出，主要用于调试。该函数是一个虚函数，各个继承类
	///需要重新定义该函数。
	///@param	pLogger	进行输出的
	///@param	indent	缩进量
	virtual void output(CLogger *pLogger,int indent=0)=0;

	///返回标示本对象类型的字符串，一般就是本对象的类名。该函数是一个虚函数，
	///各个继承类需要重新定义该函数。
	///@return	标示本对象类型的字符串
	virtual char *getType(void);
	
	///检查本对象是否是指定的对象类型，如果是则返回，否则将产生一个CDesignError
	///本函数主要用于在系统调试时检查内存错误。
	///@param	objectType	指定的对象类型
	///@param	filename	报错时指定的文件名
	///@param	line		报错时指定的行号
	///@exception	CDesignError	当不符合时，将会抛出此异常
	void checkType(char *objectType, char *filename, int line);
private:
};

#include "monitorIndex.h"

///检查本对象是否符合指定类型，如果是则返回，否则将产生一个CDesignError
///本宏必须使用在CBaseObject的一个继承类中
///@param	type	char*	指定的对象类型
///@exception	CDesignError	当不符合时，将会抛出此异常，错误位置在当前文件当前行
#define CHECK_TYPE(type) checkType(type,__FILE__,__LINE__)

///抛出一个CDesignError异常
///@param	msg	char*	指定的错误信息
///@exception	CDesignError	抛出此异常，错误位置在当前文件当前行
//#define RAISE_DESIGN_ERROR(msg) {throw new CDesignError(msg,__FILE__,__LINE__);}
#define RAISE_DESIGN_ERROR(msg) {												\
		printf("DesignError:%s in line %d of file %s\n",msg,__LINE__,__FILE__);	\
		fflush(stdout);															\
		char *__pNull = NULL; *__pNull = 0;										\
	}

///抛出一个CRuntimeError
///@param	msg	char*	指定的错误信息
///@exception	CRuntimeError	抛出此异常，错误位置在当前文件当前行
//#define RAISE_RUNTIME_ERROR(msg) {throw new CRuntimeError(msg,__FILE__,__LINE__);}
#define RAISE_RUNTIME_ERROR(msg) {												\
		printf("RuntimeError:%s in line %d of file %s\n",msg,__LINE__,__FILE__);\
		fflush(stdout);															\
		char *__pNull = NULL; *__pNull = 0;										\
	}

///运行级别，运行级别越高，运行的内容越多
extern int runLevel;

#endif
