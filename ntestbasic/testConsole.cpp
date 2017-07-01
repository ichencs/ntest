#include "stdafx.h"
#include "testConsole.h"
#include "windows.h"

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
