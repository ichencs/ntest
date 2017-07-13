#pragma once
// #include "Pointer.h"

class nvariant
{
public:
	nvariant();
	~nvariant();

public:
	union Data
	{
		char c;
		wchar_t uc;
		unsigned short us;
		int i;
		unsigned int ui;
		long l;
		unsigned long ul;
		bool b;
		double d;
		float f;
		void* ptr;
	};




};

