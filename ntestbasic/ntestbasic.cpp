// ntest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <windows.h>
#include <vld.h>

WString GetExePath()
{
	using namespace vl::filesystem;
	FilePath path = FilePath::ModulePath().GetFolder();
	return path.GetFullPath();
}

WString GetTestResourcePath()
{
#ifdef _WIN64
	return GetExePath() + L"../../Resources/";
#else
	return GetExePath() + L"../Resources/";
#endif
}

WString GetTestOutputPath()
{
#ifdef _WIN64
	return GetExePath() + L"../../Output/";
#else
	return GetExePath() + L"../Output/";
#endif
}

class testClass
{
public:
	testClass();
	~testClass();

private:

};

testClass::testClass()
{
}

testClass::~testClass()
{
}

int main()
{
// 	vint num = 3;
// 	num = sizeof(nAtomicInt);
// 	int size1 = sizeof(int);
// 	int size2 = sizeof(Object);
// 
// 	new(&num)vint(12);

	{
		using namespace filesystem;
		Folder folder(GetTestOutputPath());
		
		if (!folder.Exists())
		{
			TEST_ASSERT(folder.Create(false) == true);
		}
	}
	UnitTest::RunAndDisposeTests();
	FinalizeGlobalStorage();

//  	_CrtDumpMemoryLeaks();
	return 0;
}

