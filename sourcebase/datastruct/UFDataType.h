/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file UFDataType.h
///@brief定义了交易所内部数据的底层支持类
///@history 
///20020214	xuzh		创建该文件
///20020309	xuzh		修改此文件，支持各个ReadOnly的类
///20020330 xuzh		在每个基本类型中加上getString(char *)的方法
///20020410 xuzh		在每个基本类型中加上isNull的方法
///20020410 xuzh		在有约束值的类中加上isVilid()方法
///20060218	xuzh		彻底修改了结构，使所有的ReadOnly类型就是const类型
/////////////////////////////////////////////////////////////////////////

#ifndef UFDATATYPE_H
#define UFDATATYPE_H

#include "CBaseObject.h"
#include "utility.h"

class CUFBaseStringType
{
};

class CUFBaseIntType
{
};

class CUFBaseLongType
{
};

class CUFBaseFloatType
{
};

class CUFBaseCharType
{
};

class CUFBaseWordType
{
};

///定义一个很小的浮点数，这个数应当不影响计算结果，又大于各类浮点计算误差
#define SMALL_DOUBLE 0.000000001

/////////////////////////////////////////////////////////////////////////
///CUFStringType<int length>是一个数据字符串模版类，通过指定长度，
///可以得到真正可以使用的类。CUFStringType<int length>实质上就是根据长度，
///直接保存字符串的值，左对齐，最后加'\0'。
///@author	xuzh
///@version	2.0,20060218
/////////////////////////////////////////////////////////////////////////
template <int length> class CUFStringType: public CUFBaseStringType
{
public:
	///构造函数
	CUFStringType(void)
	{
		//buffer[0] = '\0';
		///add by wangwei, 20121229
		clear();
	}

	///复制构造子
	///@param	s	构造的源对象
	CUFStringType(const CUFStringType<length>& s)
	{
		setValue(s.getValue());
	}

	///复制构造子
	///@param	p	构造的源对象
	CUFStringType(const char *p)
	{
		setValue(p);
	}

	///等于操作符
	///@param	s	等于的值
	///@return	输入的值
	const CUFStringType & operator =(const CUFStringType<length>& s)
	{
		setValue(s.getValue());
		return s;
	}

	///等于操作符，从字符串中获取
	///@param	p	等于的字符串
	///@return	输入的字符串
	const char * operator =(const char *p)
	{
		setValue(p);
		return p;
	}

	///等于操作符，从整数中获取
	///@param	v	等于的整数
	///@return	输入的整数
	const int operator =(const int v)
	{
		char tmp[100];
		sprintf(tmp,"%*d",length,v);
		setValue(tmp);
		return v;
	}
	
	///等于操作符，从64位长整数中获取     liumeng 20140820
	///@param	v	等于的长整数
	///@return	输入的长整数
	const long operator =(const long v)
	{
		char tmp[100];
		sprintf(tmp,"%*ld",length,v);
		setValue(tmp);
		return v;
	}

	///清除字符串内容
	void clear(void)
	{
		buffer[0]='\0';
	}

	///获取字符串的值
	///@return	字符串的值
	const char *getValue(void) const
	{
		return buffer;
	}

	///设置字符串的值
	///@param	s	要设置的字符串
	void setValue(const char *s)
	{
		if (s==NULL)
			buffer[0]='\0';
		else
		{
			strncpy(buffer,s,length);
			buffer[length]='\0';
		}
	}

	///在strBuf中得到本类型的字符串表示	
	///@param	strBuf	用于放置结果的字符串
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			memcpy(strBuf, buffer,length);
			strBuf[length]='\0';
		}	
	}

	///判断是否为空
	///@return	true表示为空，false表示不为空
	bool isNull(void) const
	{
		const char *p=buffer;
		while (*p)
		{
			if (*p!=' ')
			{
				return false;
			}
			p++;
		}
		return true;
	}

	///判断是否合法
	///@return	true表示合法，false表示不合法
	bool isValid(void) const
	{
		return true;
	}

	///转化为字符串
	///@return	得到的字符串
	operator const char *(void) const
	{
		return buffer;
	}

	///将右边的空格删除
	void trimRight(void)
	{
		char *p = buffer+strlen(buffer)-1;
		while (p >= buffer)
		{
			if (*p != ' ')
			{
				break;
			}
			*p = '\0';
			p--;
		}
	}

	///判断是否小于某个字符串
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator < (const char *r) const
	{
		return strcmp(buffer,r)<0;
	}

	///判断是否大于某个字符串
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator > (const char *r) const
	{
		return strcmp(buffer, r)>0;
	}

	///判断是否小于等于某个字符串
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator <= (const char *r) const
	{
		return strcmp(buffer,r)<=0;
	}

	///判断是否大于等于某个字符串
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator >= (const char *r) const
	{
		return strcmp(buffer, r)>=0;
	}

	///判断是否等于某个字符串
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator == (const char *r) const
	{
		return strcmp(buffer, r)==0;
	}

	///判断是否不等于某个字符串
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator != (const char *r) const
	{
		return strcmp(buffer, r)!=0;
	}
	
	///产生hash值
	///@param	seed	种子
	///@return	得到的hash值
	unsigned int hash(unsigned int seed) const
	{
		unsigned long ret=seed;
		const char *str=buffer;
		
		if (*str == '\0')
		{
			return(ret);
		}
		long n = 0x100;
		while (*str)
		{
			unsigned long v = n|(*str);
			n += 0x100;
			int r = (int)((v>>2)^v)&0x0f;
			ret = (ret<<r)|(ret>>(32-r));
			ret &= 0xFFFFFFFFL;
			ret ^= v*v;
			str++;
		}
		return ((ret>>16)^ret);
	}


