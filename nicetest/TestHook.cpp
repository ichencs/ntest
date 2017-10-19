#include "stdafx.h"
#include "windows.h"
#include "vlpp/Vlpp.h"
using namespace vl;
using namespace vl::unittest;
using namespace vl::collections;

// HHOOK myhook;   // ���浱ǰ���Ӿ��
//
// /****************************************************************
// WH_KEYBOARD hook procedure
// �I�P���Ӵ������
// ****************************************************************/
// LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
// {
// 	wchar_t text[50], data[20];    // ����ַ���
// 	const wchar_t *info = NULL;    // �����ַ�ָ��
// 	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam; // ��ȡ������Ϣ
// 	HDC hdc;    // ��ͼ�豸���
//
// 				// �ж��Ƿ��յ�������Ϣ
// 	if (nCode >= 0)
// 	{
// 		// �ж���Ϣ����
// 		if (wParam == WM_KEYDOWN)      info = "��ͨ���I̧��";
// 		else if (wParam == WM_KEYUP)        info = "��ͨ���I����";
// 		else if (wParam == WM_SYSKEYDOWN)   info = "ϵ�y���I̧��";
// 		else if (wParam == WM_SYSKEYUP)     info = "ϵ�y���I����";
//
// 		// ��ʼ������
// 		ZeroMemory(text, sizeof(text));
// 		ZeroMemory(data, sizeof(data));
// 		// ƴװ�ַ���
//
// 		wsprintf(text, L"%s - ������ [%04d], ɨ���� [%04d]  ", info, p->vkCode, p->scanCode);
// 		wsprintf(data, L"���IĿ��Ϊ�� %c  ", p->vkCode);
//
// 		// �˴����� GDI ��ͼ����������ȡ�������ݻ��ڴ�����
// 		hdc = GetDC(��ͼ�Ĵ��ھ��);       // ��ȡҪ��ͼ���豸���
// 		TextOut(hdc, 10, 10, text, strlen(text));   // �ڴ����ϻ�����
// 		TextOut(hdc, 10, 30, data, strlen(data));   // �����ֱ��� Ŀ���豸, x����, y����, �ַ�������, �ַ�������
// 		ReleaseDC(��ͼ�Ĵ��ھ��, hdc);        // �ͷ��豸���
// 	}
//
// 	// ����Ϣ�������´���
// 	return CallNextHookEx(myhook, nCode, wParam, lParam);
// }
//
// TEST_CASE(TestHook)
// {
// 	HINSTANCE hInstance = GetModuleHandle(NULL);
// 	myhook = SetWindowsHookEx(
// 		WH_KEYBOARD_LL, // �������͡�������Ϣ��
// 		KeyboardProc,   // ������
// 		hInstance,      // ��ǰʵ�����
// 		0               // �����߳�ID(NULLΪȫ�ּ���)
// 	);
//
// 	// �ж��Ƿ�ɹ�
// 	if (myhook == NULL)
// 	{
// 		wsprintf(text, L"���̼���ʧ�ܣ�error : %d n", GetLastError());
// 		MessageBox(hwnd, text, TEXT("����"), MB_OK);
// 	}
//
// }

HWND hgWnd;
HHOOK myhook;

/****************************************************************
WH_KEYBOARD hook procedure
�I�P���Ӵ������
****************************************************************/
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
	const wchar_t* info = NULL;
	wchar_t text[50], data[20];
	
	// 	PAINTSTRUCT ps;
	HDC hdc;
	
	if (nCode >= 0)
	{
		if (wParam == WM_KEYDOWN)
		{
			info = L"��ͨ���I̧��";
		}
		else
			if (wParam == WM_KEYUP)
			{
				info = L"��ͨ���I����";
			}
			else
				if (wParam == WM_SYSKEYDOWN)
				{
					info = L"ϵ�y���I̧��";
				}
				else
					if (wParam == WM_SYSKEYUP)
					{
						info = L"ϵ�y���I����";
					}
					
		ZeroMemory(text, sizeof(text));
		ZeroMemory(data, sizeof(data));
		wsprintf(text, L"%s - ������ [%04d], ɨ���� [%04d]  ", info, p->vkCode, p->scanCode);
		wsprintf(data, L"���IĿ��Ϊ�� %c  ", p->vkCode);
		
		hdc = GetDC(hgWnd);
		TextOut(hdc, 10, 10, text, wcslen(text));
		TextOut(hdc, 10, 30, data, wcslen(data));
		ReleaseDC(hgWnd, hdc);
	}
	
	return CallNextHookEx(myhook, nCode, wParam, lParam);
}

