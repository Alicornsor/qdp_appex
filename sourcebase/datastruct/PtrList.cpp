// List.cpp: implementation of the CList class.
//
//////////////////////////////////////////////////////////////////////
#include "CBaseObject.h"
#include "PtrList.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CPtrListAllocator::CPtrListAllocator()
{
	_M_block = NULL;
	_M_node = NULL;
}

CPtrListAllocator::~CPtrListAllocator()
{
	while (_M_block != NULL) 
	{
		TPtrListBlock *__next = _M_block->_M_next;
		delete _M_block;
		_M_block = __next;
	}
}

TPtrListNode *CPtrListAllocator::GetNode()
{
	if (_M_node == NULL) 
	{
		TPtrListBlock *__new = new TPtrListBlock;
		__new->_M_next = _M_block;
		_M_block = __new;
		for (int i=0; i<PL_BLOCK_SIZE-1; i++)
		{
			__new->_M_listNode[i]._M_next = &__new->_M_listNode[i+1];
		}
		__new->_M_listNode[PL_BLOCK_SIZE-1]._M_next = NULL;
		_M_node = &__new->_M_listNode[0];
	}

	TPtrListNode * __temp = _M_node;
	_M_node = _M_node->_M_next; 
	return __temp;
}

void CPtrListAllocator::PutNode(TPtrListNode *__node)
{
	__node->_M_next = _M_node;
	_M_node = __node;
}

CPtrList::CPtrList()
{
	_M_node = _M_alloctor.GetNode();
    _M_node->_M_next = _M_node;
    _M_node->_M_prev = _M_node;
	_M_count = 0;
}

CPtrList::~CPtrList()
{
	Clear();
	_M_alloctor.PutNode(_M_node);

}

CPtrList::iterator CPtrList::Insert(CPtrList::iterator __position, void * __x)
{
	_Node* __tmp = _M_alloctor.GetNode();
    __tmp->_M_next = __position._M_node;
    __tmp->_M_prev = __position._M_node->_M_prev;
	__tmp->_M_data = __x;
    __position._M_node->_M_prev->_M_next = __tmp;
    __position._M_node->_M_prev = __tmp;
	_M_count++;
    return __tmp;
}

CPtrList::iterator CPtrList::Erase(CPtrList::iterator __position) {
	_Node* __next_node = __position._M_node->_M_next;
	_Node* __prev_node = __position._M_node->_M_prev;
	_Node* __n = (_Node*) __position._M_node;
	__prev_node->_M_next = __next_node;
	__next_node->_M_prev = __prev_node;
//	_Destroy(&__n->_M_data);
	_M_alloctor.PutNode(__n);
	_M_count--;
	return iterator((_Node*) __next_node);
}

void CPtrList::Remove(void *_value)
{
	iterator __first = Begin();
	iterator __last = End();
	while (__first != __last) {
		iterator __next = __first;
		++__next;
		if (*__first == _value) Erase(__first);
		__first = __next;
	}
}

void CPtrList::Clear() 
{
	_Node* __cur = (_Node*) _M_node->_M_next;
	while (__cur != _M_node) {
		_Node* __tmp = __cur;
		__cur = (_Node*) __cur->_M_next;
//		_Destroy(&__tmp->_M_data);
		_M_alloctor.PutNode(__tmp);
	}
	_M_node->_M_next = _M_node;
	_M_node->_M_prev = _M_node;
	_M_count = 0;
}

