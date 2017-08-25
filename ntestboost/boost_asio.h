#pragma once
#include <vector>

using namespace std;

class boost_asio
{
public:
	boost_asio();
	~boost_asio();
public:
	void test();
	void get_ip();
	std::vector<std::string> domain2ip(const string& domain, int port = 80);

};

