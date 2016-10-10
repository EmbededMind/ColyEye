#pragma once
#include "afxwin.h"


// CRecordAlarmAudioDlg 对话框

class CRecordAlarmAudioDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRecordAlarmAudioDlg)

public:
	CRecordAlarmAudioDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRecordAlarmAudioDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECORD_ALM_SND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton mRecordSwt;

	//void StartRecord();
	//void StopRecord();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
	short tick_down;
	bool  isRecording;

};
