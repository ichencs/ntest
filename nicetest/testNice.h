#pragma once
class testNice
{
public:
	testNice();
	~testNice();

public:
	void test();
	void testSizeof();
	void testObserve();		//π€≤Ï’ﬂ
	void testMd5();

public:
	void testDomain();


protected:
	CString GetMD5(const CString &strFilePath /*= _T("")*/);
	CString GetDomain();
};

