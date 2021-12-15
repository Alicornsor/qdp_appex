/////////////////////////////////////////////////////////////////////////
///@system XML配置文件读写API                                                  
///@company 上海量投网络科技有限公司                                     
///@file CConfigXML.h                                                          
///@brief定义了与XML配置文件操作有关的类接口                                     
///@history                                                              
///20051025	陈钧雷		创建该文件                                         
/////////////////////////////////////////////////////////////////////////

#ifndef CCONFIGXML_H
#define CCONFIGXML_H

#include <vector>
#include <string>
#include <map>
using std::string;
using std::vector;
using std::map;
typedef map<string, string> HashMap;
class CUser
{
private:
	string m_account;
	string m_pwd;
	string m_name;
	string m_dept;
	string m_tel;
	string m_email;
	string m_remark;	
public:
	CUser(void);
	~CUser(void);
	string getAccount();
	string getPwd();
	string getName();
	string getDept();
	string getTel();
	string getEmail();
	string getRemark();
	void setAccount(string);
	void setPwd(string);
	void setName(string);
	void setDept(string);
	void setTel(string);
	void setEmail(string);
	void setRemark(string);
	void setObject(HashMap);
	void getObject(HashMap*);
};
class CDeploySetting
{
private:
	string m_name;
	string m_ip;
	string m_account;
	string m_pwd;
	string m_remark;	
public:
	CDeploySetting(void);
	CDeploySetting(const CDeploySetting &);
	CDeploySetting& operator = (const CDeploySetting &);
	~CDeploySetting(void);
	string getName();
	string getIp();
	string getAccount();
	string getPwd();
	string getRemark();
	void setName(string);
	void setIp(string);
	void setAccount(string);
	void setPwd(string);
	void setRemark(string);
	void setObject(HashMap);
	void getObject(HashMap*);
};
class CConfiguration
{
private:
	string m_name;
	string m_path;
	string m_version;
	string m_remark;	
public:
	CConfiguration(void);
	~CConfiguration(void);
	string getName();
	string getPath();
	string getVersion();
	string getRemark();
	void setName(string);
	void setPath(string);
	void setVersion(string);
	void setRemark(string);
	void setObject(HashMap);
	void getObject(HashMap*);
};
class CDeployItem
{
private:
	string m_name;
	string m_deploySettingName;
	string m_cfgName;
	string m_targetPath;
	string m_para;
	string m_remark;
	string m_stat;
public:
	CDeployItem(void);
	~CDeployItem(void);
	string getName();
	string getCfgName();
	string getDeploySettingName();
	string getTargetPath();
	string getPara();
	string getRemark();
	string getStat();
	void setName(string);
	void setDeploySettingName(string);
	void setCfgName(string);
	void setTargetPath(string);
	void setPara(string);
	void setRemark(string);
	void setStat(string);
	void setObject(HashMap);
	void getObject(HashMap*);
};

/////////////////////////////////////////////////////////////////////////
///CConfigXML XML2Object接口提供从xml初始化配置对象和从配置对象生成xml配置
///文件，配置文件的缺省位置是程序运行目录下config.xml,如果config.xml文件不
///存在，直接报告错误后退出。
///@author	陈钧雷
///@version	1.0,20051025
/////////////////////////////////////////////////////////////////////////
class CConfigXML
{
public:
	vector<CUser> *m_userList;
	vector<CDeploySetting> *m_deploySettingList;
	vector<CConfiguration> *m_cfgList;
	vector<CDeployItem> *m_deployItemList;
	string m_port;
	bool readAll();//返回执行是否成功
	bool writeAll();//返回执行是否成功
	
	///查询部署环境需要的部署项
	///@param	ip	部署环境的IP地址
	///@param	pVec	由调用函数初始化，为NULL退出，返回对应IP地址需要的部署项
	///@return 当没有读取XML文件时返回false,有需要部署内容返回true.
	bool queryDeployItem(string ip, vector<CDeployItem> *pVec);
	CConfigXML(void);
	~CConfigXML(void);
private:
	bool m_bRead;
};

#endif //CCONFIGXML_H
