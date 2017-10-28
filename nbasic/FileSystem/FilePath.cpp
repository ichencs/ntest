#include "FilePath.h"

#include "../Locale.h"
#include "../Collections/OperationForEach.h"
#include "../Stream/FileStream.h"
#include "../Stream/Accessor.h"
#include "../Exception.h"
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

#define NICE_MAX_PATH  65536


namespace vl
{
	namespace filesystem
	{
	
		using namespace collections;
		using namespace stream;
		
		// ReadDirectoryChangesW
		
		/***********************************************************************
		FilePath
		***********************************************************************/
		
#if defined VCZH_GCC
		const wchar_t FilePath::Delimiter;
#endif
		
		void FilePath::Initialize()
		{
			{
				Array<wchar_t> buffer(fullPath.Length() + 1);
#if defined VCZH_MSVC
				wcscpy_s(&buffer[0], fullPath.Length() + 1, fullPath.Buffer());
#elif defined VCZH_GCC
				wcscpy(&buffer[0], fullPath.Buffer());
#endif
				
				for (vint i = 0; i < buffer.Count(); i++)
				{
					if (buffer[i] == L'\\' || buffer[i] == L'/')
					{
						buffer[i] = Delimiter;
					}
				}
				
				fullPath = &buffer[0];
			}
			
#if defined VCZH_MSVC
			
			if (fullPath != L"")
			{
				if (fullPath.Length() < 2 || fullPath[1] != L':')
				{
					wchar_t buffer[MAX_PATH + 1] = { 0 };
					DWORD result = GetCurrentDirectory(sizeof(buffer) / sizeof(*buffer), buffer);
					
					if (result > MAX_PATH + 1 || result == 0)
					{
						throw ArgumentException(L"Failed to call GetCurrentDirectory.", L"vl::filesystem::FilePath::Initialize", L"");
					}
					
					fullPath = WString(buffer) + L"\\" + fullPath;
				}
				
				{
					wchar_t buffer[MAX_PATH + 1] = { 0 };
					
					if (fullPath.Length() == 2 && fullPath[1] == L':')
					{
						fullPath += L"\\";
					}
					
					DWORD result = GetFullPathName(fullPath.Buffer(), sizeof(buffer) / sizeof(*buffer), buffer, NULL);
					
					if (result > MAX_PATH + 1 || result == 0)
					{
						throw ArgumentException(L"The path is illegal.", L"vl::filesystem::FilePath::FilePath", L"_filePath");
					}
					
					fullPath = buffer;
				}
			}
			
#endif
			
			if (fullPath != L"/" && fullPath.Length() > 0 && fullPath[fullPath.Length() - 1] == Delimiter)
			{
				fullPath = fullPath.Left(fullPath.Length() - 1);
			}
		}
		
		FilePath::FilePath()
		{
		}
		
		FilePath::FilePath(const WString& _filePath)
			: fullPath(_filePath)
		{
			Initialize();
		}
		
		FilePath::FilePath(const wchar_t* _filePath)
			: fullPath(_filePath)
		{
			Initialize();
		}
		
		FilePath::FilePath(const FilePath& _filePath)
			: fullPath(_filePath.fullPath)
		{
			Initialize();
		}
		
		FilePath::~FilePath()
		{
		}
		
		FilePath FilePath::CurrentPath()
		{
			wchar_t buffer[NICE_MAX_PATH] = { 0 };
			::GetCurrentDirectory(sizeof(buffer) / sizeof(*buffer), &buffer[0]);
			return &buffer[0];
		}
		
		HMODULE GetSafeModuleHandle()
		{
			MEMORY_BASIC_INFORMATION mbi = {0};			//通过函数指针地址，获取dll基地址（HMODULE）
			return ((::VirtualQuery(GetSafeModuleHandle, &mbi, sizeof(mbi)) != 0) ? (HMODULE)mbi.AllocationBase : NULL);
		}
		
		FilePath FilePath::ModulePath()
		{
			return ModulePath(NULL);
		}
		
		FilePath FilePath::ModulePath(void* pAddress)
		{
			wchar_t buffer[NICE_MAX_PATH] = { 0 };
			HMODULE hmodule = NULL;
			if (pAddress)
			{
				MEMORY_BASIC_INFORMATION mbi = { 0 };			//通过函数指针地址，获取dll基地址（HMODULE）
				HMODULE hBaseAddress = (::VirtualQuery(pAddress, &mbi, sizeof(mbi)) != 0) ?
				  (HMODULE)mbi.AllocationBase : NULL;
				hmodule = hBaseAddress;
				
			}
			::GetModuleFileName(hmodule, buffer, sizeof(buffer) / sizeof(*buffer));
			return buffer;
		}
		
