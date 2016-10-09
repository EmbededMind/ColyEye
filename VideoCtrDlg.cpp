// VideoCtrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "VideoCtrDlg.h"
#include "afxdialogex.h"
#include "ColyEyeDlg.h"
#include "atlconv.h"
#include "PlayCtrlSlider.h"
// VideoCtrDlg 对话框

void __stdcall  EOFCallBack(LONG nPort, LONG nUser);

IMPLEMENT_DYNAMIC(CVideoCtrDlg, CDialogEx)

CVideoCtrDlg::CVideoCtrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VIDEOCTR_DIALOG, pParent)
{
}

CVideoCtrDlg::~CVideoCtrDlg()
{
}

void CVideoCtrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVideoCtrDlg, CDialogEx)
	ON_MESSAGE(USER_MSG_PLAY, &CVideoCtrDlg::OnUserMsgPlay)
	ON_BN_CLICKED(IDC_PLAY_BUTTON, &CVideoCtrDlg::OnBnClickedPlayButton)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_PAUSE_BUTTON, &CVideoCtrDlg::OnBnClickedPauseButton)
	ON_BN_CLICKED(IDC_SLOW_BUTTON, &CVideoCtrDlg::OnBnClickedSlowButton)
	ON_BN_CLICKED(IDC_FAST_BUTTON, &CVideoCtrDlg::OnBnClickedFastButton)
	ON_BN_CLICKED(IDC_NEXT_BUTTON, &CVideoCtrDlg::OnBnClickedNextButton)
	ON_BN_CLICKED(IDC_PREVF_BUTTON, &CVideoCtrDlg::OnBnClickedPrevfButton)
END_MESSAGE_MAP()


// VideoCtrDlg 消息处理程序


