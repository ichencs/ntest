#include "Variant.h"


namespace vl
{
	//Ϊʲôʹ�� T*=0 �����Ĳ���
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
		    : static_cast<T*>(static_cast<void*>(&d->data.c)));			//������������׵�ַ
	}
	
	template <class T> class VariantPrivateSharedEx : public Variant::PrivateShared
	{
		public:
			VariantPrivateSharedEx() : Variant::PrivateShared(&m_t) { }
			VariantPrivateSharedEx(const T& t) : Variant::PrivateShared(&m_t), m_t(t) { }
			
		private:
			T m_t;
	};
	//����
	template <class T>
	inline void v_construct(Variant::Private* x, const void* copy, T* = 0)
	{
		//���ݱ���������ʱ��ʹ�ù���ķ�ʽ
		if (sizeof(T) > sizeof(Variant::Private::Data))
		{
			x->data.shared = copy ? new VariantPrivateSharedEx<T>(*static_cast<const T*>(copy))
			  : new VariantPrivateSharedEx<T>;
			x->is_shared = true;
		}
		else
		{
			if (copy)
				new (&x->data.ptr) T(*static_cast<const T*>(copy));		//���ÿ������죬���³�ʼ���ڴ�
			else
				new (&x->data.ptr) T;
		}
	}
	
	template <class T>
	inline void v_construct(Variant::Private* x, const T& t)
	{
		if (sizeof(T) > sizeof(Variant::Private::Data))
		{
			x->data.shared = new VariantPrivateSharedEx<T>(t);	//����ÿ������죬��t����
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
