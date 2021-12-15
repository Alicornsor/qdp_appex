/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file UFDataType.h
///@brief�����˽������ڲ����ݵĵײ�֧����
///@history 
///20020214	xuzh		�������ļ�
///20020309	xuzh		�޸Ĵ��ļ���֧�ָ���ReadOnly����
///20020330 xuzh		��ÿ�����������м���getString(char *)�ķ���
///20020410 xuzh		��ÿ�����������м���isNull�ķ���
///20020410 xuzh		����Լ��ֵ�����м���isVilid()����
///20060218	xuzh		�����޸��˽ṹ��ʹ���е�ReadOnly���;���const����
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

///����һ����С�ĸ������������Ӧ����Ӱ����������ִ��ڸ��ม��������
#define SMALL_DOUBLE 0.000000001

/////////////////////////////////////////////////////////////////////////
///CUFStringType<int length>��һ�������ַ���ģ���࣬ͨ��ָ�����ȣ�
///���Եõ���������ʹ�õ��ࡣCUFStringType<int length>ʵ���Ͼ��Ǹ��ݳ��ȣ�
///ֱ�ӱ����ַ�����ֵ������룬����'\0'��
///@author	xuzh
///@version	2.0,20060218
/////////////////////////////////////////////////////////////////////////
template <int length> class CUFStringType: public CUFBaseStringType
{
public:
	///���캯��
	CUFStringType(void)
	{
		//buffer[0] = '\0';
		///add by wangwei, 20121229
		clear();
	}

	///���ƹ�����
	///@param	s	�����Դ����
	CUFStringType(const CUFStringType<length>& s)
	{
		setValue(s.getValue());
	}

	///���ƹ�����
	///@param	p	�����Դ����
	CUFStringType(const char *p)
	{
		setValue(p);
	}

	///���ڲ�����
	///@param	s	���ڵ�ֵ
	///@return	�����ֵ
	const CUFStringType & operator =(const CUFStringType<length>& s)
	{
		setValue(s.getValue());
		return s;
	}

	///���ڲ����������ַ����л�ȡ
	///@param	p	���ڵ��ַ���
	///@return	������ַ���
	const char * operator =(const char *p)
	{
		setValue(p);
		return p;
	}

	///���ڲ��������������л�ȡ
	///@param	v	���ڵ�����
	///@return	���������
	const int operator =(const int v)
	{
		char tmp[100];
		sprintf(tmp,"%*d",length,v);
		setValue(tmp);
		return v;
	}
	
	///���ڲ���������64λ�������л�ȡ     liumeng 20140820
	///@param	v	���ڵĳ�����
	///@return	����ĳ�����
	const long operator =(const long v)
	{
		char tmp[100];
		sprintf(tmp,"%*ld",length,v);
		setValue(tmp);
		return v;
	}

	///����ַ�������
	void clear(void)
	{
		buffer[0]='\0';
	}

	///��ȡ�ַ�����ֵ
	///@return	�ַ�����ֵ
	const char *getValue(void) const
	{
		return buffer;
	}

	///�����ַ�����ֵ
	///@param	s	Ҫ���õ��ַ���
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

	///��strBuf�еõ������͵��ַ�����ʾ	
	///@param	strBuf	���ڷ��ý�����ַ���
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			memcpy(strBuf, buffer,length);
			strBuf[length]='\0';
		}	
	}

	///�ж��Ƿ�Ϊ��
	///@return	true��ʾΪ�գ�false��ʾ��Ϊ��
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

	///�ж��Ƿ�Ϸ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	bool isValid(void) const
	{
		return true;
	}

	///ת��Ϊ�ַ���
	///@return	�õ����ַ���
	operator const char *(void) const
	{
		return buffer;
	}

	///���ұߵĿո�ɾ��
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

	///�ж��Ƿ�С��ĳ���ַ���
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator < (const char *r) const
	{
		return strcmp(buffer,r)<0;
	}

	///�ж��Ƿ����ĳ���ַ���
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator > (const char *r) const
	{
		return strcmp(buffer, r)>0;
	}

	///�ж��Ƿ�С�ڵ���ĳ���ַ���
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator <= (const char *r) const
	{
		return strcmp(buffer,r)<=0;
	}

	///�ж��Ƿ���ڵ���ĳ���ַ���
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator >= (const char *r) const
	{
		return strcmp(buffer, r)>=0;
	}

	///�ж��Ƿ����ĳ���ַ���
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator == (const char *r) const
	{
		return strcmp(buffer, r)==0;
	}

	///�ж��Ƿ񲻵���ĳ���ַ���
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator != (const char *r) const
	{
		return strcmp(buffer, r)!=0;
	}
	
	///����hashֵ
	///@param	seed	����
	///@return	�õ���hashֵ
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
	///�洢�ַ�����ֵ
	char buffer[length+1];
};

