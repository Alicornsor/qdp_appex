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
#include "CConfigXML.h"
#include "CXML.h"
#include <typeinfo>

string getString(HashMap hashmap, string key)
{
	int count = 0;
	if(hashmap.count(key))
		return hashmap[key];
	else
		return string("");
}
CUser::CUser(void)
{
}

CUser::~CUser(void)
{
}

string CUser::getAccount()
{
	return m_account;
}
string CUser::getPwd()
{
	return m_pwd;
}

string CUser::getName()
{
	return m_name;
}
string CUser::getDept()
{
	return m_dept;
}
string CUser::getTel()
{
	return m_tel;
}
string CUser::getEmail()
{
	return m_email;
}
string CUser::getRemark()
{
	return m_remark;
}
void CUser::setAccount(string account)
{
	m_account = account;
}
void CUser::setPwd(string pwd)
{
	m_pwd = pwd;
}
void CUser::setName(string name)
{
	m_name = name;
}
void CUser::setDept(string dept)
{
	m_dept = dept;
}
void CUser::setTel(string tel)
{
	m_tel = tel;
}
void CUser::setEmail(string email)
{
	m_email = email;
}
void CUser::setRemark(string remark)
{
	m_remark = remark;
}
void CUser::setObject(HashMap hashmap)
{
	setAccount(hashmap["account"]);
	setDept(hashmap["dept"]);
	setEmail(hashmap["email"]);
	setName(hashmap["userName"]);
	setPwd(hashmap["password"]);
	setRemark(hashmap["remark"]);
	setTel(hashmap["tel"]);
}

void CUser::getObject(HashMap* pHM)
{
	(*pHM)["key"] = "User";
	(*pHM)["account"] = m_account;
	(*pHM)["dept"] = m_dept;
	(*pHM)["email"] = m_email;
	(*pHM)["userName"] = m_name;
	(*pHM)["password"] = m_pwd;
	(*pHM)["remark"] = m_remark;
	(*pHM)["tel"] = m_tel;
}

CDeploySetting::CDeploySetting(void)
{
	m_account = "";
	m_ip = "";
	m_name = "";
	m_pwd = "";
	m_remark = "";
}
CDeploySetting::CDeploySetting(const CDeploySetting &other)
{
	m_account = other.m_account;
	m_ip = other.m_ip;
	m_name = other.m_name;
	m_pwd = other.m_pwd;
	m_remark = other.m_remark;
}
CDeploySetting& CDeploySetting::operator = (const CDeploySetting &other)
{
	if(this != &other)
	{
		m_account = other.m_account;
		m_ip = other.m_ip;
		m_name = other.m_name;
		m_pwd = other.m_pwd;
		m_remark = other.m_remark;
	}
	return *this;
}

CDeploySetting::~CDeploySetting(void)
{
}
string CDeploySetting::getName()
{
	return m_name;
}
string CDeploySetting::getIp()
{
	return m_ip;
}
string CDeploySetting::getAccount()
{
	return m_account;
}
string CDeploySetting::getPwd()
{
	return m_pwd;
}
string CDeploySetting::getRemark()
{
	return m_remark;
}
void CDeploySetting::setName(string name)
{
	m_name = name;
}
void CDeploySetting::setIp(string ip)
{
	m_ip = ip;
}
void CDeploySetting::setAccount(string account)
{
	m_account = account;
}
void CDeploySetting::setPwd(string pwd)
{
	m_pwd = pwd;
}
void CDeploySetting::setRemark(string remark)
{
	m_remark = remark;
}
void CDeploySetting::setObject(HashMap hashmap)
{
	setAccount(hashmap["account"]);
	setIp(hashmap["ip"]);
	setName(hashmap["name"]);
	setPwd(hashmap["password"]);
	setRemark(hashmap["remark"]);
}
void CDeploySetting::getObject(HashMap* pHM)
{
	(*pHM)["key"] = "DeploySetting";
	(*pHM)["account"] = m_account;
	(*pHM)["ip"] = m_ip;
	(*pHM)["name"] = m_name;
	(*pHM)["password"] = m_pwd;
	(*pHM)["remark"] = m_remark;
}