protected:
	///存储字符串的值
	char buffer[length+1];
};

#define DefineStringType(length,newType)				\
	typedef CUFStringType<length> C ## newType;			\
	typedef const CUFStringType<length> CReadOnly ## newType;

/////////////////////////////////////////////////////////////////////////
///CUFFloatType是一个内部数据的浮点数类
///@author	xuzh
///@version	2.0,20060218
/////////////////////////////////////////////////////////////////////////
///xuzh，20070328
///增加了对浮点数范围的判定，防止出现超越范围的数据
template <int length, int precision> class CUFFloatType: public CUFBaseFloatType
{
public:
	///构造函数
	CUFFloatType(void)
	{
		//clear();
		///add by wangwei, 20121229
		clear();		
	}

	///复制构造子
	///@param	f	构造的源对象
	CUFFloatType(const CUFFloatType& f)
	{
		setValue(f.getValue());
	}

	///复制构造子
	///@param	value	构造的源对象
	CUFFloatType(const double value)
	{
		setValue(value);
	}

	///等于操作符
	///@param	f	等于的值
	///@return	输入的值
	const CUFFloatType & operator =(const CUFFloatType& f)
	{
		setValue(f.getValue());
		return f;
	}

	///等于操作符，从浮点数中获取
	///@param	v	等于的浮点数
	///@return	输入的字浮点数
	const double operator =(const double value)
	{
		setValue(value);
		return value;
	}

	///等于操作符，从字符串中获取
	///@param	v	等于的字符串
	///@return	输入的字符串
	const char * operator = (const char *v)
	{
		if (v[0]=='\0')
		{
			setValue(DOUBLE_NaN);
		}
		else
		{
			setValue((double)atof(v));
		}
		return v;
	}

	///清除内容，就是将值设为0
	void clear(void)
	{
		value=0.0;
	}

	///获取值
	///@return	获取的值
	const double getValue(void) const
	{
		return value;
	}

	///设置值
	///@param	v	要设置的值
	void setValue(const double v)
	{
		if ((v<SMALL_DOUBLE)&&(v>-SMALL_DOUBLE))
		{
			///这样是为了防止出现-0.00000的情况。对于某些浮点计算器，在计算例如-31.0+31.0时，得到的结果是-0.0，而非0.0
			value=0.0;
		}
		else
		{
			value=v;
		}
	}

	///在strBuf中得到本类型的字符串表示	
	///@param	strBuf	用于放置结果的字符串
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			if (value==DOUBLE_NaN)
			{
				strcpy(strBuf,"");
			}
			else
			{
				sprintf(strBuf,"%.6f", value);
			}
		}	
	}	

	///判断是否为空
	///@return	true表示为空，false表示不为空
	bool isNull(void) const
	{
		if (value==DOUBLE_NaN)
			return true;
		else
			return false;
	}

	///判断是否合法
	///@return	true表示合法，false表示不合法
	bool isValid(void) const
	{
		if (isnan(value))
       return false;
		if (value==DOUBLE_NaN)
			return true;
			
		else if (value>=pow(10,length-precision-1))
			return false;
		else if (value<=-pow(10,length-precision-2))
			return false;
		return true;
	}

	///转化为实数
	///@return	得到的实数
	operator const double (void) const
	{
		return value;
	}
	
	///加上某个值
	///@param	v	要加的值
	///@return	运算以后的结果
	const double operator += (const double v)
	{
		setValue(value+v);
		return v;
	}

	///减去某个值
	///@param	v	要减的值
	///@return	运算以后的结果
	const double operator -= (double v)
	{
		setValue(value-v);
		return v;
	}

	///乘上某个值
	///@param	v	要乘的值
	///@return	运算以后的结果
	const double operator *= (const double v)
	{
		setValue(value*v);
		return v;
	}

	///除以某个值
	///@param	v	要除的值
	///@return	运算以后的结果
	const double operator /= (const double v)
	{
		setValue(value/v);
		return v;
	}
	
	///整除某个值
	///@param	v	要除的值
	///@return	运算以后的结果
	const int operator &(const double v) const
	{
		//******//
		//	xuzh,200609028：修正了当value/v的结果为负值时的错误
		//******//
		return (int)(floor(value/v+SMALL_DOUBLE));
	}

	///判断是否小于某个值
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator < (double r) const
	{
		return value < r-SMALL_DOUBLE;
	}

	///判断是否大于某个值
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator > (double r) const
	{
		return value > r+SMALL_DOUBLE;
	}

	///判断是否小于等于某个值
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator <= (double r) const
	{
		return value <= r+SMALL_DOUBLE;
	}

	///判断是否大于等于某个值
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator >= (double r) const
	{
		return value >= r-SMALL_DOUBLE;
	}

	///判断是否等于某个值
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator == (double r) const
	{
		return fabs(value-r)<=SMALL_DOUBLE;
	}

	///判断是否不等于某个值
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator != (double r) const
	{
		return fabs(value-r)>SMALL_DOUBLE;
	}

	///判断是否小于某个值
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator < (int r) const
	{
		return value < r-SMALL_DOUBLE;
	}

	///判断是否大于某个值
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator > (int r) const
	{
		return value > r+SMALL_DOUBLE;
	}

	///判断是否小于等于某个值
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator <= (int r) const
	{
		return value <= r+SMALL_DOUBLE;
	}

	///判断是否大于等于某个值
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator >= (int r) const
	{
		return value >= r-SMALL_DOUBLE;
	}

	///判断是否等于某个值
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator == (int r) const
	{
		return fabs(value-r)<=SMALL_DOUBLE;
	}

	///判断是否不等于某个值
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator != (int r) const
	{
		return fabs(value-r)>SMALL_DOUBLE;
	}

	///产生hash值
	///@param	seed	种子
	///@return	得到的hash值
	unsigned int hash(unsigned int seed) const
	{
		unsigned long ret=seed;
		const char *str=(char *)&value;
		int i;
		
		long n = 0x100;
		for (i=0;i<sizeof(double);i++)
		{
			unsigned long v = n|(*str);
			n += 0x100;
			int r = (int)((v>>2)^v)&0x0f;
			ret = (ret<<r)|(ret>>(32-r));
			ret &= 0xFFFFFFFFL;
			ret ^= v*v;
			str++;
		}
		return ((ret>>16)^ret);
	}

