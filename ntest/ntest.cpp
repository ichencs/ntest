// ntest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
// #include <boost/lambda/lambda.hpp> 

#include "test_calculate.h"
#include "test_code.h"
#include "boost_asio.h"
#include <memory>


using namespace std;


vector<wstring> SplitString(const wchar_t* config, wchar_t delimiter)
{
	vector<wstring> fragments;
	while (auto next = wcschr(config, delimiter))
	{
		fragments.push_back(wstring(config, next));
		config = next + 1;
	}
	fragments.push_back(wstring(config));
	return fragments; // C++11���Ǻã�  
}

void ReadConfig(const wchar_t* config)
{
	auto fragments = SplitString(config, L';');
	if (fragments.size() != 3)
	{
// 		throw ArgumentException(L"Illegal config string");
	}
// 	DoName(fragments[0]);
// 	DoParent(fragments[1]);
// 	DoDescription(fragments[2]);
}




 int main()
 {
	 std::shared_ptr<int> num(new int(9));
	 *num = 1;

	 Ptr<double> num2 = new double(0);

// 	 testboost tb;


// 	 test_calculate tcal;
// 	 test_code tcode;
// 	 boost_asio basio;

// 	 if (DownloadSaveFiles("http://www.nirsoft.net/utils/nircmd.zip", "d:/cppdld_nircmd.zip") == true)
// 	 {
// 		 cout << "���سɹ�" << endl;
// 	 }
// 	 else {
// 		 cout << "����ʧ��" << endl;
// 	 }
// 	 return 0;

     return 0;
 }

