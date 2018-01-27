#include "Variant.h"
#include "String.h"
#include "Locale.h"
#include <stdlib.h>


namespace vl
{
#define DBL_DIG          15                      // # of decimal digits of precision
#define FLT_DIG          6                       // # of decimal digits of precision

	static vint64_t MetaTypeNumber(const Variant::Private* d)
	{
		switch (d->type)
		{
			// 			case Variant::Int8:
			// 				return d->data.i16;
			// 			case Variant::Int16:
			// 				return d->data.i16;
			case Variant::Int32:
				return d->data.i32;
			case Variant::Int64:
				return d->data.i32;
			case Variant::Float:
				return qRound64(d->data.f);
			case Variant::Double:
				return qRound64(d->data.d);
			case Variant::Char:
				return vint(d->data.c);
			case Variant::WChar:
				return d->data.wc;
		}
		CHECK_ERROR(false, L"MetaTypeNumber::value type error!");
		return 0;
	}
	
	static vuint64_t MetaTypeUNumber(const Variant::Private* d)
	{
		switch (d->type)
		{
			// 			case Variant::UInt8:
			// 				return d->data.ui16;
			// 			case Variant::UInt16:
			// 				return d->data.ui16;
			case Variant::UInt32:
				return d->data.ui32;
			case Variant::UInt64:
				return d->data.ui64;
		}
		CHECK_ERROR(false, L"MetaTypeUNumber::value type error!");
		return 0;
	}
	
	
	
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
			// 			case vl::Variant::Int8:
			// 				x->data.i8 = copy ? *static_cast<const vint8_t*>(copy) : 0;
			// 				break;
			// 			case vl::Variant::UInt8:
			// 				x->data.ui8 = copy ? *static_cast<const vuint8_t*>(copy) : 0u;
			// 				break;
			// 			case vl::Variant::Int16:
			// 				x->data.i16 = copy ? *static_cast<const vint16_t*>(copy) : 0;
			// 				break;
			// 			case vl::Variant::UInt16:
			// 				x->data.ui16 = copy ? *static_cast<const vuint16_t*>(copy) : 0u;
			// 				break;
			case vl::Variant::Int32:
				x->data.i32 = copy ? *static_cast<const vint32_t*>(copy) : 0;
				break;
			case vl::Variant::UInt32:
				x->data.ui32 = copy ? *static_cast<const vuint32_t*>(copy) : 0;
				break;
			case vl::Variant::Int64:
				x->data.i64 = copy ? *static_cast<const vint64_t*>(copy) : 0;
				break;
			case vl::Variant::UInt64:
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
			case vl::Variant::Wstring:
				v_construct<WString>(x, copy);
				break;
			case vl::Variant::Astring:
				v_construct<AString>(x, copy);
				break;
			// 			case vl::Variant::UString:
			// 				v_construct<UString>(x, copy);
			// 				break;
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
			// 			case vl::Variant::Int8:
			// 			case vl::Variant::UInt8:
			// 			case vl::Variant::Int16:
			// 			case vl::Variant::UInt16:
			case vl::Variant::Int32:
			case vl::Variant::UInt32:
			case vl::Variant::Int64:
			case vl::Variant::UInt64:
			case vl::Variant::Double:
			case vl::Variant::Char:
			case vl::Variant::Float:
				break;
			case vl::Variant::Wstring:
				v_clear<WString>(d);
				break;
			case vl::Variant::Astring:
				v_clear<AString>(d);
				break;
			// 			case vl::Variant::UString:
			// 				v_clear<UString>(d);
			// 				break;
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
			case vl::Variant::Int32:
				return	a->data.i32 == b->data.i32;
			case vl::Variant::UInt32:
				return	a->data.ui32 == b->data.ui32;
			// 			case vl::Variant::Int8:
			// 				return	a->data.i8 == b->data.i8;
			// 			case vl::Variant::UInt8:
			// 				return	a->data.ui8 == b->data.ui8;
			// 			case vl::Variant::Int16:
			// 				return	a->data.i16 == b->data.i16;
			// 			case vl::Variant::UInt16:
			// 				return	a->data.ui16 == b->data.ui16;
			case vl::Variant::Int64:
				return	a->data.i64 == b->data.i64;
			case vl::Variant::UInt64:
				return	a->data.ui64 == b->data.ui64;
			case vl::Variant::Double:
				return	a->data.d == b->data.d;
			case vl::Variant::Char:
				return	a->data.c == b->data.c;
			case vl::Variant::WChar:
				return	a->data.wc == b->data.wc;
			case vl::Variant::Float:
				return	a->data.f == b->data.f;
			case vl::Variant::Wstring:
				return *v_cast<WString>(a) == *v_cast<WString>(b);
			case vl::Variant::Astring:
				return *v_cast<AString>(a) == *v_cast<AString>(b);
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
	
