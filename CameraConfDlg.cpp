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

END_MESSAGE_MAP()


// CCameraConfDlg 消息处理程序




BOOL CCameraConfDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam)
		{
		case VK_SPACE:
			if (GetFocus()->GetDlgCtrlID() == IDC_EDIT1) {
				TRACE("camera name edit space\n");
				if (mNameConfPanel.IsVisible()) {
					mNameConfPanel.ShowPanel(SW_HIDE);
					mOtherConfPanel.MovePanel(0, -100);
				}
				else {
					mNameConfPanel.ShowPanel(SW_SHOW);
					mOtherConfPanel.MovePanel(0, 100);
				}				
			 }
			return true;

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

		TRACE("item pos:(%d,%d)\n", r.left, r.top);
		mNameItems[i].Create(name, WS_CHILD  | BS_PUSHBUTTON, r, this, i+1);
		mNameItems[i].SetFont(GetFont() , true);
	}
}