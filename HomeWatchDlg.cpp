// HomeWatchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColyEye.h"
#include "HomeWatchDlg.h"
#include "afxdialogex.h"


// CHomeWatchDlg �Ի���

IMPLEMENT_DYNAMIC(CHomeWatchDlg, CDialogEx)

CHomeWatchDlg::CHomeWatchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HOME_WATCH, pParent)
{

}

CHomeWatchDlg::~CHomeWatchDlg()
{
}

void CHomeWatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHomeWatchDlg, CDialogEx)
	ON_MESSAGE(USER_MSG_NOTIFY_FOCUS, &CHomeWatchDlg::OnUserMsgNotifyFocus)
END_MESSAGE_MAP()


// CHomeWatchDlg ��Ϣ�������


afx_msg LRESULT CHomeWatchDlg::OnUserMsgNotifyFocus(WPARAM wParam, LPARAM lParam)
{
	this->SetFocus();
	return 0;
}
