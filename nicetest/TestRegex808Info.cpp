#include "StdAfx.h"
#include "TestUsing.h"

using namespace vl;
using namespace vl::unittest;
using namespace vl::regex;
using namespace vl::regex_internal;

TEST_CASE(TestRegexInfo)
{
	WString wstr = L"creo://paras/?code=1234&main_filename=ss.prt&sub_filename=ss_d.prt ";
	
	WString code = L"code=/d+";
	Regex regex(code, true);
	RegexMatch::Ref match = regex.Match(wstr);
	TEST_ASSERT(match->Success() == true);
	vint start = match->Result().Start();
	vint length = match->Result().Length();
	code = L".";
	Regex regex2(code, true);
	RegexMatch::List matchList;
	regex2.Split(wstr, true, matchList);
	TEST_ASSERT(match->Success());
	using namespace console;
	
	// 	int ncount = matchList.Count();
	for (size_t i = 0; i < matchList.Count(); i++)
	{
		RegexMatch::Ref match2 = matchList.Get(i);
		WString strResult = wstr.Sub(match2->Result().Start(), match2->Result().Length());
		Console::WriteLine(strResult);
	}
	
	code = L"main_filename=/l+/./l+";
	code = L"main_filename=/.*";
	Regex regex3(code, true);
	RegexMatch::Ref match3 = regex3.Match(wstr);
	
	if (match3->Success())
	{
		WString strRes = wstr.Sub(match3->Result().Start(), match3->Result().Length());
		Console::WriteLine(strRes);
	}
	
	
}
