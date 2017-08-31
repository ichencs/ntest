#include "stdafx.h"
#include "NFuncString.h"


NFuncString::NFuncString()
{
}


NFuncString::~NFuncString()
{
}

bool NFuncString::ParseBool(LPCTSTR szVal)
{
	CString strVal(szVal);
	strVal.Trim();
	if (strVal.CompareNoCase(_T("ÊÇ")) == 0
		|| strVal.CompareNoCase(_T("Yes")) == 0
		|| strVal.CollateNoCase(_T("OK")) == 0)
	{
		return true;
	}
	else
	{
		int nVal = _tstoi(szVal);
		return ParseBool(nVal);
	}
	return false;
}

bool NFuncString::ParseBool(int nVal)
{
	return nVal != 0;
}
