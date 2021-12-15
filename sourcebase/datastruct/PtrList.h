// List.h: interface for the CList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PTRLIST_H__06F6D3EA_2196_47FA_880B_71724B2A5190__INCLUDED_)
#define AFX_PTRLIST_H__06F6D3EA_2196_47FA_880B_71724B2A5190__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PL_BLOCK_SIZE	32

struct TPtrListNode
{
	TPtrListNode *_M_next;	
	TPtrListNode *_M_prev;	
	void * _M_data;
};

class CPtrListIterator
{
public:
	typedef CPtrListIterator  _Self;
	typedef TPtrListNode _Node;
	typedef void * _Tp ;
	typedef _Tp & reference;
	CPtrListIterator(TPtrListNode *pNode):_M_node(pNode){;}
	reference operator*() const { return ((_Node*) _M_node)->_M_data; }
	_Self& operator++() { 
		this->Incr();
		return *this;
	}
	_Self operator++(int) { 
		_Self __tmp = *this;
		this->Incr();
		return __tmp;
	}
	_Self& operator--() { 
		this->Decr();
		return *this;
	}
	_Self operator--(int) { 
		_Self __tmp = *this;
		this->Decr();
		return __tmp;
	}
	bool operator==(const CPtrListIterator& __x) const {
		return _M_node == __x._M_node;
	}
	bool operator!=(const CPtrListIterator& __x) const {
		return _M_node != __x._M_node;
	}

	void Incr() { _M_node = _M_node->_M_next; }
	void Decr() { _M_node = _M_node->_M_prev; }
	
	_Node *_M_node;
};

struct TPtrListBlock
{
	TPtrListBlock *_M_next;
	TPtrListNode _M_listNode[PL_BLOCK_SIZE];
};

class CPtrListAllocator
{
public:
	CPtrListAllocator();
	~CPtrListAllocator();
	TPtrListNode *GetNode();
	void PutNode(TPtrListNode *__node);
private:
	TPtrListBlock * _M_block;
	TPtrListNode * _M_node;
};
/**Ë«ÏòÁ´±íÄ£°å
*/
class CPtrList  
{
public:
	typedef CPtrListIterator iterator;
	typedef TPtrListNode _Node;

	CPtrList();
	virtual ~CPtrList();
	iterator Insert(iterator __position, void * __x);
	iterator Erase(iterator __position);
	void Remove(void *_value);
	void Clear();
	iterator Begin(){ return (_Node*)(_M_node->_M_next); }
	iterator End(){ return _M_node; }

	void PushFront(void *__x) { Insert( Begin(), __x);}
	void PushBack(void *__x){ Insert(End(), __x);};
	int Size(){ return _M_count;};
private:
	CPtrListAllocator _M_alloctor;
	_Node * _M_node;
	int _M_count;
};

#endif // !defined(AFX_PTRLIST_H__06F6D3EA_2196_47FA_880B_71724B2A5190__INCLUDED_)
