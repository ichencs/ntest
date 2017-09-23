﻿#include "stdafx.h"

#include <Shlwapi.h>
#include <WinSock.h>

using namespace vl;
using namespace vl::collections;
using namespace vl::console;
using namespace vl::stream;
using namespace vl::filesystem;

extern WString GetTestResourcePath();
extern WString GetTestOutputPath();

void ClearTestFolders()
{
	FilePath path = GetTestOutputPath();
	TEST_ASSERT(path.IsFolder());
	
	Folder folder(GetTestOutputPath() + L"FileSystem");
	WString folderPath = folder.GetFilePath().GetFullPath();
#if defined VCZH_MSVC
	TEST_ASSERT(folderPath[1] == L':');
	TEST_ASSERT(INVLOC.FindLast(folderPath, L"\\FileSystem", Locale::None).key == folderPath.Length() - 11);
#elif defined VCZH_GCC
	TEST_ASSERT(folderPath[0] == L'/');
	TEST_ASSERT(INVLOC.FindLast(folderPath, L"/FileSystem", Locale::None).key == folderPath.Length() - 11);
#endif
	
	if (folder.Exists())
	{
		TEST_ASSERT(folder.Delete(true) == true);
	}
	
	TEST_ASSERT(folder.Create(false) == true);
	TEST_ASSERT(folder.Exists() == true);
	TEST_ASSERT(folder.Create(false) == false);
}

TEST_CASE(TestFilePath)
{
	ClearTestFolders();
	{
		FilePath p;
		TEST_ASSERT(p.IsFile() == false);
		TEST_ASSERT(p.IsFolder() == false);
		TEST_ASSERT(p.IsRoot() == true);
		TEST_ASSERT(p.GetFullPath() == L"");
		TEST_ASSERT(p.GetName() == L"");
		TEST_ASSERT(p.GetFolder().GetFullPath() == L"");
	}
	{
		FilePath p = L"C:\\";
		TEST_ASSERT(p.IsFile() == false);
		TEST_ASSERT(p.IsFolder() == true);
		TEST_ASSERT(p.IsRoot() == false);
		TEST_ASSERT(p.GetFullPath() == L"C:");
		TEST_ASSERT(p.GetName() == L"C:");
		TEST_ASSERT(p.GetFolder().GetFullPath() == L"");
	}
	{
		FilePath p = L"C:\\Windows\\";
		TEST_ASSERT(p.IsFile() == false);
		TEST_ASSERT(p.IsFolder() == true);
		TEST_ASSERT(p.IsRoot() == false);
		TEST_ASSERT(p.GetFullPath() == L"C:\\Windows");
		TEST_ASSERT(p.GetName() == L"Windows");
		TEST_ASSERT(p.GetFolder().GetFullPath() == L"C:");
	}
	{
		FilePath p = L"C:\\Windows\\Explorer.exe";
		TEST_ASSERT(p.IsFile() == true);
		TEST_ASSERT(p.IsFolder() == false);
		TEST_ASSERT(p.IsRoot() == false);
		TEST_ASSERT(p.GetFullPath() == L"C:\\Windows\\Explorer.exe");
		TEST_ASSERT(p.GetName() == L"Explorer.exe");
		TEST_ASSERT(p.GetFolder().GetFullPath() == L"C:\\Windows");
	}
	{
		FilePath p = L"C:\\Windows\\vczh.txt";
		TEST_ASSERT(p.IsFile() == false);
		TEST_ASSERT(p.IsFolder() == false);
		TEST_ASSERT(p.IsRoot() == false);
		TEST_ASSERT(p.GetFullPath() == L"C:\\Windows\\vczh.txt");
	}
	{
		FilePath p = L"C:\\Windows";
		FilePath q = p / L"Explorer.exe";
		TEST_ASSERT(q.GetFullPath() == L"C:\\Windows\\Explorer.exe");
	}
	{
		FilePath p = L"C:\\Program Files";
		FilePath q = p / L"..\\Windows\\.\\Explorer.exe";
		TEST_ASSERT(q.GetFullPath() == L"C:\\Windows\\Explorer.exe");
	}
	{
		FilePath p = L"C:\\Program Files";
		FilePath q = L"C:\\Windows\\Explorer.exe";
		FilePath r = p.GetRelativePathFor(q);
		TEST_ASSERT(r == L"..\\Windows\\Explorer.exe");
	}
	{
		FilePath p = L"C:\\Program Files\\vczh.txt";
		FilePath q = L"C:\\Windows\\Explorer.exe";
		FilePath r = p.GetRelativePathFor(q);
		TEST_ASSERT(r == L"..\\Windows\\Explorer.exe");
	}
	{
		FilePath p = L"C:\\Program Files\\vczh.txt";
		FilePath q = L"D:\\Windows\\Explorer.exe";
		FilePath r = p.GetRelativePathFor(q);
		TEST_ASSERT(r == L"D:\\Windows\\Explorer.exe");
	}
}