#define DefineStringType(length,newType)				\
	typedef CUFStringType<length> C ## newType;			\
	typedef const CUFStringType<length> CReadOnly ## newType;

/////////////////////////////////////////////////////////////////////////
///CUFFloatType��һ���ڲ����ݵĸ�������
///@author	xuzh
///@version	2.0,20060218
/////////////////////////////////////////////////////////////////////////
///xuzh��20070328
///�����˶Ը�������Χ���ж�����ֹ���ֳ�Խ��Χ������
template <int length, int precision> class CUFFloatType: public CUFBaseFloatType
{
public:
	///���캯��
	CUFFloatType(void)
	{
		//clear();
		///add by wangwei, 20121229
		clear();		
	}

	///���ƹ�����
	///@param	f	�����Դ����
	CUFFloatType(const CUFFloatType& f)
	{
		setValue(f.getValue());
	}

	///���ƹ�����
	///@param	value	�����Դ����
	CUFFloatType(const double value)
	{
		setValue(value);
	}

	///���ڲ�����
	///@param	f	���ڵ�ֵ
	///@return	�����ֵ
	const CUFFloatType & operator =(const CUFFloatType& f)
	{
		setValue(f.getValue());
		return f;
	}

	///���ڲ��������Ӹ������л�ȡ
	///@param	v	���ڵĸ�����
	///@return	������ָ�����
	const double operator =(const double value)
	{
		setValue(value);
		return value;
	}

	///���ڲ����������ַ����л�ȡ
	///@param	v	���ڵ��ַ���
	///@return	������ַ���
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

	///������ݣ����ǽ�ֵ��Ϊ0
	void clear(void)
	{
		value=0.0;
	}

	///��ȡֵ
	///@return	��ȡ��ֵ
	const double getValue(void) const
	{
		return value;
	}

	///����ֵ
	///@param	v	Ҫ���õ�ֵ
	void setValue(const double v)
	{
		if ((v<SMALL_DOUBLE)&&(v>-SMALL_DOUBLE))
		{
			///������Ϊ�˷�ֹ����-0.00000�����������ĳЩ������������ڼ�������-31.0+31.0ʱ���õ��Ľ����-0.0������0.0
			value=0.0;
		}
		else
		{
			value=v;
		}
	}

	///��strBuf�еõ������͵��ַ�����ʾ	
	///@param	strBuf	���ڷ��ý�����ַ���
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

	///�ж��Ƿ�Ϊ��
	///@return	true��ʾΪ�գ�false��ʾ��Ϊ��
	bool isNull(void) const
	{
		if (value==DOUBLE_NaN)
			return true;
		else
			return false;
	}

	///�ж��Ƿ�Ϸ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
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

	///ת��Ϊʵ��
	///@return	�õ���ʵ��
	operator const double (void) const
	{
		return value;
	}
	
	///����ĳ��ֵ
	///@param	v	Ҫ�ӵ�ֵ
	///@return	�����Ժ�Ľ��
	const double operator += (const double v)
	{
		setValue(value+v);
		return v;
	}

	///��ȥĳ��ֵ
	///@param	v	Ҫ����ֵ
	///@return	�����Ժ�Ľ��
	const double operator -= (double v)
	{
		setValue(value-v);
		return v;
	}

	///����ĳ��ֵ
	///@param	v	Ҫ�˵�ֵ
	///@return	�����Ժ�Ľ��
	const double operator *= (const double v)
	{
		setValue(value*v);
		return v;
	}

	///����ĳ��ֵ
	///@param	v	Ҫ����ֵ
	///@return	�����Ժ�Ľ��
	const double operator /= (const double v)
	{
		setValue(value/v);
		return v;
	}
	
	///����ĳ��ֵ
	///@param	v	Ҫ����ֵ
	///@return	�����Ժ�Ľ��
	const int operator &(const double v) const
	{
		//******//
		//	xuzh,200609028�������˵�value/v�Ľ��Ϊ��ֵʱ�Ĵ���
		//******//
		return (int)(floor(value/v+SMALL_DOUBLE));
	}

	///�ж��Ƿ�С��ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator < (double r) const
	{
		return value < r-SMALL_DOUBLE;
	}

	///�ж��Ƿ����ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator > (double r) const
	{
		return value > r+SMALL_DOUBLE;
	}

	///�ж��Ƿ�С�ڵ���ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator <= (double r) const
	{
		return value <= r+SMALL_DOUBLE;
	}

	///�ж��Ƿ���ڵ���ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator >= (double r) const
	{
		return value >= r-SMALL_DOUBLE;
	}

	///�ж��Ƿ����ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator == (double r) const
	{
		return fabs(value-r)<=SMALL_DOUBLE;
	}

	///�ж��Ƿ񲻵���ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator != (double r) const
	{
		return fabs(value-r)>SMALL_DOUBLE;
	}

	///�ж��Ƿ�С��ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator < (int r) const
	{
		return value < r-SMALL_DOUBLE;
	}

	///�ж��Ƿ����ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator > (int r) const
	{
		return value > r+SMALL_DOUBLE;
	}

	///�ж��Ƿ�С�ڵ���ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator <= (int r) const
	{
		return value <= r+SMALL_DOUBLE;
	}

	///�ж��Ƿ���ڵ���ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator >= (int r) const
	{
		return value >= r-SMALL_DOUBLE;
	}

	///�ж��Ƿ����ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator == (int r) const
	{
		return fabs(value-r)<=SMALL_DOUBLE;
	}

	///�ж��Ƿ񲻵���ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator != (int r) const
	{
		return fabs(value-r)>SMALL_DOUBLE;
	}

	///����hashֵ
	///@param	seed	����
	///@return	�õ���hashֵ
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
	///�洢��������ֵ
	double value;
};

