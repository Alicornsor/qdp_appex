/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CLinkTask.h
///@brief	��������CLinkTask
///@history 
///20091203	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CLINKTASK_H
#define CLINKTASK_H

#include "platform.h"
#include "ITask.h"

/////////////////////////////////////////////////////////////////////////
///CLinkTask��һ�����彫����������ӳ�һ�������������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CLinkTask: public ITask
{
private:
	queue<ITask *> m_tasks;

public:
	///���캯��
	CLinkTask(void);
	
	///��������
	virtual ~CLinkTask(void);
	
	///�������
	///@param	pTask	Ҫ��ӵ�����
	void addTask(ITask *pTask);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);
};

#endif
