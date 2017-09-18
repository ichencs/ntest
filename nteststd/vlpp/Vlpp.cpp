#include "vlpp.h"
#include <Windows.h>

namespace vl
{

	/***********************************************************************
	NotCopyable
	***********************************************************************/
	
	NotCopyable::NotCopyable()
	{
	}
	
	NotCopyable::NotCopyable(const NotCopyable&)
	{
	}
	
	NotCopyable& NotCopyable::operator=(const NotCopyable&)
	{
		return *this;
	}
	
	/***********************************************************************
	Error
	***********************************************************************/
	
	Error::Error(const wchar_t* _description)
	{
		description = _description;
	}
	
	const wchar_t* Error::Description()const
	{
		return description;
	}
	
	/***********************************************************************
	Object
	***********************************************************************/
	
	Object::~Object()
	{
	}
	
	/***********************************************************************
	DateTime
	***********************************************************************/
	
	DateTime SystemTimeToDateTime(const SYSTEMTIME& systemTime)
	{
		DateTime dateTime;
		dateTime.year = systemTime.wYear;
		dateTime.month = systemTime.wMonth;
		dateTime.dayOfWeek = systemTime.wDayOfWeek;
		dateTime.day = systemTime.wDay;
		dateTime.hour = systemTime.wHour;
		dateTime.minute = systemTime.wMinute;
		dateTime.second = systemTime.wSecond;
		dateTime.milliseconds = systemTime.wMilliseconds;
		
		FILETIME fileTime;
		SystemTimeToFileTime(&systemTime, &fileTime);
		ULARGE_INTEGER largeInteger;
		largeInteger.HighPart = fileTime.dwHighDateTime;
		largeInteger.LowPart = fileTime.dwLowDateTime;
		dateTime.filetime = largeInteger.QuadPart;
		dateTime.totalMilliseconds = dateTime.filetime / 10000;
		
		return dateTime;
	}
	
	SYSTEMTIME DateTimeToSystemTime(const DateTime& dateTime)
	{
		ULARGE_INTEGER largeInteger;
		largeInteger.QuadPart = dateTime.filetime;
		FILETIME fileTime;
		fileTime.dwHighDateTime = largeInteger.HighPart;
		fileTime.dwLowDateTime = largeInteger.LowPart;
		
		SYSTEMTIME systemTime;
		FileTimeToSystemTime(&fileTime, &systemTime);
		return systemTime;
	}
	
	DateTime DateTime::LocalTime()
	{
#if defined VCZH_MSVC
		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);
		return SystemTimeToDateTime(systemTime);
#endif
	}
	
	DateTime DateTime::UtcTime()
	{
#if defined VCZH_MSVC
		SYSTEMTIME utcTime;
		GetSystemTime(&utcTime);
		return SystemTimeToDateTime(utcTime);
#endif
	}
	
	DateTime DateTime::FromDateTime(vint _year, vint _month, vint _day, vint _hour, vint _minute, vint _second, vint _milliseconds)
	{
#if defined VCZH_MSVC
		SYSTEMTIME systemTime;
		memset(&systemTime, 0, sizeof(systemTime));
		systemTime.wYear = (WORD)_year;
		systemTime.wMonth = (WORD)_month;
		systemTime.wDay = (WORD)_day;
		systemTime.wHour = (WORD)_hour;
		systemTime.wMinute = (WORD)_minute;
		systemTime.wSecond = (WORD)_second;
		systemTime.wMilliseconds = (WORD)_milliseconds;
		
		FILETIME fileTime;
		SystemTimeToFileTime(&systemTime, &fileTime);
		FileTimeToSystemTime(&fileTime, &systemTime);
		return SystemTimeToDateTime(systemTime);
#endif
	}
	
	DateTime DateTime::FromFileTime(vuint64_t filetime)
	{
#if defined VCZH_MSVC
		ULARGE_INTEGER largeInteger;
		largeInteger.QuadPart = filetime;
		FILETIME fileTime;
		fileTime.dwHighDateTime = largeInteger.HighPart;
		fileTime.dwLowDateTime = largeInteger.LowPart;
		
		SYSTEMTIME systemTime;
		FileTimeToSystemTime(&fileTime, &systemTime);
		return SystemTimeToDateTime(systemTime);
#endif
	}
	
	DateTime::DateTime()
		: year(0)
		, month(0)
		, day(0)
		, hour(0)
		, minute(0)
		, second(0)
		, milliseconds(0)
		, filetime(0)
	{
	}
	
	DateTime DateTime::ToLocalTime()
	{
#if defined VCZH_MSVC
		SYSTEMTIME utcTime = DateTimeToSystemTime(*this);
		SYSTEMTIME localTime;
		SystemTimeToTzSpecificLocalTime(NULL, &utcTime, &localTime);
		return SystemTimeToDateTime(localTime);
#endif
	}
	
	DateTime DateTime::ToUtcTime()
	{
#if defined VCZH_MSVC
		SYSTEMTIME localTime = DateTimeToSystemTime(*this);
		SYSTEMTIME utcTime;
		TzSpecificLocalTimeToSystemTime(NULL, &localTime, &utcTime);
		return SystemTimeToDateTime(utcTime);
#endif
	}
	
	DateTime DateTime::Forward(vuint64_t milliseconds)
	{
#if defined VCZH_MSVC
		return FromFileTime(filetime + milliseconds * 10000);
#endif
	}
	
	DateTime DateTime::Backward(vuint64_t milliseconds)
	{
#if defined VCZH_MSVC
		return FromFileTime(filetime - milliseconds * 10000);
#endif
	}
	
	/***********************************************************************
	Interface
	***********************************************************************/
	
	Interface::~Interface()
	{
	}
}


#include <stdlib.h>
#include "String.h"
#if defined VCZH_MSVC
#include <Windows.h>
#endif

namespace vl
{

	vint atoi_test(const AString& string, bool& success)
	{
		char* endptr = 0;
		vint result = strtol(string.Buffer(), &endptr, 10);
		success = endptr == string.Buffer() + string.Length() && itoa(result) == string;
		return result;
	}
	
	vint wtoi_test(const WString& string, bool& success)
	{
		wchar_t* endptr = 0;
		vint result = wcstol(string.Buffer(), &endptr, 10);
		success = endptr == string.Buffer() + string.Length() && itow(result) == string;
		return result;
	}
	
	vint64_t atoi64_test(const AString& string, bool& success)
	{
		char* endptr = 0;
		vint64_t result = _strtoi64(string.Buffer(), &endptr, 10);
		success = endptr == string.Buffer() + string.Length() && i64toa(result) == string;
		return result;
	}
	
	vint64_t wtoi64_test(const WString& string, bool& success)
	{
		wchar_t* endptr = 0;
		vint64_t result = _wcstoi64(string.Buffer(), &endptr, 10);
		success = endptr == string.Buffer() + string.Length() && i64tow(result) == string;
		return result;
	}
	
	vuint atou_test(const AString& string, bool& success)
	{
		char* endptr = 0;
		vuint result = strtoul(string.Buffer(), &endptr, 10);
		success = endptr == string.Buffer() + string.Length() && utoa(result) == string;
		return result;
	}
	
	vuint wtou_test(const WString& string, bool& success)
	{
		wchar_t* endptr = 0;
		vuint result = wcstoul(string.Buffer(), &endptr, 10);
		success = endptr == string.Buffer() + string.Length() && utow(result) == string;
		return result;
	}
	
	vuint64_t atou64_test(const AString& string, bool& success)
	{
		char* endptr = 0;
		vuint64_t result = _strtoui64(string.Buffer(), &endptr, 10);
		success = endptr == string.Buffer() + string.Length() && u64toa(result) == string;
		return result;
	}
	
	vuint64_t wtou64_test(const WString& string, bool& success)
	{
		wchar_t* endptr = 0;
		vuint64_t result = _wcstoui64(string.Buffer(), &endptr, 10);
		success = endptr == string.Buffer() + string.Length() && u64tow(result) == string;
		return result;
	}
	
	double atof_test(const AString& string, bool& success)
	{
		char* endptr = 0;
		double result = strtod(string.Buffer(), &endptr);
		success = endptr == string.Buffer() + string.Length();
		return result;
	}
	
	double wtof_test(const WString& string, bool& success)
	{
		wchar_t* endptr = 0;
		double result = wcstod(string.Buffer(), &endptr);
		success = endptr == string.Buffer() + string.Length();
		return result;
	}
	
	vint atoi(const AString& string)
	{
		bool success = false;
		return atoi_test(string, success);
	}
	
	vint wtoi(const WString& string)
	{
		bool success = false;
		return wtoi_test(string, success);
	}
	
	vint64_t atoi64(const AString& string)
	{
		bool success = false;
		return atoi64_test(string, success);
	}
	
	vint64_t wtoi64(const WString& string)
	{
		bool success = false;
		return wtoi64_test(string, success);
	}
	
	vuint atou(const AString& string)
	{
		bool success = false;
		return atou_test(string, success);
	}
	
	vuint wtou(const WString& string)
	{
		bool success = false;
		return wtou_test(string, success);
	}
	
	vuint64_t atou64(const AString& string)
	{
		bool success = false;
		return atou64_test(string, success);
	}
	
	vuint64_t wtou64(const WString& string)
	{
		bool success = false;
		return wtou64_test(string, success);
	}
	
	double atof(const AString& string)
	{
		bool success = false;
		return atof_test(string, success);
	}
	
	double wtof(const WString& string)
	{
		bool success = false;
		return wtof_test(string, success);
	}
	
	AString itoa(vint number)
	{
		char buffer[100];
		ITOA_S(number, buffer, sizeof(buffer) / sizeof(*buffer), 10);
		return buffer;
	}
	
	WString itow(vint number)
	{
		wchar_t buffer[100];
		ITOW_S(number, buffer, sizeof(buffer) / sizeof(*buffer), 10);
		return buffer;
	}
	
	AString i64toa(vint64_t number)
	{
		char buffer[100];
		I64TOA_S(number, buffer, sizeof(buffer) / sizeof(*buffer), 10);
		return buffer;
	}
	
	WString i64tow(vint64_t number)
	{
		wchar_t buffer[100];
		I64TOW_S(number, buffer, sizeof(buffer) / sizeof(*buffer), 10);
		return buffer;
	}
	
	AString utoa(vuint number)
	{
		char buffer[100];
		UITOA_S(number, buffer, sizeof(buffer) / sizeof(*buffer), 10);
		return buffer;
	}
	
	WString utow(vuint number)
	{
		wchar_t buffer[100];
		UITOW_S(number, buffer, sizeof(buffer) / sizeof(*buffer), 10);
		return buffer;
	}
	
	AString u64toa(vuint64_t number)
	{
		char buffer[100];
		UI64TOA_S(number, buffer, sizeof(buffer) / sizeof(*buffer), 10);
		return buffer;
	}
	
	WString u64tow(vuint64_t number)
	{
		wchar_t buffer[100];
		UI64TOW_S(number, buffer, sizeof(buffer) / sizeof(*buffer), 10);
		return buffer;
	}
	
	AString ftoa(double number)
	{
		char buffer[320];
		_gcvt_s(buffer, 320, number, 30);
		vint len = (vint)strlen(buffer);
		
		if (buffer[len - 1] == '.')
		{
			buffer[len - 1] = '\0';
		}
		
		return buffer;
	}
	
	WString ftow(double number)
	{
		return atow(ftoa(number));
	}
	
	vint _wtoa(const wchar_t* w, char* a, vint chars)
	{
#if defined VCZH_MSVC
		return WideCharToMultiByte(CP_THREAD_ACP, 0, w, -1, a, (int)(a ? chars : 0), 0, 0);
#endif
	}
	
	AString wtoa(const WString& string)
	{
		vint len = _wtoa(string.Buffer(), 0, 0);
		char* buffer = new char[len];
		memset(buffer, 0, len * sizeof(*buffer));
		_wtoa(string.Buffer(), buffer, (int)len);
		AString s = buffer;
		delete[] buffer;
		return s;
	}
	
	vint _atow(const char* a, wchar_t* w, vint chars)
	{
#if defined VCZH_MSVC
		return MultiByteToWideChar(CP_THREAD_ACP, 0, a, -1, w, (int)(w ? chars : 0));
#endif
	}
	
	WString atow(const AString& string)
	{
		vint len = _atow(string.Buffer(), 0, 0);
		wchar_t* buffer = new wchar_t[len];
		memset(buffer, 0, len * sizeof(*buffer));
		_atow(string.Buffer(), buffer, (int)len);
		WString s = buffer;
		delete[] buffer;
		return s;
	}
	
	AString alower(const AString& string)
	{
		AString result = string.Buffer();
		_strlwr_s((char*)result.Buffer(), result.Length() + 1);
		return result;
	}
	
	WString wlower(const WString& string)
	{
		WString result = string.Buffer();
		_wcslwr_s((wchar_t*)result.Buffer(), result.Length() + 1);
		return result;
	}
	
	AString aupper(const AString& string)
	{
		AString result = string.Buffer();
		_strupr_s((char*)result.Buffer(), result.Length() + 1);
		return result;
	}
	
	WString wupper(const WString& string)
	{
		WString result = string.Buffer();
		_wcsupr_s((wchar_t*)result.Buffer(), result.Length() + 1);
		return result;
	}
}


#include "Locale.h"
#include <Windows.h>

namespace vl
{
	using namespace collections;
	
#if defined VCZH_MSVC
	
	extern SYSTEMTIME DateTimeToSystemTime(const DateTime& dateTime);
	
	BOOL CALLBACK Locale_EnumLocalesProcEx(
	  _In_  LPWSTR lpLocaleString,
	  _In_  DWORD dwFlags,
	  _In_  LPARAM lParam
	)
	{
		((List<Locale>*)lParam)->Add(Locale(lpLocaleString));
		return TRUE;
	}
	
	BOOL CALLBACK Locale_EnumDateFormatsProcExEx(
	  _In_  LPWSTR lpDateFormatString,
	  _In_  CALID CalendarID,
	  _In_  LPARAM lParam
	)
	{
		((List<WString>*)lParam)->Add(lpDateFormatString);
		return TRUE;
	}
	
	BOOL CALLBACK EnumTimeFormatsProcEx(
	  _In_  LPWSTR lpTimeFormatString,
	  _In_  LPARAM lParam
	)
	{
		((List<WString>*)lParam)->Add(lpTimeFormatString);
		return TRUE;
	}
	
	WString Transform(const WString& localeName, const WString& input, DWORD flag)
	{
		int length = LCMapStringEx(localeName.Buffer(), flag, input.Buffer(), (int)input.Length() + 1, NULL, 0, NULL, NULL, NULL);
		Array<wchar_t> buffer(length);
		LCMapStringEx(localeName.Buffer(), flag, input.Buffer(), (int)input.Length() + 1, &buffer[0], (int)buffer.Count(), NULL, NULL, NULL);
		return &buffer[0];
	}
	
	DWORD TranslateNormalization(Locale::Normalization normalization)
	{
		DWORD result = 0;
		
		if (normalization & Locale::IgnoreCase)
		{
			result |= NORM_IGNORECASE;
		}
		
		if (normalization & Locale::IgnoreCaseLinguistic)
		{
			result |= NORM_IGNORECASE | NORM_LINGUISTIC_CASING;
		}
		
		if (normalization & Locale::IgnoreKanaType)
		{
			result |= NORM_IGNOREKANATYPE;
		}
		
		if (normalization & Locale::IgnoreNonSpace)
		{
			result |= NORM_IGNORENONSPACE;
		}
		
		if (normalization & Locale::IgnoreSymbol)
		{
			result |= NORM_IGNORESYMBOLS;
		}
		
		if (normalization & Locale::IgnoreWidth)
		{
			result |= NORM_IGNOREWIDTH;
		}
		
#if _MSC_VER > 1700
		
		if (normalization & Locale::DigitsAsNumbers)
		{
			result |= SORT_DIGITSASNUMBERS;
		}
		
#endif
		
		if (normalization & Locale::StringSoft)
		{
			result |= SORT_STRINGSORT;
		}
		
		return result;
	}
	
#endif
	
	/***********************************************************************
	Locale
	***********************************************************************/
	
	Locale::Locale(const WString& _localeName)
		: localeName(_localeName)
	{
	}
	
	Locale::~Locale()
	{
	}
	
	Locale Locale::Invariant()
	{
#if defined VCZH_MSVC
		return Locale(LOCALE_NAME_INVARIANT);
#elif defined VCZH_GCC
		return Locale(L"");
#endif
	}
	
	Locale Locale::SystemDefault()
	{
#if defined VCZH_MSVC
		wchar_t buffer[LOCALE_NAME_MAX_LENGTH + 1] = { 0 };
		GetSystemDefaultLocaleName(buffer, LOCALE_NAME_MAX_LENGTH);
		return Locale(buffer);
#elif defined VCZH_GCC
		return Locale(L"en-US");
#endif
	}
	
	Locale Locale::UserDefault()
	{
#if defined VCZH_MSVC
		wchar_t buffer[LOCALE_NAME_MAX_LENGTH + 1] = { 0 };
		GetUserDefaultLocaleName(buffer, LOCALE_NAME_MAX_LENGTH);
		return Locale(buffer);
#elif defined VCZH_GCC
		return Locale(L"en-US");
#endif
	}
	
	void Locale::Enumerate(collections::List<Locale>& locales)
	{
#if defined VCZH_MSVC
		EnumSystemLocalesEx(&Locale_EnumLocalesProcEx, LOCALE_ALL, (LPARAM)&locales, NULL);
#elif defined VCZH_GCC
		locales.Add(Locale(L"en-US"));
#endif
	}
	
	const WString& Locale::GetName()const
	{
		return localeName;
	}
	
	void Locale::GetShortDateFormats(collections::List<WString>& formats)const
	{
#if defined VCZH_MSVC
		EnumDateFormatsExEx(&Locale_EnumDateFormatsProcExEx, localeName.Buffer(), DATE_SHORTDATE, (LPARAM)&formats);
#elif defined VCZH_GCC
		formats.Add(L"MM/dd/yyyy");
		formats.Add(L"yyyy-MM-dd");
#endif
	}
	
	void Locale::GetLongDateFormats(collections::List<WString>& formats)const
	{
#if defined VCZH_MSVC
		EnumDateFormatsExEx(&Locale_EnumDateFormatsProcExEx, localeName.Buffer(), DATE_LONGDATE, (LPARAM)&formats);
#elif defined VCZH_GCC
		formats.Add(L"dddd, dd MMMM yyyy");
#endif
	}
	
	void Locale::GetYearMonthDateFormats(collections::List<WString>& formats)const
	{
#if defined VCZH_MSVC
		EnumDateFormatsExEx(&Locale_EnumDateFormatsProcExEx, localeName.Buffer(), DATE_YEARMONTH, (LPARAM)&formats);
#elif defined VCZH_GCC
		formats.Add(L"yyyy MMMM");
#endif
	}
	
	void Locale::GetLongTimeFormats(collections::List<WString>& formats)const
	{
#if defined VCZH_MSVC
		EnumTimeFormatsEx(&EnumTimeFormatsProcEx, localeName.Buffer(), 0, (LPARAM)&formats);
#elif defined VCZH_GCC
		formats.Add(L"HH:mm:ss");
#endif
	}
	
	void Locale::GetShortTimeFormats(collections::List<WString>& formats)const
	{
#if defined VCZH_MSVC
		EnumTimeFormatsEx(&EnumTimeFormatsProcEx, localeName.Buffer(), TIME_NOSECONDS, (LPARAM)&formats);
#elif defined VCZH_GCC
		formats.Add(L"HH:mm");
		formats.Add(L"hh:mm tt");
#endif
	}
	
	WString Locale::FormatDate(const WString& format, DateTime date)const
	{
#if defined VCZH_MSVC
		SYSTEMTIME st = DateTimeToSystemTime(date);
		int length = GetDateFormatEx(localeName.Buffer(), 0, &st, format.Buffer(), NULL, 0, NULL);
		
		if (length == 0)
		{
			return L"";
		}
		
		Array<wchar_t> buffer(length);
		GetDateFormatEx(localeName.Buffer(), 0, &st, format.Buffer(), &buffer[0], (int)buffer.Count(), NULL);
		return &buffer[0];
#endif
	}
	
	WString Locale::FormatTime(const WString& format, DateTime time)const
	{
#if defined VCZH_MSVC
		SYSTEMTIME st = DateTimeToSystemTime(time);
		int length = GetTimeFormatEx(localeName.Buffer(), 0, &st, format.Buffer(), NULL, 0);
		
		if (length == 0)
		{
			return L"";
		}
		
		Array<wchar_t> buffer(length);
		GetTimeFormatEx(localeName.Buffer(), 0, &st, format.Buffer(), &buffer[0], (int)buffer.Count());
		return &buffer[0];
#elif defined VCZH_GCC
		return FormatDate(format, time);
#endif
	}
	
#ifdef VCZH_MSVC
	WString Locale::FormatNumber(const WString& number)const
	{
		int length = GetNumberFormatEx(localeName.Buffer(), 0, number.Buffer(), NULL, NULL, 0);
		
		if (length == 0)
		{
			return L"";
		}
		
		Array<wchar_t> buffer(length);
		GetNumberFormatEx(localeName.Buffer(), 0, number.Buffer(), NULL, &buffer[0], (int)buffer.Count());
		return &buffer[0];
	}
	
	WString Locale::FormatCurrency(const WString& currency)const
	{
		int length = GetCurrencyFormatEx(localeName.Buffer(), 0, currency.Buffer(), NULL, NULL, 0);
		
		if (length == 0)
		{
			return L"";
		}
		
		Array<wchar_t> buffer(length);
		GetCurrencyFormatEx(localeName.Buffer(), 0, currency.Buffer(), NULL, &buffer[0], (int)buffer.Count());
		return &buffer[0];
	}
#endif
	
	WString Locale::GetShortDayOfWeekName(vint dayOfWeek)const
	{
#if defined VCZH_MSVC
		return FormatDate(L"ddd", DateTime::FromDateTime(2000, 1, 2 + dayOfWeek));
#endif
	}
	
	WString Locale::GetLongDayOfWeekName(vint dayOfWeek)const
	{
#if defined VCZH_MSVC
		return FormatDate(L"dddd", DateTime::FromDateTime(2000, 1, 2 + dayOfWeek));
#endif
	}
	
	WString Locale::GetShortMonthName(vint month)const
	{
#if defined VCZH_MSVC
		return FormatDate(L"MMM", DateTime::FromDateTime(2000, month, 1));
#endif
	}
	
	WString Locale::GetLongMonthName(vint month)const
	{
#if defined VCZH_MSVC
		return FormatDate(L"MMMM", DateTime::FromDateTime(2000, month, 1));
#endif
	}
	
#ifdef VCZH_MSVC
	WString Locale::ToFullWidth(const WString& str)const
	{
		return Transform(localeName, str, LCMAP_FULLWIDTH);
	}
	
	WString Locale::ToHalfWidth(const WString& str)const
	{
		return Transform(localeName, str, LCMAP_HALFWIDTH);
	}
	
	WString Locale::ToHiragana(const WString& str)const
	{
		return Transform(localeName, str, LCMAP_HIRAGANA);
	}
	
	WString Locale::ToKatagana(const WString& str)const
	{
		return Transform(localeName, str, LCMAP_KATAKANA);
	}
#endif
	
	WString Locale::ToLower(const WString& str)const
	{
#if defined VCZH_MSVC
		return Transform(localeName, str, LCMAP_LOWERCASE);
#elif defined VCZH_GCC
		return wlower(str);
#endif
	}
	
	WString Locale::ToUpper(const WString& str)const
	{
#if defined VCZH_MSVC
		return Transform(localeName, str, LCMAP_UPPERCASE);
#elif defined VCZH_GCC
		return wupper(str);
#endif
	}
	
	WString Locale::ToLinguisticLower(const WString& str)const
	{
#if defined VCZH_MSVC
		return Transform(localeName, str, LCMAP_LOWERCASE | LCMAP_LINGUISTIC_CASING);
#elif defined VCZH_GCC
		return wlower(str);
#endif
	}
	
	WString Locale::ToLinguisticUpper(const WString& str)const
	{
#if defined VCZH_MSVC
		return Transform(localeName, str, LCMAP_UPPERCASE | LCMAP_LINGUISTIC_CASING);
#elif defined VCZH_GCC
		return wupper(str);
#endif
	}
	
#ifdef VCZH_MSVC
	WString Locale::ToSimplifiedChinese(const WString& str)const
	{
		return Transform(localeName, str, LCMAP_SIMPLIFIED_CHINESE);
	}
	
	WString Locale::ToTraditionalChinese(const WString& str)const
	{
		return Transform(localeName, str, LCMAP_TRADITIONAL_CHINESE);
	}
	
	WString Locale::ToTileCase(const WString& str)const
	{
#if _MSC_VER > 1700
		return Transform(localeName, str, LCMAP_TITLECASE);
#else
		return WString();
#endif
	}
#endif
	
	vint Locale::Compare(const WString& s1, const WString& s2, Normalization normalization)const
	{
#if defined VCZH_MSVC
	
		switch (CompareStringEx(localeName.Buffer(), TranslateNormalization(normalization), s1.Buffer(), (int)s1.Length(), s2.Buffer(), (int)s2.Length(), NULL, NULL, NULL))
		{
			case CSTR_LESS_THAN: return -1;
			
			case CSTR_GREATER_THAN: return 1;
			
			default: return 0;
		}
		
#endif
	}
	
	vint Locale::CompareOrdinal(const WString& s1, const WString& s2)const
	{
#if defined VCZH_MSVC
	
		switch (CompareStringOrdinal(s1.Buffer(), (int)s1.Length(), s2.Buffer(), (int)s2.Length(), FALSE))
		{
			case CSTR_LESS_THAN: return -1;
			
			case CSTR_GREATER_THAN: return 1;
			
			default: return 0;
		}
		
#elif defined VCZH_GCC
		return wcscmp(s1.Buffer(), s2.Buffer());
#endif
	}
	
	vint Locale::CompareOrdinalIgnoreCase(const WString& s1, const WString& s2)const
	{
#if defined VCZH_MSVC
	
		switch (CompareStringOrdinal(s1.Buffer(), (int)s1.Length(), s2.Buffer(), (int)s2.Length(), TRUE))
		{
			case CSTR_LESS_THAN: return -1;
			
			case CSTR_GREATER_THAN: return 1;
			
			default: return 0;
		}
		
#endif
	}
	
	collections::Pair<vint, vint> Locale::FindFirst(const WString& text, const WString& find, Normalization normalization)const
	{
#if defined VCZH_MSVC
		int length = 0;
		int result = FindNLSStringEx(localeName.Buffer(), FIND_FROMSTART | TranslateNormalization(normalization), text.Buffer(), (int)text.Length(), find.Buffer(), (int)find.Length(), &length, NULL, NULL, NULL);
		return result == -1 ? Pair<vint, vint>(-1, 0) : Pair<vint, vint>(result, length);
#endif
	}
	
	collections::Pair<vint, vint> Locale::FindLast(const WString& text, const WString& find, Normalization normalization)const
	{
#if defined VCZH_MSVC
		int length = 0;
		int result = FindNLSStringEx(localeName.Buffer(), FIND_FROMEND | TranslateNormalization(normalization), text.Buffer(), (int)text.Length(), find.Buffer(), (int)find.Length(), &length, NULL, NULL, NULL);
		return result == -1 ? Pair<vint, vint>(-1, 0) : Pair<vint, vint>(result, length);
#endif
	}
	
	bool Locale::StartsWith(const WString& text, const WString& find, Normalization normalization)const
	{
#if defined VCZH_MSVC
		int result = FindNLSStringEx(localeName.Buffer(), FIND_STARTSWITH | TranslateNormalization(normalization), text.Buffer(), (int)text.Length(), find.Buffer(), (int)find.Length(), NULL, NULL, NULL, NULL);
		return result != -1;
#endif
	}
	
	bool Locale::EndsWith(const WString& text, const WString& find, Normalization normalization)const
	{
#if defined VCZH_MSVC
		int result = FindNLSStringEx(localeName.Buffer(), FIND_ENDSWITH | TranslateNormalization(normalization), text.Buffer(), (int)text.Length(), find.Buffer(), (int)find.Length(), NULL, NULL, NULL, NULL);
		return result != -1;
#endif
	}
}



namespace vl
{

	/***********************************************************************
	Exception
	***********************************************************************/
	Exception::Exception(const WString& _message)
		: message(_message)
	{
	}
	
	const WString& Exception::Message()const
	{
		return message;
	}
	
	/***********************************************************************
	ArgumentException
	***********************************************************************/
	
	ArgumentException::ArgumentException(const WString& _message, const WString& _function, const WString& _name)
		: Exception(_message)
		, function(_function)
		, name(_name)
	{
	}
	
	const WString& ArgumentException::GetFunction()const
	{
		return function;
	}
	
	const WString& ArgumentException::GetName()const
	{
		return name;
	}
	
	/***********************************************************************
	ParsingException
	***********************************************************************/
	
	ParsingException::ParsingException(const WString& _message, const WString& _expression, vint _position)
		: Exception(_message)
		, expression(_expression)
		, position(_position)
	{
	}
	
	const WString& ParsingException::GetExpression()const
	{
		return expression;
	}
	
	vint ParsingException::GetPosition()const
	{
		return position;
	}
}


#if defined VCZH_MSVC
#include <Windows.h>
#endif

namespace vl
{
	namespace console
	{
	
		/***********************************************************************
		Console
		***********************************************************************/
		
		void Console::Write(const wchar_t* string, vint length)
		{
#if defined VCZH_MSVC
			HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			DWORD fileMode = 0;
			DWORD written = 0;
			
			if ((GetFileType(outHandle) & FILE_TYPE_CHAR) && GetConsoleMode(outHandle, &fileMode))
			{
				WriteConsole(outHandle, string, (int)length, &written, 0);
			}
			else
			{
				int codePage = GetConsoleOutputCP();
				int charCount = WideCharToMultiByte(codePage, 0, string, -1, 0, 0, 0, 0);
				char* codePageBuffer = new char[charCount];
				WideCharToMultiByte(codePage, 0, string, -1, codePageBuffer, charCount, 0, 0);
				WriteFile(outHandle, codePageBuffer, charCount - 1, &written, 0);
				delete[] codePageBuffer;
			}
			
#elif defined VCZH_GCC
			wstring s(string, string + length);
			wcout << s << ends;
#endif
		}
		
		void Console::Write(const wchar_t* string)
		{
			Write(string, wcslen(string));
		}
		
		void Console::Write(const WString& string)
		{
			Write(string.Buffer(), string.Length());
		}
		
		void Console::WriteLine(const WString& string)
		{
			Write(string);
			Write(L"\r\n");
		}
		
		WString Console::Read()
		{
#if defined VCZH_MSVC
			WString result;
			DWORD count;
			
			for (;;)
			{
				wchar_t buffer;
				ReadConsole(GetStdHandle(STD_INPUT_HANDLE), &buffer, 1, &count, 0);
				
				if (buffer == L'\r')
				{
					ReadConsole(GetStdHandle(STD_INPUT_HANDLE), &buffer, 1, &count, 0);
					break;
				}
				else
					if (buffer == L'\n')
					{
						break;
					}
					else
					{
						result = result + buffer;
					}
			}
			
			return result;
#endif
		}
		
		void Console::SetColor(bool red, bool green, bool blue, bool light)
		{
#if defined VCZH_MSVC
			WORD attribute = 0;
			
			if (red)
			{
				attribute |= FOREGROUND_RED;
			}
			
			if (green)
			{
				attribute |= FOREGROUND_GREEN;
			}
			
			if (blue)
			{
				attribute |= FOREGROUND_BLUE;
			}
			
			if (light)
			{
				attribute |= FOREGROUND_INTENSITY;
			}
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attribute);
			SetConsoleTextAttribute(GetStdHandle(STD_INPUT_HANDLE), attribute);
#endif
		}
		
		void Console::SetTitle(const WString& string)
		{
#if defined VCZH_MSVC
			SetConsoleTitle(string.Buffer());
#endif
		}
	}
}



namespace vl
{
	using namespace collections;
	
	class GlobalStorageManager
	{
	 public:
		Ptr<Dictionary<WString, GlobalStorage*>> storages;
		
		GlobalStorageManager()
		{
		}
	};
	
	GlobalStorageManager& GetGlobalStorageManager()
	{
		static GlobalStorageManager globalStorageManager;
		return globalStorageManager;
	}
	
	/***********************************************************************
	GlobalStorage
	***********************************************************************/
	
	GlobalStorage::GlobalStorage(const wchar_t* key)
		: cleared(false)
	{
		InitializeGlobalStorage();
		GetGlobalStorageManager().storages->Add(key, this);
	}
	
	GlobalStorage::~GlobalStorage()
	{
	}
	
	bool GlobalStorage::Cleared()
	{
		return cleared;
	}
	
	/***********************************************************************
	辅助函数
	***********************************************************************/
	
	GlobalStorage* GetGlobalStorage(const wchar_t* key)
	{
		return GetGlobalStorage(WString(key, false));
	}
	
	GlobalStorage* GetGlobalStorage(const WString& key)
	{
		return GetGlobalStorageManager().storages->Get(key);
	}
	
	void InitializeGlobalStorage()
	{
		if (!GetGlobalStorageManager().storages)
		{
			GetGlobalStorageManager().storages = new Dictionary<WString, GlobalStorage*>;
		}
	}
	
