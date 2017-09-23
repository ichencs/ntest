
// ntestdlgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "dlgntest.h"
#include "ntestdlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
	public:
		CAboutDlg();
		
		// 对话框数据
#ifdef AFX_DESIGN_TIME
		enum { IDD = IDD_ABOUTBOX };
#endif
		
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
		
		// 实现
	protected:
		DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cvc15testdlgDlg 对话框



Cntestdlg::Cntestdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VC15TESTDLG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cntestdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, TestDlgListBox, m_listBox);
	DDX_Control(pDX, TestDlgCheckCombboxEx, m_ckcb);
	DDX_Control(pDX, IDC_EDIT_TEST1, m_edt);
}

BEGIN_MESSAGE_MAP(Cntestdlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_MESSAGE(WM_TEST_ICON_MSG, OnRClickIconMsg)
	ON_BN_CLICKED(MY_OPEN, ResumeDlg)
	ON_BN_CLICKED(MY_HIDE, HideDlg)
	ON_BN_CLICKED(MY_QUITE, OnExitApp)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(TestDlgCheckCombboxEx, &Cntestdlg::OnCbnSelchangeTestdlgcheckcombboxex)
	ON_BN_CLICKED(IDOK, &Cntestdlg::OnBnClickedOk)
	ON_LBN_SETFOCUS(TestDlgListBox, &Cntestdlg::OnLbnSetfocusTestdlglistbox)
	ON_EN_SETFOCUS(IDC_EDIT_TEST1, &Cntestdlg::OnEnSetfocusEditTest1)
	ON_MESSAGE(WM_USER_MSG_READ, Cntestdlg::ReadSharedMemory)
	ON_BN_CLICKED(IDC_BTN_GET_STYLE, &Cntestdlg::OnBnClickedBtnGetStyle)
END_MESSAGE_MAP()


// Cvc15testdlgDlg 消息处理程序

BOOL Cntestdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// 将“关于...”菜单项添加到系统菜单中。
	
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	// TODO: 在此添加额外的初始化代码
	CrtTrayIcon();
	
	m_ckcb.AddString(_T("你好"));
	m_ckcb.AddString(_T("不好"));
	m_ckcb.AddString(_T("好不好"));
	m_ckcb.AddString(_T("好啊"));
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cntestdlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cntestdlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		
		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cntestdlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL Cntestdlg::CrtTrayIcon()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	// 	nid.hWnd = this->m_hWnd;
	nid.hWnd = GetSafeHwnd();
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	nid.uCallbackMessage = WM_TEST_ICON_MSG;//自定义的消息名称
	lstrcpy(nid.szTip, _T("测试对话框"));
	BOOL bRes = Shell_NotifyIcon(NIM_ADD, &nid);
	return bRes;
}

BOOL Cntestdlg::DelTrayIcon()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	// 	nid.hWnd = this->m_hWnd;
	nid.hWnd = GetSafeHwnd();
	nid.uID = IDR_MAINFRAME;
	// 	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	// 	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	// 	nid.uCallbackMessage = WM_TEST_ICON_MSG;//自定义的消息名称
	// 	lstrcpy(nid.szTip, _T("测试对话框"));
	BOOL bRes = Shell_NotifyIcon(NIM_DELETE, &nid);
	return bRes;
}

void Cntestdlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	
	// TODO: 在此处添加消息处理程序代码
	if (nType == SIZE_MINIMIZED)
	{
		//最小化窗口，并托盘
		HideDlg();
	}
}

void Cntestdlg::HideDlg()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = GetSafeHwnd();
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	nid.uCallbackMessage = WM_TEST_ICON_MSG;//自定义的消息名称
	lstrcpy(nid.szTip, _T("托盘中..."));
	lstrcpy(nid.szInfo, _T("进入托盘模式"));
	lstrcpy(nid.szInfoTitle, _T("提示"));
	BOOL bRes = Shell_NotifyIcon(NIM_MODIFY, &nid);
	ShowWindow(SW_HIDE);
}

void Cntestdlg::ResumeDlg()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	// 	nid.hWnd = this->m_hWnd;
	nid.hWnd = GetSafeHwnd();
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	nid.uCallbackMessage = WM_TEST_ICON_MSG;//自定义的消息名称
	lstrcpy(nid.szTip, _T("测试对话框"));
	BOOL bRes = Shell_NotifyIcon(NIM_MODIFY, &nid);
	ShowWindow(SW_NORMAL);
}

LRESULT Cntestdlg::OnRClickIconMsg(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)
	{
		return 1;
	}
	
	switch (lParam)
	{
		case WM_RBUTTONUP:
			{
				LPPOINT lpoint = new tagPOINT;
				::GetCursorPos(lpoint);//得到鼠标位置
				CMenu menu;
				UINT nState;
				
				menu.CreatePopupMenu();//声明一个弹出式菜单
				//增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已
				//隐藏），将程序结束。
				menu.AppendMenu(MF_STRING, MY_OPEN, _T("打开"));
				nState = IsWindowVisible() ? MF_GRAYED : MF_ENABLED;
				nState = MF_BYCOMMAND | nState;
				menu.EnableMenuItem(MY_OPEN, nState);
				
				menu.AppendMenu(MF_STRING, MY_HIDE, _T("隐藏"));
				nState = IsWindowVisible() ? MF_ENABLED : MF_GRAYED;
				nState = MF_BYCOMMAND | nState;
				menu.EnableMenuItem(MY_HIDE, nState);
				
				menu.AppendMenu(MF_STRING, MY_QUITE, _T("关闭"));
				//确定弹出式菜单的位置
				menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
				//资源回收
				HMENU hmenu = menu.Detach();
				menu.DestroyMenu();
				delete lpoint;
			}
			break;
			
		case WM_LBUTTONDBLCLK:
			{
				ResumeDlg();
			}
			
		default:
			break;
	}
	
	return 0;
}

void Cntestdlg::OnExitApp()
{
	OnOK();
}


void Cntestdlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	
	// TODO: 在此处添加消息处理程序代码
	DelTrayIcon();
}


void Cntestdlg::OnCbnSelchangeTestdlgcheckcombboxex()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Cntestdlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void Cntestdlg::OnLbnSetfocusTestdlglistbox()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Cntestdlg::OnEnSetfocusEditTest1()
{
	// TODO: 在此添加控件通知处理程序代码
}



afx_msg LRESULT  Cntestdlg::ReadSharedMemory(WPARAM wParam, LPARAM lParam)
{
	using namespace vl;
	HANDLE lhShareMemory;
	char* lpcBuffer;
	
	lhShareMemory = OpenFileMapping(FILE_MAP_READ, false, ThkSharedMemoryName);
	
	if (lhShareMemory == NULL)
	{
		return 0;
	}
	
	lpcBuffer = (char*)MapViewOfFile(lhShareMemory, FILE_MAP_READ, 0, 0, 1000);
	
	if (NULL == lpcBuffer)
	{
		return 0;
	}
	
	AString astr = lpcBuffer;
	WString wstr = atow(astr);
	MessageBox(wstr.Buffer());
	
	HWND hTranslate = ::FindWindow(NULL, TranslateWnd);
	
	if (hTranslate)
	{
		::PostMessage(hTranslate, WM_CLOSE, 0, 0);
	}
	
	return 0;
}


void Cntestdlg::OnBnClickedBtnGetStyle()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD style1 = m_edt.GetStyle();
	DWORD style2 = m_edt.GetExStyle();
	DWORD style = style1 | style2;
}
