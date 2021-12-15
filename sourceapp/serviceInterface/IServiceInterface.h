/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file IInitService.h
///@brief定义了接口IInitService
///@history 
///20060113	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef ISERVICEINTERFACE_H
#define ISERVICEINTERFACE_H

#include "customDataType.h"

/////////////////////////////////////////////////////////////////////////
///TSessionRef是一个说明会话标识的类
///@author	xuzh
///@version	1.0,20060113
/////////////////////////////////////////////////////////////////////////
typedef struct
{
	CFrontIDType	FrontID;
	CSessionIDType	SessionID;
	CRequestIDType  RequestID;
}	TSessionRef;

//复制sessionid等信息，便于回报给客户
#define COPY_SESSIONREF_INFO(target,source) \
	(target)->FrontID=(source)->FrontID; \
	(target)->SessionID=(source)->SessionID; \
	(target)->RequestID=(source)->RequestID; \
	
#endif