#define DefineFloatType(maxValue,minValue,newType)			\
	typedef CUFFloatType<maxValue,minValue> C ## newType;	\
	typedef const CUFFloatType<maxValue,minValue> CReadOnly ## newType;

/////////////////////////////////////////////////////////////////////////
///CUFIntType��һ���ڲ����ݵ�������
///@author	xuzh
///@version	2.0,20060218
/////////////////////////////////////////////////////////////////////////
class CUFIntType: public CUFBaseIntType
{
public:
	///���캯��
	CUFIntType(void)
	{
		//clear();
		///add by wangwei, 20121229
		clear();
	}

	///���ƹ�����
	///@param	i	�����Դ����
	CUFIntType(const CUFIntType& i)
	{
		setValue(i.getValue());
	}

	///���ƹ�����
	///@param	i	�����Դ����
	CUFIntType(const int i)
	{
		setValue(i);
	}

	///���ڲ�����
	///@param	i	���ڵ�ֵ
	///@return	�����ֵ
	const CUFIntType & operator =(const CUFIntType& i)
	{
		setValue(i.getValue());
		return i;
	}

	///���ڲ��������������л�ȡ
	///@param	i	���ڵ�����
	///@return	���������
	const int operator =(const int i)
	{
		setValue(i);
		return i;
	}

