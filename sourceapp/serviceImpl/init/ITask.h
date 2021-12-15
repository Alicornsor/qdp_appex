/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file ITask.h
///@brief	��������ITask
///@history 
///20091203	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef ITASK_H
#define ITASK_H

/////////////////////////////////////////////////////////////////////////
///ITask��һ�����峤ʱ����ɵ�����Ļ���
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class ITask
{
private:
	int m_fullfilCost;

public:
	///���캯��
	///@param	fullfilCost	ÿ����ɵ�Ȩֵ
	ITask(int fullfilCost=1)
	{
		m_fullfilCost=fullfilCost;
	}
	
	///��������
	virtual ~ITask(void)
	{
	}
	
	///��ȡÿ����ɵ�Ȩֵ
	///@return	ÿ����ɵ�Ȩֵ
	int getFullfilCost(void)
	{
		return m_fullfilCost;
	}
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost)=0;
};

#endif