	void FinalizeGlobalStorage()
	{
		if (GetGlobalStorageManager().storages)
		{
			for (vint i = 0; i < GetGlobalStorageManager().storages->Count(); i++)
			{
				GetGlobalStorageManager().storages->Values().Get(i)->ClearResource();
			}
			
			GetGlobalStorageManager().storages = 0;
		}
	}
}


#ifdef VCZH_MSVC
#include <Windows.h>
#include <winhttp.h>
#pragma comment(lib, "WinHttp.lib")

namespace vl
{
	using namespace collections;
	
	/***********************************************************************
	HttpRequest
	***********************************************************************/
	
	HttpRequest::HttpRequest()
		: port(0)
		, secure(false)
	{
	}
	
	bool HttpRequest::SetHost(const WString& inputQuery)
	{
		server = L"";
		query = L"";
		port = 0;
		secure = false;
		
		{
			if (server == L"")
			{
				if (inputQuery.Length() > 7)
				{
					WString protocol = inputQuery.Sub(0, 8);
					
					if (_wcsicmp(protocol.Buffer(), L"https://") == 0)
					{
						const wchar_t* reading = inputQuery.Buffer() + 8;
						const wchar_t* index1 = wcschr(reading, L':');
						const wchar_t* index2 = wcschr(reading, L'/');
						
						if (index2)
						{
							query = index2;
							server = WString(reading, (index1 ? index1 : index2) - reading);
							port = INTERNET_DEFAULT_HTTPS_PORT;
							secure = true;
							
							if (index1)
							{
								WString portString(index1 + 1, index2 - index1 - 1);
								port = _wtoi(portString.Buffer());
							}
							
							return true;
						}
					}
				}
			}
			
			if (server == L"")
			{
				if (inputQuery.Length() > 6)
				{
					WString protocol = inputQuery.Sub(0, 7);
					
					if (_wcsicmp(protocol.Buffer(), L"http://") == 0)
					{
						const wchar_t* reading = inputQuery.Buffer() + 7;
						const wchar_t* index1 = wcschr(reading, L':');
						const wchar_t* index2 = wcschr(reading, L'/');
						
						if (index2)
						{
							query = index2;
							server = WString(reading, (index1 ? index1 : index2) - reading);
							port = INTERNET_DEFAULT_HTTP_PORT;
							
							if (index1)
							{
								WString portString(index1 + 1, index2 - index1 - 1);
								port = _wtoi(portString.Buffer());
							}
							
							return true;
						}
					}
				}
			}
		}
		return false;
	}
	
	void HttpRequest::SetBodyUtf8(const WString& bodyString)
	{
		vint utf8Size = WideCharToMultiByte(CP_UTF8, 0, bodyString.Buffer(), (int)bodyString.Length(), NULL, 0, NULL, NULL);
		char* utf8 = new char[utf8Size + 1];
		ZeroMemory(utf8, utf8Size + 1);
		WideCharToMultiByte(CP_UTF8, 0, bodyString.Buffer(), (int)bodyString.Length(), utf8, (int)utf8Size, NULL, NULL);
		
		body.Resize(utf8Size);
		memcpy(&body[0], utf8, utf8Size);
		delete[] utf8;
	}
	
	/***********************************************************************
	HttpResponse
	***********************************************************************/
	
	HttpResponse::HttpResponse()
		: statusCode(0)
	{
	}
	
	WString HttpResponse::GetBodyUtf8()
	{
		WString response;
		char* utf8 = &body[0];
		vint totalSize = body.Count();
		vint utf16Size = MultiByteToWideChar(CP_UTF8, 0, utf8, (int)totalSize, NULL, 0);
		wchar_t* utf16 = new wchar_t[utf16Size + 1];
		ZeroMemory(utf16, (utf16Size + 1) * sizeof(wchar_t));
		MultiByteToWideChar(CP_UTF8, 0, utf8, (int)totalSize, utf16, (int)utf16Size);
		response = utf16;
		delete[] utf16;
		return response;
	}
	
	/***********************************************************************
	Utilities
	***********************************************************************/
	
	struct BufferPair
	{
		char*		buffer;
		vint		length;
		
		BufferPair()
			: buffer(0)
			, length(0)
		{
		}
		
		BufferPair(char* _buffer, vint _length)
			: buffer(_buffer)
			, length(_length)
		{
		}
		
		bool operator==(const BufferPair& pair)
		{
			return false;
		}
		bool operator!=(const BufferPair& pair)
		{
			return true;
		}
	};
	
	bool HttpQuery(const HttpRequest& request, HttpResponse& response)
	{
		// initialize
		response.statusCode = -1;
		HINTERNET internet = NULL;
		HINTERNET connectedInternet = NULL;
		HINTERNET requestInternet = NULL;
		BOOL httpResult = FALSE;
		DWORD error = 0;
		List<LPCWSTR> acceptTypes;
		List<BufferPair> availableBuffers;
		
		// access http
		internet = WinHttpOpen(L"vczh", WINHTTP_ACCESS_TYPE_NO_PROXY, NULL, NULL, 0);
		error = GetLastError();
		
		if (!internet)
		{
			goto CLEANUP;
		}
		
		// connect
		connectedInternet = WinHttpConnect(internet, request.server.Buffer(), (int)request.port, 0);
		error = GetLastError();
		
		if (!connectedInternet)
		{
			goto CLEANUP;
		}
		
		// open request
		for (vint i = 0; i < request.acceptTypes.Count(); i++)
		{
			acceptTypes.Add(request.acceptTypes.Get(i).Buffer());
		}
		
		acceptTypes.Add(0);
		requestInternet = WinHttpOpenRequest(connectedInternet, request.method.Buffer(), request.query.Buffer(), NULL, WINHTTP_NO_REFERER, &acceptTypes[0], (request.secure ? WINHTTP_FLAG_SECURE : 0));
		error = GetLastError();
		
		if (!requestInternet)
		{
			goto CLEANUP;
		}
		
		// authentication, cookie and request
		if (request.username != L"" && request.password != L"")
		{
			WinHttpSetCredentials(requestInternet, WINHTTP_AUTH_TARGET_SERVER, WINHTTP_AUTH_SCHEME_BASIC, request.username.Buffer(), request.password.Buffer(), NULL);
		}
		
		if (request.contentType != L"")
		{
			httpResult = WinHttpAddRequestHeaders(requestInternet, (L"Content-type:" + request.contentType).Buffer(), -1, WINHTTP_ADDREQ_FLAG_REPLACE | WINHTTP_ADDREQ_FLAG_ADD);
		}
		
		if (request.cookie != L"")
		{
			WinHttpAddRequestHeaders(requestInternet, (L"Cookie:" + request.cookie).Buffer(), -1, WINHTTP_ADDREQ_FLAG_REPLACE | WINHTTP_ADDREQ_FLAG_ADD);
		}
		
		// extra headers
		for (int i = 0; i < request.extraHeaders.Count(); i++)
		{
			WString key = request.extraHeaders.Keys()[i];
			WString value = request.extraHeaders.Values().Get(i);
			WinHttpAddRequestHeaders(requestInternet, (key + L":" + value).Buffer(), -1, WINHTTP_ADDREQ_FLAG_REPLACE | WINHTTP_ADDREQ_FLAG_ADD);
		}
		
		if (request.body.Count() > 0)
		{
			httpResult = WinHttpSendRequest(requestInternet, WINHTTP_NO_ADDITIONAL_HEADERS, 0, (LPVOID)&request.body.Get(0), (int)request.body.Count(), (int)request.body.Count(), NULL);
		}
		else
		{
			httpResult = WinHttpSendRequest(requestInternet, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, NULL);
		}
		
		error = GetLastError();
		
		if (httpResult == FALSE)
		{
			goto CLEANUP;
		}
		
		// receive response
		httpResult = WinHttpReceiveResponse(requestInternet, NULL);
		error = GetLastError();
		
		if (httpResult != TRUE)
		{
			goto CLEANUP;
		}
		
		// read response status code
		{
			DWORD headerLength = sizeof(DWORD);
			DWORD statusCode = 0;
			httpResult = WinHttpQueryHeaders(requestInternet, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &statusCode, &headerLength, WINHTTP_NO_HEADER_INDEX);
			error = GetLastError();
			
			if (httpResult == FALSE)
			{
				goto CLEANUP;
			}
			
			response.statusCode = statusCode;
		}
		// read respons cookie
		{
			DWORD headerLength = sizeof(DWORD);
			httpResult = WinHttpQueryHeaders(requestInternet, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, NULL, &headerLength, WINHTTP_NO_HEADER_INDEX);
			error = GetLastError();
			
			if (error == ERROR_INSUFFICIENT_BUFFER)
			{
				wchar_t* rawHeader = new wchar_t[headerLength / sizeof(wchar_t)];
				ZeroMemory(rawHeader, headerLength);
				httpResult = WinHttpQueryHeaders(requestInternet, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, rawHeader, &headerLength, WINHTTP_NO_HEADER_INDEX);
				
				const wchar_t* cookieStart = wcsstr(rawHeader, L"Cookie:");
				
				if (cookieStart)
				{
					const wchar_t* cookieEnd = wcsstr(cookieStart, L";");
					
					if (cookieEnd)
					{
						response.cookie = WString(cookieStart + 7, cookieEnd - cookieStart - 7);
					}
				}
				
				delete[] rawHeader;
			}
		}
		
		// read response body
		while (true)
		{
			DWORD bytesAvailable = 0;
			BOOL queryDataAvailableResult = WinHttpQueryDataAvailable(requestInternet, &bytesAvailable);
			error = GetLastError();
			
			if (queryDataAvailableResult == TRUE && bytesAvailable != 0)
			{
				char* utf8 = new char[bytesAvailable];
				DWORD bytesRead = 0;
				BOOL readDataResult = WinHttpReadData(requestInternet, utf8, bytesAvailable, &bytesRead);
				error = GetLastError();
				
				if (readDataResult == TRUE)
				{
					availableBuffers.Add(BufferPair(utf8, bytesRead));
				}
				else
				{
					delete[] utf8;
				}
			}
			else
			{
				break;
			}
		}
		
		// concatincate response body
		vint totalSize = 0;
		FOREACH(BufferPair, p, availableBuffers)
		{
			totalSize += p.length;
		}
		response.body.Resize(totalSize);
		
		if (totalSize > 0)
		{
			char* utf8 = new char[totalSize];
			{
				char* temp = utf8;
				FOREACH(BufferPair, p, availableBuffers)
				{
					memcpy(temp, p.buffer, p.length);
					temp += p.length;
				}
			}
			memcpy(&response.body[0], utf8, totalSize);
			delete[] utf8;
		}
		
		FOREACH(BufferPair, p, availableBuffers)
		{
			delete[] p.buffer;
		}
CLEANUP:

		if (requestInternet)
		{
			WinHttpCloseHandle(requestInternet);
		}
		
		if (connectedInternet)
		{
			WinHttpCloseHandle(connectedInternet);
		}
		
		if (internet)
		{
			WinHttpCloseHandle(internet);
		}
		
		return response.statusCode != -1;
	}
	
	WString UrlEncodeQuery(const WString& query)
	{
		vint utf8Size = WideCharToMultiByte(CP_UTF8, 0, query.Buffer(), (int)query.Length(), NULL, 0, NULL, NULL);
		char* utf8 = new char[utf8Size + 1];
		ZeroMemory(utf8, utf8Size + 1);
		WideCharToMultiByte(CP_UTF8, 0, query.Buffer(), (int)query.Length(), utf8, (int)utf8Size, NULL, NULL);
		
		wchar_t* encoded = new wchar_t[utf8Size * 3 + 1];
		ZeroMemory(encoded, (utf8Size * 3 + 1) * sizeof(wchar_t));
		wchar_t* writing = encoded;
		
		for (vint i = 0; i < utf8Size; i++)
		{
			unsigned char x = (unsigned char)utf8[i];
			
			if (L'a' <= x && x <= 'z' || L'A' <= x && x <= L'Z' || L'0' <= x && x <= L'9')
			{
				writing[0] = x;
				writing += 1;
			}
			else
			{
				writing[0] = L'%';
				writing[1] = L"0123456789ABCDEF"[x / 16];
				writing[2] = L"0123456789ABCDEF"[x % 16];
				writing += 3;
			}
		}
		
		WString result = encoded;
		delete[] encoded;
		delete[] utf8;
		return result;
	}
}
#endif


// #include <string.h>

namespace vl
{
	namespace stream
	{
		using namespace collections;
		
		/***********************************************************************
		TextReader
		***********************************************************************/
		
		WString TextReader::ReadString(vint length)
		{
			wchar_t* buffer = new wchar_t[length + 1];
			vint i = 0;
			
			for (; i < length; i++)
			{
				if ((buffer[i] = ReadChar()) == L'\0')
				{
					break;
				}
			}
			
			buffer[i] = L'\0';
			WString result(buffer);
			delete[] buffer;
			return result;
		}
		
		WString TextReader::ReadLine()
		{
			WString result;
			wchar_t* buffer = new wchar_t[65537];
			buffer[0] = L'\0';
			vint i = 0;
			
			while (true)
			{
				wchar_t c = ReadChar();
				
				if (c == L'\n' || c == L'\0')
				{
					buffer[i] = L'\0';
					result += buffer;
					buffer[0] = L'\0';
					i = 0;
					break;
				}
				else
				{
					if (i == 65536)
					{
						buffer[i] = L'\0';
						result += buffer;
						buffer[0] = L'\0';
						i = 0;
					}
					
					buffer[i++] = c;
				}
			}
			
			result += buffer;
			delete[] buffer;
			
			if (result.Length() > 0 && result[result.Length() - 1] == L'\r')
			{
				return result.Left(result.Length() - 1);
			}
			else
			{
				return result;
			}
		}
		
		WString TextReader::ReadToEnd()
		{
			WString result;
			wchar_t* buffer = new wchar_t[65537];
			buffer[0] = L'\0';
			vint i = 0;
			
			while (true)
			{
				wchar_t c = ReadChar();
				
				if (c == L'\0')
				{
					buffer[i] = L'\0';
					result += buffer;
					buffer[0] = L'\0';
					i = 0;
					break;
				}
				else
				{
					if (i == 65536)
					{
						buffer[i] = L'\0';
						result += buffer;
						buffer[0] = L'\0';
						i = 0;
					}
					
					buffer[i++] = c;
				}
			}
			
			result += buffer;
			delete[] buffer;
			return result;
		}
		
		/***********************************************************************
		TextWriter
		***********************************************************************/
		
		void TextWriter::WriteString(const wchar_t* string, vint charCount)
		{
			while (*string)
			{
				WriteChar(*string++);
			}
		}
		
		void TextWriter::WriteString(const wchar_t* string)
		{
			WriteString(string, (vint)wcslen(string));
		}
		
		void TextWriter::WriteString(const WString& string)
		{
			if (string.Length())
			{
				WriteString(string.Buffer(), string.Length());
			}
		}
		
		void TextWriter::WriteLine(const wchar_t* string, vint charCount)
		{
			WriteString(string, charCount);
			WriteString(L"\r\n", 2);
		}
		
		void TextWriter::WriteLine(const wchar_t* string)
		{
			WriteString(string);
			WriteString(L"\r\n", 2);
		}
		
		void TextWriter::WriteLine(const WString& string)
		{
			WriteString(string);
			WriteString(L"\r\n", 2);
		}
		
		namespace monospace_tabling
		{
			void WriteBorderLine(TextWriter& writer, Array<vint>& columnWidths, vint columns)
			{
				writer.WriteChar(L'+');
				
				for (vint i = 0; i < columns; i++)
				{
					vint c = columnWidths[i];
					
					for (vint j = 0; j < c; j++)
					{
						writer.WriteChar(L'-');
					}
					
					writer.WriteChar(L'+');
				}
				
				writer.WriteLine(L"");
			}
			
			void WriteContentLine(TextWriter& writer, Array<vint>& columnWidths, vint rowHeight, vint columns, Array<WString>& tableByRow, vint startRow)
			{
				vint cellStart = startRow * columns;
				
				for (vint r = 0; r < rowHeight; r++)
				{
					writer.WriteChar(L'|');
					
					for (vint c = 0; c < columns; c++)
					{
						const wchar_t* cell = tableByRow[cellStart + c].Buffer();
						
						for (vint i = 0; i < r; i++)
						{
							if (cell)
							{
								cell = ::wcsstr(cell, L"\r\n");
							}
							
							if (cell)
							{
								cell += 2;
							}
						}
						
						writer.WriteChar(L' ');
						vint length = 0;
						
						if (cell)
						{
							const wchar_t* end = ::wcsstr(cell, L"\r\n");
							length = end ? end - cell : (vint)wcslen(cell);
							writer.WriteString(cell, length);
						}
						
						for (vint i = columnWidths[c] - 2; i >= length; i--)
						{
							writer.WriteChar(L' ');
						}
						
						writer.WriteChar(L'|');
					}
					
					writer.WriteLine(L"");
				}
			}
		}
		using namespace monospace_tabling;
		
		void TextWriter::WriteMonospacedEnglishTable(collections::Array<WString>& tableByRow, vint rows, vint columns)
		{
			Array<vint> rowHeights(rows);
			Array<vint> columnWidths(columns);
			
			for (vint i = 0; i < rows; i++)
			{
				rowHeights[i] = 0;
			}
			
			for (vint j = 0; j < columns; j++)
			{
				columnWidths[j] = 0;
			}
			
			for (vint i = 0; i < rows; i++)
			{
				for (vint j = 0; j < columns; j++)
				{
					WString text = tableByRow[i * columns + j];
					const wchar_t* reading = text.Buffer();
					vint width = 0;
					vint height = 0;
					
					while (reading)
					{
						height++;
						const wchar_t* crlf = ::wcsstr(reading, L"\r\n");
						
						if (crlf)
						{
							vint length = crlf - reading + 2;
							
							if (width < length)
							{
								width = length;
							}
							
							reading = crlf + 2;
						}
						else
						{
							vint length = (vint)wcslen(reading) + 2;
							
							if (width < length)
							{
								width = length;
							}
							
							reading = 0;
						}
					}
					
					if (rowHeights[i] < height)
					{
						rowHeights[i] = height;
					}
					
					if (columnWidths[j] < width)
					{
						columnWidths[j] = width;
					}
				}
			}
			
			WriteBorderLine(*this, columnWidths, columns);
			
			for (vint i = 0; i < rows; i++)
			{
				WriteContentLine(*this, columnWidths, rowHeights[i], columns, tableByRow, i);
				WriteBorderLine(*this, columnWidths, columns);
			}
		}
		
		/***********************************************************************
		StringReader
		***********************************************************************/
		
		void StringReader::PrepareIfLastCallIsReadLine()
		{
			if (lastCallIsReadLine)
			{
				lastCallIsReadLine = false;
				
				if (current < string.Length() && string[current] == L'\r')
				{
					current++;
				}
				
				if (current < string.Length() && string[current] == L'\n')
				{
					current++;
				}
			}
		}
		
		StringReader::StringReader(const WString& _string)
			: string(_string)
			, current(0)
			, lastCallIsReadLine(false)
		{
		}
		
		bool StringReader::IsEnd()
		{
			return current == string.Length();
		}
		
		wchar_t StringReader::ReadChar()
		{
			PrepareIfLastCallIsReadLine();
			
			if (IsEnd())
			{
				return L'\0';
			}
			else
			{
				return string[current++];
			}
		}
		
		WString StringReader::ReadString(vint length)
		{
			PrepareIfLastCallIsReadLine();
			
			if (IsEnd())
			{
				return L"";
			}
			else
			{
				vint remain = string.Length() - current;
				
				if (length > remain)
				{
					length = remain;
				}
				
				WString result = string.Sub(current, length);
				current += length;
				return result;
			}
		}
		
		WString StringReader::ReadLine()
		{
			PrepareIfLastCallIsReadLine();
			
			if (IsEnd())
			{
				return L"";
			}
			else
			{
				vint lineEnd = current;
				
				while (lineEnd < string.Length())
				{
					wchar_t c = string[lineEnd];
					
					if (c == L'\r' || c == L'\n')
					{
						break;
					}
					
					lineEnd++;
				}
				
				WString result = string.Sub(current, lineEnd - current);
				current = lineEnd;
				lastCallIsReadLine = true;
				return result;
			}
		}
		
		WString StringReader::ReadToEnd()
		{
			return ReadString(string.Length() - current);
		}
		
		/***********************************************************************
		StreamReader
		***********************************************************************/
		
		StreamReader::StreamReader(IStream& _stream)
			: stream(&_stream)
		{
		}
		
		bool StreamReader::IsEnd()
		{
			return stream == 0;
		}
		
		wchar_t StreamReader::ReadChar()
		{
			if (stream)
			{
				wchar_t buffer = 0;
				
				if (stream->Read(&buffer, sizeof(buffer)) == 0)
				{
					stream = 0;
					return 0;
				}
				else
				{
					return buffer;
				}
			}
			else
			{
				return L'\0';
			}
		}
		
		/***********************************************************************
		StreamWriter
		***********************************************************************/
		
		StreamWriter::StreamWriter(IStream& _stream)
			: stream(&_stream)
		{
		}
		
		void StreamWriter::WriteChar(wchar_t c)
		{
			stream->Write(&c, sizeof(c));
		}
		
		void StreamWriter::WriteString(const wchar_t* string, vint charCount)
		{
			stream->Write((void*)string, charCount * sizeof(*string));
		}
		
		/***********************************************************************
		EncoderStream
		***********************************************************************/
		
		EncoderStream::EncoderStream(IStream& _stream, IEncoder& _encoder)
			: stream(&_stream)
			, encoder(&_encoder)
			, position(0)
		{
			encoder->Setup(stream);
		}
		
		EncoderStream::~EncoderStream()
		{
			Close();
		}
		
		bool EncoderStream::CanRead()const
		{
			return false;
		}
		
		bool EncoderStream::CanWrite()const
		{
			return IsAvailable();
		}
		
		bool EncoderStream::CanSeek()const
		{
			return false;
		}
		
		bool EncoderStream::CanPeek()const
		{
			return false;
		}
		
		bool EncoderStream::IsLimited()const
		{
			return stream != 0 && stream->IsLimited();
		}
		
		bool EncoderStream::IsAvailable()const
		{
			return stream != 0 && stream->IsAvailable();
		}
		
		void EncoderStream::Close()
		{
			encoder->Close();
			stream = 0;
		}
		
		pos_t EncoderStream::Position()const
		{
			return IsAvailable() ? position : -1;
		}
		
		pos_t EncoderStream::Size()const
		{
			return -1;
		}
		
		void EncoderStream::Seek(pos_t _size)
		{
			CHECK_FAIL(L"EncoderStream::Seek(pos_t)#Operation not supported.");
		}
		
		void EncoderStream::SeekFromBegin(pos_t _size)
		{
			CHECK_FAIL(L"EncoderStream::SeekFromBegin(pos_t)#Operation not supported.");
		}
		
		void EncoderStream::SeekFromEnd(pos_t _size)
		{
			CHECK_FAIL(L"EncoderStream::SeekFromEnd(pos_t)#Operation not supported.");
		}
		
		vint EncoderStream::Read(void* _buffer, vint _size)
		{
			CHECK_FAIL(L"EncoderStream::Read(void*, vint)#Operation not supported.");
		}
		
		vint EncoderStream::Write(void* _buffer, vint _size)
		{
			vint result = encoder->Write(_buffer, _size);
			
			if (result >= 0)
			{
				position += result;
			}
			
			return result;
		}
		
		vint EncoderStream::Peek(void* _buffer, vint _size)
		{
			CHECK_FAIL(L"EncoderStream::Peek(void*, vint)#Operation not supported.");
		}
		
		/***********************************************************************
		DecoderStream
		***********************************************************************/
		
		DecoderStream::DecoderStream(IStream& _stream, IDecoder& _decoder)
			: stream(&_stream)
			, decoder(&_decoder)
			, position(0)
		{
			decoder->Setup(stream);
		}
		
		DecoderStream::~DecoderStream()
		{
			Close();
		}
		
		bool DecoderStream::CanRead()const
		{
			return IsAvailable();
		}
		
		bool DecoderStream::CanWrite()const
		{
			return false;
		}
		
		bool DecoderStream::CanSeek()const
		{
			return false;
		}
		
		bool DecoderStream::CanPeek()const
		{
			return false;
		}
		
		bool DecoderStream::IsLimited()const
		{
			return stream != 0 && stream->IsLimited();
		}
		
		bool DecoderStream::IsAvailable()const
		{
			return stream != 0 && stream->IsAvailable();
		}
		
		void DecoderStream::Close()
		{
			decoder->Close();
			stream = 0;
		}
		
		pos_t DecoderStream::Position()const
		{
			return IsAvailable() ? position : -1;
		}
		
		pos_t DecoderStream::Size()const
		{
			return -1;
		}
		
		void DecoderStream::Seek(pos_t _size)
		{
			CHECK_FAIL(L"DecoderStream::Seek(pos_t)#Operation not supported.");
		}
		
		void DecoderStream::SeekFromBegin(pos_t _size)
		{
			CHECK_FAIL(L"DecoderStream::SeekFromBegin(pos_t)#Operation not supported.");
		}
		
		void DecoderStream::SeekFromEnd(pos_t _size)
		{
			CHECK_FAIL(L"DecoderStream::SeekFromEnd(pos_t)#Operation not supported.");
		}
		
		vint DecoderStream::Read(void* _buffer, vint _size)
		{
			vint result = decoder->Read(_buffer, _size);
			
			if (result >= 0)
			{
				position += result;
			}
			
			return result;
		}
		
		vint DecoderStream::Write(void* _buffer, vint _size)
		{
			CHECK_FAIL(L"DecoderStream::Write(void*, vint)#Operation not supported.");
		}
		
		vint DecoderStream::Peek(void* _buffer, vint _size)
		{
			CHECK_FAIL(L"DecoderStream::Peek(void*, vint)#Operation not supported.");
		}
	}
}

#include <string.h>
// #include "BroadcastStream.h"

namespace vl
{
	namespace stream
	{
		/***********************************************************************
		BroadcastStream
		***********************************************************************/
		
		BroadcastStream::BroadcastStream()
			: closed(false)
			, position(0)
		{
		}
		
		BroadcastStream::~BroadcastStream()
		{
		}
		
		BroadcastStream::StreamList& BroadcastStream::Targets()
		{
			return streams;
		}
		
		bool BroadcastStream::CanRead()const
		{
			return false;
		}
		
		bool BroadcastStream::CanWrite()const
		{
			return !closed;
		}
		
		bool BroadcastStream::CanSeek()const
		{
			return false;
		}
		
		bool BroadcastStream::CanPeek()const
		{
			return false;
		}
		
		bool BroadcastStream::IsLimited()const
		{
			return false;
		}
		
		bool BroadcastStream::IsAvailable()const
		{
			return !closed;
		}
		
		void BroadcastStream::Close()
		{
			closed = true;
			position = -1;
		}
		
		pos_t BroadcastStream::Position()const
		{
			return position;
		}
		
		pos_t BroadcastStream::Size()const
		{
			return position;
		}
		
		void BroadcastStream::Seek(pos_t _size)
		{
			CHECK_FAIL(L"BroadcastStream::Seek(pos_t)#Operation not supported.");
		}
		
		void BroadcastStream::SeekFromBegin(pos_t _size)
		{
			CHECK_FAIL(L"BroadcastStream::SeekFromBegin(pos_t)#Operation not supported.");
		}
		
		void BroadcastStream::SeekFromEnd(pos_t _size)
		{
			CHECK_FAIL(L"BroadcastStream::SeekFromEnd(pos_t)#Operation not supported.");
		}
		
		vint BroadcastStream::Read(void* _buffer, vint _size)
		{
			CHECK_FAIL(L"BroadcastStream::Read(void*, vint)#Operation not supported.");
		}
		
		vint BroadcastStream::Write(void* _buffer, vint _size)
		{
			for (vint i = 0; i < streams.Count(); i++)
			{
				streams[i]->Write(_buffer, _size);
			}
			
			position += _size;
			return _size;
		}
		
		vint BroadcastStream::Peek(void* _buffer, vint _size)
		{
			CHECK_FAIL(L"BroadcastStream::Peek(void*, vint)#Operation not supported.");
		}
	}
}


#include <string.h>
// #include "CacheStream.h"

namespace vl
{
	namespace stream
	{
		/***********************************************************************
		CacheStream
		***********************************************************************/
		
		void CacheStream::Flush()
		{
			if (dirtyLength > 0)
			{
				if (target->Position() != start + dirtyStart)
				{
					target->SeekFromBegin(start + dirtyStart);
				}
				
				target->Write(buffer + dirtyStart, dirtyLength);
			}
			
			dirtyStart = 0;
			dirtyLength = 0;
			availableLength = 0;
		}
		
		void CacheStream::Load(pos_t _position)
		{
			if (target->Position() != _position)
			{
				target->SeekFromBegin(_position);
			}
			
			start = _position;
			
			if (target->CanRead())
			{
				availableLength = target->Read(buffer, block);
			}
		}
		
		vint CacheStream::InternalRead(void* _buffer, vint _size)
		{
			vint readed = 0;
			
			if (position >= start && position < start + availableLength)
			{
				vint bufferMax = (vint)(start + availableLength - position);
				vint min = bufferMax < _size ? bufferMax : _size;
				memcpy(_buffer, buffer + (position - start), min);
				readed += min;
				_buffer = (char*)_buffer + min;
			}
			
			if (_size > readed)
			{
				Flush();
				
				if (_size - readed >= block)
				{
					if (CanSeek())
					{
						target->SeekFromBegin(position + readed);
					}
					
					vint additional = target->Read(_buffer, _size - readed);
					
					if (additional != -1)
					{
						readed += additional;
					}
				}
				else
				{
					Load(position + readed);
					vint remain = _size - readed;
					vint min = availableLength < remain ? availableLength : remain;
					memcpy(_buffer, buffer, min);
					readed += min;
				}
			}
			
			return readed;
		}
		
		vint CacheStream::InternalWrite(void* _buffer, vint _size)
		{
			vint written = 0;
			
			if (position >= start && position < start + block)
			{
				vint bufferMax = (vint)(start + block - position);
				vint writeLength = bufferMax < _size ? bufferMax : _size;
				vint writeStart = (vint)(position - start);
				
				memcpy(buffer + writeStart, _buffer, writeLength);
				written += writeLength;
				_buffer = (char*)_buffer + writeLength;
				
				if (dirtyLength == 0)
				{
					dirtyStart = writeStart;
					dirtyLength = writeLength;
				}
				else
				{
					dirtyLength = writeStart + writeLength - dirtyStart;
				}
				
				vint availableOffset = writeStart + writeLength - availableLength;
				
				if (availableOffset > 0)
				{
					availableLength += availableOffset;
				}
			}
			
			if (_size > written)
			{
				Flush();
				
				if (_size - written >= block)
				{
					if (CanSeek())
					{
						target->SeekFromBegin(position + written);
					}
					
					vint additional = target->Write(_buffer, _size - written);
					
					if (additional != -1)
					{
						written += additional;
					}
				}
				else
				{
					Load(position + written);
					dirtyLength = _size - written;
					memcpy(buffer, _buffer, dirtyLength);
					written += dirtyLength;
				}
			}
			
			return written;
		}
		
		CacheStream::CacheStream(IStream& _target, vint _block)
			: target(&_target)
			, block(_block)
			, start(0)
			, position(0)
			, dirtyStart(0)
			, dirtyLength(0)
			, availableLength(0)
			, operatedSize(0)
		{
			if (block <= 0)
			{
				block = 65536;
			}
			
			buffer = new char[block];
		}
		
		CacheStream::~CacheStream()
		{
			Close();
		}
		
		bool CacheStream::CanRead()const
		{
			return target != 0 && target->CanRead();
		}
		
		bool CacheStream::CanWrite()const
		{
			return target != 0 && target->CanWrite();
		}
		
		bool CacheStream::CanSeek()const
		{
			return target != 0 && target->CanSeek();
		}
		
		bool CacheStream::CanPeek()const
		{
			return target != 0 && target->CanPeek();
		}
		
		bool CacheStream::IsLimited()const
		{
			return target != 0 && target->IsLimited();
		}
		
		bool CacheStream::IsAvailable()const
		{
			return target != 0 && target->IsAvailable();
		}
		
		void CacheStream::Close()
		{
			Flush();
			target = 0;
			delete[] buffer;
			buffer = 0;
			position = -1;
			dirtyStart = 0;
			dirtyLength = 0;
			availableLength = 0;
			operatedSize = -1;
		}
		
		pos_t CacheStream::Position()const
		{
			return position;
		}
		
		pos_t CacheStream::Size()const
		{
			if (target != 0)
			{
				if (IsLimited())
				{
					return target->Size();
				}
				else
				{
					return operatedSize;
				}
			}
			else
			{
				return -1;
			}
		}
		
		void CacheStream::Seek(pos_t _size)
		{
			SeekFromBegin(position + _size);
		}
		
		void CacheStream::SeekFromBegin(pos_t _size)
		{
			if (CanSeek())
			{
				if (_size < 0)
				{
					position = 0;
				}
				else
					if (_size > Size())
					{
						position = Size();
					}
					else
					{
						position = _size;
					}
			}
		}
		
		void CacheStream::SeekFromEnd(pos_t _size)
		{
			SeekFromBegin(Size() - _size);
		}
		
