#include "stdafx.h"
#include "boost_asio.h"
#include <iostream>
#include <boost/asio.hpp>

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
	io_service iosev;
	ip::tcp::acceptor acceptor(iosev,
		ip::tcp::endpoint(ip::tcp::v4(), 1000));



}
