/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file CXML.cpp
///@brief实现了与XML实现有关的类
///@history 
///20051013	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CXML.h"
#include "XMLAction.h"

///类似性检查的严格程度，0表示最严格，越大越不严格
#define SIMILAR_CHECK_LEVEL 2

void genError(char *format, ...)
{
	char buffer[2048];
	va_list v;
	
	va_start(v,format);
	vsprintf(buffer,format,v);
	va_end(v);
	printf("--错误:%s\n",buffer);
	fflush(stdout);
}

void genWarning(char *format, ...)
{
	char buffer[2048];
	va_list v;
	
	va_start(v,format);
	vsprintf(buffer,format,v);
	va_end(v);
	printf("--警告:%s\n",buffer);
	fflush(stdout);
}

class CUniqueChecker: public CXMLEqualCheckerAction
{
public:
	CUniqueChecker(void)
	{
		mName="";
	}

	void start(char *name)
	{
		mName=strdup(name);
		clearAll();
	}

	virtual int findDuplication(char *string, char *originalString)
	{
		genError("%s重复：%s",mName,string);
		return 1;
	}
private:
	char *mName;
};

typedef struct
{
	char *group;
	char *key;
	char *value;
}	TDifferentItem;

class CDifferentCheck: public vector<TDifferentItem>
{
public:
	CDifferentCheck(char *groupPrompt, char *keyPrompt, char *valuePrompt);
	void add(char *group, char *key, char *value);
private:
	char *mGroupPrompt;
	char *mKeyPrompt;
	char *mValuePrompt;
};

CDifferentCheck::CDifferentCheck(char *groupPrompt, char *keyPrompt, char *valuePrompt)
{
	mGroupPrompt=groupPrompt;
	mKeyPrompt=keyPrompt;
	mValuePrompt=valuePrompt;
}

void CDifferentCheck::add(char *group, char *key, char *value)
{
	vector<TDifferentItem>::iterator it;
	int findSimilarKey=0;
	TDifferentItem item;
	
	for (it=begin();it<end();it++)
	{
		if (!strcmp(key,it->key))
		{
			findSimilarKey=1;
			if (strcmp(value,it->value))
			{
				genWarning("%s%s中%s%s的%s为%s，而%s%s中%s%s的%s为%s",
					mGroupPrompt,it->group,
					mKeyPrompt,it->key,
					mValuePrompt,it->value,
					mGroupPrompt,group,
					mKeyPrompt,key,
					mValuePrompt,value);
			}
		}
	}
	if (!findSimilarKey)
	{
		item.group=group;
		item.key=key;
		item.value=value;
		push_back(item);
	}
}

#define SAME_CHECK_LEVEL ((SIMILAR_CHECK_LEVEL)+3)
#define CONTAIN_CHECK_LEVEL ((SIMILAR_CHECK_LEVEL)+4)
#define PART_SAME_CHECK_LEVEL ((SIMILAR_CHECK_LEVEL)+5)

class CSimilarCheckItem: public vector<char *>
{
public:
	char *name;
	
	int isIn(char *name)
	{
		for (int i=0;i<size();i++)
		{
			if (!strcmp(name,at(i)))
			{
				return 1;
			}
		}
		return 0;
	}

	int isSimilar(CSimilarCheckItem *pItem)
	{
		//我们应该如何判定两个实体非常相似呢？
		//首先，我们计算两边分别在对方的列表中完全符合几个
		int sameCount1=0,sameCount2=0;
		int size1,size2;
		int i;
		
		size1=size();
		size2=pItem->size();
		for (i=0;i<size1;i++)
		{
			if (pItem->isIn(at(i)))
			{
				sameCount1++;
			}
		}
		for (i=0;i<size2;i++)
		{
			if (isIn(pItem->at(i)))
			{
				sameCount2++;
			}
		}
		
		//如果完全相同，而且数量至少有SAME_CHECK_LEVEL个，则需要报告
		if ((size1==sameCount1)&&(size2==sameCount2)&&(size1>=SAME_CHECK_LEVEL))
		{
			return 1;
		}
		
		//如果完全包含，而且数量至少有CONTAIN_CHECK_LEVEL个，则需要报告
		if ((size1==sameCount1)&&(size1>=CONTAIN_CHECK_LEVEL))
		{
			return 1;
		}
		
		if ((size2==sameCount2)&&(size2>=CONTAIN_CHECK_LEVEL))
		{
			return 1;
		}
		
		//如果包含的超过80%，而且数量至少有PART_SAME_CHECK_LEVEL个，则需要报告
		if ((size1*4/5<=sameCount1)&&(size1>=PART_SAME_CHECK_LEVEL))
		{
			return 1;
		}

		if ((size2*4/5<=sameCount2)&&(size2>=PART_SAME_CHECK_LEVEL))
		{
			return 1;
		}

		//否则就认为不相似
		return 0;
	}
};

class CSimilarCheck
{
public:
	void startAdd(char *name);
	void endAdd(void);
	void addItem(char *item);
private:
	vector<CSimilarCheckItem *> items;
};

void CSimilarCheck::startAdd(char *name)
{
	CSimilarCheckItem *pItem;
	
	pItem=new CSimilarCheckItem;
	pItem->name=name;
	items.push_back(pItem);
}

void CSimilarCheck::addItem(char *item)
{
	CSimilarCheckItem *pItem;
	
	pItem=items.at(items.size()-1);
	pItem->push_back(item);
}

void CSimilarCheck::endAdd(void)
{
	CSimilarCheckItem *pItem;
	
	pItem=items.at(items.size()-1);
	
	for (int i=0;i<items.size()-1;i++)
	{
		CSimilarCheckItem *pBeChecked;
		pBeChecked=items.at(i);
		if (pItem->isSimilar(pBeChecked))
		{
			genWarning("实体%s看上去与实体%s很象",pItem->name,pBeChecked->name);
		}
	}
}

typedef enum {ISDB, ISMDB, ISXTP, TRANSDB, TRANSDATATYPE, CHECK} TTransType;

CXMLDoc *pDoc,*pEntity,*pDatatype;
CXMLNode *pDocRoot=NULL;
CXMLNode *pEntityRoot=NULL;
CXMLNode *pAppEntityRoot=NULL;
CXMLNode *pDatatypeRoot=NULL;
TTransType curTransType;

CXMLNode *getRef(char *refName, int force=1)
{
	CXMLNode *defineNode;
	defineNode=pEntityRoot->findNode(XMLTag,"Entity","name",refName);
	if (defineNode!=NULL)
	{
		return defineNode;
	}
	if (pAppEntityRoot!=NULL)
	{
		defineNode=pAppEntityRoot->findNode(XMLTag,"Entity","name",refName);
		if (defineNode!=NULL)
		{
			return defineNode;
		}	
	}
	if (force)
	{
		printf("can not find ref %s\n",refName);
		fflush(stdout);
		exit(1);
	}
	else
	{
		return NULL;
	}
}

