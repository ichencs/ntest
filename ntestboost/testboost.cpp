#include "stdafx.h"
#include "testboost.h"
#include "testRegex.h"
#include "testFilesystem.h"


testboost::testboost()
{
	test();
}


testboost::~testboost()
{
}

void testboost::test()
{
	test_regex();
// 	test_filesystem();
}

void testboost::test_regex()
{
	testRegex treg;

}

void testboost::test_filesystem()
{
	testFilesystem tfs;

}
