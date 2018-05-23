#include "stdafx.h"
#include <afxwin.h>
using namespace vl;
using namespace vl::unittest;
using namespace vl::console;

#define ThkProToolkitMsgWnd			L"ThkProToolkitMsgWnd"

TEST_CASE(TestFindWndDlg)
{
	HWND hToolKitWnd = ::FindWindow(NULL, ThkProToolkitMsgWnd);
	
	if (hToolKitWnd == NULL)
	{
	
	}
	
}

TEST_CASE(CurrentUser)
{
	wchar_t buffer[MAX_PATH] = {0};
	DWORD dw = GetEnvironmentVariable(L"USERPROFILE", buffer, MAX_PATH);




}

