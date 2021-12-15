#include "public.h"
#include "TMDBEngine.h"
#include "UFEntityCopy.h"
#include "XtpPackageDesc.h"
#include "BaseFunction.h"

extern TTaskMethod g_TaskMethod[] ;
//���ս���������δ�����ҵ�ȴ�5��
const int TMDB_USTMDB_WAIT=5;

CTMDBEngine::CTMDBEngine(CTMDBScheduler *pTMDBSchulder,const char * pBrokers,const char * pExchanges)
{
	m_pTMDBSchulder=pTMDBSchulder;
	//pExchanges �ĸ�ʽΪ: CFFEX,SHFE,SGX
	m_Brokers = Txtsplit(pBrokers,",");
	m_Exchanges = Txtsplit(pExchanges,",");
}

//deleted by lihh 20130517:
//
void CTMDBEngine::handleMessage(CXTPPackage *pPackage)
{
	DWORD tid;
	tid=pPackage->GetTid();
	m_pTMDBSchulder->AssignTask(pPackage->GetSequenceNo());    
	switch (tid)
 	{
	case TID_DataSyncStart:
 		{
 			CTradingDayField field;
 			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
 			while(!it.IsEnd())
 			{	
 				it.Retrieve(&field);
				CDataSyncStatusField DataSyncStatus;
				DataSyncStatus.TradingDay = field.TradingDay;
 				DataSyncStatus.DataSyncStatus = DS_Synchronizing;
				//��ɾ���������ӡ�����˱���û�����ݣ����¸��²��ɹ��������
 				m_pTMDBSchulder->Dispatch("t_Oper_DataSyncStatus",&CDataSyncStatusField::m_Describe,&DataSyncStatus,TA_DELETE);
 				m_pTMDBSchulder->Dispatch("t_Oper_DataSyncStatus",&CDataSyncStatusField::m_Describe,&DataSyncStatus,TA_INSERT);
 				it.Next();
 			}					
 			break;
  		}	
 	case TID_DataSyncEnd: 
 		{
 			CTradingDayField field;
 			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
 			while(!it.IsEnd())
 			{	
 				it.Retrieve(&field);
				CDataSyncStatusField DataSyncStatus;
				DataSyncStatus.TradingDay = field.TradingDay;
				DataSyncStatus.DataSyncStatus = DS_Synchronized;
				m_pTMDBSchulder->Dispatch("t_Oper_DataSyncStatus",&CDataSyncStatusField::m_Describe,&DataSyncStatus,TA_UPDATE);
 				it.Next();
 			}					
 			break;
  		}
	case TID_NtfMemtableChange:
		{
			handleMemDBMsg(pPackage);
			break;
		}
 	default:
		{
 			break;
		}
 	}
	m_pTMDBSchulder->SetCommitPoint(pPackage->GetSequenceNo());
}



void CTMDBEngine::handleMemDBMsg(CXTPPackage *pPackage)
{
 	CFieldTypeIterator itor=pPackage->GetFieldTypeIterator();
	while(!itor.IsEnd())
	{
		//ȡ����������
//		TTmdbActionType actType;
//		itor.RetrieveHeader(fHead);
		
// 		if (fHead.FieldID==MEMDB_INSERT)
// 			actType=TA_INSERT;
// 		else if (fHead.FieldID==MEMDB_UPDATE)
// 			actType=TA_UPDATE;
// 		else if (fHead.FieldID==MEMDB_DELETE)
// 			actType=TA_UPDATE;
// 		else
// 			return;
		//ȡ����������
		CMemtableChangeField field;
		itor.Retrieve(&CMemtableChangeField::m_Describe,&field);
		TTmdbActionType actType;
		if(field.MemtableChangeType==MTC_INSERT)
		{
			actType = TA_INSERT;
		}
		else if(field.MemtableChangeType==MTC_UPDATE)
		{
			actType	= TA_UPDATE;
		}
		else if(field.MemtableChangeType==MTC_DELETE)
		{
			actType	= TA_DELETE;
		}
		//ȡ���ֶ�
		itor.Next();
	    TFieldHeader  fHead;
		itor.RetrieveHeader(fHead);
		ProcField(fHead.FieldID,itor,actType);
		itor.Next();
	}
}