// 5. ���ڹ��̴���
LRESULT CALLBACK WndHookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	hgWnd = hwnd;
	
	switch (msg)
	{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
			
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
			
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	
	return 0;
}

TEST_CASE(TestHookMouse)
{
	return;
	
	WNDCLASSEX wc;  // http://baike.baidu.com/view/1750396.htm
	HWND hwnd;
	MSG Msg;
	
	HINSTANCE hInstance = GetModuleHandle(NULL);
	wchar_t text[30];
	
	const wchar_t szClassName[] = L"myWindowClass";
	
	// 1. ����ע�ᴰ�ڽṹ��
	wc.cbSize = sizeof(WNDCLASSEX);              // ע�ᴰ�ڽṹ��Ĵ�С
	wc.style = 0;                               // ���ڵ���ʽ
	wc.lpfnWndProc = WndHookProc;                         // ָ�򴰿ڴ�����̵ĺ���ָ��
	wc.cbClsExtra = 0;                               // ָ�������ڴ�����ṹ��ĸ����ֽ���
	wc.cbWndExtra = 0;                               // ָ�������ڴ���������ĸ����ֽ���
	wc.hInstance = hInstance;                       // ��ģ���ʵ�����
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ͼ��ľ��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);     // ���ľ��
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);        // ������ˢ�ľ��
	wc.lpszMenuName = NULL;                            // ָ��˵���ָ��
	wc.lpszClassName = szClassName;                     // ָ�������Ƶ�ָ��
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // �ʹ����������Сͼ��
	
	// 2. ʹ�á����ڽṹ�塿ע�ᴰ��
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("����ע��ʧ�ܣ�"), TEXT("����"), MB_ICONEXCLAMATION | MB_OK);
		return ;
	}
	
	// 3. ��������
	hwnd = CreateWindowEx(
	    WS_EX_CLIENTEDGE,       // ���ڵ���չ���
	    szClassName,            // ָ��ע��������ָ��
	    TEXT("���ڱ���"),       // ָ�򴰿����Ƶ�ָ��
	    WS_OVERLAPPEDWINDOW,    // ���ڷ��
	    CW_USEDEFAULT, CW_USEDEFAULT, 350, 200, // ���ڵ� x,y �����Լ����
	    NULL,                   // �����ڵľ��
	    NULL,                   // �˵��ľ��
	    hInstance,              // Ӧ�ó���ʵ���ľ��
	    NULL                    // ָ�򴰿ڵĴ�������
	  );
	  
	if (hwnd == NULL)
	{
		MessageBox(NULL, TEXT("���ڴ���ʧ��"), TEXT("����"), MB_ICONEXCLAMATION | MB_OK);
		return ;
	}
	
	// 4. ��ʾ����
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	
	// ���ü���ȫ�ּ���
	myhook = SetWindowsHookEx(
	    WH_KEYBOARD_LL, // �������͡����̡�
	    KeyboardProc,   // ������
	    hInstance,      // ��ǰʵ�����
	    0               // �������ھ��(NULLΪȫ�ּ���)
	  );
	  
	if (myhook == NULL)
	{
		wsprintf(text, L"���̼���ʧ�ܣ�error : %d n", GetLastError());
		MessageBox(hwnd, text, TEXT("����"), MB_OK);
	}
	
	
	// 5. ��Ϣѭ��
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	
	Msg.wParam;
	return;
}
