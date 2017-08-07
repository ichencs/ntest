#include "stdafx.h"
#include "testNice.h"
#include "Bloger.h"
#include <ncrypt.h>
#include <wincrypt.h>
#include <shlwapi.h>
#include <Security.h>
#include <secext.h>

#pragma comment(lib,"Secur32.lib") 

testNice::testNice()
{
	test();
}


testNice::~testNice()
{
}

void testNice::test()
{
	CString strDomain = GetDomain();
	testConsole::WriteLine(strDomain.GetBuffer());
	strDomain.ReleaseBuffer();
	testSizeof();
// 	testObserve();
// 	testMd5();
}

void funSizeof(int *P)
{
	cout << "数组（或指针）在函数中：" << sizeof(P) << endl;
}

void testNice::testSizeof()
{
	int A[10] = {0};
	int* B = new int[10];
	cout << "数组长度" << sizeof(A) << endl;
	cout << "指针长度" << sizeof(B) << endl;
	funSizeof(A);
}

void testNice::testObserve()
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

void testNice::testMd5()
{
	CString strMd51 = GetMD5("F:\\Users\\Chencs\\Desktop\\test\\thk99-c.prt");
	CString strMd52 = GetMD5("F:\\Users\\Chencs\\Desktop\\test\\new\\thk99-c.prt");


}

void testNice::testDomain()
{


}

CString testNice::GetMD5(const CString &strFilePath /*= _T("")*/)
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
CString testNice::GetDomain()
{

	TCHAR str[128] = {0};
	DWORD l = 128;
	::GetUserNameEx(NameSamCompatible, str, &l);
// 	CString s;
// 	s.Format(_T("%s"), str);
	return CString(str);
}

