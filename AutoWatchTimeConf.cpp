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
	, mWatchTimeBegining(0)
	, mWatchTimeEnding(0)
{

}

CAutoWatchTimeConfDlg::~CAutoWatchTimeConfDlg()
{
}

void CAutoWatchTimeConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, mWatchTimeBegining);
	//DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, mWatchTimeEnding);
}


BEGIN_MESSAGE_MAP(CAutoWatchTimeConfDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoWatchTimeConfDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAutoWatchTimeConf 消息处理程序


BOOL CAutoWatchTimeConfDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	mBeginTimePicker = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER3);
	mBeginTimePicker->SetFormat(_T("HH:mm"));
	mBeginTimePicker->SetTime(&CTime(host.mConfuration.watch_time_begining));

	mEndTimePicker = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER1);
	mEndTimePicker->SetFormat(_T("HH:mm"));
	mEndTimePicker->SetTime(&CTime(host.mConfuration.watch_time_begining+host.mConfuration.watch_time_span));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CAutoWatchTimeConfDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	DWORD begin_time = mWatchTimeBegining.GetHour() * 3600 + mWatchTimeBegining.GetMinute() * 60;
	DWORD end_time = mWatchTimeEnding.GetHour() * 3600 + mWatchTimeEnding.GetMinute() * 60 ;
	DWORD span = (end_time >= begin_time ? end_time - begin_time : end_time + 24 * 3600 - begin_time);
	
	host.SetWatchTime(begin_time, span);
}
