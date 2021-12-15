/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file Engine.h
///@brief��������CEngine
///@history 
///20060118	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef ENGINE_H
#define ENGINE_H

#include "BaseEngine.h"
#include "IServiceInterface.h"
#include "ServiceXTPLink.h"
#include "FibPublishApi.h"

/////////////////////////////////////////////////////////////////////////
///CEngine��һ��XTP��Ϣ���͵����棬������һ��XTP��������
///@author	xuzh
///@version	1.0,20060118
/////////////////////////////////////////////////////////////////////////
class CEngine: protected vector<IServiceXTPLink *>, protected CBaseEngine
{
public:
	///���캯��
	///@param	pConfig	����������Ҫʹ�õ�����
	///@param	recovery	�Ƿ�ʹ�ûָ�ģʽ
	///@param	verbose	true��ʾҪ��������flase��ʾ��Ҫ������
	CEngine(CConfig *pConfig, bool verbose=true);
	
	virtual ~CEngine(void);
	
	///����һ���ڴ�XTP��
	///@param	pPackage	Ҫ�����XTP��
	virtual void handleMessage(CXTPPackage *pPackage);
	
	///����һ������
	///@param	pPackage	Ҫ���������
	///@param	nSessionID	�Ự���
	virtual void handleRequest(CXTPPackage *pPackage,DWORD nSessionID);

protected:
	///����һ���ڴ��������
	///@param	pLink	Ҫ���ӵ��ڴ��������
	void addServiceXTPLink(IServiceXTPLink *pLink);

	///ɾ��һ���ڴ��������
	///@param	pLink	Ҫɾ�����ڴ��������
	///@return	true��ʾɾ���ɹ���flase��ʾɾ��ʧ��
	bool removeServiceXTPLink(IServiceXTPLink *pLink);

	int m_seqID;	
};

#endif
