#include"stdafx.h"
#include <afxwin.h>
#include "CRegistry.h"

//����ע���

void TestWriteReg();
void TestWriteCreoReg();
TEST_CASE(TestWindowsReg)
{
// 	LONG lValue = 0;
// 	//�ȶ�ȡ���ݵĳ���  
// 	ERROR_SUCCESS;
// 	LSTATUS lRes =::RegQueryValue(HKEY_CURRENT_USER, TEXT("Environment\\"), nullptr, &lValue);
// 	TCHAR *pBuf = new TCHAR[lValue];
// 	memset(pBuf,0,lValue);
// 	lRes = ::RegQueryValue(HKEY_CURRENT_USER, TEXT("Environment\\"), pBuf, &lValue);
// 	//AfxMessageBox(pBuf);
// 
// 	HKEY hKey = nullptr;
// 	DWORD dwTpye = REG_SZ;
// 	DWORD dwValue = MAX_PATH;//�����Сһ��Ҫ�������,��������(234)  
// 	TCHAR data[MAX_PATH] = {0};
// 	LONG lRet = 0;
// 	//��ע���  
// 	lRes = ::RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Environment\\"), 0, KEY_ALL_ACCESS, &hKey);
// 	//RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\Test"), &hKey);  
// 
// 	if (ERROR_SUCCESS != (lRet = ::RegQueryValueEx(hKey, TEXT("Path"), 0, &dwTpye, (LPBYTE)data, &dwValue)))
// 	{
// 		return;
// 	}

	//TestWriteReg();
	TestWriteCreoReg();
}

void TestWriteReg()
{
	int nIndex = 1;
	CString strr1;
	strr1.Format(L"%i,%i,%i", 1, 2, 3);
	CString strr;
	strr.Format(L"CmSet%i", nIndex);
	HKEY hKey = nullptr;
	//�����ɹ�,���õ�hKey,һ��ע�����,�����������ע���  
	if (ERROR_SUCCESS != ::RegCreateKey(HKEY_CURRENT_USER, TEXT("SoftWare\\Test\\set"), &hKey))
	{
		AfxMessageBox(TEXT("����ע���ʧ��"));
		return;
	}
	//д��ע���                                  //����  //���� //�ַ�����  
	//ֻ��д��һ��value  
	if (ERROR_SUCCESS != ::RegSetValue(hKey, nullptr, REG_SZ, TEXT("Test"), 4))
	{
		AfxMessageBox(TEXT("д��ע���ʧ��"));
		return;
	}
	if (hKey == nullptr)
	{
		return;
	}
	LONG lRet = 0;

	LPSTR lpPath = (LPSTR)(LPCTSTR)strr1;
	//�����������д������Value                    //���� //ǿ��Ϊ�� //����        //����  
	if (ERROR_SUCCESS != (lRet = RegSetValueEx(hKey, strr, 0, REG_SZ, (CONST BYTE *)lpPath, strr1.GetLength()*(sizeof(TCHAR)))))
	{
		AfxMessageBox(TEXT("д��ע���ʧ��Ex"));
		return;
	}
	//AfxMessageBox(TEXT("д��ע���ɹ�!"));
	RegCloseKey(hKey);

}

void TestWriteCreoReg()
{
	return;
	CRegistry Reg;
 	Reg.CreateKey(CRegistry::classesRoot, L"Creo");
 	Reg.SetValue(L"URL Protocol", L"");
 	Reg.CloseKey();
	Reg.CreateKey(CRegistry::classesRoot, L"Creo\\shell\\open\\command");
	Reg.SetValue(L"", L"\"E:\\project\\2017����Ŀ\\808ѡ�ù���Web\\bin\\Debugx64\\Translated.exe\"\"%1\"");
	Reg.CloseKey();
};