protected:
	///存储浮点数的值
	double value;
};

#define DefineFloatType(maxValue,minValue,newType)			\
	typedef CUFFloatType<maxValue,minValue> C ## newType;	\
	typedef const CUFFloatType<maxValue,minValue> CReadOnly ## newType;

/////////////////////////////////////////////////////////////////////////
///CUFIntType是一个内部数据的整数类
///@author	xuzh
///@version	2.0,20060218
/////////////////////////////////////////////////////////////////////////
class CUFIntType: public CUFBaseIntType
{
public:
	///构造函数
	CUFIntType(void)
	{
		//clear();
		///add by wangwei, 20121229
		clear();
	}

	///复制构造子
	///@param	i	构造的源对象
	CUFIntType(const CUFIntType& i)
	{
		setValue(i.getValue());
	}

	///复制构造子
	///@param	i	构造的源对象
	CUFIntType(const int i)
	{
		setValue(i);
	}

	///等于操作符
	///@param	i	等于的值
	///@return	输入的值
	const CUFIntType & operator =(const CUFIntType& i)
	{
		setValue(i.getValue());
		return i;
	}

	///等于操作符，从整数中获取
	///@param	i	等于的整数
	///@return	输入的整数
	const int operator =(const int i)
	{
		setValue(i);
		return i;
	}

