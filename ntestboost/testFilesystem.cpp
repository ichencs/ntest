#include "stdafx.h"
#include "testFilesystem.h"
#include "boost/filesystem.hpp"
#include <iostream>
#include <windows.h>

using namespace std;

testFilesystem::testFilesystem()
{
	test();
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
	testConsole::SetTitle(L"����boost::path");
	testConsole::SetColor(true, true, false, false);

	path dir("c:\\windows");
	dir /= "system32";
	dir /= "services.exe";
	string text = "��չ��";
	wstring wtext = L"��չ��";
	std::cout << dir << std::endl;
	std::cout << dir.extension() << std::endl;
	std::cout << dir.string() << std::endl;					//ת����std::string ���� 
	std::cout << dir.root_name() << std::endl;			//�̷�����C: 
	std::cout << dir.root_directory() << std::endl;		//��Ŀ¼����\�� 
	std::cout << dir.root_path() << std::endl;			//��·������C:\�� 
	std::cout << dir.relative_path() << std::endl;		// ���·��:Windows\System32\services.exe 
	std::cout << dir.parent_path() << std::endl;		//�ϼ�Ŀ¼��C:\Windows\System32 
	std::cout << dir.filename() << std::endl;			//�ļ�����services.exe 
	std::cout << dir.stem() << std::endl;				//������չ���ļ�����services 
	std::cout << dir.extension() << std::endl;			//��չ����.exe 
	std::cout << dir.replace_extension(".txt") << std::endl;			//�滻��չ��Ϊtxt
	std::cout << basename(dir) << std::endl;					//������չ�� services
	std::cout << wtext << extension(dir)<< std::endl;					//��չ��.txt
	std::cout << change_extension(dir, ".exe");
	std::cout <<std::endl << std::endl;

	path path_relative("D:/boost/boost_1_64_0_lib");
	std::cout << path_relative << std::endl;
	wstring ws = is_directory(path_relative) ? wstring( L"��Ŀ¼") : wstring(L"����Ŀ¼");
	std::cout << ws <<path_relative << std::endl;
	path::iterator pathI = path_relative.begin();

	std::cout << std::endl;
	wtext = L"�ּ�Ŀ¼��";
	std::cout << wtext << std::endl;					//��չ��.txt
	while (pathI != path_relative.end())
	{
		std::cout << *pathI << std::endl;
		++pathI;
	}
	std::cout << std::endl;
	wtext = L"�ּ�����";
	std::cout << wtext <<::endl;


	std::cout << path_relative.root_path() << std::endl;
	std::cout << path_relative.relative_path() << std::endl;
	std::cout << path_relative.is_absolute() << std::endl;

	std::cout << std::endl;


	path crt("d:\\chencs\\chencs");
	if (!is_directory(crt))
	{
		bool bcrt = create_directories(crt);
	}
 	testConsole::WriteLine("nihao1");
	testConsole::WriteLine(L"nihao2");
	std::cout << std::endl;

}
