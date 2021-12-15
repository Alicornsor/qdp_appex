/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file databaseResources.cpp
///@brief实现了若干内存数据资源，可以放置于事务中
///@history 
///20060127	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "databaseResources.h"


CMemoryStack<CDataSyncStatusResource> CDataSyncStatusResource::resourceList;

CDataSyncStatusResource * CDataSyncStatusResource::alloc(int type, CDataSyncStatusFactory *pFactory, CDataSyncStatus *pObject, CWriteableDataSyncStatus *pWriteableObject, bool updateIndex)
{
	CDataSyncStatusResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CDataSyncStatusResource::free(void)
{
	resourceList.free(this);
}

CDataSyncStatusResource::CDataSyncStatusResource(void)
{
}

CDataSyncStatusResource::~CDataSyncStatusResource(void)
{
}

void CDataSyncStatusResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CDataSyncStatus *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CDataSyncStatus *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CDataSyncStatusResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CDataSyncStatus *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CDataSyncStatus *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CDataSyncStatusResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CSystemStatusResource> CSystemStatusResource::resourceList;

CSystemStatusResource * CSystemStatusResource::alloc(int type, CSystemStatusFactory *pFactory, CSystemStatus *pObject, CWriteableSystemStatus *pWriteableObject, bool updateIndex)
{
	CSystemStatusResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CSystemStatusResource::free(void)
{
	resourceList.free(this);
}

CSystemStatusResource::CSystemStatusResource(void)
{
}

CSystemStatusResource::~CSystemStatusResource(void)
{
}

void CSystemStatusResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CSystemStatus *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CSystemStatus *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CSystemStatusResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CSystemStatus *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CSystemStatus *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CSystemStatusResource::getPriority(void)
{
	return 2;
}


CMemoryStack<COrderActionResource> COrderActionResource::resourceList;

COrderActionResource * COrderActionResource::alloc(int type, COrderActionFactory *pFactory, COrderAction *pObject, CWriteableOrderAction *pWriteableObject, bool updateIndex)
{
	COrderActionResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void COrderActionResource::free(void)
{
	resourceList.free(this);
}

COrderActionResource::COrderActionResource(void)
{
}

COrderActionResource::~COrderActionResource(void)
{
}

void COrderActionResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((COrderAction *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((COrderAction *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void COrderActionResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((COrderAction *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((COrderAction *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int COrderActionResource::getPriority(void)
{
	return 2;
}


CMemoryStack<COrderResource> COrderResource::resourceList;

COrderResource * COrderResource::alloc(int type, COrderFactory *pFactory, COrder *pObject, CWriteableOrder *pWriteableObject, bool updateIndex)
{
	COrderResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void COrderResource::free(void)
{
	resourceList.free(this);
}

COrderResource::COrderResource(void)
{
}

COrderResource::~COrderResource(void)
{
}

void COrderResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((COrder *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((COrder *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void COrderResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((COrder *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((COrder *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int COrderResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CTradeResource> CTradeResource::resourceList;

CTradeResource * CTradeResource::alloc(int type, CTradeFactory *pFactory, CTrade *pObject, CWriteableTrade *pWriteableObject, bool updateIndex)
{
	CTradeResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CTradeResource::free(void)
{
	resourceList.free(this);
}

CTradeResource::CTradeResource(void)
{
}

CTradeResource::~CTradeResource(void)
{
}

void CTradeResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CTrade *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CTrade *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CTradeResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CTrade *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CTrade *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CTradeResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CPreOrderResource> CPreOrderResource::resourceList;

CPreOrderResource * CPreOrderResource::alloc(int type, CPreOrderFactory *pFactory, CPreOrder *pObject, CWriteablePreOrder *pWriteableObject, bool updateIndex)
{
	CPreOrderResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CPreOrderResource::free(void)
{
	resourceList.free(this);
}

CPreOrderResource::CPreOrderResource(void)
{
}

CPreOrderResource::~CPreOrderResource(void)
{
}

void CPreOrderResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CPreOrder *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CPreOrder *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CPreOrderResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CPreOrder *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CPreOrder *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CPreOrderResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CIndexPreOrderResource> CIndexPreOrderResource::resourceList;

CIndexPreOrderResource * CIndexPreOrderResource::alloc(int type, CIndexPreOrderFactory *pFactory, CIndexPreOrder *pObject, CWriteableIndexPreOrder *pWriteableObject, bool updateIndex)
{
	CIndexPreOrderResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CIndexPreOrderResource::free(void)
{
	resourceList.free(this);
}

CIndexPreOrderResource::CIndexPreOrderResource(void)
{
}

CIndexPreOrderResource::~CIndexPreOrderResource(void)
{
}

void CIndexPreOrderResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CIndexPreOrder *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CIndexPreOrder *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CIndexPreOrderResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CIndexPreOrder *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CIndexPreOrder *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CIndexPreOrderResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CInvestorPositionResource> CInvestorPositionResource::resourceList;

CInvestorPositionResource * CInvestorPositionResource::alloc(int type, CInvestorPositionFactory *pFactory, CInvestorPosition *pObject, CWriteableInvestorPosition *pWriteableObject, bool updateIndex)
{
	CInvestorPositionResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CInvestorPositionResource::free(void)
{
	resourceList.free(this);
}

CInvestorPositionResource::CInvestorPositionResource(void)
{
}

CInvestorPositionResource::~CInvestorPositionResource(void)
{
}

void CInvestorPositionResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CInvestorPosition *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CInvestorPosition *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CInvestorPositionResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CInvestorPosition *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CInvestorPosition *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CInvestorPositionResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CInvestorAccountResource> CInvestorAccountResource::resourceList;

CInvestorAccountResource * CInvestorAccountResource::alloc(int type, CInvestorAccountFactory *pFactory, CInvestorAccount *pObject, CWriteableInvestorAccount *pWriteableObject, bool updateIndex)
{
	CInvestorAccountResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CInvestorAccountResource::free(void)
{
	resourceList.free(this);
}

CInvestorAccountResource::CInvestorAccountResource(void)
{
}

CInvestorAccountResource::~CInvestorAccountResource(void)
{
}

void CInvestorAccountResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CInvestorAccount *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CInvestorAccount *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CInvestorAccountResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CInvestorAccount *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CInvestorAccount *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CInvestorAccountResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CInvestorAccountDepositResource> CInvestorAccountDepositResource::resourceList;

CInvestorAccountDepositResource * CInvestorAccountDepositResource::alloc(int type, CInvestorAccountDepositFactory *pFactory, CInvestorAccountDeposit *pObject, CWriteableInvestorAccountDeposit *pWriteableObject, bool updateIndex)
{
	CInvestorAccountDepositResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CInvestorAccountDepositResource::free(void)
{
	resourceList.free(this);
}

CInvestorAccountDepositResource::CInvestorAccountDepositResource(void)
{
}

CInvestorAccountDepositResource::~CInvestorAccountDepositResource(void)
{
}

void CInvestorAccountDepositResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CInvestorAccountDeposit *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CInvestorAccountDeposit *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CInvestorAccountDepositResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CInvestorAccountDeposit *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CInvestorAccountDeposit *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CInvestorAccountDepositResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CExchangeResource> CExchangeResource::resourceList;

CExchangeResource * CExchangeResource::alloc(int type, CExchangeFactory *pFactory, CExchange *pObject, CWriteableExchange *pWriteableObject, bool updateIndex)
{
	CExchangeResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CExchangeResource::free(void)
{
	resourceList.free(this);
}

CExchangeResource::CExchangeResource(void)
{
}

CExchangeResource::~CExchangeResource(void)
{
}

void CExchangeResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CExchange *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CExchange *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CExchangeResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CExchange *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CExchange *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CExchangeResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CSeatResource> CSeatResource::resourceList;

CSeatResource * CSeatResource::alloc(int type, CSeatFactory *pFactory, CSeat *pObject, CWriteableSeat *pWriteableObject, bool updateIndex)
{
	CSeatResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CSeatResource::free(void)
{
	resourceList.free(this);
}

CSeatResource::CSeatResource(void)
{
}

CSeatResource::~CSeatResource(void)
{
}

void CSeatResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CSeat *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CSeat *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CSeatResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CSeat *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CSeat *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CSeatResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CInstrumentResource> CInstrumentResource::resourceList;

CInstrumentResource * CInstrumentResource::alloc(int type, CInstrumentFactory *pFactory, CInstrument *pObject, CWriteableInstrument *pWriteableObject, bool updateIndex)
{
	CInstrumentResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CInstrumentResource::free(void)
{
	resourceList.free(this);
}

CInstrumentResource::CInstrumentResource(void)
{
}

CInstrumentResource::~CInstrumentResource(void)
{
}

void CInstrumentResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CInstrument *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CInstrument *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CInstrumentResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CInstrument *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CInstrument *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CInstrumentResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CCmbInstrumentDetailResource> CCmbInstrumentDetailResource::resourceList;

CCmbInstrumentDetailResource * CCmbInstrumentDetailResource::alloc(int type, CCmbInstrumentDetailFactory *pFactory, CCmbInstrumentDetail *pObject, CWriteableCmbInstrumentDetail *pWriteableObject, bool updateIndex)
{
	CCmbInstrumentDetailResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CCmbInstrumentDetailResource::free(void)
{
	resourceList.free(this);
}

CCmbInstrumentDetailResource::CCmbInstrumentDetailResource(void)
{
}

CCmbInstrumentDetailResource::~CCmbInstrumentDetailResource(void)
{
}

void CCmbInstrumentDetailResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CCmbInstrumentDetail *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CCmbInstrumentDetail *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CCmbInstrumentDetailResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CCmbInstrumentDetail *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CCmbInstrumentDetail *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CCmbInstrumentDetailResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CClientTradingIDResource> CClientTradingIDResource::resourceList;

CClientTradingIDResource * CClientTradingIDResource::alloc(int type, CClientTradingIDFactory *pFactory, CClientTradingID *pObject, CWriteableClientTradingID *pWriteableObject, bool updateIndex)
{
	CClientTradingIDResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CClientTradingIDResource::free(void)
{
	resourceList.free(this);
}

CClientTradingIDResource::CClientTradingIDResource(void)
{
}

CClientTradingIDResource::~CClientTradingIDResource(void)
{
}

void CClientTradingIDResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CClientTradingID *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CClientTradingID *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CClientTradingIDResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CClientTradingID *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CClientTradingID *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CClientTradingIDResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CInvestorResource> CInvestorResource::resourceList;

CInvestorResource * CInvestorResource::alloc(int type, CInvestorFactory *pFactory, CInvestor *pObject, CWriteableInvestor *pWriteableObject, bool updateIndex)
{
	CInvestorResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CInvestorResource::free(void)
{
	resourceList.free(this);
}

CInvestorResource::CInvestorResource(void)
{
}

CInvestorResource::~CInvestorResource(void)
{
}

void CInvestorResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CInvestor *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CInvestor *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CInvestorResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CInvestor *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CInvestor *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CInvestorResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CInvestorMarginResource> CInvestorMarginResource::resourceList;

CInvestorMarginResource * CInvestorMarginResource::alloc(int type, CInvestorMarginFactory *pFactory, CInvestorMargin *pObject, CWriteableInvestorMargin *pWriteableObject, bool updateIndex)
{
	CInvestorMarginResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CInvestorMarginResource::free(void)
{
	resourceList.free(this);
}

CInvestorMarginResource::CInvestorMarginResource(void)
{
}

CInvestorMarginResource::~CInvestorMarginResource(void)
{
}

void CInvestorMarginResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CInvestorMargin *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CInvestorMargin *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CInvestorMarginResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CInvestorMargin *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CInvestorMargin *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CInvestorMarginResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CInvestorFeeResource> CInvestorFeeResource::resourceList;

CInvestorFeeResource * CInvestorFeeResource::alloc(int type, CInvestorFeeFactory *pFactory, CInvestorFee *pObject, CWriteableInvestorFee *pWriteableObject, bool updateIndex)
{
	CInvestorFeeResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CInvestorFeeResource::free(void)
{
	resourceList.free(this);
}

CInvestorFeeResource::CInvestorFeeResource(void)
{
}

CInvestorFeeResource::~CInvestorFeeResource(void)
{
}

void CInvestorFeeResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CInvestorFee *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CInvestorFee *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CInvestorFeeResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CInvestorFee *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CInvestorFee *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CInvestorFeeResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CUserResource> CUserResource::resourceList;

CUserResource * CUserResource::alloc(int type, CUserFactory *pFactory, CUser *pObject, CWriteableUser *pWriteableObject, bool updateIndex)
{
	CUserResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CUserResource::free(void)
{
	resourceList.free(this);
}

CUserResource::CUserResource(void)
{
}

CUserResource::~CUserResource(void)
{
}

void CUserResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CUser *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CUser *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CUserResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CUser *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CUser *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CUserResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CUserInvestorResource> CUserInvestorResource::resourceList;

CUserInvestorResource * CUserInvestorResource::alloc(int type, CUserInvestorFactory *pFactory, CUserInvestor *pObject, CWriteableUserInvestor *pWriteableObject, bool updateIndex)
{
	CUserInvestorResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CUserInvestorResource::free(void)
{
	resourceList.free(this);
}

CUserInvestorResource::CUserInvestorResource(void)
{
}

CUserInvestorResource::~CUserInvestorResource(void)
{
}

void CUserInvestorResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CUserInvestor *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CUserInvestor *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CUserInvestorResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CUserInvestor *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CUserInvestor *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CUserInvestorResource::getPriority(void)
{
	return 2;
}


CMemoryStack<COrderInsertFailedResource> COrderInsertFailedResource::resourceList;

COrderInsertFailedResource * COrderInsertFailedResource::alloc(int type, COrderInsertFailedFactory *pFactory, COrderInsertFailed *pObject, CWriteableOrderInsertFailed *pWriteableObject, bool updateIndex)
{
	COrderInsertFailedResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void COrderInsertFailedResource::free(void)
{
	resourceList.free(this);
}

COrderInsertFailedResource::COrderInsertFailedResource(void)
{
}

COrderInsertFailedResource::~COrderInsertFailedResource(void)
{
}

void COrderInsertFailedResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((COrderInsertFailed *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((COrderInsertFailed *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void COrderInsertFailedResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((COrderInsertFailed *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((COrderInsertFailed *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int COrderInsertFailedResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CUserTradingRightResource> CUserTradingRightResource::resourceList;

CUserTradingRightResource * CUserTradingRightResource::alloc(int type, CUserTradingRightFactory *pFactory, CUserTradingRight *pObject, CWriteableUserTradingRight *pWriteableObject, bool updateIndex)
{
	CUserTradingRightResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CUserTradingRightResource::free(void)
{
	resourceList.free(this);
}

CUserTradingRightResource::CUserTradingRightResource(void)
{
}

CUserTradingRightResource::~CUserTradingRightResource(void)
{
}

void CUserTradingRightResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CUserTradingRight *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CUserTradingRight *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CUserTradingRightResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CUserTradingRight *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CUserTradingRight *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CUserTradingRightResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CCurrentTimeResource> CCurrentTimeResource::resourceList;

CCurrentTimeResource * CCurrentTimeResource::alloc(int type, CCurrentTimeFactory *pFactory, CCurrentTime *pObject, CWriteableCurrentTime *pWriteableObject, bool updateIndex)
{
	CCurrentTimeResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CCurrentTimeResource::free(void)
{
	resourceList.free(this);
}

CCurrentTimeResource::CCurrentTimeResource(void)
{
}

CCurrentTimeResource::~CCurrentTimeResource(void)
{
}

void CCurrentTimeResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CCurrentTime *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CCurrentTime *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CCurrentTimeResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CCurrentTime *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CCurrentTime *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CCurrentTimeResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CUserSessionResource> CUserSessionResource::resourceList;

CUserSessionResource * CUserSessionResource::alloc(int type, CUserSessionFactory *pFactory, CUserSession *pObject, CWriteableUserSession *pWriteableObject, bool updateIndex)
{
	CUserSessionResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CUserSessionResource::free(void)
{
	resourceList.free(this);
}

CUserSessionResource::CUserSessionResource(void)
{
}

CUserSessionResource::~CUserSessionResource(void)
{
}

void CUserSessionResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CUserSession *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CUserSession *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CUserSessionResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CUserSession *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CUserSession *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CUserSessionResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CMaxLocalIDResource> CMaxLocalIDResource::resourceList;

CMaxLocalIDResource * CMaxLocalIDResource::alloc(int type, CMaxLocalIDFactory *pFactory, CMaxLocalID *pObject, CWriteableMaxLocalID *pWriteableObject, bool updateIndex)
{
	CMaxLocalIDResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CMaxLocalIDResource::free(void)
{
	resourceList.free(this);
}

CMaxLocalIDResource::CMaxLocalIDResource(void)
{
}

CMaxLocalIDResource::~CMaxLocalIDResource(void)
{
}

void CMaxLocalIDResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CMaxLocalID *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CMaxLocalID *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CMaxLocalIDResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CMaxLocalID *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CMaxLocalID *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CMaxLocalIDResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CBrkUserIDLocalIDResource> CBrkUserIDLocalIDResource::resourceList;

CBrkUserIDLocalIDResource * CBrkUserIDLocalIDResource::alloc(int type, CBrkUserIDLocalIDFactory *pFactory, CBrkUserIDLocalID *pObject, CWriteableBrkUserIDLocalID *pWriteableObject, bool updateIndex)
{
	CBrkUserIDLocalIDResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CBrkUserIDLocalIDResource::free(void)
{
	resourceList.free(this);
}

CBrkUserIDLocalIDResource::CBrkUserIDLocalIDResource(void)
{
}

CBrkUserIDLocalIDResource::~CBrkUserIDLocalIDResource(void)
{
}

void CBrkUserIDLocalIDResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CBrkUserIDLocalID *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CBrkUserIDLocalID *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CBrkUserIDLocalIDResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CBrkUserIDLocalID *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CBrkUserIDLocalID *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CBrkUserIDLocalIDResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CPartClientInsGroupPositionResource> CPartClientInsGroupPositionResource::resourceList;

CPartClientInsGroupPositionResource * CPartClientInsGroupPositionResource::alloc(int type, CPartClientInsGroupPositionFactory *pFactory, CPartClientInsGroupPosition *pObject, CWriteablePartClientInsGroupPosition *pWriteableObject, bool updateIndex)
{
	CPartClientInsGroupPositionResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CPartClientInsGroupPositionResource::free(void)
{
	resourceList.free(this);
}

CPartClientInsGroupPositionResource::CPartClientInsGroupPositionResource(void)
{
}

CPartClientInsGroupPositionResource::~CPartClientInsGroupPositionResource(void)
{
}

void CPartClientInsGroupPositionResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CPartClientInsGroupPosition *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CPartClientInsGroupPosition *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CPartClientInsGroupPositionResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CPartClientInsGroupPosition *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CPartClientInsGroupPosition *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CPartClientInsGroupPositionResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CClientMarginCombTypeResource> CClientMarginCombTypeResource::resourceList;

CClientMarginCombTypeResource * CClientMarginCombTypeResource::alloc(int type, CClientMarginCombTypeFactory *pFactory, CClientMarginCombType *pObject, CWriteableClientMarginCombType *pWriteableObject, bool updateIndex)
{
	CClientMarginCombTypeResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CClientMarginCombTypeResource::free(void)
{
	resourceList.free(this);
}

CClientMarginCombTypeResource::CClientMarginCombTypeResource(void)
{
}

CClientMarginCombTypeResource::~CClientMarginCombTypeResource(void)
{
}

void CClientMarginCombTypeResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CClientMarginCombType *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CClientMarginCombType *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CClientMarginCombTypeResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CClientMarginCombType *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CClientMarginCombType *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CClientMarginCombTypeResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CInstrumentGroupResource> CInstrumentGroupResource::resourceList;

CInstrumentGroupResource * CInstrumentGroupResource::alloc(int type, CInstrumentGroupFactory *pFactory, CInstrumentGroup *pObject, CWriteableInstrumentGroup *pWriteableObject, bool updateIndex)
{
	CInstrumentGroupResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CInstrumentGroupResource::free(void)
{
	resourceList.free(this);
}

CInstrumentGroupResource::CInstrumentGroupResource(void)
{
}

CInstrumentGroupResource::~CInstrumentGroupResource(void)
{
}

void CInstrumentGroupResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CInstrumentGroup *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CInstrumentGroup *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CInstrumentGroupResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CInstrumentGroup *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CInstrumentGroup *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CInstrumentGroupResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CSGEDeferRateResource> CSGEDeferRateResource::resourceList;

CSGEDeferRateResource * CSGEDeferRateResource::alloc(int type, CSGEDeferRateFactory *pFactory, CSGEDeferRate *pObject, CWriteableSGEDeferRate *pWriteableObject, bool updateIndex)
{
	CSGEDeferRateResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CSGEDeferRateResource::free(void)
{
	resourceList.free(this);
}

CSGEDeferRateResource::CSGEDeferRateResource(void)
{
}

CSGEDeferRateResource::~CSGEDeferRateResource(void)
{
}

void CSGEDeferRateResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CSGEDeferRate *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CSGEDeferRate *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CSGEDeferRateResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CSGEDeferRate *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CSGEDeferRate *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CSGEDeferRateResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CInvestorTradingRightResource> CInvestorTradingRightResource::resourceList;

CInvestorTradingRightResource * CInvestorTradingRightResource::alloc(int type, CInvestorTradingRightFactory *pFactory, CInvestorTradingRight *pObject, CWriteableInvestorTradingRight *pWriteableObject, bool updateIndex)
{
	CInvestorTradingRightResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CInvestorTradingRightResource::free(void)
{
	resourceList.free(this);
}

CInvestorTradingRightResource::CInvestorTradingRightResource(void)
{
}

CInvestorTradingRightResource::~CInvestorTradingRightResource(void)
{
}

void CInvestorTradingRightResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CInvestorTradingRight *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CInvestorTradingRight *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CInvestorTradingRightResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CInvestorTradingRight *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CInvestorTradingRight *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CInvestorTradingRightResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CUserIPResource> CUserIPResource::resourceList;

CUserIPResource * CUserIPResource::alloc(int type, CUserIPFactory *pFactory, CUserIP *pObject, CWriteableUserIP *pWriteableObject, bool updateIndex)
{
	CUserIPResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CUserIPResource::free(void)
{
	resourceList.free(this);
}

CUserIPResource::CUserIPResource(void)
{
}

CUserIPResource::~CUserIPResource(void)
{
}

void CUserIPResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CUserIP *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CUserIP *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CUserIPResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CUserIP *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CUserIP *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CUserIPResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CInvestorOptionFeeResource> CInvestorOptionFeeResource::resourceList;

CInvestorOptionFeeResource * CInvestorOptionFeeResource::alloc(int type, CInvestorOptionFeeFactory *pFactory, CInvestorOptionFee *pObject, CWriteableInvestorOptionFee *pWriteableObject, bool updateIndex)
{
	CInvestorOptionFeeResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CInvestorOptionFeeResource::free(void)
{
	resourceList.free(this);
}

CInvestorOptionFeeResource::CInvestorOptionFeeResource(void)
{
}

CInvestorOptionFeeResource::~CInvestorOptionFeeResource(void)
{
}

void CInvestorOptionFeeResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CInvestorOptionFee *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CInvestorOptionFee *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CInvestorOptionFeeResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CInvestorOptionFee *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CInvestorOptionFee *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CInvestorOptionFeeResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CMarketDataResource> CMarketDataResource::resourceList;

CMarketDataResource * CMarketDataResource::alloc(int type, CMarketDataFactory *pFactory, CMarketData *pObject, CWriteableMarketData *pWriteableObject, bool updateIndex)
{
	CMarketDataResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CMarketDataResource::free(void)
{
	resourceList.free(this);
}

CMarketDataResource::CMarketDataResource(void)
{
}

CMarketDataResource::~CMarketDataResource(void)
{
}

void CMarketDataResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CMarketData *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CMarketData *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CMarketDataResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CMarketData *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CMarketData *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CMarketDataResource::getPriority(void)
{
	return 2;
}


CMemoryStack<COrderDelayResource> COrderDelayResource::resourceList;

COrderDelayResource * COrderDelayResource::alloc(int type, COrderDelayFactory *pFactory, COrderDelay *pObject, CWriteableOrderDelay *pWriteableObject, bool updateIndex)
{
	COrderDelayResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void COrderDelayResource::free(void)
{
	resourceList.free(this);
}

COrderDelayResource::COrderDelayResource(void)
{
}

COrderDelayResource::~COrderDelayResource(void)
{
}

void COrderDelayResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((COrderDelay *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((COrderDelay *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void COrderDelayResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((COrderDelay *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((COrderDelay *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int COrderDelayResource::getPriority(void)
{
	return 2;
}


CMemoryStack<CSystemInfoResource> CSystemInfoResource::resourceList;

CSystemInfoResource * CSystemInfoResource::alloc(int type, CSystemInfoFactory *pFactory, CSystemInfo *pObject, CWriteableSystemInfo *pWriteableObject, bool updateIndex)
{
	CSystemInfoResource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void CSystemInfoResource::free(void)
{
	resourceList.free(this);
}

CSystemInfoResource::CSystemInfoResource(void)
{
}

CSystemInfoResource::~CSystemInfoResource(void)
{
}

void CSystemInfoResource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((CSystemInfo *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((CSystemInfo *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void CSystemInfoResource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((CSystemInfo *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((CSystemInfo *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int CSystemInfoResource::getPriority(void)
{
	return 2;
}

