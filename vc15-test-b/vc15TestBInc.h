#pragma once

#ifdef _DEBUG
#pragma comment(lib,"vc15-test-bd.lib") 
#pragma message("Automatically linking with vc15-test-b debug dll")
#else
#pragma comment(lib,"vc15-test-b.lib") 
#pragma message("Automatically linking with release vc15-test-b release dll")
#endif


#include "testDef.h"
