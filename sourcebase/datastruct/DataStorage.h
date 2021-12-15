// DataStorage.h: interface for the CDataStorage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATASTORAGE_H__EA0485B7_ABCE_4BA5_BB64_C1CE0987F3C6__INCLUDED_)
#define AFX_DATASTORAGE_H__EA0485B7_ABCE_4BA5_BB64_C1CE0987F3C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <typename _Tp>
class CDataStorage  
{
public:
	typedef bool (* _compare_func_type)(const void *, const void *);
	class _compare
	{
	public:
		_compare (_compare_func_type func)
		{
			_func = func;
		}
		bool operator()(const void* p1, const void* p2) const
		{
			return  _func(p1, p2);
		}
	private:
		_compare_func_type _func;
	};
	typedef _Tp value_type;
	typedef value_type * pointer;
	typedef value_type & reference;
	typedef multiset<pointer, _compare> index_type;
	typedef index_type * index_pointer;
	typedef vector<index_pointer> index_array;
	typedef deque<value_type> storage_type;
	typedef typename index_type::iterator iterator;
	typedef typename index_type::reverse_iterator  reverse_iterator ;
	CDataStorage()
		:_free_list_head(NULL)
	{
		_create_index(__compare_func_basic);
	}
	~CDataStorage()
	{
		typename index_array::iterator i = _index_array.begin();
		for (; i!=_index_array.end(); ++i)
		{
			delete (*i);
		}
	}
	
	void Clear()
	{
		typename index_array::iterator i = _index_array.begin();
		for (; i!=_index_array.end(); ++i)
		{
			(*i)->clear();
		}
		_data_storage.clear();
	}

	pointer AppendData(reference _x)
	{
		pointer pnew = NULL;
		if (_free_list_head != NULL)
		{
			pnew = _free_list_head;
			_free_list_head = *((pointer *)_free_list_head);
			*pnew = _x;
		}
		else
		{
			_data_storage.push_back(_x);
			pnew = &(_data_storage.back());
		}
		typename index_array::iterator i = _index_array.begin();
		for (; i!=_index_array.end(); ++i)
		{
			(*i)->insert(pnew);
		}
		return pnew;
	}

	iterator Begin()
	{
		return _index_array[0]->begin();
	}
	iterator End()
	{
		return _index_array[0]->end();
	}
	reverse_iterator  RBegin()
	{
		return _index_array[0]->rbegin();
	}
	reverse_iterator  REnd()
	{
		return _index_array[0]->rend();
	}
	int Erase(pointer _x)
	{
		typename index_array::iterator i = _index_array.begin();
		int n = (*i)->erase(_x);
		if (n != 1)
		{
			return n;
		}
		for (++i; i!=_index_array.end(); ++i)
		{
#ifdef WIN32
			pair<index_type::iterator, index_type::iterator>
#else
			pair<typename index_type::iterator, typename index_type::iterator> 
#endif
				rangepair = (*i)->equal_range(_x);
			typename index_type::iterator irange = rangepair.first;
			for (; irange != rangepair.second; ++irange)
			{
				if ((*irange) == _x)
				{
					(*i)->erase(irange);
					break;
				}
			}
		}
		*((pointer *)_x) = _free_list_head;
		_free_list_head = _x;
		return n;
	}
protected:
	static bool __compare_func_basic(const void *p1, const void *p2)
	{
		return p1 < p2;
	}

	index_pointer _create_index(_compare_func_type _func)
	{
		index_pointer p = new index_type(_compare(_func));
		_index_array.push_back(p);
		return p;
	}
protected:
	index_array _index_array;
	storage_type _data_storage;
	pointer _free_list_head;
};

#define DS_CREATE_INDEX_1(_field)												\
	__index_by_##_field = _create_index(_compare_func_by_##_field);

#define DS_DEFINE_INDEX_FUNC_1(_type, _field)									\
protected:																		\
	static bool _compare_func_by_##_field(const void *p1, const void *p2){		\
		return (((pointer)p1)->_field) < (((pointer)p2)->_field);				\
	}																			\
	index_pointer __index_by_##_field;											\
