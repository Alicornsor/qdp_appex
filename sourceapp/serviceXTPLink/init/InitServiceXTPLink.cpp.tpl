!!enter XTP!!
!!function!!
int isInitPackage(char *usage)
{
	if (!strcmp(usage,"exchangeInit"))
	{
		return 1;
	}
	return 0;
}

char *getTableName(char *name)
{
	return name+4;
}
!!endfunction!!
/////////////////////////////////////////////////////////////////////////
///@system ��������ϵͳ
///@company QuantDo Platform
///@file InitServiceMemoryLink.h
///@briefʵ������CInitServiceMemoryLink
///@history 
///20130701	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#include "InitServiceXTPLink.h"
#include "XtpPackageDesc.h"
#include "UFCopy.h"

CInitServiceXTPLink::CInitServiceXTPLink(CInitServiceImpl *pInitService,
				 CErrorEngine *pErrorEngine,IServiceResponser *pServiceResponser,CFlow* pTradeResult,bool verbose)
{
	m_pInitService=pInitService;
	m_pErrorEngine=pErrorEngine;
	m_pRspMessage = new CXTPPackage;
	m_pRspMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	m_pServiceResponser = pServiceResponser;
	m_verbose=verbose;
	m_pTradeResult = pTradeResult;
}
	
CInitServiceXTPLink::~CInitServiceXTPLink()
{
	if(m_pRspMessage != NULL)
		m_pRspMessage->Release();
	delete m_pRspMessage;
}

bool CInitServiceXTPLink::handleRequest(CXTPPackage *pPackage, const TSessionRef &sessionRef,DWORD responseSession)
{
	return true;
}

bool CInitServiceXTPLink::handleMessage(CXTPPackage *pPackage, const TSessionRef &sessionRef)
{
	//�����ʼ����by wangwei,20130116
	char buffer[3900];
	memset(buffer,0,3900);
	bool success=true;
	char* errMsg="";
	int errorCode=0;
	switch (pPackage->GetTid())
	{
	!!travel packages!!
	!!if isInitPackage(@usage)!!
	!!let tableName=getTableName(@name)!!
	case TID_!!@name!!:
	{
		C!!@tableName!!Field field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteable!!@tableName!! the!!@tableName!!;
			the!!@tableName!!.init();			
			it.Retrieve(&field);
			Copy!!@tableName!!Entity(&the!!@tableName!!,&field);
			///�������ֶ��Ƿ�Ϸ�
			if (the!!@tableName!!.isValid())
			{
				success=m_pInitService->init!!@tableName!!(&the!!@tableName!!,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(the!!@tableName!!) < 3900)
				{
					the!!@tableName!!.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_!!@name!! is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	!!endif!!
	!!next!!
	case TID_DataSyncStart:
	{
		CTradingDayField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		it.Retrieve(&field);
		success=m_pInitService->DataSyncStart(field.TradingDay,sessionRef,&m_Transaction);
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_DataSyncEnd:
	{
		CTradingDayField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		it.Retrieve(&field);
		success=m_pInitService->DataSyncEnd(field.TradingDay,sessionRef,&m_Transaction);
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}	
	//���̻���ѯ��Լ���֪ͨ��Ϣ����Ҫ��������ʽ��Kernel
	case TID_RspQueryExInstrument:
	{
		//��ѯ�ɹ���ȡ����Լ��Ϣ�������ڴ��
		CInstrumentField field;			
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			it.Retrieve(&field);
			m_pInitService->RspQryExInstrument(&field,sessionRef,&m_Transaction);
			it.Next();
		}
		break;
	}
	//���̻����͵Ľ�����-�����յĲ�ѯӦ��
	case TID_RspQueryExTradingDay:
	{
		CExchangeTradingDayField field;	
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			it.Retrieve(&field);
			m_pInitService->RspQryExTradingDay(&field,sessionRef,&m_Transaction);
			it.Next();
		}
		break;
	}
	//���̻����͵Ŀͻ��ֲֲ�ѯӦ��
	case TID_RspQueryExInvestorPosition:
	{
		CInvestorPositionField field;	
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			it.Retrieve(&field);
			m_pInitService->RspQryExInvestorPosition(&field,sessionRef,&m_Transaction);
			it.Next();
		}		
		break;
	}
	//���̻����͵������ѯӦ��
	case TID_RspQueryExMarketData:
	{
		CMarketDataField field;	
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			it.Retrieve(&field);
			m_pInitService->RspQryExMarketData(&field,sessionRef,&m_Transaction);
			it.Next();
		}
		break;
	}
	//���̻����͵��ʽ��ѯӦ��
	case TID_RspQueryExCapitalData:
	{
		CExCapitalDataField field;	
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			it.Retrieve(&field);
			m_pInitService->RspQryExCapitalData(&field,sessionRef,&m_Transaction);
			it.Next();
		}
		break;
	}
	//���̻���ѯ��Ϻ�Լ��ϸӦ��
	case TID_RspQueryExCmbInstrumentDetail:
	{
		CCmbInstrumentDetailField field;	
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			it.Retrieve(&field);
			m_pInitService->RspQueryExCmbInstrumentDetail(&field,sessionRef,&m_Transaction);
			it.Next();
		}
		break;
	}
	//���̻����͵Ľ���ʱ��ƫ���ѯӦ��
	case TID_RspQueryExchDiffTime:
	{
		CExchTimeDiffField field;	
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			it.Retrieve(&field);
			m_pInitService->RspQryExDiffTime(&field,sessionRef,&m_Transaction);
			it.Next();
		}
		break;
	}
	default:
		return true;
	}
	if (pPackage->GetNoReplayFlag() && success)
	{
		pPackage->MakeNoBufPackage();
		m_pTradeResult->Append(pPackage->Address(), pPackage->Length());
		pPackage->Pop(XTPHLEN);
	}
	if (success)		
		m_Transaction.commit();
	else
		m_Transaction.rollback();
	if(m_verbose)
	{
		if(errorCode == 0)
		{
			//BIZ_OPERATION_LOG0("(OK by exchange init service)\n");
		}
		else
		{
			BIZ_OPERATION_LOG2("(FAILED by exchange init service:%d:%s)\n",errorCode,errMsg);
		}
	}
	return success;
}

!!leave!!
