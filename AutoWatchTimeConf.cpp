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
	//, mBegining(COleDateTime::GetCurrentTime())
	, _mWatchBegining(COleDateTime::GetCurrentTime())
	, _mWatchEnding(COleDateTime::GetCurrentTime())
	, mIsAutoWatchOn(FALSE)
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
	//DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, mWatchTimeEnding);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, _mWatchBegining);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, _mWatchEnding);
	DDX_Check(pDX, IDC_CHECK2, mIsAutoWatchOn);
}


BEGIN_MESSAGE_MAP(CAutoWatchTimeConfDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoWatchTimeConfDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK2, &CAutoWatchTimeConfDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CAutoWatchTimeConf 消息处理程序


BOOL CAutoWatchTimeConfDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mBeginTimePicker = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER3);
	mBeginTimePicker->SetFormat(_T("HH:mm"));

	mEndTimePicker = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER1);
	mEndTimePicker->SetFormat(_T("HH:mm"));

	TRACE("%d  %d\n", host.mConfuration.watch_time_begining, host.mConfuration.watch_time_span);

	COleDateTime time(1970, 1, 1, 0, 0, 0);
	_mWatchBegining = time + COleDateTimeSpan(0, host.mConfuration.watch_time_begining/3600,
		(host.mConfuration.watch_time_begining %3600) / 60, 0);
	_mWatchEnding = _mWatchBegining + COleDateTimeSpan(0, host.mConfuration.watch_time_span/3600,
		(host.mConfuration.watch_time_span%3600)/60, 0);

	mIsAutoWatchOn = host.mConfuration.auto_watch_switch;
	UpdateData(FALSE);




	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CAutoWatchTimeConfDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	DWORD begin_time = _mWatchBegining.GetHour() * 3600 + _mWatchBegining.GetMinute() * 60;
	DWORD end_time = _mWatchEnding.GetHour() * 3600 + _mWatchEnding.GetMinute() * 60 ;
	DWORD span = (end_time >= begin_time ? end_time - begin_time : end_time + 24 * 3600 - begin_time);

	host.SetWatchTime(begin_time, span);
}


void CAutoWatchTimeConfDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CTime t = CTime::GetCurrentTime();
	char sqlStmt[128];


	if (mIsAutoWatchOn) {
		host.mConfuration.auto_watch_switch = TRUE;
		mBeginTimePicker->EnableWindow(TRUE);
		mEndTimePicker->EnableWindow(TRUE);
		sprintf_s(sqlStmt, "INSERT INTO switch_log VALUES(%I64d, %d);", t.GetTime(), 1);
	}
	else {
		host.mConfuration.auto_watch_switch = FALSE;
		mBeginTimePicker->EnableWindow(FALSE);
		mEndTimePicker->EnableWindow(FALSE);
		sprintf_s(sqlStmt, "INSERT INTO switch_log VALUES(%I64d, %d);", t.GetTime(), 0);
	}

	if (!sqlite.DirectStatement(sqlStmt)) {
		TRACE("sql stmt error:%s\n", sqlStmt);
	}
}



void CAutoWatchTimeConfDlg::OnBack()
{

}


BOOL CAutoWatchTimeConfDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam)
		{
		case VK_BACK:
			TRACE("AutoWatchTimeConf case back\n");
			return true;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
