#pragma once
#include <string>

class testConsole abstract
{
public:
	testConsole();
	~testConsole();
public:
	static void SetColor(bool red, bool green, bool blue, bool light);
	static void SetTitle(const std::wstring& string);

public:	//wide char
	static void WriteLine(const std::wstring & string);
	static void Write(const std::wstring& wstring);
	static void Write(const wchar_t* string,int length);

public:
	static void WriteLine(const std::string & string);
	static void Write(const std::string string);
	static void Write(const char* string, int length);

};

