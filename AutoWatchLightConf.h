#pragma once


// CAutoWatchLightConf 对话框

class CAutoWatchLightConfDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoWatchLightConfDlg)

public:
	CAutoWatchLightConfDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAutoWatchLightConfDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_WATCH_ALM_LIGHT_CONF };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
