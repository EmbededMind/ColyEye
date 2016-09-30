#pragma once


// CPlayCtrlSlider

class CPlayCtrlSlider : public CSliderCtrl
{
	DECLARE_DYNAMIC(CPlayCtrlSlider)
public:
	int m_port;
public:
	CPlayCtrlSlider();
	virtual ~CPlayCtrlSlider();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