	///等于操作符，从字符串中获取
	///@param	v	等于的字符串
	///@return	输入的字符串
	const char * operator =(const char *v)
	{
		setValue(atoi(v));
		return v;
	}

	///清除内容，就是将值设为0
	void clear(void)
	{
		value=0;
	}
	
	///获取值
	///@return	获取的值
	const int getValue(void) const
	{
		return value;
	}

	///设置值
	///@param	v	要设置的值
	void setValue(const int v)
	{
		value=v;
	}

	///在strBuf中得到本类型的字符串表示	
	///@param	strBuf	用于放置结果的字符串
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			sprintf(strBuf,"%d", value);
		}	
	}	

	///判断是否为空
	///@return	true表示为空，false表示不为空
	bool isNull(void) const
	{
		return false;
	}

	///判断是否合法
	///@return	true表示合法，false表示不合法
	bool isValid(void) const
	{
		return true;
	}

	///转化为整数
	///@return	得到的整数
	operator const int (void) const
	{
		return value;
	}

	///本对象加上某个值
	///@param	v	要加的值
	///@return	得到的值
	const int operator += (const int v)
	{
		setValue(value+v);
		return value;
	}
	
	///本对象减去某个值
	///@param	v	要减的值
	///@return	得到的值
	const int operator -= (const int v)
	{
		setValue(value-v);
		return value;
	}

	///本对象乘以某个值
	///@param	v	要乘的值
	///@return	得到的值
	const int operator *= (const int v)
	{
		setValue(value*v);
		return value;
	}

	///本对象除以某个值
	///@param	v	要除的值
	///@return	得到的值
	const int operator /= (const int v)
	{
		setValue(value/v);
		return value;
	}

	///本对象模某个值
	///@param	v	要模的值
	///@return	得到的值
	const int operator %= (const int v)
	{
		setValue(value%v);
		return value;
	}

	///产生hash值
	///@param	seed	种子
	///@return	得到的hash值
	unsigned int hash(unsigned int seed) const
	{
		unsigned long ret=seed;
		unsigned  long v = 0x100 | value;
		int r = (int)((v>>2)^v)&0x0f;
		ret = (ret<<r)|(ret>>(32-r));
		ret &= 0xFFFFFFFFL;
		ret ^= v*v;
		return ((ret>>16)^ret);
	}

protected:
	///存储整数的值
	int value;
};

typedef const CUFIntType CReadOnlyUFIntType;

/////////////////////////////////////////////////////////////////////////
///CUFLongType是一个内部数据的长整数类
///@author	longqy
///@version	2.1,20130115
/////////////////////////////////////////////////////////////////////////
class CUFLongType: public CUFBaseLongType
{
public:
	///构造函数
	CUFLongType(void)
	{
		//clear();
		///add by wangwei, 20121229
		clear();
	}

	///复制构造子
	///@param	i	构造的源对象
	CUFLongType(const CUFLongType& i)
	{
		setValue(i.getValue());
	}

	///复制构造子
	///@param	i	构造的源对象
	CUFLongType(const long i)
	{
		setValue(i);
	}

	///等于操作符
	///@param	i	等于的值
	///@return	输入的值
	const CUFLongType & operator =(const CUFLongType& i)
	{
		setValue(i.getValue());
		return i;
	}

	///等于操作符，从整数中获取
	///@param	i	等于的整数
	///@return	输入的整数
	const long operator =(const long i)
	{
		setValue(i);
		return i;
	}

