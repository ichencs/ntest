#include "StdAfx.h"
#include "TestUsing.h"

using namespace vl::unittest;


TEST_CASE(TestUsing)
{
	using namespace TestUsing;
	
	Base b;
	Derived d;
	b.menfcn();
	d.menfcn();//���ȥ��Derived���е�using����������ִ���error C2660: 'Derived::menfcn' : function does not take 0 arguments
	d.menfcn(123);
	
}