#ifdef VCZH_MSVC
TEST_CASE(EnumerateDrives)
{
	Folder folder;
	List<Folder> folders;
	List<File> files;
	TEST_ASSERT(folder.GetFilePath().IsRoot());
	TEST_ASSERT(folder.GetFolders(folders));
	TEST_ASSERT(folder.GetFiles(files));
	TEST_ASSERT(folders.Count() > 0);
	TEST_ASSERT(files.Count() == 0);
	
	TEST_ASSERT(folders[0].Exists());
	TEST_ASSERT(folders[0].GetFilePath().IsFolder());
	WString drive = folders[0].GetFilePath().GetFullPath();
	TEST_ASSERT(drive.Length() == 2);
	TEST_ASSERT(drive[1] == L':');
}
#endif

TEST_CASE(CreateDeleteFolders)
{
	ClearTestFolders();
	FilePath folder = GetTestOutputPath() + L"FileSystem";
	
	File a = folder / L"A/vczh.txt";
	File b = folder / L"A/B/C/vczh.txt";
	Folder c = folder / L"A";
	Folder d = folder / L"A/B/C";
	
	TEST_ASSERT(a.Exists() == false);
	TEST_ASSERT(b.Exists() == false);
	TEST_ASSERT(c.Exists() == false);
	TEST_ASSERT(d.Exists() == false);
	TEST_ASSERT(a.WriteAllText(L"A") == false);
	TEST_ASSERT(b.WriteAllText(L"B") == false);
	TEST_ASSERT(a.ReadAllTextByBom() == L"");
	TEST_ASSERT(b.ReadAllTextByBom() == L"");
	
	TEST_ASSERT(c.Create(false) == true);
	TEST_ASSERT(d.Create(false) == false);
	TEST_ASSERT(d.Create(true) == true);
	TEST_ASSERT(c.Create(true) == false);
	TEST_ASSERT(d.Create(true) == false);
	
	TEST_ASSERT(a.Exists() == false);
	TEST_ASSERT(b.Exists() == false);
	TEST_ASSERT(c.Exists() == true);
	TEST_ASSERT(d.Exists() == true);
	TEST_ASSERT(a.WriteAllText(L"A") == true);
	TEST_ASSERT(b.WriteAllText(L"B") == true);
	TEST_ASSERT(a.ReadAllTextByBom() == L"A");
	TEST_ASSERT(b.ReadAllTextByBom() == L"B");
	TEST_ASSERT(a.Exists() == true);
	TEST_ASSERT(b.Exists() == true);
	
	TEST_ASSERT(c.Delete(false) == false);
	TEST_ASSERT(d.Delete(false) == false);
	TEST_ASSERT(c.Delete(true) == true);
	TEST_ASSERT(d.Delete(true) == false);
	
	TEST_ASSERT(a.Exists() == false);
	TEST_ASSERT(b.Exists() == false);
	TEST_ASSERT(c.Exists() == false);
	TEST_ASSERT(d.Exists() == false);
	TEST_ASSERT(a.WriteAllText(L"A") == false);
	TEST_ASSERT(b.WriteAllText(L"B") == false);
	TEST_ASSERT(a.ReadAllTextByBom() == L"");
	TEST_ASSERT(b.ReadAllTextByBom() == L"");
}

