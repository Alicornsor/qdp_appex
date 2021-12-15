/////////////////////////////////////////////////////////////////////////
///@system ���ٷ��ǰ��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file QueryComplianceParam.h
///@brief������һ��map��CExchangeClientID2ComplianceParamMap���ӱ������Ϲ�����������
/// �ҵ���ļ�¼�� ���ڲ�ѯ�˱���Ҫ������������������ͻ����������һ��map�Ѳ�ѯ���ļ�¼����������
/// ��߲�ѯ���ٶȡ�
///@history 
///20130129	longqy@cffex.net �����ļ�
/////////////////////////////////////////////////////////////////////////
#ifndef QUERYCOMPLIANCEPARAM_H
#define QUERYCOMPLIANCEPARAM_H


// ExchangeID+ClientID�����������������������������������ͻ������ �� �������Ϲ������
// �������������������ˣ����ܳ�����Ҫ�ٴε�����
// ����������Ķ��壬���� �������Ϲ������ �Ĳ�ѯ
class CExchangeClientIDIndex
{
public:
	CExchangeClientIDIndex(){};
	~CExchangeClientIDIndex(){};
public:
	CExchangeIDType	ExchangeID;//������
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

// ExchangeID+InvestorID������������������� �������ͻ������ �Ĳ�ѯ�����Ի�ö��ClientID
class CExchangeInvestorIDIndex
{
public:
	CExchangeInvestorIDIndex(){};
	~CExchangeInvestorIDIndex(){};
public:
	CExchangeIDType	ExchangeID;//������
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

