
// ntestdlgDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "CheckComboBox.h"

#define WM_TEST_ICON_MSG			WM_USER + 211	//������Ӧ���һ������


// Cvc15testdlgDlg �Ի���
class Cntestdlg : public CDialogEx
{
// ����
public:
	Cntestdlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VC15TESTDLG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	enum eTestIconMenu
	{
		MY_OPEN = 1200,
		MY_HIDE,
		MY_QUITE,
	};

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:


public://����
	afx_msg void OnSize(UINT nType, int cx, int cy);
	BOOL CrtTrayIcon();		//��������ͼ��
	BOOL DelTrayIcon();		//ɾ������ͼ��
	afx_msg void HideDlg();			//���ش���������
	afx_msg void ResumeDlg();	//�����ָ̻�����
	afx_msg LRESULT OnRClickIconMsg(WPARAM wParam, LPARAM lParam);	//����
	afx_msg void OnExitApp();	//�����һ����˳�����

	afx_msg void OnDestroy();
	CListBox m_listBox;
	CCheckComboBox m_ckcb;
	afx_msg void OnCbnSelchangeTestdlgcheckcombboxex();
};