void CTMDBEngine::ProcField(WORD fid,CFieldTypeIterator &itor,TTmdbActionType actType)
{
 	int  fLen=0;
 	char ObjName[50];
 	memset(ObjName,0,sizeof(ObjName));
 	switch (fid)
 	{
 	case FID_Order:
 		{
			COrderField field;
			fLen=itor.Retrieve(&COrderField::m_Describe,&field);
			if(BrokerCheck(field.BrokerID)&&ExchangeCheck(field.ExchangeID))
				m_pTMDBSchulder->Dispatch("t_Oper_Order",&COrderField::m_Describe,&field,actType);
			break;
		}
	case FID_Trade:
		{
			CTradeField field;
			fLen=itor.Retrieve(&CTradeField::m_Describe,&field);
			if(BrokerCheck(field.BrokerID)&&ExchangeCheck(field.ExchangeID))
				m_pTMDBSchulder->Dispatch("t_Oper_Trade",&CTradeField::m_Describe,&field,actType);

			break;
		}
	case FID_InvestorAccount:
		{
			CInvestorAccountField field;
			fLen=itor.Retrieve(&CInvestorAccountField::m_Describe,&field);
			if(BrokerCheck(field.BrokerID))
				m_pTMDBSchulder->Dispatch("t_Oper_InvestorAccount",&CInvestorAccountField::m_Describe,&field,actType);
			break;
		}
	case FID_InvestorPosition:
		{
			CInvestorPositionField field;
			fLen=itor.Retrieve(&CInvestorPositionField::m_Describe,&field);			
			if(BrokerCheck(field.BrokerID)&&ExchangeCheck(field.ExchangeID))
				m_pTMDBSchulder->Dispatch("t_Oper_InvestorPosition",&CInvestorPositionField::m_Describe,&field,actType);
			break;
		}
	case FID_User:
		{
			CUserField field;
			fLen=itor.Retrieve(&CUserField::m_Describe,&field);
			if(BrokerCheck(field.BrokerID))
			{
				m_pTMDBSchulder->Dispatch("t_Oper_User",&CUserField::m_Describe,&field,actType);
				if (actType == TA_UPDATE)
				{
					m_pTMDBSchulder->Dispatch("t_Sync_User",&CUserField::m_Describe,&field,TA_UPDATE);
				}
			}
			break;
		}
	case FID_UserSession:
		{
			CUserSessionField field;
			fLen=itor.Retrieve(&CUserSessionField::m_Describe,&field);
			if(BrokerCheck(field.BrokerID))
				m_pTMDBSchulder->Dispatch("t_Oper_UserSession",&CUserSessionField::m_Describe,&field,actType);
			break;
		}
	case FID_Instrument://��Լ�³�
		{
			CInstrumentField field;
			fLen=itor.Retrieve(&CInstrumentField::m_Describe,&field);
			if(BrokerCheck(field.ExchangeID))
				m_pTMDBSchulder->Dispatch("t_Oper_Instrument",&CInstrumentField::m_Describe,&field,actType);
			break;
		}
// 	case FID_SystemStatus://ϵͳ״̬�³�
// 		{
// 			CSystemStatusField field;
// 			fLen=itor.Retrieve(&CSystemStatusField::m_Describe,&field);		
// 			m_pTMDBSchulder->Dispatch("t_Sync_SystemStatus",&CSystemStatusField::m_Describe,&field,TA_UPDATE);
// 			REPORT_EVENT(LOG_CRITICAL, "qmdb", "System Status has been updated");
// 			break;
//		}

	//�������³�,�����ں�Լ�³�֮ǰ��ɣ�����Ӱ�쳡��
	case FID_Exchange:
		{
			CExchangeField field;
			fLen=itor.Retrieve(&CExchangeField::m_Describe,&field);
			if(BrokerCheck(field.ExchangeID))
				m_pTMDBSchulder->Dispatch("t_Oper_Exchange",&CExchangeField::m_Describe,&field,actType);
			break;
		}
	case FID_OrderInsertFailed: //�����³�  added by liumeng 20140814
		{
			COrderInsertFailedField field;
			fLen=itor.Retrieve(&COrderInsertFailedField::m_Describe,&field);
			if(BrokerCheck(field.BrokerID)&&ExchangeCheck(field.ExchangeID))
				m_pTMDBSchulder->Dispatch("t_Oper_OrderInsertFailed",&COrderInsertFailedField::m_Describe,&field,actType);
			break;
		}
		//��ֹҹ�����к�ͬ��״̬�³����ڶ���������Ҫ�����ϳ�
// 	case FID_DataSyncStatus:
// 		{
// 			CDataSyncStatusField field;
// 			fLen=itor.Retrieve(&CDataSyncStatusField::m_Describe,&field);
// 			m_pTMDBSchulder->Dispatch("t_Oper_DataSyncStatus",&CDataSyncStatusField::m_Describe,&field,TA_DELETE);
// 			m_pTMDBSchulder->Dispatch("t_Oper_DataSyncStatus",&CDataSyncStatusField::m_Describe,&field,TA_INSERT);	
// 			break;
// 		}
	case FID_SystemStatus:
		{
			CSystemStatusField field;
			fLen=itor.Retrieve(&CSystemStatusField::m_Describe,&field);
			m_pTMDBSchulder->Dispatch("t_Sync_SystemStatus",&CSystemStatusField::m_Describe,&field,TA_DELETE);
			m_pTMDBSchulder->Dispatch("t_Sync_SystemStatus",&CSystemStatusField::m_Describe,&field,TA_INSERT);	
			break;
		}
	case FID_InvestorTradingRight:
		{
			CInvestorTradingRightField field;
			fLen=itor.Retrieve(&CInvestorTradingRightField::m_Describe,&field);
			if(BrokerCheck(field.BrokerID))
				m_pTMDBSchulder->Dispatch("t_Oper_InvestorTradingRight",&CInvestorTradingRightField::m_Describe,&field,actType);
			break;
		}
	case FID_SGEDeferRate:
		{
			CSGEDeferRateField field;
			fLen=itor.Retrieve(&CSGEDeferRateField::m_Describe,&field);
			m_pTMDBSchulder->Dispatch("t_Oper_SGEDeferRate",&CSGEDeferRateField::m_Describe,&field,actType);
			break;
		}
	case FID_SystemInfo:
		{
			CSystemInfoField field;
			fLen=itor.Retrieve(&CSystemInfoField::m_Describe,&field);
			if (field.SystemID.isNull())
			{
				REPORT_EVENT(LOG_CRITICAL, "ProcField", "FID_SystemInfo systemid is null");
				break;
			}
			m_pTMDBSchulder->Dispatch("t_Oper_SystemInfo",&CSystemInfoField::m_Describe,&field,actType);
			m_SystemID = field.SystemID;
			m_pTMDBSchulder->StartAllNonSyncThread(field.SystemID.getValue());
			break;
		}
	case FID_DataSyncStatus:
		{
			CDataSyncStatusField field;
			fLen=itor.Retrieve(&CDataSyncStatusField::m_Describe,&field);
			field.SystemID = m_SystemID;
			m_pTMDBSchulder->Dispatch("t_Oper_DataSyncStatus",&CDataSyncStatusField::m_Describe,&field,TA_DELETE);
 			m_pTMDBSchulder->Dispatch("t_Oper_DataSyncStatus",&CDataSyncStatusField::m_Describe,&field,TA_INSERT);
			break;
		}
 	default:
 		{	
			//����Ϊ����Ҫ�³��ģ����Լ���
			//printf("Error:error field ID=[%04x]\n", fid);
 			break;
 		}
	}
}

bool CTMDBEngine::BrokerCheck(CBrokerIDType brokerID)
{
	int nBrokerSize = m_Brokers.size();
	if(nBrokerSize==0)
		return true;

	for(int i=0;i<nBrokerSize;i++)
	{
		if(brokerID==m_Brokers[i].c_str())
		{
			return true;
		}
	}
	return false;
}

bool CTMDBEngine::ExchangeCheck(CExchangeIDType exchangeID)
{
	int nExchangeSize = m_Exchanges.size();
	if(nExchangeSize==0)
		return true;

	for(int i=0;i<nExchangeSize;i++)
	{
		if(exchangeID==m_Exchanges[i].c_str())
		{
			return true;
		}
	}
	return false;
}