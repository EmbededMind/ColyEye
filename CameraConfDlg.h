#pragma once
#include "afxwin.h"
#include "VirtualPanel.h"
#include "TagButton.h"

#include "CameraManager.h"

#include "afxcmn.h"



// CCameraConfDlg �Ի���

class CCameraConfDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraConfDlg)

public:
	CCameraConfDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCameraConfDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAMERA_CONF };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString mCurrName;
	CButton mSwitch;
	CButton mPicDirection;
	CButton mStoreSwitch;
	CButton mAutoWatchSwitch;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();



protected:
	afx_msg LRESULT OnUserMsgGiveFocus(WPARAM wParam, LPARAM lParam);
	CSliderCtrl mSlider;
	int mVolume;
	SCROLLINFO mHScrollInfo;
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

public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
