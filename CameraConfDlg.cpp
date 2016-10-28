// CameraConfDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "ColyEyeDlg.h"
#include "CameraConfDlg.h"
#include "afxdialogex.h"

#include "CameraOffConfirmDlg.h"
#include "CameraStoreOffConfirmDlg.h"
#include "Util.h"

// CCameraConfDlg 对话框

IMPLEMENT_DYNAMIC(CCameraConfDlg, CDialogEx)

CCameraConfDlg::CCameraConfDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CAMERA_CONF, pParent)
	, mCurrName(_T(""))
{

}

CCameraConfDlg::~CCameraConfDlg()
{
}

void CCameraConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mCurrName);
	DDX_Control(pDX, IDC_SLIDER1, mSlider);
	DDX_Control(pDX, IDC_BUTTON1, mSwitcher);
	DDX_Control(pDX, IDC_BUTTON2, mPicDirection);
	DDX_Control(pDX, IDC_BUTTON3, mStoreSwitcher);
	DDX_Control(pDX, IDC_BUTTON4, mAutoWatchSwitcher);
}


BEGIN_MESSAGE_MAP(CCameraConfDlg, CDialogEx)


	ON_MESSAGE(USER_MSG_GIVE_FOCUS, &CCameraConfDlg::OnUserMsgGiveFocus)
	ON_MESSAGE(USER_MSG_DEVICE_CONFIG, &CCameraConfDlg::OnUserMsgDeviceConfig)

	ON_WM_HSCROLL()

	ON_BN_CLICKED(IDC_BUTTON1, &CCameraConfDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCameraConfDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCameraConfDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCameraConfDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CCameraConfDlg 消息处理程序


void CCameraConfDlg::FocusJumpTo(int dst_id)
{
	GetDlgItem(dst_id)->SetFocus();
}

BOOL CCameraConfDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN) {
			int id = GetFocus()->GetDlgCtrlID();

		switch (pMsg->wParam)
		{
		case VK_SPACE:
			if (id == IDC_EDIT1) {
				TRACE("camera name edit space\n");
				if (mNameConfPanel.IsVisible()) {
					mNameConfPanel.ShowPanel(SW_HIDE);
					mOtherConfPanel.MovePanel(0, -100);
				}
				else {
					mNameConfPanel.ShowPanel(SW_SHOW);
					mOtherConfPanel.MovePanel(0, 100);
					GetDlgItem(1)->SetFocus();
				}				
			 }
			return true;
        
		case VK_UP:
			// 船名选项
			if (id >= 1 && id <= 18) {
				if (id > 4) {
					FocusJumpTo(id - 4);
				}
			}
			else {
				//
			}
			return true;

		case VK_DOWN:
			if (id >= 1 && id <= 18) {
				if (id < 15) {
					FocusJumpTo(id + 4);
				}
			}
			else
			{
				//
			}
			return true;

		case VK_LEFT:
			if (id >= 1 && id <= 18) {
				if (id > 1) {
					FocusJumpTo(id - 1);
				}
				return true;
			}
			break;

		case VK_RIGHT:
			if (id >= 1 && id <= 18) {
				if (id < 18) {
					FocusJumpTo(id + 1);
				}
				return true;
			}
			break;

		case VK_RETURN:
			if (id >= 1 && id <= 18) {

				GetDlgItem(IDC_EDIT1)->SetFocus();
				CString name;
				((CTagButton*)GetDlgItem(id))->GetWindowTextW(name);
				((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowTextW(name);
				mNameConfPanel.ShowPanel(SW_HIDE);
				mOtherConfPanel.MovePanel(0, -100);
				return true;
			}
			break;
			
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CCameraConfDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	mVolume = 5;
	InitNameItem();
	InitPanel();
	mSlider.SetRange(0,10,TRUE);
	mSlider.SetTicFreq(1);
	mSlider.SetPos(mVolume);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void CCameraConfDlg::ShowConfigurationOf(CCamera* whichCamera)
{
	if (whichCamera->userConf.name_inx == 0) {
		mCurrName.Format(_T("摄像机%d"), whichCamera->mId);
	}
	else if (whichCamera->userConf.name_inx <= 18) {
		((CTagButton*)GetDlgItem(whichCamera->userConf.name_inx))->GetWindowTextW(mCurrName);
	}

	mVolume = whichCamera->userConf.vol;
	
	if (whichCamera->userConf.switches & CAMERA_USER_CONF_ON) {
		mSwitcher.SetWindowTextW(_T("开"));
	}
	else {
		mSwitcher.SetWindowTextW(_T("关"));
	}

	if (whichCamera->userConf.switches & CAMERA_USER_CONF_UP) {
		mPicDirection.SetWindowTextW(_T("正着放"));
	}
	else {
		mPicDirection.SetWindowTextW(_T("倒着放"));
	}

	if (whichCamera->userConf.switches & CAMERA_USER_CONF_STORE) {
		mStoreSwitcher.SetWindowTextW(_T("开"));
	}
	else {
		mStoreSwitcher.SetWindowTextW(_T("关"));
	}

	if (whichCamera->userConf.switches & CAMERA_USER_CONF_AWATCH) {
		mAutoWatchSwitcher.SetWindowTextW(_T("开"));
	}
	else {
		mAutoWatchSwitcher.SetWindowTextW(_T("关"));
	}

	UpdateData(FALSE);
}



void CCameraConfDlg::InitPanel()
{
	for (int i = 0; i < 18; i++) {
		mNameConfPanel.AddWindow(GetDlgItem(i+1));
	}

	mOtherConfPanel.AddWindow(GetDlgItem(IDC_STATIC1));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_STATIC2));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_STATIC3));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_STATIC4));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_STATIC5));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_STATIC6));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_STATIC7));

	mOtherConfPanel.AddWindow(GetDlgItem(IDC_BUTTON1));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_BUTTON2));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_BUTTON3));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_BUTTON4));

	mOtherConfPanel.AddWindow(GetDlgItem(IDC_SLIDER1));
}



