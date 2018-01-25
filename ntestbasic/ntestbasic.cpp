// ntest.cpp : �������̨Ӧ�ó������ڵ㡣
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
	return GetExePath() + L"/../../Resources/";
#else
	return GetExePath() + L"/../Resources/";
#endif
}

WString GetTestOutputPath()
{
#ifdef _WIN64
	return GetExePath() + L"/../../Output/";
#else
	return GetExePath() + L"/../Output/";
#endif
}

#define CalculateSize(type)\
	{	   \
		WString strLine = wformat(L"%s����ռ %d �ֽ�",L_(#type),sizeof(type));\
		vl::console::Console::WriteLine(strLine);	\
	}		\


inline bool ref()
{
	DWORD d = 7;
	
}

int main()
{
	{
		CalculateSize(short);
		CalculateSize(float);
		CalculateSize(double);
		CalculateSize(char);
		CalculateSize(wchar_t);
		CalculateSize(void*);
		
		CalculateSize(int);
		CalculateSize(long);
		CalculateSize(unsigned int);
		CalculateSize(unsigned long long);
		
		double d1 = -0.0;
		double d2 = 0.0;
		
		bool bRes = d1 < 0;
		bRes = qIsNull(0.000000000001);
		vuint64_t vi = 0x7fffffffffffffffi64;
		
		
		using namespace filesystem;
		WString strPath = GetTestOutputPath();
		Folder folder(strPath);
		vl::console::Console::WriteLine(folder.GetFilePath().GetFullPath());
		
		if (!folder.Exists())
		{
			TEST_ASSERT(folder.Create(false) == true);
		}
	}
	UnitTest::RunAndDisposeTests();
	FinalizeGlobalStorage();
	
	// 	_CrtDumpMemoryLeaks();
	return 0;
}

