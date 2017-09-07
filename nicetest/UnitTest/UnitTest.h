#pragma once
#include "String.h"

class UnitTest abstract
{
	public:
		typedef void(*TestProc)();

		/// <summary>Print a green message.</summary>
		/// <param name="string">The content.</param>
		static void PrintMessage(const WString& string);

		/// <summary>Print a white information.</summary>
		/// <param name="string">The content.</param>
		static void PrintInfo(const WString& string);

		/// <summary>Print a red error.</summary>
		/// <param name="string">The content.</param>
		static void PrintError(const WString& string);

		static void PushTest(TestProc testProc);

		/// <summary>Run all test cases.</summary>
		static void RunAndDisposeTests();
};

#define TEST_CHECK_ERROR(CONDITION,DESCRIPTION) do{if(!(CONDITION))throw Error(DESCRIPTION);}while(0)

#define TEST_ASSERT(CONDITION) do{TEST_CHECK_ERROR(CONDITION,L"");}while(0)

/// <summary>
/// �ú����Ĺ��������ɲ����࣬��ʼ���ڴ�ʱ�齨������
/// �Զ���������
/// </summary>
#define TEST_CASE(NAME)\
	extern void TESTCASE_##NAME();														\
	class TESTCASE_RUNNER_##NAME														\
	{																					\
		public:																			\
			static void RunUnitTest()													\
			{																			\
				UnitTest::PrintMessage(L_(#NAME));										\
				TESTCASE_##NAME();														\
			}																			\
			TESTCASE_RUNNER_##NAME()													\
			{																			\
				UnitTest::PushTest(&TESTCASE_RUNNER_##NAME::RunUnitTest);				\
			}																			\
	} TESTCASE_RUNNER_##NAME##_INSTANCE;												\
	void TESTCASE_##NAME()

