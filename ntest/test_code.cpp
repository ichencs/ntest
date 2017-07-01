#include "stdafx.h"
#include "test_code.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>

test_code::test_code()
{
}


test_code::~test_code()
{
}

void test_code::test()
{
	test_split();
	test_split2();
	test_split3();
	test_split4();
}

void test_code::test_split()
{
	using namespace std;
	string str("denmark;sweden;india;us");
	istringstream f(str);
	vector<string> strings;
	string s;
	while (getline(f, s, ';')) {
		cout << s << endl;
		strings.push_back(s);
	}
}

void test_code::test_split2()
{
	std::string s("Somewhere down the road");
	std::istringstream iss(s);

	do
	{
		std::string sub;
		iss >> sub;
		std::cout << "Substring: " << sub << std::endl;
	} while (iss);
}

void test_code::test_split3()
{
	using namespace std;
	string sentence = "And I feel fine...";
	istringstream iss(sentence);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		ostream_iterator<string>(cout, "\n"));
}

void test_code::test_split4()
{
	using namespace std;
	string sentence = "And I feel fine...";
	istringstream iss(sentence);
	vector<string> tokens;
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter(tokens));
}

void test_code::test_split5()
{
	

	
}

std::vector<std::string> test_code::split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}
template<typename Out>
 void test_code::split(const std::string & s, char delim, Out result)
{
	 std::stringstream ss;
	 ss.str(s);
	 std::string item;
	 while (std::getline(ss, item, delim)) {
		 *(result++) = item;
	 }
}

// std::vector<std::string> split(const std::string &s, char delim) {
/*	}*/