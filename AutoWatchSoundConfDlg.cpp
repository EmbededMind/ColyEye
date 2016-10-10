// AutoWatchSoundConfDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColyEye.h"
#include "AutoWatchSoundConfDlg.h"
#include "afxdialogex.h"



// CAutoWatchSoundConfDlg �Ի���

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


// CAutoWatchSoundConfDlg ��Ϣ�������


void CAutoWatchSoundConfDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (mRecordAlarmAudioDlg.DoModal() == IDOK) {
		TRACE("Record alarm audio return ok\n");
	}
	else {
		TRACE("Record alarm audio return cancel\n");
	}


}
