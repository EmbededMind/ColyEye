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
 void VirtualPanel::AddWindow(CWnd* pWnd)
{
	mWndPtrList.push_back(pWnd);
}



/**@brief 将制定窗口从虚拟面板中移除
 *
 * @param [in] pWnd 要移除的窗口的指针
 * @see   VirtualPanel::RemoveWindow(CWnd& wnd);
 */
void VirtualPanel::RemoveWindow(CWnd* pWnd)
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
	
	CWnd* pWnd;
	CWnd* pParentWnd;

	TRACE("panel size:%d\n", mWndPtrList.size());

	std::list<CWnd*>::iterator iter;

	CRect r;

	CRect rParentClient;

	pParentWnd = (*mWndPtrList.begin())->GetParent();

	pParentWnd->GetWindowRect(&rParentClient);

	for (iter = mWndPtrList.begin(); iter != mWndPtrList.end(); iter++) {
		pWnd = *iter;

		pWnd->ShowWindow(SW_HIDE);
		pWnd->GetWindowRect(&r);
	
		pWnd->MoveWindow(r.left-rParentClient.left+dx, 
			r.top-rParentClient.top+dy, 
			r.Width(), r.Height(), true);
		pWnd->ShowWindow(SW_SHOW);
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



/**@brief Panels是否可见
 *
 * @return 可见返回true,反之返回false
 */
BOOL VirtualPanel::IsVisible()
{
	return (*mWndPtrList.begin())->IsWindowVisible();
}