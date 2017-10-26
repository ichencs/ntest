#pragma once
#include "Basic.h"
using namespace vl;



class nAtomicInt :public Object
{
protected:
	volatile vint*		counter;


	void Inc()
	{
		if (counter)
		{
			INCRC(counter);
		}
	};

	void Dec(bool deleteIfZero = true)
	{
		if (counter)
		{
			if (DECRC(counter) == 0)
			{
				if (deleteIfZero)
				{
					delete counter;
				}
 				this->counter = nullptr;
			}
		}
	}
public:
	nAtomicInt()
		:counter(new vint(1))
	{

	}

	nAtomicInt(const nAtomicInt& other)
	{
		this->counter = other.counter;
		Inc();
	}

	nAtomicInt& operator=(const nAtomicInt& other )
	{
		Dec();
		this->counter = other.counter;
		Inc();
	}

	bool ref()
	{
		return counter != nullptr;
	};
	bool deref()
	{
		return counter == nullptr;
	}

	volatile vint* Count()
	{
		return counter;
	}


	~nAtomicInt() 
	{
		Dec();
	}


};
