// Index.cpp: implementation of the CIndex class.
//
//////////////////////////////////////////////////////////////////////
#include "CBaseObject.h"
#include "Index.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIndex::CIndex(TCompareFunc compareFunc)
{
	m_CompareFunc = compareFunc;
	clear();
}

CIndex::~CIndex(void)
{
}

#define LEFT_DEPTH(pNode) (pNode->left==NULL?0:pNode->left->depth)

#define RIGHT_DEPTH(pNode) (pNode->right==NULL?0:pNode->right->depth)

#define EVAL_DEPTH(pNode) (pNode->depth=MAX(LEFT_DEPTH(pNode),RIGHT_DEPTH(pNode))+1)

#define SET_LEFT(pNode1,pNode2)			\
	{									\
		pNode1->left=pNode2;			\
		if (pNode2!=NULL) 				\
			pNode2->father=pNode1;		\
	}

#define SET_RIGHT(pNode1,pNode2)		\
	{									\
		pNode1->right=pNode2;			\
		if (pNode2!=NULL)				\
			pNode2->father=pNode1;		\
	}

#define SET_FATHER(pNode1,pNode2,oldSon)\
	{									\
		pNode1->father=pNode2;			\
		if (pNode2!=NULL)				\
		{								\
			if (pNode2->left==oldSon)	\
				pNode2->left=pNode1;	\
			else						\
				pNode2->right=pNode1;	\
		}								\
		else							\
			setRoot(pNode1);			\
	}


CIndexNode *CIndex::addObject(void *pObject)
{
	CIndexNode tmpNode;
	CIndexNode *newNode,*thisNode,*lastNode;
	int isLeft;

	tmpNode.pObject=pObject;
	tmpNode.left=NULL;
	tmpNode.right=NULL;
	tmpNode.depth=1;
	m_Queue.push_back(tmpNode);
	newNode=&m_Queue.back();

	if (getRoot()==NULL)
	{
		SET_FATHER(newNode,getRoot(),NULL);
		return newNode;
	}
	
	thisNode=getRoot();
	while (thisNode!=NULL)
	{
		lastNode=thisNode;
		if (m_CompareFunc(pObject,thisNode->pObject)<0)
		{
			thisNode=thisNode->left;
			isLeft=1;
		}
		else
		{
			thisNode=thisNode->right;
			isLeft=0;
		}
	}
	newNode->father=lastNode;
	if (isLeft)
		lastNode->left=newNode;
	else
		lastNode->right=newNode;
	
	alterTree(lastNode);

	return newNode;
}

void CIndex::alterTree(CIndexNode *thisNode)
{
	while (thisNode!=NULL)
	{
		int leftDepth,rightDepth,thisDepth;
		CIndexNode *lTree,*llTree,*lrTree;
		CIndexNode *rTree,*rlTree,*rrTree;
		CIndexNode *fatherNode;
		
		leftDepth=LEFT_DEPTH(thisNode);
		rightDepth=RIGHT_DEPTH(thisNode);
		fatherNode=thisNode->father;
		if (leftDepth-rightDepth>=2)
		{
			rTree=thisNode->right;
			lTree=thisNode->left;
			lrTree=lTree->right;
			llTree=lTree->left;
			if (LEFT_DEPTH(lTree)>=RIGHT_DEPTH(lTree))
			{
				//LL Type
				SET_LEFT(thisNode,lrTree);
				SET_RIGHT(lTree,thisNode);
				SET_FATHER(lTree,fatherNode,thisNode);
				EVAL_DEPTH(thisNode);
				EVAL_DEPTH(lTree);
				thisNode=fatherNode;
			}
			else
			{
				CIndexNode *lrrTree,*lrlTree;
				
				//LR Type
				lrrTree=lrTree->right;
				lrlTree=lrTree->left;
				SET_LEFT(thisNode,lrrTree);
				SET_RIGHT(lTree,lrlTree);
				SET_RIGHT(lrTree,thisNode);
				SET_LEFT(lrTree,lTree);
				SET_FATHER(lrTree,fatherNode,thisNode);
				EVAL_DEPTH(thisNode);
				EVAL_DEPTH(lTree);
				EVAL_DEPTH(lrTree);
				thisNode=fatherNode;
			}
		}
		else if (rightDepth-leftDepth>=2)
		{
			lTree=thisNode->left;
			rTree=thisNode->right;
			rlTree=rTree->left;
			rrTree=rTree->right;
			if (RIGHT_DEPTH(rTree)>=LEFT_DEPTH(rTree))
			{
				//RR Type
				SET_RIGHT(thisNode,rlTree);
				SET_LEFT(rTree,thisNode);
				SET_FATHER(rTree,fatherNode,thisNode);
				EVAL_DEPTH(thisNode);
				EVAL_DEPTH(rTree);
				thisNode=fatherNode;
			}
			else
			{
				CIndexNode *rllTree,*rlrTree;
				
				//RL Type
				rllTree=rlTree->left;
				rlrTree=rlTree->right;
				SET_RIGHT(thisNode,rllTree);
				SET_LEFT(rTree,rlrTree);
				SET_LEFT(rlTree,thisNode);
				SET_RIGHT(rlTree,rTree);
				SET_FATHER(rlTree,fatherNode,thisNode);
				EVAL_DEPTH(thisNode);
				EVAL_DEPTH(rTree);
				EVAL_DEPTH(rlTree);
				thisNode=fatherNode;
			}
		}
		else
		{
			thisDepth=MAX(leftDepth,rightDepth)+1;
			if (thisNode->depth==thisDepth)
				return;
			else
			{
				thisNode->depth=thisDepth;
				thisNode=fatherNode;
			}
		}
	}
}