TEST_CASE(EnumerateFoldersAndFiles)
{
	ClearTestFolders();
	FilePath folder = GetTestOutputPath() + L"FileSystem";
	
	File a = folder / L"a.txt";
	File b = folder / L"b.txt";
	Folder c = folder / L"c";
	Folder d = folder / L"d";
	List<File> files;
	List<Folder> folders;
	
	TEST_ASSERT(a.Exists() == false);
	TEST_ASSERT(b.Exists() == false);
	TEST_ASSERT(c.Exists() == false);
	TEST_ASSERT(d.Exists() == false);
	files.Clear();
	folders.Clear();
	TEST_ASSERT(Folder(folder).GetFiles(files) == true && files.Count() == 0);
	TEST_ASSERT(Folder(folder).GetFolders(folders) == true && folders.Count() == 0);
	
	TEST_ASSERT(a.WriteAllText(L"") == true);
	TEST_ASSERT(b.WriteAllText(L"") == true);
	TEST_ASSERT(c.Create(false) == true);
	TEST_ASSERT(d.Create(false) == true);
	
	TEST_ASSERT(a.Exists() == true);
	TEST_ASSERT(b.Exists() == true);
	TEST_ASSERT(c.Exists() == true);
	TEST_ASSERT(d.Exists() == true);
	files.Clear();
	folders.Clear();
	TEST_ASSERT(Folder(folder).GetFiles(files) == true && files.Count() == 2 && ((files[0].GetFilePath().GetName() == L"a.txt" && files[1].GetFilePath().GetName() == L"b.txt") || (files[0].GetFilePath().GetName() == L"b.txt" && files[1].GetFilePath().GetName() == L"a.txt")));
	TEST_ASSERT(Folder(folder).GetFolders(folders) == true && folders.Count() == 2 && ((folders[0].GetFilePath().GetName() == L"c" && folders[1].GetFilePath().GetName() == L"d") || (folders[0].GetFilePath().GetName() == L"d" && folders[1].GetFilePath().GetName() == L"c")));
	
	TEST_ASSERT(a.Delete() == true);
	TEST_ASSERT(b.Delete() == true);
	TEST_ASSERT(c.Delete(false) == true);
	TEST_ASSERT(d.Delete(false) == true);
	
	TEST_ASSERT(a.Exists() == false);
	TEST_ASSERT(b.Exists() == false);
	TEST_ASSERT(c.Exists() == false);
	TEST_ASSERT(d.Exists() == false);
	files.Clear();
	folders.Clear();
	TEST_ASSERT(Folder(folder).GetFiles(files) == true && files.Count() == 0);
	TEST_ASSERT(Folder(folder).GetFolders(folders) == true && folders.Count() == 0);
}

TEST_CASE(RenameFoldersAndFiles)
{
	ClearTestFolders();
	FilePath folder = GetTestOutputPath() + L"FileSystem";
	
	File a = folder / L"a.txt";
	File b = folder / L"d/b.txt";
	File x = folder / L"y/x.txt";
	Folder c = folder / L"c";
	Folder d = folder / L"d";
	Folder y = folder / L"y";
	
	TEST_ASSERT(c.Create(false) == true);
	TEST_ASSERT(d.Create(false) == true);
	TEST_ASSERT(a.WriteAllText(L"A") == true);
	TEST_ASSERT(b.WriteAllText(L"B") == true);
	
	TEST_ASSERT(a.Exists() == true);
	TEST_ASSERT(b.Exists() == true);
	TEST_ASSERT(x.Exists() == false);
	TEST_ASSERT(c.Exists() == true);
	TEST_ASSERT(d.Exists() == true);
	TEST_ASSERT(y.Exists() == false);
	TEST_ASSERT(a.ReadAllTextByBom() == L"A");
	TEST_ASSERT(b.ReadAllTextByBom() == L"B");
	TEST_ASSERT(x.ReadAllTextByBom() == L"");
	
	TEST_ASSERT(d.Rename(L"y"));
	TEST_ASSERT(a.Exists() == true);
	TEST_ASSERT(b.Exists() == false);
	TEST_ASSERT(x.Exists() == false);
	TEST_ASSERT(c.Exists() == true);
	TEST_ASSERT(d.Exists() == false);
	TEST_ASSERT(y.Exists() == true);
	TEST_ASSERT(a.ReadAllTextByBom() == L"A");
	TEST_ASSERT(b.ReadAllTextByBom() == L"");
	TEST_ASSERT(x.ReadAllTextByBom() == L"");
	
	TEST_ASSERT(File(folder / L"y/b.txt").Rename(L"x.txt"));
	TEST_ASSERT(a.Exists() == true);
	TEST_ASSERT(b.Exists() == false);
	TEST_ASSERT(x.Exists() == true);
	TEST_ASSERT(c.Exists() == true);
	TEST_ASSERT(d.Exists() == false);
	TEST_ASSERT(y.Exists() == true);
	TEST_ASSERT(a.ReadAllTextByBom() == L"A");
	TEST_ASSERT(b.ReadAllTextByBom() == L"");
	TEST_ASSERT(x.ReadAllTextByBom() == L"B");
}

