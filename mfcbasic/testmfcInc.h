#pragma once


//����ֻ������lib������δ����dll����
#ifdef _DEBUG
#pragma comment(lib,"mfcbasicd.lib") 
#pragma message("Automatically linking with ntestmfc debug lib")
#else
#pragma comment(lib,"mfcbasic.lib") 
#pragma message("Automatically linking with mfcbasic release lib")
#endif


#include "testFileSystem.h"
#include "testTime.h"