#pragma once
#include "afxwin.h"
#include "CameraConfDlg.h"
#include "TagButton.h"


// CSystemConfigDlg �Ի���

class CSystemConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSystemConfigDlg)

public:
	CSystemConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSystemConfigDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYS_CONF };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam);

private:
	int mCurrCursor;
	int mPrevCursor;

	CTagButton mItems[CAMERA_MAX_NUM + 3];
	CWnd*      mSubViews[4];
	
	CCameraConfDlg mCameraConfDlg;

	void InitButton();
	void ShowSubView();

public:
	virtual BOOL OnInitDialog();
};
