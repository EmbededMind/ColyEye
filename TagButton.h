#pragma once
#include "afxwin.h"
class CTagButton :
	public CButton
{
public:
	CTagButton();
	~CTagButton();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	virtual void PreSubclassWindow();

protected:
	int mTagVal;
public:
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
};