BOOL CVideoCtrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_port = 1;
	m_pause = 0;
	m_isPlay = 0;

	m_totaltime = 1;
	m_playctrl = 0;
	mVideoDlg.Create(IDD_VIDEO_DIALOG, this);
	mVideoDlg.ShowWindow(SW_SHOW);
	if (m_sliderctrl.SubclassDlgItem(IDC_PLAY_SLIDER, this)) {

	}
	else {
		TRACE("sub class fail\n");
	}
	m_sliderctrl.SetRange(0, 100, TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

LRESULT CVideoCtrDlg::OnUserMsgPlay(WPARAM wParam, LPARAM lParam)
{
	mMenuCursor = wParam;
	TRACE("cursor = %d\n", mMenuCursor);
	m_pRecordFileInfo = (CRecordFileInfo *)lParam;
	m_pRecordFileInfo->mBeingUsed = true;
	m_pRecordFileInfo->mStatus |= 0x02;
	TRACE("%ld\n", m_pRecordFileInfo->mBeginTime);
	m_pause = 0;
	m_isPlay = 0;
	m_playctrl = 0;
	StartPlay();
	return 0;
}

BOOL CVideoCtrDlg::StartPlay()
{
	SetTimer(m_port , 100, NULL);
	CString PlayPath("E:\\Record");
	CString tmp;
	if (m_pRecordFileInfo->mStatus & RECORD_TYPE_NORMAL)
	{
		PlayPath += _T("\\normal");
	}
	else
	{
		PlayPath += _T("\\alarm");
	}
	tmp.Format(_T("\\%d\\%d%02d%02d%02d%02d%02d.h264"), m_pRecordFileInfo->mOwner, m_pRecordFileInfo->mBeginTime.GetYear(), m_pRecordFileInfo->mBeginTime.GetMonth(),
		m_pRecordFileInfo->mBeginTime.GetDay(), m_pRecordFileInfo->mBeginTime.GetHour(), m_pRecordFileInfo->mBeginTime.GetMinute(), m_pRecordFileInfo->mBeginTime.GetSecond());
	PlayPath += tmp;
	TRACE("%S\n", PlayPath);
	((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->mMenu.ShowWindow(SW_HIDE);
	this->ShowWindow(SW_SHOW);
	this->mVideoDlg.MoveWindow(135, 5, 535, 300);
	this->mVideoDlg.ShowWindow(SW_SHOW);
	this->SetFocus();
	H264_PLAY_GetPort(&m_port);
	m_sliderctrl.m_port = this->m_port;
	USES_CONVERSION;
	const char * ptr = T2CA(PlayPath);
	if (!H264_PLAY_OpenFile(m_port, ptr)) {
		TRACE("Open video file failed!\n");
	}
	H264_PLAY_Play(m_port, this->mVideoDlg.m_hWnd);
	H264_PLAY_SetFileEndCallBack(m_port, EOFCallBack, (LONG)this);
	m_totaltime = H264_PLAY_GetFileTime(m_port);
	m_isPlay = true;
	return 0;
}

BOOL CVideoCtrDlg::StopPlay()
{
	KillTimer(m_port);
	H264_PLAY_Stop(m_port);
	H264_PLAY_CloseFile(m_port);
	H264_PLAY_FreePort(m_port);
	m_pRecordFileInfo->mBeingUsed = false;
	m_pRecordFileInfo->mStatus &= ~(0x02);
	m_isPlay = false;
	return 0;
}



BOOL CVideoCtrDlg::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_BACK:
			m_pos = 0;
			StopPlay();
			this->ShowWindow(SW_HIDE);
			::SendMessage(((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->mMenu.m_hWnd, USER_MSG_PLAY, mMenuCursor, (LPARAM)m_pRecordFileInfo);
			return true;
		}
	}
	else if (pMsg->message == WM_CONTEXTMENU) {

		return true;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CVideoCtrDlg::OnBnClickedPlayButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_isPlay)
	{
		if (m_pause)
		{
			H264_PLAY_Pause(m_port, 0);
			m_pause = 0;
		}
		if (m_playctrl)
		{
			H264_PLAY_Play(m_port, this->mVideoDlg.m_hWnd);
			m_playctrl = 0;
		}
	}
	else
	{
		StartPlay();
	}
}


void CVideoCtrDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!m_isOnHScroll)
	{
		m_currenttime = H264_PLAY_GetPlayedTime(m_port);
		if (m_currenttime)
		    m_sliderctrl.SetPos((int)(m_currenttime * 100 / m_totaltime));
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CVideoCtrDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nSBCode == SB_THUMBPOSITION)
	{
		m_isOnHScroll = 0;
		m_pos = nPos;
	    H264_PLAY_SetPlayPos(m_port, (float)m_pos/100.0);
		H264_PLAY_GetLastError(m_port);		
	}
	if (nSBCode == SB_THUMBTRACK)
	{
		m_isOnHScroll = 1;
		m_pos = nPos;
		H264_PLAY_SetPlayPos(m_port, (float)m_pos / 100.0);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CVideoCtrDlg::OnBnClickedPauseButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_pause)
	{
		H264_PLAY_Pause(m_port, 1);
		m_pause = 1;
	}
}



void CVideoCtrDlg::OnBnClickedSlowButton()
{
	// TODO: 在此添加控件通知处理程序代码
	H264_PLAY_Slow(m_port);
	m_playctrl = 1;
}


void CVideoCtrDlg::OnBnClickedFastButton()
{
	// TODO: 在此添加控件通知处理程序代码
	H264_PLAY_Fast(m_port);
	m_playctrl = 1;
}


void CVideoCtrDlg::OnBnClickedNextButton()
{
	// TODO: 在此添加控件通知处理程序代码
	H264_PLAY_NextFrame(m_port);
	m_playctrl = 1;
}


void CVideoCtrDlg::OnBnClickedPrevfButton()
{
	// TODO: 在此添加控件通知处理程序代码
	H264_PLAY_PrevFrame(m_port);
	m_playctrl = 1;
}

void __stdcall EOFCallBack(LONG nPort, LONG nUser)
{
	((CVideoCtrDlg *)nUser)->StopPlay();
}
