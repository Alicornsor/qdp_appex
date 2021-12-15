/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file MemoryStack.h
///@brief	�������Զ�ջ��ʽ������ͷŵ�ĳ���ض����͵��ڴ�
///@history 
///20060513	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef MEMORYSTACK_H
#define MEMORYSTACK_H

#include "CBaseObject.h"
#include "utility.h"

/////////////////////////////////////////////////////////////////////////
///CMemoryStack<T>��һ������T���Զ�ջ��ʽ������ͷŵ��ڴ��������Ҳ����˵��
///����T��������ͷŽ�ʹ��������alloc��free���������ң���alloc��ȥ�ģ�
///һ����free�������T������ȱʡ�Ĺ����ӣ����Ҳ������ڲ������������ռ䣬
///�����������������¿���
///@author	xuzh
///@version	1.0,20060513
/////////////////////////////////////////////////////////////////////////
template <class T> class CMemoryStack: public vector<T *>
{
private:
	int allocCount;
public:
	///���캯��
	CMemoryStack(void)
	{
		allocCount=0;
	}

	///����һ��
	///@return	����õ��Ķ���
	T *alloc(void)
	{
		if (allocCount==vector<T *>::size())
		{
			//	push_back(new T);    //2013-01-24 g++ -fpermissive ���벻ͨ��
			//	�����ǰ����vector�е�ָ�붼�ù��ˣ�������һ���µĶ��󣬲���ָ�����������С�
			//	longqy 20130905
			this->push_back(new T);
		}
		return vector<T *>::at(allocCount++);	// ֱ���ظ�ʹ��ǰ�����Ķ���
	}

	///�ͷ�һ��
	///@param	p	Ҫ�ͷŵĶ���
	/// �����������ָ�룩�Ǵ��������vector�У������е��ͷ�ָ����������Ч�ˡ�
	/// ����ֻ�ǰ��������������������һ���������ָ����Ч�ˡ�
	/// �����Ķ�������û���ͷ� longqy 20130905
	void free(T *p)
	{
		allocCount--;
	}
	
	/// �ͷ����ж���
	/// ��ʾ����vector�У����е�ָ�붼��Ч�ˡ�
	void clear(void)
	{
		allocCount=0;
	}
}; 

#endif
