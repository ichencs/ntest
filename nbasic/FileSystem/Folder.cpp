#include <Windows.h>
// #include <Shlwapi.h>
// #pragma comment(lib, "Shlwapi.lib")

#include "../Collections/OperationForEach.h"
#include "Folder.h"
// #include "FileSystem.h"

namespace vl
{
	namespace filesystem
	{
		using namespace collections;
		
		/***********************************************************************
		Folder
		***********************************************************************/
		
		Folder::Folder()
		{
		}
		
		Folder::Folder(const FilePath& _filePath)
			: filePath(_filePath)
		{
		}
		
		Folder::~Folder()
		{
		}
		
		const FilePath& Folder::GetFilePath()const
		{
			return filePath;
		}
		
		bool Folder::GetFolders(collections::List<Folder>& folders)const
		{
#if defined VCZH_MSVC
		
			if (filePath.IsRoot())
			{
				DWORD bufferSize = GetLogicalDriveStrings(0, NULL);
				
				if (bufferSize > 0)
				{
					Array<wchar_t> buffer(bufferSize);
					
					if (GetLogicalDriveStrings((DWORD)buffer.Count(), &buffer[0]) > 0)
					{
						wchar_t* begin = &buffer[0];
						wchar_t* end = begin + buffer.Count();
						
						while (begin < end && *begin)
						{
							WString driveString = begin;
							begin += driveString.Length() + 1;
							folders.Add(Folder(FilePath(driveString)));
						}
						
						return true;
					}
				}
				
				return false;
			}
			else
			{
				if (!Exists())
				{
					return false;
				}
				
				WIN32_FIND_DATA findData;
				HANDLE findHandle = INVALID_HANDLE_VALUE;
				
				while (true)
				{
					if (findHandle == INVALID_HANDLE_VALUE)
					{
						WString searchPath = (filePath / L"*").GetFullPath();
						findHandle = FindFirstFile(searchPath.Buffer(), &findData);
						
						if (findHandle == INVALID_HANDLE_VALUE)
						{
							break;
						}
					}
					else
					{
						BOOL result = FindNextFile(findHandle, &findData);
						
						if (result == 0)
						{
							FindClose(findHandle);
							break;
						}
					}
					
					if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						if (wcscmp(findData.cFileName, L".") != 0 && wcscmp(findData.cFileName, L"..") != 0)
						{
							folders.Add(Folder(filePath / findData.cFileName));
						}
					}
				}
				
				return true;
			}
			
#elif defined VCZH_GCC
			
			if (!Exists())
			{
				return false;
			}
			
			DIR* dir;
			AString searchPath = wtoa(filePath.GetFullPath());
			
			if ((dir = opendir(searchPath.Buffer())) == NULL)
			{
				return false;
			}
			
			struct dirent* entry;
			
			while ((entry = readdir(dir)) != NULL)
			{
				WString childName = atow(AString(entry->d_name));
				FilePath childFullPath = filePath / childName;
			
				if (childName != L"." && childName != L".." && childFullPath.IsFolder())
				{
					folders.Add(Folder(childFullPath));
				}
			}
			
			if (closedir(dir) != 0)
			{
				return false;
			}
			
			return true;
#endif
		}
		
		bool Folder::GetFiles(collections::List<File>& files)const
		{
#if defined VCZH_MSVC
		
			if (filePath.IsRoot())
			{
				return true;
			}
			
			if (!Exists())
			{
				return false;
			}
			
			WIN32_FIND_DATA findData;
			HANDLE findHandle = INVALID_HANDLE_VALUE;
			
			while (true)
			{
				if (findHandle == INVALID_HANDLE_VALUE)
				{
					WString searchPath = (filePath / L"*").GetFullPath();
					findHandle = FindFirstFile(searchPath.Buffer(), &findData);
					
					if (findHandle == INVALID_HANDLE_VALUE)
					{
						break;
					}
				}
				else
				{
					BOOL result = FindNextFile(findHandle, &findData);
					
					if (result == 0)
					{
						FindClose(findHandle);
						break;
					}
				}
				
				if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					files.Add(File(filePath / findData.cFileName));
				}
			}
			
			return true;
#elif defined VCZH_GCC
			
			if (!Exists())
			{
				return false;
			}
			
			DIR* dir;
			AString searchPath = wtoa(filePath.GetFullPath());
			
			if ((dir = opendir(searchPath.Buffer())) == NULL)
			{
				return false;
			}
			
			struct dirent* entry;
			
			while ((entry = readdir(dir)) != NULL)
			{
				FilePath childFullPath = filePath / (atow(AString(entry->d_name)));
			
				if (childFullPath.IsFile())
				{
					files.Add(File(childFullPath));
				}
			}
			
			if (closedir(dir) != 0)
			{
				return false;
			}
			
			return true;
#endif
		}
		
		bool Folder::Exists()const
		{
			return filePath.IsFolder();
		}
		
		bool Folder::Create(bool recursively)const
		{
			if (recursively)
			{
				FilePath folder = filePath.GetFolder();
				
				if (folder.IsFile())
				{
					return false;
				}
				
				if (folder.IsFolder())
				{
					return Create(false);
				}
				
				return Folder(folder).Create(true) && Create(false);
			}
			else
			{
#if defined VCZH_MSVC
				return CreateDirectory(filePath.GetFullPath().Buffer(), NULL) != 0;
#elif defined VCZH_GCC
				AString path = wtoa(filePath.GetFullPath());
				return mkdir(path.Buffer(), 0777) == 0;
#endif
			}
		}
		
		bool Folder::Delete(bool recursively)const
		{
			if (!Exists())
			{
				return false;
			}
			
			if (recursively)
			{
				List<Folder> folders;
				GetFolders(folders);
				FOREACH(Folder, folder, folders)
				{
					if (!folder.Delete(true))
					{
						return false;
					}
				}
				
				List<File> files;
				GetFiles(files);
				FOREACH(File, file, files)
				{
					if (!file.Delete())
					{
						return false;
					}
				}
				
				return Delete(false);
			}
			
#if defined VCZH_MSVC
			return RemoveDirectory(filePath.GetFullPath().Buffer()) != 0;
#elif defined VCZH_GCC
			AString path = wtoa(filePath.GetFullPath());
			return rmdir(path.Buffer()) == 0;
#endif
		}
		
		bool Folder::Rename(const WString& newName)const
		{
#if defined VCZH_MSVC
			WString oldFileName = filePath.GetFullPath();
			WString newFileName = (filePath.GetFolder() / newName).GetFullPath();
			return MoveFile(oldFileName.Buffer(), newFileName.Buffer()) != 0;
#elif defined VCZH_GCC
			AString oldFileName = wtoa(filePath.GetFullPath());
			AString newFileName = wtoa((filePath.GetFolder() / newName).GetFullPath());
			return rename(oldFileName.Buffer(), newFileName.Buffer()) == 0;
#endif
		}
	}
}