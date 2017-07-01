#include "stdafx.h"
#include "vc15Time.h"


vc15Time::vc15Time()
{
	current = CTime::GetCurrentTime();
}


vc15Time::~vc15Time()
{
}

CTime& vc15Time::getCurrentTime()
{
	current = CTime::GetCurrentTime();
	return current;
}

CString vc15Time::toStringTime(CTime& t)
{
	CString s = t.Format(_T("%Y-%m-%d %H:%M:%S"));
// 	CString s = t.Format(_T("%Y-%m-%d %H:%M:%S %W-%A"));
	return s;
}

CString vc15Time::toStringTime()
{
	return toStringTime(current);
}

CString vc15Time::toStringTime2(CTime& t)
{
	CString s = t.Format("%c");
	return s;
}

FILETIME vc15Time::toFileTime(CTime& t)
{
	SYSTEMTIME timeDest;
	t.GetAsSystemTime(timeDest);
	FILETIME fileTime;
	::SystemTimeToFileTime(&timeDest, &fileTime);
	return fileTime;
}

FILETIME vc15Time::toFileTime()
{
	return toFileTime(current);
}

SYSTEMTIME& vc15Time::toSystemTime(CTime& t)
{
	t.GetAsSystemTime(tm_sys);
	return tm_sys;
}

SYSTEMTIME& vc15Time::toSystemTime()
{
	return toSystemTime(current);
}

tm& vc15Time::toGmtTm(CTime& t)
{
	t.GetGmtTm(&tm_gtm);
	return tm_gtm;
}

tm& vc15Time::toGmtTm()
{
	return toGmtTm(current);
}

tm& vc15Time::toLocalTm(CTime& t)
{
	t.GetLocalTm(&tm_gtm);
	return tm_gtm;
}

tm& vc15Time::toLocalTm()
{
	return toLocalTm(current);
}

DBTIMESTAMP& vc15Time::toDBTimeStamp(CTime& t)
{
	t.GetAsDBTIMESTAMP(tm_dbts);
	return tm_dbts;
}

DBTIMESTAMP& vc15Time::toDBTimeStamp()
{
	return toDBTimeStamp(current);
}

CTime vc15Time::current = CTime::GetCurrentTime();

SYSTEMTIME vc15Time::tm_sys;

tm vc15Time::tm_gtm;

DBTIMESTAMP vc15Time::tm_dbts;
