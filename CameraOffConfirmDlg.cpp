// CameraOffConfirmDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "CameraOffConfirmDlg.h"
#include "afxdialogex.h"


// CCameraOffConfirmDlg 对话框

IMPLEMENT_DYNAMIC(CCameraOffConfirmDlg, CDialogEx)

CCameraOffConfirmDlg::CCameraOffConfirmDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OFF_CONFIRM, pParent)
{

}

CCameraOffConfirmDlg::~CCameraOffConfirmDlg()
{
}

void CCameraOffConfirmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCameraOffConfirmDlg, CDialogEx)
END_MESSAGE_MAP()


// CCameraOffConfirmDlg 消息处理程序