	///���ڲ����������ַ����л�ȡ
	///@param	v	���ڵ��ַ���
	///@return	������ַ���
	const char * operator =(const char *v)
	{
		setValue(atoi(v));
		return v;
	}

	///������ݣ����ǽ�ֵ��Ϊ0
	void clear(void)
	{
		value=0;
	}
	
	///��ȡֵ
	///@return	��ȡ��ֵ
	const int getValue(void) const
	{
		return value;
	}

	///����ֵ
	///@param	v	Ҫ���õ�ֵ
	void setValue(const int v)
	{
		value=v;
	}

	///��strBuf�еõ������͵��ַ�����ʾ	
	///@param	strBuf	���ڷ��ý�����ַ���
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			sprintf(strBuf,"%d", value);
		}	
	}	

	///�ж��Ƿ�Ϊ��
	///@return	true��ʾΪ�գ�false��ʾ��Ϊ��
	bool isNull(void) const
	{
		return false;
	}

	///�ж��Ƿ�Ϸ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	bool isValid(void) const
	{
		return true;
	}

	///ת��Ϊ����
	///@return	�õ�������
	operator const int (void) const
	{
		return value;
	}

	///���������ĳ��ֵ
	///@param	v	Ҫ�ӵ�ֵ
	///@return	�õ���ֵ
	const int operator += (const int v)
	{
		setValue(value+v);
		return value;
	}
	
	///�������ȥĳ��ֵ
	///@param	v	Ҫ����ֵ
	///@return	�õ���ֵ
	const int operator -= (const int v)
	{
		setValue(value-v);
		return value;
	}

	///���������ĳ��ֵ
	///@param	v	Ҫ�˵�ֵ
	///@return	�õ���ֵ
	const int operator *= (const int v)
	{
		setValue(value*v);
		return value;
	}

	///���������ĳ��ֵ
	///@param	v	Ҫ����ֵ
	///@return	�õ���ֵ
	const int operator /= (const int v)
	{
		setValue(value/v);
		return value;
	}

	///������ģĳ��ֵ
	///@param	v	Ҫģ��ֵ
	///@return	�õ���ֵ
	const int operator %= (const int v)
	{
		setValue(value%v);
		return value;
	}

	///����hashֵ
	///@param	seed	����
	///@return	�õ���hashֵ
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
	///�洢������ֵ
	int value;
};

typedef const CUFIntType CReadOnlyUFIntType;

/////////////////////////////////////////////////////////////////////////
///CUFLongType��һ���ڲ����ݵĳ�������
///@author	longqy
///@version	2.1,20130115
/////////////////////////////////////////////////////////////////////////
class CUFLongType: public CUFBaseLongType
{
public:
	///���캯��
	CUFLongType(void)
	{
		//clear();
		///add by wangwei, 20121229
		clear();
	}

	///���ƹ�����
	///@param	i	�����Դ����
	CUFLongType(const CUFLongType& i)
	{
		setValue(i.getValue());
	}

	///���ƹ�����
	///@param	i	�����Դ����
	CUFLongType(const long i)
	{
		setValue(i);
	}

	///���ڲ�����
	///@param	i	���ڵ�ֵ
	///@return	�����ֵ
	const CUFLongType & operator =(const CUFLongType& i)
	{
		setValue(i.getValue());
		return i;
	}

	///���ڲ��������������л�ȡ
	///@param	i	���ڵ�����
	///@return	���������
	const long operator =(const long i)
	{
		setValue(i);
		return i;
	}

	///���ڲ����������ַ����л�ȡ
	///@param	v	���ڵ��ַ���
	///@return	������ַ���
	const char * operator =(const char *v)
	{
		setValue(atol(v));
		return v;
	}

	///������ݣ����ǽ�ֵ��Ϊ0
	void clear(void)
	{
		value=0;
	}
	
