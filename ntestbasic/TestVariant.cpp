#include "stdafx.h"

TEST_CASE(TestVariant)
{
	void* ptr = 0;
	WString str = L"��ð�";
	WString* pstr = &str;
	{
		new (&ptr)WString(str);			//������ʼ������� sizeof(WString) > sizeof(void*) �����ֹ������ݲ���������
	}
}