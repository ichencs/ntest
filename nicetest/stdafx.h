// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

// #include <stdio.h>
// #include <tchar.h>

#include "../nbasic/nbasicInc.h"
// #include <afx.h>

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�


#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define NICE_CHECK_MEMORY_LEAKS


#ifdef NICE_CHECK_MEMORY_LEAKS
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define NICE_CHECK_MEMORY_LEAKS_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new NICE_CHECK_MEMORY_LEAKS_NEW
#endif

#ifdef NICE_CHECK_MEMORY_LEAKS_NEW
#undef new
#endif
