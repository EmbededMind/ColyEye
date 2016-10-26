// SurfaceHolderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColyEye.h"
#include "SurfaceHolderDlg.h"
#include "afxdialogex.h"


// CSurfaceHolderDlg �Ի���

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


// CSurfaceHolderDlg ��Ϣ�������


BOOL CSurfaceHolderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	RECT r;
	GetClientRect(&r);

	///����SurfaceHolder�е�Surface
	mSurface.Create(IDD_SURFACE, this);
	mSurface.ShowWindow(SW_SHOW);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CSurfaceHolderDlg::OnSize(UINT nType, int cx, int cy)
{

	if (IsWindow(mSurface.m_hWnd)) {
		RECT r;
		GetClientRect(&r);
		mSurface.MoveWindow(r.left+1, r.top+1, r.right-r.left-2, r.bottom-r.top-41, TRUE);
	}
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: �ڴ˴������Ϣ����������
}


void CSurfaceHolderDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (GetFocus() == this) {
		TRACE("Holder hold focus\n");
	}
	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
