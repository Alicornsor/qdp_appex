!!include function.tpl!!
!!enter system!!
/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file BaseDataStruct.h
///@brief定义了内存数据库用的基本数据结构类，以及iterator、trigger的基类
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef BASEDATASTRUCT_H
#define BASEDATASTRUCT_H

#include "platform.h"
#include "CBaseObject.h"
#include "customDataType.h"
#include "CTransaction.h"
#include "XtpData.h"

///判断结果是否满足条件
extern bool satisfy(int value,int type);

///字符串比较函数
///@param	s1	字符串1
///@param	s2	字符串2
///@return	1表示大于，0表示等于，-1表示小于
int compare(const char *s1, const char *s2);

///整数比较函数
///@param	v1	整数1
///@param	v2	整数2
///@return	1表示大于，0表示等于，-1表示小于
int compare(const int v1,const int v2);

///整数比较函数
///@param	v1	整数1
///@param	v2	整数2
///@return	1表示大于，0表示等于，-1表示小于
int compare(const long v1,const long v2);

///浮点数比较函数
///@param	v1	浮点数1
///@param	v2	浮点数2
///@return	1表示大于，0表示等于，-1表示小于
int compare(const double v1,const double v2);

///从buffer中获取下一个token，这里的token是以逗号或者换行分隔的
///在使用时，第一次应当传入指定的buffer，以后应当反复传入NULL，
///这样可以依次取出所有的token。本函数将改变buffer中的内容，叫用
///方有责任自己保护数据。本函数有重入问题，在一个取token的序列结
///束前，开始新的一个取token序列，将影响前面一个的结果。此问题和
///strtok的问题类似
///@param	buffer	要取token的buffer，NULL表示从上次取的buffer中取下一个
///@return	得到的token
char *getNextToken(char *buffer);

!!travel tables!!
class CWriteable!!@name!!;
!!if !strcmp(@hasTable,"yes")!!
class C!!@name!!Factory;
!!endif!!
!!next!!

!!travel tables!!
!!command resetEntityMap();!!
!!let tableName=@name!!
/////////////////////////////////////////////////////////////////////////
///CWriteable!!@name!!是一个存储!!@usage!!的对象，可以写出。
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
!!if !strcmp(@name,"PreOrder")!!
class CWriteable!!@name!! : public CInputOrderField
!!elseif  !strcmp(@name,"Order")!!
class CWriteable!!@name!! : public COrderField
!!elseif  !strcmp(@name,"Trade")!!
class CWriteable!!@name!! : public CTradeField
!!else!!
class CWriteable!!@name!!
!!endif!!
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
	int isValid(void) const
	{
		!!travel fields!!
		if (! !!@name!!.isValid())
			return 0;
		!!next!!
		return 1;
	}

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteable!!@name!! *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	!!if  strcmp(@name,"PreOrder") && strcmp(@name,"Order") && strcmp(@name,"Trade")!!
	!!travel fields!!
	!!if (!strcmp(@comment,"")==0)!!
	///!!@comment!!
	!!endif!! 
	!!@type!! !!@name!!;
	!!next!!
	!!endif!!
	
	!!if valid_name("hashkeys")!!
	!!travel hashkeys!!
	unsigned int Hash!!@name!!;
	
	///计算!!@name!!的hash值
	void calHash!!@name!!(void)
	{
		!!let hashName=@name!!
		unsigned key=0;
		!!travel self!!
		key=!!@name!!.hash(key);
		!!next!!
		Hash!!@name!!=key;
	}
	
	///根据需要情况，更新!!@name!!的hash值
	void updateHash!!@name!!(void)
	{
		!!if !strcmp(@stableHashKey,"no")!!
		calHash!!@name!!();
		!!endif!!
	}
	!!next!!
	!!endif!!
	
	///计算所有的hash值
	void calAllHash(void)
	{
		!!if valid_name("hashkeys")!!
		!!travel hashkeys!!
		calHash!!@name!!();
		!!next!!
		!!endif!!
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
		!!if valid_name("hashkeys")!!
		!!travel hashkeys!!
		updateHash!!@name!!();
		!!next!!
		!!endif!!
	}
	
	!!travel foreigns!!
	///构造!!@comment!!的指针
	///@param	pFactory	构造!!@comment!!的指针时，寻找的对象工厂
	///@return	找到的!!@comment!!的指针!!if (strcmp(@foreignStrick,"yes"))!!，如果找不到则返回NULL!!endif!!
	!!if (!strcmp(@foreignStrick,"yes"))!!
	///@exception	如果找不到，则抛出RUNTIME_ERROR
	!!endif!!
	inline const CWriteable!!@factory!! *link!!@name!!(C!!@factory!!Factory *pFactory) const;

	///构造!!@comment!!指针
	///@param	p!!@factory!!	要连接到的对象
	///@return	输入的p!!@factory!!
	const CWriteable!!@factory!! *link!!@name!!(const CWriteable!!@factory!! *p!!@factory!!) const
	{
		void *target=(void *)(&(this->p!!@name!!));
		*((const CWriteable!!@factory!! **)target)=p!!@factory!!;
		return p!!@factory!!;
	}
	
	///获取!!@comment!!的指针
	///@return	找到的!!@comment!!的指针!!if (strcmp(@foreignStrick,"yes"))!!，如果找不到则返回NULL!!endif!!
	!!if (!strcmp(@foreignStrick,"yes"))!!
	///@exception	如果找不到，则抛出RUNTIME_ERROR
	!!endif!!
	const CWriteable!!@factory!! *get!!@name!!(void) const
	{
		return p!!@name!!;
	}
	!!next!!

