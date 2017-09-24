#include "stdafx.h"

#include <Windows.h>
#include <winhttp.h>
#pragma comment(lib, "WinHttp.lib")

extern WString GetTestOutputPath();
using namespace vl;
using namespace vl::console;
TEST_CASE(TestHttps)
{
	WString strHost = L"https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1506182955435&di=e1916dcac8c20e38a9ec517ded4830ec&imgtype=0&src=http%3A%2F%2Fc.hiphotos.baidu.com%2Fzhidao%2Fpic%2Fitem%2F1f178a82b9014a909461e9baa1773912b31bee5e.jpg";
	HttpRequest request;
	request.SetHost(strHost);

	HttpResponse response;

	HttpQuery(request, response);
// 	AString astr = &response.body[0];
// 	WString wstr = utf8tow(astr);

// 	Console::WriteLine(wstr);

	URL_COMPONENTS comp = {0};
	comp.dwStructSize = sizeof(URL_COMPONENTS);
	BOOL bRes = WinHttpCrackUrl(strHost.Buffer(),0, ICU_ESCAPE,&comp);

}


using namespace vl::filesystem;
using namespace vl::collections;
using namespace vl::stream;

typedef void(*DownLoadCallback)(vuint ContentSize, vuint CurrentLen);

bool HttpDownload(WString url,WString filePath ,DownLoadCallback Func = NULL)
{
	// initialize
	HttpRequest request;
	request.SetHost(url);
	request.method = L"GET";

	HINTERNET internet = NULL;
	HINTERNET connectedInternet = NULL;
	HINTERNET requestInternet = NULL;
	BOOL httpResult = FALSE;
	DWORD error = 0;
	DWORD resStatusCode = -1;
	vuint currentSize = 0;
	DWORD totalSize = 0;
	stream::FileStream ffile(filePath, FileStream::WriteOnly);

	// access http
	internet = WinHttpOpen(L"chencs", WINHTTP_ACCESS_TYPE_NO_PROXY, NULL, NULL, 0);
	error = GetLastError();
	if (!internet) goto CLEANUP;

	// connect
	connectedInternet = WinHttpConnect(internet, request.server.Buffer(), (int)request.port, 0);
	error = GetLastError();
	if (!connectedInternet) goto CLEANUP;

	// open request
	requestInternet = WinHttpOpenRequest(connectedInternet, request.method.Buffer(), request.query.Buffer(), NULL,
										 WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_REFRESH | (request.secure ? WINHTTP_FLAG_SECURE : 0));
	error = GetLastError();
	if (!requestInternet) goto CLEANUP;

	//(2) 发送请求
	{
		httpResult = WinHttpSendRequest(requestInternet, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, NULL);
	}
	error = GetLastError();
	if (httpResult == FALSE) goto CLEANUP;

	// receive response
	httpResult = WinHttpReceiveResponse(requestInternet, NULL);
	error = GetLastError();
	if (httpResult != TRUE) goto CLEANUP;

	// read response status code
	{
		DWORD headerLength = sizeof(DWORD);
		DWORD statusCode = 0;
		httpResult = WinHttpQueryHeaders(requestInternet, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &statusCode, &headerLength, WINHTTP_NO_HEADER_INDEX);
		error = GetLastError();
		if (httpResult == FALSE) goto CLEANUP;
		resStatusCode = statusCode;
	}
	// read total size
	{
		DWORD headerLength = sizeof(DWORD);
		httpResult = WinHttpQueryHeaders(requestInternet, WINHTTP_QUERY_CONTENT_LENGTH | WINHTTP_QUERY_FLAG_NUMBER, NULL, &totalSize, &headerLength, WINHTTP_NO_HEADER_INDEX);
		error = GetLastError();
		if (httpResult == FALSE) goto CLEANUP;
	}

	if (!ffile.CanWrite())
	{
		goto CLEANUP;
	}
	while (true)
	{
		DWORD bytesAvailable = 0;
		BOOL queryDataAvailableResult = WinHttpQueryDataAvailable(requestInternet, &bytesAvailable);
		error = GetLastError();
		if (queryDataAvailableResult == TRUE && bytesAvailable != 0)
		{
			char* utf8 = new char[bytesAvailable];
			DWORD bytesRead = 0;
			BOOL readDataResult = WinHttpReadData(requestInternet, utf8, bytesAvailable, &bytesRead);
			error = GetLastError();
			if (readDataResult == TRUE)
			{
				currentSize += bytesRead;
				ffile.Write(utf8,bytesAvailable);
				//回调函数，返回进度
				if (Func)
				{
					Func(totalSize, currentSize);
				}
			}
// 			else
			{
				delete[] utf8;
			}
		}
		else
		{
			break;
		}
	}
	
CLEANUP:
	ffile.Close();
	if (requestInternet) WinHttpCloseHandle(requestInternet);
	if (connectedInternet) WinHttpCloseHandle(connectedInternet);
	if (internet) WinHttpCloseHandle(internet);
	return resStatusCode != -1;
}

void dcallback(vuint ContentSize, vuint currentSize)
{
	printf("count:%d,size:%d\n",(int)ContentSize, (int)currentSize);
}

TEST_CASE(TestDownLoad)
{
	WString wstrUrl = L"http://sw.bos.baidu.com/sw-search-sp/software/58d7820029ae7/BaiduMusic_10.1.7.7_setup.exe";
	FilePath fpath = wstrUrl;
	;
	WString filePath = GetTestOutputPath()+ fpath.GetName();
// 	HttpDownload(wstrUrl, filePath, dcallback);

}