		vint CacheStream::Read(void* _buffer, vint _size)
		{
			CHECK_ERROR(CanRead(), L"CacheStream::Read(void*, vint)#Stream is closed or operation not supported.");
			CHECK_ERROR(_size >= 0, L"CacheStream::Read(void*, vint)#Argument size cannot be negative.");
			
			_size = InternalRead(_buffer, _size);
			position += _size;
			
			if (operatedSize < position)
			{
				operatedSize = position;
			}
			
			return _size;
		}
		
		vint CacheStream::Write(void* _buffer, vint _size)
		{
			CHECK_ERROR(CanWrite(), L"CacheStream::Write(void*, vint)#Stream is closed or operation not supported.");
			CHECK_ERROR(_size >= 0, L"CacheStream::Read(void*, vint)#Argument size cannot be negative.");
			
			if (IsLimited())
			{
				pos_t size = Size();
				
				if (size != -1)
				{
					vint remain = (vint)(size - (position + _size));
					
					if (remain < 0)
					{
						_size -= remain;
					}
				}
			}
			
			_size = InternalWrite(_buffer, _size);
			position += _size;
			
			if (operatedSize < position)
			{
				operatedSize = position;
			}
			
			return _size;
		}
		
		vint CacheStream::Peek(void* _buffer, vint _size)
		{
			CHECK_ERROR(CanPeek(), L"CacheStream::Peek(void*, vint)#Stream is closed or operation not supported.");
			CHECK_ERROR(_size >= 0, L"CacheStream::Read(void*, vint)#Argument size cannot be negative.");
			
			return InternalRead(_buffer, _size);
		}
	}
}


#include <string.h>
// #include "MemoryStream.h"

namespace vl
{
	namespace stream
	{
		/***********************************************************************
		MemoryStream
		***********************************************************************/
		
		void MemoryStream::PrepareSpace(vint totalSpace)
		{
			if (totalSpace > capacity)
			{
				totalSpace = (totalSpace / block + 1) * block;
				char* newBuffer = new char[totalSpace];
				
				if (buffer)
				{
					memcpy(newBuffer, buffer, size);
					delete[] buffer;
				}
				
				buffer = newBuffer;
				capacity = totalSpace;
			}
		}
		
		MemoryStream::MemoryStream(vint _block)
			: block(_block)
			, buffer(0)
			, size(0)
			, position(0)
			, capacity(0)
		{
			if (block <= 0)
			{
				block = 65536;
			}
		}
		
		MemoryStream::~MemoryStream()
		{
			Close();
		}
		
		bool MemoryStream::CanRead()const
		{
			return block != 0;
		}
		
		bool MemoryStream::CanWrite()const
		{
			return block != 0;
		}
		
		bool MemoryStream::CanSeek()const
		{
			return block != 0;
		}
		
		bool MemoryStream::CanPeek()const
		{
			return block != 0;
		}
		
		bool MemoryStream::IsLimited()const
		{
			return false;
		}
		
		bool MemoryStream::IsAvailable()const
		{
			return block != 0;
		}
		
		void MemoryStream::Close()
		{
			if (buffer)
			{
				delete[] buffer;
			}
			
			block = 0;
			buffer = 0;
			size = -1;
			position = -1;
			capacity = 0;
		}
		
		pos_t MemoryStream::Position()const
		{
			return position;
		}
		
		pos_t MemoryStream::Size()const
		{
			return size;
		}
		
		void MemoryStream::Seek(pos_t _size)
		{
			SeekFromBegin(position + _size);
		}
		
		void MemoryStream::SeekFromBegin(pos_t _size)
		{
			CHECK_ERROR(block != 0, L"MemoryStream::SeekFromBegin(pos_t)#Stream is closed, cannot perform this operation.");
			vint expected = (vint)_size;
			
			if (expected < 0)
			{
				position = 0;
			}
			else
				if (expected >= size)
				{
					position = size;
				}
				else
				{
					position = expected;
				}
		}
		
		void MemoryStream::SeekFromEnd(pos_t _size)
		{
			SeekFromBegin(size - _size);
		}
		
		vint MemoryStream::Read(void* _buffer, vint _size)
		{
			CHECK_ERROR(block != 0, L"MemoryStream::Read(pos_t)#Stream is closed, cannot perform this operation.");
			CHECK_ERROR(_size >= 0, L"MemoryStream::Read(void*, vint)#Argument size cannot be negative.");
			vint max = size - position;
			
			if (_size > max)
			{
				_size = max;
			}
			
			memmove(_buffer, buffer + position, _size);
			position += _size;
			return _size;
		}
		
		vint MemoryStream::Write(void* _buffer, vint _size)
		{
			CHECK_ERROR(block != 0, L"MemoryStream::Write(pos_t)#Stream is closed, cannot perform this operation.");
			CHECK_ERROR(_size >= 0, L"MemoryStream::Write(void*, vint)#Argument size cannot be negative.");
			PrepareSpace(size + _size);
			memmove(buffer + position, _buffer, _size);
			position += _size;
			
			if (size < position)
			{
				size = position;
			}
			
			return _size;
		}
		
		vint MemoryStream::Peek(void* _buffer, vint _size)
		{
			CHECK_ERROR(block != 0, L"MemoryStream::Peek(pos_t)#Stream is closed, cannot perform this operation.");
			CHECK_ERROR(_size >= 0, L"MemoryStream::Peek(void*, vint)#Argument size cannot be negative.");
			vint max = size - position;
			
			if (_size > max)
			{
				_size = max;
			}
			
			memmove(_buffer, buffer + position, _size);
			return _size;
		}
		
		void* MemoryStream::GetInternalBuffer()
		{
			return buffer;
		}
	}
}


// #include <string.h>
// #include "MemoryWrapperStream.h"

namespace vl
{
	namespace stream
	{
		/***********************************************************************
		MemoryWrapperStream
		***********************************************************************/
		
		MemoryWrapperStream::MemoryWrapperStream(void* _buffer, vint _size)
			: buffer((char*)_buffer)
			, size(_size)
			, position(0)
		{
			if (size <= 0)
			{
				buffer = 0;
				size = 0;
			}
		}
		
		MemoryWrapperStream::~MemoryWrapperStream()
		{
		}
		
		bool MemoryWrapperStream::CanRead()const
		{
			return buffer != 0;
		}
		
		bool MemoryWrapperStream::CanWrite()const
		{
			return buffer != 0;
		}
		
		bool MemoryWrapperStream::CanSeek()const
		{
			return buffer != 0;
		}
		
		bool MemoryWrapperStream::CanPeek()const
		{
			return buffer != 0;
		}
		
		bool MemoryWrapperStream::IsLimited()const
		{
			return buffer != 0;
		}
		
		bool MemoryWrapperStream::IsAvailable()const
		{
			return buffer != 0;
		}
		
		void MemoryWrapperStream::Close()
		{
			buffer = 0;
			size = -1;
			position = -1;
		}
		
		pos_t MemoryWrapperStream::Position()const
		{
			return position;
		}
		
		pos_t MemoryWrapperStream::Size()const
		{
			return size;
		}
		
		void MemoryWrapperStream::Seek(pos_t _size)
		{
			SeekFromBegin(position + _size);
		}
		
		void MemoryWrapperStream::SeekFromBegin(pos_t _size)
		{
			CHECK_ERROR(buffer != 0, L"MemoryWrapperStream::SeekFromBegin(pos_t)#Stream is closed, cannot perform this operation.");
			vint expected = (vint)_size;
			
			if (expected < 0)
			{
				position = 0;
			}
			else
				if (expected >= size)
				{
					position = size;
				}
				else
				{
					position = expected;
				}
		}
		
		void MemoryWrapperStream::SeekFromEnd(pos_t _size)
		{
			SeekFromBegin(size - _size);
		}
		
		vint MemoryWrapperStream::Read(void* _buffer, vint _size)
		{
			CHECK_ERROR(buffer != 0, L"MemoryWrapperStream::Read(pos_t)#Stream is closed, cannot perform this operation.");
			CHECK_ERROR(_size >= 0, L"MemoryWrapperStream::Read(void*, vint)#Argument size cannot be negative.");
			vint max = size - position;
			
			if (_size > max)
			{
				_size = max;
			}
			
			memmove(_buffer, buffer + position, _size);
			position += _size;
			return _size;
		}
		
		vint MemoryWrapperStream::Write(void* _buffer, vint _size)
		{
			CHECK_ERROR(buffer != 0, L"MemoryWrapperStream::Write(pos_t)#Stream is closed, cannot perform this operation.");
			CHECK_ERROR(_size >= 0, L"MemoryWrapperStream::Write(void*, vint)#Argument size cannot be negative.");
			vint max = size - position;
			
			if (_size > max)
			{
				_size = max;
			}
			
			memmove(buffer + position, _buffer, _size);
			position += _size;
			return _size;
		}
		
		vint MemoryWrapperStream::Peek(void* _buffer, vint _size)
		{
			CHECK_ERROR(buffer != 0, L"MemoryWrapperStream::Peek(pos_t)#Stream is closed, cannot perform this operation.");
			CHECK_ERROR(_size >= 0, L"MemoryWrapperStream::Peek(void*, vint)#Argument size cannot be negative.");
			vint max = size - position;
			
			if (_size > max)
			{
				_size = max;
			}
			
			memmove(_buffer, buffer + position, _size);
			return _size;
		}
	}
}


#if defined VCZH_MSVC
#include <windows.h>
#endif

namespace vl
{
	namespace stream
	{
	
		/***********************************************************************
		CharEncoder
		***********************************************************************/
		
		CharEncoder::CharEncoder()
			: stream(0)
			, cacheSize(0)
		{
		}
		
		void CharEncoder::Setup(IStream* _stream)
		{
			stream = _stream;
		}
		
		void CharEncoder::Close()
		{
		}
		
		vint CharEncoder::Write(void* _buffer, vint _size)
		{
			const vint all = cacheSize + _size;
			const vint chars = all / sizeof(wchar_t);
			const vint bytes = chars * sizeof(wchar_t);
			wchar_t* unicode = 0;
			bool needToFree = false;
			vint result = 0;
			
			if (chars)
			{
				if (cacheSize > 0)
				{
					unicode = new wchar_t[chars];
					memcpy(unicode, cacheBuffer, cacheSize);
					memcpy(((vuint8_t*)unicode) + cacheSize, _buffer, bytes - cacheSize);
					needToFree = true;
				}
				else
				{
					unicode = (wchar_t*)_buffer;
				}
				
				result = WriteString(unicode, chars) * sizeof(wchar_t) - cacheSize;
				cacheSize = 0;
			}
			
			if (needToFree)
			{
				delete[] unicode;
			}
			
			if (all - bytes > 0)
			{
				cacheSize = all - bytes;
				memcpy(cacheBuffer, (vuint8_t*)_buffer + _size - cacheSize, cacheSize);
				result += cacheSize;
			}
			
			return result;
		}
		
		/***********************************************************************
		CharDecoder
		***********************************************************************/
		
		CharDecoder::CharDecoder()
			: stream(0)
			, cacheSize(0)
		{
		}
		
		void CharDecoder::Setup(IStream* _stream)
		{
			stream = _stream;
		}
		
		void CharDecoder::Close()
		{
		}
		
		vint CharDecoder::Read(void* _buffer, vint _size)
		{
			vuint8_t* unicode = (vuint8_t*)_buffer;
			vint result = 0;
			{
				vint index = 0;
				
				while (cacheSize > 0 && _size > 0)
				{
					*unicode++ = cacheBuffer[index]++;
					cacheSize--;
					_size--;
					result++;
				}
			}
			
			const vint chars = _size / sizeof(wchar_t);
			vint bytes = ReadString((wchar_t*)unicode, chars) * sizeof(wchar_t);
			result += bytes;
			_size -= bytes;
			unicode += bytes;
			
			if (_size > 0)
			{
				wchar_t c;
				
				if (ReadString(&c, 1) == 1)
				{
					cacheSize = sizeof(wchar_t) - _size;
					memcpy(unicode, &c, _size);
					memcpy(cacheBuffer, (vuint8_t*)&c + _size, cacheSize);
					result += _size;
				}
			}
			
			return result;
		}
		
		/***********************************************************************
		Mbcs
		***********************************************************************/
		
		vint MbcsEncoder::WriteString(wchar_t* _buffer, vint chars)
		{
#if defined VCZH_MSVC
			vint length = WideCharToMultiByte(CP_THREAD_ACP, 0, _buffer, (int)chars, NULL, NULL, NULL, NULL);
			char* mbcs = new char[length];
			WideCharToMultiByte(CP_THREAD_ACP, 0, _buffer, (int)chars, mbcs, (int)length, NULL, NULL);
			vint result = stream->Write(mbcs, length);
			delete[] mbcs;
#endif
			
			if (result == length)
			{
				return chars;
			}
			else
			{
				Close();
				return 0;
			}
		}
		
		vint MbcsDecoder::ReadString(wchar_t* _buffer, vint chars)
		{
			char* source = new char[chars * 2];
			char* reading = source;
			vint readed = 0;
			
			while (readed < chars)
			{
				if (stream->Read(reading, 1) != 1)
				{
					break;
				}
				
#if defined VCZH_MSVC
				
				if (IsDBCSLeadByte(*reading))
#elif defined VCZH_GCC
				if ((vint8_t)*reading < 0)
#endif
				{
					if (stream->Read(reading + 1, 1) != 1)
					{
						break;
					}
					
					reading += 2;
				}
				else
				{
					reading++;
				}
				
				readed++;
			}
			
#if defined VCZH_MSVC
			MultiByteToWideChar(CP_THREAD_ACP, 0, source, (int)(reading - source), _buffer, (int)chars);
#endif
			delete[] source;
			return readed;
		}
		
		/***********************************************************************
		Utf-16
		***********************************************************************/
		
		vint Utf16Encoder::WriteString(wchar_t* _buffer, vint chars)
		{
#if defined VCZH_MSVC
			return stream->Write(_buffer, chars * sizeof(wchar_t)) / sizeof(wchar_t);
#endif
		}
		
		vint Utf16Decoder::ReadString(wchar_t* _buffer, vint chars)
		{
#if defined VCZH_MSVC
			return stream->Read(_buffer, chars * sizeof(wchar_t)) / sizeof(wchar_t);
#endif
		}
		
		/***********************************************************************
		Utf-16-be
		***********************************************************************/
		
		vint Utf16BEEncoder::WriteString(wchar_t* _buffer, vint chars)
		{
#if defined VCZH_MSVC
			vint writed = 0;
			
			while (writed < chars)
			{
				if (stream->Write(((unsigned char*)_buffer) + 1, 1) != 1)
				{
					break;
				}
				
				if (stream->Write(_buffer, 1) != 1)
				{
					break;
				}
				
				_buffer++;
				writed++;
			}
			
			if (writed != chars)
			{
				Close();
			}
			
			return writed;
#endif
		}
		
		vint Utf16BEDecoder::ReadString(wchar_t* _buffer, vint chars)
		{
#if defined VCZH_MSVC
			chars = stream->Read(_buffer, chars * sizeof(wchar_t)) / sizeof(wchar_t);
			unsigned char* unicode = (unsigned char*)_buffer;
			
			for (vint i = 0; i < chars; i++)
			{
				unsigned char t = unicode[0];
				unicode[0] = unicode[1];
				unicode[1] = t;
				unicode++;
			}
			
			return chars;
#endif
		}
		
		/***********************************************************************
		Utf8
		***********************************************************************/
		
		vint Utf8Encoder::WriteString(wchar_t* _buffer, vint chars)
		{
#if defined VCZH_MSVC
			vint length = WideCharToMultiByte(CP_UTF8, 0, _buffer, (int)chars, NULL, NULL, NULL, NULL);
			char* mbcs = new char[length];
			WideCharToMultiByte(CP_UTF8, 0, _buffer, (int)chars, mbcs, (int)length, NULL, NULL);
			vint result = stream->Write(mbcs, length);
			delete[] mbcs;
			
			if (result == length)
			{
				return chars;
			}
			else
			{
				Close();
				return 0;
			}
			
#endif
		}
		
		Utf8Decoder::Utf8Decoder()
#if defined VCZH_MSVC
			: cache(0)
			, cacheAvailable(false)
#endif
		{
		}
		
		vint Utf8Decoder::ReadString(wchar_t* _buffer, vint chars)
		{
			vuint8_t source[4];
#if defined VCZH_MSVC
			wchar_t target[2];
#endif
			wchar_t* writing = _buffer;
			vint readed = 0;
			vint sourceCount = 0;
			
			while (readed < chars)
			{
#if defined VCZH_MSVC
			
				if (cacheAvailable)
				{
					*writing++ = cache;
					cache = 0;
					cacheAvailable = false;
				}
				else
				{
#endif
				
					if (stream->Read(source, 1) != 1)
					{
						break;
					}
					
					if ((*source & 0xF0) == 0xF0)
					{
						if (stream->Read(source + 1, 3) != 3)
						{
							break;
						}
						
						sourceCount = 4;
					}
					else
						if ((*source & 0xE0) == 0xE0)
						{
							if (stream->Read(source + 1, 2) != 2)
							{
								break;
							}
							
							sourceCount = 3;
						}
						else
							if ((*source & 0xC0) == 0xC0)
							{
								if (stream->Read(source + 1, 1) != 1)
								{
									break;
								}
								
								sourceCount = 2;
							}
							else
							{
								sourceCount = 1;
							}
							
#if defined VCZH_MSVC
					int targetCount = MultiByteToWideChar(CP_UTF8, 0, (char*)source, (int)sourceCount, target, 2);
					
					if (targetCount == 1)
					{
						*writing++ = target[0];
					}
					else
						if (targetCount == 2)
						{
							*writing++ = target[0];
							cache = target[1];
							cacheAvailable = true;
						}
						else
						{
							break;
						}
				}
				
#endif
				readed++;
			}
			
			return readed;
		}
		
		/***********************************************************************
		BomEncoder
		***********************************************************************/
		
		BomEncoder::BomEncoder(Encoding _encoding)
			: encoding(_encoding)
			, encoder(0)
		{
			switch (encoding)
			{
				case Mbcs:
					encoder = new MbcsEncoder;
					break;
					
				case Utf8:
					encoder = new Utf8Encoder;
					break;
					
				case Utf16:
					encoder = new Utf16Encoder;
					break;
					
				case Utf16BE:
					encoder = new Utf16BEEncoder;
					break;
			}
		}
		
		BomEncoder::~BomEncoder()
		{
			Close();
		}
		
		void BomEncoder::Setup(IStream* _stream)
		{
			switch (encoding)
			{
				case Mbcs:
					break;
					
				case Utf8:
					_stream->Write((void*)"\xEF\xBB\xBF", 3);
					break;
					
				case Utf16:
					_stream->Write((void*)"\xFF\xFE", 2);
					break;
					
				case Utf16BE:
					_stream->Write((void*)"\xFE\xFF", 2);
					break;
			}
			
			encoder->Setup(_stream);
		}
		
		void BomEncoder::Close()
		{
			if (encoder)
			{
				encoder->Close();
				delete encoder;
				encoder = 0;
			}
		}
		
		vint BomEncoder::Write(void* _buffer, vint _size)
		{
			return encoder->Write(_buffer, _size);
		}
		
		/***********************************************************************
		BomDecoder
		***********************************************************************/
		
		BomDecoder::BomStream::BomStream(IStream* _stream, char* _bom, vint _bomLength)
			: stream(_stream)
			, bomPosition(0)
			, bomLength(_bomLength)
		{
			memcpy(bom, _bom, bomLength);
		}
		
		bool BomDecoder::BomStream::CanRead()const
		{
			return IsAvailable();
		}
		
		bool BomDecoder::BomStream::CanWrite()const
		{
			return false;
		}
		
		bool BomDecoder::BomStream::CanSeek()const
		{
			return false;
		}
		
		bool BomDecoder::BomStream::CanPeek()const
		{
			return false;
		}
		
		bool BomDecoder::BomStream::IsLimited()const
		{
			return stream != 0 && stream->IsLimited();
		}
		
		bool BomDecoder::BomStream::IsAvailable()const
		{
			return stream != 0 && stream->IsAvailable();
		}
		
		void BomDecoder::BomStream::Close()
		{
			stream = 0;
		}
		
		pos_t BomDecoder::BomStream::Position()const
		{
			return IsAvailable() ? bomPosition + stream->Position() : -1;
		}
		
		pos_t BomDecoder::BomStream::Size()const
		{
			return -1;
		}
		
		void BomDecoder::BomStream::Seek(pos_t _size)
		{
			CHECK_FAIL(L"BomDecoder::BomStream::Seek(pos_t)#Operation not supported.");
		}
		
		void BomDecoder::BomStream::SeekFromBegin(pos_t _size)
		{
			CHECK_FAIL(L"BomDecoder::BomStream::SeekFromBegin(pos_t)#Operation not supported.");
		}
		
		void BomDecoder::BomStream::SeekFromEnd(pos_t _size)
		{
			CHECK_FAIL(L"BomDecoder::BomStream::SeekFromEnd(pos_t)#Operation not supported.");
		}
		
		vint BomDecoder::BomStream::Read(void* _buffer, vint _size)
		{
			vint result = 0;
			unsigned char* buffer = (unsigned char*)_buffer;
			
			if (bomPosition < bomLength)
			{
				vint remain = bomLength - bomPosition;
				result = remain < _size ? remain : _size;
				memcpy(buffer, bom + bomPosition, result);
				buffer += result;
				bomPosition += result;
				_size -= result;
			}
			
			if (_size)
			{
				result += stream->Read(buffer, _size);
			}
			
			return result;
		}
		
		vint BomDecoder::BomStream::Write(void* _buffer, vint _size)
		{
			CHECK_FAIL(L"BomDecoder::BomStream::Write(void*, vint)#Operation not supported.");
		}
		
		vint BomDecoder::BomStream::Peek(void* _buffer, vint _size)
		{
			CHECK_FAIL(L"BomDecoder::BomStream::Peek(void*, vint)#Operation not supported.");
		}
		
		BomDecoder::BomDecoder()
			: decoder(0)
		{
		}
		
		BomDecoder::~BomDecoder()
		{
			Close();
		}
		
		void BomDecoder::Setup(IStream* _stream)
		{
			char bom[3] = { 0 };
			vint length = _stream->Read(bom, sizeof(bom));
			
			if (strncmp(bom, "\xEF\xBB\xBF", 3) == 0)
			{
				decoder = new Utf8Decoder;
				stream = new BomStream(_stream, bom + 3, 0);
			}
			else
				if (strncmp(bom, "\xFF\xFE", 2) == 0)
				{
					decoder = new Utf16Decoder;
					stream = new BomStream(_stream, bom + 2, 1);
				}
				else
					if (strncmp(bom, "\xFE\xFF", 2) == 0)
					{
						decoder = new Utf16BEDecoder;
						stream = new BomStream(_stream, bom + 2, 1);
					}
					else
					{
						decoder = new MbcsDecoder;
						stream = new BomStream(_stream, bom, 3);
					}
					
			decoder->Setup(stream);
		}
		
		void BomDecoder::Close()
		{
			if (decoder)
			{
				decoder->Close();
				delete decoder;
				decoder = 0;
				stream->Close();
				delete stream;
				stream = 0;
			}
		}
		
		vint BomDecoder::Read(void* _buffer, vint _size)
		{
			return decoder->Read(_buffer, _size);
		}
		
		/***********************************************************************
		CharEncoder
		***********************************************************************/
		
		bool CanBeMbcs(unsigned char* buffer, vint size)
		{
			for (vint i = 0; i < size; i++)
			{
				if (buffer[i] == 0)
				{
					return false;
				}
			}
			
			return true;
		}
		
		bool CanBeUtf8(unsigned char* buffer, vint size)
		{
			for (vint i = 0; i < size; i++)
			{
				unsigned char c = (unsigned char)buffer[i];
				
				if (c == 0)
				{
					return false;
				}
				else
				{
					vint count10xxxxxx = 0;
					
					if ((c & 0x80) == 0x00) /* 0x0xxxxxxx */
					{
						count10xxxxxx = 0;
					}
					else
						if ((c & 0xE0) == 0xC0) /* 0x110xxxxx */
						{
							count10xxxxxx = 1;
						}
						else
							if ((c & 0xF0) == 0xE0) /* 0x1110xxxx */
							{
								count10xxxxxx = 2;
							}
							else
								if ((c & 0xF8) == 0xF0) /* 0x11110xxx */
								{
									count10xxxxxx = 3;
								}
								else
									if ((c & 0xFC) == 0xF8) /* 0x111110xx */
									{
										count10xxxxxx = 4;
									}
									else
										if ((c & 0xFE) == 0xFC) /* 0x1111110x */
										{
											count10xxxxxx = 5;
										}
										
					if (size <= i + count10xxxxxx)
					{
						return false;
					}
					else
					{
						for (vint j = 0; j < count10xxxxxx; j++)
						{
							c = (unsigned char)buffer[i + j + 1];
							
							if ((c & 0xC0) != 0x80) /* 0x10xxxxxx */
							{
								return false;
							}
						}
					}
					
					i += count10xxxxxx;
				}
			}
			
			return true;
		}
		
		bool CanBeUtf16(unsigned char* buffer, vint size, bool& hitSurrogatePairs)
		{
			hitSurrogatePairs = false;
			
			if (size % 2 != 0)
			{
				return false;
			}
			
			bool needTrail = false;
			
			for (vint i = 0; i < size; i += 2)
			{
				vuint16_t c = buffer[i] + (buffer[i + 1] << 8);
				
				if (c == 0)
				{
					return false;
				}
				
				vint type = 0;
				
				if (0xD800 <= c && c <= 0xDBFF)
				{
					type = 1;
				}
				else
					if (0xDC00 <= c && c <= 0xDFFF)
					{
						type = 2;
					}
					
				if (needTrail)
				{
					if (type == 2)
					{
						needTrail = false;
					}
					else
					{
						return false;
					}
				}
				else
				{
					if (type == 1)
					{
						needTrail = true;
						hitSurrogatePairs = true;
					}
					else
						if (type != 0)
						{
							return false;
						}
				}
			}
			
			return !needTrail;
		}
		
		bool CanBeUtf16BE(unsigned char* buffer, vint size, bool& hitSurrogatePairs)
		{
			hitSurrogatePairs = false;
			
			if (size % 2 != 0)
			{
				return false;
			}
			
			bool needTrail = false;
			
			for (vint i = 0; i < size; i += 2)
			{
				vuint16_t c = buffer[i + 1] + (buffer[i] << 8);
				
				if (c == 0)
				{
					return false;
				}
				
				vint type = 0;
				
				if (0xD800 <= c && c <= 0xDBFF)
				{
					type = 1;
				}
				else
					if (0xDC00 <= c && c <= 0xDFFF)
					{
						type = 2;
					}
					
				if (needTrail)
				{
					if (type == 2)
					{
						needTrail = false;
					}
					else
					{
						return false;
					}
				}
				else
				{
					if (type == 1)
					{
						needTrail = true;
						hitSurrogatePairs = true;
					}
					else
						if (type != 0)
						{
							return false;
						}
				}
			}
			
			return !needTrail;
		}
		
#if defined VCZH_MSVC
		template<vint Count>
		bool GetEncodingResult(int(&tests)[Count], bool(&results)[Count], int test)
		{
			for (vint i = 0; i < Count; i++)
			{
				if (tests[i] & test)
				{
					if (results[i])
					{
						return true;
					}
				}
			}
			
			return false;
		}
#endif
		
		void TestEncoding(unsigned char* buffer, vint size, BomEncoder::Encoding& encoding, bool& containsBom)
		{
			if (size >= 3 && strncmp((char*)buffer, "\xEF\xBB\xBF", 3) == 0)
			{
				encoding = BomEncoder::Utf8;
				containsBom = true;
			}
			else
				if (size >= 2 && strncmp((char*)buffer, "\xFF\xFE", 2) == 0)
				{
					encoding = BomEncoder::Utf16;
					containsBom = true;
				}
				else
					if (size >= 2 && strncmp((char*)buffer, "\xFE\xFF", 2) == 0)
					{
						encoding = BomEncoder::Utf16BE;
						containsBom = true;
					}
					else
					{
						encoding = BomEncoder::Mbcs;
						containsBom = false;
						
						bool utf16HitSurrogatePairs = false;
						bool utf16BEHitSurrogatePairs = false;
						bool roughMbcs = CanBeMbcs(buffer, size);
						bool roughUtf8 = CanBeUtf8(buffer, size);
						bool roughUtf16 = CanBeUtf16(buffer, size, utf16HitSurrogatePairs);
						bool roughUtf16BE = CanBeUtf16BE(buffer, size, utf16BEHitSurrogatePairs);
						
						vint roughCount = (roughMbcs ? 1 : 0) + (roughUtf8 ? 1 : 0) + (roughUtf16 ? 1 : 0) + (roughUtf16BE ? 1 : 0);
						
						if (roughCount == 1)
						{
							if (roughUtf8)
							{
								encoding = BomEncoder::Utf8;
							}
							else
								if (roughUtf16)
								{
									encoding = BomEncoder::Utf16;
								}
								else
									if (roughUtf16BE)
									{
										encoding = BomEncoder::Utf16BE;
									}
						}
						else
							if (roughCount > 1)
							{
#if defined VCZH_MSVC
								int tests[] =
								{
									IS_TEXT_UNICODE_REVERSE_ASCII16,
									IS_TEXT_UNICODE_REVERSE_STATISTICS,
									IS_TEXT_UNICODE_REVERSE_CONTROLS,
									
									IS_TEXT_UNICODE_ASCII16,
									IS_TEXT_UNICODE_STATISTICS,
									IS_TEXT_UNICODE_CONTROLS,
									
									IS_TEXT_UNICODE_ILLEGAL_CHARS,
									IS_TEXT_UNICODE_ODD_LENGTH,
									IS_TEXT_UNICODE_NULL_BYTES,
								};
								
								const vint TestCount = sizeof(tests) / sizeof(*tests);
								bool results[TestCount];
								
								for (vint i = 0; i < TestCount; i++)
								{
									int test = tests[i];
									results[i] = IsTextUnicode(buffer, (int)size, &test) != 0;
								}
								
								if (size % 2 == 0
								  && !GetEncodingResult(tests, results, IS_TEXT_UNICODE_REVERSE_ASCII16)
								  && !GetEncodingResult(tests, results, IS_TEXT_UNICODE_REVERSE_STATISTICS)
								  && !GetEncodingResult(tests, results, IS_TEXT_UNICODE_REVERSE_CONTROLS)
								)
								{
									for (vint i = 0; i < size; i += 2)
									{
										unsigned char c = buffer[i];
										buffer[i] = buffer[i + 1];
										buffer[i + 1] = c;
									}
									
									// 3 = (count of reverse group) = (count of unicode group)
									for (vint i = 0; i < 3; i++)
									{
										int test = tests[i + 3];
										results[i] = IsTextUnicode(buffer, (int)size, &test) != 0;
									}
									
									for (vint i = 0; i < size; i += 2)
									{
										unsigned char c = buffer[i];
										buffer[i] = buffer[i + 1];
										buffer[i + 1] = c;
									}
								}
								
								if (GetEncodingResult(tests, results, IS_TEXT_UNICODE_NOT_UNICODE_MASK))
								{
									if (GetEncodingResult(tests, results, IS_TEXT_UNICODE_NOT_ASCII_MASK))
									{
										encoding = BomEncoder::Utf8;
									}
									else
										if (roughUtf8 || !roughMbcs)
										{
											encoding = BomEncoder::Utf8;
										}
								}
								else
									if (GetEncodingResult(tests, results, IS_TEXT_UNICODE_ASCII16))
									{
										encoding = BomEncoder::Utf16;
									}
									else
										if (GetEncodingResult(tests, results, IS_TEXT_UNICODE_REVERSE_ASCII16))
										{
											encoding = BomEncoder::Utf16BE;
										}
										else
											if (GetEncodingResult(tests, results, IS_TEXT_UNICODE_CONTROLS))
											{
												encoding = BomEncoder::Utf16;
											}
											else
												if (GetEncodingResult(tests, results, IS_TEXT_UNICODE_REVERSE_CONTROLS))
												{
													encoding = BomEncoder::Utf16BE;
												}
												else
												{
													if (!roughUtf8)
													{
														if (GetEncodingResult(tests, results, IS_TEXT_UNICODE_STATISTICS))
														{
															encoding = BomEncoder::Utf16;
														}
														else
															if (GetEncodingResult(tests, results, IS_TEXT_UNICODE_STATISTICS))
															{
																encoding = BomEncoder::Utf16BE;
															}
													}
													else
														if (GetEncodingResult(tests, results, IS_TEXT_UNICODE_NOT_UNICODE_MASK))
														{
															encoding = BomEncoder::Utf8;
														}
														else
															if (roughUtf8 || !roughMbcs)
															{
																encoding = BomEncoder::Utf8;
															}
												}
												
#endif
							}
					}
		}
	}
}



// #include "CompressionStream.h"

namespace vl
{
	namespace stream
	{
		using namespace lzw;
		
		/***********************************************************************
		LzwBase
		***********************************************************************/
		
		void LzwBase::UpdateIndexBits()
		{
			if (nextIndex >= 2 && (nextIndex & (nextIndex - 1)) == 0)
			{
				indexBits++;
			}
		}
		
