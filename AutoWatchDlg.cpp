// AutoWatchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "AutoWatchDlg.h"
#include "afxdialogex.h"


// CAutoWatchDlg 对话框

IMPLEMENT_DYNAMIC(CAutoWatchDlg, CDialogEx)

CAutoWatchDlg::CAutoWatchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTO_WATCH, pParent)
{

}

CAutoWatchDlg::~CAutoWatchDlg()
{
}

void CAutoWatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAutoWatchDlg, CDialogEx)
	ON_MESSAGE(USER_MSG_NOTIFY_FOCUS, &CAutoWatchDlg::OnUserMsgNotifyFocus)
	ON_MESSAGE(USER_MSG_GIVE_FOCUS, &CAutoWatchDlg::OnUserMsgGiveFocus)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CAutoWatchDlg 消息处理程序


afx_msg LRESULT CAutoWatchDlg::OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam)
{
	if (wParam) {
		int i = lParam - IDC_BUTTON1;
		if (i >= 0 && i <= 3) {
			mCurrCursor = i;
			ShowSubDlg();
		}
	}
	return 0;
}


BOOL CAutoWatchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitTagButton();
	InitSubDlg();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void CAutoWatchDlg::InitTagButton()
{
	mItems[0].SubclassDlgItem(IDC_BUTTON1, this);
	mItems[1].SubclassDlgItem(IDC_BUTTON2, this);
	mItems[2].SubclassDlgItem(IDC_BUTTON3, this);
	mItems[3].SubclassDlgItem(IDC_BUTTON4, this);
}



void CAutoWatchDlg::InitSubDlg()
{
	mSubDlg[0] = new CAutoWatchTimeConfDlg();
	((CAutoWatchTimeConfDlg*)mSubDlg[0])->Create(IDD_AUTO_WATCH_TIME_CONF, this);

	mSubDlg[1] = new CAutoWatchSoundConfDlg();
	((CAutoWatchSoundConfDlg*)mSubDlg[1])->Create(IDD_AUTO_WATCH_ALM_SND_CONF, this);

	mSubDlg[2] = new CAutoWatchLightConfDlg();
	((CAutoWatchLightConfDlg*)mSubDlg[2])->Create(IDD_AUTO_WATCH_ALM_LIGHT_CONF, this);

	mSubDlg[3] = new CAutoWatchLogDlg();
	((CAutoWatchLogDlg*)mSubDlg[3])->Create(IDD_AUTO_WATCH_LOG, this);
}



void CAutoWatchDlg::ShowSubDlg()
{
	if (mCurrCursor != mPrevCursor) {
		mSubDlg[mPrevCursor]->ShowWindow(SW_HIDE);
		mPrevCursor = mCurrCursor;
	}

	mSubDlg[mPrevCursor]->ShowWindow(SW_SHOW);
}



void CAutoWatchDlg::Layout()
{
	CRect rClient;
	GetClientRect(rClient);

	int item_width = rClient.Width() * MENU_ITEM_WIDTH_SHARE;
	int item_height = rClient.Height() * MENU_ITEM_HEIGHT_SHARE;

	for (int i = 0; i < 4; i++) {
		mItems[i].MoveWindow(0, i*item_height, item_width, item_height, TRUE);
		mSubDlg[i]->MoveWindow(item_width, 0, rClient.right-item_width, rClient.Height(), TRUE);
	}
}



afx_msg LRESULT CAutoWatchDlg::OnUserMsgGiveFocus(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_BUTTON1)->SetFocus();
	return 0;
}


BOOL CAutoWatchDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN) {
		CWnd* pFocusedWnd = GetFocus();
		int inx = -1;

		switch (pMsg->wParam)
		{
		case VK_RIGHT:
			inx = pFocusedWnd->GetDlgCtrlID() - IDC_BUTTON1;
			if (inx >= 0 && inx < 4) {
				mSubDlg[inx]->SetFocus();
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
			::SendMessage(GetParent()->m_hWnd, USER_MSG_NOTIFY_BACK, 2, (LPARAM)this);
			return true;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CAutoWatchDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (IsWindow(mItems[0])) {
		Layout();
	}
}