void copyEnum(CXMLNode *target, CXMLNode *source)
{
	int i;
	CXMLNodeList *pSourceList=source->getNodeList();
	
	for (i=0;i<pSourceList->size();i++)
	{
		CXMLNode *thisNode, *newNode;
		
		thisNode=pSourceList->at(i);
		newNode=new CXMLNode();
		newNode->setNodeType(XMLTag);
		newNode->setName("enumValue");
		
		char nameBuffer[100];
		sprintf(nameBuffer,"%s_%s",source->findProperty("prefix"),thisNode->findProperty("name"));
		newNode->addProperty("name",strdup(nameBuffer));
		newNode->addProperty("value",thisNode->findProperty("value"));
		newNode->addProperty("comment",thisNode->findProperty("label"));
		target->addNode(newNode);
	}
}

void copyDataType(CXMLNode *target)
{
	/*
	int i;
	CXMLNodeList *pSourceList;
	
	pSourceList=pDatatypeRoot->getNodeList();
	
	for (i=0;i<pSourceList->size();i++)
	{
		CXMLNode *thisNode, *newNode;
		char nameBuffer[100];
		
		thisNode=pSourceList->at(i);
		newNode=new CXMLNode();
		newNode->setNodeType(XMLTag);

		newNode->setName("DataType");
		sprintf(nameBuffer,"%sType",thisNode->findProperty("name"));
		newNode->addProperty("name",strdup(nameBuffer));
		newNode->addProperty("comment",thisNode->findProperty("label"));
		
		char *oldType=thisNode->findProperty("type");
		if (!strcmp(oldType,"Char"))
		{
			newNode->addProperty("type","Char");
		}
		else if (!strcmp(oldType,"String"))
		{
			newNode->addProperty("type","String");
			newNode->addProperty("length",thisNode->findProperty("length"));
		}
		else if (!strcmp(oldType,"Int"))
		{
			newNode->addProperty("type","Int");
		}
		else if (!strcmp(oldType,"Float"))
		{
			newNode->addProperty("type","Float");
		}
		else if (!strcmp(oldType,"Word"))
		{
			newNode->addProperty("type","Int");
		}
		else if (!strcmp(oldType,"EnumChar"))
		{
			newNode->addProperty("type","EnumChar");
			copyEnum(newNode,thisNode);
		}
		else if (!strcmp(oldType,"RangeInt"))
		{
			newNode->addProperty("type","RangeInt");
			newNode->addProperty("from",thisNode->findProperty("from"));
			newNode->addProperty("to",thisNode->findProperty("to"));
		}
		else if (!strcmp(oldType,"VString"))
		{
			newNode->addProperty("type","String");
			newNode->addProperty("length",thisNode->findProperty("length"));
		}
		else if (!strcmp(oldType,"Array"))
		{
			newNode->addProperty("type","String");
			newNode->addProperty("length",thisNode->findProperty("length"));
		}
		else if (!strcmp(oldType,"FixNumber"))
		{
			newNode->addProperty("type","Float");
			//newNode->addProperty("length",thisNode->findProperty("length"));
			//newNode->addProperty("precision",thisNode->findProperty("precision"));
		}
		else
		{
			printf("unknown type %s\n",oldType);
			exit(1);
		}

		target->addNode(newNode);
	}
	*/
	target->setNodeList(pDatatypeRoot->getNodeList());
}

int getDatabaseTypeLength(char *type)
{
	CXMLNode *pNode;
	
	pNode=pDatatypeRoot->findNode(XMLTag,NULL,"typename",type);
	if (pNode==NULL)
	{
		printf("can not find type %s\n",type);
		exit(1);
	}

	char *originalType;
	originalType=pNode->getName();
	if (!strcmp(originalType,"Char"))
	{
		return 1;
	}
	else if (!strcmp(originalType,"String"))
	{
		return atoi(pNode->findProperty("length"));
	}
	else if (!strcmp(originalType,"Int"))
	{
		return atoi(pNode->findProperty("length"));
	}
	else if (!strcmp(originalType,"Float"))
	{
		return atoi(pNode->findProperty("length"));
	}
	else if (!strcmp(originalType,"Word"))
	{
		return 5;
	}
	else if (!strcmp(originalType,"EnumChar"))
	{
		return 1;
	}
	else if (!strcmp(originalType,"RangeInt"))
	{
		return atoi(pNode->findProperty("length"));
	}
	else if (!strcmp(originalType,"VString"))
	{
		return atoi(pNode->findProperty("length"));
	}
	else if (!strcmp(originalType,"Array"))
	{
		char *element=pNode->findProperty("element");
		int elementLen=getDatabaseTypeLength(element);
		if (elementLen<=0)
		{
			printf("invalid base type of Array in %s\n",type);
			exit(1);
		}
		return atoi(pNode->findProperty("length"))*elementLen;
	}
	else if (!strcmp(originalType,"FixNumber"))
	{
		return atoi(pNode->findProperty("length"));
	}
	else if (!strcmp(originalType,"Raw"))
	{
		return -1;
	}
	else
	{
		printf("unknown base type %s\n",originalType);
		exit(1);
	}
	
	return 0;
}

int getDatabaseTypePrecision(char *type)
{
	CXMLNode *pNode;
	
	pNode=pDatatypeRoot->findNode(XMLTag,NULL,"typename",type);
	if (pNode==NULL)
	{
		printf("can not find type %s\n",type);
		exit(1);
	}

	char *originalType;
	originalType=pNode->getName();
	if (!strcmp(originalType,"Char"))
	{
		return 0;
	}
	else if (!strcmp(originalType,"String"))
	{
		return 0;
	}
	else if (!strcmp(originalType,"Int"))
	{
		return 0;
	}
	else if (!strcmp(originalType,"Float"))
	{
		return atoi(pNode->findProperty("precision"));
	}
	else if (!strcmp(originalType,"Word"))
	{
		return 0;
	}
	else if (!strcmp(originalType,"EnumChar"))
	{
		return 0;
	}
	else if (!strcmp(originalType,"RangeInt"))
	{
		return 0;
	}
	else if (!strcmp(originalType,"VString"))
	{
		return 0;
	}
	else if (!strcmp(originalType,"Array"))
	{
		return 0;
	}
	else if (!strcmp(originalType,"FixNumber"))
	{
		return atoi(pNode->findProperty("precision"));
	}
	else if (!strcmp(originalType,"Raw"))
	{
		return 0;
	}
	else
	{
		printf("unknown base type %s\n",originalType);
		exit(1);
	}
	
	return 0;
}

char *getDatabaseBaseType(char *type)
{
	CXMLNode *pNode;
	
	pNode=pDatatypeRoot->findNode(XMLTag,NULL,"typename",type);
	if (pNode==NULL)
	{
		printf("can not find type %s\n",type);
		exit(1);
	}

	return pNode->getName();
}

