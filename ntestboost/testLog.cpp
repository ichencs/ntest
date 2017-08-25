#include "stdafx.h"
#include "testLog.h"
#include <boost/log/common.hpp>
#include <iostream>  
#include <boost/log/trivial.hpp>  

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

testLog::testLog()
{
	test();
}


testLog::~testLog()
{
}

void testLog::test()
{
	simpleTest();
}

void testLog::simpleTest()
{
	BOOST_LOG_TRIVIAL(trace) << "测试中文能否正确输出（GBK编码）";

	BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
	BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
	BOOST_LOG_TRIVIAL(info) << "An informational severity message";
	BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
	BOOST_LOG_TRIVIAL(error) << "An error severity message";
	BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

	system("pause");
}
