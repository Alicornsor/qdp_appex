/////////////////////////////////////////////////////////////////////////
///@system XML配置文件读写API                                                  
///@company 上海量投网络科技有限公司                                     
///@file CConfigXML.cpp                                                         
///@brief实现了与XML配置文件操作有关的类接口                                     
///@history                                                              
///20051025	陈钧雷		创建该文件                                         
/////////////////////////////////////////////////////////////////////////
#include "public.h"
//#pragma warning(disable:4786)
#include "CDeployConfig.h"
#include "CXML.h"
#include <typeinfo>
namespace deployconfig{
!!travel DeployConfig-schema!!
C!!@name!!::C!!@name!!()
{
!!travel self!!
	!!if !strcmp("element", @name)!!
		!!** travel self!!
			 !!if strcmp("1", @maxOccurs)!!
	 m_p!!@type!! = new vector<C!!@type!! *>();
			 !!else!!
	m_p!!@type!! = new C!!@type!!();
			!!endif!!
		!!** next!!
	!!endif!!
!!next!!

}
C!!@name!!::~C!!@name!!()
{
!!travel self!!
	!!if !strcmp("element", @name)!!
		!!** travel self!!
			 !!if strcmp("1", @maxOccurs)!!
	 m_p!!@type!!->empty();
	 delete m_p!!@type!!;
			 !!else!!
	delete m_p!!@type!!;
			!!endif!!
		!!** next!!
	!!endif!!
!!next!!
}

void C!!@name!!::SetObject(CXMLNode *pNode)
{
	//CXMLNode *pChildNode;
!!travel self!!
	!!if !strcmp("attribute", @name)!!
	m_!!@type!! = NULL!=pNode->findProperty("!!@type!!")?pNode->findProperty("!!@type!!"):"";
	!!endif!!
!!next!!
!!if strcmp(@content,"empty")!!
	CXMLNodeList *pList = pNode->getNodeList();
	if(NULL == pList)
		return;
!!endif!!
!!travel self!!
	!!if !strcmp("element", @name)!!
		!!** travel self!!
			 !!if strcmp("1", @maxOccurs)!!
	for(int i=0; i<pList->size(); i++)
	{
		if(!strcmp("!!@type!!",pList->at(i)->getName()))
		{
			C!!@type!! * tmp!!@type!! = new C!!@type!!();
			tmp!!@type!!->SetObject(pList->at(i));
			m_p!!@type!!->push_back(tmp!!@type!!);
		}
	}
			 !!else!!
	m_p!!@type!!->SetObject(pNode->findNode(XMLTag, "!!@type!!"));
			!!endif!!
		!!** next!!
	!!endif!!
!!next!!
}
CXMLNode * C!!@name!!::GetObject()
{
	CXMLNode *pNode = new CXMLNode();
	pNode->setName("!!@name!!");
	pNode->setNodeType(XMLTag);
!!travel self!!
	!!if !strcmp("attribute", @name)!!
	if(m_!!@type!!.compare(""))
		pNode->setProperty("!!@type!!", (char *)m_!!@type!!.c_str());
	!!endif!!
!!next!!
!!if strcmp(@content,"empty")!!
	CXMLNodeList *pList = new CXMLNodeList();
!!endif!!
!!travel self!!
	!!if !strcmp("element", @name)!!
		!!** travel self!!
			 !!if strcmp("1", @maxOccurs)!!
	for(int i=0; i<m_p!!@type!!->size(); i++)
	{
		pList->push_back((m_p!!@type!!->at(i))->GetObject());
	}
	pNode->setNodeList(pList);
			 !!else!!
	pNode->addNode(m_p!!@type!!->GetObject());
			!!endif!!
		!!** next!!
	!!endif!!
!!next!!
	return pNode;
}

!!if !strcmp(@name,"DeployConfig")!!
bool C!!@name!!::ReadXML()
{
	// FIXME: 检查是否存在config.xml文件，不存在出错处理
	CXMLDoc *pDoc;
	pDoc=new CXMLDoc;
	//printf("port is \n");
	try{
#ifdef WIN32
	pDoc->read(".\\DeployConfig.xml");
#else
	pDoc->read("./DeployConfig.xml");
#endif
	}
	catch (CParseError *pParseError)
	{
		printf("parse error:\n%s at line %d\n",pParseError->getMsg(),pParseError->getLineNo());
		return false;
	}
	CXMLNode *pNode = pDoc->getRootNode();
	this->SetObject(pNode);	
	return true;
}

bool C!!@name!!::WriteXML()
{
	//CXMLNode *rootNode = new CXMLNode();
	//rootNode->setName("DeployConfig");
	//rootNode->setNodeType(XMLTag);
	
	CXMLNode *rootNode = this->GetObject();	

	CXMLDoc *pDoc;
	pDoc=new CXMLDoc;
	pDoc->setEncoding("gb2312");
	pDoc->setVersion("1.0");
	pDoc->setDoctype("..\\..\\config\\DeployConfig.dtd");
	pDoc->setRootNode(rootNode);
	pDoc->setRoot("DeployConfig");	
#ifdef WIN32
	pDoc->write(".\\DeployConfig.xml");
#else
	pDoc->write("./DeployConfig.xml");
#endif
	delete pDoc;
	return true;
}

!!endif!!
!!** 属性处理开始!!
	!!let classname=@name!!
	!!travel self!!
		!!if !strcmp("attribute", @name)!!
string C!!@classname!!::get!!@type!!()
{
	return m_!!@type!!;
}

void C!!@classname!!::set!!@type!!(string arg!!@type!!)
{
	m_!!@type!! = arg!!@type!!;
}
		!!endif!!
!!** 属性处理完毕!!
!!** 集合处理开始!!
		!!if !strcmp("element", @name)!!
		     !!** travel self!!
			!!if strcmp("1", @maxOccurs)!!
vector<C!!@type!! *> * C!!@classname!!::get!!@type!!()
{
	return m_p!!@type!!;
}

void C!!@classname!!::set!!@type!!(vector<C!!@type!! *> *arg!!@type!!)
{
	// FIXME: 需要处理在集合对象初始化逻辑
	if(NULL != m_p!!@type!!)
		delete m_p!!@type!!;
	m_p!!@type!! = new vector<C!!@type!! *>(*arg!!@type!!);
}
			!!else!!
C!!@type!! * C!!@classname!!::get!!@type!!()
{
	return m_p!!@type!!;
}

void C!!@classname!!::set!!@type!!(C!!@type!! *arg!!@type!!)
{
	// FIXME: 需要处理在集合对象初始化逻辑
	//if(NULL != m_!!@type!!)
		//delete m_!!@type!!;
	//m_!!@type!! = new vector<C!!@type!! *>(*arg!!@type!!);
}
			!!endif!!
			!!** next!!
		!!endif!!
	!!next!!
!!** 集合处理完毕!!
!!next!!
}