#include "Path.h"

#include <Shlwapi.h>
#include "Collections\List.h"
#pragma comment(lib, "Shlwapi.lib")

namespace vl
{
	namespace path
	{
		using namespace collections;
		
		Path::Path()
		{
		}
		
		
		Path::Path(const WString& _filePath)
			: fullPath(_filePath)
		{
			Initialize();
		}
		
		Path::Path(const wchar_t* _filePath)
			: fullPath(_filePath)
		{
			Initialize();
		}
		
		Path::Path(const Path& _filePath)
			: fullPath(_filePath.fullPath)
		{
			Initialize();
		}
		
		Path::~Path()
		{
		}
		
		vl::WString Path::UnquoteSpaces()
		{
			Array<wchar_t> buffer(fullPath.Length() + 1);
			wcscpy_s(&buffer[0], fullPath.Length() + 1, fullPath.Buffer());
			
			BOOL bRes = PathUnquoteSpaces(&buffer[0]);
			if (bRes)
			{
				fullPath = &buffer[0];
			}
			return fullPath;
		}
		
		bool Path::IsDirectory()
		{
			return PathIsDirectory(fullPath.Buffer()) != FALSE;
		}
		
		bool Path::IsFileSpec()
		{
			return PathIsFileSpec(fullPath.Buffer()) == TRUE;
		}
		
		bool Path::IsUNC()
		{
			return PathIsUNC(fullPath.Buffer()) == TRUE;
		}
		
		bool Path::IsUNCServer()
		{
			return PathIsUNCServer(fullPath.Buffer()) == TRUE;
		}
		
		bool Path::IsUNCServerShare()
		{
			return PathIsUNCServerShare(fullPath.Buffer()) == TRUE;
		}
		
		bool Path::IsURL()
		{
			return PathIsURL(fullPath.Buffer()) == TRUE;
		}
		
		bool Path::IsNetworkPath()
		{
			return PathIsNetworkPath(fullPath.Buffer()) == TRUE;
		}
		
		bool Path::IsPrefix(WString strPrefix)
		{
			return PathIsPrefix(fullPath.Buffer(), strPrefix.Buffer()) == TRUE;
		}
		
		bool Path::MatchSpec(WString strSpec)
		{
			return PathMatchSpec(fullPath.Buffer(), strSpec.Buffer()) == TRUE;
		}
		
		void Path::RemoveBackslash()
		{
			Array<wchar_t> buffer(fullPath.Length() + 1);
			wcscpy_s(&buffer[0], fullPath.Length() + 1, fullPath.Buffer());
			
			PathRemoveBackslash(&buffer[0]);
			{
				fullPath = &buffer[0];
			}
		}
		
		void Path::RemoveExtension()
		{
			Array<wchar_t> buffer(fullPath.Length() + 1);
			wcscpy_s(&buffer[0], fullPath.Length() + 1, fullPath.Buffer());
			
			PathRemoveExtension(&buffer[0]);
			{
				fullPath = &buffer[0];
			}
		}
		
		bool Path::RemoveFileSpec()
		{
			Array<wchar_t> buffer(fullPath.Length() + 1);
			wcscpy_s(&buffer[0], fullPath.Length() + 1, fullPath.Buffer());
			
			BOOL bRes = PathRemoveFileSpec(&buffer[0]);
			if (bRes)
			{
				fullPath = &buffer[0];
			}
			return bRes == TRUE;
		}
		
		vl::WString Path::FindFileName()const
		{
			WString name = PathFindFileName(fullPath.Buffer());
			return name;
		}
		
		vl::WString Path::GetFullPath() const
		{
			return fullPath;
		}
		
		bool Path::FileExists()
		{
			return PathFileExists(fullPath.Buffer()) == TRUE;
		}
		
		void Path::Initialize()
		{
		
		}
		
		vl::WString Path::FindExtension() const
		{
			return ::PathFindExtension(fullPath.Buffer());
		}
		
	}
}
