#include "CFixNumber.h"
#include <math.h>

CFixNumberImpl::CFixNumberImpl()
{
	m_precision = 2;		//缺损2位小数	
	m_numbervect.clear();
	m_dValue = 0.00;
	m_nLength = 8;		//缺损8位长度
}

CFixNumberImpl::CFixNumberImpl(char *szNumber,int length)
{
	string str1 = szNumber;
	m_nLength = length;
	initString(szNumber);
};

void CFixNumberImpl::initString(string strNumber)
{
	int nPos = strNumber.find_last_of(".");
	if(nPos == string::npos)
		m_precision = 0;
	else
		m_precision = strNumber.length()-nPos-1;
	if(strNumber[0] == '-')
		m_bIsPositive = false;
	else
		m_bIsPositive = true;
	initData(strNumber);
	m_dValue = atof(strNumber.c_str());
}

CFixNumberImpl::CFixNumberImpl(string strNumber,int length)
{
	initString(strNumber);
	m_nLength = length;
}

CFixNumberImpl::CFixNumberImpl(double dbValue,int precision,int length):m_precision(precision)
{
	char szTemp[250];
	char formatStr[10];
	sprintf(formatStr,"%%.%df",m_precision);
	sprintf(szTemp,formatStr,dbValue);
	initData(szTemp);
	m_bIsPositive = dbValue>=0?true:false;
	this->m_dValue = dbValue;
	m_nLength = length;
}

CFixNumberImpl::CFixNumberImpl(float fValue,int precision,int length):m_precision(precision)
{
	char szTemp[250];
	char formatStr[10];
	sprintf(formatStr,"%%.%df",m_precision);
	sprintf(szTemp,formatStr,fValue);
	initData(szTemp);
	m_bIsPositive = fValue>=0?true:false;
	this->m_dValue = fValue;
	m_nLength = length;
}

CFixNumberImpl::CFixNumberImpl(int intValue,int precision,int length):m_precision(precision)
{
	char szTemp[250];
	sprintf(szTemp,"%d",intValue);
	initData(szTemp);
	m_bIsPositive = intValue>=0?true:false;
	this->m_dValue = intValue;
	m_nLength = length;
}


int CFixNumberImpl::isA(char *objectType)
{
	return CBaseObject::isA(objectType);
}

void CFixNumberImpl::output(CLogger *pLogger,int indent){

}

char* CFixNumberImpl::getType(void)
{
	return "FixNumber";
}

CFixNumberImpl::CFixNumberImpl(const CFixNumberImpl& rightValue)
{
	m_precision = rightValue.m_precision;
	m_nLength = rightValue.m_nLength;
	m_numbervect.clear();
	m_bIsPositive = rightValue.m_bIsPositive;
	m_dValue = rightValue.m_dValue;
	copy(rightValue.m_numbervect.begin(),rightValue.m_numbervect.end(),back_inserter(m_numbervect));
}

CFixNumberImpl& CFixNumberImpl::operator=(const CFixNumberImpl& rightValue)
{
	m_precision = rightValue.m_precision;
	m_numbervect.clear();
	m_dValue = rightValue.m_dValue;
	m_nLength = rightValue.m_nLength;
	m_bIsPositive = rightValue.m_bIsPositive;
	copy(rightValue.m_numbervect.begin(),rightValue.m_numbervect.end(),back_inserter(m_numbervect));
	return *this;
}

void CFixNumberImpl::initData(string strNumber)
{
	m_numbervect.clear();
	string::iterator it = strNumber.begin();
	while(it != strNumber.end())
	{
		if( ((*it) < '0' || (*it) > '9') && (*it) != '.')	//错误的数据
		{
			//CBaseException exce("非法的数据输入");
			return;
		}
		if((*it) != '.')
			m_numbervect.push_back((*it)-'0');
		it++;
	}
}

