#include "stdafx.h"
#include "windows.h"
#include "vlpp/Vlpp.h"
using namespace vl;
using namespace vl::unittest;
using namespace vl::collections;

HWND hgWnd;
HHOOK myhook;

/****************************************************************
WH_KEYBOARD hook procedure
�I�P���Ӵ������
****************************************************************/
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
	WString info;
	wchar_t text[250], data[120];

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

		hdc = GetDC(hgWnd);
		ZeroMemory(text, sizeof(text));
		ZeroMemory(data, sizeof(data));
		int nRes = GetKeyNameText(lParam, text, sizeof(text));
		int last_err = GetLastError();

		TextOut(hdc, 10, 10, text, wcslen(text));
		wsprintf(text, L"%s - ������ [%04d], ɨ���� [%04d]  ", info.Buffer(), p->vkCode, p->scanCode);
		wsprintf(data, L"���IĿ��Ϊ�� %c  ", p->vkCode);

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
	WNDCLASSEX wc;  // http://baike.baidu.com/view/1750396.htm
	HWND hwnd;
	MSG Msg;

	HINSTANCE hInstance = GetModuleHandle(NULL);
	wchar_t text[300] = {0};

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
		return;
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
		return;
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