		lzw::Code* LzwBase::CreateCode(lzw::Code* prefix, vuint8_t byte)
		{
			if (nextIndex < MaxDictionarySize)
			{
				Code* code = codeAllocator.Create();
				code->byte = byte;
				code->code = nextIndex;
				code->parent = prefix;
				code->size = prefix->size + 1;
				prefix->children.Set(byte, code, mapAllocator);
				nextIndex++;
				
				return code;
			}
			else
			{
				return 0;
			}
		}
		
		LzwBase::LzwBase()
			: codeAllocator(65536)
			, mapAllocator(1048576),
			  eofIndex(-1),
			  nextIndex(0),
			  indexBits(1)
		{
			root = codeAllocator.Create();
			
			for (vint i = 0; i < 256; i++)
			{
				UpdateIndexBits();
				CreateCode(root, (vuint8_t)i);
			}
		}
		
		LzwBase::LzwBase(bool(&existingBytes)[256])
			: eofIndex(-1),
			  nextIndex(0),
			  indexBits(1)
		{
			root = codeAllocator.Create();
			
			for (vint i = 0; i < 256; i++)
			{
				if (existingBytes[i])
				{
					UpdateIndexBits();
					CreateCode(root, (vuint8_t)i);
				}
			}
			
			if (indexBits < 8)
			{
				eofIndex = nextIndex++;
			}
		}
		
		LzwBase::~LzwBase()
		{
		}
		
		/***********************************************************************
		LzwEncoder
		***********************************************************************/
		
		void LzwEncoder::Flush()
		{
			vint written = 0;
			vint bufferUsedSize = bufferUsedBits / 8;
			
			if (bufferUsedBits % 8 != 0)
			{
				bufferUsedSize++;
			}
			
			while (written < bufferUsedSize)
			{
				vint size = stream->Write(buffer + written, bufferUsedSize - written);
				CHECK_ERROR(size != 0, L"LzwEncoder::Flush()#Failed to flush the lzw buffer.");
				written += size;
			}
			
			bufferUsedBits = 0;
		}
		
		vuint8_t highMarks[9] = { 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF };
		vuint8_t lowMarks[9] = { 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF };
		
		void LzwEncoder::WriteNumber(vint number, vint bitSize)
		{
			vint bitStart = 0;
			vint bitStep = 8 - bufferUsedBits % 8;
			
			if (bitStep > bitSize)
			{
				bitStep = bitSize;
			}
			
			while (bitStart < bitSize)
			{
				if (bufferUsedBits == BufferSize * 8)
				{
					Flush();
				}
				
				vint writeStart = bufferUsedBits % 8;
				vint byteIndex = bufferUsedBits / 8;
				vuint8_t byte = buffer[byteIndex];
				byte &= highMarks[writeStart];
				
				vuint8_t content = (vuint8_t)((number >> bitStart)&lowMarks[bitStep]) << (8 - writeStart - bitStep);
				byte |= content;
				
				buffer[byteIndex] = byte;
				bufferUsedBits += bitStep;
				
				bitStart += bitStep;
				vint remain = bitSize - bitStart;
				bitStep = remain < 8 ? remain : 8;
			}
		}
		
		LzwEncoder::LzwEncoder()
			: stream(NULL),
			  bufferUsedBits(0)
		{
			prefix = root;
		}
		
		LzwEncoder::LzwEncoder(bool(&existingBytes)[256])
			: LzwBase(existingBytes),
			  stream(NULL),
			  bufferUsedBits(0)
		{
			prefix = root;
		}
		
		LzwEncoder::~LzwEncoder()
		{
		}
		
		void LzwEncoder::Setup(IStream* _stream)
		{
			stream = _stream;
		}
		
		void LzwEncoder::Close()
		{
			if (prefix != root)
			{
				WriteNumber(prefix->code, indexBits);
				prefix = root;
			}
			
			vint remain = 8 - bufferUsedBits % 8;
			
			if (remain != 8 && remain >= indexBits)
			{
				CHECK_ERROR(eofIndex != -1, L"LzwEncoder::Close()#Internal error.");
				WriteNumber(eofIndex, indexBits);
			}
			
			Flush();
		}
		
		vint LzwEncoder::Write(void* _buffer, vint _size)
		{
			vuint8_t* bytes = (vuint8_t*)_buffer;
			
			for (vint i = 0; i < _size; i++)
			{
				vuint8_t byte = bytes[i];
				Code* next = prefix->children.Get(byte);
				
				if (next)
				{
					prefix = next;
				}
				else
				{
					WriteNumber(prefix->code, indexBits);
					
					if (nextIndex < MaxDictionarySize)
					{
						UpdateIndexBits();
						CreateCode(prefix, byte);
					}
					
					prefix = root->children.Get(byte);
				}
			}
			
			return _size;
		}
		
		/***********************************************************************
		LzwDecoder
		***********************************************************************/
		
		bool LzwDecoder::ReadNumber(vint& number, vint bitSize)
		{
			number = 0;
			
			if (inputBufferSize == -1)
			{
				return false;
			}
			
			vint remainBits = inputBufferSize * 8 - inputBufferUsedBits;
			vint writtenBits = 0;
			vint bitStep = 8 - inputBufferUsedBits % 8;
			
			if (bitStep > bitSize)
			{
				bitStep = bitSize;
			}
			
			while (writtenBits < bitSize)
			{
				if (remainBits == 0)
				{
					inputBufferSize = stream->Read(inputBuffer, BufferSize);
					
					if (inputBufferSize == 0)
					{
						inputBufferSize = -1;
						return false;
					}
					
					remainBits = inputBufferSize * 8;
					inputBufferUsedBits = 0;
				}
				
				vuint8_t byte = inputBuffer[inputBufferUsedBits / 8];
				byte >>= (8 - inputBufferUsedBits % 8 - bitStep);
				byte &= lowMarks[bitStep];
				number |= byte << writtenBits;
				
				inputBufferUsedBits += bitStep;
				remainBits -= bitStep;
				writtenBits += bitStep;
				vint remain = bitSize - writtenBits;
				bitStep = remain < 8 ? remain : 8;
			}
			
			return true;
		}
		
		void LzwDecoder::PrepareOutputBuffer(vint size)
		{
			if (outputBuffer.Count() < size)
			{
				outputBuffer.Resize(size);
			}
			
			outputBufferSize = size;
		}
		
		void LzwDecoder::ExpandCodeToOutputBuffer(lzw::Code* code)
		{
			vuint8_t* outputByte = &outputBuffer[0] + code->size;
			Code* current = code;
			
			while (current != root)
			{
				*(--outputByte) = current->byte;
				current = current->parent;
			}
			
			outputBufferUsedBytes = 0;
		}
		
		LzwDecoder::LzwDecoder()
			: stream(NULL),
			  lastCode(NULL),
			  inputBufferSize(0),
			  inputBufferUsedBits(0),
			  outputBufferSize(0),
			  outputBufferUsedBytes(0)
		{
			for (vint i = 0; i < 256; i++)
			{
				dictionary.Add(root->children.Get((vuint8_t)i));
			}
		}
		
		LzwDecoder::LzwDecoder(bool(&existingBytes)[256])
			: LzwBase(existingBytes),
			  stream(NULL),
			  lastCode(NULL),
			  inputBufferSize(0),
			  inputBufferUsedBits(0),
			  outputBufferSize(0),
			  outputBufferUsedBytes(0)
		{
			for (vint i = 0; i < 256; i++)
			{
				if (existingBytes[i])
				{
					dictionary.Add(root->children.Get((vuint8_t)i));
				}
			}
			
			if (eofIndex != -1)
			{
				dictionary.Add(0);
			}
		}
		
		LzwDecoder::~LzwDecoder()
		{
		}
		
		void LzwDecoder::Setup(IStream* _stream)
		{
			stream = _stream;
		}
		
		void LzwDecoder::Close()
		{
		}
		
		vint LzwDecoder::Read(void* _buffer, vint _size)
		{
			vint written = 0;
			vuint8_t* bytes = (vuint8_t*)_buffer;
			
			while (written < _size)
			{
				vint expect = _size - written;
				vint remain = outputBufferSize - outputBufferUsedBytes;
				
				if (remain == 0)
				{
					vint index = 0;
					
					if (!ReadNumber(index, indexBits) || index == eofIndex)
					{
						break;
					}
					
					Code* prefix = 0;
					
					if (index == dictionary.Count())
					{
						prefix = lastCode;
						PrepareOutputBuffer(prefix->size + 1);
						ExpandCodeToOutputBuffer(prefix);
						outputBuffer[outputBufferSize - 1] = outputBuffer[0];
					}
					else
					{
						prefix = dictionary[index];
						PrepareOutputBuffer(prefix->size);
						ExpandCodeToOutputBuffer(prefix);
					}
					
					if (nextIndex < MaxDictionarySize)
					{
						if (lastCode)
						{
							dictionary.Add(CreateCode(lastCode, outputBuffer[0]));
						}
						
						UpdateIndexBits();
					}
					
					lastCode = dictionary[index];
				}
				else
				{
					if (remain > expect)
					{
						remain = expect;
					}
					
					memcpy(bytes + written, &outputBuffer[outputBufferUsedBytes], remain);
					
					outputBufferUsedBytes += remain;
					written += remain;
				}
			}
			
			return written;
		}
	}
}


// #include "FileStream.h"
// #if defined VCZH_GCC
// #include <stdio.h>
// #endif

namespace vl
{
	namespace stream
	{
	
#if defined VCZH_GCC
		void _fseeki64(FILE* file, pos_t offset, int origin)
		{
			fseek(file, (long)offset, origin);
		}
#endif
		
		/***********************************************************************
		FileStream
		***********************************************************************/
		
		FileStream::FileStream(const WString& fileName, AccessRight _accessRight)
			: accessRight(_accessRight)
		{
			const wchar_t* mode = L"rb";
			
			switch (accessRight)
			{
				case ReadOnly:
					mode = L"rb";
					break;
					
				case WriteOnly:
					mode = L"wb";
					break;
					
				case ReadWrite:
					mode = L"w+b";
					break;
			}
			
#if defined VCZH_MSVC
			
			if (_wfopen_s(&file, fileName.Buffer(), mode) != 0)
			{
				file = 0;
			}
			
#endif
		}
		
		FileStream::~FileStream()
		{
			Close();
		}
		
		bool FileStream::CanRead()const
		{
			return file != 0 && (accessRight == ReadOnly || accessRight == ReadWrite);
		}
		
		bool FileStream::CanWrite()const
		{
			return file != 0 && (accessRight == WriteOnly || accessRight == ReadWrite);
		}
		
		bool FileStream::CanSeek()const
		{
			return file != 0;
		}
		
		bool FileStream::CanPeek()const
		{
			return file != 0 && (accessRight == ReadOnly || accessRight == ReadWrite);
		}
		
		bool FileStream::IsLimited()const
		{
			return file != 0 && accessRight == ReadOnly;
		}
		
		bool FileStream::IsAvailable()const
		{
			return file != 0;
		}
		
		void FileStream::Close()
		{
			if (file != 0)
			{
				fclose(file);
				file = 0;
			}
		}
		
		pos_t FileStream::Position()const
		{
			if (file != 0)
			{
#if defined VCZH_MSVC
				fpos_t position = 0;
				
				if (fgetpos(file, &position) == 0)
				{
					return position;
				}
				
#elif defined VCZH_GCC
				return (pos_t)ftell(file);
#endif
			}
			
			return -1;
		}
		
		pos_t FileStream::Size()const
		{
			if (file != 0)
			{
#if defined VCZH_MSVC
				fpos_t position = 0;
				
				if (fgetpos(file, &position) == 0)
				{
					if (fseek(file, 0, SEEK_END) == 0)
					{
						pos_t size = Position();
						
						if (fsetpos(file, &position) == 0)
						{
							return size;
						}
					}
				}
				
#endif
			}
			
			return -1;
		}
		
		void FileStream::Seek(pos_t _size)
		{
			if (Position() + _size > Size())
			{
				_fseeki64(file, 0, SEEK_END);
			}
			else
				if (Position() + _size < 0)
				{
					_fseeki64(file, 0, SEEK_SET);
				}
				else
				{
					_fseeki64(file, _size, SEEK_CUR);
				}
		}
		
		void FileStream::SeekFromBegin(pos_t _size)
		{
			if (_size > Size())
			{
				_fseeki64(file, 0, SEEK_END);
			}
			else
				if (_size < 0)
				{
					_fseeki64(file, 0, SEEK_SET);
				}
				else
				{
					_fseeki64(file, _size, SEEK_SET);
				}
		}
		
		void FileStream::SeekFromEnd(pos_t _size)
		{
			if (_size < 0)
			{
				_fseeki64(file, 0, SEEK_END);
			}
			else
				if (_size > Size())
				{
					_fseeki64(file, 0, SEEK_SET);
				}
				else
				{
					_fseeki64(file, -_size, SEEK_END);
				}
		}
		
		vint FileStream::Read(void* _buffer, vint _size)
		{
			CHECK_ERROR(file != 0, L"FileStream::Read(pos_t)#Stream is closed, cannot perform this operation.");
			CHECK_ERROR(_size >= 0, L"FileStream::Read(void*, vint)#Argument size cannot be negative.");
			return fread(_buffer, 1, _size, file);
		}
		
		vint FileStream::Write(void* _buffer, vint _size)
		{
			CHECK_ERROR(file != 0, L"FileStream::Write(pos_t)#Stream is closed, cannot perform this operation.");
			CHECK_ERROR(_size >= 0, L"FileStream::Write(void*, vint)#Argument size cannot be negative.");
			return fwrite(_buffer, 1, _size, file);
		}
		
		vint FileStream::Peek(void* _buffer, vint _size)
		{
			CHECK_ERROR(file != 0, L"FileStream::Peek(pos_t)#Stream is closed, cannot perform this operation.");
			CHECK_ERROR(_size >= 0, L"FileStream::Peek(void*, vint)#Argument size cannot be negative.");
#if defined VCZH_MSVC
			fpos_t position = 0;
			
			if (fgetpos(file, &position) == 0)
			{
				size_t count = fread(_buffer, 1, _size, file);
				
				if (fsetpos(file, &position) == 0)
				{
					return count;
				}
			}
			
			return -1;
#endif
		}
	}
}


#include <string.h>
// #include "RecorderStream.h"

namespace vl
{
	namespace stream
	{
		/***********************************************************************
		RecorderStream
		***********************************************************************/
		
		RecorderStream::RecorderStream(IStream& _in, IStream& _out)
			: in(&_in)
			, out(&_out)
		{
		}
		
		RecorderStream::~RecorderStream()
		{
		}
		
		bool RecorderStream::CanRead()const
		{
			return IsAvailable() && in->CanRead();
		}
		
		bool RecorderStream::CanWrite()const
		{
			return false;
		}
		
		bool RecorderStream::CanSeek()const
		{
			return false;
		}
		
		bool RecorderStream::CanPeek()const
		{
			return false;
		}
		
		bool RecorderStream::IsLimited()const
		{
			return IsAvailable() && in->IsLimited();
		}
		
		bool RecorderStream::IsAvailable()const
		{
			return in != 0 && out != 0 && in->IsAvailable() && out->IsAvailable();
		}
		
		void RecorderStream::Close()
		{
			in = 0;
			out = 0;
		}
		
		pos_t RecorderStream::Position()const
		{
			return IsAvailable() ? in->Position() : -1;
		}
		
		pos_t RecorderStream::Size()const
		{
			return IsAvailable() ? in->Size() : -1;
		}
		
		void RecorderStream::Seek(pos_t _size)
		{
			CHECK_FAIL(L"RecorderStream::Seek(pos_t)#Operation not supported.");
		}
		
		void RecorderStream::SeekFromBegin(pos_t _size)
		{
			CHECK_FAIL(L"RecorderStream::SeekFromBegin(pos_t)#Operation not supported.");
		}
		
		void RecorderStream::SeekFromEnd(pos_t _size)
		{
			CHECK_FAIL(L"RecorderStream::SeekFromEnd(pos_t)#Operation not supported.");
		}
		
		vint RecorderStream::Read(void* _buffer, vint _size)
		{
			_size = in->Read(_buffer, _size);
			out->Write(_buffer, _size);
			return _size;
		}
		
		vint RecorderStream::Write(void* _buffer, vint _size)
		{
			CHECK_FAIL(L"RecorderStream::Write(void*, vint)#Operation not supported.");
		}
		
		vint RecorderStream::Peek(void* _buffer, vint _size)
		{
			CHECK_FAIL(L"RecorderStream::Peek(void*, vint)#Operation not supported.");
		}
	}
}

// #include "FilePath.h"
//
// #include "../Locale.h"
// #include "../Collections/OperationForEach.h"
// #include "../Stream/FileStream.h"
// #include "../Stream/Accessor.h"
// #include "../Exception.h"
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

#define NICE_MAX_PATH  65536


namespace vl
{
	namespace filesystem
	{
	
		using namespace collections;
		using namespace stream;
		
		// ReadDirectoryChangesW
		
		/***********************************************************************
		FilePath
		***********************************************************************/
		
#if defined VCZH_GCC
		const wchar_t FilePath::Delimiter;
#endif
		
		void FilePath::Initialize()
		{
			{
				Array<wchar_t> buffer(fullPath.Length() + 1);
#if defined VCZH_MSVC
				wcscpy_s(&buffer[0], fullPath.Length() + 1, fullPath.Buffer());
#elif defined VCZH_GCC
				wcscpy(&buffer[0], fullPath.Buffer());
#endif
				
				for (vint i = 0; i < buffer.Count(); i++)
				{
					if (buffer[i] == L'\\' || buffer[i] == L'/')
					{
						buffer[i] = Delimiter;
					}
				}
				
				fullPath = &buffer[0];
			}
			
#if defined VCZH_MSVC
			
			if (fullPath != L"")
			{
				if (fullPath.Length() < 2 || fullPath[1] != L':')
				{
					wchar_t buffer[MAX_PATH + 1] = { 0 };
					DWORD result = GetCurrentDirectory(sizeof(buffer) / sizeof(*buffer), buffer);
					
					if (result > MAX_PATH + 1 || result == 0)
					{
						throw ArgumentException(L"Failed to call GetCurrentDirectory.", L"vl::filesystem::FilePath::Initialize", L"");
					}
					
					fullPath = WString(buffer) + L"\\" + fullPath;
				}
				
				{
					wchar_t buffer[MAX_PATH + 1] = { 0 };
					
					if (fullPath.Length() == 2 && fullPath[1] == L':')
					{
						fullPath += L"\\";
					}
					
					DWORD result = GetFullPathName(fullPath.Buffer(), sizeof(buffer) / sizeof(*buffer), buffer, NULL);
					
					if (result > MAX_PATH + 1 || result == 0)
					{
						throw ArgumentException(L"The path is illegal.", L"vl::filesystem::FilePath::FilePath", L"_filePath");
					}
					
					fullPath = buffer;
				}
			}
			
#endif
			
			if (fullPath != L"/" && fullPath.Length() > 0 && fullPath[fullPath.Length() - 1] == Delimiter)
			{
				fullPath = fullPath.Left(fullPath.Length() - 1);
			}
		}
		
		FilePath::FilePath()
		{
		}
		
		FilePath::FilePath(const WString& _filePath)
			: fullPath(_filePath)
		{
			Initialize();
		}
		
		FilePath::FilePath(const wchar_t* _filePath)
			: fullPath(_filePath)
		{
			Initialize();
		}
		
		FilePath::FilePath(const FilePath& _filePath)
			: fullPath(_filePath.fullPath)
		{
			Initialize();
		}
		
		FilePath::~FilePath()
		{
		}
		
		FilePath FilePath::CurrentPath()
		{
			wchar_t buffer[NICE_MAX_PATH] = { 0 };
			::GetCurrentDirectory(sizeof(buffer) / sizeof(*buffer), &buffer[0]);
			return &buffer[0];
		}
		
		FilePath FilePath::TheAppPath()
		{
			wchar_t buffer[NICE_MAX_PATH] = { 0 };
			::GetModuleFileName(NULL, buffer, sizeof(buffer) / sizeof(*buffer));
			return buffer;
		}
		
		FilePath FilePath::TempPath()
		{
			wchar_t buffer[NICE_MAX_PATH] = { 0 };
			::GetTempPath(sizeof(buffer) / sizeof(*buffer), buffer);
			return buffer;
		}
		
		vint FilePath::Compare(const FilePath& a, const FilePath& b)
		{
			return WString::Compare(a.fullPath, b.fullPath);
		}
		
		FilePath FilePath::operator/(const WString& relativePath)const
		{
			if (IsRoot())
			{
				return relativePath;
			}
			else
			{
				return fullPath + L"/" + relativePath;
			}
		}
		
		bool FilePath::IsFile()const
		{
#if defined VCZH_MSVC
			WIN32_FILE_ATTRIBUTE_DATA info;
			BOOL result = GetFileAttributesEx(fullPath.Buffer(), GetFileExInfoStandard, &info);
			
			if (!result)
			{
				return false;
			}
			
			return (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
#endif
		}
		
		bool FilePath::IsFolder()const
		{
#if defined VCZH_MSVC
			WIN32_FILE_ATTRIBUTE_DATA info;
			BOOL result = GetFileAttributesEx(fullPath.Buffer(), GetFileExInfoStandard, &info);
			
			if (!result)
			{
				return false;
			}
			
			return (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
#endif
		}
		
		bool FilePath::IsRoot()const
		{
#if defined VCZH_MSVC
			return fullPath == L"";
#elif defined VCZH_GCC
			return fullPath == L"/";
#endif
		}
		
		WString FilePath::GetName()const
		{
			WString delimiter = Delimiter;
			collections::Pair<vint, vint> index = INVLOC.FindLast(fullPath, delimiter, Locale::None);
			
			if (index.key == -1)
			{
				return fullPath;
			}
			
			return fullPath.Right(fullPath.Length() - index.key - 1);
		}
		
		FilePath FilePath::GetFolder()const
		{
			WString delimiter = Delimiter;
			collections::Pair<vint, vint> index = INVLOC.FindLast(fullPath, delimiter, Locale::None);
			
			if (index.key == -1)
			{
				return FilePath();
			}
			
			return fullPath.Left(index.key);
		}
		
		WString FilePath::GetFullPath()const
		{
			return fullPath;
		}
		
		WString FilePath::GetRelativePathFor(const FilePath& _filePath)
		{
			if (fullPath.Length() == 0 || _filePath.fullPath.Length() == 0 || fullPath[0] != _filePath.fullPath[0])
			{
				return _filePath.fullPath;
			}
			
#if defined VCZH_MSVC
			wchar_t buffer[MAX_PATH + 1] = { 0 };
			PathRelativePathTo(
			  buffer,
			  fullPath.Buffer(),
			  (IsFolder() ? FILE_ATTRIBUTE_DIRECTORY : 0),
			  _filePath.fullPath.Buffer(),
			  (_filePath.IsFolder() ? FILE_ATTRIBUTE_DIRECTORY : 0)
			);
			return buffer;
#endif
		}
		
		void FilePath::GetPathComponents(WString path, collections::List<WString>& components)
		{
			WString pathRemaining = path;
			WString delimiter = Delimiter;
			
			components.Clear();
			
			while (true)
			{
				collections::Pair<vint, vint> index = INVLOC.FindFirst(pathRemaining, delimiter, Locale::None);
				
				if (index.key == -1)
				{
					break;
				}
				
				if (index.key != 0)
				{
					components.Add(pathRemaining.Left(index.key));
				}
				else
				{
#if defined VCZH_GCC
					// Unix absolute path starting with "/"
					// components[0] will be L"/"
					components.Add(delimiter);
#elif defined VCZH_MSVC
					
					if (pathRemaining.Length() >= 2 && pathRemaining[1] == Delimiter)
					{
						// Windows UNC Path starting with "\\"
						// components[0] will be L"\\"
						components.Add(L"\\");
						index.value++;
					}
					
#endif
				}
				
				pathRemaining = pathRemaining.Right(pathRemaining.Length() - (index.key + index.value));
			}
			
			if (pathRemaining.Length() != 0)
			{
				components.Add(pathRemaining);
			}
		}
		
		WString FilePath::ComponentsToPath(const collections::List<WString>& components)
		{
			WString result;
			WString delimiter = Delimiter;
			
			int i = 0;
			
#if defined VCZH_GCC
			
			// For Unix-like OSes, if first component is "/" then take it as absolute path
			if (components.Count() > 0 && components[0] == delimiter)
			{
				result += delimiter;
				i++;
			}
			
#elif defined VCZH_MSVC
			
			// For Windows, if first component is "\\" then it is an UNC path
			if (components.Count() > 0 && components[0] == L"\\")
			{
				result += delimiter;
				i++;
			}
			
#endif
			
			for (; i < components.Count(); i++)
			{
				result += components[i];
				
				if (i + 1 < components.Count())
				{
					result += delimiter;
				}
			}
			
			return result;
		}
	}
}


// #include "File.h"
// #include "../Collections/OperationForEach.h"
// #include "../Stream/FileStream.h"
// #include "../Stream/Accessor.h"
#include <Windows.h>
// #include <Shlwapi.h>
// #pragma comment(lib, "Shlwapi.lib")

namespace vl
{
	namespace filesystem
	{
		using namespace collections;
		using namespace stream;
		
		/***********************************************************************
		File
		***********************************************************************/
		
		File::File()
		{
		}
		
		File::File(const FilePath& _filePath)
			: filePath(_filePath)
		{
		}
		
		File::~File()
		{
		}
		
		const FilePath& File::GetFilePath()const
		{
			return filePath;
		}
		
		bool File::ReadAllTextWithEncodingTesting(WString& text, stream::BomEncoder::Encoding& encoding, bool& containsBom)
		{
			Array<unsigned char> buffer;
			{
				FileStream fileStream(filePath.GetFullPath(), FileStream::ReadOnly);
				
				if (!fileStream.IsAvailable())
				{
					return false;
				}
				
				if (fileStream.Size() == 0)
				{
					text = L"";
					encoding = BomEncoder::Mbcs;
					containsBom = false;
					return true;
				}
				
				buffer.Resize((vint)fileStream.Size());
				vint count = fileStream.Read(&buffer[0], buffer.Count());
				CHECK_ERROR(count == buffer.Count(), L"vl::filesystem::File::ReadAllTextWithEncodingTesting(WString&, BomEncoder::Encoding&, bool&)#Failed to read the whole file.");
			}
			TestEncoding(&buffer[0], buffer.Count(), encoding, containsBom);
			
			MemoryWrapperStream memoryStream(&buffer[0], buffer.Count());
			
			if (containsBom)
			{
				BomDecoder decoder;
				DecoderStream decoderStream(memoryStream, decoder);
				StreamReader reader(decoderStream);
				text = reader.ReadToEnd();
			}
			else
			{
				switch (encoding)
				{
					case BomEncoder::Utf8:
						{
							Utf8Decoder decoder;
							DecoderStream decoderStream(memoryStream, decoder);
							StreamReader reader(decoderStream);
							text = reader.ReadToEnd();
						}
						break;
						
					case BomEncoder::Utf16:
						{
							Utf16Decoder decoder;
							DecoderStream decoderStream(memoryStream, decoder);
							StreamReader reader(decoderStream);
							text = reader.ReadToEnd();
						}
						break;
						
					case BomEncoder::Utf16BE:
						{
							Utf16BEDecoder decoder;
							DecoderStream decoderStream(memoryStream, decoder);
							StreamReader reader(decoderStream);
							text = reader.ReadToEnd();
						}
						break;
						
					default:
						{
							MbcsDecoder decoder;
							DecoderStream decoderStream(memoryStream, decoder);
							StreamReader reader(decoderStream);
							text = reader.ReadToEnd();
						}
				}
			}
			
			return true;
		}
		
		WString File::ReadAllTextByBom()const
		{
			WString text;
			ReadAllTextByBom(text);
			return text;
		}
		
		bool File::ReadAllTextByBom(WString& text)const
		{
			FileStream fileStream(filePath.GetFullPath(), FileStream::ReadOnly);
			
			if (!fileStream.IsAvailable())
			{
				return false;
			}
			
			BomDecoder decoder;
			DecoderStream decoderStream(fileStream, decoder);
			StreamReader reader(decoderStream);
			text = reader.ReadToEnd();
			return true;
		}
		
		bool File::ReadAllLinesByBom(collections::List<WString>& lines)const
		{
			FileStream fileStream(filePath.GetFullPath(), FileStream::ReadOnly);
			
			if (!fileStream.IsAvailable())
			{
				return false;
			}
			
			BomDecoder decoder;
			DecoderStream decoderStream(fileStream, decoder);
			StreamReader reader(decoderStream);
			
			while (!reader.IsEnd())
			{
				lines.Add(reader.ReadLine());
			}
			
			return true;
		}
		
		bool File::WriteAllText(const WString& text, bool bom, stream::BomEncoder::Encoding encoding)
		{
			FileStream fileStream(filePath.GetFullPath(), FileStream::WriteOnly);
			
			if (!fileStream.IsAvailable())
			{
				return false;
			}
			
			IEncoder* encoder = NULL;
			
			if (bom)
			{
				encoder = new BomEncoder(encoding);
			}
			else switch (encoding)
				{
					case BomEncoder::Utf8:
						encoder = new Utf8Encoder;
						break;
						
					case BomEncoder::Utf16:
						encoder = new Utf16Encoder;
						break;
						
					case BomEncoder::Utf16BE:
						encoder = new Utf16BEEncoder;
						break;
						
					default:
						encoder = new MbcsEncoder;
						break;
				}
				
			{
				EncoderStream encoderStream(fileStream, *encoder);
				StreamWriter writer(encoderStream);
				writer.WriteString(text);
			}
			
			delete encoder;
			return true;
		}
		
		bool File::WriteAllLines(collections::List<WString>& lines, bool bom, stream::BomEncoder::Encoding encoding)
		{
			FileStream fileStream(filePath.GetFullPath(), FileStream::WriteOnly);
			
			if (!fileStream.IsAvailable())
			{
				return false;
			}
			
			IEncoder* encoder = NULL;
			
			if (bom)
			{
				encoder = new BomEncoder(encoding);
			}
			else switch (encoding)
				{
					case BomEncoder::Utf8:
						encoder = new Utf8Encoder;
						break;
						
					case BomEncoder::Utf16:
						encoder = new Utf16Encoder;
						break;
						
					case BomEncoder::Utf16BE:
						encoder = new Utf16BEEncoder;
						break;
						
					default:
						encoder = new MbcsEncoder;
						break;
				}
				
			{
				EncoderStream encoderStream(fileStream, *encoder);
				StreamWriter writer(encoderStream);
				FOREACH(WString, line, lines)
				{
					writer.WriteLine(line);
				}
			}
			
			delete encoder;
			return true;
		}
		
		bool File::Exists()const
		{
			return filePath.IsFile();
		}
		
		bool File::Delete()const
		{
#if defined VCZH_MSVC
			return DeleteFile(filePath.GetFullPath().Buffer()) != 0;
#elif defined VCZH_GCC
			AString path = wtoa(filePath.GetFullPath());
			return unlink(path.Buffer()) == 0;
#endif
		}
		
		bool File::Rename(const WString& newName)const
		{
#if defined VCZH_MSVC
			WString oldFileName = filePath.GetFullPath();
			WString newFileName = (filePath.GetFolder() / newName).GetFullPath();
			return MoveFile(oldFileName.Buffer(), newFileName.Buffer()) != 0;
#elif defined VCZH_GCC
			AString oldFileName = wtoa(filePath.GetFullPath());
			AString newFileName = wtoa((filePath.GetFolder() / newName).GetFullPath());
			return rename(oldFileName.Buffer(), newFileName.Buffer()) == 0;
#endif
		}
		
	}
}

#include <Windows.h>
// #include <Shlwapi.h>
// #pragma comment(lib, "Shlwapi.lib")

// #include "../Collections/OperationForEach.h"
// #include "Folder.h"
// #include "FileSystem.h"

namespace vl
{
	namespace filesystem
	{
		using namespace collections;
		
		/***********************************************************************
		Folder
		***********************************************************************/
		
		Folder::Folder()
		{
		}
		
		Folder::Folder(const FilePath& _filePath)
			: filePath(_filePath)
		{
		}
		
		Folder::~Folder()
		{
		}
		
		const FilePath& Folder::GetFilePath()const
		{
			return filePath;
		}
		
		bool Folder::GetFolders(collections::List<Folder>& folders)const
		{
#if defined VCZH_MSVC
		
			if (filePath.IsRoot())
			{
				DWORD bufferSize = GetLogicalDriveStrings(0, NULL);
				
				if (bufferSize > 0)
				{
					Array<wchar_t> buffer(bufferSize);
					
					if (GetLogicalDriveStrings((DWORD)buffer.Count(), &buffer[0]) > 0)
					{
						wchar_t* begin = &buffer[0];
						wchar_t* end = begin + buffer.Count();
						
						while (begin < end && *begin)
						{
							WString driveString = begin;
							begin += driveString.Length() + 1;
							folders.Add(Folder(FilePath(driveString)));
						}
						
						return true;
					}
				}
				
				return false;
			}
			else
			{
				if (!Exists())
				{
					return false;
				}
				
				WIN32_FIND_DATA findData;
				HANDLE findHandle = INVALID_HANDLE_VALUE;
				
				while (true)
				{
					if (findHandle == INVALID_HANDLE_VALUE)
					{
						WString searchPath = (filePath / L"*").GetFullPath();
						findHandle = FindFirstFile(searchPath.Buffer(), &findData);
						
						if (findHandle == INVALID_HANDLE_VALUE)
						{
							break;
						}
					}
					else
					{
						BOOL result = FindNextFile(findHandle, &findData);
						
						if (result == 0)
						{
							FindClose(findHandle);
							break;
						}
					}
					
					if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						if (wcscmp(findData.cFileName, L".") != 0 && wcscmp(findData.cFileName, L"..") != 0)
						{
							folders.Add(Folder(filePath / findData.cFileName));
						}
					}
				}
				
				return true;
			}
			
#endif
		}
		
