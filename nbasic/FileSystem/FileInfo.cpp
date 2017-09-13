#include "../Locale.h"
#include "../Collections/OperationForEach.h"
#include "../Stream/FileStream.h"
#include "../Stream/Accessor.h"
#include "../Exception.h"
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include "FileInfo.h"

namespace vl
{
	namespace filesystem
	{
		using namespace collections;
		using namespace stream;
		
		FileInfo::FileInfo()
		{
		}
		
		FileInfo::FileInfo(const FilePath& path)
		{
			attrbute.filePath = path;
			getProperty();
		}
		
		FileInfo::FileInfo(const WString& path)
		{
			attrbute.filePath = path;
			getProperty();
		}
		
		FileInfo::~FileInfo()
		{
		}
		
		
		void FileInfo::SetPath(const WString& path)
		{
			attrbute.filePath = path;
			getProperty();
		}
		
		void FileInfo::SetPath(const FilePath& path)
		{
			attrbute.filePath = path;
			getProperty();
		}
		
		bool FileInfo::Exists()const
		{
			return attrbute.attrbutes  != 0;
		}
		
		bool FileInfo::IsFolder()const
		{
			return (attrbute.attrbutes & FILE_ATTRIBUTE_DIRECTORY) != 0;
		}
		
		bool FileInfo::IsFile()const
		{
			return Exists() && (attrbute.attrbutes & FILE_ATTRIBUTE_DIRECTORY) == 0;
		}
		
		bool FileInfo::IsReadable() const
		{
			return (attrbute.attrbutes & FILE_SHARE_READ) == 1;
		}
		
		bool FileInfo::IsWritable() const
		{
			return (attrbute.attrbutes & FILE_SHARE_WRITE) == 1;
		}
		
		bool FileInfo::IsHidden() const
		{
			return (attrbute.attrbutes & FILE_ATTRIBUTE_HIDDEN) == 1;
		}
		
		vl::WString FileInfo::FileName()
		{
			return ::PathFindFileName(attrbute.filePath.GetFullPath().Buffer());
		}
		
		vl::WString FileInfo::Extemsion()
		{
			return ::PathFindExtension(attrbute.filePath.GetFullPath().Buffer());
		}
		
		vl::DateTime FileInfo::Created()
		{
			return attrbute.creation;
		}
		
		vl::DateTime FileInfo::LastModified()
		{
			return attrbute.lastWrite;
		}
		
		vl::DateTime FileInfo::LastRead()
		{
			return attrbute.lastAccess;
		}
		
		vl::vuint64_t FileInfo::Size()
		{
			return attrbute.size;
		}

		bool FileInfo::getProperty()
		{
			WIN32_FILE_ATTRIBUTE_DATA data;
			memset(&data, 0, sizeof(WIN32_FILE_ATTRIBUTE_DATA));
			BOOL result = GetFileAttributesEx(attrbute.filePath.GetFullPath().Buffer(), GetFileExInfoStandard, &data);
			{
				attrbute.attrbutes = data.dwFileAttributes;
				ULARGE_INTEGER largeInteger;
				largeInteger.HighPart = data.ftCreationTime.dwHighDateTime;
				largeInteger.LowPart = data.ftCreationTime.dwLowDateTime;
				attrbute.creation = DateTime::FromFileTime(largeInteger.QuadPart);

				largeInteger.HighPart = data.ftLastAccessTime.dwHighDateTime;
				largeInteger.LowPart = data.ftLastAccessTime.dwLowDateTime;
				attrbute.lastAccess = DateTime::FromFileTime(largeInteger.QuadPart);

				largeInteger.HighPart = data.ftLastWriteTime.dwHighDateTime;
				largeInteger.LowPart = data.ftLastWriteTime.dwLowDateTime;
				attrbute.lastWrite = DateTime::FromFileTime(largeInteger.QuadPart);

				largeInteger.HighPart = data.nFileSizeHigh;
				largeInteger.LowPart = data.nFileSizeLow;
				attrbute.size = largeInteger.QuadPart;
			}
			return result == TRUE;
		}
		
	}
}
