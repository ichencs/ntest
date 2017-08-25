// ntestmfc.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ntest.h"
#include <afxwin.h>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 设置入口地址

int main()
{
	CString strIdsFile = "E:\\项目文档\\501\\三维IDS\\2017-08-10--20170803 IDS读写接口\\模板 测试文件\\111(内部).idsd";
	CString strPath = "E:\\项目文档\\501\\三维IDS\\2017-08-10--20170803 IDS读写接口\\模板 测试文件";
	strPath.TrimRight('\\');
	CString strCmd;
 	strCmd.Format(_T("\"%s\" \"%s\" \"%s\""),L"read",strPath,strIdsFile);
// 	strCmd.Format(_T("'%s' '%s' '%s'"),L"read",strPath,strIdsFile);
	ntest::RunExec(_T("E:\\project\\Test\\ThkIdsReader\\ThkIdsReader\\bin\\Release\\ThkIdsReader.exe"),
		strCmd, INFINITE);
// 	CString str = _T("abcd.idsd");
// 	CString str2 = str;
// 	str.TrimRight(_T(".idsd"));
// 	str2.TrimRight(_T("idsd"));
// 	str2.TrimRight(_T("."));

// 	ntest tset;
// 	tset.test();

    return 0;
}

