// FTDCSession.cpp: implementation of the CFTDCSession class.
//
// 20070128 hwp 问题：在接收方接收速度很慢时，如果某些流中数据很多，由于
//                 GetIds中没有流控，会迅速将channel缓冲区填满，导致其它流
//                 发送很慢，且内存消耗很大。
//                 现改为：在GetIds中，如果channel的缓冲区为空，才将流中的
//                 报文发向channel
// 20100125 hwp NT-0096:修正FTDCSession的内存泄漏问题
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "FTDCPackage.h"
#include "FTDCSession.h"

const DWORD XMPTypeFTDC = 0x01;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CFTDCSession::CFTDCSession(CReactor *pReactor,CChannel *pChannel)
:CXMPSession(pReactor, pChannel)
{
	m_pCRPProtocol = new CCompressProtocol(m_pReactor);
	m_pCRPProtocol->AttachLower(m_pXMPProtocol, XMPTypeCompressed);
	m_pFTDCProtocol = new CFTDCProtocol(m_pReactor);
	m_pFTDCProtocol->AttachLower(m_pCRPProtocol, XMPTypeFTDC);

	m_pFTDCProtocol->RegisterErrorHandler(this);
	m_pFTDCProtocol->RegisterUpperHandler(this);
	
	m_pPackageHandler = NULL;
	m_pmapSubInstrument = NULL;
}

CFTDCSession::~CFTDCSession()
{
	delete m_pFTDCProtocol;
	delete m_pCRPProtocol;
	if (m_pmapSubInstrument)
	{
		delete m_pmapSubInstrument;
	}
	
}

int CFTDCSession::HandleEvent(int nEventID, DWORD dwParam, void *pParam)
{
	switch(nEventID)
	{
	case MSG_XMPERR_RECVHEARTBEAT:
	case MSG_XMPERR_SENDHEARTBEAT:
	case MSG_XMPERR_BADPACKAGE:
	case MSG_FTDCERR_BADPACKAGE:
		Disconnect(nEventID);
		return 0;
	case MSG_XMPWARNING_RECVHEARTBEAT:
		if (m_pSessionCallback != NULL)
		{
			m_pSessionCallback->OnSessionWarning(this, nEventID, (int)dwParam);
		}
		return 0;
	}

	return CSession::HandleEvent(nEventID, dwParam, pParam);
}	

void CFTDCSession::GetIds(int *pReadId, int *pWriteId)
{
	CXMPSession::GetIds(pReadId, pWriteId);
	if (*pWriteId == 0)
	{
		m_pFTDCProtocol->PublishSend();
		CXMPSession::GetIds(pReadId, pWriteId);
	}
}

void CFTDCSession::RegisterPackageHandler(CFTDCSessionCallback *pPackageHandler)
{
	m_pPackageHandler = pPackageHandler;
}

int CFTDCSession::HandlePackage(CPackage *pPackage,CProtocol *pProtocol)
{
	if (pProtocol == m_pFTDCProtocol)
	{
		CFTDCPackage *pFTDCPacakge = (CFTDCPackage *)pPackage;
		if (m_pPackageHandler == NULL)
		{
			return 0;
		}
		return m_pPackageHandler->HandlePackage(pFTDCPacakge, this);
	}
	return 0;
}


void CFTDCSession::Publish(CReadOnlyFlow *pFlow, WORD wSequenceSeries, int nStartId)
{
	m_pFTDCProtocol->Publish(pFlow, wSequenceSeries, nStartId);
}

void CFTDCSession::UnPublish(WORD wSequenceSeries)
{
	m_pFTDCProtocol->UnPublish(wSequenceSeries);
}

CFTDCPackage *CFTDCSession::CreatePackage()
{
	CFTDCPackage *pPackage = new CFTDCPackage;
	pPackage->ConstructAllocate(FTDC_PACKAGE_MAX_SIZE, m_pFTDCProtocol->GetHdrReserveLen());
	return pPackage;
}

void CFTDCSession::SendRequestPackage(CFTDCPackage *pPackage)
{
	m_pFTDCProtocol->Send(pPackage);
}

void CFTDCSession::RegisterSubscriber(CFTDCSubscriber *pSubscriber)
{
	m_pFTDCProtocol->RegisterSubscriber(pSubscriber);
}

void CFTDCSession::UnRegisterSubscriber(CFTDCSubscriber *pSubscriber)
{
	m_pFTDCProtocol->UnRegisterSubscriber(pSubscriber);
}

