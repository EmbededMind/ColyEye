#pragma once


// CHomeWatchDlg 对话框

class CHomeWatchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHomeWatchDlg)

public:
	CHomeWatchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHomeWatchDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOME_WATCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam);
};