char *getDatabaseType(char *type)
{
	CXMLNode *pNode;
	char buffer[100];
	
	pNode=pDatatypeRoot->findNode(XMLTag,NULL,"typename",type);
	if (pNode==NULL)
	{
		printf("can not find type %s\n",type);
		exit(1);
	}

	char *originalType;
	originalType=pNode->getName();
	if (!strcmp(originalType,"Char"))
	{
		strcpy(buffer,"char(1)");
	}
	else if (!strcmp(originalType,"String"))
	{
		sprintf(buffer,"char(%d)",atoi(pNode->findProperty("length")));
	}
	else if (!strcmp(originalType,"Int"))
	{
		sprintf(buffer,"number(%d)",atoi(pNode->findProperty("length")));
	}
	else if (!strcmp(originalType,"Float"))
	{
		sprintf(buffer,"number(%d,%d)",atoi(pNode->findProperty("length")),
			atoi(pNode->findProperty("precision")));
	}
	else if (!strcmp(originalType,"Word"))
	{
		strcpy(buffer,"number(5)");
	}
	else if (!strcmp(originalType,"EnumChar"))
	{
		strcpy(buffer,"char(1)");
	}
	else if (!strcmp(originalType,"RangeInt"))
	{
		sprintf(buffer,"number(%d)",atoi(pNode->findProperty("length")));
	}
	else if (!strcmp(originalType,"VString"))
	{
		sprintf(buffer,"varchar2(%d)",atoi(pNode->findProperty("length")));
	}
	else if (!strcmp(originalType,"Array"))
	{
		char *element=pNode->findProperty("element");
		int elementLen=getDatabaseTypeLength(element);
		sprintf(buffer,"varchar(%d)",atoi(pNode->findProperty("length"))*elementLen);
	}
	else if (!strcmp(originalType,"FixNumber"))
	{
		sprintf(buffer,"number(%d,%d)",atoi(pNode->findProperty("length")),
			atoi(pNode->findProperty("precision")));
	}
	else if (!strcmp(originalType,"Raw"))
	{
		strcpy(buffer,"raw");
	}
	else
	{
		printf("unknown base type %s\n",originalType);
		exit(1);
	}
	
	return strdup(buffer);
}

void copyFields(CXMLNode *target, CXMLNode *source, int isKey=0)
{
	CXMLNodeList *pSourceList=source->getNodeList();
	int i;
	
	for (i=0;i<pSourceList->size();i++)
	{
		CXMLNode *thisNode,*newNode;
		char typeBuffer[100];
		char *ref;
		
		thisNode=pSourceList->at(i);
		if (!strcmp(thisNode->getName(),"Ref"))
		{
			ref=thisNode->findProperty("entity");
			if (ref!=NULL)
			{
				int newIsKey;
				
				if (isKey!=0)
				{
					newIsKey=isKey;
				}
				else
				{
					char *isKeyFlag;
					isKeyFlag=thisNode->findProperty("iskey");
					if (isKeyFlag==NULL)
					{
						newIsKey=0;
					}
					else if (!strcmp(isKeyFlag,"yes"))
					{
						newIsKey=1;
					}
					else if (!strcmp(isKeyFlag,"no"))
					{
						newIsKey=-1;
					}
					else
					{
						newIsKey=0;
					}
				}

				copyFields(target,getRef(ref), newIsKey);
			}
		}
		else if (!strcmp(thisNode->getName(),"Field"))
		{
			newNode=new CXMLNode();
			newNode->setNodeType(XMLTag);
			if (curTransType==ISMDB)
			{
				newNode->setName("field");
				newNode->addProperty("name",thisNode->findProperty("name"));
				sprintf(typeBuffer,"C%sType",thisNode->findProperty("type"));
				newNode->addProperty("type",strdup(typeBuffer));
				newNode->addProperty("comment",thisNode->findProperty("label"));
			}
			else if (curTransType==ISXTP)
			{
				newNode->setName("item");
				newNode->addProperty("name",thisNode->findProperty("name"));
				sprintf(typeBuffer,"C%sType",thisNode->findProperty("type"));
				newNode->addProperty("type",strdup(typeBuffer));
				newNode->addProperty("description",thisNode->findProperty("label"));
			}
			else if (curTransType==ISDB)
			{
				char *originalType=thisNode->findProperty("type");
				newNode->setName("Column");
				newNode->addProperty("name",thisNode->findProperty("name"));
				newNode->addProperty("type",getDatabaseType(originalType));
				newNode->addProperty("label",thisNode->findProperty("label"));
				if (thisNode->findProperty("default")!=NULL)
				{
					newNode->addProperty("default",thisNode->findProperty("default"));
				}
				
				if (thisNode->findProperty("description")!=NULL)
				{
					newNode->addProperty("description",thisNode->findProperty("description"));
				}
				if (thisNode->findProperty("notnull")!=NULL)
				{
					newNode->addProperty("notnull",thisNode->findProperty("notnull"));
				}
				switch (isKey)
				{
				case 1:
					newNode->addProperty("iskey","yes");
				case 0:
					if (thisNode->findProperty("iskey")!=NULL)
					{
						newNode->addProperty("iskey",thisNode->findProperty("iskey"));
					}
				}
				newNode->addProperty("originaltype",originalType);
				newNode->addProperty("basetype",getDatabaseBaseType(originalType));
				char buffer[100];
				sprintf(buffer,"%d",getDatabaseTypeLength(originalType));
				newNode->addProperty("length",strdup(buffer));
				sprintf(buffer,"%d",getDatabaseTypePrecision(originalType));
				newNode->addProperty("precision",strdup(buffer));
			}
			target->addNode(newNode);
		}
		else
		{
			printf("unexpected tag %s\n",thisNode->getName());
		}
	}
}

void trans(CXMLNode *pNode)
{
	int i;
	
	//如果不是tag，就不处理了
	if (pNode->getNodeType()!=XMLTag)
	{
		return;
	}

	//先递归叫用子节点
	CXMLNodeList *pSons;
	pSons=pNode->getNodeList();
	if (pSons!=NULL)
	{
		for (i=0;i<pSons->size();i++)
		{
			trans(pSons->at(i));
		}
	}

	//如果是类型，则拷贝pDatatypeRoot
	if (!strcmp(pNode->getName(),"types"))
	{
		copyDataType(pNode);
		return;
	}

	//如果是实体引用，则拷贝相应的实体定义
	if (curTransType==ISMDB)
	{
		if (!strcmp(pNode->getName(),"fields"))
		{
			char *ref=pNode->findProperty("ref");
			if (ref!=NULL)
			{
				copyFields(pNode,getRef(ref));
				pNode->removeProperty("ref");
				return;
			}
		}
		if (!strcmp(pNode->getName(),"field"))
		{
			char typeBuffer[100];
			sprintf(typeBuffer,"C%sType",pNode->findProperty("type"));
			pNode->replaceProperty("type",strdup(typeBuffer));
		}
	}
	if (curTransType==ISXTP)
	{
		if (!strcmp(pNode->getName(),"fieldDefine"))
		{
			char *ref=pNode->findProperty("ref");
			if (ref!=NULL)
			{
				copyFields(pNode,getRef(ref));
				pNode->removeProperty("ref");
				return;
			}
		}
		if (!strcmp(pNode->getName(),"item"))
		{
			char typeBuffer[100];
			sprintf(typeBuffer,"C%sType",pNode->findProperty("type"));
			pNode->replaceProperty("type",strdup(typeBuffer));
		}
	}
	if (curTransType==ISDB)
	{
		if (!strcmp(pNode->getName(),"Columns"))
		{
			char *ref=pNode->findProperty("ref");
			if (ref!=NULL)
			{
				copyFields(pNode,getRef(ref));
				pNode->removeProperty("ref");
				return;
			}
		}
	}
	if (curTransType==TRANSDB)
	{
		if (!strcmp(pNode->getName(),"table"))
		{
			char *ref=pNode->findProperty("ref");

			CXMLNode *newNode=new CXMLNode();
			newNode->setNodeType(XMLTag);
			newNode->setName("Columns");
			newNode->addProperty("ref",ref);
			pNode->addNode(newNode);
			newNode=new CXMLNode();
			newNode->setNodeType(XMLTag);
			newNode->setName("Index");
			pNode->addNode(newNode);

			pNode->removeProperty("ref");
		}
	}
	if (curTransType==TRANSDATATYPE)
	{
		if (!strcmp(pNode->getName(),"DataType"))
		{
			pNode->setName(pNode->findProperty("type"));
			pNode->removeProperty("type");
		}
	}
	/*
	if (((curTransType==ISMDB)&&!strcmp(pNode->getName(),"fields"))||
		((curTransType=ISXTP)&&!strcmp(pNode->getName(),"fieldDefine")))
	{
		printf("ref\n");
		char *ref=pNode->findProperty("ref");
		if (ref!=NULL)
		{
			copyFields(pNode,getRef(ref));
			return;
		}
	}
	*/
}

