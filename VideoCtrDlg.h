#pragma once
#include "VideoDlg.h"
#include "RecordFileInfo.h"
#include "afxcmn.h"
#include "PlayCtrlSlider.h"

// VideoCtrDlg 对话框

class CVideoCtrDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVideoCtrDlg)

public:
	CVideoCtrDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVideoCtrDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDEOCTR_DIALOG };
#endif
private:
	long m_port;
	BOOL m_pause;
	BOOL m_playctrl;
	BOOL m_isPlay;
	int m_pos;
	int m_totaltime;
	int m_currenttime;
	BOOL m_isOnHScroll;
	CPlayCtrlSlider m_sliderctrl;
public:
	int mMenuCursor;
	CRecordFileInfo *m_pRecordFileInfo;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CVideoDlg mVideoDlg;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	afx_msg LRESULT OnUserMsgPlay(WPARAM wParam, LPARAM lParam);
public:
	BOOL StartPlay();
	BOOL StopPlay();

	afx_msg void OnBnClickedPlayButton();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	
	afx_msg void OnBnClickedPauseButton();
	afx_msg void OnBnClickedSlowButton();
	afx_msg void OnBnClickedFastButton();
	afx_msg void OnBnClickedNextButton();
	afx_msg void OnBnClickedPrevfButton();

	afx_msg void OnBnClickedPausButton();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