	template <typename T>
	inline T VariantToHelper(const Variant::Private& d, Variant::Type t,
	  const Variant::Handler* handler, T* = 0)
	{
		if (d.type == t)
			return *v_cast<T>(&d);
			
		T ret;
		handler->convert(&d, t, &ret, 0);
		return ret;
	}
	
	//转换
	static bool convert(const Variant::Private* d, Variant::Type t, void* result, bool* ok)
	{
		bool dummy = false;
		if (!ok)
			ok = &dummy;
		switch (t)
		{
			case vl::Variant::Invalid:
				break;
			case vl::Variant::Bool:
			
				break;
			// 			case vl::Variant::Int8:
			// 				break;
			// 			case vl::Variant::UInt8:
			// 				break;
			// 			case vl::Variant::Int16:
			// 				break;
			// 			case vl::Variant::UInt16:
			// 				break;
			case vl::Variant::Int32:
				break;
			case vl::Variant::UInt32:
				break;
			case vl::Variant::Int64:
				break;
			case vl::Variant::UInt64:
				break;
			case vl::Variant::Double:
				break;
			case vl::Variant::Char:
				break;
			case vl::Variant::WChar:
				break;
			case vl::Variant::Float:
				break;
			case vl::Variant::Wstring:
				{
					WString* wstr = static_cast<WString*>(result);
					switch (d->type)
					{
						case vl::Variant::Bool:
							*wstr = d->data.b ? L"true" : L"false";
							break;
						case vl::Variant::Int32:
							{
								wchar_t buffer[100];
								_itow_s(d->data.i32, buffer, sizeof(buffer) / sizeof(*buffer), 10);
								*wstr = buffer;
							}
							break;
						case vl::Variant::Int64:
							{
								*wstr = i64tow(d->data.i64);
							}
							break;
						case vl::Variant::UInt32:
							{
								wchar_t buffer[100];
								_ultow_s(d->data.i32, buffer, sizeof(buffer) / sizeof(*buffer), 10);
								*wstr = buffer;
							}
							break;
						case vl::Variant::UInt64:
							{
								*wstr = u64tow(d->data.ui64);
							}
							break;
						case vl::Variant::Double:
							{
								*wstr = ftow(d->data.d);
							}
							break;
						case vl::Variant::Char:
							break;
						case vl::Variant::WChar:
							break;
						case vl::Variant::Float:
							{
								*wstr = ftow(d->data.f);
							}
							break;
						case vl::Variant::Astring:
							{
								*wstr = atow(*v_cast<vl::AString>(d));
							}
							break;
						// 						case vl::Variant::UString:
						// 							break;
						case vl::Variant::DateTime:
							break;
						case vl::Variant::Locale:
							break;
						case vl::Variant::UserType:
							break;
							
						default:
							break;
					}
				}
				break;
			case vl::Variant::Astring:
				break;
			// 			case vl::Variant::UString:
			// 				break;
			case vl::Variant::DateTime:
				break;
			case vl::Variant::Locale:
				break;
			case vl::Variant::UserType:
				break;
			default:
				break;
		}
		
		
		
		
		
		//未完成
		
		return false;
	}
	
