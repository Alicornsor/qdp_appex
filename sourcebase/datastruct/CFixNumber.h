/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CFixNumber.h
///@brief定长数处理
///@history 
///20050811	张冀海		创建该文件
/////////////////////////////////////////////////////////////////////////
#ifndef _FIX_NUMBER_H
#define _FIX_NUMBER_H
#include "CBaseObject.h"
//#include "ErrorHandle.h"
#include "UFDataType.h"
#include <string>
#include <vector>
using namespace std;


/////////////////////////////////////////////////////////////////////////
///CFixNumberImpl是一个定点数类的具体实现。这个类定义了一个对于定点数对象的操作，同时
///给出了相应的检查的方法。
///@author	张冀海
///@version	1.0,20050811
/////////////////////////////////////////////////////////////////////////

class CFixNumberImpl;
CFixNumberImpl operator+(const CFixNumberImpl& leftValue,const CFixNumberImpl& rightValue);
CFixNumberImpl operator-(const CFixNumberImpl& leftValue,const CFixNumberImpl& rightValue);
CFixNumberImpl operator*(const CFixNumberImpl& leftValue,const CFixNumberImpl& rightValue);
CFixNumberImpl operator/(const CFixNumberImpl& leftValue,const CFixNumberImpl& rightValue);

class CFixNumberImpl:public CBaseObject
{
friend CFixNumberImpl operator+(const CFixNumberImpl& leftValue,const CFixNumberImpl& rightValue);
friend CFixNumberImpl operator-(const CFixNumberImpl& leftValue,const CFixNumberImpl& rightValue);
friend CFixNumberImpl operator*(const CFixNumberImpl& leftValue,const CFixNumberImpl& rightValue);
friend CFixNumberImpl operator/(const CFixNumberImpl& leftValue,const CFixNumberImpl& rightValue);

public:
	///缺损的构造函数
	CFixNumberImpl();		
	///根据传入的字符串构造
	CFixNumberImpl(char *szNumber,int length); 
	///根据传入的String构造
	CFixNumberImpl(string strNumber,int length);
	///根据传入的值,并且指明精度
	CFixNumberImpl(double dbValue,int precision,int length);
	///根据传入的值,并且指明精度
	CFixNumberImpl(float fValue,int precision,int length);
	///根据传入的值,并且指明精度
	CFixNumberImpl(int intValue,int precision,int length);

	///Copy Constructor
	CFixNumberImpl(const CFixNumberImpl& rValue);

	///operator =
	CFixNumberImpl& operator=(const CFixNumberImpl& rightValue);

	///判断一个对象的类型是否就是指定的对象类型。该函数是一个虚函数，各个继承
	///类需要重新定义这个函数。在检查对象类型时，即使objectType符合本对象的
	///某个祖先类，也认为是正确的，因为作为继承类，它也是祖先类的一种。
	virtual int isA(char *objectType);

	///将本对象进行输出，主要用于调试。该函数是一个虚函数，各个继承类
	///需要重新定义该函数。
	///@param	pLogger	进行输出的
	///@param	indent	缩进量
	virtual void output(CLogger *pLogger,int indent=0);

	///返回标示本对象类型的字符串，一般就是本对象的类名。该函数是一个虚函数，
	///各个继承类需要重新定义该函数。
	///@return	标示本对象类型的字符串
	virtual char *getType(void);

	///将本对象输出为一个string	
	string toString();
	
	///设置精度
	void setPrecision(int precision);

	///装换成Double
	double toDouble(){
		return m_dValue;
	}

private:
	///初始化数据,
	///@param	strNumber	传入的字符串
	void initData(string strNumber);
	void initString(string str);

private:
	int m_precision;			//保存精度
	int m_nLength;				//数字的最大长度
	vector<int>	m_numbervect;	//数字列表
	bool m_bIsPositive;			//是否为正,true:正 false:负数
	double m_dValue;			//保存的值,用来做乘法和除法
};




