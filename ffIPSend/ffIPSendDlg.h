
// ffIPSendDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


#define MAX_STREAMS 8

// CffIPSendDlg 对话框
class CffIPSendDlg : public CDialogEx
{
// 构造
public:
	CffIPSendDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FFIPSEND_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	void StreamConfig(int nIdx);
	void StreamSend(int nIdx);
	void StreamTerminate(int nIdx);
	void BtnSend(int nIdx);

	void GetCmdParam(int nIdx, CString &strParam);
	
	CButton *GetSendButton(int nIdx);
	void AddInfo(CString str);

	HANDLE m_hStreamProcess[MAX_STREAMS];

public:
	afx_msg void OnBnClickedBtnConfig1();
	afx_msg void OnBnClickedBtnConfig2();
	afx_msg void OnBnClickedBtnConfig3();
	afx_msg void OnBnClickedBtnConfig4();
	afx_msg void OnBnClickedBtnConfig5();
	afx_msg void OnBnClickedBtnConfig6();
	afx_msg void OnBnClickedBtnConfig7();
	afx_msg void OnBnClickedBtnConfig8();
	afx_msg void OnBnClickedBtnSend1();
	afx_msg void OnBnClickedBtnSend2();
	afx_msg void OnBnClickedBtnSend3();
	afx_msg void OnBnClickedBtnSend4();
	afx_msg void OnBnClickedBtnSend5();
	afx_msg void OnBnClickedBtnSend6();
	afx_msg void OnBnClickedBtnSend7();
	afx_msg void OnBnClickedBtnSend8();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CListBox m_lstInfo;
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
