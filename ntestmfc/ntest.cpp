#include "stdafx.h"
#include "ntest.h"

#include <afx.h> 
#include <afxinet.h>  
#include <iostream>  
#include <atlstr.h>

#include <wincrypt.h>
#include <shlwapi.h>
#include <Security.h>
#include <secext.h>

#pragma comment(lib,"Secur32.lib") 


#define RECVPACK_SIZE 2048  
using namespace std;

ntest::ntest()
{

}


ntest::~ntest()
{
}

void ntest::test()
{
// 	test_CAtlCString();
// 	test_Others();
	
	CString strPath = "F:/vs/";
	CString strFile;
	testFileSystem sys;
	sys.SelFileDlg(strPath,strFile);

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


void ntest::test_CAtlCString()
{
	CAtlString str1 = _T("Co-Op");
	CAtlString str2 = _T("con");

	int n;
	n = str1.CollateNoCase(str2);
	ASSERT(n < 0);

	n = str1.CompareNoCase(str2);
	ASSERT(n < 0);
}

void ntest::testMd5()
{
	CString strMd51 = GetMD5("F:\\Users\\Chencs\\Desktop\\test\\thk99-c.prt");
	CString strMd52 = GetMD5("F:\\Users\\Chencs\\Desktop\\test\\new\\thk99-c.prt");

}

void ntest::text_fileSystem()
{
	testFileSystem fsystem;
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

	testTime t;
	t.getCurrentTime();
	FILETIME ft = t.toFileTime();
	SYSTEMTIME st = t.toSystemTime();
	tm tt = t.toGmtTm();
	tm lt = t.toLocalTm();
	DBTIMESTAMP ts = t.toDBTimeStamp();
	str = t.toStringTime();
}

void ntest::test_Others()
{
	testFileSystem fsystem;

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

CString ntest::GetMD5(const CString &strFilePath /*= _T("")*/)
{
	CString strFileMD5 = _T("");
	CString filePath = strFilePath;

	if (!PathFileExists(filePath))
		return filePath;

	HANDLE hFile = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)                                        //如果CreateFile调用失败  
	{
		//提示CreateFile调用失败，并输出错误号。visual studio中可在“工具”>“错误查找”中利用错误号得到错误信息。  
		CloseHandle(hFile);
		return _T("");
	}
	HCRYPTPROV hProv = NULL;
	if (CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT) == false)       //获得CSP中一个密钥容器的句柄
	{
		return _T("");
	}
	HCRYPTPROV hHash = NULL;
	//初始化对数据流的hash，创建并返回一个与CSP的hash对象相关的句柄。这个句柄接下来将被    CryptHashData调用。
	if (CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash) == false)
	{
		return _T("");
	}
	DWORD dwFileSize = GetFileSize(hFile, 0);    //获取文件的大小
	if (dwFileSize == 0xFFFFFFFF)               //如果获取文件大小失败  
	{
		return _T("");
	}
	byte* lpReadFileBuffer = new byte[dwFileSize];
	DWORD lpReadNumberOfBytes;
	if (ReadFile(hFile, lpReadFileBuffer, dwFileSize, &lpReadNumberOfBytes, NULL) == 0)        //读取文件  
	{
		return _T("");
	}
	if (CryptHashData(hHash, lpReadFileBuffer, lpReadNumberOfBytes, 0) == false)      //hash文件  
	{
		return _T("");
	}
	delete[] lpReadFileBuffer;
	CloseHandle(hFile);          //关闭文件句柄
	BYTE *pbHash;
	DWORD dwHashLen = sizeof(DWORD);
	if (!CryptGetHashParam(hHash, HP_HASHVAL, NULL, &dwHashLen, 0)) //我也不知道为什么要先这样调用CryptGetHashParam，这块是参照的msdn       
	{
		return _T("");
	}
	pbHash = (byte*)malloc(dwHashLen);
	if (CryptGetHashParam(hHash, HP_HASHVAL, pbHash, &dwHashLen, 0))//获得md5值 
	{
		for (DWORD i = 0; i < dwHashLen; i++)         //输出md5值 
		{
			TCHAR str[2] = { 0 };
			CString strFilePartM = _T("");
			strFilePartM.Format(_T("%02x"), pbHash[i]);
			//_stprintf(str,_T("%02x"),pbHash[i]);
			strFileMD5 += strFilePartM;
		}
	}

	//善后工作
	if (CryptDestroyHash(hHash) == false)          //销毁hash对象  
	{
		return _T("");
	}
	if (CryptReleaseContext(hProv, 0) == false)
	{
		return _T("");
	}
	return strFileMD5;
}

/**---------------------------------**\
* Method:    	GetDomain
* Returns:   	CString
* Access:	  	protected
* Qualifier:
* Brief: 		获取域用户名
* Notice:
1.#pragma comment(lib,"Secur32.lib")
2.#include <Security.h>
3.#include <secext.h>
\**--------------------------------**/
CString ntest::GetDomain()
{
	TCHAR str[128] = { 0 };
	DWORD l = 128;
	::GetUserNameEx(NameSamCompatible, str, &l);
	// 	CString s;
	// 	s.Format(_T("%s"), str);
	return CString(str);

}

bool ntest::DownloadSaveFiles(const char * url, const char * strSaveFile)
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
