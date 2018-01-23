#include "Variant.h"
#include "String.h"
#include "Locale.h"


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
	inline void v_construct(Variant::Private* x, const void* copy/*, T* = 0*/)
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
	
	static void construct(Variant::Private* x, const void* copy)
	{
		x->is_shared = false;
		switch (x->type)
		{
			case vl::Variant::Bool:
				x->data.b = copy ? *static_cast<const bool*>(copy) : false;
				break;
			case vl::Variant::Short:
				x->data.s = copy ? *static_cast<const short*>(copy) : false;
				break;
			case vl::Variant::VInt32_t:
			case vl::Variant::Int:
				x->data.i32 = copy ? *static_cast<const int*>(copy) : 0;
				break;
			case vl::Variant::VUInt32_t:
			case vl::Variant::UInt:
				x->data.ui32 = copy ? *static_cast<const vint32_t*>(copy) : 0u;
				break;
			case vl::Variant::VInt8_t:
				x->data.i8 = copy ? *static_cast<const vint8_t*>(copy) : 0;
				break;
			case vl::Variant::VUInt8_t:
				x->data.ui8 = copy ? *static_cast<const vuint8_t*>(copy) : 0u;
				break;
			case vl::Variant::VInt16:
				x->data.i16 = copy ? *static_cast<const vint16_t*>(copy) : 0;
				break;
			case vl::Variant::VUInt16_t:
				x->data.ui16 = copy ? *static_cast<const vuint16_t*>(copy) : 0u;
				break;
			case vl::Variant::LongLong:
			case vl::Variant::VInt64_t:
				x->data.i64 = copy ? *static_cast<const vint64_t*>(copy) : 0;
				break;
			case vl::Variant::ULongLong:
			case vl::Variant::VUInt64_t:
				x->data.ui64 = copy ? *static_cast<const vuint64_t*>(copy) : 0u;
				break;
			case vl::Variant::Double:
				x->data.d = copy ? *static_cast<const double*>(copy) : 0.0;
				break;
			case vl::Variant::Char:
				x->data.c = copy ? *static_cast<const char*>(copy) : 0;
				break;
			case vl::Variant::WChar:
				x->data.wc = copy ? *static_cast<const wchar_t*>(copy) : 0;
				break;
			case vl::Variant::Float:
				x->data.f = copy ? *static_cast<const float*>(copy) : 0.0f;
				break;
			// 			case vl::Variant::String:
			// 				break;
			case vl::Variant::WString:
				v_construct<WString>(x, copy);
				break;
			case vl::Variant::AString:
				v_construct<AString>(x, copy);
				break;
			case vl::Variant::UString:
				v_construct<UString>(x, copy);
				break;
			case vl::Variant::DateTime:
				v_construct<DateTime>(x, copy);
				break;
			case vl::Variant::Locale:
				v_construct<Locale>(x, copy);
				break;
			default:
				break;
		}
		x->is_null = !copy;
	}
	
	static void clear(Variant::Private* d)
	{
		switch (d->type)
		{
			case vl::Variant::Bool:
			case vl::Variant::Short:
			case vl::Variant::Int:
			case vl::Variant::UInt:
			case vl::Variant::VInt8_t:
			case vl::Variant::VUInt8_t:
			case vl::Variant::VInt16:
			case vl::Variant::VUInt16_t:
			case vl::Variant::VInt32_t:
			case vl::Variant::VUInt32_t:
			case vl::Variant::VInt64_t:
			case vl::Variant::VUInt64_t:
			case vl::Variant::LongLong:
			case vl::Variant::ULongLong:
			case vl::Variant::Double:
			case vl::Variant::Char:
			case vl::Variant::Float:
				break;
			case vl::Variant::WString:
				v_clear<WString>(d);
				break;
			case vl::Variant::AString:
				v_clear<AString>(d);
				break;
			case vl::Variant::UString:
				v_clear<UString>(d);
				break;
			case vl::Variant::DateTime:
				v_clear<DateTime>(d);
				break;
			case vl::Variant::Locale:
				v_clear<Locale>(d);
				break;
		}
		
		d->type = Variant::Invalid;
		d->is_null = true;
		d->is_shared = false;
	}
	
	static bool isNull(const Variant::Private* d)
	{
		//未完成
		return d->is_null;
	}
	
	static bool compare(const Variant::Private* a, const Variant::Private* b)
	{
		switch (a->type)
		{
			case vl::Variant::Invalid:
				return true;
			case vl::Variant::Bool:
				return a->data.b == b->data.b;
			case vl::Variant::Short:
				return a->data.s == b->data.s;
				break;
			case vl::Variant::VInt32_t:
			case vl::Variant::Int:
				return	a->data.i32 == b->data.i32;
			case vl::Variant::VUInt32_t:
			case vl::Variant::UInt:
				return	a->data.ui32 == b->data.ui32;
			case vl::Variant::VInt8_t:
				return	a->data.i8 == b->data.i8;
			case vl::Variant::VUInt8_t:
				return	a->data.ui8 == b->data.ui8;
			case vl::Variant::VInt16:
				return	a->data.i16 == b->data.i16;
			case vl::Variant::VUInt16_t:
				return	a->data.ui16 == b->data.ui16;
			case vl::Variant::VInt64_t:
				return	a->data.i64 == b->data.i64;
			case vl::Variant::VUInt64_t:
				return	a->data.ui64 == b->data.ui64;
			case vl::Variant::LongLong:
				return	a->data.ll == b->data.ll;
			case vl::Variant::ULongLong:
				return	a->data.ull == b->data.ull;
			case vl::Variant::Double:
				return	a->data.d == b->data.d;
			case vl::Variant::Char:
				return	a->data.c == b->data.c;
			case vl::Variant::WChar:
				return	a->data.wc == b->data.wc;
			case vl::Variant::Float:
				return	a->data.f == b->data.f;
			case vl::Variant::WString:
				return *v_cast<WString>(a) == *v_cast<WString>(b);
			case vl::Variant::AString:
				return *v_cast<AString>(a) == *v_cast<AString>(b);
			case vl::Variant::UString:
				return *v_cast<UString>(a) == *v_cast<UString>(b);
			case vl::Variant::DateTime:
				return *v_cast<DateTime>(a) == *v_cast<DateTime>(b);
			case vl::Variant::Locale:
				return *v_cast<Locale>(a) == *v_cast<Locale>(b);
				break;
			default:
				break;
		}
		
		
		const void* a_ptr = a->is_shared ? a->data.shared->ptr : &(a->data.ptr);
		const void* b_ptr = b->is_shared ? b->data.shared->ptr : &(b->data.ptr);
		
		if (a->is_null && b->is_null)
			return true;
			
		return a_ptr == b_ptr;
	}
	
	static bool convert(const Variant::Private* d, Variant::Type t, void* result, bool* ok)
	{
		bool dummy = false;
		if (!ok)
			ok = &dummy;
			
			
			
			
			
		//未完成
		
		return false;
	}
	
	const Variant::Handler qt_kernel_variant_handler =
	{
		construct,
		clear,
		isNull,
		compare,
		convert,
	};
	
	const Variant::Handler* qcoreVariantHandler()
	{
		return &qt_kernel_variant_handler;
	}
	
	
	const Variant::Handler* Variant::handler = &qt_kernel_variant_handler;
	
	
	Variant::Variant(const Variant& other)
	{
	
	}
	
	void* Variant::data()
	{
		detach();
		return const_cast<void*>(constData());
	}
	
	bool Variant::isNull() const
	{
		return false;
	}
	
	void Variant::detach()
	{
		if (!d.is_shared || d.data.shared->ref == 1)
			return;
			
		Private dd;
		dd.type = d.type;
		handler->construct(&dd, constData());
		if (!d.data.shared->ref.deref())
			handler->clear(&d);
		d.data.shared = dd.data.shared;
	}
	
	const void* Variant::constData() const
	{
		return d.is_shared ? d.data.shared->ptr : reinterpret_cast<const void*>(&d.data.ptr);
	}
	
	Variant& Variant::operator=(const Variant& variant)
	{
		if (this == &variant)
			return *this;
			
		clear();
		if (variant.d.is_shared)
		{
			variant.d.data.shared->ref.ref();
			d = variant.d;
		}
		else if (variant.d.type > Char && variant.d.type < UserType)
		{
			d.type = variant.d.type;
			handler->construct(&d, variant.constData());
			d.is_null = variant.d.is_null;
		}
		else
		{
			d = variant.d;
		}
		
		return *this;
	}
	
	Variant::~Variant()
	{
	}
	
	void Variant::clear()
	{
		if ((d.is_shared && !d.data.shared->ref.deref()) || (!d.is_shared && d.type < UserType && d.type > Char))
			handler->clear(&d);
		d.type = Invalid;
		d.is_null = true;
		d.is_shared = false;
	}
	
}
