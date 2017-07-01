#pragma once

/*
CTime Format
	//�ο�
	//CString date = time.Format("%Y-%m-%d %H:%M:%S %W-%A");
	��ʽ����˵��
	%a ���� ���ڣ���дӢ�ģ�����Fri��
	%A ���� ���ڣ�ȫдӢ�ģ�����Friday
	%b ���� �·ݣ���дӢ�ģ�����Oct
	%B ���� �·ݣ�ȫдӢ�ģ����� October
	%c  ���� ��/��/�� ʱ:��:�룬�� 10/13/06 19:17:17
	%d  ���� ���ڣ�1 ~ 31��
	%H  ���� ʱ��24Сʱ�ƣ���0 ~ 23��
	%I    ���� ʱ��12Сʱ�ƣ���0 ~ 12��
	%j    ���� һ�굱�еĵڼ��죬��1 ~ 366��
	%m  ���� �·ݣ����� 1 ~ 12��
	%M  ���� �֣�0 ~ 59��
	%p  ���� 12Сʱ�е�A M/PMָʾ������AM������PM
	%S  ���� �루0 ~ 59��
	%U  ���� һ���еĵڼ��ܣ���������Ϊÿ�ܵĵ�һ�죨0 ~ 53��
	%w  ���� ���ڣ����ֱ�ʾ��0 ~ 6��0���������գ�
	%W ���� һ���еĵڼ��ܣ�����һ��Ϊÿ�ܵĵ�һ�죨0 ~ 53��
	%x   ���� ��/��/�꣬%c��ǰ���
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

