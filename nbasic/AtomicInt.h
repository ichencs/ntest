#pragma once
#include "Basic.h"

namespace vl
{
	class BasicAtomicInt
	{
		public:
			BasicAtomicInt(int value = 0): _q_value(value) {};
			virtual ~BasicAtomicInt() {};
			
		public:
			volatile vint _q_value;
			inline bool operator==(int value) const
			{
				return _q_value == value;
			}
			
			inline bool operator!=(int value) const
			{
				return _q_value != value;
			}
			
			inline bool operator!() const
			{
				return _q_value == 0;
			}
			
			inline operator vint() const
			{
				return _q_value;
			}
			
			inline BasicAtomicInt& operator=(int value)
			{
				_q_value = value;
				return *this;
			}
			
			
		public:
			//static bool isReferenceCountingNative();
			//static bool isReferenceCountingWaitFree();
			
			bool ref();
			bool deref();
			
			//static bool isTestAndSetNative();
			//static bool isTestAndSetWaitFree();
			
			/*	bool testAndSetRelaxed(int expectedValue, int newValue);
				bool testAndSetAcquire(int expectedValue, int newValue);
				bool testAndSetRelease(int expectedValue, int newValue);
				bool testAndSetOrdered(int expectedValue, int newValue);*/
			
			//static bool isFetchAndStoreNative();
			//static bool isFetchAndStoreWaitFree();
			
			//int fetchAndStoreRelaxed(int newValue);
			//int fetchAndStoreAcquire(int newValue);
			//int fetchAndStoreRelease(int newValue);
			//int fetchAndStoreOrdered(int newValue);
			
			//static bool isFetchAndAddNative();
			//static bool isFetchAndAddWaitFree();
			
			//int fetchAndAddRelaxed(int valueToAdd);
			//int fetchAndAddAcquire(int valueToAdd);
			//int fetchAndAddRelease(int valueToAdd);
			//int fetchAndAddOrdered(int valueToAdd);
			
	};
	
	/*inline bool BasicAtomicInt::isReferenceCountingNative()
	{
		return true;
	}
	inline bool BasicAtomicInt::isReferenceCountingWaitFree()
	{
		return true;
	}
	
	inline bool BasicAtomicInt::isTestAndSetNative()
	{
		return true;
	}
	inline bool BasicAtomicInt::isTestAndSetWaitFree()
	{
		return true;
	}
	
	inline bool BasicAtomicInt::isFetchAndStoreNative()
	{
		return true;
	}
	inline bool BasicAtomicInt::isFetchAndStoreWaitFree()
	{
		return true;
	}
	
	inline bool BasicAtomicInt::isFetchAndAddNative()
	{
		return true;
	}
	inline bool BasicAtomicInt::isFetchAndAddWaitFree()
	{
		return true;
	}*/
	
	inline bool BasicAtomicInt::ref()
	{
		return INCRC(&_q_value) != 0;
	}
	
	inline bool BasicAtomicInt::deref()
	{
		return DECRC(&_q_value) != 0;
	}
	
	// 	inline bool BasicAtomicInt::testAndSetOrdered(int expected, int newval)
	// 	{
	// 		return q_atomic_test_and_set_int(&_q_value, expected, newval) != 0;
	// 	}
	//
	// 	inline int BasicAtomicInt::fetchAndStoreOrdered(int newval)
	// 	{
	// 		return q_atomic_set_int(&_q_value, newval);
	// 	}
	//
	// 	inline int BasicAtomicInt::fetchAndAddOrdered(int aValue)
	// 	{
	// 		return q_atomic_fetch_and_add_int(&_q_value, aValue);
	// 	}
	//
	//
	// 	inline bool BasicAtomicInt::testAndSetRelaxed(int expectedValue, int newValue)
	// 	{
	// 		return testAndSetOrdered(expectedValue, newValue);
	// 	}
	//
	// 	inline bool BasicAtomicInt::testAndSetAcquire(int expectedValue, int newValue)
	// 	{
	// 		return testAndSetOrdered(expectedValue, newValue);
	// 	}
	//
	// 	inline bool BasicAtomicInt::testAndSetRelease(int expectedValue, int newValue)
	// 	{
	// 		return testAndSetOrdered(expectedValue, newValue);
	// 	}
	
	/*inline int BasicAtomicInt::fetchAndStoreRelaxed(int newValue)
	{
		return fetchAndStoreOrdered(newValue);
	}
	
	inline int BasicAtomicInt::fetchAndStoreAcquire(int newValue)
	{
		return fetchAndStoreOrdered(newValue);
	}
	
	inline int BasicAtomicInt::fetchAndStoreRelease(int newValue)
	{
		return fetchAndStoreOrdered(newValue);
	}
	
	inline int BasicAtomicInt::fetchAndAddRelaxed(int valueToAdd)
	{
		return fetchAndAddOrdered(valueToAdd);
	}
	
	inline int BasicAtomicInt::fetchAndAddAcquire(int valueToAdd)
	{
		return fetchAndAddOrdered(valueToAdd);
	}
	
	inline int BasicAtomicInt::fetchAndAddRelease(int valueToAdd)
	{
		return fetchAndAddOrdered(valueToAdd);
	}*/
	
	
	
	template<typename T>
	class BasicAtomicPointer
	{
		public:
			BasicAtomicPointer(): _q_value(0) {};
			virtual ~BasicAtomicPointer() {};
			T* volatile _q_value;
			
			inline BasicAtomicPointer<T>& operator=(T* value)
			{
				_q_value = value;
				return *this;
			}
			
			inline bool operator==(T* value) const
			{
				return _q_value == value;
			}
			
			inline bool operator!=(T* value) const
			{
				return !operator==(value);
			}
			
			inline bool operator!() const
			{
				return operator==(0);
			}
			
			inline operator T* () const
			{
				return _q_value;
			}
			
			inline T* operator->() const
			{
				return _q_value;
			}
		private:
		
	};
	
	
	
	
	class AtomicInt:
		public BasicAtomicInt
	{
		public:
			inline AtomicInt(int value = 0)
				: BasicAtomicInt(value)
			{
			
			};
			~AtomicInt() {};
			
			inline AtomicInt(const AtomicInt& other)
			{
				_q_value = other._q_value;
			}
			
			inline AtomicInt& operator=(const AtomicInt& other)
			{
				if (this != &other)
				{
					BasicAtomicInt::operator=(other);
				}
				return *this;
			}
			
			inline AtomicInt& operator=(int value)
			{
				BasicAtomicInt::operator=(value);
				return *this;
			}
			
	};
	
	
	/*!
	This is a helper for the assignment operators of implicitly
	shared classes. Your assignment operator should look like this:
	
	\snippet doc/src/snippets/code/src.corelib.thread.qatomic.h 0
	*/
	template <typename T>
	inline void AtomicAssign(T*& d, T* x)
	{
		if (d == x)
		{
			return;
		}
		x->ref.ref();
		if (!d->ref.deref())
		{
			delete d;
		}
		d = x;
	}
	
	/*!
	This is a helper for the detach method of implicitly shared
	classes. Your private class needs a copy constructor which copies
	the members and sets the refcount to 1. After that, your detach
	function should look like this:
	
	\snippet doc/src/snippets/code/src.corelib.thread.qatomic.h 1
	*/
	template <typename T>
	inline void AtomicDetach(T*& d)
	{
		if (d->ref == 1)
			return;
			
		T* x = d;
		d = new T(*d);
		if (!x->ref.deref())
			delete x;
	}
	
}


