#pragma once
#include <vector>
class test_code
{
public:
	test_code();
	~test_code();
	void test();
public:
	void test_split();
	void test_split2();
	void test_split3();
	void test_split4();
	void test_split5();
	template<typename Out>
	void split(const std::string &s, char delim, Out result);
	std::vector<std::string> split(const std::string &s, char delim);

};


