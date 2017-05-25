// vc15-test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cmath>
#include <string>
#include <iostream>
#include <exception>
#include <memory>
#include <boost/lambda/lambda.hpp> 
#include <iostream> 
#include <iterator> 
#include <algorithm> 
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


int main()
{
	using namespace boost::lambda;
	typedef std::istream_iterator<int> in;

	std::for_each(
		in(std::cin), in(), std::cout << (_1 * 3) << " ");

// 	string s;
//  	std::shared_ptr<int> ptr(new int) ;
// 
// 	int n = 1, m = 0;
// 
// 	s = n != 1 ? "1" : m == 0 ? "2": "3";

    return 0;
}

