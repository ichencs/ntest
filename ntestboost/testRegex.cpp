#include "stdafx.h"
#include "testRegex.h"
#include <cassert>
#include <iostream>

using namespace std;

using namespace vl::console;

testRegex::testRegex()
{
	test();
}


testRegex::~testRegex()
{
}

/*--------------------------------------------------*\
	//指定使用perl语法（默认），忽略大小写。
	boost::regex reg1( szReg, boost::regex::perl|boost::regex::icase );

	/指定使用POSIX扩展语法（其实也差不多）
	boost::regex reg2( szReg, boost::regex::extended );
\*--------------------------------------------------*/

void testRegex::test()
{
	Console::SetColor(false, true, true, true);
	Console::WriteLine(L"测试正则表达式");
	match();
	search();
	replace();
}

void testRegex::match()
{
	Console::WriteLine(L"测试match");
	match_date();
	match_date2();
	match_ip();
	match_url();
	match_url2();
	match_email();
	match_chs();
	match_pid();
	Console::WriteLine(L"结束match\r\n");
}

void testRegex::match_date()
{
	/*----------------------------------------------*\
	Checks date is formatted properly -- will work for dates 01/01/1900 (or 1/1/1900) through 12/31/2099
	\*----------------------------------------------*/
	
	std::string reg = "^(0?[1-9]|1[0-2])[\\/](0?[1-9]|[12]\\d|3[01])[\\/](19|20)\\d{2}$";
	std::wstring wstr = L"日期1";
	std::string text = "10/2/2015";
	match_res(reg, wstr, text);
}

void testRegex::match_date2()
{
	/*----------------------------------------------*\
	Matches an ISO date in format yyyy-mm-dd
	
	checks for years in 1900-2099 range,months in 01-12 range and days in 01-31 range
	
	DOES NOT check for valid dates, a date such as 2013-02-31 will be valid.
	
	只检查格式，不检查是否有效。
	\*----------------------------------------------*/
	std::string reg = "(19|20)\\d\\d-(0?[1-9]|1[0-2])-(0?[1-9]|[12][0-9]|3[01])";
	std::wstring wstr = L"日期2";
	vector<std::string> vtext;
	vtext.push_back("2015-1-2");
	vtext.push_back("2015-01-02");
	vtext.push_back("2015-011-012");
	match_res(reg, wstr, vtext);
}


void testRegex::match_ip()
{
	/*----------------------------------------------*\
	0.0.0.0 - 255.255.255.255 - valid ip address range
	\*----------------------------------------------*/
	std::string reg = "\\b((([0-2]\\d[0-5])|(\\d{2})|(\\d))\\.){3}(([0-2]\\d[0-5])|(\\d{2})|(\\d))\\b";
	std::wstring wstr = L"ip1";
	vector<std::string> vtext;
	vtext.push_back("10.11.44.100");
	vtext.push_back("194.66.32.10");
	vtext.push_back("255.255.255.255");
	vtext.push_back("300.301.302.304");
	vtext.push_back("30.30.301.30");
	vtext.push_back("30.30.31.301");
	match_res(reg, wstr, vtext);
}

void testRegex::match_ip2()
{
	std::string reg = "\\b(?:(?:2(?:[0-4][0-9]|5[0-5])|[0-1]?[0-9]?[0-9])\\.){3}(?:(?:2([0-4][0-9]|5[0-5])|[0-1]?[0-9]?[0-9]))\\b";
	std::wstring wstr = L"ip2";
	vector<std::string> vtext;
	
	vtext.push_back("10.11.44.100");
	vtext.push_back("194.66.32.10");
	vtext.push_back("255.255.255.255");
	vtext.push_back("300.301.302.304");
	vtext.push_back("30.30.301.30");
	vtext.push_back("30.30.31.301");
	match_res(reg, wstr, vtext);
}

void testRegex::match_url()
{
	std::string reg = "[a-zA-z]+://[^\\s]*";
	std::wstring wstr = L"url";
	std::string text = "http://regexr.com/";
	match_res(reg, wstr, text);
}

void testRegex::match_url2()
{
	/*----------------------------------------------*\
	[0]: protocall,
	[1]: host,
	[2]: port,
	[3]: path,
	[4]: file,
	[5]: query,
	[6]: hash
	
	如： "https://www.google.com:80/dir/1/2/search.html?arg=0-a&arg1=1-b&arg3-c#hash"
	protocall:		https
	host:			www.google.com
	port:			:80
	path:			/dir/1/2/
	file:			search.html
	query:			?arg=0-a&arg1=1-b&arg3-c
	hash:			#hash
	\*----------------------------------------------*/
	
	std::string reg = "^(?:(http[s]?|ftp[s]):\\/\\/)?([^:\\/\\s]+)(:[0-9]+)?((?:\\/\\w+)*\\/)([\\w\\-\\.]+[^#?\\s]+)([^#\\s]*)?(#[\\w\\-]+)?$";
	std::wstring wstr = L"url";
	std::string text = "https://www.google.com:80/dir/1/2/search.html?arg=0-a&arg1=1-b&arg3-c#hash";
	match_res(reg, wstr, text);
}

