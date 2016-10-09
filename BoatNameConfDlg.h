#pragma once


// CBoatNameConfDlg 对话框

class CBoatNameConfDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBoatNameConfDlg)

public:
	CBoatNameConfDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBoatNameConfDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOATNAME_CONF };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
