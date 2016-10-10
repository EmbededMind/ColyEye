// RecordAlarmAudioDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "RecordAlarmAudioDlg.h"
#include "afxdialogex.h"


// CRecordAlarmAudioDlg 对话框

IMPLEMENT_DYNAMIC(CRecordAlarmAudioDlg, CDialogEx)

CRecordAlarmAudioDlg::CRecordAlarmAudioDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RECORD_ALM_SND, pParent)
{

}

CRecordAlarmAudioDlg::~CRecordAlarmAudioDlg()
{
}

void CRecordAlarmAudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, mRecordSwt);
}


BEGIN_MESSAGE_MAP(CRecordAlarmAudioDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CRecordAlarmAudioDlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CRecordAlarmAudioDlg 消息处理程序


void CRecordAlarmAudioDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (isRecording == false) {
		isRecording = true;
		tick_down = 60;
		mRecordSwt.SetWindowTextW(_T("60"));

		// TODO: 在此添加开始录音的代码
		// StartRecord();

		SetTimer(1, 1000, NULL);
	}
	else {
		isRecording = false;
		KillTimer(1);

		// TODO: 在此添加停止录音的代码
		// StopRecord();

		mRecordSwt.SetWindowTextW(_T("手咪"));
		OnCancel();
	}
	
	
}


void CRecordAlarmAudioDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (tick_down > 0) {
		tick_down--;
		CString str;
		str.Format(_T("%d"), tick_down);
		mRecordSwt.SetWindowTextW(str);
	}
	else {
		isRecording = false;
		KillTimer(1);

		// TODO: 在此添加停止录音的代码
		// StopRecord();

		mRecordSwt.SetWindowTextW(_T("手咪"));
		OnOK();
	}
	CDialogEx::OnTimer(nIDEvent);
}


