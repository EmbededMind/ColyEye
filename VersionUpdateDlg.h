#pragma once


// CVersionUpdateDlg 对话框

class CVersionUpdateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVersionUpdateDlg)

public:
	CVersionUpdateDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVersionUpdateDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