CConfiguration::CConfiguration(void){}
CConfiguration::~CConfiguration(void){}
string CConfiguration::getName()
{
	return m_name;
}
string CConfiguration::getPath()
{
	return m_path;
}
string CConfiguration::getVersion()
{
	return m_version;
}
string CConfiguration::getRemark()
{
	return m_remark;
}
void CConfiguration::setName(string name)
{
	m_name = name;
}
void CConfiguration::setPath(string path)
{
	m_path = path;
}
void CConfiguration::setVersion(string version)
{
	m_version = version;
}
void CConfiguration::setRemark(string remark)
{
	m_remark = remark;
}
void CConfiguration::setObject(HashMap hashmap)
{
	setName(hashmap["name"]);
	setPath(hashmap["path"]);
	setRemark(hashmap["remark"]);
	setVersion(hashmap["version"]);
}
void CConfiguration::getObject(HashMap* pHM)
{
	(*pHM)["key"] = "Configuration";
	(*pHM)["path"] = m_path;
	(*pHM)["name"] = m_name;
	(*pHM)["version"] = m_version;
	(*pHM)["remark"] = m_remark;
}

CDeployItem::CDeployItem(void){}
CDeployItem::~CDeployItem(void){}
string CDeployItem::getName()
{
	return m_name;
}
string CDeployItem::getDeploySettingName()
{
	return m_deploySettingName;
}
string CDeployItem::getCfgName()
{
	return m_cfgName;
}
string CDeployItem::getTargetPath()
{
	return m_targetPath;
}
string CDeployItem::getPara()
{
	return m_para;
}
string CDeployItem::getRemark()
{
	return m_remark;
}
string CDeployItem::getStat()
{
	return m_stat;
}
void CDeployItem::setName(string name)
{
	m_name = name;
}
void CDeployItem::setDeploySettingName(string settingName)
{
	m_deploySettingName = settingName;
}
void CDeployItem::setCfgName(string cfgName)
{
	m_cfgName = cfgName;
}
void CDeployItem::setTargetPath(string targetPath)
{
	m_targetPath = targetPath;
}
void CDeployItem::setPara(string para)
{
	m_para = para;
}
void CDeployItem::setRemark(string remark)
{
	m_remark = remark;
}
void CDeployItem::setStat(string stat)
{
	m_stat = stat;
}

void CDeployItem::setObject(HashMap hashmap)
{
	setCfgName(hashmap["cfgName"]);
	setDeploySettingName(hashmap["deploySettingName"]);
	setName(hashmap["name"]);
	setPara(hashmap["para"]);
	setRemark(hashmap["remark"]);
	setTargetPath(hashmap["targetPath"]);
	setStat(hashmap["stat"]);
}
void CDeployItem::getObject(HashMap* pHM)
{
	(*pHM)["key"] = "DeployItem";
	(*pHM)["cfgName"] = m_cfgName;
	(*pHM)["deploySettingName"] = m_deploySettingName;
	(*pHM)["name"] = m_name;
	(*pHM)["para"] = m_para;
	(*pHM)["targetPath"] = m_targetPath;
	(*pHM)["remark"] = m_remark;
	(*pHM)["stat"] = m_stat;
}

CConfigXML::CConfigXML(void)
{
	m_userList = new vector<CUser>();
	m_deploySettingList = new vector<CDeploySetting>();
	m_cfgList = new vector<CConfiguration>();
	m_deployItemList = new vector<CDeployItem>();
	//初始化的时候标记为未读取XML文件
	m_bRead = false;
}

CConfigXML::~CConfigXML(void)
{
	if(NULL != m_userList)
		delete m_userList;
	if(NULL != m_deploySettingList)
		delete m_deploySettingList;
	if(NULL != m_cfgList)
		delete m_cfgList;
	if(NULL != m_deployItemList)
		delete m_deployItemList;
}

///
bool XML2HashMap(CXMLNode * node, HashMap *hashmap)
{
	CXMLPropertyList *pList = node->getPropertyList();
	string key, value;
	HashMap hm;
	for(int i=0; i<pList->size(); i++)
	{
		CXMLProperty *  property = pList->at(i);
		key = property->getName();
		value = property->getValue();
		 
		//hashmap.insert(key, value);
		hm[key] = value;
		//printf("test %s\n", hashmap[key].c_str());
	}
	*hashmap = hm;
	return true;
}
template <typename elemType>
bool XML2Object(CXMLNode * node, vector<elemType> *vec)
{
	
	CXMLNodeList *pList = node->getNodeList();
	if(NULL == pList)
		return true;
	for(int i=0; i<pList->size(); i++)
	{
		
		elemType elem;
		HashMap hashmap;
		XML2HashMap(pList->at(i), &hashmap);
		elem.setObject(hashmap);
		vec->push_back(elem);
	}
	return true;
}