string CFixNumberImpl::toString()
{
	char sz[1];
	string result;
	if(!m_bIsPositive)
		result = "-";
	int pos = m_numbervect.size()-m_precision;
	for(int i=0;i<(int)m_numbervect.size();i++)
	{		
		if(i == pos)
			result += ".";
		sprintf(sz,"%d",m_numbervect[i]);
		result += sz;
	
	}
	
	return result;

}


void CFixNumberImpl::setPrecision(int precision)
{
	if(precision > m_precision)	//现在的精度不够，后面添上0
	{
		while(m_precision != precision)
		{
			m_precision++;
			m_numbervect.push_back(0);
		}
	}
	else			//精度过剩,采取舍去的方法
	{
		while(m_precision != precision)
		{
			m_precision--;
			m_numbervect.pop_back();
		}
	}
}

CFixNumberImpl operator+(const CFixNumberImpl& leftValue,const CFixNumberImpl& rightValue)
{
	if(leftValue.m_bIsPositive != rightValue.m_bIsPositive) //符号不等
	{
		if(leftValue.m_bIsPositive == true){	
			CFixNumberImpl result(rightValue);
			result.m_bIsPositive = true;
			return leftValue - result;
		}
		else {
			CFixNumberImpl result(leftValue);
			result.m_bIsPositive = true;
			return rightValue - result;
		}
	}
	else
	{
		///精度向大的靠拢
		const CFixNumberImpl* pBigPrecision = leftValue.m_precision>rightValue.m_precision?&leftValue:&rightValue;
		const CFixNumberImpl* pSmallBigPrecision = leftValue.m_precision>rightValue.m_precision?&rightValue:&leftValue;

		CFixNumberImpl result(*pSmallBigPrecision);
		CFixNumberImpl bigOne(*pBigPrecision);

		///为了保证精度,小数点后面必须填0
		while(result.m_precision != pBigPrecision->m_precision)
		{
			result.m_precision++;
			result.m_numbervect.push_back(0);
		}
		
		if(result.m_numbervect.size() < bigOne.m_numbervect.size())
		{
			int number = bigOne.m_numbervect.size() - result.m_numbervect.size();
			for (int i=0;i<number;i++)
			{
				result.m_numbervect.insert(result.m_numbervect.begin(),0);
			}
		}
		else if(result.m_numbervect.size() > bigOne.m_numbervect.size())
		{
			int number = result.m_numbervect.size() - bigOne.m_numbervect.size();
			for (int i=0;i<number;i++)
			{
				bigOne.m_numbervect.insert(bigOne.m_numbervect.begin(),0);
			}
		}

		int value = 0;
		for(int i = result.m_numbervect.size()-1;i>=0;i--)
		{
			value = result.m_numbervect[i] + bigOne.m_numbervect[i] + value;
			result.m_numbervect[i] = value%10;
			value = value/10; 
		}
		if(value != 0)
			result.m_numbervect.insert(result.m_numbervect.begin(),value);
		result.m_bIsPositive = leftValue.m_bIsPositive;
		result.m_nLength = leftValue.m_nLength>rightValue.m_nLength?leftValue.m_nLength:rightValue.m_nLength;
		return result;
	}
}

