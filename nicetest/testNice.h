#pragma once
class testNice
{
public:
	testNice();
	~testNice();

public:
	void test();
	void testSizeof();
	void testObserve();		//�۲���
	void testMd5();

public:
	void testDomain();


protected:
	CString GetMD5(const CString &strFilePath /*= _T("")*/);
	CString GetDomain();
};

