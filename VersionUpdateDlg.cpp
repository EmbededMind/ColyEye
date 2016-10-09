// VersionUpdateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "VersionUpdateDlg.h"
#include "afxdialogex.h"


// CVersionUpdateDlg 对话框

IMPLEMENT_DYNAMIC(CVersionUpdateDlg, CDialogEx)

CVersionUpdateDlg::CVersionUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_UPDATE, pParent)
{

}

CVersionUpdateDlg::~CVersionUpdateDlg()
{
}

void CVersionUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVersionUpdateDlg, CDialogEx)
END_MESSAGE_MAP()


// CVersionUpdateDlg 消息处理程序
