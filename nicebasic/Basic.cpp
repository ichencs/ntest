#include "stdafx.h"
#include "Basic.h"


NotCopyable::NotCopyable(const NotCopyable&)
{

}

NotCopyable::NotCopyable()
{

}

NotCopyable& NotCopyable::operator=(const NotCopyable&)
{
	return *this;
}

Object::~Object()
{

}
