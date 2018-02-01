#pragma once
#include "Basic.h"
#include "AtomicInt.h"
#include "String.h"

namespace vl
{
	/*!
	 * \class: 	Variant
	 *
	 * \ingroup GroupName
	 *
	 * \brief:
	 *
	 * TODO: 	新定义类型：
	 *			1.该类型支持拷贝相关操作
	 *			2.Type中添加定义
	 *			3.construct函数支持
	 *			4.clear函数支持
	 *			5.compare函数支持
	 *			6.convert函数支持（检查）
	 *			7.Variant构造支持
	 *
	 * \note:
	 *
	 * \author:	Chencs
	 *
	 * \version:1.0
	 *
	 * \date: 2018/01/26
	 *
	 * Contact: chencs@thinkerinfo.com
	 *
	 */
	class Variant;
	class Locale;
	
	class Variant:
		public Object
	{
		public:
			enum Type
			{
				Invalid = 0,
				Bool,
				
				Int32,
				UInt32,
				Int64,	//8*8		long long
				UInt64,
				Double,		//8*8
				Float,		//4*8
				
				WChar,
				// 				Char,	//统一由WChar存储
				
				Astring,
				Wstring,
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
			
			Variant(vint32_t i);			//32
			Variant(vint64_t i);			//8
			
			Variant(vuint32_t u);
			Variant(vuint64_t u);
			
			Variant(char c);		//存储为wchar_t
			Variant(wchar_t wc);
			Variant(float f);
			Variant(double d);
			Variant(bool val);
			Variant(char* val);
			Variant(wchar_t* val);
			Variant(vl::AString val);
			Variant(vl::WString val);
			Variant(vl::Locale val);
			Variant(vl::DateTime val);
			
			inline bool operator==(const Variant& v) const
			{
				return cmp(v);
			}
			inline bool operator!=(const Variant& v) const
			{
				return !cmp(v);
			}
			
		public:		//转换
			vl::AString toAString(bool* ok = NULL)const;
			vl::WString toWString(bool* ok = NULL)const;
			int toInt(bool* ok = NULL)const
			{
				return toInt32(ok);
			};
			vl::vint32_t toInt32(bool* ok = NULL)const;
			vl::vuint32_t toUInt32(bool* ok = NULL)const;
			vl::vint64_t toInt64(bool* ok = NULL)const;
			vl::vuint64_t toUInt64(bool* ok = NULL)const;
			char toChar(bool* ok = NULL)const;
			wchar_t toWChar(bool* ok = NULL)const;
			double toDouble(bool* ok = NULL)const;
			bool toBool(bool* ok = NULL)const;
			
			vl::Variant type();
			
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
					data.ptr = NULL;
				}
				explicit Private(vuint variantType)
					: type(variantType), is_shared(false), is_null(false)
				{}
				
				inline Private(const Private& other)
					: data(other.data), type(other.type),
					  is_shared(other.is_shared), is_null(other.is_null)
				{}
				union Data
					{
					  bool b;
					  // 					  char c;
					  wchar_t c;
					  
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
			bool cmp(const Variant& other) const;
		protected:
			Private d;
			static const Handler* handler;
			
		public:
			void* data();
			const void* constData() const;
			inline const void* data() const
			{
				return constData();
			}
			bool convert(Variant::Type t);
			bool canConvert(Type t) const;
			
			void detach();
		public:	//判断
			inline bool isValid() const;
			bool isNull() const;
			inline bool isDetached() const;
			inline bool isInt()const;	//int
			inline bool isUInt()const;	//unsinged int
			inline bool isFloatingPoint()const;	//Float double
			inline bool isNumber()const;
			inline bool isChar()const;
			inline bool isWChar()const;
			inline bool isDatetime()const;
			inline bool isLocal()const;
			inline bool isAString()const;
			inline bool isWString()const;
			inline bool isString()const;
			inline bool isBool()const;
	};
	inline bool Variant::isValid() const
	{
		return d.type != Variant::Invalid;
	}
	inline bool Variant::isDetached() const
	{
		return !d.is_shared || d.data.shared->ref == 1;
	}
	
	inline bool Variant::isInt()const
	{
		return d.type == Variant::Int32 || d.type == Variant::Int64;
	}
	
	inline bool Variant::isUInt()const
	{
		return d.type == Variant::UInt32 || d.type == Variant::UInt64;
	}
	
	inline bool Variant::isFloatingPoint()const
	{
		return d.type == Variant::Float || d.type == Variant::Double;
	}
	
	inline bool Variant::isNumber()const
	{
		return isInt() || isUInt() || isFloatingPoint();
	}
	
	inline bool Variant::isChar()const
	{
		return isWChar();
	}
	
	inline bool Variant::isWChar()const
	{
		return d.type == Variant::WChar;
	}
	
	inline bool Variant::isDatetime()const
	{
		return d.type == Variant::DateTime;
	}
	
	inline bool Variant::isLocal()const
	{
		return d.type == Variant::Locale;
	}
	inline bool Variant::isAString()const
	{
		return d.type == Variant::Astring;
	}
	inline bool Variant::isWString()const
	{
		return d.type == Variant::Wstring;
	}
	inline bool Variant::isString()const
	{
		return isAString() || isWString();
	}
	inline bool Variant::isBool()const
	{
		return d.type == Variant::Bool;
	}
}