int validNameChar(char ch)
{
	if (isalnum(ch))
	{
		return 1;
	}
	if (ch=='_')
	{
		return 1;
	}
	return 0;
}

int validName(char *name)
{
	for (char *p=name; *p!='\0'; p++)
	{
		if (!validNameChar(*p))
		{
			return 0;
		}
	}
	return 1;
}

int checkUniqueEnum(CXMLNode *pNode, void *parameter)
{
	CUniqueChecker nameChecker,valueChecker;
	char *typeName=pNode->findProperty("typename");

	char buffer[100];
			
	sprintf(buffer,"%s中的枚举值名称",typeName);
	nameChecker.start(buffer);
	sprintf(buffer,"%s中的枚举值取值",typeName);
	valueChecker.start(buffer);

	if (pNode->getNodeList()==NULL)
	{
		genWarning("%s中没有定义枚举值",typeName);
		return 1;
	}

	pNode->XAction("/@name",&nameChecker);
	pNode->XAction("/@value",&valueChecker);
	
	return 1;
}

int tokenCheck(char *value, void *parameter)
{
	if ((value==NULL) || !validName(value))
	{
		genError("不合法的%s%s",parameter,value);
	}
	return 1;
}

CXMLNode *findDataType(char *type)
{
	CXMLNode *pNode;
	
	pNode=pDatatypeRoot->findNode(XMLTag,NULL,"typename",type);
	return pNode;
}


int checkArray(CXMLNode *pNode, void *parameter)
{
	CXMLNode *pType;
	
	pType=findDataType(pNode->findProperty("element"));
	if (pType==NULL)
	{
		genError("数组类型%s的元素类型%s没有定义",pNode->findProperty("typename"),
			pNode->findProperty("element"));
	}
	else
	{
		pType->setProperty("used","yes");
	}
	return 1;
}

int usageCheck(CXMLNode *pNode, void *parameter)
{
	if (!pNode->findProperty("used"))
	{
		genWarning("类型%s定义了，但是没有被使用",pNode->findProperty("typename"));
	}
	return 1;
}

void checkDataType(void)
{
	CUniqueChecker checker;
	
	//检查类型名称是否重复
	checker.start("数据类型");
	pDatatypeRoot->XAction("/@typename",&checker);
	
	//检查类型前缀是否重复
	checker.start("枚举类型前缀");
	pDatatypeRoot->XAction("/EnumChar/@prefix",&checker);

	//检查枚举值的名称和取值是否重复
	pDatatypeRoot->groupAction(checkUniqueEnum,NULL,XMLTag,"EnumChar");
	
	//检查所有名称字符合法性
	pDatatypeRoot->groupAction("typename",tokenCheck,(void *)"类型名称");
	
	//将所有的数组类型
	pDatatypeRoot->groupAction(checkArray,NULL,XMLTag,"Array");
	
	//检查各个类型是否都被使用过
	pDatatypeRoot->groupAction(usageCheck);
}

int refAddChecker(char *value, void *parameter);

void addChecker(CXMLNode *pNode, void *parameter)
{
	CXMLNodeList *fields;

	fields=pNode->getNodeList();
	if (fields==NULL)
	{
		genWarning("实体%s的内容为空",pNode->findProperty("name"));
		return;
	}
	pNode->XAction("/Field/@name",(CXMLAction *)parameter);
	pNode->groupAction("entity",refAddChecker,parameter,XMLTag,"Ref");
}

int refAddChecker(char *name, void *parameter)
{
	CXMLNode *pNode=getRef(name,0);
	
	if (pNode==NULL)
	{
		genError("无法找到实体%s的定义",name);
		return 1;
	}
	
	addChecker(pNode, parameter);

	return 1;
}

void addWord(vector<char *> *result, char *start, char *end)
{
	char buffer[100];
	int len=end-start;
	memcpy(buffer,start,len);
	buffer[len]='\0';
	result->push_back(strdup(buffer));
}

vector<char *> *splitWords(char *string)
{
	char *start,*end;
	vector<char *> *result=new vector<char *>;
	
	start=string;
	for (end=start+1;*end!='\0';end++)
	{
		if (isupper(*end))
		{
			addWord(result,start,end);
			start=end;
		}
	}
	addWord(result,start,end);
	/*
	printf("%s split to:",string);
	for (int i=0;i<result->size();i++)
	{
		printf("%s ",result->at(i));
	}
	printf("\n");
	*/
	return result;
}

int contain(vector<char *> *stringList1, vector<char *> *stringList2)
{
	int i,j;
	
	for (i=0;i<stringList1->size();i++)
	{
		char *string1=stringList1->at(i);
		for (j=0;j<stringList2->size();j++)
		{
			char *string2=stringList2->at(j);
			if (!strcmp(string1,string2))
			{
				break;
			}
		}
		if (j==stringList2->size())
		{
			return 0;
		}
	}
	return 1;
}

int similarName(char *name, char *type)
{
	vector<char *> *pNameWords=splitWords(name);
	vector<char *> *pTypeWords=splitWords(type);
	int result;

	if (contain(pNameWords,pTypeWords)||contain(pTypeWords,pNameWords))
	{
		result=1;
	}
	else
	{
		result=0;
	}
	
	delete pNameWords;
	delete pTypeWords;
	
	return result;

}

typedef struct
{
	char *message;
	char *type;
}	TSimilarCheck;

int checkSimilarString(char *value, void *parameter)
{
	TSimilarCheck *pSimilarCheck=(TSimilarCheck *)parameter;
	if (similarName(value,pSimilarCheck->type))
	{
		genWarning("%s%s",pSimilarCheck->message,value);
	}
	return 1;
}

int checkSimilarType(CXMLNode *pNode, void *parameter)
{
	char *fieldName=pNode->findProperty("name");
	char *type=pNode->findProperty("type");
	
	if (similarName(fieldName,type))
	{
		return 1;
	}
	
	char buffer[200];
	sprintf(buffer,"实体%s中的字段%s类型为%s，可能应该为",(char *)parameter,fieldName,type);
	
	TSimilarCheck similarCheck;
	similarCheck.message=buffer;
	similarCheck.type=fieldName;

	pDatatypeRoot->groupAction("typename",checkSimilarString,&similarCheck);
	return 1;
}

