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
	
	CStringA astr = "abced";
	
	CStringW wstr3 = astr;
	Console::WriteLine(wstr3.GetString());
	
	
	Console::WriteLine(L"Æ¥Åä½áÊø");
}

void IsWStringValid(CStringW wcode)
{
	CStringW str(L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ()-_.¦Á¦Â¦Ã¦Ä¦Å¦Æ¦Ç¦È¦Ë¦Ì¦Î¦Ð¦Ñ¦Ò¦Ó¦Ô¦Õ¦×¦Ø");
	CStringW wstr_temp;
	for (size_t i = 0; i < wcode.GetLength(); i++)
	{
		wstr_temp = wcode.GetAt(i);
		if (wstr_temp.FindOneOf(str) < 0)
		{
			WString wstr = L"²»Æ¥Åä×Ö·û£º";
			Console::WriteLine(wstr + wstr_temp.GetString());
		}
	}
}


TEST_CASE(TestCStringW)
{
	CStringW wstr1 = "ÄãºÃ";
	CStringW wstr2 = "abcedfssfs612216-/*+23235r";
	IsWStringValid(wstr1);
	IsWStringValid(wstr2);
}
