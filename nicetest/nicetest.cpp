// nicetest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
// #include <boost/lambda/lambda.hpp>

#include "test_calculate.h"
// #include "boost_asio.h"
#include <memory>
#include <iostream>
#include "Bloger.h"
#include "testNice.h"
#include <cmath>
#include "testAes.h"
#include "TestUsing.h"
#include "UnitTest.h"

using namespace std;


int main()
{
	UnitTest::RunAndDisposeTests();
	
	system("pause");
	return 0;
}

