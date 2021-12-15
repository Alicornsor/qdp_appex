/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file BaseEngine.h
///@brief��������CMemoryEngine
///@history 
///20060903	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef BASEENGINE_H
#define BASEENGINE_H

#include "CConfig.h"
#include "errorDefine.h"
#include "CMemoryDB.h"
#include "CDumpLog.h"
#include "monitorIndex.h"

/////////////////////////////////////////////////////////////////////////
///CBaseEngine��һ����������Ļ��࣬�������ڴ����ݿ⣬������˻ָ�����
///@author	xuzh
///@version	1.0,20060903
/////////////////////////////////////////////////////////////////////////
class CBaseEngine
{
public:
	///���캯��
	///@param	pConfig	����������Ҫʹ�õ�����
	///@param	recovery	�Ƿ�ʹ�ûָ�ģʽ
	///@param	verbose	true��ʾҪ��������flase��ʾ��Ҫ������
	CBaseEngine(CConfig *pConfig,bool verbose=true);
	
	virtual ~CBaseEngine(void);

	///��ʼ����ĳ����ŵ���Ϣ
	///@param	seqID	Ҫ�������Ϣ�ı��
	///@return	true��ʾ������false��ʾҪ���н�������
	virtual bool startProcess(int seqID);
	
	///��������ĳ����ŵ���Ϣ
	///@param	seqID	�մ��������Ϣ���
	///@return	true��ʾ������false��ʾҪ���н�������
	virtual bool endProcess(int seqID);

protected:
	///��ȡ��һ�������ţ�����ʱ���ļ�ָ���ڶ���ǰ��λ�ã�
	///�������ɹ����������һ������ǰ��λ�ã�������ɹ���
	///����ԭλ����
	///@return	��һ�������ţ����û���ˣ��򷵻�0
	virtual int getNextID(void);

	///������һ�������ţ�������󣬽���ʱ���ļ�ָ����д��
	///ǰ��λ�ã�����ʱ���ļ�ָ�벻��
	///@param	��һ��������
	virtual void setNextID(int nextID);

	///����Ӧ������
	///@param	seqID	���к�
	virtual void handleEmerge(int seqID);

	///�����ڴ��ļ���ʼ��
	///@param	isInit	true���������  false:�ָ���ʽ������ȡ�����¼ֵ
	///@param	processFileName	�����ڴ��ļ���
	///@return	����ӳ��Ĺ����ڴ��ַ��NULL��ʼ��ʧ��
	char *initMmap(bool isInit,char *processFileName);

	bool m_verbose;
	CConfig *m_pConfig;
	CMemoryDB *m_pDB;
	CDumpLog *m_pDumpLog;
	CErrorEngine *m_pErrorEngine;
//	CIntTotalMonitorIndex *m_handleInputIndex;

	FILE *m_processFile;

	char *m_pProcess;
	int  m_CurrPos;
};

#endif
