// ntestmfc.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ntest.h"
#include <afxwin.h>

int main()
{
	CString str = _T("abcd.idsd");
	CString str2 = str;
	str.TrimRight(_T(".idsd"));
	str2.TrimRight(_T("idsd"));
	str2.TrimRight(_T("."));

	ntest tset;
	tset.test();

    return 0;
}