TEST_CASE(FastAccessFiles)
{
	ClearTestFolders();
	FilePath folder = GetTestOutputPath() + L"FileSystem";
	File file = folder / L"vczh.txt";
	
	WString text;
	List<WString> lines;
	TEST_ASSERT(file.Exists() == false);
	TEST_ASSERT(file.ReadAllTextByBom() == L"");
	TEST_ASSERT(file.ReadAllTextByBom(text) == false && text == L"");
	TEST_ASSERT(file.ReadAllLinesByBom(lines) == false && lines.Count() == 0);
	
	text = L"";
	lines.Clear();
	file.WriteAllText(L"Vczh is a genius!");
	TEST_ASSERT(file.Exists() == true);
	TEST_ASSERT(file.ReadAllTextByBom() == L"Vczh is a genius!");
	TEST_ASSERT(file.ReadAllTextByBom(text) == true && text == L"Vczh is a genius!");
	TEST_ASSERT(file.ReadAllLinesByBom(lines) == true && lines.Count() == 1 && lines[0] == L"Vczh is a genius!");
	
	text = L"";
	lines.Clear();
	file.WriteAllText(L"Vczh is a genius!", true, BomEncoder::Mbcs);
	TEST_ASSERT(file.Exists() == true);
	TEST_ASSERT(file.ReadAllTextByBom() == L"Vczh is a genius!");
	TEST_ASSERT(file.ReadAllTextByBom(text) == true && text == L"Vczh is a genius!");
	TEST_ASSERT(file.ReadAllLinesByBom(lines) == true && lines.Count() == 1 && lines[0] == L"Vczh is a genius!");
	
	text = L"";
	lines.Clear();
	file.WriteAllText(L"Vczh is a genius!", true, BomEncoder::Utf8);
	TEST_ASSERT(file.Exists() == true);
	TEST_ASSERT(file.ReadAllTextByBom() == L"Vczh is a genius!");
	TEST_ASSERT(file.ReadAllTextByBom(text) == true && text == L"Vczh is a genius!");
	TEST_ASSERT(file.ReadAllLinesByBom(lines) == true && lines.Count() == 1 && lines[0] == L"Vczh is a genius!");
	
	text = L"";
	lines.Clear();
	file.WriteAllText(L"Vczh is a genius!", true, BomEncoder::Utf16);
	TEST_ASSERT(file.Exists() == true);
	TEST_ASSERT(file.ReadAllTextByBom() == L"Vczh is a genius!");
	TEST_ASSERT(file.ReadAllTextByBom(text) == true && text == L"Vczh is a genius!");
	TEST_ASSERT(file.ReadAllLinesByBom(lines) == true && lines.Count() == 1 && lines[0] == L"Vczh is a genius!");
	
	text = L"";
	lines.Clear();
	file.WriteAllText(L"Vczh is a genius!", true, BomEncoder::Utf16BE);
	TEST_ASSERT(file.Exists() == true);
	TEST_ASSERT(file.ReadAllTextByBom() == L"Vczh is a genius!");
	TEST_ASSERT(file.ReadAllTextByBom(text) == true && text == L"Vczh is a genius!");
	TEST_ASSERT(file.ReadAllLinesByBom(lines) == true && lines.Count() == 1 && lines[0] == L"Vczh is a genius!");
	
	text = L"";
	lines.Clear();
	TEST_ASSERT(file.Delete());
	TEST_ASSERT(file.Exists() == false);
	TEST_ASSERT(file.ReadAllTextByBom() == L"");
	TEST_ASSERT(file.ReadAllTextByBom(text) == false && text == L"");
	TEST_ASSERT(file.ReadAllLinesByBom(lines) == false && lines.Count() == 0);
}

void TestFastAccessFilesWithEncodingTestingInternal(IEncoder& encoder, IDecoder& decoder, BomEncoder::Encoding encoding, bool containsBom)
{
	WString filePath = GetTestOutputPath() + L"TestFile.ReadWrite.txt";
	const wchar_t* text =
	  encoding == BomEncoder::Mbcs
	  ? L"Vczh is genius!@我是天才"
	  : L"𩰪㦲𦰗𠀼 𣂕𣴑𣱳𦁚 Vczh is genius!@我是天才"
	  ;
	  
	{
		FileStream fileStream(filePath, FileStream::WriteOnly);
		{
			EncoderStream encoderStream(fileStream, encoder);
			StreamWriter writer(encoderStream);
			writer.WriteString(text);
		}
	}
	
	File file(filePath);
	TEST_ASSERT(file.Exists());
	
	WString fileText;
	BomEncoder::Encoding fileEncoding = BomEncoder::Mbcs;
	bool fileContainsBom = false;
	TEST_ASSERT(file.ReadAllTextWithEncodingTesting(fileText, fileEncoding, fileContainsBom));
	
	TEST_ASSERT(fileText == text);
	TEST_ASSERT(fileEncoding == encoding);
	TEST_ASSERT(fileContainsBom == containsBom);
}

