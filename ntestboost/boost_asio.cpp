#include "stdafx.h"
#include "boost_asio.h"
#include <iostream>
#include <boost/asio.hpp>
#include "boost/shared_ptr.hpp"  
#include "boost/thread.hpp"  
#include <boost/lexical_cast.hpp>//ʹ���ַ���ת������ 

using namespace boost::asio;

boost_asio::boost_asio()
{
	test();
}


boost_asio::~boost_asio()
{
}

void boost_asio::test()
{
	get_ip();


}

void boost_asio::get_ip()
{
	std::vector<std::string> ip = domain2ip("www.csdn.net", 0);
	for (size_t i = 0; i < ip.size(); i++)
	{
		cout << ip[i] << endl;
	}

	system("pause");
// 	std::cout << sockfd.local_endpoint().address() << std::endl;

}

std::vector<std::string> boost_asio::domain2ip(const string& domain, int port)
{
	io_service ios;
	//����resolver����  
	ip::tcp::resolver slv(ios);
	//����query����  
	ip::tcp::resolver::query qry(domain, boost::lexical_cast<string>(port));//��int�Ͷ˿�ת��Ϊ�ַ���  
																			//ʹ��resolve�����˵�  
	ip::tcp::resolver::iterator it = slv.resolve(qry);
	ip::tcp::resolver::iterator end;
	vector<std::string> ip;
	for (; it != end; it++)
	{
		ip.push_back((*it).endpoint().address().to_string());
	}
	return ip;
}

