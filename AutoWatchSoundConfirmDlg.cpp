// AutoWatchSoundConfirmDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColyEye.h"
#include "AutoWatchSoundConfirmDlg.h"
#include "afxdialogex.h"


// CAutoWatchSoundConfirmDlg �Ի���

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


// CAutoWatchSoundConfirmDlg ��Ϣ�������


void CAutoWatchSoundConfirmDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DeleteFile(_T("E:\\Record\\Sound\\custom.wav"));
	CFile::Rename(_T("E:\\Record\\Sound\\tmp.wav"), _T("E:\\Record\\Sound\\custom.wav"));
	CDialogEx::OnOK();
}


void CAutoWatchSoundConfirmDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DeleteFile(_T("E:\\Record\\Sound\\tmp.wav"));
	CDialogEx::OnOK();
}


void CAutoWatchSoundConfirmDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DeleteFile(_T("E:\\Record\\Sound\\tmp.wav"));
	CDialogEx::OnCancel();
}