void checkTypeLabel(char *entityName, char *fieldName, char *label)
{
	CXMLNode *pNode;
	
	pNode=findDataType(fieldName);
	if (pNode==NULL)
	{
		return;
	}
	if (strcmp(label,pNode->findProperty("label")))
	{
		genWarning("实体%s中的字段%s被说明成\"%s\"，但是数据类型文件中被说明成\"%s\"",
			entityName,fieldName,label,
			pNode->findProperty("label"));
	}
}

int checkDuplicateField(CXMLNode *pNode, void *parameter)
{
	CUniqueChecker checker;
	char buffer[100];

	sprintf(buffer,"实体%s的域名",pNode->findProperty("name"));
	checker.start(buffer);
	addChecker(pNode, &checker);
	return 1;
}

int checkTypeDefinition(CXMLNode *pNode, void *parameter)
{
	CXMLNode *pType;
	
	pType=findDataType(pNode->findProperty("type"));
	if (pType==NULL)
	{
		genError("%s%s的类型%s没有定义",
			parameter,
			pNode->findProperty("name"),
			pNode->findProperty("type"));
	}
	else
	{
		pType->setProperty("used","yes");
	}
	return 1;
}

int checkEntityTypeDefinition(CXMLNode *pNode, void *parameter)
{
	char buffer[100];
	
	sprintf(buffer,"实体%s中的字段",pNode->findProperty("name"));
	pNode->groupAction(checkTypeDefinition,buffer,XMLTag,"Field");
	return 1;
}

int checkEntitySimilarTypes(CXMLNode *pNode, void *parameter)
{
	pNode->groupAction(checkSimilarType,pNode->findProperty("name"),XMLTag,"Field");
	return 1;
}

int checkIdenticalLabel(CXMLNode *pNode, void *parameter)
{
	if (!strcmp(pNode->findProperty("name"),pNode->findProperty("type")))
	{
		checkTypeLabel((char *)parameter,pNode->findProperty("name"),
			pNode->findProperty("label"));
	}
	return 1;
}

int checkEntityIdenticalLabel(CXMLNode *pNode, void *parameter)
{
	pNode->groupAction(checkIdenticalLabel,pNode->findProperty("name"),XMLTag,"Field");
	return 1;
}

CDifferentCheck typeCheck("实体","域","类型");
CDifferentCheck labelCheck("实体","域","说明");

int checkIdenticalField(CXMLNode *pNode,void *parameter)
{
	typeCheck.add((char *)parameter,pNode->findProperty("name"),pNode->findProperty("type"));
	labelCheck.add((char *)parameter,pNode->findProperty("name"),pNode->findProperty("label"));
	return 1;
}

int checkEntityIdenticalField(CXMLNode *pNode, void *parameter)
{
	pNode->groupAction(checkIdenticalField,pNode->findProperty("name"),XMLTag,"Field");
	return 1;
}

CSimilarCheck entitySimilarCheck;

int similarAddField(char *value, void *parameter)
{
	entitySimilarCheck.addItem(value);
	return 1;
}

int checkEntitySimilar(CXMLNode *pNode, void *parameter)
{
	entitySimilarCheck.startAdd(pNode->findProperty("name"));
	pNode->groupAction("name",similarAddField,NULL,XMLTag,"Field");
	pNode->groupAction("entity",similarAddField,NULL,XMLTag,"Ref");
	entitySimilarCheck.endAdd();
	return 1;
}

void entityBaseChecks(CXMLNode *pEntity)
{
	CUniqueChecker checker;
	
	if (pEntity==NULL)
	{
		return;
	}

	//检查所有实体名称字符合法性
	pEntity->groupAction("name",tokenCheck,(void *)"实体名称");
	
	//检查实体名称是否重复
	checker.start("实体名称");
	pEntity->XAction("/@name",&checker);

	//检查各个实体中的域名是否重复
	pEntity->groupAction(checkDuplicateField);

	//检查各个域的类型是否有定义
	pEntity->groupAction(checkEntityTypeDefinition);
	
	//检查各个域的名称，是否类似于其他类型
	pEntity->groupAction(checkEntitySimilarTypes);
	
	//名称和类型同名的字段，注释应当与类型定义中的相同
	pEntity->groupAction(checkEntityIdenticalLabel);
	
	//检查同名域的类型和说明是否相同
	pEntity->groupAction(checkEntityIdenticalField);
	
	//检查类似的entity
	pEntity->groupAction(checkEntitySimilar);
}

int checkReusedEntityName(CXMLNode *pNode, void *parameter)
{
	if (pEntityRoot->findNode(XMLTag, "Entity", "name", pNode->findProperty("name")))
	{
		genWarning("实体%s已经在实体文件中定义过",pNode->findProperty("name"));
	}
	return 1;
}

void checkDefinition(CXMLNode *beChecked, char *checkPropertyName, CXMLNode *definition, char *definePropertyName, char *msg, char *secondCheckPropertyName=NULL)
{
	CXMLNodeList::iterator it;

	if (beChecked->getNodeList()==NULL)
	{
		return;
	}
	for (it=beChecked->getNodeList()->begin();it<beChecked->getNodeList()->end();it++)
	{
		char *checkProperty;
		checkProperty=(*it)->findProperty(checkPropertyName);
		if ((checkProperty==NULL)&&(secondCheckPropertyName!=NULL))
		{
			if (!strcmp(secondCheckPropertyName,"allowNull"))
			{
				continue;
			}
			checkProperty=(*it)->findProperty(secondCheckPropertyName);
		}
		
		if (checkProperty==NULL)
		{
			genError("%s没有定义",msg);
			continue;
		}

		if (definition->findNode(XMLTag,NULL,definePropertyName,checkProperty)==NULL)			
		{
			genError("%s%s没有定义",msg,checkProperty);
		}
	}
}

void checkDefinition(CXMLNode *beChecked, char *checkPropertyName, CXMLNode *definition, char *definePropertyName, char *msg, char *itemNameProperty, char *keyPrompt)
{
	CXMLNodeList::iterator it;
	
	if (beChecked->getNodeList()==NULL)
	{
		return;
	}
	for (it=beChecked->getNodeList()->begin();it<beChecked->getNodeList()->end();it++)
	{
		char *itemName=(*it)->findProperty(itemNameProperty);
		char buffer[100];
		
		sprintf(buffer,"%s%s中的%s",msg,itemName,keyPrompt);
		checkDefinition(*it, checkPropertyName, definition,definePropertyName, buffer);
	}
}

int validNumber(char *s)
{
	while (*s!='\0')
	{
		if (!isdigit(*s))
		{
			return 0;
		}
		s++;
	}
	return 1;
}

int subNodeList(CXMLNode *largeNode, CXMLNodeList *smallNode)
{
	CXMLNodeList::iterator it;
	
	for (it=smallNode->begin();it<smallNode->end();it++)
	{
		if (largeNode->findNode(XMLTag,NULL,"name",(*it)->findProperty("name"))==NULL)
		{
			return 0;
		}
	}
	return 1;
}

