/////////////////////////////////////////////////////////////////////////
///@system ���ٷ��ǰ�� ִ������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file TradingQueryPredicts.h
///@brief	�����˲�ѯ�õĸ��ֻ�����ν��
///@history 
///20121115		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef TRADINGQUERYPREDICTS_H
#define TRADINGQUERYPREDICTS_H

#include "databaseIteratorRepository.h"

/////////////////////////////////////////////////////////////////////////
///COrderActionExchangeIDPredict���ж�һ�����������Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionExchangeIDPredict: public COrderActionPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderActionExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~COrderActionExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderAction	Ҫ���жϵı�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderAction *pOrderAction);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionOrderSysIDPredict���ж�һ�����������Ƿ����㱨�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionOrderSysIDPredict: public COrderActionPredict
{
private:
	COrderSysIDType *m_pOrderSysIDStart;
	COrderSysIDType *m_pOrderSysIDEnd;
public:
	///���췽��
	///@param	pOrderSysIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pOrderSysIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderActionOrderSysIDPredict(COrderSysIDType *pOrderSysIDStart, COrderSysIDType *pOrderSysIDEnd)
	{
		m_pOrderSysIDStart=pOrderSysIDStart;
		m_pOrderSysIDEnd=pOrderSysIDEnd;
	}

	virtual ~COrderActionOrderSysIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderAction	Ҫ���жϵı�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderAction *pOrderAction);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionBrokerIDPredict���ж�һ�����������Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionBrokerIDPredict: public COrderActionPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderActionBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~COrderActionBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderAction	Ҫ���жϵı�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderAction *pOrderAction);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionInvestorIDPredict���ж�һ�����������Ƿ�����Ͷ���߱��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionInvestorIDPredict: public COrderActionPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderActionInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~COrderActionInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderAction	Ҫ���жϵı�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderAction *pOrderAction);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionUserIDPredict���ж�һ�����������Ƿ������û�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionUserIDPredict: public COrderActionPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///���췽��
	///@param	pUserIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pUserIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderActionUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~COrderActionUserIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderAction	Ҫ���жϵı�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderAction *pOrderAction);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionInstrumentIDStartPredict���ж�һ�����������Ƿ����㿪ʼ�ĺ�Լ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionInstrumentIDStartPredict: public COrderActionPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///���췽��
	///@param	pInstrumentIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInstrumentIDEnd	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	COrderActionInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~COrderActionInstrumentIDStartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderAction	Ҫ���жϵı�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderAction *pOrderAction);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionClientIDPredict���ж�һ�����������Ƿ�����ͻ�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionClientIDPredict: public COrderActionPredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///���췽��
	///@param	pClientIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pClientIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderActionClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~COrderActionClientIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderAction	Ҫ���жϵı�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderAction *pOrderAction);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionParticipantIDPredict���ж�һ�����������Ƿ������Ա����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionParticipantIDPredict: public COrderActionPredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///���췽��
	///@param	pParticipantIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pParticipantIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderActionParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~COrderActionParticipantIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderAction	Ҫ���жϵı�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderAction *pOrderAction);
};

