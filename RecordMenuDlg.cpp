// RecordMenuDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "RecordMenuDlg.h"
#include "afxdialogex.h"
#include "DBShadow.h"


// CRecordMenuDlg 对话框

IMPLEMENT_DYNAMIC(CRecordMenuDlg, CDialogEx)

CRecordMenuDlg::CRecordMenuDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RECORD, pParent)
{

}

CRecordMenuDlg::~CRecordMenuDlg()
{
}

void CRecordMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRecordMenuDlg, CDialogEx)
	ON_MESSAGE(USER_MSG_BRING, &CRecordMenuDlg::OnUserMsgBring)
	ON_MESSAGE(USER_MSG_NOTIFY_FOCUS, &CRecordMenuDlg::OnUserMsgNotifyFocus)
	ON_MESSAGE(USER_MSG_ADD_FILE, &CRecordMenuDlg::OnUserMsgAddFile)
	ON_MESSAGE(USER_MSG_DEL_FILE, &CRecordMenuDlg::OnUserMsgDelFile)
END_MESSAGE_MAP()



void CRecordMenuDlg::initButton()
{
	RECT r;
	GetClientRect(&r);
	for (int i = 0; i < CAMERA_MAX_NUM; i++) {
		mItems[i].SubclassDlgItem(IDC_BUTTON1 + i, this);
		mItems[i].MoveWindow(r.left + 5, r.top + 5 + i * 45, 80, 40, TRUE);
	}
}



void CRecordMenuDlg::initTreeCtrl()
{
	RECT r;
	GetClientRect(&r);

	CRecordFileInfoManager* pMgr = CRecordFileInfoManager::getInstance();
	CTime time = CTime::GetCurrentTime();

	for (int i = 0; i < CAMERA_MAX_NUM; i++) {
		mFileTrees[i].SubclassDlgItem(IDC_TREE1 + i, this);
		
		mFileTrees[i].ShowWindow(SW_HIDE);
		mFileTrees[i].MoveWindow(r.left + 90, r.top + 5, r.right - r.left - 90, r.bottom - r.top - 10, TRUE);
		mFileTrees[i].Refresh(pMgr->mNormalRecordInfoLists[i], time);
	}
}


void CRecordMenuDlg::showTreeCtrl()
{
	if (mCurrCursor != mPrevCursor) {
		if (mFileTrees[mPrevCursor].IsWindowVisible()) {
			mFileTrees[mPrevCursor].ShowWindow(SW_HIDE);
			mPrevCursor = mCurrCursor;
		}
	}

	if (!mFileTrees[mCurrCursor].IsWindowVisible()) {
		mFileTrees[mCurrCursor].ShowWindow(SW_SHOW);
	}
}
// CRecordMenuDlg 消息处理程序


BOOL CRecordMenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	initButton();
	initTreeCtrl();


	// 这样搞破坏了封装性啊，呜呼
	DBShadow::GetInstance()->pRecordFileWnd = this;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}





afx_msg LRESULT CRecordMenuDlg::OnUserMsgBring(WPARAM wParam, LPARAM lParam)
{
	if (wParam){
		
	}
	return 0;
}


BOOL CRecordMenuDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN) {
		CWnd* pFocusedWnd = GetFocus();
		int inx = -1;
		switch (pMsg->wParam)
		{
		case VK_RIGHT:
			inx = pFocusedWnd->GetDlgCtrlID();
			return true;
			
		case VK_UP:
			keybd_event(VK_SHIFT, 0, 0, 0);
			keybd_event(VK_TAB, 0, 0, 0);
			keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
			return true;

		case VK_DOWN:
			keybd_event(VK_TAB, 0, 0, 0);
			keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
			return true;

		//case VK_TAB:
		//	inx = pFocusedWnd->GetDlgCtrlID() - IDC_BUTTON7;
		//	if (inx >= 0 && inx < CAMERA_MAX_NUM) {
		//		mCurrCursor = inx;
		//		showTreeCtrl();
		//	}
		//	return CDialogEx::PreTranslateMessage(pMsg);

		default:
			return CDialogEx::PreTranslateMessage(pMsg);
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


afx_msg LRESULT CRecordMenuDlg::OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam)
{
	if (wParam) {
		int i = lParam - IDC_BUTTON1;
		if (i >= 0 && i < CAMERA_MAX_NUM) {
			mCurrCursor = i;
			showTreeCtrl();
		}
	}
	else {
		mItems[mCurrCursor].SetFocus();
	}
	return 0;
}


afx_msg LRESULT CRecordMenuDlg::OnUserMsgAddFile(WPARAM wParam, LPARAM lParam)
{
	CRecordFileInfo* pInfo = (CRecordFileInfo*)lParam;
	if (pInfo->mOwner > 0 && pInfo->mOwner <= CAMERA_MAX_NUM) {
		TRACE("case add record file msg\n");
		mFileTrees[pInfo->mOwner - 1].AddFile(pInfo);
	}
	return 0;
}


afx_msg LRESULT CRecordMenuDlg::OnUserMsgDelFile(WPARAM wParam, LPARAM lParam)
{
	int owner = wParam;

	if (owner > 0 && owner <= CAMERA_MAX_NUM) {
		TRACE("case del normal file msg\n");
		if (!mFileTrees[owner - 1].DelFile(lParam)) {
			TRACE("Delete item failed\n");
		}
	}
	return 0;
}
