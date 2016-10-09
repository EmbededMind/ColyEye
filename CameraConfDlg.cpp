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


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void CCameraConfDlg::InitPanel()
{
	
}



void CCameraConfDlg::InitNameItem()
{
	for (int i = 0; i < 18; i++) {
		
	}
}