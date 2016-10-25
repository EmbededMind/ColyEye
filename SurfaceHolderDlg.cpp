// SurfaceHolderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "SurfaceHolderDlg.h"
#include "afxdialogex.h"


// CSurfaceHolderDlg 对话框

IMPLEMENT_DYNAMIC(CSurfaceHolderDlg, CDialogEx)

CSurfaceHolderDlg::CSurfaceHolderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SURFACE_HOLDER, pParent)
{

}

CSurfaceHolderDlg::~CSurfaceHolderDlg()
{
}

void CSurfaceHolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSurfaceHolderDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CSurfaceHolderDlg 消息处理程序


BOOL CSurfaceHolderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	RECT r;
	GetClientRect(&r);

	///创建SurfaceHolder中的Surface
	mSurface.Create(IDD_SURFACE, this);
	mSurface.ShowWindow(SW_SHOW);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSurfaceHolderDlg::OnSize(UINT nType, int cx, int cy)
{

	if (IsWindow(mSurface.m_hWnd)) {
		RECT r;
		GetClientRect(&r);
		mSurface.MoveWindow(r.left+1, r.top+1, r.right-r.left-2, r.bottom-r.top-41, TRUE);
	}
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
}


void CSurfaceHolderDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (GetFocus() == this) {
		TRACE("Holder hold focus\n");
	}
	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
