// nicetest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>

// #undef DEBUG
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
// #endif

using namespace std;
using namespace vl::unittest;


int main(int, char*)
{
	UnitTest::RunAndDisposeTests();
	
	system("pause");
	return 0;
}

