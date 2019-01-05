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
// 				ip = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list); //�õ���ַ�ַ���
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
	//�۲���.һ���۲��߿��Թ۲���Ŀ��
	CRSSReader* pRssReader = new CRSSReader("rss reader");
	CMailReader* pMailReader = new CMailReader("mail reader");
	pBloger->Attach(pRssReader);//blogerע��۲���
	pBloger->Attach(pMailReader);//blogerע��۲���
	pPortal->Attach(pRssReader);//portalע��۲���
	pPortal->Attach(pMailReader);//portalע��۲���
	//���ͷ�����Ϣ
	pBloger->Publish("���ͷ������ģʽ");
	cout << endl;
	//�Ż�������Ϣ
	pPortal->Publish("�Ż��������ģʽ");
	cout << "\n portal detached mail reader" << endl;
	pPortal->Detach(pMailReader);
	cout << "portal observers count:" << pPortal->GetObserversCount() << endl << endl;
	pPortal->Publish("�Ż��������ģʽ");
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
	int nlen = swprintf(str,sizeof(str), L"%08lx", LangCharset);//10����ת����16���ƣ���������д����ĸ��sprintf(str,"%X",a)


	//080404b0Ϊ���ģ�040904E4ΪӢ��
	//�ļ�����
	//strSubBlock.Format(L"\\StringFileInfo\\%s\\FileDescription",strTranslation);
	//	VerQueryValue(pBlock, strSubBlock.GetString(), (LPVOID*)&pVerValue, &nSize);
	//strTemp.Format(L"�ļ�����: %s", pVerValue);
// 	AfxMessageBox(strTemp);
	//�ڲ�����
	strSubBlock.Format(L"\\StringFileInfo\\%s\\InternalName",strTranslation);
		VerQueryValue(pBlock, strSubBlock.GetString(), (LPVOID*)&pVerValue, &nSize);
	strTemp.Format(L"�ļ�����: %s", pVerValue);
// 	AfxMessageBox(strTemp);
	//�Ϸ���Ȩ
	strSubBlock.Format(L"\\StringFileInfo\\%s\\LegalTradeMarks",strTranslation);
		VerQueryValue(pBlock, strSubBlock.GetString(), (LPVOID*)&pVerValue, &nSize);
	strTemp.Format(L"�Ϸ���Ȩ: %s", pVerValue);
// 	AfxMessageBox(strTemp);
	//ԭʼ�ļ���
	strSubBlock.Format(L"\\StringFileInfo\\%s\\OriginalFileName",strTranslation);
		VerQueryValue(pBlock, strSubBlock.GetString(), (LPVOID*)&pVerValue, &nSize);
	strTemp.Format(L"ԭʼ�ļ���: %s", pVerValue);
// 	AfxMessageBox(strTemp);
	//��Ʒ����
	strSubBlock.Format(L"\\StringFileInfo\\%s\\ProductName",strTranslation);
		VerQueryValue(pBlock, strSubBlock.GetString(), (LPVOID*)&pVerValue, &nSize);
	strTemp.Format(L"��Ʒ����: %s", pVerValue);
// 	AfxMessageBox(strTemp);
	//��Ʒ�汾
	strSubBlock.Format(L"\\StringFileInfo\\%s\\ProductVersion",strTranslation);
		VerQueryValue(pBlock, strSubBlock.GetString(), (LPVOID*)&pVerValue, &nSize);
	strTemp.Format(L"��Ʒ�汾: %s", pVerValue);
// 	AfxMessageBox(strTemp);
	free(pBlock);	
}

