#pragma once


//����ֻ������lib������δ����dll����
#ifdef _DEBUG
#pragma comment(lib,"vc15-test-md.lib") 
#pragma message("Automatically linking with vc15-test-m debug lib")
#else
#pragma comment(lib,"vc15-test-b.lib") 
#pragma message("Automatically linking with release vc15-test-m release lib")
#endif

#include "vc15FileSystem.h"
#include "vc15Time.h"