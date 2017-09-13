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
namespace vl
{
	namespace filesystem
	{
	

		class FileInfo
		{
			struct FileAttrbutes
			{
				FileAttrbutes()
					:attrbutes(0),
					size(0) {}
				DateTime creation;
				DateTime lastAccess;
				DateTime lastWrite;

				FilePath filePath;
				vuint64_t attrbutes;
				vuint64_t size;
			};	
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
			vuint64_t Size();
		 protected:
			bool getProperty();
		 private:
			 FileAttrbutes attrbute;
		};
		
		
		
		
		
	}
}

#endif
