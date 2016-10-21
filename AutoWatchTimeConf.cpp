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


// CAutoWatchTimeConf ��Ϣ�������


BOOL CAutoWatchTimeConfDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	mBeginTimePicker = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER3);
	mBeginTimePicker->SetFormat(_T("HH:mm"));
	mBeginTimePicker->SetTime(&CTime(host.mConfuration.watch_time_begining));

	mEndTimePicker = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER1);
	mEndTimePicker->SetFormat(_T("HH:mm"));
	mEndTimePicker->SetTime(&CTime(host.mConfuration.watch_time_begining+host.mConfuration.watch_time_span));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CAutoWatchTimeConfDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	DWORD begin_time = mWatchTimeBegining.GetHour() * 3600 + mWatchTimeBegining.GetMinute() * 60;
	DWORD end_time = mWatchTimeEnding.GetHour() * 3600 + mWatchTimeEnding.GetMinute() * 60 ;
	DWORD span = (end_time >= begin_time ? end_time - begin_time : end_time + 24 * 3600 - begin_time);
	
	host.SetWatchTime(begin_time, span);
}
