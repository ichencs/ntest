#include "stdafx.h"
#include "windows.h"
#include "vlpp/Vlpp.h"
using namespace vl;
using namespace vl::unittest;
using namespace vl::collections;

//  HHOOK myhook;   // 保存当前钩子句柄

 /****************************************************************
 WH_KEYBOARD hook procedure
 鍵盤钩子处理过程
 ****************************************************************/
//  LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
//  {
//  	wchar_t text[50], data[20];    // 输出字符串
//  	const wchar_t *info = NULL;    // 类型字符指针
//  	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam; // 获取按键消息
//  	HDC hdc;    // 画图设备句柄
// 
//  				// 判断是否收到键盘消息
//  	if (nCode >= 0)
//  	{
//  		// 判断消息类型
//  		if (wParam == WM_KEYDOWN)      info = "普通按鍵抬起";
//  		else if (wParam == WM_KEYUP)        info = "普通按鍵按下";
//  		else if (wParam == WM_SYSKEYDOWN)   info = "系統按鍵抬起";
//  		else if (wParam == WM_SYSKEYUP)     info = "系統按鍵按下";
// 
//  		// 初始化数组
//  		ZeroMemory(text, sizeof(text));
//  		ZeroMemory(data, sizeof(data));
//  		// 拼装字符串
// 
//  		wsprintf(text, L"%s - 键盘码 [%04d], 扫描码 [%04d]  ", info, p->vkCode, p->scanCode);
//  		wsprintf(data, L"按鍵目测为： %c  ", p->vkCode);
// 
//  		// 此处调用 GDI 画图函数来将截取到的内容画在窗口上
//  		hdc = GetDC(画图的窗口句柄);       // 获取要画图的设备句柄
//  		TextOut(hdc, 10, 10, text, strlen(text));   // 在窗口上画文字
//  		TextOut(hdc, 10, 30, data, strlen(data));   // 参数分别是 目标设备, x坐标, y坐标, 字符串内容, 字符串长度
//  		ReleaseDC(画图的窗口句柄, hdc);        // 释放设备句柄
//  	}
// 
//  	// 将消息继续往下传递
//  	return CallNextHookEx(myhook, nCode, wParam, lParam);
//  }

//  TEST_CASE(TestHook)
//  {
//  	HINSTANCE hInstance = GetModuleHandle(NULL);
//  	myhook = SetWindowsHookEx(
//  		WH_KEYBOARD_LL, // 监听类型【键盘消息】
//  		KeyboardProc,   // 处理函数
//  		hInstance,      // 当前实例句柄
//  		0               // 监听线程ID(NULL为全局监听)
//  	);
// 
//  	// 判断是否成功
//  	if (myhook == NULL)
//  	{
//  		wsprintf(text, L"键盘监听失败！error : %d n", GetLastError());
//  		MessageBox(hwnd, text, TEXT("错误"), MB_OK);
//  	}
// 
//  }



