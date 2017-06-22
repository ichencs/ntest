#include "stdafx.h"
#include "vc15Test.h"


vc15Test::vc15Test()
{

}


vc15Test::~vc15Test()
{
}

void vc15Test::test()
{
// 	test_CAtlCString();
// 	test_Others();
	CString str = _T("900");
	CString str2;
	str2.Format(_T("%%%s%%"),str);

// 	text_fileSystem();
}


void vc15Test::test_CAtlCString()
{
	CAtlString str1 = _T("Co-Op");
	CAtlString str2 = _T("con");

	int n;
	n = str1.CollateNoCase(str2);
	ASSERT(n < 0);

	n = str1.CompareNoCase(str2);
	ASSERT(n < 0);
}

void vc15Test::text_fileSystem()
{
	vc15FileSystem fsystem;
	CString str;
	str = fsystem.GetDllName();
	str = fsystem.GetDllPathName();
	str = fsystem.GetDllPath();
	CString strPath2 = fsystem.GetDesktopPath();
// 	fsystem.SelFileDlg(str,strPath2);
//  	fsystem.SaveFileDlg(strPath2,strPath2);
//  	fsystem.SaveFile(str,strPath2);
// 	fsystem.WriteFileLine(str+_T("\\1234.txt"),_T("1111ÄãºÃ"));
// 	fsystem.WriteFileLine(str+_T("\\1234.txt"),_T("2222ÄãºÃ2"));
	fsystem.WriteDllPathFileLine(_T("1"));
	fsystem.WriteDllPathFileLine(_T("2"));
	fsystem.WriteDllPathFileLine(_T("3"));

	vc15Time t;
	t.getCurrentTime();
	FILETIME ft = t.toFileTime();
	SYSTEMTIME st = t.toSystemTime();
	tm tt = t.toGmtTm();
	tm lt = t.toLocalTm();
	DBTIMESTAMP ts = t.toDBTimeStamp();
	str = t.toStringTime();
}

void vc15Test::test_Others()
{
	vc15FileSystem fsystem;

	CString str;
	int num = 5;
	str.Format(_T("H%02d"), num);
	fsystem.WriteDllPathFileLine(str);
	num = 20;
	str.Format(_T("H%2d"), num);
	fsystem.WriteDllPathFileLine(str);
	num = 120;
	str.Format(_T("H%2d"), num);
	fsystem.WriteDllPathFileLine(str);

}
