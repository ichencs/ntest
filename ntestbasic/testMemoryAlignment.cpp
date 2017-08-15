#include "StdAfx.h"
#include "testMemoryAlignment.h"
#include <iostream>
#include <stddef.h>

using namespace std;
testMemoryAlignment::testMemoryAlignment()
{
}


testMemoryAlignment::~testMemoryAlignment()
{
}

void testMemoryAlignment::test()
{
	MemoryA sa;
	cout << sizeof(sa) << endl;
	cout << "&sa.a = " << &sa.a << endl;
	cout << "&sa.b = " << &sa.b << endl;
	cout << "&sa.c = " << &sa.c << endl;
	cout << "&sa.d = " << &sa.d << endl;
	cout << "&sa.e = " << &sa.e << endl;


	cout << "offsetof(MemoryA, a) = " << offsetof(MemoryA, a) << endl;
	cout << "offsetof(MemoryA, b) = " << offsetof(MemoryA, b) << endl;
	cout << "offsetof(MemoryA, c) = " << offsetof(MemoryA, c) << endl;
	cout << "offsetof(MemoryA, d) = " << offsetof(MemoryA, d) << endl;
	cout << "offsetof(MemoryA, e) = " << offsetof(MemoryA, e) << endl;

	MemoryB sb;
	cout << sizeof(sb) << endl;
	cout << "&sa.a = " << &sb.a << endl;
	cout << "&sa.b = " << &sb.b << endl;
	cout << "&sa.c = " << &sb.c << endl;
	cout << "&sa.d = " << &sb.d << endl;
	cout << "&sa.e = " << &sb.e << endl;

	cout << "offsetof(MemoryB, a) = " << offsetof(MemoryB, d) << endl;
	cout << "offsetof(MemoryB, b) = " << offsetof(MemoryB, b) << endl;
	cout << "offsetof(MemoryB, c) = " << offsetof(MemoryB, a) << endl;
	cout << "offsetof(MemoryB, d) = " << offsetof(MemoryB, c) << endl;
	cout << "offsetof(MemoryB, e) = " << offsetof(MemoryB, e) << endl;

	MemoryC sc;
	cout << sizeof(sc) << endl;
	cout << "&sa.a = " << &sc.a << endl;
	cout << "&sa.b = " << &sc.b << endl;
	cout << "&sa.c = " << &sc.c << endl;
	cout << "&sa.d = " << &sc.d << endl;
	cout << "&sa.e = " << &sc.e << endl;

	cout << "offsetof(MemoryC, a) = " << offsetof(MemoryC, a) << endl;
	cout << "offsetof(MemoryC, b) = " << offsetof(MemoryC, c) << endl;
	cout << "offsetof(MemoryC, c) = " << offsetof(MemoryC, e) << endl;
	cout << "offsetof(MemoryC, d) = " << offsetof(MemoryC, b) << endl;
	cout << "offsetof(MemoryC, e) = " << offsetof(MemoryC, d) << endl;

}
