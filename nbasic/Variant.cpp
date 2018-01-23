#include "Variant.h"


namespace vl
{
	//为什么使用 T*=0 这样的参数
	template <typename T>
	inline const T* v_cast(const Variant::Private* d, T* = 0)
	{
		return ((sizeof(T) > sizeof(Variant::Private::Data))
		    ? static_cast<const T*>(d->data.shared->ptr)
		    : static_cast<const T*>(static_cast<const void*>(&d->data.c)));
	}
	
	template <typename T>
	inline T* v_cast(Variant::Private* d, T* = 0)
	{
		return ((sizeof(T) > sizeof(Variant::Private::Data))
		    ? static_cast<T*>(d->data.shared->ptr)
		    : static_cast<T*>(static_cast<void*>(&d->data.c)));			//返回联合体的首地址
	}
	
	template <class T> class VariantPrivateSharedEx : public Variant::PrivateShared
	{
		public:
			VariantPrivateSharedEx() : Variant::PrivateShared(&m_t) { }
			VariantPrivateSharedEx(const T& t) : Variant::PrivateShared(&m_t), m_t(t) { }
			
		private:
			T m_t;
	};
	//构造
	template <class T>
	inline void v_construct(Variant::Private* x, const void* copy, T* = 0)
	{
		//数据比联合体大的时候，使用共享的方式
		if (sizeof(T) > sizeof(Variant::Private::Data))
		{
			x->data.shared = copy ? new VariantPrivateSharedEx<T>(*static_cast<const T*>(copy))
			  : new VariantPrivateSharedEx<T>;
			x->is_shared = true;
		}
		else
		{
			if (copy)
				new (&x->data.ptr) T(*static_cast<const T*>(copy));		//调用拷贝构造，重新初始化内存
			else
				new (&x->data.ptr) T;
		}
	}
	
	template <class T>
	inline void v_construct(Variant::Private* x, const T& t)
	{
		if (sizeof(T) > sizeof(Variant::Private::Data))
		{
			x->data.shared = new VariantPrivateSharedEx<T>(t);	//会调用拷贝构造，将t拷贝
			x->is_shared = true;
		}
		else
		{
			new (&x->data.ptr) T(t);
		}
	}
	
	template <class T>
	inline void v_clear(Variant::Private* d, T* = 0)
	{
		if (sizeof(T) > sizeof(Variant::Private::Data))
		{
			//now we need to cast
			//because QVariant::PrivateShared doesn't have a virtual destructor
			delete static_cast<VariantPrivateSharedEx<T>*>(d->data.shared);
		}
		else
		{
			v_cast<T>(d)->~T();
		}
		
	}
	
	
	Variant::Variant(const Variant& other)
	{
	
	}
	
	Variant::~Variant()
	{
	}
}
