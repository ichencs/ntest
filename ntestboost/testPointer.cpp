#include "StdAfx.h"
#include "testPointer.h"
#include <boost\smart_ptr\weak_ptr.hpp>

using namespace boost;


testPointer::testPointer()
{
}


testPointer::~testPointer()
{
}

void testPointer::test()
{
	boost::shared_ptr<int> s_ptr(new int(2));
	boost::weak_ptr<int> w_ptr;
	w_ptr = s_ptr;
	w_ptr.use_count();
	w_ptr.lock();

}
