#pragma once
#include "afxwin.h"
#include "AutoWatchSoundConfirmDlg.h"
#include "RecordAlarmSound.h"

// CRecordAlarmAudioDlg �Ի���

class CRecordAlarmAudioDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRecordAlarmAudioDlg)

public:
	CRecordAlarmAudioDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRecordAlarmAudioDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECORD_ALM_SND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:


	//void StartRecord();
	//void StopRecord();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
	short tick_down;
	bool  isRecording;

	CButton mRecordSwt;
	CAutoWatchSoundConfirmDlg mConfirmDlg;
};
