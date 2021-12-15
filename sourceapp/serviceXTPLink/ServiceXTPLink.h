/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file IServiceMemoryLink.h
///@brief�����˽ӿ�IServiceMemoryLink
///@history 
///20060118	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef ISERVICEXTPLINK_H
#define ISERVICEXTPLINK_H

#include "XTPPackage.h"
#include "IServiceInterface.h"
#include "errorDefine.h"

/**IServiceResponser��һ����ӦXTPӦ��Ľӿ���
*/
class IServiceResponser
{
public:
	/**����XTPӦ��
	*@param pPackage Ҫ���͵�Ӧ��
	*@remark ���麯������Ҫ����������
	*/
	virtual void SendResponse(CXTPPackage *pPackage,DWORD dwSessionID = 0) = 0;
	virtual ~IServiceResponser(){};
};

/////////////////////////////////////////////////////////////////////////
///IServiceMemoryLink��һ��˵�����ڴ����еķ���Ľӿ�
///@author	xuzh
///@version	1.0,20060118
/////////////////////////////////////////////////////////////////////////
class IServiceXTPLink
{
public:
	///����һ��XTP��
	///@param	pPackage	Ҫ�����XTP��
	///@param	sessionRef	�Ự����
	///@return	true��ʾ����ɹ���false��ʾ����ʧ��
	virtual bool handleMessage(CXTPPackage *pPackage, const TSessionRef &sessionRef)=0;

	///����һ��XTP����
	///@param	pPackage	Ҫ�����XTP��
	///@param	sessionRef	�Ự����
	///@return	true��ʾ����ɹ���false��ʾ����ʧ��
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
