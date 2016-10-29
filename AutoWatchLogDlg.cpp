// AutoWatchLogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "AutoWatchLogDlg.h"
#include "afxdialogex.h"


// CAutoWatchLogDlg 对话框

IMPLEMENT_DYNAMIC(CAutoWatchLogDlg, CDialogEx)

CAutoWatchLogDlg::CAutoWatchLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTO_WATCH_LOG, pParent)
{

}

CAutoWatchLogDlg::~CAutoWatchLogDlg()
{
}

void CAutoWatchLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mLogText);
}


BEGIN_MESSAGE_MAP(CAutoWatchLogDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


void CAutoWatchLogDlg::Layout()
{
	CRect rClient;
	GetClientRect(rClient);

	mLogText.MoveWindow(rClient.left, rClient.top, rClient.Width(), rClient.Height(), TRUE);
}


void CAutoWatchLogDlg::ShowLog()
{
	//CStdioFile file();
}

// CAutoWatchLogDlg 消息处理程序


BOOL CAutoWatchLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CAutoWatchLogDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (IsWindow(mLogText)) {
		Layout();
	}
}
