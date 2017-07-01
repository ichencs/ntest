#pragma once


//这里只定义了lib导出，未定义dll导出
#ifdef _DEBUG
#pragma comment(lib,"ntestmd.lib") 
#pragma message("Automatically linking with ntestm debug lib")
#else
#pragma comment(lib,"ntestb.lib") 
#pragma message("Automatically linking with release ntestm release lib")
#endif

#include "vc15FileSystem.h"
#include "vc15Time.h"