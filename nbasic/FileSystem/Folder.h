#ifndef NICE_FOLDER
#define NICE_FOLDER

#include "../Basic.h"
#include "../String.h"
#include "../Collections/List.h"
#include "../Stream/CharFormat.h"
#include "FilePath.h"
#include "File.h"
// #include "FileSystem.h"


namespace vl
{
	namespace filesystem
	{
		/// <summary>Representing a folder reference.</summary>
		class Folder : public Object
		{
			private:
				FilePath					filePath;
				
			public:
				/// <summary>Create a root reference.</summary>
				Folder();
				/// <summary>Create a reference to a specified folder.</summary>
				/// <param name="_filePath">The specified folder.</param>
				Folder(const WString& _filePath);
				Folder(const FilePath& _filePath);
				Folder(const wchar_t* _filePath);

				~Folder();
				
				/// <summary>Get the file path of the folder.</summary>
				/// <returns>The file path.</returns>
				const FilePath&				GetFilePath()const;
				/// <summary>Get all folders in this folder.</summary>
				/// <returns>Returns true if this operation succeeded.</returns>
				/// <param name="folders">All folders.</param>
				bool						GetFolders(collections::List<Folder>& folders)const;
				/// <summary>Get all files in this folder.</summary>
				/// <returns>Returns true if this operation succeeded.</returns>
				/// <param name="files">All files.</param>
				bool						GetFiles(collections::List<File>& files)const;
				
				/// <summary>Test does the folder exist or not.</summary>
				/// <returns>Returns true if the folder exists.</returns>
				bool						Exists()const;
				/// <summary>Create the folder.</summary>
				/// <returns>Returns true if this operation succeeded.</returns>
				/// <param name="recursively">Set to true to create all parent folders if necessary.</param>
				bool						Create(bool recursively)const;
				/// <summary>Delete the folder.</summary>
				/// <returns>Returns true if this operation succeeded.</returns>
				/// <param name="recursively">Set to true to delete everything in the folder.</param>
				bool						Delete(bool recursively)const;
				/// <summary>Rename the folder in the same folder.</summary>
				/// <returns>Returns true if this operation succeeded.</returns>
				/// <param name="newName">The new folder name.</param>
				bool						Rename(const WString& newName)const;

				WString						GetName();
		};
	}
	
}
#endif // !FOLDER
