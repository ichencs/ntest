#pragma once


//����ֻ������lib������δ����dll����
#ifdef _DEBUG
#pragma comment(lib,"ntestmd.lib") 
#pragma message("Automatically linking with ntestm debug lib")
#else
#pragma comment(lib,"ntestb.lib") 
#pragma message("Automatically linking with release ntestm release lib")
#endif

#include "vc15FileSystem.h"
#include "vc15Time.h"