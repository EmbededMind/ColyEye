#pragma once
#include "AutoWatchTimeConf.h"
#include "AutoWatchSoundConfDlg.h"
#include "AutoWatchLightConf.h"
#include "AutoWatchLogDlg.h"
#include "TagButton.h"

// CAutoWatchDlg �Ի���

class CAutoWatchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoWatchDlg)

public:
	CAutoWatchDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAutoWatchDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_WATCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam);

private:
	CWnd* mSubDlg[4];
	CTagButton mItems[4];

	int mCurrCursor;
	int mPrevCursor;

	void InitTagButton();
	void InitSubDlg();

	void ShowSubDlg();
public:
	virtual BOOL OnInitDialog();
protected:
	afx_msg LRESULT OnUserMsgGiveFocus(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