int isSum(CXMLNode *sum, CXMLNode *item1, CXMLNode *item2)
{
	/*
	if (sum!=NULL)
	{
		sum->write(stdout,0);
	}
	if (item1!=NULL)
	{
		item1->write(stdout,0);
	}
	if (item2!=NULL)
	{
		item2->write(stdout,0);
	}
	*/
	int sumCount, item1Count, item2Count;
	if ((sum==NULL)||(sum->getNodeList()==NULL))
	{
		sumCount=0;
	}
	else
	{
		sumCount=sum->getNodeList()->size();
	}
	if ((item1==NULL)||(item1->getNodeList()==NULL))
	{
		item1Count=0;
	}
	else
	{
		item1Count=item1->getNodeList()->size();
	}
	if ((item2==NULL)||(item2->getNodeList()==NULL))
	{
		item2Count=0;
	}
	else
	{
		item2Count=item2->getNodeList()->size();
	}
	if (sumCount!=item1Count+item2Count)
	{
		return 0;
	}
	if (sumCount==0)
	{
		return 1;
	}
	if (item1Count!=0)
	{
		if (!subNodeList(sum,item1->getNodeList()))
		{
			return 0;
		}
	}
	if (item2Count!=0)
	{
		if (!subNodeList(sum,item2->getNodeList()))
		{
			return 0;
		}
	}
	return 1;
}

void checkEntity(void)
{
	entityBaseChecks(pEntityRoot);
}

int checkTable(CXMLNode *pNode, void *parameter)
{
	char buffer[100];
	CUniqueChecker checker;
	char *tableName=pNode->findProperty("name");

	//表内字段名不重复
	CXMLNode *columns=pNode->findNode(XMLTag,"Columns");
	sprintf(buffer,"%s%s中的字段",(char *)parameter,tableName);
	checker.start(buffer);
	columns->XAction("/@name",&checker);

	//表内索引名不重复
	CXMLNode *index=pNode->findNode(XMLTag,"Index");
	sprintf(buffer,"%s%s中的索引",(char *)parameter,tableName);
	checker.start(buffer);
	index->XAction("/@name",&checker);

	//表是否有主键
	if (columns->findNode(XMLTag,"Column","iskey","yes")==NULL)
	{
		genWarning("%s%s没有主键",parameter,tableName);
	}

	//索引字段是否都有说明
	sprintf(buffer,"%s%s中的索引",(char *)parameter,tableName);
	checkDefinition(index, "name", columns, "name", buffer, "name", "键");
	return 1;
}

int checkTableGroup(CXMLNode *pNode, void *parameter)
{
	CUniqueChecker checker;
	char buffer[100];

	//同一个table group中的表名不重复
	sprintf(buffer,"表组%s中的表",pNode->findProperty("group"));
	checker.start(buffer);
	pNode->XAction("/@name",&checker);
	
	//检查各个表
	pNode->groupAction(checkTable,buffer);	

	return 1;
}

int checkCheckTable(CXMLNode *pNode, void *parameter)
{
	CXMLNode *pTableGroup,*pTable,*pColumn;
	char *groupName, *tableName;
	
	groupName=pNode->findProperty("group");
	tableName=pNode->findProperty("name");
	
	pTableGroup=pDocRoot->findNode(XMLTag,"tableGroups")->
		findNode(XMLTag,"tables","group",groupName);
	if (pTableGroup==NULL)
	{
		genError("检查表中的表组%s找不到",groupName);
	}
	
	pTable=pTableGroup->findNode(XMLTag,"table","name",tableName);
	if (pTable==NULL)
	{
		genError("检查表中的表名%s找不到",tableName);
	}
	
	char buffer[100];
	sprintf(buffer,"检查表，表组%s表%s中的检查字段",groupName,tableName);
	pColumn=pTable->findNode(XMLTag,"Columns");
	checkDefinition(pNode,"fieldname",pColumn,"name",buffer,"name");
	
	return 1;
}

void checkDB(void)
{
	CXMLNode *pEntity,*pTableGroup,*pCheckFields,*pCheckTables,*pSchema,*pCheckRight;
	CUniqueChecker checker;
	
	pTableGroup=pDocRoot->findNode(XMLTag,"tableGroups");
	pEntity=pDocRoot->findNode(XMLTag,"entities");
	pSchema=pDocRoot->findNode(XMLTag,"schemas");
	pCheckRight=pDocRoot->findNode(XMLTag,"checkrights");
	if (pCheckRight!=NULL)
	{
		pCheckFields=pDocRoot->findNode(XMLTag,"checkrights")->findNode(XMLTag,"checkfields");
		pCheckTables=pDocRoot->findNode(XMLTag,"checkrights")->findNode(XMLTag,"checktables");
	}

	entityBaseChecks(pEntity);

	//检查实体名称是否与UFEntity重复
	pEntity->groupAction(checkReusedEntityName);

	if (pTableGroup->getNodeList()==NULL)
	{
		genError("没有定义任何表组");
		return;
	}

	//table group名不重复
	checker.start("表组名称");
	pTableGroup->XAction("/@group",&checker);

	//检查各个表组
	pTableGroup->groupAction(checkTableGroup);
	
	//schema名不重复
	checker.start("schema名称");
	pSchema->XAction("/@name",&checker);
	
	//检查各个schema中的表组名有定义
	checkDefinition(pSchema,"name",pTableGroup,"group","schema ","name","表组");
	
	//检查各个表组是否在schema中有使用
	
	if (pCheckRight!=NULL)
	{
		//检查权限检查字段是否有定义
		checkDefinition(pCheckFields,"name",pDatatypeRoot,"typename","检查字段");
		
		//检查各个表检查字段
		pCheckTables->groupAction(checkCheckTable);
	}
}

int checkMDBSearch(CXMLNode *pSearch, void *parameter)
{
	CXMLNode *pTable=(CXMLNode *)parameter;
	CXMLNode *index=pTable->findNode(XMLTag,"index");
	char *indexName=pSearch->findProperty("indexName");

	//检查是否没有定义索引
	if (indexName==NULL)
	{
		/*
		genWarning("表%s中的检索%s没有使用索引",
			pTable->findProperty("name"),
			pSearch->findProperty("name"));
		*/
		return 1;
	}

	//search中的参数和default合起来是否等于index中的定义
	CXMLNode *parameters=pSearch->findNode(XMLTag,"parameter");
	CXMLNode *defaults=pSearch->findNode(XMLTag,"default");
	CXMLNode *keys=index->findNode(XMLTag,"defineIndex","name",indexName);
	if (!isSum(keys,parameters,defaults))
	{
		genError("表%s中的检索%s，所定义参数与缺省值与索引定义不匹配",
			pTable->findProperty("name"),
			pSearch->findProperty("name"));
	}
	return 1;
}

int checkMDBIndex(CXMLNode *pIndex, void *parameter)
{
	CXMLNode *pTable=(CXMLNode *)parameter;
	CXMLNode *fields=pTable->findNode(XMLTag,"fields");
	CUniqueChecker checker;
	char buffer[100];

	//所有的索引中的字段是否有重复
	sprintf(buffer,"表%s中的索引%s中的键",pTable->findProperty("name"),pIndex->findProperty("name"));
	checker.start(buffer);
	pIndex->XAction("name",&checker);
			
	//所有的索引中的字段是否有定义
	sprintf(buffer,"表%s中索引%s中的键",pTable->findProperty("name"),pIndex->findProperty("name"));
	checkDefinition(pIndex, "name", fields, "name", buffer);
	
	return 1;
}

