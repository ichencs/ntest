// ntestmfc.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ntest.h"
#include <afxwin.h>
#include <winsock.h>

int main()
{
	using namespace vl::unittest;
	UnitTest::RunAndDisposeTests();
	HWND hwnd = ::FindWindow(NULL, L"TemplateWindow");
	
	if (hwnd)
	{
		::PostMessage(hwnd, WM_DESTROY, 0, 0);
	}
	
	CString str, str2;
	int num = 3;
	str.Format(_T("%%.%d"), num);
	str2.Format(_T("%%f"));
	
	// 	CString strIdsFile = "E:\\��Ŀ�ĵ�\\501\\��άIDS\\2017-08-10--20170803 IDS��д�ӿ�\\ģ�� �����ļ�\\111(�ڲ�).idsd";
	// 	CString strPath = "E:\\��Ŀ�ĵ�\\501\\��άIDS\\2017-08-10--20170803 IDS��д�ӿ�\\ģ�� �����ļ�";
	// 	strPath.TrimRight('\\');
	// 	CString strCmd;
	//  	strCmd.Format(_T("\"%s\" \"%s\" \"%s\""),L"read",strPath,strIdsFile);
	// // 	strCmd.Format(_T("'%s' '%s' '%s'"),L"read",strPath,strIdsFile);
	// 	ntest::RunExec(_T("E:\\project\\Test\\ThkIdsReader\\ThkIdsReader\\bin\\Release\\ThkIdsReader.exe"),
	// 		strCmd, INFINITE);
	// 	CString str = _T("abcd.idsd");
	// 	CString str2 = str;
	// 	str.TrimRight(_T(".idsd"));
	// 	str2.TrimRight(_T("idsd"));
	// 	str2.TrimRight(_T("."));
	
	ntest tset;
	tset.test();
	
	char hostname[300] = { 0 };
	struct hostent* phost = 0;
	gethostname(hostname, sizeof(hostname) / sizeof(*hostname));
	phost = gethostbyname(hostname);
	
	// 	system("pause");
	return 0;
}

