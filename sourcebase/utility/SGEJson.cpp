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
			//是键值队
			break;
		}
		else if (c == ','){

			fpvalue.valuetype	= 0;
			//是键值对的结束
			break;
		}
		else if (c == '['){
			fpvalue.isZKHclear			= true;
			fpvalue.valuetype	= 2;
			//数组类型开始
			break;
		}
		else if (c == '{'){
			fpvalue.isDKHclear			= true;
			fpvalue.arrcount	= fpvalue.arrcount+1;
			fpvalue.valuetype   = 1;
			//哈希类型开始
			break;
		}
		else if (c == ']'){
			fpvalue.isZKHclear			= false;
			//数组类型结束
			break;
		}
		else if (c == '}'){
			fpvalue.isDKHclear			= false;
			fpvalue.valuetype   = 0;
			//哈希类型结束
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

//获取key值
void  CJSonSimple::Analisyskeyandvalue(CValue &fpvalue,int itype,void *v_value) {
	
	
	//获取键
	char temp[256];
	bool delFlag=false;			//false不要删除tmpvalue，true是要删除tmpvalue的
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
				//new  一个map写入vector
				Analisyskeyandvalue(fpvalue,1,NULL);		
				break;
			}	
		case '=':
			{
				//获取值
				tmp=current_;
				char m=readString(fpvalue);
				switch(m)
				{
				case '[':
					{
						acount++;
						//new 一个vector
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
							//往fpvalue里的map写入
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
							//寻找出对应vector
							Analisyskeyandvalue(fpvalue,1,NULL);
						}else{
							//new  一个map
						
							Analisyskeyandvalue(*tmpvalue,1,NULL);
							tmpvalue->valuetype = 1;
							tmpvalue->setkey(skey);
							//往fpvalue里的map写入
							fpvalue.m_value.insert(std::pair< string,void* >(skey,(void *)tmpvalue));
						}
						break;
					}
				default:
					{
						memset(valuetmp,0x00,sizeof(valuetmp));
						
						//查看转义字符，是否需要转义
						if (ZYFlag)
						{
							//过滤掉\\转义字符
							memcpy(valuetmp,tmp,(current_ - tmp -1));
							//需要清零
							ZYFlag		=false;
							ZYPosition  =NULL;
						}else
						{
							memcpy(valuetmp,tmp,(current_ - tmp - 1));
						}
						
						string svalue(valuetmp);
						//上面传入的是数组，这个key-value将存入map中，这里新new一个map出来，再存入vector里面
						if ( itype == 2 )
						{
							tmpvalue->setkey(skey);
							tmpvalue->setValue(svalue);
							tmpvalue->valuetype	=2;
						
							//printf("%s = %s,itype =%d,arrcount = %d\n",skey.c_str(),svalue.c_str(),itype,fpvalue.arrcount);
							Analisyskeyandvalue(fpvalue,2,NULL);
							fpvalue.m_value.insert(std::pair< string,void* >(skey,(void *)tmpvalue));

						//上面传入的是map，这个key-value要存入map里面
						}else if ( itype == 1)
						{
							CValue *vstr=NULL;
							//vector 里面 寻找对应的map如果找不到就new一个出来
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
							//存入map里
							//printf("特殊值%s = %s,itype =%d,arrcount = %d,father acount = %d,fpvalue.getkey = %s\n",skey.c_str(),svalue.c_str(),itype,fpvalue.arrcount,fpvalue.acount,fpvalue.getkey().c_str());
 							while(fpvalue.isZKHclear || fpvalue.isDKHclear)
 							{
 								Analisyskeyandvalue(fpvalue,1,NULL);
 							}

						//普通值
						}else{

							tmpvalue->setkey(skey);
							tmpvalue->setValue(svalue);
							tmpvalue->valuetype =0;
							fpvalue.m_value.insert(std::pair< string,void* >(skey,(void *)tmpvalue));
							//printf("普通值%s = %s,itype =%d,arrcount = %d,father acount = %d,fpvalue.getkey() = %s\n",skey.c_str(),svalue.c_str(),itype,fpvalue.arrcount,fpvalue.acount,fpvalue.getkey().c_str());
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

//根据指定的key获取 sring
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


//根据key获取
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