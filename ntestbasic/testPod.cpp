#include "stdafx.h"
#include "testPod.h"
#include <iostream>
#include <type_traits>
// #include "..\ntestbasic\testConsole.h"

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
	testConsole::SetColor(true, true, false, true);
	testConsole::WriteLine("测试POD~~~~");
	test_trival();
	test_layout();
}

class a { a() {} };
class b { b(b&) {} };
// class c { c(c&&) {} };
class d { d operator=(d&) {} };
// class e { e operator=(e&&) {} };
class f { ~f() {} };
class g { virtual void foo() = 0; };
class h : g {};
class i {};

void testPod::test_trival()
{
	testConsole::WriteLine("POD1~~~~");
// 	std::cout << std::is_trivial<a>::value << std::endl;  // 有不平凡的构造函数  
// 	std::cout << std::is_trivial<b>::value << std::endl;  // 有不平凡的拷贝构造函数  
// 	std::cout << std::is_trivial<c>::value << std::endl;  // 有不平凡的拷贝赋值运算符  
// 	std::cout << std::is_trivial<d>::value << std::endl;  // 有不平凡的拷贝赋值运算符  
// 	std::cout << std::is_trivial<e>::value << std::endl;  // 有不平凡的移动赋值运算符  
// 	std::cout << std::is_trivial<f>::value << std::endl;  // 有不平凡的析构函数  
// 	std::cout << std::is_trivial<g>::value << std::endl;  // 有虚函数  
// 	std::cout << std::is_trivial<h>::value << std::endl;  // 有虚基类  
// 
// 	std::cout << std::is_trivial<i>::value << std::endl;  // 平凡的类  
// 	testConsole::SetColor(true, true, true	, false);
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

class D { virtual void foo() = 0; };
class E : D {};
class F { A x; };	

void testPod::test_layout()
{
// 	testConsole::SetColor(true, true, false, true);
	testConsole::WriteLine("POD2~~~~");
// 	std::cout << std::is_standard_layout<A>::value << std::endl;  // 违反定义1。成员a和b具有不同的访问权限  
// 	std::cout << std::is_standard_layout<B>::value << std::endl;  // 违反定义2。继承树有两个(含)以上的类有非静态成员  
// 	std::cout << std::is_standard_layout<C>::value << std::endl;  // 违反定义3。第一个非静态成员是基类类型  
// 	std::cout << std::is_standard_layout<D>::value << std::endl;  // 违反定义4。有虚函数  
// 	std::cout << std::is_standard_layout<E>::value << std::endl;  // 违反定义5。有虚基类  
// 	std::cout << std::is_standard_layout<F>::value << std::endl;  // 违反定义6。非静态成员x不符合标准布局类型  
// 	testConsole::SetColor(true, true, true, false);
// 	testConsole::WriteLine("结束POD2~~~~");
}
