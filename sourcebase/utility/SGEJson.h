#pragma once
#pragma warning (disable: 4514 4786)
#include <string>
#include <vector>
#include <map>
#include <string.h>
#include <stdio.h>
using namespace std;

#define  DENYU		1;   //=��
#define  DOUHAO		2;   //,
#define  ZKHAOY		3;   //[
#define  ZKHAOZ		4;   //]
#define  DKHAOY		5;   //{
#define  DKHAOZ		5;   //}
#define  CZYZF		'\\';

typedef	map< string, void * > ValueString;
typedef	vector< void * > ValueVector;

class CValue{

public:

	CValue(){
		arrlength = 0;
		arrcount  = 0;
		valuetype = 0;

		ValueFlag = false;
		isDKHclear = false;
		isZKHclear =false;
	};

	void setkey(string &key)
	{
		ValueFlag = true;
		key_=key;
	};

	void  setValue(string &value)
	{
		ValueFlag = true;
		value_=value;
	};
	
	
	string  getkey()
	{
		return key_;
	};
	
	string  getValue()
	{
		return value_;
	};
	
	bool  isNull()
	{
		return ValueFlag;
	};

	void ClearEntity()
	{
	
		CValue *tmp=NULL;
		//��ɾ��vector����new����
		if (v_valueobj.size() > 0)
		{
			
			int iloop;
			for (iloop=0;iloop < v_valueobj.size();iloop++)  
			{  
				CValue *tmp=NULL;
				tmp=(CValue *)v_valueobj[iloop];
				if (tmp)
				{
					tmp->ClearEntity();
					delete tmp;
					tmp=NULL;
				}
			
			}
			v_valueobj.clear();
		}

		if (m_value.size() > 0)
		{
			ValueString::iterator itmap=m_value.begin();
			for (;itmap!=m_value.end();)
			{
				CValue *tmp=NULL;
				tmp=(CValue *)itmap->second;
				m_value.erase(itmap++);
				if (tmp)
				{
					tmp->ClearEntity();
					delete tmp;
					tmp=NULL;
				}
			}
			m_value.clear();
		}
	};

	string getStringValueFromMap(string &key){
		ValueString::iterator itmap=m_value.find(key);
		if ( itmap != m_value.end())
		{
			CValue *tmp=NULL;
			tmp=(CValue *)itmap->second;
			return tmp->getValue();
		} 
		else
		{
			return "";
		}
	};
	
	CValue *getCValueFromMap(string &key){
		ValueString::iterator itmap=m_value.find(key);
		if ( itmap != m_value.end())
		{
			CValue *tmp=NULL;
			tmp=(CValue *)itmap->second;
			return tmp;
		} 
		else
		{
			return NULL;
		}
	};

	int			arrlength;	//��������
	int			arrcount;	//��ǰ��������
	int			valuetype;	//��������  1��string 2������
	
	ValueVector	v_valueobj;
	ValueString m_value;
	bool isDKHclear;
	bool isZKHclear;
	int acount;
private:
	bool ValueFlag;
	string key_;
	string value_;
};


class CJSonSimple 
{
public:

	CJSonSimple();

	void    Analisyskeyandvalue(CValue &fpvalue,int itype,void *v_value);

	char	getNextChar();

	char	readString(CValue &fpvalue);

	//��ʼ�����ַ�������
	void	Start();

	string  IntToString(int strint);

	//����key��ȡvalue
	string  GetStringByKey(string skey);

	//����key��ȡcvalue��
	CValue  *GetCValueByKey(string skey);

	//����json������
	void	ClearEntity();

	//���ý����ַ���
	void SetSrc(char *src);
private:

	char * begin_;

	char * current_;
	
	char * end_;
	
	int singleTypeDENYU;
	int singleTypeDOUHAO;
	int singleTypeZKHAOY;
	int singleTypeZKHAOZ;
	int singleTypeDKHAOY;
	int singleTypeDKHAOZ;
	CValue cvalue_;
	
	//�Ƿ���������
	bool isDKHclear;
	bool isZKHclear;

	//ת���ַ���
	bool ZYFlag;
	char *ZYPosition;
	int acount;

	//ֵȫ��
	char valuetmp[1024*10];
};