int checkMDBTable(CXMLNode *pTable, void *parameter)
{
	CXMLNode *fields,*foreigns, *index, *search;
	CUniqueChecker checker;
	char buffer[100];

	fields=pTable->findNode(XMLTag,"fields");
	foreigns=pTable->findNode(XMLTag,"foreigns");
	index=pTable->findNode(XMLTag,"index");
	search=pTable->findNode(XMLTag,"search");
		
	//表内字段名不重复
	sprintf(buffer,"表%s中的字段",pTable->findProperty("name"));
	checker.start(buffer);
	fields->XAction("/@name",&checker);

	//表内外键名不重复
	sprintf(buffer,"表%s中的外键",pTable->findProperty("name"));
	checker.start(buffer);
	foreigns->XAction("/@name",&checker);

	//表内索引名不重复 
	sprintf(buffer,"表%s中的索引",pTable->findProperty("name"));
	checker.start(buffer);
	index->XAction("/@name",&checker);

	//表内检索不重复
	sprintf(buffer,"表%s中的检索",pTable->findProperty("name"));
	checker.start(buffer);
	search->XAction("name",&checker);
	
	//检查索引
	index->groupAction(checkMDBIndex,pTable);

	//search是否使用了索引，而且所需的索引都已经建立
	sprintf(buffer,"表%s中检索使用的索引",pTable->findProperty("name"));
	checkDefinition(search,"indexName",index,"name",buffer,"allowNull");
		
	//所有的索引都曾经被使用

	//search中的参数和default合起来是否等于index中的定义
	search->groupAction(checkMDBSearch,pTable);
		
	//foreign的键都有定义
	sprintf(buffer,"表%s中的外键",pTable->findProperty("name"));
	checkDefinition(foreigns,"key",fields,"name",buffer);

	//foreign指向的表定义是否存在
	sprintf(buffer,"表%s中的外键表",pTable->findProperty("name"));
	checkDefinition(foreigns,"factory",pDocRoot->findNode(XMLTag,"tables"),"name",buffer);
	
	return 1;
}

void checkMDB(void)
{
	CXMLNode *pTables,*pEntity;
	CUniqueChecker checker;

	pTables=pDocRoot->findNode(XMLTag,"tables");
	pEntity=pDocRoot->findNode(XMLTag, "entities");

	entityBaseChecks(pEntity);

	//检查实体名称是否与UFEntity重复
	pEntity->groupAction(checkReusedEntityName);

	//检查是否有表定义
	if (pTables->getNodeList()==NULL)
	{
		genError("没有定义任何表");
		return;
	}

	//表名无重复
	checker.start("表名称");
	pTables->XAction("/@name",&checker);
	
	//检查表
	pTables->groupAction(checkMDBTable);
}

int checkXTPType(CXMLNode *pNode, void *parameter)
{
	CXMLNode *pType;
	
	char *finalType,originalType[100];
	
	finalType=pNode->findProperty("type");
	
	strcpy(originalType,finalType+1);
	originalType[strlen(originalType)-4]='\0';

	pType=findDataType(originalType);

	if (pType==NULL)
	{
		genError("%s%s的类型%s没有定义",parameter,pNode->findProperty("name"),
			pNode->findProperty("type"));
	}
	else
	{
		pType->setProperty("used","yes");
	}

	return 1;
}

int checkXTPField(CXMLNode *pNode, void *parameter)
{
	CUniqueChecker checker;
	char buffer[100];

	//XTP域名item名不重复
	sprintf(buffer,"域%s中的字段",pNode->findProperty("name"));
	checker.start(buffer);
	pNode->XAction("/@name",&checker);
	
	//检查类型是否被定义
	pNode->groupAction(checkXTPType,buffer);
	
	return 1;
}

int checkOccur(CXMLNode *pField, void *parameter)
{
	char *minOccur,*maxOccur;
			
	minOccur=pField->findProperty("minOccur");
	maxOccur=pField->findProperty("maxOccur");
			
	if (!validNumber(minOccur))
	{
		genError("%s%s的minOccur是%s",
			parameter,
			pField->findProperty("name"),
			minOccur);
	}
	if (!validNumber(maxOccur)&&strcmp(maxOccur,"*"))
	{
		genError("%s%s的maxOccur是%s",
			parameter,
			pField->findProperty("name"),
			maxOccur);
	}
	if (strcmp(maxOccur,"*"))
	{
		if (atoi(minOccur)>atoi(maxOccur))
		{
			genError("%s%s的minOccur比maxOccur大",
				parameter,
				pField->findProperty("name"));
		}
	}
	return 1;
}

int checkXTPPackage(CXMLNode *pPackage, void *parameter)
{
	CUniqueChecker checker;
	char buffer[100];

	//检查空包
	if (pPackage->getNodeList()==NULL)
	{
		genError("报文%s中没有定义任何域",pPackage->findProperty("name"));
	}
		
	//检查重复的域
	sprintf(buffer,"包%s中的域",pPackage->findProperty("name"));
	checker.start(buffer);
	pPackage->XAction("/@name",&checker);
	
	//检查minOccur是否大于等于0，maxOccur是否大于0或者为*
	pPackage->groupAction(checkOccur,buffer);
	
	return 1;
}

void checkXTP(void)
{
	CXMLNode *pPackages,*pFields,*pEntity;
	CUniqueChecker checker;

	pPackages=pDocRoot->findNode(XMLTag,"packages");
	pFields=pDocRoot->findNode(XMLTag,"fields");
	pEntity=pDocRoot->findNode(XMLTag, "entities");

	entityBaseChecks(pEntity);

	//检查实体名称是否与UFEntity重复
	pEntity->groupAction(checkReusedEntityName);

	//package名不重复
	checker.start("包");
	pPackages->XAction("name",&checker);
	
	//tid无重复
	checker.start("tid");
	pPackages->XAction("name",&checker);

	//XTP域名不重复
	checker.start("域");
	pFields->XAction("name",&checker);
	
	//fid无重复
	checker.start("fid");
	pFields->XAction("fid",&checker);

	if (pPackages->getNodeList()==NULL)
	{
		genError("没有定义任何报文");
		return;
	}

	if (pFields->getNodeList()==NULL)
	{
		genError("没有定义任何域");
		return;
	}

	//检查各个域
	pFields->groupAction(checkXTPField);

	//各个package中的XTP域是否都有定义
	checkDefinition(pPackages,"name",pFields,"name","包","name","域");

	//检查各个包
	pPackages->groupAction(checkXTPPackage);
}

CXMLNode *makeCopyItem(CXMLNode *pMDBField, CXMLNode *pXTPItem)
{
	char *MDBName, *XTPName;
	char *MDBType, *XTPType;
	
	MDBName=pMDBField->findProperty("name");
	XTPName=pXTPItem->findProperty("name");
	MDBType=pMDBField->findProperty("type");
	XTPType=pXTPItem->findProperty("type");
	
	if (strcmp(MDBName,XTPName))
	{
		return NULL;
	}
	if (strcmp(MDBType,XTPType))
	{
		return NULL;
	}
	
	return pXTPItem;
}