	///等于操作符，从字符串中获取
	///@param	v	等于的字符串
	///@return	输入的字符串
	const char * operator =(const char *v)
	{
		setValue(atol(v));
		return v;
	}

	///清除内容，就是将值设为0
	void clear(void)
	{
		value=0;
	}
	
	///获取值
	///@return	获取的值
	const long getValue(void) const
	{
		return value;
	}

	///设置值
	///@param	v	要设置的值
	void setValue(const long v)
	{
		value=v;
	}

	///在strBuf中得到本类型的字符串表示	
	///@param	strBuf	用于放置结果的字符串
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			sprintf(strBuf,"%ld", value);
		}	
	}	

	///判断是否为空
	///@return	true表示为空，false表示不为空
	bool isNull(void) const
	{
		return false;
	}

	///判断是否合法
	///@return	true表示合法，false表示不合法
	bool isValid(void) const
	{
		return true;
	}

	///转化为整数
	///@return	得到的整数
	operator const long (void) const
	{
		return value;
	}

	///本对象加上某个值
	///@param	v	要加的值
	///@return	得到的值
	const long operator += (const long v)
	{
		setValue(value+v);
		return value;
	}
	
	///本对象减去某个值
	///@param	v	要减的值
	///@return	得到的值
	const long operator -= (const long v)
	{
		setValue(value-v);
		return value;
	}

	///本对象乘以某个值
	///@param	v	要乘的值
	///@return	得到的值
	const long operator *= (const long v)
	{
		setValue(value*v);
		return value;
	}

	///本对象除以某个值
	///@param	v	要除的值
	///@return	得到的值
	const long operator /= (const long v)
	{
		setValue(value/v);
		return value;
	}

	///本对象模某个值
	///@param	v	要模的值
	///@return	得到的值
	const long operator %= (const long v)
	{
		setValue(value%v);
		return value;
	}

	///产生hash值
	///@param	seed	种子
	///@return	得到的hash值
	unsigned long hash(unsigned long seed) const
	{
		unsigned long ret=seed;
		unsigned  long v = 0x100 | value;
		long r = (long)((v>>2)^v)&0x0f;
		ret = (ret<<r)|(ret>>(32-r));
		ret &= 0xFFFFFFFFL;
		ret ^= v*v;
		return ((ret>>16)^ret);
	}

protected:
	///存储整数的值
	long value;
};

typedef const CUFLongType CReadOnlyUFLongType;


