#pragma once

#pragma once
#ifdef _DEBUG
#pragma comment(lib,"nteststdd.lib") 
#pragma message("Automatically linking with nteststdd debug lib")
#else
#pragma comment(lib,"nteststd.lib") 
#pragma message("Automatically linking with nteststd release lib")
#endif


#include "testString.h"