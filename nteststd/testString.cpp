#include "stdafx.h"
#include "testString.h"
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;

testString::testString()
{
	test();
}


testString::~testString()
{

}

void testString::test()
{
	string str1, str2;
	str1 = toString(1);
	str2 = toString(3.1415);
}

void testString::testSplit()
{

}

std::string testString::toString(int d)
{
	stringstream ss;
	ss << d;
	return ss.str();
}

std::string testString::toString(double d)
{
	stringstream ss;
	ss << d;
	return ss.str();
}

vector<wstring> testString::SplitString(const wchar_t * config, wchar_t delimiter)
{
	vector<wstring> fragments;
	while (const wchar_t* next = wcschr(config, delimiter))
	{
		fragments.push_back(wstring(config, next));
		config = next + 1;
	}
	fragments.push_back(wstring(config));
	return fragments; // C++11¾ÍÊÇºÃ£¡  
}

void testString::test_split()
{
	string str("denmark;sweden;india;us");
	istringstream f(str);
	vector<string> strings;
	string s;
	while (getline(f, s, ';')) {
		cout << s << endl;
		strings.push_back(s);
	}
}

void testString::test_split2()
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

void testString::test_split3()
{
	string sentence = "And I feel fine...";
	istringstream iss(sentence);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		ostream_iterator<string>(cout, "\n"));
}

void testString::test_split4()
{
	string sentence = "And I feel fine...";
	istringstream iss(sentence);
	vector<string> tokens;
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter(tokens));
}

void testString::test_split5()
{

}

template<typename Out>
void testString::split(const std::string &s, char delim, Out result)
{
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}

std::vector<std::string> testString::split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}
