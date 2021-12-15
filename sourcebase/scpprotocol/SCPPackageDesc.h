// SCPPackageDesc.h: interface for the CSCPPackageDesc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCPPACKAGEDESC_H__C16CC87D_1BD0_4F0A_B286_BBAA19BAC3BF__INCLUDED_)
#define AFX_SCPPACKAGEDESC_H__C16CC87D_1BD0_4F0A_B286_BBAA19BAC3BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FieldDescribe.h"

#define STID_LOGIN_REQ						0x0001			//系统同步请求
#define STID_LOGIN_RSP						0x0002			//系统同步响应
#define STID_LSA_REQ						0x0003			//LSA发送请求
#define STID_LSA_UPDATE						0x0004			//LSA信息
#define STID_LSA_COMPLETE					0x0005			//LSA发送完毕
#define STID_SUBSCRIBE						0x0006			//订阅主题
#define STID_UN_SUBSCRIBE					0x0007			//取消订阅
#define STID_PUBLISH						0x0008			//发布主题声明
#define STID_ACK							0x0009			//主动确认

class  CSCPLoginReqField 
{
public:
	CUFIntType	NodeID;				/**<设备号*/
	CUFIntType	Metric;				/**<花费*/
	CUFCharType	Type;				/**<设备类型 'R'路由器 'T'终端*/
	/**产生各属性的描述，并填写描述对照表
	*/
	TYPE_DESCRIPTOR((
		TYPE_DESC(NodeID),
		TYPE_DESC(Metric),
		TYPE_DESC(Type)
	));
};

class CSCPLinkStateField 
{
public:
	CUFIntType NodeID;				/**< 目标地址*/
	CUFIntType Metric;				/**< 花费 */
	CUFCharType Type;				/**< 类型 'T'终端, 'R'路由*/
	/**产生各属性的描述，并填写描述对照表
	*/
	TYPE_DESCRIPTOR((
		TYPE_DESC(NodeID),
		TYPE_DESC(Metric),
		TYPE_DESC(Type)
	));
};

class CSCPLsaHeadField 
{
public:
	CUFIntType NodeID;				/**<产生LSA的节点ID*/
	CUFCharType Type;				/**< 产生LSA的节点类型 'T'终端, 'R'路由*/
	CUFIntType TimeStamp;			/**<时间戳*/
	/**产生各属性的描述，并填写描述对照表
	*/
	TYPE_DESCRIPTOR((
		TYPE_DESC(NodeID),
		TYPE_DESC(Type),
		TYPE_DESC(TimeStamp)
	));
};

class CSCPSubscribeField 
{
public:
	CUFIntType SubscriberID;		/**<订阅者标识  */
	CUFIntType SubjectID;			/**<主题标识*/
	CUFIntType StartID;				/**<起始序号*/
	CUFWordType  CommPhaseNo;		/**<通讯阶段序号,每次更换序号，SequenceNo都从1重新开始 */
	/**产生各属性的描述，并填写描述对照表
	*/
	TYPE_DESCRIPTOR((
		TYPE_DESC(SubscriberID),
		TYPE_DESC(SubjectID),
		TYPE_DESC(StartID),
		TYPE_DESC(CommPhaseNo)
	));
};

class CSCPPublishField 
{
public:
	CUFIntType SubjectID;			/**<主题标识*/
	CUFIntType SeqNo;				/**<主题最大序号*/
	CUFWordType  CommPhaseNo;		/**<通讯阶段序号,每次更换序号，SequenceNo都从1重新开始 */
	/**产生各属性的描述，并填写描述对照表
	*/
	TYPE_DESCRIPTOR((
		TYPE_DESC(SubjectID),
		TYPE_DESC(SeqNo),
		TYPE_DESC(CommPhaseNo)
	));
};
#endif // !defined(AFX_SCPPACKAGEDESC_H__C16CC87D_1BD0_4F0A_B286_BBAA19BAC3BF__INCLUDED_)
