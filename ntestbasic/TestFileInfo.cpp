#include "stdafx.h"


using namespace vl::filesystem;

extern void ClearTestFolders();
static int num = 0;

TEST_CASE(TestFileInfo)
{
	FilePath path = L"C:\\Windows";
	FileInfo info = path;
	TEST_ASSERT(info.Exists());
	TEST_ASSERT(info.IsFolder());
	TEST_ASSERT(info.Size() > 0);
	TEST_ASSERT(!info.IsFile());
	
	WString strInfo = info.FileName();
	strInfo = info.Extemsion();
	
	path = L"";
	info.SetFile(path);
	TEST_ASSERT(!info.IsFile());
	TEST_ASSERT(!info.Exists());
	TEST_ASSERT(!info.IsFolder());
	TEST_ASSERT(!info.IsReadable());
	TEST_ASSERT(!info.IsWritable());
	TEST_ASSERT(!info.IsHidden());
	
	path = FilePath::ModulePath(&num);
	info.SetFile(path);
	TEST_ASSERT(info.IsFile());
	TEST_ASSERT(info.Exists());
	TEST_ASSERT(!info.IsFolder());
	TEST_ASSERT(!info.IsHidden());
	
	info.SetFile(path.GetFolder());
	TEST_ASSERT(!info.IsFile());
	TEST_ASSERT(info.Exists());
	TEST_ASSERT(info.IsFolder());
	TEST_ASSERT(!info.IsHidden());
	path = FilePath::TempPath();
	
}
