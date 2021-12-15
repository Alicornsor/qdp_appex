/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file LoginServiceImpl.h
///@brief定义了类CLoginServiceImpl
///@history 
///20130703	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGINSERVICEIMPL_H__F819C104_5152_44C2_8A65_701104146259__INCLUDED_)
#define AFX_LOGINSERVICEIMPL_H__F819C104_5152_44C2_8A65_701104146259__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "databaseData.h"
#include "CErrorEngine.h"
#include "IServiceInterface.h"
#include "databaseData.h"
#include "CTransaction.h"

/**CLoginServiceImpl实现了ILoginService定义的登录功能
*@author	hwp
*@version	1.0,20130703
*/
class CLoginServiceImpl
{
public:
	CLoginServiceImpl(CMemoryDB *pDB, CErrorEngine *pErrorEngine);
	virtual ~CLoginServiceImpl();

	/**是否拥有权限
	*@param	reqTid	请求的TID
	*@param	pRspTid	用于返回给出响应的TID
	*@param	sessionRef	会话编号
	*@param	pTransaction	本操作属于的事务
	*@return	true表示拥有，false表示不拥有
	*/
// 	virtual bool CheckUserFunctionRight(int reqTid, int *pRspTid,
// 		const TSessionRef &sessionRef, CTransaction *pTransaction);

	/**用户登录
	*@param UserID	用户代码
	*@param BrokerID	经纪公司代码
	*@param	Password	密码 
	*@param IPAddress	登录的IP
	*@param TradingDay	当前交易日(返回)
	*@param LoginTime	登录时间(返回)
	*@param MaxOrderLocalID	最大本地报单号(返回)
	*@param	UserProductInfo	用户端产品信息
	*@param	InterfaceProductInfo	接口端产品信息
	*@param	ProtocolInfo	协议信息
	*@param	TradingSystemName	交易系统名称(返回)
	*@param	UserType	用户类型(返回)
	*@param	MaxCommFlux	最大通讯量
	*@param	sessionRef	会话编号
	*@param	pTransaction	本操作属于的事务
	*@return	true表示成功，false表示失败
	*/
 	virtual bool UserLogin(CReadOnlyUserIDType &UserID,	
 		CBrokerIDType &BrokerID,
 		CReadOnlyPasswordType &Password, 
 		CReadOnlyIPAddressType &IPAddress,
 		CReadOnlyMacAddressType &MacAddress,
 		CDateType &TradingDay,
 		CTimeType &LoginTime,
 		CUserOrderLocalIDType &MaxOrderLocalID,
 		CReadOnlyProductInfoType &UserProductInfo,
 		CReadOnlyProductInfoType &InterfaceProductInfo,
 		CReadOnlyProtocolInfoType &ProtocolInfo,
 		CTradingSystemNameType &TradingSystemName,
 		CUserTypeType &UserType,
 		CCommFluxType &MaxCommFlux,
 		const TSessionRef &sessionRef, CTransaction *pTransaction);
 	
 	/**用户登出
 	*@param UserID	用户代码
 	*@param BrokerID	经纪公司代码
 	*@param	sessionRef	会话编号
 	*@param	pTransaction	本操作属于的事务
 	*@return	true表示成功，false表示失败
 	*/
 	virtual bool UserLogout(CReadOnlyUserIDType &UserID,	
 		CReadOnlyBrokerIDType &BrokerID,
 		const TSessionRef &sessionRef, CTransaction *pTransaction);
 
 	/**删除交易员会话 
 	*@param UserID	用户代码
 	*@param BrokerID	经纪公司代码
 	*@param	sessionRef	会话编号
 	*@param	pTransaction	本操作属于的事务
 	*@return	true表示成功，false表示失败
 	*/
 	virtual bool ForceUserLogout(CReadOnlyUserIDType &UserID,
 		CReadOnlyBrokerIDType &BrokerID,
 		const TSessionRef &sessionRef, CTransaction *pTransaction);
 
 	/**强制交易员退出 
 	*@param UserID	用户代码
 	*@param BrokerID	经纪公司代码
 	*@param	sessionRef	会话编号
 	*@param	pTransaction	本操作属于的事务
 	*@return	true表示成功，false表示失败
 	*/
 	virtual bool ForceUserExit(CReadOnlyUserIDType &UserID,
 		CReadOnlyBrokerIDType &BrokerID,
 		const TSessionRef &sessionRef, CTransaction *pTransaction);
 
 	/**密码修改
 	*@param UserID	用户代码
 	*@param BrokerID	经纪公司代码
 	*@param	OldPassword	旧密码 
 	*@param	NewPassword	新密码 
 	*@param	sessionRef	会话编号
 	*@param	pTransaction	本操作属于的事务
 	*@return	true表示成功，false表示失败
 	*/
 	virtual bool UserPasswordUpdate(CReadOnlyUserIDType &UserID,	
 		CBrokerIDType &BrokerID,
 		CReadOnlyPasswordType &OldPassword, 
 		CReadOnlyPasswordType &NewPassword, 
 		const TSessionRef &sessionRef, CTransaction *pTransaction);
 
 	///时间提醒
 	///@param	CurrTime	当前时间
 	///@param	sessionRef	会话编号
 	///@param	pTransaction	本操作属于的事务
 	///@return	true表示成功，false表示失败
 	virtual bool TimeSync(CReadOnlyTimeType &CurrTime,
 		const TSessionRef &sessionRef,CTransaction *pTransaction); 		

	virtual bool RspUserPasswordUpdate(CUserPasswordUpdateField *pField, CTransaction *pTransaction); 	

private:
//	void ForceLogout(CTransaction *pTransaction);
private:
	CMemoryDB *m_pDB;
	CErrorEngine *m_pErrorEngine;
	bool m_loginTimeFirst;
	bool m_md5Password;
	
};

#endif // !defined(AFX_LOGINSERVICEIMPL_H__F819C104_5152_44C2_8A65_701104146259__INCLUDED_)
