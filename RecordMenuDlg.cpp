// RecordMenuDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "RecordMenuDlg.h"
#include "afxdialogex.h"
#include "DBShadow.h"
#include "ColyEyeDlg.h"

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
	ON_MESSAGE(USER_MSG_GIVE_FOCUS, &CRecordMenuDlg::OnUserMsgGiveFocus)
	ON_MESSAGE(USER_MSG_COPY_RECORD, &CRecordMenuDlg::OnUserMsgCopyRecord)
	ON_WM_SIZE()
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



void CRecordMenuDlg::Layout()
{
	CRect rClient;
	GetClientRect(rClient);

	int item_width = rClient.Width() * MENU_ITEM_WIDTH_SHARE;
	int item_height = rClient.Height() * MENU_ITEM_HEIGHT_SHARE;

	for (int i = 0; i < CAMERA_MAX_NUM; i++) {
		mItems[i].MoveWindow(0, i*(item_height), item_width, item_height, TRUE);
		mFileTrees[i].MoveWindow(item_width, 0, rClient.right - item_width, rClient.Height(), TRUE);
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
			inx = pFocusedWnd->GetDlgCtrlID() - IDC_BUTTON1;
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
			if (inx >= IDC_TREE1  &&  inx < IDC_TREE1 + CAMERA_MAX_NUM) {
				mItems[inx-IDC_TREE1].SetFocus();
			}
			else if (inx >= IDC_BUTTON1  &&  inx < IDC_BUTTON1 + CAMERA_MAX_NUM) {
				::SendMessage(GetParent()->m_hWnd, USER_MSG_NOTIFY_BACK, 3, (LPARAM)this);
			}
			return true;

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
		//TRACE("case add record file msg\n");
		mFileTrees[pInfo->mOwner - 1].AddFile(pInfo);
	}
	return 0;
}


afx_msg LRESULT CRecordMenuDlg::OnUserMsgDelFile(WPARAM wParam, LPARAM lParam)
{
	int owner = wParam;

	if (owner > 0 && owner <= CAMERA_MAX_NUM) {

		if (!mFileTrees[owner - 1].DelFile(lParam)) {

		}
	}
	return 0;
}


afx_msg LRESULT CRecordMenuDlg::OnUserMsgGiveFocus(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_BUTTON1)->SetFocus();
	return 0;
}

LRESULT CRecordMenuDlg::OnUserMsgCopyRecord(WPARAM wParam, LPARAM lParam)
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




void CRecordMenuDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (IsWindow(mItems[0])) {
		Layout();
	}
}
