
// ffIPSendDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ffIPSend.h"
#include "ffIPSendDlg.h"
#include "afxdialogex.h"
#include "DlgStreamConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define  SHOW_STATUS_TIMER_ID 1


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


// CffIPSendDlg 对话框



CffIPSendDlg::CffIPSendDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FFIPSEND_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CffIPSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_INFO, m_lstInfo);
}

BEGIN_MESSAGE_MAP(CffIPSendDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CONFIG1, &CffIPSendDlg::OnBnClickedBtnConfig1)
	ON_BN_CLICKED(IDC_BTN_CONFIG2, &CffIPSendDlg::OnBnClickedBtnConfig2)
	ON_BN_CLICKED(IDC_BTN_CONFIG3, &CffIPSendDlg::OnBnClickedBtnConfig3)
	ON_BN_CLICKED(IDC_BTN_CONFIG4, &CffIPSendDlg::OnBnClickedBtnConfig4)
	ON_BN_CLICKED(IDC_BTN_CONFIG5, &CffIPSendDlg::OnBnClickedBtnConfig5)
	ON_BN_CLICKED(IDC_BTN_CONFIG6, &CffIPSendDlg::OnBnClickedBtnConfig6)
	ON_BN_CLICKED(IDC_BTN_CONFIG7, &CffIPSendDlg::OnBnClickedBtnConfig7)
	ON_BN_CLICKED(IDC_BTN_CONFIG8, &CffIPSendDlg::OnBnClickedBtnConfig8)
	ON_BN_CLICKED(IDC_BTN_SEND1, &CffIPSendDlg::OnBnClickedBtnSend1)
	ON_BN_CLICKED(IDC_BTN_SEND2, &CffIPSendDlg::OnBnClickedBtnSend2)
	ON_BN_CLICKED(IDC_BTN_SEND3, &CffIPSendDlg::OnBnClickedBtnSend3)
	ON_BN_CLICKED(IDC_BTN_SEND4, &CffIPSendDlg::OnBnClickedBtnSend4)
	ON_BN_CLICKED(IDC_BTN_SEND5, &CffIPSendDlg::OnBnClickedBtnSend5)
	ON_BN_CLICKED(IDC_BTN_SEND6, &CffIPSendDlg::OnBnClickedBtnSend6)
	ON_BN_CLICKED(IDC_BTN_SEND7, &CffIPSendDlg::OnBnClickedBtnSend7)
	ON_BN_CLICKED(IDC_BTN_SEND8, &CffIPSendDlg::OnBnClickedBtnSend8)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CffIPSendDlg 消息处理程序

BOOL CffIPSendDlg::OnInitDialog()
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
	for (int i = 0; i < MAX_STREAMS; i++)
	{
		m_hStreamProcess[i] = INVALID_HANDLE_VALUE;
	}
	SetTimer(SHOW_STATUS_TIMER_ID, 500, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CffIPSendDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CffIPSendDlg::OnPaint()
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
HCURSOR CffIPSendDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CffIPSendDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
			return TRUE;

		case VK_RETURN:
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CffIPSendDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(SHOW_STATUS_TIMER_ID);

	for (int i = 0; i < MAX_STREAMS; i++)
	{
		StreamTerminate(i);
	}
}


void CffIPSendDlg::OnBnClickedBtnConfig1()
{
	StreamConfig(0);
}


void CffIPSendDlg::OnBnClickedBtnConfig2()
{
	StreamConfig(1);
}


void CffIPSendDlg::OnBnClickedBtnConfig3()
{
	StreamConfig(2);
}


void CffIPSendDlg::OnBnClickedBtnConfig4()
{
	StreamConfig(3);
}


void CffIPSendDlg::OnBnClickedBtnConfig5()
{
	StreamConfig(4);
}


void CffIPSendDlg::OnBnClickedBtnConfig6()
{
	StreamConfig(5);
}


void CffIPSendDlg::OnBnClickedBtnConfig7()
{
	StreamConfig(6);
}


void CffIPSendDlg::OnBnClickedBtnConfig8()
{
	StreamConfig(7);
}


void CffIPSendDlg::OnBnClickedBtnSend1()
{
	BtnSend(0);
}


void CffIPSendDlg::OnBnClickedBtnSend2()
{
	BtnSend(1);
}


void CffIPSendDlg::OnBnClickedBtnSend3()
{
	BtnSend(2);
}


void CffIPSendDlg::OnBnClickedBtnSend4()
{
	BtnSend(3);
}


void CffIPSendDlg::OnBnClickedBtnSend5()
{
	BtnSend(4);
}


void CffIPSendDlg::OnBnClickedBtnSend6()
{
	BtnSend(5);
}


void CffIPSendDlg::OnBnClickedBtnSend7()
{
	BtnSend(6);
}


