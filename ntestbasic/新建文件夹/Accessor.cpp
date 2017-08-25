#include "stdafx.h"
#include <string.h>
#include "Accessor.h"


/***********************************************************************
TextReader
***********************************************************************/

		wstring TextReader::ReadString(int length)
		{
			wchar_t* buffer=new wchar_t[length+1];
			int i=0;
			for(;i<length;i++)
			{
				if((buffer[i]=ReadChar())==L'\0')
				{
					break;
				}
			}
			buffer[i]=L'\0';
			wstring result(buffer);
			delete[] buffer;
			return result;
		}

		wstring TextReader::ReadLine()
		{
			wstring result;
			auto buffer = new wchar_t[65537];
			buffer[0]=L'\0';
			int i=0;
			while(true)
			{
				wchar_t c=ReadChar();
				if(c==L'\n' || c==L'\0')
				{
					buffer[i]=L'\0';
					result+=buffer;
					buffer[0]=L'\0';
					i=0;
					break;
				}
				else
				{
					if(i==65536)
					{
						buffer[i]=L'\0';
						result+=buffer;
						buffer[0]=L'\0';
						i=0;
					}
					buffer[i++]=c;
				}
			}
			result+=buffer;
			delete[] buffer;
			if(result.size()>0 && result[result.size()-1]==L'\r')
			{
				return result.left(result.size()-1);
			}
			else
			{
				return result;
			}
		}

		wstring TextReader::ReadToEnd()
		{
			wstring result;
			auto buffer = new wchar_t[65537];
			buffer[0]=L'\0';
			int i=0;
			while(true)
			{
				wchar_t c=ReadChar();
				if(c==L'\0')
				{
					buffer[i]=L'\0';
					result+=buffer;
					buffer[0]=L'\0';
					i=0;
					break;
				}
				else
				{
					if(i==65536)
					{
						buffer[i]=L'\0';
						result+=buffer;
						buffer[0]=L'\0';
						i=0;
					}
					buffer[i++]=c;
				}
			}
			result+=buffer;
			delete[] buffer;
			return result;
		}

/***********************************************************************
TextWriter
***********************************************************************/

		void TextWriter::WriteString(const wchar_t* string, int charCount)
		{
			while(*string)
			{
				WriteChar(*string++);
			}
		}

		void TextWriter::WriteString(const wchar_t* string)
		{
			WriteString(string, (int)wcslen(string));
		}

		void TextWriter::WriteString(const wstring& string)
		{
			if(string.size())
			{
				WriteString(string.c_str(), string.size());
			}
		}

		void TextWriter::WriteLine(const wchar_t* string, int charCount)
		{
			WriteString(string, charCount);
			WriteString(L"\r\n", 2);
		}

		void TextWriter::WriteLine(const wchar_t* string)
		{
			WriteString(string);
			WriteString(L"\r\n", 2);
		}

		void TextWriter::WriteLine(const wstring& string)
		{
			WriteString(string);
			WriteString(L"\r\n", 2);
		}

		namespace monospace_tabling
		{
			void WriteBorderLine(TextWriter& writer, Array<int>& columnWidths, int columns)
			{
				writer.WriteChar(L'+');
				for(int i=0;i<columns;i++)
				{
					int c=columnWidths[i];
					for(int j=0;j<c;j++)
					{
						writer.WriteChar(L'-');
					}
					writer.WriteChar(L'+');
				}
				writer.WriteLine(L"");
			}

			void WriteContentLine(TextWriter& writer, Array<int>& columnWidths, int rowHeight, int columns, Array<wstring>& tableByRow, int startRow)
			{
				int cellStart=startRow*columns;
				for(int r=0;r<rowHeight;r++)
				{
					writer.WriteChar(L'|');
					for(int c=0;c<columns;c++)
					{
						const wchar_t* cell=tableByRow[cellStart+c].c_str();
						for(int i=0;i<r;i++)
						{
							if(cell) cell=::wcsstr(cell, L"\r\n");
							if(cell) cell+=2;
						}

						writer.WriteChar(L' ');
						int length=0;
						if(cell)
						{
							const wchar_t* end=::wcsstr(cell, L"\r\n");
							length=end?end-cell:(int)wcslen(cell);
							writer.WriteString(cell, length);
						}

						for(int i=columnWidths[c]-2;i>=length;i--)
						{
							writer.WriteChar(L' ');
						}
						writer.WriteChar(L'|');
					}
					writer.WriteLine(L"");
				}
			}
		}
		using namespace monospace_tabling;

		void TextWriter::WriteMonospacedEnglishTable(Array<wstring>& tableByRow, int rows, int columns)
		{
			Array<int> rowHeights(rows);
			Array<int> columnWidths(columns);
			for(int i=0;i<rows;i++) rowHeights[i]=0;
			for(int j=0;j<columns;j++) columnWidths[j]=0;

			for(int i=0;i<rows;i++)
			{
				for(int j=0;j<columns;j++)
				{
					wstring text=tableByRow[i*columns+j];
					const wchar_t* reading=text.c_str();
					int width=0;
					int height=0;

					while(reading)
					{
						height++;
						const wchar_t* crlf=::wcsstr(reading, L"\r\n");
						if(crlf)
						{
							int length=crlf-reading+2;
							if(width<length) width=length;
							reading=crlf+2;
						}
						else
						{
							int length=(int)wcslen(reading)+2;
							if(width<length) width=length;
							reading=0;
						}
					}

					if(rowHeights[i]<height) rowHeights[i]=height;
					if(columnWidths[j]<width) columnWidths[j]=width;
				}
			}

			WriteBorderLine(*this, columnWidths, columns);
			for(int i=0;i<rows;i++)
			{
				WriteContentLine(*this, columnWidths, rowHeights[i], columns, tableByRow, i);
				WriteBorderLine(*this, columnWidths, columns);
			}
		}