/////////////////////////////////////////////////////////////////////////
///COrderBrokerIDPredict���ж�һ��ί�б��Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderBrokerIDPredict: public COrderPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~COrderBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrder	Ҫ���жϵ�ί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderExchangeIDPredict���ж�һ��ί�б��Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderExchangeIDPredict: public COrderPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~COrderExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrder	Ҫ���жϵ�ί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderOrderSysIDPredict���ж�һ��ί�б��Ƿ�����ϵͳ�������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderOrderSysIDPredict: public COrderPredict
{
private:
	COrderSysIDType *m_pOrderSysIDStart;
	COrderSysIDType *m_pOrderSysIDEnd;
public:
	///���췽��
	///@param	pOrderSysIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pOrderSysIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderOrderSysIDPredict(COrderSysIDType *pOrderSysIDStart, COrderSysIDType *pOrderSysIDEnd)
	{
		m_pOrderSysIDStart=pOrderSysIDStart;
		m_pOrderSysIDEnd=pOrderSysIDEnd;
	}

	virtual ~COrderOrderSysIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrder	Ҫ���жϵ�ί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderInvestorIDPredict���ж�һ��ί�б��Ƿ�����Ͷ���߱��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInvestorIDPredict: public COrderPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~COrderInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrder	Ҫ���жϵ�ί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderUserIDPredict���ж�һ��ί�б��Ƿ������û�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderUserIDPredict: public COrderPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///���췽��
	///@param	pUserIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pUserIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~COrderUserIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrder	Ҫ���жϵ�ί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderInstrumentIDStartPredict���ж�һ��ί�б��Ƿ����㿪ʼ�ĺ�Լ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInstrumentIDStartPredict: public COrderPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///���췽��
	///@param	pInstrumentIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInstrumentIDEnd	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	COrderInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~COrderInstrumentIDStartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrder	Ҫ���жϵ�ί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderDirectionPredict���ж�һ��ί�б��Ƿ�������������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDirectionPredict: public COrderPredict
{
private:
	CDirectionType *m_pDirectionStart;
	CDirectionType *m_pDirectionEnd;
public:
	///���췽��
	///@param	pDirectionStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pDirectionEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderDirectionPredict(CDirectionType *pDirectionStart, CDirectionType *pDirectionEnd)
	{
		m_pDirectionStart=pDirectionStart;
		m_pDirectionEnd=pDirectionEnd;
	}

	virtual ~COrderDirectionPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrder	Ҫ���жϵ�ί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderParticipantIDPredict���ж�һ��ί�б��Ƿ������Ա���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderParticipantIDPredict: public COrderPredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///���췽��
	///@param	pParticipantIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pParticipantIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~COrderParticipantIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrder	Ҫ���жϵ�ί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderClientIDPredict���ж�һ��ί�б��Ƿ�����ͻ���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderClientIDPredict: public COrderPredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///���췽��
	///@param	pClientIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pClientIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~COrderClientIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrder	Ҫ���жϵ�ί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertTimePredict���ж�һ��ί�б��Ƿ��������ʱ��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertTimePredict: public COrderPredict
{
private:
	CTimeType *m_pInsertTimeStart;
	CTimeType *m_pInsertTimeEnd;
public:
	///���췽��
	///@param	pInsertTimeStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInsertTimeEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderInsertTimePredict(CTimeType *pInsertTimeStart, CTimeType *pInsertTimeEnd)
	{
		m_pInsertTimeStart=pInsertTimeStart;
		m_pInsertTimeEnd=pInsertTimeEnd;
	}

	virtual ~COrderInsertTimePredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrder	Ҫ���жϵ�ί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderAccountIDPredict���ж�һ��ί�б��Ƿ������ʽ��ʺ�������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderAccountIDPredict: public COrderPredict
{
private:
	CAccountIDType *m_pAccountIDStart;
	CAccountIDType *m_pAccountIDEnd;
public:
	///���췽��
	///@param	pAccountIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pAccountIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderAccountIDPredict(CAccountIDType *pAccountIDStart, CAccountIDType *pAccountIDEnd)
	{
		m_pAccountIDStart=pAccountIDStart;
		m_pAccountIDEnd=pAccountIDEnd;
	}

	virtual ~COrderAccountIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrder	Ҫ���жϵ�ί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///CTradeBrokerIDPredict���ж�һ���ɽ����Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeBrokerIDPredict: public CTradePredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CTradeBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CTradeBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeExchangeIDPredict���ж�һ���ɽ����Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeExchangeIDPredict: public CTradePredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CTradeExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CTradeExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeParticipantIDPredict���ж�һ���ɽ����Ƿ������Ա���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeParticipantIDPredict: public CTradePredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///���췽��
	///@param	pParticipantIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pParticipantIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CTradeParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~CTradeParticipantIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeInvestorIDPredict���ж�һ���ɽ����Ƿ�����Ͷ���߱��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeInvestorIDPredict: public CTradePredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CTradeInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CTradeInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeClientIDPredict���ж�һ���ɽ����Ƿ�����ͻ���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeClientIDPredict: public CTradePredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///���췽��
	///@param	pClientIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pClientIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CTradeClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~CTradeClientIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeUserIDPredict���ж�һ���ɽ����Ƿ������û����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeUserIDPredict: public CTradePredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///���췽��
	///@param	pUserIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pUserIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CTradeUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CTradeUserIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeTradeIDPredict���ж�һ���ɽ����Ƿ�����ɽ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeTradeIDPredict: public CTradePredict
{
private:
	CTradeIDType *m_pTradeIDStart;
	CTradeIDType *m_pTradeIDEnd;
public:
	///���췽��
	///@param	pTradeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pTradeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CTradeTradeIDPredict(CTradeIDType *pTradeIDStart, CTradeIDType *pTradeIDEnd)
	{
		m_pTradeIDStart=pTradeIDStart;
		m_pTradeIDEnd=pTradeIDEnd;
	}

	virtual ~CTradeTradeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeOrderSysIDPredict���ж�һ���ɽ����Ƿ����㱨�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeOrderSysIDPredict: public CTradePredict
{
private:
	COrderSysIDType *m_pOrderSysIDStart;
	COrderSysIDType *m_pOrderSysIDEnd;
public:
	///���췽��
	///@param	pOrderSysIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pOrderSysIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CTradeOrderSysIDPredict(COrderSysIDType *pOrderSysIDStart, COrderSysIDType *pOrderSysIDEnd)
	{
		m_pOrderSysIDStart=pOrderSysIDStart;
		m_pOrderSysIDEnd=pOrderSysIDEnd;
	}

	virtual ~CTradeOrderSysIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeInstrumentIDStartPredict���ж�һ���ɽ����Ƿ����㿪ʼ�ĺ�Լ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeInstrumentIDStartPredict: public CTradePredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///���췽��
	///@param	pInstrumentIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInstrumentIDEnd	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	CTradeInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CTradeInstrumentIDStartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeDirectionPredict���ж�һ���ɽ����Ƿ�������������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeDirectionPredict: public CTradePredict
{
private:
	CDirectionType *m_pDirectionStart;
	CDirectionType *m_pDirectionEnd;
public:
	///���췽��
	///@param	pDirectionStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pDirectionEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CTradeDirectionPredict(CDirectionType *pDirectionStart, CDirectionType *pDirectionEnd)
	{
		m_pDirectionStart=pDirectionStart;
		m_pDirectionEnd=pDirectionEnd;
	}

	virtual ~CTradeDirectionPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeTradeTimePredict���ж�һ���ɽ����Ƿ�����ɽ�ʱ��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeTradeTimePredict: public CTradePredict
{
private:
	CTimeType *m_pTradeTimeStart;
	CTimeType *m_pTradeTimeEnd;
public:
	///���췽��
	///@param	pTradeTimeStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pTradeTimeEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CTradeTradeTimePredict(CTimeType *pTradeTimeStart, CTimeType *pTradeTimeEnd)
	{
		m_pTradeTimeStart=pTradeTimeStart;
		m_pTradeTimeEnd=pTradeTimeEnd;
	}

	virtual ~CTradeTradeTimePredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeClearingPartIDPredict���ж�һ���ɽ����Ƿ����������Ա���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeClearingPartIDPredict: public CTradePredict
{
private:
	CParticipantIDType *m_pClearingPartIDStart;
	CParticipantIDType *m_pClearingPartIDEnd;
public:
	///���췽��
	///@param	pClearingPartIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pClearingPartIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CTradeClearingPartIDPredict(CParticipantIDType *pClearingPartIDStart, CParticipantIDType *pClearingPartIDEnd)
	{
		m_pClearingPartIDStart=pClearingPartIDStart;
		m_pClearingPartIDEnd=pClearingPartIDEnd;
	}

	virtual ~CTradeClearingPartIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeAccountIDPredict���ж�һ���ɽ����Ƿ������ʽ��ʺ�������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeAccountIDPredict: public CTradePredict
{
private:
	CAccountIDType *m_pAccountIDStart;
	CAccountIDType *m_pAccountIDEnd;
public:
	///���췽��
	///@param	pAccountIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pAccountIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CTradeAccountIDPredict(CAccountIDType *pAccountIDStart, CAccountIDType *pAccountIDEnd)
	{
		m_pAccountIDStart=pAccountIDStart;
		m_pAccountIDEnd=pAccountIDEnd;
	}

	virtual ~CTradeAccountIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderBrokerIDPredict���ж�һ��Ԥί�б��Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderBrokerIDPredict: public CPreOrderPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CPreOrderBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CPreOrderBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pPreOrder	Ҫ���жϵ�Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderExchangeIDPredict���ж�һ��Ԥί�б��Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderExchangeIDPredict: public CPreOrderPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CPreOrderExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CPreOrderExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pPreOrder	Ҫ���жϵ�Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderOrderSysIDPredict���ж�һ��Ԥί�б��Ƿ�����ϵͳ�������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderOrderSysIDPredict: public CPreOrderPredict
{
private:
	COrderSysIDType *m_pOrderSysIDStart;
	COrderSysIDType *m_pOrderSysIDEnd;
public:
	///���췽��
	///@param	pOrderSysIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pOrderSysIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CPreOrderOrderSysIDPredict(COrderSysIDType *pOrderSysIDStart, COrderSysIDType *pOrderSysIDEnd)
	{
		m_pOrderSysIDStart=pOrderSysIDStart;
		m_pOrderSysIDEnd=pOrderSysIDEnd;
	}

	virtual ~CPreOrderOrderSysIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pPreOrder	Ҫ���жϵ�Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderInvestorIDPredict���ж�һ��Ԥί�б��Ƿ�����Ͷ���߱��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderInvestorIDPredict: public CPreOrderPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CPreOrderInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CPreOrderInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pPreOrder	Ҫ���жϵ�Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderUserIDPredict���ж�һ��Ԥί�б��Ƿ������û�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderUserIDPredict: public CPreOrderPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///���췽��
	///@param	pUserIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pUserIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CPreOrderUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CPreOrderUserIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pPreOrder	Ҫ���жϵ�Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderInstrumentIDStartPredict���ж�һ��Ԥί�б��Ƿ����㿪ʼ�ĺ�Լ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderInstrumentIDStartPredict: public CPreOrderPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///���췽��
	///@param	pInstrumentIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInstrumentIDEnd	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	CPreOrderInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CPreOrderInstrumentIDStartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pPreOrder	Ҫ���жϵ�Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderDirectionPredict���ж�һ��Ԥί�б��Ƿ�������������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderDirectionPredict: public CPreOrderPredict
{
private:
	CDirectionType *m_pDirectionStart;
	CDirectionType *m_pDirectionEnd;
public:
	///���췽��
	///@param	pDirectionStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pDirectionEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CPreOrderDirectionPredict(CDirectionType *pDirectionStart, CDirectionType *pDirectionEnd)
	{
		m_pDirectionStart=pDirectionStart;
		m_pDirectionEnd=pDirectionEnd;
	}

	virtual ~CPreOrderDirectionPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pPreOrder	Ҫ���жϵ�Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderParticipantIDPredict���ж�һ��Ԥί�б��Ƿ������Ա���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderParticipantIDPredict: public CPreOrderPredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///���췽��
	///@param	pParticipantIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pParticipantIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CPreOrderParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~CPreOrderParticipantIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pPreOrder	Ҫ���жϵ�Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderClientIDPredict���ж�һ��Ԥί�б��Ƿ�����ͻ���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderClientIDPredict: public CPreOrderPredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///���췽��
	///@param	pClientIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pClientIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CPreOrderClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~CPreOrderClientIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pPreOrder	Ҫ���жϵ�Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderInsertTimePredict���ж�һ��Ԥί�б��Ƿ��������ʱ��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderInsertTimePredict: public CPreOrderPredict
{
private:
	CTimeType *m_pInsertTimeStart;
	CTimeType *m_pInsertTimeEnd;
public:
	///���췽��
	///@param	pInsertTimeStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInsertTimeEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CPreOrderInsertTimePredict(CTimeType *pInsertTimeStart, CTimeType *pInsertTimeEnd)
	{
		m_pInsertTimeStart=pInsertTimeStart;
		m_pInsertTimeEnd=pInsertTimeEnd;
	}

	virtual ~CPreOrderInsertTimePredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pPreOrder	Ҫ���жϵ�Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderAccountIDPredict���ж�һ��Ԥί�б��Ƿ������ʽ��ʺ�������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderAccountIDPredict: public CPreOrderPredict
{
private:
	CAccountIDType *m_pAccountIDStart;
	CAccountIDType *m_pAccountIDEnd;
public:
	///���췽��
	///@param	pAccountIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pAccountIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CPreOrderAccountIDPredict(CAccountIDType *pAccountIDStart, CAccountIDType *pAccountIDEnd)
	{
		m_pAccountIDStart=pAccountIDStart;
		m_pAccountIDEnd=pAccountIDEnd;
	}

	virtual ~CPreOrderAccountIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pPreOrder	Ҫ���жϵ�Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderBrokerIDPredict���ж�һ������Ԥί�б��Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderBrokerIDPredict: public CIndexPreOrderPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CIndexPreOrderBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CIndexPreOrderBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pIndexPreOrder	Ҫ���жϵ�����Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderExchangeIDPredict���ж�һ������Ԥί�б��Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderExchangeIDPredict: public CIndexPreOrderPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CIndexPreOrderExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CIndexPreOrderExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pIndexPreOrder	Ҫ���жϵ�����Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderInvestorIDPredict���ж�һ������Ԥί�б��Ƿ�����Ͷ���߱��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderInvestorIDPredict: public CIndexPreOrderPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CIndexPreOrderInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CIndexPreOrderInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pIndexPreOrder	Ҫ���жϵ�����Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderInstrumentIDStartPredict���ж�һ������Ԥί�б��Ƿ����㿪ʼ�ĺ�Լ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderInstrumentIDStartPredict: public CIndexPreOrderPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///���췽��
	///@param	pInstrumentIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInstrumentIDEnd	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	CIndexPreOrderInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CIndexPreOrderInstrumentIDStartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pIndexPreOrder	Ҫ���жϵ�����Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderDirectionPredict���ж�һ������Ԥί�б��Ƿ�������������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderDirectionPredict: public CIndexPreOrderPredict
{
private:
	CDirectionType *m_pDirectionStart;
	CDirectionType *m_pDirectionEnd;
public:
	///���췽��
	///@param	pDirectionStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pDirectionEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CIndexPreOrderDirectionPredict(CDirectionType *pDirectionStart, CDirectionType *pDirectionEnd)
	{
		m_pDirectionStart=pDirectionStart;
		m_pDirectionEnd=pDirectionEnd;
	}

	virtual ~CIndexPreOrderDirectionPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pIndexPreOrder	Ҫ���жϵ�����Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderClientIDPredict���ж�һ������Ԥί�б��Ƿ����㽻�ױ���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderClientIDPredict: public CIndexPreOrderPredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///���췽��
	///@param	pClientIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pClientIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CIndexPreOrderClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~CIndexPreOrderClientIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pIndexPreOrder	Ҫ���жϵ�����Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionBrokerIDPredict���ж�һ���ֱֲ��Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionBrokerIDPredict: public CInvestorPositionPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorPositionBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInvestorPositionBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorPosition	Ҫ���жϵĳֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorPosition *pInvestorPosition);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionExchangeIDPredict���ж�һ���ֱֲ��Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionExchangeIDPredict: public CInvestorPositionPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorPositionExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CInvestorPositionExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorPosition	Ҫ���жϵĳֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorPosition *pInvestorPosition);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionInvestorIDPredict���ж�һ���ֱֲ��Ƿ�����Ͷ���߱��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionInvestorIDPredict: public CInvestorPositionPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorPositionInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CInvestorPositionInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorPosition	Ҫ���жϵĳֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorPosition *pInvestorPosition);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionParticipantIDPredict���ж�һ���ֱֲ��Ƿ������Ա���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionParticipantIDPredict: public CInvestorPositionPredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///���췽��
	///@param	pParticipantIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pParticipantIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorPositionParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~CInvestorPositionParticipantIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorPosition	Ҫ���жϵĳֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorPosition *pInvestorPosition);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionClientIDPredict���ж�һ���ֱֲ��Ƿ�����ͻ�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionClientIDPredict: public CInvestorPositionPredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///���췽��
	///@param	pClientIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pClientIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorPositionClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~CInvestorPositionClientIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorPosition	Ҫ���жϵĳֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorPosition *pInvestorPosition);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionInstrumentIDStartPredict���ж�һ���ֱֲ��Ƿ����㿪ʼ�ĺ�Լ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionInstrumentIDStartPredict: public CInvestorPositionPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///���췽��
	///@param	pInstrumentIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInstrumentIDEnd	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorPositionInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CInvestorPositionInstrumentIDStartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorPosition	Ҫ���жϵĳֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorPosition *pInvestorPosition);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionDirectionPredict���ж�һ���ֱֲ��Ƿ�������������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionDirectionPredict: public CInvestorPositionPredict
{
private:
	CDirectionType *m_pDirectionStart;
	CDirectionType *m_pDirectionEnd;
public:
	///���췽��
	///@param	pDirectionStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pDirectionEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorPositionDirectionPredict(CDirectionType *pDirectionStart, CDirectionType *pDirectionEnd)
	{
		m_pDirectionStart=pDirectionStart;
		m_pDirectionEnd=pDirectionEnd;
	}

	virtual ~CInvestorPositionDirectionPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorPosition	Ҫ���жϵĳֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorPosition *pInvestorPosition);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionAccountIDPredict���ж�һ���ֱֲ��Ƿ������ʽ��ʺ�������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionAccountIDPredict: public CInvestorPositionPredict
{
private:
	CAccountIDType *m_pAccountIDStart;
	CAccountIDType *m_pAccountIDEnd;
public:
	///���췽��
	///@param	pAccountIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pAccountIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorPositionAccountIDPredict(CAccountIDType *pAccountIDStart, CAccountIDType *pAccountIDEnd)
	{
		m_pAccountIDStart=pAccountIDStart;
		m_pAccountIDEnd=pAccountIDEnd;
	}

	virtual ~CInvestorPositionAccountIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorPosition	Ҫ���жϵĳֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorPosition *pInvestorPosition);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountBrokerIDPredict���ж�һ���˻�ʵʱ�ʽ���Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountBrokerIDPredict: public CInvestorAccountPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorAccountBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInvestorAccountBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorAccount	Ҫ���жϵ��˻�ʵʱ�ʽ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorAccount *pInvestorAccount);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountInvestorIDPredict���ж�һ���˻�ʵʱ�ʽ���Ƿ�����Ͷ���߱��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountInvestorIDPredict: public CInvestorAccountPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorAccountInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CInvestorAccountInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorAccount	Ҫ���жϵ��˻�ʵʱ�ʽ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorAccount *pInvestorAccount);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountAccountIDPredict���ж�һ���˻�ʵʱ�ʽ���Ƿ������ʽ��ʺ�������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountAccountIDPredict: public CInvestorAccountPredict
{
private:
	CAccountIDType *m_pAccountIDStart;
	CAccountIDType *m_pAccountIDEnd;
public:
	///���췽��
	///@param	pAccountIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pAccountIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorAccountAccountIDPredict(CAccountIDType *pAccountIDStart, CAccountIDType *pAccountIDEnd)
	{
		m_pAccountIDStart=pAccountIDStart;
		m_pAccountIDEnd=pAccountIDEnd;
	}

	virtual ~CInvestorAccountAccountIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorAccount	Ҫ���жϵ��˻�ʵʱ�ʽ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorAccount *pInvestorAccount);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositBrokerIDPredict���ж�һ���˻�ʵʱ�������Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositBrokerIDPredict: public CInvestorAccountDepositPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorAccountDepositBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInvestorAccountDepositBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorAccountDeposit	Ҫ���жϵ��˻�ʵʱ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorAccountDeposit *pInvestorAccountDeposit);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositAccountIDPredict���ж�һ���˻�ʵʱ�������Ƿ������ʽ��ʺ�������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositAccountIDPredict: public CInvestorAccountDepositPredict
{
private:
	CAccountIDType *m_pAccountIDStart;
	CAccountIDType *m_pAccountIDEnd;
public:
	///���췽��
	///@param	pAccountIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pAccountIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorAccountDepositAccountIDPredict(CAccountIDType *pAccountIDStart, CAccountIDType *pAccountIDEnd)
	{
		m_pAccountIDStart=pAccountIDStart;
		m_pAccountIDEnd=pAccountIDEnd;
	}

	virtual ~CInvestorAccountDepositAccountIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorAccountDeposit	Ҫ���жϵ��˻�ʵʱ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorAccountDeposit *pInvestorAccountDeposit);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositInvestorIDPredict���ж�һ���˻�ʵʱ�������Ƿ�����Ͷ���߱��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositInvestorIDPredict: public CInvestorAccountDepositPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorAccountDepositInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CInvestorAccountDepositInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorAccountDeposit	Ҫ���жϵ��˻�ʵʱ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorAccountDeposit *pInvestorAccountDeposit);
};

/////////////////////////////////////////////////////////////////////////
///CExchangeExchangeIDPredict���ж�һ�����������Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeExchangeIDPredict: public CExchangePredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CExchangeExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CExchangeExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pExchange	Ҫ���жϵĽ�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CExchange *pExchange);
};

/////////////////////////////////////////////////////////////////////////
///CSeatBrokerIDPredict���ж�һ���µ�ϯλ���Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatBrokerIDPredict: public CSeatPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CSeatBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CSeatBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pSeat	Ҫ���жϵ��µ�ϯλ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSeat *pSeat);
};

/////////////////////////////////////////////////////////////////////////
///CSeatExchangeIDPredict���ж�һ���µ�ϯλ���Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatExchangeIDPredict: public CSeatPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CSeatExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CSeatExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pSeat	Ҫ���жϵ��µ�ϯλ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSeat *pSeat);
};

/////////////////////////////////////////////////////////////////////////
///CSeatParticipantIDPredict���ж�һ���µ�ϯλ���Ƿ������Ա���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatParticipantIDPredict: public CSeatPredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///���췽��
	///@param	pParticipantIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pParticipantIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CSeatParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~CSeatParticipantIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pSeat	Ҫ���жϵ��µ�ϯλ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSeat *pSeat);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentExchangeIDPredict���ж�һ���ڻ���Լ���Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentExchangeIDPredict: public CInstrumentPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInstrumentExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CInstrumentExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInstrument	Ҫ���жϵ��ڻ���Լ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInstrument *pInstrument);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentProductIDPredict���ж�һ���ڻ���Լ���Ƿ�����Ʒ�ִ���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentProductIDPredict: public CInstrumentPredict
{
private:
	CProductIDType *m_pProductIDStart;
	CProductIDType *m_pProductIDEnd;
public:
	///���췽��
	///@param	pProductIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pProductIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInstrumentProductIDPredict(CProductIDType *pProductIDStart, CProductIDType *pProductIDEnd)
	{
		m_pProductIDStart=pProductIDStart;
		m_pProductIDEnd=pProductIDEnd;
	}

	virtual ~CInstrumentProductIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInstrument	Ҫ���жϵ��ڻ���Լ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInstrument *pInstrument);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentInstrumentIDStartPredict���ж�һ���ڻ���Լ���Ƿ����㿪ʼ�ĺ�Լ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentInstrumentIDStartPredict: public CInstrumentPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///���췽��
	///@param	pInstrumentIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInstrumentIDEnd	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	CInstrumentInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CInstrumentInstrumentIDStartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInstrument	Ҫ���жϵ��ڻ���Լ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInstrument *pInstrument);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentProductGroupIDPredict���ж�һ���ڻ���Լ���Ƿ������Ʒ��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentProductGroupIDPredict: public CInstrumentPredict
{
private:
	CProductGroupIDType *m_pProductGroupIDStart;
	CProductGroupIDType *m_pProductGroupIDEnd;
public:
	///���췽��
	///@param	pProductGroupIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pProductGroupIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInstrumentProductGroupIDPredict(CProductGroupIDType *pProductGroupIDStart, CProductGroupIDType *pProductGroupIDEnd)
	{
		m_pProductGroupIDStart=pProductGroupIDStart;
		m_pProductGroupIDEnd=pProductGroupIDEnd;
	}

	virtual ~CInstrumentProductGroupIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInstrument	Ҫ���жϵ��ڻ���Լ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInstrument *pInstrument);
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailExchangeIDPredict���ж�һ���ڻ���Ϻ�Լ��ϸ���Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailExchangeIDPredict: public CCmbInstrumentDetailPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CCmbInstrumentDetailExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CCmbInstrumentDetailExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pCmbInstrumentDetail	Ҫ���жϵ��ڻ���Ϻ�Լ��ϸ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CCmbInstrumentDetail *pCmbInstrumentDetail);
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailDirectionPredict���ж�һ���ڻ���Ϻ�Լ��ϸ���Ƿ�������������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailDirectionPredict: public CCmbInstrumentDetailPredict
{
private:
	CDirectionType *m_pDirectionStart;
	CDirectionType *m_pDirectionEnd;
public:
	///���췽��
	///@param	pDirectionStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pDirectionEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CCmbInstrumentDetailDirectionPredict(CDirectionType *pDirectionStart, CDirectionType *pDirectionEnd)
	{
		m_pDirectionStart=pDirectionStart;
		m_pDirectionEnd=pDirectionEnd;
	}

	virtual ~CCmbInstrumentDetailDirectionPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pCmbInstrumentDetail	Ҫ���жϵ��ڻ���Ϻ�Լ��ϸ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CCmbInstrumentDetail *pCmbInstrumentDetail);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDBrokerIDPredict���ж�һ���������ͻ�������Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDBrokerIDPredict: public CClientTradingIDPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CClientTradingIDBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CClientTradingIDBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pClientTradingID	Ҫ���жϵĽ������ͻ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientTradingID *pClientTradingID);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDInvestorIDPredict���ж�һ���������ͻ�������Ƿ�����Ͷ���߱��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDInvestorIDPredict: public CClientTradingIDPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CClientTradingIDInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CClientTradingIDInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pClientTradingID	Ҫ���жϵĽ������ͻ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientTradingID *pClientTradingID);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDAccountIDPredict���ж�һ���������ͻ�������Ƿ������ʽ��ʺ�������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDAccountIDPredict: public CClientTradingIDPredict
{
private:
	CAccountIDType *m_pAccountIDStart;
	CAccountIDType *m_pAccountIDEnd;
public:
	///���췽��
	///@param	pAccountIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pAccountIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CClientTradingIDAccountIDPredict(CAccountIDType *pAccountIDStart, CAccountIDType *pAccountIDEnd)
	{
		m_pAccountIDStart=pAccountIDStart;
		m_pAccountIDEnd=pAccountIDEnd;
	}

	virtual ~CClientTradingIDAccountIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pClientTradingID	Ҫ���жϵĽ������ͻ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientTradingID *pClientTradingID);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDExchangeIDPredict���ж�һ���������ͻ�������Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDExchangeIDPredict: public CClientTradingIDPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CClientTradingIDExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CClientTradingIDExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pClientTradingID	Ҫ���жϵĽ������ͻ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientTradingID *pClientTradingID);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDParticipantIDPredict���ж�һ���������ͻ�������Ƿ������Ա���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDParticipantIDPredict: public CClientTradingIDPredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///���췽��
	///@param	pParticipantIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pParticipantIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CClientTradingIDParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~CClientTradingIDParticipantIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pClientTradingID	Ҫ���жϵĽ������ͻ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientTradingID *pClientTradingID);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDClientIDPredict���ж�һ���������ͻ�������Ƿ�����ͻ�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDClientIDPredict: public CClientTradingIDPredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///���췽��
	///@param	pClientIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pClientIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CClientTradingIDClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~CClientTradingIDClientIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pClientTradingID	Ҫ���жϵĽ������ͻ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientTradingID *pClientTradingID);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorBrokerIDPredict���ж�һ��Ͷ������Ϣ���Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorBrokerIDPredict: public CInvestorPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInvestorBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestor	Ҫ���жϵ�Ͷ������Ϣ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestor *pInvestor);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorInvestorIDPredict���ж�һ��Ͷ������Ϣ���Ƿ�����Ͷ���߱��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorInvestorIDPredict: public CInvestorPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CInvestorInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestor	Ҫ���жϵ�Ͷ������Ϣ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestor *pInvestor);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginBrokerIDPredict���ж�һ���ͻ��ڻ���֤���ʱ��Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginBrokerIDPredict: public CInvestorMarginPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorMarginBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInvestorMarginBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorMargin	Ҫ���жϵĿͻ��ڻ���֤���ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorMargin *pInvestorMargin);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginExchangeIDPredict���ж�һ���ͻ��ڻ���֤���ʱ��Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginExchangeIDPredict: public CInvestorMarginPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorMarginExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CInvestorMarginExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorMargin	Ҫ���жϵĿͻ��ڻ���֤���ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorMargin *pInvestorMargin);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginInvestorIDPredict���ж�һ���ͻ��ڻ���֤���ʱ��Ƿ�����Ͷ���߱���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginInvestorIDPredict: public CInvestorMarginPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorMarginInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CInvestorMarginInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorMargin	Ҫ���жϵĿͻ��ڻ���֤���ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorMargin *pInvestorMargin);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginInstrumentIDStartPredict���ж�һ���ͻ��ڻ���֤���ʱ��Ƿ����㿪ʼ�ĺ�Լ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginInstrumentIDStartPredict: public CInvestorMarginPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///���췽��
	///@param	pInstrumentIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInstrumentIDEnd	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorMarginInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CInvestorMarginInstrumentIDStartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorMargin	Ҫ���жϵĿͻ��ڻ���֤���ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorMargin *pInvestorMargin);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeBrokerIDPredict���ж�һ���ͻ��������ʱ��Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeBrokerIDPredict: public CInvestorFeePredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorFeeBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInvestorFeeBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorFee	Ҫ���жϵĿͻ��������ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorFee *pInvestorFee);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeExchangeIDPredict���ж�һ���ͻ��������ʱ��Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeExchangeIDPredict: public CInvestorFeePredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorFeeExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CInvestorFeeExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorFee	Ҫ���жϵĿͻ��������ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorFee *pInvestorFee);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeInvestorIDPredict���ж�һ���ͻ��������ʱ��Ƿ�����Ͷ���߱���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeInvestorIDPredict: public CInvestorFeePredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorFeeInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CInvestorFeeInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorFee	Ҫ���жϵĿͻ��������ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorFee *pInvestorFee);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeInstrumentIDStartPredict���ж�һ���ͻ��������ʱ��Ƿ����㿪ʼ�ĺ�Լ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeInstrumentIDStartPredict: public CInvestorFeePredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///���췽��
	///@param	pInstrumentIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInstrumentIDEnd	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorFeeInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CInvestorFeeInstrumentIDStartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorFee	Ҫ���жϵĿͻ��������ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorFee *pInvestorFee);
};

/////////////////////////////////////////////////////////////////////////
///CUserBrokerIDPredict���ж�һ���û����Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserBrokerIDPredict: public CUserPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CUserBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CUserBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pUser	Ҫ���жϵ��û���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUser *pUser);
};

/////////////////////////////////////////////////////////////////////////
///CUserUserIDPredict���ж�һ���û����Ƿ������û�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserUserIDPredict: public CUserPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///���췽��
	///@param	pUserIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pUserIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CUserUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CUserUserIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pUser	Ҫ���жϵ��û���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUser *pUser);
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorBrokerIDPredict���ж�һ���û�Ͷ���߹�ϵ���Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorBrokerIDPredict: public CUserInvestorPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CUserInvestorBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CUserInvestorBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pUserInvestor	Ҫ���жϵ��û�Ͷ���߹�ϵ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserInvestor *pUserInvestor);
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorUserIDPredict���ж�һ���û�Ͷ���߹�ϵ���Ƿ����㽻���û�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorUserIDPredict: public CUserInvestorPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///���췽��
	///@param	pUserIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pUserIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CUserInvestorUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CUserInvestorUserIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pUserInvestor	Ҫ���жϵ��û�Ͷ���߹�ϵ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserInvestor *pUserInvestor);
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorInvestorIDPredict���ж�һ���û�Ͷ���߹�ϵ���Ƿ�����Ͷ���߱��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorInvestorIDPredict: public CUserInvestorPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CUserInvestorInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CUserInvestorInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pUserInvestor	Ҫ���жϵ��û�Ͷ���߹�ϵ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserInvestor *pUserInvestor);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedBrokerIDPredict���ж�һ�������Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedBrokerIDPredict: public COrderInsertFailedPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderInsertFailedBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~COrderInsertFailedBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderInsertFailed	Ҫ���жϵĴ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedExchangeIDPredict���ж�һ�������Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedExchangeIDPredict: public COrderInsertFailedPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderInsertFailedExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~COrderInsertFailedExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderInsertFailed	Ҫ���жϵĴ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedOrderSysIDPredict���ж�һ�������Ƿ�����ϵͳ�������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedOrderSysIDPredict: public COrderInsertFailedPredict
{
private:
	COrderSysIDType *m_pOrderSysIDStart;
	COrderSysIDType *m_pOrderSysIDEnd;
public:
	///���췽��
	///@param	pOrderSysIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pOrderSysIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderInsertFailedOrderSysIDPredict(COrderSysIDType *pOrderSysIDStart, COrderSysIDType *pOrderSysIDEnd)
	{
		m_pOrderSysIDStart=pOrderSysIDStart;
		m_pOrderSysIDEnd=pOrderSysIDEnd;
	}

	virtual ~COrderInsertFailedOrderSysIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderInsertFailed	Ҫ���жϵĴ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedInvestorIDPredict���ж�һ�������Ƿ�����Ͷ���߱��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedInvestorIDPredict: public COrderInsertFailedPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderInsertFailedInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~COrderInsertFailedInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderInsertFailed	Ҫ���жϵĴ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedUserIDPredict���ж�һ�������Ƿ������û�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedUserIDPredict: public COrderInsertFailedPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///���췽��
	///@param	pUserIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pUserIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderInsertFailedUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~COrderInsertFailedUserIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderInsertFailed	Ҫ���жϵĴ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedInstrumentIDStartPredict���ж�һ�������Ƿ����㿪ʼ�ĺ�Լ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedInstrumentIDStartPredict: public COrderInsertFailedPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///���췽��
	///@param	pInstrumentIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInstrumentIDEnd	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	COrderInsertFailedInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~COrderInsertFailedInstrumentIDStartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderInsertFailed	Ҫ���жϵĴ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedDirectionPredict���ж�һ�������Ƿ�������������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedDirectionPredict: public COrderInsertFailedPredict
{
private:
	CDirectionType *m_pDirectionStart;
	CDirectionType *m_pDirectionEnd;
public:
	///���췽��
	///@param	pDirectionStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pDirectionEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderInsertFailedDirectionPredict(CDirectionType *pDirectionStart, CDirectionType *pDirectionEnd)
	{
		m_pDirectionStart=pDirectionStart;
		m_pDirectionEnd=pDirectionEnd;
	}

	virtual ~COrderInsertFailedDirectionPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderInsertFailed	Ҫ���жϵĴ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedParticipantIDPredict���ж�һ�������Ƿ������Ա���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedParticipantIDPredict: public COrderInsertFailedPredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///���췽��
	///@param	pParticipantIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pParticipantIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderInsertFailedParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~COrderInsertFailedParticipantIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderInsertFailed	Ҫ���жϵĴ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedClientIDPredict���ж�һ�������Ƿ�����ͻ���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedClientIDPredict: public COrderInsertFailedPredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///���췽��
	///@param	pClientIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pClientIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderInsertFailedClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~COrderInsertFailedClientIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderInsertFailed	Ҫ���жϵĴ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedInsertTimePredict���ж�һ�������Ƿ��������ʱ��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedInsertTimePredict: public COrderInsertFailedPredict
{
private:
	CTimeType *m_pInsertTimeStart;
	CTimeType *m_pInsertTimeEnd;
public:
	///���췽��
	///@param	pInsertTimeStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInsertTimeEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderInsertFailedInsertTimePredict(CTimeType *pInsertTimeStart, CTimeType *pInsertTimeEnd)
	{
		m_pInsertTimeStart=pInsertTimeStart;
		m_pInsertTimeEnd=pInsertTimeEnd;
	}

	virtual ~COrderInsertFailedInsertTimePredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderInsertFailed	Ҫ���жϵĴ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedAccountIDPredict���ж�һ�������Ƿ������ʽ��ʺ�������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedAccountIDPredict: public COrderInsertFailedPredict
{
private:
	CAccountIDType *m_pAccountIDStart;
	CAccountIDType *m_pAccountIDEnd;
public:
	///���췽��
	///@param	pAccountIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pAccountIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderInsertFailedAccountIDPredict(CAccountIDType *pAccountIDStart, CAccountIDType *pAccountIDEnd)
	{
		m_pAccountIDStart=pAccountIDStart;
		m_pAccountIDEnd=pAccountIDEnd;
	}

	virtual ~COrderInsertFailedAccountIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderInsertFailed	Ҫ���жϵĴ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightBrokerIDPredict���ж�һ���û�����Ȩ�ޱ��Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightBrokerIDPredict: public CUserTradingRightPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CUserTradingRightBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CUserTradingRightBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pUserTradingRight	Ҫ���жϵ��û�����Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserTradingRight *pUserTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightExchangeIDPredict���ж�һ���û�����Ȩ�ޱ��Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightExchangeIDPredict: public CUserTradingRightPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CUserTradingRightExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CUserTradingRightExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pUserTradingRight	Ҫ���жϵ��û�����Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserTradingRight *pUserTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightInstrumentIDStartPredict���ж�һ���û�����Ȩ�ޱ��Ƿ����㿪ʼ�ĺ�Լ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightInstrumentIDStartPredict: public CUserTradingRightPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///���췽��
	///@param	pInstrumentIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInstrumentIDEnd	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	CUserTradingRightInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CUserTradingRightInstrumentIDStartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pUserTradingRight	Ҫ���жϵ��û�����Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserTradingRight *pUserTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightUserIDPredict���ж�һ���û�����Ȩ�ޱ��Ƿ������û�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightUserIDPredict: public CUserTradingRightPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///���췽��
	///@param	pUserIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pUserIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CUserTradingRightUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CUserTradingRightUserIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pUserTradingRight	Ҫ���жϵ��û�����Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserTradingRight *pUserTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightInvestorIDPredict���ж�һ���û�����Ȩ�ޱ��Ƿ�����Ͷ���߱��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightInvestorIDPredict: public CUserTradingRightPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CUserTradingRightInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CUserTradingRightInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pUserTradingRight	Ҫ���жϵ��û�����Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserTradingRight *pUserTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionBrokerIDPredict���ж�һ������Ա���߻Ự�Ƿ����㾭�͹�˾����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionBrokerIDPredict: public CUserSessionPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CUserSessionBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CUserSessionBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pUserSession	Ҫ���жϵĽ���Ա���߻Ự
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserSession *pUserSession);
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionUserIDPredict���ж�һ������Ա���߻Ự�Ƿ����㽻���û�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionUserIDPredict: public CUserSessionPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///���췽��
	///@param	pUserIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pUserIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CUserSessionUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CUserSessionUserIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pUserSession	Ҫ���жϵĽ���Ա���߻Ự
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserSession *pUserSession);
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDBrokerIDPredict���ж�һ����󱾵ر������Ƿ����㾭�͹�˾����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDBrokerIDPredict: public CMaxLocalIDPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CMaxLocalIDBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CMaxLocalIDBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pMaxLocalID	Ҫ���жϵ���󱾵ر�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CMaxLocalID *pMaxLocalID);
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDUserIDPredict���ж�һ����󱾵ر������Ƿ����㽻���û�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDUserIDPredict: public CMaxLocalIDPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///���췽��
	///@param	pUserIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pUserIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CMaxLocalIDUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CMaxLocalIDUserIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pMaxLocalID	Ҫ���жϵ���󱾵ر�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CMaxLocalID *pMaxLocalID);
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDBrokerIDPredict���ж�һ���û����ر������Ƿ����㾭�͹�˾����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDBrokerIDPredict: public CBrkUserIDLocalIDPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CBrkUserIDLocalIDBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CBrkUserIDLocalIDBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pBrkUserIDLocalID	Ҫ���жϵ��û����ر�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CBrkUserIDLocalID *pBrkUserIDLocalID);
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDUserIDPredict���ж�һ���û����ر������Ƿ����㽻���û�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDUserIDPredict: public CBrkUserIDLocalIDPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///���췽��
	///@param	pUserIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pUserIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CBrkUserIDLocalIDUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CBrkUserIDLocalIDUserIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pBrkUserIDLocalID	Ҫ���жϵ��û����ر�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CBrkUserIDLocalID *pBrkUserIDLocalID);
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionBrokerIDPredict���ж�һ���ͻ���Լ��ֱֲ��Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionBrokerIDPredict: public CPartClientInsGroupPositionPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CPartClientInsGroupPositionBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CPartClientInsGroupPositionBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pPartClientInsGroupPosition	Ҫ���жϵĿͻ���Լ��ֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition);
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionParticipantIDPredict���ж�һ���ͻ���Լ��ֱֲ��Ƿ������Ա����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionParticipantIDPredict: public CPartClientInsGroupPositionPredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///���췽��
	///@param	pParticipantIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pParticipantIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CPartClientInsGroupPositionParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~CPartClientInsGroupPositionParticipantIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pPartClientInsGroupPosition	Ҫ���жϵĿͻ���Լ��ֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition);
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionClientIDPredict���ж�һ���ͻ���Լ��ֱֲ��Ƿ�����ͻ�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionClientIDPredict: public CPartClientInsGroupPositionPredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///���췽��
	///@param	pClientIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pClientIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CPartClientInsGroupPositionClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~CPartClientInsGroupPositionClientIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pPartClientInsGroupPosition	Ҫ���жϵĿͻ���Լ��ֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition);
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeBrokerIDPredict���ж�һ�����ױ�����ϱ�֤�������Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeBrokerIDPredict: public CClientMarginCombTypePredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CClientMarginCombTypeBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CClientMarginCombTypeBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pClientMarginCombType	Ҫ���жϵĽ��ױ�����ϱ�֤������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientMarginCombType *pClientMarginCombType);
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeParticipantIDPredict���ж�һ�����ױ�����ϱ�֤�������Ƿ������Ա����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeParticipantIDPredict: public CClientMarginCombTypePredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///���췽��
	///@param	pParticipantIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pParticipantIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CClientMarginCombTypeParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~CClientMarginCombTypeParticipantIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pClientMarginCombType	Ҫ���жϵĽ��ױ�����ϱ�֤������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientMarginCombType *pClientMarginCombType);
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeClientIDPredict���ж�һ�����ױ�����ϱ�֤�������Ƿ�����ͻ�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeClientIDPredict: public CClientMarginCombTypePredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///���췽��
	///@param	pClientIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pClientIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CClientMarginCombTypeClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~CClientMarginCombTypeClientIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pClientMarginCombType	Ҫ���жϵĽ��ױ�����ϱ�֤������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientMarginCombType *pClientMarginCombType);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupExchangeIDPredict���ж�һ����Լ�ͺ�Լ���ϵ�Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupExchangeIDPredict: public CInstrumentGroupPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInstrumentGroupExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CInstrumentGroupExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInstrumentGroup	Ҫ���жϵĺ�Լ�ͺ�Լ���ϵ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInstrumentGroup *pInstrumentGroup);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupBrokerIDPredict���ж�һ����Լ�ͺ�Լ���ϵ�Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupBrokerIDPredict: public CInstrumentGroupPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInstrumentGroupBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInstrumentGroupBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInstrumentGroup	Ҫ���жϵĺ�Լ�ͺ�Լ���ϵ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInstrumentGroup *pInstrumentGroup);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupInstrumentIDStartPredict���ж�һ����Լ�ͺ�Լ���ϵ�Ƿ����㿪ʼ�ĺ�Լ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupInstrumentIDStartPredict: public CInstrumentGroupPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///���췽��
	///@param	pInstrumentIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInstrumentIDEnd	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	CInstrumentGroupInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CInstrumentGroupInstrumentIDStartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInstrumentGroup	Ҫ���жϵĺ�Լ�ͺ�Լ���ϵ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInstrumentGroup *pInstrumentGroup);
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateInstrumentIDStartPredict���ж�һ���������ӷ��ʱ��Ƿ����㿪ʼ�ĺ�Լ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateInstrumentIDStartPredict: public CSGEDeferRatePredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///���췽��
	///@param	pInstrumentIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInstrumentIDEnd	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	CSGEDeferRateInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CSGEDeferRateInstrumentIDStartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pSGEDeferRate	Ҫ���жϵĽ������ӷ��ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSGEDeferRate *pSGEDeferRate);
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateExchangeIDPredict���ж�һ���������ӷ��ʱ��Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateExchangeIDPredict: public CSGEDeferRatePredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CSGEDeferRateExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CSGEDeferRateExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pSGEDeferRate	Ҫ���жϵĽ������ӷ��ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSGEDeferRate *pSGEDeferRate);
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateDirectionPredict���ж�һ���������ӷ��ʱ��Ƿ�����֧������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateDirectionPredict: public CSGEDeferRatePredict
{
private:
	CPayDirectionType *m_pDirectionStart;
	CPayDirectionType *m_pDirectionEnd;
public:
	///���췽��
	///@param	pDirectionStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pDirectionEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CSGEDeferRateDirectionPredict(CPayDirectionType *pDirectionStart, CPayDirectionType *pDirectionEnd)
	{
		m_pDirectionStart=pDirectionStart;
		m_pDirectionEnd=pDirectionEnd;
	}

	virtual ~CSGEDeferRateDirectionPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pSGEDeferRate	Ҫ���жϵĽ������ӷ��ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSGEDeferRate *pSGEDeferRate);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightBrokerIDPredict���ж�һ��Ͷ���߽���Ȩ�ޱ��Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightBrokerIDPredict: public CInvestorTradingRightPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorTradingRightBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInvestorTradingRightBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorTradingRight	Ҫ���жϵ�Ͷ���߽���Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorTradingRight *pInvestorTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightInvestorIDPredict���ж�һ��Ͷ���߽���Ȩ�ޱ��Ƿ�����Ͷ���߱��������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightInvestorIDPredict: public CInvestorTradingRightPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorTradingRightInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CInvestorTradingRightInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorTradingRight	Ҫ���жϵ�Ͷ���߽���Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorTradingRight *pInvestorTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightExchangeIDPredict���ж�һ��Ͷ���߽���Ȩ�ޱ��Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightExchangeIDPredict: public CInvestorTradingRightPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorTradingRightExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CInvestorTradingRightExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorTradingRight	Ҫ���жϵ�Ͷ���߽���Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorTradingRight *pInvestorTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightInstrumentIDStartPredict���ж�һ��Ͷ���߽���Ȩ�ޱ��Ƿ����㿪ʼ�ĺ�Լ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightInstrumentIDStartPredict: public CInvestorTradingRightPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///���췽��
	///@param	pInstrumentIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInstrumentIDEnd	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorTradingRightInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CInvestorTradingRightInstrumentIDStartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorTradingRight	Ҫ���жϵ�Ͷ���߽���Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorTradingRight *pInvestorTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CUserIPBrokerIDPredict���ж�һ������ԱIP��ַ�Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPBrokerIDPredict: public CUserIPPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CUserIPBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CUserIPBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pUserIP	Ҫ���жϵĽ���ԱIP��ַ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserIP *pUserIP);
};

