/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Framework::FileSystem

***********************************************************************/

#ifndef NICE_FILEINFO
#define NICE_FILEINFO

#include "../Basic.h"
#include "../String.h"
#include "../Collections/List.h"
#include "../Stream/CharFormat.h"
#include "FilePath.h"
#include <Shlwapi.h>
namespace vl
{
	namespace filesystem
	{
		class FileInfo
		{
		 public:
			FileInfo();
			FileInfo(const FilePath& path);
			FileInfo(const WString& path);
			~FileInfo();
		 public:
			void SetPath(const WString& path);
			void SetPath(const FilePath& path);
		 public:
			bool Exists()const;
			bool IsFolder()const;
			bool IsFile()const;
			bool IsReadable()const;
			bool IsWritable()const;
			bool IsHidden()const;
			WString FileName();
			WString Extemsion();
			
			DateTime Created();
			DateTime LastModified();
			DateTime LastRead();
		 protected:
			bool getPropInfo();
		 private:
			WIN32_FILE_ATTRIBUTE_DATA attribute;
			FilePath filePath;
		};
		
		
		
		
		
	}
}

#endif
