#pragma once
#include "afxwin.h"
#include "VirtualPanel.h"
#include "TagButton.h"


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
	int mVolumn;
	CButton mStoreSwitch;
	CButton mAutoWatchSwitch;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

private:
	CTagButton  mNameItems[18];

	VirtualPanel mNameConfPanel;
	VirtualPanel mOtherConfPanel;

	void InitNameItem();
	void InitPanel();

	void FocusJumpTo(int dst_id);
};
