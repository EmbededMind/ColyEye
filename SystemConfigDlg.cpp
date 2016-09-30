// SystemConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "SystemConfigDlg.h"
#include "afxdialogex.h"


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
END_MESSAGE_MAP()


// CSystemConfigDlg 消息处理程序


afx_msg LRESULT CSystemConfigDlg::OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam)
{
	this->SetFocus();
	return 0;
}
