#include "stdafx.h"

TEST_CASE(TestVariant)
{
	// 	void* ptr = 0;
	// 	WString str = L"��ð�";
	// 	WString* pstr = &str;
	// 	{
	// 		new (&ptr)WString(str);			//������ʼ������� sizeof(WString) > sizeof(void*) �����ֹ������ݲ���������
	// 	}
	Variant var = 1;
	Variant var8 = 10i8;
	Variant var16 = 17i16;
	Variant var32 = 123456;
	Variant varStr = WString(L"�����");
	bool bIsDetached = varStr.isDetached();
	{
		Variant varStr2 = varStr;
		AString astr = varStr.toAString();
		WString wstr = varStr2.toWString();
		AString intStr = var32.toAString();
	}
	WString wstr_t = Locale::UserDefault().GetName();
	
}