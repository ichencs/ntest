#include "stdafx.h"

TEST_CASE(TestVariant)
{
	void* ptr = 0;
	WString str = L"你好啊";
	WString* pstr = &str;
	{
		new (&ptr)WString(str);			//这样初始化，如果 sizeof(WString) > sizeof(void*) 则会出现构造内容不完整！！
	}
}