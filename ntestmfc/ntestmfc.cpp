// ntestmfc.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ntest.h"
#include <afxwin.h>


int main()
{
	ntest::RunExec(_T("E:\\project\\Test\\ThkIdsReader\\ThkIdsReader\\bin\\Debug\\ThkIdsReader.exe"),
		_T("\"1 2\" \"3\""), INFINITE);
	CString str = _T("abcd.idsd");
	CString str2 = str;
	str.TrimRight(_T(".idsd"));
	str2.TrimRight(_T("idsd"));
	str2.TrimRight(_T("."));

// 	ntest tset;
// 	tset.test();

    return 0;
}

