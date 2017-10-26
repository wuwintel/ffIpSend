#pragma once


// CDlgStreamConfig �Ի���

class CDlgStreamConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgStreamConfig)

public:
	CDlgStreamConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStreamConfig();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CONFIG };
#endif

public:
	void SetStreamConfigIdx(int nIdx);

private:
	int  m_nStreamIdx;

	void LoadParams();  // ���ز���ʾ����	
	void SaveParams();	// �������
	
	// ����ָ�����ַ�������ѡ����
	void SetCmbBoxSelByString(CComboBoxEx *pCmbBox, CString strVal);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBnClickedBtnFileopen();
};
