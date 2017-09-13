#include "stdafx.h"
#include "UnitTest.h"

// using namespace vl::environemnt;
using namespace vl::environment;
TEST_CASE(TestEnvironment)
{
	WString user = Environment::UserName();
	WString computer = Environment::ComputerName();
	Environment env;
	env.System();
	env.Version();
	env.Variable();

}