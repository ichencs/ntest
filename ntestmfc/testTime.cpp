#include "stdafx.h"
#include "testTime.h"


testTime::testTime()
{
	current = CTime::GetCurrentTime();
}


testTime::~testTime()
{
}

CTime& testTime::getCurrentTime()
{
	current = CTime::GetCurrentTime();
	return current;
}

CString testTime::toStringTime(CTime& t)
{
	CString s = t.Format(_T("%Y-%m-%d %H:%M:%S"));
// 	CString s = t.Format(_T("%Y-%m-%d %H:%M:%S %W-%A"));
	return s;
}

CString testTime::toStringTime()
{
	return toStringTime(current);
}

CString testTime::toStringTime2(CTime& t)
{
	CString s = t.Format("%c");
	return s;
}

FILETIME testTime::toFileTime(CTime& t)
{
	SYSTEMTIME timeDest;
	t.GetAsSystemTime(timeDest);
	FILETIME fileTime;
	::SystemTimeToFileTime(&timeDest, &fileTime);
	return fileTime;
}

FILETIME testTime::toFileTime()
{
	return toFileTime(current);
}

SYSTEMTIME& testTime::toSystemTime(CTime& t)
{
	t.GetAsSystemTime(tm_sys);
	return tm_sys;
}

SYSTEMTIME& testTime::toSystemTime()
{
	return toSystemTime(current);
}

tm& testTime::toGmtTm(CTime& t)
{
	t.GetGmtTm(&tm_gtm);
	return tm_gtm;
}

tm& testTime::toGmtTm()
{
	return toGmtTm(current);
}

tm& testTime::toLocalTm(CTime& t)
{
	t.GetLocalTm(&tm_gtm);
	return tm_gtm;
}

tm& testTime::toLocalTm()
{
	return toLocalTm(current);
}

DBTIMESTAMP& testTime::toDBTimeStamp(CTime& t)
{
	t.GetAsDBTIMESTAMP(tm_dbts);
	return tm_dbts;
}

DBTIMESTAMP& testTime::toDBTimeStamp()
{
	return toDBTimeStamp(current);
}

CTime testTime::current = CTime::GetCurrentTime();

SYSTEMTIME testTime::tm_sys;

tm testTime::tm_gtm;

DBTIMESTAMP testTime::tm_dbts;
