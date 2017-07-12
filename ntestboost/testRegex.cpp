#include "stdafx.h"
#include "testRegex.h"
#include <cassert>
// #include <boost\mpl\aux_\numeric_cast_utils.hpp>
// #include <boost\regex.hpp>


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
	testConsole::SetColor(false, true, true, true);
	testConsole::WriteLine(L"测试正则表达式");
	match();
	search();
	replace();
}

void testRegex::match()
{
	testConsole::WriteLine(L"测试match");
	match1();
	match2();
	match3();
	match4();
	match5();
	match6();
	match7();
	match8();
	testConsole::WriteLine(L"结束match\r\n");

}

void testRegex::match1()
{
	/*----------------------------------------------*\
	()		表示：子表达式
	*		称为Kleene star, 表示它前面的表达式可以被匹配零次或多次
	\*----------------------------------------------*/

	boost::regex reg("(A.*)");
	testConsole::Write(L"表达式：");
	testConsole::WriteLine(reg.str());

	string str = "This expression could match from A and beyond.";
	bool b = boost::regex_match(str, reg);
	testConsole::WriteLine(str);
	testConsole::WriteLine(b);

	str = "As this string starts with A, does it match? ";
	testConsole::WriteLine(str);
	b = boost::regex_match(str, reg);
	testConsole::WriteLine(b);

	str = "A";
	testConsole::WriteLine(str);
	b = boost::regex_match(str, reg);
	testConsole::WriteLine(b);

	str = " A ";
	testConsole::WriteLine(str);
	b = boost::regex_match(str, reg);
	testConsole::WriteLine(b);
}

void testRegex::match2()
{
	/*----------------------------------------------*\
	\*----------------------------------------------*/
	testConsole::Write(L"表达式：");
	boost::regex reg("//d{3}([a-zA-Z]+).(//d{2}|N/A)//s//1");
	testConsole::WriteLine(reg.str());

	std::string correct = "123Hello N/A Hello";
	std::string incorrect = "123Hello 12 hello";

	bool bRes = boost::regex_match(correct, reg);
	testConsole::WriteLine(correct);
	testConsole::WriteLine(bRes);

	bRes = boost::regex_match(incorrect, reg);
	testConsole::WriteLine(incorrect);
	testConsole::WriteLine(bRes);

}

void testRegex::match3()
{
	/*----------------------------------------------*\
	\*----------------------------------------------*/
	boost::regex reg("//d{3}([a-zA-Z]+).(//d{2}|N/A)//s//1");
	testConsole::Write(L"表达式：");
	testConsole::WriteLine(reg.str());


}

void testRegex::match4()
{
	/*----------------------------------------------*\
	[a-zA-Z]	英文字母
	+			可以重复
	\*----------------------------------------------*/
	boost::regex reg("[a-zA-Z]+");		//

}

void testRegex::match5()
{
	/*----------------------------------------------*\
	.			任意字符
	\*----------------------------------------------*/
	boost::regex reg(".");	//任意字符
}

void testRegex::match6()
{
	/*----------------------------------------------*\
	d{2}		两个数字
	|			表示选择（or）
	N/A			字符串
	\*----------------------------------------------*/
	boost::regex reg("(//d{2}|N/A)");
}

void testRegex::match7()
{
	/*----------------------------------------------*\
	/s		增加一个空格
	\*----------------------------------------------*/
	boost::regex reg("//d{3}[a-zA-Z]+.(//d{2}|N/A)//s");	// 
}

void testRegex::match8()
{
	/*----------------------------------------------*\
	()		子表达式
	/1		后项索引
	\*----------------------------------------------*/
	boost::regex reg("//d{3}([a-zA-Z]+).(//d{2}|N/A)//s//1");

}

void testRegex::search()
{
	testConsole::WriteLine(L"测试search");
	search1();
	search2();

	testConsole::WriteLine(L"结束search\r\n");
}

void testRegex::search1()
{
// 	typedef boost::match_results<std::string::const_iterator> smatch;
	boost::regex reg("(new)|(delete)");
	boost::smatch m;
	std::string s =	"Calls to new must be followed by delete. Calling simply new results in a leak!";
	bool bRes = boost::regex_search(s, m, reg);
	size_t num = m.size();
	std::string str,str1,str2;
	str = m[0].str();
	m[0].first;
	m[0].second;
	str1 = m[1].str();
	str2 = m[2].str();
	//boost::regex_search();
	testConsole::WriteLine(str);
	testConsole::WriteLine(str1);
	testConsole::WriteLine(str2);
}

void testRegex::search2()
{



}

void testRegex::replace()
{
	testConsole::WriteLine(L"测试replace");
	replace1();
	replace2();

	testConsole::WriteLine(L"结束replace\r\n");
}

void testRegex::replace1()
{
	/*----------------------------------------------*\
	\*----------------------------------------------*/
	boost::regex reg("(Colo)(u)(r)",
		boost::regex::icase | boost::regex::perl);
	testConsole::Write(L"表达式：");
	testConsole::WriteLine(reg.str());

	std::string s = "Colour, colours, color, colourize";
	testConsole::WriteLine(s);

	std::string s1 = boost::regex_replace(s, reg, "$1$3");
	testConsole::WriteLine(s1);
	std::string s2 = boost::regex_replace(s, reg, "$1");
	testConsole::WriteLine(s2);

}

void testRegex::replace2()
{
	/*----------------------------------------------*\
	\*----------------------------------------------*/


}
