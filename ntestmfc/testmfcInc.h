#pragma once


//这里只定义了lib导出，未定义dll导出
#ifdef _DEBUG
#pragma comment(lib,"ntestmfcd.lib") 
#pragma message("Automatically linking with ntestmfc debug lib")
#else
#pragma comment(lib,"ntestb.lib") 
#pragma message("Automatically linking with release ntestmfc release lib")
#endif

#include "testFileSystem.h"
#include "testTime.h"