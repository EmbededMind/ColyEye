// AutoWatchLogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "AutoWatchLogDlg.h"
#include "afxdialogex.h"


// CAutoWatchLogDlg 对话框

IMPLEMENT_DYNAMIC(CAutoWatchLogDlg, CDialogEx)

CAutoWatchLogDlg::CAutoWatchLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTO_WATCH_LOG, pParent)
{

}

CAutoWatchLogDlg::~CAutoWatchLogDlg()
{
}

void CAutoWatchLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAutoWatchLogDlg, CDialogEx)
END_MESSAGE_MAP()


// CAutoWatchLogDlg 消息处理程序
