#include "stdafx.h"
#include "windows.h"
#include <WinBase.h>

// using namespace vl::environemnt;
using namespace vl::system;
using namespace vl::console;
using namespace vl::collections;

void ConsoleOutComputerName(COMPUTER_NAME_FORMAT fmt)
{
	DWORD nsize;
	BOOL bRes;
	WString string;
	wchar_t buffer[200];
	bRes = GetComputerNameEx(fmt, buffer, &nsize);
	string = buffer;
	Console::WriteLine(string);
}


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
	
	ConsoleOutComputerName(ComputerNameNetBIOS);
	ConsoleOutComputerName(ComputerNameDnsHostname);
	ConsoleOutComputerName(ComputerNameDnsDomain);
	ConsoleOutComputerName(ComputerNameDnsFullyQualified);
	ConsoleOutComputerName(ComputerNamePhysicalNetBIOS);
	ConsoleOutComputerName(ComputerNamePhysicalDnsHostname);
	ConsoleOutComputerName(ComputerNamePhysicalDnsDomain);
	ConsoleOutComputerName(ComputerNamePhysicalDnsFullyQualified);
	ConsoleOutComputerName(ComputerNameMax);
	
}

TEST_CASE(TestDiskInfo)
{
	DiskSpaceInfo info;
	info.disk = L"c://";
	System::GetDiskSpaceInfo(info);
	
	WString strCmd = System::CommandLine();
	vl::console::Console::WriteLine(strCmd);
}

