/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file LoginServiceImpl.h
///@brief��������CLoginServiceImpl
///@history 
///20130703	hwp		�������ļ�
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

/**CLoginServiceImplʵ����ILoginService����ĵ�¼����
*@author	hwp
*@version	1.0,20130703
*/
class CLoginServiceImpl
{
public:
	CLoginServiceImpl(CMemoryDB *pDB, CErrorEngine *pErrorEngine);
	virtual ~CLoginServiceImpl();

	/**�Ƿ�ӵ��Ȩ��
	*@param	reqTid	�����TID
	*@param	pRspTid	���ڷ��ظ�����Ӧ��TID
	*@param	sessionRef	�Ự���
	*@param	pTransaction	���������ڵ�����
	*@return	true��ʾӵ�У�false��ʾ��ӵ��
	*/
// 	virtual bool CheckUserFunctionRight(int reqTid, int *pRspTid,
// 		const TSessionRef &sessionRef, CTransaction *pTransaction);

	/**�û���¼
	*@param UserID	�û�����
	*@param BrokerID	���͹�˾����
	*@param	Password	���� 
	*@param IPAddress	��¼��IP
	*@param TradingDay	��ǰ������(����)
	*@param LoginTime	��¼ʱ��(����)
	*@param MaxOrderLocalID	��󱾵ر�����(����)
	*@param	UserProductInfo	�û��˲�Ʒ��Ϣ
	*@param	InterfaceProductInfo	�ӿڶ˲�Ʒ��Ϣ
	*@param	ProtocolInfo	Э����Ϣ
	*@param	TradingSystemName	����ϵͳ����(����)
	*@param	UserType	�û�����(����)
	*@param	MaxCommFlux	���ͨѶ��
	*@param	sessionRef	�Ự���
	*@param	pTransaction	���������ڵ�����
	*@return	true��ʾ�ɹ���false��ʾʧ��
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
 	
 	/**�û��ǳ�
 	*@param UserID	�û�����
 	*@param BrokerID	���͹�˾����
 	*@param	sessionRef	�Ự���
 	*@param	pTransaction	���������ڵ�����
 	*@return	true��ʾ�ɹ���false��ʾʧ��
 	*/
 	virtual bool UserLogout(CReadOnlyUserIDType &UserID,	
 		CReadOnlyBrokerIDType &BrokerID,
 		const TSessionRef &sessionRef, CTransaction *pTransaction);
 
 	/**ɾ������Ա�Ự 
 	*@param UserID	�û�����
 	*@param BrokerID	���͹�˾����
 	*@param	sessionRef	�Ự���
 	*@param	pTransaction	���������ڵ�����
 	*@return	true��ʾ�ɹ���false��ʾʧ��
 	*/
 	virtual bool ForceUserLogout(CReadOnlyUserIDType &UserID,
 		CReadOnlyBrokerIDType &BrokerID,
 		const TSessionRef &sessionRef, CTransaction *pTransaction);
 
 	/**ǿ�ƽ���Ա�˳� 
 	*@param UserID	�û�����
 	*@param BrokerID	���͹�˾����
 	*@param	sessionRef	�Ự���
 	*@param	pTransaction	���������ڵ�����
 	*@return	true��ʾ�ɹ���false��ʾʧ��
 	*/
 	virtual bool ForceUserExit(CReadOnlyUserIDType &UserID,
 		CReadOnlyBrokerIDType &BrokerID,
 		const TSessionRef &sessionRef, CTransaction *pTransaction);
 
 	/**�����޸�
 	*@param UserID	�û�����
 	*@param BrokerID	���͹�˾����
 	*@param	OldPassword	������ 
 	*@param	NewPassword	������ 
 	*@param	sessionRef	�Ự���
 	*@param	pTransaction	���������ڵ�����
 	*@return	true��ʾ�ɹ���false��ʾʧ��
 	*/
 	virtual bool UserPasswordUpdate(CReadOnlyUserIDType &UserID,	
 		CBrokerIDType &BrokerID,
 		CReadOnlyPasswordType &OldPassword, 
 		CReadOnlyPasswordType &NewPassword, 
 		const TSessionRef &sessionRef, CTransaction *pTransaction);
 
 	///ʱ������
 	///@param	CurrTime	��ǰʱ��
 	///@param	sessionRef	�Ự���
 	///@param	pTransaction	���������ڵ�����
 	///@return	true��ʾ�ɹ���false��ʾʧ��
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
