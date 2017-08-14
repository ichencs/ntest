#pragma once
#include <vector>
using namespace std;

class testString
{
public:
	testString();
	~testString();
protected:
	void test();

	void testSplit();
	std::string toString(int d);
	std::string toString(double d);

protected:
	/*--------------------------------*\
	C++ 11���з���ֵ�Ż������Է������飨��������������Ϳ������죩
	\*--------------------------------*/
	vector<wstring> SplitString(const wchar_t* config, wchar_t delimiter);

protected:
	void test_split();
	void test_split2();
	void test_split3();
	void test_split4();
	void test_split5();
	template<typename Out>
	void split(const std::string &s, char delim, Out result);
	std::vector<std::string> split(const std::string &s, char delim);


};


