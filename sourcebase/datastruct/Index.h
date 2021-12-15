// Index.h: interface for the CIndex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INDEX_H__4366595F_1D6D_49A5_9BEF_AB1FAD9EC14C__INCLUDED_)
#define AFX_INDEX_H__4366595F_1D6D_49A5_9BEF_AB1FAD9EC14C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//TCompareFunc是一个比较函数指针类型
typedef int (* TCompareFunc)(void *,void *);

//**********************************************************************
//CIndexNode是一个平衡数节点对象
//@作者	xuzh
//@版本	1.0,20020214
//**********************************************************************
class CIndexNode
{
public:
	//保存本节点中包含的对象
	void *pObject;
	//保存本节点的父节点、左儿子节点和右儿子节点
	CIndexNode *father, *left, *right;
	//平衡状况
	int depth;
};

//**********************************************************************
//CIndex是一个索引对象。索引对象是对某种类型的数据结构，以及其上的一种比较函数，
//生成的平衡树。
//@作者	xuzh
//@版本	1.0,20020214
//**********************************************************************
class CIndex
{
public:
	//构造函数，申请空间，建立一棵空的平衡树
	//@参数	compareFunc	比较函数指针
	CIndex(TCompareFunc compareFunc);
	
	//析构函数，负责释放空间
	virtual ~CIndex(void);
	
	//在本平衡树中加入一个新的对象节点
	//@参数	pObject	新的对象的首地址
	//@返回	加入树后包含此对象的节点
	CIndexNode *addObject(void *pObject);
	
	//获取最小的一个节点
	//@返回	最小的一个节点，如果还没有节点，则返回NULL
	CIndexNode *getSmallest(void);
	
	//获取最大的一个节点
	//@返回	最大的一个节点，如果还没有节点，则返回NULL
	CIndexNode *getLargest(void);

	//寻找第一个大于等于此对象的节点
	//@参数 pObject	比较时用的对象
	//@返回	第一个大于等于此对象的节点，如果不存在此节点，则返回NULL
	CIndexNode *searchFirstGreatEqual(void *pObject);
	
	//寻找第一个大于此对象的节点
	//@参数 pObject	比较时用的对象
	//@返回	第一个大于此对象的节点，如果不存在此节点，则返回NULL
	CIndexNode *searchFirstGreat(void *pObject);
	
	//寻找最后一个小于等于此对象的节点
	//@参数 pObject	比较时用的对象
	//@返回	最后一个小于等于此对象的节点，如果不存在此节点，则返回NULL
	CIndexNode *searchLastLessEqual(void *pObject);
	
	//寻找最后一个小于此对象的节点
	//@参数 pObject	比较时用的对象
	//@返回	最后一个小于此对象的节点，如果不存在此节点，则返回NULL
	CIndexNode *searchLastLess(void *pObject);
	
	//寻找第一个等于此对象的节点
	//@参数 pObject	比较时用的对象
	//@返回	第一个等于此对象的节点，如果不存在此节点，则返回NULL
	CIndexNode *searchFirstEqual(void *pObject);
	
	//寻找最后一个等于此对象的节点
	//@参数 pObject	比较时用的对象
	//@返回	最后一个等于此对象的节点，如果不存在此节点，则返回NULL
	CIndexNode *searchLastEqual(void *pObject);
	
	//寻找下一个节点，即大于此节点的第一个节点
	//@参数 pNode	目前节点
	//@返回	大于此节点的第一个节点，如果不存在此节点，则返回NULL
	CIndexNode *getNextNode(CIndexNode *pNode);
	
	//寻找前一个节点，即小于此节点的最后一个节点
	//@参数 pNode	目前节点
	//@返回	小于此节点的最后一个节点，如果不存在此节点，则返回NULL
	CIndexNode *getPrevNode(CIndexNode *pNode);

	void removeNode(CIndexNode *pNode);

	void clear();
private:
	//存储平衡树的CQueue
	deque<CIndexNode> m_Queue;
	
	//存储比较函数指针
	TCompareFunc m_CompareFunc;
	
	//调整树的平衡结构，从指定节点开始向上调整
	//@参数	thisNode	开始调整的节点
	void alterTree(CIndexNode *thisNode);
	
	//设置本平衡树的根
	//@参数	pNode	要设置为根的节点
	void setRoot(CIndexNode *pNode)
	{
		m_pRoot = pNode;
	}
	
	//获取本平衡树的根
	//@返回	当前的根节点
	CIndexNode *getRoot(void)
	{
		return m_pRoot;
	}

	CIndexNode *m_pRoot;
};

#endif // !defined(AFX_INDEX_H__4366595F_1D6D_49A5_9BEF_AB1FAD9EC14C__INCLUDED_)
