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
	
	
}