/////////////////////////////////////////////////////////////////////////
///CUFRangeIntType<int from,int to>是一个内部数据有范围限定的整数
///模版类，通过指定范围，可以得到真正可以使用的类。CUFRangeIntType<int 
///from, int to>实质上就是存储一个整数，但是在设置值时将做检测
///@author	xuzh
///@version	2.0,20060218
/////////////////////////////////////////////////////////////////////////
template <int from, int to> class CUFRangeIntType: public CUFBaseIntType
{
public:
	///构造函数
	CUFRangeIntType(void)
	{
		//clear();
		///add by wangwei, 20121229
		clear();	
	}

	///复制构造子
	///@param	i	构造的源对象
	CUFRangeIntType(const CUFRangeIntType<from,to>& i)
	{
		setValue(i.getValue());
	}

	///复制构造子
	///@param	i	构造的源对象
	CUFRangeIntType(const int i)
	{
		setValue(i);
	}

	///等于操作符
	///@param	i	等于的值
	///@return	输入的值
	const CUFRangeIntType<from,to> & operator =(const CUFRangeIntType<from,to>& i)
	{
		setValue(i.getValue());
		return i;
	}

	///等于操作符，从整数中获取
	///@param	i	等于的整数
	///@return	输入的整数
	const int operator =(const int i)
	{
		setValue(i);
		return i;
	}

	///等于操作符，从字符串中获取
	///@param	v	等于的字符串
	///@return	输入的字符串
	const char * operator =(const char *v)
	{
		setValue(atoi(v));
		return v;
	}

	///清除内容，就是将值设为from
	void clear(void)
	{
		value=from;
	}

	///获取值
	///@return	获取的值
	const int getValue(void) const
	{
		return value;
	}

	///设置值
	///@param	v	要设置的值
	///@exception	CRuntimeError	发现数值越界，则抛出此异常
	void setValue(const int v)
	{
		/*
		if ((v>to)||(v<from))
		{
			RAISE_RUNTIME_WARNING("out of range");
		}
		*/
		value=v;
	}

	///在strBuf中得到本类型的字符串表示	
	///@param	strBuf	用于放置结果的字符串
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			sprintf(strBuf,"%d", value);
		}	
	}

	///判断是否为空
	///@return	true表示为空，false表示不为空
	bool isNull(void) const
	{
		return false;
	}

	///判断是否合法
	///@return	true表示合法，false表示不合法
	bool isValid(void) const
	{
		if ((value>to)||(value<from))
			return false;
		else
			return true;
	}

	///转化为整数
	///@return	得到的整数
	operator const int (void) const
	{
		return value;
	}

	///本对象加上某个值
	///@param	v	要加的值
	///@return	得到的值
	const int operator += (const int v)
	{
		setValue(value+v);
		return value;
	}
	
	///本对象减去某个值
	///@param	v	要减的值
	///@return	得到的值
	const int operator -= (const int v)
	{
		setValue(value-v);
		return value;
	}

	///本对象乘以某个值
	///@param	v	要乘的值
	///@return	得到的值
	const int operator *= (const int v)
	{
		setValue(value*v);
		return value;
	}

	///本对象除以某个值
	///@param	v	要除的值
	///@return	得到的值
	const int operator /= (const int v)
	{
		setValue(value/v);
		return value;
	}

	///本对象模某个值
	///@param	v	要模的值
	///@return	得到的值
	const int operator %= (const int v)
	{
		setValue(value%v);
		return value;
	}

	///产生hash值
	///@param	seed	种子
	///@return	得到的hash值
	unsigned int hash(unsigned int seed) const
	{
		unsigned long ret=seed;
		unsigned  long v = 0x100 | value;
		int r = (int)((v>>2)^v)&0x0f;
		ret = (ret<<r)|(ret>>(32-r));
		ret &= 0xFFFFFFFFL;
		ret ^= v*v;
		return ((ret>>16)^ret);
	}
protected:
	///存储整数的值
	int value;
};

#define DefineRangeIntType(from,to,newType)					\
	typedef CUFRangeIntType<from,to> C ## newType;			\
	typedef const CUFRangeIntType<from,to> CReadOnly ## newType;

/////////////////////////////////////////////////////////////////////////
///CUFCharType是一个内部数据的字符类
///@author	xuzh
///@version	2.0,20060218
/////////////////////////////////////////////////////////////////////////
class CUFCharType: public CUFBaseCharType
{
public:
	///构造函数
	CUFCharType(void)
	{
		//clear();
		///add by wangwei, 20121229
		clear();		
	}

	///复制构造子
	///@param	c	构造的源对象
	CUFCharType(const CUFCharType& c)
	{
		setValue(c.getValue());
	}

	///复制构造子
	///@param	c	构造的源对象
	CUFCharType(const char c)
	{
		setValue(c);
	}

	///等于操作符
	///@param	c	等于的值
	///@return	输入的值
	const CUFCharType & operator =(const CUFCharType& c)
	{
		setValue(c.getValue());
		return c;
	}

	///等于操作符，从字符中获取
	///@param	c	等于的字符
	///@return	输入的字符
	const char operator =(const char c)
	{
		setValue(c);
		return c;
	}

	///等于操作符，从字符串中获取
	///@param	v	等于的字符串
	///@return	输入的字符串
	const char * operator =(const char *v)
	{
		setValue(*v);
		return v;
	}

	///清除内容，就是将值设为'\0'
	void clear(void)
	{
		value='\0';
	}
	
	///获取值
	///@return	获取的值
	char getValue(void) const
	{
		return value;
	}

	///设置值
	///@param	v	要设置的值
	void setValue(const char v)
	{
		value=v;
	}

