#include "File.h"
#include "../Collections/OperationForEach.h"
#include "../Stream/FileStream.h"
#include "../Stream/Accessor.h"
#include <Windows.h>
// #include <Shlwapi.h>
// #pragma comment(lib, "Shlwapi.lib")

namespace vl
{
	namespace filesystem
	{
		using namespace collections;
		using namespace stream;
		
		/***********************************************************************
		File
		***********************************************************************/
		
		File::File()
		{
		}
		
		File::File(const FilePath& _filePath)
			: filePath(_filePath)
		{
		}
		
		File::~File()
		{
		}
		
		const FilePath& File::GetFilePath()const
		{
			return filePath;
		}
		
		bool File::ReadAllTextWithEncodingTesting(WString& text, stream::BomEncoder::Encoding& encoding, bool& containsBom)
		{
			Array<unsigned char> buffer;
			{
				FileStream fileStream(filePath.GetFullPath(), FileStream::ReadOnly);
				
				if (!fileStream.IsAvailable())
				{
					return false;
				}
				
				if (fileStream.Size() == 0)
				{
					text = L"";
					encoding = BomEncoder::Mbcs;
					containsBom = false;
					return true;
				}
				
				buffer.Resize((vint)fileStream.Size());
				vint count = fileStream.Read(&buffer[0], buffer.Count());
				CHECK_ERROR(count == buffer.Count(), L"vl::filesystem::File::ReadAllTextWithEncodingTesting(WString&, BomEncoder::Encoding&, bool&)#Failed to read the whole file.");
			}
			TestEncoding(&buffer[0], buffer.Count(), encoding, containsBom);
			
			MemoryWrapperStream memoryStream(&buffer[0], buffer.Count());
			
			if (containsBom)
			{
				BomDecoder decoder;
				DecoderStream decoderStream(memoryStream, decoder);
				StreamReader reader(decoderStream);
				text = reader.ReadToEnd();
			}
			else
			{
				switch (encoding)
				{
					case BomEncoder::Utf8:
						{
							Utf8Decoder decoder;
							DecoderStream decoderStream(memoryStream, decoder);
							StreamReader reader(decoderStream);
							text = reader.ReadToEnd();
						}
						break;
						
					case BomEncoder::Utf16:
						{
							Utf16Decoder decoder;
							DecoderStream decoderStream(memoryStream, decoder);
							StreamReader reader(decoderStream);
							text = reader.ReadToEnd();
						}
						break;
						
					case BomEncoder::Utf16BE:
						{
							Utf16BEDecoder decoder;
							DecoderStream decoderStream(memoryStream, decoder);
							StreamReader reader(decoderStream);
							text = reader.ReadToEnd();
						}
						break;
						
					default:
						{
							MbcsDecoder decoder;
							DecoderStream decoderStream(memoryStream, decoder);
							StreamReader reader(decoderStream);
							text = reader.ReadToEnd();
						}
				}
			}
			
			return true;
		}
		
		WString File::ReadAllTextByBom()const
		{
			WString text;
			ReadAllTextByBom(text);
			return text;
		}
		
		bool File::ReadAllTextByBom(WString& text)const
		{
			FileStream fileStream(filePath.GetFullPath(), FileStream::ReadOnly);
			
			if (!fileStream.IsAvailable())
			{
				return false;
			}
			
			BomDecoder decoder;
			DecoderStream decoderStream(fileStream, decoder);
			StreamReader reader(decoderStream);
			text = reader.ReadToEnd();
			return true;
		}
		
		bool File::ReadAllLinesByBom(collections::List<WString>& lines)const
		{
			FileStream fileStream(filePath.GetFullPath(), FileStream::ReadOnly);
			
			if (!fileStream.IsAvailable())
			{
				return false;
			}
			
			BomDecoder decoder;
			DecoderStream decoderStream(fileStream, decoder);
			StreamReader reader(decoderStream);
			
			while (!reader.IsEnd())
			{
				lines.Add(reader.ReadLine());
			}
			
			return true;
		}
		
		bool File::WriteAllText(const WString& text, bool bom, stream::BomEncoder::Encoding encoding)
		{
			FileStream fileStream(filePath.GetFullPath(), FileStream::WriteOnly);
			
			if (!fileStream.IsAvailable())
			{
				return false;
			}
			
			IEncoder* encoder = NULL;
			
			if (bom)
			{
				encoder = new BomEncoder(encoding);
			}
			else switch (encoding)
				{
					case BomEncoder::Utf8:
						encoder = new Utf8Encoder;
						break;
						
					case BomEncoder::Utf16:
						encoder = new Utf16Encoder;
						break;
						
					case BomEncoder::Utf16BE:
						encoder = new Utf16BEEncoder;
						break;
						
					default:
						encoder = new MbcsEncoder;
						break;
				}
				
			{
				EncoderStream encoderStream(fileStream, *encoder);
				StreamWriter writer(encoderStream);
				writer.WriteString(text);
			}
			
			delete encoder;
			return true;
		}
		
		bool File::WriteAllLines(collections::List<WString>& lines, bool bom, stream::BomEncoder::Encoding encoding)
		{
			FileStream fileStream(filePath.GetFullPath(), FileStream::WriteOnly);
			
			if (!fileStream.IsAvailable())
			{
				return false;
			}
			
			IEncoder* encoder = NULL;
			
			if (bom)
			{
				encoder = new BomEncoder(encoding);
			}
			else switch (encoding)
				{
					case BomEncoder::Utf8:
						encoder = new Utf8Encoder;
						break;
						
					case BomEncoder::Utf16:
						encoder = new Utf16Encoder;
						break;
						
					case BomEncoder::Utf16BE:
						encoder = new Utf16BEEncoder;
						break;
						
					default:
						encoder = new MbcsEncoder;
						break;
				}
				
			{
				EncoderStream encoderStream(fileStream, *encoder);
				StreamWriter writer(encoderStream);
				FOREACH(WString, line, lines)
				{
					writer.WriteLine(line);
				}
			}
			
			delete encoder;
			return true;
		}
		
		bool File::Exists()const
		{
			return filePath.IsFile();
		}
		
		bool File::Delete()const
		{
#if defined VCZH_MSVC
			return DeleteFile(filePath.GetFullPath().Buffer()) != 0;
#elif defined VCZH_GCC
			AString path = wtoa(filePath.GetFullPath());
			return unlink(path.Buffer()) == 0;
#endif
		}
		
		bool File::Rename(const WString& newName)const
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
		
		vl::WString File::GetName()
		{
			return filePath.GetName();
		}

	}
}

