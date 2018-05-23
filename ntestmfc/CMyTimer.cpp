#include "stdafx.h"
#include "CMyTimer.h"
#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afx.h>  // ��������
CTimerMap CMyTimer::m_sTimeMap;

void CMyTimer::MyTimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	WString sz;
	sz = wformat(L"%d�Ŷ�ʱ����%s", idEvent, m_sTimeMap[idEvent]->szContent);
	AfxMessageBox(sz.Buffer());
}

CMyTimer::CMyTimer()
{
}


CMyTimer::~CMyTimer()
{
}

void CMyTimer::SetMyTimer(UINT nElapse, CString sz)
{
	szContent = sz;
	m_nTimerID = SetTimer(NULL, NULL, nElapse, MyTimerProc);
	m_sTimeMap[m_nTimerID] = this;
}

void CMyTimer::KillMyTimer()
{
	KillTimer(NULL, m_nTimerID);
	m_sTimeMap.RemoveKey(m_nTimerID);
}