CIndexNode *CIndex::getSmallest(void)
{
	CIndexNode *thisNode;
	
	if (getRoot()==NULL)
		return NULL;
	thisNode=getRoot();
	while (thisNode->left!=NULL)
		thisNode=thisNode->left;
	return thisNode;
}

CIndexNode *CIndex::getLargest(void)
{
	CIndexNode *thisNode;
	
	if (getRoot()==NULL)
		return NULL;
	thisNode=getRoot();
	while (thisNode->right!=NULL)
		thisNode=thisNode->right;
	return thisNode;
}

CIndexNode *CIndex::searchFirstGreatEqual(void *pObject)
{
	CIndexNode *thisNode,*lastNode;
	
	thisNode=getRoot();
	lastNode=NULL;
	while (thisNode!=NULL)
	{
		switch (m_CompareFunc(thisNode->pObject,pObject))
		{
		case 1:
			lastNode=thisNode;
			thisNode=thisNode->left;
			break;
		case -1:
			thisNode=thisNode->right;
			break;
		case 0:
			lastNode=thisNode;
			thisNode=thisNode->left;
			break;
		default:
			assert(false);
		}
	}
	return lastNode;
}

CIndexNode *CIndex::searchFirstGreat(void *pObject)
{
	CIndexNode *thisNode,*lastNode;
	
	thisNode=getRoot();
	lastNode=NULL;
	while (thisNode!=NULL)
	{
		switch (m_CompareFunc(thisNode->pObject,pObject))
		{
		case 1:
			lastNode=thisNode;
			thisNode=thisNode->left;
			break;
		case -1:
			thisNode=thisNode->right;
			break;
		case 0:
			thisNode=thisNode->right;
			break;
		default:
			assert(false);
		}
	}
	return lastNode;
}

CIndexNode *CIndex::searchLastLessEqual(void *pObject)
{
	CIndexNode *thisNode,*lastNode;
	
	thisNode=getRoot();
	lastNode=NULL;
	while (thisNode!=NULL)
	{
		switch (m_CompareFunc(thisNode->pObject,pObject))
		{
		case 1:
			thisNode=thisNode->left;
			break;
		case -1:
			lastNode=thisNode;
			thisNode=thisNode->right;
			break;
		case 0:
			lastNode=thisNode;
			thisNode=thisNode->right;
			break;
		default:
			assert(false);
		}
	}
	return lastNode;
}

CIndexNode *CIndex::searchLastLess(void *pObject)
{
	CIndexNode *thisNode,*lastNode;
	
	thisNode=getRoot();
	lastNode=NULL;
	while (thisNode!=NULL)
	{
		switch (m_CompareFunc(thisNode->pObject,pObject))
		{
		case 1:
			thisNode=thisNode->left;
			break;
		case -1:
			lastNode=thisNode;
			thisNode=thisNode->right;
			break;
		case 0:
			thisNode=thisNode->left;
			break;
		default:
			assert(false);
		}
	}
	return lastNode;
}

