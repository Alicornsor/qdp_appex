#include "SGEJson.h"


CJSonSimple::CJSonSimple(){

}

void CJSonSimple::SetSrc(char *src)
{
	current_	=src;
	begin_		=src;
	int i		=strlen(src);
	end_		=src+i+1;
	ZYPosition	=NULL;
	singleTypeDENYU		= 0;
	singleTypeDOUHAO	= 0;
	singleTypeZKHAOY	= 0;
	singleTypeZKHAOZ	= 0;
	singleTypeDKHAOY	= 0;
	singleTypeDKHAOZ	= 0;
	isDKHclear			= false;
	isZKHclear			= false;
	ZYFlag				= false;
	acount				= 0;
}

void CJSonSimple::ClearEntity()
{
	cvalue_.ClearEntity();
}

char CJSonSimple::readString(CValue &fpvalue) {
	char c = '\0';
	while (current_ != end_) {
		c = getNextChar();
		if (c == '\\')
		{
			ZYPosition	=current_;
			ZYFlag		=true;
			getNextChar();
		}
		else if (c == '='){
			fpvalue.valuetype	= 0;
			//�Ǽ�ֵ��
			break;
		}
		else if (c == ','){

			fpvalue.valuetype	= 0;
			//�Ǽ�ֵ�ԵĽ���
			break;
		}
		else if (c == '['){
			fpvalue.isZKHclear			= true;
			fpvalue.valuetype	= 2;
			//�������Ϳ�ʼ
			break;
		}
		else if (c == '{'){
			fpvalue.isDKHclear			= true;
			fpvalue.arrcount	= fpvalue.arrcount+1;
			fpvalue.valuetype   = 1;
			//��ϣ���Ϳ�ʼ
			break;
		}
		else if (c == ']'){
			fpvalue.isZKHclear			= false;
			//�������ͽ���
			break;
		}
		else if (c == '}'){
			fpvalue.isDKHclear			= false;
			fpvalue.valuetype   = 0;
			//��ϣ���ͽ���
			break;
		}
	}
	return c ;
}

char CJSonSimple::getNextChar() {
	if (current_ == end_)
		return 0;
	return *current_++;
}

