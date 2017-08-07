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
#include <afxwin.h>

using namespace std;




 int main()
 {
	 testNice tn;

	 char strHost[50] = { 0 };
	 int nsize = sizeof(strHost);
	 int rs = gethostname(strHost, nsize);
	 return 0;

	 wstring strWnd = L"";
	 HWND hwnd = ::FindWindow(0,strWnd.c_str());
	 CWnd* pWnd = CWnd::FromHandle(hwnd);

	 double dv = pow(0.1, 3);

	 //目标(被观察者)
	 system("pause");

	 
	 std::pair<int,double> par;
	 
	 testboost tb;
	 testPod tp;

// 	 if (DownloadSaveFiles("http://www.nirsoft.net/utils/nircmd.zip", "d:/cppdld_nircmd.zip") == true)
// 	 {
// 		 cout << "下载成功" << endl;
// 	 }
// 	 else {
// 		 cout << "下载失败" << endl;
// 	 }
// 	 return 0;
// 	 make_shared();
	 system("pause");
     return 0;
 }

