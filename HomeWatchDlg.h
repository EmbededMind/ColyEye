#pragma once


// CHomeWatchDlg �Ի���

class CHomeWatchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHomeWatchDlg)

public:
	CHomeWatchDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHomeWatchDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOME_WATCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam);
};