void CffIPSendDlg::OnBnClickedBtnSend8()
{
	BtnSend(7);
}

void CffIPSendDlg::AddInfo(CString str)
{
	if (m_lstInfo.GetCount() > 500)
	{
		m_lstInfo.ResetContent();
	}

	m_lstInfo.AddString(str);
}

void CffIPSendDlg::StreamConfig(int nIdx)
{
	CDlgStreamConfig dlgCfg;
	
	dlgCfg.SetStreamConfigIdx(nIdx);

	if (dlgCfg.DoModal() == IDOK)
	{
		CString strInfo;
		strInfo.Format(_T("Config Stream: [%d] parameters\n"), nIdx+1);
		AddInfo(strInfo);
	}
}

// 使用ffmpeg循环推流(循环读取视频文件)推送EasyDSS RTMP流媒体服务器的方法   
// http://blog.csdn.net/cai6811376/article/details/74783269
void CffIPSendDlg::GetCmdParam(int nIdx, CString &strParam)
{
	TCHAR strVal[MAX_PATH], strSection[MAX_PATH];
	_stprintf_s(strSection, MAX_PATH, _T("Stream%d"), nIdx + 1);

	CString strPart;

	strParam.Empty();

	// 根据实际码率均匀输出
	strParam += _T("-re ");

	// 循环播放,
	strParam += _T("-stream_loop -1 ");		// -1 表示循环无数次
	
	// 输入文件
	::GetPrivateProfileString(strSection, _T("input"), _T(""), strVal, MAX_PATH, APP_CONFIGFILE);
	// 正常情况，应该检测文件的基本信息, 暂时未实现 
	strPart.Format(_T("-i %s "), strVal);
	strParam += strPart;

	// 帧率
	// 24000 / 1001≈23.976, 30000 / 1001≈29.970, 60000/1000≈59.94
	::GetPrivateProfileString(strSection, _T("vid_framerate"), _T("25"), strVal, MAX_PATH, APP_CONFIGFILE);
	if (CString(strVal) == CString(_T("23.976")))
	{
		strPart = CString(_T("-r 24000/1001 "));
	}
	else if (CString(strVal) == CString(_T("29.97")))
	{
		strPart = CString(_T("-r 30000/1001 "));
	}
	else if (CString(strVal) == CString(_T("59.94")))
	{
		strPart = CString(_T("-r 60000/1001 "));
	}
	else // 一般情况
	{
		strPart.Format(_T("-r %s "), strVal);
	}
	strParam += strPart;

	// 视频编码格式
	::GetPrivateProfileString(strSection, _T("vid_encode_type"), _T("libx264"), strVal, MAX_PATH, APP_CONFIGFILE);
	strPart.Format(_T("-vcodec %s "), strVal);
	strParam += strPart;

	// video encode GOP length
	::GetPrivateProfileString(strSection, _T("gop_length"), _T("250"), strVal, MAX_PATH, APP_CONFIGFILE);
	strPart.Format(_T("-g %s "), strVal);
	strParam += strPart;

	// video encode B Frames
	::GetPrivateProfileString(strSection, _T("b_frames"), _T("2"), strVal, MAX_PATH, APP_CONFIGFILE);
	strPart.Format(_T("-bf %s "), strVal);
	strParam += strPart;

	// video preset
	::GetPrivateProfileString(strSection, _T("vid_preset"), _T(""), strVal, MAX_PATH, APP_CONFIGFILE);
	if (CString(strVal) == CString(_T("ultrafast")))
	{
		strPart.Format(_T("-preset:v %s "), strVal);
		strParam += strPart;
	}

	// video profile
	::GetPrivateProfileString(strSection, _T("vid_profile"), _T(""), strVal, MAX_PATH, APP_CONFIGFILE);
	if (CString(strVal) == CString(_T("baseline")))
	{
		strPart.Format(_T("-profile:v %s "), strVal);
		strParam += strPart;
	}

	// video tune
	::GetPrivateProfileString(strSection, _T("vid_tune"), _T(""), strVal, MAX_PATH, APP_CONFIGFILE);
	if (CString(strVal) == CString(_T("zerolatency")))
	{
		strPart.Format(_T("-tune:v %s "), strVal);
		strParam += strPart;
	}

	// 音频编码
	::GetPrivateProfileString(strSection, _T("aud_encode_type"), _T("aac"), strVal, MAX_PATH, APP_CONFIGFILE);
	strPart.Format(_T("-acodec %s "), strVal);
	strParam += strPart;

	// 视频编码尺寸
	::GetPrivateProfileString(strSection, _T("vid_size"), _T("720x576"), strVal, MAX_PATH, APP_CONFIGFILE);
	if (CString(strVal) != CString(_T("auto")))
	{
		strPart.Format(_T("-s %s "), strVal);
		strParam += strPart;
	}

	// 视频编码码率
	::GetPrivateProfileString(strSection, _T("vid_bitrate"), _T("1000"), strVal, MAX_PATH, APP_CONFIGFILE);
	strPart.Format(_T("-b %sk "), strVal);
	strParam += strPart;

	// 音频编码码率
	::GetPrivateProfileString(strSection, _T("aud_bitrate"), _T("128"), strVal, MAX_PATH, APP_CONFIGFILE);
	strPart.Format(_T("-ab %sk "), strVal);
	strParam += strPart;

#if 0
	// 参数需要交换出去 !!!!!!!!!!!!!!!!!!
	// 音频采样率
	_stprintf_s(strVal, MAX_PATH, _T("48000"));
	strPart.Format(_T("-ac 2 -ar %s "), strVal);
	strParam += strPart;
#endif // 0

	// 输出格式
	strParam += _T("-f mpegts ");

	// 输出
	::GetPrivateProfileString(strSection, _T("output"), _T(""), strVal, MAX_PATH, APP_CONFIGFILE);
	strParam += strVal;

	CString strInfo;
	strInfo.Format(_T("Stream: [%d] sendto (%s)\n"), nIdx, strVal);
	AddInfo(strInfo);
}