	static vint64_t ConvertToNumber(const Variant::Private* d, bool* ok)
	{
		*ok = true;
		
		switch (d->type)
		{
			// 			case Variant::UString:
			case Variant::Astring:
				return atoi64_test(*v_cast<AString>(d), *ok);
			case Variant::Wstring:
				return wtoi64_test(*v_cast<WString>(d), *ok);
			case Variant::Char:
			case Variant::WChar:
			case Variant::Bool:
			case Variant::Double:
			case Variant::Float:
			// 			case Variant::Int8:
			// 			case Variant::Int16:
			case Variant::Int32:
			case Variant::Int64:
				return MetaTypeNumber(d);
			// 			case Variant::UInt8:
			// 			case Variant::UInt16:
			case Variant::UInt32:
			case Variant::UInt64:
				return MetaTypeUNumber(d);
		}
		
		*ok = false;
		return Q_INT64_C(0);
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
	
	
	void Variant::create(int type, const void* copy)
	{
		d.type = type;
		handler->construct(&d, copy);
	}
	
	const Variant::Handler* Variant::handler = &qt_kernel_variant_handler;
	
	
	Variant::Variant(const Variant& other)
		: d(other.d)
	{
		if (d.is_shared)
		{
			d.data.shared->ref.ref();
		}
		else if (other.d.type > Variant::Char && other.d.type < Variant::UserType)
		{
			handler->construct(&d, other.constData());
		}
	}
	
	Variant::Variant(Variant::Type type)
	{
		create(type, 0);
	}
	
	//为了提高效率，常用简单类型的相关构造未调用construct
	
	Variant::Variant(vint32_t i)
		: d(Int32)
	{
		d.data.i32 = i;
	}
	
	Variant::Variant(vint64_t i)
		: d(Int64)
	{
		d.data.i64 = i;
	}
	
	
	Variant::Variant(vuint32_t u)
		: d(UInt32)
	{
		d.data.ui32 = u;
	}
	
	Variant::Variant(vuint64_t u)
		: d(UInt64)
	{
		d.data.ui64 = u;
	}
	
	Variant::Variant(char c)
		: d(Char)
	{
		d.data.c = c;
	}
	
	Variant::Variant(wchar_t wc)
		: d(WChar)
	{
		d.data.wc = wc;
	}
	
	Variant::Variant(float f)
		: d(Float)
	{
		d.data.f = f;
	}
	
	Variant::Variant(double d)
		: d(Double)
	{
		this->d.data.d = d;
	}
	
	Variant::Variant(bool val)
		: d(Bool)
	{
		this->d.data.b = val;
	}
	
	Variant::Variant(vl::AString val)
		: d(Variant::Astring)
	{
		v_construct<vl::AString>(&d, val);
	}
	
	Variant::Variant(vl::WString val)
		: d(Variant::Wstring)
	{
		v_construct<vl::WString>(&d, val);
	}
	
	Variant::Variant(vl::Locale val)
		: d(Variant::Locale)
	{
		v_construct<vl::Locale>(&d, val);
	}
	
	Variant::Variant(vl::DateTime val)
		: d(Variant::DateTime)
	{
		v_construct <vl::DateTime> (&d, val);
	}
	
	Variant::Variant(char* val)
	{
		vl::AString astr = val;
		create(Variant::Astring, &astr);
	}
	
	Variant::Variant(wchar_t* val)
	{
		vl::WString wstr = val;
		create(Variant::Wstring, &wstr);
	}
	
	vl::AString Variant::toAString(bool* ok /*= 0*/)
	{
		return VariantToHelper<AString>(d, Astring, handler);
	}
	
	void* Variant::data()
	{
		detach();
		return const_cast<void*>(constData());
	}
	
	bool Variant::isNull() const
	{
		//未完成
		return d.is_null;
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
	
	Variant& Variant::operator=(const Variant& other)
	{
		if (this == &other)
			return *this;
			
		clear();
		if (other.d.is_shared)
		{
			other.d.data.shared->ref.ref();
			d = other.d;
		}
		else if (other.d.type > Variant::Char && other.d.type < Variant::UserType)
		{
			d.type = other.d.type;
			handler->construct(&d, other.constData());
			d.is_null = other.d.is_null;
		}
		else
		{
			d = other.d;
		}
		return *this;
	}
	
	Variant::~Variant()
	{
		if ((d.is_shared && !d.data.shared->ref.deref()) || (!d.is_shared && d.type > Char && d.type < UserType))
			handler->clear(&d);
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
