#include "stdafx.h"

using namespace vl::path;
using namespace vl::filesystem;
using namespace vl::console;
TEST_CASE(TestPath)
{
	Path path = L"c:\\Program Files\\File.txt/";
	TEST_ASSERT(!path.IsDirectory());
	Path path_t = path;
	path_t.RemoveFileSpec();
	Console::WriteLine(path_t.GetFullPath());
	path_t = path;
	path_t.RemoveBackslash();
	Console::WriteLine(path_t.GetFullPath());
	// 	WString wpath = FilePath::ModulePath().GetFullPath();
	FilePath fpath = FilePath::ModulePath();
	Console::WriteLine(fpath.FindFileName());
	fpath.RemoveFileSpec();
	Console::WriteLine(fpath.FindFileName());
	fpath.RemoveFileSpec();
	Console::WriteLine(fpath.FindFileName());
	
	Path p2 = fpath.GetFullPath();
	p2.RemoveBackslash();
	
	Console::WriteLine(p2.FindFileName());
	
	TEST_ASSERT(p2.FileExists());
	TEST_ASSERT(p2.IsDirectory());
	
	Path p3 = L"https://msdn.microsoft.com/query/dev15.query?appId=Dev15IDEF1&l=ZH-CN&k=k(SHLWAPI%2FPathIsDirectory);k(PathIsDirectory);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true";
	
	TEST_ASSERT(p3.IsURL());
	TEST_ASSERT(!p3.IsUNC());
	Console::WriteLine(p3.FindFileName());
	
	Path p4 = L"\\\\servername\\sharename";
	TEST_ASSERT(p4.IsUNC());
	TEST_ASSERT(!p4.IsURL());
	
	Console::WriteLine(p4.FindFileName());
	
	
}