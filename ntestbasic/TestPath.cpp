#include "stdafx.h"

using namespace vl::path;
using namespace vl::filesystem;
TEST_CASE(TestPath)
{
	Path path = L"c:\\Program Files\\File.txt";
	TEST_ASSERT(!path.IsDirectory());

	WString wpath =FilePath::ModulePath().GetFullPath(); 
	Path p2 = FilePath::ModulePath().GetFolder().GetFullPath();
	p2.RemoveBackslash();
	TEST_ASSERT(p2.FileExists());
	TEST_ASSERT(p2.IsDirectory());



}