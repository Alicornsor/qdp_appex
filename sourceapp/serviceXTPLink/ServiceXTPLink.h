/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file IServiceMemoryLink.h
///@brief定义了接口IServiceMemoryLink
///@history 
///20060118	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef ISERVICEXTPLINK_H
#define ISERVICEXTPLINK_H

#include "XTPPackage.h"
#include "IServiceInterface.h"
#include "errorDefine.h"

/**IServiceResponser是一个发应XTP应答的接口类
*/
class IServiceResponser
{
public:
	/**发送XTP应答
	*@param pPackage 要发送的应答
	*@remark 纯虚函数，需要派生类重载
	*/
	virtual void SendResponse(CXTPPackage *pPackage,DWORD dwSessionID = 0) = 0;
	virtual ~IServiceResponser(){};
};

/////////////////////////////////////////////////////////////////////////
///IServiceMemoryLink是一个说明在内存运行的服务的接口
///@author	xuzh
///@version	1.0,20060118
/////////////////////////////////////////////////////////////////////////
class IServiceXTPLink
{
public:
	///处理一个XTP包
	///@param	pPackage	要处理的XTP包
	///@param	sessionRef	会话引用
	///@return	true表示处理成功，false表示处理失败
	virtual bool handleMessage(CXTPPackage *pPackage, const TSessionRef &sessionRef)=0;

	///处理一个XTP请求
	///@param	pPackage	要处理的XTP包
	///@param	sessionRef	会话引用
	///@return	true表示处理成功，false表示处理失败
	virtual bool handleRequest(CXTPPackage *pPackage,const TSessionRef &sessionRef,DWORD dwReponseSession)=0;
	virtual ~IServiceXTPLink(){};
};

#define CaseSpread(packageName,responseName,fieldName,tableName,entityName,serviceName,pService,pTransaction)									\
			case TID_ ## packageName:													\
{																	\
	m_pRspMessage->PrepareResponse(pPackage,TID_ ## responseName);	\
	C ## fieldName ## Field field;									\
	CNamedFieldIterator it= pPackage->GetNamedFieldIterator(&field.m_Describe);		\
	it.Retrieve(&field);									\
	CWriteable ## tableName the ## tableName;										\
	the ## tableName.init();												\
	Copy ## entityName ## Entity(&the ## tableName ,&field);						\
	success=pService->serviceName(&the ##tableName ,sessionRef,pTransaction);						\
	m_pErrorEngine->getLastError(&errorCode,&errMsg);	\
	Copy ## entityName ## Entity(&field, &the ## tableName);						\
	XTP_ADD_FIELD(m_pRspMessage,&field);	\
	CRspInfoField responseField;	\
	responseField.ErrorID = errorCode;		\
	responseField.ErrorMsg = errMsg;		\
	XTP_ADD_FIELD(m_pRspMessage,&responseField);	\
	m_pRspMessage->MakePackage();					\
	m_pServiceResponser->SendResponse(m_pRspMessage);	\
	break;															\
}
//Modified by huwp 20101013
#define CaseOrderSpread(packageName,responseName,fieldName,tableName,entityName,serviceName,pService,pTransaction)									\
			case TID_ ## packageName:													\
{																	\
	m_pRspMessage->PrepareResponse(pPackage,TID_ ## responseName);	\
	C ## fieldName ## Field field;									\
	CNamedFieldIterator it= pPackage->GetNamedFieldIterator(&field.m_Describe);		\
	it.Retrieve(&field);									\
	CRspInfoField responseField;	\
	CWriteable ## tableName the ## tableName;										\
	the ## tableName.init();												\
	Copy ## entityName ## Entity(&the ## tableName ,&field);						\
	if(0 == pPackage->GetGroupID())									\
	{									\
		success=pService->serviceName(&the ##tableName ,sessionRef,pTransaction);						\
		Copy ## entityName ## Entity(&field, &the ## tableName);						\
	}				\
	else									\
	{\
		m_pErrorEngine->reportError((int)pPackage->GetGroupID()); \
		pService->insertErrorOrder(&the ##tableName);						\
	}										\
	XTP_ADD_FIELD(m_pRspMessage,&field);	\
	m_pErrorEngine->getLastError(&errorCode,&errMsg);										\
	responseField.ErrorID = errorCode;		\
	responseField.ErrorMsg = errMsg;		\
	XTP_ADD_FIELD(m_pRspMessage,&responseField);	\
	m_pRspMessage->MakePackage();					\
	m_pServiceResponser->SendResponse(m_pRspMessage);	\
	break;															\
}

#define CaseSpreadNotify(packageName,fieldName,tableName,entityName,serviceName,pService,pTransaction)									\
		case TID_ ## packageName:													\
{																	\
	m_pRspMessage->PreparePublish(TID_ ## packageName);	\
	C ## fieldName ## Field field;									\
	CNamedFieldIterator it= pPackage->GetNamedFieldIterator(&field.m_Describe);		\
	it.Retrieve(&field);									\
	CWriteable ## tableName the ## tableName;										\
	the ## tableName.init();												\
	Copy ## entityName ## Entity(&the ## tableName ,&field);						\
	success=pService->serviceName(&the ##tableName ,sessionRef,pTransaction);	\
	m_pErrorEngine->getLastError(&errorCode,&errMsg);	\
	XTP_ADD_FIELD(m_pRspMessage,&field);				\
	m_pRspMessage->MakePackage();					\
	m_pServiceResponser->SendResponse(m_pRspMessage);	\
	break;															\
}

#define CaseSpreadNotNotify(packageName,fieldName,tableName,entityName,serviceName,pService,pTransaction)									\
		case TID_ ## packageName:													\
{																	\
	C ## fieldName ## Field field;									\
	CNamedFieldIterator it= pPackage->GetNamedFieldIterator(&field.m_Describe);		\
	it.Retrieve(&field);									\
	CWriteable ## tableName the ## tableName;										\
	the ## tableName.init();												\
	Copy ## entityName ## Entity(&the ## tableName ,&field);						\
	success=pService->serviceName(&the ##tableName ,sessionRef,pTransaction);	\
	m_pErrorEngine->getLastError(&errorCode,&errMsg);	\
	break;															\
}
#endif
