#include "stdafx.h"
#include "testPod.h"
#include <iostream>
#include <type_traits>
// #include "..\ntestbasic\Console.h"
using namespace vl::console;
using namespace std;

testPod::testPod()
{
	test();
}


testPod::~testPod()
{
}

void testPod::test()
{
	Console::SetColor(true, true, false, true);
	Console::WriteLine(L"??POD~~~~");
	test_trival();
	test_layout();
}

class a
{
		a() {}
};
class b
{
		b(b&) {}
};
// class c { c(c&&) {} };
class d
{
		d operator=(d&) {}
};
// class e { e operator=(e&&) {} };
class fFileAttribute
{
		~fFileAttribute() {}
};
class g
{
		virtual void foo() = 0;
};
class h : g {};
class i {};

void testPod::test_trival()
{
	Console::WriteLine(L"POD1~~~~");
	// 	std::cout << std::is_trivial<a>::value << std::endl;  // ?????????
	// 	std::cout << std::is_trivial<b>::value << std::endl;  // ???????????
	// 	std::cout << std::is_trivial<c>::value << std::endl;  // ????????????
	// 	std::cout << std::is_trivial<d>::value << std::endl;  // ????????????
	// 	std::cout << std::is_trivial<e>::value << std::endl;  // ????????????
	// 	std::cout << std::is_trivial<f>::value << std::endl;  // ?????????
	// 	std::cout << std::is_trivial<g>::value << std::endl;  // ????
	// 	std::cout << std::is_trivial<h>::value << std::endl;  // ????
	//
	// 	std::cout << std::is_trivial<i>::value << std::endl;  // ????
	// 	Console::SetColor(true, true, true	, false);
}

class A
{
	private:
		int a;
	public:
		int b;
};

class B1
{
		static int x1;
};

class B2
{
		int x2;
};

class B : B1, B2
{
		int x;
};

class C1 {};
class C : C1
{
		C1 c;
};

class D
{
		virtual void foo() = 0;
};
class E : D {};
class F
{
		A x;
};

void testPod::test_layout()
{
	// 	Console::SetColor(true, true, false, true);
	Console::WriteLine(L"POD2~~~~");
	// 	std::cout << std::is_standard_layout<A>::value << std::endl;  // ????1???a?b?????????
	// 	std::cout << std::is_standard_layout<B>::value << std::endl;  // ????2???????(?)??????????
	// 	std::cout << std::is_standard_layout<C>::value << std::endl;  // ????3??????????????
	// 	std::cout << std::is_standard_layout<D>::value << std::endl;  // ????4?????
	// 	std::cout << std::is_standard_layout<E>::value << std::endl;  // ????5?????
	// 	std::cout << std::is_standard_layout<F>::value << std::endl;  // ????6??????x?????????
	// 	Console::SetColor(true, true, true, false);
	// 	Console::WriteLine("??POD2~~~~");
}