template <typename elemType>
bool Object2XML(vector<elemType> vec, CXMLNode *node)
{	
	for(int i=0; i<vec.size(); i++)
	{
		CXMLNode *childNode = new CXMLNode();
		childNode->setNodeType(XMLTag);
		HashMap *pHM = new HashMap();
		vec[i].getObject(pHM);
		HashMap::const_iterator iter = pHM->begin();
		HashMap::const_iterator end_it = pHM->end();
		for(; iter != end_it; ++iter)
		{
			if(iter->first == "key")
			{
				childNode->setName((char *)((iter->second).c_str()));
			}
			else
			{
				childNode->addProperty((char *)((iter->first).c_str()), (char *)((iter->second).c_str()));
			}
		}
		node->addNode(childNode);
	}
	return true;
}
bool CConfigXML::readAll()
{
	// FIXME: 检查是否存在config.xml文件，不存在出错处理
	CXMLDoc *pDoc;
	pDoc=new CXMLDoc;
	//printf("port is \n");
	try{
#ifdef WIN32
	pDoc->read(".\\config.xml");
#else
	pDoc->read("./config.xml");
#endif
	}
	catch (CParseError *pParseError)
	{
		printf("parse error:\n%s at line %d\n",pParseError->getMsg(),pParseError->getLineNo());
		return false;
	}
	CXMLNode *node = pDoc->getRootNode();
	m_port = node->findProperty("port");
	XML2Object(node->findNode(XMLTag, "SettingList"), m_deploySettingList);
	XML2Object(node->findNode(XMLTag, "CfgList"), m_cfgList);
	XML2Object(node->findNode(XMLTag, "DeployItemList"), m_deployItemList);
	XML2Object(node->findNode(XMLTag, "UserList"), m_userList);
	delete pDoc;
	m_bRead = true;
	return true;
}
bool CConfigXML::queryDeployItem(string ip, vector<CDeployItem> *pVec)
{
	assert(NULL != pVec);
	if(!m_bRead)
		return false;
	string sDeploySetting("");
	vector<CDeploySetting>::iterator iter = m_deploySettingList->begin();
	vector<CDeploySetting>::iterator end = m_deploySettingList->end();
	for(; iter !=end; ++iter)
	{
		if((iter->getIp()) == ip)
			sDeploySetting=iter->getName();
	}
	if(sDeploySetting=="")
		return false;
	
	vector<CDeployItem>::iterator item_iter = m_deployItemList->begin();
	vector<CDeployItem>::iterator item_end = m_deployItemList->end();
	for(; item_iter!=item_end; ++item_iter)
	{
		if((item_iter->getDeploySettingName())==sDeploySetting)
			pVec->push_back(*item_iter);
	}
	if(0 == pVec->size())
		return false;
	return true;
}
bool CConfigXML::writeAll()
{
	CXMLNode *rootNode = new CXMLNode();
	rootNode->setName("csss");
	rootNode->setNodeType(XMLTag);
	rootNode->addProperty("port", (char *)m_port.c_str());

	CXMLNode *nodeSettingList = new CXMLNode();
	nodeSettingList->setName("SettingList");
	nodeSettingList->setNodeType(XMLTag);
	Object2XML(*m_deploySettingList,nodeSettingList);
	rootNode->addNode(nodeSettingList);

	CXMLNode *nodeCfgList = new CXMLNode();
	nodeCfgList->setName("CfgList");
	nodeCfgList->setNodeType(XMLTag);
	Object2XML(*m_cfgList,nodeCfgList);
	rootNode->addNode(nodeCfgList);

	CXMLNode *nodeDeployItemList = new CXMLNode();
	nodeDeployItemList->setName("DeployItemList");
	nodeDeployItemList->setNodeType(XMLTag);
	Object2XML(*m_deployItemList,nodeDeployItemList);
	rootNode->addNode(nodeDeployItemList);

	CXMLNode *nodeUserList = new CXMLNode();
	nodeUserList->setName("UserList");
	nodeUserList->setNodeType(XMLTag);
	Object2XML(*m_userList,nodeUserList);
	rootNode->addNode(nodeUserList);

	CXMLDoc *pDoc;
	pDoc=new CXMLDoc;
	pDoc->setEncoding("gb2312");
	pDoc->setVersion("1.0");
	pDoc->setDoctype(".\\csss.dtd");
	pDoc->setRootNode(rootNode);
	pDoc->setRoot("csss");	
#ifdef WIN32
	pDoc->write(".\\config.xml");
#else
	pDoc->write("./config.xml");
#endif
	delete pDoc;
	return true;
}

