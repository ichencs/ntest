/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Framework::Basic

Classes:
NotCopyable									：不可复制对象
Error										：内部错误，检查到了不可出现的变量、参数或状态错误
Object										：对象基类

Macros:
CHECK_ERROR(CONDITION,DESCRIPTION)			：检查内部错误
***********************************************************************/

#ifndef VCZH_BASIC
#define VCZH_BASIC


#if defined _WIN64 || __x86_64 || __LP64__
#define VCZH_64
#endif

#if defined _MSC_VER
#define VCZH_MSVC
#else
#define VCZH_GCC
#if defined(__APPLE__)
#define VCZH_APPLE
#endif
#endif

#if defined VCZH_MSVC
#include <intrin.h>
#endif

#define L_(x) L__(x)
#define L__(x) L ## x

namespace vl
{

	/***********************************************************************
	32位/64位兼容
	***********************************************************************/
	
#if defined VCZH_MSVC
	/// <summary>1-byte signed integer.</summary>
	typedef signed __int8			vint8_t;
	/// <summary>1-byte unsigned integer.</summary>
	typedef unsigned __int8			vuint8_t;
	/// <summary>2-bytes signed integer.</summary>
	typedef signed __int16			vint16_t;
	/// <summary>2-bytes unsigned integer.</summary>
	typedef unsigned __int16		vuint16_t;
	/// <summary>4-bytes signed integer.</summary>
	typedef signed __int32			vint32_t;
	/// <summary>4-bytes unsigned integer.</summary>
	typedef unsigned __int32		vuint32_t;
	/// <summary>8-bytes signed integer.</summary>
	typedef signed __int64			vint64_t;
	/// <summary>8-bytes unsigned integer.</summary>
	typedef unsigned __int64		vuint64_t;
#endif
	
#ifdef VCZH_64
	/// <summary>Signed interface whose size is equal to sizeof(void*).</summary>
	typedef vint64_t				vint;
	/// <summary>Signed interface whose size is equal to sizeof(void*).</summary>
	typedef vint64_t				vsint;
	/// <summary>Unsigned interface whose size is equal to sizeof(void*).</summary>
	typedef vuint64_t				vuint;
#else
	/// <summary>Signed interface whose size is equal to sizeof(void*).</summary>
	typedef vint32_t				vint;
	/// <summary>Signed interface whose size is equal to sizeof(void*).</summary>
	typedef vint32_t				vsint;
	/// <summary>Unsigned interface whose size is equal to sizeof(void*).</summary>
	typedef vuint32_t				vuint;
#endif
	/// <summary>Signed interger representing position.</summary>
	typedef vint64_t				pos_t;
	
#ifdef VCZH_64
#define ITOA_S		_i64toa_s
#define ITOW_S		_i64tow_s
#define I64TOA_S	_i64toa_s
#define I64TOW_S	_i64tow_s
#define UITOA_S		_ui64toa_s
#define UITOW_S		_ui64tow_s
#define UI64TOA_S	_ui64toa_s
#define UI64TOW_S	_ui64tow_s
#if defined VCZH_MSVC
#define INCRC(x)	(_InterlockedIncrement64(x))
#define DECRC(x)	(_InterlockedDecrement64(x))
#endif
#else
#define ITOA_S		_itoa_s
#define ITOW_S		_itow_s
#define I64TOA_S	_i64toa_s
#define I64TOW_S	_i64tow_s
#define UITOA_S		_ui64toa_s
#define UITOW_S		_ui64tow_s
#define UI64TOA_S	_ui64toa_s
#define UI64TOW_S	_ui64tow_s
#if defined VCZH_MSVC
#define INCRC(x)	(_InterlockedIncrement((volatile long*)(x)))
#define DECRC(x)	(_InterlockedDecrement((volatile long*)(x)))
#endif
#endif
	
	/***********************************************************************
	基础
	***********************************************************************/
	
	class NotCopyable
	{
	 private:
		NotCopyable(const NotCopyable&);
		NotCopyable& operator=(const NotCopyable&);
	 public:
		NotCopyable();
	};
	
	/// <summary>Base type of all errors. An error is an exception that you are not allowed to catch. Raising it means there is a fatal error in the code.</summary>
	class Error
	{
	 private:
		const wchar_t*		description;
	 public:
		Error(const wchar_t* _description);
		
		const wchar_t*		Description()const;
	};
	
#if defined VCZH_MSVC || defined VCZH_GCC || defined _DEBUG
#define CHECK_ERROR(CONDITION,DESCRIPTION) do{if(!(CONDITION))throw Error(DESCRIPTION);}while(0)
#elif defined NDEBUG
#define CHECK_ERROR(CONDITION,DESCRIPTION)
#endif
	
#define CHECK_FAIL(DESCRIPTION) do{throw Error(DESCRIPTION);}while(0)
	
#define SCOPE_VARIABLE(TYPE, VARIABLE, VALUE)\
	if(bool __scope_variable_flag__=true)\
		for(TYPE VARIABLE = VALUE;__scope_variable_flag__;__scope_variable_flag__=false)
	
	/***********************************************************************
	类型计算
	***********************************************************************/
	
	template<typename T>
	struct RemoveReference
	{
		typedef T			Type;
	};
	
	template<typename T>
	struct RemoveReference<T&>
	{
		typedef T			Type;
	};
	
	
	template<typename T>
	struct RemoveConst
	{
		typedef T			Type;
	};
	
	template<typename T>
	struct RemoveConst<const T>
	{
		typedef T			Type;
	};
	
	template<typename T>
	struct RemoveVolatile
	{
		typedef T			Type;
	};
	
	template<typename T>
	struct RemoveVolatile<volatile T>
	{
		typedef T			Type;
	};
	
	template<typename T>
	struct RemoveCVR
	{
		typedef T								Type;
	};
	
	template<typename T>
	struct RemoveCVR<T&>
	{
		typedef typename RemoveCVR<T>::Type		Type;
	};
	
	
	template<typename T>
	struct RemoveCVR<const T>
	{
		typedef typename RemoveCVR<T>::Type		Type;
	};
	
	template<typename T>
	struct RemoveCVR<volatile T>
	{
		typedef typename RemoveCVR<T>::Type		Type;
	};
	
	
	/***********************************************************************
	基础
	***********************************************************************/
	
	/// <summary>Base type of all classes.</summary>
	class Object
	{
	 public:
		virtual ~Object();
	};
	
	/// <summary>Type for storing a value to wherever requiring a [T:vl.Ptr`1] to [T:vl.Object].</summary>
	/// <typeparam name="T">Type of the value.</typeparam>
	template<typename T>
	class ObjectBox : public Object
	{
	 private:
		T					object;
	 public:
		/// <summary>Box a value.</summary>
		/// <param name="_object">The value to box.</param>
		ObjectBox(const T& _object)
			: object(_object)
		{
		}
		
		
		/// <summary>Copy a box.</summary>
		/// <param name="value">The box.</param>
		ObjectBox(const ObjectBox<T>& value)
			: object(value.object)
		{
		}
		
		
		/// <summary>Box a value.</summary>
		/// <returns>The boxed value.</returns>
		/// <param name="_object">The value to box.</param>
		ObjectBox<T>& operator=(const T& _object)
		{
			object = _object;
			return *this;
		}
		
		/// <summary>Copy a box.</summary>
		/// <returns>The boxed value.</returns>
		/// <param name="value">The box.</param>
		ObjectBox<T>& operator=(const ObjectBox<T>& value)
		{
			object = value.object;
			return *this;
		}
		
		
		/// <summary>Unbox the value.</summary>
		/// <returns>The original value.</returns>
		const T& Unbox()
		{
			return object;
		}
	};
	
	/// <summary>Type for optionally storing a value.</summary>
	/// <typeparam name="T">Type of the value.</typeparam>
	template<typename T>
	class Nullable
	{
	 private:
		T*					object;
	 public:
		/// <summary>Create a null value.</summary>
		Nullable()
			: object(0)
		{
		}
		
		/// <summary>Create a non-null value.</summary>
		/// <param name="value">The value to copy.</param>
		Nullable(const T& value)
			: object(new T(value))
		{
		}
		
		
		/// <summary>Copy a nullable value.</summary>
		/// <param name="nullable">The nullable value to copy.</param>
		Nullable(const Nullable<T>& nullable)
			: object(nullable.object ? new T(*nullable.object) : 0)
		{
		}
		
		
		~Nullable()
		{
			if (object)
			{
				delete object;
				object = 0;
			}
		}
		
		/// <summary>Create a non-null value.</summary>
		/// <returns>The created nullable value.</returns>
		/// <param name="value">The value to copy.</param>
		Nullable<T>& operator=(const T& value)
		{
			if (object)
			{
				delete object;
				object = 0;
			}
			
			object = new T(value);
			return *this;
		}
		
		/// <summary>Copy a nullable value.</summary>
		/// <returns>The created nullable value.</returns>
		/// <param name="nullable">The nullable value to copy.</param>
		Nullable<T>& operator=(const Nullable<T>& nullable)
		{
			if (this != &nullable)
			{
				if (object)
				{
					delete object;
					object = 0;
				}
				
				if (nullable.object)
				{
					object = new T(*nullable.object);
				}
			}
			
			return *this;
		}
		
		
		static bool Equals(const Nullable<T>& a, const Nullable<T>& b)
		{
			return
			  a.object
			  ? b.object
			  ? *a.object == *b.object
			  : false
			  : b.object
			  ? false
			  : true;
		}
		
		static vint Compare(const Nullable<T>& a, const Nullable<T>& b)
		{
			return
			  a.object
			  ? b.object
			  ? (*a.object == *b.object ? 0 : *a.object < *b.object ? -1 : 1)
			  : 1
			  : b.object
			  ? -1
			  : 0;
		}
		
		bool operator==(const Nullable<T>& nullable)const
		{
			return Equals(*this, nullable);
		}
		
		bool operator!=(const Nullable<T>& nullable)const
		{
			return !Equals(*this, nullable);
		}
		
		bool operator<(const Nullable<T>& nullable)const
		{
			return Compare(*this, nullable) < 0;
		}
		
		bool operator<=(const Nullable<T>& nullable)const
		{
			return Compare(*this, nullable) <= 0;
		}
		
		bool operator>(const Nullable<T>& nullable)const
		{
			return Compare(*this, nullable) > 0;
		}
		
		bool operator>=(const Nullable<T>& nullable)const
		{
			return Compare(*this, nullable) >= 0;
		}
		
		/// <summary>Convert the nullable value to a bool value.</summary>
		/// <returns>Returns true if it is not null.</returns>
		operator bool()const
		{
			return object != 0;
		}
		
		/// <summary>Unbox the value. This operation will cause an access violation of it is null.</summary>
		/// <returns>The original value.</returns>
		const T& Value()const
		{
			return *object;
		}
	};
	
	template<typename T, size_t minSize>
	union BinaryRetriver
	{
		T t;
		char binary[sizeof(T) > minSize ? sizeof(T) : minSize];
	};
	
	/***********************************************************************
	配置
	***********************************************************************/
	
	/// <summary>Get the index type of a value for containers.</summary>
	/// <typeparam name="T">Type of the value.</typeparam>
	template<typename T>
	struct KeyType
	{
	 public:
		/// <summary>The index type of a value for containers.</summary>
		typedef T Type;
		
		/// <summary>Convert a value to its index type.</summary>
		/// <returns>The corresponding index value.</returns>
		/// <param name="value">The value.</param>
		static T GetKeyValue(const T& value)
		{
			return value;
		}
	};
	
	/// <summary>Test is a type a Plain-Old-Data type for containers.</summary>
	/// <typeparam name="T">The type to test.</typeparam>
	template<typename T>
	struct POD
	{
		/// <summary>Returns true if the type is a Plain-Old-Data type.</summary>
		static const bool Result = false;
	};
	
	template<>struct POD<bool>
	{
		static const bool Result = true;
	};
	template<>struct POD<vint8_t>
	{
		static const bool Result = true;
	};
	template<>struct POD<vuint8_t>
	{
		static const bool Result = true;
	};
	template<>struct POD<vint16_t>
	{
		static const bool Result = true;
	};
	template<>struct POD<vuint16_t>
	{
		static const bool Result = true;
	};
	template<>struct POD<vint32_t>
	{
		static const bool Result = true;
	};
	template<>struct POD<vuint32_t>
	{
		static const bool Result = true;
	};
	template<>struct POD<vint64_t>
	{
		static const bool Result = true;
	};
	template<>struct POD<vuint64_t>
	{
		static const bool Result = true;
	};
	template<>struct POD<char>
	{
		static const bool Result = true;
	};
	template<>struct POD<wchar_t>
	{
		static const bool Result = true;
	};
	template<typename T>struct POD<T*>
	{
		static const bool Result = true;
	};
	template<typename T>struct POD<T&>
	{
		static const bool Result = true;
	};
	template<typename T, typename C>struct POD<T C::*>
	{
		static const bool Result = true;
	};
	template<typename T, vint _Size>struct POD<T[_Size]>
	{
		static const bool Result = POD<T>::Result;
	};
	template<typename T>struct POD<const T>
	{
		static const bool Result = POD<T>::Result;
	};
	template<typename T>struct POD<volatile T>
	{
		static const bool Result = POD<T>::Result;
	};
	template<typename T>struct POD<const volatile T>
	{
		static const bool Result = POD<T>::Result;
	};
	
	/***********************************************************************
	时间
	***********************************************************************/
	
	/// <summary>A type representing the combination of date and time.</summary>
	struct DateTime
	{
		vint				year;
		vint				month;
		vint				dayOfWeek;
		vint				day;
		vint				hour;
		vint				minute;
		vint				second;
		vint				milliseconds;
		
		vuint64_t			totalMilliseconds;
		
		// in gcc, this will be mktime(t) * 1000 + gettimeofday().tv_usec / 1000
		vuint64_t			filetime;
		
		/// <summary>Get the current local time.</summary>
		/// <returns>The current local time.</returns>
		static DateTime		LocalTime();
		
		/// <summary>Get the current UTC time.</summary>
		/// <returns>The current UTC time.</returns>
		static DateTime		UtcTime();
		
		/// <summary>Create a date time value.</summary>
		/// <returns>The created date time value.</returns>
		/// <param name="_year">The year.</param>
		/// <param name="_month">The month.</param>
		/// <param name="_day">The day.</param>
		/// <param name="_hour">The hour.</param>
		/// <param name="_minute">The minute.</param>
		/// <param name="_second">The second.</param>
		/// <param name="_milliseconds">The millisecond.</param>
		static DateTime		FromDateTime(vint _year, vint _month, vint _day, vint _hour = 0, vint _minute = 0, vint _second = 0, vint _milliseconds = 0);
		
		static DateTime		FromFileTime(vuint64_t filetime);
		
		/// <summary>Create an empty date time value.</summary>
		DateTime();
		
		/// <summary>Convert the UTC time to the local time.</summary>
		/// <returns>The UTC time.</returns>
		DateTime			ToLocalTime();
		/// <summary>Convert the local time to the UTC time.</summary>
		/// <returns>The local time.</returns>
		DateTime			ToUtcTime();
		/// <summary>Move forward.</summary>
		/// <returns>The moved time.</returns>
		/// <param name="milliseconds">The delta in milliseconds.</param>
		DateTime			Forward(vuint64_t milliseconds);
		/// <summary>Move Backward.</summary>
		/// <returns>The moved time.</returns>
		/// <param name="milliseconds">The delta in milliseconds.</param>
		DateTime			Backward(vuint64_t milliseconds);
		
		bool operator==(const DateTime& value)const
		{
			return filetime == value.filetime;
		}
		bool operator!=(const DateTime& value)const
		{
			return filetime != value.filetime;
		}
		bool operator<(const DateTime& value)const
		{
			return filetime < value.filetime;
		}
		bool operator<=(const DateTime& value)const
		{
			return filetime <= value.filetime;
		}
		bool operator>(const DateTime& value)const
		{
			return filetime > value.filetime;
		}
		bool operator>=(const DateTime& value)const
		{
			return filetime >= value.filetime;
		}
	};
	
	/***********************************************************************
	接口
	***********************************************************************/
	
	/// <summary>Base type of all interfaces. All interface types are encouraged to be virtual inherited.</summary>
	class Interface : private NotCopyable
	{
	 public:
		virtual ~Interface();
	};
	
	/***********************************************************************
	类型萃取
	***********************************************************************/
	
	struct YesType {};
	struct NoType {};
	
	template<typename T, typename YesOrNo>
	struct AcceptType
	{
	};
	
	template<typename T>
	struct AcceptType<T, YesType>
	{
		typedef T Type;
	};
	
	template<typename YesOrNo>
	struct AcceptValue
	{
		static const bool Result = false;
	};
	
	template<>
	struct AcceptValue<YesType>
	{
		static const bool Result = true;
	};
	// 	template<typename TFrom, typename TTo>
	// 	struct RequiresConvertable
	// 	{
	// 		static YesType Test(TTo* value);
	// 		static NoType Test(void* value);
	//
	// 		typedef decltype(Test((TFrom*)0)) YesNoType;
	// 	};
	template<typename T, typename U>
	struct AcceptAlways
	{
		typedef T Type;
	};
}

#endif


/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Data Structure::Smart Pointer

Classes:
Ptr<T>							：智能指针
***********************************************************************/

#ifndef VCZH_POINTER
#define VCZH_POINTER


namespace vl
{

	/***********************************************************************
	ReferenceCounterOperator
	***********************************************************************/
	
	/// <summary>The strategy to get the pointer to the reference counter from an object. If you get the same pointer multiple times from the same object by calling [M:vl.ReferenceCounterOperator`2.CreateCounter], than it is safe to convert a object pointer to a [T:vl.Ptr`1]. Currently for reflectable C++ types which inherit from [T:vl.reflection.DescriptableObject] it is yet. For others it is no.</summary>
	/// <typeparam name="T">The type of the object.</typeparam>
	/// <typeparam name="Enabled">[T:vl.Ptr`1] will always use [T:vl.YesType] as the second type parameter. This parameter is useful when you want to do partial specialization in the SFINAE way.</typeparam>
	template<typename T, typename Enabled = YesType>
	struct ReferenceCounterOperator
	{
		/// <summary>Create a pointer to the reference counter from an object.</summary>
		/// <returns>The pointer to the reference counter.</returns>
		/// <param name="reference">The object.</param>
		static __forceinline volatile vint* CreateCounter(T* reference)
		{
			return new vint(0);
		}
		
		/// <summary>Destroy a pointer to the reference counter from an object.</summary>
		/// <param name="counter">The pointer to the reference counter.</param>
		/// <param name="reference">The object.</param>
		static __forceinline void DeleteReference(volatile vint* counter, void* reference)
		{
			delete counter;
			delete (T*)reference;
		}
	};
	
	/***********************************************************************
	Ptr
	***********************************************************************/
	
	/// <summary>A smart pointer. It is always safe to convert a pointer to an object to a smart pointer once. If you do it multiple times, it may be wrong due to different implementation of [T:vl.ReferenceCounterOperator`2]. In case of wrong, disposing the smart pointer will cause an access violation.</summary>
	/// <typeparam name="T">The type of the object.</typeparam>
	template<typename T>
	class Ptr
	{
		template<typename X>
		friend class Ptr;
	 protected:
		typedef void(*Destructor)(volatile vint*, void*);
		
		volatile vint*		counter;
		T*					reference;
		void*				originalReference;
		Destructor			originalDestructor;
		
		void Inc()
		{
			if (counter)
			{
				INCRC(counter);
			}
		}
		
		void Dec(bool deleteIfZero = true)
		{
			if (counter)
			{
				if (DECRC(counter) == 0)
				{
					if (deleteIfZero)
					{
						originalDestructor(counter, originalReference);
					}
					
					counter = NULL;
					reference = NULL;
					originalReference = NULL;
					originalDestructor = NULL;
				}
			}
		}
		
		volatile vint* Counter()const
		{
			return counter;
		}
		
		Ptr(volatile vint* _counter, T* _reference, void* _originalReference, Destructor _originalDestructor)
			: counter(_counter)
			, reference(_reference)
			, originalReference(_originalReference)
			, originalDestructor(_originalDestructor)
		{
			Inc();
		}
	 public:
	 
		/// <summary>Create a null pointer.</summary>
		Ptr()
			: counter(0)
			, reference(0)
			, originalReference(0)
			, originalDestructor(0)
		{
		}
		
		/// <summary>Convert a pointer to an object to a smart pointer.</summary>
		/// <param name="pointer">The pointer to the object.</param>
		Ptr(T* pointer)
			: counter(0)
			, reference(0)
			, originalReference(0)
			, originalDestructor(0)
		{
			if (pointer)
			{
				counter = ReferenceCounterOperator<T>::CreateCounter(pointer);
				reference = pointer;
				originalReference = pointer;
				originalDestructor = &ReferenceCounterOperator<T>::DeleteReference;
				Inc();
			}
		}
		
		/// <summary>Copy a smart pointer.</summary>
		/// <param name="pointer">The smart pointer to copy.</param>
		Ptr(const Ptr<T>& pointer)
			: counter(pointer.counter)
			, reference(pointer.reference)
			, originalReference(pointer.originalReference)
			, originalDestructor(pointer.originalDestructor)
		{
			Inc();
		}
		
		/// <summary>Move a smart pointer.</summary>
		/// <param name="pointer">The smart pointer to Move.</param>
		// 		Ptr(Ptr<T>&& pointer)
		// 			:counter(pointer.counter)
		// 			,reference(pointer.reference)
		// 			,originalReference(pointer.originalReference)
		// 			,originalDestructor(pointer.originalDestructor)
		// 		{
		// 			pointer.counter=0;
		// 			pointer.reference=0;
		// 			pointer.originalReference=0;
		// 			pointer.originalDestructor=0;
		// 		}
		
		/// <summary>Cast a smart pointer.</summary>
		/// <typeparam name="C">The type of the object before casting.</typeparam>
		/// <param name="pointer">The smart pointer to cast.</param>
		template<typename C>
		Ptr(const Ptr<C>& pointer)
			: counter(0)
			, reference(0)
			, originalReference(0)
			, originalDestructor(0)
		{
			T* converted = pointer.Obj();
			
			if (converted)
			{
				counter = pointer.Counter();
				reference = converted;
				originalReference = pointer.originalReference;
				originalDestructor = pointer.originalDestructor;
				Inc();
			}
		}
		
		~Ptr()
		{
			Dec();
		}
		
		/// <summary>Detach the contained object from this smart pointer.</summary>
		/// <returns>The detached object. Returns null if this smart pointer is empty.</returns>
		T* Detach()
		{
			T* detached = reference;
			Dec(false);
			return detached;
		}
		
		/// <summary>Cast a smart pointer.</summary>
		/// <typeparam name="C">The type of the object after casting.</typeparam>
		/// <returns>The casted smart pointer. Returns null if failed.</returns>
		template<typename C>
		Ptr<C> Cast()const
		{
			C* converted = dynamic_cast<C*>(reference);
			return Ptr<C>((converted ? counter : 0), converted, originalReference, originalDestructor);
		}
		
		/// <summary>Convert a pointer to an object to a smart pointer.</summary>
		/// <returns>The converted smart pointer.</returns>
		/// <param name="pointer">The pointer to the object.</param>
		Ptr<T>& operator=(T* pointer)
		{
			Dec();
			
			if (pointer)
			{
				counter = ReferenceCounterOperator<T>::CreateCounter(pointer);
				reference = pointer;
				originalReference = pointer;
				originalDestructor = &ReferenceCounterOperator<T>::DeleteReference;
				Inc();
			}
			else
			{
				counter = 0;
				reference = 0;
				originalReference = 0;
				originalDestructor = 0;
			}
			
			return *this;
		}
		
		/// <summary>Copy a smart pointer.</summary>
		/// <returns>The copied smart pointer.</returns>
		/// <param name="pointer">The smart pointer to copy.</param>
		Ptr<T>& operator=(const Ptr<T>& pointer)
		{
			if (this != &pointer)
			{
				Dec();
				counter = pointer.counter;
				reference = pointer.reference;
				originalReference = pointer.originalReference;
				originalDestructor = pointer.originalDestructor;
				Inc();
			}
			
			return *this;
		}
		
		/// <summary>Move a smart pointer.</summary>
		/// <returns>The moved smart pointer.</returns>
		/// <param name="pointer">The smart pointer to Move.</param>
		/*Ptr<T>& operator=(Ptr<T>&& pointer)
		{
		if (this != &pointer)
		{
		Dec();
		counter = pointer.counter;
		reference = pointer.reference;
		originalReference = pointer.originalReference;
		originalDestructor = pointer.originalDestructor;
		
		pointer.counter = 0;
		pointer.reference = 0;
		pointer.originalReference = 0;
		pointer.originalDestructor = 0;
		}
		
		return *this;
		}*/
		
		/// <summary>Cast a smart pointer.</summary>
		/// <typeparam name="C">The type of the object before casting.</typeparam>
		/// <returns>The smart pointer after casting.</returns>
		/// <param name="pointer">The smart pointer to cast.</param>
		template<typename C>
		Ptr<T>& operator=(const Ptr<C>& pointer)
		{
			T* converted = pointer.Obj();
			Dec();
			
			if (converted)
			{
				counter = pointer.counter;
				reference = converted;
				originalReference = pointer.originalReference;
				originalDestructor = pointer.originalDestructor;
				Inc();
			}
			else
			{
				counter = 0;
				reference = 0;
				originalReference = 0;
				originalDestructor = 0;
			}
			
			return *this;
		}
		
		bool operator==(const T* pointer)const
		{
			return reference == pointer;
		}
		
		bool operator!=(const T* pointer)const
		{
			return reference != pointer;
		}
		
		bool operator>(const T* pointer)const
		{
			return reference > pointer;
		}
		
		bool operator>=(const T* pointer)const
		{
			return reference >= pointer;
		}
		
		bool operator<(const T* pointer)const
		{
			return reference < pointer;
		}
		
		bool operator<=(const T* pointer)const
		{
			return reference <= pointer;
		}
		
		bool operator==(const Ptr<T>& pointer)const
		{
			return reference == pointer.reference;
		}
		
		bool operator!=(const Ptr<T>& pointer)const
		{
			return reference != pointer.reference;
		}
		
		bool operator>(const Ptr<T>& pointer)const
		{
			return reference > pointer.reference;
		}
		
		bool operator>=(const Ptr<T>& pointer)const
		{
			return reference >= pointer.reference;
		}
		
		bool operator<(const Ptr<T>& pointer)const
		{
			return reference < pointer.reference;
		}
		
		bool operator<=(const Ptr<T>& pointer)const
		{
			return reference <= pointer.reference;
		}
		
		/// <summary>Test if it is a null pointer.</summary>
		/// <returns>Returns true if it is not null.</returns>
		operator bool()const
		{
			return reference != 0;
		}
		
		/// <summary>Get the pointer to the object.</summary>
		/// <returns>The pointer to the object.</returns>
		T* Obj()const
		{
			return reference;
		}
		
		/// <summary>Get the pointer to the object.</summary>
		/// <returns>The pointer to the object.</returns>
		T* operator->()const
		{
			return reference;
		}
	};
	
	/***********************************************************************
	ComPtr
	***********************************************************************/
	
	template<typename T>
	class ComPtr
	{
	 protected:
		volatile vint*		counter;
		T*					reference;
		
		void Inc()
		{
			if (counter)
			{
				INCRC(counter);
			}
		}
		
		void Dec()
		{
			if (counter)
			{
				if (DECRC(counter) == 0)
				{
					delete counter;
					reference->Release();
					counter = 0;
					reference = 0;
				}
			}
		}
		
		volatile vint* Counter()const
		{
			return counter;
		}
		
		ComPtr(volatile vint* _counter, T* _reference)
			: counter(_counter)
			, reference(_reference)
		{
			Inc();
		}
	 public:
	 
		ComPtr()
		{
			counter = 0;
			reference = 0;
		}
		
		ComPtr(T* pointer)
		{
			if (pointer)
			{
				counter = new volatile vint(1);
				reference = pointer;
			}
			else
			{
				counter = 0;
				reference = 0;
			}
		}
		
		ComPtr(const ComPtr<T>& pointer)
		{
			counter = pointer.counter;
			reference = pointer.reference;
			Inc();
		}
		
		/*ComPtr(ComPtr<T>&& pointer)
		{
		counter = pointer.counter;
		reference = pointer.reference;
		
		pointer.counter = 0;
		pointer.reference = 0;
		}*/
		
		~ComPtr()
		{
			Dec();
		}
		
		ComPtr<T>& operator=(T* pointer)
		{
			Dec();
			
			if (pointer)
			{
				counter = new vint(1);
				reference = pointer;
			}
			else
			{
				counter = 0;
				reference = 0;
			}
			
			return *this;
		}
		
		ComPtr<T>& operator=(const ComPtr<T>& pointer)
		{
			if (this != &pointer)
			{
				Dec();
				counter = pointer.counter;
				reference = pointer.reference;
				Inc();
			}
			
			return *this;
		}
		
		/*ComPtr<T>& operator=(ComPtr<T>&& pointer)
		{
		if (this != &pointer)
		{
		Dec();
		counter = pointer.counter;
		reference = pointer.reference;
		
		pointer.counter = 0;
		pointer.reference = 0;
		}
		
		return *this;
		}*/
		
		bool operator==(const T* pointer)const
		{
			return reference == pointer;
		}
		
		bool operator!=(const T* pointer)const
		{
			return reference != pointer;
		}
		
		bool operator>(const T* pointer)const
		{
			return reference > pointer;
		}
		
		bool operator>=(const T* pointer)const
		{
			return reference >= pointer;
		}
		
		bool operator<(const T* pointer)const
		{
			return reference < pointer;
		}
		
		bool operator<=(const T* pointer)const
		{
			return reference <= pointer;
		}
		
		bool operator==(const ComPtr<T>& pointer)const
		{
			return reference == pointer.reference;
		}
		
		bool operator!=(const ComPtr<T>& pointer)const
		{
			return reference != pointer.reference;
		}
		
		bool operator>(const ComPtr<T>& pointer)const
		{
			return reference > pointer.reference;
		}
		
		bool operator>=(const ComPtr<T>& pointer)const
		{
			return reference >= pointer.reference;
		}
		
		bool operator<(const ComPtr<T>& pointer)const
		{
			return reference < pointer.reference;
		}
		
		bool operator<=(const ComPtr<T>& pointer)const
		{
			return reference <= pointer.reference;
		}
		
		operator bool()const
		{
			return reference != 0;
		}
		
		T* Obj()const
		{
			return reference;
		}
		
		T* operator->()const
		{
			return reference;
		}
	};
	
	
	/***********************************************************************
	Traits
	***********************************************************************/
	
	template<typename T>
	struct KeyType<Ptr<T>>
	{
		typedef T* Type;
		
		static T* GetKeyValue(const Ptr<T>& key)
		{
			return key.Obj();
		}
	};
	
	template<typename T>
	struct POD<Ptr<T>>
	{
		static const bool Result = false;
	};
	
	template<typename T>
	struct KeyType<ComPtr<T>>
	{
		typedef T* Type;
		
		static T* GetKeyValue(const ComPtr<T>& key)
		{
			return key.Obj();
		}
	};
	
	template<typename T>
	struct POD<ComPtr<T>>
	{
		static const bool Result = false;
	};
}

#endif



/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Data Structure::String

Classes:
AString										：Mbcs字符串
WString										：Utf-16字符串
***********************************************************************/

#ifndef VCZH_STRING
#define VCZH_STRING

#include <memory.h>

namespace vl
{
	/// <summary>A type representing a string.</summary>
	/// <typeparam name="T">Type of a character.</typeparam>
	template<typename T>
	class ObjectString : public Object
	{
	 private:
		static const T				zero;
		
		mutable T*					buffer;
		mutable volatile vint*		counter;
		mutable vint				start;
		mutable vint				length;
		mutable vint				realLength;
		
		static vint CalculateLength(const T* buffer)
		{
			vint result = 0;
			
			while (*buffer++)
			{
				result++;
			}
			
			return result;
		}
		
		static vint Compare(const T* bufA, const ObjectString<T>& strB)
		{
			const T* bufB = strB.buffer + strB.start;
			const T* bufAOld = bufA;
			vint length = strB.length;
			
			while (length-- && *bufA)
			{
				vint diff = *bufA++ - *bufB++;
				
				if (diff != 0)
				{
					return diff;
				}
			};
			
			return CalculateLength(bufAOld) - strB.length;
		}
		
	 public:
	 
		static vint Compare(const ObjectString<T>& strA, const ObjectString<T>& strB)
		{
			const T* bufA = strA.buffer + strA.start;
			const T* bufB = strB.buffer + strB.start;
			vint length = strA.length < strB.length ? strA.length : strB.length;
			
			while (length--)
			{
				vint diff = *bufA++ - *bufB++;
				
				if (diff != 0)
				{
					return diff;
				}
			};
			
			return strA.length - strB.length;
		}
		
	 private:
	 
		void Inc()const
		{
			if (counter)
			{
				INCRC(counter);
			}
		}
		
		void Dec()const
		{
			if (counter)
			{
				if (DECRC(counter) == 0)
				{
					delete[] buffer;
					delete counter;
				}
			}
		}
		
		ObjectString(const ObjectString<T>& string, vint _start, vint _length)
		{
			if (_length <= 0)
			{
				buffer = (T*)&zero;
				counter = 0;
				start = 0;
				length = 0;
				realLength = 0;
			}
			else
			{
				buffer = string.buffer;
				counter = string.counter;
				start = string.start + _start;
				length = _length;
				realLength = string.realLength;
				Inc();
			}
		}
		
		ObjectString(const ObjectString<T>& dest, const ObjectString<T>& source, vint index, vint count)
		{
			if (index == 0 && count == dest.length && source.length == 0)
			{
				buffer = (T*)&zero;
				counter = 0;
				start = 0;
				length = 0;
				realLength = 0;
			}
			else
			{
				counter = new vint(1);
				start = 0;
				length = dest.length - count + source.length;
				realLength = length;
				buffer = new T[length + 1];
				memcpy(buffer, dest.buffer + dest.start, sizeof(T)*index);
				memcpy(buffer + index, source.buffer + source.start, sizeof(T)*source.length);
				memcpy(buffer + index + source.length, (dest.buffer + dest.start + index + count), sizeof(T) * (dest.length - index - count));
				buffer[length] = 0;
			}
		}
	 public:
		static ObjectString<T>	Empty;
		
