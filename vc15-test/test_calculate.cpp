#include "stdafx.h"
#include "test_calculate.h"
#include <cmath>


test_calculate::test_calculate()
{
}


test_calculate::~test_calculate()
{
}

void test_calculate::test()
{

}

double test_calculate::Precision(double d, int num)
{
	if (num >= 0)
	{
		num;
		double d2 = pow(0.1, num + 1) * 5;
		d = d + d2 - fmod(d + d2, pow(0.1, num));
	}
	return d;
}
