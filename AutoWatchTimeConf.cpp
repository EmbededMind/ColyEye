// AutoWatchTimeConf.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColyEye.h"
#include "AutoWatchTimeConf.h"
#include "afxdialogex.h"


// CAutoWatchTimeConf �Ի���

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
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoWatchTimeConfDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAutoWatchTimeConf ��Ϣ�������


BOOL CAutoWatchTimeConfDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	mBeginTimePicker = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER3);
	mBeginTimePicker->SetFormat(_T("HH:mm"));

	mEndTimePicker = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER1);
	mEndTimePicker->SetFormat(_T("HH:mm"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CAutoWatchTimeConfDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTime endTime;
	CTime beginTime;
	mEndTimePicker->GetTime(endTime);
	mBeginTimePicker->GetTime(beginTime);

	host.mConfuration.watch_time_begining = beginTime.GetHour() * 3600 + beginTime.GetMinute() * 60;

	DWORD end_time = endTime.GetHour() * 3600 + endTime.GetMinute() * 60 ;


	host.mConfuration.watch_time_span = (end_time >= host.mConfuration.watch_time_begining ? end_time - host.mConfuration.watch_time_begining :
		                                end_time + 24 * 3600 - host.mConfuration.watch_time_begining);
	TRACE("Auto watch time fragment:%S -- %S\n", beginTime.Format(_T("%y-%m-%d %H:%M:%S")), endTime.Format(_T("%y-%m-%d %H:%M:%S")));

}
