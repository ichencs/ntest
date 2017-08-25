#include "stdafx.h"
#include "testConsole.h"
#include "windows.h"
#include <sstream>
#include <iostream>

testConsole::testConsole()
{
}


testConsole::~testConsole()
{
}

void testConsole::SetColor(bool red, bool green, bool blue, bool light)
{
	WORD attribute = 0;
	if (red)attribute |= FOREGROUND_RED;
	if (green)attribute |= FOREGROUND_GREEN;
	if (blue)attribute |= FOREGROUND_BLUE;
	if (light)attribute |= FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attribute);
	SetConsoleTextAttribute(GetStdHandle(STD_INPUT_HANDLE), attribute);
}

void testConsole::SetTitle(const std::wstring& string)
{
	SetConsoleTitle(string.c_str());
}

void testConsole::Write(const wchar_t* string, int length)
{
	HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD fileMode = 0;
	DWORD written = 0;
	if (GetFileType(outHandle) & FILE_TYPE_CHAR && GetConsoleMode(outHandle,&fileMode))
	{
		//必须输出双字节
		WriteConsole(outHandle, string,length, &written, 0);
	}
	else
	{
		//必须进行转换
		int codePage = GetConsoleOutputCP();
		int charCount = WideCharToMultiByte(codePage, 0, string, -1, 0, 0, 0, 0);
		char* codePageBuffer = new char[charCount];
		WideCharToMultiByte(codePage, 0, string, -1, codePageBuffer, charCount, 0, 0);
		WriteFile(outHandle, codePageBuffer, charCount - 1, &written, 0);		// -1:
		delete[] codePageBuffer;
	}
}

void testConsole::Write(wchar_t* str)
{
	std::wstring wstr(str);
	Write(wstr);
}

void testConsole::Write(char* str)
{
	std::string wstr(str);
	Write(wstr);
}

void testConsole::WriteLine(const std::string & string)
{
	Write(string);
	Write(L"\r\n");
}

void testConsole::WriteLine(int num)
{
	std::string str;
	std::stringstream ss;
	ss << num;
	ss >> str;
	WriteLine(str);
}

void testConsole::WriteLine(bool b)
{
	std::string str = b?"true":"false";
// 	std::stringstream ss;
// 	ss << b;
// 	ss >> str;
	WriteLine(str);
}

void testConsole::WriteLine(double d)
{
	std::string str;
	std::stringstream ss;
	ss << d;
	ss >> str;
	WriteLine(str);
}

void testConsole::WriteLine(wchar_t* str)
{
	std::wstring wstr(str);
	WriteLine(wstr);
}

void testConsole::WriteLine(char* str)
{
	std::string wstr(str);
	WriteLine(wstr);
}

void testConsole::Write(const std::string string)
{
	Write(string.c_str(),(int) string.size());
}

void testConsole::Write(const char * string, int length)
{
	HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int codePage = GetConsoleOutputCP();
	DWORD written = 0;
	WriteFile(outHandle, string, length, &written, 0);
}


void testConsole::WriteLine(const std::wstring & string)
{
	Write(string);
	Write(L"\r\n");
}

void testConsole::Write(const std::wstring& wstring)
{
	Write(wstring.c_str(),(int)wstring.size());
}
