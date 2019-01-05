#include "stdafx.h"
#include "Bloger.h"
// #include <ncrypt.h>

#include "winsock2.h"
#include <cmath>
#include "fFileDetail.h"
#pragma comment(lib,"ws2_32.lib")

#pragma comment(lib,"Mincore.lib")
#pragma comment(lib,"version.lib")




// void testNice::testIP()
// {
// 	WSADATA wsaData;
// 	char name[155] = {0};
// 	char *ip;
// 	PHOSTENT hostinfo;
// 	if (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0)
// 	{
// 		if (gethostname(name, sizeof(name)) == 0)
// 		{
// 			printf("hostname=%s\n", name);
// 			if ((hostinfo = gethostbyname(name)) != NULL)
// 			{
// 				ip = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list); //得到地址字符串
// 				printf("local host ip: %s\n", ip);
// 			}
// 		}
// 		WSACleanup();
// 	}
// }



TEST_CASE(TestObservable)
{
	CBloger* pBloger = new CBloger();
	CPortal* pPortal = new CPortal();
	//观察者.一个观察者可以观察多个目标
	CRSSReader* pRssReader = new CRSSReader("rss reader");
	CMailReader* pMailReader = new CMailReader("mail reader");
	pBloger->Attach(pRssReader);//bloger注册观察者
	pBloger->Attach(pMailReader);//bloger注册观察者
	pPortal->Attach(pRssReader);//portal注册观察者
	pPortal->Attach(pMailReader);//portal注册观察者
	//博客发布信息
	pBloger->Publish("博客分享设计模式");
	cout << endl;
	//门户发布信息
	pPortal->Publish("门户分享设计模式");
	cout << "\n portal detached mail reader" << endl;
	pPortal->Detach(pMailReader);
	cout << "portal observers count:" << pPortal->GetObserversCount() << endl << endl;
	pPortal->Publish("门户分享设计模式");
}


TEST_CASE(FileInfoReader)
{
	wchar_t* szFileName = L"D:\\Qt\\5.6.3\\msvc2015_64\\bin\\assistant.exe";
	
	using namespace fFileAttribute;
	fFileDetail fdtl;
	fdtl.Initialize(szFileName);
	wstring iname = fdtl.InternalName();
	wstring pname = fdtl.ProductName();
	wstring pver = fdtl.ProductVersion();
	wstring ofname = fdtl.OriginalFileName();
	wstring ltmarks = fdtl.LegalTradeMarks();
	wstring cname = fdtl.CompanyName();
	wstring fdesc = fdtl.FileDescription();

	return;

	
	
	
	DWORD dwSize = GetFileVersionInfoSize(szFileName, NULL);
	LPVOID pBlock = malloc(dwSize*sizeof(wchar_t));
	GetFileVersionInfo(szFileName, 0, dwSize, pBlock);
	DWORD* pVerValue = NULL;
	UINT nSize = 0;
	VerQueryValue(pBlock, TEXT("\\VarFileInfo\\Translation"),	(LPVOID*)&pVerValue, &nSize);
	DWORD dErr =	GetLastError();
 	DWORD LangCharset = MAKELONG(HIWORD(pVerValue[0]), LOWORD(pVerValue[0]));
//	DWORD LangCharset = MAKELONG(LOWORD(pVerValue[0]),HIWORD(pVerValue[0]));

	CString strBlockName;
	strBlockName.Format(_T("//StringFileInfo//%08lx"),	LangCharset);
	CString str123;
	CString strSubBlock, strTranslation, strTemp;
	strTemp.Format(L"000%x", pVerValue[0]);
	str123.Format(L"000%x", LOWORD(pVerValue[0]));
	strTranslation = strTemp.Right(4);
	strTemp.Format(L"000%x", pVerValue[1]);
	strTranslation += strTemp.Right(4);
	wstring wstr_123 = std::to_wstring(LangCharset);
	wchar_t str[256] = {0};
	int nlen = swprintf(str,sizeof(str), L"%08lx", LangCharset);//10进制转换成16进制，如果输出大写的字母是sprintf(str,"%X",a)


	//080404b0为中文，040904E4为英文
	//文件描述
	//strSubBlock.Format(L"\\StringFileInfo\\%s\\FileDescription",strTranslation);
	//	VerQueryValue(pBlock, strSubBlock.GetString(), (LPVOID*)&pVerValue, &nSize);
	//strTemp.Format(L"文件描述: %s", pVerValue);
// 	AfxMessageBox(strTemp);
	//内部名称
	strSubBlock.Format(L"\\StringFileInfo\\%s\\InternalName",strTranslation);
		VerQueryValue(pBlock, strSubBlock.GetString(), (LPVOID*)&pVerValue, &nSize);
	strTemp.Format(L"文件描述: %s", pVerValue);
// 	AfxMessageBox(strTemp);
	//合法版权
	strSubBlock.Format(L"\\StringFileInfo\\%s\\LegalTradeMarks",strTranslation);
		VerQueryValue(pBlock, strSubBlock.GetString(), (LPVOID*)&pVerValue, &nSize);
	strTemp.Format(L"合法版权: %s", pVerValue);
// 	AfxMessageBox(strTemp);
	//原始文件名
	strSubBlock.Format(L"\\StringFileInfo\\%s\\OriginalFileName",strTranslation);
		VerQueryValue(pBlock, strSubBlock.GetString(), (LPVOID*)&pVerValue, &nSize);
	strTemp.Format(L"原始文件名: %s", pVerValue);
// 	AfxMessageBox(strTemp);
	//产品名称
	strSubBlock.Format(L"\\StringFileInfo\\%s\\ProductName",strTranslation);
		VerQueryValue(pBlock, strSubBlock.GetString(), (LPVOID*)&pVerValue, &nSize);
	strTemp.Format(L"产品名称: %s", pVerValue);
// 	AfxMessageBox(strTemp);
	//产品版本
	strSubBlock.Format(L"\\StringFileInfo\\%s\\ProductVersion",strTranslation);
		VerQueryValue(pBlock, strSubBlock.GetString(), (LPVOID*)&pVerValue, &nSize);
	strTemp.Format(L"产品版本: %s", pVerValue);
// 	AfxMessageBox(strTemp);
	free(pBlock);	
}

