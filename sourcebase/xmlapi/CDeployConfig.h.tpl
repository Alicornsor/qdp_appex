/////////////////////////////////////////////////////////////////////////
///@system DeployConfig XML�����ļ���дAPI                                                  
///@company �Ϻ���Ͷ����Ƽ����޹�˾                                     
///@file CDeployConfig.h                                                          
///@brief��������DeployConfig XML�����ļ������йص���ӿ�                                     
///@history                                                              
///20051025	�¾���		�������ļ�                                         
/////////////////////////////////////////////////////////////////////////

#ifndef CDEPLOYCONFIG_H
#define CDEPLOYCONFIG_H

#include <vector>
#include <string>
#include <map>
#include "CXML.h"
using std::string;
using std::vector;
using std::map;
typedef map<string, string> HashMap;
namespace deployconfig{
class IElementInterface
{
public:
	virtual void SetObject(CXMLNode *pNode)=0;
	virtual CXMLNode * GetObject()=0;
};
!!travel DeployConfig-schema!!
!!** enter system!!
!!** travel package!!
class C!!@name!!;
!!next!!
!!travel DeployConfig-schema!!
class C!!@name!! : public IElementInterface
!!** enter complexType!!
{
private:
!!travel self!!
	!!if !strcmp("attribute", @name)!!
	string m_!!@type!!;
	!!endif!!
	!!if !strcmp("element", @name)!!
		!!** travel self!!
			 !!if strcmp("1",@maxOccurs)!!
	vector<C!!@type!! *> *m_p!!@type!!;
			 !!else!!
	C!!@type!! *m_p!!@type!!;
			!!endif!!
		!!** next!!
	!!endif!!
!!next!!
public:
	C!!@name!!();
	~C!!@name!!();
	virtual void SetObject(CXMLNode *pNode);
	virtual CXMLNode * GetObject();
!!if !strcmp(@name,"DeployConfig")!!
	bool ReadXML();
	bool WriteXML();
!!endif!!
!!travel self!!
	!!if !strcmp("attribute", @name)!!
	string get!!@type!!();
	void set!!@type!!(string arg!!@type!!);
	!!endif!!
	!!if !strcmp("element", @name)!!
		!!** travel self!!
			 !!if strcmp("1", @maxOccurs)!!
	vector<C!!@type!! *> *get!!@type!!();
	void set!!@type!!(vector<C!!@type!! *> *arg!!@type!!);
			 !!else!!
	C!!@type!! *get!!@type!!();
	void set!!@type!!(C!!@type!! *arg!!@type!!);
			!!endif!!
		!!** next!!
	!!endif!!
!!next!!
};
!!** leave!!
!!next!!
}

#endif //CDEPLOYCONFIG_H