void CffIPSendDlg::StreamSend(int nIdx)
{
	CString strParam;
	GetCmdParam(nIdx, strParam);

	// 执行命令
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = _T("open");
	ShExecInfo.lpFile = _T("ffmpeg.exe");
	ShExecInfo.lpParameters = (LPTSTR)(LPCTSTR)strParam;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;

	BOOL bRet = ShellExecuteEx(&ShExecInfo);
	if (bRet)
	{
		m_hStreamProcess[nIdx] = ShExecInfo.hProcess;
	}

	/*
	WaitCursorBegin();
	WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
	WaitCursorEnd();
	*/
}

CButton * CffIPSendDlg::GetSendButton(int nIdx)
{
	UINT uBtnId;
	switch (nIdx)
	{
	case 0: uBtnId = IDC_BTN_SEND1; break;
	case 1: uBtnId = IDC_BTN_SEND2; break;
	case 2: uBtnId = IDC_BTN_SEND3; break;
	case 3: uBtnId = IDC_BTN_SEND4; break;
	case 4: uBtnId = IDC_BTN_SEND5; break;
	case 5: uBtnId = IDC_BTN_SEND6; break;
	case 6: uBtnId = IDC_BTN_SEND7; break;
	case 7: uBtnId = IDC_BTN_SEND8; break;
	default:
		AddInfo(_T("Invalid stream index"));
		return NULL;
	}

	return (CButton *)GetDlgItem(uBtnId);
}

void CffIPSendDlg::StreamTerminate(int nIdx)
{
	if (m_hStreamProcess[nIdx] != INVALID_HANDLE_VALUE)
	{
		::TerminateProcess(m_hStreamProcess[nIdx], 0);	
		m_hStreamProcess[nIdx] = INVALID_HANDLE_VALUE;

		CString strInfo;
		strInfo.Format(_T("Stop stream:[%d]"), nIdx);
		AddInfo(strInfo);
	}
}

void CffIPSendDlg::BtnSend(int nIdx)
{
	CButton *pSend = GetSendButton(nIdx);
	CString strTitle;

	pSend->GetWindowText(strTitle);
	if (pSend == NULL)
	{
		return;
	}

	if (strTitle == CString(_T("Send")))
	{
		StreamSend(nIdx);
		pSend->SetWindowTextW(_T("Stop"));
	}
	else if (strTitle == CString(_T("Stop")))
	{
		StreamTerminate(nIdx);
		pSend->SetWindowTextW(_T("Send"));
	}
}


static int nCount = 0;
void CffIPSendDlg::OnTimer(UINT_PTR nIDEvent)
{
	const TCHAR str[4] = { _T('-'), _T('\\'), _T('|'), _T('/') };
	UINT  uInfoId[8] = {
		IDC_STC_SENDINFO1, IDC_STC_SENDINFO2, IDC_STC_SENDINFO3, IDC_STC_SENDINFO4,
		IDC_STC_SENDINFO5, IDC_STC_SENDINFO6, IDC_STC_SENDINFO7, IDC_STC_SENDINFO8
	};
	
	if (nIDEvent == SHOW_STATUS_TIMER_ID)
	{
		nCount++;
		for (int i = 0; i < MAX_STREAMS; i++)
		{
			if (m_hStreamProcess[i] != INVALID_HANDLE_VALUE)
			{
				int nIdx = (nCount + i) % 4;
				SetDlgItemText(uInfoId[i], CString(str[nIdx]));
			}
			else
			{
				SetDlgItemText(uInfoId[i], _T("."));
			}
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}
