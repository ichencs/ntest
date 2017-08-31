#include "stdafx.h"
#include "NFuncNumber.h"


NFuncNumber::NFuncNumber()
{
}


NFuncNumber::~NFuncNumber()
{
}

double NFuncNumber::ParseZero(double d, int nprecision /*= 3*/)
{
	if (fabs(d) < pow(0.1, nprecision + 1))
	{
		d = 0.0;
	}
	return d;
}

double NFuncNumber::ParseZeroEx(double& d, int nprecision /*= 3*/)
{
	if (fabs(d) < pow(0.1, nprecision + 1))
	{
		d = 0.0;
	}
	return d;
}

double NFuncNumber::ParsePercision(double d, int nprec /*= 3*/)
{
	if (nprec > 0)
	{
		double dp = pow(10.0, nprec);
		d = floor(d * dp + 0.5) / dp;
	}
	return d;
}

CString NFuncNumber::ParseString(double d, int npre /*= 3*/)
{
	ParseZeroEx(d);
	CString str;
	str.Format(_T("%%.%df"));
	CString strVal;
	strVal.Format(str, d);
	strVal.TrimRight('0');
	strVal.TrimRight('.');
	return strVal;
}

CString NFuncNumber::ParseString(int n)
{
	CString strVal;
	strVal.Format(_T("%d"), n);
	return strVal;
}
