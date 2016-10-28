// SurfaceHolderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "SurfaceHolderDlg.h"
#include "afxdialogex.h"


// CSurfaceHolderDlg 对话框

IMPLEMENT_DYNAMIC(CSurfaceHolderDlg, CDialogEx)

CSurfaceHolderDlg::CSurfaceHolderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SURFACE_HOLDER, pParent)
{

}

CSurfaceHolderDlg::~CSurfaceHolderDlg()
{
}

void CSurfaceHolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSurfaceHolderDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_NCPAINT()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


// CSurfaceHolderDlg 消息处理程序


BOOL CSurfaceHolderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rClient;
	GetClientRect(&rClient);

	

	///创建SurfaceHolder中的Surface
	//mSurface.Create(IDD_SURFACE, this);
	//mSurface.ShowWindow(SW_SHOW);
	mSurface.Create(NULL, NULL, WS_CHILDWINDOW, CRect(0, 0, 0, 0), this, 0);
	

	mSurface.SetWindowPos(NULL, rClient.left, rClient.top, rClient.Width(), rClient.Height(), 0);
	//int surface_width = (rClient.Height() - SURFACE_LABEL_OFFSET) * SURFACE_WH_SCALE;
	//mSurface.SetWindowPos(NULL, rClient.left+(rClient.Width()-surface_width)/2, rClient.top+ SURFACE_LABEL_OFFSET,
	//	surface_width, rClient.Height()-SURFACE_LABEL_OFFSET, 0);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSurfaceHolderDlg::OnSize(UINT nType, int cx, int cy)
{
	CRect rClient;
	GetClientRect(&rClient);

	if (IsWindow(mSurface.m_hWnd)) {
		mSurface.SetWindowPos(NULL,rClient.left, rClient.top, rClient.Width(), rClient.Height(), 0);
		//int surface_width = (rClient.Height() - SURFACE_LABEL_OFFSET) * SURFACE_WH_SCALE;
		//mSurface.SetWindowPos(NULL, rClient.left + (rClient.Width() - surface_width) / 2, rClient.top + SURFACE_LABEL_OFFSET,
		//	surface_width, rClient.Height() - SURFACE_LABEL_OFFSET, 0);
	}

	CDialogEx::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码

}




BOOL CSurfaceHolderDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类 
	if (pMsg->message == WM_KEYDOWN) {
		CString text;
		this->GetWindowTextW(text);
    	switch (pMsg->wParam)
		{
		case VK_LEFT:
			TRACE("%S  case left\n", text);
			::SendMessage(GetParent()->m_hWnd, USER_MSG_NOTIFY_ARROW,  pMsg->wParam, (LPARAM)this);
			break;
		case VK_RIGHT:
			TRACE("%S  case right\n", text);
			::SendMessage(GetParent()->m_hWnd, USER_MSG_NOTIFY_ARROW, pMsg->wParam, (LPARAM)this);
			break;
		case VK_UP:
			TRACE("SurfaceHolderDlg case up\n");
			::SendMessage(GetParent()->m_hWnd, USER_MSG_NOTIFY_ARROW, pMsg->wParam, (LPARAM)this);
			break;
		case VK_DOWN:
			TRACE("SurfaceHolderDlg case down\n");
			::SendMessage(GetParent()->m_hWnd, USER_MSG_NOTIFY_ARROW, pMsg->wParam, (LPARAM)this);
			break;
		}
	}
	else if (pMsg->message == WM_CONTEXTMENU)
	{
		TRACE("SurfaceHolderDlg case contextmenu\n");
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}



void CSurfaceHolderDlg::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnNcPaint()
	CDialogEx::OnNcPaint();

	if (!mIsSelected) {
		return;
	}

	HDC hDC = ::GetWindowDC(m_hWnd);
	CRect rc;
	::GetWindowRect(m_hWnd, &rc);
	rc = CRect(0, 0, rc.right - rc.left, rc.bottom - rc.top);

	::FrameRect(hDC, &rc, ::CreateSolidBrush(GetSysColor(COLOR_WINDOWFRAME)));
	rc.InflateRect(-1, -1);
	::FrameRect(hDC, &rc, ::CreateSolidBrush(GetSysColor(COLOR_WINDOWFRAME)));

	::ReleaseDC(m_hWnd, hDC);
}


void CSurfaceHolderDlg::OnKillFocus(CWnd* pNewWnd)
{
	CString holder_text;
	this->GetWindowTextW(holder_text);
	TRACE("Holder %S begin OnKillFocus\n", holder_text);

	CString text;
	pNewWnd->GetWindowTextW(text);
	TRACE("New window:%S\n", text);


	CDialogEx::OnKillFocus(pNewWnd);
	mIsSelected = FALSE;

	TRACE("Holder %S end OnKillFocus and flag is:%s\n", holder_text, mIsSelected ? "TRUE" : "FALSE");
	// TODO: 在此处添加消息处理程序代码
}





void CSurfaceHolderDlg::OnSetFocus(CWnd* pOldWnd)
{
	CString holder_text;
	this->GetWindowTextW(holder_text);
	TRACE("Holder %S begin OnSetFocus\n", holder_text);

    CString text;
	pOldWnd->GetWindowTextW(text);
	TRACE("Old window:%S\n", text);


	CDialogEx::OnSetFocus(pOldWnd);
	mIsSelected = TRUE;


	TRACE("Holder %S end OnSetFocus and flag is:%s\n", holder_text, mIsSelected?"TRUE":"FALSE");

	// TODO: 在此处添加消息处理程序代码
}
