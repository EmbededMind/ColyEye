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
	this->SetFocus();
	return 0;
}
