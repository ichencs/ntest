
// ntestdlgDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "CheckComboBox.h"

#define WM_TEST_ICON_MSG			WM_USER + 211	//托盘响应：右击，左击


// Cvc15testdlgDlg 对话框
class Cntestdlg : public CDialogEx
{
// 构造
public:
	Cntestdlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VC15TESTDLG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	enum eTestIconMenu
	{
		MY_OPEN = 1200,
		MY_HIDE,
		MY_QUITE,
	};

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:


public://托盘
	afx_msg void OnSize(UINT nType, int cx, int cy);
	BOOL CrtTrayIcon();		//创建托盘图标
	BOOL DelTrayIcon();		//删除托盘图标
	afx_msg void HideDlg();			//隐藏窗口至托盘
	afx_msg void ResumeDlg();	//从托盘恢复窗口
	afx_msg LRESULT OnRClickIconMsg(WPARAM wParam, LPARAM lParam);	//托盘
	afx_msg void OnExitApp();	//托盘右击：退出程序

	afx_msg void OnDestroy();
	CListBox m_listBox;
	CCheckComboBox m_ckcb;
	afx_msg void OnCbnSelchangeTestdlgcheckcombboxex();
};
