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


int main()
{
	{
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

