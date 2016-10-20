#pragma once


// CCameraOffConfirmDlg 对话框

class CCameraOffConfirmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraOffConfirmDlg)

public:
	CCameraOffConfirmDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCameraOffConfirmDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OFF_CONFIRM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
