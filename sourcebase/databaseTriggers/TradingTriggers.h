#ifndef _TRADINGTRIGGERS_H
#define _TRADINGTRIGGERS_H
#include "BaseDataStruct.h"
#include "Flow.h"
#include "CXTPRspMaker.h"
#include "CopyFunction.h"

const DWORD NULLTID = 0xFFFFFFFF;
template <class BaseTriggers,			///�����Ĵ�����
		  class BaseDataType,			///����������
		  class WriteableDataType,		///��д������
		  class FieldType,				///XTPFiled������
		  DWORD NOTIFY_ADD_MESSAGE=NULLTID,	///Add��ϢID
		  DWORD NOTIFY_UPDATE_MESSAGE=NULLTID,	///Update��ϢID
		  DWORD NOTIFY_REMOVE_MESSAGE=NULLTID>	///Remove��ϢID
class CTradingTrigger:public BaseTriggers,public CXTPRspMaker
{
public:
	CTradingTrigger(CFlow *pFlow):m_AddNotifyMsg(NOTIFY_ADD_MESSAGE),
	m_UpdateNotifyMsg(NOTIFY_UPDATE_MESSAGE),m_RemoveNotifyMsg(NOTIFY_REMOVE_MESSAGE)
	{ m_pFlow = pFlow;}

	virtual ~CTradingTrigger(){}

	virtual void commitAdd(BaseDataType *pData)
	{
		if(m_AddNotifyMsg != NULLTID)
			NotifyMessage(pData,m_AddNotifyMsg);
	}

	virtual void commitUpdate(BaseDataType *pData, WriteableDataType *pWriteableData)
	{
		if(m_UpdateNotifyMsg != NULLTID)
			NotifyMessage(pData,m_UpdateNotifyMsg);
	}

	virtual void commitRemove(WriteableDataType *pWriteableData)
	{
		if(m_RemoveNotifyMsg != NULLTID)
			NotifyMessage(pWriteableData,m_RemoveNotifyMsg);
	}

protected:
	CFlow *m_pFlow;
	DWORD m_AddNotifyMsg;
	DWORD m_RemoveNotifyMsg;
	DWORD m_UpdateNotifyMsg;
protected:
	void NotifyMessage(BaseDataType *pData,DWORD dwTID)
	{
		FieldType field;
		m_pRspMessage->PreparePublish(dwTID);
		CopyDataClass<FieldType,BaseDataType>::CopyEntity(&field,pData);
		XTP_ADD_FIELD(m_pRspMessage,&field);
		m_pRspMessage->MakePackage();
		m_pFlow->Append(m_pRspMessage->Address(),m_pRspMessage->Length());
	}
};

#endif