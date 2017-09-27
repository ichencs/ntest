#ifndef NICE_NVARIANT_H
#define NICE_NVARIANT_H


#include <string>
#include "Basic.h"
#include "Pointer.h"
using namespace vl;

typedef signed char  nschar;
typedef unsigned long nulong;

class NVariant
{
 public:
	NVariant();
	~NVariant();
 public:
	enum Type
	{
		Invalid = -1,
		Bool,
		Int,
		UInt,
		LongLong,
		Float,
		Double,
		StdString,
		ColorRef,
		DataTime,
		WString,
		AString,
		
	};
	
 public:
 
	struct PrivateShared
	{
		inline PrivateShared(void* v) : ptr(v)
		{
			if (ref)
			{
				Inc();
			}
			else
			{
				ref = new vint(1);
			}
		}
		~PrivateShared()
		{
			Dec();
		}
		void Inc()const
		{
			if (ref)
			{
				INCRC(ref);
			}
		}
		void Dec()const
		{
			if (ref)
			{
				if (DECRC(ref) == 0)
				{
					delete ref;
				}
			}
		}
		void* ptr;
		volatile vint*		ref;
	};
	
	struct Private
	{
		union Data
		{
			bool b;
			char c;
			nschar sc;
			
			wchar_t uc;
			short s;
			nschar us;
			int i;
			vuint ui;
			long l;
			nulong ul;
			float f;
			double d;
			void* ptr;
			// 			unsigned long dw;	//DWORD
			
			PrivateShared* shared;
		} data;
		vuint type : 30;
		bool is_null : 1;
		bool is_shared : 1;
		
	};
	
 public:
	Private d;
	
	
	
};

#endif