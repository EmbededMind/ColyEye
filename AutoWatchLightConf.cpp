// AutoWatchLightConf.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "AutoWatchLightConf.h"
#include "afxdialogex.h"


// CAutoWatchLightConf 对话框

IMPLEMENT_DYNAMIC(CAutoWatchLightConfDlg, CDialogEx)

CAutoWatchLightConfDlg::CAutoWatchLightConfDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTO_WATCH_ALM_LIGHT_CONF, pParent)
{

}

CAutoWatchLightConfDlg::~CAutoWatchLightConfDlg()
{
}

void CAutoWatchLightConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAutoWatchLightConfDlg, CDialogEx)
END_MESSAGE_MAP()


// CAutoWatchLightConf 消息处理程序
