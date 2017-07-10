// nicetest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
// #include <boost/lambda/lambda.hpp> 

#include "test_calculate.h"
// #include "boost_asio.h"
#include <memory>


 int main()
 {
	 std::shared_ptr<int> num(new int(9));
	 *num = 1;
// 	 testboost tb;
	 testPod tp;

// 	 if (DownloadSaveFiles("http://www.nirsoft.net/utils/nircmd.zip", "d:/cppdld_nircmd.zip") == true)
// 	 {
// 		 cout << "下载成功" << endl;
// 	 }
// 	 else {
// 		 cout << "下载失败" << endl;
// 	 }
// 	 return 0;

	 system("pause");
     return 0;
 }

