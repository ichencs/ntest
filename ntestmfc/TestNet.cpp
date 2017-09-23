#include "stdafx.h"
#include <wininet.h>
using namespace vl;
using namespace vl::unittest;
using namespace vl::console;

TEST_CASE(TestNetUrl)
{
	WString url = L"http://www.nipic.com/show/3161324.html";
	wchar_t hostname[64] = {0};
	wchar_t urlpath[128] = {0};
	URL_COMPONENTS UrlParts = {sizeof(URL_COMPONENTS), NULL, 1, (INTERNET_SCHEME)0,
		hostname, sizeof(hostname), 0, NULL, 1, urlpath, sizeof(urlpath), NULL, 1};

	DWORD dwFlags;
	BOOL bRes = InternetCrackUrl(url.Buffer(), (DWORD)url.Length(), 0, &UrlParts);
	bRes = InternetGetConnectedState(&dwFlags, 0);
}