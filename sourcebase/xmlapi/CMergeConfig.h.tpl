/////////////////////////////////////////////////////////////////////////
///@system MergeConfig XML配置文件读写API                                                  
///@company 上海量投网络科技有限公司                                     
///@file CMergeConfig.h                                                          
///@brief定义了与MergeConfig XML配置文件操作有关的类接口                                     
///@history                                                              
///20051025	陈钧雷		创建该文件                                         
/////////////////////////////////////////////////////////////////////////

#ifndef CMERGECONFIG_H
#define CMERGECONFIG_H

#include <vector>
#include <string>
#include <map>
#include "CXML.h"
using std::string;
using std::vector;
using std::map;
typedef map<string, string> HashMap;
namespace mergeconfig{
class IElementInterface
{
public:
	virtual void SetObject(CXMLNode *pNode)=0;
	virtual CXMLNode * GetObject()=0;
};
!!travel MergeConfig-schema!!
!!** enter system!!
!!** travel package!!
class C!!@name!!;
!!next!!
!!travel MergeConfig-schema!!
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
!!if !strcmp(@name,"MergeConfig")!!
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

#endif //CMERGECONFIG_H
