#pragma once
#include "Basic.h"
#include "AtomicInt.h"

namespace vl
{
	class Variant:
		public Object
	{
		public:
			enum Type
			{
				Invalid = 0,
				
				Bool,
				Short,
				Int,
				UInt,
				VInt8_t,
				VUInt8_t,
				VInt16,
				VUInt16_t,
				VInt32_t,
				VUInt32_t,
				VInt64_t,
				VUInt64_t,
				
				LongLong,
				ULongLong,
				Double,
				Char,
				WChar,
				Float,
				// 				String,
				WString,
				AString,
				UString,
				DateTime,
				Locale,
				
				UserType = 127,			//暂时不支持
				
			};
		public:
			inline Variant() {};
			~Variant();
			Variant(const Variant& other);
			Variant& operator=(const Variant& other);
			
			
			struct PrivateShared
			{
				inline PrivateShared(void* v) : ptr(v), ref(1) { };		//未写虚析构，释放内存时，需要static_cast转换类型
				void* ptr;
				AtomicInt ref;
			};
			
			struct Private
			{
				inline Private() : type(Invalid), is_shared(false), is_null(true)
				{
					data.ptr = 0;
				}
				inline Private(const Private& other)
					: data(other.data), type(other.type),
					  is_shared(other.is_shared), is_null(other.is_null)
				{}
				union Data
					{
					  bool b;
					  char c;
					  short s;
					  wchar_t wc;
					  vint8_t i8;
					  vuint8_t ui8;
					  
					  vint16_t i16;
					  vuint16_t ui16;
					  
					  int i;
					  vint32_t i32;
					  vuint32_t ui32;
					  
					  vint64_t i64;
					  vuint64_t ui64;
					  
					  double d;
					  float f;
					  long long ll;
					  unsigned long long ull;
					  Object* o;
					  void* ptr;
					  PrivateShared* shared;
					} data;
				vuint type : 30;
				vuint is_shared : 1;
				vuint is_null : 1;
			};
			
			typedef void(*f_construct)(Private*, const void*);
			typedef void(*f_clear)(Private*);
			typedef bool(*f_null)(const Private*);
			typedef bool(*f_compare)(const Private*, const Private*);
			typedef bool(*f_convert)(const Variant::Private* d, Type t, void*, bool*);
			typedef bool(*f_canConvert)(const Variant::Private* d, Type t);
			struct Handler
			{
				f_construct construct;
				f_clear clear;
				f_null isNull;
				f_compare compare;
				f_convert convert;
				// 				f_canConvert canConvert;
			};
			void Variant::clear();
		protected:
			Private d;
			static const Handler* handler;
			
			void* data();
			const void* constData() const;
			inline const void* data() const
			{
				return constData();
			}
			
			inline bool isValid() const;
			bool isNull() const;
			
			void detach();
			inline bool isDetached() const;
			
	};
	inline bool Variant::isValid() const
	{
		return d.type != Invalid;
	}
	inline bool Variant::isDetached() const
	{
		return !d.is_shared || d.data.shared->ref == 1;
	}
	
	
}

