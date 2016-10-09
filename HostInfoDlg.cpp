// HostInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "HostInfoDlg.h"
#include "afxdialogex.h"


// CHostInfoDlg 对话框

IMPLEMENT_DYNAMIC(CHostInfoDlg, CDialogEx)

CHostInfoDlg::CHostInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HOSTINFO, pParent)
{

}

CHostInfoDlg::~CHostInfoDlg()
{
}

void CHostInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHostInfoDlg, CDialogEx)
END_MESSAGE_MAP()


// CHostInfoDlg 消息处理程序