		FilePath FilePath::TempPath()
		{
			wchar_t buffer[NICE_MAX_PATH] = { 0 };
			::GetTempPath(sizeof(buffer) / sizeof(*buffer), buffer);
			return buffer;
		}
		
		vint FilePath::Compare(const FilePath& a, const FilePath& b)
		{
			return WString::Compare(a.fullPath, b.fullPath);
		}
		
		FilePath FilePath::operator/(const WString& relativePath)const
		{
			if (IsRoot())
			{
				return relativePath;
			}
			else
			{
				return fullPath + L"/" + relativePath;
			}
		}
		
		bool FilePath::IsFile()const
		{
#if defined VCZH_MSVC
			WIN32_FILE_ATTRIBUTE_DATA info;
			BOOL result = GetFileAttributesEx(fullPath.Buffer(), GetFileExInfoStandard, &info);
			
			if (!result)
			{
				return false;
			}
			
			return (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
#endif
		}
		
		bool FilePath::IsFolder()const
		{
#if defined VCZH_MSVC
			WIN32_FILE_ATTRIBUTE_DATA info;
			BOOL result = GetFileAttributesEx(fullPath.Buffer(), GetFileExInfoStandard, &info);
			
			if (!result)
			{
				return false;
			}
			
			return (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
#endif
		}
		
		bool FilePath::IsRoot()const
		{
#if defined VCZH_MSVC
			return fullPath == L"";
#endif
		}
		
		WString FilePath::GetName()const
		{
			WString delimiter = Delimiter;
			collections::Pair<vint, vint> index = INVLOC.FindLast(fullPath, delimiter, Locale::None);
			
			if (index.key == -1)
			{
				return fullPath;
			}
			
			return fullPath.Right(fullPath.Length() - index.key - 1);
		}
		
		FilePath FilePath::GetFolder()const
		{
			WString delimiter = Delimiter;
			collections::Pair<vint, vint> index = INVLOC.FindLast(fullPath, delimiter, Locale::None);
			
			if (index.key == -1)
			{
				return FilePath();
			}
			
			return fullPath.Left(index.key);
		}
		
		WString FilePath::GetFullPath()const
		{
			return fullPath;
		}
		
		WString FilePath::GetRelativePathFor(const FilePath& _filePath)
		{
			if (fullPath.Length() == 0 || _filePath.fullPath.Length() == 0 || fullPath[0] != _filePath.fullPath[0])
			{
				return _filePath.fullPath;
			}
			
#if defined VCZH_MSVC
			wchar_t buffer[MAX_PATH + 1] = { 0 };
			PathRelativePathTo(
			  buffer,
			  fullPath.Buffer(),
			  (IsFolder() ? FILE_ATTRIBUTE_DIRECTORY : 0),
			  _filePath.fullPath.Buffer(),
			  (_filePath.IsFolder() ? FILE_ATTRIBUTE_DIRECTORY : 0)
			);
			return buffer;
#endif
		}
		
		void FilePath::GetPathComponents(WString path, collections::List<WString>& components)
		{
			WString pathRemaining = path;
			WString delimiter = Delimiter;
			
			components.Clear();
			
			while (true)
			{
				collections::Pair<vint, vint> index = INVLOC.FindFirst(pathRemaining, delimiter, Locale::None);
				
				if (index.key == -1)
				{
					break;
				}
				
				if (index.key != 0)
				{
					components.Add(pathRemaining.Left(index.key));
				}
				else
				{
#if defined VCZH_GCC
					// Unix absolute path starting with "/"
					// components[0] will be L"/"
					components.Add(delimiter);
#elif defined VCZH_MSVC
					
					if (pathRemaining.Length() >= 2 && pathRemaining[1] == Delimiter)
					{
						// Windows UNC Path starting with "\\"
						// components[0] will be L"\\"
						components.Add(L"\\");
						index.value++;
					}
					
#endif
				}
				
				pathRemaining = pathRemaining.Right(pathRemaining.Length() - (index.key + index.value));
			}
			
			if (pathRemaining.Length() != 0)
			{
				components.Add(pathRemaining);
			}
		}
		
		WString FilePath::ComponentsToPath(const collections::List<WString>& components)
		{
			WString result;
			WString delimiter = Delimiter;
			
			int i = 0;
			
#if defined VCZH_GCC
			
			// For Unix-like OSes, if first component is "/" then take it as absolute path
			if (components.Count() > 0 && components[0] == delimiter)
			{
				result += delimiter;
				i++;
			}
			
#elif defined VCZH_MSVC
			
			// For Windows, if first component is "\\" then it is an UNC path
			if (components.Count() > 0 && components[0] == L"\\")
			{
				result += delimiter;
				i++;
			}
			
#endif
			
			for (; i < components.Count(); i++)
			{
				result += components[i];
				
				if (i + 1 < components.Count())
				{
					result += delimiter;
				}
			}
			
			return result;
		}
	}
}
