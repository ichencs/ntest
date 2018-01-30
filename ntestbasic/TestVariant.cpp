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
	
}