		/// <summary>Create an empty string.</summary>
		ObjectString()
		{
			buffer = (T*)&zero;
			counter = 0;
			start = 0;
			length = 0;
			realLength = 0;
		}
		
		/// <summary>Create a string continaing one character.</summary>
		/// <param name="_char">The character.</param>
		ObjectString(const T& _char)
		{
			counter = new vint(1);
			start = 0;
			length = 1;
			buffer = new T[2];
			buffer[0] = _char;
			buffer[1] = 0;
			realLength = length;
		}
		
		/// <summary>Copy a string.</summary>
		/// <param name="_buffer">Memory to copy. It does not have to contain the zero terminator.</param>
		/// <param name="_length">Size of the content in characters.</param>
		ObjectString(const T* _buffer, vint _length)
		{
			if (_length <= 0)
			{
				buffer = (T*)&zero;
				counter = 0;
				start = 0;
				length = 0;
				realLength = 0;
			}
			else
			{
				buffer = new T[_length + 1];
				memcpy(buffer, _buffer, _length * sizeof(T));
				buffer[_length] = 0;
				counter = new vint(1);
				start = 0;
				length = _length;
				realLength = _length;
			}
		}
		
		/// <summary>Copy a string.</summary>
		/// <param name="_buffer">Memory to copy. It should have to contain the zero terminator.</param>
		/// <param name="copy">Set to true to copy the memory. Set to false to use the memory directly.</param>
		ObjectString(const T* _buffer, bool copy = true)
		{
			CHECK_ERROR(_buffer != 0, L"ObjectString<T>::ObjectString(const T*, bool)#Cannot construct a string from NULL.");
			
			if (copy)
			{
				counter = new vint(1);
				start = 0;
				length = CalculateLength(_buffer);
				buffer = new T[length + 1];
				memcpy(buffer, _buffer, sizeof(T) * (length + 1));
				realLength = length;
			}
			else
			{
				buffer = (T*)_buffer;
				counter = 0;
				start = 0;
				length = CalculateLength(_buffer);
				realLength = length;
			}
		}
		
		/// <summary>Copy a string.</summary>
		/// <param name="string">The string to copy.</param>
		ObjectString(const ObjectString<T>& string)
		{
			buffer = string.buffer;
			counter = string.counter;
			start = string.start;
			length = string.length;
			realLength = string.realLength;
			Inc();
		}
		
		
		
		~ObjectString()
		{
			Dec();
		}
		
		/// <summary>Get the zero-terminated buffer in the string. Copying parts of a string does not necessarily create a new buffer, so in some situation the string will not actually points to a zero-terminated buffer. In this case, this function will copy the content to a new buffer with a zero terminator and return.</summary>
		/// <returns>Returns the buffer.</returns>
		const T* Buffer()const
		{
			if (start + length != realLength)
			{
				T* newBuffer = new T[length + 1];
				memcpy(newBuffer, buffer + start, sizeof(T)*length);
				newBuffer[length] = 0;
				Dec();
				buffer = newBuffer;
				counter = new vint(1);
				start = 0;
				realLength = length;
			}
			
			return buffer + start;
		}
		
		ObjectString<T>& operator=(const ObjectString<T>& string)
		{
			if (this != &string)
			{
				Dec();
				buffer = string.buffer;
				counter = string.counter;
				start = string.start;
				length = string.length;
				realLength = string.realLength;
				Inc();
			}
			
			return *this;
		}
		
		
		
		ObjectString<T>& operator+=(const ObjectString<T>& string)
		{
			return *this = *this + string;
		}
		
		ObjectString<T> operator+(const ObjectString<T>& string)const
		{
			return ObjectString<T>(*this, string, length, 0);
		}
		
		bool operator==(const ObjectString<T>& string)const
		{
			return Compare(*this, string) == 0;
		}
		
		bool operator!=(const ObjectString<T>& string)const
		{
			return Compare(*this, string) != 0;
		}
		
		bool operator>(const ObjectString<T>& string)const
		{
			return Compare(*this, string) > 0;
		}
		
		bool operator>=(const ObjectString<T>& string)const
		{
			return Compare(*this, string) >= 0;
		}
		
		bool operator<(const ObjectString<T>& string)const
		{
			return Compare(*this, string) < 0;
		}
		
		bool operator<=(const ObjectString<T>& string)const
		{
			return Compare(*this, string) <= 0;
		}
		
		bool operator==(const T* buffer)const
		{
			return Compare(buffer, *this) == 0;
		}
		
		bool operator!=(const T* buffer)const
		{
			return Compare(buffer, *this) != 0;
		}
		
		bool operator>(const T* buffer)const
		{
			return Compare(buffer, *this) < 0;
		}
		
		bool operator>=(const T* buffer)const
		{
			return Compare(buffer, *this) <= 0;
		}
		
		bool operator<(const T* buffer)const
		{
			return Compare(buffer, *this) > 0;
		}
		
		bool operator<=(const T* buffer)const
		{
			return Compare(buffer, *this) >= 0;
		}
		
		T operator[](vint index)const
		{
			CHECK_ERROR(index >= 0 && index < length, L"ObjectString:<T>:operator[](vint)#Argument index not in range.");
			return buffer[start + index];
		}
		
		/// <summary>Get the size of the string in characters.</summary>
		/// <returns>The size.</returns>
		vint Length()const
		{
			return length;
		}
		
		/// <summary>Find a character.</summary>
		/// <returns>The position of the character. Returns -1 if it doesn not exist.</returns>
		/// <param name="c">The character to find.</param>
		vint IndexOf(T c)const
		{
			const T* reading = buffer + start;
			
			for (vint i = 0; i < length; i++)
			{
				if (reading[i] == c)
				{
					return i;
				}
			}
			
			return -1;
		}
		
		ObjectString<T>Mid(vint index, vint  count = -1)const
		{
			if (count < 0)
			{
				count = length - index;
			}
			
			return Sub(index, count);
		}
		
		vint IndexOf(T c, vint startIndex)const
		{
			const T* reading = buffer + start;
			
			for (vint i = startIndex; i < length; i++)
			{
				if (reading[i] == c)
				{
					return i;
				}
			}
			
			return -1;
		}
		
		ObjectString<T> Trim(T c)const
		{
			return TrimLeft(c).TrimRight(c);
		};
		
		ObjectString<T> TrimLeft(T c)const
		{
			vint nstart = start;		//起始位置
			vint nend = start + length;	//结束符位置（理论）
			vint nlen = length;			//实际长度
			
			while (buffer[nstart] == c && nstart < nend)
			{
				nstart++;
				nlen--;
			}
			
			return ObjectString<T>(*this, nstart - start, nlen);
		};
		ObjectString<T>TrimLeft(const T* buf)const
		{
			vint nbuflen = CalculateLength(buf);
			vint nfirst = start;
			vint nlen = length;
			vint nend = start + length;
			vint nflag;
			
			while (nfirst < nend)
			{
				nflag = -1;
				
				for (vint i = 0; i < nbuflen; i++)
				{
					if (buffer[nfirst] == buf[i])
					{
						nflag = 0;
						nfirst++;
						nlen--;
					}
				}
				
				if (nflag != 0)
				{
					break;
				}
			}
			
			return ObjectString<T>(*this, nfirst - start, nlen);
		}
		
		ObjectString<T> TrimRight(T c)const
		{
			vint nlast = start + length - 1;
			vint nlen = length;
			
			while (nlen && buffer[nlast] == c)
			{
				nlen--;
				nlast--;
			}
			
			return ObjectString<T>(*this, 0, nlen);
		};
		
		ObjectString<T>TrimRight(const T* buf)const
		{
			vint nlast = start + length - 1;
			vint nlen = length;
			vint nbuflen = CalculateLength(buf);
			vint nflag;
			
			while (nlen)
			{
				nflag = -1;
				
				for (vint i = 0; i < nbuflen; i++)
				{
					if (buffer[nlast] == buf[i])
					{
						nflag = 0;
						nlen--;
						nlast--;
					}
				}
				
				if (nflag != 0)
				{
					break;
				}
			}
			
			return ObjectString<T>(*this, 0, nlen);
		}
		
		/// <summary>Copy the beginning of the string.</summary>
		/// <returns>The copied string.</returns>
		/// <param name="count">Size of characters to copy.</param>
		ObjectString<T> Left(vint count)const
		{
			CHECK_ERROR(count >= 0 && count <= length, L"ObjectString<T>::Left(vint)#Argument count not in range.");
			return ObjectString<T>(*this, 0, count);
		}
		
		/// <summary>Copy the ending of the string.</summary>
		/// <returns>The copied string.</returns>
		/// <param name="count">Size of characters to copy.</param>
		ObjectString<T> Right(vint count)const
		{
			CHECK_ERROR(count >= 0 && count <= length, L"ObjectString<T>::Right(vint)#Argument count not in range.");
			return ObjectString<T>(*this, length - count, count);
		}
		
		/// <summary>Copy the middle of the string.</summary>
		/// <returns>The copied string.</returns>
		/// <param name="index">Position of characters to copy.</param>
		/// <param name="count">Size of characters to copy.</param>
		ObjectString<T> Sub(vint index, vint count)const
		{
			CHECK_ERROR(index >= 0 && index <= length, L"ObjectString<T>::Sub(vint, vint)#Argument index not in range.");
			CHECK_ERROR(index + count >= 0 && index + count <= length, L"ObjectString<T>::Sub(vint, vint)#Argument count not in range.");
			return ObjectString<T>(*this, index, count);
		}
		
		/// <summary>Copy the beginning and the end of the string.</summary>
		/// <returns>The copied string.</returns>
		/// <param name="index">Position of characters NOT to copy.</param>
		/// <param name="count">Size of characters NOT to copy.</param>
		ObjectString<T> Remove(vint index, vint count)const
		{
			CHECK_ERROR(index >= 0 && index < length, L"ObjectString<T>::Remove(vint, vint)#Argument index not in range.");
			CHECK_ERROR(index + count >= 0 && index + count <= length, L"ObjectString<T>::Remove(vint, vint)#Argument count not in range.");
			return ObjectString<T>(*this, ObjectString<T>(), index, count);
		}
		
		/// <summary>Make a new string by inserting a string in this string.</summary>
		/// <returns>The copied string.</returns>
		/// <param name="index">Position of characters to insert.</param>
		/// <param name="string">The string to be inserted in this string.</param>
		ObjectString<T> Insert(vint index, const ObjectString<T>& string)const
		{
			CHECK_ERROR(index >= 0 && index <= length, L"ObjectString<T>::Insert(vint)#Argument count not in range.");
			return ObjectString<T>(*this, string, index, 0);
		}
		
		friend bool operator<(const T* left, const ObjectString<T>& right)
		{
			return Compare(left, right) < 0;
		}
		
		friend bool operator<=(const T* left, const ObjectString<T>& right)
		{
			return Compare(left, right) <= 0;
		}
		
		friend bool operator>(const T* left, const ObjectString<T>& right)
		{
			return Compare(left, right) > 0;
		}
		
		friend bool operator>=(const T* left, const ObjectString<T>& right)
		{
			return Compare(left, right) >= 0;
		}
		
		friend bool operator==(const T* left, const ObjectString<T>& right)
		{
			return Compare(left, right) == 0;
		}
		
		friend bool operator!=(const T* left, const ObjectString<T>& right)
		{
			return Compare(left, right) != 0;
		}
		
		friend ObjectString<T> operator+(const T* left, const ObjectString<T>& right)
		{
			return ObjectString<T>(left, false) + right;
		}
	};
	
	template<typename T>
	ObjectString<T> ObjectString<T>::Empty = ObjectString<T>();
	template<typename T>
	const T ObjectString<T>::zero = 0;
	
	/// <summary>Ansi string.</summary>
	typedef ObjectString<char>		AString;
	/// <summary>Unicode string.</summary>
	typedef ObjectString<wchar_t>	WString;
	
	/// <summary>Convert a string to an signed integer.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	/// <param name="success">Returns true if this operation succeeded.</param>
	extern vint					atoi_test(const AString& string, bool& success);
	/// <summary>Convert a string to an signed integer.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	/// <param name="success">Returns true if this operation succeeded.</param>
	extern vint					wtoi_test(const WString& string, bool& success);
	/// <summary>Convert a string to an signed 64-bits integer.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	/// <param name="success">Returns true if this operation succeeded.</param>
	extern vint64_t				atoi64_test(const AString& string, bool& success);
	/// <summary>Convert a string to an signed 64-bits integer.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	/// <param name="success">Returns true if this operation succeeded.</param>
	extern vint64_t				wtoi64_test(const WString& string, bool& success);
	/// <summary>Convert a string to an unsigned integer.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	/// <param name="success">Returns true if this operation succeeded.</param>
	extern vuint				atou_test(const AString& string, bool& success);
	/// <summary>Convert a string to an unsigned integer.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	/// <param name="success">Returns true if this operation succeeded.</param>
	extern vuint				wtou_test(const WString& string, bool& success);
	/// <summary>Convert a string to a 64-bits unsigned integer.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	/// <param name="success">Returns true if this operation succeeded.</param>
	extern vuint64_t			atou64_test(const AString& string, bool& success);
	/// <summary>Convert a string to a 64-bits unsigned integer.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	/// <param name="success">Returns true if this operation succeeded.</param>
	extern vuint64_t			wtou64_test(const WString& string, bool& success);
	/// <summary>Convert a string to 64-bits floating point number.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	/// <param name="success">Returns true if this operation succeeded.</param>
	extern double				atof_test(const AString& string, bool& success);
	/// <summary>Convert a string to 64-bits floating point number.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	/// <param name="success">Returns true if this operation succeeded.</param>
	extern double				wtof_test(const WString& string, bool& success);
	
	/// <summary>Convert a string to an signed integer.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	extern vint					atoi(const AString& string);
	/// <summary>Convert a string to an signed integer.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	extern vint					wtoi(const WString& string);
	/// <summary>Convert a string to an signed 64-bits integer.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	extern vint64_t				atoi64(const AString& string);
	/// <summary>Convert a string to an signed 64-bits integer.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	extern vint64_t				wtoi64(const WString& string);
	/// <summary>Convert a string to an unsigned integer.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	extern vuint				atou(const AString& string);
	/// <summary>Convert a string to an unsigned integer.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	extern vuint				wtou(const WString& string);
	/// <summary>Convert a string to a 64-bits unsigned integer.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	extern vuint64_t			atou64(const AString& string);
	/// <summary>Convert a string to a 64-bits unsigned integer.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	extern vuint64_t			wtou64(const WString& string);
	/// <summary>Convert a string to a 64-bits floating point number.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	extern double				atof(const AString& string);
	/// <summary>Convert a string to a 64-bits floating point number.</summary>
	/// <returns>The converted number. If the convert failed, the result is undefined.</returns>
	/// <param name="string">The string to convert.</param>
	extern double				wtof(const WString& string);
	
	/// <summary>Convert a signed interger to a string.</summary>
	/// <returns>The converted string.</returns>
	/// <param name="number">The number to convert.</param>
	extern AString				itoa(vint number);
	/// <summary>Convert a signed interger to a string.</summary>
	/// <returns>The converted string.</returns>
	/// <param name="number">The number to convert.</param>
	extern WString				itow(vint number);
	/// <summary>Convert a 64-bits signed interger to a string.</summary>
	/// <returns>The converted string.</returns>
	/// <param name="number">The number to convert.</param>
	extern AString				i64toa(vint64_t number);
	/// <summary>Convert a 64-bits signed interger to a string.</summary>
	/// <returns>The converted string.</returns>
	/// <param name="number">The number to convert.</param>
	extern WString				i64tow(vint64_t number);
	/// <summary>Convert an unsigned interger to a string.</summary>
	/// <returns>The converted string.</returns>
	/// <param name="number">The number to convert.</param>
	extern AString				utoa(vuint number);
	/// <summary>Convert an unsigned interger to a string.</summary>
	/// <returns>The converted string.</returns>
	/// <param name="number">The number to convert.</param>
	extern WString				utow(vuint number);
	/// <summary>Convert a 64-bits unsigned interger to a string.</summary>
	/// <returns>The converted string.</returns>
	/// <param name="number">The number to convert.</param>
	extern AString				u64toa(vuint64_t number);
	/// <summary>Convert a 64-bits unsigned interger to a string.</summary>
	/// <returns>The converted string.</returns>
	/// <param name="number">The number to convert.</param>
	extern WString				u64tow(vuint64_t number);
	/// <summary>Convert a 64-bits floating pointer number to a string.</summary>
	/// <returns>The converted string.</returns>
	/// <param name="number">The number to convert.</param>
	extern AString				ftoa(double number);
	/// <summary>Convert a 64-bits floating pointer number to a string.</summary>
	/// <returns>The converted string.</returns>
	/// <param name="number">The number to convert.</param>
	extern WString				ftow(double number);
	
	extern vint					_wtoa(const wchar_t* w, char* a, vint chars);
	/// <summary>Convert an Unicode string to an Ansi string.</summary>
	/// <returns>The converted string.</returns>
	/// <param name="string">The string to convert.</param>
	extern AString				wtoa(const WString& string);
	extern vint					_atow(const char* a, wchar_t* w, vint chars);
	/// <summary>Convert an Ansi string to an Unicode string.</summary>
	/// <returns>The converted string.</returns>
	/// <param name="string">The string to convert.</param>
	extern WString				atow(const AString& string);
	/// <summary>Convert all letters to lower case letters.</summary>
	/// <returns>The converted string.</returns>
	/// <param name="string">The string to convert.</param>
	extern AString				alower(const AString& string);
	/// <summary>Convert all letters to lower case letters.</summary>
	/// <returns>The converted string.</returns>
	/// <param name="string">The string to convert.</param>
	extern WString				wlower(const WString& string);
	/// <summary>Convert all letters to upper case letters.</summary>
	/// <returns>The converted string.</returns>
	/// <param name="string">The string to convert.</param>
	extern AString				aupper(const AString& string);
	/// <summary>Convert all letters to upper case letters.</summary>
	/// <returns>The converted string.</returns>
	/// <param name="string">The string to convert.</param>
	extern WString				wupper(const WString& string);
	
}

#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Data Structure::Pair

Classes:
Pair<K, V>							：二元组
***********************************************************************/

#ifndef VCZH_COLLECTIONS_PAIR
#define VCZH_COLLECTIONS_PAIR


namespace vl
{
	namespace collections
	{
		/// <summary>A type representing a pair of key and value.</summary>
		/// <typeparam name="K">Type of the key.</typeparam>
		/// <typeparam name="V">Type of the value.</typeparam>
		template<typename K, typename V>
		class Pair
		{
		 public:
			/// <summary>The key.</summary>
			K				key;
			/// <summary>The value.</summary>
			V				value;
			
			Pair()
			{
			}
			
			Pair(const K& _key, const V& _value)
			{
				key = _key;
				value = _value;
			}
			
			Pair(const Pair<K, V>& pair)
			{
				key = pair.key;
				value = pair.value;
			}
			
			vint CompareTo(const Pair<K, V>& pair)const
			{
				if (key < pair.key)
				{
					return -1;
				}
				else
					if (key > pair.key)
					{
						return 1;
					}
					else
						if (value < pair.value)
						{
							return -1;
						}
						else
							if (value > pair.value)
							{
								return 1;
							}
							else
							{
								return 0;
							}
			}
			
			bool operator==(const Pair<K, V>& pair)const
			{
				return CompareTo(pair) == 0;
			}
			
			bool operator!=(const Pair<K, V>& pair)const
			{
				return CompareTo(pair) != 0;
			}
			
			bool operator<(const Pair<K, V>& pair)const
			{
				return CompareTo(pair) < 0;
			}
			
			bool operator<=(const Pair<K, V>& pair)const
			{
				return CompareTo(pair) <= 0;
			}
			
			bool operator>(const Pair<K, V>& pair)const
			{
				return CompareTo(pair) > 0;
			}
			
			bool operator>=(const Pair<K, V>& pair)const
			{
				return CompareTo(pair) >= 0;
			}
		};
	}
	
	template<typename K, typename V>
	struct POD<collections::Pair<K, V>>
	{
		static const bool Result = POD<K>::Result && POD<V>::Result;
	};
}

#endif



/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Data Structure::Interfaces

Interfaces:
IEnumerator<T>									：枚举器
IEnumerable<T>									：可枚举对象
***********************************************************************/

#ifndef VCZH_COLLECTIONS_INTERFACES
#define VCZH_COLLECTIONS_INTERFACES



namespace vl
{
	namespace collections
	{
	
		/***********************************************************************
		接口
		***********************************************************************/
		
		/// <summary>Enumerator.</summary>
		/// <typeparam name="T">Type of the elements in the enumerator.</typeparam>
		template<typename T>
		class IEnumerator : public virtual Interface
		{
		 public:
			typedef T									ElementType;
			
			/// <summary>Copy the enumerator with the current state.</summary>
			/// <returns>The copied enumerator.</returns>
			virtual IEnumerator<T>*						Clone()const = 0;
			/// <summary>Get the reference to the current element in the enumerator.</summary>
			/// <returns>The reference to the current element.</returns>
			virtual const T&							Current()const = 0;
			/// <summary>Get the position of the current element in the enumerator.</summary>
			/// <returns>The position of the current element.</returns>
			virtual vint								Index()const = 0;
			/// <summary>Step forward.</summary>
			/// <returns>Returns false if the enumerator reaches the end.</returns>
			virtual bool								Next() = 0;
			/// <summary>Reset the enumerator.</summary>
			virtual void								Reset() = 0;
			
			virtual bool								Evaluated()const
			{
				return false;
			}
		};
		
		/// <summary>Enumerable.</summary>
		/// <typeparam name="T">Type of the elements in the enumerator.</typeparam>
		template<typename T>
		class IEnumerable : public virtual Interface
		{
		 public:
			typedef T									ElementType;
			
			/// <summary>Create an enumerator. [M:vl.collections.IEnumerator`1.Next] should be called to get the first element.</summary>
			/// <returns>The enumerator.</returns>
			virtual IEnumerator<T>*						CreateEnumerator()const = 0;
		};
		
		/***********************************************************************
		随机存取
		***********************************************************************/
		
		namespace randomaccess_internal
		{
			template<typename T>
			struct RandomAccessable
			{
				static const bool							CanRead = false;
				static const bool							CanResize = false;
			};
			
			template<typename T>
			struct RandomAccess
			{
				static vint GetCount(const T& t)
				{
					return t.Count();
				}
				
				static const typename T::ElementType& GetValue(const T& t, vint index)
				{
					return t.Get(index);
				}
				
				static void SetCount(T& t, vint count)
				{
					t.Resize(count);
				}
				
				static void SetValue(T& t, vint index, const typename T::ElementType& value)
				{
					t.Set(index, value);
				}
				
				static void AppendValue(T& t, const typename T::ElementType& value)
				{
					t.Add(value);
				}
			};
		}
	}
}

#endif


/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Data Structure::List

Classes:
ListStore<T,PODType>				：列表存储复制算法
ListBase<T,K>						：列表基类
Array<T,K>							：数组
List<T,K>							：列表
SortedList<T,K>						：有序列表
***********************************************************************/

#ifndef VCZH_COLLECTIONS_LIST
#define VCZH_COLLECTIONS_LIST

#include <string.h>

#ifdef VCZH_CHECK_MEMORY_LEAKS_NEW
#undef new
#endif

#include <new>

namespace vl
{
	namespace collections
	{
	
		/***********************************************************************
		Memory Management
		***********************************************************************/
		
		template<typename T, bool PODType>
		class ListStore abstract : public Object
		{
		};
		
		template<typename T>
		class ListStore<T, false> abstract : public Object
		{
		 protected:
			static void InitializeItemsByDefault(void* dst, vint count)
			{
				T* ds = (T*)dst;
				
				for (vint i = 0; i < count; i++)
				{
					new (&ds[i])T();
				}
			}
			
			static void InitializeItemsByMove(void* dst, void* src, vint count)
			{
				T* ds = (T*)dst;
				T* ss = (T*)src;
				
				for (vint i = 0; i < count; i++)
				{
					new (&ds[i])T(ss[i]);
				}
			}
			
			static void InitializeItemsByCopy(void* dst, void* src, vint count)
			{
				T* ds = (T*)dst;
				T* ss = (T*)src;
				
				for (vint i = 0; i < count; i++)
				{
					new (&ds[i])T(ss[i]);
				}
			}
			
			static void MoveItemsInTheSameBuffer(void* dst, void* src, vint count)
			{
				T* ds = (T*)dst;
				T* ss = (T*)src;
				
				if (ds < ss)
				{
					for (vint i = 0; i < count; i++)
					{
						// 							ds[i] = MoveValue(ss[i]);
						ds[i] = ss[i];
					}
				}
				else
					if (ds > ss)
					{
						for (vint i = count - 1; i >= 0; i--)
						{
							ds[i] = ss[i];
							// 								ds[i] = MoveValue(ss[i]);
						}
					}
			}
			
			static void ReleaseItems(void* dst, vint count)
			{
				T* ds = (T*)dst;
				
				for (vint i = 0; i < count; i++)
				{
					ds[i].~T();
				}
			}
			
			static void* AllocateBuffer(vint size)
			{
				if (size <= 0)
				{
					return NULL;
				}
				
				return (void*)malloc(sizeof(T) * size);
			}
			
			static void DeallocateBuffer(void* buffer)
			{
				if (buffer == NULL)
				{
					return;
				}
				
				free(buffer);
			}
		 public:
		};
		
		template<typename T>
		class ListStore<T, true> abstract : public Object
		{
		 protected:
			static void InitializeItemsByDefault(void* dst, vint count)
			{
			}
			
			static void InitializeItemsByMove(void* dst, void* src, vint count)
			{
				if (count > 0)
				{
					memcpy(dst, src, sizeof(T) * count);
				}
			}
			
			static void InitializeItemsByCopy(void* dst, void* src, vint count)
			{
				if (count > 0)
				{
					memcpy(dst, src, sizeof(T) * count);
				}
			}
			
			static void MoveItemsInTheSameBuffer(void* dst, void* src, vint count)
			{
				if (count > 0)
				{
					memmove(dst, src, sizeof(T) * count);
				}
			}
			
			static void ReleaseItems(void* dst, vint count)
			{
			}
			
			static void* AllocateBuffer(vint size)
			{
				if (size <= 0)
				{
					return NULL;
				}
				
				return (void*)malloc(sizeof(T) * size);
			}
			
			static void DeallocateBuffer(void* buffer)
			{
				if (buffer == NULL)
				{
					return;
				}
				
				free(buffer);
			}
		 public:
		};
		
		/***********************************************************************
		ArrayBase
		***********************************************************************/
		
		/// <summary>Base type of all linear container.</summary>
		/// <typeparam name="T">Type of elements.</typeparam>
		template<typename T>
		class ArrayBase abstract : public ListStore<T, POD<T>::Result>, public virtual IEnumerable<T>
		{
		 protected:
			class Enumerator : public Object, public virtual IEnumerator<T>
			{
			 private:
				const ArrayBase<T>*				container;
				vint							index;
				
			 public:
				Enumerator(const ArrayBase<T>* _container, vint _index = -1)
				{
					container = _container;
					index = _index;
				}
				
				IEnumerator<T>* Clone()const
				{
					return new Enumerator(container, index);
				}
				
				const T& Current()const
				{
					return container->Get(index);
				}
				
				vint Index()const
				{
					return index;
				}
				
				bool Next()
				{
					index++;
					return index >= 0 && index < container->Count();
				}
				
				void Reset()
				{
					index = -1;
				}
			};
			
			void*					buffer/* = NULL*/;
			vint					count/* = 0*/;
			
			static void* AddressOf(void* bufferOfTs, vint index)
			{
				return (void*)((char*)bufferOfTs + sizeof(T) * index);
			}
			
			const T& ItemOf(vint index)const
			{
				return *(const T*)AddressOf(buffer, index);
			}
			
			T& ItemOf(vint index)
			{
				return *(T*)AddressOf(buffer, index);
			}
		 public:
			ArrayBase() : buffer(NULL), count(0)
			{
			}
			
			IEnumerator<T>* CreateEnumerator()const
			{
				return new Enumerator(this);
			}
			
			/// <summary>Get the number of elements in the container.</summary>
			/// <returns>The number of elements.</returns>
			vint Count()const
			{
				return count;
			}
			
			/// <summary>Get the reference to the specified element.</summary>
			/// <returns>The reference to the specified element.</returns>
			/// <param name="index">The index of the element.</param>
			const T& Get(vint index)const
			{
				CHECK_ERROR(index >= 0 && index < this->count, L"ArrayBase<T, K>::Get(vint)#Argument index not in range.");
				return ItemOf(index);
			}
			
			/// <summary>Get the reference to the specified element.</summary>
			/// <returns>The reference to the specified element.</returns>
			/// <param name="index">The index of the element.</param>
			const T& operator[](vint index)const
			{
				CHECK_ERROR(index >= 0 && index < this->count, L"ArrayBase<T, K>::operator[](vint)#Argument index not in range.");
				return ItemOf(index);
			}
		};
		
		/***********************************************************************
		Array
		***********************************************************************/
		
		/// <summary>Array.</summary>
		/// <typeparam name="T">Type of elements.</typeparam>
		/// <typeparam name="K">Type of the key type of elements.</typeparam>
		template<typename T, typename K = typename KeyType<T>::Type>
		class Array : public ArrayBase<T>
		{
		 public:
			/// <summary>Create an array.</summary>
			/// <param name="size">The size of the array.</param>
			Array(vint size = 0)
			{
				this->buffer = this->AllocateBuffer(size);
				this->InitializeItemsByDefault(this->buffer, size);
				this->count = size;
			}
			
			/// <summary>Create an array.</summary>
			/// <param name="_buffer">Pointer to an array to copy.</param>
			/// <param name="size">The size of the array.</param>
			Array(const T* _buffer, vint size)
			{
				this->buffer = this->AllocateBuffer(size);
				this->InitializeItemsByCopy(this->buffer, (void*)_buffer, size);
				this->count = size;
			}
			
			~Array()
			{
				this->ReleaseItems(this->buffer, this->count);
				this->DeallocateBuffer(this->buffer);
			}
			
			/// <summary>Test does the array contain an item or not.</summary>
			/// <returns>Returns true if the array contains the specified item.</returns>
			/// <param name="item">The item to test.</param>
			bool Contains(const K& item)const
			{
				return IndexOf(item) != -1;
			}
			
			/// <summary>Get the position of an item in this array.</summary>
			/// <returns>Returns the position. Returns -1 if not exists</returns>
			/// <param name="item">The item to find.</param>
			vint IndexOf(const K& item)const
			{
				for (vint i = 0; i < this->count; i++)
				{
					if (this->ItemOf(i) == item)
					{
						return i;
					}
				}
				
				return -1;
			}
			
			/// <summary>Replace an item.</summary>
			/// <param name="index">The position of the item.</param>
			/// <param name="item">The new item to put into the array.</param>
			void Set(vint index, const T& item)
			{
				CHECK_ERROR(index >= 0 && index < this->count, L"Array<T, K>::Set(vint)#Argument index not in range.");
				this->ItemOf(index) = item;
			}
			
			/// <summary>Get the reference to the specified element.</summary>
			/// <returns>The reference to the specified element.</returns>
			/// <param name="index">The index of the element.</param>
			using ArrayBase<T>::operator[];
			T& operator[](vint index)
			{
				CHECK_ERROR(index >= 0 && index < this->count, L"Array<T, K>::operator[](vint)#Argument index not in range.");
				return this->ItemOf(index);
			}
			
			/// <summary>Change the size of the array.</summary>
			/// <param name="size">The new size of the array.</param>
			void Resize(vint size)
			{
				void* newBuffer = this->AllocateBuffer(size);
				
				if (size < this->count)
				{
					this->InitializeItemsByMove(this->AddressOf(newBuffer, 0), this->AddressOf(this->buffer, 0), size);
				}
				else
				{
					this->InitializeItemsByMove(this->AddressOf(newBuffer, 0), this->AddressOf(this->buffer, 0), this->count);
					this->InitializeItemsByDefault(this->AddressOf(newBuffer, this->count), size - this->count);
				}
				
				this->ReleaseItems(this->buffer, this->count);
				this->DeallocateBuffer(this->buffer);
				this->buffer = newBuffer;
				this->count = size;
			}
		};
		
		/***********************************************************************
		ListBase
		***********************************************************************/
		
		/// <summary>Base type for a list container.</summary>
		/// <typeparam name="T">Type of elements.</typeparam>
		/// <typeparam name="K">Type of the key type of elements.</typeparam>
		template<typename T, typename K = typename KeyType<T>::Type>
		class ListBase abstract : public ArrayBase<T>
		{
		 protected:
			vint					capacity /*= 0*/;
			bool					lessMemoryMode /*= false*/;
			
			vint CalculateCapacity(vint expected)
			{
				vint result = capacity;
				
				while (result < expected)
				{
					result = result * 5 / 4 + 1;
				}
				
				return result;
			}
			
			void MakeRoom(vint index, vint _count, bool& uninitialized)
			{
				vint newCount = this->count + _count;
				
				if (newCount > capacity)
				{
					vint newCapacity = CalculateCapacity(newCount);
					void* newBuffer = this->AllocateBuffer(newCapacity);
					this->InitializeItemsByMove(this->AddressOf(newBuffer, 0), this->AddressOf(this->buffer, 0), index);
					this->InitializeItemsByMove(this->AddressOf(newBuffer, index + _count), this->AddressOf(this->buffer, index), this->count - index);
					this->ReleaseItems(this->buffer, this->count);
					this->DeallocateBuffer(this->buffer);
					this->capacity = newCapacity;
					this->buffer = newBuffer;
					uninitialized = true;
				}
				else
					if (index >= this->count)
					{
						uninitialized = true;
					}
					else
						if (this->count - index < _count)
						{
							this->InitializeItemsByMove(this->AddressOf(this->buffer, index + _count), this->AddressOf(this->buffer, index), this->count - index);
							this->ReleaseItems(this->AddressOf(this->buffer, index), _count - (this->count - index));
							uninitialized = true;
						}
						else
						{
							this->InitializeItemsByMove(this->AddressOf(this->buffer, this->count), this->AddressOf(this->buffer, this->count - _count), _count);
							this->MoveItemsInTheSameBuffer(this->AddressOf(this->buffer, index + _count), this->AddressOf(this->buffer, index), this->count - index - _count);
							uninitialized = false;
						}
						
				this->count = newCount;
			}
			
