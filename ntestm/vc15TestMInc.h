#pragma once


//����ֻ������lib������δ����dll����
#ifdef _DEBUG
#pragma comment(lib,"ntestmd.lib") 
#pragma message("Automatically linking with ntestm debug lib")
#else
#pragma comment(lib,"ntestb.lib") 
#pragma message("Automatically linking with release ntestm release lib")
#endif

#include "testFileSystem.h"
#include "testTime.h"