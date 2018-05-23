#pragma once
#include <afxtempl.h>

class CMyTimer;
typedef CMap<UINT, UINT, CMyTimer*, CMyTimer*> CTimerMap;

class CMyTimer
{
public:
	CMyTimer();
	~CMyTimer();

public:
	//���ö�ʱ����nElapse��ʾʱ������sz��ʾҪ��ʾ������
	void SetMyTimer(UINT nElapse, CString sz);
	//���ٸ�ʵ���Ķ�ʱ��
	void KillMyTimer();
	//�����ʵ���Ķ�ʱ����־ֵ
	UINT m_nTimerID;
	//��̬���ݳ�ԱҪ��ʾ������ 
	CString szContent;
	//��̬���ݳ�Ա��ӳ����࣬���ڱ������еĶ�ʱ����Ϣ
	static CTimerMap m_sTimeMap;
	//��̬��Ա���������ڴ���ʱ������Ϣ
	static void CALLBACK MyTimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);

};

