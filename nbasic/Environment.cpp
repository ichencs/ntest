#include "Environment.h"
#include <Windows.h>
#include "Collections\List.h"
#pragma warning(disable: 4996)     

// #pragma comment(lib,"kernel32.lib")

#define NICE_MAX_NAME 200

namespace vl
{

namespace environment
{
	using namespace collections;
	Environment::Environment()
	{
	}
	
	
	Environment::~Environment()
	{
	}
	
	vl::WString Environment::ComputerName()
	{
		wchar_t name[NICE_MAX_NAME] = {0};
		DWORD dwNamelen = sizeof(name)/sizeof(*name);
		GetComputerName(name, &dwNamelen);
		return name;
	}
	
	vl::WString Environment::UserName()
	{
		wchar_t name[NICE_MAX_NAME] = { 0 };
		DWORD dwNamelen = sizeof(name) / sizeof(*name);
		GetUserName(name, &dwNamelen);
		return name;
	}

	void Environment::Version()
	{
		OSVERSIONINFOEX osver;
		ZeroMemory(&osver,sizeof(osver));
		osver.dwOSVersionInfoSize = sizeof(osver);
		::GetVersionEx((OSVERSIONINFO *)&osver);
	}

	void Environment::System()
	{
		SYSTEM_INFO info;                                   //用SYSTEM_INFO结构判断64位AMD处理器 
		::GetSystemInfo(&info);
	}

	void Environment::Variable()
	{
// 		GetEnvironmentVariable();
// 		LPWCH pEv = GetEnvironmentStrings();
		
// 		PVOID pEv = GetEnvironmentStrings();
// 		LPSTR szEnvs;
// 		// 显示  
// // 		for (szEnvs = (LPSTR)pEv; *szEnvs;)
// // 		{
// // // 			printf("%s\n", szEnvs);
// // 			while (*szEnvs++);
// // 		}
// 		// 释放  
// 		FreeEnvironmentStrings((LPWCH)pEv);
	}


}

}
