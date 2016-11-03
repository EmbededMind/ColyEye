// AutoWatchSoundConfirmDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "AutoWatchSoundConfirmDlg.h"
#include "afxdialogex.h"


// CAutoWatchSoundConfirmDlg 对话框

IMPLEMENT_DYNAMIC(CAutoWatchSoundConfirmDlg, CDialogEx)

CAutoWatchSoundConfirmDlg::CAutoWatchSoundConfirmDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTO_WATCH_ALM_SND_CONFIRM, pParent)
{

}

CAutoWatchSoundConfirmDlg::~CAutoWatchSoundConfirmDlg()
{
}

void CAutoWatchSoundConfirmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAutoWatchSoundConfirmDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAutoWatchSoundConfirmDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAutoWatchSoundConfirmDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoWatchSoundConfirmDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAutoWatchSoundConfirmDlg 消息处理程序


void CAutoWatchSoundConfirmDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	DeleteFile(_T("voice_g711a_alarm"));
	CFile::Rename(_T("voice_g711a"), _T("voice_g711a_alarm"));
	CDialogEx::OnOK();
}


void CAutoWatchSoundConfirmDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	DeleteFile(_T("voice_g711a"));
	CDialogEx::OnOK();
}


void CAutoWatchSoundConfirmDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	DeleteFile(_T("voice_g711a"));
	CDialogEx::OnCancel();
}
