#pragma once

/*
CTime Format
	//参考
	//CString date = time.Format("%Y-%m-%d %H:%M:%S %W-%A");
	格式符号说明
	%a —— 星期（缩写英文），如Fri；
	%A —— 星期（全写英文），如Friday
	%b —— 月份（缩写英文），如Oct
	%B —— 月份（全写英文），如 October
	%c  —— 月/日/年 时:分:秒，如 10/13/06 19:17:17
	%d  —— 日期（1 ~ 31）
	%H  —— 时（24小时制）（0 ~ 23）
	%I    —— 时（12小时制）（0 ~ 12）
	%j    —— 一年当中的第几天，（1 ~ 366）
	%m  —— 月份（数字 1 ~ 12）
	%M  —— 分（0 ~ 59）
	%p  —— 12小时中的A M/PM指示，或者AM，或者PM
	%S  —— 秒（0 ~ 59）
	%U  —— 一年中的第几周，星期日作为每周的第一天（0 ~ 53）
	%w  —— 星期（数字表示，0 ~ 6，0代表星期日）
	%W —— 一年中的第几周，星期一作为每周的第一天（0 ~ 53）
	%x   —— 月/日/年，%c的前半段
*/
class vc15Time
{
public:
	vc15Time();
	~vc15Time();

public:
	static CTime& getCurrentTime();
	static CString toStringTime();
	static CString toStringTime(CTime& t);	//2017-06-07 13:01:48
	static CString toStringTime2(CTime& t);
	
public:
	static FILETIME toFileTime();
	static FILETIME toFileTime(CTime& t);
	static SYSTEMTIME& toSystemTime();
	static SYSTEMTIME& toSystemTime(CTime& t);
	static tm& toGmtTm();
	static tm& toGmtTm(CTime& t);
	static tm& toLocalTm();
	static tm& toLocalTm(CTime& t);
	static DBTIMESTAMP& toDBTimeStamp(CTime& t);
	static DBTIMESTAMP& toDBTimeStamp();
private:
	static CTime current;
	static SYSTEMTIME tm_sys;
	static tm tm_gtm;
	static DBTIMESTAMP tm_dbts;
};

