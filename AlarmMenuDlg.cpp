// AlarmMenuDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "AlarmMenuDlg.h"
#include "afxdialogex.h"
#include "DBOperator.h"
#include "RecordFileInfoManager.h"
#include "DBShadow.h"
#include "ColyEyeDlg.h"
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
	ON_MESSAGE(USER_MSG_COPY_RECORD, &CAlarmMenuDlg::OnUserMsgCopyRecord)
	ON_WM_SETFOCUS()
//	ON_WM_NCPAINT()
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
	mItems[0].SubclassDlgItem(IDC_BUTTON7, this);

	mItems[1].SubclassDlgItem(IDC_BUTTON8, this);

	mItems[2].SubclassDlgItem(IDC_BUTTON9, this);

	mItems[3].SubclassDlgItem(IDC_BUTTON10, this);

	mItems[4].SubclassDlgItem(IDC_BUTTON11, this);
	
	mItems[5].SubclassDlgItem(IDC_BUTTON12, this);

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
			inx = pFocusedWnd->GetDlgCtrlID() - IDC_BUTTON7;
			if (inx >= 0 && inx < CAMERA_MAX_NUM) {
				mFileTrees[inx].SetFocus();
			}
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

		case VK_BACK:
			inx = pFocusedWnd->GetDlgCtrlID();
			if (inx >= IDC_TREE1  &&  inx <IDC_TREE1+CAMERA_MAX_NUM) {
				mItems[inx-IDC_TREE1].SetFocus();
			}
			else if (inx >= IDC_BUTTON7  &&  inx < IDC_BUTTON7 + CAMERA_MAX_NUM) {
				TRACE("tag btn %d case back\n", inx - IDC_BUTTON7);
				::SendMessage(GetParent()->m_hWnd, USER_MSG_NOTIFY_BACK, 0, (LPARAM)this);
			}
			return true;

		default:
			return CDialogEx::PreTranslateMessage(pMsg);
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}




/**@brief 切换报警文件列表
 *
 */
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
		/*CDBOperator * pDBOptor = CDBOperator::getInstance();
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
		}*/

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



 afx_msg LRESULT CAlarmMenuDlg::OnUserMsgCopyRecord(WPARAM wParam, LPARAM lParam)
 {
	 float size = 0;
	 CTagTreeCtrl *pTree = (CTagTreeCtrl*)lParam;
	 CString PlayPath("E:\\Record");
	 if (((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->m_USBFlashDiskStatus.m_bInsert)
	 {
		 HTREEITEM hItem = pTree->GetSelectedItem();
		 if (!hItem)
			 return 0;
		 if (pTree->ItemHasChildren(hItem))
		 {
			 HTREEITEM hChild = pTree->GetChildItem(hItem);
			 CRecordFileInfo *pRecordInfo = (CRecordFileInfo *)pTree->GetItemData(hChild);
			 size += pRecordInfo->mTotalSize;
			 CString tmp;

			 if (pRecordInfo->mStatus & RECORD_TYPE_NORMAL)
			 {
				 PlayPath += _T("\\normal");
			 }
			 else
			 {
				 PlayPath += _T("\\alarm");
			 }
			 tmp.Format(_T("\\%d\\%d%02d%02d%02d%02d%02d.h264"), pRecordInfo->mOwner, pRecordInfo->mBeginTime.GetYear(), pRecordInfo->mBeginTime.GetMonth(),
				 pRecordInfo->mBeginTime.GetDay(), pRecordInfo->mBeginTime.GetHour(), pRecordInfo->mBeginTime.GetMinute(), pRecordInfo->mBeginTime.GetSecond());
			 PlayPath += tmp;
			 PlayPath += _T('\0');
			 hChild = pTree->GetNextItem(hChild, TVGN_NEXT);
			 while (hChild)
			 {
				 pRecordInfo = (CRecordFileInfo *)pTree->GetItemData(hChild);
				 size += pRecordInfo->mTotalSize;
				 PlayPath += _T("E:\\Record");
				 CString tmp;
				 if (pRecordInfo->mStatus & RECORD_TYPE_NORMAL)
				 {
					 PlayPath += _T("\\normal");
				 }
				 else
				 {
					 PlayPath += _T("\\alarm");
				 }
				 tmp.Format(_T("\\%d\\%d%02d%02d%02d%02d%02d.h264"), pRecordInfo->mOwner, pRecordInfo->mBeginTime.GetYear(), pRecordInfo->mBeginTime.GetMonth(),
					 pRecordInfo->mBeginTime.GetDay(), pRecordInfo->mBeginTime.GetHour(), pRecordInfo->mBeginTime.GetMinute(), pRecordInfo->mBeginTime.GetSecond());
				 PlayPath += tmp;
				 PlayPath += _T('\0');
				 hChild = pTree->GetNextItem(hChild, TVGN_NEXT);
			 }
		 }
		 else
		 {
			 CRecordFileInfo *pRecordInfo = (CRecordFileInfo *)pTree->GetItemData(hItem);
			 size += pRecordInfo->mTotalSize;
			 CString tmp;
			 if (pRecordInfo->mStatus & RECORD_TYPE_NORMAL)
			 {
				 PlayPath += _T("\\normal");
			 }
			 else
			 {
				 PlayPath += _T("\\alarm");
			 }
			 tmp.Format(_T("\\%d\\%d%02d%02d%02d%02d%02d.h264"), pRecordInfo->mOwner, pRecordInfo->mBeginTime.GetYear(), pRecordInfo->mBeginTime.GetMonth(),
				 pRecordInfo->mBeginTime.GetDay(), pRecordInfo->mBeginTime.GetHour(), pRecordInfo->mBeginTime.GetMinute(), pRecordInfo->mBeginTime.GetSecond());
			 PlayPath += tmp;
			 PlayPath += _T('\0');
		 }
		 if (((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->m_USBFlashDiskStatus.m_spaceLeft*1000*1000 > size)
			 ((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->m_usbManager.CopyRecord(PlayPath);
		 else
			 AfxMessageBox(_T("U盘空间不足！"));
	 }
	 return 0;
 }


 void CAlarmMenuDlg::OnSetFocus(CWnd* pOldWnd)
 {
	 CDialogEx::OnSetFocus(pOldWnd);
	 TRACE("\n");
	 // TODO: 在此处添加消息处理程序代码
 }


// void CAlarmMenuDlg::OnNcPaint()
// {
//	 // TODO: 在此处添加消息处理程序代码
//	 // 不为绘图消息调用 CDialogEx::OnNcPaint()
// }
