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
#include "PathFile.h"
namespace vl
{
	namespace filesystem
	{
		class FileInfo
		{
			struct FileAttrbutes
			{
				FileAttrbutes()
					: nattrbutes(0),
					  nsize(0) {}
				DateTime creation;
				DateTime lastAccess;
				DateTime lastWrite;
				
				FilePath filePath;
				vuint64_t nattrbutes;
				vuint64_t nsize;
			};
		 public:
			FileInfo();
			FileInfo(const PathFile& _pathFile);
			FileInfo(const FilePath& path);
			FileInfo(const WString& path);
			~FileInfo();
		 public:
			void SetFile(const WString& path);
			void SetFile(const FilePath& path);
			void SetPath(const WString& path);
			void SetPath(const FilePath& path);
		 public:
			bool Exists()const;
			bool IsFolder()const;
			bool IsFile()const;
			bool IsReadable()const;
			bool IsWritable()const;
			bool IsHidden()const;
			WString FileName()const;
			WString Extemsion()const;
			WString FullPath()const;
			
			DateTime Created()const;		//创建时间
			DateTime CreatedTime()const;
			DateTime LastModified()const;
			DateTime LastRead()const;
			vuint64_t Size()const;
		 protected:
			virtual bool Initialize();
		 protected:
			FileAttrbutes attrbute;
		};
		
	}
}

#endif
