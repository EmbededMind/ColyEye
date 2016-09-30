#pragma once
#include "TagButton.h"
#include "TagTreeCtrl.h"
#include "RecordFileInfo.h"

// CRecordMenuDlg �Ի���

class CRecordMenuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRecordMenuDlg)

public:
	CRecordMenuDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRecordMenuDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECORD };
#endif


private:
private:
	CTagButton mItems[CAMERA_MAX_NUM];
	CTagTreeCtrl mFileTrees[CAMERA_MAX_NUM];

	int mNewRecordNumber[CAMERA_MAX_NUM];
	int mTotalNewRecord;

	int  mCurrCursor;
	int  mPrevCursor;

private:
	void initButton();
	void initTreeCtrl();
	void showTreeCtrl();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	afx_msg LRESULT OnUserMsgBring(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	afx_msg LRESULT OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserMsgAddFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserMsgDelFile(WPARAM wParam, LPARAM lParam);
};
