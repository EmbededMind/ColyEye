#pragma once


// CSystemConfigDlg 对话框

class CSystemConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSystemConfigDlg)

public:
	CSystemConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSystemConfigDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYS_CONF };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam);

private:
	CButton mItems[CAMERA_MAX_NUM + 3];
};
