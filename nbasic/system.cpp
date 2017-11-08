#include "system.h"
#include <Windows.h>
#include "Collections\List.h"
#pragma warning(disable: 4996)
#include <Psapi.h>
#pragma comment(lib,"Psapi.lib")
// #pragma comment(lib,"kernel32.lib")

#define NICE_MAX_NAME 200
#define NICE_MAX_PATH 65536

namespace vl
{
	// 	extern DateTime DateTimeToSystemTime(const DateTime& dateTime);
	// 	extern DateTime SystemTimeToDateTime(const SYSTEMTIME& systemTime);
	
	namespace system
	{
		using namespace collections;
		
		struct ProcessData
		{
			HANDLE hProcess;
			ProcessData(HANDLE _handle)
				: hProcess(_handle)
			{
			
			}
			
		};
		
		Process::Process()
		{
			InitializeCurrent();
		}
		
		Process::~Process()
		{
		
		}
		
		
		void Process::InitializeCurrent()
		{
		
		}
		
		vl::vuint Process::CurrentID()
		{
			return ::GetCurrentProcessId();
		}
		
		// 	typedef struct _PROCESS_MEMORY_COUNTERS {
		// 		DWORD cb;                                                                            　　　　　　　　　　Size of the structure, in bytes.//潤更悶寄弌
		// 			DWORD PageFaultCount;　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　 Number of page faults. // 髪匈嶄僅肝方
		// 			SIZE_T PeakWorkingSetSize;　　　　　　　　　　　　　　　　　　　　　　　　　　　　 Peak working set size, in bytes. // 聞喘坪贋互桁
		// 			SIZE_T WorkingSetSize;　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　  Current working set size, in bytes. // 輝念聞喘議坪贋
		// 			SIZE_T QuotaPeakPagedPoolUsage;　　　　　　　　　　　　　　　　　　　　　　　　　 Peak paged pool usage, in bytes. // 聞喘匈中産贋学互桁
		// 			SIZE_T QuotaPagedPoolUsage;　　　　　　　　　　　　　　　　　　　　　　　　　　     Current paged pool usage, in bytes.// 聞喘匈中産贋学
		// 			SIZE_T QuotaPeakNonPagedPoolUsage;　　　　　　　　　　　　　　　　　　　　          Peak nonpaged pool usage, in bytes.// 聞喘掲蛍匈産贋学互桁
		// 			SIZE_T QuotaNonPagedPoolUsage;　　　　　　　　　　　　　　　　　　　　　　　　　　Current nonpaged pool usage, in bytes.// 聞喘掲蛍匈産贋学
		// 			SIZE_T PagefileUsage;　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　Current space allocated for the pagefile, in bytes.Those pages may or may not be in memory.// 聞喘蛍匈猟周
		// 			SIZE_T PeakPagefileUsage;　　　　　　　　　　　　　　　　　　　　　　　　　　　　　Peak space allocated for the pagefile, in bytes.// 聞喘蛍匈猟周互桁
		// 	} PROCESS_MEMORY_COUNTERS, *PPROCESS_MEMORY_COUNTERS;
		
		bool Process::GetMemoryInfo(ProcessMemory& memory)
		{
			HANDLE handle = ::GetCurrentProcess();
			PROCESS_MEMORY_COUNTERS info;
			memset(&info, 0, sizeof(PROCESS_MEMORY_COUNTERS));
			info.cb = sizeof(PROCESS_MEMORY_COUNTERS);
			BOOL bres = ::GetProcessMemoryInfo(handle, &info, sizeof(info));
			
			if (bres)
			{
				memory.pageFaultCount = info.PageFaultCount;
				memory.peakWorkingSetSize = info.PeakWorkingSetSize;
				memory.workingSetSize = info.WorkingSetSize;
				memory.quotaPeakPagedPoolUsage = info.QuotaPeakPagedPoolUsage;
				memory.quotaPagedPoolUsage = info.QuotaPagedPoolUsage;
				memory.quotaPeakNonPagedPoolUsage = info.QuotaPeakNonPagedPoolUsage;
				memory.quotaNonPagedPoolUsage = info.QuotaNonPagedPoolUsage;
				memory.pagefileUsage = info.PagefileUsage;
				memory.peakPagefileUsage = info.PeakPagefileUsage;
			}
			CloseHandle(handle);
			return bres == TRUE;
		}
		
