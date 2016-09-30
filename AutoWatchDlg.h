#pragma once


// CAutoWatchDlg 对话框

class CAutoWatchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoWatchDlg)

public:
	CAutoWatchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAutoWatchDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_WATCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam);
};
