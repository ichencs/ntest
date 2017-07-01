#pragma once
#ifdef _DEBUG
#pragma comment(lib,"ntestbasicd.lib") 
#pragma message("Automatically linking with ntestb debug dll")
#else
#pragma comment(lib,"ntestbasic.lib") 
#pragma message("Automatically linking with release ntestb release dll")
#endif

#include "testConsole.h"
