// nicetest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>
#include <vector>

// #undef DEBUG
// #pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
// #endif

using namespace std;
using namespace vl::unittest;


int main(int, char*)
{

	vector<double> dval;
	dval.push_back(0.25);
	
	double dval2 = *dval.end();
	
	UnitTest::RunAndDisposeTests();
	
	// 	system("pause");
	return 0;
}

