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
	C++ 11具有返回值优化，可以返回数组（补拷贝，但必须就拷贝构造）
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


