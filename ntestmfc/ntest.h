#pragma once
class ntest
{
public:
	ntest();
	~ntest();
public:
	void test();
public:
	BOOL static RunExec(const TCHAR *cmd, const TCHAR *para, DWORD dwMilliseconds);
	BOOL static RunExec2(const TCHAR *cmd, const TCHAR *para, DWORD dwMilliseconds);

protected:
	void test_CAtlCString();
	void testMd5();

protected:
	void text_fileSystem();

protected:
	void test_Others();

	CString GetMD5(const CString &strFilePath /*= _T("")*/);
	CString GetDomain();
	CString GetComputerObjName();
	bool DownloadSaveFiles(const char* url, const char* strSaveFile);
};

