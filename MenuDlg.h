#pragma once
#include "TagButton.h"

#include "AlarmMenuDlg.h"
#include "AutoWatchDlg.h"
#include "RecordMenuDlg.h"
#include "SystemConfigDlg.h"
#include "HomeWatchDlg.h"

#include "TestDlg.h"

#define MENU_ITEM_NUM  5

// CMenuDlg 对话框

class CMenuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMenuDlg)

public:
	CMenuDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMenuDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MENU };
#endif

public:
	CTagButton mItems[MENU_ITEM_NUM];	
	//CDialogEx  mSubWnds[MENU_ITEM_NUM];
	CWnd* mSubWnds[MENU_ITEM_NUM];
	int  mCurrCursor;
	int  mPrevCursor;
	//CAlarmMenuDlg mAlarmMenu;
	//CSystemConfigDlg mSystemConfMenu;
	//CHomeWatchDlg    mHomeWatchMenu;
	//CAutoWatchDlg    mAutoWatchMenu;
	//CRecordDlg       mRecordMenu;
	//CTestDlg   mTestDlg;

private:
	void initMenuItem();
	void initSubMenu();
	void ShowSubMenu();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	afx_msg LRESULT OnUserMsgBring(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg LRESULT OnUserMsgNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam);
protected:
	afx_msg LRESULT OnUserMsgPlay(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButton1();
protected:
	afx_msg LRESULT OnUserMsgLogin(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserMsgNotifyBack(WPARAM wParam, LPARAM lParam);
};
