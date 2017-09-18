#include "stdafx.h"
using namespace vl;
using namespace vl::unittest;
using namespace vl::console;

CString GetMapInfoByField(CString strInfo, CString strField)
{
	strInfo.MakeLower();
	int nsel = strInfo.Find(strField);
	
	if (nsel > 0)
	{
		int nlen = strField.GetLength();
		int nsel2 = strInfo.Find(_T("&"), nsel);
		
		return strInfo.Mid(nsel + nlen, nsel2 - nsel - nlen);
	}
	
	return CString();
}

TEST_CASE(TestCstring)
{
	CString strInfo = _T("creo://paras/?code=1234&main_filename=ss.prt&sub_filename=ss_d.prt");
	
	CString str = GetMapInfoByField(strInfo, _T("main_filename="));
	
	WString wstr = CT2W(strInfo);
	Console::WriteLine(wstr);
	WString wstr2 = CT2W(str);
	Console::WriteLine(wstr2);
	
}