	///在strBuf中得到本类型的字符串表示	
	///@param	strBuf	用于放置结果的字符串
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			sprintf(strBuf,"%c", value);
		}	
	}	

	///判断是否为空
	///@return	true表示为空，false表示不为空
	bool isNull(void) const
	{
		return false;
	}

	///判断是否合法
	///@return	true表示合法，false表示不合法
	bool isValid(void) const
	{
		return true;
	}

	///转化为字符
	///@return	得到的字符
	operator const char (void) const
	{
		return value;
	}

	///产生hash值
	///@param	seed	种子
	///@return	得到的hash值
	unsigned int hash(unsigned int seed) const
	{
		unsigned long ret=seed;
		unsigned  long v = 0x100 | value;
		int r = (int)((v>>2)^v)&0x0f;
		ret = (ret<<r)|(ret>>(32-r));
		ret &= 0xFFFFFFFFL;
		ret ^= v*v;
		return ((ret>>16)^ret);
	}
protected:
	///存储字符的值
	char value;
};

typedef const CUFCharType CReadOnlyUFCharType;

#define EnumNull ' '

///用于定义一个带有检查的字符类型
///@param	typename	要定义的类型
///@param	validString	所有允许取值的字符构成的字符串
#define DefineEnumCharType(typename,validString)				\
	class C ## typename: public CUFCharType						\
	{															\
	public:														\
		C ## typename(void)										\
		{														\
		}														\
		C ## typename(const C ## typename &v)					\
		{														\
			setValue(v.getValue());								\
		}														\
		C ## typename(const char v)								\
		{														\
			setValue(v);										\
		}														\
		C ## typename(const CUFCharType &v)						\
		{														\
			setValue(v.getValue());								\
		}														\
		C ## typename& operator=(const C ## typename &c)		\
		{														\
			setValue(c.getValue());								\
			return *this;										\
		}														\
		C ## typename& operator=(const CUFCharType &c)			\
		{														\
			setValue(c.getValue());								\
			return *this;										\
		}														\
		const char operator =(const char c)						\
		{														\
			setValue(c);										\
			return c;											\
		}														\
		const char * operator =(const char *v)					\
		{														\
			setValue(*v);										\
			return v;											\
		}														\
		void clear(void)										\
		{														\
			setValue(validString[0]);							\
		}														\
		void setValue(const char v)								\
		{														\
/*			if ((v!=EnumNull)&&!strchr(validString,v))			\
			{													\
				RAISE_RUNTIME_WARNING("out of enum char range");\
			}													\
*/			value=v;											\
		} 														\
		bool isNull(void) const									\
		{														\
			return value==EnumNull;								\
		}														\
		bool isValid(void) const								\
		{														\
			if (value=='\0')									\
				return false;									\
			if (strchr(validString,value))						\
				return true;									\
			else												\
				return false;									\
		} 														\
		static bool isValid(const char ch)						\
		{														\
			if (strchr(validString,ch))							\
				return true;									\
			else												\
				return false;									\
		}														\
	};															\
	typedef const C ## typename CReadOnly ## typename;			\

/////////////////////////////////////////////////////////////////////////
///CUFWordType是一个内部数据的字符类
///@author	xuzh
///@version	2.0,20060218
/////////////////////////////////////////////////////////////////////////
class CUFWordType : public CUFBaseWordType
{
public:
	///构造函数
	CUFWordType(void)
	{
//		clear();
///add by wangwei, 20121229
		clear();
	}

	///复制构造子
	///@param	w	构造的源对象
	CUFWordType(const CUFWordType& w)
	{
		setValue(w.getValue());
	}

	///复制构造子
	///@param	w	构造的源对象
	CUFWordType(WORD w)
	{
		setValue(w);
	}
	
	///等于操作符
	///@param	w	等于的值
	///@return	输入的值
	const CUFWordType & operator =(const CUFWordType& w)
	{
		setValue(w.getValue());
		return w;
	}

	///等于操作符，从字中获取
	///@param	w	等于的字
	///@return	输入的字
	const WORD operator =(const WORD w)
	{
		setValue(w);
		return w;
	}

	///等于操作符，从字符串中获取
	///@param	v	等于的字符串
	///@return	输入的字符串
	const char * operator =(const char *v)
	{
		setValue(atoi(v));
		return v;
	}

	///清除内容，就是将值设为0
	void clear(void)
	{
		value=0;
	}

	///获取值
	///@return	获取的值
	WORD getValue(void) const
	{
		return value;
	}

