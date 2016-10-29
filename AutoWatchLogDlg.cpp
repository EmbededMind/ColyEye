// AutoWatchLogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColyEye.h"
#include "AutoWatchLogDlg.h"
#include "afxdialogex.h"


// CAutoWatchLogDlg �Ի���

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
	DDX_Control(pDX, IDC_EDIT1, mLogText);
}


BEGIN_MESSAGE_MAP(CAutoWatchLogDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


void CAutoWatchLogDlg::Layout()
{
	CRect rClient;
	GetClientRect(rClient);

	mLogText.MoveWindow(rClient.left, rClient.top, rClient.Width(), rClient.Height(), TRUE);
}


void CAutoWatchLogDlg::ShowLog()
{
	//CStdioFile file();
}

// CAutoWatchLogDlg ��Ϣ�������


BOOL CAutoWatchLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��



	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CAutoWatchLogDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (IsWindow(mLogText)) {
		Layout();
	}
}
