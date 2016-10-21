#pragma once

#include "TagButton.h"
#include "TagTreeCtrl.h"
#include "DBOperator.h"
#include "RecordFileInfo.h"
// CAlarmMenuDlg �Ի���

class CAlarmMenuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAlarmMenuDlg)

public:
	CAlarmMenuDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAlarmMenuDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALARM_MENU };
#endif

private:
	CTagButton mItems[CAMERA_MAX_NUM];
	CTagTreeCtrl mFileTrees[CAMERA_MAX_NUM];

private:
	int mNewAlarmRecordNumber[CAMERA_MAX_NUM];
	int mTotalNewRecord;

	int mCurrCursor;
	int mPrevCursor;

private:
	void initTreeCtrl();
	void showTreeCtrl();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
protected:
	afx_msg LRESULT OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserMsgBring(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserMsgGiveFocus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserMsgAddFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserMsgDelFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserMsgCopyRecord(WPARAM wParam, LPARAM lParam);
};
