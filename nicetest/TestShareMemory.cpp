#include "stdafx.h"
#include <Windows.h>
#include <winuser.h>

using namespace vl;
using namespace vl::console;
#define WM_USER_MSG_READ	WM_USER + 100


TEST_CASE(TestSharedMemory)
{
	HANDLE lhShareMemory;
	char* lpBuffer = NULL;
	
	lhShareMemory = CreateFileMapping(HANDLE(0xFFFFFFFF), NULL, PAGE_READWRITE,
	    0, 10, L"mySharedMemory");
	    
	if (NULL == lhShareMemory)
	{
		if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			Console::WriteLine(L"Already exists!");
		}
		else
		{
			Console::WriteLine(L"Create Sheared Memory unsuccessfully!");
		}
	}
	
	lpBuffer = (char*)MapViewOfFile(lhShareMemory, FILE_MAP_WRITE, 0, 0, 10);
	
	if (NULL == lpBuffer)
	{
		Console::WriteLine(L"Get Share memory unsuccessfully!");
	}
	
	char info[] = "hello";
	strcpy(lpBuffer, info);
	AString abuffer = lpBuffer;
	WString wbuffer = atow(abuffer);
	Console::WriteLine(wbuffer);
	// 	Sleep(600000);
	
	HWND hDeCode = ::FindWindow(NULL, L"ntestdlg");
	
	if (hDeCode != NULL)
	{
		::PostMessage(hDeCode, WM_USER_MSG_READ, (WPARAM)0, (LPARAM)sizeof(info));
		
	}
	
	// 	Sleep(6000);
	UnmapViewOfFile(lpBuffer);
	vint size1 = sizeof(WPARAM);
	vint size2 = sizeof(LPARAM);
	
}


void WaitingMessage()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	
	DateTime time = DateTime::LocalTime();
	
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		
	}
	
	
}


LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
		case WM_SIZE:
		
			return 0;
			
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			{
				return 0;
			}
			
			break;
			
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


TEST_CASE(TestCreateWindow)
{
	HMODULE hModule = GetModuleHandle(NULL);
	HCURSOR hCursor = LoadCursor(NULL, IDC_ARROW);
	WString className = L"Template";
	WString windowName = L"TemplateWindow";
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, hModule, NULL, hCursor, NULL, NULL, className.Buffer(), NULL };
	RegisterClassEx(&wc);
	HWND hwnd = CreateWindow(className.Buffer(), windowName.Buffer(), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);
	
	if (hwnd)
	{
		ShowWindow(hwnd, SW_HIDE);
	}
	
	WaitingMessage();
	UnregisterClass(className.Buffer(), wc.hInstance);
}