/////////////////////////////////////////////////////////////////////////
///CFixNumber是一个定点数类的。这个类定义了一个对于定点数对象的操作，同时
///给出了相应的检查的方法。模板参数制定包含的数字的精度.
///@author	张冀海
///@version	1.0,20050811
/////////////////////////////////////////////////////////////////////////

template<int length,int precision>
class CFixNumber
{
public:
	CFixNumber():m_fixNumberImpl(0.00,precision){};
	CFixNumber(double dValue):m_fixNumberImpl(dValue,precision,length){m_strNumber=m_fixNumberImpl.toString().c_str();}
	CFixNumber(int intValue):m_fixNumberImpl(intValue,precision,length){m_strNumber=m_fixNumberImpl.toString().c_str();}
	CFixNumber(float fValue):m_fixNumberImpl(fValue,precision,length){m_strNumber=m_fixNumberImpl.toString().c_str();}
	CFixNumber(string strValue):m_fixNumberImpl(strValue,length){
		m_fixNumberImpl.setPrecision(precision);
		m_strNumber=m_fixNumberImpl.toString().c_str();
	}
	CFixNumber(char *szValue):m_fixNumberImpl(szValue,length){
		m_fixNumberImpl.setPrecision(precision);
		m_strNumber=m_fixNumberImpl.toString().c_str();
	}

	CFixNumber<length,precision> operator+(const CFixNumber<length,precision>& value)
	{
		CFixNumberImpl temp1(m_strNumber,precision);
		CFixNumberImpl temp2(value.m_strNumber,precision);
		CFixNumberImpl result =  temp1 + temp2;		
		CFixNumber<length,precision> value1(result);
		return value1;
	}
	
	CFixNumber<length,precision> operator-(const CFixNumber<length,precision>& value)
	{
		CFixNumberImpl temp1(m_strNumber,precision);
		CFixNumberImpl temp2(value.m_strNumber,precision);
		CFixNumberImpl result =  temp1 - temp2;		
		CFixNumber<length,precision> value1(result);
		return value1;
	}

	/*CFixNumber<precision*2> operator*(const CFixNumber<precision>& value)
	{
		CFixNumberImpl result = m_fixNumberImpl*value.m_fixNumberImpl;		
		CFixNumber<precision*2> value1(result);
		return value1;
	}*/

	template<int length2,int precision2>
	CFixNumber<length+length2,precision+precision2> operator*(const CFixNumber<length2,precision2>& value)
	{
		CFixNumberImpl result = m_fixNumberImpl*value.m_fixNumberImpl;		
		CFixNumber<length+length2,precision+precision2> value1(result);
		return value1;
	}

	template<int length2,int precision2>
	CFixNumber<length,precision> operator/(const CFixNumber<length2,precision2>& value)
	{
		CFixNumberImpl result = m_fixNumberImpl/value.m_fixNumberImpl;		
		CFixNumber<length,precision> value1(result);
		return value1;
	}

	///将本对象输出为一个string	
	string toString() const {
		return string(m_strNumber.getValue());
	}

	double toDouble() const {
		CFixNumberImpl temp(m_strNumber.getValue(),precision);
		return temp.toDouble();
	}

	CFixNumber(CFixNumberImpl& value):m_fixNumberImpl(value){m_fixNumberImpl.setPrecision(precision);}	
	CFixNumber(const CFixNumber<length,precision>& value){
		m_fixNumberImpl = CFixNumberImpl(value.toDouble(),precision,length);
		m_strNumber = value.toString().c_str();
	}

	template<int length2,int precision2>
	CFixNumber<length,precision>& operator=(const CFixNumber<length2,precision2>& value)
	{
		m_fixNumberImpl = CFixNumberImpl(value.toDouble(),precision,length);
		m_strNumber = value.toString().c_str();
		return *this;
	}
private:
	CFixNumberImpl m_fixNumberImpl;
	CUFStringType<length> m_strNumber;
};

#endif
