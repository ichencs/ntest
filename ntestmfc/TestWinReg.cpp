#include"stdafx.h"
#include <afxwin.h>
#include "CRegistry.h"

//测试注册表

void TestWriteReg();
void TestWriteCreoReg();
TEST_CASE(TestWindowsReg)
{
// 	LONG lValue = 0;
// 	//先读取数据的长度  
// 	ERROR_SUCCESS;
// 	LSTATUS lRes =::RegQueryValue(HKEY_CURRENT_USER, TEXT("Environment\\"), nullptr, &lValue);
// 	TCHAR *pBuf = new TCHAR[lValue];
// 	memset(pBuf,0,lValue);
// 	lRes = ::RegQueryValue(HKEY_CURRENT_USER, TEXT("Environment\\"), pBuf, &lValue);
// 	//AfxMessageBox(pBuf);
// 
// 	HKEY hKey = nullptr;
// 	DWORD dwTpye = REG_SZ;
// 	DWORD dwValue = MAX_PATH;//这个大小一定要先求出来,否则会出错(234)  
// 	TCHAR data[MAX_PATH] = {0};
// 	LONG lRet = 0;
// 	//打开注册表  
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
	//创建成功,将得到hKey,一个注册表句柄,用于下面操作注册表  
	if (ERROR_SUCCESS != ::RegCreateKey(HKEY_CURRENT_USER, TEXT("SoftWare\\Test\\set"), &hKey))
	{
		AfxMessageBox(TEXT("创建注册表失败"));
		return;
	}
	//写入注册表                                  //类型  //名称 //字符个数  
	//只能写入一个value  
	if (ERROR_SUCCESS != ::RegSetValue(hKey, nullptr, REG_SZ, TEXT("Test"), 4))
	{
		AfxMessageBox(TEXT("写入注册表失败"));
		return;
	}
	if (hKey == nullptr)
	{
		return;
	}
	LONG lRet = 0;

	LPSTR lpPath = (LPSTR)(LPCTSTR)strr1;
	//这个函数可以写入更多的Value                    //名称 //强制为零 //类型        //数据  
	if (ERROR_SUCCESS != (lRet = RegSetValueEx(hKey, strr, 0, REG_SZ, (CONST BYTE *)lpPath, strr1.GetLength()*(sizeof(TCHAR)))))
	{
		AfxMessageBox(TEXT("写入注册表失败Ex"));
		return;
	}
	//AfxMessageBox(TEXT("写入注册表成功!"));
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
	Reg.SetValue(L"", L"\"E:\\project\\2017年项目\\808选用工具Web\\bin\\Debugx64\\Translated.exe\"\"%1\"");
	Reg.CloseKey();
};
