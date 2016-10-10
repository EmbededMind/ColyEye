#pragma once


// CAutoWatchSoundConfirmDlg 对话框

class CAutoWatchSoundConfirmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoWatchSoundConfirmDlg)

public:
	CAutoWatchSoundConfirmDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAutoWatchSoundConfirmDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_WATCH_ALM_SND_CONFIRM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
};
