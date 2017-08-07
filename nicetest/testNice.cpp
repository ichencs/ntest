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
	cout << "���飨��ָ�룩�ں����У�" << sizeof(P) << endl;
}

void testNice::testSizeof()
{
	int A[10] = {0};
	int* B = new int[10];
	cout << "���鳤��" << sizeof(A) << endl;
	cout << "ָ�볤��" << sizeof(B) << endl;
	funSizeof(A);
}

void testNice::testObserve()
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
CString testNice::GetDomain()
{

	TCHAR str[128] = {0};
	DWORD l = 128;
	::GetUserNameEx(NameSamCompatible, str, &l);
// 	CString s;
// 	s.Format(_T("%s"), str);
	return CString(str);
}

