#pragma once


// CAutoWatchDlg �Ի���

class CAutoWatchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoWatchDlg)

public:
	CAutoWatchDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAutoWatchDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_WATCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam);
};
