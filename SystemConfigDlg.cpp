// SystemConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "SystemConfigDlg.h"
#include "afxdialogex.h"
#include "CameraManager.h"
#include "BoatNameConfDlg.h"
#include "VersionUpdateDlg.h"
#include "HostInfoDlg.h"
#include "CameraConfDlg.h"


// CSystemConfigDlg 对话框

IMPLEMENT_DYNAMIC(CSystemConfigDlg, CDialogEx)

CSystemConfigDlg::CSystemConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SYS_CONF, pParent)
{

}

CSystemConfigDlg::~CSystemConfigDlg()
{
}

void CSystemConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSystemConfigDlg, CDialogEx)
	ON_MESSAGE(USER_MSG_NOTIFY_FOCUS, &CSystemConfigDlg::OnUserMsgNotifyFocus)
	ON_MESSAGE(USER_MSG_LOGIN, &CSystemConfigDlg::OnUserMsgLogin)
END_MESSAGE_MAP()


// CSystemConfigDlg 消息处理程序


afx_msg LRESULT CSystemConfigDlg::OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam)
{
	if (wParam) {
		int i = lParam - IDC_BUTTON1;
		if (i >= 0  &&  i < 9) {
			mCurrCursor = i;
			ShowSubView();
		}
	}
	else {
		mItems[mCurrCursor].SetFocus();
	}
	return 0;
}



void CSystemConfigDlg::InitButton()
{
	//for (int i = 0; i < CAMERA_MAX_NUM + 3; i++) {
	//	mItemPtrs[i] = (CButton*)GetDlgItem(IDC_BUTTON1+i);
	//}

	//for (int i = 1; i < CAMERA_MAX_NUM + 1; i++) {
	//	mItemPtrs[i]->ShowWindow(SW_HIDE);
	//}
	CRect r;
	GetClientRect(&r);


	for (int i = 0; i < CAMERA_MAX_NUM + 3; i++) {
		if (!mItems[i].SubclassDlgItem(IDC_BUTTON1 + i, this)) {
			TRACE("Subclass failed!\n");
		}
		mItems[i].MoveWindow(r.left+2, r.top+i*45, 80, 40, false);
	}

	UpdateItemLayout();
}



void CSystemConfigDlg::InitSubView()
{
	mSubViews[0] = new CBoatNameConfDlg();
	((CBoatNameConfDlg*)mSubViews[0])->Create(IDD_BOATNAME_CONF, this);

	mSubViews[1] = new CVersionUpdateDlg();
	((CVersionUpdateDlg*)mSubViews[1])->Create(IDD_UPDATE, this);

	mSubViews[2] = new CHostInfoDlg();
	((CHostInfoDlg*)mSubViews[2])->Create(IDD_HOSTINFO, this);

	mSubViews[3] = new CCameraConfDlg();
	((CCameraConfDlg*)mSubViews[3])->Create(IDD_CAMERA_CONF, this);
}


void CSystemConfigDlg::ShowSubView()
{
	if (mCurrCursor != mPrevCursor) {
		//摄像头按钮得到焦点
		if (mCurrCursor > 2 ) {
			if (mPrevCursor <= 2) {
				mSubViews[mPrevCursor]->ShowWindow(SW_HIDE);
				mSubViews[3]->ShowWindow(SW_SHOW);
			}

			::SendMessage(mSubViews[3]->m_hWnd, USER_MSG_DEVICE_CONFIG, mCurrCursor-3, 0);
		}
		//其他按钮得到焦点
		else {
			if (mPrevCursor <= 2) {
				mSubViews[mPrevCursor]->ShowWindow(SW_HIDE);
			}
			else {
				mSubViews[3]->ShowWindow(SW_HIDE);
			}
			mSubViews[mCurrCursor]->ShowWindow(SW_SHOW);
		}
		mPrevCursor = mCurrCursor;
	}
	else {
		if (mCurrCursor > 2) {
			mSubViews[3]->ShowWindow(SW_SHOW);
		}
		else {
			mSubViews[mCurrCursor]->ShowWindow(SW_SHOW);
		}
	}
}



void CSystemConfigDlg::UpdateItemLayout()
{
	CCameraManager * pMgr = CCameraManager::getInstance();
	POSITION pos = pMgr->mCameras.GetHeadPosition();

	CWnd* pItem;
	int   cnt = 1;
	CRect r;

	GetClientRect(&r);

	for (int i = 0; i < CAMERA_MAX_NUM; i++) {
		pItem = GetDlgItem(ID_BTN_CAMERA_BASE + i);

		if (pMgr->mLoginDevice[i] != nullptr  &&  pMgr->mLoginDevice[i]->mLoginId) {
			pItem->MoveWindow(r.left+2, r.top + cnt*45, 80, 40, true);
			pItem->ShowWindow(SW_SHOW);
			cnt++;
		}
		else {
			pItem->ShowWindow(SW_HIDE);
		}
	}


	pItem = GetDlgItem(IDC_BUTTON2);
	pItem->MoveWindow(r.left+2, r.top+cnt*45, 80, 40, true);

	cnt++;
	pItem = GetDlgItem(IDC_BUTTON3);
	pItem->MoveWindow(r.left+2, r.top+cnt*45, 80, 40, true);
}



BOOL CSystemConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect r;
	GetClientRect(&r);

	InitButton();
	InitSubView();

	//mCameraConfDlg.Create(IDD_CAMERA_CONF, this);
	//mCameraConfDlg.MoveWindow(r.left+ 100, r.top, r.Width() - 100, r.Height(), true);
	//mCameraConfDlg.ShowWindow(SW_SHOW);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


afx_msg LRESULT CSystemConfigDlg::OnUserMsgLogin(WPARAM wParam, LPARAM lParam)
{
	UpdateItemLayout();
	return 0;
}
