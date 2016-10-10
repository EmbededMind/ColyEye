// AutoWatchTimeConf.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "AutoWatchTimeConf.h"
#include "afxdialogex.h"


// CAutoWatchTimeConf 对话框

IMPLEMENT_DYNAMIC(CAutoWatchTimeConfDlg, CDialogEx)

CAutoWatchTimeConfDlg::CAutoWatchTimeConfDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTO_WATCH_TIME_CONF, pParent)
{

}

CAutoWatchTimeConfDlg::~CAutoWatchTimeConfDlg()
{
}

void CAutoWatchTimeConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAutoWatchTimeConfDlg, CDialogEx)
END_MESSAGE_MAP()


// CAutoWatchTimeConf 消息处理程序


BOOL CAutoWatchTimeConfDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	mTimePicker = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER3);
	mTimePicker->SetFormat(_T("hh:mm"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
