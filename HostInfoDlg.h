#pragma once


// CHostInfoDlg 对话框

class CHostInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHostInfoDlg)

public:
	CHostInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHostInfoDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOSTINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
