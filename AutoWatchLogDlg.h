#pragma once
#include "afxwin.h"


// CAutoWatchLogDlg �Ի���

class CAutoWatchLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoWatchLogDlg)

public:
	CAutoWatchLogDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAutoWatchLogDlg();

private:
	void Layout();
	void ShowLog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_WATCH_LOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit mLogText;
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	afx_msg LRESULT OnUserMsgBring(WPARAM wParam, LPARAM lParam);
};