	///设置值
	///@param	v	要设置的值
	void setValue(WORD v)
	{
		value=v;
	}

	///在strBuf中得到本类型的字符串表示	
	///@param	strBuf	用于放置结果的字符串
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			sprintf(strBuf,"%d", value);
		}	
	}	

	///判断是否为空
	///@return	true表示为空，false表示不为空
	bool isNull(void) const
	{
		return false;
	}

	///判断是否合法
	///@return	true表示合法，false表示不合法
	bool isValid(void) const
	{
		return true;
	}

	///转化为字
	///@return	得到的字
	operator const WORD (void)
	{
		return value;
	}

	///产生hash值
	///@param	seed	种子
	///@return	得到的hash值
	unsigned int hash(unsigned int seed) const
	{
		unsigned long ret=seed;
		unsigned  long v = 0x100 | value;
		int r = (int)((v>>2)^v)&0x0f;
		ret = (ret<<r)|(ret>>(32-r));
		ret &= 0xFFFFFFFFL;
		ret ^= v*v;
		return ((ret>>16)^ret);
	}
protected:
	///存储字符的值
	WORD value;
};

typedef const CUFWordType CReadOnlyUFWordType;


#define DefineUFType(pureType, newType)			\
	typedef C ## pureType C ## newType;			\
	typedef CReadOnly ## pureType CReadOnly ## newType;	\
/*
template<int length,int precision> class CFixNumberType;

template <int length, int precision> 
class CReadOnlyFixNumberType
{
protected:
	CReadOnlyFixNumberType(const CReadOnlyFixNumberType<length,precision>& );
	CReadOnlyFixNumberType<length,precision>& operator=(const CReadOnlyFixNumberType<length,precision>&);
public:
	CReadOnlyFixNumberType(void)
	{
	}
	double getValue(void)
	{
		return atof(value);
	}
	///在strBuf中得到本类型的字符串表示	
	void getString(char *strBuf)
	{
		strcpy(value);
	}	
	int isNull(void)
	{
		if (value[0]=='\0')
			return true;
		else
			return false;
	}
	int isValid(void)
	{
		return 1;
	}
	operator double (void)
	{
		return getValue();
	}
	operator int (void)
	{
		return getValue();
	}
	operator char *(void)
	{
		return getValue();
	}
	CFixNumberType<length,precision> operator + (CReadOnlyFixNumberType<length,precision> &v)
	{
	}
	CFixNumberType<length,precision> operator + (int v)
	{
	}
	CFixNumberType<length,precision> operator + (double v)
	{
	}
	CFixNumberType<length,precision> operator + (char *v)
	{
	}
protected:
	char value[length+1];
};

template<int length,int precision>
class CFixNumberType: public CReadOnlyFixNumberType<length,precision>
{
public:
	CFixNumberType(const CFixNumberType<length,precision>& f)
	{
		strcpy(value,f.value);
	}
	CFixNumberType<length,precision>& operator=(const CFixNumberType<length,precision>& f)
	{
		strcpy(value,f.value);
		return *this;
	}
	CFixNumberType<length,precision>& operator=(double f)
	{
	}
	CFixNumberType<length,precision>& operator=(int f)
	{
	}
	CFixNumberType<length,precision>& operator=(char *f)
	{
	}

	CFixNumberType()
	{
		clear();
	}

	///清除内容，就是将值设为0
	void clear(void)
	{
		value[0]='\0';
	}

	///设置值
	///@param	v	要设置的值
	void setValue(char *v)
	{
	}

	///设置值
	///@param	v	要设置的值
	void setValue(int v)
	{
	}

	///设置值
	///@param	v	要设置的值
	void setValue(double v)
	{
	}

	CFixNumberType<length,precision> &operator += (double v)
	{
	}
	CFixNumberType<length,precision> &operator += (int v)
	{
	}
	CFixNumberType<length,precision> &operator += (char *v)
	{
	}
	CFixNumberType<length,precision> &operator += (CReadOnlyFixNumberType &v)
	{
	}
}; 

#define DefineFixNumberType(length,precision,newType)					\
	typedef CUFFixNumberType<length,precision> C ## newType;			\
	typedef CReadOnlyUFFixNumberType<length,precision> CReadOnly ## newType;
*/
#endif
