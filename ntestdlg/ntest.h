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

protected:
	void text_fileSystem();

protected:
	void test_Others();

	bool DownloadSaveFiles(const char* url, const char* strSaveFile);
};

