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
		FileInfo::FileInfo()
		{
		}
		
		FileInfo::FileInfo(const FilePath& path)
		{
			attrbute.filePath = path;
			Initialize();
		}
		
		FileInfo::FileInfo(const WString& path)
		{
			attrbute.filePath = path;
			Initialize();
		}
		
		FileInfo::FileInfo(const PathFile& _pathFile)
		{
			attrbute.filePath = _pathFile.GetFilePath();
			Initialize();
		}
		
		FileInfo::~FileInfo()
		{
		}
		
		
		void FileInfo::SetFile(const WString& path)
		{
			attrbute.filePath = path;
			Initialize();
		}
		
		void FileInfo::SetFile(const FilePath& path)
		{
			attrbute.filePath = path;
			Initialize();
		}
		
		void FileInfo::SetPath(const WString& path)
		{
			attrbute.filePath = path;
			Initialize();
		}
		
		void FileInfo::SetPath(const FilePath& path)
		{
			attrbute.filePath = path;
			Initialize();
		}
		
		bool FileInfo::Exists()const
		{
			return attrbute.nattrbutes  != 0;
		}
		
		bool FileInfo::IsFolder()const
		{
			return (attrbute.nattrbutes & FILE_ATTRIBUTE_DIRECTORY) != 0;
		}
		
		bool FileInfo::IsFile()const
		{
			return Exists() && (attrbute.nattrbutes & FILE_ATTRIBUTE_DIRECTORY) == 0;
		}
		
		bool FileInfo::IsReadable() const
		{
			return (attrbute.nattrbutes & FILE_SHARE_READ) == 1;
		}
		
		bool FileInfo::IsWritable() const
		{
			return (attrbute.nattrbutes & FILE_SHARE_WRITE) == 1;
		}
		
		bool FileInfo::IsHidden() const
		{
			return (attrbute.nattrbutes & FILE_ATTRIBUTE_HIDDEN) == 1;
		}
		
		vl::WString FileInfo::FileName()const
		{
			return ::PathFindFileName(attrbute.filePath.GetFullPath().Buffer());
		}
		
		vl::WString FileInfo::Extemsion()const
		{
			// 			return ::PathFindExtension(attrbute.filePath.GetFullPath().Buffer());
			return attrbute.filePath.FindExtension();
		}
		
		vl::WString FileInfo::FullPath()const
		{
			return attrbute.filePath.GetFullPath();
		}
		
		vl::DateTime FileInfo::Created()const
		{
			return attrbute.creation;
		}
		
		vl::DateTime FileInfo::CreatedTime() const
		{
			return attrbute.creation;
		}
		
		vl::DateTime FileInfo::LastModified()const
		{
			return attrbute.lastWrite;
		}
		
		vl::DateTime FileInfo::LastRead()const
		{
			return attrbute.lastAccess;
		}
		
		vl::vuint64_t FileInfo::Size()const
		{
			return attrbute.nsize;
		}
		
		bool FileInfo::Initialize()
		{
			WIN32_FILE_ATTRIBUTE_DATA data = {0};
			// 			memset(&data, 0, sizeof(WIN32_FILE_ATTRIBUTE_DATA));
			BOOL result = GetFileAttributesEx(attrbute.filePath.GetFullPath().Buffer(),
			    GetFileExInfoStandard, &data);
			{
				attrbute.nattrbutes = data.dwFileAttributes;
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
				attrbute.nsize = largeInteger.QuadPart;
			}
			return result == TRUE;
		}
	}
}
