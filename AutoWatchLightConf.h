#pragma once


// CAutoWatchLightConf �Ի���

class CAutoWatchLightConfDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoWatchLightConfDlg)

public:
	CAutoWatchLightConfDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAutoWatchLightConfDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_WATCH_ALM_LIGHT_CONF };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
