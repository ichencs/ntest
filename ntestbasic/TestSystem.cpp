#include "stdafx.h"

// using namespace vl::environemnt;
using namespace vl::system;
TEST_CASE(TestEnvironment)
{
	WString user = System::UserName();
	WString computer = System::ComputerName();
	System env;
	env.SystemInfo();
	env.Version();
	DateTime time1, time2;
	time1 = DateTime::LocalTime();
	time2 = env.Time();
	WString host = L"localhost";
	host = L"192.168.31.1";
	WString directory = System::WindowsDirectory();
	directory = System::SystemWindowsDirectory();
	
	Process proc;
	ProcessMemory memo;
	proc.GetMemoryInfo(memo);
	
}