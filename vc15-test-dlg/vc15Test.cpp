#include "stdafx.h"
#include "vc15Test.h"

#include <afx.h> 
#include <afxinet.h>  
#include <iostream>  
#define RECVPACK_SIZE 2048  
using namespace std;

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

//  	 if (DownloadSaveFiles("http://www.nirsoft.net/utils/nircmd.zip", "d:/cppdld_nircmd.zip") == true)
//  	 {
//  		 cout << "下载成功" << endl;
//  	 }
//  	 else {
//  		 cout << "下载失败" << endl;
//  	 }
// 	bool bRes = vc15FileSystem::UrlFileSaveAs("http://www.nirsoft.net/utils/nircmd.zip", "d:/cppdld_nircmd.zip");
	int nres = URLDownloadToFile(NULL, _T("http://www.nirsoft.net/utils/nircmd.zip"), _T("d:\\qq.exe"), NULL, NULL);
// 	CDocument::OnFileSaveAs();

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
// 	fsystem.WriteFileLine(str+_T("\\1234.txt"),_T("1111你好"));
// 	fsystem.WriteFileLine(str+_T("\\1234.txt"),_T("2222你好2"));
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

bool vc15Test::DownloadSaveFiles(const char * url, const char * strSaveFile)
{

	bool ret = false;
	CInternetSession Sess(_T("lpload"));
	Sess.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5000); //5秒的连接超时  
	Sess.SetOption(INTERNET_OPTION_SEND_TIMEOUT, 5000); //5秒的发送超时  
	Sess.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 5000); //5秒的接收超时  
	Sess.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 5000); //5秒的发送超时  
	Sess.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 5000); //5秒的接收超时  
	DWORD dwFlag = INTERNET_FLAG_TRANSFER_BINARY | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_RELOAD;

	CHttpFile* cFile = NULL;
	char      *pBuf = NULL;
	int        nBufLen = 0;
	do {
		try {
			cFile = (CHttpFile*)Sess.OpenURL((CString)url, 1, dwFlag);
			DWORD dwStatusCode;
			cFile->QueryInfoStatusCode(dwStatusCode);
			if (dwStatusCode == HTTP_STATUS_OK) {
				//查询文件长度  
				DWORD nLen = 0;
				cFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, nLen);
				//CString strFilename = GetFileName(url,TRUE);  
				nBufLen = nLen;
				//cout << "nLen=" << nLen << endl;  
				if (nLen <= 0) break;//  

									 //分配接收数据缓存  
				pBuf = (char*)malloc(nLen + 8);
				ZeroMemory(pBuf, nLen + 8);

				char *p = pBuf;
				while (nLen > 0) {
					//每次下载8K  
					int n = cFile->Read(p, (nLen < RECVPACK_SIZE) ? nLen : RECVPACK_SIZE);
					//接收完成退出循环  
					if (n <= 0) break;//  
									  //接收缓存后移  
					p += n;
					//剩余长度递减  
					nLen -= n;
					//cout << "nLen=" << nLen << endl;  
				}

				//如果未接收完中断退出  
				if (nLen != 0) break;

				//接收成功保存到文件  

				CFile file((CString)strSaveFile, CFile::modeCreate | CFile::modeWrite);
				file.Write(pBuf, nBufLen);
				file.Close();
				ret = true;
			}
		}
		catch (...) {
			cout << "异常" << endl;
			break;//  
		}
	} while (0);

	//释放缓存  
	if (pBuf) {
		free(pBuf);
		pBuf = NULL;
		nBufLen = 0;
	}

	//关闭下载连接  
	if (cFile) {
		cFile->Close();
		Sess.Close();
		delete cFile;
	}
	return ret;
}
