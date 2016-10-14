
// ColyEyeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColyEye.h"
#include "ColyEyeDlg.h"
#include "afxdialogex.h"
#include "CameraManager.h"
#include "Util.h"

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
	ON_MESSAGE(USER_MSG_LOGIN, &CColyEyeDlg::OnUserMsgLogin)
	ON_MESSAGE(WM_COMM_RXCHAR, &CColyEyeDlg::OnCommChar)
	ON_MESSAGE(WM_COMM_RXDATA, &CColyEyeDlg::OnCommData)
	ON_WM_DEVICECHANGE()
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

	if (m_SerialPortKbd.InitPort(this, 8, 9600, 'N', 8, 1, EV_RXFLAG | EV_RXCHAR, 512))
	{
		m_SerialPortKbd.StartMonitoring();
		m_bSerialPortKbdOpened = TRUE;
	}
	else
	{
		AfxMessageBox(_T("û�з��ִ��ڻ򴮿ڱ�ռ��"));
		m_bSerialPortKbdOpened = FALSE;
	}
	if (m_SerialPortCom.InitPort(this, 10, 9600, 'N', 8, 1, EV_RXFLAG | EV_RXCHAR, 512))
	{
		m_SerialPortCom.StartMonitoring();
		m_bSerialPortComOpened = TRUE;
	}
	else
	{
		AfxMessageBox(_T("û�з��ִ��ڻ򴮿ڱ�ռ��"));
		m_bSerialPortComOpened = FALSE;
	}
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
	char tmpIP[64];
	CCamera* pCamera;
	/// �õ�ɨ�赽���豸��IP��ַ
	for (int i = 0; i < devNum; i++) {

		Util::IPTransform( pCameraMgr->mSdkConfNetCommonV2[i].HostIP.c, tmpIP);
		TRACE("Transform IP:%s\n", tmpIP);
		
		pCamera = pCameraMgr->FindCameraByIP(tmpIP);

		// �����е��豸���Ҳ���ƥ��ip���豸��˵��Ϊ�¼������ڵ��豸
		if (pCamera == nullptr) {
			CCamera* pNewCamera = new CCamera();
			strcpy_s(pNewCamera->mIp, 20, tmpIP);
			memcpy_s(&pNewCamera->mCommonNetConfig,sizeof(pNewCamera->mCommonNetConfig),
				      &pCameraMgr->mSdkConfNetCommonV2[i], sizeof(pCameraMgr->mSdkConfNetCommonV2[i]));

			pCameraMgr->addCamera(pNewCamera);
			pCameraMgr->distributeId(pNewCamera);
		}
		//CCamera* pCamera = new CCamera();


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


afx_msg LRESULT CColyEyeDlg::OnUserMsgLogin(WPARAM wParam, LPARAM lParam)
{
	::SendMessage(mWall.m_hWnd, USER_MSG_LOGIN, wParam, lParam);
	::SendMessage(mMenu.m_hWnd, USER_MSG_LOGIN, wParam, lParam);
	return 0;
}
LONG CColyEyeDlg::OnCommChar(WPARAM ch, LPARAM port)
{
	return 0;
}

LONG CColyEyeDlg::OnCommData(WPARAM pData, LPARAM port)
{
	if (port == 8)
	{
		onedata *p = (onedata*)pData;
		int i;
		p->ch[p->num] = '\0';
		TRACE(_T("COM%d ---%S\n"), (UINT)port, p->ch);
		/*m_SerialPortKbd.WriteToPort(p->ch, p->num);*/
		return 0;
	}
	if (port == 11)
	{
		onedata *p = (onedata*)pData;
		int i;
		p->ch[p->num] = '\0';
		TRACE(_T("COM%d ---%S\n"), (UINT)port, p->ch);
		/*m_SerialPortKbd.WriteToPort(p->ch, p->num);*/
		return 0;
	}
}

BOOL CColyEyeDlg::OnDeviceChange(UINT nEventType, DWORD_PTR dwData)
{
	int i = 0;
	CString flag;
	DWORD mask;
	TCHAR diskname[5];
	DEV_BROADCAST_VOLUME* pDisk;
	switch (nEventType)
	{
	case DBT_DEVICEARRIVAL:
		pDisk = (DEV_BROADCAST_VOLUME*)dwData;
		mask = pDisk->dbcv_unitmask;
		for (i = 0; i < 32; i++)
		{
			if ((mask >> i) == 1)
			{
				diskname[0] = 'A' + i;
				diskname[1] = '\0';
				wcscat_s(diskname,TEXT(":"));
				break;
			}
		}		
		flag.Format(_T("%s"), diskname);
		TRACE(_T("U�̲��� %s\n"), flag);
		m_usbManager.InitUSB(this, flag);
		m_usbManager.StartMonitoring();
		m_usbManager.GetStatus(&m_USBFlashDiskStatus);
		m_usbManager.CopyRecord(_T("11"));
		m_usbManager.Updata();
		return TRUE;
	case DBT_DEVICEREMOVECOMPLETE:
		pDisk = (DEV_BROADCAST_VOLUME*)dwData;
		mask = pDisk->dbcv_unitmask;
		for (i = 0; i < 32; i++)
		{
			if ((mask >> i) == 1)
			{
				diskname[0] = 'A' + i;
				diskname[1] = '\0';
				wcscat_s(diskname, TEXT(":"));
				break;
			}
		}
		flag.Format(_T("%s"), diskname);
		TRACE(_T("U�̰γ� %s\n"), flag);
		m_usbManager.EndThread();
		return TRUE;
	}
	return 0;
}

