#include "FileSystem.h"
#include "../Locale.h"
#include "../Collections/OperationForEach.h"
#include "../Stream/FileStream.h"
#include "../Stream/Accessor.h"
#include "../Exception.h"
#if defined VCZH_MSVC
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#elif defined VCZH_GCC
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#endif

namespace vl
{
	namespace filesystem
	{
		using namespace collections;
		using namespace stream;
		
		
		
		
	}
}
