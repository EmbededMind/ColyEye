// PlayCtrlSlider.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "PlayCtrlSlider.h"


// CPlayCtrlSlider

IMPLEMENT_DYNAMIC(CPlayCtrlSlider, CSliderCtrl)

CPlayCtrlSlider::CPlayCtrlSlider()
{

}

CPlayCtrlSlider::~CPlayCtrlSlider()
{
}


BEGIN_MESSAGE_MAP(CPlayCtrlSlider, CSliderCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CPlayCtrlSlider 消息处理程序



void CPlayCtrlSlider::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CSliderCtrl::OnLButtonDown(nFlags, point);
	CRect rect;
	GetClientRect(rect);
	int nMin = 0;
	int nMax = 0;
	GetRange(nMin, nMax);
	point.x = point.x - rect.left;
	int pos = nMin + (nMax - nMin) * point.x / (rect.Width() - 5);
	this->SetPos(pos);
	H264_PLAY_SetPlayPos(m_port, (float)pos / 100.0);

}