TEST_CASE(FastAccessFilesWithEncodingTesting)
{
	if (Locale::SystemDefault().GetName() == L"zh-CN")
	{
		TEST_PRINT(L"<MBCS, NO-BOM>");
		MbcsEncoder encoder;
		MbcsDecoder decoder;
		TestFastAccessFilesWithEncodingTestingInternal(encoder, decoder, BomEncoder::Mbcs, false);
	}
	
	{
		TEST_PRINT(L"<UTF8, NO-BOM>");
		Utf8Encoder encoder;
		Utf8Decoder decoder;
		TestFastAccessFilesWithEncodingTestingInternal(encoder, decoder, BomEncoder::Utf8, false);
	}
	
	{
		TEST_PRINT(L"<UTF16, NO-BOM>");
		Utf16Encoder encoder;
		Utf16Decoder decoder;
		TestFastAccessFilesWithEncodingTestingInternal(encoder, decoder, BomEncoder::Utf16, false);
	}
	
	{
		TEST_PRINT(L"<UTF16_BE, NO-BOM>");
		Utf16BEEncoder encoder;
		Utf16BEDecoder decoder;
		TestFastAccessFilesWithEncodingTestingInternal(encoder, decoder, BomEncoder::Utf16BE, false);
	}
	
	if (Locale::SystemDefault().GetName() == L"zh-CN")
	{
		TEST_PRINT(L"<MBCS, BOM>");
		BomEncoder encoder(BomEncoder::Mbcs);
		BomDecoder decoder;
		TestFastAccessFilesWithEncodingTestingInternal(encoder, decoder, BomEncoder::Mbcs, false);
	}
	
	{
		TEST_PRINT(L"<UTF8, BOM>");
		BomEncoder encoder(BomEncoder::Utf8);
		BomDecoder decoder;
		TestFastAccessFilesWithEncodingTestingInternal(encoder, decoder, BomEncoder::Utf8, true);
	}
	
	{
		TEST_PRINT(L"<UTF16, BOM>");
		BomEncoder encoder(BomEncoder::Utf16);
		BomDecoder decoder;
		TestFastAccessFilesWithEncodingTestingInternal(encoder, decoder, BomEncoder::Utf16, true);
	}
	
	{
		TEST_PRINT(L"<UTF16_BE, BOM>");
		BomEncoder encoder(BomEncoder::Utf16BE);
		BomDecoder decoder;
		TestFastAccessFilesWithEncodingTestingInternal(encoder, decoder, BomEncoder::Utf16BE, true);
	}
}

TEST_CASE(TestFileSystemOthers)
{
	WString filePath = L"F:\\Users\\Chencs\\Desktop\\ids测试\\d323(内部).idsd";
	WString strExtension = PathFindExtension(filePath.Buffer());
	WString name = PathFindFileName(filePath.Buffer());
	FilePath path = FilePath::CurrentPath();
	Console::WriteLine(strExtension);
}

TEST_CASE(TestFileInfo)
{
	FilePath path = L"C:\\Windows";
	FileInfo info = path;
	TEST_ASSERT(info.Exists());
	TEST_ASSERT(info.IsFolder());
	TEST_ASSERT(!info.IsFile());
	
	WString strInfo = info.FileName();
	strInfo = info.Extemsion();
	
	path = L"";
	info.SetPath(path);
	TEST_ASSERT(!info.IsFile());
	TEST_ASSERT(!info.Exists());
	TEST_ASSERT(!info.IsFolder());
	TEST_ASSERT(!info.IsReadable());
	TEST_ASSERT(!info.IsWritable());
	TEST_ASSERT(!info.IsHidden());
	
	path = FilePath::ModulePath();
	info.SetPath(path);
	TEST_ASSERT(info.IsFile());
	TEST_ASSERT(info.Exists());
	TEST_ASSERT(!info.IsFolder());
	TEST_ASSERT(!info.IsHidden());
	
	info.SetPath(path.GetFolder());
	TEST_ASSERT(!info.IsFile());
	TEST_ASSERT(info.Exists());
	TEST_ASSERT(info.IsFolder());
	TEST_ASSERT(!info.IsHidden());
	path = FilePath::TempPath();
	
}
