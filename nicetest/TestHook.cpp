#include "stdafx.h"
#include "windows.h"
#include "vlpp/Vlpp.h"
using namespace vl;
using namespace vl::unittest;
using namespace vl::collections;

//  HHOOK myhook;   // ���浱ǰ���Ӿ��

 /****************************************************************
 WH_KEYBOARD hook procedure
 �I�P���Ӵ������
 ****************************************************************/
//  LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
//  {
//  	wchar_t text[50], data[20];    // ����ַ���
//  	const wchar_t *info = NULL;    // �����ַ�ָ��
//  	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam; // ��ȡ������Ϣ
//  	HDC hdc;    // ��ͼ�豸���
// 
//  				// �ж��Ƿ��յ�������Ϣ
//  	if (nCode >= 0)
//  	{
//  		// �ж���Ϣ����
//  		if (wParam == WM_KEYDOWN)      info = "��ͨ���I̧��";
//  		else if (wParam == WM_KEYUP)        info = "��ͨ���I����";
//  		else if (wParam == WM_SYSKEYDOWN)   info = "ϵ�y���I̧��";
//  		else if (wParam == WM_SYSKEYUP)     info = "ϵ�y���I����";
// 
//  		// ��ʼ������
//  		ZeroMemory(text, sizeof(text));
//  		ZeroMemory(data, sizeof(data));
//  		// ƴװ�ַ���
// 
//  		wsprintf(text, L"%s - ������ [%04d], ɨ���� [%04d]  ", info, p->vkCode, p->scanCode);
//  		wsprintf(data, L"���IĿ��Ϊ�� %c  ", p->vkCode);
// 
//  		// �˴����� GDI ��ͼ����������ȡ�������ݻ��ڴ�����
//  		hdc = GetDC(��ͼ�Ĵ��ھ��);       // ��ȡҪ��ͼ���豸���
//  		TextOut(hdc, 10, 10, text, strlen(text));   // �ڴ����ϻ�����
//  		TextOut(hdc, 10, 30, data, strlen(data));   // �����ֱ��� Ŀ���豸, x����, y����, �ַ�������, �ַ�������
//  		ReleaseDC(��ͼ�Ĵ��ھ��, hdc);        // �ͷ��豸���
//  	}
// 
//  	// ����Ϣ�������´���
//  	return CallNextHookEx(myhook, nCode, wParam, lParam);
//  }

//  TEST_CASE(TestHook)
//  {
//  	HINSTANCE hInstance = GetModuleHandle(NULL);
//  	myhook = SetWindowsHookEx(
//  		WH_KEYBOARD_LL, // �������͡�������Ϣ��
//  		KeyboardProc,   // ������
//  		hInstance,      // ��ǰʵ�����
//  		0               // �����߳�ID(NULLΪȫ�ּ���)
//  	);
// 
//  	// �ж��Ƿ�ɹ�
//  	if (myhook == NULL)
//  	{
//  		wsprintf(text, L"���̼���ʧ�ܣ�error : %d n", GetLastError());
//  		MessageBox(hwnd, text, TEXT("����"), MB_OK);
//  	}
// 
//  }



