#pragma once
#include "RecordAlarmAudioDlg.h"

// CAutoWatchSoundConfDlg 对话框

class CAutoWatchSoundConfDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoWatchSoundConfDlg)

public:
	CAutoWatchSoundConfDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAutoWatchSoundConfDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_WATCH_ALM_SND_CONF };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

private:
	CRecordAlarmAudioDlg mRecordAlarmAudioDlg;

};