//��ȡkeyֵ
void  CJSonSimple::Analisyskeyandvalue(CValue &fpvalue,int itype,void *v_value) {
	
	
	//��ȡ��
	char temp[256];
	bool delFlag=false;			//false��Ҫɾ��tmpvalue��true��Ҫɾ��tmpvalue��
	if (current_ == end_)
	{
		fpvalue.isZKHclear =false;
		fpvalue.isDKHclear =false;
		return;
	}
	char *tmp	=current_;
	char c		=readString(fpvalue);
	CValue *tmpvalue=new CValue();
	
	
	memset(temp,0x00,256);
	memcpy(temp,tmp,(current_ - tmp - 1));

	string  skey(temp);
	switch(c)
	{
		case '[':
			{
				tmpvalue->valuetype = 2;
				tmpvalue->isZKHclear=true;
				tmpvalue->setkey(skey) ;
				Analisyskeyandvalue(*tmpvalue,2,NULL);
				fpvalue.m_value.insert(std::pair< string,void* >(skey,(void *)tmpvalue));
				break;
			}
		case '{':
			{
				delFlag =true;
				//new  һ��mapд��vector
				Analisyskeyandvalue(fpvalue,1,NULL);		
				break;
			}	
		case '=':
			{
				//��ȡֵ
				tmp=current_;
				char m=readString(fpvalue);
				switch(m)
				{
				case '[':
					{
						acount++;
						//new һ��vector
						tmpvalue->isZKHclear=true;
						fpvalue.acount = acount;
						tmpvalue->setkey(skey);
						Analisyskeyandvalue(*tmpvalue,2,NULL);
						string stmp			=IntToString(tmpvalue->arrcount);
						tmpvalue->arrlength	=tmpvalue->arrcount;
						tmpvalue->valuetype	= 2;
						if (fpvalue.arrcount > 0 )
						{
							if (fpvalue.v_valueobj.size() < fpvalue.arrcount)
							{
								printf("error analysis \n");
							}else{
								CValue *vstr= (CValue *)fpvalue.v_valueobj[fpvalue.arrcount-1];
								vstr->m_value.insert(std::pair< string,void* >(skey,(void *)tmpvalue));
							}
						} 
						else
						{
							//��fpvalue���mapд��
							fpvalue.m_value.insert(std::pair< string,void* >(skey,(void *)tmpvalue));
							fpvalue.isZKHclear = false;
						}
						
						//printf("skey = %s,father acount = %d,fpvalue.getkey = %s,fpvalue.arrcount = %d\n",skey.c_str(),fpvalue.acount,fpvalue.getkey().c_str(),fpvalue.arrcount);
						break;
					}
				case '{':
					{

						if ( itype == 2)
						{
							delFlag =true;
							//Ѱ�ҳ���Ӧvector
							Analisyskeyandvalue(fpvalue,1,NULL);
						}else{
							//new  һ��map
						
							Analisyskeyandvalue(*tmpvalue,1,NULL);
							tmpvalue->valuetype = 1;
							tmpvalue->setkey(skey);
							//��fpvalue���mapд��
							fpvalue.m_value.insert(std::pair< string,void* >(skey,(void *)tmpvalue));
						}
						break;
					}
				default:
					{
						memset(valuetmp,0x00,sizeof(valuetmp));
						
						//�鿴ת���ַ����Ƿ���Ҫת��
						if (ZYFlag)
						{
							//���˵�\\ת���ַ�
							memcpy(valuetmp,tmp,(current_ - tmp -1));
							//��Ҫ����
							ZYFlag		=false;
							ZYPosition  =NULL;
						}else
						{
							memcpy(valuetmp,tmp,(current_ - tmp - 1));
						}
						
						string svalue(valuetmp);
						//���洫��������飬���key-value������map�У�������newһ��map�������ٴ���vector����
						if ( itype == 2 )
						{
							tmpvalue->setkey(skey);
							tmpvalue->setValue(svalue);
							tmpvalue->valuetype	=2;
						
							//printf("%s = %s,itype =%d,arrcount = %d\n",skey.c_str(),svalue.c_str(),itype,fpvalue.arrcount);
							Analisyskeyandvalue(fpvalue,2,NULL);
							fpvalue.m_value.insert(std::pair< string,void* >(skey,(void *)tmpvalue));

						//���洫�����map�����key-valueҪ����map����
						}else if ( itype == 1)
						{
							CValue *vstr=NULL;
							//vector ���� Ѱ�Ҷ�Ӧ��map����Ҳ�����newһ������
							if (fpvalue.v_valueobj.size() < fpvalue.arrcount)
							{
								vstr=new CValue();
								fpvalue.v_valueobj.push_back(vstr);
							}else{
								vstr= (CValue *)fpvalue.v_valueobj[fpvalue.arrcount-1];
							}
							tmpvalue->setkey(skey);
							tmpvalue->setValue(svalue);
							tmpvalue->valuetype =1;
							vstr->m_value.insert(std::pair< string,void* >(skey,(void *)tmpvalue));
							vstr->valuetype		=1;
							//����map��
							//printf("����ֵ%s = %s,itype =%d,arrcount = %d,father acount = %d,fpvalue.getkey = %s\n",skey.c_str(),svalue.c_str(),itype,fpvalue.arrcount,fpvalue.acount,fpvalue.getkey().c_str());
 							while(fpvalue.isZKHclear || fpvalue.isDKHclear)
 							{
 								Analisyskeyandvalue(fpvalue,1,NULL);
 							}

						//��ֵͨ
						}else{

							tmpvalue->setkey(skey);
							tmpvalue->setValue(svalue);
							tmpvalue->valuetype =0;
							fpvalue.m_value.insert(std::pair< string,void* >(skey,(void *)tmpvalue));
							//printf("��ֵͨ%s = %s,itype =%d,arrcount = %d,father acount = %d,fpvalue.getkey() = %s\n",skey.c_str(),svalue.c_str(),itype,fpvalue.arrcount,fpvalue.acount,fpvalue.getkey().c_str());
						}
						break;
					}
				}	
				break;
			}
		case ',':
			{
				delFlag =true;
				if ( !fpvalue.isDKHclear && !fpvalue.isZKHclear )
				{
					Analisyskeyandvalue(cvalue_,0,NULL);
				}else{	
					if(fpvalue.isDKHclear){
						Analisyskeyandvalue(fpvalue,1,v_value);
					}else{
						Analisyskeyandvalue(fpvalue,2,v_value);
					}
					
				}
				break;
			}
		case '}':
			{
				delFlag =true;
				fpvalue.isDKHclear = false;
				if ( !fpvalue.isDKHclear && !fpvalue.isZKHclear )
				{
					Analisyskeyandvalue(cvalue_,0,NULL);
				}else{	
					if(fpvalue.isDKHclear){
						Analisyskeyandvalue(fpvalue,1,v_value);
					}else{
						Analisyskeyandvalue(fpvalue,2,v_value);
					}
				}
				break;
				
			}
		case ']':
			{
				delFlag =true;
				fpvalue.isZKHclear  = false;
				break;
				
			}
		default:
			{
				fpvalue.isZKHclear  = false;
				fpvalue.isDKHclear  = false;
				delFlag =true;
				break;
			}
			
	}
	if (delFlag)
	{
		delete tmpvalue;
	}
	if ( !fpvalue.isDKHclear && !fpvalue.isDKHclear )
	{
		//Analisyskeyandvalue(cvalue_,0,NULL);
	}else{	
		if(fpvalue.isDKHclear){
			//Analisyskeyandvalue(fpvalue,1,v_value);
		}else{
			Analisyskeyandvalue(fpvalue,2,v_value);
		}
	}

}
void CJSonSimple::Start(){

	while (current_ != end_)
	{
		string str;
		Analisyskeyandvalue(cvalue_,0,NULL);
	}
}


string  CJSonSimple::IntToString(int strint)
{
	char tmp[100];
	memset(tmp,0x00,100);
	sprintf(tmp,"%d",strint);
	string stmp(tmp);
	return stmp;
}

//����ָ����key��ȡ sring
string  CJSonSimple::GetStringByKey(string skey)
{
	ValueString::iterator tmp=cvalue_.m_value.find(skey);
	if (tmp != cvalue_.m_value.end())
	{
		CValue *val	= (CValue *)tmp->second;
		if (val->valuetype == 0)
		{
			return val->getValue();
		}else if ( val->valuetype == 2 )
		{
			printf("v_valueobj = %d\n",val->v_valueobj.size());
			return "";
		}
	} 
	return "";
}


//����key��ȡ
CValue  *CJSonSimple::GetCValueByKey(string skey)
{
	CValue *val	=NULL;
	ValueString::iterator tmp=cvalue_.m_value.find(skey);
	if (tmp != cvalue_.m_value.end())
	{
		val	= (CValue *)tmp->second;
		return val;
	
	}
	return NULL;
	
}