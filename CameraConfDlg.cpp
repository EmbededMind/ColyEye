// CameraConfDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColyEye.h"
#include "CameraConfDlg.h"
#include "afxdialogex.h"


// CCameraConfDlg �Ի���

IMPLEMENT_DYNAMIC(CCameraConfDlg, CDialogEx)

CCameraConfDlg::CCameraConfDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CAMERA_CONF, pParent)
	, mCurrName(_T(""))
	, mVolumn(0)
{

}

CCameraConfDlg::~CCameraConfDlg()
{
}

void CCameraConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mCurrName);
	DDX_Control(pDX, IDC_BUTTON1, mSwitch);
	DDX_Control(pDX, IDC_BUTTON2, mPicDirection);
	DDX_Slider(pDX, IDC_SLIDER1, mVolumn);
	DDX_Control(pDX, IDC_BUTTON3, mStoreSwitch);
	DDX_Control(pDX, IDC_BUTTON4, mAutoWatchSwitch);
}


BEGIN_MESSAGE_MAP(CCameraConfDlg, CDialogEx)

END_MESSAGE_MAP()


// CCameraConfDlg ��Ϣ�������




BOOL CCameraConfDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam)
		{
		case VK_SPACE:
			if (GetFocus()->GetDlgCtrlID() == IDC_EDIT1) {
				TRACE("camera name edit space\n");

			 }
			return true;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CCameraConfDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}



void CCameraConfDlg::InitPanel()
{
	
}



void CCameraConfDlg::InitNameItem()
{
	for (int i = 0; i < 18; i++) {
		
	}
}