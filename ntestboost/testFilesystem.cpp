#include "stdafx.h"
#include "testFilesystem.h"
#include "boost/filesystem.hpp"
#include <iostream>
#include <windows.h>

using namespace std;

testFilesystem::testFilesystem()
{
}


testFilesystem::~testFilesystem()
{
}

void testFilesystem::test()
{
	test_path();
}

void testFilesystem::test_path()
{
	using namespace boost::filesystem;
	testConsole::SetTitle(L"测试boost::path");
	testConsole::SetColor(true, true, false, false);

	path dir("c:\\windows");
	dir /= "system32";
	dir /= "services.exe";
	string text = "扩展名";
	wstring wtext = L"扩展名";
	std::cout << dir << std::endl;
	std::cout << dir.extension() << std::endl;
	std::cout << dir.string() << std::endl;					//转换成std::string 类型 
	std::cout << dir.root_name() << std::endl;			//盘符名：C: 
	std::cout << dir.root_directory() << std::endl;		//根目录：”\” 
	std::cout << dir.root_path() << std::endl;			//根路径：”C:\” 
	std::cout << dir.relative_path() << std::endl;		// 相对路径:Windows\System32\services.exe 
	std::cout << dir.parent_path() << std::endl;		//上级目录：C:\Windows\System32 
	std::cout << dir.filename() << std::endl;			//文件名：services.exe 
	std::cout << dir.stem() << std::endl;				//不带扩展的文件名：services 
	std::cout << dir.extension() << std::endl;			//扩展名：.exe 
	std::cout << dir.replace_extension(".txt") << std::endl;			//替换扩展名为txt
	std::cout << basename(dir) << std::endl;					//不带扩展名 services
	std::cout << wtext << extension(dir)<< std::endl;					//扩展名.txt
	std::cout << change_extension(dir, ".exe");
	std::cout <<std::endl << std::endl;

	path path_relative("D:/boost/boost_1_64_0_lib");
	std::cout << path_relative << std::endl;
	wstring ws = is_directory(path_relative) ? wstring( L"是目录") : wstring(L"不是目录");
	std::cout << ws <<path_relative << std::endl;
	path::iterator pathI = path_relative.begin();

	std::cout << std::endl;
	wtext = L"分级目录：";
	std::cout << wtext << std::endl;					//扩展名.txt
	while (pathI != path_relative.end())
	{
		std::cout << *pathI << std::endl;
		++pathI;
	}
	std::cout << std::endl;
	wtext = L"分级结束";
	std::cout << wtext <<::endl;


	std::cout << path_relative.root_path() << std::endl;
	std::cout << path_relative.relative_path() << std::endl;
	std::cout << path_relative.is_absolute() << std::endl;

// 	cout << "原色testCOLOR（没有设置字体颜色）" << endl;
// 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
// 		FOREGROUND_GREEN | FOREGROUND_BLUE);//设置三色相加
// 	cout << "白色testCOLOR（红色绿色蓝色相加）" << endl;
// 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
// 	//设置红色
// 	cout << "红色testCOLOR（设置的颜色为红色）" << endl;
// 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN)
// 		;//设置绿色
// 	cout << "绿色testCOLOR（设置的颜色为绿色）" << endl;
// 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
// 	//设置蓝色
// 	cout << "蓝色testCOLOR（设置的颜色为蓝色）" << endl;
// 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
// 		FOREGROUND_GREEN);//设置红色和绿色相加
// 	cout << "黄色testCOLOR（红色和绿色相加色）" << endl;
// 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
// 		FOREGROUND_BLUE);//设置红色和蓝色相加
// 	cout << "粉色testCOLOR（红色和蓝色相加色）" << endl;
// 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
// 		FOREGROUND_BLUE);//设置绿色和蓝色相加
// 	cout << "青色testCOLOR（绿色和蓝色相加色）" << endl;
// 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	//设置颜色，没有添加颜色，故为原色
	cout << endl;


	path crt("d:\\chencs\\chencs");
	if (!is_directory(crt))
	{
		bool bcrt = create_directories(crt);
	}

	system("pause");
}