		bool Folder::GetFiles(collections::List<File>& files)const
		{
#if defined VCZH_MSVC
		
			if (filePath.IsRoot())
			{
				return true;
			}
			
			if (!Exists())
			{
				return false;
			}
			
			WIN32_FIND_DATA findData;
			HANDLE findHandle = INVALID_HANDLE_VALUE;
			
			while (true)
			{
				if (findHandle == INVALID_HANDLE_VALUE)
				{
					WString searchPath = (filePath / L"*").GetFullPath();
					findHandle = FindFirstFile(searchPath.Buffer(), &findData);
					
					if (findHandle == INVALID_HANDLE_VALUE)
					{
						break;
					}
				}
				else
				{
					BOOL result = FindNextFile(findHandle, &findData);
					
					if (result == 0)
					{
						FindClose(findHandle);
						break;
					}
				}
				
				if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					files.Add(File(filePath / findData.cFileName));
				}
			}
			
			return true;
#endif
		}
		
		bool Folder::Exists()const
		{
			return filePath.IsFolder();
		}
		
		bool Folder::Create(bool recursively)const
		{
			if (recursively)
			{
				FilePath folder = filePath.GetFolder();
				
				if (folder.IsFile())
				{
					return false;
				}
				
				if (folder.IsFolder())
				{
					return Create(false);
				}
				
				return Folder(folder).Create(true) && Create(false);
			}
			else
			{
#if defined VCZH_MSVC
				return CreateDirectory(filePath.GetFullPath().Buffer(), NULL) != 0;
#elif defined VCZH_GCC
				AString path = wtoa(filePath.GetFullPath());
				return mkdir(path.Buffer(), 0777) == 0;
#endif
			}
		}
		
		bool Folder::Delete(bool recursively)const
		{
			if (!Exists())
			{
				return false;
			}
			
			if (recursively)
			{
				List<Folder> folders;
				GetFolders(folders);
				FOREACH(Folder, folder, folders)
				{
					if (!folder.Delete(true))
					{
						return false;
					}
				}
				
				List<File> files;
				GetFiles(files);
				FOREACH(File, file, files)
				{
					if (!file.Delete())
					{
						return false;
					}
				}
				
				return Delete(false);
			}
			
#if defined VCZH_MSVC
			return RemoveDirectory(filePath.GetFullPath().Buffer()) != 0;
#elif defined VCZH_GCC
			AString path = wtoa(filePath.GetFullPath());
			return rmdir(path.Buffer()) == 0;
#endif
		}
		
		bool Folder::Rename(const WString& newName)const
		{
#if defined VCZH_MSVC
			WString oldFileName = filePath.GetFullPath();
			WString newFileName = (filePath.GetFolder() / newName).GetFullPath();
			return MoveFile(oldFileName.Buffer(), newFileName.Buffer()) != 0;
#elif defined VCZH_GCC
			AString oldFileName = wtoa(filePath.GetFullPath());
			AString newFileName = wtoa((filePath.GetFolder() / newName).GetFullPath());
			return rename(oldFileName.Buffer(), newFileName.Buffer()) == 0;
#endif
		}
	}
}

// #include "../Locale.h"
// #include "../Collections/OperationForEach.h"
// #include "../Stream/FileStream.h"
// #include "../Stream/Accessor.h"
// #include "../Exception.h"
// #include <Windows.h>
// #include <Shlwapi.h>
// #pragma comment(lib, "Shlwapi.lib")
// #include "FileInfo.h"

namespace vl
{
	namespace filesystem
	{
		using namespace collections;
		using namespace stream;
		
		FileInfo::FileInfo()
		{
		}
		
		FileInfo::FileInfo(const FilePath& path)
		{
			attrbute.filePath = path;
			getProperty();
		}
		
		FileInfo::FileInfo(const WString& path)
		{
			attrbute.filePath = path;
			getProperty();
		}
		
		FileInfo::~FileInfo()
		{
		}
		
		
		void FileInfo::SetPath(const WString& path)
		{
			attrbute.filePath = path;
			getProperty();
		}
		
		void FileInfo::SetPath(const FilePath& path)
		{
			attrbute.filePath = path;
			getProperty();
		}
		
		bool FileInfo::Exists()const
		{
			return attrbute.attrbutes != 0;
		}
		
		bool FileInfo::IsFolder()const
		{
			return (attrbute.attrbutes & FILE_ATTRIBUTE_DIRECTORY) != 0;
		}
		
		bool FileInfo::IsFile()const
		{
			return Exists() && (attrbute.attrbutes & FILE_ATTRIBUTE_DIRECTORY) == 0;
		}
		
		bool FileInfo::IsReadable() const
		{
			return (attrbute.attrbutes & FILE_SHARE_READ) == 1;
		}
		
		bool FileInfo::IsWritable() const
		{
			return (attrbute.attrbutes & FILE_SHARE_WRITE) == 1;
		}
		
		bool FileInfo::IsHidden() const
		{
			return (attrbute.attrbutes & FILE_ATTRIBUTE_HIDDEN) == 1;
		}
		
		vl::WString FileInfo::FileName()
		{
			return ::PathFindFileName(attrbute.filePath.GetFullPath().Buffer());
		}
		
		vl::WString FileInfo::Extemsion()
		{
			return ::PathFindExtension(attrbute.filePath.GetFullPath().Buffer());
		}
		
		vl::DateTime FileInfo::Created()
		{
			return attrbute.creation;
		}
		
		vl::DateTime FileInfo::LastModified()
		{
			return attrbute.lastWrite;
		}
		
		vl::DateTime FileInfo::LastRead()
		{
			return attrbute.lastAccess;
		}
		
		vl::vuint64_t FileInfo::Size()
		{
			return attrbute.size;
		}
		
		bool FileInfo::getProperty()
		{
			WIN32_FILE_ATTRIBUTE_DATA data;
			memset(&data, 0, sizeof(WIN32_FILE_ATTRIBUTE_DATA));
			BOOL result = GetFileAttributesEx(attrbute.filePath.GetFullPath().Buffer(), GetFileExInfoStandard, &data);
			{
				attrbute.attrbutes = data.dwFileAttributes;
				ULARGE_INTEGER largeInteger;
				largeInteger.HighPart = data.ftCreationTime.dwHighDateTime;
				largeInteger.LowPart = data.ftCreationTime.dwLowDateTime;
				attrbute.creation = DateTime::FromFileTime(largeInteger.QuadPart);
				
				largeInteger.HighPart = data.ftLastAccessTime.dwHighDateTime;
				largeInteger.LowPart = data.ftLastAccessTime.dwLowDateTime;
				attrbute.lastAccess = DateTime::FromFileTime(largeInteger.QuadPart);
				
				largeInteger.HighPart = data.ftLastWriteTime.dwHighDateTime;
				largeInteger.LowPart = data.ftLastWriteTime.dwLowDateTime;
				attrbute.lastWrite = DateTime::FromFileTime(largeInteger.QuadPart);
				
				largeInteger.HighPart = data.nFileSizeHigh;
				largeInteger.LowPart = data.nFileSizeLow;
				attrbute.size = largeInteger.QuadPart;
			}
			return result == TRUE;
		}
		
	}
}


// #include "RegexData.h"

namespace vl
{
	namespace regex_internal
	{
	
		/***********************************************************************
		CharRange
		***********************************************************************/
		
		CharRange::CharRange()
			: begin(L'\0')
			, end(L'\0')
		{
		}
		
		CharRange::CharRange(wchar_t _begin, wchar_t _end)
			: begin(_begin)
			, end(_end)
		{
		}
		
		bool CharRange::operator<(CharRange item)const
		{
			return end < item.begin;
		}
		
		bool CharRange::operator<=(CharRange item)const
		{
			return *this < item || *this == item;
		}
		
		bool CharRange::operator>(CharRange item)const
		{
			return item.end < begin;
		}
		
		bool CharRange::operator>=(CharRange item)const
		{
			return *this > item || *this == item;
		}
		
		bool CharRange::operator==(CharRange item)const
		{
			return begin == item.begin && end == item.end;
		}
		
		bool CharRange::operator!=(CharRange item)const
		{
			return begin != item.begin || item.end != end;
		}
		
		bool CharRange::operator<(wchar_t item)const
		{
			return end < item;
		}
		
		bool CharRange::operator<=(wchar_t item)const
		{
			return begin <= item;
		}
		
		bool CharRange::operator>(wchar_t item)const
		{
			return item < begin;
		}
		
		bool CharRange::operator>=(wchar_t item)const
		{
			return item <= end;
		}
		
		bool CharRange::operator==(wchar_t item)const
		{
			return begin <= item && item <= end;
		}
		
		bool CharRange::operator!=(wchar_t item)const
		{
			return item < begin || end < item;
		}
		
	}
}

// #include "RegexAutomaton.h"
// #include "../Collections/OperationCopyFrom.h"

namespace vl
{
	namespace regex_internal
	{
		using namespace collections;
		
		/***********************************************************************
		Automaton
		***********************************************************************/
		
		Automaton::Automaton()
		{
			startState = 0;
		}
		
		State* Automaton::NewState()
		{
			State* state = new State;
			state->finalState = false;
			state->userData = 0;
			states.Add(state);
			return state;
		}
		
		Transition* Automaton::NewTransition(State* start, State* end)
		{
			Transition* transition = new Transition;
			transition->source = start;
			transition->target = end;
			start->transitions.Add(transition);
			end->inputs.Add(transition);
			transitions.Add(transition);
			return transition;
		}
		
		Transition* Automaton::NewChars(State* start, State* end, CharRange range)
		{
			Transition* transition = NewTransition(start, end);
			transition->type = Transition::Chars;
			transition->range = range;
			return transition;
		}
		
		Transition* Automaton::NewEpsilon(State* start, State* end)
		{
			Transition* transition = NewTransition(start, end);
			transition->type = Transition::Epsilon;
			return transition;
		}
		
		Transition* Automaton::NewBeginString(State* start, State* end)
		{
			Transition* transition = NewTransition(start, end);
			transition->type = Transition::BeginString;
			return transition;
		}
		
		Transition* Automaton::NewEndString(State* start, State* end)
		{
			Transition* transition = NewTransition(start, end);
			transition->type = Transition::EndString;
			return transition;
		}
		
		Transition* Automaton::NewNop(State* start, State* end)
		{
			Transition* transition = NewTransition(start, end);
			transition->type = Transition::Nop;
			return transition;
		}
		
		Transition* Automaton::NewCapture(State* start, State* end, vint capture)
		{
			Transition* transition = NewTransition(start, end);
			transition->type = Transition::Capture;
			transition->capture = capture;
			return transition;
		}
		
		Transition* Automaton::NewMatch(State* start, State* end, vint capture, vint index)
		{
			Transition* transition = NewTransition(start, end);
			transition->type = Transition::Match;
			transition->capture = capture;
			transition->index = index;
			return transition;
		}
		
		Transition* Automaton::NewPositive(State* start, State* end)
		{
			Transition* transition = NewTransition(start, end);
			transition->type = Transition::Positive;
			return transition;
		}
		
		Transition* Automaton::NewNegative(State* start, State* end)
		{
			Transition* transition = NewTransition(start, end);
			transition->type = Transition::Negative;
			return transition;
		}
		
		Transition* Automaton::NewNegativeFail(State* start, State* end)
		{
			Transition* transition = NewTransition(start, end);
			transition->type = Transition::NegativeFail;
			return transition;
		}
		
		Transition* Automaton::NewEnd(State* start, State* end)
		{
			Transition* transition = NewTransition(start, end);
			transition->type = Transition::End;
			return transition;
		}
		
		/***********************************************************************
		辅助函数
		***********************************************************************/
		
		bool PureEpsilonChecker(Transition* transition)
		{
			switch (transition->type)
			{
				case Transition::Epsilon:
				case Transition::Nop:
				case Transition::Capture:
				case Transition::End:
					return true;
					
				default:
					return false;
			}
		}
		
		bool RichEpsilonChecker(Transition* transition)
		{
			switch (transition->type)
			{
				case Transition::Epsilon:
					return true;
					
				default:
					return false;
			}
		}
		
		bool AreEqual(Transition* transA, Transition* transB)
		{
			if (transA->type != transB->type)
			{
				return false;
			}
			
			switch (transA->type)
			{
				case Transition::Chars:
					return transA->range == transB->range;
					
				case Transition::Capture:
					return transA->capture == transB->capture;
					
				case Transition::Match:
					return transA->capture == transB->capture && transA->index == transB->index;
					
				default:
					return true;
			}
		}
		
		//递归保证转换先后顺序
		void CollectEpsilon(State* targetState, State* sourceState, bool(*epsilonChecker)(Transition*), List<State*>& epsilonStates, List<Transition*>& transitions)
		{
			if (!epsilonStates.Contains(sourceState))
			{
				epsilonStates.Add(sourceState);
				
				for (vint i = 0; i < sourceState->transitions.Count(); i++)
				{
					Transition* transition = sourceState->transitions[i];
					
					if (epsilonChecker(transition))
					{
						if (!epsilonStates.Contains(transition->target))
						{
							if (transition->target->finalState)
							{
								targetState->finalState = true;
							}
							
							CollectEpsilon(targetState, transition->target, epsilonChecker, epsilonStates, transitions);
						}
					}
					else
					{
						transitions.Add(transition);
					}
				}
			}
		}
		
		Automaton::Ref EpsilonNfaToNfa(Automaton::Ref source, bool(*epsilonChecker)(Transition*), Dictionary<State*, State*>& nfaStateMap)
		{
			Automaton::Ref target = new Automaton;
			Dictionary<State*, State*> stateMap;	//source->target
			List<State*> epsilonStates;				//每次迭代当前状态的epsilon闭包
			List<Transition*> transitions;			//每次迭代当前状态的epsilon闭包的转换集合
			
			stateMap.Add(source->startState, target->NewState());
			nfaStateMap.Add(stateMap[source->startState], source->startState);
			target->startState = target->states[0].Obj();
			CopyFrom(target->captureNames, source->captureNames);
			
			for (vint i = 0; i < target->states.Count(); i++)
			{
				//清空epsilonStates并包含自己
				State* targetState = target->states[i].Obj();
				State* sourceState = nfaStateMap[targetState];
				
				if (sourceState->finalState)
				{
					targetState->finalState = true;
				}
				
				epsilonStates.Clear();
				transitions.Clear();
				
				//对所有产生的epsilonStates进行遍历，计算出该状态的一次epsilon直接目标加进去，并继续迭代
				CollectEpsilon(targetState, sourceState, epsilonChecker, epsilonStates, transitions);
				
				//遍历所有epsilon闭包转换
				for (vint j = 0; j < transitions.Count(); j++)
				{
					Transition* transition = transitions[j];
					
					//寻找到一个非epsilon闭包的时候更新映射
					if (!stateMap.Keys().Contains(transition->target))
					{
						stateMap.Add(transition->target, target->NewState());
						nfaStateMap.Add(stateMap[transition->target], transition->target);
					}
					
					//将该转换复制到新状态机里
					Transition* newTransition = target->NewTransition(targetState, stateMap[transition->target]);
					newTransition->capture = transition->capture;
					newTransition->index = transition->index;
					newTransition->range = transition->range;
					newTransition->type = transition->type;
				}
			}
			
			return target;
		}
		
		Automaton::Ref NfaToDfa(Automaton::Ref source, Group<State*, State*>& dfaStateMap)
		{
			Automaton::Ref target = new Automaton;
			Group<Transition*, Transition*> nfaTransitions;
			List<Transition*> transitionClasses;//保证转换先后顺序不被nfaTransitions.Keys破坏
			
			CopyFrom(target->captureNames, source->captureNames);
			State* startState = target->NewState();
			target->startState = startState;
			dfaStateMap.Add(startState, source->startState);
			
			SortedList<State*> transitionTargets;
			SortedList<State*> relativeStates;
			transitionTargets.SetLessMemoryMode(false);
			relativeStates.SetLessMemoryMode(false);
			
			for (vint i = 0; i < target->states.Count(); i++)
			{
				State* currentState = target->states[i].Obj();
				nfaTransitions.Clear();
				transitionClasses.Clear();
				
				//对该DFA状态的所有等价NFA状态进行遍历
				const List<State*>& nfaStates = dfaStateMap[currentState];
				
				for (vint j = 0; j < nfaStates.Count(); j++)
				{
					State* nfaState = nfaStates.Get(j);
					
					//对每一个NFA状态的所有转换进行遍历
					for (vint k = 0; k < nfaState->transitions.Count(); k++)
					{
						Transition* nfaTransition = nfaState->transitions[k];
						//检查该NFA转换类型是否已经具有已经被记录
						Transition* transitionClass = 0;
						
						for (vint l = 0; l < nfaTransitions.Keys().Count(); l++)
						{
							Transition* key = nfaTransitions.Keys()[l];
							
							if (AreEqual(key, nfaTransition))
							{
								transitionClass = key;
								break;
							}
						}
						
						//不存在则创建一个转换类型
						if (transitionClass == 0)
						{
							transitionClass = nfaTransition;
							transitionClasses.Add(transitionClass);
						}
						
						//注册转换
						nfaTransitions.Add(transitionClass, nfaTransition);
					}
				}
				
				//遍历所有种类的NFA转换
				for (vint j = 0; j < transitionClasses.Count(); j++)
				{
					const List<Transition*>& transitionSet = nfaTransitions[transitionClasses[j]];
					//对所有转换的NFA目标状态集合进行排序
					transitionTargets.Clear();
					
					for (vint l = 0; l < transitionSet.Count(); l++)
					{
						State* nfaState = transitionSet.Get(l)->target;
						
						if (!transitionTargets.Contains(nfaState))
						{
							transitionTargets.Add(nfaState);
						}
					}
					
					//判断转换类的所有转换的NFA目标状态组成的集合是否已经有一个对应的DFA状态
					State* dfaState = 0;
					
					for (vint k = 0; k < dfaStateMap.Count(); k++)
					{
						//将DFA的等价NFA状态集合进行排序
						CopyFrom(relativeStates, dfaStateMap.GetByIndex(k));
						
						//比较两者是否相等
						if (relativeStates.Count() == transitionTargets.Count())
						{
							bool equal = true;
							
							for (vint l = 0; l < relativeStates.Count(); l++)
							{
								if (relativeStates[l] != transitionTargets[l])
								{
									equal = false;
									break;
								}
							}
							
							if (equal)
							{
								dfaState = dfaStateMap.Keys()[k];
								break;
							}
						}
					}
					
					//不存在等价DFA状态则创建一个
					if (!dfaState)
					{
						dfaState = target->NewState();
						
						for (vint k = 0; k < transitionTargets.Count(); k++)
						{
							dfaStateMap.Add(dfaState, transitionTargets[k]);
							
							if (transitionTargets[k]->finalState)
							{
								dfaState->finalState = true;
							}
						}
					}
					
					//将该转换复制到新状态机里
					Transition* transitionClass = transitionClasses[j];
					Transition* newTransition = target->NewTransition(currentState, dfaState);
					newTransition->capture = transitionClass->capture;
					newTransition->index = transitionClass->index;
					newTransition->range = transitionClass->range;
					newTransition->type = transitionClass->type;
				}
			}
			
			return target;
		}
	}
}


// #include "RegexRich.h"

namespace vl
{
	namespace regex_internal
	{
		using namespace collections;
		
		/***********************************************************************
		回溯辅助数据结构
		***********************************************************************/
		
		class SaverBase
		{
		 public:
			bool					available;
			vint					previous;
		};
		
		class StateSaver
		{
		 public:
			enum StateStoreType
			{
				Positive,
				Negative,
				Other
			};
			
			const wchar_t*			reading;					//当前字符串位置
			State*					currentState;				//当前状态
			vint					minTransition;				//最小可用转换
			vint					captureCount;				//有效capture数量
			vint					stateSaverCount;			//有效回溯状态数量
			vint					extensionSaverAvailable;	//有效未封闭扩展功能数量
			vint					extensionSaverCount;		//所有未封闭扩展功能数量
			StateStoreType			storeType;					//保存状态的原因
			
			bool operator==(const StateSaver& saver)const
			{
				return
				  reading == saver.reading &&
				  currentState == saver.currentState &&
				  minTransition == saver.minTransition &&
				  captureCount == saver.captureCount;
			}
		};
		
		class ExtensionSaver : public SaverBase
		{
		 public:
			vint					captureListIndex;
			Transition*				transition;
			const wchar_t*			reading;
			
			bool operator==(const ExtensionSaver& saver)const
			{
				return
				  captureListIndex == saver.captureListIndex &&
				  transition == saver.transition &&
				  reading == saver.reading;
			}
		};
		
		template<typename T, typename K>
		void Push(List<T, K>& elements, vint& available, vint& count, const T& element)
		{
			if (elements.Count() == count)
			{
				elements.Add(element);
			}
			else
			{
				elements[count] = element;
			}
			
			T& current = elements[count];
			current.previous = available;
			available = count++;
		}
		
		template<typename T, typename K>
		T Pop(List<T, K>& elements, vint& available, vint& count)
		{
			T& current = elements[available];
			available = current.previous;
			return current;
		}
		
		template<typename T, typename K>
		void PushNonSaver(List<T, K>& elements, vint& count, const T& element)
		{
			if (elements.Count() == count)
			{
				elements.Add(element);
			}
			else
			{
				elements[count] = element;
			}
			
			count++;
		}
		
		template<typename T, typename K>
		T PopNonSaver(List<T, K>& elements, vint& count)
		{
			return elements[--count];
		}
	}
	
	template<>
	struct POD<regex_internal::StateSaver>
	{
		static const bool Result = true;
	};
	
	template<>
	struct POD<regex_internal::ExtensionSaver>
	{
		static const bool Result = true;
	};
	
	namespace regex_internal
	{
		/***********************************************************************
		CaptureRecord
		***********************************************************************/
		
		bool CaptureRecord::operator==(const CaptureRecord& record)const
		{
			return capture == record.capture && start == record.start && length == record.length;
		}
		
		/***********************************************************************
		RichInterpretor
		***********************************************************************/
		
		RichInterpretor::RichInterpretor(Automaton::Ref _dfa)
			: dfa(_dfa)
		{
			datas = new UserData[dfa->states.Count()];
			
			for (vint i = 0; i < dfa->states.Count(); i++)
			{
				State* state = dfa->states[i].Obj();
				vint charEdges = 0;
				vint nonCharEdges = 0;
				bool mustSave = false;
				
				for (vint j = 0; j < state->transitions.Count(); j++)
				{
					if (state->transitions[j]->type == Transition::Chars)
					{
						charEdges++;
					}
					else
					{
						if (state->transitions[j]->type == Transition::Negative ||
						  state->transitions[j]->type == Transition::Positive)
						{
							mustSave = true;
						}
						
						nonCharEdges++;
					}
				}
				
				datas[i].NeedKeepState = mustSave || nonCharEdges > 1 || (nonCharEdges != 0 && charEdges != 0);
				state->userData = &datas[i];
			}
		}
		
		RichInterpretor::~RichInterpretor()
		{
			delete[] datas;
		}
		
		bool RichInterpretor::MatchHead(const wchar_t* input, const wchar_t* start, RichResult& result)
		{
			List<StateSaver> stateSavers;
			List<ExtensionSaver> extensionSavers;
			
			StateSaver currentState;
			currentState.captureCount = 0;
			currentState.currentState = dfa->startState;
			currentState.extensionSaverAvailable = -1;
			currentState.extensionSaverCount = 0;
			currentState.minTransition = 0;
			currentState.reading = input;
			currentState.stateSaverCount = 0;
			currentState.storeType = StateSaver::Other;
			
			while (!currentState.currentState->finalState)
			{
				bool found = false;
				StateSaver oldState = currentState;
				
				//开始遍历转换
				for (vint i = currentState.minTransition; i < currentState.currentState->transitions.Count(); i++)
				{
					Transition* transition = currentState.currentState->transitions[i];
					
					switch (transition->type)
					{
						case Transition::Chars:
							{
								CharRange range = transition->range;
								found =
								  range.begin <= *currentState.reading &&
								  range.end >= *currentState.reading;
								  
								if (found)
								{
									currentState.reading++;
								}
							}
							break;
							
						case Transition::BeginString:
							{
								found = currentState.reading == start;
							}
							break;
							
						case Transition::EndString:
							{
								found = *currentState.reading == L'\0';
							}
							break;
							
						case Transition::Nop:
							{
								found = true;
							}
							break;
							
						case Transition::Capture:
							{
								ExtensionSaver saver;
								saver.captureListIndex = currentState.captureCount;
								saver.reading = currentState.reading;
								saver.transition = transition;
								Push(extensionSavers, currentState.extensionSaverAvailable, currentState.extensionSaverCount, saver);
								
								CaptureRecord capture;
								capture.capture = transition->capture;
								capture.start = currentState.reading - start;
								capture.length = -1;
								PushNonSaver(result.captures, currentState.captureCount, capture);
								
								found = true;
							}
							break;
							
						case Transition::Match:
							{
								vint index = 0;
								
								for (vint j = 0; j < currentState.captureCount; j++)
								{
									CaptureRecord& capture = result.captures[j];
									
									if (capture.capture == transition->capture)
									{
										if (capture.length != -1 && (transition->index == -1 || transition->index == index))
										{
											if (wcsncmp(start + capture.start, currentState.reading, capture.length) == 0)
											{
												currentState.reading += capture.length;
												found = true;
												break;
											}
										}
										
										if (transition->index != -1 && index == transition->index)
										{
											break;
										}
										else
										{
											index++;
										}
									}
								}
							}
							break;
							
						case Transition::Positive:
							{
								ExtensionSaver saver;
								saver.captureListIndex = -1;
								saver.reading = currentState.reading;
								saver.transition = transition;
								Push(extensionSavers, currentState.extensionSaverAvailable, currentState.extensionSaverCount, saver);
								//Positive的oldState一定会被push
								oldState.storeType = StateSaver::Positive;
								found = true;
							}
							break;
							
						case Transition::Negative:
							{
								ExtensionSaver saver;
								saver.captureListIndex = -1;
								saver.reading = currentState.reading;
								saver.transition = transition;
								Push(extensionSavers, currentState.extensionSaverAvailable, currentState.extensionSaverCount, saver);
								//Negative的oldState一定会被push
								oldState.storeType = StateSaver::Negative;
								found = true;
							}
							break;
							
						case Transition::NegativeFail:
							{
								//只有在回溯的时候NegativeFail才会被考虑
							}
							break;
							
						case Transition::End:
							{
								ExtensionSaver extensionSaver = Pop(extensionSavers, currentState.extensionSaverAvailable, currentState.extensionSaverCount);
								
								switch (extensionSaver.transition->type)
								{
									case Transition::Capture:
										{
											CaptureRecord& capture = result.captures[extensionSaver.captureListIndex];
											capture.length = (currentState.reading - start) - capture.start;
											found = true;
										}
										break;
										
									case Transition::Positive:
										for (vint j = currentState.stateSaverCount - 1; j >= 0; j--)
										{
											StateSaver& stateSaver = stateSavers[j];
											
											if (stateSaver.storeType == StateSaver::Positive)
											{
												oldState.reading = stateSaver.reading;
												oldState.stateSaverCount = j;
												currentState.reading = stateSaver.reading;
												currentState.stateSaverCount = j;
												break;
											}
										}
										
										found = true;
										break;
										
									case Transition::Negative:
										for (vint j = currentState.stateSaverCount - 1; j >= 0; j--)
										{
											StateSaver& stateSaver = stateSavers[j];
											
											if (stateSaver.storeType == StateSaver::Negative)
											{
												oldState = stateSaver;
												oldState.storeType = StateSaver::Other;
												currentState = stateSaver;
												currentState.storeType = StateSaver::Other;
												i = currentState.minTransition - 1;
												break;
											}
										}
										
										break;
										
									default:;
								}
							}
							break;
							
						default:;
					}
					
					//寻找成功，在必要的时候保存当前的回溯状态
					if (found)
					{
						UserData* data = (UserData*)currentState.currentState->userData;
						
						if (data->NeedKeepState)
						{
							oldState.minTransition = i + 1;
							PushNonSaver(stateSavers, currentState.stateSaverCount, oldState);
						}
						
						currentState.currentState = transition->target;
						currentState.minTransition = 0;
						break;
					}
				}
				
				if (!found)
				{
					//存在回溯记录则回溯
					if (currentState.stateSaverCount)
					{
						//恢复Negative失败状态的时候要移动到NegativeFail后面
						currentState = PopNonSaver(stateSavers, currentState.stateSaverCount);
						
						//minTransition总是被+1后保存，因此直接-1总是有效值
						if (currentState.currentState->transitions[currentState.minTransition - 1]->type == Transition::Negative)
						{
							//寻找NegativeFail
							for (vint i = 0; i < currentState.currentState->transitions.Count(); i++)
							{
								Transition* transition = currentState.currentState->transitions[i];
								
								if (transition->type == Transition::NegativeFail)
								{
									//将当前状态移动到NegativeFail后面
									currentState.currentState = transition->target;
									currentState.minTransition = 0;
									currentState.storeType = StateSaver::Other;
									break;
								}
							}
						}
					}
					else
					{
						break;
					}
				}
			}
			
			//判断是否成功并且处理返回结果
			if (currentState.currentState->finalState)
			{
				result.start = input - start;
				result.length = (currentState.reading - start) - result.start;
				
				for (vint i = result.captures.Count() - 1; i >= currentState.captureCount; i--)
				{
					result.captures.RemoveAt(i);
				}
				
				return true;
			}
			else
			{
				result.captures.Clear();
				return false;
			}
		}
		
		bool RichInterpretor::Match(const wchar_t* input, const wchar_t* start, RichResult& result)
		{
			const wchar_t* read = input;
			
			while (*read)
			{
				if (MatchHead(read, start, result))
				{
					return true;
				}
				
				read++;
			}
			
			return false;
		}
		
		const List<WString>& RichInterpretor::CaptureNames()
		{
			return dfa->captureNames;
		}
	}
}

// #include "RegexExpression.h"
// #include "../Collections/OperationCopyFrom.h"

namespace vl
{
	namespace regex_internal
	{
	
		/***********************************************************************
		IsEqualAlgorithm
		***********************************************************************/
		
		class IsEqualAlgorithm : public RegexExpressionAlgorithm<bool, Expression*>
		{
		 public:
			bool Apply(CharSetExpression* expression, Expression* target)
			{
				CharSetExpression* expected = dynamic_cast<CharSetExpression*>(target);
				
				if (expected)
				{
					if (expression->reverse != expected->reverse)
					{
						return false;
					}
					
					if (expression->ranges.Count() != expected->ranges.Count())
					{
						return false;
					}
					
					for (vint i = 0; i < expression->ranges.Count(); i++)
					{
						if (expression->ranges[i] != expected->ranges[i])
						{
							return false;
						}
					}
					
					return true;
				}
				
				return false;
			}
			
			bool Apply(LoopExpression* expression, Expression* target)
			{
				LoopExpression* expected = dynamic_cast<LoopExpression*>(target);
				
				if (expected)
				{
					if (expression->min != expected->min)
					{
						return false;
					}
					
					if (expression->max != expected->max)
					{
						return false;
					}
					
					if (expression->preferLong != expected->preferLong)
					{
						return false;
					}
					
					if (!Invoke(expression->expression, expected->expression.Obj()))
					{
						return false;
					}
					
					return true;
				}
				
				return false;
			}
			
			bool Apply(SequenceExpression* expression, Expression* target)
			{
				SequenceExpression* expected = dynamic_cast<SequenceExpression*>(target);
				
				if (expected)
				{
					if (!Invoke(expression->left, expected->left.Obj()))
					{
						return false;
					}
					
					if (!Invoke(expression->right, expected->right.Obj()))
					{
						return false;
					}
					
					return true;
				}
				
				return false;
			}
			
			bool Apply(AlternateExpression* expression, Expression* target)
			{
				AlternateExpression* expected = dynamic_cast<AlternateExpression*>(target);
				
				if (expected)
				{
					if (!Invoke(expression->left, expected->left.Obj()))
					{
						return false;
					}
					
					if (!Invoke(expression->right, expected->right.Obj()))
					{
						return false;
					}
					
					return true;
				}
				
				return false;
			}
			
			bool Apply(BeginExpression* expression, Expression* target)
			{
				BeginExpression* expected = dynamic_cast<BeginExpression*>(target);
				
				if (expected)
				{
					return true;
				}
				
				return false;
			}
			
			bool Apply(EndExpression* expression, Expression* target)
			{
				EndExpression* expected = dynamic_cast<EndExpression*>(target);
				
				if (expected)
				{
					return true;
				}
				
				return false;
			}
			
