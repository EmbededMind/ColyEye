#pragma once


// CSurface

class CSurface : public CWnd
{
	DECLARE_DYNAMIC(CSurface)

public:
	CSurface();
	virtual ~CSurface();

	void          SetUserData(DWORD data);
	DWORD         GetUserData();


protected:
	BOOL          RegisterWindowClass(HINSTANCE hInstance = NULL);


private:
	BOOL mHasFocused;
	DWORD mUserData;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnNcPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