	///��ȡֵ
	///@return	��ȡ��ֵ
	const long getValue(void) const
	{
		return value;
	}

	///����ֵ
	///@param	v	Ҫ���õ�ֵ
	void setValue(const long v)
	{
		value=v;
	}

	///��strBuf�еõ������͵��ַ�����ʾ	
	///@param	strBuf	���ڷ��ý�����ַ���
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			sprintf(strBuf,"%ld", value);
		}	
	}	

	///�ж��Ƿ�Ϊ��
	///@return	true��ʾΪ�գ�false��ʾ��Ϊ��
	bool isNull(void) const
	{
		return false;
	}

	///�ж��Ƿ�Ϸ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	bool isValid(void) const
	{
		return true;
	}

	///ת��Ϊ����
	///@return	�õ�������
	operator const long (void) const
	{
		return value;
	}

	///���������ĳ��ֵ
	///@param	v	Ҫ�ӵ�ֵ
	///@return	�õ���ֵ
	const long operator += (const long v)
	{
		setValue(value+v);
		return value;
	}
	
	///�������ȥĳ��ֵ
	///@param	v	Ҫ����ֵ
	///@return	�õ���ֵ
	const long operator -= (const long v)
	{
		setValue(value-v);
		return value;
	}

	///���������ĳ��ֵ
	///@param	v	Ҫ�˵�ֵ
	///@return	�õ���ֵ
	const long operator *= (const long v)
	{
		setValue(value*v);
		return value;
	}

	///���������ĳ��ֵ
	///@param	v	Ҫ����ֵ
	///@return	�õ���ֵ
	const long operator /= (const long v)
	{
		setValue(value/v);
		return value;
	}

	///������ģĳ��ֵ
	///@param	v	Ҫģ��ֵ
	///@return	�õ���ֵ
	const long operator %= (const long v)
	{
		setValue(value%v);
		return value;
	}

	///����hashֵ
	///@param	seed	����
	///@return	�õ���hashֵ
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
	///�洢������ֵ
	long value;
};

typedef const CUFLongType CReadOnlyUFLongType;


