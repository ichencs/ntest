#pragma once
class ntest
{
public:
	ntest();
	~ntest();
public:
	void test();
protected:
	void test_CAtlCString();
	void testMd5();

protected:
	void text_fileSystem();

protected:
	void test_Others();

	CString GetMD5(const CString &strFilePath /*= _T("")*/);
	CString GetDomain();

	bool DownloadSaveFiles(const char* url, const char* strSaveFile);
};

