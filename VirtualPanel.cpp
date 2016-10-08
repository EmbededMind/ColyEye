#include "stdafx.h"
#include "VirtualPanel.h"


VirtualPanel::VirtualPanel()
{
}


VirtualPanel::~VirtualPanel()
{
}


/**@brief �������������Ӵ���
 *
 * @param [in]  pWnd Ҫ��ӵĴ��ڵ�ָ��
 * @see   VirtualPanel::RemoveWindow(CWnd& wnd)
 */
__inline void VirtualPanel::AddWindow(CWnd* pWnd)
{
	mWndPtrList.push_back(pWnd);
}



/**@brief ���ƶ����ڴ�����������Ƴ�
 *
 * @param [in] pWnd Ҫ�Ƴ��Ĵ��ڵ�ָ��
 * @see   VirtualPanel::RemoveWindow(CWnd& wnd);
 */
__inline void VirtualPanel::RemoveWindow(CWnd* pWnd)
{
	mWndPtrList.remove(pWnd);
}


/**@brief ����������еĴ���ͳһ����ƫ��
 *
 * @param[in] dx x����ƫ����
 * @param[in] dy y����ƫ����
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



/**@brief ��ʾ��������������еĴ���
 *
 * @param[in] nCmdShow ��ʾ�������صĿ�������
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
