#if !defined(FTDC_RSESSION_H)
#define FTDC_RSESSION_H

#include "FTDCSession.h"

#define XMP_READ  1
#define XMP_WRITE 2

class CExXMPProtocol : public CProtocol
{
public:
	/**���캯��
	* @param pReactor ָ�����������ָ��
	* @param pBelow �²�Э���ָ��
	*/
	CExXMPProtocol(CReactor *pReactor, int type = XMP_READ);
	/**��������
	*/
	virtual ~CExXMPProtocol();

	/**����XMP��ͷ�������²�Э��
	* @param pPackage �ϲ��Э���´��İ�
	* @return 0   �ɹ�
	* @return <>0 ʧ��
	*/
	virtual int Push(CPackage *pPackage, CProtocol *pUpper);

	void EnableHeartbeat(bool bEnable);
	
	void SetHeartbeatTimeout(DWORD dwReadTimeout);

	void SetWriteTimeout(CXMPPackage *pPackage);

	DWORD GetTimeout();
protected:	
	/**��¼��ǰ�յ�����ʱ�䣬�ж��Ƿ�XMP�������ϴ�
	* @param pPackage �²�Э���ϴ��İ�
	* @return 0   �ɹ�
	* @return <>0 ʧ��
	*/
	virtual int Pop(CPackage *pPackage);

	/**�յ�һ����������ݰ�ʱ����
	* @param pPackage ��������ݰ�
	* @return 0   �ɹ�
	* @return <>0 ʧ��
	*/
	virtual int OnRecvErrorPackage(CPackage *pPackage);

	/**����ʱ��������CReactor���á�����������ʱ����֪ͨ�ϲ�Э�顣
	* ������д��ʱ�������������ġ�
	* @param nIDEvent ������Ϊ��ʱ��ʱ���ڶ�ʱ������ʱ����ʶ   
	*/
	virtual void OnTimer(int nIDEvent);

	int SendHeartbeat();

	/**���ɲ���������������ʱ����
	* @return >0   �ɹ�
	* @return <=0  ʧ�� 
	*/
	int SendWriteTimeout(DWORD dwWriteTimeout);
protected:
	bool m_bHeartEnable;		/**< �Ƿ����/�������� */
	DWORD m_LastReadTime;		/**< ����հ�ʱ�䡡*/
	DWORD m_dwReadTimeout;		/**< ���������ĳ�ʱʱ�� */

	DWORD m_LastWriteTime;		/**< ����հ�ʱ�䡡*/
	DWORD m_dwWriteTimeout;		/**< ����������ʱ���� */
	int  m_Type;
};
class CExXMPSession : public CSession
{
public:
	CExXMPSession(CReactor *pReactor,CChannel *pChannel, int type = XMP_READ);
	virtual ~CExXMPSession();

	void SetHeartbeatTimeout(DWORD dwReadTimeout);


	void EnableHeartbeat(bool bEnable);

	DWORD GetTimeout();
protected:
	CExXMPProtocol *m_pExXMPProtocol;	/**< �����ڵĵڶ���Э��(���²���ʼ)*/
};

class CFTDCRSession;

class CFTDCRSessionCallback
{
public:
	virtual int HandlePackage(CFTDCPackage *pFTDCPackage, CFTDCRSession *pSession) = 0;
};


class CFTDCRSession : public CProtocolCallback , public CExXMPSession
{
public:
	/**���캯�������Э��ջ�Ĺ���
	* @param pReactor   ��������
	* @param pChannel   һ��TcpChannel
	*/ 	
	CFTDCRSession(CReactor *pReactor,CChannel *pChannel, int type = XMP_READ);
	
	/**�����������ͷſɿ���Դ
	*/
	virtual ~CFTDCRSession();
	
	/**����һ����Ϣ
	* @param nEventID ��ϢID
	* @param dwParam ��һ������
	* @param pParam �ڶ�������
	* @return ������
	*/
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);


	/**��ȡ����дsocket����selectʹ��
	* @param pReadId   ������������ض���ʹ�õ�socket��Ϊ0��ʾ����Ҫ��
	* @param pWriteId  �������������д��ʹ�õ�socket��Ϊ0��ʾ����Ҫд
	* @remark �����ｫ��������������ݰ����ݵ����²�Э��
	*/
	virtual void GetIds(int *pReadId, int *pWriteId);

	virtual int HandlePackage(CPackage *pPackage,CProtocol *pProtocol);
	
	void RegisterPackageHandler(CFTDCRSessionCallback *pPackageHandler);
	
	CFTDCPackage *CreatePackage();

	void SendRequestPackage(CFTDCPackage *pPackage);

	void Publish(CReadOnlyFlow *pFlow, WORD wSequenceSeries, int nStartId);

	virtual void Disconnect(int nErrorCode);

	void ResetSession(DWORD nSessionID);

	virtual void Closeconnect(int nErrorCode);
protected:
	CFTDCProtocol *m_pFTDCProtocol;		/**< FTDCЭ�����*/
	CCompressProtocol *m_pCRPProtocol;	/**< CRPЭ�����*/
	CFTDCRSessionCallback *m_pPackageHandler;
	///-----
	///	xuzh��20060223�������˶�FTDЭ��İ汾����
	///-----
	BYTE m_version;
	int m_type;
};

#endif
