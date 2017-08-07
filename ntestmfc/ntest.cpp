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
//  		 cout << "���سɹ�" << endl;
//  	 }
//  	 else {
//  		 cout << "����ʧ��" << endl;
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
// 	fsystem.WriteFileLine(str+_T("\\1234.txt"),_T("1111���"));
// 	fsystem.WriteFileLine(str+_T("\\1234.txt"),_T("2222���2"));
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
	if (hFile == INVALID_HANDLE_VALUE)                                        //���CreateFile����ʧ��  
	{
		//��ʾCreateFile����ʧ�ܣ����������š�visual studio�п��ڡ����ߡ�>��������ҡ������ô���ŵõ�������Ϣ��  
		CloseHandle(hFile);
		return _T("");
	}
	HCRYPTPROV hProv = NULL;
	if (CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT) == false)       //���CSP��һ����Կ�����ľ��
	{
		return _T("");
	}
	HCRYPTPROV hHash = NULL;
	//��ʼ������������hash������������һ����CSP��hash������صľ��������������������    CryptHashData���á�
	if (CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash) == false)
	{
		return _T("");
	}
	DWORD dwFileSize = GetFileSize(hFile, 0);    //��ȡ�ļ��Ĵ�С
	if (dwFileSize == 0xFFFFFFFF)               //�����ȡ�ļ���Сʧ��  
	{
		return _T("");
	}
	byte* lpReadFileBuffer = new byte[dwFileSize];
	DWORD lpReadNumberOfBytes;
	if (ReadFile(hFile, lpReadFileBuffer, dwFileSize, &lpReadNumberOfBytes, NULL) == 0)        //��ȡ�ļ�  
	{
		return _T("");
	}
	if (CryptHashData(hHash, lpReadFileBuffer, lpReadNumberOfBytes, 0) == false)      //hash�ļ�  
	{
		return _T("");
	}
	delete[] lpReadFileBuffer;
	CloseHandle(hFile);          //�ر��ļ����
	BYTE *pbHash;
	DWORD dwHashLen = sizeof(DWORD);
	if (!CryptGetHashParam(hHash, HP_HASHVAL, NULL, &dwHashLen, 0)) //��Ҳ��֪��ΪʲôҪ����������CryptGetHashParam������ǲ��յ�msdn       
	{
		return _T("");
	}
	pbHash = (byte*)malloc(dwHashLen);
	if (CryptGetHashParam(hHash, HP_HASHVAL, pbHash, &dwHashLen, 0))//���md5ֵ 
	{
		for (DWORD i = 0; i < dwHashLen; i++)         //���md5ֵ 
		{
			TCHAR str[2] = { 0 };
			CString strFilePartM = _T("");
			strFilePartM.Format(_T("%02x"), pbHash[i]);
			//_stprintf(str,_T("%02x"),pbHash[i]);
			strFileMD5 += strFilePartM;
		}
	}

	//�ƺ���
	if (CryptDestroyHash(hHash) == false)          //����hash����  
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
* Brief: 		��ȡ���û���
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
	Sess.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5000); //5������ӳ�ʱ  
	Sess.SetOption(INTERNET_OPTION_SEND_TIMEOUT, 5000); //5��ķ��ͳ�ʱ  
	Sess.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 5000); //5��Ľ��ճ�ʱ  
	Sess.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 5000); //5��ķ��ͳ�ʱ  
	Sess.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 5000); //5��Ľ��ճ�ʱ  
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
				//��ѯ�ļ�����  
				DWORD nLen = 0;
				cFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, nLen);
				//CString strFilename = GetFileName(url,TRUE);  
				nBufLen = nLen;
				//cout << "nLen=" << nLen << endl;  
				if (nLen <= 0) break;//  

									 //����������ݻ���  
				pBuf = (char*)malloc(nLen + 8);
				ZeroMemory(pBuf, nLen + 8);

				char *p = pBuf;
				while (nLen > 0) {
					//ÿ������8K  
					int n = cFile->Read(p, (nLen < RECVPACK_SIZE) ? nLen : RECVPACK_SIZE);
					//��������˳�ѭ��  
					if (n <= 0) break;//  
									  //���ջ������  
					p += n;
					//ʣ�೤�ȵݼ�  
					nLen -= n;
					//cout << "nLen=" << nLen << endl;  
				}

				//���δ�������ж��˳�  
				if (nLen != 0) break;

				//���ճɹ����浽�ļ�  

				CFile file((CString)strSaveFile, CFile::modeCreate | CFile::modeWrite);
				file.Write(pBuf, nBufLen);
				file.Close();
				ret = true;
			}
		}
		catch (...) {
			cout << "�쳣" << endl;
			break;//  
		}
	} while (0);

	//�ͷŻ���  
	if (pBuf) {
		free(pBuf);
		pBuf = NULL;
		nBufLen = 0;
	}

	//�ر���������  
	if (cFile) {
		cFile->Close();
		Sess.Close();
		delete cFile;
	}
	return ret;
}
