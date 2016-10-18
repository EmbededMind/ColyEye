#pragma once
#include "afxwin.h"
#include "VirtualPanel.h"
#include "TagButton.h"
#include "CameraManager.h"

// CCameraConfDlg 对话框

class CCameraConfDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraConfDlg)

public:
	CCameraConfDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCameraConfDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAMERA_CONF };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString mCurrName;
	CButton mSwitch;
	CButton mPicDirection;
	int mVolumn;
	CButton mStoreSwitch;
	CButton mAutoWatchSwitch;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();


protected:
	afx_msg LRESULT OnUserMsgGiveFocus(WPARAM wParam, LPARAM lParam);


private:
	CCamera*    pCamera;

	CTagButton  mNameItems[18];

	VirtualPanel mNameConfPanel;
	VirtualPanel mOtherConfPanel;

	void InitNameItem();
	void InitPanel();

	void FocusJumpTo(int dst_id);

protected:
	afx_msg LRESULT OnUserMsgDeviceConfig(WPARAM wParam, LPARAM lParam);
};
