/////////////////////////////////////////////////////////////////////////
///@system XML�����ļ���дAPI                                                  
///@company �Ϻ���Ͷ����Ƽ����޹�˾                                     
///@file CConfigXML.h                                                          
///@brief��������XML�����ļ������йص���ӿ�                                     
///@history                                                              
///20051025	�¾���		�������ļ�                                         
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
///CConfigXML XML2Object�ӿ��ṩ��xml��ʼ�����ö���ʹ����ö�������xml����
///�ļ��������ļ���ȱʡλ���ǳ�������Ŀ¼��config.xml,���config.xml�ļ���
///���ڣ�ֱ�ӱ��������˳���
///@author	�¾���
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
	bool readAll();//����ִ���Ƿ�ɹ�
	bool writeAll();//����ִ���Ƿ�ɹ�
	
	///��ѯ���𻷾���Ҫ�Ĳ�����
	///@param	ip	���𻷾���IP��ַ
	///@param	pVec	�ɵ��ú�����ʼ����ΪNULL�˳������ض�ӦIP��ַ��Ҫ�Ĳ�����
	///@return ��û�ж�ȡXML�ļ�ʱ����false,����Ҫ�������ݷ���true.
	bool queryDeployItem(string ip, vector<CDeployItem> *pVec);
	CConfigXML(void);
	~CConfigXML(void);
private:
	bool m_bRead;
};

#endif //CCONFIGXML_H
