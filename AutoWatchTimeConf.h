#pragma once


// CAutoWatchTimeConf �Ի���

class CAutoWatchTimeConfDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoWatchTimeConfDlg)

public:
	CAutoWatchTimeConfDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAutoWatchTimeConfDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_WATCH__TIME_CONF };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();


private:
	CDateTimeCtrl* mTimePicker;
};
