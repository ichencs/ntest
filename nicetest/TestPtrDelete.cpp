#include "stdafx.h"

using namespace vl;
using namespace vl::console;
namespace test_delete
{
	class tdl_b
	{
		public:
			tdl_b();
			virtual ~tdl_b();
			
		private:
		
	};
	
	tdl_b::tdl_b()
	{
	
	}
	
	tdl_b::~tdl_b()
	{
		Console::WriteLine(L"�����˻���");
	}
	
	class tdl_s : public tdl_b
	{
		public:
			tdl_s();
			~tdl_s();
			
		private:
		
	};
	
	tdl_s::tdl_s()
	{
	}
	
	tdl_s::~tdl_s()
	{
		Console::WriteLine(L"����������.");
	}
	
	class tdl_ss : public tdl_s
	{
		public:
			tdl_ss();
			~tdl_ss();
			
		private:
		
	};
	
	tdl_ss::tdl_ss()
	{
	}
	
	tdl_ss::~tdl_ss()
	{
		Console::WriteLine(L"������������...");
	}
	
}


using namespace test_delete;

TEST_CASE(TestPtrDelte)
{
	Ptr<tdl_b> ptr_smart = new tdl_ss();
	
	
	
}

