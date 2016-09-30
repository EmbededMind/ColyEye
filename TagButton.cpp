#include "stdafx.h"
#include "TagButton.h"


CTagButton::CTagButton()
{
}


CTagButton::~CTagButton()
{
}


BOOL CTagButton::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_CONTEXTMENU){
		TRACE("tag button case wm_contextmenu\n");
	}
	return CButton::PreTranslateMessage(pMsg);
}


BEGIN_MESSAGE_MAP(CTagButton, CButton)
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


void CTagButton::OnSetFocus(CWnd* pOldWnd)
{
	CButton::OnSetFocus(pOldWnd);
	::SendMessage(GetParent()->m_hWnd, USER_MSG_NOTIFY_FOCUS, true, this->GetDlgCtrlID());	                                   
	// TODO: 在此处添加消息处理程序代码
}
