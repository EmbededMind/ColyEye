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
