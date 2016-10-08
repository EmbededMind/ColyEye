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


