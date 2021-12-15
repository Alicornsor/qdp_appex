// FixedCapVector.h: interface for the CFixedCapVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIXEDCAPVECTOR_H__CE858A99_B14A_4A81_94B3_0DC5F03C9C3C__INCLUDED_)
#define AFX_FIXEDCAPVECTOR_H__CE858A99_B14A_4A81_94B3_0DC5F03C9C3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template<class _Tp, int _capacity> 
class CFixedCapVector
{
public:
	typedef CFixedCapVector<_Tp, _capacity> * pointer;
	typedef CFixedCapVector<_Tp, _capacity> & reference;
	typedef _Tp value_type;
	class iterator
	{
	public:
		iterator(pointer i_container, int i_offset){
			this->_container=i_container; _offset=i_offset;
		}
		value_type & operator*() const {	return _container->_data[_offset]; };
		iterator & operator++() {	_offset++; return *this; }
		iterator operator++(int) { 	iterator __tmp = *this;	++*this; return __tmp; }
		bool operator==(const iterator& _X) const
		{return (_container==_X._container && _offset==_X._offset); }
		bool operator!=(const iterator& _X) const
		{return (!(*this == _X)); }
		int offset(){	return _offset; };
	private:
		pointer _container;
		int _offset;
	};
	CFixedCapVector(){	_count = 0; };
	iterator begin(){	return iterator(this, 0); };
	iterator end(){	return iterator(this, _count); };
	bool push_back(const _Tp &_x){if(_count>=_capacity)return false;_data[_count++]=_x;return true;};
protected:
	value_type _data[_capacity];
	int _count;
	
	friend class iterator;
};

#endif // !defined(AFX_FIXEDCAPVECTOR_H__CE858A99_B14A_4A81_94B3_0DC5F03C9C3C__INCLUDED_)
