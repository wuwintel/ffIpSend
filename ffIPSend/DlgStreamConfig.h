#pragma once


// CDlgStreamConfig 对话框

class CDlgStreamConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgStreamConfig)

public:
	CDlgStreamConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgStreamConfig();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CONFIG };
#endif

public:
	void SetStreamConfigIdx(int nIdx);

private:
	int  m_nStreamIdx;

	void LoadParams();  // 加载并显示参数	
	void SaveParams();	// 保存参数
	
	// 根据指定的字符串设置选择项
	void SetCmbBoxSelByString(CComboBoxEx *pCmbBox, CString strVal);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBnClickedBtnFileopen();
};
