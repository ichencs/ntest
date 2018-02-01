#include "stdafx.h"

TEST_CASE(TestVariant)
{
	// 	void* ptr = 0;
	// 	WString str = L"你好啊";
	// 	WString* pstr = &str;
	// 	{
	// 		new (&ptr)WString(str);			//这样初始化，如果 sizeof(WString) > sizeof(void*) 则会出现构造内容不完整！！
	// 	}
	Variant var = 1;
	Variant var8 = 10i8;
	Variant var16 = 17i16;
	Variant var32 = 123456;
	Variant varStr = WString(L"你好吗？");
	bool bIsDetached = varStr.isDetached();
	{
		Variant varStr2 = varStr;
		AString astr = varStr.toAString();
		WString wstr = varStr2.toWString();
		AString intStr = var32.toAString();
	}
	WString wstr_t = Locale::UserDefault().GetName();
	DateTime dt = DateTime::LocalTime();
	varStr = "true";
	bool bRes = varStr.toBool();
	
}

TEST_CASE(TestVariantJ)
{
	Variant var_b = L"TRUE";
	TEST_ASSERT(var_b.toBool() == true);
	TEST_ASSERT(var_b.toAString() == "TRUE");
	TEST_ASSERT(var_b.toWString() == L"TRUE");
	var_b = L"FALSE";
	TEST_ASSERT(var_b.toBool() == false);
	TEST_ASSERT(var_b.toAString() == "FALSE");
	TEST_ASSERT(var_b.toWString() == L"FALSE");
	var_b = L"";
	TEST_ASSERT(var_b.toBool() == false);
	TEST_ASSERT(var_b.toAString() == "");
	TEST_ASSERT(var_b.toWString() == L"");
	
	Variant var_a = L"";
	TEST_ASSERT(var_a == var_b);
	var_a = var_b = L"你好";
	TEST_ASSERT(var_a == var_b);
	
	var_a = var_b = L"nihao";
	var_b = "nihao";
	TEST_ASSERT(var_a == var_b);
	TEST_ASSERT(var_a == "nihao");
	TEST_ASSERT(var_a == L"nihao");
	TEST_ASSERT(var_a.isWString());
	TEST_ASSERT(var_a.isString());
	var_a = 1i64;
	TEST_ASSERT(var_a.isInt());
	TEST_ASSERT(var_a.isNumber());
	
	TEST_ASSERT(var_a.toInt() == 1);
	var_b = 1;
	TEST_ASSERT(!(var_a != var_b));
	var_a = 'a';
	var_b = L'a';
	TEST_ASSERT(var_a == var_b);
	
}

