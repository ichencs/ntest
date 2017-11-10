#ifndef PATH_FILE
#define PATH_FILE

#include "..\Basic.h"
#include "FilePath.h"
namespace vl
{
	namespace filesystem
	{
		/*!
		 * \class: 	PathFile
		 *
		 * \brief:  带路径的文件
		 *			File/Folder 的基类
		 *
		 * \author: Chencs
		 * \date:	2017/11/10
		 */
		class PathFile abstract :
			public Object
		{
		 protected:
			FilePath					filePath;
		 protected:
			PathFile();
			PathFile(const wchar_t* _pathFile);
			PathFile(const WString& _pathFile);
			PathFile(const PathFile& _pathFile);
			PathFile(const FilePath& _filePath);
		 public:
		 
			virtual ~PathFile();
			bool						IsFile()const;
			bool						IsFolder()const;
			/// <summary>Get the file path of the folder.</summary>
			/// <returns>The file path.</returns>
			const FilePath&				GetFilePath()const;
			WString						GetFullPath()const;
			/// <summary>Test does the folder exist or not.</summary>
			/// <returns>Returns true if the folder exists.</returns>
			virtual bool				Exists()const;
			
			/// <summary>Rename the folder in the same folder.</summary>
			/// <returns>Returns true if this operation succeeded.</returns>
			/// <param name="newName">The new folder name.</param>
			WString						GetName()const;
			/// <summary>Rename the file in the same folder.</summary>
			/// <returns>Returns true if this operation succeeded.</returns>
			/// <param name="newName">The new file name.</param>
			bool						Rename(const WString& newName)const;
			
		 public:
		 
		 
		};
	}
	
}
#endif