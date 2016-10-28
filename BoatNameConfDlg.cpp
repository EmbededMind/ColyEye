// BoatNameConfDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "BoatNameConfDlg.h"
#include "afxdialogex.h"


// CBoatNameConfDlg 对话框

IMPLEMENT_DYNAMIC(CBoatNameConfDlg, CDialogEx)

CBoatNameConfDlg::CBoatNameConfDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BOATNAME_CONF, pParent)
{

}

CBoatNameConfDlg::~CBoatNameConfDlg()
{
}


void CBoatNameConfDlg::Layout()
{
	CRect rClient;
	GetClientRect(rClient);

	// 船舶名称编辑框位于客户区水平 1/5 到 4/5 
	//                       垂直 1/10 到 1/10 + 30
	int name_edit_width = rClient.Width() * 3 / 5;
	int name_edit_x = (rClient.Width() - name_edit_width) / 2 + rClient.left;
	int name_edit_y = rClient.top + rClient.Height() / 10;


	CWnd* pWnd = GetDlgItem(IDC_EDIT1);
	pWnd->MoveWindow(name_edit_x, name_edit_y, name_edit_width, 30, TRUE);

	// '船舶名称' 静态文本位于编辑框前 80 处
	pWnd = GetDlgItem(IDC_STATIC);
	pWnd->MoveWindow(name_edit_x - 80, name_edit_y, 80, 30, TRUE);

	// 保存按钮宽为编辑框宽度的 1/10 高与编辑框相同
	// 按钮与编辑框右边相接，上下边对齐。
	pWnd = GetDlgItem(IDC_BUTTON1);
	pWnd->MoveWindow(name_edit_x+name_edit_width, name_edit_y, name_edit_width/10, 30, TRUE);
}



void CBoatNameConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBoatNameConfDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CBoatNameConfDlg 消息处理程序


void CBoatNameConfDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CWnd* pWnd = GetDlgItem(IDC_EDIT1);
	if (pWnd && IsWindow(pWnd->m_hWnd)) {
		Layout();
	}
}
