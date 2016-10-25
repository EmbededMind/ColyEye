#include "stdafx.h"
#include "TagButton.h"


CTagButton::CTagButton()
{
	mTagVal = 1;
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
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CTagButton::OnNMCustomdraw)
END_MESSAGE_MAP()


void CTagButton::OnSetFocus(CWnd* pOldWnd)
{
	CButton::OnSetFocus(pOldWnd);
	::SendMessage(GetParent()->m_hWnd, USER_MSG_NOTIFY_FOCUS, true, this->GetDlgCtrlID());	                                   
	// TODO: 在此处添加消息处理程序代码
}


void CTagButton::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	//ModifyStyle(0, BS_OWNERDRAW);
	ModifyStyle(0, BS_NOTIFY);

	CButton::PreSubclassWindow();
}




void CTagButton::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMCD->dwDrawStage == CDDS_PREPAINT) {
		CDC* pDC = CDC::FromHandle(pNMCD->hdc);
		int nSaveDC = pDC->SaveDC();
		VERIFY(pDC);
		if (mTagVal != 0)
			pDC->DrawText(_T("2"), &pNMCD->rc, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);
		pDC->RestoreDC(nSaveDC);

		*pResult = CDRF_DODEFAULT;
		return;
	}

	*pResult = 0;
}

