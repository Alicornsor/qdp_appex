// FTDCSession.h: interface for the CFTDCSession class .
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTDCSESSION_H__88022E6A_66E9_46E0_B66F_8F73B23CDEFA__INCLUDED_)
#define AFX_FTDCSESSION_H__88022E6A_66E9_46E0_B66F_8F73B23CDEFA__INCLUDED_

#include "EventHandler.h"
#include "XMPSession.h"
#include "XMPProtocol.h"
#include "CompressProtocol.h"
#include "FTDCProtocol.h"
#include "FlowReader.h"
#include "FtdPackageDesc.h"

class CFTDCSession;

class CFTDCSessionCallback
{
public:
	virtual int HandlePackage(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession) = 0;
};

/**��һ�����Э��ջ���������ǻ���IO�����EventHandler�࣬һ������ListenCtrl
*������������ע�ᵽһ��Reactor�������ĵײ�������һ��TcpChannel�ϣ������ڵ�
*Э��ֻ��ͨ�������Ĳ��ܵõ���д���� */
class CFTDCSession : public CProtocolCallback, public CXMPSession
{
public:
	/**���캯�������Э��ջ�Ĺ���
	* @param pReactor   ��������
	* @param pChannel   һ��TcpChannel
	*/ 	
	CFTDCSession(CReactor *pReactor,CChannel *pChannel);
	
	/**�����������ͷſɿ���Դ
	*/
	virtual ~CFTDCSession();
	
	/**����һ����Ϣ
	* @param nEventID ��ϢID
	* @param dwParam ��һ������
	* @param pParam �ڶ�������
	* @return ������
	*/
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);

	virtual int HandlePackage(CPackage *pPackage,CProtocol *pProtocol);

	/**��ȡ����дsocket����selectʹ��
	* @param pReadId   ������������ض���ʹ�õ�socket��Ϊ0��ʾ����Ҫ��
	* @param pWriteId  �������������д��ʹ�õ�socket��Ϊ0��ʾ����Ҫд
	* @remark �����ｫ��������������ݰ����ݵ����²�Э��
	*/
	virtual void GetIds(int *pReadId, int *pWriteId);
	
	void RegisterPackageHandler(CFTDCSessionCallback *pPackageHandler);

	void Publish(CReadOnlyFlow *pFlow, WORD wSequenceSeries, int nStartId);
	void UnPublish(WORD wSequenceSeries);
	void RegisterSubscriber(CFTDCSubscriber *pSubscriber);
	void UnRegisterSubscriber(CFTDCSubscriber *pSubscriber);
	
	CFTDCPackage *CreatePackage();
	
	void SendRequestPackage(CFTDCPackage *pPackage);
	
	void SetCommPhaseNo(WORD wCommPhaseNo);	

	virtual void Disconnect(int nErrorCode);

	/**�������FTDC��ѹ���㷨
	*@param chCompressMethod ѹ���㷨���룬0��ʾ��ѹ��
	*/
	void SetCompressMethod(BYTE chCompressMethod);
	
	/**���ñ��Ự�İ汾
	*@param	version	�汾��
	*/
	void SetVersion(BYTE version);
	
	/**��ȡ���Ự�İ汾
	*@return	���Ự�İ汾
	*/
	BYTE GetVersion(void);

	void CreatSubInstrument();
	bool InsertInstrumentID(DWORD instrumentIDCount,CInstrumentIDType instrumentID);
	bool DeleteInstrumentID(DWORD instrumentIDCount);
	void DisplayInstrumentID();
	void RspAllSubInstrumentID(DWORD RspType);

	CSubInstrumentMap *m_pmapSubInstrument;	
	
protected:
	CFTDCProtocol *m_pFTDCProtocol;		/**< FTDCЭ�����*/
	CCompressProtocol *m_pCRPProtocol;	/**< CRPЭ�����*/
	CFTDCSessionCallback *m_pPackageHandler;
	///-----
	///	xuzh��20060223�������˶�FTDЭ��İ汾����
	///-----
	BYTE m_version;
	
	//add by jinpc 20160928 ������ɺ���ȫ���������еĺ�Լ��ֻ���Ͷ��ĵĺ�Լ��
	vector<CInstrumentIDType> v_subinstrumet;
};

#endif // !defined(AFX_FTDCSESSION_H__88022E6A_66E9_46E0_B66F_8F73B23CDEFA__INCLUDED_)
