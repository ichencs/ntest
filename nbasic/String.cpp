#include <stdlib.h>
#include "String.h"
#if defined VCZH_MSVC
#include <Windows.h>
// #elif defined VCZH_GCC
// #include <stdio.h>
// #include <ctype.h>
// #include <wctype.h>
// #define _strtoi64 strtoll
// #define _strtoui64 strtoull
// #define _wcstoi64 wcstoll
// #define _wcstoui64 wcstoull
#endif
#include <stdio.h>
#include <stdarg.h>
namespace vl
{
	__pragma(warning(disable: 4996))
	
	
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
#elif defined VCZH_GCC
		return wcstombs(a, w, chars - 1) + 1;
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
	
	vint _wtoUtf8(const wchar_t* w, char* u, vint chars)
	{
		return WideCharToMultiByte(CP_UTF8, 0, w, -1, (char*)u, (int)(u ? chars : 0), 0, 0);
	}
	
	UString wtoUtf8(const WString& string)
	{
		vint len = _wtoUtf8(string.Buffer(), 0, 0);
		char* buffer = new char[len];
		memset(buffer, 0, len * sizeof(*buffer));
		_wtoUtf8(string.Buffer(), buffer, (int)len);
		UString s = buffer;
		delete[] buffer;
		return s;
	}
	
	vint _utf8tow(const char* u, wchar_t* w, vint chars)
	{
		return MultiByteToWideChar(CP_UTF8, 0, (char*)u, -1, w, (int)(w ? chars : 0));
	}
	
	WString utf8tow(const UString& string)
	{
		vint len = _utf8tow(string.Buffer(), 0, 0);
		wchar_t* buffer = new wchar_t[len];
		memset(buffer, 0, len * sizeof(*buffer));
		_utf8tow(string.Buffer(), buffer, (int)len);
		WString s = buffer;
		delete[] buffer;
		return s;
	}
	
	vint _atow(const char* a, wchar_t* w, vint chars)
	{
#if defined VCZH_MSVC
		return MultiByteToWideChar(CP_THREAD_ACP, 0, a, -1, w, (int)(w ? chars : 0));
#elif defined VCZH_GCC
		return mbstowcs(w, a, chars - 1) + 1;
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
	
	WString wformat(const wchar_t* pszFormat, ...)
	{
		WString string;
		va_list argList;
		va_start(argList, pszFormat);
		{
			wchar_t* pszBuffer = NULL;
			int nlen = -1;
			{
				nlen = _vscwprintf(pszFormat, argList);
				pszBuffer = (wchar_t*)malloc((nlen + 1) * sizeof(wchar_t));
				vswprintf(pszBuffer, pszFormat, argList);
			}
			if (nlen > 0 && pszBuffer)
			{
				string = pszBuffer;
				free(pszBuffer);
			}
		}
		va_end(argList);
		return string;
	}
	
	AString aformat(const char* pszFormat, ...)
	{
		AString string;
		va_list argList;
		va_start(argList, pszFormat);
		{
			char* pszBuffer = NULL;
			int nlen = -1;
			{
				nlen = _vscprintf(pszFormat, argList);
				pszBuffer = (char*)malloc((nlen + 1) * sizeof(char));
				vsprintf(pszBuffer, pszFormat, argList);
			}
			if (nlen > 0 && pszBuffer)
			{
				string = pszBuffer;
				free(pszBuffer);
			}
		}
		va_end(argList);
		return string;
	}
	
}
