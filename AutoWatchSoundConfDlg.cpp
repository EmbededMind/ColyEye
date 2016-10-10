// AutoWatchSoundConfDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "AutoWatchSoundConfDlg.h"
#include "afxdialogex.h"



// CAutoWatchSoundConfDlg 对话框

IMPLEMENT_DYNAMIC(CAutoWatchSoundConfDlg, CDialogEx)

CAutoWatchSoundConfDlg::CAutoWatchSoundConfDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTO_WATCH_ALM_SND_CONF, pParent)
{

}

CAutoWatchSoundConfDlg::~CAutoWatchSoundConfDlg()
{
}

void CAutoWatchSoundConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAutoWatchSoundConfDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoWatchSoundConfDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAutoWatchSoundConfDlg 消息处理程序


void CAutoWatchSoundConfDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (mRecordAlarmAudioDlg.DoModal() == IDOK) {
		TRACE("Record alarm audio return ok\n");
	}
	else {
		TRACE("Record alarm audio return cancel\n");
	}


}
