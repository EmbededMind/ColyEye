
// ColyEyeDlg.cpp : 实现文件
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


// CColyEyeDlg 对话框



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


// CColyEyeDlg 消息处理程序

BOOL CColyEyeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	///创建Wall对话框
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
		AfxMessageBox(_T("没有发现串口或串口被占用"));
		m_bSerialPortKbdOpened = FALSE;
	}
	if (m_SerialPortCom.InitPort(this, 10, 9600, 'N', 8, 1, EV_RXFLAG | EV_RXCHAR, 512))
	{
		m_SerialPortCom.StartMonitoring();
		m_bSerialPortComOpened = TRUE;
	}
	else
	{
		AfxMessageBox(_T("没有发现串口或串口被占用"));
		m_bSerialPortComOpened = FALSE;
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CColyEyeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CColyEyeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/**@brief 设备扫描结果消息
 *
 */
afx_msg LRESULT CColyEyeDlg::OnUserMsgScanDev(WPARAM wParam, LPARAM lParam)
{
	int devNum = wParam;
	CCameraManager* pCameraMgr = CCameraManager::getInstance();
	char tmpIP[64];
	CCamera* pCamera;
	/// 得到扫描到的设备的IP地址
	for (int i = 0; i < devNum; i++) {

		Util::IPTransform( pCameraMgr->mSdkConfNetCommonV2[i].HostIP.c, tmpIP);
		TRACE("Transform IP:%s\n", tmpIP);
		
		pCamera = pCameraMgr->FindCameraByIP(tmpIP);

		// 在已有的设备中找不到匹配ip的设备，说明为新加入网内的设备
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CCameraManager::getInstance()->destrucCameras();
	CDialogEx::OnClose();
}


BOOL CColyEyeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
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
		TRACE(_T("U盘插入 %s\n"), flag);
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
		TRACE(_T("U盘拔出 %s\n"), flag);
		m_usbManager.EndThread();
		return TRUE;
	}
	return 0;
}

