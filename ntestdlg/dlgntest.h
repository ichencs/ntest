
// ntestdlg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cvc15testdlgApp: 
// �йش����ʵ�֣������ ntestdlg.cpp
//

class CntestdlgApp : public CWinApp
{
public:
	CntestdlgApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CntestdlgApp theApp;