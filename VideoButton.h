#pragma once


// CVideoButton

class CVideoButton : public CStatic
{
	DECLARE_DYNAMIC(CVideoButton)

public:
	CVideoButton();
	virtual ~CVideoButton();

protected:
	DWORD   mUserData;

public:
	void   SetUserData(DWORD data);
	DWORD  GetUserData();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnNcPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


