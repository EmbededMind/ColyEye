#pragma once


// CAutoWatchSoundConfirmDlg �Ի���

class CAutoWatchSoundConfirmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoWatchSoundConfirmDlg)

public:
	CAutoWatchSoundConfirmDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAutoWatchSoundConfirmDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_WATCH_ALM_SND_CONFIRM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
};
