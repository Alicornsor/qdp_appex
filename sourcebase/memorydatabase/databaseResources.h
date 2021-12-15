/////////////////////////////////////////////////////////////////////////
///@system ִ������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file databaseResources.h
///@brief�����������ڴ�������Դ�����Է�����������
///@history 
///20060127	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef DATABASERESOURCES_H
#define DATABASERESOURCES_H

#include "databaseData.h"
#include "MemoryStack.h"

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusResource��һ��˵����CDataSyncStatusFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusResource : public CDatabaseResource
{
public:
	///���췽��
	CDataSyncStatusResource(void);
	virtual ~CDataSyncStatusResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CDataSyncStatusFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CDataSyncStatusFactory *pFactory, CDataSyncStatus *pObject, CWriteableDataSyncStatus *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CDataSyncStatusFactory
	///@return	��CDataSyncStatusFactory
	CDataSyncStatusFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CDataSyncStatusFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CDataSyncStatusResource *alloc(int type, CDataSyncStatusFactory *pFactory, CDataSyncStatus *pObject, CWriteableDataSyncStatus *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CDataSyncStatusFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableDataSyncStatus writeableObject;
	
	static CMemoryStack<CDataSyncStatusResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusResource��һ��˵����CSystemStatusFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusResource : public CDatabaseResource
{
public:
	///���췽��
	CSystemStatusResource(void);
	virtual ~CSystemStatusResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CSystemStatusFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CSystemStatusFactory *pFactory, CSystemStatus *pObject, CWriteableSystemStatus *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CSystemStatusFactory
	///@return	��CSystemStatusFactory
	CSystemStatusFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CSystemStatusFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CSystemStatusResource *alloc(int type, CSystemStatusFactory *pFactory, CSystemStatus *pObject, CWriteableSystemStatus *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CSystemStatusFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableSystemStatus writeableObject;
	
	static CMemoryStack<CSystemStatusResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///COrderActionResource��һ��˵����COrderActionFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionResource : public CDatabaseResource
{
public:
	///���췽��
	COrderActionResource(void);
	virtual ~COrderActionResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�COrderActionFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, COrderActionFactory *pFactory, COrderAction *pObject, CWriteableOrderAction *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�COrderActionFactory
	///@return	��COrderActionFactory
	COrderActionFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�COrderActionFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static COrderActionResource *alloc(int type, COrderActionFactory *pFactory, COrderAction *pObject, CWriteableOrderAction *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	COrderActionFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableOrderAction writeableObject;
	
	static CMemoryStack<COrderActionResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///COrderResource��һ��˵����COrderFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderResource : public CDatabaseResource
{
public:
	///���췽��
	COrderResource(void);
	virtual ~COrderResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�COrderFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, COrderFactory *pFactory, COrder *pObject, CWriteableOrder *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�COrderFactory
	///@return	��COrderFactory
	COrderFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�COrderFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static COrderResource *alloc(int type, COrderFactory *pFactory, COrder *pObject, CWriteableOrder *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	COrderFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableOrder writeableObject;
	
	static CMemoryStack<COrderResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CTradeResource��һ��˵����CTradeFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeResource : public CDatabaseResource
{
public:
	///���췽��
	CTradeResource(void);
	virtual ~CTradeResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CTradeFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CTradeFactory *pFactory, CTrade *pObject, CWriteableTrade *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CTradeFactory
	///@return	��CTradeFactory
	CTradeFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CTradeFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CTradeResource *alloc(int type, CTradeFactory *pFactory, CTrade *pObject, CWriteableTrade *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CTradeFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableTrade writeableObject;
	
	static CMemoryStack<CTradeResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderResource��һ��˵����CPreOrderFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderResource : public CDatabaseResource
{
public:
	///���췽��
	CPreOrderResource(void);
	virtual ~CPreOrderResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CPreOrderFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CPreOrderFactory *pFactory, CPreOrder *pObject, CWriteablePreOrder *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CPreOrderFactory
	///@return	��CPreOrderFactory
	CPreOrderFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CPreOrderFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CPreOrderResource *alloc(int type, CPreOrderFactory *pFactory, CPreOrder *pObject, CWriteablePreOrder *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CPreOrderFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteablePreOrder writeableObject;
	
	static CMemoryStack<CPreOrderResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderResource��һ��˵����CIndexPreOrderFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderResource : public CDatabaseResource
{
public:
	///���췽��
	CIndexPreOrderResource(void);
	virtual ~CIndexPreOrderResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CIndexPreOrderFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CIndexPreOrderFactory *pFactory, CIndexPreOrder *pObject, CWriteableIndexPreOrder *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CIndexPreOrderFactory
	///@return	��CIndexPreOrderFactory
	CIndexPreOrderFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CIndexPreOrderFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CIndexPreOrderResource *alloc(int type, CIndexPreOrderFactory *pFactory, CIndexPreOrder *pObject, CWriteableIndexPreOrder *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CIndexPreOrderFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableIndexPreOrder writeableObject;
	
	static CMemoryStack<CIndexPreOrderResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionResource��һ��˵����CInvestorPositionFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionResource : public CDatabaseResource
{
public:
	///���췽��
	CInvestorPositionResource(void);
	virtual ~CInvestorPositionResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInvestorPositionFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CInvestorPositionFactory *pFactory, CInvestorPosition *pObject, CWriteableInvestorPosition *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CInvestorPositionFactory
	///@return	��CInvestorPositionFactory
	CInvestorPositionFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInvestorPositionFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CInvestorPositionResource *alloc(int type, CInvestorPositionFactory *pFactory, CInvestorPosition *pObject, CWriteableInvestorPosition *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CInvestorPositionFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableInvestorPosition writeableObject;
	
	static CMemoryStack<CInvestorPositionResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountResource��һ��˵����CInvestorAccountFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountResource : public CDatabaseResource
{
public:
	///���췽��
	CInvestorAccountResource(void);
	virtual ~CInvestorAccountResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInvestorAccountFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CInvestorAccountFactory *pFactory, CInvestorAccount *pObject, CWriteableInvestorAccount *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CInvestorAccountFactory
	///@return	��CInvestorAccountFactory
	CInvestorAccountFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInvestorAccountFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CInvestorAccountResource *alloc(int type, CInvestorAccountFactory *pFactory, CInvestorAccount *pObject, CWriteableInvestorAccount *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CInvestorAccountFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableInvestorAccount writeableObject;
	
	static CMemoryStack<CInvestorAccountResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositResource��һ��˵����CInvestorAccountDepositFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositResource : public CDatabaseResource
{
public:
	///���췽��
	CInvestorAccountDepositResource(void);
	virtual ~CInvestorAccountDepositResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInvestorAccountDepositFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CInvestorAccountDepositFactory *pFactory, CInvestorAccountDeposit *pObject, CWriteableInvestorAccountDeposit *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CInvestorAccountDepositFactory
	///@return	��CInvestorAccountDepositFactory
	CInvestorAccountDepositFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInvestorAccountDepositFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CInvestorAccountDepositResource *alloc(int type, CInvestorAccountDepositFactory *pFactory, CInvestorAccountDeposit *pObject, CWriteableInvestorAccountDeposit *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CInvestorAccountDepositFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableInvestorAccountDeposit writeableObject;
	
	static CMemoryStack<CInvestorAccountDepositResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CExchangeResource��һ��˵����CExchangeFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeResource : public CDatabaseResource
{
public:
	///���췽��
	CExchangeResource(void);
	virtual ~CExchangeResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CExchangeFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CExchangeFactory *pFactory, CExchange *pObject, CWriteableExchange *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CExchangeFactory
	///@return	��CExchangeFactory
	CExchangeFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CExchangeFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CExchangeResource *alloc(int type, CExchangeFactory *pFactory, CExchange *pObject, CWriteableExchange *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CExchangeFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableExchange writeableObject;
	
	static CMemoryStack<CExchangeResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CSeatResource��һ��˵����CSeatFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatResource : public CDatabaseResource
{
public:
	///���췽��
	CSeatResource(void);
	virtual ~CSeatResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CSeatFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CSeatFactory *pFactory, CSeat *pObject, CWriteableSeat *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CSeatFactory
	///@return	��CSeatFactory
	CSeatFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CSeatFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CSeatResource *alloc(int type, CSeatFactory *pFactory, CSeat *pObject, CWriteableSeat *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CSeatFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableSeat writeableObject;
	
	static CMemoryStack<CSeatResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentResource��һ��˵����CInstrumentFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentResource : public CDatabaseResource
{
public:
	///���췽��
	CInstrumentResource(void);
	virtual ~CInstrumentResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInstrumentFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CInstrumentFactory *pFactory, CInstrument *pObject, CWriteableInstrument *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CInstrumentFactory
	///@return	��CInstrumentFactory
	CInstrumentFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInstrumentFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CInstrumentResource *alloc(int type, CInstrumentFactory *pFactory, CInstrument *pObject, CWriteableInstrument *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CInstrumentFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableInstrument writeableObject;
	
	static CMemoryStack<CInstrumentResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailResource��һ��˵����CCmbInstrumentDetailFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailResource : public CDatabaseResource
{
public:
	///���췽��
	CCmbInstrumentDetailResource(void);
	virtual ~CCmbInstrumentDetailResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CCmbInstrumentDetailFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CCmbInstrumentDetailFactory *pFactory, CCmbInstrumentDetail *pObject, CWriteableCmbInstrumentDetail *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CCmbInstrumentDetailFactory
	///@return	��CCmbInstrumentDetailFactory
	CCmbInstrumentDetailFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CCmbInstrumentDetailFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CCmbInstrumentDetailResource *alloc(int type, CCmbInstrumentDetailFactory *pFactory, CCmbInstrumentDetail *pObject, CWriteableCmbInstrumentDetail *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CCmbInstrumentDetailFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableCmbInstrumentDetail writeableObject;
	
	static CMemoryStack<CCmbInstrumentDetailResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDResource��һ��˵����CClientTradingIDFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDResource : public CDatabaseResource
{
public:
	///���췽��
	CClientTradingIDResource(void);
	virtual ~CClientTradingIDResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CClientTradingIDFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CClientTradingIDFactory *pFactory, CClientTradingID *pObject, CWriteableClientTradingID *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CClientTradingIDFactory
	///@return	��CClientTradingIDFactory
	CClientTradingIDFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CClientTradingIDFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CClientTradingIDResource *alloc(int type, CClientTradingIDFactory *pFactory, CClientTradingID *pObject, CWriteableClientTradingID *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CClientTradingIDFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableClientTradingID writeableObject;
	
	static CMemoryStack<CClientTradingIDResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorResource��һ��˵����CInvestorFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorResource : public CDatabaseResource
{
public:
	///���췽��
	CInvestorResource(void);
	virtual ~CInvestorResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInvestorFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CInvestorFactory *pFactory, CInvestor *pObject, CWriteableInvestor *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CInvestorFactory
	///@return	��CInvestorFactory
	CInvestorFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInvestorFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CInvestorResource *alloc(int type, CInvestorFactory *pFactory, CInvestor *pObject, CWriteableInvestor *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CInvestorFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableInvestor writeableObject;
	
	static CMemoryStack<CInvestorResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginResource��һ��˵����CInvestorMarginFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginResource : public CDatabaseResource
{
public:
	///���췽��
	CInvestorMarginResource(void);
	virtual ~CInvestorMarginResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInvestorMarginFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CInvestorMarginFactory *pFactory, CInvestorMargin *pObject, CWriteableInvestorMargin *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CInvestorMarginFactory
	///@return	��CInvestorMarginFactory
	CInvestorMarginFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInvestorMarginFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CInvestorMarginResource *alloc(int type, CInvestorMarginFactory *pFactory, CInvestorMargin *pObject, CWriteableInvestorMargin *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CInvestorMarginFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableInvestorMargin writeableObject;
	
	static CMemoryStack<CInvestorMarginResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeResource��һ��˵����CInvestorFeeFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeResource : public CDatabaseResource
{
public:
	///���췽��
	CInvestorFeeResource(void);
	virtual ~CInvestorFeeResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInvestorFeeFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CInvestorFeeFactory *pFactory, CInvestorFee *pObject, CWriteableInvestorFee *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CInvestorFeeFactory
	///@return	��CInvestorFeeFactory
	CInvestorFeeFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInvestorFeeFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CInvestorFeeResource *alloc(int type, CInvestorFeeFactory *pFactory, CInvestorFee *pObject, CWriteableInvestorFee *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CInvestorFeeFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableInvestorFee writeableObject;
	
	static CMemoryStack<CInvestorFeeResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CUserResource��һ��˵����CUserFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserResource : public CDatabaseResource
{
public:
	///���췽��
	CUserResource(void);
	virtual ~CUserResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CUserFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CUserFactory *pFactory, CUser *pObject, CWriteableUser *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CUserFactory
	///@return	��CUserFactory
	CUserFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CUserFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CUserResource *alloc(int type, CUserFactory *pFactory, CUser *pObject, CWriteableUser *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CUserFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableUser writeableObject;
	
	static CMemoryStack<CUserResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorResource��һ��˵����CUserInvestorFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorResource : public CDatabaseResource
{
public:
	///���췽��
	CUserInvestorResource(void);
	virtual ~CUserInvestorResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CUserInvestorFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CUserInvestorFactory *pFactory, CUserInvestor *pObject, CWriteableUserInvestor *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CUserInvestorFactory
	///@return	��CUserInvestorFactory
	CUserInvestorFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CUserInvestorFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CUserInvestorResource *alloc(int type, CUserInvestorFactory *pFactory, CUserInvestor *pObject, CWriteableUserInvestor *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CUserInvestorFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableUserInvestor writeableObject;
	
	static CMemoryStack<CUserInvestorResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedResource��һ��˵����COrderInsertFailedFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedResource : public CDatabaseResource
{
public:
	///���췽��
	COrderInsertFailedResource(void);
	virtual ~COrderInsertFailedResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�COrderInsertFailedFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, COrderInsertFailedFactory *pFactory, COrderInsertFailed *pObject, CWriteableOrderInsertFailed *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�COrderInsertFailedFactory
	///@return	��COrderInsertFailedFactory
	COrderInsertFailedFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�COrderInsertFailedFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static COrderInsertFailedResource *alloc(int type, COrderInsertFailedFactory *pFactory, COrderInsertFailed *pObject, CWriteableOrderInsertFailed *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	COrderInsertFailedFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableOrderInsertFailed writeableObject;
	
	static CMemoryStack<COrderInsertFailedResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightResource��һ��˵����CUserTradingRightFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightResource : public CDatabaseResource
{
public:
	///���췽��
	CUserTradingRightResource(void);
	virtual ~CUserTradingRightResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CUserTradingRightFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CUserTradingRightFactory *pFactory, CUserTradingRight *pObject, CWriteableUserTradingRight *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CUserTradingRightFactory
	///@return	��CUserTradingRightFactory
	CUserTradingRightFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CUserTradingRightFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CUserTradingRightResource *alloc(int type, CUserTradingRightFactory *pFactory, CUserTradingRight *pObject, CWriteableUserTradingRight *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CUserTradingRightFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableUserTradingRight writeableObject;
	
	static CMemoryStack<CUserTradingRightResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeResource��һ��˵����CCurrentTimeFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeResource : public CDatabaseResource
{
public:
	///���췽��
	CCurrentTimeResource(void);
	virtual ~CCurrentTimeResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CCurrentTimeFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CCurrentTimeFactory *pFactory, CCurrentTime *pObject, CWriteableCurrentTime *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CCurrentTimeFactory
	///@return	��CCurrentTimeFactory
	CCurrentTimeFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CCurrentTimeFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CCurrentTimeResource *alloc(int type, CCurrentTimeFactory *pFactory, CCurrentTime *pObject, CWriteableCurrentTime *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CCurrentTimeFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableCurrentTime writeableObject;
	
	static CMemoryStack<CCurrentTimeResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionResource��һ��˵����CUserSessionFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionResource : public CDatabaseResource
{
public:
	///���췽��
	CUserSessionResource(void);
	virtual ~CUserSessionResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CUserSessionFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CUserSessionFactory *pFactory, CUserSession *pObject, CWriteableUserSession *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CUserSessionFactory
	///@return	��CUserSessionFactory
	CUserSessionFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CUserSessionFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CUserSessionResource *alloc(int type, CUserSessionFactory *pFactory, CUserSession *pObject, CWriteableUserSession *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CUserSessionFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableUserSession writeableObject;
	
	static CMemoryStack<CUserSessionResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDResource��һ��˵����CMaxLocalIDFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDResource : public CDatabaseResource
{
public:
	///���췽��
	CMaxLocalIDResource(void);
	virtual ~CMaxLocalIDResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CMaxLocalIDFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CMaxLocalIDFactory *pFactory, CMaxLocalID *pObject, CWriteableMaxLocalID *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CMaxLocalIDFactory
	///@return	��CMaxLocalIDFactory
	CMaxLocalIDFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CMaxLocalIDFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CMaxLocalIDResource *alloc(int type, CMaxLocalIDFactory *pFactory, CMaxLocalID *pObject, CWriteableMaxLocalID *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CMaxLocalIDFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableMaxLocalID writeableObject;
	
	static CMemoryStack<CMaxLocalIDResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDResource��һ��˵����CBrkUserIDLocalIDFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDResource : public CDatabaseResource
{
public:
	///���췽��
	CBrkUserIDLocalIDResource(void);
	virtual ~CBrkUserIDLocalIDResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CBrkUserIDLocalIDFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CBrkUserIDLocalIDFactory *pFactory, CBrkUserIDLocalID *pObject, CWriteableBrkUserIDLocalID *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CBrkUserIDLocalIDFactory
	///@return	��CBrkUserIDLocalIDFactory
	CBrkUserIDLocalIDFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CBrkUserIDLocalIDFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CBrkUserIDLocalIDResource *alloc(int type, CBrkUserIDLocalIDFactory *pFactory, CBrkUserIDLocalID *pObject, CWriteableBrkUserIDLocalID *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CBrkUserIDLocalIDFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableBrkUserIDLocalID writeableObject;
	
	static CMemoryStack<CBrkUserIDLocalIDResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionResource��һ��˵����CPartClientInsGroupPositionFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionResource : public CDatabaseResource
{
public:
	///���췽��
	CPartClientInsGroupPositionResource(void);
	virtual ~CPartClientInsGroupPositionResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CPartClientInsGroupPositionFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CPartClientInsGroupPositionFactory *pFactory, CPartClientInsGroupPosition *pObject, CWriteablePartClientInsGroupPosition *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CPartClientInsGroupPositionFactory
	///@return	��CPartClientInsGroupPositionFactory
	CPartClientInsGroupPositionFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CPartClientInsGroupPositionFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CPartClientInsGroupPositionResource *alloc(int type, CPartClientInsGroupPositionFactory *pFactory, CPartClientInsGroupPosition *pObject, CWriteablePartClientInsGroupPosition *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CPartClientInsGroupPositionFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteablePartClientInsGroupPosition writeableObject;
	
	static CMemoryStack<CPartClientInsGroupPositionResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeResource��һ��˵����CClientMarginCombTypeFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeResource : public CDatabaseResource
{
public:
	///���췽��
	CClientMarginCombTypeResource(void);
	virtual ~CClientMarginCombTypeResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CClientMarginCombTypeFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CClientMarginCombTypeFactory *pFactory, CClientMarginCombType *pObject, CWriteableClientMarginCombType *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CClientMarginCombTypeFactory
	///@return	��CClientMarginCombTypeFactory
	CClientMarginCombTypeFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CClientMarginCombTypeFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CClientMarginCombTypeResource *alloc(int type, CClientMarginCombTypeFactory *pFactory, CClientMarginCombType *pObject, CWriteableClientMarginCombType *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CClientMarginCombTypeFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableClientMarginCombType writeableObject;
	
	static CMemoryStack<CClientMarginCombTypeResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupResource��һ��˵����CInstrumentGroupFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupResource : public CDatabaseResource
{
public:
	///���췽��
	CInstrumentGroupResource(void);
	virtual ~CInstrumentGroupResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInstrumentGroupFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CInstrumentGroupFactory *pFactory, CInstrumentGroup *pObject, CWriteableInstrumentGroup *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CInstrumentGroupFactory
	///@return	��CInstrumentGroupFactory
	CInstrumentGroupFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInstrumentGroupFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CInstrumentGroupResource *alloc(int type, CInstrumentGroupFactory *pFactory, CInstrumentGroup *pObject, CWriteableInstrumentGroup *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CInstrumentGroupFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableInstrumentGroup writeableObject;
	
	static CMemoryStack<CInstrumentGroupResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateResource��һ��˵����CSGEDeferRateFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateResource : public CDatabaseResource
{
public:
	///���췽��
	CSGEDeferRateResource(void);
	virtual ~CSGEDeferRateResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CSGEDeferRateFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CSGEDeferRateFactory *pFactory, CSGEDeferRate *pObject, CWriteableSGEDeferRate *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CSGEDeferRateFactory
	///@return	��CSGEDeferRateFactory
	CSGEDeferRateFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CSGEDeferRateFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CSGEDeferRateResource *alloc(int type, CSGEDeferRateFactory *pFactory, CSGEDeferRate *pObject, CWriteableSGEDeferRate *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CSGEDeferRateFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableSGEDeferRate writeableObject;
	
	static CMemoryStack<CSGEDeferRateResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightResource��һ��˵����CInvestorTradingRightFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightResource : public CDatabaseResource
{
public:
	///���췽��
	CInvestorTradingRightResource(void);
	virtual ~CInvestorTradingRightResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInvestorTradingRightFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CInvestorTradingRightFactory *pFactory, CInvestorTradingRight *pObject, CWriteableInvestorTradingRight *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CInvestorTradingRightFactory
	///@return	��CInvestorTradingRightFactory
	CInvestorTradingRightFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInvestorTradingRightFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CInvestorTradingRightResource *alloc(int type, CInvestorTradingRightFactory *pFactory, CInvestorTradingRight *pObject, CWriteableInvestorTradingRight *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CInvestorTradingRightFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableInvestorTradingRight writeableObject;
	
	static CMemoryStack<CInvestorTradingRightResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CUserIPResource��һ��˵����CUserIPFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPResource : public CDatabaseResource
{
public:
	///���췽��
	CUserIPResource(void);
	virtual ~CUserIPResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CUserIPFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CUserIPFactory *pFactory, CUserIP *pObject, CWriteableUserIP *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CUserIPFactory
	///@return	��CUserIPFactory
	CUserIPFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CUserIPFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CUserIPResource *alloc(int type, CUserIPFactory *pFactory, CUserIP *pObject, CWriteableUserIP *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CUserIPFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableUserIP writeableObject;
	
	static CMemoryStack<CUserIPResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeResource��һ��˵����CInvestorOptionFeeFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeResource : public CDatabaseResource
{
public:
	///���췽��
	CInvestorOptionFeeResource(void);
	virtual ~CInvestorOptionFeeResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInvestorOptionFeeFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CInvestorOptionFeeFactory *pFactory, CInvestorOptionFee *pObject, CWriteableInvestorOptionFee *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CInvestorOptionFeeFactory
	///@return	��CInvestorOptionFeeFactory
	CInvestorOptionFeeFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CInvestorOptionFeeFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CInvestorOptionFeeResource *alloc(int type, CInvestorOptionFeeFactory *pFactory, CInvestorOptionFee *pObject, CWriteableInvestorOptionFee *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CInvestorOptionFeeFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableInvestorOptionFee writeableObject;
	
	static CMemoryStack<CInvestorOptionFeeResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataResource��һ��˵����CMarketDataFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataResource : public CDatabaseResource
{
public:
	///���췽��
	CMarketDataResource(void);
	virtual ~CMarketDataResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CMarketDataFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CMarketDataFactory *pFactory, CMarketData *pObject, CWriteableMarketData *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CMarketDataFactory
	///@return	��CMarketDataFactory
	CMarketDataFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CMarketDataFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CMarketDataResource *alloc(int type, CMarketDataFactory *pFactory, CMarketData *pObject, CWriteableMarketData *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CMarketDataFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableMarketData writeableObject;
	
	static CMemoryStack<CMarketDataResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayResource��һ��˵����COrderDelayFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayResource : public CDatabaseResource
{
public:
	///���췽��
	COrderDelayResource(void);
	virtual ~COrderDelayResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�COrderDelayFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, COrderDelayFactory *pFactory, COrderDelay *pObject, CWriteableOrderDelay *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�COrderDelayFactory
	///@return	��COrderDelayFactory
	COrderDelayFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�COrderDelayFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static COrderDelayResource *alloc(int type, COrderDelayFactory *pFactory, COrderDelay *pObject, CWriteableOrderDelay *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	COrderDelayFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableOrderDelay writeableObject;
	
	static CMemoryStack<COrderDelayResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoResource��һ��˵����CSystemInfoFactory��ʹ����������ԭ����Դ
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoResource : public CDatabaseResource
{
public:
	///���췽��
	CSystemInfoResource(void);
	virtual ~CSystemInfoResource(void);

	///��ʼ��
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CSystemInfoFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	void init(int type, CSystemInfoFactory *pFactory, CSystemInfo *pObject, CWriteableSystemInfo *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
		switch (type)
		{
		case CREATE_ACTION:
			break;
		case UPDATE_ACTION:
		case DELETE_ACTION:
			pFactory->retrieve(pObject,&writeableObject);
			break;
		default:
			RAISE_DESIGN_ERROR("Invalid resource type");
		}				
	}

	///�ͷ��Լ�
	virtual void free(void);

	///��ȡ����Դ���ڵ�CSystemInfoFactory
	///@return	��CSystemInfoFactory
	CSystemInfoFactory *getFactory(void)
	{
		return pFactory;
	}

	///����ύ
	virtual void commit(void);
	
	///��ɹ���
	virtual void rollback(void);
	
	///��ȡ���ȼ������ȼ����Կ���commitʱ�Ĵ���
	///@return	����Դ�����ȼ���0��ʾ��ߣ�1��ʾ������1��ʾ���
	virtual int getPriority(void);

	///����һ����ָ�����ݵ���Դ
	///@param	type	��Դ���ͣ�Ӧ����CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION
	///@param	pFactory	����Դ���ڵ�CSystemInfoFactory
	///@param	pObject	����Դ�ĵ�ַ
	///@param	pWriteableObject	�µĶ���ֵ����typeΪUPDATE_ACTIONʱ��Ч����Ŀǰ��ʵ����û���ô�
	///@param	updateIndex	�Ƿ��������
	///@return	����һ����ָ�����ݵ���Դ
	static CSystemInfoResource *alloc(int type, CSystemInfoFactory *pFactory, CSystemInfo *pObject, CWriteableSystemInfo *pWriteableObject, bool updateIndex=true);
private:
	///��ű���Դ���ڵĶ��󹤳�
	CSystemInfoFactory *pFactory;
	
	///��ű���Դ�޸�ǰ��ֵ����typeΪCREATE_ACTION��DELETE_ACTIONʱ������������
	CWriteableSystemInfo writeableObject;
	
	static CMemoryStack<CSystemInfoResource> resourceList;
};

#endif
