#include "PathFile.h"
#include <Windows.h>



namespace vl
{
	namespace filesystem
	{
		PathFile::PathFile()
		{
		}
		
		
		PathFile::PathFile(const PathFile& _pathFile)
			: filePath(_pathFile.filePath)
		{
		
		}
		
		PathFile::PathFile(const WString& _pathFile)
			: filePath(_pathFile)
		{
		
		}
		
		PathFile::PathFile(const wchar_t* _pathFile)
			: filePath(_pathFile)
		{
		
		}
		
		PathFile::PathFile(const FilePath& _filePath)
			: filePath(_filePath)
		{
		
		}
		
		PathFile::~PathFile()
		{
		}
		
		bool PathFile::IsFile()const
		{
			return filePath.IsFile();
		}
		
		bool PathFile::IsFolder()const
		{
			return filePath.IsFolder();
		}
		
		const vl::filesystem::FilePath& PathFile::GetFilePath() const
		{
			return filePath;
		}
		
		vl::WString PathFile::GetFullPath() const
		{
			return filePath.GetFullPath();
		}
		
		bool PathFile::Exists() const
		{
			return filePath.IsFolder();
		}
		
		vl::WString PathFile::GetName()const
		{
			return filePath.GetName();
		}
		
		bool PathFile::Rename(const WString& newName) const
		{
			WString oldFileName = filePath.GetFullPath();
			WString newFileName = (filePath.GetFolder() / newName).GetFullPath();
			return MoveFile(oldFileName.Buffer(), newFileName.Buffer()) != 0;
		}
		
	}
}
