#pragma once
#include "RecordAlarmAudioDlg.h"

// CAutoWatchSoundConfDlg �Ի���

class CAutoWatchSoundConfDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoWatchSoundConfDlg)

public:
	CAutoWatchSoundConfDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAutoWatchSoundConfDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_WATCH_ALM_SND_CONF };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

private:
	CRecordAlarmAudioDlg mRecordAlarmAudioDlg;

};
