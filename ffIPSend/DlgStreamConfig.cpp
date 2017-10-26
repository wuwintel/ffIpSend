// DlgStreamConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ffIPSend.h"
#include "DlgStreamConfig.h"
#include "afxdialogex.h"

// ffmpeg ������Ƶ����fps�ı�: http://blog.csdn.net/wangzhebupt/article/details/51133823
// FFmpeg �����÷�:	http://blog.csdn.net/doublefi123/article/details/24325159


// CDlgStreamConfig �Ի���

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


// CDlgStreamConfig ��Ϣ�������



BOOL CDlgStreamConfig::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	LoadParams();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CDlgStreamConfig::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CDlgStreamConfig::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

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
	// ȡֵ�� ultrafast, superfast, veryfast, faster, fast, medium, slow, slower, veryslow, placebo 
	// av_opt_set(c->priv_data, ��preset��, ��slow��, 0)�����˱����ٶ� AvCodecContext
	::GetPrivateProfileString(strSection, _T("vid_preset"), _T(""), strRet, MAX_PATH, APP_CONFIGFILE);
	if (CString(strRet) == CString(_T("ultrafast"))) ((CButton *)GetDlgItem(IDC_CHK_H264PRESET))->SetCheck(TRUE);

	// h264 encode profile:
	// ȡֵ�� baseline, main, high
	::GetPrivateProfileString(strSection, _T("vid_profile"), _T(""), strRet, MAX_PATH, APP_CONFIGFILE);
	if (CString(strRet) == CString(_T("baseline"))) ((CButton *)GetDlgItem(IDC_CHK_H264PROFILE))->SetCheck(TRUE);

	// h264 encode tune
	// �������ʵ��ʵʱ���루�������ٶȲ����������ٶȣ���
	// ��Ҫ��һ��av_opt_set(pOutputVideoCodecCtx->priv_data, ��tune��, ��zerolatency��, 0)��
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

	// �����ļ�
	GetDlgItemText(IDC_EDT_FILENAME, strVal);
	WritePrivateProfileString(strSection, _T("input"), strVal, APP_CONFIGFILE);

	// ���������
	GetDlgItemText(IDC_EDT_OUTPUTURL, strVal);
	WritePrivateProfileString(strSection, _T("output"), strVal, APP_CONFIGFILE);

	// ��Ƶ����ߴ�
	CComboBoxEx *pCmbVidEncSize = (CComboBoxEx *)GetDlgItem(IDC_CMB_VIDENCSIZE);
	pCmbVidEncSize->GetLBText(pCmbVidEncSize->GetCurSel(), strVal);
	WritePrivateProfileString(strSection, _T("vid_size"), strVal, APP_CONFIGFILE);

	// ��Ƶ����֡�� 
	CComboBoxEx *pCmbVidEncFR = (CComboBoxEx *)GetDlgItem(IDC_CMB_FRAMERATE);
	pCmbVidEncFR->GetLBText(pCmbVidEncFR->GetCurSel(), strVal);
	WritePrivateProfileString(strSection, _T("vid_framerate"), strVal, APP_CONFIGFILE);

	// ��Ƶ��������
	CComboBoxEx *pCmbVidEncType = (CComboBoxEx *)GetDlgItem(IDC_CMB_VIDENCTYPE);
	pCmbVidEncType->GetLBText(pCmbVidEncType->GetCurSel(), strVal);
	WritePrivateProfileString(strSection, _T("vid_encode_type"), strVal, APP_CONFIGFILE);

	// ��Ƶ��������
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

	// ��Ƶ��������
	CComboBoxEx *pCmbAudEncType = (CComboBoxEx *)GetDlgItem(IDC_CMB_AUDENCTYPE);
	pCmbAudEncType->GetLBText(pCmbAudEncType->GetCurSel(), strVal);
	WritePrivateProfileString(strSection, _T("aud_encode_type"), strVal, APP_CONFIGFILE);

	//  ��Ƶ��������
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