			void ReleaseUnnecessaryBuffer(vint previousCount)
			{
				if (this->buffer && this->count < previousCount)
				{
					this->ReleaseItems(this->AddressOf(this->buffer, this->count), previousCount - this->count);
				}
				
				if (this->lessMemoryMode && this->count <= this->capacity / 2)
				{
					vint newCapacity = capacity * 5 / 8;
					
					if (this->count < newCapacity)
					{
						void* newBuffer = this->AllocateBuffer(newCapacity);
						this->InitializeItemsByMove(this->AddressOf(newBuffer, 0), this->AddressOf(this->buffer, 0), this->count);
						this->ReleaseItems(this->buffer, this->count);
						this->DeallocateBuffer(this->buffer);
						this->capacity = newCapacity;
						this->buffer = newBuffer;
					}
				}
			}
		 public:
			ListBase() : capacity(0), lessMemoryMode(false)
			{
			}
			
			~ListBase()
			{
				this->ReleaseItems(this->buffer, this->count);
				this->DeallocateBuffer(this->buffer);
			}
			
			/// <summary>Set a preference of using memory.</summary>
			/// <param name="mode">Set to true (by default) to let the container efficiently reduce memory usage when necessary.</param>
			void SetLessMemoryMode(bool mode)
			{
				this->lessMemoryMode = mode;
			}
			
			/// <summary>Remove an element.</summary>
			/// <returns>Returns true if the element is removed.</returns>
			/// <param name="index">The index of the element to remove.</param>
			bool RemoveAt(vint index)
			{
				vint previousCount = this->count;
				CHECK_ERROR(index >= 0 && index < this->count, L"ListBase<T, K>::RemoveAt(vint)#Argument index not in range.");
				this->MoveItemsInTheSameBuffer(this->AddressOf(this->buffer, index), this->AddressOf(this->buffer, index + 1), this->count - index - 1);
				this->count--;
				ReleaseUnnecessaryBuffer(previousCount);
				return true;
			}
			
			/// <summary>Remove elements.</summary>
			/// <returns>Returns true if the element is removed.</returns>
			/// <param name="index">The index of the first element to remove.</param>
			/// <param name="_count">The number of elements to remove.</param>
			bool RemoveRange(vint index, vint _count)
			{
				vint previousCount = this->count;
				CHECK_ERROR(index >= 0 && index <= this->count, L"ListBase<T, K>::RemoveRange(vint, vint)#Argument index not in range.");
				CHECK_ERROR(index + _count >= 0 && index + _count <= this->count, L"ListBase<T,K>::RemoveRange(vint, vint)#Argument _count not in range.");
				this->MoveItemsInTheSameBuffer(this->AddressOf(this->buffer, index), this->AddressOf(this->buffer, index + _count), this->count - index - _count);
				this->count -= _count;
				ReleaseUnnecessaryBuffer(previousCount);
				return true;
			}
			
			/// <summary>Remove all elements.</summary>
			/// <returns>Returns true if all elements are removed.</returns>
			bool Clear()
			{
				vint previousCount = this->count;
				this->count = 0;
				
				if (lessMemoryMode)
				{
					this->capacity = 0;
					this->ReleaseItems(this->buffer, this->count);
					this->DeallocateBuffer(this->buffer);
					this->buffer = NULL;
				}
				else
				{
					ReleaseUnnecessaryBuffer(previousCount);
				}
				
				return true;
			}
		};
		
		/***********************************************************************
		List
		***********************************************************************/
		
		/// <summary>List.</summary>
		/// <typeparam name="T">Type of elements.</typeparam>
		/// <typeparam name="K">Type of the key type of elements.</typeparam>
		template<typename T, typename K = typename KeyType<T>::Type>
		class List : public ListBase<T, K>
		{
		 public:
			/// <summary>Create a list.</summary>
			List()
			{
			}
			
			/// <summary>Test does the list contain an item or not.</summary>
			/// <returns>Returns true if the list contains the specified item.</returns>
			/// <param name="item">The item to test.</param>
			bool Contains(const K& item)const
			{
				return IndexOf(item) != -1;
			}
			
			/// <summary>Get the position of an item in this list.</summary>
			/// <returns>Returns the position. Returns -1 if not exists</returns>
			/// <param name="item">The item to find.</param>
			vint IndexOf(const K& item)const
			{
				for (vint i = 0; i < this->count; i++)
				{
					if (this->ItemOf(i) == item)
					{
						return i;
					}
				}
				
				return -1;
			}
			
			/// <summary>Add an item at the end of the list.</summary>
			/// <returns>The index of the added item.</returns>
			/// <param name="item">The item to add.</param>
			vint Add(const T& item)
			{
				return Insert(this->count, item);
			}
			
			/// <summary>Add an item at the specified position.</summary>
			/// <returns>The index of the added item.</returns>
			/// <param name="index">The position of the item to add.</param>
			/// <param name="item">The item to add.</param>
			vint Insert(vint index, const T& item)
			{
				CHECK_ERROR(index >= 0 && index <= this->count, L"List<T, K>::Insert(vint, const T&)#Argument index not in range.");
				bool uninitialized = false;
				this->MakeRoom(index, 1, uninitialized);
				
				if (uninitialized)
				{
					new (&this->ItemOf(index))T(item);
				}
				else
				{
					this->ItemOf(index) = item;
				}
				
				return index;
			}
			
			/// <summary>Remove an item.</summary>
			/// <returns>Returns true if the item is removed.</returns>
			/// <param name="item">The item to remove.</param>
			bool Remove(const K& item)
			{
				vint index = IndexOf(item);
				
				if (index >= 0 && index < this->count)
				{
					this->RemoveAt(index);
					return true;
				}
				else
				{
					return false;
				}
			}
			
			/// <summary>Replace an item.</summary>
			/// <returns>Returns true if this operation succeeded.</returns>
			/// <param name="index">The position of the item.</param>
			/// <param name="item">The new item to put into the array.</param>
			bool Set(vint index, const T& item)
			{
				CHECK_ERROR(index >= 0 && index < this->count, L"List<T, K>::Set(vint)#Argument index not in range.");
				this->ItemOf(index) = item;
				return true;
			}
			
			/// <summary>Get the reference to the specified element.</summary>
			/// <returns>The reference to the specified element.</returns>
			/// <param name="index">The index of the element.</param>
			using ListBase<T, K>::operator[];
			T& operator[](vint index)
			{
				CHECK_ERROR(index >= 0 && index < this->count, L"List<T, K>::operator[](vint)#Argument index not in range.");
				return this->ItemOf(index);
			}
		};
		
		/***********************************************************************
		SortedList
		***********************************************************************/
		
		/// <summary>List that keeps everything in order.</summary>
		/// <typeparam name="T">Type of elements.</typeparam>
		/// <typeparam name="K">Type of the key type of elements.</typeparam>
		template<typename T, typename K = typename KeyType<T>::Type>
		class SortedList : public ListBase<T, K>
		{
		 protected:
		 
			/// <summary>Get the position of an item in this list.</summary>
			/// <typeparam name="Key">Type of the item to find.</typeparam>
			/// <returns>Returns the position. Returns -1 if not exists</returns>
			/// <param name="item">The item to find.</param>
			/// <param name="index">Returns the last index.</param>
			template<typename Key>
			vint IndexOfInternal(const Key& item, vint& index)const
			{
				vint start = 0;
				vint end = this->count - 1;
				index = -1;
				
				while (start <= end)
				{
					index = start + (end - start) / 2;
					
					if (this->ItemOf(index) == item)
					{
						return index;
					}
					else
						if (this->ItemOf(index) > item)
						{
							end = index - 1;
						}
						else
						{
							start = index + 1;
						}
				}
				
				return -1;
			}
			
			vint Insert(vint index, const T& item)
			{
				bool uninitialized = false;
				this->MakeRoom(index, 1, uninitialized);
				
				if (uninitialized)
				{
					new (&this->ItemOf(index))T(item);
				}
				else
				{
					this->ItemOf(index) = item;
				}
				
				return index;
			}
		 public:
			/// <summary>Create a list.</summary>
			SortedList()
			{
			}
			
			/// <summary>Test does the list contain an item or not.</summary>
			/// <returns>Returns true if the list contains the specified item.</returns>
			/// <param name="item">The item to test.</param>
			bool Contains(const K& item)const
			{
				return IndexOf(item) != -1;
			}
			
			/// <summary>Get the position of an item in this list.</summary>
			/// <returns>Returns the position. Returns -1 if not exists</returns>
			/// <param name="item">The item to find.</param>
			vint IndexOf(const K& item)const
			{
				vint outputIndex = -1;
				return IndexOfInternal<K>(item, outputIndex);
			}
			
			/// <summary>Add an item at a correct position to keep everying in order.</summary>
			/// <returns>The index of the added item.</returns>
			/// <param name="item">The item to add.</param>
			vint Add(const T& item)
			{
				if (ArrayBase<T>::count == 0)
				{
					return Insert(0, item);
				}
				else
				{
					vint outputIndex = -1;
					IndexOfInternal<T>(item, outputIndex);
					CHECK_ERROR(outputIndex >= 0 && outputIndex < this->count, L"SortedList<T, K>::Add(const T&)#Internal error, index not in range.");
					
					if (this->ItemOf(outputIndex) < item)
					{
						outputIndex++;
					}
					
					return Insert(outputIndex, item);
				}
			}
			
			/// <summary>Remove an item.</summary>
			/// <returns>Returns true if the item is removed.</returns>
			/// <param name="item">The item to remove.</param>
			bool Remove(const K& item)
			{
				vint index = IndexOf(item);
				
				if (index >= 0 && index < ArrayBase<T>::count)
				{
					this->RemoveAt(index);
					return true;
				}
				else
				{
					return false;
				}
			}
		};
		
		/***********************************************************************
		Special Containers
		***********************************************************************/
		
		template<typename T>
		class PushOnlyAllocator : public Object, private NotCopyable
		{
		 protected:
			vint							blockSize;
			vint							allocatedSize;
			List<T*>						blocks;
			
		 public:
			PushOnlyAllocator(vint _blockSize = 65536)
				: blockSize(_blockSize)
				, allocatedSize(0)
			{
			}
			
			~PushOnlyAllocator()
			{
				for (vint i = 0; i < blocks.Count(); i++)
				{
					delete[] blocks[i];
				}
			}
			
			T* Get(vint index)
			{
				if (index >= allocatedSize)
				{
					return 0;
				}
				
				vint row = index / blockSize;
				vint column = index % blockSize;
				return &blocks[row][column];
			}
			
			T* Create()
			{
				if (allocatedSize == blocks.Count()*blockSize)
				{
					blocks.Add(new T[blockSize]);
				}
				
				vint index = allocatedSize++;
				return Get(index);
			}
		};
		
		namespace bom_helper
		{
			struct TreeNode
			{
				TreeNode*					nodes[4];
			};
			
			template<vint Index = 4>
			struct Accessor
			{
				static __forceinline void* Get(TreeNode* root, vuint8_t index)
				{
					if (!root)
					{
						return 0;
					}
					
					vint fragmentIndex = (index >> (2 * (Index - 1))) % 4;
					TreeNode* fragmentRoot = root->nodes[fragmentIndex];
					return fragmentRoot ? Accessor < Index - 1 >::Get(fragmentRoot, index) : 0;
				}
				
				static __forceinline void Set(TreeNode*& root, vuint8_t index, void* value, PushOnlyAllocator<TreeNode>& allocator)
				{
					if (!root)
					{
						root = allocator.Create();
						memset(root->nodes, 0, sizeof(root->nodes));
					}
					
					vint fragmentIndex = (index >> (2 * (Index - 1))) % 4;
					TreeNode*& fragmentRoot = root->nodes[fragmentIndex];
					Accessor < Index - 1 >::Set(fragmentRoot, index, value, allocator);
				}
			};
			
			template<>
			struct Accessor<0>
			{
				static __forceinline void* Get(TreeNode* root, vuint8_t index)
				{
					return (void*)root;
				}
				
				static __forceinline void Set(TreeNode*& root, vuint8_t index, void* value, PushOnlyAllocator<TreeNode>& allocator)
				{
					((void*&)root) = value;
				}
			};
		}
		
		template<typename T>
		class ByteObjectMap : public Object, private NotCopyable
		{
		 public:
			typedef PushOnlyAllocator<bom_helper::TreeNode>			Allocator;
		 protected:
			bom_helper::TreeNode*			root;
			
		 public:
			ByteObjectMap()
				: root(0)
			{
			}
			
			~ByteObjectMap()
			{
			}
			
			T* Get(vuint8_t index)
			{
				return (T*)bom_helper::Accessor<>::Get(root, index);
			}
			
			void Set(vuint8_t index, T* value, Allocator& allocator)
			{
				bom_helper::Accessor<>::Set(root, index, value, allocator);
			}
		};
		
		/***********************************************************************
		Random Access
		***********************************************************************/
		
		namespace randomaccess_internal
		{
			template<typename T, typename K>
			struct RandomAccessable<Array<T, K>>
			{
				static const bool							CanRead = true;
				static const bool							CanResize = true;
			};
			
			template<typename T, typename K>
			struct RandomAccessable<List<T, K>>
			{
				static const bool							CanRead = true;
				static const bool							CanResize = false;
			};
			
			template<typename T, typename K>
			struct RandomAccessable<SortedList<T, K>>
			{
				static const bool							CanRead = true;
				static const bool							CanResize = false;
			};
		}
	}
}

#ifdef VCZH_CHECK_MEMORY_LEAKS_NEW
#define new VCZH_CHECK_MEMORY_LEAKS_NEW
#endif

#endif


/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Data Structure::Dictionary

Classes:
Dictionary<KT, VT, KK, VK>					：映射
Group<KT, VT, KK, VK>						：多重映射
***********************************************************************/

#ifndef VCZH_COLLECTIONS_DICTIONARY
#define VCZH_COLLECTIONS_DICTIONARY


namespace vl
{
	namespace collections
	{
		/// <summary>Dictionary.</summary>
		/// <typeparam name="KT">Type of keys.</typeparam>
		/// <typeparam name="VT">Type of values.</typeparam>
		/// <typeparam name="KK">Type of the key type of keys.</typeparam>
		/// <typeparam name="VK">Type of the key type of values.</typeparam>
		template <
		  typename KT,
		  typename VT,
		  typename KK = typename KeyType<KT>::Type,
		  typename VK = typename KeyType<VT>::Type
		  >
		class Dictionary : public Object, public virtual IEnumerable<Pair<KT, VT>>
		{
		 public:
			typedef SortedList<KT, KK>			KeyContainer;
			typedef List<VT, VK>				ValueContainer;
		 protected:
			class Enumerator : public Object, public virtual IEnumerator<Pair<KT, VT>>
			{
			 private:
				const Dictionary<KT, VT, KK, VK>*	container;
				vint								index;
				Pair<KT, VT>						current;
				
				void UpdateCurrent()
				{
					if (index < container->Count())
					{
						current.key = container->Keys().Get(index);
						current.value = container->Values().Get(index);
					}
				}
			 public:
				Enumerator(const Dictionary<KT, VT, KK, VK>* _container, vint _index = -1)
				{
					container = _container;
					index = _index;
				}
				
				IEnumerator<Pair<KT, VT>>* Clone()const
				{
					return new Enumerator(container, index);
				}
				
				const Pair<KT, VT>& Current()const
				{
					return current;
				}
				
				vint Index()const
				{
					return index;
				}
				
				bool Next()
				{
					index++;
					UpdateCurrent();
					return index >= 0 && index < container->Count();
				}
				
				void Reset()
				{
					index = -1;
					UpdateCurrent();
				}
			};
			
			KeyContainer						keys;
			ValueContainer						values;
		 public:
			/// <summary>Create a dictionary.</summary>
			Dictionary()
			{
			}
			
			IEnumerator<Pair<KT, VT>>* CreateEnumerator()const
			{
				return new Enumerator(this);
			}
			
			/// <summary>Set a preference of using memory.</summary>
			/// <param name="mode">Set to true (by default) to let the container efficiently reduce memory usage when necessary.</param>
			void SetLessMemoryMode(bool mode)
			{
				keys.SetLessMemoryMode(mode);
				values.SetLessMemoryMode(mode);
			}
			
			/// <summary>Get all keys.</summary>
			/// <returns>All keys.</returns>
			const KeyContainer& Keys()const
			{
				return keys;
			}
			
			/// <summary>Get all values.</summary>
			/// <returns>All values.</returns>
			const ValueContainer& Values()const
			{
				return values;
			}
			
			/// <summary>Get the number of keys.</summary>
			/// <returns>The number of keys.</returns>
			vint Count()const
			{
				return keys.Count();
			}
			
			/// <summary>Get the reference to the value associated with a key.</summary>
			/// <returns>The reference to the value.</returns>
			/// <param name="key">The key to find.</param>
			const VT& Get(const KK& key)const
			{
				return values.Get(keys.IndexOf(key));
			}
			
			/// <summary>Get the reference to the value associated with a key.</summary>
			/// <returns>The reference to the value.</returns>
			/// <param name="key">The key to find.</param>
			const VT& operator[](const KK& key)const
			{
				return values.Get(keys.IndexOf(key));
			}
			
			/// <summary>Replace the value associated with a key.</summary>
			/// <returns>Returns true if the value is replaced.</returns>
			/// <param name="key">The key to find.</param>
			/// <param name="value">The key to replace.</param>
			bool Set(const KT& key, const VT& value)
			{
				vint index = keys.IndexOf(KeyType<KT>::GetKeyValue(key));
				
				if (index == -1)
				{
					index = keys.Add(key);
					values.Insert(index, value);
				}
				else
				{
					values[index] = value;
				}
				
				return true;
			}
			
			/// <summary>Add a key with an associated value. Exception will raise if the key already exists.</summary>
			/// <returns>Returns true if the pair is added.</returns>
			/// <param name="value">The pair of key and value.</param>
			bool Add(const Pair<KT, VT>& value)
			{
				return Add(value.key, value.value);
			}
			
			/// <summary>Add a key with an associated value. Exception will raise if the key already exists.</summary>
			/// <returns>Returns true if the pair is added.</returns>
			/// <param name="key">The key.</param>
			/// <param name="value">The value.</param>
			bool Add(const KT& key, const VT& value)
			{
				CHECK_ERROR(!keys.Contains(KeyType<KT>::GetKeyValue(key)), L"Dictionary<KT, KK, ValueContainer, VT, VK>::Add(const KT&, const VT&)#Key already exists.");
				vint index = keys.Add(key);
				values.Insert(index, value);
				return true;
			}
			
			/// <summary>Remove a key with the associated value.</summary>
			/// <returns>Returns true if the key and the value is removed.</returns>
			/// <param name="key">The key.</param>
			bool Remove(const KK& key)
			{
				vint index = keys.IndexOf(key);
				
				if (index != -1)
				{
					keys.RemoveAt(index);
					values.RemoveAt(index);
					return true;
				}
				else
				{
					return false;
				}
			}
			
			/// <summary>Remove everything.</summary>
			/// <returns>Returns true if all keys and values are removed.</returns>
			bool Clear()
			{
				keys.Clear();
				values.Clear();
				return true;
			}
		};
		
		/// <summary>Group, which is similar to an dictionary, but a group can associate multiple values with a key.</summary>
		/// <typeparam name="KT">Type of keys.</typeparam>
		/// <typeparam name="VT">Type of values.</typeparam>
		/// <typeparam name="KK">Type of the key type of keys.</typeparam>
		/// <typeparam name="VK">Type of the key type of values.</typeparam>
		template <
		  typename KT,
		  typename VT,
		  typename KK = typename KeyType<KT>::Type,
		  typename VK = typename KeyType<VT>::Type
		  >
		class Group : public Object, public virtual IEnumerable<Pair<KT, VT>>
		{
			typedef SortedList<KT, KK>		KeyContainer;
			typedef List<VT, VK>			ValueContainer;
		 protected:
			class Enumerator : public Object, public virtual IEnumerator<Pair<KT, VT>>
			{
			 private:
				const Group<KT, VT, KK, VK>*		container;
				vint								keyIndex;
				vint								valueIndex;
				Pair<KT, VT>						current;
				
				void UpdateCurrent()
				{
					if (keyIndex < container->Count())
					{
						const ValueContainer& values = container->GetByIndex(keyIndex);
						
						if (valueIndex < values.Count())
						{
							current.key = container->Keys().Get(keyIndex);
							current.value = values.Get(valueIndex);
						}
					}
				}
			 public:
				Enumerator(const Group<KT, VT, KK, VK>* _container, vint _keyIndex = -1, vint _valueIndex = -1)
				{
					container = _container;
					keyIndex = _keyIndex;
					valueIndex = _valueIndex;
				}
				
				IEnumerator<Pair<KT, VT>>* Clone()const
				{
					return new Enumerator(container, keyIndex, valueIndex);
				}
				
				const Pair<KT, VT>& Current()const
				{
					return current;
				}
				
				vint Index()const
				{
					if (0 <= keyIndex && keyIndex < container->Count())
					{
						vint index = 0;
						
						for (vint i = 0; i < keyIndex; i++)
						{
							index += container->GetByIndex(i).Count();
						}
						
						return index + valueIndex;
					}
					else
					{
						return -1;
					}
				}
				
				bool Next()
				{
					if (keyIndex == -1)
					{
						keyIndex = 0;
					}
					
					while (keyIndex < container->Count())
					{
						valueIndex++;
						const ValueContainer& values = container->GetByIndex(keyIndex);
						
						if (valueIndex < values.Count())
						{
							UpdateCurrent();
							return true;
						}
						else
						{
							keyIndex++;
							valueIndex = -1;
						}
					}
					
					return false;
				}
				
				void Reset()
				{
					keyIndex = -1;
					valueIndex = -1;
					UpdateCurrent();
				}
			};
			
			KeyContainer					keys;
			List<ValueContainer*>			values;
		 public:
			Group()
			{
			}
			
			~Group()
			{
				Clear();
			}
			
			IEnumerator<Pair<KT, VT>>* CreateEnumerator()const
			{
				return new Enumerator(this);
			}
			
			/// <summary>Get all keys.</summary>
			/// <returns>All keys.</returns>
			const KeyContainer& Keys()const
			{
				return keys;
			}
			
			/// <summary>Get the number of keys.</summary>
			/// <returns>The number of keys.</returns>
			vint Count()const
			{
				return keys.Count();
			}
			
			/// <summary>Get all values associated with a key.</summary>
			/// <returns>All values.</returns>
			/// <param name="key">The key to find.</param>
			const ValueContainer& Get(const KK& key)const
			{
				return *values.Get(keys.IndexOf(key));
			}
			
			/// <summary>Get all values associated with a key.</summary>
			/// <returns>All values.</returns>
			/// <param name="index">The position of a the key.</param>
			const ValueContainer& GetByIndex(vint index)const
			{
				return *values.Get(index);
			}
			
			/// <summary>Get all values associated with a key.</summary>
			/// <returns>All values.</returns>
			/// <param name="key">The key to find.</param>
			const ValueContainer& operator[](const KK& key)const
			{
				return *values.Get(keys.IndexOf(key));
			}
			
			/// <summary>Test if a key exists in the group or not.</summary>
			/// <returns>Returns true if the key exists.</returns>
			/// <param name="key">The key to find.</param>
			bool Contains(const KK& key)const
			{
				return keys.Contains(key);
			}
			
			/// <summary>Test if a key exists with an associated value in the group or not.</summary>
			/// <returns>Returns true if the key exists with an associated value.</returns>
			/// <param name="key">The key to find.</param>
			/// <param name="value">The value to find.</param>
			bool Contains(const KK& key, const VK& value)const
			{
				vint index = keys.IndexOf(key);
				
				if (index != -1)
				{
					return values.Get(index)->Contains(value);
				}
				else
				{
					return false;
				}
			}
			
			/// <summary>Add a key with an associated value. If the key already exists, the value will be associated with the key with other values.</summary>
			/// <returns>Returns true if the pair is added.</returns>
			/// <param name="value">The pair of key and value.</param>
			bool Add(const Pair<KT, VT>& value)
			{
				return Add(value.key, value.value);
			}
			
			/// <summary>Add a key with an associated value. If the key already exists, the value will be associated with the key with other values.</summary>
			/// <returns>Returns true if the pair is added.</returns>
			/// <param name="key">The key.</param>
			/// <param name="value">The value.</param>
			bool Add(const KT& key, const VT& value)
			{
				ValueContainer* target = 0;
				vint index = keys.IndexOf(KeyType<KT>::GetKeyValue(key));
				
				if (index == -1)
				{
					target = new ValueContainer;
					values.Insert(keys.Add(key), target);
				}
				else
				{
					target = values[index];
				}
				
				target->Add(value);
				return true;
			}
			
			/// <summary>Remove a key with all associated values.</summary>
			/// <returns>Returns true if the key and all associated values are removed.</returns>
			/// <param name="key">The key.</param>
			bool Remove(const KK& key)
			{
				vint index = keys.IndexOf(key);
				
				if (index != -1)
				{
					keys.RemoveAt(index);
					List<VT, VK>* target = values[index];
					values.RemoveAt(index);
					delete target;
					return true;
				}
				else
				{
					return false;
				}
			}
			
			/// <summary>Remove a key with the associated values.</summary>
			/// <returns>Returns true if the key and the associated values are removed. If there are multiple values associated with the key, only the value will be removed.</returns>
			/// <param name="key">The key.</param>
			/// <param name="value">The value.</param>
			bool Remove(const KK& key, const VK& value)
			{
				vint index = keys.IndexOf(key);
				
				if (index != -1)
				{
					List<VT, VK>* target = values[index];
					target->Remove(value);
					
					if (target->Count() == 0)
					{
						keys.RemoveAt(index);
						values.RemoveAt(index);
						delete target;
					}
					
					return true;
				}
				else
				{
					return false;
				}
			}
			
			/// <summary>Remove everything.</summary>
			/// <returns>Returns true if all keys and values are removed.</returns>
			bool Clear()
			{
				for (vint i = 0; i < values.Count(); i++)
				{
					delete values[i];
				}
				
				keys.Clear();
				values.Clear();
				return true;
			}
		};
		
		/***********************************************************************
		辅助函数
		***********************************************************************/
		
		template <
		  typename TKey,
		  typename TValueFirst,
		  typename TValueSecond,
		  typename TDiscardFirst,		// TKey * [TValueFirst] -> void
		  typename TDiscardSecond,	// TKey * [TValueSecond] -> void
		  typename TAccept			// TKey * [TValueFirst] * [TValueSecond] -> void
		  >
		void GroupInnerJoin(
		  const Group<TKey, TValueFirst>& first,
		  const Group<TKey, TValueSecond>& second,
		  const TDiscardFirst& discardFirst,
		  const TDiscardSecond& discardSecond,
		  const TAccept& accept
		)
		{
			vint firstIndex = 0;
			vint secondIndex = 0;
			vint firstCount = first.Keys().Count();
			vint secondCount = second.Keys().Count();
			
			while (true)
			{
				if (firstIndex < firstCount)
				{
					auto firstKey = first.Keys()[firstIndex];
					const List<TValueFirst>& firstValues = first.GetByIndex(firstIndex);
					
					if (secondIndex < secondCount)
					{
						auto secondKey = second.Keys()[secondIndex];
						const List<TValueSecond>& secondValues = second.GetByIndex(secondIndex);
						
						if (firstKey < secondKey)
						{
							discardFirst(firstKey, firstValues);
							firstIndex++;
						}
						else
							if (firstKey > secondKey)
							{
								discardSecond(secondKey, secondValues);
								secondIndex++;
							}
							else
							{
								accept(firstKey, firstValues, secondValues);
								firstIndex++;
								secondIndex++;
							}
					}
					else
					{
						discardFirst(firstKey, firstValues);
						firstIndex++;
					}
				}
				else
				{
					if (secondIndex < secondCount)
					{
						auto secondKey = second.Keys()[secondIndex];
						const List<TValueSecond>& secondValues = second.GetByIndex(secondIndex);
						
						discardSecond(secondKey, secondValues);
						secondIndex++;
					}
					else
					{
						break;
					}
				}
			}
		}
		
		/***********************************************************************
		随机访问
		***********************************************************************/
		namespace randomaccess_internal
		{
			template<typename KT, typename VT, typename KK, typename VK>
			struct RandomAccessable<Dictionary<KT, VT, KK, VK>>
			{
				static const bool							CanRead = true;
				static const bool							CanResize = false;
			};
			
			template<typename KT, typename VT, typename KK, typename VK>
			struct RandomAccess<Dictionary<KT, VT, KK, VK>>
			{
				static vint GetCount(const Dictionary<KT, VT, KK, VK>& t)
				{
					return t.Count();
				}
				
				static Pair<KT, VT> GetValue(const Dictionary<KT, VT, KK, VK>& t, vint index)
				{
					return Pair<KT, VT>(t.Keys().Get(index), t.Values().Get(index));
				}
				
				static void AppendValue(Dictionary<KT, VT, KK, VK>& t, const Pair<KT, VT>& value)
				{
					t.Set(value.key, value.value);
				}
			};
		}
	}
}

#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Data Structure::Operations

***********************************************************************/

#ifndef VCZH_COLLECTIONS_OPERATIONCOPYFROM
#define VCZH_COLLECTIONS_OPERATIONCOPYFROM


namespace vl
{
	namespace collections
	{
	
		/***********************************************************************
		容器复制
		***********************************************************************/
		
		namespace copyfrom_internal
		{
			using namespace randomaccess_internal;
			
			template<typename Ds, typename Ss, bool DsRA, bool SsRA>
			struct CopyFromAlgorithm
			{
			};
			
			template<typename Ds, typename Ss>
			struct CopyFromAlgorithm<Ds, Ss, true, true>
			{
				static void Perform(Ds& ds, const Ss& ss, bool append)
				{
					vint copyCount = RandomAccess<Ss>::GetCount(ss);
					vint index = (append ? RandomAccess<Ds>::GetCount(ds) : 0);
					vint resizeCount = index + copyCount;
					RandomAccess<Ds>::SetCount(ds, resizeCount);
					
					for (vint i = 0; i < copyCount; i++)
					{
						RandomAccess<Ds>::SetValue(ds, index + i, RandomAccess<Ss>::GetValue(ss, i));
					}
				}
			};
			
			template<typename Ds, typename Ss>
			struct CopyFromAlgorithm<Ds, Ss, false, true>
			{
				static void Perform(Ds& ds, const Ss& ss, bool append)
				{
					if (!append)
					{
						ds.Clear();
					}
					
					vint copyCount = RandomAccess<Ss>::GetCount(ss);
					
					for (vint i = 0; i < copyCount; i++)
					{
						RandomAccess<Ds>::AppendValue(ds, RandomAccess<Ss>::GetValue(ss, i));
					}
				}
			};
			
			template<typename Ds, typename Ss>
			struct CopyFromAlgorithm<Ds, Ss, true, false>
			{
				static void Perform(Ds& ds, const Ss& ss, bool append)
				{
					Ptr<IEnumerator<typename Ss::ElementType>> enumerator;
					vint copyCount = 0;
					
					enumerator = ss.CreateEnumerator();
					
					while (enumerator->Next())
					{
						copyCount++;
					}
					
					vint index = (append ? RandomAccess<Ds>::GetCount(ds) : 0);
					vint resizeCount = index + copyCount;
					RandomAccess<Ds>::SetCount(ds, resizeCount);
					
					enumerator = ss.CreateEnumerator();
					
					while (enumerator->Next())
					{
						RandomAccess<Ds>::SetValue(ds, index++, enumerator->Current());
					}
				}
			};
			
			template<typename Ds, typename Ss>
			struct CopyFromAlgorithm<Ds, Ss, false, false>
			{
				static void Perform(Ds& ds, const Ss& ss, bool append)
				{
					if (!append)
					{
						ds.Clear();
					}
					
					Ptr<IEnumerator<typename Ss::ElementType>> enumerator = ss.CreateEnumerator();
					
					while (enumerator->Next())
					{
						RandomAccess<Ds>::AppendValue(ds, enumerator->Current());
					}
				}
			};
			
			template<typename T>
			struct Slice
			{
				const T*	items;
				vint		count;
			};
		}
		
		namespace randomaccess_internal
		{
			template<typename T>
			struct RandomAccessable<copyfrom_internal::Slice<T>>
			{
				static const bool							CanRead = true;
				static const bool							CanResize = true;
			};
			
			template<typename T>
			struct RandomAccess<copyfrom_internal::Slice<T>>
			{
				static vint GetCount(const copyfrom_internal::Slice<T>& t)
				{
					return t.count;
				}
				
				static const T& GetValue(const copyfrom_internal::Slice<T>& t, vint index)
				{
					return t.items[index];
				}
			};
		}
		
		/// <summary>Copy containers.</summary>
		/// <typeparam name="Ds">Type of the destination container.</typeparam>
		/// <typeparam name="Ss">Type of the source container.</typeparam>
		/// <param name="ds">The destination container.</param>
		/// <param name="ss">The source container.</param>
		/// <param name="append">Set to false to delete everything in the destination container before copying.</param>
		template<typename Ds, typename Ss>
		void CopyFrom(Ds& ds, const Ss& ss, bool append = false)
		{
			copyfrom_internal::CopyFromAlgorithm<Ds, Ss, randomaccess_internal::RandomAccessable<Ds>::CanResize, randomaccess_internal::RandomAccessable<Ss>::CanRead>::Perform(ds, ss, append);
		}
		
		/// <summary>Copy containers.</summary>
		/// <typeparam name="Ds">Type of the destination container.</typeparam>
		/// <typeparam name="S">Type of the elements in the source container.</typeparam>
		/// <param name="ds">The destination container.</param>
		/// <param name="buffer">Pointer to the source array.</param>
		/// <param name="count">The number of elements to copy.</param>
		/// <param name="append">Set to false to delete everything in the destination container before copying.</param>
		template<typename Ds, typename S>
		void CopyFrom(Ds& ds, const S* buffer, vint count, bool append = false)
		{
			copyfrom_internal::Slice<S> slice = { buffer, count };
			CopyFrom(ds, slice, append);
		}
		
		/// <summary>Copy containers.</summary>
		/// <typeparam name="Ds">Type of the destination container.</typeparam>
		/// <typeparam name="S">Type of the elements in the source container.</typeparam>
		/// <param name="ds">The destination container.</param>
		/// <param name="begin">Pointer to the first element in the source array.</param>
		/// <param name="end">Pointer to the element after the last element in the source array.</param>
		/// <param name="append">Set to false to delete everything in the destination container before copying.</param>
		template<typename Ds, typename S>
		void CopyFrom(Ds& ds, const S* begin, const S* end, bool append = false)
		{
			copyfrom_internal::Slice<S> slice = { begin, end - begin };
			CopyFrom(ds, slice, append);
		}
	}
}

