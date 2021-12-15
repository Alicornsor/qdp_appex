/////////////////////////////////////////////////////////////////////////
///@system ִ������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file databaseIteratorRepository.h
///@brief	���������ɸ��ڴ����ݿ��iterator�⣬�Ա���ֲ�ѯ
///@history 
///20121227	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef DATABASEITERATORREPOSITORY_H
#define DATABASEITERATORREPOSITORY_H

#include "BaseDataStruct.h"
#include "databaseFactories.h"

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusSingleIterator�����෵��һ������ͬ��״̬���ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusSingleIterator: public CDataSyncStatusIterator
{
private:
	CDataSyncStatus *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CDataSyncStatusSingleIterator(CDataSyncStatusFactory *pFactory,CDataSyncStatus *pResult)
		:CDataSyncStatusIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CDataSyncStatusSingleIterator(void)
	{
	}

	///Ѱ����һ������������CDataSyncStatus
	///@return	��һ����������CDataSyncStatus������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CDataSyncStatus *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pDataSyncStatus ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableDataSyncStatus * pDataSyncStatus,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusPredict���ж�һ������ͬ��״̬���Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusPredict
{
public:
	virtual ~CDataSyncStatusPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pDataSyncStatus	Ҫ���жϵ�����ͬ��״̬��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CDataSyncStatus *pDataSyncStatus)=0;
};

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusAndPredict�Ƕ���������ͬ��״̬��ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusAndPredict : public CDataSyncStatusPredict
{
private:
	CDataSyncStatusPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CDataSyncStatusAndPredict(CDataSyncStatusPredict *p1, CDataSyncStatusPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CDataSyncStatusAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pDataSyncStatus	Ҫ���жϵ�����ͬ��״̬��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CDataSyncStatus *pDataSyncStatus)
	{
		return m_p1->isValid(pDataSyncStatus) && m_p2->isValid(pDataSyncStatus);
	}
};

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusOrPredict�Ƕ���������ͬ��״̬��ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusOrPredict : public CDataSyncStatusPredict
{
private:
	CDataSyncStatusPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CDataSyncStatusOrPredict(CDataSyncStatusPredict *p1, CDataSyncStatusPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CDataSyncStatusOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pDataSyncStatus	Ҫ���жϵ�����ͬ��״̬��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CDataSyncStatus *pDataSyncStatus)
	{
		return m_p1->isValid(pDataSyncStatus) || m_p2->isValid(pDataSyncStatus);
	}
};

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusNotPredict�Ƕ�һ������ͬ��״̬��ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusNotPredict : public CDataSyncStatusPredict
{
private:
	CDataSyncStatusPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CDataSyncStatusNotPredict(CDataSyncStatusPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CDataSyncStatusNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pDataSyncStatus	Ҫ���жϵ�����ͬ��״̬��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CDataSyncStatus *pDataSyncStatus)
	{
		return !m_predict->isValid(pDataSyncStatus);
	}
};

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusFilter��һ�������е�����ͬ��״̬��ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusFilter: public CDataSyncStatusIterator
{
private:
	CDataSyncStatusIterator *m_baseIterator;
	CDataSyncStatusPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CDataSyncStatusFilter(CDataSyncStatusIterator *pBaseIterator, CDataSyncStatusPredict *pPredict, bool continueResult=false)
		:CDataSyncStatusIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CDataSyncStatusFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CDataSyncStatus
	///@return	��һ����������CDataSyncStatus������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CDataSyncStatus *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pDataSyncStatus ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableDataSyncStatus * pDataSyncStatus,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusLinkIterator��������������ͬ��״̬��ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusLinkIterator: public CDataSyncStatusIterator
{
private:
	CDataSyncStatusIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CDataSyncStatusLinkIterator(CDataSyncStatusIterator *pBaseIterator1,CDataSyncStatusIterator *pBaseIterator2)
		:CDataSyncStatusIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CDataSyncStatusLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CDataSyncStatus
	///@return	��һ����������CDataSyncStatus������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CDataSyncStatus *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pDataSyncStatus ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableDataSyncStatus * pDataSyncStatus,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CSystemStatusSingleIterator�����෵��һ��QDP״̬���ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusSingleIterator: public CSystemStatusIterator
{
private:
	CSystemStatus *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CSystemStatusSingleIterator(CSystemStatusFactory *pFactory,CSystemStatus *pResult)
		:CSystemStatusIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CSystemStatusSingleIterator(void)
	{
	}

	///Ѱ����һ������������CSystemStatus
	///@return	��һ����������CSystemStatus������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSystemStatus *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pSystemStatus ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSystemStatus * pSystemStatus,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusPredict���ж�һ��QDP״̬���Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusPredict
{
public:
	virtual ~CSystemStatusPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pSystemStatus	Ҫ���жϵ�QDP״̬��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSystemStatus *pSystemStatus)=0;
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusAndPredict�Ƕ�����QDP״̬��ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusAndPredict : public CSystemStatusPredict
{
private:
	CSystemStatusPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CSystemStatusAndPredict(CSystemStatusPredict *p1, CSystemStatusPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CSystemStatusAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pSystemStatus	Ҫ���жϵ�QDP״̬��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSystemStatus *pSystemStatus)
	{
		return m_p1->isValid(pSystemStatus) && m_p2->isValid(pSystemStatus);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusOrPredict�Ƕ�����QDP״̬��ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusOrPredict : public CSystemStatusPredict
{
private:
	CSystemStatusPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CSystemStatusOrPredict(CSystemStatusPredict *p1, CSystemStatusPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CSystemStatusOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pSystemStatus	Ҫ���жϵ�QDP״̬��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSystemStatus *pSystemStatus)
	{
		return m_p1->isValid(pSystemStatus) || m_p2->isValid(pSystemStatus);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusNotPredict�Ƕ�һ��QDP״̬��ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusNotPredict : public CSystemStatusPredict
{
private:
	CSystemStatusPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CSystemStatusNotPredict(CSystemStatusPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CSystemStatusNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pSystemStatus	Ҫ���жϵ�QDP״̬��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSystemStatus *pSystemStatus)
	{
		return !m_predict->isValid(pSystemStatus);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusFilter��һ�������е�QDP״̬��ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusFilter: public CSystemStatusIterator
{
private:
	CSystemStatusIterator *m_baseIterator;
	CSystemStatusPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CSystemStatusFilter(CSystemStatusIterator *pBaseIterator, CSystemStatusPredict *pPredict, bool continueResult=false)
		:CSystemStatusIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CSystemStatusFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CSystemStatus
	///@return	��һ����������CSystemStatus������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSystemStatus *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pSystemStatus ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSystemStatus * pSystemStatus,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusLinkIterator����������QDP״̬��ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusLinkIterator: public CSystemStatusIterator
{
private:
	CSystemStatusIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CSystemStatusLinkIterator(CSystemStatusIterator *pBaseIterator1,CSystemStatusIterator *pBaseIterator2)
		:CSystemStatusIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CSystemStatusLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CSystemStatus
	///@return	��һ����������CSystemStatus������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSystemStatus *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pSystemStatus ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSystemStatus * pSystemStatus,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///COrderActionSingleIterator�����෵��һ������������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionSingleIterator: public COrderActionIterator
{
private:
	COrderAction *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	COrderActionSingleIterator(COrderActionFactory *pFactory,COrderAction *pResult)
		:COrderActionIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~COrderActionSingleIterator(void)
	{
	}

	///Ѱ����һ������������COrderAction
	///@return	��һ����������COrderAction������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrderAction *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrderAction ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrderAction * pOrderAction,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionPredict���ж�һ�����������Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionPredict
{
public:
	virtual ~COrderActionPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pOrderAction	Ҫ���жϵı�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderAction *pOrderAction)=0;
};

/////////////////////////////////////////////////////////////////////////
///COrderActionAndPredict�Ƕ�������������ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionAndPredict : public COrderActionPredict
{
private:
	COrderActionPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	COrderActionAndPredict(COrderActionPredict *p1, COrderActionPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~COrderActionAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pOrderAction	Ҫ���жϵı�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderAction *pOrderAction)
	{
		return m_p1->isValid(pOrderAction) && m_p2->isValid(pOrderAction);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderActionOrPredict�Ƕ�������������ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionOrPredict : public COrderActionPredict
{
private:
	COrderActionPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	COrderActionOrPredict(COrderActionPredict *p1, COrderActionPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~COrderActionOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pOrderAction	Ҫ���жϵı�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderAction *pOrderAction)
	{
		return m_p1->isValid(pOrderAction) || m_p2->isValid(pOrderAction);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderActionNotPredict�Ƕ�һ����������ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionNotPredict : public COrderActionPredict
{
private:
	COrderActionPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	COrderActionNotPredict(COrderActionPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~COrderActionNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pOrderAction	Ҫ���жϵı�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderAction *pOrderAction)
	{
		return !m_predict->isValid(pOrderAction);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderActionFilter��һ�������еı�������ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionFilter: public COrderActionIterator
{
private:
	COrderActionIterator *m_baseIterator;
	COrderActionPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	COrderActionFilter(COrderActionIterator *pBaseIterator, COrderActionPredict *pPredict, bool continueResult=false)
		:COrderActionIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~COrderActionFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������COrderAction
	///@return	��һ����������COrderAction������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrderAction *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrderAction ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrderAction * pOrderAction,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionLinkIterator������������������ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionLinkIterator: public COrderActionIterator
{
private:
	COrderActionIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	COrderActionLinkIterator(COrderActionIterator *pBaseIterator1,COrderActionIterator *pBaseIterator2)
		:COrderActionIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~COrderActionLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������COrderAction
	///@return	��һ����������COrderAction������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrderAction *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrderAction ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrderAction * pOrderAction,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderOfOrderActionIterator��һ����������ö������Ӧ�ı�����ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderOfOrderActionIterator: public COrderIterator
{
private:
	COrderActionIterator *m_baseIterator;
	COrder *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	COrderOfOrderActionIterator(COrderFactory *pFactory,COrderActionIterator *pBaseIterator)
		:COrderIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~COrderOfOrderActionIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������COrder
	///@return	��һ����������COrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrder ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrder *pOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderOfOrderActionIterator��һ����������ö������Ӧ�ı�����ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderOfOrderActionIterator: public CPreOrderIterator
{
private:
	COrderActionIterator *m_baseIterator;
	CPreOrder *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CPreOrderOfOrderActionIterator(CPreOrderFactory *pFactory,COrderActionIterator *pBaseIterator)
		:CPreOrderIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CPreOrderOfOrderActionIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CPreOrder
	///@return	��һ����������CPreOrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CPreOrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pPreOrder ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteablePreOrder *pPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///COrderSingleIterator�����෵��һ��ί�б��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderSingleIterator: public COrderIterator
{
private:
	COrder *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	COrderSingleIterator(COrderFactory *pFactory,COrder *pResult)
		:COrderIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~COrderSingleIterator(void)
	{
	}

	///Ѱ����һ������������COrder
	///@return	��һ����������COrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrder ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrder * pOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderPredict���ж�һ��ί�б��Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderPredict
{
public:
	virtual ~COrderPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pOrder	Ҫ���жϵ�ί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrder *pOrder)=0;
};

/////////////////////////////////////////////////////////////////////////
///COrderAndPredict�Ƕ�����ί�б�ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderAndPredict : public COrderPredict
{
private:
	COrderPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	COrderAndPredict(COrderPredict *p1, COrderPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~COrderAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pOrder	Ҫ���жϵ�ί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrder *pOrder)
	{
		return m_p1->isValid(pOrder) && m_p2->isValid(pOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderOrPredict�Ƕ�����ί�б�ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderOrPredict : public COrderPredict
{
private:
	COrderPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	COrderOrPredict(COrderPredict *p1, COrderPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~COrderOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pOrder	Ҫ���жϵ�ί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrder *pOrder)
	{
		return m_p1->isValid(pOrder) || m_p2->isValid(pOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderNotPredict�Ƕ�һ��ί�б�ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderNotPredict : public COrderPredict
{
private:
	COrderPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	COrderNotPredict(COrderPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~COrderNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pOrder	Ҫ���жϵ�ί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrder *pOrder)
	{
		return !m_predict->isValid(pOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderFilter��һ�������е�ί�б�ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderFilter: public COrderIterator
{
private:
	COrderIterator *m_baseIterator;
	COrderPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	COrderFilter(COrderIterator *pBaseIterator, COrderPredict *pPredict, bool continueResult=false)
		:COrderIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~COrderFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������COrder
	///@return	��һ����������COrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrder ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrder * pOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderLinkIterator����������ί�б�ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderLinkIterator: public COrderIterator
{
private:
	COrderIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	COrderLinkIterator(COrderIterator *pBaseIterator1,COrderIterator *pBaseIterator2)
		:COrderIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~COrderLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������COrder
	///@return	��һ����������COrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrder ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrder * pOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOfOrderIterator��һ��ί�б�ö������Ӧ��Ͷ���ߵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOfOrderIterator: public CInvestorIterator
{
private:
	COrderIterator *m_baseIterator;
	CInvestor *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorOfOrderIterator(CInvestorFactory *pFactory,COrderIterator *pBaseIterator)
		:CInvestorIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestor
	///@return	��һ����������CInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestor *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestor ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestor *pInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDOfOrderIterator��һ��ί�б�ö������Ӧ�Ľ��ױ����ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDOfOrderIterator: public CClientTradingIDIterator
{
private:
	COrderIterator *m_baseIterator;
	CClientTradingID *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CClientTradingIDOfOrderIterator(CClientTradingIDFactory *pFactory,COrderIterator *pBaseIterator)
		:CClientTradingIDIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CClientTradingIDOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CClientTradingID
	///@return	��һ����������CClientTradingID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CClientTradingID *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pClientTradingID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableClientTradingID *pClientTradingID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountOfOrderIterator��һ��ί�б�ö������Ӧ���ʻ���ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountOfOrderIterator: public CInvestorAccountIterator
{
private:
	COrderIterator *m_baseIterator;
	CInvestorAccount *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorAccountOfOrderIterator(CInvestorAccountFactory *pFactory,COrderIterator *pBaseIterator)
		:CInvestorAccountIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorAccountOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorAccount
	///@return	��һ����������CInvestorAccount������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorAccount *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorAccount ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorAccount *pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionOfOrderIterator��һ��ί�б�ö������Ӧ�ĺ�Լ�ֲ���Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionOfOrderIterator: public CInvestorPositionIterator
{
private:
	COrderIterator *m_baseIterator;
	CInvestorPosition *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorPositionOfOrderIterator(CInvestorPositionFactory *pFactory,COrderIterator *pBaseIterator)
		:CInvestorPositionIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorPositionOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorPosition
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorPosition ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorPosition *pInvestorPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentOfOrderIterator��һ��ί�б�ö������Ӧ�ĺ�Լ��Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentOfOrderIterator: public CInstrumentIterator
{
private:
	COrderIterator *m_baseIterator;
	CInstrument *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInstrumentOfOrderIterator(CInstrumentFactory *pFactory,COrderIterator *pBaseIterator)
		:CInstrumentIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInstrumentOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInstrument
	///@return	��һ����������CInstrument������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInstrument *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInstrument ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInstrument *pInstrument,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginOfOrderIterator��һ��ί�б�ö������Ӧ��Ͷ���߱�֤������Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginOfOrderIterator: public CInvestorMarginIterator
{
private:
	COrderIterator *m_baseIterator;
	CInvestorMargin *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorMarginOfOrderIterator(CInvestorMarginFactory *pFactory,COrderIterator *pBaseIterator)
		:CInvestorMarginIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorMarginOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorMargin
	///@return	��һ����������CInvestorMargin������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorMargin *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorMargin ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorMargin *pInvestorMargin,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeOfOrderIterator��һ��ί�б�ö������Ӧ��Ͷ��������������Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeOfOrderIterator: public CInvestorFeeIterator
{
private:
	COrderIterator *m_baseIterator;
	CInvestorFee *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorFeeOfOrderIterator(CInvestorFeeFactory *pFactory,COrderIterator *pBaseIterator)
		:CInvestorFeeIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorFeeOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorFee
	///@return	��һ����������CInvestorFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorFee *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorFee ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorFee *pInvestorFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeOfOrderIterator��һ��ί�б�ö������Ӧ��Ͷ������Ȩ����������Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeOfOrderIterator: public CInvestorOptionFeeIterator
{
private:
	COrderIterator *m_baseIterator;
	CInvestorOptionFee *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorOptionFeeOfOrderIterator(CInvestorOptionFeeFactory *pFactory,COrderIterator *pBaseIterator)
		:CInvestorOptionFeeIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorOptionFeeOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorOptionFee
	///@return	��һ����������CInvestorOptionFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorOptionFee *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorOptionFee ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorOptionFee *pInvestorOptionFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientGroupPositionOfOrderIterator��һ��ί�б�ö������Ӧ�ĺ�Լ�����ֲ���Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientGroupPositionOfOrderIterator: public CPartClientInsGroupPositionIterator
{
private:
	COrderIterator *m_baseIterator;
	CPartClientInsGroupPosition *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CClientGroupPositionOfOrderIterator(CPartClientInsGroupPositionFactory *pFactory,COrderIterator *pBaseIterator)
		:CPartClientInsGroupPositionIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CClientGroupPositionOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CPartClientInsGroupPosition
	///@return	��һ����������CPartClientInsGroupPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CPartClientInsGroupPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pPartClientInsGroupPosition ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CTradeSingleIterator�����෵��һ���ɽ����ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeSingleIterator: public CTradeIterator
{
private:
	CTrade *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CTradeSingleIterator(CTradeFactory *pFactory,CTrade *pResult)
		:CTradeIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CTradeSingleIterator(void)
	{
	}

	///Ѱ����һ������������CTrade
	///@return	��һ����������CTrade������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CTrade *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pTrade ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableTrade * pTrade,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CTradePredict���ж�һ���ɽ����Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradePredict
{
public:
	virtual ~CTradePredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade)=0;
};

/////////////////////////////////////////////////////////////////////////
///CTradeAndPredict�Ƕ������ɽ���ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeAndPredict : public CTradePredict
{
private:
	CTradePredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CTradeAndPredict(CTradePredict *p1, CTradePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CTradeAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade)
	{
		return m_p1->isValid(pTrade) && m_p2->isValid(pTrade);
	}
};

/////////////////////////////////////////////////////////////////////////
///CTradeOrPredict�Ƕ������ɽ���ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeOrPredict : public CTradePredict
{
private:
	CTradePredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CTradeOrPredict(CTradePredict *p1, CTradePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CTradeOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade)
	{
		return m_p1->isValid(pTrade) || m_p2->isValid(pTrade);
	}
};

/////////////////////////////////////////////////////////////////////////
///CTradeNotPredict�Ƕ�һ���ɽ���ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeNotPredict : public CTradePredict
{
private:
	CTradePredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CTradeNotPredict(CTradePredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CTradeNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pTrade	Ҫ���жϵĳɽ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CTrade *pTrade)
	{
		return !m_predict->isValid(pTrade);
	}
};

/////////////////////////////////////////////////////////////////////////
///CTradeFilter��һ�������еĳɽ���ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeFilter: public CTradeIterator
{
private:
	CTradeIterator *m_baseIterator;
	CTradePredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CTradeFilter(CTradeIterator *pBaseIterator, CTradePredict *pPredict, bool continueResult=false)
		:CTradeIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CTradeFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CTrade
	///@return	��һ����������CTrade������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CTrade *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pTrade ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableTrade * pTrade,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CTradeLinkIterator�����������ɽ���ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeLinkIterator: public CTradeIterator
{
private:
	CTradeIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CTradeLinkIterator(CTradeIterator *pBaseIterator1,CTradeIterator *pBaseIterator2)
		:CTradeIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CTradeLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CTrade
	///@return	��һ����������CTrade������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CTrade *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pTrade ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableTrade * pTrade,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CPreOrderSingleIterator�����෵��һ��Ԥί�б��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderSingleIterator: public CPreOrderIterator
{
private:
	CPreOrder *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CPreOrderSingleIterator(CPreOrderFactory *pFactory,CPreOrder *pResult)
		:CPreOrderIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CPreOrderSingleIterator(void)
	{
	}

	///Ѱ����һ������������CPreOrder
	///@return	��һ����������CPreOrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CPreOrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pPreOrder ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteablePreOrder * pPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderPredict���ж�һ��Ԥί�б��Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderPredict
{
public:
	virtual ~CPreOrderPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pPreOrder	Ҫ���жϵ�Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPreOrder *pPreOrder)=0;
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderAndPredict�Ƕ�����Ԥί�б�ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderAndPredict : public CPreOrderPredict
{
private:
	CPreOrderPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CPreOrderAndPredict(CPreOrderPredict *p1, CPreOrderPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CPreOrderAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pPreOrder	Ҫ���жϵ�Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPreOrder *pPreOrder)
	{
		return m_p1->isValid(pPreOrder) && m_p2->isValid(pPreOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderOrPredict�Ƕ�����Ԥί�б�ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderOrPredict : public CPreOrderPredict
{
private:
	CPreOrderPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CPreOrderOrPredict(CPreOrderPredict *p1, CPreOrderPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CPreOrderOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pPreOrder	Ҫ���жϵ�Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPreOrder *pPreOrder)
	{
		return m_p1->isValid(pPreOrder) || m_p2->isValid(pPreOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderNotPredict�Ƕ�һ��Ԥί�б�ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderNotPredict : public CPreOrderPredict
{
private:
	CPreOrderPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CPreOrderNotPredict(CPreOrderPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CPreOrderNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pPreOrder	Ҫ���жϵ�Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPreOrder *pPreOrder)
	{
		return !m_predict->isValid(pPreOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderFilter��һ�������е�Ԥί�б�ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderFilter: public CPreOrderIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CPreOrderPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CPreOrderFilter(CPreOrderIterator *pBaseIterator, CPreOrderPredict *pPredict, bool continueResult=false)
		:CPreOrderIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CPreOrderFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CPreOrder
	///@return	��һ����������CPreOrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CPreOrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pPreOrder ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteablePreOrder * pPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderLinkIterator����������Ԥί�б�ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderLinkIterator: public CPreOrderIterator
{
private:
	CPreOrderIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CPreOrderLinkIterator(CPreOrderIterator *pBaseIterator1,CPreOrderIterator *pBaseIterator2)
		:CPreOrderIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CPreOrderLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CPreOrder
	///@return	��һ����������CPreOrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CPreOrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pPreOrder ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteablePreOrder * pPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOfPreOrderIterator��һ��Ԥί�б�ö������Ӧ��Ͷ���ߵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOfPreOrderIterator: public CInvestorIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CInvestor *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorOfPreOrderIterator(CInvestorFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CInvestorIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestor
	///@return	��һ����������CInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestor *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestor ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestor *pInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDOfPreOrderIterator��һ��Ԥί�б�ö������Ӧ�Ľ��ױ����ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDOfPreOrderIterator: public CClientTradingIDIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CClientTradingID *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CClientTradingIDOfPreOrderIterator(CClientTradingIDFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CClientTradingIDIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CClientTradingIDOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CClientTradingID
	///@return	��һ����������CClientTradingID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CClientTradingID *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pClientTradingID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableClientTradingID *pClientTradingID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountOfPreOrderIterator��һ��Ԥί�б�ö������Ӧ���ʻ���ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountOfPreOrderIterator: public CInvestorAccountIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CInvestorAccount *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorAccountOfPreOrderIterator(CInvestorAccountFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CInvestorAccountIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorAccountOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorAccount
	///@return	��һ����������CInvestorAccount������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorAccount *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorAccount ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorAccount *pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionOfPreOrderIterator��һ��Ԥί�б�ö������Ӧ�ĺ�Լ�ֲ���Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionOfPreOrderIterator: public CInvestorPositionIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CInvestorPosition *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorPositionOfPreOrderIterator(CInvestorPositionFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CInvestorPositionIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorPositionOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorPosition
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorPosition ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorPosition *pInvestorPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentOfPreOrderIterator��һ��Ԥί�б�ö������Ӧ�ĺ�Լ��Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentOfPreOrderIterator: public CInstrumentIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CInstrument *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInstrumentOfPreOrderIterator(CInstrumentFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CInstrumentIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInstrumentOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInstrument
	///@return	��һ����������CInstrument������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInstrument *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInstrument ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInstrument *pInstrument,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginOfPreOrderIterator��һ��Ԥί�б�ö������Ӧ��Ͷ���߱�֤������Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginOfPreOrderIterator: public CInvestorMarginIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CInvestorMargin *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorMarginOfPreOrderIterator(CInvestorMarginFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CInvestorMarginIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorMarginOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorMargin
	///@return	��һ����������CInvestorMargin������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorMargin *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorMargin ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorMargin *pInvestorMargin,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeOfPreOrderIterator��һ��Ԥί�б�ö������Ӧ��Ͷ��������������Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeOfPreOrderIterator: public CInvestorFeeIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CInvestorFee *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorFeeOfPreOrderIterator(CInvestorFeeFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CInvestorFeeIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorFeeOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorFee
	///@return	��һ����������CInvestorFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorFee *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorFee ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorFee *pInvestorFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeOfPreOrderIterator��һ��Ԥί�б�ö������Ӧ��Ͷ������Ȩ����������Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeOfPreOrderIterator: public CInvestorOptionFeeIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CInvestorOptionFee *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorOptionFeeOfPreOrderIterator(CInvestorOptionFeeFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CInvestorOptionFeeIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorOptionFeeOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorOptionFee
	///@return	��һ����������CInvestorOptionFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorOptionFee *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorOptionFee ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorOptionFee *pInvestorOptionFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientGroupPositionOfPreOrderIterator��һ��Ԥί�б�ö������Ӧ�ĺ�Լ�����ֲ���Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientGroupPositionOfPreOrderIterator: public CPartClientInsGroupPositionIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CPartClientInsGroupPosition *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CClientGroupPositionOfPreOrderIterator(CPartClientInsGroupPositionFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CPartClientInsGroupPositionIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CClientGroupPositionOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CPartClientInsGroupPosition
	///@return	��һ����������CPartClientInsGroupPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CPartClientInsGroupPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pPartClientInsGroupPosition ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderSingleIterator�����෵��һ������Ԥί�б��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderSingleIterator: public CIndexPreOrderIterator
{
private:
	CIndexPreOrder *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CIndexPreOrderSingleIterator(CIndexPreOrderFactory *pFactory,CIndexPreOrder *pResult)
		:CIndexPreOrderIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CIndexPreOrderSingleIterator(void)
	{
	}

	///Ѱ����һ������������CIndexPreOrder
	///@return	��һ����������CIndexPreOrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CIndexPreOrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pIndexPreOrder ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableIndexPreOrder * pIndexPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderPredict���ж�һ������Ԥί�б��Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderPredict
{
public:
	virtual ~CIndexPreOrderPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pIndexPreOrder	Ҫ���жϵ�����Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder)=0;
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderAndPredict�Ƕ���������Ԥί�б�ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderAndPredict : public CIndexPreOrderPredict
{
private:
	CIndexPreOrderPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CIndexPreOrderAndPredict(CIndexPreOrderPredict *p1, CIndexPreOrderPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CIndexPreOrderAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pIndexPreOrder	Ҫ���жϵ�����Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder)
	{
		return m_p1->isValid(pIndexPreOrder) && m_p2->isValid(pIndexPreOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderOrPredict�Ƕ���������Ԥί�б�ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderOrPredict : public CIndexPreOrderPredict
{
private:
	CIndexPreOrderPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CIndexPreOrderOrPredict(CIndexPreOrderPredict *p1, CIndexPreOrderPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CIndexPreOrderOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pIndexPreOrder	Ҫ���жϵ�����Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder)
	{
		return m_p1->isValid(pIndexPreOrder) || m_p2->isValid(pIndexPreOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderNotPredict�Ƕ�һ������Ԥί�б�ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderNotPredict : public CIndexPreOrderPredict
{
private:
	CIndexPreOrderPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CIndexPreOrderNotPredict(CIndexPreOrderPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CIndexPreOrderNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pIndexPreOrder	Ҫ���жϵ�����Ԥί�б�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder)
	{
		return !m_predict->isValid(pIndexPreOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderFilter��һ�������е�����Ԥί�б�ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderFilter: public CIndexPreOrderIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator;
	CIndexPreOrderPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CIndexPreOrderFilter(CIndexPreOrderIterator *pBaseIterator, CIndexPreOrderPredict *pPredict, bool continueResult=false)
		:CIndexPreOrderIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CIndexPreOrderFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CIndexPreOrder
	///@return	��һ����������CIndexPreOrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CIndexPreOrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pIndexPreOrder ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableIndexPreOrder * pIndexPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderLinkIterator��������������Ԥί�б�ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderLinkIterator: public CIndexPreOrderIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CIndexPreOrderLinkIterator(CIndexPreOrderIterator *pBaseIterator1,CIndexPreOrderIterator *pBaseIterator2)
		:CIndexPreOrderIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CIndexPreOrderLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CIndexPreOrder
	///@return	��һ����������CIndexPreOrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CIndexPreOrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pIndexPreOrder ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableIndexPreOrder * pIndexPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOfIndexPreOrderIterator��һ������Ԥί�б�ö������Ӧ��Ͷ���ߵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOfIndexPreOrderIterator: public CInvestorIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator;
	CInvestor *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorOfIndexPreOrderIterator(CInvestorFactory *pFactory,CIndexPreOrderIterator *pBaseIterator)
		:CInvestorIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorOfIndexPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestor
	///@return	��һ����������CInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestor *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestor ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestor *pInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDOfIndexPreOrderIterator��һ������Ԥί�б�ö������Ӧ�Ľ��ױ����ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDOfIndexPreOrderIterator: public CClientTradingIDIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator;
	CClientTradingID *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CClientTradingIDOfIndexPreOrderIterator(CClientTradingIDFactory *pFactory,CIndexPreOrderIterator *pBaseIterator)
		:CClientTradingIDIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CClientTradingIDOfIndexPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CClientTradingID
	///@return	��һ����������CClientTradingID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CClientTradingID *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pClientTradingID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableClientTradingID *pClientTradingID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountOfIndexPreOrderIterator��һ������Ԥί�б�ö������Ӧ���ʻ���ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountOfIndexPreOrderIterator: public CInvestorAccountIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator;
	CInvestorAccount *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorAccountOfIndexPreOrderIterator(CInvestorAccountFactory *pFactory,CIndexPreOrderIterator *pBaseIterator)
		:CInvestorAccountIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorAccountOfIndexPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorAccount
	///@return	��һ����������CInvestorAccount������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorAccount *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorAccount ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorAccount *pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentOfIndexPreOrderIterator��һ������Ԥί�б�ö������Ӧ�ĺ�Լ��Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentOfIndexPreOrderIterator: public CInstrumentIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator;
	CInstrument *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInstrumentOfIndexPreOrderIterator(CInstrumentFactory *pFactory,CIndexPreOrderIterator *pBaseIterator)
		:CInstrumentIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInstrumentOfIndexPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInstrument
	///@return	��һ����������CInstrument������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInstrument *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInstrument ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInstrument *pInstrument,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginOfIndexPreOrderIterator��һ������Ԥί�б�ö������Ӧ��Ͷ���߱�֤������Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginOfIndexPreOrderIterator: public CInvestorMarginIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator;
	CInvestorMargin *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorMarginOfIndexPreOrderIterator(CInvestorMarginFactory *pFactory,CIndexPreOrderIterator *pBaseIterator)
		:CInvestorMarginIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorMarginOfIndexPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorMargin
	///@return	��һ����������CInvestorMargin������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorMargin *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorMargin ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorMargin *pInvestorMargin,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeOfIndexPreOrderIterator��һ������Ԥί�б�ö������Ӧ��Ͷ��������������Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeOfIndexPreOrderIterator: public CInvestorFeeIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator;
	CInvestorFee *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorFeeOfIndexPreOrderIterator(CInvestorFeeFactory *pFactory,CIndexPreOrderIterator *pBaseIterator)
		:CInvestorFeeIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorFeeOfIndexPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorFee
	///@return	��һ����������CInvestorFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorFee *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorFee ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorFee *pInvestorFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientGroupPositionOfIndexPreOrderIterator��һ������Ԥί�б�ö������Ӧ�ĺ�Լ�����ֲ���Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientGroupPositionOfIndexPreOrderIterator: public CPartClientInsGroupPositionIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator;
	CPartClientInsGroupPosition *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CClientGroupPositionOfIndexPreOrderIterator(CPartClientInsGroupPositionFactory *pFactory,CIndexPreOrderIterator *pBaseIterator)
		:CPartClientInsGroupPositionIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CClientGroupPositionOfIndexPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CPartClientInsGroupPosition
	///@return	��һ����������CPartClientInsGroupPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CPartClientInsGroupPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pPartClientInsGroupPosition ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorPositionSingleIterator�����෵��һ���ֱֲ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionSingleIterator: public CInvestorPositionIterator
{
private:
	CInvestorPosition *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CInvestorPositionSingleIterator(CInvestorPositionFactory *pFactory,CInvestorPosition *pResult)
		:CInvestorPositionIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CInvestorPositionSingleIterator(void)
	{
	}

	///Ѱ����һ������������CInvestorPosition
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorPosition ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorPosition * pInvestorPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionPredict���ж�һ���ֱֲ��Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionPredict
{
public:
	virtual ~CInvestorPositionPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorPosition	Ҫ���жϵĳֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorPosition *pInvestorPosition)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionAndPredict�Ƕ������ֱֲ�ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionAndPredict : public CInvestorPositionPredict
{
private:
	CInvestorPositionPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInvestorPositionAndPredict(CInvestorPositionPredict *p1, CInvestorPositionPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInvestorPositionAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorPosition	Ҫ���жϵĳֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorPosition *pInvestorPosition)
	{
		return m_p1->isValid(pInvestorPosition) && m_p2->isValid(pInvestorPosition);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionOrPredict�Ƕ������ֱֲ�ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionOrPredict : public CInvestorPositionPredict
{
private:
	CInvestorPositionPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInvestorPositionOrPredict(CInvestorPositionPredict *p1, CInvestorPositionPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInvestorPositionOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorPosition	Ҫ���жϵĳֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorPosition *pInvestorPosition)
	{
		return m_p1->isValid(pInvestorPosition) || m_p2->isValid(pInvestorPosition);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionNotPredict�Ƕ�һ���ֱֲ�ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionNotPredict : public CInvestorPositionPredict
{
private:
	CInvestorPositionPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CInvestorPositionNotPredict(CInvestorPositionPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CInvestorPositionNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorPosition	Ҫ���жϵĳֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorPosition *pInvestorPosition)
	{
		return !m_predict->isValid(pInvestorPosition);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionFilter��һ�������еĳֱֲ�ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionFilter: public CInvestorPositionIterator
{
private:
	CInvestorPositionIterator *m_baseIterator;
	CInvestorPositionPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CInvestorPositionFilter(CInvestorPositionIterator *pBaseIterator, CInvestorPositionPredict *pPredict, bool continueResult=false)
		:CInvestorPositionIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CInvestorPositionFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CInvestorPosition
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorPosition ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorPosition * pInvestorPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionLinkIterator�����������ֱֲ�ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionLinkIterator: public CInvestorPositionIterator
{
private:
	CInvestorPositionIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CInvestorPositionLinkIterator(CInvestorPositionIterator *pBaseIterator1,CInvestorPositionIterator *pBaseIterator2)
		:CInvestorPositionIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CInvestorPositionLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CInvestorPosition
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorPosition ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorPosition * pInvestorPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorAccountSingleIterator�����෵��һ���˻�ʵʱ�ʽ���ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountSingleIterator: public CInvestorAccountIterator
{
private:
	CInvestorAccount *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CInvestorAccountSingleIterator(CInvestorAccountFactory *pFactory,CInvestorAccount *pResult)
		:CInvestorAccountIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CInvestorAccountSingleIterator(void)
	{
	}

	///Ѱ����һ������������CInvestorAccount
	///@return	��һ����������CInvestorAccount������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorAccount *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorAccount ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorAccount * pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountPredict���ж�һ���˻�ʵʱ�ʽ���Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountPredict
{
public:
	virtual ~CInvestorAccountPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorAccount	Ҫ���жϵ��˻�ʵʱ�ʽ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorAccount *pInvestorAccount)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountAndPredict�Ƕ������˻�ʵʱ�ʽ��ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountAndPredict : public CInvestorAccountPredict
{
private:
	CInvestorAccountPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInvestorAccountAndPredict(CInvestorAccountPredict *p1, CInvestorAccountPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInvestorAccountAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorAccount	Ҫ���жϵ��˻�ʵʱ�ʽ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorAccount *pInvestorAccount)
	{
		return m_p1->isValid(pInvestorAccount) && m_p2->isValid(pInvestorAccount);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountOrPredict�Ƕ������˻�ʵʱ�ʽ��ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountOrPredict : public CInvestorAccountPredict
{
private:
	CInvestorAccountPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInvestorAccountOrPredict(CInvestorAccountPredict *p1, CInvestorAccountPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInvestorAccountOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorAccount	Ҫ���жϵ��˻�ʵʱ�ʽ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorAccount *pInvestorAccount)
	{
		return m_p1->isValid(pInvestorAccount) || m_p2->isValid(pInvestorAccount);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountNotPredict�Ƕ�һ���˻�ʵʱ�ʽ��ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountNotPredict : public CInvestorAccountPredict
{
private:
	CInvestorAccountPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CInvestorAccountNotPredict(CInvestorAccountPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CInvestorAccountNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorAccount	Ҫ���жϵ��˻�ʵʱ�ʽ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorAccount *pInvestorAccount)
	{
		return !m_predict->isValid(pInvestorAccount);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountFilter��һ�������е��˻�ʵʱ�ʽ��ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountFilter: public CInvestorAccountIterator
{
private:
	CInvestorAccountIterator *m_baseIterator;
	CInvestorAccountPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CInvestorAccountFilter(CInvestorAccountIterator *pBaseIterator, CInvestorAccountPredict *pPredict, bool continueResult=false)
		:CInvestorAccountIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CInvestorAccountFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CInvestorAccount
	///@return	��һ����������CInvestorAccount������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorAccount *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorAccount ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorAccount * pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountLinkIterator�����������˻�ʵʱ�ʽ��ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountLinkIterator: public CInvestorAccountIterator
{
private:
	CInvestorAccountIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CInvestorAccountLinkIterator(CInvestorAccountIterator *pBaseIterator1,CInvestorAccountIterator *pBaseIterator2)
		:CInvestorAccountIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CInvestorAccountLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CInvestorAccount
	///@return	��һ����������CInvestorAccount������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorAccount *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorAccount ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorAccount * pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositSingleIterator�����෵��һ���˻�ʵʱ�������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositSingleIterator: public CInvestorAccountDepositIterator
{
private:
	CInvestorAccountDeposit *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CInvestorAccountDepositSingleIterator(CInvestorAccountDepositFactory *pFactory,CInvestorAccountDeposit *pResult)
		:CInvestorAccountDepositIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CInvestorAccountDepositSingleIterator(void)
	{
	}

	///Ѱ����һ������������CInvestorAccountDeposit
	///@return	��һ����������CInvestorAccountDeposit������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorAccountDeposit *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorAccountDeposit ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorAccountDeposit * pInvestorAccountDeposit,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositPredict���ж�һ���˻�ʵʱ�������Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositPredict
{
public:
	virtual ~CInvestorAccountDepositPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorAccountDeposit	Ҫ���жϵ��˻�ʵʱ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorAccountDeposit *pInvestorAccountDeposit)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositAndPredict�Ƕ������˻�ʵʱ������ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositAndPredict : public CInvestorAccountDepositPredict
{
private:
	CInvestorAccountDepositPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInvestorAccountDepositAndPredict(CInvestorAccountDepositPredict *p1, CInvestorAccountDepositPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInvestorAccountDepositAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorAccountDeposit	Ҫ���жϵ��˻�ʵʱ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return m_p1->isValid(pInvestorAccountDeposit) && m_p2->isValid(pInvestorAccountDeposit);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositOrPredict�Ƕ������˻�ʵʱ������ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositOrPredict : public CInvestorAccountDepositPredict
{
private:
	CInvestorAccountDepositPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInvestorAccountDepositOrPredict(CInvestorAccountDepositPredict *p1, CInvestorAccountDepositPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInvestorAccountDepositOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorAccountDeposit	Ҫ���жϵ��˻�ʵʱ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return m_p1->isValid(pInvestorAccountDeposit) || m_p2->isValid(pInvestorAccountDeposit);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositNotPredict�Ƕ�һ���˻�ʵʱ������ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositNotPredict : public CInvestorAccountDepositPredict
{
private:
	CInvestorAccountDepositPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CInvestorAccountDepositNotPredict(CInvestorAccountDepositPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CInvestorAccountDepositNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorAccountDeposit	Ҫ���жϵ��˻�ʵʱ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return !m_predict->isValid(pInvestorAccountDeposit);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositFilter��һ�������е��˻�ʵʱ������ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositFilter: public CInvestorAccountDepositIterator
{
private:
	CInvestorAccountDepositIterator *m_baseIterator;
	CInvestorAccountDepositPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CInvestorAccountDepositFilter(CInvestorAccountDepositIterator *pBaseIterator, CInvestorAccountDepositPredict *pPredict, bool continueResult=false)
		:CInvestorAccountDepositIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CInvestorAccountDepositFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CInvestorAccountDeposit
	///@return	��һ����������CInvestorAccountDeposit������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorAccountDeposit *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorAccountDeposit ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorAccountDeposit * pInvestorAccountDeposit,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositLinkIterator�����������˻�ʵʱ������ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositLinkIterator: public CInvestorAccountDepositIterator
{
private:
	CInvestorAccountDepositIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CInvestorAccountDepositLinkIterator(CInvestorAccountDepositIterator *pBaseIterator1,CInvestorAccountDepositIterator *pBaseIterator2)
		:CInvestorAccountDepositIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CInvestorAccountDepositLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CInvestorAccountDeposit
	///@return	��һ����������CInvestorAccountDeposit������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorAccountDeposit *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorAccountDeposit ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorAccountDeposit * pInvestorAccountDeposit,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CExchangeSingleIterator�����෵��һ�����������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeSingleIterator: public CExchangeIterator
{
private:
	CExchange *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CExchangeSingleIterator(CExchangeFactory *pFactory,CExchange *pResult)
		:CExchangeIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CExchangeSingleIterator(void)
	{
	}

	///Ѱ����һ������������CExchange
	///@return	��һ����������CExchange������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CExchange *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pExchange ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableExchange * pExchange,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CExchangePredict���ж�һ�����������Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangePredict
{
public:
	virtual ~CExchangePredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pExchange	Ҫ���жϵĽ�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CExchange *pExchange)=0;
};

/////////////////////////////////////////////////////////////////////////
///CExchangeAndPredict�Ƕ�������������ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeAndPredict : public CExchangePredict
{
private:
	CExchangePredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CExchangeAndPredict(CExchangePredict *p1, CExchangePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CExchangeAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pExchange	Ҫ���жϵĽ�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CExchange *pExchange)
	{
		return m_p1->isValid(pExchange) && m_p2->isValid(pExchange);
	}
};

/////////////////////////////////////////////////////////////////////////
///CExchangeOrPredict�Ƕ�������������ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeOrPredict : public CExchangePredict
{
private:
	CExchangePredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CExchangeOrPredict(CExchangePredict *p1, CExchangePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CExchangeOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pExchange	Ҫ���жϵĽ�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CExchange *pExchange)
	{
		return m_p1->isValid(pExchange) || m_p2->isValid(pExchange);
	}
};

/////////////////////////////////////////////////////////////////////////
///CExchangeNotPredict�Ƕ�һ����������ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeNotPredict : public CExchangePredict
{
private:
	CExchangePredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CExchangeNotPredict(CExchangePredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CExchangeNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pExchange	Ҫ���жϵĽ�������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CExchange *pExchange)
	{
		return !m_predict->isValid(pExchange);
	}
};

/////////////////////////////////////////////////////////////////////////
///CExchangeFilter��һ�������еĽ�������ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeFilter: public CExchangeIterator
{
private:
	CExchangeIterator *m_baseIterator;
	CExchangePredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CExchangeFilter(CExchangeIterator *pBaseIterator, CExchangePredict *pPredict, bool continueResult=false)
		:CExchangeIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CExchangeFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CExchange
	///@return	��һ����������CExchange������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CExchange *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pExchange ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableExchange * pExchange,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CExchangeLinkIterator������������������ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeLinkIterator: public CExchangeIterator
{
private:
	CExchangeIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CExchangeLinkIterator(CExchangeIterator *pBaseIterator1,CExchangeIterator *pBaseIterator2)
		:CExchangeIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CExchangeLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CExchange
	///@return	��һ����������CExchange������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CExchange *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pExchange ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableExchange * pExchange,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CSeatSingleIterator�����෵��һ���µ�ϯλ���ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatSingleIterator: public CSeatIterator
{
private:
	CSeat *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CSeatSingleIterator(CSeatFactory *pFactory,CSeat *pResult)
		:CSeatIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CSeatSingleIterator(void)
	{
	}

	///Ѱ����һ������������CSeat
	///@return	��һ����������CSeat������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSeat *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pSeat ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSeat * pSeat,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CSeatPredict���ж�һ���µ�ϯλ���Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatPredict
{
public:
	virtual ~CSeatPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pSeat	Ҫ���жϵ��µ�ϯλ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSeat *pSeat)=0;
};

/////////////////////////////////////////////////////////////////////////
///CSeatAndPredict�Ƕ������µ�ϯλ��ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatAndPredict : public CSeatPredict
{
private:
	CSeatPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CSeatAndPredict(CSeatPredict *p1, CSeatPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CSeatAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pSeat	Ҫ���жϵ��µ�ϯλ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSeat *pSeat)
	{
		return m_p1->isValid(pSeat) && m_p2->isValid(pSeat);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSeatOrPredict�Ƕ������µ�ϯλ��ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatOrPredict : public CSeatPredict
{
private:
	CSeatPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CSeatOrPredict(CSeatPredict *p1, CSeatPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CSeatOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pSeat	Ҫ���жϵ��µ�ϯλ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSeat *pSeat)
	{
		return m_p1->isValid(pSeat) || m_p2->isValid(pSeat);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSeatNotPredict�Ƕ�һ���µ�ϯλ��ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatNotPredict : public CSeatPredict
{
private:
	CSeatPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CSeatNotPredict(CSeatPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CSeatNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pSeat	Ҫ���жϵ��µ�ϯλ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSeat *pSeat)
	{
		return !m_predict->isValid(pSeat);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSeatFilter��һ�������е��µ�ϯλ��ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatFilter: public CSeatIterator
{
private:
	CSeatIterator *m_baseIterator;
	CSeatPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CSeatFilter(CSeatIterator *pBaseIterator, CSeatPredict *pPredict, bool continueResult=false)
		:CSeatIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CSeatFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CSeat
	///@return	��һ����������CSeat������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSeat *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pSeat ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSeat * pSeat,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CSeatLinkIterator�����������µ�ϯλ��ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatLinkIterator: public CSeatIterator
{
private:
	CSeatIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CSeatLinkIterator(CSeatIterator *pBaseIterator1,CSeatIterator *pBaseIterator2)
		:CSeatIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CSeatLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CSeat
	///@return	��һ����������CSeat������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSeat *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pSeat ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSeat * pSeat,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInstrumentSingleIterator�����෵��һ���ڻ���Լ���ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentSingleIterator: public CInstrumentIterator
{
private:
	CInstrument *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CInstrumentSingleIterator(CInstrumentFactory *pFactory,CInstrument *pResult)
		:CInstrumentIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CInstrumentSingleIterator(void)
	{
	}

	///Ѱ����һ������������CInstrument
	///@return	��һ����������CInstrument������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInstrument *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInstrument ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInstrument * pInstrument,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentPredict���ж�һ���ڻ���Լ���Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentPredict
{
public:
	virtual ~CInstrumentPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pInstrument	Ҫ���жϵ��ڻ���Լ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInstrument *pInstrument)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentAndPredict�Ƕ������ڻ���Լ��ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentAndPredict : public CInstrumentPredict
{
private:
	CInstrumentPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInstrumentAndPredict(CInstrumentPredict *p1, CInstrumentPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInstrumentAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInstrument	Ҫ���жϵ��ڻ���Լ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInstrument *pInstrument)
	{
		return m_p1->isValid(pInstrument) && m_p2->isValid(pInstrument);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentOrPredict�Ƕ������ڻ���Լ��ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentOrPredict : public CInstrumentPredict
{
private:
	CInstrumentPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInstrumentOrPredict(CInstrumentPredict *p1, CInstrumentPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInstrumentOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInstrument	Ҫ���жϵ��ڻ���Լ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInstrument *pInstrument)
	{
		return m_p1->isValid(pInstrument) || m_p2->isValid(pInstrument);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentNotPredict�Ƕ�һ���ڻ���Լ��ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentNotPredict : public CInstrumentPredict
{
private:
	CInstrumentPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CInstrumentNotPredict(CInstrumentPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CInstrumentNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInstrument	Ҫ���жϵ��ڻ���Լ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInstrument *pInstrument)
	{
		return !m_predict->isValid(pInstrument);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentFilter��һ�������е��ڻ���Լ��ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentFilter: public CInstrumentIterator
{
private:
	CInstrumentIterator *m_baseIterator;
	CInstrumentPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CInstrumentFilter(CInstrumentIterator *pBaseIterator, CInstrumentPredict *pPredict, bool continueResult=false)
		:CInstrumentIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CInstrumentFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CInstrument
	///@return	��һ����������CInstrument������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInstrument *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInstrument ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInstrument * pInstrument,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentLinkIterator�����������ڻ���Լ��ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentLinkIterator: public CInstrumentIterator
{
private:
	CInstrumentIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CInstrumentLinkIterator(CInstrumentIterator *pBaseIterator1,CInstrumentIterator *pBaseIterator2)
		:CInstrumentIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CInstrumentLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CInstrument
	///@return	��һ����������CInstrument������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInstrument *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInstrument ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInstrument * pInstrument,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailSingleIterator�����෵��һ���ڻ���Ϻ�Լ��ϸ���ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailSingleIterator: public CCmbInstrumentDetailIterator
{
private:
	CCmbInstrumentDetail *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CCmbInstrumentDetailSingleIterator(CCmbInstrumentDetailFactory *pFactory,CCmbInstrumentDetail *pResult)
		:CCmbInstrumentDetailIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CCmbInstrumentDetailSingleIterator(void)
	{
	}

	///Ѱ����һ������������CCmbInstrumentDetail
	///@return	��һ����������CCmbInstrumentDetail������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CCmbInstrumentDetail *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pCmbInstrumentDetail ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableCmbInstrumentDetail * pCmbInstrumentDetail,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailPredict���ж�һ���ڻ���Ϻ�Լ��ϸ���Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailPredict
{
public:
	virtual ~CCmbInstrumentDetailPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pCmbInstrumentDetail	Ҫ���жϵ��ڻ���Ϻ�Լ��ϸ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CCmbInstrumentDetail *pCmbInstrumentDetail)=0;
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailAndPredict�Ƕ������ڻ���Ϻ�Լ��ϸ��ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailAndPredict : public CCmbInstrumentDetailPredict
{
private:
	CCmbInstrumentDetailPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CCmbInstrumentDetailAndPredict(CCmbInstrumentDetailPredict *p1, CCmbInstrumentDetailPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CCmbInstrumentDetailAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pCmbInstrumentDetail	Ҫ���жϵ��ڻ���Ϻ�Լ��ϸ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return m_p1->isValid(pCmbInstrumentDetail) && m_p2->isValid(pCmbInstrumentDetail);
	}
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailOrPredict�Ƕ������ڻ���Ϻ�Լ��ϸ��ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailOrPredict : public CCmbInstrumentDetailPredict
{
private:
	CCmbInstrumentDetailPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CCmbInstrumentDetailOrPredict(CCmbInstrumentDetailPredict *p1, CCmbInstrumentDetailPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CCmbInstrumentDetailOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pCmbInstrumentDetail	Ҫ���жϵ��ڻ���Ϻ�Լ��ϸ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return m_p1->isValid(pCmbInstrumentDetail) || m_p2->isValid(pCmbInstrumentDetail);
	}
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailNotPredict�Ƕ�һ���ڻ���Ϻ�Լ��ϸ��ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailNotPredict : public CCmbInstrumentDetailPredict
{
private:
	CCmbInstrumentDetailPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CCmbInstrumentDetailNotPredict(CCmbInstrumentDetailPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CCmbInstrumentDetailNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pCmbInstrumentDetail	Ҫ���жϵ��ڻ���Ϻ�Լ��ϸ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return !m_predict->isValid(pCmbInstrumentDetail);
	}
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailFilter��һ�������е��ڻ���Ϻ�Լ��ϸ��ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailFilter: public CCmbInstrumentDetailIterator
{
private:
	CCmbInstrumentDetailIterator *m_baseIterator;
	CCmbInstrumentDetailPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CCmbInstrumentDetailFilter(CCmbInstrumentDetailIterator *pBaseIterator, CCmbInstrumentDetailPredict *pPredict, bool continueResult=false)
		:CCmbInstrumentDetailIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CCmbInstrumentDetailFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CCmbInstrumentDetail
	///@return	��һ����������CCmbInstrumentDetail������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CCmbInstrumentDetail *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pCmbInstrumentDetail ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableCmbInstrumentDetail * pCmbInstrumentDetail,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailLinkIterator�����������ڻ���Ϻ�Լ��ϸ��ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailLinkIterator: public CCmbInstrumentDetailIterator
{
private:
	CCmbInstrumentDetailIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CCmbInstrumentDetailLinkIterator(CCmbInstrumentDetailIterator *pBaseIterator1,CCmbInstrumentDetailIterator *pBaseIterator2)
		:CCmbInstrumentDetailIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CCmbInstrumentDetailLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CCmbInstrumentDetail
	///@return	��һ����������CCmbInstrumentDetail������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CCmbInstrumentDetail *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pCmbInstrumentDetail ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableCmbInstrumentDetail * pCmbInstrumentDetail,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CClientTradingIDSingleIterator�����෵��һ���������ͻ�������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDSingleIterator: public CClientTradingIDIterator
{
private:
	CClientTradingID *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CClientTradingIDSingleIterator(CClientTradingIDFactory *pFactory,CClientTradingID *pResult)
		:CClientTradingIDIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CClientTradingIDSingleIterator(void)
	{
	}

	///Ѱ����һ������������CClientTradingID
	///@return	��һ����������CClientTradingID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CClientTradingID *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pClientTradingID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableClientTradingID * pClientTradingID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDPredict���ж�һ���������ͻ�������Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDPredict
{
public:
	virtual ~CClientTradingIDPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pClientTradingID	Ҫ���жϵĽ������ͻ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientTradingID *pClientTradingID)=0;
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDAndPredict�Ƕ������������ͻ������ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDAndPredict : public CClientTradingIDPredict
{
private:
	CClientTradingIDPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CClientTradingIDAndPredict(CClientTradingIDPredict *p1, CClientTradingIDPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CClientTradingIDAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pClientTradingID	Ҫ���жϵĽ������ͻ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientTradingID *pClientTradingID)
	{
		return m_p1->isValid(pClientTradingID) && m_p2->isValid(pClientTradingID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDOrPredict�Ƕ������������ͻ������ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDOrPredict : public CClientTradingIDPredict
{
private:
	CClientTradingIDPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CClientTradingIDOrPredict(CClientTradingIDPredict *p1, CClientTradingIDPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CClientTradingIDOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pClientTradingID	Ҫ���жϵĽ������ͻ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientTradingID *pClientTradingID)
	{
		return m_p1->isValid(pClientTradingID) || m_p2->isValid(pClientTradingID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDNotPredict�Ƕ�һ���������ͻ������ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDNotPredict : public CClientTradingIDPredict
{
private:
	CClientTradingIDPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CClientTradingIDNotPredict(CClientTradingIDPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CClientTradingIDNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pClientTradingID	Ҫ���жϵĽ������ͻ������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientTradingID *pClientTradingID)
	{
		return !m_predict->isValid(pClientTradingID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDFilter��һ�������еĽ������ͻ������ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDFilter: public CClientTradingIDIterator
{
private:
	CClientTradingIDIterator *m_baseIterator;
	CClientTradingIDPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CClientTradingIDFilter(CClientTradingIDIterator *pBaseIterator, CClientTradingIDPredict *pPredict, bool continueResult=false)
		:CClientTradingIDIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CClientTradingIDFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CClientTradingID
	///@return	��һ����������CClientTradingID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CClientTradingID *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pClientTradingID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableClientTradingID * pClientTradingID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDLinkIterator�����������������ͻ������ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDLinkIterator: public CClientTradingIDIterator
{
private:
	CClientTradingIDIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CClientTradingIDLinkIterator(CClientTradingIDIterator *pBaseIterator1,CClientTradingIDIterator *pBaseIterator2)
		:CClientTradingIDIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CClientTradingIDLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CClientTradingID
	///@return	��һ����������CClientTradingID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CClientTradingID *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pClientTradingID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableClientTradingID * pClientTradingID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountOfClientTradingIDIterator��һ���������ͻ������ö������Ӧ���ʻ���ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountOfClientTradingIDIterator: public CInvestorAccountIterator
{
private:
	CClientTradingIDIterator *m_baseIterator;
	CInvestorAccount *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorAccountOfClientTradingIDIterator(CInvestorAccountFactory *pFactory,CClientTradingIDIterator *pBaseIterator)
		:CInvestorAccountIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorAccountOfClientTradingIDIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorAccount
	///@return	��һ����������CInvestorAccount������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorAccount *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorAccount ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorAccount *pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorSingleIterator�����෵��һ��Ͷ������Ϣ���ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorSingleIterator: public CInvestorIterator
{
private:
	CInvestor *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CInvestorSingleIterator(CInvestorFactory *pFactory,CInvestor *pResult)
		:CInvestorIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CInvestorSingleIterator(void)
	{
	}

	///Ѱ����һ������������CInvestor
	///@return	��һ����������CInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestor *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestor ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestor * pInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPredict���ж�һ��Ͷ������Ϣ���Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPredict
{
public:
	virtual ~CInvestorPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pInvestor	Ҫ���жϵ�Ͷ������Ϣ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestor *pInvestor)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAndPredict�Ƕ�����Ͷ������Ϣ��ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAndPredict : public CInvestorPredict
{
private:
	CInvestorPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInvestorAndPredict(CInvestorPredict *p1, CInvestorPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInvestorAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestor	Ҫ���жϵ�Ͷ������Ϣ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestor *pInvestor)
	{
		return m_p1->isValid(pInvestor) && m_p2->isValid(pInvestor);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOrPredict�Ƕ�����Ͷ������Ϣ��ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOrPredict : public CInvestorPredict
{
private:
	CInvestorPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInvestorOrPredict(CInvestorPredict *p1, CInvestorPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInvestorOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestor	Ҫ���жϵ�Ͷ������Ϣ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestor *pInvestor)
	{
		return m_p1->isValid(pInvestor) || m_p2->isValid(pInvestor);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorNotPredict�Ƕ�һ��Ͷ������Ϣ��ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorNotPredict : public CInvestorPredict
{
private:
	CInvestorPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CInvestorNotPredict(CInvestorPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CInvestorNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestor	Ҫ���жϵ�Ͷ������Ϣ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestor *pInvestor)
	{
		return !m_predict->isValid(pInvestor);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFilter��һ�������е�Ͷ������Ϣ��ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFilter: public CInvestorIterator
{
private:
	CInvestorIterator *m_baseIterator;
	CInvestorPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CInvestorFilter(CInvestorIterator *pBaseIterator, CInvestorPredict *pPredict, bool continueResult=false)
		:CInvestorIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CInvestorFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CInvestor
	///@return	��һ����������CInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestor *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestor ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestor * pInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorLinkIterator����������Ͷ������Ϣ��ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorLinkIterator: public CInvestorIterator
{
private:
	CInvestorIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CInvestorLinkIterator(CInvestorIterator *pBaseIterator1,CInvestorIterator *pBaseIterator2)
		:CInvestorIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CInvestorLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CInvestor
	///@return	��һ����������CInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestor *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestor ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestor * pInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorMarginSingleIterator�����෵��һ���ͻ��ڻ���֤���ʱ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginSingleIterator: public CInvestorMarginIterator
{
private:
	CInvestorMargin *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CInvestorMarginSingleIterator(CInvestorMarginFactory *pFactory,CInvestorMargin *pResult)
		:CInvestorMarginIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CInvestorMarginSingleIterator(void)
	{
	}

	///Ѱ����һ������������CInvestorMargin
	///@return	��һ����������CInvestorMargin������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorMargin *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorMargin ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorMargin * pInvestorMargin,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginPredict���ж�һ���ͻ��ڻ���֤���ʱ��Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginPredict
{
public:
	virtual ~CInvestorMarginPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorMargin	Ҫ���жϵĿͻ��ڻ���֤���ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorMargin *pInvestorMargin)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginAndPredict�Ƕ������ͻ��ڻ���֤���ʱ�ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginAndPredict : public CInvestorMarginPredict
{
private:
	CInvestorMarginPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInvestorMarginAndPredict(CInvestorMarginPredict *p1, CInvestorMarginPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInvestorMarginAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorMargin	Ҫ���жϵĿͻ��ڻ���֤���ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorMargin *pInvestorMargin)
	{
		return m_p1->isValid(pInvestorMargin) && m_p2->isValid(pInvestorMargin);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginOrPredict�Ƕ������ͻ��ڻ���֤���ʱ�ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginOrPredict : public CInvestorMarginPredict
{
private:
	CInvestorMarginPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInvestorMarginOrPredict(CInvestorMarginPredict *p1, CInvestorMarginPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInvestorMarginOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorMargin	Ҫ���жϵĿͻ��ڻ���֤���ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorMargin *pInvestorMargin)
	{
		return m_p1->isValid(pInvestorMargin) || m_p2->isValid(pInvestorMargin);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginNotPredict�Ƕ�һ���ͻ��ڻ���֤���ʱ�ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginNotPredict : public CInvestorMarginPredict
{
private:
	CInvestorMarginPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CInvestorMarginNotPredict(CInvestorMarginPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CInvestorMarginNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorMargin	Ҫ���жϵĿͻ��ڻ���֤���ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorMargin *pInvestorMargin)
	{
		return !m_predict->isValid(pInvestorMargin);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginFilter��һ�������еĿͻ��ڻ���֤���ʱ�ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginFilter: public CInvestorMarginIterator
{
private:
	CInvestorMarginIterator *m_baseIterator;
	CInvestorMarginPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CInvestorMarginFilter(CInvestorMarginIterator *pBaseIterator, CInvestorMarginPredict *pPredict, bool continueResult=false)
		:CInvestorMarginIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CInvestorMarginFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CInvestorMargin
	///@return	��һ����������CInvestorMargin������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorMargin *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorMargin ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorMargin * pInvestorMargin,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginLinkIterator�����������ͻ��ڻ���֤���ʱ�ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginLinkIterator: public CInvestorMarginIterator
{
private:
	CInvestorMarginIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CInvestorMarginLinkIterator(CInvestorMarginIterator *pBaseIterator1,CInvestorMarginIterator *pBaseIterator2)
		:CInvestorMarginIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CInvestorMarginLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CInvestorMargin
	///@return	��һ����������CInvestorMargin������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorMargin *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorMargin ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorMargin * pInvestorMargin,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorFeeSingleIterator�����෵��һ���ͻ��������ʱ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeSingleIterator: public CInvestorFeeIterator
{
private:
	CInvestorFee *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CInvestorFeeSingleIterator(CInvestorFeeFactory *pFactory,CInvestorFee *pResult)
		:CInvestorFeeIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CInvestorFeeSingleIterator(void)
	{
	}

	///Ѱ����һ������������CInvestorFee
	///@return	��һ����������CInvestorFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorFee *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorFee ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorFee * pInvestorFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeePredict���ж�һ���ͻ��������ʱ��Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeePredict
{
public:
	virtual ~CInvestorFeePredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorFee	Ҫ���жϵĿͻ��������ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorFee *pInvestorFee)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeAndPredict�Ƕ������ͻ��������ʱ�ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeAndPredict : public CInvestorFeePredict
{
private:
	CInvestorFeePredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInvestorFeeAndPredict(CInvestorFeePredict *p1, CInvestorFeePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInvestorFeeAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorFee	Ҫ���жϵĿͻ��������ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorFee *pInvestorFee)
	{
		return m_p1->isValid(pInvestorFee) && m_p2->isValid(pInvestorFee);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeOrPredict�Ƕ������ͻ��������ʱ�ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeOrPredict : public CInvestorFeePredict
{
private:
	CInvestorFeePredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInvestorFeeOrPredict(CInvestorFeePredict *p1, CInvestorFeePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInvestorFeeOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorFee	Ҫ���жϵĿͻ��������ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorFee *pInvestorFee)
	{
		return m_p1->isValid(pInvestorFee) || m_p2->isValid(pInvestorFee);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeNotPredict�Ƕ�һ���ͻ��������ʱ�ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeNotPredict : public CInvestorFeePredict
{
private:
	CInvestorFeePredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CInvestorFeeNotPredict(CInvestorFeePredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CInvestorFeeNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorFee	Ҫ���жϵĿͻ��������ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorFee *pInvestorFee)
	{
		return !m_predict->isValid(pInvestorFee);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeFilter��һ�������еĿͻ��������ʱ�ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeFilter: public CInvestorFeeIterator
{
private:
	CInvestorFeeIterator *m_baseIterator;
	CInvestorFeePredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CInvestorFeeFilter(CInvestorFeeIterator *pBaseIterator, CInvestorFeePredict *pPredict, bool continueResult=false)
		:CInvestorFeeIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CInvestorFeeFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CInvestorFee
	///@return	��һ����������CInvestorFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorFee *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorFee ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorFee * pInvestorFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeLinkIterator�����������ͻ��������ʱ�ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeLinkIterator: public CInvestorFeeIterator
{
private:
	CInvestorFeeIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CInvestorFeeLinkIterator(CInvestorFeeIterator *pBaseIterator1,CInvestorFeeIterator *pBaseIterator2)
		:CInvestorFeeIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CInvestorFeeLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CInvestorFee
	///@return	��һ����������CInvestorFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorFee *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorFee ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorFee * pInvestorFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CUserSingleIterator�����෵��һ���û����ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSingleIterator: public CUserIterator
{
private:
	CUser *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CUserSingleIterator(CUserFactory *pFactory,CUser *pResult)
		:CUserIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CUserSingleIterator(void)
	{
	}

	///Ѱ����һ������������CUser
	///@return	��һ����������CUser������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUser *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUser ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUser * pUser,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserPredict���ж�һ���û����Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserPredict
{
public:
	virtual ~CUserPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pUser	Ҫ���жϵ��û���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUser *pUser)=0;
};

/////////////////////////////////////////////////////////////////////////
///CUserAndPredict�Ƕ������û���ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserAndPredict : public CUserPredict
{
private:
	CUserPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CUserAndPredict(CUserPredict *p1, CUserPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CUserAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pUser	Ҫ���жϵ��û���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUser *pUser)
	{
		return m_p1->isValid(pUser) && m_p2->isValid(pUser);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserOrPredict�Ƕ������û���ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserOrPredict : public CUserPredict
{
private:
	CUserPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CUserOrPredict(CUserPredict *p1, CUserPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CUserOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pUser	Ҫ���жϵ��û���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUser *pUser)
	{
		return m_p1->isValid(pUser) || m_p2->isValid(pUser);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserNotPredict�Ƕ�һ���û���ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserNotPredict : public CUserPredict
{
private:
	CUserPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CUserNotPredict(CUserPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CUserNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pUser	Ҫ���жϵ��û���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUser *pUser)
	{
		return !m_predict->isValid(pUser);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserFilter��һ�������е��û���ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserFilter: public CUserIterator
{
private:
	CUserIterator *m_baseIterator;
	CUserPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CUserFilter(CUserIterator *pBaseIterator, CUserPredict *pPredict, bool continueResult=false)
		:CUserIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CUserFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CUser
	///@return	��һ����������CUser������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUser *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUser ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUser * pUser,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserLinkIterator�����������û���ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserLinkIterator: public CUserIterator
{
private:
	CUserIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CUserLinkIterator(CUserIterator *pBaseIterator1,CUserIterator *pBaseIterator2)
		:CUserIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CUserLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CUser
	///@return	��һ����������CUser������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUser *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUser ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUser * pUser,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CUserInvestorSingleIterator�����෵��һ���û�Ͷ���߹�ϵ���ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorSingleIterator: public CUserInvestorIterator
{
private:
	CUserInvestor *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CUserInvestorSingleIterator(CUserInvestorFactory *pFactory,CUserInvestor *pResult)
		:CUserInvestorIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CUserInvestorSingleIterator(void)
	{
	}

	///Ѱ����һ������������CUserInvestor
	///@return	��һ����������CUserInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserInvestor *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUserInvestor ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserInvestor * pUserInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorPredict���ж�һ���û�Ͷ���߹�ϵ���Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorPredict
{
public:
	virtual ~CUserInvestorPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pUserInvestor	Ҫ���жϵ��û�Ͷ���߹�ϵ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserInvestor *pUserInvestor)=0;
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorAndPredict�Ƕ������û�Ͷ���߹�ϵ��ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorAndPredict : public CUserInvestorPredict
{
private:
	CUserInvestorPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CUserInvestorAndPredict(CUserInvestorPredict *p1, CUserInvestorPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CUserInvestorAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pUserInvestor	Ҫ���жϵ��û�Ͷ���߹�ϵ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserInvestor *pUserInvestor)
	{
		return m_p1->isValid(pUserInvestor) && m_p2->isValid(pUserInvestor);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorOrPredict�Ƕ������û�Ͷ���߹�ϵ��ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorOrPredict : public CUserInvestorPredict
{
private:
	CUserInvestorPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CUserInvestorOrPredict(CUserInvestorPredict *p1, CUserInvestorPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CUserInvestorOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pUserInvestor	Ҫ���жϵ��û�Ͷ���߹�ϵ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserInvestor *pUserInvestor)
	{
		return m_p1->isValid(pUserInvestor) || m_p2->isValid(pUserInvestor);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorNotPredict�Ƕ�һ���û�Ͷ���߹�ϵ��ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorNotPredict : public CUserInvestorPredict
{
private:
	CUserInvestorPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CUserInvestorNotPredict(CUserInvestorPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CUserInvestorNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pUserInvestor	Ҫ���жϵ��û�Ͷ���߹�ϵ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserInvestor *pUserInvestor)
	{
		return !m_predict->isValid(pUserInvestor);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorFilter��һ�������е��û�Ͷ���߹�ϵ��ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorFilter: public CUserInvestorIterator
{
private:
	CUserInvestorIterator *m_baseIterator;
	CUserInvestorPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CUserInvestorFilter(CUserInvestorIterator *pBaseIterator, CUserInvestorPredict *pPredict, bool continueResult=false)
		:CUserInvestorIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CUserInvestorFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CUserInvestor
	///@return	��һ����������CUserInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserInvestor *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUserInvestor ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserInvestor * pUserInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorLinkIterator�����������û�Ͷ���߹�ϵ��ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorLinkIterator: public CUserInvestorIterator
{
private:
	CUserInvestorIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CUserInvestorLinkIterator(CUserInvestorIterator *pBaseIterator1,CUserInvestorIterator *pBaseIterator2)
		:CUserInvestorIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CUserInvestorLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CUserInvestor
	///@return	��һ����������CUserInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserInvestor *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUserInvestor ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserInvestor * pUserInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedSingleIterator�����෵��һ�������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedSingleIterator: public COrderInsertFailedIterator
{
private:
	COrderInsertFailed *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	COrderInsertFailedSingleIterator(COrderInsertFailedFactory *pFactory,COrderInsertFailed *pResult)
		:COrderInsertFailedIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~COrderInsertFailedSingleIterator(void)
	{
	}

	///Ѱ����һ������������COrderInsertFailed
	///@return	��һ����������COrderInsertFailed������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrderInsertFailed *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrderInsertFailed ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrderInsertFailed * pOrderInsertFailed,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedPredict���ж�һ�������Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedPredict
{
public:
	virtual ~COrderInsertFailedPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pOrderInsertFailed	Ҫ���жϵĴ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed)=0;
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedAndPredict�Ƕ���������ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedAndPredict : public COrderInsertFailedPredict
{
private:
	COrderInsertFailedPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	COrderInsertFailedAndPredict(COrderInsertFailedPredict *p1, COrderInsertFailedPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~COrderInsertFailedAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pOrderInsertFailed	Ҫ���жϵĴ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed)
	{
		return m_p1->isValid(pOrderInsertFailed) && m_p2->isValid(pOrderInsertFailed);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedOrPredict�Ƕ���������ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedOrPredict : public COrderInsertFailedPredict
{
private:
	COrderInsertFailedPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	COrderInsertFailedOrPredict(COrderInsertFailedPredict *p1, COrderInsertFailedPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~COrderInsertFailedOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pOrderInsertFailed	Ҫ���жϵĴ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed)
	{
		return m_p1->isValid(pOrderInsertFailed) || m_p2->isValid(pOrderInsertFailed);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedNotPredict�Ƕ�һ������ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedNotPredict : public COrderInsertFailedPredict
{
private:
	COrderInsertFailedPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	COrderInsertFailedNotPredict(COrderInsertFailedPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~COrderInsertFailedNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pOrderInsertFailed	Ҫ���жϵĴ���
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed)
	{
		return !m_predict->isValid(pOrderInsertFailed);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedFilter��һ�������еĴ���ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedFilter: public COrderInsertFailedIterator
{
private:
	COrderInsertFailedIterator *m_baseIterator;
	COrderInsertFailedPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	COrderInsertFailedFilter(COrderInsertFailedIterator *pBaseIterator, COrderInsertFailedPredict *pPredict, bool continueResult=false)
		:COrderInsertFailedIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~COrderInsertFailedFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������COrderInsertFailed
	///@return	��һ����������COrderInsertFailed������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrderInsertFailed *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrderInsertFailed ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrderInsertFailed * pOrderInsertFailed,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedLinkIterator��������������ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedLinkIterator: public COrderInsertFailedIterator
{
private:
	COrderInsertFailedIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	COrderInsertFailedLinkIterator(COrderInsertFailedIterator *pBaseIterator1,COrderInsertFailedIterator *pBaseIterator2)
		:COrderInsertFailedIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~COrderInsertFailedLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������COrderInsertFailed
	///@return	��һ����������COrderInsertFailed������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrderInsertFailed *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrderInsertFailed ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrderInsertFailed * pOrderInsertFailed,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountOfOrderInsertFailedIterator��һ������ö������Ӧ���ʻ���ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountOfOrderInsertFailedIterator: public CInvestorAccountIterator
{
private:
	COrderInsertFailedIterator *m_baseIterator;
	CInvestorAccount *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorAccountOfOrderInsertFailedIterator(CInvestorAccountFactory *pFactory,COrderInsertFailedIterator *pBaseIterator)
		:CInvestorAccountIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorAccountOfOrderInsertFailedIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorAccount
	///@return	��һ����������CInvestorAccount������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorAccount *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorAccount ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorAccount *pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionOfOrderInsertFailedIterator��һ������ö������Ӧ�ĺ�Լ�ֲ���Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionOfOrderInsertFailedIterator: public CInvestorPositionIterator
{
private:
	COrderInsertFailedIterator *m_baseIterator;
	CInvestorPosition *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorPositionOfOrderInsertFailedIterator(CInvestorPositionFactory *pFactory,COrderInsertFailedIterator *pBaseIterator)
		:CInvestorPositionIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorPositionOfOrderInsertFailedIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorPosition
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorPosition ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorPosition *pInvestorPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentOfOrderInsertFailedIterator��һ������ö������Ӧ�ĺ�Լ��Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentOfOrderInsertFailedIterator: public CInstrumentIterator
{
private:
	COrderInsertFailedIterator *m_baseIterator;
	CInstrument *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInstrumentOfOrderInsertFailedIterator(CInstrumentFactory *pFactory,COrderInsertFailedIterator *pBaseIterator)
		:CInstrumentIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInstrumentOfOrderInsertFailedIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInstrument
	///@return	��һ����������CInstrument������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInstrument *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInstrument ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInstrument *pInstrument,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginOfOrderInsertFailedIterator��һ������ö������Ӧ��Ͷ���߱�֤������Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginOfOrderInsertFailedIterator: public CInvestorMarginIterator
{
private:
	COrderInsertFailedIterator *m_baseIterator;
	CInvestorMargin *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorMarginOfOrderInsertFailedIterator(CInvestorMarginFactory *pFactory,COrderInsertFailedIterator *pBaseIterator)
		:CInvestorMarginIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorMarginOfOrderInsertFailedIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorMargin
	///@return	��һ����������CInvestorMargin������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorMargin *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorMargin ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorMargin *pInvestorMargin,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeOfOrderInsertFailedIterator��һ������ö������Ӧ��Ͷ��������������Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeOfOrderInsertFailedIterator: public CInvestorFeeIterator
{
private:
	COrderInsertFailedIterator *m_baseIterator;
	CInvestorFee *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CInvestorFeeOfOrderInsertFailedIterator(CInvestorFeeFactory *pFactory,COrderInsertFailedIterator *pBaseIterator)
		:CInvestorFeeIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CInvestorFeeOfOrderInsertFailedIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CInvestorFee
	///@return	��һ����������CInvestorFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorFee *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorFee ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorFee *pInvestorFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CUserTradingRightSingleIterator�����෵��һ���û�����Ȩ�ޱ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightSingleIterator: public CUserTradingRightIterator
{
private:
	CUserTradingRight *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CUserTradingRightSingleIterator(CUserTradingRightFactory *pFactory,CUserTradingRight *pResult)
		:CUserTradingRightIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CUserTradingRightSingleIterator(void)
	{
	}

	///Ѱ����һ������������CUserTradingRight
	///@return	��һ����������CUserTradingRight������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserTradingRight *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUserTradingRight ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserTradingRight * pUserTradingRight,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightPredict���ж�һ���û�����Ȩ�ޱ��Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightPredict
{
public:
	virtual ~CUserTradingRightPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pUserTradingRight	Ҫ���жϵ��û�����Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserTradingRight *pUserTradingRight)=0;
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightAndPredict�Ƕ������û�����Ȩ�ޱ�ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightAndPredict : public CUserTradingRightPredict
{
private:
	CUserTradingRightPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CUserTradingRightAndPredict(CUserTradingRightPredict *p1, CUserTradingRightPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CUserTradingRightAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pUserTradingRight	Ҫ���жϵ��û�����Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserTradingRight *pUserTradingRight)
	{
		return m_p1->isValid(pUserTradingRight) && m_p2->isValid(pUserTradingRight);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightOrPredict�Ƕ������û�����Ȩ�ޱ�ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightOrPredict : public CUserTradingRightPredict
{
private:
	CUserTradingRightPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CUserTradingRightOrPredict(CUserTradingRightPredict *p1, CUserTradingRightPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CUserTradingRightOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pUserTradingRight	Ҫ���жϵ��û�����Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserTradingRight *pUserTradingRight)
	{
		return m_p1->isValid(pUserTradingRight) || m_p2->isValid(pUserTradingRight);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightNotPredict�Ƕ�һ���û�����Ȩ�ޱ�ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightNotPredict : public CUserTradingRightPredict
{
private:
	CUserTradingRightPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CUserTradingRightNotPredict(CUserTradingRightPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CUserTradingRightNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pUserTradingRight	Ҫ���жϵ��û�����Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserTradingRight *pUserTradingRight)
	{
		return !m_predict->isValid(pUserTradingRight);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightFilter��һ�������е��û�����Ȩ�ޱ�ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightFilter: public CUserTradingRightIterator
{
private:
	CUserTradingRightIterator *m_baseIterator;
	CUserTradingRightPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CUserTradingRightFilter(CUserTradingRightIterator *pBaseIterator, CUserTradingRightPredict *pPredict, bool continueResult=false)
		:CUserTradingRightIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CUserTradingRightFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CUserTradingRight
	///@return	��һ����������CUserTradingRight������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserTradingRight *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUserTradingRight ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserTradingRight * pUserTradingRight,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightLinkIterator�����������û�����Ȩ�ޱ�ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightLinkIterator: public CUserTradingRightIterator
{
private:
	CUserTradingRightIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CUserTradingRightLinkIterator(CUserTradingRightIterator *pBaseIterator1,CUserTradingRightIterator *pBaseIterator2)
		:CUserTradingRightIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CUserTradingRightLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CUserTradingRight
	///@return	��һ����������CUserTradingRight������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserTradingRight *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUserTradingRight ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserTradingRight * pUserTradingRight,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CCurrentTimeSingleIterator�����෵��һ����ǰʱ���ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeSingleIterator: public CCurrentTimeIterator
{
private:
	CCurrentTime *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CCurrentTimeSingleIterator(CCurrentTimeFactory *pFactory,CCurrentTime *pResult)
		:CCurrentTimeIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CCurrentTimeSingleIterator(void)
	{
	}

	///Ѱ����һ������������CCurrentTime
	///@return	��һ����������CCurrentTime������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CCurrentTime *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pCurrentTime ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableCurrentTime * pCurrentTime,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimePredict���ж�һ����ǰʱ���Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimePredict
{
public:
	virtual ~CCurrentTimePredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pCurrentTime	Ҫ���жϵĵ�ǰʱ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CCurrentTime *pCurrentTime)=0;
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeAndPredict�Ƕ�������ǰʱ��ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeAndPredict : public CCurrentTimePredict
{
private:
	CCurrentTimePredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CCurrentTimeAndPredict(CCurrentTimePredict *p1, CCurrentTimePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CCurrentTimeAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pCurrentTime	Ҫ���жϵĵ�ǰʱ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CCurrentTime *pCurrentTime)
	{
		return m_p1->isValid(pCurrentTime) && m_p2->isValid(pCurrentTime);
	}
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeOrPredict�Ƕ�������ǰʱ��ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeOrPredict : public CCurrentTimePredict
{
private:
	CCurrentTimePredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CCurrentTimeOrPredict(CCurrentTimePredict *p1, CCurrentTimePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CCurrentTimeOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pCurrentTime	Ҫ���жϵĵ�ǰʱ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CCurrentTime *pCurrentTime)
	{
		return m_p1->isValid(pCurrentTime) || m_p2->isValid(pCurrentTime);
	}
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeNotPredict�Ƕ�һ����ǰʱ��ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeNotPredict : public CCurrentTimePredict
{
private:
	CCurrentTimePredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CCurrentTimeNotPredict(CCurrentTimePredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CCurrentTimeNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pCurrentTime	Ҫ���жϵĵ�ǰʱ��
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CCurrentTime *pCurrentTime)
	{
		return !m_predict->isValid(pCurrentTime);
	}
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeFilter��һ�������еĵ�ǰʱ��ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeFilter: public CCurrentTimeIterator
{
private:
	CCurrentTimeIterator *m_baseIterator;
	CCurrentTimePredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CCurrentTimeFilter(CCurrentTimeIterator *pBaseIterator, CCurrentTimePredict *pPredict, bool continueResult=false)
		:CCurrentTimeIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CCurrentTimeFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CCurrentTime
	///@return	��һ����������CCurrentTime������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CCurrentTime *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pCurrentTime ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableCurrentTime * pCurrentTime,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeLinkIterator������������ǰʱ��ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeLinkIterator: public CCurrentTimeIterator
{
private:
	CCurrentTimeIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CCurrentTimeLinkIterator(CCurrentTimeIterator *pBaseIterator1,CCurrentTimeIterator *pBaseIterator2)
		:CCurrentTimeIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CCurrentTimeLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CCurrentTime
	///@return	��һ����������CCurrentTime������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CCurrentTime *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pCurrentTime ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableCurrentTime * pCurrentTime,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CUserSessionSingleIterator�����෵��һ������Ա���߻Ự��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionSingleIterator: public CUserSessionIterator
{
private:
	CUserSession *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CUserSessionSingleIterator(CUserSessionFactory *pFactory,CUserSession *pResult)
		:CUserSessionIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CUserSessionSingleIterator(void)
	{
	}

	///Ѱ����һ������������CUserSession
	///@return	��һ����������CUserSession������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserSession *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUserSession ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserSession * pUserSession,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionPredict���ж�һ������Ա���߻Ự�Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionPredict
{
public:
	virtual ~CUserSessionPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pUserSession	Ҫ���жϵĽ���Ա���߻Ự
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserSession *pUserSession)=0;
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionAndPredict�Ƕ���������Ա���߻Ựν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionAndPredict : public CUserSessionPredict
{
private:
	CUserSessionPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CUserSessionAndPredict(CUserSessionPredict *p1, CUserSessionPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CUserSessionAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pUserSession	Ҫ���жϵĽ���Ա���߻Ự
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserSession *pUserSession)
	{
		return m_p1->isValid(pUserSession) && m_p2->isValid(pUserSession);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionOrPredict�Ƕ���������Ա���߻Ựν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionOrPredict : public CUserSessionPredict
{
private:
	CUserSessionPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CUserSessionOrPredict(CUserSessionPredict *p1, CUserSessionPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CUserSessionOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pUserSession	Ҫ���жϵĽ���Ա���߻Ự
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserSession *pUserSession)
	{
		return m_p1->isValid(pUserSession) || m_p2->isValid(pUserSession);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionNotPredict�Ƕ�һ������Ա���߻Ựν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionNotPredict : public CUserSessionPredict
{
private:
	CUserSessionPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CUserSessionNotPredict(CUserSessionPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CUserSessionNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pUserSession	Ҫ���жϵĽ���Ա���߻Ự
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserSession *pUserSession)
	{
		return !m_predict->isValid(pUserSession);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionFilter��һ�������еĽ���Ա���߻Ựö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionFilter: public CUserSessionIterator
{
private:
	CUserSessionIterator *m_baseIterator;
	CUserSessionPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CUserSessionFilter(CUserSessionIterator *pBaseIterator, CUserSessionPredict *pPredict, bool continueResult=false)
		:CUserSessionIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CUserSessionFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CUserSession
	///@return	��һ����������CUserSession������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserSession *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUserSession ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserSession * pUserSession,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionLinkIterator��������������Ա���߻Ựö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionLinkIterator: public CUserSessionIterator
{
private:
	CUserSessionIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CUserSessionLinkIterator(CUserSessionIterator *pBaseIterator1,CUserSessionIterator *pBaseIterator2)
		:CUserSessionIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CUserSessionLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CUserSession
	///@return	��һ����������CUserSession������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserSession *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUserSession ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserSession * pUserSession,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDSingleIterator�����෵��һ����󱾵ر����ŵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDSingleIterator: public CMaxLocalIDIterator
{
private:
	CMaxLocalID *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CMaxLocalIDSingleIterator(CMaxLocalIDFactory *pFactory,CMaxLocalID *pResult)
		:CMaxLocalIDIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CMaxLocalIDSingleIterator(void)
	{
	}

	///Ѱ����һ������������CMaxLocalID
	///@return	��һ����������CMaxLocalID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CMaxLocalID *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pMaxLocalID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableMaxLocalID * pMaxLocalID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDPredict���ж�һ����󱾵ر������Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDPredict
{
public:
	virtual ~CMaxLocalIDPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pMaxLocalID	Ҫ���жϵ���󱾵ر�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CMaxLocalID *pMaxLocalID)=0;
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDAndPredict�Ƕ�������󱾵ر�����ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDAndPredict : public CMaxLocalIDPredict
{
private:
	CMaxLocalIDPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CMaxLocalIDAndPredict(CMaxLocalIDPredict *p1, CMaxLocalIDPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CMaxLocalIDAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pMaxLocalID	Ҫ���жϵ���󱾵ر�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CMaxLocalID *pMaxLocalID)
	{
		return m_p1->isValid(pMaxLocalID) && m_p2->isValid(pMaxLocalID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDOrPredict�Ƕ�������󱾵ر�����ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDOrPredict : public CMaxLocalIDPredict
{
private:
	CMaxLocalIDPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CMaxLocalIDOrPredict(CMaxLocalIDPredict *p1, CMaxLocalIDPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CMaxLocalIDOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pMaxLocalID	Ҫ���жϵ���󱾵ر�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CMaxLocalID *pMaxLocalID)
	{
		return m_p1->isValid(pMaxLocalID) || m_p2->isValid(pMaxLocalID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDNotPredict�Ƕ�һ����󱾵ر�����ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDNotPredict : public CMaxLocalIDPredict
{
private:
	CMaxLocalIDPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CMaxLocalIDNotPredict(CMaxLocalIDPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CMaxLocalIDNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pMaxLocalID	Ҫ���жϵ���󱾵ر�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CMaxLocalID *pMaxLocalID)
	{
		return !m_predict->isValid(pMaxLocalID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDFilter��һ�������е���󱾵ر�����ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDFilter: public CMaxLocalIDIterator
{
private:
	CMaxLocalIDIterator *m_baseIterator;
	CMaxLocalIDPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CMaxLocalIDFilter(CMaxLocalIDIterator *pBaseIterator, CMaxLocalIDPredict *pPredict, bool continueResult=false)
		:CMaxLocalIDIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CMaxLocalIDFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CMaxLocalID
	///@return	��һ����������CMaxLocalID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CMaxLocalID *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pMaxLocalID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableMaxLocalID * pMaxLocalID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDLinkIterator������������󱾵ر�����ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDLinkIterator: public CMaxLocalIDIterator
{
private:
	CMaxLocalIDIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CMaxLocalIDLinkIterator(CMaxLocalIDIterator *pBaseIterator1,CMaxLocalIDIterator *pBaseIterator2)
		:CMaxLocalIDIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CMaxLocalIDLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CMaxLocalID
	///@return	��һ����������CMaxLocalID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CMaxLocalID *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pMaxLocalID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableMaxLocalID * pMaxLocalID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDSingleIterator�����෵��һ���û����ر����ŵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDSingleIterator: public CBrkUserIDLocalIDIterator
{
private:
	CBrkUserIDLocalID *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CBrkUserIDLocalIDSingleIterator(CBrkUserIDLocalIDFactory *pFactory,CBrkUserIDLocalID *pResult)
		:CBrkUserIDLocalIDIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CBrkUserIDLocalIDSingleIterator(void)
	{
	}

	///Ѱ����һ������������CBrkUserIDLocalID
	///@return	��һ����������CBrkUserIDLocalID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CBrkUserIDLocalID *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pBrkUserIDLocalID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableBrkUserIDLocalID * pBrkUserIDLocalID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDPredict���ж�һ���û����ر������Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDPredict
{
public:
	virtual ~CBrkUserIDLocalIDPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pBrkUserIDLocalID	Ҫ���жϵ��û����ر�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CBrkUserIDLocalID *pBrkUserIDLocalID)=0;
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDAndPredict�Ƕ������û����ر�����ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDAndPredict : public CBrkUserIDLocalIDPredict
{
private:
	CBrkUserIDLocalIDPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CBrkUserIDLocalIDAndPredict(CBrkUserIDLocalIDPredict *p1, CBrkUserIDLocalIDPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CBrkUserIDLocalIDAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pBrkUserIDLocalID	Ҫ���жϵ��û����ر�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return m_p1->isValid(pBrkUserIDLocalID) && m_p2->isValid(pBrkUserIDLocalID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDOrPredict�Ƕ������û����ر�����ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDOrPredict : public CBrkUserIDLocalIDPredict
{
private:
	CBrkUserIDLocalIDPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CBrkUserIDLocalIDOrPredict(CBrkUserIDLocalIDPredict *p1, CBrkUserIDLocalIDPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CBrkUserIDLocalIDOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pBrkUserIDLocalID	Ҫ���жϵ��û����ر�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return m_p1->isValid(pBrkUserIDLocalID) || m_p2->isValid(pBrkUserIDLocalID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDNotPredict�Ƕ�һ���û����ر�����ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDNotPredict : public CBrkUserIDLocalIDPredict
{
private:
	CBrkUserIDLocalIDPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CBrkUserIDLocalIDNotPredict(CBrkUserIDLocalIDPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CBrkUserIDLocalIDNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pBrkUserIDLocalID	Ҫ���жϵ��û����ر�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return !m_predict->isValid(pBrkUserIDLocalID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDFilter��һ�������е��û����ر�����ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDFilter: public CBrkUserIDLocalIDIterator
{
private:
	CBrkUserIDLocalIDIterator *m_baseIterator;
	CBrkUserIDLocalIDPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CBrkUserIDLocalIDFilter(CBrkUserIDLocalIDIterator *pBaseIterator, CBrkUserIDLocalIDPredict *pPredict, bool continueResult=false)
		:CBrkUserIDLocalIDIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CBrkUserIDLocalIDFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CBrkUserIDLocalID
	///@return	��һ����������CBrkUserIDLocalID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CBrkUserIDLocalID *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pBrkUserIDLocalID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableBrkUserIDLocalID * pBrkUserIDLocalID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDLinkIterator�����������û����ر�����ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDLinkIterator: public CBrkUserIDLocalIDIterator
{
private:
	CBrkUserIDLocalIDIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CBrkUserIDLocalIDLinkIterator(CBrkUserIDLocalIDIterator *pBaseIterator1,CBrkUserIDLocalIDIterator *pBaseIterator2)
		:CBrkUserIDLocalIDIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CBrkUserIDLocalIDLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CBrkUserIDLocalID
	///@return	��һ����������CBrkUserIDLocalID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CBrkUserIDLocalID *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pBrkUserIDLocalID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableBrkUserIDLocalID * pBrkUserIDLocalID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderOfBrkUserIDLocalIDIterator��һ���û����ر�����ö������Ӧ�ı�����ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderOfBrkUserIDLocalIDIterator: public CPreOrderIterator
{
private:
	CBrkUserIDLocalIDIterator *m_baseIterator;
	CPreOrder *m_current;
public:
	///���캯��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pBaseIterator	������ö����
	CPreOrderOfBrkUserIDLocalIDIterator(CPreOrderFactory *pFactory,CBrkUserIDLocalIDIterator *pBaseIterator)
		:CPreOrderIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///��������
	virtual ~CPreOrderOfBrkUserIDLocalIDIterator(void)
	{
		m_baseIterator->free();
	}

	///Ѱ����һ������������CPreOrder
	///@return	��һ����������CPreOrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CPreOrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pPreOrder ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteablePreOrder *pPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionSingleIterator�����෵��һ���ͻ���Լ��ֱֲ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionSingleIterator: public CPartClientInsGroupPositionIterator
{
private:
	CPartClientInsGroupPosition *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CPartClientInsGroupPositionSingleIterator(CPartClientInsGroupPositionFactory *pFactory,CPartClientInsGroupPosition *pResult)
		:CPartClientInsGroupPositionIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CPartClientInsGroupPositionSingleIterator(void)
	{
	}

	///Ѱ����һ������������CPartClientInsGroupPosition
	///@return	��һ����������CPartClientInsGroupPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CPartClientInsGroupPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pPartClientInsGroupPosition ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteablePartClientInsGroupPosition * pPartClientInsGroupPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionPredict���ж�һ���ͻ���Լ��ֱֲ��Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionPredict
{
public:
	virtual ~CPartClientInsGroupPositionPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pPartClientInsGroupPosition	Ҫ���жϵĿͻ���Լ��ֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition)=0;
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionAndPredict�Ƕ������ͻ���Լ��ֱֲ�ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionAndPredict : public CPartClientInsGroupPositionPredict
{
private:
	CPartClientInsGroupPositionPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CPartClientInsGroupPositionAndPredict(CPartClientInsGroupPositionPredict *p1, CPartClientInsGroupPositionPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CPartClientInsGroupPositionAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pPartClientInsGroupPosition	Ҫ���жϵĿͻ���Լ��ֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return m_p1->isValid(pPartClientInsGroupPosition) && m_p2->isValid(pPartClientInsGroupPosition);
	}
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionOrPredict�Ƕ������ͻ���Լ��ֱֲ�ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionOrPredict : public CPartClientInsGroupPositionPredict
{
private:
	CPartClientInsGroupPositionPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CPartClientInsGroupPositionOrPredict(CPartClientInsGroupPositionPredict *p1, CPartClientInsGroupPositionPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CPartClientInsGroupPositionOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pPartClientInsGroupPosition	Ҫ���жϵĿͻ���Լ��ֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return m_p1->isValid(pPartClientInsGroupPosition) || m_p2->isValid(pPartClientInsGroupPosition);
	}
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionNotPredict�Ƕ�һ���ͻ���Լ��ֱֲ�ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionNotPredict : public CPartClientInsGroupPositionPredict
{
private:
	CPartClientInsGroupPositionPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CPartClientInsGroupPositionNotPredict(CPartClientInsGroupPositionPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CPartClientInsGroupPositionNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pPartClientInsGroupPosition	Ҫ���жϵĿͻ���Լ��ֱֲ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return !m_predict->isValid(pPartClientInsGroupPosition);
	}
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionFilter��һ�������еĿͻ���Լ��ֱֲ�ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionFilter: public CPartClientInsGroupPositionIterator
{
private:
	CPartClientInsGroupPositionIterator *m_baseIterator;
	CPartClientInsGroupPositionPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CPartClientInsGroupPositionFilter(CPartClientInsGroupPositionIterator *pBaseIterator, CPartClientInsGroupPositionPredict *pPredict, bool continueResult=false)
		:CPartClientInsGroupPositionIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CPartClientInsGroupPositionFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CPartClientInsGroupPosition
	///@return	��һ����������CPartClientInsGroupPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CPartClientInsGroupPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pPartClientInsGroupPosition ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteablePartClientInsGroupPosition * pPartClientInsGroupPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionLinkIterator�����������ͻ���Լ��ֱֲ�ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionLinkIterator: public CPartClientInsGroupPositionIterator
{
private:
	CPartClientInsGroupPositionIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CPartClientInsGroupPositionLinkIterator(CPartClientInsGroupPositionIterator *pBaseIterator1,CPartClientInsGroupPositionIterator *pBaseIterator2)
		:CPartClientInsGroupPositionIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CPartClientInsGroupPositionLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CPartClientInsGroupPosition
	///@return	��һ����������CPartClientInsGroupPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CPartClientInsGroupPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pPartClientInsGroupPosition ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteablePartClientInsGroupPosition * pPartClientInsGroupPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeSingleIterator�����෵��һ�����ױ�����ϱ�֤�����͵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeSingleIterator: public CClientMarginCombTypeIterator
{
private:
	CClientMarginCombType *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CClientMarginCombTypeSingleIterator(CClientMarginCombTypeFactory *pFactory,CClientMarginCombType *pResult)
		:CClientMarginCombTypeIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CClientMarginCombTypeSingleIterator(void)
	{
	}

	///Ѱ����һ������������CClientMarginCombType
	///@return	��һ����������CClientMarginCombType������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CClientMarginCombType *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pClientMarginCombType ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableClientMarginCombType * pClientMarginCombType,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypePredict���ж�һ�����ױ�����ϱ�֤�������Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypePredict
{
public:
	virtual ~CClientMarginCombTypePredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pClientMarginCombType	Ҫ���жϵĽ��ױ�����ϱ�֤������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientMarginCombType *pClientMarginCombType)=0;
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeAndPredict�Ƕ��������ױ�����ϱ�֤������ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeAndPredict : public CClientMarginCombTypePredict
{
private:
	CClientMarginCombTypePredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CClientMarginCombTypeAndPredict(CClientMarginCombTypePredict *p1, CClientMarginCombTypePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CClientMarginCombTypeAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pClientMarginCombType	Ҫ���жϵĽ��ױ�����ϱ�֤������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientMarginCombType *pClientMarginCombType)
	{
		return m_p1->isValid(pClientMarginCombType) && m_p2->isValid(pClientMarginCombType);
	}
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeOrPredict�Ƕ��������ױ�����ϱ�֤������ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeOrPredict : public CClientMarginCombTypePredict
{
private:
	CClientMarginCombTypePredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CClientMarginCombTypeOrPredict(CClientMarginCombTypePredict *p1, CClientMarginCombTypePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CClientMarginCombTypeOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pClientMarginCombType	Ҫ���жϵĽ��ױ�����ϱ�֤������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientMarginCombType *pClientMarginCombType)
	{
		return m_p1->isValid(pClientMarginCombType) || m_p2->isValid(pClientMarginCombType);
	}
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeNotPredict�Ƕ�һ�����ױ�����ϱ�֤������ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeNotPredict : public CClientMarginCombTypePredict
{
private:
	CClientMarginCombTypePredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CClientMarginCombTypeNotPredict(CClientMarginCombTypePredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CClientMarginCombTypeNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pClientMarginCombType	Ҫ���жϵĽ��ױ�����ϱ�֤������
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CClientMarginCombType *pClientMarginCombType)
	{
		return !m_predict->isValid(pClientMarginCombType);
	}
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeFilter��һ�������еĽ��ױ�����ϱ�֤������ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeFilter: public CClientMarginCombTypeIterator
{
private:
	CClientMarginCombTypeIterator *m_baseIterator;
	CClientMarginCombTypePredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CClientMarginCombTypeFilter(CClientMarginCombTypeIterator *pBaseIterator, CClientMarginCombTypePredict *pPredict, bool continueResult=false)
		:CClientMarginCombTypeIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CClientMarginCombTypeFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CClientMarginCombType
	///@return	��һ����������CClientMarginCombType������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CClientMarginCombType *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pClientMarginCombType ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableClientMarginCombType * pClientMarginCombType,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeLinkIterator�������������ױ�����ϱ�֤������ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeLinkIterator: public CClientMarginCombTypeIterator
{
private:
	CClientMarginCombTypeIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CClientMarginCombTypeLinkIterator(CClientMarginCombTypeIterator *pBaseIterator1,CClientMarginCombTypeIterator *pBaseIterator2)
		:CClientMarginCombTypeIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CClientMarginCombTypeLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CClientMarginCombType
	///@return	��һ����������CClientMarginCombType������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CClientMarginCombType *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pClientMarginCombType ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableClientMarginCombType * pClientMarginCombType,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupSingleIterator�����෵��һ����Լ�ͺ�Լ���ϵ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupSingleIterator: public CInstrumentGroupIterator
{
private:
	CInstrumentGroup *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CInstrumentGroupSingleIterator(CInstrumentGroupFactory *pFactory,CInstrumentGroup *pResult)
		:CInstrumentGroupIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CInstrumentGroupSingleIterator(void)
	{
	}

	///Ѱ����һ������������CInstrumentGroup
	///@return	��һ����������CInstrumentGroup������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInstrumentGroup *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInstrumentGroup ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInstrumentGroup * pInstrumentGroup,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupPredict���ж�һ����Լ�ͺ�Լ���ϵ�Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupPredict
{
public:
	virtual ~CInstrumentGroupPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pInstrumentGroup	Ҫ���жϵĺ�Լ�ͺ�Լ���ϵ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInstrumentGroup *pInstrumentGroup)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupAndPredict�Ƕ�������Լ�ͺ�Լ���ϵν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupAndPredict : public CInstrumentGroupPredict
{
private:
	CInstrumentGroupPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInstrumentGroupAndPredict(CInstrumentGroupPredict *p1, CInstrumentGroupPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInstrumentGroupAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInstrumentGroup	Ҫ���жϵĺ�Լ�ͺ�Լ���ϵ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInstrumentGroup *pInstrumentGroup)
	{
		return m_p1->isValid(pInstrumentGroup) && m_p2->isValid(pInstrumentGroup);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupOrPredict�Ƕ�������Լ�ͺ�Լ���ϵν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupOrPredict : public CInstrumentGroupPredict
{
private:
	CInstrumentGroupPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInstrumentGroupOrPredict(CInstrumentGroupPredict *p1, CInstrumentGroupPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInstrumentGroupOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInstrumentGroup	Ҫ���жϵĺ�Լ�ͺ�Լ���ϵ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInstrumentGroup *pInstrumentGroup)
	{
		return m_p1->isValid(pInstrumentGroup) || m_p2->isValid(pInstrumentGroup);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupNotPredict�Ƕ�һ����Լ�ͺ�Լ���ϵν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupNotPredict : public CInstrumentGroupPredict
{
private:
	CInstrumentGroupPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CInstrumentGroupNotPredict(CInstrumentGroupPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CInstrumentGroupNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInstrumentGroup	Ҫ���жϵĺ�Լ�ͺ�Լ���ϵ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInstrumentGroup *pInstrumentGroup)
	{
		return !m_predict->isValid(pInstrumentGroup);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupFilter��һ�������еĺ�Լ�ͺ�Լ���ϵö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupFilter: public CInstrumentGroupIterator
{
private:
	CInstrumentGroupIterator *m_baseIterator;
	CInstrumentGroupPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CInstrumentGroupFilter(CInstrumentGroupIterator *pBaseIterator, CInstrumentGroupPredict *pPredict, bool continueResult=false)
		:CInstrumentGroupIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CInstrumentGroupFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CInstrumentGroup
	///@return	��һ����������CInstrumentGroup������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInstrumentGroup *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInstrumentGroup ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInstrumentGroup * pInstrumentGroup,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupLinkIterator������������Լ�ͺ�Լ���ϵö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupLinkIterator: public CInstrumentGroupIterator
{
private:
	CInstrumentGroupIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CInstrumentGroupLinkIterator(CInstrumentGroupIterator *pBaseIterator1,CInstrumentGroupIterator *pBaseIterator2)
		:CInstrumentGroupIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CInstrumentGroupLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CInstrumentGroup
	///@return	��һ����������CInstrumentGroup������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInstrumentGroup *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInstrumentGroup ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInstrumentGroup * pInstrumentGroup,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateSingleIterator�����෵��һ���������ӷ��ʱ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateSingleIterator: public CSGEDeferRateIterator
{
private:
	CSGEDeferRate *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CSGEDeferRateSingleIterator(CSGEDeferRateFactory *pFactory,CSGEDeferRate *pResult)
		:CSGEDeferRateIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CSGEDeferRateSingleIterator(void)
	{
	}

	///Ѱ����һ������������CSGEDeferRate
	///@return	��һ����������CSGEDeferRate������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSGEDeferRate *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pSGEDeferRate ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSGEDeferRate * pSGEDeferRate,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRatePredict���ж�һ���������ӷ��ʱ��Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRatePredict
{
public:
	virtual ~CSGEDeferRatePredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pSGEDeferRate	Ҫ���жϵĽ������ӷ��ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSGEDeferRate *pSGEDeferRate)=0;
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateAndPredict�Ƕ������������ӷ��ʱ�ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateAndPredict : public CSGEDeferRatePredict
{
private:
	CSGEDeferRatePredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CSGEDeferRateAndPredict(CSGEDeferRatePredict *p1, CSGEDeferRatePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CSGEDeferRateAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pSGEDeferRate	Ҫ���жϵĽ������ӷ��ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSGEDeferRate *pSGEDeferRate)
	{
		return m_p1->isValid(pSGEDeferRate) && m_p2->isValid(pSGEDeferRate);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateOrPredict�Ƕ������������ӷ��ʱ�ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateOrPredict : public CSGEDeferRatePredict
{
private:
	CSGEDeferRatePredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CSGEDeferRateOrPredict(CSGEDeferRatePredict *p1, CSGEDeferRatePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CSGEDeferRateOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pSGEDeferRate	Ҫ���жϵĽ������ӷ��ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSGEDeferRate *pSGEDeferRate)
	{
		return m_p1->isValid(pSGEDeferRate) || m_p2->isValid(pSGEDeferRate);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateNotPredict�Ƕ�һ���������ӷ��ʱ�ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateNotPredict : public CSGEDeferRatePredict
{
private:
	CSGEDeferRatePredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CSGEDeferRateNotPredict(CSGEDeferRatePredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CSGEDeferRateNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pSGEDeferRate	Ҫ���жϵĽ������ӷ��ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSGEDeferRate *pSGEDeferRate)
	{
		return !m_predict->isValid(pSGEDeferRate);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateFilter��һ�������еĽ������ӷ��ʱ�ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateFilter: public CSGEDeferRateIterator
{
private:
	CSGEDeferRateIterator *m_baseIterator;
	CSGEDeferRatePredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CSGEDeferRateFilter(CSGEDeferRateIterator *pBaseIterator, CSGEDeferRatePredict *pPredict, bool continueResult=false)
		:CSGEDeferRateIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CSGEDeferRateFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CSGEDeferRate
	///@return	��һ����������CSGEDeferRate������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSGEDeferRate *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pSGEDeferRate ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSGEDeferRate * pSGEDeferRate,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateLinkIterator�����������������ӷ��ʱ�ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateLinkIterator: public CSGEDeferRateIterator
{
private:
	CSGEDeferRateIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CSGEDeferRateLinkIterator(CSGEDeferRateIterator *pBaseIterator1,CSGEDeferRateIterator *pBaseIterator2)
		:CSGEDeferRateIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CSGEDeferRateLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CSGEDeferRate
	///@return	��һ����������CSGEDeferRate������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSGEDeferRate *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pSGEDeferRate ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSGEDeferRate * pSGEDeferRate,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightSingleIterator�����෵��һ��Ͷ���߽���Ȩ�ޱ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightSingleIterator: public CInvestorTradingRightIterator
{
private:
	CInvestorTradingRight *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CInvestorTradingRightSingleIterator(CInvestorTradingRightFactory *pFactory,CInvestorTradingRight *pResult)
		:CInvestorTradingRightIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CInvestorTradingRightSingleIterator(void)
	{
	}

	///Ѱ����һ������������CInvestorTradingRight
	///@return	��һ����������CInvestorTradingRight������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorTradingRight *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorTradingRight ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorTradingRight * pInvestorTradingRight,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightPredict���ж�һ��Ͷ���߽���Ȩ�ޱ��Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightPredict
{
public:
	virtual ~CInvestorTradingRightPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorTradingRight	Ҫ���жϵ�Ͷ���߽���Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorTradingRight *pInvestorTradingRight)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightAndPredict�Ƕ�����Ͷ���߽���Ȩ�ޱ�ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightAndPredict : public CInvestorTradingRightPredict
{
private:
	CInvestorTradingRightPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInvestorTradingRightAndPredict(CInvestorTradingRightPredict *p1, CInvestorTradingRightPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInvestorTradingRightAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorTradingRight	Ҫ���жϵ�Ͷ���߽���Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorTradingRight *pInvestorTradingRight)
	{
		return m_p1->isValid(pInvestorTradingRight) && m_p2->isValid(pInvestorTradingRight);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightOrPredict�Ƕ�����Ͷ���߽���Ȩ�ޱ�ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightOrPredict : public CInvestorTradingRightPredict
{
private:
	CInvestorTradingRightPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInvestorTradingRightOrPredict(CInvestorTradingRightPredict *p1, CInvestorTradingRightPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInvestorTradingRightOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorTradingRight	Ҫ���жϵ�Ͷ���߽���Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorTradingRight *pInvestorTradingRight)
	{
		return m_p1->isValid(pInvestorTradingRight) || m_p2->isValid(pInvestorTradingRight);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightNotPredict�Ƕ�һ��Ͷ���߽���Ȩ�ޱ�ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightNotPredict : public CInvestorTradingRightPredict
{
private:
	CInvestorTradingRightPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CInvestorTradingRightNotPredict(CInvestorTradingRightPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CInvestorTradingRightNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorTradingRight	Ҫ���жϵ�Ͷ���߽���Ȩ�ޱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorTradingRight *pInvestorTradingRight)
	{
		return !m_predict->isValid(pInvestorTradingRight);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightFilter��һ�������е�Ͷ���߽���Ȩ�ޱ�ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightFilter: public CInvestorTradingRightIterator
{
private:
	CInvestorTradingRightIterator *m_baseIterator;
	CInvestorTradingRightPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CInvestorTradingRightFilter(CInvestorTradingRightIterator *pBaseIterator, CInvestorTradingRightPredict *pPredict, bool continueResult=false)
		:CInvestorTradingRightIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CInvestorTradingRightFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CInvestorTradingRight
	///@return	��һ����������CInvestorTradingRight������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorTradingRight *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorTradingRight ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorTradingRight * pInvestorTradingRight,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightLinkIterator����������Ͷ���߽���Ȩ�ޱ�ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightLinkIterator: public CInvestorTradingRightIterator
{
private:
	CInvestorTradingRightIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CInvestorTradingRightLinkIterator(CInvestorTradingRightIterator *pBaseIterator1,CInvestorTradingRightIterator *pBaseIterator2)
		:CInvestorTradingRightIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CInvestorTradingRightLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CInvestorTradingRight
	///@return	��һ����������CInvestorTradingRight������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorTradingRight *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorTradingRight ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorTradingRight * pInvestorTradingRight,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CUserIPSingleIterator�����෵��һ������ԱIP��ַ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPSingleIterator: public CUserIPIterator
{
private:
	CUserIP *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CUserIPSingleIterator(CUserIPFactory *pFactory,CUserIP *pResult)
		:CUserIPIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CUserIPSingleIterator(void)
	{
	}

	///Ѱ����һ������������CUserIP
	///@return	��һ����������CUserIP������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserIP *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUserIP ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserIP * pUserIP,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserIPPredict���ж�һ������ԱIP��ַ�Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPPredict
{
public:
	virtual ~CUserIPPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pUserIP	Ҫ���жϵĽ���ԱIP��ַ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserIP *pUserIP)=0;
};

/////////////////////////////////////////////////////////////////////////
///CUserIPAndPredict�Ƕ���������ԱIP��ַν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPAndPredict : public CUserIPPredict
{
private:
	CUserIPPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CUserIPAndPredict(CUserIPPredict *p1, CUserIPPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CUserIPAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pUserIP	Ҫ���жϵĽ���ԱIP��ַ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserIP *pUserIP)
	{
		return m_p1->isValid(pUserIP) && m_p2->isValid(pUserIP);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserIPOrPredict�Ƕ���������ԱIP��ַν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPOrPredict : public CUserIPPredict
{
private:
	CUserIPPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CUserIPOrPredict(CUserIPPredict *p1, CUserIPPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CUserIPOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pUserIP	Ҫ���жϵĽ���ԱIP��ַ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserIP *pUserIP)
	{
		return m_p1->isValid(pUserIP) || m_p2->isValid(pUserIP);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserIPNotPredict�Ƕ�һ������ԱIP��ַν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPNotPredict : public CUserIPPredict
{
private:
	CUserIPPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CUserIPNotPredict(CUserIPPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CUserIPNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pUserIP	Ҫ���жϵĽ���ԱIP��ַ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CUserIP *pUserIP)
	{
		return !m_predict->isValid(pUserIP);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserIPFilter��һ�������еĽ���ԱIP��ַö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPFilter: public CUserIPIterator
{
private:
	CUserIPIterator *m_baseIterator;
	CUserIPPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CUserIPFilter(CUserIPIterator *pBaseIterator, CUserIPPredict *pPredict, bool continueResult=false)
		:CUserIPIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CUserIPFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CUserIP
	///@return	��һ����������CUserIP������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserIP *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUserIP ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserIP * pUserIP,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserIPLinkIterator��������������ԱIP��ַö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPLinkIterator: public CUserIPIterator
{
private:
	CUserIPIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CUserIPLinkIterator(CUserIPIterator *pBaseIterator1,CUserIPIterator *pBaseIterator2)
		:CUserIPIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CUserIPLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CUserIP
	///@return	��һ����������CUserIP������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserIP *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUserIP ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserIP * pUserIP,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeSingleIterator�����෵��һ���ͻ���Ȩ�������ʱ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeSingleIterator: public CInvestorOptionFeeIterator
{
private:
	CInvestorOptionFee *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CInvestorOptionFeeSingleIterator(CInvestorOptionFeeFactory *pFactory,CInvestorOptionFee *pResult)
		:CInvestorOptionFeeIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CInvestorOptionFeeSingleIterator(void)
	{
	}

	///Ѱ����һ������������CInvestorOptionFee
	///@return	��һ����������CInvestorOptionFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorOptionFee *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorOptionFee ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorOptionFee * pInvestorOptionFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeePredict���ж�һ���ͻ���Ȩ�������ʱ��Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeePredict
{
public:
	virtual ~CInvestorOptionFeePredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorOptionFee	Ҫ���жϵĿͻ���Ȩ�������ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorOptionFee *pInvestorOptionFee)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeAndPredict�Ƕ������ͻ���Ȩ�������ʱ�ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeAndPredict : public CInvestorOptionFeePredict
{
private:
	CInvestorOptionFeePredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInvestorOptionFeeAndPredict(CInvestorOptionFeePredict *p1, CInvestorOptionFeePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInvestorOptionFeeAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorOptionFee	Ҫ���жϵĿͻ���Ȩ�������ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorOptionFee *pInvestorOptionFee)
	{
		return m_p1->isValid(pInvestorOptionFee) && m_p2->isValid(pInvestorOptionFee);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeOrPredict�Ƕ������ͻ���Ȩ�������ʱ�ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeOrPredict : public CInvestorOptionFeePredict
{
private:
	CInvestorOptionFeePredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CInvestorOptionFeeOrPredict(CInvestorOptionFeePredict *p1, CInvestorOptionFeePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CInvestorOptionFeeOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorOptionFee	Ҫ���жϵĿͻ���Ȩ�������ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorOptionFee *pInvestorOptionFee)
	{
		return m_p1->isValid(pInvestorOptionFee) || m_p2->isValid(pInvestorOptionFee);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeNotPredict�Ƕ�һ���ͻ���Ȩ�������ʱ�ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeNotPredict : public CInvestorOptionFeePredict
{
private:
	CInvestorOptionFeePredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CInvestorOptionFeeNotPredict(CInvestorOptionFeePredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CInvestorOptionFeeNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pInvestorOptionFee	Ҫ���жϵĿͻ���Ȩ�������ʱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CInvestorOptionFee *pInvestorOptionFee)
	{
		return !m_predict->isValid(pInvestorOptionFee);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeFilter��һ�������еĿͻ���Ȩ�������ʱ�ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeFilter: public CInvestorOptionFeeIterator
{
private:
	CInvestorOptionFeeIterator *m_baseIterator;
	CInvestorOptionFeePredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CInvestorOptionFeeFilter(CInvestorOptionFeeIterator *pBaseIterator, CInvestorOptionFeePredict *pPredict, bool continueResult=false)
		:CInvestorOptionFeeIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CInvestorOptionFeeFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CInvestorOptionFee
	///@return	��һ����������CInvestorOptionFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorOptionFee *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorOptionFee ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorOptionFee * pInvestorOptionFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeLinkIterator�����������ͻ���Ȩ�������ʱ�ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeLinkIterator: public CInvestorOptionFeeIterator
{
private:
	CInvestorOptionFeeIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CInvestorOptionFeeLinkIterator(CInvestorOptionFeeIterator *pBaseIterator1,CInvestorOptionFeeIterator *pBaseIterator2)
		:CInvestorOptionFeeIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CInvestorOptionFeeLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CInvestorOptionFee
	///@return	��һ����������CInvestorOptionFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorOptionFee *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorOptionFee ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorOptionFee * pInvestorOptionFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CMarketDataSingleIterator�����෵��һ��ʵʱ������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataSingleIterator: public CMarketDataIterator
{
private:
	CMarketData *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CMarketDataSingleIterator(CMarketDataFactory *pFactory,CMarketData *pResult)
		:CMarketDataIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CMarketDataSingleIterator(void)
	{
	}

	///Ѱ����һ������������CMarketData
	///@return	��һ����������CMarketData������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CMarketData *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pMarketData ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableMarketData * pMarketData,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataPredict���ж�һ��ʵʱ������Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataPredict
{
public:
	virtual ~CMarketDataPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pMarketData	Ҫ���жϵ�ʵʱ�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CMarketData *pMarketData)=0;
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataAndPredict�Ƕ�����ʵʱ�����ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataAndPredict : public CMarketDataPredict
{
private:
	CMarketDataPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CMarketDataAndPredict(CMarketDataPredict *p1, CMarketDataPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CMarketDataAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pMarketData	Ҫ���жϵ�ʵʱ�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CMarketData *pMarketData)
	{
		return m_p1->isValid(pMarketData) && m_p2->isValid(pMarketData);
	}
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataOrPredict�Ƕ�����ʵʱ�����ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataOrPredict : public CMarketDataPredict
{
private:
	CMarketDataPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CMarketDataOrPredict(CMarketDataPredict *p1, CMarketDataPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CMarketDataOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pMarketData	Ҫ���жϵ�ʵʱ�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CMarketData *pMarketData)
	{
		return m_p1->isValid(pMarketData) || m_p2->isValid(pMarketData);
	}
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataNotPredict�Ƕ�һ��ʵʱ�����ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataNotPredict : public CMarketDataPredict
{
private:
	CMarketDataPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CMarketDataNotPredict(CMarketDataPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CMarketDataNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pMarketData	Ҫ���жϵ�ʵʱ�����
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CMarketData *pMarketData)
	{
		return !m_predict->isValid(pMarketData);
	}
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataFilter��һ�������е�ʵʱ�����ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataFilter: public CMarketDataIterator
{
private:
	CMarketDataIterator *m_baseIterator;
	CMarketDataPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CMarketDataFilter(CMarketDataIterator *pBaseIterator, CMarketDataPredict *pPredict, bool continueResult=false)
		:CMarketDataIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CMarketDataFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CMarketData
	///@return	��һ����������CMarketData������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CMarketData *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pMarketData ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableMarketData * pMarketData,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataLinkIterator����������ʵʱ�����ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataLinkIterator: public CMarketDataIterator
{
private:
	CMarketDataIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CMarketDataLinkIterator(CMarketDataIterator *pBaseIterator1,CMarketDataIterator *pBaseIterator2)
		:CMarketDataIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CMarketDataLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CMarketData
	///@return	��һ����������CMarketData������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CMarketData *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pMarketData ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableMarketData * pMarketData,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///COrderDelaySingleIterator�����෵��һ��ί���ӳٱ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelaySingleIterator: public COrderDelayIterator
{
private:
	COrderDelay *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	COrderDelaySingleIterator(COrderDelayFactory *pFactory,COrderDelay *pResult)
		:COrderDelayIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~COrderDelaySingleIterator(void)
	{
	}

	///Ѱ����һ������������COrderDelay
	///@return	��һ����������COrderDelay������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrderDelay *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrderDelay ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrderDelay * pOrderDelay,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayPredict���ж�һ��ί���ӳٱ��Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayPredict
{
public:
	virtual ~COrderDelayPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pOrderDelay	Ҫ���жϵ�ί���ӳٱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderDelay *pOrderDelay)=0;
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayAndPredict�Ƕ�����ί���ӳٱ�ν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayAndPredict : public COrderDelayPredict
{
private:
	COrderDelayPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	COrderDelayAndPredict(COrderDelayPredict *p1, COrderDelayPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~COrderDelayAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pOrderDelay	Ҫ���жϵ�ί���ӳٱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderDelay *pOrderDelay)
	{
		return m_p1->isValid(pOrderDelay) && m_p2->isValid(pOrderDelay);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayOrPredict�Ƕ�����ί���ӳٱ�ν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayOrPredict : public COrderDelayPredict
{
private:
	COrderDelayPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	COrderDelayOrPredict(COrderDelayPredict *p1, COrderDelayPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~COrderDelayOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pOrderDelay	Ҫ���жϵ�ί���ӳٱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderDelay *pOrderDelay)
	{
		return m_p1->isValid(pOrderDelay) || m_p2->isValid(pOrderDelay);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayNotPredict�Ƕ�һ��ί���ӳٱ�ν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayNotPredict : public COrderDelayPredict
{
private:
	COrderDelayPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	COrderDelayNotPredict(COrderDelayPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~COrderDelayNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pOrderDelay	Ҫ���жϵ�ί���ӳٱ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(COrderDelay *pOrderDelay)
	{
		return !m_predict->isValid(pOrderDelay);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayFilter��һ�������е�ί���ӳٱ�ö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayFilter: public COrderDelayIterator
{
private:
	COrderDelayIterator *m_baseIterator;
	COrderDelayPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	COrderDelayFilter(COrderDelayIterator *pBaseIterator, COrderDelayPredict *pPredict, bool continueResult=false)
		:COrderDelayIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~COrderDelayFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������COrderDelay
	///@return	��һ����������COrderDelay������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrderDelay *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrderDelay ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrderDelay * pOrderDelay,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayLinkIterator����������ί���ӳٱ�ö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayLinkIterator: public COrderDelayIterator
{
private:
	COrderDelayIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	COrderDelayLinkIterator(COrderDelayIterator *pBaseIterator1,COrderDelayIterator *pBaseIterator2)
		:COrderDelayIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~COrderDelayLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������COrderDelay
	///@return	��һ����������COrderDelay������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrderDelay *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrderDelay ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrderDelay * pOrderDelay,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CSystemInfoSingleIterator�����෵��һ��QDPϵͳ��Ϣ��ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoSingleIterator: public CSystemInfoIterator
{
private:
	CSystemInfo *m_pResult;
	bool m_finished;
public:
	///���췽��
	///@param	pFactory	Ҫʹ�õĶ��󹤳�
	///@param	pResult	Ҫ���صĵ������
	CSystemInfoSingleIterator(CSystemInfoFactory *pFactory,CSystemInfo *pResult)
		:CSystemInfoIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///���췽��
	virtual ~CSystemInfoSingleIterator(void)
	{
	}

	///Ѱ����һ������������CSystemInfo
	///@return	��һ����������CSystemInfo������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSystemInfo *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pSystemInfo ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSystemInfo * pSystemInfo,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoPredict���ж�һ��QDPϵͳ��Ϣ�Ƿ����������ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoPredict
{
public:
	virtual ~CSystemInfoPredict(){};

	///�ж��Ƿ�Ϸ�
	///@param	pSystemInfo	Ҫ���жϵ�QDPϵͳ��Ϣ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSystemInfo *pSystemInfo)=0;
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoAndPredict�Ƕ�����QDPϵͳ��Ϣν�ʵ���ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoAndPredict : public CSystemInfoPredict
{
private:
	CSystemInfoPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CSystemInfoAndPredict(CSystemInfoPredict *p1, CSystemInfoPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CSystemInfoAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pSystemInfo	Ҫ���жϵ�QDPϵͳ��Ϣ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSystemInfo *pSystemInfo)
	{
		return m_p1->isValid(pSystemInfo) && m_p2->isValid(pSystemInfo);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoOrPredict�Ƕ�����QDPϵͳ��Ϣν�ʵĻ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoOrPredict : public CSystemInfoPredict
{
private:
	CSystemInfoPredict *m_p1,*m_p2;
public:
	///���췽��
	///@param	p1	��һ��ν��
	///@param	p2	�ڶ���ν��
	CSystemInfoOrPredict(CSystemInfoPredict *p1, CSystemInfoPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///��������
	virtual ~CSystemInfoOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pSystemInfo	Ҫ���жϵ�QDPϵͳ��Ϣ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSystemInfo *pSystemInfo)
	{
		return m_p1->isValid(pSystemInfo) || m_p2->isValid(pSystemInfo);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoNotPredict�Ƕ�һ��QDPϵͳ��Ϣν�ʵķ�ν��
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoNotPredict : public CSystemInfoPredict
{
private:
	CSystemInfoPredict *m_predict;
public:
	///���췽��
	///@param	predict	����ν��
	CSystemInfoNotPredict(CSystemInfoPredict *predict)
	{
		m_predict=predict;
	}
	
	///��������
	virtual ~CSystemInfoNotPredict(void)
	{
		delete m_predict;
	}

	///�ж��Ƿ�Ϸ�
	///@param	pSystemInfo	Ҫ���жϵ�QDPϵͳ��Ϣ
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(CSystemInfo *pSystemInfo)
	{
		return !m_predict->isValid(pSystemInfo);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoFilter��һ�������е�QDPϵͳ��Ϣö�������й��˵�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoFilter: public CSystemInfoIterator
{
private:
	CSystemInfoIterator *m_baseIterator;
	CSystemInfoPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///���캯��
	///@param	pBaseIterator	������ö����
	///@param	pPredict	�ж��Ƿ�Ϸ���ν��
	///@param	continueResult	true��ʾ�������������ǻ���ö�������������������false��ʾ�������
	CSystemInfoFilter(CSystemInfoIterator *pBaseIterator, CSystemInfoPredict *pPredict, bool continueResult=false)
		:CSystemInfoIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///��������
	virtual ~CSystemInfoFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///Ѱ����һ������������CSystemInfo
	///@return	��һ����������CSystemInfo������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSystemInfo *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pSystemInfo ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSystemInfo * pSystemInfo,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoLinkIterator����������QDPϵͳ��Ϣö������ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoLinkIterator: public CSystemInfoIterator
{
private:
	CSystemInfoIterator *m_baseIterator[2];
	int m_id;
public:
	///���캯��
	///@param	pBaseIterator1	������ö����1
	///@param	pBaseIterator2	������ö����2
	CSystemInfoLinkIterator(CSystemInfoIterator *pBaseIterator1,CSystemInfoIterator *pBaseIterator2)
		:CSystemInfoIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///��������
	virtual ~CSystemInfoLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///Ѱ����һ������������CSystemInfo
	///@return	��һ����������CSystemInfo������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSystemInfo *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pSystemInfo ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSystemInfo * pSystemInfo,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


#endif