		System::System()
		{
		}
		
		
		System::~System()
		{
		}
		
		DateTime System::Time()
		{
			return DateTime::UtcTime();
		}
		
		vl::WString System::ComputerName()
		{
			wchar_t name[NICE_MAX_NAME] = {0};
			DWORD dwNamelen = sizeof(name) / sizeof(*name);
			GetComputerName(name, &dwNamelen);
			return name;
		}
		
		vl::WString System::UserName()
		{
			wchar_t name[NICE_MAX_NAME] = { 0 };
			DWORD dwNamelen = sizeof(name) / sizeof(*name);
			GetUserName(name, &dwNamelen);
			return name;
		}
		
		
		WString System::WindowsDirectory()
		{
			wchar_t directory[NICE_MAX_PATH] = {0};
			GetWindowsDirectory(directory, sizeof(directory) / sizeof(*directory));
			return directory;
		}
		
		WString System::SystemWindowsDirectory()
		{
			wchar_t directory[NICE_MAX_PATH] = { 0 };
			GetSystemWindowsDirectory(directory, sizeof(directory) / sizeof(*directory));
			return directory;
		}
		
		vl::WString System::CommandLine()
		{
			WString string = ::GetCommandLine();
			return string;
		}
		
		void System::Version()
		{
			OSVERSIONINFOEX osver;
			ZeroMemory(&osver, sizeof(osver));
			osver.dwOSVersionInfoSize = sizeof(osver);
			::GetVersionEx((OSVERSIONINFO*)&osver);
		}
		
		void System::SystemInfo()
		{
			SYSTEM_INFO info;                                   //喘SYSTEM_INFO潤更登僅64了AMD侃尖匂
			::GetSystemInfo(&info);
			ProcessorArchitecture(info.wProcessorArchitecture);
			
			switch (info.dwProcessorType)
			{
				case PROCESSOR_INTEL_386:
					break;
					
				case PROCESSOR_INTEL_486:
					break;
					
				case PROCESSOR_INTEL_PENTIUM:
					break;
					
				case PROCESSOR_INTEL_IA64:
					break;
					
				case PROCESSOR_AMD_X8664:
					break;
					
				case PROCESSOR_MIPS_R4000:
					break;
					
				case PROCESSOR_ALPHA_21064:
					break;
					
				case PROCESSOR_PPC_601:
					break;
					
				case PROCESSOR_PPC_603:
					break;
					
				case PROCESSOR_PPC_604:
					break;
					
				case PROCESSOR_PPC_620:
					break;
					
				case PROCESSOR_HITACHI_SH3:
					break;
					
				case PROCESSOR_HITACHI_SH3E:
					break;
					
				case PROCESSOR_HITACHI_SH4:
					break;
					
				case PROCESSOR_MOTOROLA_821:
					break;
					
				case PROCESSOR_SHx_SH3:
					break;
					
				case PROCESSOR_SHx_SH4:
					break;
					
				case PROCESSOR_STRONGARM:
					break;
					
				case PROCESSOR_ARM720:
					break;
					
				case PROCESSOR_ARM820:
					break;
					
				case PROCESSOR_ARM920:
					break;
					
				case PROCESSOR_ARM_7TDMI:
					break;
					
				case PROCESSOR_OPTIL:
					break;
					
				default:
					break;
			}
		}
		
		
		bool System::GetGlobalMemory(GlobalMemory& memory)
		{
			MEMORYSTATUSEX memo;
			BOOL bres = GlobalMemoryStatusEx(&memo);
			
			if (bres)
			{
				memory.	dwMemoryLoad = memo.dwMemoryLoad;
				memory.ullTotalPhys = memo.ullTotalPhys;
				memory.ullAvailPhys = memo.ullAvailPhys;
				memory.ullTotalPageFile = memo.ullTotalPageFile;
				memory.ullAvailPageFile = memo.ullAvailPageFile;
				memory.ullTotalVirtual = memo.ullTotalVirtual;
				memory.ullAvailVirtual = memo.ullAvailVirtual;
				memory.ullAvailExtendedVirtual = memo.ullAvailExtendedVirtual;
			}
			
			return bres == TRUE;
		}
		