void testRegex::match_email()
{
	std::string reg = ("[\\w!#$%&'*+/=?^_`{|}~-]+(?:\\.[\\w!#$%&'*+/=?^_`{|}~-]+)*@(?:[\\w](?:[\\w-]*[\\w])?\\.)+[\\w](?:[\\w-]*[\\w])?");
	std::wstring wstr = L"email";
	std::string text = "ichencs@163.com";
	match_res(reg, wstr, text);
}

void testRegex::match_email2()
{
	std::string reg = ("[a-z0-9]+[_a-z0-9\\.-]*[a-z0-9]+@[a-z0-9-]+(\\.[a-z0-9-]+)*(\\.[a-z]{2,4})");
	std::wstring wstr = L"email";
	std::string text = "ichencs@163.com";
	match_res(reg, wstr, text);
	
}

void testRegex::match_chs()
{
	std::string reg = ("[\\u4e00-\\u9fa5]");
	std::wstring wstr = L"中文";
	std::string text = "你好";
	match_res(reg, wstr, text);
	
}

void testRegex::match_pid()
{
	std::string reg = ("^(\\d{6})(\\d{4})(\\d{2})(\\d{2})(\\d{3})([0-9]|X)$");
	std::wstring wstr = L"身份证号";
	std::string text = "371121199500004235";
	match_res(reg, wstr, text);
	
}

void testRegex::match_res(std::string sreg, std::wstring name, std::string text)
{
	boost::regex reg(sreg);
	// 	Console::WriteLine(name + L"表达式：");
	// 	Console::WriteLine(sreg);
	// 	Console::WriteLine(text);
	bool bRes = boost::regex_match(text, reg);
	// 	Console::WriteLine(bRes);
	// 	Console::WriteLine("");
}

void testRegex::match_res(std::string sreg, std::wstring name, std::vector<std::string> vtext)
{
	boost::regex reg(sreg);
	// 	Console::WriteLine(name + L"表达式：");
	// 	Console::WriteLine(sreg);
	
	for (size_t i = 0; i < vtext.size(); i++)
	{
		bool bRes = boost::regex_match(vtext.at(i), reg);
		// 		Console::WriteLine(vtext.at(i));
		// 		Console::WriteLine(bRes);
	}
	
	// 	Console::WriteLine("");
}

void testRegex::search()
{
	Console::WriteLine(L"测试search");
	search1();
	search2();
	Console::WriteLine(L"结束search\r\n");
}

void testRegex::search1()
{
	// 	typedef boost::match_results<std::string::const_iterator> smatch;
	boost::regex reg("(new)|(delete)");
	boost::smatch m;
	std::string s =	"Calls to new must be followed by delete. Calling simply new results in a leak!";
	bool bRes = boost::regex_search(s, m, reg);
	size_t num = m.size();
	std::string str, str1, str2;
	str = m[0].str();
	m[0].first;
	m[0].second;
	str1 = m[1].str();
	str2 = m[2].str();
	//boost::regex_search();
	// 	Console::WriteLine(str);
	// 	Console::WriteLine(str1);
	// 	Console::WriteLine(str2);
}

void testRegex::search2()
{



}

void testRegex::replace()
{
	Console::WriteLine(L"测试replace");
	replace1();
	replace2();
	
	Console::WriteLine(L"结束replace\r\n");
}

void testRegex::replace1()
{
	/*----------------------------------------------*\
	\*----------------------------------------------*/
	boost::regex reg("(Colo)(u)(r)",
	  boost::regex::icase | boost::regex::perl);
	Console::Write(L"表达式：");
	cout << reg.str() << endl;
	// 	Console::WriteLine(reg.str());
	
	std::wstring s = L"Colour, colours, color, colourize";
	// 	Console::WriteLine(s);
	
	// 	std::string s1 = boost::regex_replace(s, reg, "$1$3");
	// 	Console::WriteLine(s1);
	// 	std::string s2 = boost::regex_replace(s, reg, "$1");
	// 	Console::WriteLine(s2);
	
}

void testRegex::replace2()
{
	/*----------------------------------------------*\
	\*----------------------------------------------*/
	
	
}

void testRegex::format()
{
}

void testRegex::split()
{
	// 	boost::regex::split_regex();
}
