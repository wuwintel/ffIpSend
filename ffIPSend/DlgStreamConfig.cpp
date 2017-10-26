// DlgStreamConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "ffIPSend.h"
#include "DlgStreamConfig.h"
#include "afxdialogex.h"

// ffmpeg 对于视频进行fps改变: http://blog.csdn.net/wangzhebupt/article/details/51133823
// FFmpeg 基本用法:	http://blog.csdn.net/doublefi123/article/details/24325159


// CDlgStreamConfig 对话框

IMPLEMENT_DYNAMIC(CDlgStreamConfig, CDialogEx)

CDlgStreamConfig::CDlgStreamConfig(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_CONFIG, pParent)
{
	m_nStreamIdx = 0;
}

CDlgStreamConfig::~CDlgStreamConfig()
{
}

void CDlgStreamConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgStreamConfig, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_FILEOPEN, &CDlgStreamConfig::OnBnClickedBtnFileopen)
END_MESSAGE_MAP()


// CDlgStreamConfig 消息处理程序



BOOL CDlgStreamConfig::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	LoadParams();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL CDlgStreamConfig::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CDlgStreamConfig::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	SaveParams();

	CDialogEx::OnOK();
}

void CDlgStreamConfig::SetStreamConfigIdx(int nIdx)
{
	m_nStreamIdx = nIdx;
}

void CDlgStreamConfig::SetCmbBoxSelByString(CComboBoxEx *pCmbBox, CString strVal)
{
	for (int i = 0; i < pCmbBox->GetCount(); i++)
	{
		CString str;
		pCmbBox->GetLBText(i, str);
		if (str == strVal)
		{
			pCmbBox->SetCurSel(i);
			break;
		}
	}
}

void CDlgStreamConfig::LoadParams()
{
	TCHAR strRet[MAX_PATH], strSection[MAX_PATH];
	
	_stprintf_s(strSection, MAX_PATH, _T("Stream%d"), m_nStreamIdx + 1);
	
	// input
	::GetPrivateProfileString(strSection, _T("input"), _T(""), strRet, MAX_PATH, APP_CONFIGFILE);
	SetDlgItemText(IDC_EDT_FILENAME, strRet);

	// output
	::GetPrivateProfileString(strSection, _T("output"), _T(""), strRet, MAX_PATH, APP_CONFIGFILE);
	SetDlgItemText(IDC_EDT_OUTPUTURL, strRet);

	// video encode size
	::GetPrivateProfileString(strSection, _T("vid_size"), _T("720x576"), strRet, MAX_PATH, APP_CONFIGFILE);
	SetCmbBoxSelByString((CComboBoxEx *)GetDlgItem(IDC_CMB_VIDENCSIZE), strRet);

	// video encode frame rate
	::GetPrivateProfileString(strSection, _T("vid_framerate"), _T("25"), strRet, MAX_PATH, APP_CONFIGFILE);
	SetCmbBoxSelByString((CComboBoxEx *)GetDlgItem(IDC_CMB_FRAMERATE), strRet);

	// video encode type
	::GetPrivateProfileString(strSection, _T("vid_encode_type"), _T("libx264"), strRet, MAX_PATH, APP_CONFIGFILE);
	SetCmbBoxSelByString((CComboBoxEx *)GetDlgItem(IDC_CMB_VIDENCTYPE), strRet);

	// video encode bitrate
	::GetPrivateProfileString(strSection, _T("vid_bitrate"), _T("1000"), strRet, MAX_PATH, APP_CONFIGFILE);
	SetDlgItemText(IDC_EDT_VIDENCBITRATE, strRet);

	// video encode GOP length
	::GetPrivateProfileString(strSection, _T("gop_length"), _T("250"), strRet, MAX_PATH, APP_CONFIGFILE);
	SetDlgItemText(IDC_EDT_VIDENCGOPLENGTH, strRet);

	// video encode B Frames
	::GetPrivateProfileString(strSection, _T("b_frames"), _T("2"), strRet, MAX_PATH, APP_CONFIGFILE);
	SetDlgItemText(IDC_EDT_VIDENCBFRAMES, strRet);

	// h264 encode preset
	// 取值： ultrafast, superfast, veryfast, faster, fast, medium, slow, slower, veryslow, placebo 
	// av_opt_set(c->priv_data, “preset”, “slow”, 0)声明了编码速度 AvCodecContext
	::GetPrivateProfileString(strSection, _T("vid_preset"), _T(""), strRet, MAX_PATH, APP_CONFIGFILE);
	if (CString(strRet) == CString(_T("ultrafast"))) ((CButton *)GetDlgItem(IDC_CHK_H264PRESET))->SetCheck(TRUE);

	// h264 encode profile:
	// 取值： baseline, main, high
	::GetPrivateProfileString(strSection, _T("vid_profile"), _T(""), strRet, MAX_PATH, APP_CONFIGFILE);
	if (CString(strRet) == CString(_T("baseline"))) ((CButton *)GetDlgItem(IDC_CHK_H264PROFILE))->SetCheck(TRUE);

	// h264 encode tune
	// 但如果想实现实时编码（即编码速度不慢于输入速度），
	// 还要加一句av_opt_set(pOutputVideoCodecCtx->priv_data, “tune”, “zerolatency”, 0)。
	::GetPrivateProfileString(strSection, _T("vid_tune"), _T(""), strRet, MAX_PATH, APP_CONFIGFILE);
	if (CString(strRet) == CString(_T("zerolatency"))) ((CButton *)GetDlgItem(IDC_CHK_H264TUNE))->SetCheck(TRUE);

	// audio encode type
	::GetPrivateProfileString(strSection, _T("aud_encode_type"), _T("aac"), strRet, MAX_PATH, APP_CONFIGFILE);
	SetCmbBoxSelByString((CComboBoxEx *)GetDlgItem(IDC_CMB_AUDENCTYPE), strRet);

	// audio encode bitrate
	::GetPrivateProfileString(strSection, _T("aud_bitrate"), _T("128"), strRet, MAX_PATH, APP_CONFIGFILE);
	SetDlgItemText(IDC_EDT_AUDENCBITRATE, strRet);
}

