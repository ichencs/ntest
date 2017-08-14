#pragma once

#pragma once
#ifdef _DEBUG
#pragma comment(lib,"nteststdd.lib") 
#pragma message("Automatically linking with teststdd debug lib")
#else
#pragma comment(lib,"nteststd.lib") 
#pragma message("Automatically linking with teststd release lib")
#endif


#include "testString.h"