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
	testConsole::WriteLine("����POD~~~~");
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
// 	std::cout << std::is_trivial<a>::value << std::endl;  // �в�ƽ���Ĺ��캯��  
// 	std::cout << std::is_trivial<b>::value << std::endl;  // �в�ƽ���Ŀ������캯��  
// 	std::cout << std::is_trivial<c>::value << std::endl;  // �в�ƽ���Ŀ�����ֵ�����  
// 	std::cout << std::is_trivial<d>::value << std::endl;  // �в�ƽ���Ŀ�����ֵ�����  
// 	std::cout << std::is_trivial<e>::value << std::endl;  // �в�ƽ�����ƶ���ֵ�����  
// 	std::cout << std::is_trivial<f>::value << std::endl;  // �в�ƽ������������  
// 	std::cout << std::is_trivial<g>::value << std::endl;  // ���麯��  
// 	std::cout << std::is_trivial<h>::value << std::endl;  // �������  
// 
// 	std::cout << std::is_trivial<i>::value << std::endl;  // ƽ������  
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
// 	std::cout << std::is_standard_layout<A>::value << std::endl;  // Υ������1����Աa��b���в�ͬ�ķ���Ȩ��  
// 	std::cout << std::is_standard_layout<B>::value << std::endl;  // Υ������2���̳���������(��)���ϵ����зǾ�̬��Ա  
// 	std::cout << std::is_standard_layout<C>::value << std::endl;  // Υ������3����һ���Ǿ�̬��Ա�ǻ�������  
// 	std::cout << std::is_standard_layout<D>::value << std::endl;  // Υ������4�����麯��  
// 	std::cout << std::is_standard_layout<E>::value << std::endl;  // Υ������5���������  
// 	std::cout << std::is_standard_layout<F>::value << std::endl;  // Υ������6���Ǿ�̬��Աx�����ϱ�׼��������  
// 	testConsole::SetColor(true, true, true, false);
// 	testConsole::WriteLine("����POD2~~~~");
}