#endif


/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Data Structure::Operations

***********************************************************************/

#ifndef VCZH_COLLECTIONS_OPERATIONENUMERABLE
#define VCZH_COLLECTIONS_OPERATIONENUMERABLE


namespace vl
{
	namespace collections
	{
	
		/***********************************************************************
		空迭代器
		***********************************************************************/
		
		template<typename T>
		class EmptyEnumerable : public Object, public IEnumerable<T>
		{
		 private:
			class Enumerator : public Object, public virtual IEnumerator<T>
			{
				IEnumerator<T>* Clone()const override
				{
					return new Enumerator;
				}
				
				const T& Current()const override
				{
					return *(T*)0;
				}
				
				vint Index()const override
				{
					return -1;
				}
				
				bool Next()override
				{
					return false;
				}
				
				void Reset()override
				{
				}
				
				bool Evaluated()const override
				{
					return true;
				}
			};
		 public:
			IEnumerator<T>* CreateEnumerator()const
			{
				return new Enumerator;
			}
		};
		
		/***********************************************************************
		递增数组迭代器
		***********************************************************************/
		
		template<typename T>
		class RangeEnumerator : public Object, public virtual IEnumerator<T>
		{
		 protected:
			T			start;
			T			count;
			T			current;
		 public:
			RangeEnumerator(T _start, T _count, T _current)
				: start(_start)
				, count(_count)
				, current(_current)
			{
			}
			
			RangeEnumerator(T _start, T _count)
				: start(_start)
				, count(_count)
				, current(_start - 1)
			{
			}
			
			IEnumerator<T>* Clone()const override
			{
				return new RangeEnumerator(start, count, current);
			}
			
			const T& Current()const override
			{
				return current;
			}
			
			T Index()const override
			{
				return current - start;
			}
			
			bool Next()override
			{
				if (start - 1 <= current && current < start + count - 1)
				{
					current++;
					return true;
				}
				else
				{
					return false;
				}
			}
			
			void Reset()override
			{
				current = start - 1;
			}
			
			bool Evaluated()const override
			{
				return true;
			}
		};
		
		/***********************************************************************
		自包含迭代器
		***********************************************************************/
		
		template<typename T, typename TContainer>
		class ContainerEnumerator : public Object, public virtual IEnumerator<T>
		{
		 private:
			Ptr<TContainer>					container;
			vint							index;
			
		 public:
			ContainerEnumerator(Ptr<TContainer> _container, vint _index = -1)
			{
				container = _container;
				index = _index;
			}
			
			IEnumerator<T>* Clone()const override
			{
				return new ContainerEnumerator(container, index);
			}
			
			const T& Current()const override
			{
				return container->Get(index);
			}
			
			vint Index()const override
			{
				return index;
			}
			
			bool Next()override
			{
				index++;
				return index >= 0 && index < container->Count();
			}
			
			void Reset()override
			{
				index = -1;
			}
			
			bool Evaluated()const override
			{
				return true;
			}
		};
		
		/***********************************************************************
		迭代器比较
		***********************************************************************/
		
		template<typename T, typename U>
		vint CompareEnumerable(const IEnumerable<T>& a, const IEnumerable<U>& b)
		{
			Ptr<IEnumerator<T>> ator = a.CreateEnumerator();
			Ptr<IEnumerator<U>> btor = b.CreateEnumerator();
			
			while (true)
			{
				bool a = ator->Next();
				bool b = btor->Next();
				
				if (a && !b)
				{
					return 1;
				}
				
				if (!a && b)
				{
					return -1;
				}
				
				if (!a && !b)
				{
					break;
				}
				
				const T& ac = ator->Current();
				const U& bc = btor->Current();
				
				if (ac < bc)
				{
					return -1;
				}
				else
					if (ac > bc)
					{
						return 1;
					}
					
				ator->Next();
				btor->Next();
			}
			
			return 0;
		}
		
		template<typename T>
		struct SortedListOperations
		{
			static bool Contains(const SortedList<T>& items, const T& item)
			{
				return items.Contains(item);
			}
		};
		
		template<typename T>
		struct SortedListOperations<Ptr<T>>
		{
			static bool Contains(const SortedList<Ptr<T>>& items, const Ptr<T>& item)
			{
				return items.Contains(item.Obj());
			}
		};
	}
}

#endif


/***********************************************************************
.\COLLECTIONS\OPERATIONCONCAT.H
***********************************************************************/
/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Data Structure::Operations

***********************************************************************/

#ifndef VCZH_COLLECTIONS_OPERATIONCONCAT
#define VCZH_COLLECTIONS_OPERATIONCONCAT


namespace vl
{
	namespace collections
	{
	
		/***********************************************************************
		Concat
		***********************************************************************/
		
		template<typename T>
		class ConcatEnumerator : public virtual IEnumerator<T>
		{
		 protected:
			IEnumerator<T>*					enumerator1;
			IEnumerator<T>*					enumerator2;
			vint							index;
			bool							turned;
		 public:
			ConcatEnumerator(IEnumerator<T>* _enumerator1, IEnumerator<T>* _enumerator2, vint _index = -1, bool _turned = false)
				: enumerator1(_enumerator1)
				, enumerator2(_enumerator2)
				, index(_index)
				, turned(_turned)
			{
			}
			
			~ConcatEnumerator()
			{
				delete enumerator1;
				delete enumerator2;
			}
			
			IEnumerator<T>* Clone()const override
			{
				return new ConcatEnumerator(enumerator1->Clone(), enumerator2->Clone(), index, turned);
			}
			
			const T& Current()const override
			{
				if (turned)
				{
					return enumerator2->Current();
				}
				else
				{
					return enumerator1->Current();
				}
			}
			
			vint Index()const override
			{
				return index;
			}
			
			bool Next()override
			{
				index++;
				
				if (turned)
				{
					return enumerator2->Next();
				}
				else
				{
					if (enumerator1->Next())
					{
						return true;
					}
					else
					{
						turned = true;
						return enumerator2->Next();
					}
				}
			}
			
			void Reset()override
			{
				enumerator1->Reset();
				enumerator2->Reset();
				index = -1;
				turned = false;
			}
			
			bool Evaluated()const override
			{
				return enumerator1->Evaluated() && enumerator2->Evaluated();
			}
		};
	}
}

#endif

/***********************************************************************
.\COLLECTIONS\OPERATIONFOREACH.H
***********************************************************************/
/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Data Structure::Operations

扩展：
实现一个函数重载IteratorType CreateForEachIterator(const CollectionType& collection);
CollectionType是所需要的容器类型
IteratorType继承自ForEachIterator<T>
必须写在vl::collections命名空间里
***********************************************************************/

#ifndef VCZH_COLLECTIONS_FOREACH
#define VCZH_COLLECTIONS_FOREACH

namespace vl
{
	namespace collections
	{
	
		/***********************************************************************
		ForEach基础设施
		***********************************************************************/
		
		template<typename T>
		class ForEachIterator : public Object
		{
		 public:
			virtual bool				Next(T& variable)const = 0;
			
			operator bool()const
			{
				return true;
			}
		};
		
		/***********************************************************************
		IEnumerable<T>支持
		***********************************************************************/
		
		template<typename T>
		class EnumerableForEachIterator : public ForEachIterator<T>
		{
		 protected:
			Ptr<IEnumerator<T>>			enumerator;
		 public:
			EnumerableForEachIterator(const IEnumerable<T>& enumerable)
				: enumerator(enumerable.CreateEnumerator())
			{
			}
			
			EnumerableForEachIterator(const EnumerableForEachIterator<T>& enumerableIterator)
				: enumerator(enumerableIterator.enumerator)
			{
			}
			
			bool Next(T& variable)const
			{
				if (enumerator->Next())
				{
					variable = enumerator->Current();
					return true;
				}
				else
				{
					return false;
				}
			}
		};
		
		template<typename T>
		EnumerableForEachIterator<T> CreateForEachIterator(const IEnumerable<T>& enumerable)
		{
			return enumerable;
		}
		
		/***********************************************************************
		ForEach宏
		***********************************************************************/
		
#define FOREACH(TYPE, VARIABLE, COLLECTION)\
	SCOPE_VARIABLE(const ::vl::collections::ForEachIterator<TYPE>&, __foreach_iterator__, ::vl::collections::CreateForEachIterator(COLLECTION))\
	for(TYPE VARIABLE;__foreach_iterator__.Next(VARIABLE);)
		
#define FOREACH_INDEXER(TYPE, VARIABLE, INDEXER, COLLECTION)\
	SCOPE_VARIABLE(const ::vl::collections::ForEachIterator<TYPE>&, __foreach_iterator__, ::vl::collections::CreateForEachIterator(COLLECTION))\
	SCOPE_VARIABLE(vint, INDEXER, 0)\
	for(TYPE VARIABLE;__foreach_iterator__.Next(VARIABLE);INDEXER++)
	}
}

#endif

/***********************************************************************
.\COLLECTIONS\OPERATIONPAIR.H
***********************************************************************/
/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Data Structure::Operations

***********************************************************************/

#ifndef VCZH_COLLECTIONS_OPERATIONPAIR
#define VCZH_COLLECTIONS_OPERATIONPAIR


namespace vl
{
	namespace collections
	{
	
		/***********************************************************************
		Pairwise
		***********************************************************************/
		
		template<typename S, typename T>
		class PairwiseEnumerator : public virtual IEnumerator<Pair<S, T>>
		{
		 protected:
			IEnumerator<S>*					enumerator1;
			IEnumerator<T>*					enumerator2;
			Pair<S, T>						current;
		 public:
			PairwiseEnumerator(IEnumerator<S>* _enumerator1, IEnumerator<T>* _enumerator2, Pair<S, T> _current = Pair<S, T>())
				: enumerator1(_enumerator1)
				, enumerator2(_enumerator2)
				, current(_current)
			{
			}
			
			~PairwiseEnumerator()
			{
				delete enumerator1;
				delete enumerator2;
			}
			
			IEnumerator<Pair<S, T>>* Clone()const override
			{
				return new PairwiseEnumerator(enumerator1->Clone(), enumerator2->Clone(), current);
			}
			
			const Pair<S, T>& Current()const override
			{
				return current;
			}
			
			vint Index()const override
			{
				return enumerator1->Index();
			}
			
			bool Next()override
			{
				if (enumerator1->Next() && enumerator2->Next())
				{
					current = Pair<S, T>(enumerator1->Current(), enumerator2->Current());
					return true;
				}
				else
				{
					return false;
				}
			}
			
			void Reset()override
			{
				enumerator1->Reset();
				enumerator2->Reset();
			}
			
			bool Evaluated()const override
			{
				return enumerator1->Evaluated() && enumerator2->Evaluated();
			}
		};
	}
}

#endif
/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Data Structure::Operations

***********************************************************************/

#ifndef VCZH_COLLECTIONS_OPERATIONSEQUENCE
#define VCZH_COLLECTIONS_OPERATIONSEQUENCE


namespace vl
{
	namespace collections
	{
	
		/***********************************************************************
		Take
		***********************************************************************/
		
		template<typename T>
		class TakeEnumerator : public virtual IEnumerator<T>
		{
		 protected:
			IEnumerator<T>*			enumerator;
			vint					count;
		 public:
			TakeEnumerator(IEnumerator<T>* _enumerator, vint _count)
				: enumerator(_enumerator)
				, count(_count)
			{
			}
			
			~TakeEnumerator()
			{
				delete enumerator;
			}
			
			IEnumerator<T>* Clone()const override
			{
				return new TakeEnumerator(enumerator->Clone(), count);
			}
			
			const T& Current()const override
			{
				return enumerator->Current();
			}
			
			vint Index()const override
			{
				return enumerator->Index();
			}
			
			bool Next()override
			{
				if (enumerator->Index() >= count - 1)
				{
					return false;
				}
				
				return enumerator->Next();
			}
			
			void Reset()override
			{
				enumerator->Reset();
			}
			
			bool Evaluated()const override
			{
				return enumerator->Evaluated();
			}
		};
		
		/***********************************************************************
		Skip
		***********************************************************************/
		
		template<typename T>
		class SkipEnumerator : public virtual IEnumerator<T>
		{
		 protected:
			IEnumerator<T>*			enumerator;
			vint					count;
			bool					skipped;
		 public:
			SkipEnumerator(IEnumerator<T>* _enumerator, vint _count, bool _skipped = false)
				: enumerator(_enumerator)
				, count(_count)
				, skipped(_skipped)
			{
			}
			
			~SkipEnumerator()
			{
				delete enumerator;
			}
			
			IEnumerator<T>* Clone()const override
			{
				return new SkipEnumerator(enumerator->Clone(), count, skipped);
			}
			
			const T& Current()const override
			{
				return enumerator->Current();
			}
			
			vint Index()const override
			{
				return enumerator->Index() - count;
			}
			
			bool Next()override
			{
				if (!skipped)
				{
					skipped = true;
					
					for (vint i = 0; i < count; i++)
					{
						if (!enumerator->Next())
						{
							return false;
						}
					}
				}
				
				return enumerator->Next();
			}
			
			void Reset()override
			{
				enumerator->Reset();
				skipped = false;
			}
			
			bool Evaluated()const override
			{
				return enumerator->Evaluated();
			}
		};
		
		/***********************************************************************
		Repeat
		***********************************************************************/
		
		template<typename T>
		class RepeatEnumerator : public virtual IEnumerator<T>
		{
		 protected:
			IEnumerator<T>*			enumerator;
			vint					count;
			vint					index;
			vint					repeatedCount;
		 public:
			RepeatEnumerator(IEnumerator<T>* _enumerator, vint _count, vint _index = -1, vint _repeatedCount = 0)
				: enumerator(_enumerator)
				, count(_count)
				, index(_index)
				, repeatedCount(_repeatedCount)
			{
			}
			
			~RepeatEnumerator()
			{
				delete enumerator;
			}
			
			IEnumerator<T>* Clone()const override
			{
				return new RepeatEnumerator(enumerator->Clone(), count, index, repeatedCount);
			}
			
			const T& Current()const override
			{
				return enumerator->Current();
			}
			
			vint Index()const override
			{
				return index;
			}
			
			bool Next()override
			{
				while (repeatedCount < count)
				{
					if (enumerator->Next())
					{
						index++;
						return true;
					}
					
					repeatedCount++;
					enumerator->Reset();
				}
				
				return false;
			}
			
			void Reset()override
			{
				enumerator->Reset();
				index = -1;
				repeatedCount = 0;
			}
			
			bool Evaluated()const override
			{
				return enumerator->Evaluated();
			}
		};
		
		/***********************************************************************
		Distinct
		***********************************************************************/
		
		template<typename T>
		class DistinctEnumerator : public virtual IEnumerator<T>
		{
		 protected:
			IEnumerator<T>*		enumerator;
			SortedList<T>		distinct;
			T					lastValue;
			
		 public:
			DistinctEnumerator(IEnumerator<T>* _enumerator)
				: enumerator(_enumerator)
			{
			}
			
			DistinctEnumerator(const DistinctEnumerator& _enumerator)
				: lastValue(_enumerator.lastValue)
			{
				enumerator = _enumerator.enumerator->Clone();
				CopyFrom(distinct, _enumerator.distinct);
			}
			
			~DistinctEnumerator()
			{
				delete enumerator;
			}
			
			IEnumerator<T>* Clone()const override
			{
				return new DistinctEnumerator(*this);
			}
			
			const T& Current()const override
			{
				return lastValue;
			}
			
			vint Index()const override
			{
				return distinct.Count() - 1;
			}
			
			bool Next()override
			{
				while (enumerator->Next())
				{
					const T& current = enumerator->Current();
					
					if (!SortedListOperations<T>::Contains(distinct, current))
					{
						lastValue = current;
						distinct.Add(current);
						return true;
					}
				}
				
				return false;
			}
			
			void Reset()override
			{
				enumerator->Reset();
				distinct.Clear();
			}
		};
		
		/***********************************************************************
		Reverse
		***********************************************************************/
		
		template<typename T>
		class ReverseEnumerator : public virtual IEnumerator<T>
		{
		 protected:
			List<T>						cache;
			vint						index;
		 public:
			ReverseEnumerator(const IEnumerable<T>& enumerable)
				: index(-1)
			{
				CopyFrom(cache, enumerable);
			}
			
			ReverseEnumerator(const ReverseEnumerator& _enumerator)
				: index(_enumerator.index)
			{
				CopyFrom(cache, _enumerator.cache);
			}
			
			~ReverseEnumerator()
			{
			}
			
			IEnumerator<T>* Clone()const override
			{
				return new ReverseEnumerator(*this);
			}
			
			const T& Current()const override
			{
				return cache.Get(cache.Count() - 1 - index);
			}
			
			vint Index()const override
			{
				return index;
			}
			
			bool Next()override
			{
				index++;
				return index < cache.Count();
			}
			
			void Reset()override
			{
				index = -1;
			}
			
			bool Evaluated()const override
			{
				return true;
			}
		};
		
		/***********************************************************************
		FromIterator
		***********************************************************************/
		
		template<typename T, typename I>
		class FromIteratorEnumerable : public Object, public IEnumerable<T>
		{
		 private:
			class Enumerator : public Object, public IEnumerator<T>
			{
			 private:
				I				begin;
				I				end;
				I				current;
				
			 public:
				Enumerator(I _begin, I _end, I _current)
					: begin(_begin)
					, end(_end)
					, current(_current)
				{
				}
				
				IEnumerator<T>* Clone()const override
				{
					return new Enumerator(begin, end, current);
				}
				
				const T& Current()const override
				{
					return *current;
				}
				
				vint Index()const override
				{
					return current - begin;
				}
				
				bool Next()override
				{
					current++;
					return begin <= current && current < end;
				}
				
				void Reset()override
				{
					current = begin - 1;
				}
				
				bool Evaluated()const override
				{
					return true;
				}
			};
		 private:
			I					begin;
			I					end;
		 public:
			IEnumerator<T>* CreateEnumerator()const
			{
				return new Enumerator(begin, end, begin - 1);
			}
			
			FromIteratorEnumerable(I _begin, I _end)
				: begin(_begin)
				, end(_end)
			{
			}
			
			FromIteratorEnumerable(const FromIteratorEnumerable<T, I>& enumerable)
				: begin(enumerable.begin)
				, end(enumerable.end)
			{
			}
		};
		
		template<typename T>
		class FromIterator
		{
		 public:
			template<typename I>
			static FromIteratorEnumerable<T, I> Wrap(I begin, I end)
			{
				return FromIteratorEnumerable<T, I>(begin, end);
			}
		};
		
		template<typename T>
		FromIteratorEnumerable<T, T*> FromPointer(T* begin, T* end)
		{
			return FromIteratorEnumerable<T, T*>(begin, end);
		}
		
		template<typename T, int size>
		FromIteratorEnumerable<T, T*> FromArray(T(&items)[size])
		{
			return FromIteratorEnumerable<T, T*>(&items[0], &items[size]);
		}
	}
}

#endif

/***********************************************************************
.\COLLECTIONS\OPERATIONSET.H
***********************************************************************/
/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Data Structure::Operations

***********************************************************************/

#ifndef VCZH_COLLECTIONS_OPERATIONSET
#define VCZH_COLLECTIONS_OPERATIONSET


namespace vl
{
	namespace collections
	{
	
		/***********************************************************************
		Intersect/Except
		***********************************************************************/
		
		template<typename T, bool Intersect>
		class IntersectExceptEnumerator : public virtual IEnumerator<T>
		{
		 protected:
			IEnumerator<T>*				enumerator;
			SortedList<T>				reference;
			vint						index;
			
		 public:
			IntersectExceptEnumerator(IEnumerator<T>* _enumerator, const IEnumerable<T>& _reference)
				: enumerator(_enumerator)
				, index(-1)
			{
				CopyFrom(reference, _reference);
			}
			
			IntersectExceptEnumerator(const IntersectExceptEnumerator& _enumerator)
			{
				enumerator = _enumerator.enumerator->Clone();
				CopyFrom(reference, _enumerator.reference);
				index = _enumerator.index;
			}
			
			~IntersectExceptEnumerator()
			{
				delete enumerator;
			}
			
			IEnumerator<T>* Clone()const override
			{
				return new IntersectExceptEnumerator(*this);
			}
			
			const T& Current()const override
			{
				return enumerator->Current();
			}
			
			vint Index()const override
			{
				return index;
			}
			
			bool Next()override
			{
				while (enumerator->Next())
				{
					if (SortedListOperations<T>::Contains(reference, enumerator->Current()) == Intersect)
					{
						index++;
						return true;
					}
				}
				
				return false;
			}
			
			void Reset()override
			{
				enumerator->Reset();
				index = -1;
			}
		};
	}
}

#endif


/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Data Structure::Operations

***********************************************************************/


#ifndef VCZH_COLLECTIONS_OPERATIONSTRING
#define VCZH_COLLECTIONS_OPERATIONSTRING


namespace vl
{
	namespace collections
	{
		template<typename Ds, typename S>
		void CopyFrom(Ds& ds, const ObjectString<S>& ss, bool append = false)
		{
			const S* buffer = ss.Buffer();
			vint count = ss.Length();
			CopyFrom(ds, buffer, count, append);
		}
		
		template<typename D, typename Ss>
		void CopyFrom(ObjectString<D>& ds, const Ss& ss, bool append = false)
		{
			Array<D> da(ds.Buffer(), ds.Length());
			CopyFrom(da, ss, append);
			
			if (da.Count() == 0)
			{
				ds = ObjectString<D>();
			}
			else
			{
				ds = ObjectString<D>(&da[0], da.Count());
			}
		}
	}
	
	template<typename D, typename Ss>
	void SplitString(const ObjectString<D>& ds, Ss& lst, D delimiter)
	{
		vint index = -1;
		vint length = ds.Length();
		vint start;
		
		while (true)
		{
			start = index + 1;
			index = ds.IndexOf(delimiter, start);
			
			if (index < 0)
			{
				break;
			}
			
			lst.Add(ds.Sub(start, index - start));
		}
		
		if (start >= length)
		{
			start = 0;
			length = 0;
		}
		
		lst.Add(ds.Sub(start, length - start));
	}
	
}

#endif


/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Data Structure::Operations

Functions:
CopyFrom(TargetContainer, SourceContainer)
[T]		.Select(T->K) => [K]
[T]		.SelectMany(T->[K]) => [K]
[T]		.Where(T->bool) => [T]
[Ptr<T>].Cast<K>() => [Ptr<K>]
[Ptr<T>].FindType<K>() => [Ptr<K>]
[T]		.OrderBy(T->T->int) => [T]

[T]		.Aggregate(T->T->T) => T
[T]		.Aggregate(T->T->T, T) => T
[T]		.All(T->bool) => bool
[T]		.Any(T->bool) => bool
[T]		.Max() => T
[T]		.Min() => T
[T]		.First() => T
[T]		.FirstOrDefault(T) => T
[T]		.Last() => T
[T]		.LastOrDefault(T) => T
[T]		.Count() => vint
[T]		.IsEmpty() => bool

[T]		.Concat([T]) => [T]
[T]		.Repeat(vint) => [T]
[T]		.Take(vint) => [T]
[T]		.Skip(vint) => [T]
[T]		.Distinct() => [T]
[T]		.Reverse() => [T]

[T]		.Pairwise([K]) => [(T,K)]
[T]		.Intersect([T]) => [T]
[T]		.Union([T]) => [T]
[T]		.Except([T]) => [T]

[T]		.Evaluate() => [T]
[T]		.GroupBy(T->K) => [(K, [T])]

From(begin, end) => [T]
From(array) => [T]
Range(start, count) => [vint]

FOREACH(X, a, XList)
FOREACH_INDEXER(X, a, index, XList)
***********************************************************************/

#ifndef VCZH_COLLECTIONS_OPERATION
#define VCZH_COLLECTIONS_OPERATION

// #include "OperationSelect.h"
// #include "OperationWhere.h"

namespace vl
{
	namespace collections
	{
	
		/***********************************************************************
		OrderBy Quick Sort
		***********************************************************************/
		
		template<typename T, typename F>
		void SortLambda(T* items, vint length, F orderer)
		{
			if (length == 0)
			{
				return;
			}
			
			vint pivot = 0;
			vint left = 0;
			vint right = 0;
			bool flag = false;
			
			while (left + right + 1 != length)
			{
				vint& mine = (flag ? left : right);
				vint& theirs = (flag ? right : left);
				vint candidate = (flag ? left : length - right - 1);
				vint factor = (flag ? -1 : 1);
				
				if (orderer(items[pivot], items[candidate])*factor <= 0)
				{
					mine++;
				}
				else
				{
					theirs++;
					T temp = items[pivot];
					items[pivot] = items[candidate];
					items[candidate] = temp;
					pivot = candidate;
					flag = !flag;
				}
			}
			
			SortLambda(items, left, orderer);
			SortLambda(items + left + 1, right, orderer);
		}
		
		
		/***********************************************************************
		LazyList
		***********************************************************************/
		
		/// <summary>A lazy evaluated readonly container.</summary>
		/// <typeparam name="T">The type of elements.</typeparam>
		template<typename T>
		class LazyList : public Object, public IEnumerable<T>
		{
		 protected:
			Ptr<IEnumerator<T>>			enumeratorPrototype;
			
			template<typename U>
			static U Element(const IEnumerable<U>&);
			
			IEnumerator<T>* xs()const
			{
				return enumeratorPrototype->Clone();
			}
		 public:
			/// <summary>Create a lazy list with an enumerator.</summary>
			/// <param name="enumerator">The enumerator.</param>
			LazyList(IEnumerator<T>* enumerator)
				: enumeratorPrototype(enumerator)
			{
			}
			
			/// <summary>Create a lazy list with an enumerator.</summary>
			/// <param name="enumerator">The enumerator.</param>
			LazyList(Ptr<IEnumerator<T>> enumerator)
				: enumeratorPrototype(enumerator)
			{
			}
			
			/// <summary>Create a lazy list with an enumerable.</summary>
			/// <param name="enumerable">The enumerator.</param>
			LazyList(const IEnumerable<T>& enumerable)
				: enumeratorPrototype(enumerable.CreateEnumerator())
			{
			}
			
			/// <summary>Create a lazy list with an lazy list.</summary>
			/// <param name="lazyList">The lazy list.</param>
			LazyList(const LazyList<T>& lazyList)
				: enumeratorPrototype(lazyList.enumeratorPrototype)
			{
			}
			
			/// <summary>Create a lazy list with a container.</summary>
			/// <typeparam name="TContainer">Type of the container.</typeparam>
			/// <param name="container">The container.</param>
			template<typename TContainer>
			LazyList(Ptr<TContainer> container)
				: enumeratorPrototype(new ContainerEnumerator<T, TContainer>(container))
			{
			}
			
			/// <summary>Create an empty lazy list.</summary>
			LazyList()
				: enumeratorPrototype(EmptyEnumerable<T>().CreateEnumerator())
			{
			}
			
			LazyList<T>& operator=(const LazyList<T>& lazyList)
			{
				enumeratorPrototype = lazyList.enumeratorPrototype;
				return *this;
			}
			
			IEnumerator<T>* CreateEnumerator()const
			{
				return enumeratorPrototype->Clone();
			}
			
			//-------------------------------------------------------
			
			
			/// <summary>Create a new lazy list with all elements sorted.</summary>
			/// <typeparam name="F">Type of the lambda expression.</typeparam>
			/// <returns>The created lazy list.</returns>
			/// <param name="f">The lambda expression as a comparing function.</param>
			template<typename F>
			LazyList<T> OrderBy(F f)const
			{
				Ptr<List<T>> sorted = new List<T>;
				CopyFrom(*sorted.Obj(), *this);
				
				if (sorted->Count() > 0)
				{
					SortLambda<T, F>(&sorted->operator[](0), sorted->Count(), f);
				}
				
				return new ContainerEnumerator<T, List<T>>(sorted);
			}
			
			//-------------------------------------------------------
			
			/// <summary>Aggregate a lazy list. An exception will raise if the lazy list is empty.</summary>
			/// <typeparam name="F">Type of the lambda expression.</typeparam>
			/// <returns>The aggregated value.</returns>
			/// <param name="f">The lambda expression as an aggregator.</param>
			template<typename F>
			T Aggregate(F f)const
			{
				Ptr<IEnumerator<T>> enumerator = CreateEnumerator();
				
				if (!enumerator->Next())
				{
					throw Error(L"LazyList<T>::Aggregate(F)#Aggregate failed to calculate from an empty container.");
				}
				
				T result = enumerator->Current();
				
				while (enumerator->Next())
				{
					result = f(result, enumerator->Current());
				}
				
				return result;
			}
			
			/// <summary>Aggregate a lazy list.</summary>
			/// <typeparam name="I">Type of the initial value.</typeparam>
			/// <typeparam name="F">Type of the lambda expression.</typeparam>
			/// <returns>The aggregated value.</returns>
			/// <param name="init">The initial value that is virtually added before the lazy list.</param>
			/// <param name="f">The lambda expression as an aggregator.</param>
			template<typename I, typename F>
			I Aggregate(I init, F f)const
			{
				FOREACH(T, t, *this)
				{
					init = f(init, t);
				}
				return init;
			}
			
			
			/// <summary>Get the first value in the lazy list. An exception will raise if the lazy list is empty.</summary>
			/// <returns>The first value.</returns>
			T First()const
			{
				Ptr<IEnumerator<T>> enumerator = CreateEnumerator();
				
				if (!enumerator->Next())
				{
					throw Error(L"LazyList<T>::First(F)#First failed to calculate from an empty container.");
				}
				
				return enumerator->Current();
			}
			
			/// <summary>Get the first value in the lazy list.</summary>
			/// <returns>The first value.</returns>
			/// <param name="defaultValue">Returns this argument if the lazy list is empty.</param>
			T First(T defaultValue)const
			{
				Ptr<IEnumerator<T>> enumerator = CreateEnumerator();
				
				if (!enumerator->Next())
				{
					return defaultValue;
				}
				
				return enumerator->Current();
			}
			
			/// <summary>Get the last value in the lazy list. An exception will raise if the lazy list is empty.</summary>
			/// <returns>The last value.</returns>
			T Last()const
			{
				Ptr<IEnumerator<T>> enumerator = CreateEnumerator();
				
				if (!enumerator->Next())
				{
					throw Error(L"LazyList<T>::Last(F)#Last failed to calculate from an empty container.");
				}
				else
				{
					T value = enumerator->Current();
					
					while (enumerator->Next())
					{
						value = enumerator->Current();
					}
					
					return value;
				}
			}
			
			/// <summary>Get the last value in the lazy list.</summary>
			/// <returns>The last value.</returns>
			/// <param name="defaultValue">Returns this argument if the lazy list is empty.</param>
			T Last(T defaultValue)const
			{
				Ptr<IEnumerator<T>> enumerator = CreateEnumerator();
				
				while (enumerator->Next())
				{
					defaultValue = enumerator->Current();
				}
				
				return defaultValue;
			}
			
			/// <summary>Get the number of elements in the lazy list.</summary>
			/// <returns>The number of elements.</returns>
			vint Count()const
			{
				vint result = 0;
				Ptr<IEnumerator<T>> enumerator = CreateEnumerator();
				
				while (enumerator->Next())
				{
					result++;
				}
				
				return result;
			}
			
			/// <summary>Test is the lazy list empty.</summary>
			/// <returns>Returns true if the lazy list is empty.</returns>
			bool IsEmpty()const
			{
				Ptr<IEnumerator<T>> enumerator = CreateEnumerator();
				return !enumerator->Next();
			}
			
			//-------------------------------------------------------
			
			/// <summary>Create a new lazy list containing elements of the two container one after another.</summary>
			/// <returns>The created lazy list.</returns>
			/// <param name="remains">Elements that put after this lazy list.</param>
			LazyList<T> Concat(const IEnumerable<T>& remains)const
			{
				return new ConcatEnumerator<T>(xs(), remains.CreateEnumerator());
			}
			
			/// <summary>Create a new lazy list with some prefix elements.</summary>
			/// <returns>The created lazy list.</returns>
			/// <param name="count">The size of the prefix.</param>
			LazyList<T> Take(vint count)const
			{
				return new TakeEnumerator<T>(xs(), count);
			}
			
			/// <summary>Create a new lazy list without some prefix elements.</summary>
			/// <returns>The created lazy list.</returns>
			/// <param name="count">The size of the prefix.</param>
			LazyList<T> Skip(vint count)const
			{
				return new SkipEnumerator<T>(xs(), count);
			}
			
			/// <summary>Create a new lazy list with several copies of this lazy list one after another.</summary>
			/// <returns>The created lazy list.</returns>
			/// <param name="count">The numbers of copies.</param>
			LazyList<T> Repeat(vint count)const
			{
				return new RepeatEnumerator<T>(xs(), count);
			}
			
			/// <summary>Create a new lazy list with all elements in this lazy list. If some elements appear several times, only one will be kept.</summary>
			/// <returns>The created lazy list.</returns>
			LazyList<T> Distinct()const
			{
				return new DistinctEnumerator<T>(xs());
			}
			
			/// <summary>Create a new lazy list with all elements in this lazy list in a reverse order.</summary>
			/// <returns>The created lazy list.</returns>
			LazyList<T> Reverse()const
			{
				return new ReverseEnumerator<T>(*this);
			}
			
			//-------------------------------------------------------
			
			/// <summary>Create a new lazy list of pairs from elements from two containers.</summary>
			/// <typeparam name="U">Type of all elements in the second container.</typeparam>
			/// <returns>The created lazy list.</returns>
			/// <param name="remains">The second container.</param>
			template<typename U>
			LazyList<Pair<T, U>> Pairwise(const IEnumerable<U>& remains)const
			{
				return new PairwiseEnumerator<T, U>(xs(), remains.CreateEnumerator());
			}
			
			/// <summary>Create a new lazy list with only elements that appear in both containers.</summary>
			/// <returns>The created lazy list.</returns>
			/// <param name="remains">The second container.</param>
			LazyList<T> Intersect(const IEnumerable<T>& remains)const
			{
				return LazyList<T>(new IntersectExceptEnumerator<T, true>(xs(), remains)).Distinct();
			}
			
			/// <summary>Create a new lazy list with only elements that appear in this lazy list but not in another container.</summary>
			/// <returns>The created lazy list.</returns>
			/// <param name="remains">The second container.</param>
			LazyList<T> Except(const IEnumerable<T>& remains)const
			{
				return LazyList<T>(new IntersectExceptEnumerator<T, false>(xs(), remains)).Distinct();
			}
			