/////////////////////////////////////////////////////////////////////////
///CUFRangeIntType<int from,int to>��һ���ڲ������з�Χ�޶�������
///ģ���࣬ͨ��ָ����Χ�����Եõ���������ʹ�õ��ࡣCUFRangeIntType<int 
///from, int to>ʵ���Ͼ��Ǵ洢һ������������������ֵʱ�������
///@author	xuzh
///@version	2.0,20060218
/////////////////////////////////////////////////////////////////////////
template <int from, int to> class CUFRangeIntType: public CUFBaseIntType
{
public:
	///���캯��
	CUFRangeIntType(void)
	{
		//clear();
		///add by wangwei, 20121229
		clear();	
	}

	///���ƹ�����
	///@param	i	�����Դ����
	CUFRangeIntType(const CUFRangeIntType<from,to>& i)
	{
		setValue(i.getValue());
	}

	///���ƹ�����
	///@param	i	�����Դ����
	CUFRangeIntType(const int i)
	{
		setValue(i);
	}

	///���ڲ�����
	///@param	i	���ڵ�ֵ
	///@return	�����ֵ
	const CUFRangeIntType<from,to> & operator =(const CUFRangeIntType<from,to>& i)
	{
		setValue(i.getValue());
		return i;
	}

	///���ڲ��������������л�ȡ
	///@param	i	���ڵ�����
	///@return	���������
	const int operator =(const int i)
	{
		setValue(i);
		return i;
	}

	///���ڲ����������ַ����л�ȡ
	///@param	v	���ڵ��ַ���
	///@return	������ַ���
	const char * operator =(const char *v)
	{
		setValue(atoi(v));
		return v;
	}

	///������ݣ����ǽ�ֵ��Ϊfrom
	void clear(void)
	{
		value=from;
	}

	///��ȡֵ
	///@return	��ȡ��ֵ
	const int getValue(void) const
	{
		return value;
	}

	///����ֵ
	///@param	v	Ҫ���õ�ֵ
	///@exception	CRuntimeError	������ֵԽ�磬���׳����쳣
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

	///��strBuf�еõ������͵��ַ�����ʾ	
	///@param	strBuf	���ڷ��ý�����ַ���
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			sprintf(strBuf,"%d", value);
		}	
	}

	///�ж��Ƿ�Ϊ��
	///@return	true��ʾΪ�գ�false��ʾ��Ϊ��
	bool isNull(void) const
	{
		return false;
	}

	///�ж��Ƿ�Ϸ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	bool isValid(void) const
	{
		if ((value>to)||(value<from))
			return false;
		else
			return true;
	}

	///ת��Ϊ����
	///@return	�õ�������
	operator const int (void) const
	{
		return value;
	}

	///���������ĳ��ֵ
	///@param	v	Ҫ�ӵ�ֵ
	///@return	�õ���ֵ
	const int operator += (const int v)
	{
		setValue(value+v);
		return value;
	}
	
	///�������ȥĳ��ֵ
	///@param	v	Ҫ����ֵ
	///@return	�õ���ֵ
	const int operator -= (const int v)
	{
		setValue(value-v);
		return value;
	}

	///���������ĳ��ֵ
	///@param	v	Ҫ�˵�ֵ
	///@return	�õ���ֵ
	const int operator *= (const int v)
	{
		setValue(value*v);
		return value;
	}

	///���������ĳ��ֵ
	///@param	v	Ҫ����ֵ
	///@return	�õ���ֵ
	const int operator /= (const int v)
	{
		setValue(value/v);
		return value;
	}

	///������ģĳ��ֵ
	///@param	v	Ҫģ��ֵ
	///@return	�õ���ֵ
	const int operator %= (const int v)
	{
		setValue(value%v);
		return value;
	}

	///����hashֵ
	///@param	seed	����
	///@return	�õ���hashֵ
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
	///�洢������ֵ
	int value;
};

#define DefineRangeIntType(from,to,newType)					\
	typedef CUFRangeIntType<from,to> C ## newType;			\
	typedef const CUFRangeIntType<from,to> CReadOnly ## newType;

/////////////////////////////////////////////////////////////////////////
///CUFCharType��һ���ڲ����ݵ��ַ���
///@author	xuzh
///@version	2.0,20060218
/////////////////////////////////////////////////////////////////////////
class CUFCharType: public CUFBaseCharType
{
public:
	///���캯��
	CUFCharType(void)
	{
		//clear();
		///add by wangwei, 20121229
		clear();		
	}

	///���ƹ�����
	///@param	c	�����Դ����
	CUFCharType(const CUFCharType& c)
	{
		setValue(c.getValue());
	}

	///���ƹ�����
	///@param	c	�����Դ����
	CUFCharType(const char c)
	{
		setValue(c);
	}

	///���ڲ�����
	///@param	c	���ڵ�ֵ
	///@return	�����ֵ
	const CUFCharType & operator =(const CUFCharType& c)
	{
		setValue(c.getValue());
		return c;
	}

	///���ڲ����������ַ��л�ȡ
	///@param	c	���ڵ��ַ�
	///@return	������ַ�
	const char operator =(const char c)
	{
		setValue(c);
		return c;
	}

	///���ڲ����������ַ����л�ȡ
	///@param	v	���ڵ��ַ���
	///@return	������ַ���
	const char * operator =(const char *v)
	{
		setValue(*v);
		return v;
	}

	///������ݣ����ǽ�ֵ��Ϊ'\0'
	void clear(void)
	{
		value='\0';
	}
	
	///��ȡֵ
	///@return	��ȡ��ֵ
	char getValue(void) const
	{
		return value;
	}

	///����ֵ
	///@param	v	Ҫ���õ�ֵ
	void setValue(const char v)
	{
		value=v;
	}

