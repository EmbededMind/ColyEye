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
	// TODO: �ڴ˴������Ϣ����������
}


void CTagButton::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	//ModifyStyle(0, BS_OWNERDRAW);
	ModifyStyle(0, BS_NOTIFY);

	CButton::PreSubclassWindow();
}




void CTagButton::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

