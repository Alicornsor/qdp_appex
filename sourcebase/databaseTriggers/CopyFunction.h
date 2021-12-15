#ifndef _Copy_FUNCION_H
#define _Copy_FUNCION_H
#include "UFCopy.h"

template <class DesType,class SourceType>
class CopyDataClass
{
public:
	static void CopyEntity(DesType *,SourceType *);
};

template <>
class CopyDataClass<COrderField,COrder>
{
public:
	static void CopyEntity(COrderField *pField,COrder *pData)
	{
		CopyOrderEntity(pField,pData);
	}	
};

template <>
class CopyDataClass<CTradeField,CTrade>
{
public:
	static void CopyEntity(CTradeField *pField,CTrade *pData)
	{
		CopyTradeEntity(pField,pData);
	}	
};

template <>
class CopyDataClass<CInstrumentField,CInstrument>
{
public:
	static void CopyEntity(CInstrumentField *pField,CInstrument *pData)
	{
		CopyInstrumentEntity(pField,pData);
	}	
};

template <>
class CopyDataClass<CUserField,CUser>
{
public:
	static void CopyEntity(CUserField *pField,CUser *pData)
	{
		CopyUserEntity(pField,pData);
	}	
};

template <>
class CopyDataClass<CMarketDataField,CMarketData>
{
public:
	static void CopyEntity(CMarketDataField *pField,CMarketData *pData)
	{
		CopyMarketDataEntity(pField,pData);
	}	
};

template <>
class CopyDataClass<CUserSessionField,CUserSession>
{
public:
	static void CopyEntity(CUserSessionField *pField,CUserSession *pData)
	{
		CopyUserSessionEntity(pField,pData);
	}	
};


#endif 