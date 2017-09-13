#ifndef NICE_ENVIRONMENT
#define NICE_ENVIRONMENT
#include "String.h"


namespace vl
{
	namespace environment
	{
		class Environment
		{
		public:
			Environment();
			~Environment();
		public:
			static WString ComputerName();
			static WString UserName();
			static void Version();
			static void System();
			void Variable();
		};
	}
}

#endif