CXMLNode *makeCopyNode(CXMLNode *pMDBTable, CXMLNode *pXTPField)
{
	CXMLNode *pCopyNode;
	
	pCopyNode=new CXMLNode();
	pCopyNode->setNodeType(XMLTag);
	pCopyNode->setName("copy");
	pCopyNode->addProperty("MDBTable",pMDBTable->findProperty("name"));
	pCopyNode->addProperty("MDBUsage",pMDBTable->findProperty("usage"));
	pCopyNode->addProperty("XTPField",pXTPField->findProperty("name"));
	pCopyNode->addProperty("XTPComment",pXTPField->findProperty("comment"));
	
	CXMLNodeList *pMDBFields,*pXTPItems;
	
	pMDBFields=pMDBTable->findNode(XMLTag,"fields")->getNodeList();
	pXTPItems=pXTPField->getNodeList();
	
	int i,j;
	
	for (i=0;i<pMDBFields->size();i++)
	{
		for (j=0;j<pXTPItems->size();j++)
		{
			CXMLNode *pItemNode;
			
			pItemNode=makeCopyItem(pMDBFields->at(i),pXTPItems->at(j));
			
			if (pItemNode!=NULL)
			{
				pCopyNode->addNode(pItemNode);
			}
		}
	}
	
	if ((pCopyNode->getNodeList()==NULL)||(pCopyNode->getNodeList()->size()<=1))
	{
		return NULL;
	}
	
	return pCopyNode;
}

int mergeMDB_XTP(char *target, char *mdb, char *xtp)
{
	CXMLDoc *pTarget, *pMDB, *pXTP;
	
	pTarget=new CXMLDoc();
	pMDB=new CXMLDoc();
	pXTP=new CXMLDoc();
	
	pMDB->read(mdb,1);
	pXTP->read(xtp,1);
	
	pTarget->setEncoding(pMDB->getEncoding());
	pTarget->setVersion(pMDB->getVersion());
	pTarget->setRoot("copylist");
	pTarget->setDoctype("../env/copy.dtd");
	
	CXMLNode *rootNode;
	
	rootNode=new CXMLNode();
	rootNode->setNodeType(XMLTag);
	rootNode->setName("copylist");
	pTarget->setRootNode(rootNode);
	
	CXMLNodeList *MDBTables,*XTPFields;
	
	MDBTables=pMDB->getRootNode()->findNode(XMLTag, "tables")->getNodeList();
	XTPFields=pXTP->getRootNode()->findNode(XMLTag, "fields")->getNodeList();
	
	int i,j;
	
	for (i=0;i<MDBTables->size();i++)
	{
		for (j=0;j<XTPFields->size();j++)
		{
			CXMLNode *pCopyNode;
			
			pCopyNode=makeCopyNode(MDBTables->at(i),XTPFields->at(j));
			
			if (pCopyNode!=NULL)
			{
				rootNode->addNode(pCopyNode);
			}
		}
	}
	
	if (!pTarget->write(target))
	{
		printf("can not write %s\n",target);
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	try
	{
		if (argc==1)
		{
			printf("%s (DB|MDB|XTP|FTD) <target> <source> <entity> <datatype> or\n",argv[0]);
			printf("%s CHECK <datatype> <entity> <miscfiles>\n",argv[0]);
			printf("%s MERGE_MDB_XTP <target> <mdb> <xtp>\n",argv[0]);
			return 1;
		}
		char *transType=argv[1];
		
		if (!strcmp(transType,"DB"))
		{
			curTransType=ISDB;
		}
		else if (!strcmp(transType,"MDB"))
		{
			curTransType=ISMDB;
		}
		else if (!strcmp(transType,"XTP"))
		{
			curTransType=ISXTP;
		}
		else if (!strcmp(transType,"FTD"))
		{
			curTransType=ISXTP;
		}
		else if (!strcmp(transType,"TRANSDB"))
		{
			curTransType=TRANSDB;
		}
		else if (!strcmp(transType,"TRANSDATATYPE"))
		{
			curTransType=TRANSDATATYPE;
		}
		else if (!strcmp(transType,"CHECK"))
		{
			curTransType=CHECK;
		}
		else if (!strcmp(transType,"MERGE_MDB_XTP"))
		{
			return mergeMDB_XTP(argv[2],argv[3],argv[4]);
		}
		else
		{
			printf("unknown trans type %s\n",transType);
			return 1;
		}

		char *target;
		char *source;
		char *entity;
		char *datatype;

		if (curTransType!=CHECK)
		{
			target=argv[2];
			source=argv[3];
			entity=argv[4];
			datatype=argv[5];
	
			pEntity=new CXMLDoc;
			pEntity->read(entity,1);
			pEntityRoot=pEntity->getRootNode();
	
			pDatatype=new CXMLDoc;
			pDatatype->read(datatype,1);
			pDatatypeRoot=pDatatype->getRootNode();

			pDoc=new CXMLDoc;
			if (curTransType!=TRANSDATATYPE)
			{
				pDoc->read(source);
			}
			else
			{
				pDoc=pDatatype;
			}
			pDocRoot=pDoc->getRootNode();
	
			
			pAppEntityRoot=pDocRoot->findNode(XMLTag,"entities");
			
			/*
			if (curTransType==ISDB)
			{
				checkDB();
			}
			else if (curTransType==ISMDB)
			{
				checkMDB();
			}
			else if (curTransType==ISXTP)
			{
				checkXTP();
			}
			*/

			trans(pDocRoot);
			
			if (!pDoc->write(target))
			{
				printf("can not write XML document\n");
				return 1;
			}
			//pDoc->write(stdout);
		}
		else
		{
			int i;

			datatype=argv[2];
			entity=argv[3];

			pEntity=new CXMLDoc;
			pEntity->read(entity,1);
			pEntityRoot=pEntity->getRootNode();
	
			pDatatype=new CXMLDoc;
			pDatatype->read(datatype,1);
			pDatatypeRoot=pDatatype->getRootNode();
			
			printf("检查 %s\n",entity);
			checkEntity();
			
			for (i=4;i<argc;i++)
			{
				source=argv[i];
				
				printf("检查 %s\n",source);
				fflush(stdout);

				pDoc=new CXMLDoc;
				pDoc->read(source);
				pDocRoot=pDoc->getRootNode();
				pAppEntityRoot=pDocRoot->findNode(XMLTag,"entities");
				
				if (!strcmp(pDocRoot->getName(),"DB"))
				{
					checkDB();
				}
				else if (!strcmp(pDocRoot->getName(),"system"))
				{
					checkMDB();
				}
				else if (!strcmp(pDocRoot->getName(),"XTP"))
				{
					checkXTP();
				}
				else if (!strcmp(pDocRoot->getName(),"FTD"))
				{
					checkXTP();
				}
				else
				{
					printf("unknown Misc file type %s in file %s\n",
						pDocRoot->getName(),source);
				}
			}

			printf("检查 %s\n",datatype);
			checkDataType();
		}
	}
	catch (CParseError *pParseError)
	{
		printf("parse error:\n%s at line %d\n",pParseError->getMsg(),pParseError->getLineNo());
		return 1;
	}
	return 0;
}
