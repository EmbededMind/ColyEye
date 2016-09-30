// HomeWatchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "HomeWatchDlg.h"
#include "afxdialogex.h"


// CHomeWatchDlg 对话框

IMPLEMENT_DYNAMIC(CHomeWatchDlg, CDialogEx)

CHomeWatchDlg::CHomeWatchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HOME_WATCH, pParent)
{

}

CHomeWatchDlg::~CHomeWatchDlg()
{
}

void CHomeWatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHomeWatchDlg, CDialogEx)
	ON_MESSAGE(USER_MSG_NOTIFY_FOCUS, &CHomeWatchDlg::OnUserMsgNotifyFocus)
END_MESSAGE_MAP()


// CHomeWatchDlg 消息处理程序


afx_msg LRESULT CHomeWatchDlg::OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam)
{
	this->SetFocus();
	return 0;
}
