
// vc15-test-dlg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cvc15testdlgApp: 
// �йش����ʵ�֣������ vc15-test-dlg.cpp
//

class Cvc15testdlgApp : public CWinApp
{
public:
	Cvc15testdlgApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cvc15testdlgApp theApp;