private:
	!!travel foreigns!!
	!!if (!strcmp(@comment,"")==0)!!
	///!!@comment!!
	!!endif!!
	const CWriteable!!@factory!! *p!!@name!!;
	!!next!!
};

typedef const CWriteable!!@name!! C!!@name!!;

!!if !strcmp(@hasTable,"yes")!!
/////////////////////////////////////////////////////////////////////////
///C!!@name!!ActionTrigger是操作!!@usage!!时的触发器
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@name!!ActionTrigger
{
public:
	///构造方法
	C!!@name!!ActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~C!!@name!!ActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(C!!@name!!Factory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	p!!@name!!	要加入的!!@name!!
	virtual void beforeAdd(CWriteable!!@name!! *p!!@name!!)
	{
		return;
	}
	
	///加入后触发
	///@param	p!!@name!!	已经加入的!!@name!!
	virtual void afterAdd(C!!@name!! *p!!@name!!)
	{
		return;
	}

	///更新前触发	
	///@param	p!!@name!!	被刷新的C!!@name!!
	///@param	pNew!!@name!!	新的值
	virtual void beforeUpdate(C!!@name!! *p!!@name!!, CWriteable!!@name!! *pNew!!@name!!)
	{
		return;
	}
	
	///更新后触发
	///@param	p!!@name!!	被刷新的C!!@name!!
	virtual void afterUpdate(C!!@name!! *p!!@name!!)
	{
		return;
	}
	
	///删除前触发
	///@param	p!!@name!!	要删除的C!!@name!!
	virtual void beforeRemove(C!!@name!! *p!!@name!!)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	C!!@name!!Factory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///C!!@name!!CommitTrigger是确认!!@usage!!时的触发器
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@name!!CommitTrigger
{
public:
	///构造方法
	C!!@name!!CommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~C!!@name!!CommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(C!!@name!!Factory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	p!!@name!!	已经加入的!!@name!!
	virtual void commitAdd(C!!@name!! *p!!@name!!)
	{
		return;
	}

	///更新后触发
	///@param	p!!@name!!	被刷新的C!!@name!!
	///@param	pold!!@name!!	原来的值
	virtual void commitUpdate(C!!@name!! *p!!@name!!, CWriteable!!@name!! *pOld!!@name!!)
	{
		return;
	}
	
	///删除后触发
	///@param	p!!@name!!	已经删除的C!!@name!!
	virtual void commitRemove(CWriteable!!@name!! *p!!@name!!)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	C!!@name!!Factory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///C!!@name!!Iterator是一个对!!@usage!!的枚举器接口
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@name!!Iterator
{
public:
	///构造方法
	C!!@name!!Iterator(void)
	{
	}

	///构造方法
	C!!@name!!Iterator(C!!@name!!Factory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~C!!@name!!Iterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个!!@name!!
	///@return	下一个满足条件C!!@name!!，如果已经没有一个满足要求了，则返回NULL
	virtual C!!@name!! *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	C!!@name!!Factory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	p!!@name!! 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteable!!@name!! * p!!@name!!,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	C!!@name!!Factory *m_Factory;	
};

!!endif!!
!!next!!

#include "databaseFactories.h"

!!travel tables!!
!!command resetEntityMap();!!
!!let tableName=@name!!
!!travel foreigns!!
const CWriteable!!@factory!! *CWriteable!!@tableName!!::link!!@name!!(C!!@factory!!Factory *pFactory) const
{
	void *target=(void *)(&p!!@name!!);
	*((const CWriteable!!@factory!! **)target)=pFactory->find!!@method!!(!!@key!!);
	!!if !strcmp(@foreignStrick,"yes")!!
	if (p!!@name!!==NULL)
	{
		RAISE_RUNTIME_ERROR("can not link !!@name!! in !!@tableName!!");
	}
	!!endif!!
	return p!!@name!!;
}

!!next!!
!!next!!
#endif


!!leave!!