void CDlgStreamConfig::SaveParams()
{
	TCHAR strSection[MAX_PATH];
	CString  strVal;
	_stprintf_s(strSection, MAX_PATH, _T("Stream%d"), m_nStreamIdx + 1);

	// 输入文件
	GetDlgItemText(IDC_EDT_FILENAME, strVal);
	WritePrivateProfileString(strSection, _T("input"), strVal, APP_CONFIGFILE);

	// 输出流设置
	GetDlgItemText(IDC_EDT_OUTPUTURL, strVal);
	WritePrivateProfileString(strSection, _T("output"), strVal, APP_CONFIGFILE);

	// 视频编码尺寸
	CComboBoxEx *pCmbVidEncSize = (CComboBoxEx *)GetDlgItem(IDC_CMB_VIDENCSIZE);
	pCmbVidEncSize->GetLBText(pCmbVidEncSize->GetCurSel(), strVal);
	WritePrivateProfileString(strSection, _T("vid_size"), strVal, APP_CONFIGFILE);

	// 视频编码帧率 
	CComboBoxEx *pCmbVidEncFR = (CComboBoxEx *)GetDlgItem(IDC_CMB_FRAMERATE);
	pCmbVidEncFR->GetLBText(pCmbVidEncFR->GetCurSel(), strVal);
	WritePrivateProfileString(strSection, _T("vid_framerate"), strVal, APP_CONFIGFILE);

	// 视频编码类型
	CComboBoxEx *pCmbVidEncType = (CComboBoxEx *)GetDlgItem(IDC_CMB_VIDENCTYPE);
	pCmbVidEncType->GetLBText(pCmbVidEncType->GetCurSel(), strVal);
	WritePrivateProfileString(strSection, _T("vid_encode_type"), strVal, APP_CONFIGFILE);

	// 视频编码码率
	GetDlgItemText(IDC_EDT_VIDENCBITRATE, strVal);
	WritePrivateProfileString(strSection, _T("vid_bitrate"), strVal, APP_CONFIGFILE);

	// video encode GOP length
	GetDlgItemText(IDC_EDT_VIDENCGOPLENGTH, strVal);
	::WritePrivateProfileString(strSection, _T("gop_length"), strVal, APP_CONFIGFILE);

	// video encode B Frames
	GetDlgItemText(IDC_EDT_VIDENCBFRAMES, strVal);
	::WritePrivateProfileString(strSection, _T("b_frames"), strVal, APP_CONFIGFILE);

	// h264 preset
	BOOL bFastPreset = ((CButton *)GetDlgItem(IDC_CHK_H264PRESET))->GetCheck();
	WritePrivateProfileString(strSection, _T("vid_preset"), bFastPreset ? _T("ultrafast") : NULL, APP_CONFIGFILE);

	// h264 profile
	BOOL bBaseline = ((CButton *)GetDlgItem(IDC_CHK_H264PROFILE))->GetCheck();
	//CString strProfile = bBaseline ? _T("baseline") : _T("main");
	WritePrivateProfileString(strSection, _T("vid_profile"), bBaseline ? _T("baseline") : NULL, APP_CONFIGFILE);

	// h264 tune
	BOOL bTune = ((CButton *)GetDlgItem(IDC_CHK_H264TUNE))->GetCheck();
	WritePrivateProfileString(strSection, _T("vid_tune "), bTune ? _T("zerolatency") : NULL, APP_CONFIGFILE);

	// 音频编码类型
	CComboBoxEx *pCmbAudEncType = (CComboBoxEx *)GetDlgItem(IDC_CMB_AUDENCTYPE);
	pCmbAudEncType->GetLBText(pCmbAudEncType->GetCurSel(), strVal);
	WritePrivateProfileString(strSection, _T("aud_encode_type"), strVal, APP_CONFIGFILE);

	//  音频编码码率
	GetDlgItemText(IDC_EDT_AUDENCBITRATE, strVal);
	WritePrivateProfileString(strSection, _T("aud_bitrate"), strVal, APP_CONFIGFILE);
}

void CDlgStreamConfig::OnBnClickedBtnFileopen()
{
	CString strFilter = _T("MP4 file(*.mp4)|*.mp4|MKV file(*.mkv)|*.mkv|All files(*.*)|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, strFilter);

	if (dlg.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_EDT_FILENAME, dlg.GetPathName());
	}
}


