#pragma once
#include "Basic.h"
#include "AtomicInt.h"

namespace vl
{

#define COMPARE_EXCHANGE_POINTER(value, newValue, expectedValue)\
	(_InterlockedCompareExchangePointer((void * volatile *)(value),\
	    (void *)(newValue), \
	    (void *)(expectedValue)))

#define EXCHANGE_POINTER(value, newValue)\
	(_InterlockedExchangePointer( \
	    (void * volatile *)(value), \
	    (void *) (newValue))

#define 	EXCHANGE_ADD_POINTER(value, valueToAdd) \
	(_InterlockedExchangeAdd64((void * volatile *)(value),(valueToAdd)))
	// #define EXCHG(x)	(_InterlockedDecrement64(x))
	// #define EXCHGADD() ()
	
	
	class Variant:
		public Object
	{
		public:
			enum Type
			{
				Invalid = 0,
				Bool,
				
				Int8,
				UInt8,
				Int16,
				UInt16,
				Int32,
				UInt32,
				Int64,	//8*8		long long
				UInt64,
				Double,		//8*8
				Float,		//4*8
				
				WChar,
				Char,
				
				AString,
				// 				UString,	//
				WString,
				DateTime,
				Locale,
				
				UserType = 127,			//暂时不支持
				
			};
		public:
			inline Variant() {};
			~Variant();
			Variant(Variant::Type type);
			Variant(const Variant& other);
			Variant& operator=(const Variant& other);
			Variant(vint8_t i);			//8
			Variant(vint16_t i);			//8
			Variant(vint32_t i);			//32
			Variant(vint64_t i);			//8
			// 			Variant(vint i);
			// 			Variant(int i);			//32
			// 			Variant(long long i);
			
			
		public:		//内部类型定义
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
					  wchar_t wc;
					  vint8_t i8;
					  vuint8_t ui8;
					  
					  vint16_t i16;			//short
					  vuint16_t ui16;
					  
					  vint32_t i32;			//int
					  vuint32_t ui32;
					  
					  vint64_t i64;			//long
					  vuint64_t ui64;		//long
					  
					  double d;
					  float f;
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
		protected:
			void Variant::clear();
			void create(int type, const void* copy);
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