public:																			\
	pointer GetBy##_field(_type _field){										\
		value_type _value;														\
		_value._field = _field;													\
		iterator _i = __index_by_##_field->find(&_value);						\
		if(_i != __index_by_##_field->end())									\
			return (*_i);														\
		return NULL;															\
	}																			\
	int EraseBy##_field(_type _field){											\
		pointer _find = GetBy##_field(_field);									\
		if (_find == NULL)														\
			return 0;															\
		return Erase(_find);													\
	}																			\
	iterator BeginBy##_field()													\
	{																			\
		return __index_by_##_field->begin();									\
	}																			\
	iterator EndBy##_field()													\
	{																			\
		return __index_by_##_field->end();										\
	}																			\
	reverse_iterator RBeginBy##_field()											\
	{																			\
		return __index_by_##_field->rbegin();									\
	}																			\
	reverse_iterator REndBy##_field()											\
	{																			\
		return __index_by_##_field->rend();										\
	}																			\
	iterator LowerBoundBy##_field(_type _field)									\
	{																			\
		value_type _value;														\
		_value._field = _field;													\
		return __index_by_##_field->lower_bound(&_value);						\
	}																			\
	iterator UpperBoundBy##_field(_type _field)									\
	{																			\
		value_type _value;														\
		_value._field = _field;													\
		return __index_by_##_field->upper_bound(&_value);						\
	}
	
#define DS_CREATE_INDEX_2(_field1, _field2)										\
	__index_by_##_field1##_field2 = _create_index(_compare_func_by_##_field1##_field2);

#define DS_DEFINE_INDEX_FUNC_2(_type1, _field1, _type2, _field2)				\
	protected:																	\
		static bool _compare_func_by_##_field1##_field2(const void *p1, const void *p2){\
			if ((((pointer)p1)->_field1) == (((pointer)p2)->_field1))			\
				return (((pointer)p1)->_field2) < (((pointer)p2)->_field2);		\
			return (((pointer)p1)->_field1) < (((pointer)p2)->_field1);			\
		}																		\
		index_pointer __index_by_##_field1##_field2;							\
	public:																		\
		pointer GetBy##_field1##_field2(_type1 _field1, _type2 _field2){		\
			value_type _value;													\
			_value._field1 = _field1;											\
			_value._field2 = _field2;											\
			iterator _i = __index_by_##_field1##_field2->find(&_value);			\
			if(_i != __index_by_##_field1##_field2->end())						\
				return (*_i);													\
			return NULL;														\
		}																		\
		int EraseBy##_field1##_field2(_type1 _field1, _type2 _field2){			\
			pointer _find = GetBy##_field1##_field2(_field1, _field2);			\
			if (_find == NULL)													\
				return 0;														\
			return Erase(_find);												\
		}																		\
		iterator BeginBy##_field1##_field2()									\
		{																		\
			return __index_by_##_field1##_field2->begin();						\
		}																		\
		iterator EndBy##_field1##_field2()										\
		{																		\
			return __index_by_##_field1##_field2->end();						\
		}																		\
		reverse_iterator RBeginBy##_field1##_field2()							\
		{																		\
			return __index_by_##_field1##_field2->rbegin();						\
		}																		\
		reverse_iterator REndBy##_field1##_field2()								\
		{																		\
			return __index_by_##_field1##_field2->rend();						\
		}																		\
		iterator LowerBoundBy##_field1##_field2(_type1 _field1, _type2 _field2)	\
		{																		\
			value_type _value;													\
			_value._field1 = _field1;											\
			_value._field2 = _field2;											\
			return __index_by_##_field1##_field2->lower_bound(&_value);			\
		}																		\
		iterator UpperBoundBy##_field1##_field2(_type1 _field1, _type2 _field2)	\
		{																		\
			value_type _value;													\
			_value._field1 = _field1;											\
			_value._field2 = _field2;											\
			return __index_by_##_field1##_field2->upper_bound(&_value);			\
		}


#endif // !defined(AFX_DATASTORAGE_H__EA0485B7_ABCE_4BA5_BB64_C1CE0987F3C6__INCLUDED_)
