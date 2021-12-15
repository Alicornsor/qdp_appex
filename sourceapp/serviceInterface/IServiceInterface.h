/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file IInitService.h
///@brief�����˽ӿ�IInitService
///@history 
///20060113	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef ISERVICEINTERFACE_H
#define ISERVICEINTERFACE_H

#include "customDataType.h"

/////////////////////////////////////////////////////////////////////////
///TSessionRef��һ��˵���Ự��ʶ����
///@author	xuzh
///@version	1.0,20060113
/////////////////////////////////////////////////////////////////////////
typedef struct
{
	CFrontIDType	FrontID;
	CSessionIDType	SessionID;
	CRequestIDType  RequestID;
}	TSessionRef;

//����sessionid����Ϣ�����ڻر����ͻ�
#define COPY_SESSIONREF_INFO(target,source) \
	(target)->FrontID=(source)->FrontID; \
	(target)->SessionID=(source)->SessionID; \
	(target)->RequestID=(source)->RequestID; \
	
#endif
