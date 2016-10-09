// MenuDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColyEye.h"
#include "MenuDlg.h"
#include "afxdialogex.h"
#include "DBOperator.h"

// CMenuDlg �Ի���

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

/**@brief ��ʼ����һ�в˵�
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


/**@brief ��ʼ���ڶ��в˵�
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


// CMenuDlg ��Ϣ�������


BOOL CMenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	initMenuItem();
	initSubMenu();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
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
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN)
	{
		CWnd* pFocusedWnd = GetFocus();
		int inx = -1;

		switch (pMsg->wParam)
		{
			///�ڵ�һ�в˵��� '��' ���� USER_MSG_NOTIFY_FOCUS ��Ϣ���¼����ڣ����¼������ж��Ƿ��ý��㡣
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

/**@brief �����һ�в˵���õ�����ʱ������֪ͨ��Ϣ
 * 
 * @note �� n ���˵���õ����㣬���� n ���¼�������ʾ������
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