			bool Apply(CaptureExpression* expression, Expression* target)
			{
				CaptureExpression* expected = dynamic_cast<CaptureExpression*>(target);
				
				if (expected)
				{
					if (expression->name != expected->name)
					{
						return false;
					}
					
					if (!Invoke(expression->expression, expected->expression.Obj()))
					{
						return false;
					}
					
					return true;
				}
				
				return false;
			}
			
			bool Apply(MatchExpression* expression, Expression* target)
			{
				MatchExpression* expected = dynamic_cast<MatchExpression*>(target);
				
				if (expected)
				{
					if (expression->name != expected->name)
					{
						return false;
					}
					
					if (expression->index != expected->index)
					{
						return false;
					}
					
					return true;
				}
				
				return false;
			}
			
			bool Apply(PositiveExpression* expression, Expression* target)
			{
				PositiveExpression* expected = dynamic_cast<PositiveExpression*>(target);
				
				if (expected)
				{
					if (!Invoke(expression->expression, expected->expression.Obj()))
					{
						return false;
					}
					
					return true;
				}
				
				return false;
			}
			
			bool Apply(NegativeExpression* expression, Expression* target)
			{
				NegativeExpression* expected = dynamic_cast<NegativeExpression*>(target);
				
				if (expected)
				{
					if (!Invoke(expression->expression, expected->expression.Obj()))
					{
						return false;
					}
					
					return true;
				}
				
				return false;
			}
			
			bool Apply(UsingExpression* expression, Expression* target)
			{
				UsingExpression* expected = dynamic_cast<UsingExpression*>(target);
				
				if (expected)
				{
					if (expression->name != expected->name)
					{
						return false;
					}
					
					return true;
				}
				
				return false;
			}
		};
		
		/***********************************************************************
		HasNoExtensionAlgorithm
		***********************************************************************/
		
		class HasNoExtensionAlgorithm : public RegexExpressionAlgorithm<bool, void*>
		{
		 public:
			bool Apply(CharSetExpression* expression, void* target)
			{
				return true;
			}
			
			bool Apply(LoopExpression* expression, void* target)
			{
				return expression->preferLong && Invoke(expression->expression, 0);
			}
			
			bool Apply(SequenceExpression* expression, void* target)
			{
				return Invoke(expression->left, 0) && Invoke(expression->right, 0);
			}
			
			bool Apply(AlternateExpression* expression, void* target)
			{
				return Invoke(expression->left, 0) && Invoke(expression->right, 0);
			}
			
			bool Apply(BeginExpression* expression, void* target)
			{
				return false;
			}
			
			bool Apply(EndExpression* expression, void* target)
			{
				return false;
			}
			
			bool Apply(CaptureExpression* expression, void* target)
			{
				return false;
			}
			
			bool Apply(MatchExpression* expression, void* target)
			{
				return false;
			}
			
			bool Apply(PositiveExpression* expression, void* target)
			{
				return false;
			}
			
			bool Apply(NegativeExpression* expression, void* target)
			{
				return false;
			}
			
			bool Apply(UsingExpression* expression, void* target)
			{
				return false;
			}
		};
		
		/***********************************************************************
		CanTreatAsPureAlgorithm
		***********************************************************************/
		
		class CanTreatAsPureAlgorithm : public RegexExpressionAlgorithm<bool, void*>
		{
		 public:
			bool Apply(CharSetExpression* expression, void* target)
			{
				return true;
			}
			
			bool Apply(LoopExpression* expression, void* target)
			{
				return expression->preferLong && Invoke(expression->expression, 0);
			}
			
			bool Apply(SequenceExpression* expression, void* target)
			{
				return Invoke(expression->left, 0) && Invoke(expression->right, 0);
			}
			
			bool Apply(AlternateExpression* expression, void* target)
			{
				return Invoke(expression->left, 0) && Invoke(expression->right, 0);
			}
			
			bool Apply(BeginExpression* expression, void* target)
			{
				return false;
			}
			
			bool Apply(EndExpression* expression, void* target)
			{
				return false;
			}
			
			bool Apply(CaptureExpression* expression, void* target)
			{
				return Invoke(expression->expression, 0);
			}
			
			bool Apply(MatchExpression* expression, void* target)
			{
				return false;
			}
			
			bool Apply(PositiveExpression* expression, void* target)
			{
				return false;
			}
			
			bool Apply(NegativeExpression* expression, void* target)
			{
				return false;
			}
			
			bool Apply(UsingExpression* expression, void* target)
			{
				return false;
			}
		};
		
		/***********************************************************************
		CharSetNormalizationAlgorithm
		***********************************************************************/
		
		class NormalizedCharSet
		{
		 public:
			CharRange::List			ranges;
		};
		
		class CharSetAlgorithm : public RegexExpressionAlgorithm<void, NormalizedCharSet*>
		{
		 public:
			virtual void Process(CharSetExpression* expression, NormalizedCharSet* target, CharRange range) = 0;
			
			void Loop(CharSetExpression* expression, CharRange::List& ranges, NormalizedCharSet* target)
			{
				if (expression->reverse)
				{
					wchar_t begin = 1;
					
					for (vint i = 0; i < ranges.Count(); i++)
					{
						CharRange range = ranges[i];
						
						if (range.begin > begin)
						{
							Process(expression, target, CharRange(begin, range.begin - 1));
						}
						
						begin = range.end + 1;
					}
					
					if (begin <= 65535)
					{
						Process(expression, target, CharRange(begin, 65535));
					}
				}
				else
				{
					for (vint i = 0; i < ranges.Count(); i++)
					{
						Process(expression, target, ranges[i]);
					}
				}
			}
			
			void Apply(LoopExpression* expression, NormalizedCharSet* target)
			{
				Invoke(expression->expression, target);
			}
			
			void Apply(SequenceExpression* expression, NormalizedCharSet* target)
			{
				Invoke(expression->left, target);
				Invoke(expression->right, target);
			}
			
			void Apply(AlternateExpression* expression, NormalizedCharSet* target)
			{
				Invoke(expression->left, target);
				Invoke(expression->right, target);
			}
			
			void Apply(BeginExpression* expression, NormalizedCharSet* target)
			{
			}
			
			void Apply(EndExpression* expression, NormalizedCharSet* target)
			{
			}
			
			void Apply(CaptureExpression* expression, NormalizedCharSet* target)
			{
				Invoke(expression->expression, target);
			}
			
			void Apply(MatchExpression* expression, NormalizedCharSet* target)
			{
			}
			
			void Apply(PositiveExpression* expression, NormalizedCharSet* target)
			{
				Invoke(expression->expression, target);
			}
			
			void Apply(NegativeExpression* expression, NormalizedCharSet* target)
			{
				Invoke(expression->expression, target);
			}
			
			void Apply(UsingExpression* expression, NormalizedCharSet* target)
			{
			}
		};
		
		class BuildNormalizedCharSetAlgorithm : public CharSetAlgorithm
		{
		 public:
			void Process(CharSetExpression* expression, NormalizedCharSet* target, CharRange range)
			{
				vint index = 0;
				
				while (index < target->ranges.Count())
				{
					CharRange current = target->ranges[index];
					
					if (current < range || current > range)
					{
						index++;
					}
					else
						if (current.begin < range.begin)
						{
							// range   :    [    ?
							// current : [       ]
							target->ranges.RemoveAt(index);
							target->ranges.Add(CharRange(current.begin, range.begin - 1));
							target->ranges.Add(CharRange(range.begin, current.end));
							index++;
						}
						else
							if (current.begin > range.begin)
							{
								// range  :  [       ]
								// current  :   [    ?
								target->ranges.Add(CharRange(range.begin, current.begin - 1));
								range.begin = current.begin;
							}
							else
								if (current.end < range.end)
								{
									// range   : [       ]
									// current : [    ]
									range.begin = current.end + 1;
									index++;
								}
								else
									if (current.end > range.end)
									{
										// range   : [    ]
										// current : [       ]
										target->ranges.RemoveAt(index);
										target->ranges.Add(range);
										target->ranges.Add(CharRange(range.end + 1, current.end));
										return;
									}
									else
									{
										// range   : [       ]
										// current : [       ]
										return;
									}
				}
				
				target->ranges.Add(range);
			}
			
			void Apply(CharSetExpression* expression, NormalizedCharSet* target)
			{
				Loop(expression, expression->ranges, target);
			}
		};
		
		class SetNormalizedCharSetAlgorithm : public CharSetAlgorithm
		{
		 public:
			void Process(CharSetExpression* expression, NormalizedCharSet* target, CharRange range)
			{
				for (vint j = 0; j < target->ranges.Count(); j++)
				{
					CharRange targetRange = target->ranges[j];
					
					if (range.begin <= targetRange.begin && targetRange.end <= range.end)
					{
						expression->ranges.Add(targetRange);
					}
				}
			}
			
			void Apply(CharSetExpression* expression, NormalizedCharSet* target)
			{
				CharRange::List source;
				CopyFrom(source, expression->ranges);
				expression->ranges.Clear();
				Loop(expression, source, target);
				expression->reverse = false;
			}
		};
		
		/***********************************************************************
		MergeAlgorithm
		***********************************************************************/
		
		class MergeParameter
		{
		 public:
			Expression::Map			definitions;
			RegexExpression*		regex;
		};
		
		class MergeAlgorithm : public RegexExpressionAlgorithm<Expression::Ref, MergeParameter*>
		{
		 public:
			Expression::Ref Apply(CharSetExpression* expression, MergeParameter* target)
			{
				Ptr<CharSetExpression> result = new CharSetExpression;
				CopyFrom(result->ranges, expression->ranges);
				result->reverse = expression->reverse;
				return result;
			}
			
			Expression::Ref Apply(LoopExpression* expression, MergeParameter* target)
			{
				Ptr<LoopExpression> result = new LoopExpression;
				result->max = expression->max;
				result->min = expression->min;
				result->preferLong = expression->preferLong;
				result->expression = Invoke(expression->expression, target);
				return result;
			}
			
			Expression::Ref Apply(SequenceExpression* expression, MergeParameter* target)
			{
				Ptr<SequenceExpression> result = new SequenceExpression;
				result->left = Invoke(expression->left, target);
				result->right = Invoke(expression->right, target);
				return result;
			}
			
			Expression::Ref Apply(AlternateExpression* expression, MergeParameter* target)
			{
				Ptr<AlternateExpression> result = new AlternateExpression;
				result->left = Invoke(expression->left, target);
				result->right = Invoke(expression->right, target);
				return result;
			}
			
			Expression::Ref Apply(BeginExpression* expression, MergeParameter* target)
			{
				return new BeginExpression;
			}
			
			Expression::Ref Apply(EndExpression* expression, MergeParameter* target)
			{
				return new EndExpression;
			}
			
			Expression::Ref Apply(CaptureExpression* expression, MergeParameter* target)
			{
				Ptr<CaptureExpression> result = new CaptureExpression;
				result->expression = Invoke(expression->expression, target);
				result->name = expression->name;
				return result;
			}
			
			Expression::Ref Apply(MatchExpression* expression, MergeParameter* target)
			{
				Ptr<MatchExpression> result = new MatchExpression;
				result->name = expression->name;
				result->index = expression->index;
				return result;
			}
			
			Expression::Ref Apply(PositiveExpression* expression, MergeParameter* target)
			{
				Ptr<PositiveExpression> result = new PositiveExpression;
				result->expression = Invoke(expression->expression, target);
				return result;
			}
			
			Expression::Ref Apply(NegativeExpression* expression, MergeParameter* target)
			{
				Ptr<NegativeExpression> result = new NegativeExpression;
				result->expression = Invoke(expression->expression, target);
				return result;
			}
			
			Expression::Ref Apply(UsingExpression* expression, MergeParameter* target)
			{
				if (target->definitions.Keys().Contains(expression->name))
				{
					Expression::Ref reference = target->definitions[expression->name];
					
					if (reference)
					{
						return reference;
					}
					else
					{
						throw ArgumentException(L"Regular expression syntax error: Found reference loops in\"" + expression->name + L"\".", L"vl::regex_internal::RegexExpression::Merge", L"");
					}
				}
				else
					if (target->regex->definitions.Keys().Contains(expression->name))
					{
						target->definitions.Add(expression->name, 0);
						Expression::Ref result = Invoke(target->regex->definitions[expression->name], target);
						target->definitions.Set(expression->name, result);
						return result;
					}
					else
					{
						throw ArgumentException(L"Regular expression syntax error: Cannot find sub expression reference\"" + expression->name + L"\".", L"vl::regex_internal::RegexExpression::Merge", L"");
					}
			}
		};
		
		/***********************************************************************
		EpsilonNfaAlgorithm
		***********************************************************************/
		
		class EpsilonNfaInfo
		{
		 public:
			Automaton::Ref		automaton;
		};
		
		class EpsilonNfa
		{
		 public:
			State*				start;
			State*				end;
			
			EpsilonNfa()
			{
				start = 0;
				end = 0;
			}
		};
		
		class EpsilonNfaAlgorithm : public RegexExpressionAlgorithm<EpsilonNfa, Automaton*>
		{
		 public:
			EpsilonNfa Connect(EpsilonNfa a, EpsilonNfa b, Automaton* target)
			{
				if (a.start)
				{
					target->NewEpsilon(a.end, b.start);
					a.end = b.end;
					return a;
				}
				else
				{
					return b;
				}
			}
			
			EpsilonNfa Apply(CharSetExpression* expression, Automaton* target)
			{
				EpsilonNfa nfa;
				nfa.start = target->NewState();
				nfa.end = target->NewState();
				
				for (vint i = 0; i < expression->ranges.Count(); i++)
				{
					target->NewChars(nfa.start, nfa.end, expression->ranges[i]);
				}
				
				return nfa;
			}
			
			EpsilonNfa Apply(LoopExpression* expression, Automaton* target)
			{
				EpsilonNfa head;
				
				for (vint i = 0; i < expression->min; i++)
				{
					EpsilonNfa body = Invoke(expression->expression, target);
					head = Connect(head, body, target);
				}
				
				if (expression->max == -1)
				{
					EpsilonNfa body = Invoke(expression->expression, target);
					
					if (!head.start)
					{
						head.start = head.end = target->NewState();
					}
					
					State* loopBegin = head.end;
					State* loopEnd = target->NewState();
					
					if (expression->preferLong)
					{
						target->NewEpsilon(loopBegin, body.start);
						target->NewEpsilon(body.end, loopBegin);
						target->NewNop(loopBegin, loopEnd);
					}
					else
					{
						target->NewNop(loopBegin, loopEnd);
						target->NewEpsilon(loopBegin, body.start);
						target->NewEpsilon(body.end, loopBegin);
					}
					
					head.end = loopEnd;
				}
				else
					if (expression->max > expression->min)
					{
						for (vint i = expression->min; i < expression->max; i++)
						{
							EpsilonNfa body = Invoke(expression->expression, target);
							State* start = target->NewState();
							State* end = target->NewState();
							
							if (expression->preferLong)
							{
								target->NewEpsilon(start, body.start);
								target->NewEpsilon(body.end, end);
								target->NewNop(start, end);
							}
							else
							{
								target->NewNop(start, end);
								target->NewEpsilon(start, body.start);
								target->NewEpsilon(body.end, end);
							}
							
							body.start = start;
							body.end = end;
							head = Connect(head, body, target);
						}
					}
					
				return head;
			}
			
			EpsilonNfa Apply(SequenceExpression* expression, Automaton* target)
			{
				EpsilonNfa a = Invoke(expression->left, target);
				EpsilonNfa b = Invoke(expression->right, target);
				return Connect(a, b, target);
			}
			
			EpsilonNfa Apply(AlternateExpression* expression, Automaton* target)
			{
				EpsilonNfa result;
				result.start = target->NewState();
				result.end = target->NewState();
				EpsilonNfa a = Invoke(expression->left, target);
				EpsilonNfa b = Invoke(expression->right, target);
				target->NewEpsilon(result.start, a.start);
				target->NewEpsilon(a.end, result.end);
				target->NewEpsilon(result.start, b.start);
				target->NewEpsilon(b.end, result.end);
				return result;
			}
			
			EpsilonNfa Apply(BeginExpression* expression, Automaton* target)
			{
				EpsilonNfa result;
				result.start = target->NewState();
				result.end = target->NewState();
				target->NewBeginString(result.start, result.end);
				return result;
			}
			
			EpsilonNfa Apply(EndExpression* expression, Automaton* target)
			{
				EpsilonNfa result;
				result.start = target->NewState();
				result.end = target->NewState();
				target->NewEndString(result.start, result.end);
				return result;
			}
			
			EpsilonNfa Apply(CaptureExpression* expression, Automaton* target)
			{
				EpsilonNfa result;
				result.start = target->NewState();
				result.end = target->NewState();
				
				vint capture = -1;
				
				if (expression->name != L"")
				{
					capture = target->captureNames.IndexOf(expression->name);
					
					if (capture == -1)
					{
						capture = target->captureNames.Count();
						target->captureNames.Add(expression->name);
					}
				}
				
				EpsilonNfa body = Invoke(expression->expression, target);
				target->NewCapture(result.start, body.start, capture);
				target->NewEnd(body.end, result.end);
				return result;
			}
			
			EpsilonNfa Apply(MatchExpression* expression, Automaton* target)
			{
				vint capture = -1;
				
				if (expression->name != L"")
				{
					capture = target->captureNames.IndexOf(expression->name);
					
					if (capture == -1)
					{
						capture = target->captureNames.Count();
						target->captureNames.Add(expression->name);
					}
				}
				
				EpsilonNfa result;
				result.start = target->NewState();
				result.end = target->NewState();
				target->NewMatch(result.start, result.end, capture, expression->index);
				return result;
			}
			
			EpsilonNfa Apply(PositiveExpression* expression, Automaton* target)
			{
				EpsilonNfa result;
				result.start = target->NewState();
				result.end = target->NewState();
				EpsilonNfa body = Invoke(expression->expression, target);
				target->NewPositive(result.start, body.start);
				target->NewEnd(body.end, result.end);
				return result;
			}
			
			EpsilonNfa Apply(NegativeExpression* expression, Automaton* target)
			{
				EpsilonNfa result;
				result.start = target->NewState();
				result.end = target->NewState();
				EpsilonNfa body = Invoke(expression->expression, target);
				target->NewNegative(result.start, body.start);
				target->NewEnd(body.end, result.end);
				target->NewNegativeFail(result.start, result.end);
				return result;
			}
			
			EpsilonNfa Apply(UsingExpression* expression, Automaton* target)
			{
				CHECK_FAIL(L"RegexExpression::GenerateEpsilonNfa()#UsingExpression cannot create state machine.");
			}
		};
		
		/***********************************************************************
		Expression
		***********************************************************************/
		
		bool Expression::IsEqual(vl::regex_internal::Expression* expression)
		{
			return IsEqualAlgorithm().Invoke(this, expression);
		}
		
		bool Expression::HasNoExtension()
		{
			return HasNoExtensionAlgorithm().Invoke(this, 0);
		}
		
		bool Expression::CanTreatAsPure()
		{
			return CanTreatAsPureAlgorithm().Invoke(this, 0);
		}
		
		void Expression::NormalizeCharSet(CharRange::List& subsets)
		{
			NormalizedCharSet normalized;
			BuildNormalizedCharSetAlgorithm().Invoke(this, &normalized);
			SetNormalizedCharSetAlgorithm().Invoke(this, &normalized);
			CopyFrom(subsets, normalized.ranges);
		}
		
		void Expression::CollectCharSet(CharRange::List& subsets)
		{
			NormalizedCharSet normalized;
			CopyFrom(normalized.ranges, subsets);
			BuildNormalizedCharSetAlgorithm().Invoke(this, &normalized);
			CopyFrom(subsets, normalized.ranges);
		}
		
		void Expression::ApplyCharSet(CharRange::List& subsets)
		{
			NormalizedCharSet normalized;
			CopyFrom(normalized.ranges, subsets);
			SetNormalizedCharSetAlgorithm().Invoke(this, &normalized);
		}
		
		Automaton::Ref Expression::GenerateEpsilonNfa()
		{
			Automaton::Ref automaton = new Automaton;
			EpsilonNfa result = EpsilonNfaAlgorithm().Invoke(this, automaton.Obj());
			automaton->startState = result.start;
			result.end->finalState = true;
			return automaton;
		}
		
		/***********************************************************************
		CharSetExpression
		***********************************************************************/
		
		bool CharSetExpression::AddRangeWithConflict(CharRange range)
		{
			if (range.begin > range.end)
			{
				wchar_t t = range.begin;
				range.begin = range.end;
				range.end = t;
			}
			
			for (vint i = 0; i < ranges.Count(); i++)
			{
				if (!(range < ranges[i] || range > ranges[i]))
				{
					return false;
				}
			}
			
			ranges.Add(range);
			return true;
		}
		
		/***********************************************************************
		RegexExpression
		***********************************************************************/
		
		Expression::Ref RegexExpression::Merge()
		{
			MergeParameter merge;
			merge.regex = this;
			return MergeAlgorithm().Invoke(expression, &merge);
		}
		
		/***********************************************************************
		Expression::Apply
		***********************************************************************/
		
		void CharSetExpression::Apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.Visit(this);
		}
		
		void LoopExpression::Apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.Visit(this);
		}
		
		void SequenceExpression::Apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.Visit(this);
		}
		
		void AlternateExpression::Apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.Visit(this);
		}
		
		void BeginExpression::Apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.Visit(this);
		}
		
		void EndExpression::Apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.Visit(this);
		}
		
		void CaptureExpression::Apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.Visit(this);
		}
		
		void MatchExpression::Apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.Visit(this);
		}
		
		void PositiveExpression::Apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.Visit(this);
		}
		
		void NegativeExpression::Apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.Visit(this);
		}
		
		void UsingExpression::Apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.Visit(this);
		}
	}
}

// #include "RegexExpression.h"
// #include "../Collections/OperationCopyFrom.h"

namespace vl
{
	namespace regex_internal
	{
	
		/***********************************************************************
		辅助函数
		***********************************************************************/
		
		bool IsChar(const wchar_t*& input, wchar_t c)
		{
			if (*input == c)
			{
				input++;
				return true;
			}
			else
			{
				return false;
			}
		}
		
		bool IsChars(const wchar_t*& input, const wchar_t* chars, wchar_t& c)
		{
			const wchar_t* position = ::wcschr(chars, *input);
			
			if (position)
			{
				c = *input++;
				return true;
			}
			else
			{
				return false;
			}
		}
		
		bool IsStr(const wchar_t*& input, const wchar_t* str)
		{
			size_t len = wcslen(str);
			
			if (wcsncmp(input, str, len) == 0)
			{
				input += len;
				return true;
			}
			else
			{
				return false;
			}
		}
		
		bool IsChars(const wchar_t*& input, const wchar_t* chars)
		{
			wchar_t c;
			return IsChars(input, chars, c);
		}
		
		bool IsPositiveInteger(const wchar_t*& input, vint& number)
		{
			bool readed = false;
			number = 0;
			
			while (L'0' <= *input && *input <= L'9')
			{
				number = number * 10 + (*input++) - L'0';
				readed = true;
			}
			
			return readed;
		}
		
		bool IsName(const wchar_t*& input, WString& name)
		{
			const wchar_t* read = input;
			
			if ((L'A' <= *read && *read <= L'Z') || (L'a' <= *read && *read <= L'z') || *read == L'_')
			{
				read++;
				
				while ((L'A' <= *read && *read <= L'Z') || (L'a' <= *read && *read <= L'z') || (L'0' <= *read && *read <= L'9') || *read == L'_')
				{
					read++;
				}
			}
			
			if (input == read)
			{
				return false;
			}
			else
			{
				name = WString(input, vint(read - input));
				input = read;
				return true;
			}
		}
		
		Ptr<LoopExpression> ParseLoop(const wchar_t*& input)
		{
			vint min = 0;
			vint max = 0;
			
			if (!*input)
			{
				return 0;
			}
			else
				if (IsChar(input, L'+'))
				{
					min = 1;
					max = -1;
				}
				else
					if (IsChar(input, L'*'))
					{
						min = 0;
						max = -1;
					}
					else
						if (IsChar(input, L'?'))
						{
							min = 0;
							max = 1;
						}
						else
							if (IsChar(input, L'{'))
							{
								if (IsPositiveInteger(input, min))
								{
									if (IsChar(input, L','))
									{
										if (!IsPositiveInteger(input, max))
										{
											max = -1;
										}
									}
									else
									{
										max = min;
									}
									
									if (!IsChar(input, L'}'))
									{
										goto THROW_EXCEPTION;
									}
								}
								else
								{
									goto THROW_EXCEPTION;
								}
							}
							else
							{
								return 0;
							}
							
			{
				LoopExpression* expression = new LoopExpression;
				expression->min = min;
				expression->max = max;
				expression->preferLong = !IsChar(input, L'?');
				return expression;
			}
			
THROW_EXCEPTION:
			throw ArgumentException(L"Regular expression syntax error: Illegal loop expression.", L"vl::regex_internal::ParseLoop", L"input");
		}
		
		Ptr<Expression> ParseCharSet(const wchar_t*& input)
		{
			if (!*input)
			{
				return 0;
			}
			else
				if (IsChar(input, L'^'))
				{
					return new BeginExpression;
				}
				else
					if (IsChar(input, L'$'))
					{
						return new EndExpression;
					}
					else
						if (IsChar(input, L'\\') || IsChar(input, L'/'))
						{
							Ptr<CharSetExpression> expression = new CharSetExpression;
							expression->reverse = false;
							
							switch (*input)
							{
								case L'.':
									expression->ranges.Add(CharRange(1, 65535));
									break;
									
								case L'r':
									expression->ranges.Add(CharRange(L'\r', L'\r'));
									break;
									
								case L'n':
									expression->ranges.Add(CharRange(L'\n', L'\n'));
									break;
									
								case L't':
									expression->ranges.Add(CharRange(L'\t', L'\t'));
									break;
									
								case L'\\': case L'/': case L'(': case L')': case L'+': case L'*': case L'?': case L'|':
								case L'{': case L'}': case L'[': case L']': case L'<': case L'>':
								case L'^': case L'$': case L'!': case L'=':
									expression->ranges.Add(CharRange(*input, *input));
									break;
									
								case L'S':
									expression->reverse = true;
									
								case L's':
									expression->ranges.Add(CharRange(L' ', L' '));
									expression->ranges.Add(CharRange(L'\r', L'\r'));
									expression->ranges.Add(CharRange(L'\n', L'\n'));
									expression->ranges.Add(CharRange(L'\t', L'\t'));
									break;
									
								case L'D':
									expression->reverse = true;
									
								case L'd':
									expression->ranges.Add(CharRange(L'0', L'9'));
									break;
									
								case L'L':
									expression->reverse = true;
									
								case L'l':
									expression->ranges.Add(CharRange(L'_', L'_'));
									expression->ranges.Add(CharRange(L'A', L'Z'));
									expression->ranges.Add(CharRange(L'a', L'z'));
									break;
									
								case L'W':
									expression->reverse = true;
									
								case L'w':
									expression->ranges.Add(CharRange(L'_', L'_'));
									expression->ranges.Add(CharRange(L'0', L'9'));
									expression->ranges.Add(CharRange(L'A', L'Z'));
									expression->ranges.Add(CharRange(L'a', L'z'));
									break;
									
								default:
									throw ArgumentException(L"Regular expression syntax error: Illegal character escaping.", L"vl::regex_internal::ParseCharSet", L"input");
							}
							
							input++;
							return expression;
						}
						else
							if (IsChar(input, L'['))
							{
								Ptr<CharSetExpression> expression = new CharSetExpression;
								
								if (IsChar(input, L'^'))
								{
									expression->reverse = true;
								}
								else
								{
									expression->reverse = false;
								}
								
								bool midState = false;
								wchar_t a = L'\0';
								wchar_t b = L'\0';
								
								while (true)
								{
									if (IsChar(input, L'\\') || IsChar(input, L'/'))
									{
										wchar_t c = L'\0';
										
										switch (*input)
										{
											case L'r':
												c = L'\r';
												break;
												
											case L'n':
												c = L'\n';
												break;
												
											case L't':
												c = L'\t';
												break;
												
											case L'-': case L'[': case L']': case L'\\': case L'/': case L'^': case L'$':
												c = *input;
												break;
												
											default:
												throw ArgumentException(L"Regular expression syntax error: Illegal character escaping, only \"rnt-[]\\/\" are legal escaped characters in [].", L"vl::regex_internal::ParseCharSet", L"input");
										}
										
										input++;
										midState ? b = c : a = c;
										midState = !midState;
									}
									else
										if (IsChars(input, L"-]"))
										{
											goto THROW_EXCEPTION;
										}
										else
											if (*input)
											{
												midState ? b = *input++ : a = *input++;
												midState = !midState;
											}
											else
											{
												goto THROW_EXCEPTION;
											}
											
									if (IsChar(input, L']'))
									{
										if (midState)
										{
											b = a;
										}
										
										if (!expression->AddRangeWithConflict(CharRange(a, b)))
										{
											goto THROW_EXCEPTION;
										}
										
										break;
									}
									else
										if (IsChar(input, L'-'))
										{
											if (!midState)
											{
												goto THROW_EXCEPTION;
											}
										}
										else
										{
											if (midState)
											{
												b = a;
											}
											
											if (expression->AddRangeWithConflict(CharRange(a, b)))
											{
												midState = false;
											}
											else
											{
												goto THROW_EXCEPTION;
											}
										}
								}
								
								return expression;
THROW_EXCEPTION:
								throw ArgumentException(L"Regular expression syntax error: Illegal character set definition.");
							}
							else
								if (IsChars(input, L"()+*?{}|"))
								{
									input--;
									return 0;
								}
								else
								{
									CharSetExpression* expression = new CharSetExpression;
									expression->reverse = false;
									expression->ranges.Add(CharRange(*input, *input));
									input++;
									return expression;
								}
		}
		
		Ptr<Expression> ParseFunction(const wchar_t*& input)
		{
			if (IsStr(input, L"(="))
			{
				Ptr<Expression> sub = ParseExpression(input);
				
				if (!IsChar(input, L')'))
				{
					goto NEED_RIGHT_BRACKET;
				}
				
				PositiveExpression* expression = new PositiveExpression;
				expression->expression = sub;
				return expression;
			}
			else
				if (IsStr(input, L"(!"))
				{
					Ptr<Expression> sub = ParseExpression(input);
					
					if (!IsChar(input, L')'))
					{
						goto NEED_RIGHT_BRACKET;
					}
					
					NegativeExpression* expression = new NegativeExpression;
					expression->expression = sub;
					return expression;
				}
				else
					if (IsStr(input, L"(<&"))
					{
						WString name;
						
						if (!IsName(input, name))
						{
							goto NEED_NAME;
						}
						
						if (!IsChar(input, L'>'))
						{
							goto NEED_GREATER;
						}
						
						if (!IsChar(input, L')'))
						{
							goto NEED_RIGHT_BRACKET;
						}
						
						UsingExpression* expression = new UsingExpression;
						expression->name = name;
						return expression;
					}
					else
						if (IsStr(input, L"(<$"))
						{
							WString name;
							vint index = -1;
							
							if (IsName(input, name))
							{
								if (IsChar(input, L';'))
								{
									if (!IsPositiveInteger(input, index))
									{
										goto NEED_NUMBER;
									}
								}
							}
							else
								if (!IsPositiveInteger(input, index))
								{
									goto NEED_NUMBER;
								}
								
							if (!IsChar(input, L'>'))
							{
								goto NEED_GREATER;
							}
							
							if (!IsChar(input, L')'))
							{
								goto NEED_RIGHT_BRACKET;
							}
							
							MatchExpression* expression = new MatchExpression;
							expression->name = name;
							expression->index = index;
							return expression;
						}
						else
							if (IsStr(input, L"(<"))
							{
								WString name;
								
								if (!IsName(input, name))
								{
									goto NEED_NAME;
								}
								
								if (!IsChar(input, L'>'))
								{
									goto NEED_GREATER;
								}
								
								Ptr<Expression> sub = ParseExpression(input);
								
								if (!IsChar(input, L')'))
								{
									goto NEED_RIGHT_BRACKET;
								}
								
								CaptureExpression* expression = new CaptureExpression;
								expression->name = name;
								expression->expression = sub;
								return expression;
							}
							else
								if (IsStr(input, L"(?"))
								{
									Ptr<Expression> sub = ParseExpression(input);
									
									if (!IsChar(input, L')'))
									{
										goto NEED_RIGHT_BRACKET;
									}
									
									CaptureExpression* expression = new CaptureExpression;
									expression->expression = sub;
									return expression;
								}
								else
									if (IsChar(input, L'('))
									{
										Ptr<Expression> sub = ParseExpression(input);
										
										if (!IsChar(input, L')'))
										{
											goto NEED_RIGHT_BRACKET;
										}
										
										return sub;
									}
									else
									{
										return 0;
									}
									
NEED_RIGHT_BRACKET:
			throw ArgumentException(L"Regular expression syntax error: \")\" expected.", L"vl::regex_internal::ParseFunction", L"input");
NEED_GREATER:
			throw ArgumentException(L"Regular expression syntax error: \">\" expected.", L"vl::regex_internal::ParseFunction", L"input");
NEED_NAME:
			throw ArgumentException(L"Regular expression syntax error: Identifier expected.", L"vl::regex_internal::ParseFunction", L"input");
NEED_NUMBER:
			throw ArgumentException(L"Regular expression syntax error: Number expected.", L"vl::regex_internal::ParseFunction", L"input");
		}
		
