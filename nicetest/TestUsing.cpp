#include "StdAfx.h"
#include "TestUsing.h"


TestUsing::TestUsing()
{
}


TestUsing::~TestUsing()
{
}

void TestUsing::Test()
{
	Base b;
	Derived d;
	b.menfcn();
	d.menfcn();//���ȥ��Derived���е�using����������ִ���error C2660: 'Derived::menfcn' : function does not take 0 arguments      
	d.menfcn(123);
}