/***********************************************************************
StringReader
***********************************************************************/

		void StringReader::PrepareIfLastCallIsReadLine()
		{
			if(lastCallIsReadLine)
			{
				lastCallIsReadLine=false;
				if(current<string.size() && string[current]==L'\r') current++;
				if(current<string.size() && string[current]==L'\n') current++;
			}
		}

		StringReader::StringReader(const wstring& _string)
			:string(_string)
			,current(0)
			,lastCallIsReadLine(false)
		{
		}

		bool StringReader::IsEnd()
		{
			return current==string.size();
		}

		wchar_t StringReader::ReadChar()
		{
			PrepareIfLastCallIsReadLine();
			if(IsEnd())
			{
				return L'\0';
			}
			else
			{
				return string[current++];
			}
		}

		wstring StringReader::ReadString(int length)
		{
			PrepareIfLastCallIsReadLine();
			if(IsEnd())
			{
				return L"";
			}
			else
			{
				int remain=string.size()-current;
				if(length>remain) length=remain;
				wstring result=string.Sub(current, length);
				current+=length;
				return result;
			}
		}

		wstring StringReader::ReadLine()
		{
			PrepareIfLastCallIsReadLine();
			if(IsEnd())
			{
				return L"";
			}
			else
			{
				int lineEnd=current;
				while(lineEnd<string.size())
				{
					wchar_t c=string[lineEnd];
					if(c==L'\r' || c==L'\n') break;
					lineEnd++;
				}
				wstring result=string.Sub(current, lineEnd-current);
				current=lineEnd;
				lastCallIsReadLine=true;
				return result;
			}
		}

		wstring StringReader::ReadToEnd()
		{
			return ReadString(string.size()-current);
		}

/***********************************************************************
StreamReader
***********************************************************************/

		StreamReader::StreamReader(IStream& _stream)
			:stream(&_stream)
		{
		}

		bool StreamReader::IsEnd()
		{
			return stream==0;
		}

		wchar_t StreamReader::ReadChar()
		{
			if(stream)
			{
				wchar_t buffer=0;
				if(stream->Read(&buffer, sizeof(buffer))==0)
				{
					stream=0;
					return 0;
				}
				else
				{
					return buffer;
				}
			}
			else
			{
				return L'\0';
			}
		}

/***********************************************************************
StreamWriter
***********************************************************************/

		StreamWriter::StreamWriter(IStream& _stream)
			:stream(&_stream)
		{
		}

		void StreamWriter::WriteChar(wchar_t c)
		{
			stream->Write(&c, sizeof(c));
		}

		void StreamWriter::WriteString(const wchar_t* string, int charCount)
		{
			stream->Write((void*)string, charCount*sizeof(*string));
		}