void CFTDCSession::SetCommPhaseNo(WORD wCommPhaseNo)
{
	m_pFTDCProtocol->SetCommPhaseNo(wCommPhaseNo);
}

void CFTDCSession::Disconnect(int nErrorCode)
{
	if (nErrorCode == 0)
	{
		//如果是主动断开，则尝试发送流中未发完的包
		m_pFTDCProtocol->PublishSend();
	}

	m_pFTDCProtocol->Clear();
	
	CXMPSession::Disconnect(nErrorCode);
}

void CFTDCSession::SetCompressMethod(BYTE chCompressMethod)
{
	m_pCRPProtocol->SetCompressMethod(XMPTypeFTDC, chCompressMethod);
}

void CFTDCSession::SetVersion(BYTE version)
{
	m_version=version;
}
	
BYTE CFTDCSession::GetVersion(void)
{
	return m_version;
}

void CFTDCSession::CreatSubInstrument()
{
	if (m_pmapSubInstrument==NULL)
	{
		m_pmapSubInstrument = new CSubInstrumentMap();
		m_pFTDCProtocol->SetSubInstrumentMap(m_pmapSubInstrument);
	}
}

bool CFTDCSession::InsertInstrumentID(DWORD instrumentIDCount,CInstrumentIDType instrumentID)
{
	CInstrumentIDType *iter = m_pmapSubInstrument->Find(instrumentIDCount);
	if(iter == NULL)
	{
		m_pmapSubInstrument->Insert(instrumentIDCount,instrumentID);
		v_subinstrumet.push_back(instrumentID);
		return true;
	}
	else
	{
		return false;
	}
}

bool CFTDCSession::DeleteInstrumentID(DWORD instrumentIDCount)
{
	CInstrumentIDType *iter = m_pmapSubInstrument->Find(instrumentIDCount);
	if(iter == NULL)
	{	
		return false;
	}
	else
	{
		m_pmapSubInstrument->Erase(instrumentIDCount);
		return true;
	}
}

void CFTDCSession::DisplayInstrumentID()
{
	CSubInstrumentMap::iterator iter = m_pmapSubInstrument->Begin();		
	while (!iter.IsEnd())
	{
		printf("%d->%s ",iter.GetKey(),(*iter).getValue());
		iter++;
	}
	printf("\n");
}

void CFTDCSession::RspAllSubInstrumentID(DWORD RspType)
{

	CFTDCPackage m_rspPackage;
	m_rspPackage.ConstructAllocate(FTDC_PACKAGE_MAX_SIZE, 1000);

	if(v_subinstrumet.size() == 0)
	{
		//空的map就什么都不回调
	}
	else
	{	
		//update by jinpc 20160928
		/*CSubInstrumentMap::iterator iter = m_pmapSubInstrument->Begin();		
		while (!iter.IsEnd())
		{
 			CFTDSpecificInstrumentField specificInstrumentField;
 			specificInstrumentField.InstrumentID = *iter;
 			int ret = FTDC_ADD_FIELD(&m_rspPackage, &specificInstrumentField);
 			if( ret < 0 )
			{
 				this->SendRequestPackage(&m_rspPackage);
 				m_rspPackage.PreparePackage(RspType, FTDC_CHAIN_CONTINUE, FTD_VERSION);
 				FTDC_ADD_FIELD(&m_rspPackage, &specificInstrumentField);			
			}
			iter++;
		}*/
		m_rspPackage.PreparePackage(RspType, FTDC_CHAIN_CONTINUE, FTD_VERSION);

		vector<CInstrumentIDType>::iterator itor = v_subinstrumet.begin();
		for (itor;itor!=v_subinstrumet.end();itor++)
		{
			CFTDSpecificInstrumentField specificInstrumentField;
			specificInstrumentField.InstrumentID = *itor;
 			int ret = FTDC_ADD_FIELD(&m_rspPackage, &specificInstrumentField);
			if( ret < 0 )
			{
				this->SendRequestPackage(&m_rspPackage);
				m_rspPackage.PreparePackage(RspType, FTDC_CHAIN_CONTINUE, FTD_VERSION);
				FTDC_ADD_FIELD(&m_rspPackage, &specificInstrumentField);			
			}
		}
		//打包完 清空v_subinstrumet
		v_subinstrumet.clear();

		//需要增加最后的包的标志
		m_rspPackage.SetChain(FTDC_CHAIN_LAST);
		this->SendRequestPackage(&m_rspPackage);
	}
}