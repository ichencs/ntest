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
			
#elif defined VCZH_GCC
			
			if (fullPath.Length() == 0)
			{
				fullPath = L"/";
			}
			
			if (fullPath[0] != Delimiter)
			{
				char buffer[PATH_MAX] = { 0 };
				getcwd(buffer, PATH_MAX);
				fullPath = atow(AString(buffer)) + Delimiter + fullPath;
			}
			
			{
				collections::List<WString> components;
				GetPathComponents(fullPath, components);
			
				for (int i = 0; i < components.Count(); i++)
				{
					if (components[i] == L".")
					{
						components.RemoveAt(i);
						i--;
					}
					else
						if (components[i] == L"..")
						{
							if (i > 0)
							{
								components.RemoveAt(i);
								components.RemoveAt(i - 1);
								i -= 2;
							}
							else
							{
								throw ArgumentException(L"Illegal path.");
							}
						}
				}
			
				fullPath = ComponentsToPath(components);
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
		
		FilePath FilePath::TheAppPath()
		{
			wchar_t buffer[NICE_MAX_PATH] = { 0 };
			::GetModuleFileName(NULL, buffer, sizeof(buffer) / sizeof(*buffer));
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
#elif defined VCZH_GCC
			struct stat info;
			AString path = wtoa(fullPath);
			int result = stat(path.Buffer(), &info);
			
			if (result != 0)
			{
				return false;
			}
			else
			{
				return S_ISREG(info.st_mode);
			}
			
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
#elif defined VCZH_GCC
			struct stat info;
			AString path = wtoa(fullPath);
			int result = stat(path.Buffer(), &info);
			
			if (result != 0)
			{
				return false;
			}
			else
			{
				return S_ISDIR(info.st_mode);
			}
			
#endif
		}
		
		bool FilePath::IsRoot()const
		{
#if defined VCZH_MSVC
			return fullPath == L"";
#elif defined VCZH_GCC
			return fullPath == L"/";
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
#elif defined VCZH_GCC
			collections::List<WString> srcComponents, tgtComponents, resultComponents;
			GetPathComponents(IsFolder() ? fullPath : GetFolder().GetFullPath(), srcComponents);
			GetPathComponents(_filePath.fullPath, tgtComponents);
			
			int minLength = srcComponents.Count() <= tgtComponents.Count() ? srcComponents.Count() : tgtComponents.Count();
			int lastCommonComponent = 0;
			
			for (int i = 0; i < minLength; i++)
			{
				if (srcComponents[i] == tgtComponents[i])
				{
					lastCommonComponent = i;
				}
				else
				{
					break;
				}
			}
			
			for (int i = lastCommonComponent + 1; i < srcComponents.Count(); i++)
			{
				resultComponents.Add(L"..");
			}
			
			for (int i = lastCommonComponent + 1; i < tgtComponents.Count(); i++)
			{
				resultComponents.Add(tgtComponents[i]);
			}
			
			return ComponentsToPath(resultComponents);
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
