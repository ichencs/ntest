#pragma once


/// <summary>Test is a type a Plain-Old-Data type for containers.</summary>
/// <typeparam name="T">The type to test.</typeparam>
template<typename T>
struct POD
{
	/// <summary>Returns true if the type is a Plain-Old-Data type.</summary>
	static const bool Result = false;
};

// 下面这些事POD类型
template<>struct POD<bool> { static const bool Result = true; };
template<>struct POD<int> { static const bool Result = true; };
// template<>struct POD<vuint8_t> { static const bool Result = true; };
// template<>struct POD<vint16_t> { static const bool Result = true; };
// template<>struct POD<vuint16_t> { static const bool Result = true; };
// template<>struct POD<vint32_t> { static const bool Result = true; };
// template<>struct POD<vuint32_t> { static const bool Result = true; };
// template<>struct POD<vint64_t> { static const bool Result = true; };
// template<>struct POD<vuint64_t> { static const bool Result = true; };
template<>struct POD<char> { static const bool Result = true; };
template<>struct POD<wchar_t> { static const bool Result = true; };
template<typename T>struct POD<T*> { static const bool Result = true; };
template<typename T>struct POD<T&> { static const bool Result = true; };
template<typename T, typename C>struct POD<T C::*> { static const bool Result = true; };
template<typename T,int _Size>struct POD<T[_Size]> { static const bool Result = POD<T>::Result; };
template<typename T>struct POD<const T> { static const bool Result = POD<T>::Result; };
template<typename T>struct POD<volatile T> { static const bool Result = POD<T>::Result; };
template<typename T>struct POD<const volatile T> { static const bool Result = POD<T>::Result; };

 /*---------------------------------------------*\
 不可拷贝的类（基类）
 \*---------------------------------------------*/
class NotCopyable
{
private:
	NotCopyable(const NotCopyable&);
	NotCopyable& operator=(const NotCopyable&);
public:
	NotCopyable();
};


/// <summary>Base type of all classes.</summary>
class Object
{
public:
	virtual ~Object();
};


struct YesType {};