		Ptr<Expression> ParseUnit(const wchar_t*& input)
		{
			Ptr<Expression> unit = ParseCharSet(input);
			
			if (!unit)
			{
				unit = ParseFunction(input);
			}
			
			if (!unit)
			{
				return 0;
			}
			
			Ptr<LoopExpression> loop;
			
			while ((loop = ParseLoop(input)))
			{
				loop->expression = unit;
				unit = loop;
			}
			
			return unit;
		}
		
		Ptr<Expression> ParseJoin(const wchar_t*& input)
		{
			Ptr<Expression> expression = ParseUnit(input);
			
			while (true)
			{
				Ptr<Expression> right = ParseUnit(input);
				
				if (right)
				{
					SequenceExpression* sequence = new SequenceExpression;
					sequence->left = expression;
					sequence->right = right;
					expression = sequence;
				}
				else
				{
					break;
				}
			}
			
			return expression;
		}
		
		Ptr<Expression> ParseAlt(const wchar_t*& input)
		{
			Ptr<Expression> expression = ParseJoin(input);
			
			while (true)
			{
				if (IsChar(input, L'|'))
				{
					Ptr<Expression> right = ParseJoin(input);
					
					if (right)
					{
						AlternateExpression* alternate = new AlternateExpression;
						alternate->left = expression;
						alternate->right = right;
						expression = alternate;
					}
					else
					{
						throw ArgumentException(L"Regular expression syntax error: Expression expected.", L"vl::regex_internal::ParseAlt", L"input");
					}
				}
				else
				{
					break;
				}
			}
			
			return expression;
		}
		
		Ptr<Expression> ParseExpression(const wchar_t*& input)
		{
			return ParseAlt(input);
		}
		
		RegexExpression::Ref ParseRegexExpression(const WString& code)
		{
			RegexExpression::Ref regex = new RegexExpression;
			const wchar_t* start = code.Buffer();
			const wchar_t* input = start;
			
			try
			{
				while (IsStr(input, L"(<#"))
				{
					WString name;
					
					if (!IsName(input, name))
					{
						throw ArgumentException(L"Regular expression syntax error: Identifier expected.", L"vl::regex_internal::ParseRegexExpression", L"code");
					}
					
					if (!IsChar(input, L'>'))
					{
						throw ArgumentException(L"Regular expression syntax error: \">\" expected.", L"vl::regex_internal::ParseFunction", L"input");
					}
					
					Ptr<Expression> sub = ParseExpression(input);
					
					if (!IsChar(input, L')'))
					{
						throw ArgumentException(L"Regular expression syntax error: \")\" expected.", L"vl::regex_internal::ParseFunction", L"input");
					}
					
					if (regex->definitions.Keys().Contains(name))
					{
						throw ArgumentException(L"Regular expression syntax error: Found duplicated sub expression name: \"" + name + L"\". ", L"vl::regex_internal::ParseFunction", L"input");
					}
					else
					{
						regex->definitions.Add(name, sub);
					}
				}
				
				regex->expression = ParseExpression(input);
				
				if (!regex->expression)
				{
					throw ArgumentException(L"Regular expression syntax error: Expression expected.", L"vl::regex_internal::ParseUnit", L"input");
				}
				
				if (*input)
				{
					throw ArgumentException(L"Regular expression syntax error: Found unnecessary tokens.", L"vl::regex_internal::ParseUnit", L"input");
				}
				
				return regex;
			}
			catch (const ArgumentException& e)
			{
				throw ParsingException(e.Message(), code, input - start);
			}
		}
		
		WString EscapeTextForRegex(const WString& literalString)
		{
			WString result;
			
			for (vint i = 0; i < literalString.Length(); i++)
			{
				wchar_t c = literalString[i];
				
				switch (c)
				{
					case L'\\': case L'/': case L'(': case L')': case L'+': case L'*': case L'?': case L'|':
					case L'{': case L'}': case L'[': case L']': case L'<': case L'>':
					case L'^': case L'$': case L'!': case L'=':
						result += WString(L"\\") + c;
						break;
						
					case L'\r':
						result += L"\\r";
						break;
						
					case L'\n':
						result += L"\\n";
						break;
						
					case L'\t':
						result += L"\\t";
						break;
						
					default:
						result += c;
				}
			}
			
			return result;
		}
		
		WString UnescapeTextForRegex(const WString& escapedText)
		{
			WString result;
			
			for (vint i = 0; i < escapedText.Length(); i++)
			{
				wchar_t c = escapedText[i];
				
				if (c == L'\\' || c == L'/')
				{
					if (i < escapedText.Length() - 1)
					{
						i++;
						c = escapedText[i];
						
						switch (c)
						{
							case L'r':
								result += L"\r";
								break;
								
							case L'n':
								result += L"\n";
								break;
								
							case L't':
								result += L"\t";
								break;
								
							default:
								result += c;
						}
						
						continue;
					}
				}
				
				result += c;
			}
			
			return result;
		}
		
		WString NormalizeEscapedTextForRegex(const WString& escapedText)
		{
			WString result;
			
			for (vint i = 0; i < escapedText.Length(); i++)
			{
				wchar_t c = escapedText[i];
				
				if (c == L'\\' || c == L'/')
				{
					if (i < escapedText.Length() - 1)
					{
						i++;
						c = escapedText[i];
						result += WString(L"\\") + c;
						continue;
					}
				}
				
				result += c;
			}
			
			return result;
		}
		
		bool IsRegexEscapedLiteralString(const WString& regex)
		{
			for (vint i = 0; i < regex.Length(); i++)
			{
				wchar_t c = regex[i];
				
				if (c == L'\\' || c == L'/')
				{
					i++;
				}
				else
				{
					switch (c)
					{
						case L'\\': case L'/': case L'(': case L')': case L'+': case L'*': case L'?': case L'|':
						case L'{': case L'}': case L'[': case L']': case L'<': case L'>':
						case L'^': case L'$': case L'!': case L'=':
							return false;
					}
				}
			}
			
			return true;
		}
	}
}


// #include "RegexPure.h"

namespace vl
{
	namespace regex_internal
	{
	
		/***********************************************************************
		PureInterpretor
		***********************************************************************/
		
		PureInterpretor::PureInterpretor(Automaton::Ref dfa, CharRange::List& subsets)
			: transition(0)
			, finalState(0)
			, relatedFinalState(0)
		{
			stateCount = dfa->states.Count();
			charSetCount = subsets.Count() + 1;
			startState = dfa->states.IndexOf(dfa->startState);
			
			//填充字符映射表
			for (vint i = 0; i < SupportedCharCount; i++)
			{
				charMap[i] = charSetCount - 1;
			}
			
			for (vint i = 0; i < subsets.Count(); i++)
			{
				CharRange range = subsets[i];
				
				for (vint j = range.begin; j <= range.end; j++)
				{
					charMap[j] = i;
				}
			}
			
			//构造状态转换表
			transition = new vint*[stateCount];
			
			for (vint i = 0; i < stateCount; i++)
			{
				transition[i] = new vint[charSetCount];
				
				for (vint j = 0; j < charSetCount; j++)
				{
					transition[i][j] = -1;
				}
				
				State* state = dfa->states[i].Obj();
				
				for (vint j = 0; j < state->transitions.Count(); j++)
				{
					Transition* dfaTransition = state->transitions[j];
					
					switch (dfaTransition->type)
					{
						case Transition::Chars:
							{
								vint index = subsets.IndexOf(dfaTransition->range);
								
								if (index == -1)
								{
									CHECK_ERROR(false, L"PureInterpretor::PureInterpretor(Automaton::Ref, CharRange::List&)#Specified chars don't appear in the normalized char ranges.");
								}
								
								transition[i][index] = dfa->states.IndexOf(dfaTransition->target);
							}
							break;
							
						default:
							CHECK_ERROR(false, L"PureInterpretor::PureInterpretor(Automaton::Ref, CharRange::List&)#PureInterpretor only accepts Transition::Chars transitions.");
					}
				}
			}
			
			//填充终结状态表
			finalState = new bool[stateCount];
			
			for (vint i = 0; i < stateCount; i++)
			{
				finalState[i] = dfa->states[i]->finalState;
			}
		}
		
		PureInterpretor::~PureInterpretor()
		{
			if (relatedFinalState)
			{
				delete[] relatedFinalState;
			}
			
			delete[] finalState;
			
			for (vint i = 0; i < stateCount; i++)
			{
				delete[] transition[i];
			}
			
			delete[] transition;
		}
		
		bool PureInterpretor::MatchHead(const wchar_t* input, const wchar_t* start, PureResult& result)
		{
			result.start = input - start;
			result.length = -1;
			result.finalState = -1;
			result.terminateState = -1;
			
			vint currentState = startState;
			vint terminateState = -1;
			vint terminateLength = -1;
			const wchar_t* read = input;
			
			while (currentState != -1)
			{
				terminateState = currentState;
				terminateLength = read - input;
				
				if (finalState[currentState])
				{
					result.length = terminateLength;
					result.finalState = currentState;
				}
				
				if (!*read)
				{
					break;
				}
				
				vint charIndex = charMap[*read++];
				currentState = transition[currentState][charIndex];
			}
			
			if (result.finalState == -1)
			{
				if (terminateLength > 0)
				{
					result.terminateState = terminateState;
				}
				
				result.length = terminateLength;
				return false;
			}
			else
			{
				return true;
			}
		}
		
		bool PureInterpretor::Match(const wchar_t* input, const wchar_t* start, PureResult& result)
		{
			const wchar_t* read = input;
			
			while (*read)
			{
				if (MatchHead(read, start, result))
				{
					return true;
				}
				
				read++;
			}
			
			return false;
		}
		
		vint PureInterpretor::GetStartState()
		{
			return startState;
		}
		
		vint PureInterpretor::Transit(wchar_t input, vint state)
		{
			if (0 <= state && state < stateCount)
			{
				vint charIndex = charMap[input];
				vint nextState = transition[state][charIndex];
				return nextState;
			}
			else
			{
				return -1;
			}
		}
		
		bool PureInterpretor::IsFinalState(vint state)
		{
			return 0 <= state && state < stateCount && finalState[state];
		}
		
		bool PureInterpretor::IsDeadState(vint state)
		{
			if (state == -1)
			{
				return true;
			}
			
			for (vint i = 0; i < charSetCount; i++)
			{
				if (transition[state][i] != -1)
				{
					return false;
				}
			}
			
			return true;
		}
		
		void PureInterpretor::PrepareForRelatedFinalStateTable()
		{
			if (!relatedFinalState)
			{
				relatedFinalState = new vint[stateCount];
				
				for (vint i = 0; i < stateCount; i++)
				{
					relatedFinalState[i] = finalState[i] ? i : -1;
				}
				
				while (true)
				{
					vint modifyCount = 0;
					
					for (vint i = 0; i < stateCount; i++)
					{
						if (relatedFinalState[i] == -1)
						{
							vint state = -1;
							
							for (vint j = 0; j < charSetCount; j++)
							{
								vint nextState = transition[i][j];
								
								if (nextState != -1)
								{
									state = relatedFinalState[nextState];
									
									if (state != -1)
									{
										break;
									}
								}
							}
							
							if (state != -1)
							{
								relatedFinalState[i] = state;
								modifyCount++;
							}
						}
					}
					
					if (modifyCount == 0)
					{
						break;
					}
				}
			}
		}
		
		vint PureInterpretor::GetRelatedFinalState(vint state)
		{
			return relatedFinalState ? relatedFinalState[state] : -1;
		}
	}
}

// #include "RegexWriter.h"
// #include "../Collections/OperationCopyFrom.h"

namespace vl
{
	namespace regex
	{
		using namespace vl::regex_internal;
		
		/***********************************************************************
		RegexNode
		***********************************************************************/
		
		RegexNode::RegexNode(vl::regex_internal::Expression::Ref _expression)
			: expression(_expression)
		{
		}
		
		RegexNode RegexNode::Some()const
		{
			return Loop(1, -1);
		}
		
		RegexNode RegexNode::Any()const
		{
			return Loop(0, -1);
		}
		
		RegexNode RegexNode::Opt()const
		{
			return Loop(0, 1);
		}
		
		RegexNode RegexNode::Loop(vint min, vint max)const
		{
			LoopExpression* target = new LoopExpression;
			target->min = min;
			target->max = max;
			target->preferLong = true;
			target->expression = expression;
			return RegexNode(target);
		}
		
		RegexNode RegexNode::AtLeast(vint min)const
		{
			return Loop(min, -1);
		}
		
		RegexNode RegexNode::operator+(const RegexNode& node)const
		{
			SequenceExpression* target = new SequenceExpression;
			target->left = expression;
			target->right = node.expression;
			return RegexNode(target);
		}
		
		RegexNode RegexNode::operator|(const RegexNode& node)const
		{
			AlternateExpression* target = new AlternateExpression;
			target->left = expression;
			target->right = node.expression;
			return RegexNode(target);
		}
		
		RegexNode RegexNode::operator+()const
		{
			PositiveExpression* target = new PositiveExpression;
			target->expression = expression;
			return RegexNode(target);
		}
		
		RegexNode RegexNode::operator-()const
		{
			NegativeExpression* target = new NegativeExpression;
			target->expression = expression;
			return RegexNode(target);
		}
		
		RegexNode RegexNode::operator!()const
		{
			CharSetExpression* source = dynamic_cast<CharSetExpression*>(expression.Obj());
			CHECK_ERROR(source, L"RegexNode::operator!()#operator ! can only applies on charset expressions.");
			Ptr<CharSetExpression> target = new CharSetExpression;
			CopyFrom(target->ranges, source->ranges);
			target->reverse = !source->reverse;
			return RegexNode(target);
		}
		
		RegexNode RegexNode::operator%(const RegexNode& node)const
		{
			CharSetExpression* left = dynamic_cast<CharSetExpression*>(expression.Obj());
			CharSetExpression* right = dynamic_cast<CharSetExpression*>(node.expression.Obj());
			CHECK_ERROR(left && right && !left->reverse && !right->reverse, L"RegexNode::operator%(const RegexNode&)#operator % only connects non-reverse charset expressions.");
			Ptr<CharSetExpression> target = new CharSetExpression;
			target->reverse = false;
			CopyFrom(target->ranges, left->ranges);
			
			for (vint i = 0; i < right->ranges.Count(); i++)
			{
				if (!target->AddRangeWithConflict(right->ranges[i]))
				{
					CHECK_ERROR(false, L"RegexNode::operator%(const RegexNode&)#Failed to create charset expression from operator %.");
				}
			}
			
			return RegexNode(target);
		}
		
		/***********************************************************************
		外部函数
		***********************************************************************/
		
		RegexNode rCapture(const WString& name, const RegexNode& node)
		{
			CaptureExpression* target = new CaptureExpression;
			target->name = name;
			target->expression = node.expression;
			return RegexNode(target);
		}
		
		RegexNode rUsing(const WString& name)
		{
			UsingExpression* target = new UsingExpression;
			target->name = name;
			return RegexNode(target);
		}
		
		RegexNode rMatch(const WString& name, vint index)
		{
			MatchExpression* target = new MatchExpression;
			target->name = name;
			target->index = index;
			return RegexNode(target);
		}
		
		RegexNode rMatch(vint index)
		{
			MatchExpression* target = new MatchExpression;
			target->index = index;
			return RegexNode(target);
		}
		
		RegexNode rBegin()
		{
			return RegexNode(new BeginExpression);
		}
		
		RegexNode rEnd()
		{
			return RegexNode(new EndExpression);
		}
		
		RegexNode rC(wchar_t a, wchar_t b)
		{
			if (!b)
			{
				b = a;
			}
			
			CharSetExpression* target = new CharSetExpression;
			target->reverse = false;
			target->AddRangeWithConflict(CharRange(a, b));
			return RegexNode(target);
		}
		
		RegexNode r_d()
		{
			return rC(L'0', L'9');
		}
		
		RegexNode r_l()
		{
			return rC(L'a', L'z') % rC(L'A', L'Z') % rC(L'_');
		}
		
		RegexNode r_w()
		{
			return rC(L'0', L'9') % rC(L'a', L'z') % rC(L'A', L'Z') % rC(L'_');
		}
		
		RegexNode rAnyChar()
		{
			return rC(1, 65535);
		}
	}
}

// #include "Regex.h"
// #include "RegexExpression.h"
// #include "RegexPure.h"
// #include "RegexRich.h"
// #include "../Collections/OperationCopyFrom.h"

namespace vl
{
	namespace regex
	{
		using namespace collections;
		using namespace regex_internal;
		
		/***********************************************************************
		RegexString
		***********************************************************************/
		
		RegexString::RegexString(vint _start)
			: start(_start)
			, length(0)
		{
		}
		
		RegexString::RegexString(const WString& _string, vint _start, vint _length)
			: value(_length == 0 ? L"" : _string.Sub(_start, _length))
			, start(_start)
			, length(_length)
		{
		}
		
		vint RegexString::Start()const
		{
			return start;
		}
		
		vint RegexString::Length()const
		{
			return length;
		}
		
		const WString& RegexString::Value()const
		{
			return value;
		}
		
		bool RegexString::operator==(const RegexString& string)const
		{
			return start == string.start && length == string.length && value == string.value;
		}
		
		/***********************************************************************
		RegexMatch
		***********************************************************************/
		
		RegexMatch::RegexMatch(const WString& _string, PureResult* _result)
			: success(true)
			, result(_string, _result->start, _result->length)
		{
		}
		
		RegexMatch::RegexMatch(const WString& _string, RichResult* _result, RichInterpretor* _rich)
			: success(true)
			, result(_string, _result->start, _result->length)
		{
			for (vint i = 0; i < _result->captures.Count(); i++)
			{
				CaptureRecord& capture = _result->captures[i];
				
				if (capture.capture == -1)
				{
					captures.Add(RegexString(_string, capture.start, capture.length));
				}
				else
				{
					groups.Add(_rich->CaptureNames().Get(capture.capture), RegexString(_string, capture.start, capture.length));
				}
			}
		}
		
		RegexMatch::RegexMatch(const RegexString& _result)
			: success(false)
			, result(_result)
		{
		}
		
		bool RegexMatch::Success()const
		{
			return success;
		}
		
		const RegexString& RegexMatch::Result()const
		{
			return result;
		}
		
		const RegexMatch::CaptureList& RegexMatch::Captures()const
		{
			return captures;
		}
		
		const RegexMatch::CaptureGroup& RegexMatch::Groups()const
		{
			return groups;
		}
		
		/***********************************************************************
		Regex
		***********************************************************************/
		
		void Regex::Process(const WString& text, bool keepEmpty, bool keepSuccess, bool keepFail, RegexMatch::List& matches)const
		{
			if (rich)
			{
				const wchar_t* start = text.Buffer();
				const wchar_t* input = start;
				RichResult result;
				
				while (rich->Match(input, start, result))
				{
					vint offset = input - start;
					
					if (keepFail)
					{
						if (result.start > offset || keepEmpty)
						{
							matches.Add(new RegexMatch(RegexString(text, offset, result.start - offset)));
						}
					}
					
					if (keepSuccess)
					{
						matches.Add(new RegexMatch(text, &result, rich));
					}
					
					input = start + result.start + result.length;
				}
				
				if (keepFail)
				{
					vint remain = input - start;
					vint length = text.Length() - remain;
					
					if (length || keepEmpty)
					{
						matches.Add(new RegexMatch(RegexString(text, remain, length)));
					}
				}
			}
			else
			{
				const wchar_t* start = text.Buffer();
				const wchar_t* input = start;
				PureResult result;
				
				while (pure->Match(input, start, result))
				{
					vint offset = input - start;
					
					if (keepFail)
					{
						if (result.start > offset || keepEmpty)
						{
							matches.Add(new RegexMatch(RegexString(text, offset, result.start - offset)));
						}
					}
					
					if (keepSuccess)
					{
						matches.Add(new RegexMatch(text, &result));
					}
					
					input = start + result.start + result.length;
				}
				
				if (keepFail)
				{
					vint remain = input - start;
					vint length = text.Length() - remain;
					
					if (length || keepEmpty)
					{
						matches.Add(new RegexMatch(RegexString(text, remain, length)));
					}
				}
			}
		}
		
		Regex::Regex(const WString& code, bool preferPure)
			: pure(0)
			, rich(0)
		{
			CharRange::List subsets;
			RegexExpression::Ref regex = ParseRegexExpression(code);
			Expression::Ref expression = regex->Merge();
			expression->NormalizeCharSet(subsets);
			
			bool pureRequired = false;
			bool richRequired = false;
			
			if (preferPure)
			{
				if (expression->HasNoExtension())
				{
					pureRequired = true;
				}
				else
				{
					if (expression->CanTreatAsPure())
					{
						pureRequired = true;
						richRequired = true;
					}
					else
					{
						richRequired = true;
					}
				}
			}
			else
			{
				richRequired = true;
			}
			
			try
			{
				if (pureRequired)
				{
					Dictionary<State*, State*> nfaStateMap;
					Group<State*, State*> dfaStateMap;
					Automaton::Ref eNfa = expression->GenerateEpsilonNfa();
					Automaton::Ref nfa = EpsilonNfaToNfa(eNfa, PureEpsilonChecker, nfaStateMap);
					Automaton::Ref dfa = NfaToDfa(nfa, dfaStateMap);
					pure = new PureInterpretor(dfa, subsets);
				}
				
				if (richRequired)
				{
					Dictionary<State*, State*> nfaStateMap;
					Group<State*, State*> dfaStateMap;
					Automaton::Ref eNfa = expression->GenerateEpsilonNfa();
					Automaton::Ref nfa = EpsilonNfaToNfa(eNfa, RichEpsilonChecker, nfaStateMap);
					Automaton::Ref dfa = NfaToDfa(nfa, dfaStateMap);
					rich = new RichInterpretor(dfa);
				}
			}
			catch (...)
			{
				if (pure)
				{
					delete pure;
				}
				
				if (rich)
				{
					delete rich;
				}
				
				throw;
			}
		}
		
		Regex::~Regex()
		{
			if (pure)
			{
				delete pure;
			}
			
			if (rich)
			{
				delete rich;
			}
		}
		
		bool Regex::IsPureMatch()const
		{
			return rich ? false : true;
		}
		
		bool Regex::IsPureTest()const
		{
			return pure ? true : false;
		}
		
		RegexMatch::Ref Regex::MatchHead(const WString& text)const
		{
			if (rich)
			{
				RichResult result;
				
				if (rich->MatchHead(text.Buffer(), text.Buffer(), result))
				{
					return new RegexMatch(text, &result, rich);
				}
				else
				{
					return 0;
				}
			}
			else
			{
				PureResult result;
				
				if (pure->MatchHead(text.Buffer(), text.Buffer(), result))
				{
					return new RegexMatch(text, &result);
				}
				else
				{
					return 0;
				}
			}
		}
		
		RegexMatch::Ref Regex::Match(const WString& text)const
		{
			if (rich)
			{
				RichResult result;
				
				if (rich->Match(text.Buffer(), text.Buffer(), result))
				{
					return new RegexMatch(text, &result, rich);
				}
				else
				{
					return 0;
				}
			}
			else
			{
				PureResult result;
				
				if (pure->Match(text.Buffer(), text.Buffer(), result))
				{
					return new RegexMatch(text, &result);
				}
				else
				{
					return 0;
				}
			}
		}
		
		bool Regex::TestHead(const WString& text)const
		{
			if (pure)
			{
				PureResult result;
				return pure->MatchHead(text.Buffer(), text.Buffer(), result);
			}
			else
			{
				RichResult result;
				return rich->MatchHead(text.Buffer(), text.Buffer(), result);
			}
		}
		
		bool Regex::Test(const WString& text)const
		{
			if (pure)
			{
				PureResult result;
				return pure->Match(text.Buffer(), text.Buffer(), result);
			}
			else
			{
				RichResult result;
				return rich->Match(text.Buffer(), text.Buffer(), result);
			}
		}
		
		void Regex::Search(const WString& text, RegexMatch::List& matches)const
		{
			Process(text, false, true, false, matches);
		}
		
		void Regex::Split(const WString& text, bool keepEmptyMatch, RegexMatch::List& matches)const
		{
			Process(text, keepEmptyMatch, false, true, matches);
		}
		
		void Regex::Cut(const WString& text, bool keepEmptyMatch, RegexMatch::List& matches)const
		{
			Process(text, keepEmptyMatch, true, true, matches);
		}
		
		/***********************************************************************
		RegexTokens
		***********************************************************************/
		
		bool RegexToken::operator==(const RegexToken& _token)const
		{
			return length == _token.length && token == _token.token && reading == _token.reading;
		}
		
		bool RegexToken::operator==(const wchar_t* _token)const
		{
			return wcslen(_token) == length && wcsncmp(reading, _token, length) == 0;
		}
		
		class RegexTokenEnumerator : public Object, public IEnumerator<RegexToken>
		{
		 protected:
			RegexToken				token;
			vint					index;
			
			PureInterpretor*		pure;
			const Array<vint>&		stateTokens;
			const wchar_t*			start;
			vint					codeIndex;
			
			const wchar_t*			reading;
			vint					rowStart;
			vint					columnStart;
			bool					cacheAvailable;
			RegexToken				cacheToken;
			
		 public:
			RegexTokenEnumerator(const RegexTokenEnumerator& enumerator)
				: token(enumerator.token)
				, index(enumerator.index)
				, pure(enumerator.pure)
				, stateTokens(enumerator.stateTokens)
				, reading(enumerator.reading)
				, start(enumerator.start)
				, rowStart(enumerator.rowStart)
				, columnStart(enumerator.columnStart)
				, codeIndex(enumerator.codeIndex)
				, cacheAvailable(enumerator.cacheAvailable)
				, cacheToken(enumerator.cacheToken)
			{
			}
			
			RegexTokenEnumerator(PureInterpretor* _pure, const Array<vint>& _stateTokens, const wchar_t* _start, vint _codeIndex)
				: index(-1)
				, pure(_pure)
				, stateTokens(_stateTokens)
				, reading(_start)
				, start(_start)
				, rowStart(0)
				, columnStart(0)
				, codeIndex(_codeIndex)
				, cacheAvailable(false)
			{
			}
			
			IEnumerator<RegexToken>* Clone()const
			{
				return new RegexTokenEnumerator(*this);
			}
			
			const RegexToken& Current()const
			{
				return token;
			}
			
			vint Index()const
			{
				return index;
			}
			
			bool Next()
			{
				if (!cacheAvailable && !*reading)
				{
					return false;
				}
				
				if (cacheAvailable)
				{
					token = cacheToken;
					cacheAvailable = false;
				}
				else
				{
					token.reading = reading;
					token.start = 0;
					token.length = 0;
					token.token = -2;
					token.completeToken = true;
				}
				
				token.rowStart = rowStart;
				token.columnStart = columnStart;
				token.rowEnd = rowStart;
				token.columnEnd = columnStart;
				token.codeIndex = codeIndex;
				
				PureResult result;
				
				while (*reading)
				{
					vint id = -1;
					bool completeToken = true;
					
					if (!pure->MatchHead(reading, start, result))
					{
						result.start = reading - start;
						
						if (id == -1 && result.terminateState != -1)
						{
							vint state = pure->GetRelatedFinalState(result.terminateState);
							
							if (state != -1)
							{
								id = stateTokens[state];
							}
						}
						
						if (id == -1)
						{
							result.length = 1;
						}
						else
						{
							completeToken = false;
						}
					}
					else
					{
						id = stateTokens.Get(result.finalState);
					}
					
					if (token.token == -2)
					{
						token.start = result.start;
						token.length = result.length;
						token.token = id;
						token.completeToken = completeToken;
					}
					else
						if (token.token == id && id == -1)
						{
							token.length += result.length;
						}
						else
						{
							cacheAvailable = true;
							cacheToken.reading = reading;
							cacheToken.start = result.start;
							cacheToken.length = result.length;
							cacheToken.codeIndex = codeIndex;
							cacheToken.token = id;
							cacheToken.completeToken = completeToken;
						}
						
					reading += result.length;
					
					if (cacheAvailable)
					{
						break;
					}
				}
				
				index++;
				
				for (vint i = 0; i < token.length; i++)
				{
					token.rowEnd = rowStart;
					token.columnEnd = columnStart;
					
					if (token.reading[i] == L'\n')
					{
						rowStart++;
						columnStart = 0;
					}
					else
					{
						columnStart++;
					}
				}
				
				return true;
			}
			
			void Reset()
			{
				index = -1;
				reading = start;
				cacheAvailable = false;
			}
			
			void ReadToEnd(List<RegexToken>& tokens, bool(*discard)(vint))
			{
				while (Next())
				{
					if (!discard(token.token))
					{
						tokens.Add(token);
					}
				}
			}
		};
		
		RegexTokens::RegexTokens(PureInterpretor* _pure, const Array<vint>& _stateTokens, const WString& _code, vint _codeIndex)
			: pure(_pure)
			, stateTokens(_stateTokens)
			, code(_code)
			, codeIndex(_codeIndex)
		{
		}
		
		RegexTokens::RegexTokens(const RegexTokens& tokens)
			: pure(tokens.pure)
			, stateTokens(tokens.stateTokens)
			, code(tokens.code)
			, codeIndex(tokens.codeIndex)
		{
		}
		
		IEnumerator<RegexToken>* RegexTokens::CreateEnumerator()const
		{
			return new RegexTokenEnumerator(pure, stateTokens, code.Buffer(), codeIndex);
		}
		
		bool DefaultDiscard(vint token)
		{
			return false;
		}
		
		void RegexTokens::ReadToEnd(collections::List<RegexToken>& tokens, bool(*discard)(vint))const
		{
			if (discard == 0)
			{
				discard = &DefaultDiscard;
			}
			
			RegexTokenEnumerator(pure, stateTokens, code.Buffer(), codeIndex).ReadToEnd(tokens, discard);
		}
		
		/***********************************************************************
		RegexLexerWalker
		***********************************************************************/
		
		RegexLexerWalker::RegexLexerWalker(PureInterpretor* _pure, const Array<vint>& _stateTokens)
			: pure(_pure)
			, stateTokens(_stateTokens)
		{
		}
		
		RegexLexerWalker::RegexLexerWalker(const RegexLexerWalker& walker)
			: pure(walker.pure)
			, stateTokens(walker.stateTokens)
		{
		}
		
		RegexLexerWalker::~RegexLexerWalker()
		{
		}
		
		vint RegexLexerWalker::GetStartState()const
		{
			return pure->GetStartState();
		}
		
		vint RegexLexerWalker::GetRelatedToken(vint state)const
		{
			vint finalState = pure->GetRelatedFinalState(state);
			return finalState == -1 ? -1 : stateTokens.Get(finalState);
		}
		
		void RegexLexerWalker::Walk(wchar_t input, vint& state, vint& token, bool& finalState, bool& previousTokenStop)const
		{
			vint previousState = state;
			token = -1;
			finalState = false;
			previousTokenStop = false;
			
			if (state == -1)
			{
				state = pure->GetStartState();
				previousTokenStop = true;
			}
			
			state = pure->Transit(input, state);
			
			if (state == -1)
			{
				previousTokenStop = true;
				
				if (previousState == -1)
				{
					finalState = true;
					return;
				}
				else
					if (pure->IsFinalState(previousState))
					{
						state = pure->Transit(input, pure->GetStartState());
					}
			}
			
			if (pure->IsFinalState(state))
			{
				token = stateTokens.Get(state);
				finalState = true;
				return;
			}
			else
			{
				finalState = state == -1;
				return;
			}
		}
		
		vint RegexLexerWalker::Walk(wchar_t input, vint state)const
		{
			vint token = -1;
			bool finalState = false;
			bool previousTokenStop = false;
			Walk(input, state, token, finalState, previousTokenStop);
			return state;
		}
		
		bool RegexLexerWalker::IsClosedToken(const wchar_t* input, vint length)const
		{
			vint state = pure->GetStartState();
			
			for (vint i = 0; i < length; i++)
			{
				state = pure->Transit(input[i], state);
				
				if (state == -1)
				{
					return true;
				}
				
				if (pure->IsDeadState(state))
				{
					return true;
				}
			}
			
			return false;
		}
		
		bool RegexLexerWalker::IsClosedToken(const WString& input)const
		{
			return IsClosedToken(input.Buffer(), input.Length());
		}
		
		/***********************************************************************
		RegexLexerColorizer
		***********************************************************************/
		
		RegexLexerColorizer::RegexLexerColorizer(const RegexLexerWalker& _walker)
			: walker(_walker)
			, currentState(_walker.GetStartState())
		{
		}
		
		RegexLexerColorizer::RegexLexerColorizer(const RegexLexerColorizer& colorizer)
			: walker(colorizer.walker)
			, currentState(colorizer.currentState)
		{
		}
		
		RegexLexerColorizer::~RegexLexerColorizer()
		{
		}
		
		void RegexLexerColorizer::Reset(vint state)
		{
			currentState = state;
		}
		
		void RegexLexerColorizer::Pass(wchar_t input)
		{
			currentState = walker.Walk(input, currentState);
		}
		
		vint RegexLexerColorizer::GetStartState()const
		{
			return walker.GetStartState();
		}
		
		vint RegexLexerColorizer::GetCurrentState()const
		{
			return currentState;
		}
		