		bool System::GetDiskSpaceInfo(DiskSpaceInfo& disk)
		{
			ULARGE_INTEGER liFreeBytesAvailable, liTotalBytes, liTotalFreeBytes;
			BOOL bRes = GetDiskFreeSpaceEx(disk.disk.Buffer(), &liFreeBytesAvailable, &liTotalBytes, &liTotalFreeBytes);
			if (bRes)
			{
				disk.available = liFreeBytesAvailable.QuadPart;
				disk.total = liTotalBytes.QuadPart;
				disk.free = liTotalFreeBytes.QuadPart;
			}
			return bRes == TRUE;
		}
		
		eProcessorArchitecture System::ProcessorArchitecture(vuint architecture)
		{
			eProcessorArchitecture pa;
			
			switch (architecture)
			{
				case PROCESSOR_ARCHITECTURE_INTEL:
					pa = Inter;
					break;
					
				case PROCESSOR_ARCHITECTURE_MIPS:
					pa = Mips;
					break;
					
				case PROCESSOR_ARCHITECTURE_ALPHA:
					pa = Alpha;
					break;
					
				case PROCESSOR_ARCHITECTURE_PPC:
					pa = Ppc;
					break;
					
				case PROCESSOR_ARCHITECTURE_SHX:
					pa = Shx;
					break;
					
				case PROCESSOR_ARCHITECTURE_ARM:
					pa = Arm;
					break;
					
				case PROCESSOR_ARCHITECTURE_IA64:
					pa = IA64;
					break;
					
				case PROCESSOR_ARCHITECTURE_ALPHA64:
					pa = Alpha64;
					break;
					
				case PROCESSOR_ARCHITECTURE_MSIL:
					pa = Msil;
					break;
					
				case PROCESSOR_ARCHITECTURE_AMD64:
					pa = Amd64;
					break;
					
				case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64:
					pa = Ia32onWin64;
					break;
					
				// #ifdef _MSC_VER > 1800
				//
				// 		case PROCESSOR_ARCHITECTURE_NEUTRAL:
				// 			pa = Neutral;
				// 			break;
				// #endif
				
				default:
					pa = PAUnknown;
					break;
			}
			
			return pa;
		}
		
		eProcessorType System::ProcessorType(vuint type)
		{
			eProcessorType pt;
			
			switch (type)
			{
				case PROCESSOR_INTEL_386:
					pt = Intel386;
					break;
					
				case PROCESSOR_INTEL_486:
					pt = Intel486;
					break;
					
				case PROCESSOR_INTEL_PENTIUM:
					pt = IntelPentium;
					break;
					
				case PROCESSOR_INTEL_IA64:
					pt = IntelIa64;
					break;
					
				case PROCESSOR_AMD_X8664:
					pt = AmdX8664;
					break;
					
				case PROCESSOR_MIPS_R4000:
					pt = MipsR4000;
					break;
					
				case PROCESSOR_ALPHA_21064:
					pt = Alpha21064;
					break;
					
				case PROCESSOR_PPC_601:
					pt = Ppc601;
					break;
					
				case PROCESSOR_PPC_603:
					pt = Ppc603;
					break;
					
				case PROCESSOR_PPC_604:
					pt = Ppc604;
					break;
					
				case PROCESSOR_PPC_620:
					pt = Ppc620;
					break;
					
				case PROCESSOR_HITACHI_SH3:
					pt = HitachiSh3;
					break;
					
				case PROCESSOR_HITACHI_SH3E:
					pt = HitachiSh3E;
					break;
					
				case PROCESSOR_HITACHI_SH4:
					pt = HitachiSh4;
					break;
					
				case PROCESSOR_MOTOROLA_821:
					pt = Motorola821;
					break;
					
				case PROCESSOR_SHx_SH3:
					pt = ShxSh3;
					break;
					
				case PROCESSOR_SHx_SH4:
					pt = ShxSh4;
					break;
					
				case PROCESSOR_STRONGARM:
					pt = StrongArm;
					break;
					
				case PROCESSOR_ARM720:
					pt = Arm720;
					break;
					
				case PROCESSOR_ARM820:
					pt = Arm820;
					break;
					
				case PROCESSOR_ARM920:
					pt = Arm920;
					break;
					
				case PROCESSOR_ARM_7TDMI:
					pt = Arm7Tdmi;
					break;
					
				case PROCESSOR_OPTIL:
					pt = Optil;
					break;
					
				default:
					pt = PTUnknown;
					break;
			}
			
			return pt;
		}
		
	}
	
}
