
#ifndef FILE_PATH
#define FILE_PATH
#include "../Basic.h"
#include "../String.h"
#include "../Collections/List.h"
#include "../Stream/CharFormat.h"
#include "../Path.h"

namespace vl
{

	namespace filesystem
	{
		/// <summary>A type representing a file path.</summary>
		class FilePath : public vl::path::Path
		{
		 protected:
			// 			WString						fullPath;
			
			void						Initialize()override;
			
			static void					GetPathComponents(WString path, collections::List<WString>& components);
			static WString				ComponentsToPath(const collections::List<WString>& components);
		 public:
#if defined VCZH_MSVC
			static const wchar_t		Delimiter = L'\\';
#endif
			
			/// <summary>Create a root path.</summary>
			FilePath();
			FilePath(const Path& _path);
			/// <summary>Create a file path.</summary>
			/// <param name="_filePath">Content of the file path. If it is a relative path, it will be converted to an absolute path.</param>
			FilePath(const WString& _filePath);
			/// <summary>Create a file path.</summary>
			/// <param name="_filePath">Content of the file path. If it is a relative path, it will be converted to an absolute path.</param>
			FilePath(const wchar_t* _filePath);
			/// <summary>Copy a file path.</summary>
			/// <param name="_filePath">The file path to copy.</param>
			FilePath(const FilePath& _filePath);
			~FilePath();
			
			FilePath&						operator=(const FilePath& filePath);
		 public:
			static FilePath CurrentPath();
			static FilePath ModuleFolder(void* pAddress = NULL);		//app(exe) path
			/// <summary>
			/// 通过当前模块（dll）的基地址获取dll路径
			/// </summary>
			/// <param name="pAddress">当前模块中的函数或变量地址</param>
			/// <param name="isDll"></param>
			/// <returns></returns>\
			/// VirtualQuery: 查询进程地址信息
			static FilePath ModulePath(void* pAddress = NULL);			//	NULL:EXE root  not null: dll root
			static FilePath TempPath();
		 public:
			static vint					Compare(const FilePath& a, const FilePath& b);
			bool						operator==(const FilePath& filePath)const
			{
				return Compare(*this, filePath) == 0;
			}
			bool						operator!=(const FilePath& filePath)const
			{
				return Compare(*this, filePath) != 0;
			}
			bool						operator< (const FilePath& filePath)const
			{
				return Compare(*this, filePath) < 0;
			}
			bool						operator<=(const FilePath& filePath)const
			{
				return Compare(*this, filePath) <= 0;
			}
			bool						operator> (const FilePath& filePath)const
			{
				return Compare(*this, filePath) > 0;
			}
			bool						operator>=(const FilePath& filePath)const
			{
				return Compare(*this, filePath) >= 0;
			}
			
			/// <summary>Concat an absolute path and a relative path.</summary>
			/// <returns>The result absolute path.</returns>
			/// <param name="relativePath">The relative path to concat.</param>
			FilePath					operator/(const WString& relativePath)const;
			
			/// <summary>Test if the file path is a file.</summary>
			/// <returns>Returns true if the file path is a file.</returns>
			bool						IsFile()const;
			/// <summary>Test if the file path is a folder.</summary>
			/// <returns>Returns true if the file path is a folder.</returns>
			bool						IsFolder()const;
			/// <summary>Test if the file path is a the root of all file system objects.</summary>
			/// <returns>Returns true if the file path is the root of all file system objects.</returns>
			bool						IsRoot()const;
			
			/// <summary>Get the last piece of names in the file path.</summary>
			/// <returns>The last piece of names in the file path.</returns>
			WString						GetName()const;
			/// <summary>Get the containing folder of this file path.</summary>
			/// <returns>The containing folder.</returns>
			FilePath					GetFolder()const;
			/// <summary>Get the content of the file path.</summary>
			/// <returns>The content of the file path.</returns>
			WString						GetFullPath()const;
			/// <summary>Calculate the relative path using a referencing folder.</summary>
			/// <returns>The relative path.</returns>
			/// <param name="_filePath">The referencing folder.</param>
			WString						GetRelativePathFor(const FilePath& _filePath);
			
		};
		
	}
	
}


#endif