/////////////////////////////////////////////////////////////////////////
///CUserIPUserIDPredict���ж�һ������ԱIP��ַ�Ƿ����㽻���û�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPUserIDPredict: public CUserIPPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///���췽��
	///@param	pUserIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pUserIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CUserIPUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CUserIPUserIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pUserIP	Ҫ���жϵĽ���ԱIP��ַ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserIP *pUserIP);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeBrokerIDPredict���ж�һ���ͻ���Ȩ�������ʱ��Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeBrokerIDPredict: public CInvestorOptionFeePredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorOptionFeeBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInvestorOptionFeeBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorOptionFee	Ҫ���жϵĿͻ���Ȩ�������ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorOptionFee *pInvestorOptionFee);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeExchangeIDPredict���ж�һ���ͻ���Ȩ�������ʱ��Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeExchangeIDPredict: public CInvestorOptionFeePredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorOptionFeeExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CInvestorOptionFeeExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorOptionFee	Ҫ���жϵĿͻ���Ȩ�������ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorOptionFee *pInvestorOptionFee);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeInvestorIDPredict���ж�һ���ͻ���Ȩ�������ʱ��Ƿ�����Ͷ���߱���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeInvestorIDPredict: public CInvestorOptionFeePredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///���췽��
	///@param	pInvestorIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInvestorIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorOptionFeeInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CInvestorOptionFeeInvestorIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorOptionFee	Ҫ���жϵĿͻ���Ȩ�������ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorOptionFee *pInvestorOptionFee);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeInstrumentIDStartPredict���ж�һ���ͻ���Ȩ�������ʱ��Ƿ����㿪ʼ�ĺ�Լ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeInstrumentIDStartPredict: public CInvestorOptionFeePredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///���췽��
	///@param	pInstrumentIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInstrumentIDEnd	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	CInvestorOptionFeeInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CInvestorOptionFeeInstrumentIDStartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pInvestorOptionFee	Ҫ���жϵĿͻ���Ȩ�������ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorOptionFee *pInvestorOptionFee);
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataExchangeIDPredict���ж�һ��ʵʱ������Ƿ����㽻��������������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataExchangeIDPredict: public CMarketDataPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///���췽��
	///@param	pExchangeIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pExchangeIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	CMarketDataExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CMarketDataExchangeIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pMarketData	Ҫ���жϵ�ʵʱ�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CMarketData *pMarketData);
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataInstrumentIDStartPredict���ж�һ��ʵʱ������Ƿ����㿪ʼ�ĺ�Լ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataInstrumentIDStartPredict: public CMarketDataPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///���췽��
	///@param	pInstrumentIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pInstrumentIDEnd	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	CMarketDataInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CMarketDataInstrumentIDStartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pMarketData	Ҫ���жϵ�ʵʱ�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CMarketData *pMarketData);
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayBrokerIDPredict���ж�һ��ί���ӳٱ��Ƿ����㾭�͹�˾���������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayBrokerIDPredict: public COrderDelayPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///���췽��
	///@param	pBrokerIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pBrokerIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderDelayBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~COrderDelayBrokerIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderDelay	Ҫ���жϵ�ί���ӳٱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderDelay *pOrderDelay);
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayUserIDPredict���ж�һ��ί���ӳٱ��Ƿ������û�����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayUserIDPredict: public COrderDelayPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///���췽��
	///@param	pUserIDStart	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	pUserIDEnd	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	COrderDelayUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~COrderDelayUserIDPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	pOrderDelay	Ҫ���жϵ�ί���ӳٱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderDelay *pOrderDelay);
};

#endif
