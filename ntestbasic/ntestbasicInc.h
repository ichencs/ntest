#pragma once
#ifdef _DEBUG
#pragma comment(lib,"ntestbasicd.lib") 
#pragma message("Automatically linking with ntestbasicd debug lib")
#else
#pragma comment(lib,"ntestbasic.lib") 
#pragma message("Automatically linking with ntestbasic release lib")
#endif

#include "testConsole.h"
#include "Pointer.h"