// vc15-test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cmath>
#include <string>
#include <exception>
#include <memory>
// #include <boost/lambda/lambda.hpp> 
#include <iostream> 
#include <iterator> 
#include <algorithm> 
#include <iosfwd>
#include <sstream>
#include <vector>
// #include "test_code.h"
// #include "boost/filesystem.hpp"

// #include <afxwin.h>

using namespace std;

#define PI 3.1415926
#define a2r(dangle) (dangle /180.0 * PI)
#define r2a(dr) (dr/PI * 180.0)

double Accuracy(double d, int n /*= 3*/)
{
	if (n < 0)
		return d;
	double dacc = pow(10.0, n + 1);
	if (dacc != 0.0)
	{
		d = floor(d * dacc + 5.0);
		d = d / (int)dacc;
	}
	return d;
}
double Precision(double d,int num = 3)
{
	if (num >= 0)
	{
		num;
		double d2 = pow(0.1,num +1) * 5;
		d= d + d2 - fmod(d + d2, pow(0.1,num));
	}
	return d;
}

class CStudent
{
public:
	CStudent() {
		Accuracy(3, 3);
	};
	~CStudent() {};
};



int fooVar = 10;
void foo(int *pVar, int& var)
{
	pVar = &fooVar;
	var = fooVar;
}
CStudent student;

int main()
{
// 	test_code test;
// 	test.test();



}
	double d3 = 1.23456789;
	double d4 = Precision(d3);
	double d5 = Precision(d3, 4);

// int main()
// {
// // 	using namespace boost::lambda;
// // 	typedef std::istream_iterator<int> in;
// 
// // 	std::for_each(
// // 		in(std::cin), in(), std::cout << (_1 * 3) << " ");
// 
// 	typedef std::string string;
// 	string s;
// 	s = "你好";
// 
// 	int ns = s.size();
// 	int nlen1 = s.length();
// 	typedef std::wstring wstring;
// 	wstring ws;
// 	ws = L"你好";
// 	int len2 = ws.length();
// 	int nc = ws.size();
// 
// // 	boost::filesystem::path _path =	boost::filesystem::current_path();
// // 	cout << _path.string() << endl;
// // 	boost_file b_f;
// // 	cout << b_f.current_path() << endl;
// 
// // 	string s;
// //  	std::shared_ptr<int> ptr(new int) ;
// // 
// // 	int n = 1, m = 0;
// // 
// // 	s = n != 1 ? "1" : m == 0 ? "2": "3";
// 
//     return 0;
// }