	///��strBuf�еõ������͵��ַ�����ʾ	
	///@param	strBuf	���ڷ��ý�����ַ���
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			sprintf(strBuf,"%c", value);
		}	
	}	

	///�ж��Ƿ�Ϊ��
	///@return	true��ʾΪ�գ�false��ʾ��Ϊ��
	bool isNull(void) const
	{
		return false;
	}

	///�ж��Ƿ�Ϸ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	bool isValid(void) const
	{
		return true;
	}

	///ת��Ϊ�ַ�
	///@return	�õ����ַ�
	operator const char (void) const
	{
		return value;
	}

	///����hashֵ
	///@param	seed	����
	///@return	�õ���hashֵ
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
	///�洢�ַ���ֵ
	char value;
};

typedef const CUFCharType CReadOnlyUFCharType;

#define EnumNull ' '

///���ڶ���һ�����м����ַ�����
///@param	typename	Ҫ���������
///@param	validString	��������ȡֵ���ַ����ɵ��ַ���
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
///CUFWordType��һ���ڲ����ݵ��ַ���
///@author	xuzh
///@version	2.0,20060218
/////////////////////////////////////////////////////////////////////////
class CUFWordType : public CUFBaseWordType
{
public:
	///���캯��
	CUFWordType(void)
	{
//		clear();
///add by wangwei, 20121229
		clear();
	}

	///���ƹ�����
	///@param	w	�����Դ����
	CUFWordType(const CUFWordType& w)
	{
		setValue(w.getValue());
	}

	///���ƹ�����
	///@param	w	�����Դ����
	CUFWordType(WORD w)
	{
		setValue(w);
	}
	
	///���ڲ�����
	///@param	w	���ڵ�ֵ
	///@return	�����ֵ
	const CUFWordType & operator =(const CUFWordType& w)
	{
		setValue(w.getValue());
		return w;
	}

	///���ڲ������������л�ȡ
	///@param	w	���ڵ���
	///@return	�������
	const WORD operator =(const WORD w)
	{
		setValue(w);
		return w;
	}

	///���ڲ����������ַ����л�ȡ
	///@param	v	���ڵ��ַ���
	///@return	������ַ���
	const char * operator =(const char *v)
	{
		setValue(atoi(v));
		return v;
	}

	///������ݣ����ǽ�ֵ��Ϊ0
	void clear(void)
	{
		value=0;
	}

	///��ȡֵ
	///@return	��ȡ��ֵ
	WORD getValue(void) const
	{
		return value;
	}

	///����ֵ
	///@param	v	Ҫ���õ�ֵ
	void setValue(WORD v)
	{
		value=v;
	}

	///��strBuf�еõ������͵��ַ�����ʾ	
	///@param	strBuf	���ڷ��ý�����ַ���
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			sprintf(strBuf,"%d", value);
		}	
	}	

	///�ж��Ƿ�Ϊ��
	///@return	true��ʾΪ�գ�false��ʾ��Ϊ��
	bool isNull(void) const
	{
		return false;
	}

	///�ж��Ƿ�Ϸ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	bool isValid(void) const
	{
		return true;
	}

	///ת��Ϊ��
	///@return	�õ�����
	operator const WORD (void)
	{
		return value;
	}

	///����hashֵ
	///@param	seed	����
	///@return	�õ���hashֵ
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
	///�洢�ַ���ֵ
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
	///��strBuf�еõ������͵��ַ�����ʾ	
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

	///������ݣ����ǽ�ֵ��Ϊ0
	void clear(void)
	{
		value[0]='\0';
	}

	///����ֵ
	///@param	v	Ҫ���õ�ֵ
	void setValue(char *v)
	{
	}

	///����ֵ
	///@param	v	Ҫ���õ�ֵ
	void setValue(int v)
	{
	}

	///����ֵ
	///@param	v	Ҫ���õ�ֵ
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