void CCameraConfDlg::InitNameItem()
{
	CString name;
	CRect rClient;

	GetClientRect(&rClient);

	RECT r = { 0 };

	int item_width = rClient.Width() / 9;
	int item_height = item_width / 2;
	//name.LoadStringW(IDS_STR_CAMERA_NAME_1);
	//mNameItems[0].Create(name, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, r, this, 1);


	for (int i = 0; i < 18; i++) {
		name.LoadStringW(IDS_STR_CAMERA_NAME_1+i);

		r.left = rClient.left + (i % 4) * item_width + item_width;
		r.top = rClient.top + (i / 4) * item_height + item_height;
		r.right = r.left + item_width;
		r.bottom = r.top + item_height;


		mNameItems[i].Create(name, WS_CHILD  | BS_PUSHBUTTON, r, this, i+1);
		mNameItems[i].SetFont(GetFont() , true);
	}
}



void CCameraConfDlg::Layout()
{
	CRect rClient;
	GetClientRect(&rClient);

	CWnd* pItem;
	int label_x, label_y,label_width, label_height;

	// 
	label_x = rClient.left + rClient.Width() / 8;
	label_y = rClient.top + rClient.Height() / 10;
	label_width = 80;
	label_height = 30;

	pItem = GetDlgItem(IDC_STATIC);
	pItem->MoveWindow(label_x, label_y, label_width, label_height, TRUE);

}


afx_msg LRESULT CCameraConfDlg::OnUserMsgGiveFocus(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_EDIT1)->SetFocus();

	return 0;
}


afx_msg LRESULT CCameraConfDlg::OnUserMsgDeviceConfig(WPARAM wParam, LPARAM lParam)
{	
	pCamera = CCameraManager::getInstance()->mLoginDevice[wParam-1];
	if (pCamera != NULL) {
		//   刷新设置项
		ShowConfigurationOf(pCamera);
	}
	return 0;
}


void CCameraConfDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int curpos = mSlider.GetPos();
	switch (nSBCode)
	{
	case SB_ENDSCROLL:
		if (mVolume != curpos)
		{
			mVolume = curpos;
			TRACE(_T("mVolume = %d\n"), mVolume);
			Util::LoadOrder(mOrder, 0x24,0x01, 0x02, 0x01, mVolume, 0, pCamera);
			TRACE("%s\n", pCamera->mCommonNetConfig.sMac);
			TRACE("%0x %0x %0x %0x %0x %0x %0x %0x %0x %0x %0x %0x %0x %0x %0x\n", mOrder[1], mOrder[2], mOrder[3], mOrder[4], mOrder[5], mOrder[6], mOrder[7], mOrder[8], mOrder[9], mOrder[10], mOrder[11], mOrder[12], mOrder[13], mOrder[14], mOrder[15]);
			((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->m_SerialPortCom.WriteToPort(mOrder, 17);
		}
		break;
	}	
	CDialogEx::OnHScroll(nSBCode, mVolume, pScrollBar);

}


void CCameraConfDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	ASSERT(pCamera != NULL);

	// 本来是开启，结果点击了
	if (pCamera->userConf.switches & CAMERA_USER_CONF_ON) {
		CCameraOffConfirmDlg dlg;
		if (dlg.DoModal() == IDOK) {
			TRACE("确定关闭摄像机\n");
			mSwitcher.SetWindowTextW(_T("关"));
			pCamera->userConf.switches &= (~CAMERA_USER_CONF_ON);
			::SendMessage(((CColyEyeApp*)AfxGetApp())->m_pWallWnd->m_hWnd, USER_MSG_DEVICE_CONFIG, false, (LPARAM)pCamera);
		}
		else {
			TRACE("取消关闭摄像机\n");
		}
	}
	// 本来是关闭，现在开启
	else {
		mSwitcher.SetWindowTextW(_T("开"));
		pCamera->userConf.switches |= CAMERA_USER_CONF_ON;
		::SendMessage(((CColyEyeApp*)AfxGetApp())->m_pWallWnd->m_hWnd, USER_MSG_DEVICE_CONFIG, true, (LPARAM)pCamera);
	}
}


/**@brief 控制视频方向按钮
 *
 */
void CCameraConfDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	ASSERT(pCamera != NULL);


}


/**@brief 视频存储功能开关
 *
 */
void CCameraConfDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	ASSERT(pCamera != NULL);

	//本来开启了存储，结果悲剧了，点了关闭
	if (pCamera->userConf.switches & CAMERA_USER_CONF_STORE) {
		CCameraStoreOffConfirmDlg dlg;
		if (dlg.DoModal() == IDOK) {
			mStoreSwitcher.SetWindowTextW(_T("关闭"));
			pCamera->userConf.switches &= (~CAMERA_USER_CONF_STORE);
			::SendMessage(((CColyEyeApp*)AfxGetApp())->m_pWallWnd->m_hWnd, USER_MSG_DEVICE_CONFIG, false, (LPARAM)pCamera);
		}
	}
	// 本来是关闭，现在开启
	else {
		mStoreSwitcher.SetWindowTextW(_T("开启"));
		pCamera->userConf.switches |= CAMERA_USER_CONF_STORE;
		::SendMessage(((CColyEyeApp*)AfxGetApp())->m_pWallWnd->m_hWnd, USER_MSG_DEVICE_CONFIG, true, (LPARAM)pCamera);
	}
}


/**@brief 自动看船功能开关
 *
 */
void CCameraConfDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//本来开启了自动看船，结果悲剧了，点了关闭
	if (pCamera->userConf.switches & CAMERA_USER_CONF_AWATCH) {
		//CCameraStoreOffConfirmDlg dlg;
		//if (dlg.DoModal() == IDOK) {
		    mAutoWatchSwitcher.SetWindowTextW(_T("关闭"));
			pCamera->userConf.switches &= (~CAMERA_USER_CONF_AWATCH);
			::SendMessage(((CColyEyeApp*)AfxGetApp())->m_pWallWnd->m_hWnd, USER_MSG_DEVICE_CONFIG, false, (LPARAM)pCamera);
		//}
	}
	// 本来是关闭，现在开启
	else {
		mAutoWatchSwitcher.SetWindowTextW(_T("开启"));
		pCamera->userConf.switches |= CAMERA_USER_CONF_AWATCH;
		::SendMessage(((CColyEyeApp*)AfxGetApp())->m_pWallWnd->m_hWnd, USER_MSG_DEVICE_CONFIG, true, (LPARAM)pCamera);
	}
}

