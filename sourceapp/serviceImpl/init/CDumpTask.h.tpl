/////////////////////////////////////////////////////////////////////////
///@system ��������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CDumpTask.h
///@brief	��������CDumpTask�������
///@history 
///20091203	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CDUMPTASK_H
#define CDUMPTASK_H

#include "CLinkTask.h"
#include "databaseData.h"

!!enter system!!
!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!

/////////////////////////////////////////////////////////////////////////
///CDump!!@name!!Task��һ��������!!@usage!!��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDump!!@name!!Task: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDump!!@name!!Task(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDump!!@name!!Task(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	C!!@name!!Factory *m_pFactory;
	FILE *m_output;
	CWriteable!!@name!! *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};

!!endif!!
!!next!!

/////////////////////////////////////////////////////////////////////////
///CDumpTask��һ�������������ڴ����ݿ��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpTask: public CLinkTask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	virtual ~CDumpTask(void)
	{
	}
};

!!leave!!

#endif
