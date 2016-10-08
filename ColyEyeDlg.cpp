
// ColyEyeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColyEye.h"
#include "ColyEyeDlg.h"
#include "afxdialogex.h"
#include "CameraManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColyEyeDlg �Ի���



CColyEyeDlg::CColyEyeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COLYEYE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CColyEyeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CColyEyeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(USER_MSG_SCAN_DEV, &CColyEyeDlg::OnUserMsgScanDev)
	ON_WM_CLOSE()
	ON_MESSAGE(USER_MSG_NOTIFY, &CColyEyeDlg::OnUserMsgNotify)
END_MESSAGE_MAP()


// CColyEyeDlg ��Ϣ�������

BOOL CColyEyeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	///����Wall�Ի���
	mWall.Create(IDD_WALL, this);
	mWall.MoveWindow(5, 5, 800, 400);
	mWall.ShowWindow(SW_SHOW);

	mMenu.Create(IDD_MENU, this);
	mMenu.MoveWindow(5, 5, 800, 400);
	mMenu.ShowWindow(SW_HIDE);

	mVideoCtr.Create(IDD_VIDEOCTR_DIALOG, this);
	mVideoCtr.MoveWindow(5, 5, 800, 400);
	mVideoCtr.ShowWindow(SW_HIDE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CColyEyeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CColyEyeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/**@brief �豸ɨ������Ϣ
 *
 */
afx_msg LRESULT CColyEyeDlg::OnUserMsgScanDev(WPARAM wParam, LPARAM lParam)
{
	int devNum = wParam;
	CCameraManager* pCameraMgr = CCameraManager::getInstance();


	/// �õ�ɨ�赽���豸��IP��ַ
	for (int i = 0; i < devNum; i++) {

		CCamera* pCamera = new CCamera();
		pCamera->mCommonNetConfig = &pCameraMgr->mSdkConfNetCommonV2[i];
		int tmp = 0;
		for (int j = 0; j < 4; j++) { 
			tmp += sprintf_s(&(pCamera->mIp[tmp]), 4,"%d", pCamera->mCommonNetConfig->HostIP.c[j]);
			if (j < 3) {
				pCamera->mIp[tmp] = '.';
				tmp++;
			}

		}

		pCameraMgr->addCamera(pCamera);
		pCameraMgr->distributeId(pCamera);
	}

	POSITION pos = pCameraMgr->mCameras.GetHeadPosition();
	CCamera* pDev;
	while (pos) {
		pDev = (CCamera*)pCameraMgr->mCameras.GetNext(pos);
		PostThreadMessage(((CColyEyeApp*)AfxGetApp())->pidOfLoginThread, USER_MSG_LOGIN, 0, (LPARAM)pDev);
	}
	return 0;
}





void CColyEyeDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CCameraManager::getInstance()->destrucCameras();
	CDialogEx::OnClose();
}


BOOL CColyEyeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_CONTEXTMENU) {
		if (mWall.IsWindowVisible()) {
			mWall.ShowWindow(SW_HIDE);
			mMenu.ShowWindow(SW_SHOW);
			::SendMessage(mMenu.m_hWnd, USER_MSG_BRING, 0, 0);
		}
		else {
			mMenu.ShowWindow(SW_HIDE);
			mWall.ShowWindow(SW_SHOW);
			mWall.SetFocus();
		}		
	}
	
	return CDialogEx::PreTranslateMessage(pMsg);
}


afx_msg LRESULT CColyEyeDlg::OnUserMsgNotify(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case WM_CONTEXTMENU:
		if (lParam == (LPARAM)&mMenu) {
			mMenu.ShowWindow(SW_HIDE);
			//mWall.ShowWindow(SW_SHOW);
			//mWall.SetFocus();
			::SendMessage(mWall.m_hWnd, USER_MSG_BRING, true, 0);
		}
		else {
			mWall.ShowWindow(SW_HIDE);
			::SendMessage(mMenu.m_hWnd, USER_MSG_BRING, 0, 0);
		}
		break;
	}
	return 0;
}
