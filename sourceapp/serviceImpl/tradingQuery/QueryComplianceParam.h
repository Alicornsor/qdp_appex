/////////////////////////////////////////////////////////////////////////
///@system 极速风控前置系统
///@company 上海量投网络科技有限公司
///@file QueryComplianceParam.h
///@brief定义了一个map，CExchangeClientID2ComplianceParamMap，从表交易所合规参数表的主键
/// 找到表的记录。 由于查询此表，需要查找另外个表（交易所客户编码表）。用一个map把查询到的记录保存下来，
/// 提高查询的速度。
///@history 
///20130129	longqy@cffex.net 创建文件
/////////////////////////////////////////////////////////////////////////
#ifndef QUERYCOMPLIANCEPARAM_H
#define QUERYCOMPLIANCEPARAM_H


// ExchangeID+ClientID索引，这个索引是两个表的主键：交易所客户编码表 和 交易所合规参数表
// 如果这两个表的主键变了，可能程序需要再次调整。
// 下面两个类的定义，用于 交易所合规参数表 的查询
class CExchangeClientIDIndex
{
public:
	CExchangeClientIDIndex(){};
	~CExchangeClientIDIndex(){};
public:
	CExchangeIDType	ExchangeID;//交易所
	CClientIDType ClientID;
	bool operator > (const CExchangeClientIDIndex &m)const
	{
		if (ExchangeID > m.ExchangeID)
		{
			return true;
		}
		else if (ExchangeID < m.ExchangeID)
		{
			return false;
		}
		else
		{
			if (ClientID > m.ClientID)
			{
				return true;
			}
			else if (ClientID < m.ClientID)
			{
				return false;
			}
			else
			{
				return false;
			}
		}
	}
};

// ExchangeID+InvestorID索引，这个索引是用于 交易所客户编码表 的查询，可以获得多个ClientID
class CExchangeInvestorIDIndex
{
public:
	CExchangeInvestorIDIndex(){};
	~CExchangeInvestorIDIndex(){};
public:
	CExchangeIDType	ExchangeID;//交易所
	CInvestorIDType InvestorID;
	bool operator > (const CExchangeInvestorIDIndex &m)const
	{
		if (ExchangeID > m.ExchangeID)
		{
			return true;
		}
		else if (ExchangeID < m.ExchangeID)
		{
			return false;
		}
		else
		{
			if (InvestorID > m.InvestorID)
			{
				return true;
			}
			else if (InvestorID < m.InvestorID)
			{
				return false;
			}
			else
			{
				return false;
			}
		}
	}
};

typedef vector<CClientIDType>  ClientIDVector;
typedef vector<CInvestorIDType>  InvestorIDVector;
typedef vector<CAccountIDType>  AccountIDVector;

typedef map<CExchangeInvestorIDIndex, ClientIDVector *, greater<CExchangeInvestorIDIndex> >  CExchangeInvestorID2ClientIDMap;

#endif