			/// <summary>Create a new lazy list with elements in two containers. If some elements appear several times, only one will be kept.</summary>
			/// <returns>The created lazy list.</returns>
			/// <param name="remains">The second container.</param>
			LazyList<T> Union(const IEnumerable<T>& remains)const
			{
				return Concat(remains).Distinct();
			}
			
			//-------------------------------------------------------
			
			LazyList<T> Evaluate()const
			{
				if (enumeratorPrototype->Evaluated())
				{
					return *this;
				}
				else
				{
					Ptr<List<T>> xs = new List<T>;
					CopyFrom(*xs.Obj(), *this);
					return xs;
				}
			}
			
			
		};
		
		template<typename T>
		LazyList<T> Range(T start, T count)
		{
			return new RangeEnumerator<T>(start, count);
		}
		
		template<typename T>
		LazyList<T> From(const IEnumerable<T>& enumerable)
		{
			return enumerable;
		}
		
		template<typename T>
		LazyList<T> From(const LazyList<T>& enumerable)
		{
			return enumerable;
		}
		
		template<typename T>
		LazyList<T> From(const T* begin, const T* end)
		{
			return FromPointer(begin, end);
		}
		
		template<typename T, int size>
		LazyList<T> From(T(&items)[size])
		{
			return FromArray(items);
		}
		
		template<typename T, int size>
		LazyList<T> From(const T(&items)[size])
		{
			return FromArray(items);
		}
	}
}

#endif


/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Framework::Locale

Interfaces:
***********************************************************************/

#ifndef VCZH_LOCALE
#define VCZH_LOCALE


namespace vl
{
	/// <summary>Locale awared operations. Macro "INVLOC" is a shortcut to get a invariant locale.</summary>
	class Locale : public Object
	{
	 protected:
		WString						localeName;
		
	 public:
		Locale(const WString& _localeName = WString::Empty);
		~Locale();
		
		bool operator==(const Locale& value)const
		{
			return localeName == value.localeName;
		}
		bool operator!=(const Locale& value)const
		{
			return localeName != value.localeName;
		}
		bool operator<(const Locale& value)const
		{
			return localeName < value.localeName;
		}
		bool operator<=(const Locale& value)const
		{
			return localeName <= value.localeName;
		}
		bool operator>(const Locale& value)const
		{
			return localeName > value.localeName;
		}
		bool operator>=(const Locale& value)const
		{
			return localeName >= value.localeName;
		}
		
		/// <summary>Get the invariant locale.</summary>
		/// <returns>The invariant locale.</returns>
		static Locale				Invariant();
		/// <summary>Get the system default locale. This locale controls the code page that used by the the system to interpret ANSI string buffers.</summary>
		/// <returns>The system default locale.</returns>
		static Locale				SystemDefault();
		/// <summary>Get the user default locale. This locale reflect the user's setting.</summary>
		/// <returns>The user default locale.</returns>
		static Locale				UserDefault();
		/// <summary>Get all supported locales.</summary>
		/// <param name="locales">All supported locales.</param>
		static void					Enumerate(collections::List<Locale>& locales);
		
		/// <summary>Get the name of the locale.</summary>
		/// <returns>The name of the locale.</returns>
		const WString&				GetName()const;
		
		/// <summary>Get all short date formats for the locale.</summary>
		/// <param name="formats">The formats.</param>
		void						GetShortDateFormats(collections::List<WString>& formats)const;
		/// <summary>Get all long date formats for the locale.</summary>
		/// <param name="formats">The formats.</param>
		void						GetLongDateFormats(collections::List<WString>& formats)const;
		/// <summary>Get all Year-Month date formats for the locale.</summary>
		/// <param name="formats">The formats.</param>
		void						GetYearMonthDateFormats(collections::List<WString>& formats)const;
		/// <summary>Get all long time formats for the locale.</summary>
		/// <param name="formats">The formats.</param>
		void						GetLongTimeFormats(collections::List<WString>& formats)const;
		/// <summary>Get all short time formats for the locale.</summary>
		/// <param name="formats">The formats.</param>
		void						GetShortTimeFormats(collections::List<WString>& formats)const;
		
		/// <summary>Convert a date to a formatted string.</summary>
		/// <returns>The formatted string.</returns>
		/// <param name="format">The format to use.</param>
		/// <param name="date">The date to convert.</param>
		WString						FormatDate(const WString& format, DateTime date)const;
		/// <summary>Convert a time to a formatted string.</summary>
		/// <returns>The formatted string.</returns>
		/// <param name="format">The format to use.</param>
		/// <param name="time">The time to convert.</param>
		WString						FormatTime(const WString& format, DateTime time)const;
#ifdef VCZH_MSVC
		/// <summary>Convert a number to a formatted string.</summary>
		/// <returns>The formatted string.</returns>
		/// <param name="number">The number to convert.</param>
		WString						FormatNumber(const WString& number)const;
		/// <summary>Convert a currency (money) to a formatted string.</summary>
		/// <returns>The formatted string.</returns>
		/// <param name="currency">The currency to convert.</param>
		WString						FormatCurrency(const WString& currency)const;
#endif
		
		/// <summary>Get the short display string of a day of week.</summary>
		/// <returns>The display string.</returns>
		/// <param name="dayOfWeek">Day of week, begins from 0 as Sunday.</param>
		WString						GetShortDayOfWeekName(vint dayOfWeek)const;
		/// <summary>Get the long display string of a day of week.</summary>
		/// <returns>The display string.</returns>
		/// <param name="dayOfWeek">Day of week, begins from 0 as Sunday.</param>
		WString						GetLongDayOfWeekName(vint dayOfWeek)const;
		/// <summary>Get the short display string of a month.</summary>
		/// <returns>The display string.</returns>
		/// <param name="month">Month, begins from 1 as January.</param>
		WString						GetShortMonthName(vint month)const;
		/// <summary>Get the long display string of a month.</summary>
		/// <returns>The display string.</returns>
		/// <param name="month">Month, begins from 1 as January.</param>
		WString						GetLongMonthName(vint month)const;
		
#ifdef VCZH_MSVC
		/// <summary>Convert characters to the full width.</summary>
		/// <returns>The converted string.</returns>
		/// <param name="str">The string to convert.</param>
		WString						ToFullWidth(const WString& str)const;
		/// <summary>Convert characters to the half width.</summary>
		/// <returns>The converted string.</returns>
		/// <param name="str">The string to convert.</param>
		WString						ToHalfWidth(const WString& str)const;
		/// <summary>Convert characters to the Hiragana.</summary>
		/// <returns>The converted string.</returns>
		/// <param name="str">The string to convert.</param>
		WString						ToHiragana(const WString& str)const;
		/// <summary>Convert characters to the Katagana.</summary>
		/// <returns>The converted string.</returns>
		/// <param name="str">The string to convert.</param>
		WString						ToKatagana(const WString& str)const;
#endif
		
		/// <summary>Convert characters to the lower case using the file system rule.</summary>
		/// <returns>The converted string.</returns>
		/// <param name="str">The string to convert.</param>
		WString						ToLower(const WString& str)const;
		/// <summary>Convert characters to the upper case using the file system rule.</summary>
		/// <returns>The converted string.</returns>
		/// <param name="str">The string to convert.</param>
		WString						ToUpper(const WString& str)const;
		/// <summary>Convert characters to the lower case using the linguistic rule.</summary>
		/// <returns>The converted string.</returns>
		/// <param name="str">The string to convert.</param>
		WString						ToLinguisticLower(const WString& str)const;
		/// <summary>Convert characters to the upper case using the linguistic rule.</summary>
		/// <returns>The converted string.</returns>
		/// <param name="str">The string to convert.</param>
		WString						ToLinguisticUpper(const WString& str)const;
		
#ifdef VCZH_MSVC
		/// <summary>Convert characters to Simplified Chinese.</summary>
		/// <returns>The converted string.</returns>
		/// <param name="str">The string to convert.</param>
		WString						ToSimplifiedChinese(const WString& str)const;
		/// <summary>Convert characters to the Traditional Chinese.</summary>
		/// <returns>The converted string.</returns>
		/// <param name="str">The string to convert.</param>
		WString						ToTraditionalChinese(const WString& str)const;
		/// <summary>Convert characters to the tile case, in which the first letter of each major word is capitalized.</summary>
		/// <returns>The converted string.</returns>
		/// <param name="str">The string to convert.</param>
		WString						ToTileCase(const WString& str)const;
#endif
		
		/// <summary>Mergable flags controlling how to normalize a string.</summary>
		enum Normalization
		{
			/// <summary>Do nothing.</summary>
			None = 0,
			/// <summary>Ignore case using the file system rule.</summary>
			IgnoreCase = 1,
#ifdef VCZH_MSVC
			/// <summary>Ignore case using the linguistic rule.</summary>
			IgnoreCaseLinguistic = 2,
			/// <summary>Ignore the difference between between hiragana and katakana characters.</summary>
			IgnoreKanaType = 4,
			/// <summary>Ignore nonspacing characters.</summary>
			IgnoreNonSpace = 8,
			/// <summary>Ignore symbols and punctuation.</summary>
			IgnoreSymbol = 16,
			/// <summary>Ignore the difference between half-width and full-width characters.</summary>
			IgnoreWidth = 32,
			/// <summary>Treat digits as numbers during sorting.</summary>
			DigitsAsNumbers = 64,
			/// <summary>Treat punctuation the same as symbols.</summary>
			StringSoft = 128,
#endif
		};
		
		/// <summary>Compare two strings.</summary>
		/// <returns>Returns 0 if two strings are equal. Returns a positive number if the first string is larger. Returns a negative number if the second string is larger. When sorting strings, larger strings are put after then smaller strings.</returns>
		/// <param name="s1">The first string to compare.</param>
		/// <param name="s2">The second string to compare.</param>
		/// <param name="normalization">Flags controlling how to normalize a string.</param>
		vint									Compare(const WString& s1, const WString& s2, Normalization normalization)const;
		/// <summary>Compare two strings to test binary equivalence.</summary>
		/// <returns>Returns 0 if two strings are equal. Returns a positive number if the first string is larger. Returns a negative number if the second string is larger. When sorting strings, larger strings are put after then smaller strings.</returns>
		/// <param name="s1">The first string to compare.</param>
		/// <param name="s2">The second string to compare.</param>
		vint									CompareOrdinal(const WString& s1, const WString& s2)const;
		/// <summary>Compare two strings to test binary equivalence, ignoring case.</summary>
		/// <returns>Returns 0 if two strings are equal. Returns a positive number if the first string is larger. Returns a negative number if the second string is larger. When sorting strings, larger strings are put after then smaller strings.</returns>
		/// <param name="s1">The first string to compare.</param>
		/// <param name="s2">The second string to compare.</param>
		vint									CompareOrdinalIgnoreCase(const WString& s1, const WString& s2)const;
		/// <summary>Find the first position that the sub string appears in a text.</summary>
		/// <returns>Returns a pair of numbers, the first number indicating the position in the text, the second number indicating the size of the equivalence sub string in the text. For some normalization, the found sub string may be binary different to the string you want to find.</returns>
		/// <param name="text">The text to find the sub string.</param>
		/// <param name="find">The sub string to match.</param>
		/// <param name="normalization">Flags controlling how to normalize a string.</param>
		collections::Pair<vint, vint>			FindFirst(const WString& text, const WString& find, Normalization normalization)const;
		/// <summary>Find the last position that the sub string appears in a text.</summary>
		/// <returns>Returns a pair of numbers, the first number indicating the position in the text, the second number indicating the size of the equivalence sub string in the text. For some normalization, the found sub string may be binary different to the string you want to find.</returns>
		/// <param name="text">The text to find the sub string.</param>
		/// <param name="find">The sub string to match.</param>
		/// <param name="normalization">Flags controlling how to normalize a string.</param>
		collections::Pair<vint, vint>			FindLast(const WString& text, const WString& find, Normalization normalization)const;
		/// <summary>Test is the prefix of the text equivalence to the provided sub string.</summary>
		/// <returns>Returns true if the prefix of the text equivalence to the provided sub string.</returns>
		/// <param name="text">The text to test the prefix.</param>
		/// <param name="find">The sub string to match.</param>
		/// <param name="normalization">Flags controlling how to normalize a string.</param>
		bool									StartsWith(const WString& text, const WString& find, Normalization normalization)const;
		/// <summary>Test is the postfix of the text equivalence to the provided sub string.</summary>
		/// <returns>Returns true if the postfix of the text equivalence to the provided sub string.</returns>
		/// <param name="text">The text to test the postfix.</param>
		/// <param name="find">The sub string to match.</param>
		/// <param name="normalization">Flags controlling how to normalize a string.</param>
		bool									EndsWith(const WString& text, const WString& find, Normalization normalization)const;
	};
	
#define INVLOC vl::Locale::Invariant()
}

#endif


/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Framework::Exception

Classes:
Exception									：异常
ArgumentException							：预料的的参数错误
***********************************************************************/

#ifndef VCZH_EXCEPTION
#define VCZH_EXCEPTION


namespace vl
{
	/// <summary>Base type of all exceptions.</summary>
	class Exception : public Object
	{
	 protected:
		WString						message;
		
	 public:
		Exception(const WString& _message = WString::Empty);
		
		const WString&				Message()const;
	};
	
	class ArgumentException : public Exception
	{
	 protected:
		WString						function;
		WString						name;
		
	 public:
		ArgumentException(const WString& _message = WString::Empty, const WString& _function = WString::Empty, const WString& _name = WString::Empty);
		
		const WString&				GetFunction()const;
		const WString&				GetName()const;
	};
	
	class ParsingException : public Exception
	{
	 protected:
		vint							position;
		WString						expression;
		
	 public:
		ParsingException(const WString& _message, const WString& _expression, vint _position);
		
		const WString&				GetExpression()const;
		vint							GetPosition()const;
	};
}

#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
UI::Console

***********************************************************************/

#ifndef VCZH_CONSOLE
#define VCZH_CONSOLE


namespace vl
{
	namespace console
	{
		/// <summary>A Static class for command line window operations.</summary>
		class Console abstract
		{
		 public:
			/// <summary>Write to the command line window.</summary>
			/// <param name="string">Content to write.</param>
			/// <param name="length">Size of the content in wchar_t. The zero terminator is not included.</param>
			static void Write(const wchar_t* string, vint length);
			
			/// <summary>Write to the command line window.</summary>
			/// <param name="string">Content to write.</param>
			static void Write(const wchar_t* string);
			
			/// <summary>Write to the command line window.</summary>
			/// <param name="string">Content to write.</param>
			static void Write(const WString& string);
			
			/// <summary>Write to the command line window with a CRLF.</summary>
			/// <param name="string">Content to write.</param>
			static void WriteLine(const WString& string);
			
			/// <summary>Read from the command line window.</summary>
			/// <returns>The whole line read from the command line window.</returns>
			static WString Read();
			
			static void SetColor(bool red, bool green, bool blue, bool light);
			static void SetTitle(const WString& string);
		};
	}
}

#endif




/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Framework::Global Storage

Classes:
GlobalStorage							：全局对象

***********************************************************************/

#ifndef VCZH_GLOBALSTORAGE
#define VCZH_GLOBALSTORAGE


namespace vl
{
	/// <summary><![CDATA[
	/// Base type of all global storages. A global storage is a value with a key to store some information. In order to create a global storage, you should do the following in a cpp file:
	/// BEGIN_GLOBAL_STOREGE_CLASS(<put the key here, it should be a legal C++ identifier>)
	///		<put all variables here>
	/// INITIALIZE_GLOBAL_STORAGE_CLASS
	///		<initialize all variables>
	/// FINALIZE_GLOBAL_STORAGE_CLASS
	///		<clear all resources because the program is about to exit>
	/// END_GLOBAL_STORAGE_CLASS
	/// Then you have a global storage. You can only use this global storage in the current cpp file. [M:vl.InitializeGlobalStorage] should be called before using any global storage. [M:vl.FinalizeGlobalStorage] is encouraged to call if you think you will not use any global storages anymore. It will reduce noices when you want to detect memory leaks.
	/// If the key of the global variable is called Key, and the variable you want to access is called Variable, then you can use GetKey()->Variable to access that variable. The GetKey function is created in the macro calls before.
	/// ]]></summary>
	class GlobalStorage : public Object, private NotCopyable
	{
	 private:
		bool					cleared;
	 public:
		GlobalStorage(const wchar_t* key);
		~GlobalStorage();
		
		bool					Cleared();
		virtual void			ClearResource() = 0;
	};
	
	extern GlobalStorage* GetGlobalStorage(const wchar_t* key);
	extern GlobalStorage* GetGlobalStorage(const WString& key);
	
	/// <summary>Initialize the global storage.</summary>
	extern void InitializeGlobalStorage();
	/// <summary>Finalize the global storage.</summary>
	extern void FinalizeGlobalStorage();
}

