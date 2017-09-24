#pragma once

// #ifdef _DEBUG
// #pragma comment(lib,"nbasicd.lib")
// #pragma message("Automatically linking with nbasicd debug lib")
// #else
// #pragma comment(lib,"nbasic.lib")
// #pragma message("Automatically linking with nbasic release lib")
// #endif

#include "Basic.h"

#include "Pointer.h"
#include "String.h"
#include "Console.h"
#include "Exception.h"
#include "Locale.h"
#include "GlobalStorage.h"
#include "Locale.h"
#include "Threading.h"
#include "HttpUtility.h"
#include "system.h"

#include ".\FileSystem\Folder.h"
#include ".\FileSystem\file.h"
#include ".\FileSystem\FilePath.h"
#include ".\FileSystem\FileInfo.h"

#include ".\Stream\Interfaces.h"
#include ".\Stream\Accessor.h"
#include ".\Stream\BroadcastStream.h"
#include ".\Stream\CharFormat.h"
#include ".\Stream\CacheStream.h"
#include ".\Stream\FileStream.h"
#include ".\Stream\memorystream.h"
#include ".\Stream\recorderstream.h"
#include ".\Stream\CompressionStream.h"

#include ".\Collections\interfaces.h"
#include ".\Collections\Pair.h"
#include ".\Collections\List.h"
#include ".\Collections\Dictionary.h"
#include ".\Collections\Operation.h"
#include ".\Collections\OperationCopyFrom.h"
#include ".\Collections\OperationForEach.h"
#include ".\Collections\OperationString.h"
#include ".\Collections\OperationEnumerable.h"
#include ".\Collections\OperationSequence.h"

#include ".\Regex\Regex.h"
#include ".\Regex\RegexAutomaton.h"
#include ".\Regex\RegexData.h"
#include ".\Regex\RegexExpression.h"
#include ".\Regex\RegexWriter.h"
#include ".\Regex\RegexPure.h"
#include ".\Regex\RegexRich.h"

#include ".\UnitTest\UnitTest.h"