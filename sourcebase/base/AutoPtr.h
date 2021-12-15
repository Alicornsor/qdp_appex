#ifndef _AUTO_PTR_H
#define _AUTO_PTR_H

/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file     CAutoPtr.h
///@brief    CAutoPtr 是一个自动封装对象指针的类，通过它来完成对指针的操作
///@history 
///20050623	张冀海		创建该文件
/////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// CAutoPtr 是一个自动封装对象指针的类，通过它来完成对指针的操作，以避免
///   出现内存泄露的问题。
///   在其中包含的对象需要由这几个方法
/// void AddRef 增加引用计数
/// void Release 减少引用技术，并且根据引用技术清除对象实例
/// 注：1. 对象的解构之所以放在对象之中自行处理，是因为这样可以提供更大的
///         灵活性，可以让有些对象只能通过auto_ptr来进行处理之类的工作。
///     2. 对象自行处理线程相关的情况，本类不做任何处理。
/// 使用方法：
///     1. 示例类
///			class A
///			{
///			public:
///				A():m_nCount(0){
///				}
///			protected:
///				virtual ~A(){} //可以防止在外部使用delete来删除
///			public:
///				void AddRef(){
///					m_nCount++;
///				}
///
///				virtual void Release(){
///					m_nCount--;
///					if(m_nCount == 0)
///						delete this;	
///				}
///				int m_nCount;
///			};
///		 2. 使用方法
///			CAutoPtr<A> pa(new A());
//////////////////////////////////////////////////////////////////////////

template <class T>
class CAutoPtr
{
	typedef T element_type;
private:
	T*   _point;		///传入的对象指针
public:
	//////////////////////////////////////////////////////////////////////////
	/// 构造函数,析构函数以及operatot = 
	//////////////////////////////////////////////////////////////////////////
	explicit CAutoPtr(T* p=0) throw():_point(p){	//从一个指针创建
		_point->AddRef();
	}	

	CAutoPtr(CAutoPtr& rhs) throw()          ///Copy contructor
	{
		_point = rhs._point;
		_point->AddRef();
	}

	template <class Y>
		CAutoPtr(CAutoPtr<Y>& rhs) throw()   ///支持继承类型
	{
		_point = rhs._point();
		_point->AddRef();
	}

	CAutoPtr& operator=(CAutoPtr& rhs) throw() ///Operator = 
	{
		_point = rhs._point;
		_point->AddRef();
		return *this;
	}

	template <class Y>
		CAutoPtr& operator=(CAutoPtr<Y>& rhs) throw()	///Operator = 
	{
		_point = rhs.operator ->();
		_point->AddRef();
		return *this;
	}


	~CAutoPtr() throw()				///析构函数
	{
		_point->Release();
		/*if(_point->GetRefCount() == 0)
		delete _point;*/
	}				

	//////////////////////////////////////////////////////////////////////////
	/// 成员函数
	//////////////////////////////////////////////////////////////////////////
	T& operator*() const throw()
	{
		return *_point;
	}

	T* operator->() const throw()
	{
		return _point;
	}

	void reset(T* p=0) throw()
	{
		if(_point != p)
		{
			_point->Release();
			_point = p;
		}
	}
};
#endif