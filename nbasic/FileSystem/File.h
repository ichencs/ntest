#ifndef NICE_FILE
#define NICE_FILE
#include "../Basic.h"
#include "../String.h"
#include "../Collections/List.h"
#include "../Stream/CharFormat.h"
// #include "FilePath.h"
#include "PathFile.h"

namespace vl
{
	namespace filesystem
	{
		/// <summary>Representing a file reference.</summary>
		class File : public PathFile
		{
		
		 public:
			/// <summary>Create an empty reference.</summary>
			File();
			/// <summary>Create a reference to a specified file.</summary>
			/// <param name="_filePath">The specified file.</param>
			File(const File& _file);
			File(const wchar_t* _filePath);
			File(const WString& _filePath);
			File(const FilePath& _filePath);
			File(const PathFile& _filePath);
			~File();
			
			// 			/// <summary>Get the file path of the file.</summary>
			// 			/// <returns>The file path.</returns>
			// 			const FilePath&				GetFilePath()const;
			
			/// <summary>Get the content of the file as text with encoding testing.</summary>
			/// <returns>The content of the file.</returns>
			/// <returns>Returns false if this operation succeeded.</returns>
			/// <param name="text">The content of the file.</param>
			/// <param name="encoding">The encoding.</param>
			/// <param name="bom">True if there is BOM.</param>
			bool						ReadAllTextWithEncodingTesting(WString& text, stream::BomEncoder::Encoding& encoding, bool& containsBom);
			/// <summary>Get the content of the file as text.</summary>
			/// <returns>The content of the file.</returns>
			WString						ReadAllTextByBom()const;
			/// <summary>Get the content of the file as text.</summary>
			/// <returns>Returns false if this operation succeeded.</returns>
			/// <param name="text">The content of the file.</param>
			bool						ReadAllTextByBom(WString& text)const;
			/// <summary>Get the content of the file as text.</summary>
			/// <returns>Returns false if this operation succeeded.</returns>
			/// <param name="lines">The content of the file.</param>
			bool						ReadAllLinesByBom(collections::List<WString>& lines)const;
			
			/// <summary>Write text to the file.</summary>
			/// <returns>Returns false if this operation succeeded.</returns>
			/// <param name="text">The text to write.</param>
			/// <param name="bom">Set to true to add a corresponding BOM at the beginning of the file according to the encoding.</param>
			/// <param name="encoding">The text encoding.</param>
			bool						WriteAllText(const WString& text, bool bom = true, stream::BomEncoder::Encoding encoding = stream::BomEncoder::Utf16);
			/// <summary>Write text to the file.</summary>
			/// <returns>Returns false if this operation succeeded.</returns>
			/// <param name="lines">The text to write.</param>
			/// <param name="bom">Set to true to add a corresponding BOM at the beginning of the file according to the encoding.</param>
			/// <param name="encoding">The text encoding.</param>
			bool						WriteAllLines(collections::List<WString>& lines, bool bom = true, stream::BomEncoder::Encoding encoding = stream::BomEncoder::Utf16);
			
			/// <summary>Test does the file exist or not.</summary>
			/// <returns>Returns true if the file exists.</returns>
			bool						Exists()const;
			/// <summary>Delete the file.</summary>
			/// <returns>Returns true if this operation succeeded.</returns>
			bool						Delete()const;
			/// <summary>Rename the file in the same folder.</summary>
			/// <returns>Returns true if this operation succeeded.</returns>
			/// <param name="newName">The new file name.</param>
			// 			bool						Rename(const WString& newName)const;
			// 			WString						GetName();
		};
		
	}
}



#endif