#define BEGIN_GLOBAL_STORAGE_CLASS(NAME)\
	class NAME : public vl::GlobalStorage\
	{\
	 public:\
		NAME()\
			:vl::GlobalStorage(L ## #NAME)\
		{\
			InitializeClearResource();\
		}\
		~NAME()\
		{\
			if(!Cleared())ClearResource();\
		}\

#define INITIALIZE_GLOBAL_STORAGE_CLASS\
	void InitializeClearResource()\
	{\

#define FINALIZE_GLOBAL_STORAGE_CLASS\
	}\
	void ClearResource()\
	{\

#define END_GLOBAL_STORAGE_CLASS(NAME)\
	}\
	};\
	NAME& Get##NAME()\
	{\
		static NAME __global_storage_##NAME;\
		return __global_storage_##NAME;\
	}\

#define EXTERN_GLOBAL_STORAGE_CLASS(NAME)\
	class NAME;\
	extern NAME& Get##NAME();\

#endif





#ifndef VCZH_HTTPUTILITY
#define VCZH_HTTPUTILITY


#ifdef VCZH_MSVC

namespace vl
{

	/***********************************************************************
	HTTP Utility
	***********************************************************************/
	
	/// <summary>A type representing an http requiest.</summary>
	class HttpRequest
	{
		typedef collections::Array<char>					BodyBuffer;
		typedef collections::List<WString>					StringList;
		typedef collections::Dictionary<WString, WString>	HeaderMap;
	 public:
		/// <summary>Name of the server, like "gaclib.net".</summary>
		WString				server;
		/// <summary>Port of the server, like 80.</summary>
		vint				port;
		/// <summary>Query of the request, like "/GettingStart.html".</summary>
		WString				query;
		/// <summary>Set to true if the request uses SSL.</summary>
		bool				secure;
		/// <summary>User name to authorize. Set to empty if you don't want to provide it.</summary>
		WString				username;
		/// <summary>Password to authorize. Set to empty if you don't want to provide it.</summary>
		WString				password;
		/// <summary>HTTP method, like "GET", "POST", "PUT", "DELETE", etc.</summary>
		WString				method;
		/// <summary>Cookie. Set to empty if you don't want to provide it.</summary>
		WString				cookie;
		/// <summary>Request body. This is a binary array using an array container to char.</summary>
		BodyBuffer			body;
		/// <summary>Content type, like "text/xml".</summary>
		WString				contentType;
		/// <summary>Accept type list, elements of it like "text/xml".</summary>
		StringList			acceptTypes;
		/// <summary>A dictionary to contain extra headers.</summary>
		HeaderMap			extraHeaders;
		
		/// <summary>Create an empty request.</summary>
		HttpRequest();
		
		/// <summary>Set <see cref="server"/>, <see cref="port"/>, <see cref="query"/> and <see cref="secure"/> fields for you using an URL.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="inputQuery">The URL.</param>
		bool				SetHost(const WString& inputQuery);
		
		/// <summary>Fill the body with a text using UTF-8 encoding.</summary>
		/// <param name="bodyString">The text to fill.</param>
		void				SetBodyUtf8(const WString& bodyString);
	};
	
	/// <summary>A type representing an http response.</summary>
	class HttpResponse
	{
		typedef collections::Array<char>		BodyBuffer;
	 public:
		/// <summary>Status code, like 200.</summary>
		vint				statusCode;
		/// <summary>Response body. This is a binary array using an array container to char.</summary>
		BodyBuffer			body;
		/// <summary>Returned cookie from the server.</summary>
		WString				cookie;
		
		HttpResponse();
		
		/// <summary>If you believe the server returns a text in UTF-8, use it to decode the body.</summary>
		/// <returns>The response body as text.</returns>
		WString				GetBodyUtf8();
	};
	
	/// <summary>Send an http request and receive a response.</summary>
	/// <returns>Returns true if this operation succeeded. Even the server returns 404 will be treated as success, because you get the response.</returns>
	/// <param name="request">The request.</param>
	/// <param name="response">The response.</param>
	extern bool				HttpQuery(const HttpRequest& request, HttpResponse& response);
	
	/// <summary>Encode a text as part of the url. This function can be used to create arguments in an URL.</summary>
	/// <returns>The encoded text.</returns>
	/// <param name="query">The text to encode.</param>
	extern WString			UrlEncodeQuery(const WString& query);
}

#endif

#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Stream::Interfaces

Interfaces:
IStream							：流
***********************************************************************/

#ifndef VCZH_STREAM_INTERFACES
#define VCZH_STREAM_INTERFACES


namespace vl
{
	namespace stream
	{
		/// <summary>
		/// Interface for streams. Stream functions are grouped into 5 categories:
		/// 1) Feature testing functions.
		/// 2) Read functions, available only if [M:vl.stream.IStream.CanRead] returns true.
		/// 3) Peek functions, available only if [M:vl.stream.IStream.CanPeek] returns true.
		/// 4) Write functions, available only if [M:vl.stream.IStream.CanWrite] returns true.
		/// 5) Seek functions, available only if [M:vl.stream.IStream.CanSeek] returns true.
		/// 6) Size functions, available only if [M:vl.stream.IStream.IsLimited] returns true. But there are still some streams knows that the content is limited, but the size is unknown. In this case, [M:vl.stream.IStream.Size] will return -1.
		/// </summary>
		class IStream : public virtual Interface
		{
		 public:
			/// <summary>Test if the stream is readable.</summary>
			/// <returns>Returns true if the stream is readable.</returns>
			virtual bool					CanRead()const = 0;
			/// <summary>Test if the stream is writable.</summary>
			/// <returns>Returns true if the stream is writable.</returns>
			virtual bool					CanWrite()const = 0;
			/// <summary>Test if the stream is seekable.</summary>
			/// <returns>Returns true if the stream is seekable.</returns>
			virtual bool					CanSeek()const = 0;
			/// <summary>Test if the stream is peekable.</summary>
			/// <returns>Returns true if the stream is peekable.</returns>
			virtual bool					CanPeek()const = 0;
			/// <summary>Test if the content of the stream is limited. A writable stream can also be limited, it means that you can only write a limited content to the stream.</summary>
			/// <returns>Returns true if the content of the stream is limited.</returns>
			virtual bool					IsLimited()const = 0;
			/// <summary>Test if the stream is available. For example, if you create a readable [T:vl.stream.FileStream] giving a wrong file name, it will be unavailable.</summary>
			/// <returns>Returns true if the stream is available.</returns>
			virtual bool					IsAvailable()const = 0;
			/// <summary>Close the stream.</summary>
			virtual void					Close() = 0;
			/// <summary>Get the current position in the stream.</summary>
			/// <returns>The position in the stream. Returns -1 if the stream is not available.</returns>
			virtual pos_t					Position()const = 0;
			/// <summary>Get the size of the content..</summary>
			/// <returns>The size of the content. Returns -1 if the size is unknown or the stream is not available.</returns>
			virtual pos_t					Size()const = 0;
			/// <summary>Step forward or backward from the current position. Will throw exception if the stream is not seekable or not available.</summary>
			/// <param name="_size">The length of the step.</param>
			virtual void					Seek(pos_t _size) = 0;
			/// <summary>Step fowward from the beginning. Will throw exception if the stream is not seekable or not available.</summary>
			/// <param name="_size">The length of the step.</param>
			virtual void					SeekFromBegin(pos_t _size) = 0;
			/// <summary>Step backward from the end. Will throw exception if the stream is not seekable or not available.</summary>
			/// <param name="_size">The length of the step.</param>
			virtual void					SeekFromEnd(pos_t _size) = 0;
			/// <summary>Read from the current position and step forward. Will throw exception if the stream is not readable or not available.</summary>
			/// <returns>Returns the actual size of the content that is read. Returns 0 indicates that the stream reaches the end if the stream is limited.</returns>
			/// <param name="_buffer">A buffer to store the content.</param>
			/// <param name="_size">The size of the content that is expected to read.</param>
			virtual vint					Read(void* _buffer, vint _size) = 0;
			/// <summary>Write to the current position and step forward. Will throw exception if the stream is not writable or not available.</summary>
			/// <returns>Returns the actual size of the content that is written. Returns 0 indicates that the stream reaches the end if the stream is limited.</returns>
			/// <param name="_buffer">A buffer storing the content to write.</param>
			/// <param name="_size">The size of the content that is expected to write.</param>
			virtual vint					Write(void* _buffer, vint _size) = 0;
			/// <summary>Read from the current position but not step forward. Will throw exception if the stream is not peekable or not available.</summary>
			/// <returns>Returns the actual size of the content that is read. Returns 0 indicates that the stream reaches the end if the stream is limited.</returns>
			/// <param name="_buffer">A buffer to store the content.</param>
			/// <param name="_size">The size of the content that is expected to peek.</param>
			virtual vint					Peek(void* _buffer, vint _size) = 0;
		};
		
		/// <summary>Encoder interface. This interface defines a writable transformation from one stream to another stream. You can create a [T:vl.stream.EncoderStream] after you have an encoder.</summary>
		class IEncoder : public Interface
		{
		 public:
			/// <summary>Set a target writable stream. The <see cref="Write"/> function will transform the content and write to this tream.</summary>
			/// <param name="_stream">The target writable stream.</param>
			virtual void					Setup(IStream* _stream) = 0;
			/// <summary>Stop the transformation, ensuring all written content is transformed to the target stream.</summary>
			virtual	void					Close() = 0;
			/// <summary>Transform content and write to the target stream. This function may cache something to increase performance, so it cannot expect that all transformed content will be written to the target stream immediately.</summary>
			/// <returns>Returns the actual size of the content before transforming that is written. The content is treated as being written even it is cached and not actually write to the target stream.</returns>
			/// <param name="_buffer">A buffer storing the content to write.</param>
			/// <param name="_size">The size of the content that is expected to write.</param>
			virtual vint					Write(void* _buffer, vint _size) = 0;
		};
		
		/// <summary>Decoder interface. This interface defines a readable transformation from one stream to another stream. You can create a [T:vl.stream.DecoderStream] after you have an decoder.</summary>
		class IDecoder : public Interface
		{
		 public:
			/// <summary>Set a target readable stream. The <see cref="Read"/> function will read from this tream and transform the content.</summary>
			/// <param name="_stream">The target readable stream.</param>
			virtual void					Setup(IStream* _stream) = 0;
			/// <summary>Stop the transformation.</summary>
			virtual	void					Close() = 0;
			/// <summary>Read from the target stream and transform the content.</summary>
			/// <returns>Returns the actual size of the content after transforming that is read.</returns>
			/// <param name="_buffer">A buffer to store the content.</param>
			/// <param name="_size">The size of the content that is expected to read.</param>
			virtual vint					Read(void* _buffer, vint _size) = 0;
		};
	}
}

#endif


/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Stream::Accessor

Classes:
TextReader						：字符串阅读器
TextWriter						：字符串书写器
StreamReader					：流阅读器
StreamWriter					：流书写器
EncoderStream					：编码流
DecoderStream					：解码流
***********************************************************************/

#ifndef VCZH_STREAM_ACCESSOR
#define VCZH_STREAM_ACCESSOR


namespace vl
{
	namespace stream
	{
	
		/***********************************************************************
		流控制器
		***********************************************************************/
		
		/// <summary>Text reader. All line breaks are normalized to CRLF regardless the format in the source.</summary>
		class TextReader : public Object, private NotCopyable
		{
		 public:
			/// <summary>Test does the reader reach the end or not.</summary>
			/// <returns>Returns true if the reader reaches the end.</returns>
			virtual bool				IsEnd() = 0;
			/// <summary>Read a single character.</summary>
			/// <returns>The character.</returns>
			virtual wchar_t				ReadChar() = 0;
			/// <summary>Read a string of a specified size.</summary>
			/// <returns>The string.</returns>
			/// <param name="length">Expected length of the string to read.</param>
			virtual WString				ReadString(vint length);
			/// <summary>Read a string until a line breaks is reached.</summary>
			/// <returns>The string. It does not contain the line break.</returns>
			virtual WString				ReadLine();
			/// <summary>Read everying remain.</summary>
			/// <returns>The string.</returns>
			virtual WString				ReadToEnd();
		};
		
		/// <summary>Text writer.</summary>
		class TextWriter : public Object, private NotCopyable
		{
		 public:
			/// <summary>Write a single character.</summary>
			/// <param name="c">The character to write.</param>
			virtual void				WriteChar(wchar_t c) = 0;
			/// <summary>Write a string.</summary>
			/// <param name="string">Buffer to the string to write.</param>
			/// <param name="charCount">Size of the string in characters not including the zero terminator.</param>
			virtual void				WriteString(const wchar_t* string, vint charCount);
			/// <summary>Write a string.</summary>
			/// <param name="string">Buffer to the zero terminated string to write.</param>
			virtual void				WriteString(const wchar_t* string);
			/// <summary>Write a string.</summary>
			/// <param name="string">The string to write.</param>
			virtual void				WriteString(const WString& string);
			/// <summary>Write a string with a CRLF.</summary>
			/// <param name="string">Buffer to the string to write.</param>
			/// <param name="charCount">Size of the string in characters not including the zero terminator.</param>
			virtual void				WriteLine(const wchar_t* string, vint charCount);
			/// <summary>Write a string with a CRLF.</summary>
			/// <param name="string">Buffer to the zero terminated string to write.</param>
			virtual void				WriteLine(const wchar_t* string);
			/// <summary>Write a string with a CRLF.</summary>
			/// <param name="string">The string to write.</param>
			virtual void				WriteLine(const WString& string);
			
			virtual void				WriteMonospacedEnglishTable(collections::Array<WString>& tableByRow, vint rows, vint columns);
		};
		
		/// <summary>Text reader from a string.</summary>
		class StringReader : public TextReader
		{
		 protected:
			WString						string;
			vint						current;
			bool						lastCallIsReadLine;
			
			void						PrepareIfLastCallIsReadLine();
		 public:
			/// <summary>Create a text reader.</summary>
			/// <param name="_string">The string to read.</param>
			StringReader(const WString& _string);
			
			bool						IsEnd();
			wchar_t						ReadChar();
			WString						ReadString(vint length);
			WString						ReadLine();
			WString						ReadToEnd();
		};
		
		/// <summary>Text reader from a stream.</summary>
		class StreamReader : public TextReader
		{
		 protected:
			IStream*					stream;
		 public:
			/// <summary>Create a text reader.</summary>
			/// <param name="_stream">The stream to read.</param>
			StreamReader(IStream& _stream);
			
			bool						IsEnd();
			wchar_t						ReadChar();
		};
		
		/// <summary>Text writer to a stream.</summary>
		class StreamWriter : public TextWriter
		{
		 protected:
			IStream*					stream;
		 public:
			/// <summary>Create a text writer.</summary>
			/// <param name="_stream">The stream to write.</param>
			StreamWriter(IStream& _stream);
			using TextWriter::WriteString;
			
			void						WriteChar(wchar_t c);
			void						WriteString(const wchar_t* string, vint charCount);
		};
		
		/***********************************************************************
		编码解码
		***********************************************************************/
		
		/// <summary>Encoder stream, a writable stream using an [T:vl.stream.IEncoder] to transform content.</summary>
		class EncoderStream : public virtual IStream
		{
		 protected:
			IStream*					stream;
			IEncoder*					encoder;
			pos_t						position;
			
		 public:
			/// <summary>Create a stream.</summary>
			/// <param name="_stream">The target stream to write.</param>
			/// <param name="_encoder">The encoder to transform content.</param>
			EncoderStream(IStream& _stream, IEncoder& _encoder);
			~EncoderStream();
			
			bool						CanRead()const;
			bool						CanWrite()const;
			bool						CanSeek()const;
			bool						CanPeek()const;
			bool						IsLimited()const;
			bool						IsAvailable()const;
			void						Close();
			pos_t						Position()const;
			pos_t						Size()const;
			void						Seek(pos_t _size);
			void						SeekFromBegin(pos_t _size);
			void						SeekFromEnd(pos_t _size);
			vint						Read(void* _buffer, vint _size);
			vint						Write(void* _buffer, vint _size);
			vint						Peek(void* _buffer, vint _size);
		};
		
		/// <summary>Decoder stream, a readable stream using an [T:vl.stream.IDecoder] to transform content.</summary>
		class DecoderStream : public virtual IStream
		{
		 protected:
			IStream*					stream;
			IDecoder*					decoder;
			pos_t						position;
			
		 public:
			/// <summary>Create a stream.</summary>
			/// <param name="_stream">The target stream to read.</param>
			/// <param name="_decoder">The decoder to transform content.</param>
			DecoderStream(IStream& _stream, IDecoder& _decoder);
			~DecoderStream();
			
			bool						CanRead()const;
			bool						CanWrite()const;
			bool						CanSeek()const;
			bool						CanPeek()const;
			bool						IsLimited()const;
			bool						IsAvailable()const;
			void						Close();
			pos_t						Position()const;
			pos_t						Size()const;
			void						Seek(pos_t _size);
			void						SeekFromBegin(pos_t _size);
			void						SeekFromEnd(pos_t _size);
			vint						Read(void* _buffer, vint _size);
			vint						Write(void* _buffer, vint _size);
			vint						Peek(void* _buffer, vint _size);
		};
	}
}

#endif


/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Stream::BroadcastStream

Interfaces:
BroadcastStream					：广播流
***********************************************************************/

#ifndef VCZH_STREAM_BROADCASTSTREAM
#define VCZH_STREAM_BROADCASTSTREAM


namespace vl
{
	namespace stream
	{
		/// <summary>A writable stream that copy written content to multiple target streams.</summary>
		class BroadcastStream : public Object, public virtual IStream
		{
			typedef collections::List<IStream*>		StreamList;
		 protected:
			bool					closed;
			pos_t					position;
			StreamList				streams;
		 public:
			/// <summary>Create a strema.</summary>
			BroadcastStream();
			~BroadcastStream();
			
			/// <summary>Get the list of target streams. You can add streams to this list, or remove streams from this list.</summary>
			/// <returns>The list of target streams.</returns>
			StreamList&				Targets();
			bool					CanRead()const;
			bool					CanWrite()const;
			bool					CanSeek()const;
			bool					CanPeek()const;
			bool					IsLimited()const;
			bool					IsAvailable()const;
			void					Close();
			pos_t					Position()const;
			pos_t					Size()const;
			void					Seek(pos_t _size);
			void					SeekFromBegin(pos_t _size);
			void					SeekFromEnd(pos_t _size);
			vint					Read(void* _buffer, vint _size);
			vint					Write(void* _buffer, vint _size);
			vint					Peek(void* _buffer, vint _size);
		};
	}
}

#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Stream::CacheStream

Interfaces:
CacheStream						：缓冲流
***********************************************************************/

#ifndef VCZH_STREAM_CACHESTREAM
#define VCZH_STREAM_CACHESTREAM

// #include "Interfaces.h"

namespace vl
{
	namespace stream
	{
		/// <summary>
		/// A cache stream. Features (readable, writable, seekable, peekable) are enabled according to the target stream.
		/// When you read from the cache strema, it will read a specified size of content from the target stream first and cache, reducing the numbers of operations on the target stream.
		/// When you write to the cache strema, it will save them to a buffer, and write to the target stream until the buffer reaches a specified size, reducing the numbers of operations on the target stream.
		/// </summary>
		class CacheStream : public Object, public virtual IStream
		{
		 protected:
			IStream*				target;
			vint					block;
			pos_t					start;
			pos_t					position;
			
			char*					buffer;
			vint					dirtyStart;
			vint					dirtyLength;
			vint					availableLength;
			pos_t					operatedSize;
			
			void					Flush();
			void					Load(pos_t _position);
			vint					InternalRead(void* _buffer, vint _size);
			vint					InternalWrite(void* _buffer, vint _size);
		 public:
			/// <summary>Create a cache stream using a target stream.</summary>
			/// <param name="_target">The target stream.</param>
			/// <param name="_block">Size of the cache.</param>
			CacheStream(IStream& _target, vint _block = 65536);
			~CacheStream();
			
			bool					CanRead()const;
			bool					CanWrite()const;
			bool					CanSeek()const;
			bool					CanPeek()const;
			bool					IsLimited()const;
			bool					IsAvailable()const;
			void					Close();
			pos_t					Position()const;
			pos_t					Size()const;
			void					Seek(pos_t _size);
			void					SeekFromBegin(pos_t _size);
			void					SeekFromEnd(pos_t _size);
			vint					Read(void* _buffer, vint _size);
			vint					Write(void* _buffer, vint _size);
			vint					Peek(void* _buffer, vint _size);
		};
	}
}

#endif


/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Stream::MemoryStream

Interfaces:
MemoryStream					：内存流
***********************************************************************/

#ifndef VCZH_STREAM_MEMORYSTREAM
#define VCZH_STREAM_MEMORYSTREAM

// #include "Interfaces.h"

namespace vl
{
	namespace stream
	{
		/// <summary>A readable, writable, seekable and peekable stream that stores everything in memory.</summary>
		class MemoryStream : public Object, public virtual IStream
		{
		 protected:
			vint					block;
			char*					buffer;
			vint					size;
			vint					position;
			vint					capacity;
			
			void					PrepareSpace(vint totalSpace);
		 public:
			/// <summary>Create a stream.</summary>
			/// <param name="_block">Size for each allocation. The stream will only allocate new memory of size "_block" when it reaches the end and has to extend.</param>
			MemoryStream(vint _block = 65536);
			~MemoryStream();
			
			bool					CanRead()const;
			bool					CanWrite()const;
			bool					CanSeek()const;
			bool					CanPeek()const;
			bool					IsLimited()const;
			bool					IsAvailable()const;
			void					Close();
			pos_t					Position()const;
			pos_t					Size()const;
			void					Seek(pos_t _size);
			void					SeekFromBegin(pos_t _size);
			void					SeekFromEnd(pos_t _size);
			vint					Read(void* _buffer, vint _size);
			vint					Write(void* _buffer, vint _size);
			vint					Peek(void* _buffer, vint _size);
			void*					GetInternalBuffer();
		};
	}
}

#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Stream::MemoryWrapperStream

Interfaces:
MemoryWrapperStream				：内存代理流
***********************************************************************/

#ifndef VCZH_STREAM_MEMORYWRAPPERSTREAM
#define VCZH_STREAM_MEMORYWRAPPERSTREAM

// #include "Interfaces.h"

namespace vl
{
	namespace stream
	{
		/// <summary>A readable, writable, seekable and peekable stream that operates a buffer.</summary>
		class MemoryWrapperStream : public Object, public virtual IStream
		{
		 protected:
			char*					buffer;
			vint						size;
			vint						position;
		 public:
			/// <summary>Create a stream.</summary>
			/// <param name="_buffer">The buffer to operate.</param>
			/// <param name="_size">Size of the buffer.</param>
			MemoryWrapperStream(void* _buffer, vint _size);
			~MemoryWrapperStream();
			
			bool					CanRead()const;
			bool					CanWrite()const;
			bool					CanSeek()const;
			bool					CanPeek()const;
			bool					IsLimited()const;
			bool					IsAvailable()const;
			void					Close();
			pos_t					Position()const;
			pos_t					Size()const;
			void					Seek(pos_t _size);
			void					SeekFromBegin(pos_t _size);
			void					SeekFromEnd(pos_t _size);
			vint					Read(void* _buffer, vint _size);
			vint					Write(void* _buffer, vint _size);
			vint					Peek(void* _buffer, vint _size);
		};
	}
}

#endif


/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Stream::CharFormat

Classes:
CharEncoder									：字符串编码器基类
CharDecoder									：字符串解码器基类
MbcsEncoder									：Mbcs编码器
MbcsDecoder									：Mbcs解码器
Utf16Encoder								：Utf16编码器
Utf16Decoder								：Utf16解码器
Utf16BEEncoder								：Utf16 Big Endian编码器
Utf16BEDecoder								：Utf16 Big Endian解码器
Utf8Encoder									：Utf8编码器
Utf8Decoder									：Utf8解码器
BomEncoder									：BOM相关编码器
BomDecoder									：BOM相关解码器
***********************************************************************/

#ifndef VCZH_STREAM_CHARFORMAT
#define VCZH_STREAM_CHARFORMAT

// #include "Interfaces.h"
// #include "MemoryStream.h"
// #include "MemoryWrapperStream.h"

namespace vl
{
	namespace stream
	{
	
		/*编码资料
		UCS-4和UTF-8的对应关系:
		U-00000000 - U-0000007F:  0xxxxxxx
		U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
		U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
		U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		U-04000000 - U-7FFFFFFF:  1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		BOM:
		FFFE	=Unicode			(vceUtf16)
		FEFF	=Unicode Big Endian	(vceUtf16_be)
		EFBBBF	=UTF-8				(vceUtf8)
		other	=MBCS(GBK)			(vceMbcs)
		*/
		
		/***********************************************************************
		字符串编码解码基类
		***********************************************************************/
		
		/// <summary>Base type of all character encoder.</summary>
		class CharEncoder : public Object, public IEncoder
		{
		 protected:
			IStream*						stream;
			vuint8_t						cacheBuffer[sizeof(wchar_t)];
			vint							cacheSize;
			
			virtual vint					WriteString(wchar_t* _buffer, vint chars) = 0;
		 public:
			CharEncoder();
			
			void							Setup(IStream* _stream);
			void							Close();
			vint							Write(void* _buffer, vint _size);
		};
		
		/// <summary>Base type of all character decoder.</summary>
		class CharDecoder : public Object, public IDecoder
		{
		 protected:
			IStream*						stream;
			vuint8_t						cacheBuffer[sizeof(wchar_t)];
			vint							cacheSize;
			
			virtual vint					ReadString(wchar_t* _buffer, vint chars) = 0;
		 public:
			CharDecoder();
			
			void							Setup(IStream* _stream);
			void							Close();
			vint							Read(void* _buffer, vint _size);
		};
		
		/***********************************************************************
		Mbcs
		***********************************************************************/
		
		/// <summary>Encoder to transform text in a local code page from wchar_t.</summary>
		class MbcsEncoder : public CharEncoder
		{
		 protected:
			vint							WriteString(wchar_t* _buffer, vint chars);
		};
		
		/// <summary>Encoder to transform text in a local code page to wchar_t.</summary>
		class MbcsDecoder : public CharDecoder
		{
		 protected:
			vint							ReadString(wchar_t* _buffer, vint chars);
		};
		
		/***********************************************************************
		Utf-16
		***********************************************************************/
		
		/// <summary>Encoder to transform UTF-16 text from wchar_t.</summary>
		class Utf16Encoder : public CharEncoder
		{
		 protected:
			vint							WriteString(wchar_t* _buffer, vint chars);
		};
		
		/// <summary>Decoder to transform UTF-16 text to wchar_t.</summary>
		class Utf16Decoder : public CharDecoder
		{
		 protected:
			vint							ReadString(wchar_t* _buffer, vint chars);
		};
		
		/***********************************************************************
		Utf-16-be
		***********************************************************************/
		
		/// <summary>Encoder to transform big endian UTF-16 text from wchar_t.</summary>
		class Utf16BEEncoder : public CharEncoder
		{
		 protected:
			vint							WriteString(wchar_t* _buffer, vint chars);
		};
		
		/// <summary>Decoder to transform big endian UTF-16 text to wchar_t.</summary>
		class Utf16BEDecoder : public CharDecoder
		{
		 protected:
			vint							ReadString(wchar_t* _buffer, vint chars);
		};
		
		/***********************************************************************
		Utf-8
		***********************************************************************/
		
		/// <summary>Encoder to transform UTF-8 text from wchar_t.</summary>
		class Utf8Encoder : public CharEncoder
		{
		 protected:
			vint							WriteString(wchar_t* _buffer, vint chars);
		};
		
		/// <summary>Decoder to transform UTF-8 text to wchar_t.</summary>
		class Utf8Decoder : public CharDecoder
		{
		 protected:
#if defined VCZH_MSVC
			wchar_t							cache;
			bool							cacheAvailable;
#endif
			vint							ReadString(wchar_t* _buffer, vint chars);
		 public:
			Utf8Decoder();
		};
		
		/***********************************************************************
		Bom
		***********************************************************************/
		
		/// <summary>Encoder to transform text from wchar_t. A BOM will be added at the beginning.</summary>
		class BomEncoder : public Object, public IEncoder
		{
		 public:
			/// <summary>Text encoding.</summary>
			enum Encoding
			{
				/// <summary>Multi-bytes character string.</summary>
				Mbcs,
				/// <summary>UTF-8.</summary>
				Utf8,
				/// <summary>UTF-16.</summary>
				Utf16,
				/// <summary>Big endian UTF-16.</summary>
				Utf16BE
			};
		 protected:
			Encoding						encoding;
			IEncoder*						encoder;
		 public:
			/// <summary>Create an encoder.</summary>
			/// <param name="_encoding">Specified encoding.</param>
			BomEncoder(Encoding _encoding);
			~BomEncoder();
			
			void							Setup(IStream* _stream);
			void							Close();
			vint							Write(void* _buffer, vint _size);
		};
		
		/// <summary>Decoder to transform text to wchar_t. This decoder depends on the BOM information at the beginning to decide the format of the input.</summary>
		class BomDecoder : public Object, public IDecoder
		{
		 private:
			class BomStream : public Object, public IStream
			{
			 protected:
				IStream*					stream;
				char						bom[3];
				vint						bomLength;
				vint						bomPosition;
			 public:
				BomStream(IStream* _stream, char* _bom, vint _bomLength);
				
				bool						CanRead()const;
				bool						CanWrite()const;
				bool						CanSeek()const;
				bool						CanPeek()const;
				bool						IsLimited()const;
				bool						IsAvailable()const;
				void						Close();
				pos_t						Position()const;
				pos_t						Size()const;
				void						Seek(pos_t _size);
				void						SeekFromBegin(pos_t _size);
				void						SeekFromEnd(pos_t _size);
				vint						Read(void* _buffer, vint _size);
				vint						Write(void* _buffer, vint _size);
				vint						Peek(void* _buffer, vint _size);
			};
		 protected:
			IDecoder*						decoder;
			IStream*						stream;
			
		 public:
			/// <summary>Create an decoder.</summary>
			BomDecoder();
			~BomDecoder();
			
			void							Setup(IStream* _stream);
			void							Close();
			vint							Read(void* _buffer, vint _size);
		};
		
		/***********************************************************************
		Encoding Test
		***********************************************************************/
		
		/// <summary>Guess the text encoding in a buffer.</summary>
		/// <param name="buffer">The buffer to guess.</param>
		/// <param name="size">Size of the buffer in bytes.</param>
		/// <param name="encoding">Returns the most possible encoding.</param>
		/// <param name="containsBom">Returns true if the BOM information is at the beginning of the buffer.</param>
		extern void							TestEncoding(unsigned char* buffer, vint size, BomEncoder::Encoding& encoding, bool& containsBom);
		
		/***********************************************************************
		Serialization
		***********************************************************************/
		
		namespace internal
		{
			template<typename T>
			struct Reader
			{
				stream::IStream&			input;
				T							context;
				
				Reader(stream::IStream& _input)
					: input(_input)
					, context(NULL)
				{
				}
			};
			
			template<typename T>
			struct Writer
			{
				stream::IStream&			output;
				T							context;
				
				Writer(stream::IStream& _output)
					: output(_output)
					, context(NULL)
				{
				}
			};
			
			// 			using ContextFreeReader = Reader<void*>;
			// 			using ContextFreeWriter = Writer<void*>;
			typedef Reader<void*> ContextFreeReader;
			typedef Writer<void*> ContextFreeWriter;
			
			template<typename T>
			struct Serialization
			{
				template<typename TIO>
				static void IO(TIO& io, T& value);
			};
			
			template<typename TValue, typename TContext>
			Reader<TContext>& operator<<(Reader<TContext>& reader, TValue& value)
			{
				Serialization<TValue>::IO(reader, value);
				return reader;
			}
			
			template<typename TValue, typename TContext>
			Writer<TContext>& operator<<(Writer<TContext>& writer, TValue& value)
			{
				Serialization<TValue>::IO(writer, value);
				return writer;
			}
			
			//---------------------------------------------
			
			template<>
			struct Serialization<vint64_t>
			{
				template<typename TContext>
				static void IO(Reader<TContext>& reader, vint64_t& value)
				{
					if (reader.input.Read(&value, sizeof(value)) != sizeof(value))
					{
						CHECK_FAIL(L"Deserialization failed.");
					}
				}
				
				template<typename TContext>
				static void IO(Writer<TContext>& writer, vint64_t& value)
				{
					if (writer.output.Write(&value, sizeof(value)) != sizeof(value))
					{
						CHECK_FAIL(L"Serialization failed.");
					}
				}
			};
			
			template<>
			struct Serialization<vint32_t>
			{
				template<typename TContext>
				static void IO(Reader<TContext>& reader, vint32_t& value)
				{
					vint64_t v = 0;
					Serialization<vint64_t>::IO(reader, v);
					value = (vint32_t)v;
				}
				
				template<typename TContext>
				static void IO(Writer<TContext>& writer, vint32_t& value)
				{
					vint64_t v = (vint64_t)value;
					Serialization<vint64_t>::IO(writer, v);
				}
			};
			
			template<>
			struct Serialization<bool>
			{
				template<typename TContext>
				static void IO(Reader<TContext>& reader, bool& value)
				{
					vint8_t v = 0;
					
					if (reader.input.Read(&v, sizeof(v)) != sizeof(v))
					{
						CHECK_FAIL(L"Deserialization failed.");
					}
					else
					{
						value = v == -1;
					}
				}
				
				template<typename TContext>
				static void IO(Writer<TContext>& writer, bool& value)
				{
					vint8_t v = value ? -1 : 0;
					
					if (writer.output.Write(&v, sizeof(v)) != sizeof(v))
					{
						CHECK_FAIL(L"Serialization failed.");
					}
				}
			};
			
			template<typename T>
			struct Serialization<Ptr<T>>
			{
				template<typename TContext>
				static void IO(Reader<TContext>& reader, Ptr<T>& value)
				{
					bool notNull = false;
					reader << notNull;
					
					if (notNull)
					{
						value = new T;
						Serialization<T>::IO(reader, *value.Obj());
					}
					else
					{
						value = 0;
					}
				}
				
				template<typename TContext>
				static void IO(Writer<TContext>& writer, Ptr<T>& value)
				{
					bool notNull = value;
					writer << notNull;
					
					if (notNull)
					{
						Serialization<T>::IO(writer, *value.Obj());
					}
				}
			};
			
			template<typename T>
			struct Serialization<Nullable<T>>
			{
				template<typename TContext>
				static void IO(Reader<TContext>& reader, Nullable<T>& value)
				{
					bool notNull = false;
					reader << notNull;
					
					if (notNull)
					{
						T data;
						Serialization<T>::IO(reader, data);
						value = Nullable<T>(data);
					}
					else
					{
						value = Nullable<T>();
					}
				}
				
				template<typename TContext>
				static void IO(Writer<TContext>& writer, Nullable<T>& value)
				{
					bool notNull = value;
					writer << notNull;
					
					if (notNull)
					{
						T data = value.Value();
						Serialization<T>::IO(writer, data);
					}
				}
			};
			
			template<>
			struct Serialization<WString>
			{
				template<typename TContext>
				static void IO(Reader<TContext>& reader, WString& value)
				{
					vint count = -1;
					reader << count;
					
					if (count > 0)
					{
						MemoryStream stream;
						reader << (IStream&)stream;
						Utf8Decoder decoder;
						decoder.Setup(&stream);
						
						collections::Array<wchar_t> stringBuffer(count + 1);
						vint stringSize = decoder.Read(&stringBuffer[0], count * sizeof(wchar_t));
						stringBuffer[stringSize / sizeof(wchar_t)] = 0;
						
						value = &stringBuffer[0];
					}
					else
					{
						value = L"";
					}
				}
				
				template<typename TContext>
				static void IO(Writer<TContext>& writer, WString& value)
				{
					vint count = value.Length();
					writer << count;
					
					if (count > 0)
					{
						MemoryStream stream;
						{
							Utf8Encoder encoder;
							encoder.Setup(&stream);
							encoder.Write((void*)value.Buffer(), count * sizeof(wchar_t));
						}
						writer << (IStream&)stream;
					}
				}
			};
			
			template<typename T>
			struct Serialization<collections::List<T>>
			{
				template<typename TContext>
				static void IO(Reader<TContext>& reader, collections::List<T>& value)
				{
					vint32_t count = -1;
					reader << count;
					value.Clear();
					
					for (vint i = 0; i < count; i++)
					{
						T t;
						reader << t;
						value.Add(t);
					}
				}
				
				template<typename TContext>
				static void IO(Writer<TContext>& writer, collections::List<T>& value)
				{
					vint32_t count = (vint32_t)value.Count();
					writer << count;
					
					for (vint i = 0; i < count; i++)
					{
						writer << value[i];
					}
				}
			};
			
			template<typename T>
			struct Serialization<collections::Array<T>>
			{
				template<typename TContext>
				static void IO(Reader<TContext>& reader, collections::Array<T>& value)
				{
					vint32_t count = -1;
					reader << count;
					value.Resize(count);
					
					for (vint i = 0; i < count; i++)
					{
						reader << value[i];
					}
				}
				
				template<typename TContext>
				static void IO(Writer<TContext>& writer, collections::Array<T>& value)
				{
					vint32_t count = (vint32_t)value.Count();
					writer << count;
					
					for (vint i = 0; i < count; i++)
					{
						writer << value[i];
					}
				}
			};
			
			template<typename K, typename V>
			struct Serialization<collections::Dictionary<K, V>>
			{
				template<typename TContext>
				static void IO(Reader<TContext>& reader, collections::Dictionary<K, V>& value)
				{
					vint32_t count = -1;
					reader << count;
					value.Clear();
					
					for (vint i = 0; i < count; i++)
					{
						K k;
						V v;
						reader << k << v;
						value.Add(k, v);
					}
				}
				
				template<typename TContext>
				static void IO(Writer<TContext>& writer, collections::Dictionary<K, V>& value)
				{
					vint32_t count = (vint32_t)value.Count();
					writer << count;
					
					for (vint i = 0; i < count; i++)
					{
						K k = value.Keys()[i];
						V v = value.Values()[i];
						writer << k << v;
					}
				}
			};
			
			template<typename K, typename V>
			struct Serialization<collections::Group<K, V>>
			{
				template<typename TContext>
				static void IO(Reader<TContext>& reader, collections::Group<K, V>& value)
				{
					vint32_t count = -1;
					reader << count;
					value.Clear();
					
					for (vint i = 0; i < count; i++)
					{
						K k;
						collections::List<V> v;
						reader << k << v;
						
						for (vint j = 0; j < v.Count(); j++)
						{
							value.Add(k, v[j]);
						}
					}
				}
				
				template<typename TContext>
				static void IO(Writer<TContext>& writer, collections::Group<K, V>& value)
				{
					vint32_t count = (vint32_t)value.Count();
					writer << count;
					
					for (vint i = 0; i < count; i++)
					{
						K k = value.Keys()[i];
						collections::List<V>& v = const_cast<collections::List<V>&>(value.GetByIndex(i));
						writer << k << v;
					}
				}
			};
			
			template<>
			struct Serialization<stream::IStream>
			{
				template<typename TContext>
				static void IO(Reader<TContext>& reader, stream::IStream& value)
				{
					vint32_t count = 0;
					reader.input.Read(&count, sizeof(count));
					
					if (count > 0)
					{
						vint length = 0;
						collections::Array<vuint8_t> buffer(count);
						value.SeekFromBegin(0);
						length = reader.input.Read(&buffer[0], count);
						
						if (length != count)
						{
							CHECK_FAIL(L"Deserialization failed.");
						}
						
						length = value.Write(&buffer[0], count);
						
						if (length != count)
						{
							CHECK_FAIL(L"Deserialization failed.");
						}
						
						value.SeekFromBegin(0);
					}
				}
				
				template<typename TContext>
				static void IO(Writer<TContext>& writer, stream::IStream& value)
				{
					vint32_t count = (vint32_t)value.Size();
					writer.output.Write(&count, sizeof(count));
					
					if (count > 0)
					{
						vint length = 0;
						collections::Array<vuint8_t> buffer(count);
						value.SeekFromBegin(0);
						length = value.Read(&buffer[0], count);
						
						if (length != count)
						{
							CHECK_FAIL(L"Serialization failed.");
						}
						
						length = writer.output.Write(&buffer[0], count);
						
						if (length != count)
						{
							CHECK_FAIL(L"Serialization failed.");
						}
						
						value.SeekFromBegin(0);
					}
				}
			};
			
			//---------------------------------------------
			
#define BEGIN_SERIALIZATION(TYPE)\
	template<>\
	struct Serialization<TYPE>\
	{\
		template<typename TIO>\
		static void IO(TIO& op, TYPE& value)\
		{\
			op\
			
#define SERIALIZE(FIELD)\
	    << value.FIELD\
			
#define END_SERIALIZATION\
	;\
}\
};\
			
#define SERIALIZE_ENUM(TYPE)\
	template<>\
	struct Serialization<TYPE>\
	{\
		template<typename TContext>\
		static void IO(Reader<TContext>& reader, TYPE& value)\
		{\
			vint32_t v = 0;\
			Serialization<vint32_t>::IO(reader, v);\
			value = (TYPE)v;\
		}\
		template<typename TContext>\
		static void IO(Writer<TContext>& writer, TYPE& value)\
		{\
			vint32_t v = (vint32_t)value;\
			Serialization<vint32_t>::IO(writer, v);\
		}\
	};\
			
		}
	}
}

#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Stream::CharFormat

Classes:
***********************************************************************/

#ifndef VCZH_STREAM_COMPRESSIONSTREAM
#define VCZH_STREAM_COMPRESSIONSTREAM

// #include "Interfaces.h"

namespace vl
{
	namespace stream
	{
	
		/***********************************************************************
		Compression
		***********************************************************************/
		
		namespace lzw
		{
			static const vint						BufferSize = 1024;
			static const vint						MaxDictionarySize = 1 << 24;
			
			struct Code
			{
				Code() : byte(0), code(-1), parent(NULL), size(0)
				{
				}
				typedef collections::PushOnlyAllocator<Code>			CodeAllocator;
				typedef collections::ByteObjectMap<Code>::Allocator		MapAllocator;
				
				vuint8_t							byte/* = 0*/;
				vint								code /*= -1*/;
				Code*								parent /*= 0*/;
				vint								size /*= 0*/;
				collections::ByteObjectMap<Code>	children;
			};
		}
		
		class LzwBase : public Object
		{
		 protected:
			lzw::Code::CodeAllocator				codeAllocator;
			lzw::Code::MapAllocator					mapAllocator;
			lzw::Code*								root;
			vint									eofIndex /*= -1*/;
			vint									nextIndex /*= 0*/;
			vint									indexBits /*= 1*/;
			
			void									UpdateIndexBits();
			lzw::Code*								CreateCode(lzw::Code* parent, vuint8_t byte);
			
			LzwBase();
			LzwBase(bool(&existingBytes)[256]);
			~LzwBase();
		};
		
		/// <summary>An encoder to compress using Lzw algorithm.</summary>
		class LzwEncoder : public LzwBase, public IEncoder
		{
		 protected:
			IStream*								stream /*= 0*/;
			
			vuint8_t								buffer[lzw::BufferSize];
			vint									bufferUsedBits/* = 0*/;
			lzw::Code*								prefix;
			
			void									Flush();
			void									WriteNumber(vint number, vint bitSize);
		 public:
			/// <summary>Create an encoder.</summary>
			LzwEncoder();
			/// <summary>Create an encoder and tell it which byte will never appear in the data before compression.</summary>
			/// <param name="existingBytes">An array to tell the encoder which byte will never appear in the data before compression.</param>
			LzwEncoder(bool(&existingBytes)[256]);
			~LzwEncoder();
			
			void									Setup(IStream* _stream)override;
			void									Close()override;
			vint									Write(void* _buffer, vint _size)override;
		};
		
		/// <summary>An decoder to decompress using Lzw algorithm.</summary>
		class LzwDecoder : public LzwBase, public IDecoder
		{
		 protected:
			IStream*								stream /*= 0*/;
			collections::List<lzw::Code*>			dictionary;
			lzw::Code*								lastCode/* = 0*/;
			
			vuint8_t								inputBuffer[lzw::BufferSize];
			vint									inputBufferSize /*= 0*/;
			vint									inputBufferUsedBits /*= 0*/;
			
			collections::Array<vuint8_t>			outputBuffer;
			vint									outputBufferSize/* = 0*/;
			vint									outputBufferUsedBytes /*= 0*/;
			
			bool									ReadNumber(vint& number, vint bitSize);
			void									PrepareOutputBuffer(vint size);
			void									ExpandCodeToOutputBuffer(lzw::Code* code);
		 public:
			/// <summary>Create an decoder.</summary>
			LzwDecoder();
			/// <summary>Create an decoder and tell it which byte will never appear in the data before compression.</summary>
			/// <param name="existingBytes">An array to tell the encoder which byte will never appear in the data before compression.</param>
			LzwDecoder(bool(&existingBytes)[256]);
			~LzwDecoder();
			
			void									Setup(IStream* _stream)override;
			void									Close()override;
			vint									Read(void* _buffer, vint _size)override;
		};
	}
}

#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Stream::FileStream

Interfaces:
FileStream						：文件流
***********************************************************************/

#ifndef VCZH_STREAM_FILESTREAM
#define VCZH_STREAM_FILESTREAM

#include <stdio.h>
// #include "Interfaces.h"
// #include "../String.h"

namespace vl
{
	namespace stream
	{
		/// <summary>A file stream. It is readable when you use [F:vl.stream.FileStream.AccessRight.ReadOnly] or [F:vl.stream.FileStream.AccessRight.ReadWrite] to create the stream. It is writable when you use [F:vl.stream.FileStream.AccessRight.WriteOnly] or [F:vl.stream.FileStream.AccessRight.ReadWrite] to create the stream.</summary>
		class FileStream : public Object, public virtual IStream
		{
		 public:
			/// <summary>Access to the file.</summary>
			enum AccessRight
			{
				/// <summary>The file is opened to read.</summary>
				ReadOnly,
				/// <summary>The file is opened to write.</summary>
				WriteOnly,
				/// <summary>The file is opened to both read and write.</summary>
				ReadWrite
			};
		 protected:
			AccessRight				accessRight;
			FILE*					file;
		 public:
			/// <summary>Create a stream.</summary>
			/// <param name="fileName">File to operate.</param>
			/// <param name="_accessRight">Operations want to perform on the file.</param>
			FileStream(const WString& fileName, AccessRight _accessRight);
			~FileStream();
			
			bool					CanRead()const;
			bool					CanWrite()const;
			bool					CanSeek()const;
			bool					CanPeek()const;
			bool					IsLimited()const;
			bool					IsAvailable()const;
			void					Close();
			pos_t					Position()const;
			pos_t					Size()const;
			void					Seek(pos_t _size);
			void					SeekFromBegin(pos_t _size);
			void					SeekFromEnd(pos_t _size);
			vint					Read(void* _buffer, vint _size);
			vint					Write(void* _buffer, vint _size);
			vint					Peek(void* _buffer, vint _size);
		};
	}
}

#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Stream::RecorderStream

Interfaces:
RecorderStream					：备份流
***********************************************************************/

#ifndef VCZH_STREAM_RECORDERSTREAM
#define VCZH_STREAM_RECORDERSTREAM

// #include "Interfaces.h"

namespace vl
{
	namespace stream
	{
		/// <summary>A readable stream that, read from an stream, and write everything that is read to another stream.</summary>
		class RecorderStream : public Object, public virtual IStream
		{
		 protected:
			IStream*				in;
			IStream*				out;
		 public:
			/// <summary>Create a stream.</summary>
			/// <param name="_in">The stream to read.</param>
			/// <param name="_out">The stream to write what is read from "_in".</param>
			RecorderStream(IStream& _in, IStream& _out);
			~RecorderStream();
			
			bool					CanRead()const;
			bool					CanWrite()const;
			bool					CanSeek()const;
			bool					CanPeek()const;
			bool					IsLimited()const;
			bool					IsAvailable()const;
			void					Close();
			pos_t					Position()const;
			pos_t					Size()const;
			void					Seek(pos_t _size);
			void					SeekFromBegin(pos_t _size);
			void					SeekFromEnd(pos_t _size);
			vint					Read(void* _buffer, vint _size);
			vint					Write(void* _buffer, vint _size);
			vint					Peek(void* _buffer, vint _size);
		};
	}
}

#endif


#ifndef FILEPATH
#define FILEPATH
// #include "../Basic.h"
// #include "../String.h"
// #include "../Collections/List.h"
// #include "../Stream/CharFormat.h"

namespace vl
{

	namespace filesystem
	{
		/// <summary>A type representing a file path.</summary>
		class FilePath : public Object
		{
		 protected:
			WString						fullPath;
			
			void						Initialize();
			
			static void					GetPathComponents(WString path, collections::List<WString>& components);
			static WString				ComponentsToPath(const collections::List<WString>& components);
		 public:
#if defined VCZH_MSVC
			static const wchar_t		Delimiter = L'\\';
#elif defined VCZH_GCC
			static const wchar_t		Delimiter = L'/';
#endif
			
			/// <summary>Create a root path.</summary>
			FilePath();
			/// <summary>Create a file path.</summary>
			/// <param name="_filePath">Content of the file path. If it is a relative path, it will be converted to an absolute path.</param>
			FilePath(const WString& _filePath);
			/// <summary>Create a file path.</summary>
			/// <param name="_filePath">Content of the file path. If it is a relative path, it will be converted to an absolute path.</param>
			FilePath(const wchar_t* _filePath);
			/// <summary>Copy a file path.</summary>
			/// <param name="_filePath">The file path to copy.</param>
			FilePath(const FilePath& _filePath);
			~FilePath();
			
		 public:
			static FilePath CurrentPath();
			static FilePath TheAppPath();
			static FilePath TempPath();
		 public:
			static vint					Compare(const FilePath& a, const FilePath& b);
			bool						operator==(const FilePath& filePath)const
			{
				return Compare(*this, filePath) == 0;
			}
			bool						operator!=(const FilePath& filePath)const
			{
				return Compare(*this, filePath) != 0;
			}
			bool						operator< (const FilePath& filePath)const
			{
				return Compare(*this, filePath) < 0;
			}
			bool						operator<=(const FilePath& filePath)const
			{
				return Compare(*this, filePath) <= 0;
			}
			bool						operator> (const FilePath& filePath)const
			{
				return Compare(*this, filePath) > 0;
			}
			bool						operator>=(const FilePath& filePath)const
			{
				return Compare(*this, filePath) >= 0;
			}
			
			/// <summary>Concat an absolute path and a relative path.</summary>
			/// <returns>The result absolute path.</returns>
			/// <param name="relativePath">The relative path to concat.</param>
			FilePath					operator/(const WString& relativePath)const;
			
			/// <summary>Test if the file path is a file.</summary>
			/// <returns>Returns true if the file path is a file.</returns>
			bool						IsFile()const;
			/// <summary>Test if the file path is a folder.</summary>
			/// <returns>Returns true if the file path is a folder.</returns>
			bool						IsFolder()const;
			/// <summary>Test if the file path is a the root of all file system objects.</summary>
			/// <returns>Returns true if the file path is the root of all file system objects.</returns>
			bool						IsRoot()const;
			
			/// <summary>Get the last piece of names in the file path.</summary>
			/// <returns>The last piece of names in the file path.</returns>
			WString						GetName()const;
			/// <summary>Get the containing folder of this file path.</summary>
			/// <returns>The containing folder.</returns>
			FilePath					GetFolder()const;
			/// <summary>Get the content of the file path.</summary>
			/// <returns>The content of the file path.</returns>
			WString						GetFullPath()const;
			/// <summary>Calculate the relative path using a referencing folder.</summary>
			/// <returns>The relative path.</returns>
			/// <param name="_filePath">The referencing folder.</param>
			WString						GetRelativePathFor(const FilePath& _filePath);
			
		};
		
	}
	
}


#endif

#ifndef NICE_FILE
#define NICE_FILE
// #include "../Basic.h"
// #include "../String.h"
// #include "../Collections/List.h"
// #include "../Stream/CharFormat.h"
// #include "FilePath.h"

namespace vl
{
	namespace filesystem
	{
		/// <summary>Representing a file reference.</summary>
		class File : public Object
		{
		 private:
			FilePath					filePath;
			
		 public:
			/// <summary>Create an empty reference.</summary>
			File();
			/// <summary>Create a reference to a specified file.</summary>
			/// <param name="_filePath">The specified file.</param>
			File(const FilePath& _filePath);
			~File();
			
			/// <summary>Get the file path of the file.</summary>
			/// <returns>The file path.</returns>
			const FilePath&				GetFilePath()const;
			
			/// <summary>Get the content of the file as text with encoding testing.</summary>
			/// <returns>The content of the file.</returns>
			/// <returns>Returns false if this operation succeeded.</returns>
			/// <param name="text">The content of the file.</param>
			/// <param name="encoding">The encoding.</param>
			/// <param name="bom">True if there is BOM.</param>
			bool						ReadAllTextWithEncodingTesting(WString& text, stream::BomEncoder::Encoding& encoding, bool& containsBom);
			/// <summary>Get the content of the file as text.</summary>
			/// <returns>The content of the file.</returns>
			WString						ReadAllTextByBom()const;
			/// <summary>Get the content of the file as text.</summary>
			/// <returns>Returns false if this operation succeeded.</returns>
			/// <param name="text">The content of the file.</param>
			bool						ReadAllTextByBom(WString& text)const;
			/// <summary>Get the content of the file as text.</summary>
			/// <returns>Returns false if this operation succeeded.</returns>
			/// <param name="lines">The content of the file.</param>
			bool						ReadAllLinesByBom(collections::List<WString>& lines)const;
			
			/// <summary>Write text to the file.</summary>
			/// <returns>Returns false if this operation succeeded.</returns>
			/// <param name="text">The text to write.</param>
			/// <param name="bom">Set to true to add a corresponding BOM at the beginning of the file according to the encoding.</param>
			/// <param name="encoding">The text encoding.</param>
			bool						WriteAllText(const WString& text, bool bom = true, stream::BomEncoder::Encoding encoding = stream::BomEncoder::Utf16);
			/// <summary>Write text to the file.</summary>
			/// <returns>Returns false if this operation succeeded.</returns>
			/// <param name="lines">The text to write.</param>
			/// <param name="bom">Set to true to add a corresponding BOM at the beginning of the file according to the encoding.</param>
			/// <param name="encoding">The text encoding.</param>
			bool						WriteAllLines(collections::List<WString>& lines, bool bom = true, stream::BomEncoder::Encoding encoding = stream::BomEncoder::Utf16);
			
			/// <summary>Test does the file exist or not.</summary>
			/// <returns>Returns true if the file exists.</returns>
			bool						Exists()const;
			/// <summary>Delete the file.</summary>
			/// <returns>Returns true if this operation succeeded.</returns>
			bool						Delete()const;
			/// <summary>Rename the file in the same folder.</summary>
			/// <returns>Returns true if this operation succeeded.</returns>
			/// <param name="newName">The new file name.</param>
			bool						Rename(const WString& newName)const;
		};
		
	}
}


#endif

#ifndef NICE_FOLDER
#define NICE_FOLDER

// #include "../Basic.h"
// #include "../String.h"
// #include "../Collections/List.h"
// #include "../Stream/CharFormat.h"
// #include "FilePath.h"
// #include "File.h"
// #include "FileSystem.h"


namespace vl
{
	namespace filesystem
	{
		/// <summary>Representing a folder reference.</summary>
		class Folder : public Object
		{
		 private:
			FilePath					filePath;
			
		 public:
			/// <summary>Create a root reference.</summary>
			Folder();
			/// <summary>Create a reference to a specified folder.</summary>
			/// <param name="_filePath">The specified folder.</param>
			Folder(const FilePath& _filePath);
			~Folder();
			
			/// <summary>Get the file path of the folder.</summary>
			/// <returns>The file path.</returns>
			const FilePath&				GetFilePath()const;
			/// <summary>Get all folders in this folder.</summary>
			/// <returns>Returns true if this operation succeeded.</returns>
			/// <param name="folders">All folders.</param>
			bool						GetFolders(collections::List<Folder>& folders)const;
			/// <summary>Get all files in this folder.</summary>
			/// <returns>Returns true if this operation succeeded.</returns>
			/// <param name="files">All files.</param>
			bool						GetFiles(collections::List<File>& files)const;
			
			/// <summary>Test does the folder exist or not.</summary>
			/// <returns>Returns true if the folder exists.</returns>
			bool						Exists()const;
			/// <summary>Create the folder.</summary>
			/// <returns>Returns true if this operation succeeded.</returns>
			/// <param name="recursively">Set to true to create all parent folders if necessary.</param>
			bool						Create(bool recursively)const;
			/// <summary>Delete the folder.</summary>
			/// <returns>Returns true if this operation succeeded.</returns>
			/// <param name="recursively">Set to true to delete everything in the folder.</param>
			bool						Delete(bool recursively)const;
			/// <summary>Rename the folder in the same folder.</summary>
			/// <returns>Returns true if this operation succeeded.</returns>
			/// <param name="newName">The new folder name.</param>
			bool						Rename(const WString& newName)const;
		};
	}
	
}
#endif // !FOLDER

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Framework::FileSystem

***********************************************************************/

#ifndef NICE_FILEINFO
#define NICE_FILEINFO

// #include "../Basic.h"
// #include "../String.h"
// #include "../Collections/List.h"
// #include "../Stream/CharFormat.h"
// #include "FilePath.h"
namespace vl
{
	namespace filesystem
	{
	
	
		class FileInfo
		{
			struct FileAttrbutes
			{
				FileAttrbutes()
					: attrbutes(0),
					  size(0) {}
				DateTime creation;
				DateTime lastAccess;
				DateTime lastWrite;
				
				FilePath filePath;
				vuint64_t attrbutes;
				vuint64_t size;
			};
		 public:
			FileInfo();
			FileInfo(const FilePath& path);
			FileInfo(const WString& path);
			~FileInfo();
		 public:
			void SetPath(const WString& path);
			void SetPath(const FilePath& path);
		 public:
			bool Exists()const;
			bool IsFolder()const;
			bool IsFile()const;
			bool IsReadable()const;
			bool IsWritable()const;
			bool IsHidden()const;
			WString FileName();
			WString Extemsion();
			
			DateTime Created();
			DateTime LastModified();
			DateTime LastRead();
			vuint64_t Size();
		 protected:
			bool getProperty();
		 private:
			FileAttrbutes attrbute;
		};
		
		
	}
}

#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Regex::Basic Data Structure

Classes:
***********************************************************************/

#ifndef VCZH_REGEX_REGEXDATA
#define VCZH_REGEX_REGEXDATA

// #include "../String.h"
// #include "../Pointer.h"
// #include "../Exception.h"
// #include "../Collections/List.h"
// #include "../Collections/Dictionary.h"

namespace vl
{
	namespace regex_internal
	{
	
		/***********************************************************************
		基础数据结构
		***********************************************************************/
		
		class CharRange
		{
		 public:
			typedef collections::SortedList<CharRange>		List;
			
			wchar_t					begin;
			wchar_t					end;
			
			CharRange();
			CharRange(wchar_t _begin, wchar_t _end);
			
			bool					operator<(CharRange item)const;
			bool					operator<=(CharRange item)const;
			bool					operator>(CharRange item)const;
			bool					operator>=(CharRange item)const;
			bool					operator==(CharRange item)const;
			bool					operator!=(CharRange item)const;
			
			bool					operator<(wchar_t item)const;
			bool					operator<=(wchar_t item)const;
			bool					operator>(wchar_t item)const;
			bool					operator>=(wchar_t item)const;
			bool					operator==(wchar_t item)const;
			bool					operator!=(wchar_t item)const;
		};
	}
	
	template<>
	struct POD<regex_internal::CharRange>
	{
		static const bool Result = true;
	};
}

#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Regex::RegexAutomaton

Classes:
State						：状态
Transition					：转换
Automaton					：状态机

Functions:
EpsilonNfaToNfa				：去Epsilon
NfaToDfa					：NFA转DFA
***********************************************************************/

#ifndef VCZH_REGEX_REGEXAUTOMATON
#define VCZH_REGEX_REGEXAUTOMATON

// #include "RegexData.h"

namespace vl
{
	namespace regex_internal
	{
		class State;
		class Transition;
		
		class Transition
		{
		 public:
			enum Type
			{
				Chars,				//range为字符范围
				Epsilon,
				BeginString,
				EndString,
				Nop,				//无动作（不可消除epsilon，用来控制优先级）
				Capture,			//capture为捕获频道
				Match,				//capture为捕获频道，index为匹配的位置，-1代表匹配频道下面的所有项目
				Positive,			//正向匹配
				Negative,			//反向匹配
				NegativeFail,		//反向匹配失败
				End					//Capture, Position, Negative
			};
			
			State*								source;
			State*								target;
			CharRange							range;
			Type								type;
			vint								capture;
			vint								index;
		};
		
		class State
		{
		 public:
			collections::List<Transition*>		transitions;
			collections::List<Transition*>		inputs;
			bool								finalState;
			void*								userData;
		};
		
		class Automaton
		{
		 public:
			typedef Ptr<Automaton>		Ref;
			
			collections::List<Ptr<State>>		states;
			collections::List<Ptr<Transition>>	transitions;
			collections::List<WString>			captureNames;
			State*								startState;
			
			Automaton();
			
			State*								NewState();
			Transition*							NewTransition(State* start, State* end);
			Transition*							NewChars(State* start, State* end, CharRange range);
			Transition*							NewEpsilon(State* start, State* end);
			Transition*							NewBeginString(State* start, State* end);
			Transition*							NewEndString(State* start, State* end);
			Transition*							NewNop(State* start, State* end);
			Transition*							NewCapture(State* start, State* end, vint capture);
			Transition*							NewMatch(State* start, State* end, vint capture, vint index = -1);
			Transition*							NewPositive(State* start, State* end);
			Transition*							NewNegative(State* start, State* end);
			Transition*							NewNegativeFail(State* start, State* end);
			Transition*							NewEnd(State* start, State* end);
		};
		
		extern bool								PureEpsilonChecker(Transition* transition);
		extern bool								RichEpsilonChecker(Transition* transition);
		extern bool								AreEqual(Transition* transA, Transition* transB);
		extern Automaton::Ref					EpsilonNfaToNfa(Automaton::Ref source, bool(*epsilonChecker)(Transition*), collections::Dictionary<State*, State*>& nfaStateMap);
		extern Automaton::Ref					NfaToDfa(Automaton::Ref source, collections::Group<State*, State*>& dfaStateMap);
	}
}

#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Regex::RegexInterpretor

Classes:
RichInterpretor					：正则表达式完全模拟器
***********************************************************************/

#ifndef VCZH_REGEX_REGEXRICH
#define VCZH_REGEX_REGEXRICH

// #include "RegexAutomaton.h"

namespace vl
{
	namespace regex_internal
	{
		class CaptureRecord
		{
		 public:
			vint								capture;
			vint								start;
			vint								length;
			
			bool								operator==(const CaptureRecord& record)const;
		};
	}
	
	template<>
	struct POD<regex_internal::CaptureRecord>
	{
		static const bool Result = true;
	};
	
	namespace regex_internal
	{
		class RichResult
		{
		 public:
			vint								start;
			vint								length;
			collections::List<CaptureRecord>	captures;
		};
		
		class RichInterpretor : public Object
		{
		 public:
		 protected:
			class UserData
			{
			 public:
				bool							NeedKeepState;
			};
			
			Automaton::Ref						dfa;
			UserData*							datas;
		 public:
			RichInterpretor(Automaton::Ref _dfa);
			~RichInterpretor();
			
			bool								MatchHead(const wchar_t* input, const wchar_t* start, RichResult& result);
			bool								Match(const wchar_t* input, const wchar_t* start, RichResult& result);
			const collections::List<WString>&	CaptureNames();
		};
	};
}

#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Regex::RegexExpression

Classes:
Expression						：表达式基类					|
CharSetExpression				：字符集表达式				| a, [a-b], [^a-b0_9], \.rnt\/()+*?{}[]<>^$!=SsDdLlWw, [\rnt-[]\/^$]
LoopExpression					：循环表达式					| a{3}, a{3,}, a{1,3}, a+, a*, a?, LOOP?
SequenceExpression				：顺序表达式					| ab
AlternateExpression				：选择表达式					| a|b
BeginExpression					：【非纯】字符串起始表达式	| ^
EndExpression					：【非纯】字符串末尾表达式	| $
CaptureExpression				：【非纯】捕获表达式			| (<name>expr), (?expr)
MatchExpression					：【非纯】匹配表达式			| (<$name>), (<$name;i>), (<$i>)
PositiveExpression				：【非纯】正向预查表达式		| (=expr)
NegativeExpression				：【非纯】反向预查表达式		| (!expr)
UsingExpression					：引用表达式					| (<#name1>expr)...(<&name1>)...

RegexExpression					：正则表达式

Functions:
ParseRegexExpression			：将字符串分析为RegexExpression对象，如果语法有问题则抛异常
***********************************************************************/

#ifndef VCZH_REGEX_REGEXEXPRESSION
#define VCZH_REGEX_REGEXEXPRESSION
//
// #include "RegexData.h"
// #include "RegexAutomaton.h"
//
namespace vl
{
	namespace regex_internal
	{
		class IRegexExpressionAlgorithm;
		
		/***********************************************************************
		正则表达式表达式树
		***********************************************************************/
		
		class Expression : public Object, private NotCopyable
		{
		 public:
			typedef Ptr<Expression>											Ref;
			typedef collections::Dictionary<WString, Expression::Ref>		Map;
			
			virtual void				Apply(IRegexExpressionAlgorithm& algorithm) = 0;
			bool						IsEqual(Expression* expression);
			bool						HasNoExtension();
			bool						CanTreatAsPure();
			void						NormalizeCharSet(CharRange::List& subsets);
			void						CollectCharSet(CharRange::List& subsets);
			void						ApplyCharSet(CharRange::List& subsets);
			Automaton::Ref				GenerateEpsilonNfa();
		};
		
		class CharSetExpression : public Expression
		{
		 public:
			CharRange::List				ranges;
			bool						reverse;
			
			bool						AddRangeWithConflict(CharRange range);
			void						Apply(IRegexExpressionAlgorithm& algorithm);
		};
		
		class LoopExpression : public Expression
		{
		 public:
			Expression::Ref				expression;		//被循环表达式
			vint							min;			//下限
			vint							max;			//上限，-1代表无限
			bool						preferLong;		//长匹配优先
			
			void						Apply(IRegexExpressionAlgorithm& algorithm);
		};
		
		class SequenceExpression : public Expression
		{
		 public:
			Expression::Ref				left;			//左表达式
			Expression::Ref				right;			//右表达式
			
			void						Apply(IRegexExpressionAlgorithm& algorithm);
		};
		
		class AlternateExpression : public Expression
		{
		 public:
			Expression::Ref				left;			//左表达式
			Expression::Ref				right;			//右表达式
			
			void						Apply(IRegexExpressionAlgorithm& algorithm);
		};
		
		class BeginExpression : public Expression
		{
		 public:
		 
			void						Apply(IRegexExpressionAlgorithm& algorithm);
		};
		
		class EndExpression : public Expression
		{
		 public:
		 
			void						Apply(IRegexExpressionAlgorithm& algorithm);
		};
		
		class CaptureExpression : public Expression
		{
		 public:
			WString						name;			//捕获名，空代表缺省捕获
			Expression::Ref				expression;		//被捕获表达式
			
			void						Apply(IRegexExpressionAlgorithm& algorithm);
		};
		
		class MatchExpression : public Expression
		{
		 public:
			WString						name;			//捕获名，空代表缺省捕获
			vint							index;			//捕获序号，-1代表非空捕获的所有项
			
			void						Apply(IRegexExpressionAlgorithm& algorithm);
		};
		
		class PositiveExpression : public Expression
		{
		 public:
			Expression::Ref				expression;		//正向匹配表达式
			
			void						Apply(IRegexExpressionAlgorithm& algorithm);
		};
		
		class NegativeExpression : public Expression
		{
		 public:
			Expression::Ref				expression;		//反向匹配表达式
			
			void						Apply(IRegexExpressionAlgorithm& algorithm);
		};
		
		class UsingExpression : public Expression
		{
		 public:
			WString						name;			//引用名
			
			void						Apply(IRegexExpressionAlgorithm& algorithm);
		};
		
		class RegexExpression : public Object, private NotCopyable
		{
		 public:
			typedef Ptr<RegexExpression>						Ref;
			
			Expression::Map				definitions;	//命名子表达式
			Expression::Ref				expression;		//主表达式
			
			Expression::Ref				Merge();
		};
		
		/***********************************************************************
		算法基类
		***********************************************************************/
		
		class IRegexExpressionAlgorithm : public Interface
		{
		 public:
			virtual void				Visit(CharSetExpression* expression) = 0;
			virtual void				Visit(LoopExpression* expression) = 0;
			virtual void				Visit(SequenceExpression* expression) = 0;
			virtual void				Visit(AlternateExpression* expression) = 0;
			virtual void				Visit(BeginExpression* expression) = 0;
			virtual void				Visit(EndExpression* expression) = 0;
			virtual void				Visit(CaptureExpression* expression) = 0;
			virtual void				Visit(MatchExpression* expression) = 0;
			virtual void				Visit(PositiveExpression* expression) = 0;
			virtual void				Visit(NegativeExpression* expression) = 0;
			virtual void				Visit(UsingExpression* expression) = 0;
		};
		
		template<typename ReturnType, typename ParameterType = void*>
		class RegexExpressionAlgorithm : public Object, public IRegexExpressionAlgorithm
		{
		 private:
			ReturnType					returnValue;
			ParameterType*				parameterValue;
		 public:
		 
			ReturnType Invoke(Expression* expression, ParameterType parameter)
			{
				parameterValue = &parameter;
				expression->Apply(*this);
				return returnValue;
			}
			
			ReturnType Invoke(Expression::Ref expression, ParameterType parameter)
			{
				parameterValue = &parameter;
				expression->Apply(*this);
				return returnValue;
			}
			
			virtual ReturnType			Apply(CharSetExpression* expression, ParameterType parameter) = 0;
			virtual ReturnType			Apply(LoopExpression* expression, ParameterType parameter) = 0;
			virtual ReturnType			Apply(SequenceExpression* expression, ParameterType parameter) = 0;
			virtual ReturnType			Apply(AlternateExpression* expression, ParameterType parameter) = 0;
			virtual ReturnType			Apply(BeginExpression* expression, ParameterType parameter) = 0;
			virtual ReturnType			Apply(EndExpression* expression, ParameterType parameter) = 0;
			virtual ReturnType			Apply(CaptureExpression* expression, ParameterType parameter) = 0;
			virtual ReturnType			Apply(MatchExpression* expression, ParameterType parameter) = 0;
			virtual ReturnType			Apply(PositiveExpression* expression, ParameterType parameter) = 0;
			virtual ReturnType			Apply(NegativeExpression* expression, ParameterType parameter) = 0;
			virtual ReturnType			Apply(UsingExpression* expression, ParameterType parameter) = 0;
		 public:
			void Visit(CharSetExpression* expression)
			{
				returnValue = Apply(expression, *parameterValue);
			}
			
			void Visit(LoopExpression* expression)
			{
				returnValue = Apply(expression, *parameterValue);
			}
			
			void Visit(SequenceExpression* expression)
			{
				returnValue = Apply(expression, *parameterValue);
			}
			
			void Visit(AlternateExpression* expression)
			{
				returnValue = Apply(expression, *parameterValue);
			}
			
			void Visit(BeginExpression* expression)
			{
				returnValue = Apply(expression, *parameterValue);
			}
			
			void Visit(EndExpression* expression)
			{
				returnValue = Apply(expression, *parameterValue);
			}
			
			void Visit(CaptureExpression* expression)
			{
				returnValue = Apply(expression, *parameterValue);
			}
			
			void Visit(MatchExpression* expression)
			{
				returnValue = Apply(expression, *parameterValue);
			}
			
			void Visit(PositiveExpression* expression)
			{
				returnValue = Apply(expression, *parameterValue);
			}
			
			void Visit(NegativeExpression* expression)
			{
				returnValue = Apply(expression, *parameterValue);
			}
			
			void Visit(UsingExpression* expression)
			{
				returnValue = Apply(expression, *parameterValue);
			}
		};
		
		template<typename ParameterType>
		class RegexExpressionAlgorithm<void, ParameterType> : public Object, public IRegexExpressionAlgorithm
		{
		 private:
			ParameterType*				parameterValue;
		 public:
		 
			void Invoke(Expression* expression, ParameterType parameter)
			{
				parameterValue = &parameter;
				expression->Apply(*this);
			}
			
			void Invoke(Expression::Ref expression, ParameterType parameter)
			{
				parameterValue = &parameter;
				expression->Apply(*this);
			}
			
			virtual void				Apply(CharSetExpression* expression, ParameterType parameter) = 0;
			virtual void				Apply(LoopExpression* expression, ParameterType parameter) = 0;
			virtual void				Apply(SequenceExpression* expression, ParameterType parameter) = 0;
			virtual void				Apply(AlternateExpression* expression, ParameterType parameter) = 0;
			virtual void				Apply(BeginExpression* expression, ParameterType parameter) = 0;
			virtual void				Apply(EndExpression* expression, ParameterType parameter) = 0;
			virtual void				Apply(CaptureExpression* expression, ParameterType parameter) = 0;
			virtual void				Apply(MatchExpression* expression, ParameterType parameter) = 0;
			virtual void				Apply(PositiveExpression* expression, ParameterType parameter) = 0;
			virtual void				Apply(NegativeExpression* expression, ParameterType parameter) = 0;
			virtual void				Apply(UsingExpression* expression, ParameterType parameter) = 0;
		 public:
			void Visit(CharSetExpression* expression)
			{
				Apply(expression, *parameterValue);
			}
			
			void Visit(LoopExpression* expression)
			{
				Apply(expression, *parameterValue);
			}
			
			void Visit(SequenceExpression* expression)
			{
				Apply(expression, *parameterValue);
			}
			
			void Visit(AlternateExpression* expression)
			{
				Apply(expression, *parameterValue);
			}
			
			void Visit(BeginExpression* expression)
			{
				Apply(expression, *parameterValue);
			}
			
			void Visit(EndExpression* expression)
			{
				Apply(expression, *parameterValue);
			}
			
			void Visit(CaptureExpression* expression)
			{
				Apply(expression, *parameterValue);
			}
			
			void Visit(MatchExpression* expression)
			{
				Apply(expression, *parameterValue);
			}
			
			void Visit(PositiveExpression* expression)
			{
				Apply(expression, *parameterValue);
			}
			
			void Visit(NegativeExpression* expression)
			{
				Apply(expression, *parameterValue);
			}
			
			void Visit(UsingExpression* expression)
			{
				Apply(expression, *parameterValue);
			}
		};
		
		/***********************************************************************
		辅助函数
		***********************************************************************/
		
		extern Ptr<LoopExpression>		ParseLoop(const wchar_t*& input);
		extern Ptr<Expression>			ParseCharSet(const wchar_t*& input);
		extern Ptr<Expression>			ParseFunction(const wchar_t*& input);
		extern Ptr<Expression>			ParseUnit(const wchar_t*& input);
		extern Ptr<Expression>			ParseJoin(const wchar_t*& input);
		extern Ptr<Expression>			ParseAlt(const wchar_t*& input);
		extern Ptr<Expression>			ParseExpression(const wchar_t*& input);
		extern RegexExpression::Ref		ParseRegexExpression(const WString& code);
		
		extern WString					EscapeTextForRegex(const WString& literalString);
		extern WString					UnescapeTextForRegex(const WString& escapedText);
		extern WString					NormalizeEscapedTextForRegex(const WString& escapedText);
		extern bool						IsRegexEscapedLiteralString(const WString& regex);
	}
}

#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Regex::RegexInterpretor

Classes:
PureInterpretor					：正则表达式纯模拟器
***********************************************************************/

#ifndef VCZH_REGEX_REGEXPURE
#define VCZH_REGEX_REGEXPURE

// #include "RegexAutomaton.h"

namespace vl
{
	namespace regex_internal
	{
		class PureResult
		{
		 public:
			vint				start;
			vint				length;
			vint				finalState;
			vint				terminateState;
		};
		
		class PureInterpretor : public Object
		{
		 protected:
#if defined VCZH_MSVC
			static const vint	SupportedCharCount = 0x10000;		// UTF-16
#elif defined VCZH_GCC
			static const vint	SupportedCharCount = 0x110000;		// UTF-32
#endif
			
			vint				charMap[SupportedCharCount];		// char -> char set index
			vint**				transition;							// (state * char set index) -> state*
			bool*				finalState;							// state -> bool
			vint*				relatedFinalState;					// sate -> (finalState or -1)
			vint				stateCount;
			vint				charSetCount;
			vint				startState;
		 public:
			PureInterpretor(Automaton::Ref dfa, CharRange::List& subsets);
			~PureInterpretor();
			
			bool				MatchHead(const wchar_t* input, const wchar_t* start, PureResult& result);
			bool				Match(const wchar_t* input, const wchar_t* start, PureResult& result);
			
			vint				GetStartState();
			vint				Transit(wchar_t input, vint state);
			bool				IsFinalState(vint state);
			bool				IsDeadState(vint state);
			
			void				PrepareForRelatedFinalStateTable();
			vint				GetRelatedFinalState(vint state);
		};
	}
}

#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Regex::RegexWriter

Classes:
***********************************************************************/

#ifndef VCZH_REGEX_REGEXWRITER
#define VCZH_REGEX_REGEXWRITER

// #include "RegexExpression.h"

namespace vl
{
	namespace regex
	{
		class RegexNode : public Object
		{
		 public:
			vl::regex_internal::Expression::Ref		expression;
			
			RegexNode(vl::regex_internal::Expression::Ref _expression);
			
			RegexNode					Some()const;
			RegexNode					Any()const;
			RegexNode					Opt()const;
			RegexNode					Loop(vint min, vint max)const;
			RegexNode					AtLeast(vint min)const;
			RegexNode					operator+(const RegexNode& node)const;
			RegexNode					operator|(const RegexNode& node)const;
			RegexNode					operator+()const;
			RegexNode					operator-()const;
			RegexNode					operator!()const;
			RegexNode					operator%(const RegexNode& node)const;
		};
		
		extern RegexNode				rCapture(const WString& name, const RegexNode& node);
		extern RegexNode				rUsing(const WString& name);
		extern RegexNode				rMatch(const WString& name, vint index = -1);
		extern RegexNode				rMatch(vint index);
		extern RegexNode				rBegin();
		extern RegexNode				rEnd();
		extern RegexNode				rC(wchar_t a, wchar_t b = L'\0');
		extern RegexNode				r_d();
		extern RegexNode				r_l();
		extern RegexNode				r_w();
		extern RegexNode				rAnyChar();
	}
}

#endif


/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Regex::Regular Expression

Classes:
RegexString						：字符串匹配结果
RegexMatch						：匹配结果
Regex							：正则表达式引擎
RegexToken						：词法记号
RegexTokens						：词法记号表
RegexLexer						：词法分析器
***********************************************************************/

#ifndef VCZH_REGEX_REGEX
#define VCZH_REGEX_REGEX

// #include "../String.h"
// #include "../Pointer.h"
// #include "../Collections/List.h"
// #include "../Collections/Dictionary.h"

namespace vl
{
	namespace regex_internal
	{
		class PureResult;
		class PureInterpretor;
		class RichResult;
		class RichInterpretor;
	}
	
	namespace regex
	{
	
		/***********************************************************************
		正则表达式引擎数据结构
		***********************************************************************/
		
		/// <summary>A type representing a fragment of the input string.</summary>
		class RegexString : public Object
		{
		 protected:
			WString										value;
			vint										start;
			vint										length;
			
		 public:
			RegexString(vint _start = 0);
			RegexString(const WString& _string, vint _start, vint _length);
			
			/// <summary>The position of the input string.</summary>
			/// <returns>The position.</returns>
			vint										Start()const;
			/// <summary>The size of the fragment in characters.</summary>
			/// <returns>The size.</returns>
			vint										Length()const;
			/// <summary>Get the fragment.</summary>
			/// <returns>The fragment.</returns>
			const WString&								Value()const;
			bool										operator==(const RegexString& string)const;
		};
		
		/// <summary>A type representing a match of the input string.</summary>
		class RegexMatch : public Object, private NotCopyable
		{
			friend class Regex;
		 public:
			typedef Ptr<RegexMatch>										Ref;
			typedef collections::List<Ref>								List;
			typedef collections::List<RegexString>						CaptureList;
			typedef collections::Group<WString, RegexString>			CaptureGroup;
		 protected:
			collections::List<RegexString>				captures;
			collections::Group<WString, RegexString>	groups;
			bool										success;
			RegexString									result;
			
			RegexMatch(const WString& _string, regex_internal::PureResult* _result);
			RegexMatch(const WString& _string, regex_internal::RichResult* _result, regex_internal::RichInterpretor* _rich);
			RegexMatch(const RegexString& _result);
		 public:
		 
			/// <summary>Test if this match is a success match or a failed match. A failed match will only appear when calling [M:vl.regex.Regex.Split] or [M:vl.regex.Regex.Cut]. In other cases, failed matches are either not included in the result, or become null pointers.</summary>
			/// <returns>Returns true if this match is a success match.</returns>
			bool										Success()const;
			/// <summary>Get the whole fragment that matches.</summary>
			/// <returns>The whole fragment.</returns>
			const RegexString&							Result()const;
			/// <summary>Get all fragments that are captured.</summary>
			/// <returns>All fragments that are captured.</returns>
			const CaptureList&							Captures()const;
			/// <summary>Get all fragments that are captured by named groups.</summary>
			/// <returns>All fragments that are captured.</returns>
			const CaptureGroup&							Groups()const;
		};
		
		/***********************************************************************
		正则表达式引擎
		***********************************************************************/
		
		/// <summary><![CDATA[
		/// Regular Expression. Here is a brief description of the regular expression grammar:
		///	1) Charset:
		///		a, [a-z], [^a-z]
		/// 2) Functional characters:
		///		^: the beginning of the input (DFA incompatible)
		///		$: the end of the input (DFA incompatible)
		///		regex1|regex2: match either regex1 or regex2
		///	3) Escaping (both \ and / mean the next character is escaped)
		///		Escaped characters:
		///			\r: the CR character
		///			\n: the LF character
		///			\t: the tab character
		///			\s: spacing characters (including space, \r, \n, \t)
		///			\S: non-spacing characters
		///			\d: [0-9]
		///			\D: [^0-9]
		///			\l: [a-zA-Z]
		///			\L: [^a-zA-Z]
		///			\w: [a-zA-Z0-9_]
		///			\W: [^a-zA-Z0-9_]
		///			\.: any character (this is the main different from other regex, which treat "." as any characters and "\." as the dot character)
		///			\\, \/, \(, \), \+, \*, \?, \{, \}, \[, \], \<, \>, \^, \$, \!, \=: represents itself
		///		Escaped characters in charset defined in a square bracket:
		///			\r: the CR character
		///			\n: the LF character
		///			\t: the tab character
		///			\-, \[, \], \\, \/, \^, \$: represents itself
		///	4) Loops:
		///		regex{3}: repeats 3 times
		///		regex{3,}: repeats 3 or more times
		///		regex{1,3}: repeats 1 to 3 times
		///		regex?: repeats 0 or 1 times
		///		regex*: repeats 0 or more times
		///		regex+: repeats 1 or more times
		///		if you add a "?" right after a loop, it means repeating as less as possible (DFA incompatible)
		///	5) Capturing: (DFA incompatible)
		///		(regex): No capturing, just change the operators' association
		///		(?regex): Capture matched fragment
		///		(<name>regex): Capture matched fragment in a named group called "name"
		///		(<$i>): Match the i-th captured fragment, begins from 0
		///		(<$name;i>): Match the i-th captured fragment in the named group called "name", begins from 0
		///		(<$name>): Match any captured fragment in the named group called "name"
		///	6) MISC
		///		(=regex): The prefix of the following text should match the regex, but it is not counted in the whole match (DFA incompatible)
		///		(!regex): Any prefix of the following text should not match the regex, and it is not counted in the whole match (DFA incompatible)
		///		(<#name>regex): Name the regex "name", and it applies here
		///		(<&name>): Copy the named regex "name" here and apply
		/// ]]></summary>
		class Regex : public Object, private NotCopyable
		{
		 protected:
			regex_internal::PureInterpretor*			pure;
			regex_internal::RichInterpretor*			rich;
			
			void										Process(const WString& text, bool keepEmpty, bool keepSuccess, bool keepFail, RegexMatch::List& matches)const;
		 public:
			/// <summary>Create a regular expression.</summary>
			/// <param name="code">The regular expression in a string.</param>
			/// <param name="preferPure">Set to true to tell the Regex to use DFA if possible.</param>
			Regex(const WString& code, bool preferPure = true);
			~Regex();
			
			/// <summary>Test does the Regex uses DFA to match a string.</summary>
			/// <returns>Returns true if DFA is used.</returns>
			bool										IsPureMatch()const;
			/// <summary>Test does the Regex uses DFA to test a string. Test means ignoring all capturing requirements.</summary>
			/// <returns>Returns true if DFA is used.</returns>
			bool										IsPureTest()const;
			
			/// <summary>Match a prefix of the text.</summary>
			/// <returns>Returns the match. Returns null if failed.</returns>
			/// <param name="text">The text to match.</param>
			RegexMatch::Ref								MatchHead(const WString& text)const;
			/// <summary>Match a fragment of the text.</summary>
			/// <returns>Returns the match. Returns null if failed.</returns>
			/// <param name="text">The text to match.</param>
			RegexMatch::Ref								Match(const WString& text)const;
			/// <summary>Match a prefix of the text, ignoring all capturing requirements.</summary>
			/// <returns>Returns true if succeeded.</returns>
			/// <param name="text">The text to match.</param>
			bool										TestHead(const WString& text)const;
			/// <summary>Match a fragment of the text, ignoring all capturing requirements.</summary>
			/// <returns>Returns true if succeeded.</returns>
			/// <param name="text">The text to match.</param>
			bool										Test(const WString& text)const;
			/// <summary>Find all matched fragments of the text, returning all matched fragments.</summary>
			/// <param name="text">The text to match.</param>
			/// <param name="matches">All successful matches.</param>
			void										Search(const WString& text, RegexMatch::List& matches)const;
			/// <summary>Split the text by matched fragments, returning all unmatched fragments.</summary>
			/// <param name="text">The text to match.</param>
			/// <param name="keepEmptyMatch">Set to true to keep all empty matches.</param>
			/// <param name="matches">All failed matches.</param>
			void										Split(const WString& text, bool keepEmptyMatch, RegexMatch::List& matches)const;
			/// <summary>Cut the text by matched fragments, returning all matched or unmatched fragments.</summary>
			/// <param name="text">The text to match.</param>
			/// <param name="keepEmptyMatch">Set to true to keep all empty matches.</param>
			/// <param name="matches">All successful and failed matches.</param>
			void										Cut(const WString& text, bool keepEmptyMatch, RegexMatch::List& matches)const;
		};
		
		/***********************************************************************
		正则表达式词法分析器
		***********************************************************************/
		
		/// <summary>A token.</summary>
		class RegexToken
		{
		 public:
			/// <summary>Position in the input string.</summary>
			vint										start;
			/// <summary>Size of this token in characters.</summary>
			vint										length;
			/// <summary>The token id, begins at 0, represents the regular expression in the list that matches this token. -1 means this token is produced by an error.</summary>
			vint										token;
			/// <summary>The pointer to where this token starts in the input string .</summary>
			const wchar_t*								reading;
			/// <summary>The argument value from [M:vl.regex.RegexLexer.Parse].</summary>
			vint										codeIndex;
			/// <summary>True if this token is complete. False if this token does not end here.</summary>
			bool										completeToken;
			
			/// <summary>Row number of the first character, begins at 0.</summary>
			vint										rowStart;
			/// <summary>Column number of the first character, begins at 0.</summary>
			vint										columnStart;
			/// <summary>Row number of the last character, begins at 0.</summary>
			vint										rowEnd;
			/// <summary>Column number of the last character, begins at 0.</summary>
			vint										columnEnd;
			
			bool										operator==(const RegexToken& _token)const;
			bool										operator==(const wchar_t* _token)const;
		};
		
		/// <summary>Token collection representing the result from the lexical analyzer.</summary>
		class RegexTokens : public Object, public collections::IEnumerable<RegexToken>
		{
			friend class RegexLexer;
		 protected:
			regex_internal::PureInterpretor*			pure;
			const collections::Array<vint>&				stateTokens;
			WString										code;
			vint										codeIndex;
			
			RegexTokens(regex_internal::PureInterpretor* _pure, const collections::Array<vint>& _stateTokens, const WString& _code, vint _codeIndex);
		 public:
			RegexTokens(const RegexTokens& tokens);
			
			collections::IEnumerator<RegexToken>*		CreateEnumerator()const;
			
			/// <summary>Copy all tokens.</summary>
			/// <param name="tokens">Returns all tokens.</param>
			/// <param name="discard">A callback to decide which kind of tokens to discard. The input is [F:vl.regex.RegexToken.token]. Returns true to discard this kind of tokens.</param>
			void										ReadToEnd(collections::List<RegexToken>& tokens, bool(*discard)(vint) = 0)const;
		};
		
		/// <summary>Lexical walker.</summary>
		class RegexLexerWalker : public Object
		{
			friend class RegexLexer;
		 protected:
			regex_internal::PureInterpretor*			pure;
			const collections::Array<vint>&				stateTokens;
			
			RegexLexerWalker(regex_internal::PureInterpretor* _pure, const collections::Array<vint>& _stateTokens);
		 public:
			RegexLexerWalker(const RegexLexerWalker& walker);
			~RegexLexerWalker();
			
			/// <summary>Get the start DFA state number, which represents the correct state before parsing any input.</summary>
			/// <returns>The DFA state number.</returns>
			vint										GetStartState()const;
			/// <summary>Test if this state can only lead to the end of one kind of token.</summary>
			/// <returns>Returns the token index if this state can only lead to the end of one kind of token. Returns -1 if not.</returns>
			/// <param name="state">The DFA state number.</param>
			vint										GetRelatedToken(vint state)const;
			/// <summary>Step forward by one character.</summary>
			/// <param name="input">The input character.</param>
			/// <param name="state">The current state. Returns the new current state when this function returns.</param>
			/// <param name="token">Returns the token index at the end of the token.</param>
			/// <param name="finalState">Returns true if it reach the end of the token.</param>
			/// <param name="previousTokenStop">Returns true if the last character is the end of the token.</param>
			void										Walk(wchar_t input, vint& state, vint& token, bool& finalState, bool& previousTokenStop)const;
			/// <summary>Step forward by one character.</summary>
			/// <returns>Returns the new current state.</returns>
			/// <param name="input">The input character.</param>
			/// <param name="state">The current state.</param>
			vint										Walk(wchar_t input, vint state)const;
			/// <summary>Test if the input text is a complete token.</summary>
			/// <returns>Returns true if the input text is a complete token.</returns>
			/// <param name="input">The input text.</param>
			/// <param name="length">Size of the input text in characters.</param>
			bool										IsClosedToken(const wchar_t* input, vint length)const;
			/// <summary>Test if the input is a complete token.</summary>
			/// <returns>Returns true if the input text is a complete token.</returns>
			/// <param name="input">The input text.</param>
			bool										IsClosedToken(const WString& input)const;
		};
		
		/// <summary>Lexical colorizer.</summary>
		class RegexLexerColorizer : public Object
		{
			friend class RegexLexer;
		 public:
			typedef void(*TokenProc)(void* argument, vint start, vint length, vint token);
			
		 protected:
			RegexLexerWalker							walker;
			vint										currentState;
			
			RegexLexerColorizer(const RegexLexerWalker& _walker);
		 public:
			RegexLexerColorizer(const RegexLexerColorizer& colorizer);
			~RegexLexerColorizer();
			
			/// <summary>Reset the colorizer using the DFA state number.</summary>
			/// <param name="state">The DFA state number.</param>
			void										Reset(vint state);
			/// <summary>Step forward by one character.</summary>
			/// <param name="input">The input character.</param>
			void										Pass(wchar_t input);
			/// <summary>Get the start DFA state number, which represents the correct state before colorizing any characters.</summary>
			/// <returns>The DFA state number.</returns>
			vint										GetStartState()const;
			/// <summary>Get the current DFA state number.</summary>
			/// <returns>The DFA state number.</returns>
			vint										GetCurrentState()const;
			/// <summary>Colorize a text.</summary>
			/// <param name="input">The text to colorize.</param>
			/// <param name="length">Size of the text in characters.</param>
			/// <param name="tokenProc">Colorizer callback. This callback will be called if any token is found..</param>
			/// <param name="tokenProcArgument">The argument to call the callback.</param>
			void										Colorize(const wchar_t* input, vint length, TokenProc tokenProc, void* tokenProcArgument);
		};
		
		/// <summary>Lexical analyzer.</summary>
		class RegexLexer : public Object, private NotCopyable
		{
		 protected:
			regex_internal::PureInterpretor*			pure;
			collections::Array<vint>					ids;
			collections::Array<vint>					stateTokens;
		 public:
			/// <summary>Create a lexical analyzer by a set of regular expressions. [F:vl.regex.RegexToken.token] will be the index of the matched regular expression.</summary>
			/// <param name="tokens">The regular expressions.</param>
			RegexLexer(const collections::IEnumerable<WString>& tokens);
			~RegexLexer();
			
			/// <summary>Tokenize a input text.</summary>
			/// <returns>The result.</returns>
			/// <param name="code">The text to tokenize.</param>
			/// <param name="codeIndex">Extra information that will store in [F:vl.regex.RegexToken.codeIndex].</param>
			RegexTokens									Parse(const WString& code, vint codeIndex = -1)const;
			/// <summary>Create a equivalence walker from this lexical analyzer.</summary>
			/// <returns>The walker.</returns>
			RegexLexerWalker							Walk()const;
			/// <summary>Create a equivalence colorizer from this lexical analyzer.</summary>
			/// <returns>The colorizer.</returns>
			RegexLexerColorizer							Colorize()const;
		};
	}
}

#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Framework::Threading

Classes:
Thread										：线程
CriticalSection
Mutex
Semaphore
EventObject
***********************************************************************/

#ifndef VCZH_THREADING
#define VCZH_THREADING

// #include "Basic.h"
// #include "String.h"
// #include "Function.h"

namespace vl
{

	/***********************************************************************
	内核模式对象
	***********************************************************************/
	
	namespace threading_internal
	{
		struct WaitableData;
		struct ThreadData;
		struct MutexData;
		struct SemaphoreData;
		struct EventData;
		struct CriticalSectionData;
		struct ReaderWriterLockData;
		struct ConditionVariableData;
	}
	
	/// <summary>Base type of all synchronization objects.</summary>
	class WaitableObject : public Object, public NotCopyable
	{
#if defined VCZH_MSVC
	 private:
		threading_internal::WaitableData*			waitableData;
	 protected:
	 
		WaitableObject();
		void										SetData(threading_internal::WaitableData* data);
	 public:
		/// <summary>Test if the object has already been created. Some of the synchronization objects should initialize itself after the constructor. This function is only available in Windows.</summary>
		/// <returns>Returns true if the object has already been created.</returns>
		bool										IsCreated();
		/// <summary>Wait for this object to signal.</summary>
		/// <returns>Returns true if the object is signaled. Returns false if this operation failed.</returns>
		bool										Wait();
		/// <summary>Wait for this object to signal for a period of time. This function is only available in Windows.</summary>
		/// <returns>Returns true if the object is signaled. Returns false if this operation failed, including time out.</returns>
		/// <param name="ms">Time in milliseconds.</param>
		bool										WaitForTime(vint ms);
		
		/// <summary>Wait for multiple objects. This function is only available in Windows.</summary>
		/// <returns>Returns true if all objects are signaled. Returns false if this operation failed.</returns>
		/// <param name="objects">A pointer to an array to <see cref="WaitableObject"/> pointers.</param>
		/// <param name="count">The number of <see cref="WaitableObject"/> objects in the array.</param>
		static bool									WaitAll(WaitableObject** objects, vint count);
		/// <summary>Wait for multiple objects for a period of time. This function is only available in Windows.</summary>
		/// <returns>Returns true if all objects are signaled. Returns false if this operation failed, including time out.</returns>
		/// <param name="objects">A pointer to an array to <see cref="WaitableObject"/> pointers.</param>
		/// <param name="count">The number of <see cref="WaitableObject"/> objects in the array.</param>
		/// <param name="ms">Time in milliseconds.</param>
		static bool									WaitAllForTime(WaitableObject** objects, vint count, vint ms);
		/// <summary>Wait for one of the objects. This function is only available in Windows.</summary>
		/// <returns>Returns the index of the first signaled or abandoned object, according to the "abandoned" parameter. Returns -1 if this operation failed.</returns>
		/// <param name="objects">A pointer to an array to <see cref="WaitableObject"/> pointers.</param>
		/// <param name="count">The number of <see cref="WaitableObject"/> objects in the array.</param>
		/// <param name="abandoned">Returns true if the waiting is canceled by an abandoned object. An abandoned object is caused by it's owner thread existing without releasing it.</param>
		static vint									WaitAny(WaitableObject** objects, vint count, bool* abandoned);
		/// <summary>Wait for one of the objects for a period of time. This function is only available in Windows.</summary>
		/// <returns>Returns the index of the first signaled or abandoned object, according to the "abandoned" parameter. Returns -1 if this operation failed, including time out.</returns>
		/// <param name="objects">A pointer to an array to <see cref="WaitableObject"/> pointers.</param>
		/// <param name="count">The number of <see cref="WaitableObject"/> objects in the array.</param>
		/// <param name="ms">Time in milliseconds.</param>
		/// <param name="abandoned">Returns true if the waiting is canceled by an abandoned object. An abandoned object is caused by it's owner thread existing without releasing it.</param>
		static vint									WaitAnyForTime(WaitableObject** objects, vint count, vint ms, bool* abandoned);
#elif defined VCZH_GCC
		virtual bool								Wait() = 0;
#endif
	};
	
	/// <summary>Representing a thread. [M:vl.Thread.CreateAndStart] is the suggested way to create threads.</summary>
	class Thread : public WaitableObject
	{
		friend void InternalThreadProc(Thread* thread);
	 public:
		/// <summary>Thread state.</summary>
		enum ThreadState
		{
			/// <summary>The thread has not started.</summary>
			NotStarted,
			/// <summary>The thread is running.</summary>
			Running,
			/// <summary>The thread has been stopped.</summary>
			Stopped
		};
		
		typedef void(*ThreadProcedure)(Thread*, void*);
	 protected:
		threading_internal::ThreadData*				internalData;
		volatile ThreadState						threadState;
		
		virtual void								Run() = 0;
		
		Thread();
	 public:
		~Thread();
		
		/// <summary>Create a thread using a function pointer.</summary>
		/// <returns>Returns the created thread.</returns>
		/// <param name="procedure">The function pointer.</param>
		/// <param name="argument">The argument to call the function pointer.</param>
		/// <param name="deleteAfterStopped">Set to true (by default) to make the thread delete itself after the job is done. If you set this argument to true, you are not suggested to touch the returned thread pointer in any way.</param>
		static Thread*								CreateAndStart(ThreadProcedure procedure, void* argument = 0, bool deleteAfterStopped = true);
		/// <summary>Create a thread using a function object or a lambda expression.</summary>
		/// <returns>Returns the created thread.</returns>
		/// <param name="procedure">The function object or the lambda expression.</param>
		/// <param name="deleteAfterStopped">Set to true (by default) to make the thread delete itself after the job is done. If you set this argument to true, you are not suggested to touch the returned thread pointer in any way.</param>
		// 			static Thread*								CreateAndStart(const Func<void()>& procedure, bool deleteAfterStopped = true);
		/// <summary>Pause the caller thread for a period of time.</summary>
		/// <param name="ms">Time in milliseconds.</param>
		static void									Sleep(vint ms);
		/// <summary>Get the number of logical processors.</summary>
		/// <returns>The number of logical processor.</returns>
		static vint									GetCPUCount();
		/// <summary>Get the current thread id.</summary>
		/// <returns>The current thread id.</returns>
		static vint									GetCurrentThreadId();
		
		/// <summary>Start the thread.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		bool										Start();
#if defined VCZH_GCC
		bool										Wait();
#endif
		/// <summary>Stop the thread.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		bool										Stop();
		/// <summary>Get the state of the thread.</summary>
		/// <returns>The state of the thread.</returns>
		ThreadState									GetState();
#ifdef VCZH_MSVC
		void										SetCPU(vint index);
#endif
	};
	
	/// <summary>Mutex.</summary>
	class Mutex : public WaitableObject
	{
	 private:
		threading_internal::MutexData*				internalData;
	 public:
		Mutex();
		~Mutex();
		
		/// <summary>Create a mutex.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="owned">Set to true to own the created mutex.</param>
		/// <param name="name">Name of the mutex. If it is not empty, than it is a global named mutex. This argument is ignored in Linux.</param>
		bool										Create(bool owned = false, const WString& name = L"");
		/// <summary>Open an existing global named mutex.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="inheritable">Set to true make the mutex visible to all all child processes. This argument is only used in Windows.</param>
		/// <param name="name">Name of the mutex. This argument is ignored in Linux.</param>
		bool										Open(bool inheritable, const WString& name);
		
		/// <summary>
		/// Release the mutex.
		/// In the implementation for Linux, calling Release() more than once between two Wait(), or calling Wait() more than once between two Release(), will results in an undefined behavior.
		/// </summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		bool										Release();
#ifdef VCZH_GCC
		bool										Wait();
#endif
	};
	
	/// <summary>Semaphore.</summary>
	class Semaphore : public WaitableObject
	{
	 private:
		threading_internal::SemaphoreData*			internalData;
	 public:
		Semaphore();
		~Semaphore();
		
		/// <summary>Create a semaphore.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="initialCount">Define the counter of the semaphore.</param>
		/// <param name="maxCount">Define the maximum value of the counter of the semaphore. This argument is only used in Windows.</param>
		/// <param name="name">Name of the semaphore. If it is not empty, than it is a global named semaphore. This argument is ignored in Linux.</param>
		bool										Create(vint initialCount, vint maxCount, const WString& name = L"");
		/// <summary>Open an existing global named semaphore.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="inheritable">Set to true make the semaphore visible to all all child processes. This argument is only used in Windows.</param>
		/// <param name="name">Name of the semaphore. This argument is ignored in Linux.</param>
		bool										Open(bool inheritable, const WString& name);
		
		/// <summary> Release the semaphore once. </summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		bool										Release();
		/// <summary> Release the semaphore multiple times. </summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="count">The amout to release.</param>
		vint										Release(vint count);
#ifdef VCZH_GCC
		bool										Wait();
#endif
	};
	
	/// <summary>Event.</summary>
	class EventObject : public WaitableObject
	{
	 private:
		threading_internal::EventData*				internalData;
	 public:
		EventObject();
		~EventObject();
		
		/// <summary>Create an auto unsignal event. Auto unsignal means, when one thread waits for the event and succeeded, the event will become unsignaled immediately.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="signaled">Set to true make the event signaled at the beginning.</param>
		/// <param name="name">Name of the event. If it is not empty, than it is a global named mutex. This argument is only used in Windows.</param>
		bool										CreateAutoUnsignal(bool signaled, const WString& name = L"");
		/// <summary>Create a manual unsignal event.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="signaled">Set to true make the event signaled at the beginning.</param>
		/// <param name="name">Name of the event. If it is not empty, than it is a global named mutex. This argument is only used in Windows.</param>
		bool										CreateManualUnsignal(bool signaled, const WString& name = L"");
		/// <summary>Open an existing global named event.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="inheritable">Set to true make the event visible to all all child processes. This argument is only used in Windows.</param>
		/// <param name="name">Name of the event. This argument is only used in Windows.</param>
		bool										Open(bool inheritable, const WString& name);
		
		/// <summary>Signal the event.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		bool										Signal();
		/// <summary>Unsignal the event.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		bool										Unsignal();
#ifdef VCZH_GCC
		bool										Wait();
#endif
	};
	
	/***********************************************************************
	线程池
	***********************************************************************/
	
	/// <summary>A light-weight thread pool.</summary>
	class ThreadPoolLite : public Object
	{
	 private:
		ThreadPoolLite();
		~ThreadPoolLite();
	 public:
		/// <summary>Queue a function pointer.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="proc">The function pointer.</param>
		/// <param name="argument">The argument to call the function pointer.</param>
		static bool									Queue(void(*proc)(void*), void* argument);
		/// <summary>Queue a function object.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="proc">The function object.</param>
		// 			static bool									Queue(const Func<void()>& proc);
		
		/// <summary>Queue a lambda expression.</summary>
		/// <typeparam name="T">The type of the lambda expression.</typeparam>
		/// <param name="proc">The lambda expression.</param>
		template<typename T>
		static void QueueLambda(const T& proc)
		{
			Queue(Func<void()>(proc));
		}
		
#ifdef VCZH_GCC
		static bool									Stop(bool discardPendingTasks);
#endif
	};
	
	/***********************************************************************
	进程内对象
	***********************************************************************/
	
	/// <summary><![CDATA[
	/// Critical section. It is similar to mutex, but in Windows, enter a owned critical section will not cause dead lock.
	/// The macro "CS_LOCK" is encouraged to use instead of calling [M:vl.CriticalSection.Enter] and [M:vl.CriticalSection.Leave] like this:
	/// CS_LOCK(yourCriticalSection)
	/// {
	///		<code>
	/// }
	/// ]]></summary>
	class CriticalSection : public Object, public NotCopyable
	{
	 private:
		friend class ConditionVariable;
		threading_internal::CriticalSectionData*	internalData;
	 public:
		/// <summary>Create a critical section.</summary>
		CriticalSection();
		~CriticalSection();
		
		/// <summary>Try enter a critical section. This function will return immediately.</summary>
		/// <returns>Returns true if the current thread owned the critical section.</returns>
		bool										TryEnter();
		/// <summary>Enter a critical section.</summary>
		void										Enter();
		/// <summary>Leave a critical section.</summary>
		void										Leave();
		
	 public:
		class Scope : public Object, public NotCopyable
		{
		 private:
			CriticalSection*						criticalSection;
		 public:
			Scope(CriticalSection& _criticalSection);
			~Scope();
		};
	};
	
	/// <summary><![CDATA[
	/// Reader writer lock.
	/// The macro "READER_LOCK" and "WRITER_LOCK" are encouraged to use instead of calling [M:vl.ReaderWriterLock.EnterReader], [M:vl.ReaderWriterLock.LeaveReader], [M:vl.ReaderWriterLock.EnterWriter] and [M:vl.ReaderWriterLock.LeaveWriter] like this:
	/// READER_LOCK(yourLock)
	/// {
	///		<code>
	/// }
	/// or
	/// WRITER_LOCK(yourLock)
	/// {
	///		<code>
	/// }
	/// ]]></summary>
	class ReaderWriterLock : public Object, public NotCopyable
	{
	 private:
		friend class ConditionVariable;
		threading_internal::ReaderWriterLockData*	internalData;
	 public:
		/// <summary>Create a reader writer lock.</summary>
		ReaderWriterLock();
		~ReaderWriterLock();
		
		/// <summary>Try acquire a reader lock. This function will return immediately.</summary>
		/// <returns>Returns true if the current thread acquired the reader lock.</returns>
		bool										TryEnterReader();
		/// <summary>Acquire a reader lock.</summary>
		void										EnterReader();
		/// <summary>Release a reader lock.</summary>
		void										LeaveReader();
		/// <summary>Try acquire a writer lock. This function will return immediately.</summary>
		/// <returns>Returns true if the current thread acquired the writer lock.</returns>
		bool										TryEnterWriter();
		/// <summary>Acquire a writer lock.</summary>
		void										EnterWriter();
		/// <summary>Release a writer lock.</summary>
		void										LeaveWriter();
	 public:
		class ReaderScope : public Object, public NotCopyable
		{
		 private:
			ReaderWriterLock*						lock;
		 public:
			ReaderScope(ReaderWriterLock& _lock);
			~ReaderScope();
		};
		
		class WriterScope : public Object, public NotCopyable
		{
		 private:
			ReaderWriterLock*						lock;
		 public:
			WriterScope(ReaderWriterLock& _lock);
			~WriterScope();
		};
	};
	
	/// <summary>Conditional variable.</summary>
	class ConditionVariable : public Object, public NotCopyable
	{
	 private:
		threading_internal::ConditionVariableData*	internalData;
	 public:
		/// <summary>Create a conditional variable.</summary>
		ConditionVariable();
		~ConditionVariable();
		
		/// <summary>Bind a conditional variable with a owned critical section and release it. When the function returns, the condition variable is activated, and the current thread owned the critical section again.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="cs">The critical section.</param>
		bool										SleepWith(CriticalSection& cs);
#ifdef VCZH_MSVC
		/// <summary>Bind a conditional variable with a owned critical section and release it for a period of time. When the function returns, the condition variable is activated or it is time out, and the current thread owned the critical section again. This function is only available in Windows.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="cs">The critical section.</param>
		/// <param name="ms">Time in milliseconds.</param>
		bool										SleepWithForTime(CriticalSection& cs, vint ms);
		/// <summary>Bind a conditional variable with a owned reader lock and release it. When the function returns, the condition variable is activated, and the current thread owned the reader lock again. This function is only available in Windows.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="lock">The reader lock.</param>
		bool										SleepWithReader(ReaderWriterLock& lock);
		/// <summary>Bind a conditional variable with a owned reader lock and release it for a period of time. When the function returns, the condition variable is activated or it is time out, and the current thread owned the reader lock again. This function is only available in Windows.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="lock">The reader lock.</param>
		/// <param name="ms">Time in milliseconds.</param>
		bool										SleepWithReaderForTime(ReaderWriterLock& lock, vint ms);
		/// <summary>Bind a conditional variable with a owned writer lock and release it. When the function returns, the condition variable is activated, and the current thread owned the writer lock again. This function is only available in Windows.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="lock">The writer lock.</param>
		bool										SleepWithWriter(ReaderWriterLock& lock);
		/// <summary>Bind a conditional variable with a owned writer lock and release it for a period of time. When the function returns, the condition variable is activated or it is time out, and the current thread owned the writer lock again. This function is only available in Windows.</summary>
		/// <returns>Returns true if this operation succeeded.</returns>
		/// <param name="lock">The writer lock.</param>
		/// <param name="ms">Time in milliseconds.</param>
		bool										SleepWithWriterForTime(ReaderWriterLock& lock, vint ms);
#endif
		/// <summary>Wake one thread that pending on this condition variable.</summary>
		void										WakeOnePending();
		/// <summary>Wake all thread that pending on this condition variable.</summary>
		void										WakeAllPendings();
	};
	
	/***********************************************************************
	用户模式对象
	***********************************************************************/
	
	typedef long LockedInt;
	
	/// <summary><![CDATA[
	/// Spin lock. It is similar to mutex.
	/// The macro "SPIN_LOCK" is encouraged to use instead of calling [M:vl.SpinLock.Enter] and [M:vl.SpinLock.Leave] like this:
	/// SPIN_LOCK(yourLock)
	/// {
	///		<code>
	/// }
	/// ]]></summary>
	class SpinLock : public Object, public NotCopyable
	{
	 protected:
		volatile LockedInt							token;
	 public:
		/// <summary>Create a spin lock.</summary>
		SpinLock();
		~SpinLock();
		
		/// <summary>Try enter a spin lock. This function will return immediately.</summary>
		/// <returns>Returns true if the current thread owned the spin lock.</returns>
		bool										TryEnter();
		/// <summary>Enter a spin lock.</summary>
		void										Enter();
		/// <summary>Leave a spin lock.</summary>
		void										Leave();
		
	 public:
		class Scope : public Object, public NotCopyable
		{
		 private:
			SpinLock*								spinLock;
		 public:
			Scope(SpinLock& _spinLock);
			~Scope();
		};
	};
	
#define SPIN_LOCK(LOCK) SCOPE_VARIABLE(const SpinLock::Scope&, scope, LOCK)
#define CS_LOCK(LOCK) SCOPE_VARIABLE(const CriticalSection::Scope&, scope, LOCK)
#define READER_LOCK(LOCK) SCOPE_VARIABLE(const ReaderWriterLock::ReaderScope&, scope, LOCK)
#define WRITER_LOCK(LOCK) SCOPE_VARIABLE(const ReaderWriterLock::WriterScope&, scope, LOCK)
	
	/***********************************************************************
	Thread Local Storage
	
	ThreadLocalStorage and ThreadVariable<T> are designed to be used as global value types only.
	Dynamically create instances of them are undefined behavior.
	***********************************************************************/
	
	/// <summary>Thread local storage operations.</summary>
	class ThreadLocalStorage : public Object, private NotCopyable
	{
		typedef void(*Destructor)(void*);
	 protected:
		vuint64_t								key;
		Destructor								destructor;
		volatile bool							disposed /*= false*/;
		
		static void								PushStorage(ThreadLocalStorage* storage);
	 public:
		ThreadLocalStorage(Destructor _destructor);
		~ThreadLocalStorage();
		
		void*									Get();
		void									Set(void* data);
		void									Clear();
		void									Dispose();
		
		/// <summary>Fix all storage creation.</summary>
		static void								FixStorages();
		/// <summary>Clear all storages for the current thread. For threads that are created using [T:vl.Thread], this function will be automatically called when before the thread exit.</summary>
		static void								ClearStorages();
		/// <summary>Clear all storages for the current thread (should be the main thread) and clear all records. This function can only be called by the main thread when all other threads are exited. It will reduce noices when you want to detect memory leaks.</summary>
		static void								DisposeStorages();
	};
	
	/// <summary>Thread local variable. This type can only be used to define global variables. Different threads can store different values to and obtain differnt values from a thread local variable.</summary>
	/// <typeparam name="T">Type of the storage.</typeparam>
	template<typename T>
	class ThreadVariable : public Object, private NotCopyable
	{
	 protected:
		ThreadLocalStorage						storage;
		
		static void Destructor(void* data)
		{
			if (data)
			{
				delete (T*)data;
			}
		}
	 public:
		/// <summary>Create a thread local variable.</summary>
		ThreadVariable()
			: storage(&Destructor)
		{
		}
		
		~ThreadVariable()
		{
		}
		
		/// <summary>Test if the storage has data.</summary>
		/// <returns>Returns true if the storage has data.</returns>
		bool HasData()
		{
			return storage.Get() != NULL;
		}
		
		/// <summary>Remove the data from this storage.</summary>
		void Clear()
		{
			storage.Clear();
		}
		
		/// <summary>Get the stored data.</summary>
		/// <returns>The stored ata.</returns>
		T& Get()
		{
			return *(T*)storage.Get();
		}
		
		/// <summary>Set data to this storage.</summary>
		/// <param name="value">The data to set.</param>
		void Set(const T& value)
		{
			storage.Clear();
			storage.Set(new T(value));
		}
	};
	
	template<typename T>
	class ThreadVariable<T*> : public Object, private NotCopyable
	{
	 protected:
		ThreadLocalStorage						storage;
		
	 public:
		ThreadVariable()
			: storage(NULL)
		{
		}
		
		~ThreadVariable()
		{
		}
		
		bool HasData()
		{
			return storage.Get() != NULL;
		}
		
		void Clear()
		{
			storage.Set(NULL);
		}
		
		T* Get()
		{
			return (T*)storage.Get();
		}
		
		void Set(T* value)
		{
			storage.Set((void*)value);
		}
	};
	
	/***********************************************************************
	RepeatingTaskExecutor
	***********************************************************************/
	
	/// <summary>Queued task executor. It is different from a thread pool by: 1) Task execution is single threaded, 2) If you queue a task, it will override the the unexecuted queued task.</summary>
	/// <typeparam name="T">The type of the argument to run a task.</typeparam>
	template<typename T>
	class RepeatingTaskExecutor : public Object
	{
	 private:
		SpinLock								inputLock;
		T										inputData;
		volatile bool							inputDataAvailable;
		SpinLock								executingEvent;
		volatile bool							executing;
		
		void ExecutingProcInternal()
		{
			while (true)
			{
				bool currentInputDataAvailable;
				T currentInputData;
				SPIN_LOCK(inputLock)
				{
					currentInputData = inputData;
					inputData = T();
					currentInputDataAvailable = inputDataAvailable;
					inputDataAvailable = false;
					
					if (!currentInputDataAvailable)
					{
						executing = false;
						goto FINISH_EXECUTING;
					}
				}
				Execute(currentInputData);
			}
			
FINISH_EXECUTING:
			executingEvent.Leave();
		}
		
		static void ExecutingProc(void* argument)
		{
			((RepeatingTaskExecutor<T>*)argument)->ExecutingProcInternal();
		}
		
	 protected:
		/// <summary>This function is called when it is ready to execute a task. Task execution is single threaded. All task code should be put inside the function.</summary>
		/// <param name="input">The argument to run a task.</param>
		virtual void							Execute(const T& input) = 0;
		
	 public:
		/// <summary>Create a task executor.</summary>
		RepeatingTaskExecutor()
			: inputDataAvailable(false)
			, executing(false)
		{
		}
		
		~RepeatingTaskExecutor()
		{
			EnsureTaskFinished();
		}
		
		/// <summary>Wait for all tasks to finish.</summary>
		void EnsureTaskFinished()
		{
			executingEvent.Enter();
			executingEvent.Leave();
		}
		
		/// <summary>Queue a task. If there is a queued task that has not been executied yet, those tasks will be canceled. Only one task can be queued at the same moment.</summary>
		/// <param name="input">The argument to run a task.</param>
		void SubmitTask(const T& input)
		{
			SPIN_LOCK(inputLock)
			{
				inputData = input;
				inputDataAvailable = true;
			}
			
			if (!executing)
			{
				executing = true;
				executingEvent.Enter();
				ThreadPoolLite::Queue(&ExecutingProc, this);
			}
		}
	};
}
#endif

/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
UI::Console

***********************************************************************/

#ifndef VCZH_UNITTEST
#define VCZH_UNITTEST

// #include "../String.h"

class UnitTestError
{
};

namespace vl
{
	namespace unittest
	{
		/// <summary><![CDATA[
		/// A static class containing all unit test operations. In order to run test cases, you should do the following:
		/// 1) Write test cases in cpp files like this
		/// TEST_CASE(<Name of the test case, which should be a legal C++ identifier>)
		/// {
		///		<Use TEST_ASSERT(condition) to test>
		///		<Use TEST_ERROR(expression) if you know "expression" will cause a fatal error by using the CHECK_ERROR macro.>
		///		<Use TEST_EXCEPTION(expression, exceptionType, assertFunction) if you know "expression" will throw an expression of "exceptionType", and then you can provide "assertFunction" to check the information provided in the exception.>
		///		<Use TEST_PRINT(message) to print whatever to the command line window.>
		/// }
		/// You should call [M:vl.unittest.UnitTest.RunAndDisposeTests] in your main function to run all test cases.
		/// ]]></summary>
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
#define TEST_ERROR(CONDITION) do{try{CONDITION;throw UnitTestError();}catch(const Error&){}catch(const UnitTestError&){TEST_CHECK_ERROR(false,L"");}}while(0)
#define TEST_CASE(NAME)\
	extern void TESTCASE_##NAME();														\
	namespace vl_unittest_executors														\
	{																					\
		class TESTCASE_RUNNER_##NAME													\
		{																				\
		 public:																			\
			static void RunUnitTest()													\
			{																			\
				vl::unittest::UnitTest::PrintMessage(L_(#NAME));						\
				TESTCASE_##NAME();														\
			}																			\
			TESTCASE_RUNNER_##NAME()													\
			{																			\
				vl::unittest::UnitTest::PushTest(&TESTCASE_RUNNER_##NAME::RunUnitTest);	\
			}																			\
		} TESTCASE_RUNNER_##NAME##_INSTANCE;											\
	}																					\
	void TESTCASE_##NAME()
#define TEST_PRINT(x) vl::unittest::UnitTest::PrintInfo(x)
#define TEST_EXCEPTION(STATEMENT,EXCEPTION,ASSERT_FUNCTION) try{STATEMENT; TEST_ASSERT(false);}catch(const EXCEPTION& e){ASSERT_FUNCTION(e);}
	}
}

#endif
