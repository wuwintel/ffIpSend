
// ffIPSendDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CffIPSendDlg �Ի���



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


// CffIPSendDlg ��Ϣ�������

BOOL CffIPSendDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	for (int i = 0; i < MAX_STREAMS; i++)
	{
		m_hStreamProcess[i] = INVALID_HANDLE_VALUE;
	}
	SetTimer(SHOW_STATUS_TIMER_ID, 500, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CffIPSendDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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

// ʹ��ffmpegѭ������(ѭ����ȡ��Ƶ�ļ�)����EasyDSS RTMP��ý��������ķ���   
// http://blog.csdn.net/cai6811376/article/details/74783269
void CffIPSendDlg::GetCmdParam(int nIdx, CString &strParam)
{
	TCHAR strVal[MAX_PATH], strSection[MAX_PATH];
	_stprintf_s(strSection, MAX_PATH, _T("Stream%d"), nIdx + 1);

	CString strPart;

	strParam.Empty();

	// ����ʵ�����ʾ������
	strParam += _T("-re ");

	// ѭ������,
	strParam += _T("-stream_loop -1 ");		// -1 ��ʾѭ��������
	
	// �����ļ�
	::GetPrivateProfileString(strSection, _T("input"), _T(""), strVal, MAX_PATH, APP_CONFIGFILE);
	// ���������Ӧ�ü���ļ��Ļ�����Ϣ, ��ʱδʵ�� 
	strPart.Format(_T("-i %s "), strVal);
	strParam += strPart;

	// ֡��
	// 24000 / 1001��23.976, 30000 / 1001��29.970, 60000/1000��59.94
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
	else // һ�����
	{
		strPart.Format(_T("-r %s "), strVal);
	}
	strParam += strPart;

	// ��Ƶ�����ʽ
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

	// ��Ƶ����
	::GetPrivateProfileString(strSection, _T("aud_encode_type"), _T("aac"), strVal, MAX_PATH, APP_CONFIGFILE);
	strPart.Format(_T("-acodec %s "), strVal);
	strParam += strPart;

	// ��Ƶ����ߴ�
	::GetPrivateProfileString(strSection, _T("vid_size"), _T("720x576"), strVal, MAX_PATH, APP_CONFIGFILE);
	if (CString(strVal) != CString(_T("auto")))
	{
		strPart.Format(_T("-s %s "), strVal);
		strParam += strPart;
	}

	// ��Ƶ��������
	::GetPrivateProfileString(strSection, _T("vid_bitrate"), _T("1000"), strVal, MAX_PATH, APP_CONFIGFILE);
	strPart.Format(_T("-b %sk "), strVal);
	strParam += strPart;

	// ��Ƶ��������
	::GetPrivateProfileString(strSection, _T("aud_bitrate"), _T("128"), strVal, MAX_PATH, APP_CONFIGFILE);
	strPart.Format(_T("-ab %sk "), strVal);
	strParam += strPart;

#if 0
	// ������Ҫ������ȥ !!!!!!!!!!!!!!!!!!
	// ��Ƶ������
	_stprintf_s(strVal, MAX_PATH, _T("48000"));
	strPart.Format(_T("-ac 2 -ar %s "), strVal);
	strParam += strPart;
#endif // 0

	// �����ʽ
	strParam += _T("-f mpegts ");

	// ���
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

	// ִ������
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