CFixNumberImpl operator-(const CFixNumberImpl& leftValue,const CFixNumberImpl& rightValue)
{
	if(leftValue.m_bIsPositive != rightValue.m_bIsPositive)
	{
		if(leftValue.m_bIsPositive == true)
		{
			CFixNumberImpl result(rightValue);
			result.m_bIsPositive = true;
			return leftValue+ result;
		}
		else
		{
			CFixNumberImpl result1(rightValue);
			CFixNumberImpl result(leftValue);
			result1.m_bIsPositive = result.m_bIsPositive = false;
			return result+ result1;
		}
	}
	else
	{
		if(leftValue.m_bIsPositive == false)
		{
			CFixNumberImpl result(rightValue);
			result.m_bIsPositive = true;
			return result+leftValue;
		}
		///精度向大的靠拢
		CFixNumberImpl left(leftValue);
		CFixNumberImpl right(rightValue);

		///为了保证精度,小数点后面必须填0
		while(left.m_precision < right.m_precision)
		{
			left.m_precision++;
			left.m_numbervect.push_back(0);
		}

		while(right.m_precision < left.m_precision)
		{
			right.m_precision++;
			right.m_numbervect.push_back(0);
		}

		if(right.m_numbervect.size() < left.m_numbervect.size())
		{
			int number = left.m_numbervect.size() - right.m_numbervect.size();
			for (int i=0;i<number;i++)
			{
				right.m_numbervect.insert(right.m_numbervect.begin(),0);
			}
		}
		else if(right.m_numbervect.size() > left.m_numbervect.size())
		{
			int number = right.m_numbervect.size() - left.m_numbervect.size();
			for (int i=0;i<number;i++)
			{
				left.m_numbervect.insert(left.m_numbervect.begin(),0);
			}
		}
		
		CFixNumberImpl result;
		result.m_precision = left.m_precision;
		//计算
		int value = 0;
		result.m_bIsPositive = true;
		for(int i = 0;i<(int)right.m_numbervect.size();i++)
		{
			if(result.m_bIsPositive)
			{
				value = left.m_numbervect[i] - right.m_numbervect[i];
				if(value < 0)	//需要借位
				{
					int x =  i-1;
					bool bSucess = false;	//判断是否借位成功
					while (x >= 0)
					{
						if(result.m_numbervect[x] != 0)
						{
							bSucess = true;
							result.m_numbervect[x] -= 1;
							break;
						}
						x--;
					}
					
					if(!bSucess)
					{
						result.m_bIsPositive = false;
						result.m_numbervect.push_back(0-value);
					}else
					{
						value += 10;
						result.m_numbervect.push_back(value);
					}
				}else
					result.m_numbervect.push_back(value);
			}
			else
			{	
				value = rightValue.m_numbervect[i] - left.m_numbervect[i];
				if(value < 0)	//需要借位
				{
					int x =  i-1;
					while (x >= 0)
					{
						if(result.m_numbervect[x] != 0)
						{
							result.m_numbervect[x] -= 1;
							break;
						}
					}
					value += 10;
					result.m_numbervect.push_back(value);
				}
			}
		}	
		///去除前面的多余的0
		int pos = result.m_numbervect.size()-result.m_precision-1;
		for(i =0;i<pos;i++)
		{
			if(result.m_numbervect[0] == 0 && pos != 0 )
				result.m_numbervect.erase(result.m_numbervect.begin());
		}
		result.m_nLength = leftValue.m_nLength>rightValue.m_nLength?leftValue.m_nLength:rightValue.m_nLength;
		return result;
	}
}

CFixNumberImpl operator*(const CFixNumberImpl& leftValue,const CFixNumberImpl& rightValue)
{
	int presion = leftValue.m_precision>rightValue.m_precision?leftValue.m_precision:rightValue.m_precision;
	int l = (int)(leftValue.m_dValue* pow(10,presion));
	int r = (int)(rightValue.m_dValue* pow(10,presion));
	int value = l*r;
	double retValue = value/pow(10,presion);
	int	   length = leftValue.m_nLength>rightValue.m_nLength?leftValue.m_nLength:rightValue.m_nLength;
	return CFixNumberImpl(retValue,leftValue.m_precision+rightValue.m_precision,length);
}

CFixNumberImpl operator/(const CFixNumberImpl& leftValue,const CFixNumberImpl& rightValue)
{
	int presion = leftValue.m_precision>rightValue.m_precision?leftValue.m_precision:rightValue.m_precision;
	int l = (int)(leftValue.m_dValue* pow(10,presion));
	int r = (int)(rightValue.m_dValue* pow(10,presion));
	int value = l/r;
	double retValue = value/pow(10,presion);
	int	   length = leftValue.m_nLength>rightValue.m_nLength?leftValue.m_nLength:rightValue.m_nLength;
	return CFixNumberImpl(retValue,leftValue.m_precision+rightValue.m_precision,length);
}

