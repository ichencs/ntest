#pragma once

#ifdef _DEBUG
#pragma comment(lib,"ntestboostd.lib") 
#pragma message("Automatically linking with ntestb debug dll")
#else
#pragma comment(lib,"ntestboost.lib") 
#pragma message("Automatically linking with release ntestb release dll")
#endif


#include "ntestDef.h"
#include "testboost.h"