CIndexNode *CIndex::searchFirstEqual(void *pObject)
{
	CIndexNode *thisNode,*lastNode;
	
	thisNode=getRoot();
	lastNode=NULL;
	while (thisNode!=NULL)
	{
		int ret = m_CompareFunc(thisNode->pObject,pObject);
		switch (ret)
		{
		case 1:
			thisNode=thisNode->left;
			break;
		case -1:
			thisNode=thisNode->right;
			break;
		case 0:
			lastNode=thisNode;
			thisNode=thisNode->left;
			break;
		default:
			assert(false);
		}
	}
	return lastNode;
}

CIndexNode *CIndex::searchLastEqual(void *pObject)
{
	CIndexNode *thisNode,*lastNode;
	
	thisNode=getRoot();
	lastNode=NULL;
	while (thisNode!=NULL)
	{
		switch (m_CompareFunc(thisNode->pObject,pObject))
		{
		case 1:
			thisNode=thisNode->left;
			break;
		case -1:
			thisNode=thisNode->right;
			break;
		case 0:
			lastNode=thisNode;
			thisNode=thisNode->right;
			break;
		default:
			assert(false);
		}
	}
	return lastNode;
}

CIndexNode *CIndex::getNextNode(CIndexNode *pNode)
{
	CIndexNode *thisNode,*fatherNode;
	
	if (pNode->right!=NULL)
	{
		//right tree exist, find the leftmost node in the right tree
		thisNode=pNode->right;
		while (thisNode->left!=NULL)
			thisNode=thisNode->left;
		return thisNode;
	}
	//find the recent ascend, whose left tree contain this node
	thisNode=pNode;
	fatherNode=thisNode->father;
	while (fatherNode!=NULL)
	{
		if (fatherNode->left==thisNode)
			return fatherNode;
		thisNode=fatherNode;
		fatherNode=thisNode->father;
	}
	return NULL;
}

CIndexNode *CIndex::getPrevNode(CIndexNode *pNode)
{
	CIndexNode *thisNode,*fatherNode;
	
	if (pNode->left!=NULL)
	{
		//left tree exist, find the rightmost node in the left tree
		thisNode=pNode->left;
		while (thisNode->right!=NULL)
			thisNode=thisNode->right;
		return thisNode;
	}
	//find the recent ascend, whose right tree contain this node
	thisNode=pNode;
	fatherNode=thisNode->father;
	while (fatherNode!=NULL)
	{
		if (fatherNode->right==thisNode)
			return fatherNode;
		thisNode=fatherNode;
		fatherNode=thisNode->father;
	}
	return NULL;
}

void CIndex::clear()
{
	m_Queue.clear();
	setRoot(NULL);
}

void CIndex::removeNode(CIndexNode *pNode)
{
	CIndexNode *thisNode,*fatherNode,*targetNode;
	int leftDepth,rightDepth;
	
	thisNode=pNode;
	fatherNode=thisNode->father;
	while (thisNode->depth!=1)
	{
		leftDepth=LEFT_DEPTH(thisNode);
		rightDepth=RIGHT_DEPTH(thisNode);
		if (leftDepth>rightDepth)
		{
			//find the rightmost in the left tree
			targetNode=thisNode->left;
			while (targetNode->right!=NULL)
				targetNode=targetNode->right;
			//move object
			thisNode->pObject=targetNode->pObject;
			thisNode=targetNode;
		}
		else
		{
			//find the leftmost in the right tree
			targetNode=thisNode->right;
			while (targetNode->left!=NULL)
				targetNode=targetNode->left;
			//move object
			thisNode->pObject=targetNode->pObject;
			thisNode=targetNode;
		}
		fatherNode=thisNode->father;
	}
	if (fatherNode!=NULL)
	{
		if (fatherNode->left==thisNode)
			fatherNode->left=NULL;
		else
			fatherNode->right=NULL;
	}
	else
		setRoot(NULL);
	alterTree(fatherNode);
//	pIndexMem->free(thisNode);
}

