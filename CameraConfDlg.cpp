// CameraConfDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "CameraConfDlg.h"
#include "afxdialogex.h"


// CCameraConfDlg 对话框

IMPLEMENT_DYNAMIC(CCameraConfDlg, CDialogEx)

CCameraConfDlg::CCameraConfDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CAMERA_CONF, pParent)
	, mCurrName(_T(""))
	, mVolumn(0)
{

}

CCameraConfDlg::~CCameraConfDlg()
{
}

void CCameraConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mCurrName);
	DDX_Control(pDX, IDC_BUTTON1, mSwitch);
	DDX_Control(pDX, IDC_BUTTON2, mPicDirection);
	DDX_Slider(pDX, IDC_SLIDER1, mVolumn);
	DDX_Control(pDX, IDC_BUTTON3, mStoreSwitch);
	DDX_Control(pDX, IDC_BUTTON4, mAutoWatchSwitch);
}


BEGIN_MESSAGE_MAP(CCameraConfDlg, CDialogEx)

	ON_MESSAGE(USER_MSG_GIVE_FOCUS, &CCameraConfDlg::OnUserMsgGiveFocus)
	ON_MESSAGE(USER_MSG_DEVICE_CONFIG, &CCameraConfDlg::OnUserMsgDeviceConfig)
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
					FocusJumpTo(id -1);
				}
			}
			return true;

		case VK_RIGHT:
			if (id >= 1 && id <= 18) {
				if (id < 18) {
					FocusJumpTo(id+1);
				}
			}
			return true;

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
	InitNameItem();
	InitPanel();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
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
	RECT rClient;
	RECT r = {5, 45, 60, 30};
	GetClientRect(&rClient);


	//name.LoadStringW(IDS_STR_CAMERA_NAME_1);
	//mNameItems[0].Create(name, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, r, this, 1);


	for (int i = 0; i < 18; i++) {
		name.LoadStringW(IDS_STR_CAMERA_NAME_1+i);

		r.left = rClient.left + (i % 4) * 85 + 40;
		r.top = rClient.top + (i / 4) * 25 + 45;
		r.right = r.left + 80;
		r.bottom = r.top + 20;


		mNameItems[i].Create(name, WS_CHILD  | BS_PUSHBUTTON, r, this, i+1);
		mNameItems[i].SetFont(GetFont() , true);
	}
}

afx_msg LRESULT CCameraConfDlg::OnUserMsgGiveFocus(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_EDIT1)->SetFocus();

	return 0;
}


afx_msg LRESULT CCameraConfDlg::OnUserMsgDeviceConfig(WPARAM wParam, LPARAM lParam)
{
	pCamera = CCameraManager::getInstance()->findCameraById(wParam);
	if (pCamera != NULL) {
		//   刷新设置项
	}
	return 0;
}
