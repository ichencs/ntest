
#ifndef FILEPATH
#define FILEPATH
#include "../Basic.h"
#include "../String.h"
#include "../Collections/List.h"
#include "../Stream/CharFormat.h"

namespace vl
{

	namespace filesystem
	{
		/// <summary>A type representing a file path.</summary>
		class FilePath : public Object
		{
			protected:
				WString						fullPath;
				
				void						Initialize();
				
				static void					GetPathComponents(WString path, collections::List<WString>& components);
				static WString				ComponentsToPath(const collections::List<WString>& components);
			public:
#if defined VCZH_MSVC
				static const wchar_t		Delimiter = L'\\';
#elif defined VCZH_GCC
				static const wchar_t		Delimiter = L'/';
#endif
				
				/// <summary>Create a root path.</summary>
				FilePath();
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
				
			public:
				static FilePath CurrentPath();
				static FilePath ModulePath(bool isDll = true);
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