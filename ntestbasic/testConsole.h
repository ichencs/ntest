#pragma once
#include <string>

class testConsole
{
public:
	testConsole();
	~testConsole();
public:
	static void SetColor(bool red, bool green, bool blue, bool light);
	static void SetTitle(const std::wstring& string);


};

