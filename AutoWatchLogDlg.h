#pragma once


// CAutoWatchLogDlg �Ի���

class CAutoWatchLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoWatchLogDlg)

public:
	CAutoWatchLogDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAutoWatchLogDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_WATCH_LOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
