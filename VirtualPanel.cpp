#include "stdafx.h"
#include "VirtualPanel.h"


VirtualPanel::VirtualPanel()
{
}


VirtualPanel::~VirtualPanel()
{
}


/**@brief 向虚拟面板中添加窗口
 *
 * @param [in]  pWnd 要添加的窗口的指针
 * @see   VirtualPanel::RemoveWindow(CWnd& wnd)
 */
__inline void VirtualPanel::AddWindow(CWnd* pWnd)
{
	mWndPtrList.push_back(pWnd);
}



/**@brief 将制定窗口从虚拟面板中移除
 *
 * @param [in] pWnd 要移除的窗口的指针
 * @see   VirtualPanel::RemoveWindow(CWnd& wnd);
 */
__inline void VirtualPanel::RemoveWindow(CWnd* pWnd)
{
	mWndPtrList.remove(pWnd);
}


/**@brief 将虚拟面板中的窗口统一进行偏移
 *
 * @param[in] dx x方向偏移量
 * @param[in] dy y方向偏移量
 */
void VirtualPanel::MovePanel(int dx, int dy)
{
	CRect r;
	CWnd* pWnd;

	std::list<CWnd*>::iterator iter;


	for (iter = mWndPtrList.begin(); iter != mWndPtrList.end(); iter++) {
		//CWnd& wnd = *iter;
		//wnd.GetWindowRect(&r);
		//wnd.MoveWindow(r.left + dx, r.top + dy, r.Width(), r.Height(), true);
		pWnd = *iter;
		pWnd->GetWindowRect(&r);
		pWnd->MoveWindow(r.left+dx, r.top+dy, r.Width(), r.Height(), true);
	}
}



/**@brief 显示或隐藏虚拟面板中的窗口
 *
 * @param[in] nCmdShow 显示或者隐藏的控制命令
 */
void VirtualPanel::ShowPanel(int nCmdShow)
{
	CWnd* pWnd;
	std::list<CWnd*>::iterator iter;

	for (iter = mWndPtrList.begin(); iter != mWndPtrList.end(); iter++) {
		//CWnd& wnd = *iter;
		//wnd.ShowWindow(nCmdShow);
		pWnd = *iter;
		pWnd->ShowWindow(nCmdShow);
	}
}
