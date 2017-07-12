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

public:
	static void WriteLine(const std::string & string);
	static void Write(const std::string string);
public:
	static void WriteLine(wchar_t* str);
	static void WriteLine(char* str);
	static void Write(wchar_t* str);
	static void Write(char* str);

	static void WriteLine(int num);
	static void WriteLine(bool b);
	static void WriteLine(double d);
private:
	static void Write(const wchar_t* string,int length);
	static void Write(const char* string, int length);


};

