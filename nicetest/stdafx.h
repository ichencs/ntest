// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

// #include <stdio.h>
// #include <tchar.h>

#include "../nbasic/nbasicInc.h"
// #include <afx.h>

// TODO:  在此处引用程序需要的其他头文件


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
