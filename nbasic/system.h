#ifndef NICE_ENVIRONMENT
#define NICE_ENVIRONMENT
#include "String.h"

namespace vl
{
	namespace system
	{
	
		struct ProcessMemory
		{
			ProcessMemory()
			{
			}
			vuint		pageFaultCount;						// ȱҳ�жϴ���
			vuint64_t	peakWorkingSetSize;					// ʹ���ڴ�߷�
			vuint64_t	workingSetSize;						// ��ǰʹ�õ��ڴ�
			vuint64_t	quotaPeakPagedPoolUsage;			// ʹ��ҳ�滺��ظ߷�
			vuint64_t	quotaPagedPoolUsage;				// ʹ��ҳ�滺���
			vuint64_t	quotaPeakNonPagedPoolUsage;			// ʹ�÷Ƿ�ҳ����ظ߷�
			vuint64_t	quotaNonPagedPoolUsage;				// ʹ�÷Ƿ�ҳ�����
			vuint64_t	pagefileUsage;						// ʹ�÷�ҳ�ļ�
			vuint64_t	peakPagefileUsage;					// ʹ�÷�ҳ�ļ��߷�
		};
		
		class Process;
		class Process
		{
		 public:
			Process();
			~Process();
		 protected:
			void InitializeCurrent();
		 public:
			static vuint CurrentID();
			static bool GetMemoryInfo(ProcessMemory& memory);
			
		 private:
		 
		};
		
		
		
		
		//�������ܹ�
		enum eProcessorArchitecture
		{
			Inter,
			Mips,	//MIPS �Ƽ���˾������
			Alpha,	//DEC Alpha | Alpha AXP
			Ppc,	//PowerPC
			Shx,	//
			Arm,
			IA64,	//Ӣ�ض����ڼܹ���Intel Itanium architecture�� 64λָ�
			Alpha64,
			Msil,
			Amd64,
			Ia32onWin64,
			Neutral,
			PAUnknown,
		};
		
		enum eProcessorType
		{
			Intel386,
			Intel486,
			IntelPentium,
			IntelIa64,
			AmdX8664,
			MipsR4000,
			Alpha21064,
			Ppc601,
			Ppc603,
			Ppc604,
			Ppc620,
			HitachiSh3,
			HitachiSh3E,
			HitachiSh4,
			Motorola821,
			ShxSh3,
			ShxSh4,
			StrongArm,
			Arm720,
			Arm820,
			Arm920,
			Arm7Tdmi,
			Optil,
			PTUnknown,
		};
		
		struct GlobalMemory
		{
			GlobalMemory()
// 				: dwMemoryLoad(0),
// 				  ullTotalPhys(0),
// 				  ullAvailPhys(0),
// 				  ullTotalPageFile(0),
// 				  ullAvailPageFile(0),
// 				  ullTotalVirtual(0),
// 				  ullAvailVirtual(0),
// 				  ullAvailExtendedVirtual(0)
			{
			}
			vuint		dwMemoryLoad;
			vuint64_t	ullTotalPhys;
			vuint64_t	ullAvailPhys;
			vuint64_t	ullTotalPageFile;
			vuint64_t	ullAvailPageFile;
			vuint64_t	ullTotalVirtual;
			vuint64_t	ullAvailVirtual;
			vuint64_t	ullAvailExtendedVirtual;
		};
		
		struct DiskSpaceInfo
		{
			DiskSpaceInfo():
				available(0),
				total(0),
				free(0)
			{
			}
			WString disk;		//�̷�
			vuint64_t available;	//����(�ֽ�)
			vuint64_t total;
			vuint64_t free;
			
		};
		
		class System
		{
		 public:
			System();
			~System();
		 public:
			static DateTime Time();
			static WString ComputerName();
			static WString UserName();
			// 			static WString DnsHotsNameToComputer(WString dnsHost);
			//************************************
			// Method:    SystemWindowsDirectory
			// FullName:  vl::system::System::SystemWindowsDirectory
			// Access:    public static
			// Returns:   vl::WString
			// Qualifier:On a system that is running Terminal Services, each user has a unique Windows directory.
			//************************************
			static WString WindowsDirectory();
			//************************************
			// Method:    SystemWindowsDirectory
			// FullName:  vl::system::System::SystemWindowsDirectory
			// Access:    public static
			// Returns:   vl::WString
			// Qualifier: The system Windows directory is shared by all users,
			//			  so it is the directory where an application should store initialization and help files that apply to all users.
			//************************************
			static WString SystemWindowsDirectory();
			static WString CommandLine();
			static void Version();
			static void SystemInfo();
			static bool GetGlobalMemory(GlobalMemory& memory);
			static bool GetDiskSpaceInfo(DiskSpaceInfo& disk);
		 protected:
			static eProcessorArchitecture ProcessorArchitecture(vuint architecture);
			static eProcessorType ProcessorType(vuint type);
		};
	}
}

#endif