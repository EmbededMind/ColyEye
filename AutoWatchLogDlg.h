#pragma once
#include "afxwin.h"


// CAutoWatchLogDlg 对话框

class CAutoWatchLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoWatchLogDlg)

public:
	CAutoWatchLogDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAutoWatchLogDlg();

private:
	void Layout();
	void ShowLog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_WATCH_LOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit mLogText;
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	afx_msg LRESULT OnUserMsgBring(WPARAM wParam, LPARAM lParam);
};
