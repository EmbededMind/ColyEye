#pragma once
#include "atltime.h"
#include "ATLComTime.h"


// CAutoWatchTimeConf 对话框

class CAutoWatchTimeConfDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoWatchTimeConfDlg)

public:
	CAutoWatchTimeConfDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAutoWatchTimeConfDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_WATCH_TIME_CONF };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();



public:
	afx_msg void OnBnClickedButton1();
private:
	CTime mWatchTimeBegining;
	CTime mWatchTimeEnding;
		CDateTimeCtrl* mEndTimePicker;
		CDateTimeCtrl* mBeginTimePicker;
public:
	COleDateTime mBegining;
};
