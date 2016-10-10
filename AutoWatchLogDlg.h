#pragma once


// CAutoWatchLogDlg 对话框

class CAutoWatchLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoWatchLogDlg)

public:
	CAutoWatchLogDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAutoWatchLogDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_WATCH_LOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
