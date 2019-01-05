#include "stdafx.h"
#include "EnablePrivilege.h"

//宏的功能介绍:
//-------------------------------------------------------------
//#define            SE_BACKUP_NAME               TEXT("SeBackupPrivilege")     //备份数据权限
//#define            SE_RESTORE_NAME              TEXT("SeRestorePrivilege")    //恢复数据权限
//#define            SE_SHUTDOWN_NAME             TEXT("SeShutdownPrivilege")   //关机权限
//#define            SE_DEBUG_NAME                TEXT("SeDebugPrivilege")      //读、写控制权限
//-------------------------------------------------------------

//宏的功能介绍:
//-------------------------------------------------------------
//ABOVE_NORMAL_PRIORITY_CLASS(0x00008000)   高于标准
//BELOW_NORMAL_PRIORITY_CLASS(0x00004000)   低于标准
//HIGH_PRIORITY_CLASS(0x00000080)           高
//IDLE_PRIORITY_CLASS(0x00000040)           低
//NORMAL_PRIORITY_CLASS(0x00000020)         标准
//REALTIME_PRIORITY_CLASS(0x00000100)       实时
//-------------------------------------------------------------

EnablePrivilege::EnablePrivilege()
{
}


EnablePrivilege::~EnablePrivilege()
{
}

BOOL EnablePrivilege::SetRealTimePriority()
{
	if (!SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS))
	{
		return false;
	}

	return true;
}

BOOL EnablePrivilege::EnableShutdownPriv()
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return false;

	if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &sedebugnameValue))
	{
		CloseHandle(hToken);
		return false;
	}

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, NULL, NULL))
		CloseHandle(hToken);

	return true;
}

BOOL EnablePrivilege::EnableDebugPriv()
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return false;

	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue))
	{
		CloseHandle(hToken);
		return false;
	}

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, NULL, NULL))
		CloseHandle(hToken);

	return true;
}

BOOL EnablePrivilege::EnableBackupPriv()
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return false;

	if (!LookupPrivilegeValue(NULL, SE_BACKUP_NAME, &sedebugnameValue))
	{
		CloseHandle(hToken);
		return false;
	}

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, NULL, NULL))
		CloseHandle(hToken);

	return true;
}

BOOL EnablePrivilege::EnableRestorePriv()
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return false;

	if (!LookupPrivilegeValue(NULL, SE_RESTORE_NAME, &sedebugnameValue))
	{
		CloseHandle(hToken);
		return false;
	}

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, NULL, NULL))
		CloseHandle(hToken);

	return true;
}
