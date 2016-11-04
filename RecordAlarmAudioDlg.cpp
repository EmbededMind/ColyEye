// RecordAlarmAudioDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColyEye.h"
#include "RecordAlarmAudioDlg.h"
#include "afxdialogex.h"


// CRecordAlarmAudioDlg �Ի���

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


// CRecordAlarmAudioDlg ��Ϣ�������


void CRecordAlarmAudioDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (isRecording == false) {
		isRecording = true;
		tick_down = 60;
		mRecordSwt.SetWindowTextW(_T("60"));

		// TODO: �ڴ���ӿ�ʼ¼���Ĵ���

		//mRecorder.SetReocrdPath(_T("D:\\Record\\Sound\\tmp.wav"));
		//mRecorder.Record();
		for(int i = 0; i < 6; i++)
		{
			if (CCameraManager::getInstance()->mLoginDevice[i])
			{
				CRecordAlarmSound::getInstance()->Record(CCameraManager::getInstance()->mLoginDevice[i]);
			}
		}
		
		SetTimer(1, 1000, NULL);
	}
	else {
		isRecording = false;
		KillTimer(1);

		// TODO: �ڴ����ֹͣ¼���Ĵ���

		/*mRecorder.Save();*/
		CRecordAlarmSound::getInstance()->StopTalk();
		if (mConfirmDlg.DoModal() == IDOK) {
			OnCancel();
		}
		mRecordSwt.SetWindowTextW(_T("����"));
	}
	
	
}


void CRecordAlarmAudioDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (tick_down > 0) {
		tick_down--;
		CString str;
		str.Format(_T("%d"), tick_down);
		mRecordSwt.SetWindowTextW(str);
	}
	else {
		isRecording = false;
		KillTimer(1);

		// TODO: �ڴ����ֹͣ¼���Ĵ���
		// StopRecord();
		CRecordAlarmSound::getInstance()->StopTalk();

		if (mConfirmDlg.DoModal() == IDOK) {
			OnCancel();
		}

		mRecordSwt.SetWindowTextW(_T("����"));
	}
	CDialogEx::OnTimer(nIDEvent);
}