/***********************************************************************
EncoderStream
***********************************************************************/

		EncoderStream::EncoderStream(IStream& _stream, IEncoder& _encoder)
			:stream(&_stream)
			,encoder(&_encoder)
			,position(0)
		{
			encoder->Setup(stream);
		}

		EncoderStream::~EncoderStream()
		{
			Close();
		}

		bool EncoderStream::CanRead()const
		{
			return false;
		}

		bool EncoderStream::CanWrite()const
		{
			return IsAvailable();
		}

		bool EncoderStream::CanSeek()const
		{
			return false;
		}

		bool EncoderStream::CanPeek()const
		{
			return false;
		}

		bool EncoderStream::IsLimited()const
		{
			return stream!=0 && stream->IsLimited();
		}

		bool EncoderStream::IsAvailable()const
		{
			return stream!=0 && stream->IsAvailable();
		}

		void EncoderStream::Close()
		{
			encoder->Close();
			stream=0;
		}

		pos_t EncoderStream::Position()const
		{
			return IsAvailable()?position:-1;
		}

		pos_t EncoderStream::Size()const
		{
			return -1;
		}

		void EncoderStream::Seek(pos_t _size)
		{
			CHECK_FAIL(L"EncoderStream::Seek(pos_t)#Operation not supported.");
		}

		void EncoderStream::SeekFromBegin(pos_t _size)
		{
			CHECK_FAIL(L"EncoderStream::SeekFromBegin(pos_t)#Operation not supported.");
		}

		void EncoderStream::SeekFromEnd(pos_t _size)
		{
			CHECK_FAIL(L"EncoderStream::SeekFromEnd(pos_t)#Operation not supported.");
		}

		int EncoderStream::Read(void* _buffer, int _size)
		{
			CHECK_FAIL(L"EncoderStream::Read(void*, int)#Operation not supported.");
		}

		int EncoderStream::Write(void* _buffer, int _size)
		{
			int result=encoder->Write(_buffer, _size);
			if(result>=0)
			{
				position+=result;
			}
			return result;
		}

		int EncoderStream::Peek(void* _buffer, int _size)
		{
			CHECK_FAIL(L"EncoderStream::Peek(void*, int)#Operation not supported.");
		}

/***********************************************************************
DecoderStream
***********************************************************************/

		DecoderStream::DecoderStream(IStream& _stream, IDecoder& _decoder)
			:stream(&_stream)
			,decoder(&_decoder)
			,position(0)
		{
			decoder->Setup(stream);
		}

		DecoderStream::~DecoderStream()
		{
			Close();
		}

		bool DecoderStream::CanRead()const
		{
			return IsAvailable();
		}

		bool DecoderStream::CanWrite()const
		{
			return false;
		}

		bool DecoderStream::CanSeek()const
		{
			return false;
		}

		bool DecoderStream::CanPeek()const
		{
			return false;
		}

		bool DecoderStream::IsLimited()const
		{
			return stream!=0 && stream->IsLimited();
		}

		bool DecoderStream::IsAvailable()const
		{
			return stream!=0 && stream->IsAvailable();
		}

		void DecoderStream::Close()
		{
			decoder->Close();
			stream=0;
		}

		pos_t DecoderStream::Position()const
		{
			return IsAvailable()?position:-1;
		}

		pos_t DecoderStream::Size()const
		{
			return -1;
		}

		void DecoderStream::Seek(pos_t _size)
		{
			CHECK_FAIL(L"DecoderStream::Seek(pos_t)#Operation not supported.");
		}

		void DecoderStream::SeekFromBegin(pos_t _size)
		{
			CHECK_FAIL(L"DecoderStream::SeekFromBegin(pos_t)#Operation not supported.");
		}

		void DecoderStream::SeekFromEnd(pos_t _size)
		{
			CHECK_FAIL(L"DecoderStream::SeekFromEnd(pos_t)#Operation not supported.");
		}

		int DecoderStream::Read(void* _buffer, int _size)
		{
			int result=decoder->Read(_buffer, _size);
			if(result>=0)
			{
				position+=result;
			}
			return result;
		}

		int DecoderStream::Write(void* _buffer, int _size)
		{
			CHECK_FAIL(L"DecoderStream::Write(void*, int)#Operation not supported.");
		}

		int DecoderStream::Peek(void* _buffer, int _size)
		{
			CHECK_FAIL(L"DecoderStream::Peek(void*, int)#Operation not supported.");
		}
// 	}
// }
