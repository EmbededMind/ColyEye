// VideoButton.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "VideoButton.h"


// CVideoButton

IMPLEMENT_DYNAMIC(CVideoButton, CStatic)

CVideoButton::CVideoButton()
{

}

CVideoButton::~CVideoButton()
{
}


void CVideoButton::SetUserData(DWORD data)
{
	this->mUserData = data;
}


DWORD CVideoButton::GetUserData()
{
	return this->mUserData;
}


BEGIN_MESSAGE_MAP(CVideoButton, CButton)
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// CVideoButton 消息处理程序




void CVideoButton::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CButton::OnPaint()
	CStatic::OnPaint();
}


void CVideoButton::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CButton::OnNcPaint()
	//CDialogEx::OnNcPaint();

	//if (!mIsSelected) {
	//	return;
	//}
	if (GetFocus() != this) {
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


void CVideoButton::OnSetFocus(CWnd* pOldWnd)
{
	CStatic::OnSetFocus(pOldWnd);
	OnNcPaint();
	// TODO: 在此处添加消息处理程序代码
}


void CVideoButton::OnKillFocus(CWnd* pNewWnd)
{
	CStatic::OnKillFocus(pNewWnd);
	OnNcPaint();
	// TODO: 在此处添加消息处理程序代码
}
