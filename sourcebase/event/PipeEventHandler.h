// EventHandler.h: interface for the CPipeEventHandler class .
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPipeEventHandler_H__D0DAF147_AD16_4C5C_9393_78E357E0A93E__INCLUDED_)
#define AFX_CPipeEventHandler_H__D0DAF147_AD16_4C5C_9393_78E357E0A93E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "EventHandler.h"
class  CSelectReactor;

/**
* CPipeEventHandler��һ��֪ͨ���������Ҫ��������CSelectReactor,���������˯�ߣ�
* �Ӷ������䲻�ܼ�ʱ�������Զ��е�����
*/
class CPipeEventHandler: public CEventHandler
{
public:
	/**���캯��
	* @param pReactor ��ǰ���ж������������ 
	*/
	CPipeEventHandler(CReactor *pReactor,int nLocalPivatePort=0);
	
	/**��������
	*/
	virtual ~CPipeEventHandler();
	
	/**����IO�����Ķ���������CReactor����
	* @return ����
	*/
	virtual int HandleInput();
	
	/**��ȡ����дsocket����selectʹ��
	* @param pReadId   ������������ض���ʹ�õ�socket��Ϊ0��ʾ����Ҫ��
	* @param pWriteId  �������������д��ʹ�õ�socket��Ϊ0��ʾ����Ҫд 
	*/
	virtual void GetIds(int *pReadId, int *pWriteId);
	
	/**����֪ͨ
	*/
	virtual void Notify();
	
	/*��ȡ����ʱ��
	*/
	DWORD GettMilSec();

protected:
	void CreatePipe(int &p0, int &p1);
protected:
	CReactor *m_pDestReactor;
	int             m_nReadPipe;
	int             m_nWritePipe;
	DWORD 		m_nPreClock;
	DWORD 		m_nPerCnt;
	bool			m_SendFlag;
	char 			m_buffer[10];
	
	volatile DWORD     m_nWriteCnt;
	volatile DWORD     m_nReadCnt;

	int	m_nLocalPivatePort;  //WIN32ר��
};

#endif // !defined(AFX_EVENTHANDLER_H__D0DAF147_AD16_4C5C_9393_78E357E0A93E__INCLUDED_)
