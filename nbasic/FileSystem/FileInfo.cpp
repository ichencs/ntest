#include "FileInfo.h"
#include "../Locale.h"
#include "../Collections/OperationForEach.h"
#include "../Stream/FileStream.h"
#include "../Stream/Accessor.h"
#include "../Exception.h"
#if defined VCZH_MSVC
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#elif defined VCZH_GCC
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#endif

namespace vl
{
	namespace filesystem
	{
		using namespace collections;
		using namespace stream;
		
		FileInfo::FileInfo()
		{
			memset(&attribute, 0, sizeof(WIN32_FILE_ATTRIBUTE_DATA));
		}
		
		FileInfo::FileInfo(const FilePath& path)
		{
			filePath = path;
			getPropInfo();
		}
		
		FileInfo::FileInfo(const WString& path)
		{
			filePath = path;
			getPropInfo();
		}
		
		FileInfo::~FileInfo()
		{
		}
		
		
		void FileInfo::SetPath(const WString& path)
		{
			filePath = path;
			getPropInfo();
		}
		
		void FileInfo::SetPath(const FilePath& path)
		{
			filePath = path;
			getPropInfo();
		}
		
		bool FileInfo::Exists()const
		{
			return attribute.dwFileAttributes  != 0;
		}
		
		bool FileInfo::IsFolder()const
		{
			return (attribute.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
		}
		
		bool FileInfo::IsFile()const
		{
			return (attribute.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
		}
		
		bool FileInfo::IsReadable() const
		{
			return (attribute.dwFileAttributes & FILE_SHARE_READ) == 1;
		}
		
		bool FileInfo::IsWritable() const
		{
			return (attribute.dwFileAttributes & FILE_SHARE_WRITE) == 1;
		}
		
		bool FileInfo::IsHidden() const
		{
			return (attribute.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) == 1;
		}
		
		vl::WString FileInfo::FileName()
		{
			return ::PathFindFileName(filePath.GetFullPath().Buffer());
		}
		
		vl::WString FileInfo::Extemsion()
		{
			return ::PathFindExtension(filePath.GetFullPath().Buffer());
		}
		
		vl::DateTime FileInfo::Created()
		{
			return DateTime();
		}
		
		vl::DateTime FileInfo::LastModified()
		{
			return DateTime();
		}
		
		vl::DateTime FileInfo::LastRead()
		{
			return DateTime();
		}
		
		bool FileInfo::getPropInfo()
		{
			memset(&attribute, 0, sizeof(WIN32_FILE_ATTRIBUTE_DATA));
			BOOL result = GetFileAttributesEx(filePath.GetFullPath().Buffer(), GetFileExInfoStandard, &attribute);
			return result == TRUE;
		}
		
	}
}