		void RegexLexerColorizer::Colorize(const wchar_t* input, vint length, TokenProc tokenProc, void* tokenProcArgument)
		{
			vint start = 0;
			vint stop = 0;
			vint state = -1;
			vint token = -1;
			
			vint index = 0;
			vint currentToken = -1;
			bool finalState = false;
			bool previousTokenStop = false;
			
			while (index < length)
			{
				currentToken = -1;
				finalState = false;
				previousTokenStop = false;
				walker.Walk(input[index], currentState, currentToken, finalState, previousTokenStop);
				
				if (previousTokenStop)
				{
					vint tokenLength = stop - start;
					
					if (tokenLength > 0)
					{
						tokenProc(tokenProcArgument, start, tokenLength, token);
						currentState = state;
						start = stop;
						index = stop - 1;
						state = -1;
						token = -1;
						finalState = false;
					}
					else
						if (stop < index)
						{
							stop = index + 1;
							tokenProc(tokenProcArgument, start, stop - start, -1);
							start = index + 1;
							state = -1;
							token = -1;
						}
				}
				
				if (finalState)
				{
					stop = index + 1;
					state = currentState;
					token = currentToken;
				}
				
				index++;
			}
			
			if (start < length)
			{
				if (finalState)
				{
					tokenProc(tokenProcArgument, start, length - start, token);
				}
				else
				{
					tokenProc(tokenProcArgument, start, length - start, walker.GetRelatedToken(currentState));
				}
			}
		}
		
		/***********************************************************************
		RegexLexer
		***********************************************************************/
		
		RegexLexer::RegexLexer(const collections::IEnumerable<WString>& tokens)
			: pure(0)
		{
			//构造所有DFA
			List<Expression::Ref> expressions;
			List<Automaton::Ref> dfas;
			CharRange::List subsets;
			Ptr<IEnumerator<WString>> enumerator = tokens.CreateEnumerator();
			
			while (enumerator->Next())
			{
				const WString& code = enumerator->Current();
				
				RegexExpression::Ref regex = ParseRegexExpression(code);
				Expression::Ref expression = regex->Merge();
				expression->CollectCharSet(subsets);
				expressions.Add(expression);
			}
			
			for (vint i = 0; i < expressions.Count(); i++)
			{
				Dictionary<State*, State*> nfaStateMap;
				Group<State*, State*> dfaStateMap;
				Expression::Ref expression = expressions[i];
				expression->ApplyCharSet(subsets);
				Automaton::Ref eNfa = expression->GenerateEpsilonNfa();
				Automaton::Ref nfa = EpsilonNfaToNfa(eNfa, PureEpsilonChecker, nfaStateMap);
				Automaton::Ref dfa = NfaToDfa(nfa, dfaStateMap);
				dfas.Add(dfa);
			}
			
			//为每一个DFA设置标记
			for (vint i = 0; i < dfas.Count(); i++)
			{
				Automaton::Ref dfa = dfas[i];
				
				for (vint j = 0; j < dfa->states.Count(); j++)
				{
					if (dfa->states[j]->finalState)
					{
						dfa->states[j]->userData = (void*)i;
					}
					else
					{
						dfa->states[j]->userData = (void*)dfas.Count();
					}
				}
			}
			
			//将DFA组合成大的e-NFA
			Automaton::Ref bigEnfa = new Automaton;
			
			for (vint i = 0; i < dfas.Count(); i++)
			{
				CopyFrom(bigEnfa->states, dfas[i]->states);
				CopyFrom(bigEnfa->transitions, dfas[i]->transitions);
			}
			
			bigEnfa->startState = bigEnfa->NewState();
			
			for (vint i = 0; i < dfas.Count(); i++)
			{
				bigEnfa->NewEpsilon(bigEnfa->startState, dfas[i]->startState);
			}
			
			//转换成DFA
			Dictionary<State*, State*> nfaStateMap;
			Group<State*, State*> dfaStateMap;
			Automaton::Ref bigNfa = EpsilonNfaToNfa(bigEnfa, PureEpsilonChecker, nfaStateMap);
			
			for (vint i = 0; i < nfaStateMap.Keys().Count(); i++)
			{
				void* userData = nfaStateMap.Values().Get(i)->userData;
				nfaStateMap.Keys()[i]->userData = userData;
			}
			
			Automaton::Ref bigDfa = NfaToDfa(bigNfa, dfaStateMap);
			
			for (vint i = 0; i < dfaStateMap.Keys().Count(); i++)
			{
				void* userData = dfaStateMap.GetByIndex(i).Get(0)->userData;
				
				for (vint j = 1; j < dfaStateMap.GetByIndex(i).Count(); j++)
				{
					void* newData = dfaStateMap.GetByIndex(i).Get(j)->userData;
					
					if (userData > newData)
					{
						userData = newData;
					}
				}
				
				dfaStateMap.Keys()[i]->userData = userData;
			}
			
			//构造状态机
			pure = new PureInterpretor(bigDfa, subsets);
			stateTokens.Resize(bigDfa->states.Count());
			
			for (vint i = 0; i < stateTokens.Count(); i++)
			{
				void* userData = bigDfa->states[i]->userData;
				stateTokens[i] = (vint)userData;
			}
		}
		
		RegexLexer::~RegexLexer()
		{
			if (pure)
			{
				delete pure;
			}
		}
		
		RegexTokens RegexLexer::Parse(const WString& code, vint codeIndex)const
		{
			pure->PrepareForRelatedFinalStateTable();
			return RegexTokens(pure, stateTokens, code, codeIndex);
		}
		
		RegexLexerWalker RegexLexer::Walk()const
		{
			pure->PrepareForRelatedFinalStateTable();
			return RegexLexerWalker(pure, stateTokens);
		}
		
		RegexLexerColorizer RegexLexer::Colorize()const
		{
			return RegexLexerColorizer(Walk());
		}
	}
}

// #include "Threading.h"
// #include "Collections/List.h"
#ifdef VCZH_MSVC
#include <Windows.h>

namespace vl
{
	using namespace threading_internal;
	using namespace collections;
	
	/***********************************************************************
	WaitableObject
	***********************************************************************/
	
	namespace threading_internal
	{
		struct WaitableData
		{
			HANDLE			handle;
			
			WaitableData(HANDLE _handle)
				: handle(_handle)
			{
			}
		};
	}
	
	WaitableObject::WaitableObject()
		: waitableData(0)
	{
	}
	
	void WaitableObject::SetData(threading_internal::WaitableData* data)
	{
		waitableData = data;
	}
	
	bool WaitableObject::IsCreated()
	{
		return waitableData != 0;
	}
	
	bool WaitableObject::Wait()
	{
		return WaitForTime(INFINITE);
	}
	
	bool WaitableObject::WaitForTime(vint ms)
	{
		if (IsCreated())
		{
			if (WaitForSingleObject(waitableData->handle, (DWORD)ms) == WAIT_OBJECT_0)
			{
				return true;
			}
		}
		
		return false;
	}
	
	bool WaitableObject::WaitAll(WaitableObject** objects, vint count)
	{
		Array<HANDLE> handles(count);
		
		for (vint i = 0; i < count; i++)
		{
			handles[i] = objects[i]->waitableData->handle;
		}
		
		DWORD result = WaitForMultipleObjects((DWORD)count, &handles[0], TRUE, INFINITE);
		return result == WAIT_OBJECT_0 || result == WAIT_ABANDONED_0;
		
	}
	
	bool WaitableObject::WaitAllForTime(WaitableObject** objects, vint count, vint ms)
	{
		Array<HANDLE> handles(count);
		
		for (vint i = 0; i < count; i++)
		{
			handles[i] = objects[i]->waitableData->handle;
		}
		
		DWORD result = WaitForMultipleObjects((DWORD)count, &handles[0], TRUE, (DWORD)ms);
		return result == WAIT_OBJECT_0 || result == WAIT_ABANDONED_0;
	}
	
	vint WaitableObject::WaitAny(WaitableObject** objects, vint count, bool* abandoned)
	{
		Array<HANDLE> handles(count);
		
		for (vint i = 0; i < count; i++)
		{
			handles[i] = objects[i]->waitableData->handle;
		}
		
		DWORD result = WaitForMultipleObjects((DWORD)count, &handles[0], FALSE, INFINITE);
		
		if (WAIT_OBJECT_0 <= result && result < WAIT_OBJECT_0 + count)
		{
			*abandoned = false;
			return result - WAIT_OBJECT_0;
		}
		else
			if (WAIT_ABANDONED_0 <= result && result < WAIT_ABANDONED_0 + count)
			{
				*abandoned = true;
				return result - WAIT_ABANDONED_0;
			}
			else
			{
				return -1;
			}
	}
	
	vint WaitableObject::WaitAnyForTime(WaitableObject** objects, vint count, vint ms, bool* abandoned)
	{
		Array<HANDLE> handles(count);
		
		for (vint i = 0; i < count; i++)
		{
			handles[i] = objects[i]->waitableData->handle;
		}
		
		DWORD result = WaitForMultipleObjects((DWORD)count, &handles[0], FALSE, (DWORD)ms);
		
		if (WAIT_OBJECT_0 <= result && result < WAIT_OBJECT_0 + count)
		{
			*abandoned = false;
			return result - WAIT_OBJECT_0;
		}
		else
			if (WAIT_ABANDONED_0 <= result && result < WAIT_ABANDONED_0 + count)
			{
				*abandoned = true;
				return result - WAIT_ABANDONED_0;
			}
			else
			{
				return -1;
			}
	}
	
	/***********************************************************************
	Thread
	***********************************************************************/
	
	namespace threading_internal
	{
		struct ThreadData : public WaitableData
		{
			DWORD						id;
			
			ThreadData()
				: WaitableData(NULL)
			{
				id = -1;
			}
		};
		
		class ProceduredThread : public Thread
		{
		 private:
			Thread::ThreadProcedure		procedure;
			void*						argument;
			bool						deleteAfterStopped;
			
		 protected:
			void Run()
			{
				bool deleteAfterStopped = this->deleteAfterStopped;
				ThreadLocalStorage::FixStorages();
				
				try
				{
					procedure(this, argument);
					threadState = Thread::Stopped;
					ThreadLocalStorage::ClearStorages();
				}
				catch (...)
				{
					ThreadLocalStorage::ClearStorages();
					throw;
				}
				
				if (deleteAfterStopped)
				{
					delete this;
				}
			}
		 public:
			ProceduredThread(Thread::ThreadProcedure _procedure, void* _argument, bool _deleteAfterStopped)
				: procedure(_procedure)
				, argument(_argument)
				, deleteAfterStopped(_deleteAfterStopped)
			{
			}
		};
		
		// 		class LambdaThread : public Thread
		// 		{
		// 		private:
		// 			Func<void()>				procedure;
		// 			bool						deleteAfterStopped;
		//
		// 		protected:
		// 			void Run()
		// 			{
		// 				bool deleteAfterStopped = this->deleteAfterStopped;
		// 				ThreadLocalStorage::FixStorages();
		// 				try
		// 				{
		// 					procedure();
		// 					threadState=Thread::Stopped;
		// 					ThreadLocalStorage::ClearStorages();
		// 				}
		// 				catch (...)
		// 				{
		// 					ThreadLocalStorage::ClearStorages();
		// 					throw;
		// 				}
		// 				if(deleteAfterStopped)
		// 				{
		// 					delete this;
		// 				}
		// 			}
		// 		public:
		// 			LambdaThread(const Func<void()>& _procedure, bool _deleteAfterStopped)
		// 				:procedure(_procedure)
		// 				,deleteAfterStopped(_deleteAfterStopped)
		// 			{
		// 			}
		// 		};
	}
	
	void InternalThreadProc(Thread* thread)
	{
		thread->Run();
	}
	
	DWORD WINAPI InternalThreadProcWrapper(LPVOID lpParameter)
	{
		InternalThreadProc((Thread*)lpParameter);
		return 0;
	}
	
	Thread::Thread()
	{
		internalData = new ThreadData;
		internalData->handle = CreateThread(NULL, 0, InternalThreadProcWrapper, this, CREATE_SUSPENDED, &internalData->id);
		threadState = Thread::NotStarted;
		SetData(internalData);
	}
	
	Thread::~Thread()
	{
		if (internalData)
		{
			Stop();
			CloseHandle(internalData->handle);
			delete internalData;
		}
	}
	
	Thread* Thread::CreateAndStart(ThreadProcedure procedure, void* argument, bool deleteAfterStopped)
	{
		if (procedure)
		{
			Thread* thread = new ProceduredThread(procedure, argument, deleteAfterStopped);
			
			if (thread->Start())
			{
				return thread;
			}
			else
			{
				delete thread;
			}
		}
		
		return 0;
	}
	
	// 	Thread* Thread::CreateAndStart(const Func<void()>& procedure, bool deleteAfterStopped)
	// 	{
	// 		Thread* thread=new LambdaThread(procedure, deleteAfterStopped);
	// 		if(thread->Start())
	// 		{
	// 			return thread;
	// 		}
	// 		else
	// 		{
	// 			delete thread;
	// 		}
	// 		return 0;
	// 	}
	
	void Thread::Sleep(vint ms)
	{
		::Sleep((DWORD)ms);
	}
	
	
	vint Thread::GetCPUCount()
	{
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		return info.dwNumberOfProcessors;
	}
	
	vint Thread::GetCurrentThreadId()
	{
		return (vint)::GetCurrentThreadId();
	}
	
	bool Thread::Start()
	{
		if (threadState == Thread::NotStarted && internalData->handle != NULL)
		{
			if (ResumeThread(internalData->handle) != -1)
			{
				threadState = Thread::Running;
				return true;
			}
		}
		
		return false;
	}
	
	bool Thread::Stop()
	{
		if (internalData->handle != NULL)
		{
			if (SuspendThread(internalData->handle) != -1)
			{
				threadState = Thread::Stopped;
				return true;
			}
		}
		
		return false;
	}
	
	Thread::ThreadState Thread::GetState()
	{
		return threadState;
	}
	
	void Thread::SetCPU(vint index)
	{
		SetThreadAffinityMask(internalData->handle, ((vint)1 << index));
	}
	
	/***********************************************************************
	Mutex
	***********************************************************************/
	
	namespace threading_internal
	{
		struct MutexData : public WaitableData
		{
			MutexData(HANDLE _handle)
				: WaitableData(_handle)
			{
			}
		};
	}
	
	Mutex::Mutex()
		: internalData(0)
	{
	}
	
	Mutex::~Mutex()
	{
		if (internalData)
		{
			CloseHandle(internalData->handle);
			delete internalData;
		}
	}
	
	bool Mutex::Create(bool owned, const WString& name)
	{
		if (IsCreated())
		{
			return false;
		}
		
		BOOL aOwned = owned ? TRUE : FALSE;
		LPCTSTR aName = name == L"" ? NULL : name.Buffer();
		HANDLE handle = CreateMutex(NULL, aOwned, aName);
		
		if (handle)
		{
			internalData = new MutexData(handle);
			SetData(internalData);
		}
		
		return IsCreated();
	}
	
	bool Mutex::Open(bool inheritable, const WString& name)
	{
		if (IsCreated())
		{
			return false;
		}
		
		BOOL aInteritable = inheritable ? TRUE : FALSE;
		HANDLE handle = OpenMutex(SYNCHRONIZE, aInteritable, name.Buffer());
		
		if (handle)
		{
			internalData = new MutexData(handle);
			SetData(internalData);
		}
		
		return IsCreated();
	}
	
	bool Mutex::Release()
	{
		if (IsCreated())
		{
			return ReleaseMutex(internalData->handle) != 0;
		}
		
		return false;
	}
	
	/***********************************************************************
	Semaphore
	***********************************************************************/
	
	namespace threading_internal
	{
		struct SemaphoreData : public WaitableData
		{
			SemaphoreData(HANDLE _handle)
				: WaitableData(_handle)
			{
			}
		};
	}
	
	Semaphore::Semaphore()
		: internalData(0)
	{
	}
	
	Semaphore::~Semaphore()
	{
		if (internalData)
		{
			CloseHandle(internalData->handle);
			delete internalData;
		}
	}
	
	bool Semaphore::Create(vint initialCount, vint maxCount, const WString& name)
	{
		if (IsCreated())
		{
			return false;
		}
		
		LONG aInitial = (LONG)initialCount;
		LONG aMax = (LONG)maxCount;
		LPCTSTR aName = name == L"" ? NULL : name.Buffer();
		HANDLE handle = CreateSemaphore(NULL, aInitial, aMax, aName);
		
		if (handle)
		{
			internalData = new SemaphoreData(handle);
			SetData(internalData);
		}
		
		return IsCreated();
	}
	
	bool Semaphore::Open(bool inheritable, const WString& name)
	{
		if (IsCreated())
		{
			return false;
		}
		
		BOOL aInteritable = inheritable ? TRUE : FALSE;
		HANDLE handle = OpenSemaphore(SYNCHRONIZE, aInteritable, name.Buffer());
		
		if (handle)
		{
			internalData = new SemaphoreData(handle);
			SetData(internalData);
		}
		
		return IsCreated();
	}
	
	bool Semaphore::Release()
	{
		if (IsCreated())
		{
			return Release(1) != -1;
		}
		
		return false;
	}
	
	vint Semaphore::Release(vint count)
	{
		if (IsCreated())
		{
			LONG previous = -1;
			
			if (ReleaseSemaphore(internalData->handle, (LONG)count, &previous) != 0)
			{
				return (vint)previous;
			}
		}
		
		return -1;
	}
	
	/***********************************************************************
	EventObject
	***********************************************************************/
	
	namespace threading_internal
	{
		struct EventData : public WaitableData
		{
			EventData(HANDLE _handle)
				: WaitableData(_handle)
			{
			}
		};
	}
	
	EventObject::EventObject()
		: internalData(0)
	{
	}
	
	EventObject::~EventObject()
	{
		if (internalData)
		{
			CloseHandle(internalData->handle);
			delete internalData;
		}
	}
	
	bool EventObject::CreateAutoUnsignal(bool signaled, const WString& name)
	{
		if (IsCreated())
		{
			return false;
		}
		
		BOOL aSignaled = signaled ? TRUE : FALSE;
		LPCTSTR aName = name == L"" ? NULL : name.Buffer();
		HANDLE handle = CreateEvent(NULL, FALSE, aSignaled, aName);
		
		if (handle)
		{
			internalData = new EventData(handle);
			SetData(internalData);
		}
		
		return IsCreated();
	}
	
	bool EventObject::CreateManualUnsignal(bool signaled, const WString& name)
	{
		if (IsCreated())
		{
			return false;
		}
		
		BOOL aSignaled = signaled ? TRUE : FALSE;
		LPCTSTR aName = name == L"" ? NULL : name.Buffer();
		HANDLE handle = CreateEvent(NULL, TRUE, aSignaled, aName);
		
		if (handle)
		{
			internalData = new EventData(handle);
			SetData(internalData);
		}
		
		return IsCreated();
	}
	
	bool EventObject::Open(bool inheritable, const WString& name)
	{
		if (IsCreated())
		{
			return false;
		}
		
		BOOL aInteritable = inheritable ? TRUE : FALSE;
		HANDLE handle = OpenEvent(SYNCHRONIZE, aInteritable, name.Buffer());
		
		if (handle)
		{
			internalData = new EventData(handle);
			SetData(internalData);
		}
		
		return IsCreated();
	}
	
	bool EventObject::Signal()
	{
		if (IsCreated())
		{
			return SetEvent(internalData->handle) != 0;
		}
		
		return false;
	}
	
	bool EventObject::Unsignal()
	{
		if (IsCreated())
		{
			return ResetEvent(internalData->handle) != 0;
		}
		
		return false;
	}
	
	/***********************************************************************
	ThreadPoolLite
	***********************************************************************/
	
	struct ThreadPoolQueueProcArgument
	{
		void(*proc)(void*);
		void* argument;
	};
	
	DWORD WINAPI ThreadPoolQueueProc(void* argument)
	{
		Ptr<ThreadPoolQueueProcArgument> proc = (ThreadPoolQueueProcArgument*)argument;
		ThreadLocalStorage::FixStorages();
		
		try
		{
			proc->proc(proc->argument);
			ThreadLocalStorage::ClearStorages();
		}
		catch (...)
		{
			ThreadLocalStorage::ClearStorages();
		}
		
		return 0;
	}
	
	// 		DWORD WINAPI ThreadPoolQueueFunc(void* argument)
	// 		{
	// 			Ptr<Func<void()>> proc=(Func<void()>*)argument;
	// 			ThreadLocalStorage::FixStorages();
	// 			try
	// 			{
	// 				(*proc.Obj())();
	// 				ThreadLocalStorage::ClearStorages();
	// 			}
	// 			catch (...)
	// 			{
	// 				ThreadLocalStorage::ClearStorages();
	// 			}
	// 			return 0;
	// 		}
	
	ThreadPoolLite::ThreadPoolLite()
	{
	}
	
	ThreadPoolLite::~ThreadPoolLite()
	{
	}
	
	bool ThreadPoolLite::Queue(void(*proc)(void*), void* argument)
	{
		ThreadPoolQueueProcArgument* p = new ThreadPoolQueueProcArgument;
		p->proc = proc;
		p->argument = argument;
		
		if (QueueUserWorkItem(&ThreadPoolQueueProc, p, WT_EXECUTEDEFAULT))
		{
			return true;
		}
		else
		{
			delete p;
			return false;
		}
	}
	
	// 		bool ThreadPoolLite::Queue(const Func<void()>& proc)
	// 		{
	// 			Func<void()>* p=new Func<void()>(proc);
	// 			if(QueueUserWorkItem(&ThreadPoolQueueFunc, p, WT_EXECUTEDEFAULT))
	// 			{
	// 				return true;
	// 			}
	// 			else
	// 			{
	// 				delete p;
	// 				return false;
	// 			}
	// 		}
	
	/***********************************************************************
	CriticalSection
	***********************************************************************/
	
	namespace threading_internal
	{
		struct CriticalSectionData
		{
			CRITICAL_SECTION		criticalSection;
		};
	}
	
	CriticalSection::Scope::Scope(CriticalSection& _criticalSection)
		: criticalSection(&_criticalSection)
	{
		criticalSection->Enter();
	}
	
	CriticalSection::Scope::~Scope()
	{
		criticalSection->Leave();
	}
	
	CriticalSection::CriticalSection()
	{
		internalData = new CriticalSectionData;
		InitializeCriticalSection(&internalData->criticalSection);
	}
	
	CriticalSection::~CriticalSection()
	{
		DeleteCriticalSection(&internalData->criticalSection);
		delete internalData;
	}
	
	bool CriticalSection::TryEnter()
	{
		return TryEnterCriticalSection(&internalData->criticalSection) != 0;
	}
	
	void CriticalSection::Enter()
	{
		EnterCriticalSection(&internalData->criticalSection);
	}
	
	void CriticalSection::Leave()
	{
		LeaveCriticalSection(&internalData->criticalSection);
	}
	
	/***********************************************************************
	ReaderWriterLock
	***********************************************************************/
	
	namespace threading_internal
	{
		struct ReaderWriterLockData
		{
			SRWLOCK			lock;
		};
	}
	
	ReaderWriterLock::ReaderScope::ReaderScope(ReaderWriterLock& _lock)
		: lock(&_lock)
	{
		lock->EnterReader();
	}
	
	ReaderWriterLock::ReaderScope::~ReaderScope()
	{
		lock->LeaveReader();
	}
	
	ReaderWriterLock::WriterScope::WriterScope(ReaderWriterLock& _lock)
		: lock(&_lock)
	{
		lock->EnterWriter();
	}
	
	ReaderWriterLock::WriterScope::~WriterScope()
	{
		lock->LeaveWriter();
	}
	
	ReaderWriterLock::ReaderWriterLock()
		: internalData(new threading_internal::ReaderWriterLockData)
	{
		InitializeSRWLock(&internalData->lock);
	}
	
	ReaderWriterLock::~ReaderWriterLock()
	{
		delete internalData;
	}
	
	bool ReaderWriterLock::TryEnterReader()
	{
#if _MSC_VER > 1700
		return TryAcquireSRWLockShared(&internalData->lock) != 0;
#else
		return false;
#endif
	}
	
	void ReaderWriterLock::EnterReader()
	{
		AcquireSRWLockShared(&internalData->lock);
	}
	
	void ReaderWriterLock::LeaveReader()
	{
		ReleaseSRWLockShared(&internalData->lock);
	}
	
	bool ReaderWriterLock::TryEnterWriter()
	{
#if _MSC_VER > 1700
		return TryAcquireSRWLockExclusive(&internalData->lock) != 0;
#else
		return false;
#endif
	}
	
	void ReaderWriterLock::EnterWriter()
	{
		AcquireSRWLockExclusive(&internalData->lock);
	}
	
	void ReaderWriterLock::LeaveWriter()
	{
		ReleaseSRWLockExclusive(&internalData->lock);
	}
	
	/***********************************************************************
	ConditionVariable
	***********************************************************************/
	
	namespace threading_internal
	{
		struct ConditionVariableData
		{
			CONDITION_VARIABLE			variable;
		};
	}
	
	ConditionVariable::ConditionVariable()
		: internalData(new threading_internal::ConditionVariableData)
	{
		InitializeConditionVariable(&internalData->variable);
	}
	
	ConditionVariable::~ConditionVariable()
	{
		delete internalData;
	}
	
	bool ConditionVariable::SleepWith(CriticalSection& cs)
	{
		return SleepConditionVariableCS(&internalData->variable, &cs.internalData->criticalSection, INFINITE) != 0;
	}
	
	bool ConditionVariable::SleepWithForTime(CriticalSection& cs, vint ms)
	{
		return SleepConditionVariableCS(&internalData->variable, &cs.internalData->criticalSection, (DWORD)ms) != 0;
	}
	
	bool ConditionVariable::SleepWithReader(ReaderWriterLock& lock)
	{
		return SleepConditionVariableSRW(&internalData->variable, &lock.internalData->lock, INFINITE, CONDITION_VARIABLE_LOCKMODE_SHARED) != 0;
	}
	
	bool ConditionVariable::SleepWithReaderForTime(ReaderWriterLock& lock, vint ms)
	{
		return SleepConditionVariableSRW(&internalData->variable, &lock.internalData->lock, (DWORD)ms, CONDITION_VARIABLE_LOCKMODE_SHARED) != 0;
	}
	
	bool ConditionVariable::SleepWithWriter(ReaderWriterLock& lock)
	{
		return SleepConditionVariableSRW(&internalData->variable, &lock.internalData->lock, INFINITE, 0) != 0;
	}
	
	bool ConditionVariable::SleepWithWriterForTime(ReaderWriterLock& lock, vint ms)
	{
		return SleepConditionVariableSRW(&internalData->variable, &lock.internalData->lock, (DWORD)ms, 0) != 0;
	}
	
	void ConditionVariable::WakeOnePending()
	{
		WakeConditionVariable(&internalData->variable);
	}
	
	void ConditionVariable::WakeAllPendings()
	{
		WakeAllConditionVariable(&internalData->variable);
	}
	
	/***********************************************************************
	SpinLock
	***********************************************************************/
	
	SpinLock::Scope::Scope(SpinLock& _spinLock)
		: spinLock(&_spinLock)
	{
		spinLock->Enter();
	}
	
	SpinLock::Scope::~Scope()
	{
		spinLock->Leave();
	}
	
	SpinLock::SpinLock()
		: token(0)
	{
	}
	
	SpinLock::~SpinLock()
	{
	}
	
	bool SpinLock::TryEnter()
	{
		return _InterlockedExchange(&token, 1) == 0;
	}
	
	void SpinLock::Enter()
	{
		while (_InterlockedCompareExchange(&token, 1, 0) != 0)
		{
			while (token != 0)
			{
				_mm_pause();
			}
		}
	}
	
	void SpinLock::Leave()
	{
		_InterlockedExchange(&token, 0);
	}
	
	/***********************************************************************
	ThreadLocalStorage
	***********************************************************************/
	
#define KEY ((DWORD&)key)
	
	ThreadLocalStorage::ThreadLocalStorage(Destructor _destructor)
		: destructor(_destructor), disposed(false)
	{
		//static_assert(sizeof(key) >= sizeof(DWORD), "ThreadLocalStorage's key storage is not large enouth.");
		PushStorage(this);
		KEY = TlsAlloc();
		CHECK_ERROR(KEY != TLS_OUT_OF_INDEXES, L"vl::ThreadLocalStorage::ThreadLocalStorage()#Failed to alloc new thread local storage index.");
	}
	
	ThreadLocalStorage::~ThreadLocalStorage()
	{
		TlsFree(KEY);
	}
	
	void* ThreadLocalStorage::Get()
	{
		CHECK_ERROR(!disposed, L"vl::ThreadLocalStorage::Get()#Cannot access a disposed ThreadLocalStorage.");
		return TlsGetValue(KEY);
	}
	
	void ThreadLocalStorage::Set(void* data)
	{
		CHECK_ERROR(!disposed, L"vl::ThreadLocalStorage::Set()#Cannot access a disposed ThreadLocalStorage.");
		TlsSetValue(KEY, data);
	}
	
#undef KEY
}
#endif

/***********************************************************************
ThreadLocalStorage Common Implementations
***********************************************************************/

namespace vl
{
	void ThreadLocalStorage::Clear()
	{
		CHECK_ERROR(!disposed, L"vl::ThreadLocalStorage::Clear()#Cannot access a disposed ThreadLocalStorage.");
		
		if (destructor)
		{
			if (void* data = Get())
			{
				destructor(data);
			}
		}
		
		Set(NULL);
	}
	
	void ThreadLocalStorage::Dispose()
	{
		CHECK_ERROR(!disposed, L"vl::ThreadLocalStorage::Dispose()#Cannot access a disposed ThreadLocalStorage.");
		Clear();
		disposed = true;
	}
	
	struct TlsStorageLink
	{
		TlsStorageLink() : storage(NULL), next(NULL)
		{}
		ThreadLocalStorage*		storage /*= NULL*/;
		TlsStorageLink*			next /*= NULL*/;
	};
	
	volatile bool				tlsFixed = false;
	TlsStorageLink*				tlsHead = NULL;
	TlsStorageLink**			tlsTail = &tlsHead;
	
	void ThreadLocalStorage::PushStorage(ThreadLocalStorage* storage)
	{
		CHECK_ERROR(!tlsFixed, L"vl::ThreadLocalStorage::PushStorage(ThreadLocalStorage*)#Cannot create new ThreadLocalStorage instance after calling ThreadLocalStorage::FixStorages().");
		TlsStorageLink*	 link = new TlsStorageLink;
		link->storage = storage;
		*tlsTail = link;
		tlsTail = &link->next;
	}
	
	void ThreadLocalStorage::FixStorages()
	{
		tlsFixed = true;
	}
	
	void ThreadLocalStorage::ClearStorages()
	{
		FixStorages();
		TlsStorageLink* current = tlsHead;
		
		while (current)
		{
			current->storage->Clear();
			current = current->next;
		}
	}
	
	void ThreadLocalStorage::DisposeStorages()
	{
		FixStorages();
		TlsStorageLink*	 current = tlsHead;
		tlsHead = NULL;
		tlsTail = NULL;
		
		while (current)
		{
			current->storage->Dispose();
			
			TlsStorageLink*	 temp = current;
			current = current->next;
			delete temp;
		}
	}
}

// #include "UnitTest.h"
// #include "../Console.h"
// #if defined VCZH_MSVC
// #include "../Threading.h"
// #endif

namespace vl
{
	namespace unittest
	{
		using namespace vl::console;
		
		/***********************************************************************
		UnitTest
		***********************************************************************/
		
#if defined VCZH_MSVC
		SpinLock spinLockUnitTest;
#endif
		
		void UnitTest::PrintMessage(const WString& string)
		{
#if defined VCZH_MSVC
			SpinLock::Scope scope(spinLockUnitTest);
#endif
			Console::SetColor(false, true, false, true);
			Console::WriteLine(string);
			Console::SetColor(true, true, true, false);
		}
		
		void UnitTest::PrintInfo(const WString& string)
		{
#if defined VCZH_MSVC
			SpinLock::Scope scope(spinLockUnitTest);
#endif
			Console::SetColor(true, true, true, true);
			Console::WriteLine(string);
			Console::SetColor(true, true, true, false);
		}
		
		void UnitTest::PrintError(const WString& string)
		{
#if defined VCZH_MSVC
			SpinLock::Scope scope(spinLockUnitTest);
#endif
			Console::SetColor(true, false, false, true);
			Console::WriteLine(string);
			Console::SetColor(true, true, true, false);
		}
		
		struct UnitTestLink
		{
			UnitTestLink() : testProc(NULL), next(NULL) {};
			UnitTest::TestProc			testProc/* = NULL*/;
			UnitTestLink*				next/* = NULL*/;
		};
		UnitTestLink*					testHead = NULL;
		UnitTestLink**					testTail = &testHead;
		
		void UnitTest::PushTest(TestProc testProc)
		{
			UnitTestLink* link = new UnitTestLink;
			link->testProc = testProc;
			*testTail = link;
			testTail = &link->next;
		}
		
		void UnitTest::RunAndDisposeTests()
		{
			UnitTestLink* current = testHead;
			testHead = NULL;
			testTail = NULL;
			
			while (current)
			{
				current->testProc();
				UnitTestLink* temp = current;
				current = current->next;
				delete temp;
			}
		}
	}
}
