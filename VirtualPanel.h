#pragma once
#include <list>


class VirtualPanel
{
public:
	VirtualPanel();
	~VirtualPanel();

	void AddWindow(CWnd* pWnd);
	void RemoveWindow(CWnd* pWnd);
	void MovePanel(int dx, int dy);
	void ShowPanel(int nCmdShow);

private:
	std::list<CWnd*> mWndPtrList;
};

