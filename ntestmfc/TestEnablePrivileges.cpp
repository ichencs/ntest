#include"stdafx.h"
// Privileges

#define SE_MIN_WELL_KNOWN_PRIVILEGE (2L)
#define SE_CREATE_TOKEN_PRIVILEGE (2L)
#define SE_ASSIGNPRIMARYTOKEN_PRIVILEGE (3L)
#define SE_LOCK_MEMORY_PRIVILEGE (4L)
#define SE_INCREASE_QUOTA_PRIVILEGE (5L)
#define SE_MACHINE_ACCOUNT_PRIVILEGE (6L)
#define SE_TCB_PRIVILEGE (7L)
#define SE_SECURITY_PRIVILEGE (8L)
#define SE_TAKE_OWNERSHIP_PRIVILEGE (9L)
#define SE_LOAD_DRIVER_PRIVILEGE (10L)
#define SE_SYSTEM_PROFILE_PRIVILEGE (11L)
#define SE_SYSTEMTIME_PRIVILEGE (12L)
#define SE_PROF_SINGLE_PROCESS_PRIVILEGE (13L)
#define SE_INC_BASE_PRIORITY_PRIVILEGE (14L)
#define SE_CREATE_PAGEFILE_PRIVILEGE (15L)
#define SE_CREATE_PERMANENT_PRIVILEGE (16L)
#define SE_BACKUP_PRIVILEGE (17L)
#define SE_RESTORE_PRIVILEGE (18L)
#define SE_SHUTDOWN_PRIVILEGE (19L)
#define SE_DEBUG_PRIVILEGE (20L)
#define SE_AUDIT_PRIVILEGE (21L)
#define SE_SYSTEM_ENVIRONMENT_PRIVILEGE (22L)
#define SE_CHANGE_NOTIFY_PRIVILEGE (23L)
#define SE_REMOTE_SHUTDOWN_PRIVILEGE (24L)
#define SE_UNDOCK_PRIVILEGE (25L)
#define SE_SYNC_AGENT_PRIVILEGE (26L)
#define SE_ENABLE_DELEGATION_PRIVILEGE (27L)
#define SE_MANAGE_VOLUME_PRIVILEGE (28L)
#define SE_IMPERSONATE_PRIVILEGE (29L)
#define SE_CREATE_GLOBAL_PRIVILEGE (30L)
#define SE_TRUSTED_CREDMAN_ACCESS_PRIVILEGE (31L)
#define SE_RELABEL_PRIVILEGE (32L)
#define SE_INC_WORKING_SET_PRIVILEGE (33L)
#define SE_TIME_ZONE_PRIVILEGE (34L)
#define SE_CREATE_SYMBOLIC_LINK_PRIVILEGE (35L)
#define SE_MAX_WELL_KNOWN_PRIVILEGE SE_CREATE_SYMBOLIC_LINK_PRIVILEGE

#define PF_INIT_OR_SET_STATUS(proc, name)  do {PF_INIT(proc, name);                            \
	if ((pf##proc == NULL) && (NT_SUCCESS(status))) status = STATUS_NOT_IMPLEMENTED; } while(0)

#ifdef _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <windows.h>
#include "process.h"
#include <inttypes.h>


// #define PF_INIT_OR_OUT(proc, name)			do {PF_INIT(proc, name);         \
// 	if (pf##proc == NULL) {uprintf("Unable to locate %s() in %s.dll: %s\n",  \
// 	#proc, #name, WindowsErrorString()); goto out;} } while(0)
// #define PF_DECL(proc)						static proc##_t pf##proc = NULL
// 
// PF_TYPE_DECL(NTAPI, NTSTATUS, NtClose, (HANDLE));
// 
// /**
// * Increase the privileges of the current application.
// *
// * \return TRUE if the request was successful.
// */
// BOOL EnablePrivileges(void)
// {
// 	// List of the privileges we require. A list of requestable privileges can
// 	// be obtained at https://technet.microsoft.com/en-us/library/dn221963.aspx
// 	const DWORD requestedPrivileges[] = {
// 		SE_DEBUG_PRIVILEGE,
// 	};
// 	NTSTATUS status = STATUS_NOT_IMPLEMENTED;
// 	HANDLE tokenHandle;
// 
// 	PF_INIT_OR_OUT(NtClose, NtDll);
// 	PF_INIT_OR_OUT(NtOpenProcessToken, NtDll);
// 	PF_INIT_OR_OUT(NtAdjustPrivilegesToken, NtDll);
// 
// 	status = pfNtOpenProcessToken(NtCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &tokenHandle);
// 
// 	if (NT_SUCCESS(status)) {
// 		CHAR privilegesBuffer[FIELD_OFFSET(TOKEN_PRIVILEGES, Privileges) +
// 			sizeof(LUID_AND_ATTRIBUTES) * ARRAYSIZE(requestedPrivileges)];
// 		PTOKEN_PRIVILEGES privileges;
// 		ULONG i;
// 
// 		privileges = (PTOKEN_PRIVILEGES)privilegesBuffer;
// 		privileges->PrivilegeCount = ARRAYSIZE(requestedPrivileges);
// 
// 		for (i = 0; i < privileges->PrivilegeCount; i++) {
// 			privileges->Privileges[i].Attributes = SE_PRIVILEGE_ENABLED;
// 			privileges->Privileges[i].Luid.HighPart = 0;
// 			privileges->Privileges[0].Luid.LowPart = requestedPrivileges[i];
// 		}
// 
// 		status = pfNtAdjustPrivilegesToken(tokenHandle, FALSE, privileges, 0, NULL, NULL);
// 
// 		pfNtClose(tokenHandle);
// 	}
// 
// out:
// 	if (!NT_SUCCESS(status))
// 		ubprintf("NOTE: Could not set process privileges: %s", NtStatusError(status));
// 	return NT_SUCCESS(status);
// }
