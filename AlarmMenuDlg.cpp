// AlarmMenuDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "AlarmMenuDlg.h"
#include "afxdialogex.h"
#include "DBOperator.h"
#include "RecordFileInfoManager.h"
#include "DBShadow.h"

// CAlarmMenuDlg 对话框

IMPLEMENT_DYNAMIC(CAlarmMenuDlg, CDialogEx)

CAlarmMenuDlg::CAlarmMenuDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ALARM_MENU, pParent)
{

}

CAlarmMenuDlg::~CAlarmMenuDlg()
{
}

void CAlarmMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAlarmMenuDlg, CDialogEx)
	ON_MESSAGE(USER_MSG_NOTIFY_FOCUS, &CAlarmMenuDlg::OnUserMsgNotifyFocus)
	ON_MESSAGE(USER_MSG_BRING, &CAlarmMenuDlg::OnUserMsgBring)
	ON_MESSAGE(USER_MSG_GIVE_FOCUS, &CAlarmMenuDlg::OnUserMsgGiveFocus)
	ON_MESSAGE(USER_MSG_ADD_FILE, &CAlarmMenuDlg::OnUserMsgAddFile)
	ON_MESSAGE(USER_MSG_DEL_FILE, &CAlarmMenuDlg::OnUserMsgDelFile)
END_MESSAGE_MAP()



void CAlarmMenuDlg::initTreeCtrl()
{
	mFileTrees[0].SubclassDlgItem(IDC_TREE1, this);
	mFileTrees[1].SubclassDlgItem(IDC_TREE2, this);
	mFileTrees[2].SubclassDlgItem(IDC_TREE3, this);
	mFileTrees[3].SubclassDlgItem(IDC_TREE4, this);
	mFileTrees[4].SubclassDlgItem(IDC_TREE5, this);
	mFileTrees[5].SubclassDlgItem(IDC_TREE6, this);

	CRecordFileInfoManager* pMgr = CRecordFileInfoManager::getInstance();
	CTime time = CTime::GetCurrentTime();
	for (int i = 0; i < CAMERA_MAX_NUM; i++) {
		//RefreshTreeCtrl(mFileTrees[i], pMgr->mNormalRecordInfoLists[i]);
		mFileTrees[i].Refresh(pMgr->mAlarmRecordInfoLists[i], time);
		mFileTrees[i].ShowWindow(SW_HIDE);
	}	
}


BOOL CAlarmMenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (!mItems[0].SubclassDlgItem(IDC_BUTTON7, this)) {
		TRACE("gg\n");
	}
	if (!mItems[1].SubclassDlgItem(IDC_BUTTON8, this)) {
		TRACE("gg\n");
	}
	if (!mItems[2].SubclassDlgItem(IDC_BUTTON9, this)) {
		TRACE("gg\n");
	}
	if (!mItems[3].SubclassDlgItem(IDC_BUTTON10, this)) {
		TRACE("gg\n");
	}
	if (!mItems[4].SubclassDlgItem(IDC_BUTTON11, this)) {
		TRACE("gg\n");
	}	
	if (!mItems[5].SubclassDlgItem(IDC_BUTTON12, this)) {
		TRACE("gg\n");
	}
    

	initTreeCtrl();

	DBShadow::GetInstance()->pAlarmRecordFileWnd = this;
	return true;  // return TRUE unless you set the focus to a control
				   // 异常: OCX 属性页应返回 FALSE
}



void CAlarmMenuDlg::showTreeCtrl()
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



BOOL CAlarmMenuDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		CWnd * pFocusedWnd = GetFocus();
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





afx_msg LRESULT CAlarmMenuDlg::OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam)
{
	if (wParam) {
		int i = lParam - IDC_BUTTON7;
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


afx_msg LRESULT CAlarmMenuDlg::OnUserMsgBring(WPARAM wParam, LPARAM lParam)
{
	if (wParam) {
		int cnt = 0;
		RECT r;
		GetClientRect(&r);
		mTotalNewRecord = 0;
		CDBOperator * pDBOptor = CDBOperator::getInstance();
		for (int i = 0; i < CAMERA_MAX_NUM; i++) {
			mNewAlarmRecordNumber[i] = pDBOptor->queryNewAlarmRecord(i+1);
			if (mNewAlarmRecordNumber[i]) {

				mItems[i].MoveWindow(r.left, r.top+cnt*40, 100, 40, TRUE);
				mItems[i].ShowWindow(SW_SHOW);
				mTotalNewRecord += mNewAlarmRecordNumber[i];
				cnt++;
			}
			else {
				mItems[i].ShowWindow(SW_HIDE);
			}
		}
	}

	return 0;
}


afx_msg LRESULT CAlarmMenuDlg::OnUserMsgGiveFocus(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_BUTTON7)->SetFocus();
	return 0;
}


afx_msg LRESULT CAlarmMenuDlg::OnUserMsgAddFile(WPARAM wParam, LPARAM lParam)
{
	CRecordFileInfo* pInfo = (CRecordFileInfo*)lParam;
	if (pInfo->mOwner > 0 && pInfo->mOwner <= CAMERA_MAX_NUM) {
		TRACE("case add file message\n");
		//AddFileToTree(pInfo->mOwner-1, pInfo);
		mFileTrees[pInfo->mOwner - 1].AddFile(pInfo);
	}
	return 0;
}

/**  @warning 此时的lParam 是单纯的指针变量，此指针所指的对象已被析构。
 */
afx_msg LRESULT CAlarmMenuDlg::OnUserMsgDelFile(WPARAM wParam, LPARAM lParam)
{

	int owner = wParam;

	if (owner > 0 && owner <= CAMERA_MAX_NUM) {
		TRACE("case del file message\n");
		//if (!DelFileFromTree(mFileTrees[owner-1],lParam)) {
		//	TRACE("Delete item failed\n");
		//}
		if (!mFileTrees[owner-1].DelFile(lParam)) {
			TRACE("Delete item failed\n");
		}
	}
	return 0;
}
