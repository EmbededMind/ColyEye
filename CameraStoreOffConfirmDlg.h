#pragma once


// CCameraStoreOffConfirmDlg 对话框

class CCameraStoreOffConfirmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraStoreOffConfirmDlg)

public:
	CCameraStoreOffConfirmDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCameraStoreOffConfirmDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAMERA_STORE_OFF_CONFIRM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
