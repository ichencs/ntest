#include "stdafx.h"
#include "windows.h"
#include "vlpp/Vlpp.h"

#include <devguid.h>
#include <setupapi.h>
#pragma comment(lib, "Setupapi.lib")

using namespace vl;
using namespace vl::unittest;
using namespace vl::collections;

TEST_CASE(TestGetDevice)
{
	HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_PORTS, NULL, NULL, 0);

	if (hDevInfo)
	{
		SP_DEVINFO_DATA SpDevInfo = { sizeof(SP_DEVINFO_DATA) };
		for (DWORD iDevIndex = 0; SetupDiEnumDeviceInfo(hDevInfo, iDevIndex, &SpDevInfo); iDevIndex++)
		{
			TCHAR szName[512] = { 0 };
			if (SetupDiGetDeviceRegistryProperty(hDevInfo, &SpDevInfo, SPDRP_FRIENDLYNAME,
				NULL, (PBYTE)szName, sizeof(szName), NULL))
			{
				//_tprintf(_T("%s\n"), szName);
				WString wstr = szName;
				console::Console::WriteLine(wstr);
			}
		}

		SetupDiDestroyDeviceInfoList(hDevInfo);
	}


}

extern BOOL GetSystemSerialComport(List<WString, WString> &comarray);
TEST_CASE(TestGetDevice2) {

	List<WString, WString> comarray;
	GetSystemSerialComport(comarray);
}
BOOL GetSystemSerialComport(List<WString, WString> &comarray)
{
	HKEY hKey = NULL;

	comarray.Clear();

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		return FALSE;
	}

	wchar_t valuename[200], databuffer[200];
	DWORD valuenamebufferlength = 200, valuetype, databuddersize = 200;

	int i = 0;
	 
	while (RegEnumValue(hKey, i++, valuename, &valuenamebufferlength, NULL, &valuetype, (BYTE*)databuffer, &databuddersize) != ERROR_NO_MORE_ITEMS)
	{
		comarray.Add(databuffer);

		databuddersize = 200;
		valuenamebufferlength = 200;
	}

	RegCloseKey(hKey);

	return TRUE;
}


void SL_ThreadProc(Thread*, void*)
{
	MSG msg;

	while (1)
	{
		GetMessage(&msg, NULL, 0, 0);
		if (msg.message == WM_DEVICECHANGE)
		{
			console::Console::WriteLine(L"有设备接入");
		}
// 		if (!TranslateAccelerator(msg.hwnd, 0, &msg))
// 		{
// 			TranslateMessage(&msg);
// 			DispatchMessage(&msg);
// 		}
	}

}

TEST_CASE(DeviceChange)
{
	Thread* pthread = Thread::CreateAndStart(SL_ThreadProc);

	pthread->Wait();


}