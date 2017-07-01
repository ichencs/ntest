#pragma once

#ifdef _DEBUG
#pragma comment(lib,"ntestbd.lib") 
#pragma message("Automatically linking with ntestb debug dll")
#else
#pragma comment(lib,"ntestb.lib") 
#pragma message("Automatically linking with release ntestb release dll")
#endif


#include "ntestDef.h"
