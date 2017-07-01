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
}

void testboost::test_regex()
{
	testRegex treg;
	treg.test();
	testFilesystem tfs;
	tfs.test();

}
