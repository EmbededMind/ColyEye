// MenuDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "MenuDlg.h"
#include "afxdialogex.h"
#include "DBOperator.h"

// CMenuDlg 对话框

IMPLEMENT_DYNAMIC(CMenuDlg, CDialogEx)

CMenuDlg::CMenuDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MENU, pParent)
{

}

CMenuDlg::~CMenuDlg()
{
}

void CMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

/**@brief 初始化第一列菜单
 *
 */
void CMenuDlg::initMenuItem()
{
	if (!mItems[0].SubclassDlgItem(IDC_BUTTON1, this)) {
		TRACE(" subhclass gg\n");
	}
	if (!mItems[1].SubclassDlgItem(IDC_BUTTON2, this)) {
		TRACE(" subhclass gg\n");
	}
	if (!mItems[2].SubclassDlgItem(IDC_BUTTON3, this)) {
		TRACE(" subhclass gg\n");
	}
	if (!mItems[3].SubclassDlgItem(IDC_BUTTON4, this)) {
		TRACE(" subhclass gg\n");
	}
	if (!mItems[4].SubclassDlgItem(IDC_BUTTON5, this)) {
		TRACE(" subhclass gg\n");
	}
}


/**@brief 初始化第二列菜单
 *
 */
void CMenuDlg::initSubMenu()
{
	
	//mSubWnds[0].Create(IDD_ALARM_MENU, this);
	//mSubWnds[0].ShowWindow(SW_HIDE);
	//mSubWnds[1].Create(IDD_SYS_CONF, this);
	//mSubWnds[1].ShowWindow(SW_HIDE);
	//mSubWnds[2].Create(IDD_AUTO_WATCH, this);
	//mSubWnds[2].ShowWindow(SW_HIDE);
	//mSubWnds[3].Create(IDD_RECORD, this);
	//mSubWnds[3].ShowWindow(SW_HIDE);
	//mSubWnds[4].Create(IDD_HOME_WATCH, this);
	//mSubWnds[4].ShowWindow(SW_HIDE);
	mSubWnds[0] = new CAlarmMenuDlg();
	((CAlarmMenuDlg*)mSubWnds[0])->Create(IDD_ALARM_MENU, this);

	mSubWnds[1] = new CSystemConfigDlg();
	((CSystemConfigDlg*)mSubWnds[1])->Create(IDD_SYS_CONF, this);

	mSubWnds[2] = new CAutoWatchDlg();
	((CAutoWatchDlg*)mSubWnds[2])->Create(IDD_AUTO_WATCH, this);

	mSubWnds[3] = new CRecordMenuDlg();
	((CRecordMenuDlg*)mSubWnds[3])->Create(IDD_RECORD, this);

	mSubWnds[4] = new CHomeWatchDlg();
	((CHomeWatchDlg*)mSubWnds[4])->Create(IDD_HOME_WATCH, this);
}

BEGIN_MESSAGE_MAP(CMenuDlg, CDialogEx)
	ON_MESSAGE(USER_MSG_BRING, &CMenuDlg::OnUserMsgBring)
	ON_MESSAGE(USER_MSG_NOTIFY, &CMenuDlg::OnUserMsgNotify)
	ON_MESSAGE(USER_MSG_NOTIFY_FOCUS, &CMenuDlg::OnUserMsgNotifyFocus)
	ON_MESSAGE(USER_MSG_PLAY, &CMenuDlg::OnUserMsgPlay)
	ON_MESSAGE(USER_MSG_LOGIN, &CMenuDlg::OnUserMsgLogin)
END_MESSAGE_MAP()


// CMenuDlg 消息处理程序


BOOL CMenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	initMenuItem();
	initSubMenu();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}




void CMenuDlg::ShowSubMenu()
{
	if (mCurrCursor != mPrevCursor) {
		if (mSubWnds[mPrevCursor]->IsWindowVisible()) {
			mSubWnds[mPrevCursor]->ShowWindow(SW_HIDE);
		}

		mPrevCursor = mCurrCursor;
	}


	if (!mSubWnds[mCurrCursor]->IsWindowVisible()) {
		mSubWnds[mPrevCursor]->ShowWindow(SW_SHOW);
	}
}



afx_msg LRESULT CMenuDlg::OnUserMsgBring(WPARAM wParam, LPARAM lParam)
{
	::SendMessage(mSubWnds[wParam]->m_hWnd, USER_MSG_BRING, true, 0);
	this->SetFocus();
	return 0;
}


BOOL CMenuDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		CWnd* pFocusedWnd = GetFocus();
		int inx = -1;

		switch (pMsg->wParam)
		{
			///在第一列菜单按 '右' 发送 USER_MSG_NOTIFY_FOCUS 消息给下级窗口，由下级窗口判断是否获得焦点。
		case VK_RIGHT:
			inx = pFocusedWnd->GetDlgCtrlID() - IDC_BUTTON1;
			if (inx >= 0 && inx <= MENU_ITEM_NUM) {
				::SendMessage(mSubWnds[inx]->m_hWnd, USER_MSG_GIVE_FOCUS, 0, 0);
				return true;
			}
			break;

		case VK_TAB:
			inx = pFocusedWnd->GetDlgCtrlID() - IDC_BUTTON1;
			if (inx >= 0 && inx < MENU_ITEM_NUM) {
				mCurrCursor = inx;
				ShowSubMenu();
			}
			return CDialogEx::PreTranslateMessage(pMsg);

		case VK_DOWN:
			keybd_event(VK_TAB, 0, 0, 0);
			keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
			return true;

		case VK_UP:
			keybd_event(VK_SHIFT, 0, 0, 0);
			keybd_event(VK_TAB, 0, 0, 0);
			keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
			return true;
		case VK_LEFT:
		case VK_BACK:
			TRACE("case back or left\n");
			return true;
		}
	}
	else if(pMsg->message == WM_CONTEXTMENU){
		::SendMessage(GetParent()->m_hWnd, USER_MSG_NOTIFY, WM_CONTEXTMENU, (LPARAM)this);
		return true;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


afx_msg LRESULT CMenuDlg::OnUserMsgNotify(WPARAM wParam, LPARAM lParam)
{

	return 0;
}

/**@brief 处理第一列菜单项得到焦点时发来的通知消息
 * 
 * @note 第 n 个菜单项得到焦点，将第 n 个下级窗口显示出来。
 */
afx_msg LRESULT CMenuDlg::OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam)
{
	if (wParam) {
		int i = lParam - IDC_BUTTON1;
		if(i>=0  &&  i<CAMERA_MAX_NUM){
			mCurrCursor = i;
			ShowSubMenu();
		}
	}
	else {
		for (int i = 0; i < MENU_ITEM_NUM; i++) {
			if (lParam == (LPARAM)&mSubWnds[i]) {
				mItems[i].SetFocus();
			}
		}
	}
	return 0;
}
LRESULT CMenuDlg::OnUserMsgPlay(WPARAM wParam, LPARAM lParam)
{
	int cursor = wParam;
	this->ShowWindow(SW_SHOW);
	this->SetFocus();
	mSubWnds[cursor]->SetFocus();
	return true;
}





afx_msg LRESULT CMenuDlg::OnUserMsgLogin(WPARAM wParam, LPARAM lParam)
{
	::SendMessage(mSubWnds[1]->m_hWnd, USER_MSG_LOGIN, wParam, lParam);
	return 0;
}
