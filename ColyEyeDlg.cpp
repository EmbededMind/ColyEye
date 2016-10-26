
// ColyEyeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "ColyEyeDlg.h"
#include "afxdialogex.h"
#include "CameraManager.h"
#include "Util.h"
#include "PhysicalMonitorEnumerationAPI.h"
#include "HighLevelMonitorConfigurationAPI.h"

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

	if (m_SerialPortKbd.InitPort(this, COM_KEYBD, 9600, 'N', 8, 1, EV_RXFLAG | EV_RXCHAR, 512))
	{
		m_SerialPortKbd.StartMonitoring();
		m_bSerialPortKbdOpened = TRUE;
	}
	else
	{
		AfxMessageBox(_T("没有发现串口或串口被占用"));
		m_bSerialPortKbdOpened = FALSE;
	}
	//if (m_SerialPortCom.InitPort(this, COM_CAMERA, 9600, 'N', 8, 1, EV_RXFLAG | EV_RXCHAR, 512))
	//{
	//	m_SerialPortCom.StartMonitoring();
	//	m_bSerialPortComOpened = TRUE;
	//}
	//else
	//{
	//	AfxMessageBox(_T("没有发现串口或串口被占用"));
	//	m_bSerialPortComOpened = FALSE;
	//}
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
	//TRACE("%d\n", pMsg->wParam);
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

LONG CColyEyeDlg::OnCommData(WPARAM pData, LPARAM port)
{
	if (port == COM_KEYBD)
	{
		onedata *p = (onedata*)pData;
		p->ch[p->num] = '\0';
		TRACE(_T("COM%d ---%d\n"), (UINT)port, p->ch[0]);
		for (int i = 0; i < p->num; i++)
		{
			switch (p->ch[i])
			{
			case KB_MENU:
				keybd_event(VK_APPS, 0, 0, 0);
				keybd_event(VK_APPS, 0, KEYEVENTF_KEYUP, 0);
				break;
			case KB_UP:
				keybd_event(VK_UP, 0, 0, 0);
				keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);
				break;
			case KB_BACK:
				keybd_event(VK_BACK, 0, 0, 0);
				keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP, 0);
				break;
			case KB_AUTOWATCH:
				break;
			case KB_LEFT:
				keybd_event(VK_LEFT, 0, 0, 0);
				keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
				break;
			case KB_ENTER:
				keybd_event(VK_RETURN, 0, 0, 0);
				keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
				break;
			case KB_RIGHT:
				keybd_event(VK_RIGHT, 0, 0, 0);
				keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
				break;
			case KB_UDISK:
				keybd_event(VK_CONTROL, 0, 0, 0);
				keybd_event('U', 0, 0, 0);
				keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
				keybd_event('U', 0, KEYEVENTF_KEYUP, 0);
				break;
			case KB_VOLUP:
				this->SetVolumeLevel(2);
				break;
			case KB_DOWN:
				keybd_event(VK_DOWN, 0, 0, 0);
				keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
				break;
			case KB_BRIUP:
				SetBrightLevel(2);
				break;
			case KB_FUNC:
				this->SetFocus();
				this->SetActiveWindow();
				break;
			case KB_VOLDOWN:
				this->SetVolumeLevel(3);
				break;
			case KB_TALKQUIET:
				break;
			case KB_BRIDOWN:
				SetBrightLevel(2);
				break;
			case KB_SWITCH:
			{
				char str[120] = "shutdown -f -s -t 0";
				system(str);
				break;
			}
			default:
				break;
			}
		}
		return 0;
	}
	if (port == COM_CAMERA)
	{
		onedata *p = (onedata*)pData;
		int i;
		p->ch[p->num] = '\0';
		TRACE(_T("COM%d ---%S\n"), (UINT)port, p->ch);
		/*m_SerialPortKbd.WriteToPort(p->ch, p->num);*/
		return 0;
	}

	return 0;
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
		//m_usbManager.CopyRecord(_T("11"));
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
				wcscat_s(diskname, TEXT(":\\"));
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

BOOL CColyEyeDlg::SetVolumeLevel(int level)
{
	HRESULT hr;
	IMMDeviceEnumerator* pDeviceEnumerator = 0;
	IMMDevice *pDevice = 0;
	IAudioEndpointVolume* pAudioEndpointVolume = 0;
	IAudioClient* pAudioClient = 0;

	try {
		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pDeviceEnumerator);
		if (FAILED(hr)) throw "CoCreateInstance";
		hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
		if (FAILED(hr)) throw "GetDefaultAudioEndpoint";
		hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pAudioEndpointVolume);
		if (FAILED(hr)) throw "pDevice->Active";
		hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&pAudioClient);
		if (FAILED(hr)) throw "pDevice->Active";

		if (level == 1) {
			hr = pAudioEndpointVolume->SetMute(FALSE, NULL);
			if (FAILED(hr)) throw "SetMute";
		}
		else if (level == 0) {
			hr = pAudioEndpointVolume->SetMute(TRUE, NULL);
			if (FAILED(hr)) throw "SetMute";
		}
		else {
			if (level<=1 || level>=4) {
				hr = E_INVALIDARG;
				throw "Invalid Arg";
			}

			float fVolume;
			fVolume = level / 100.0f;
			hr = pAudioEndpointVolume->GetMasterVolumeLevelScalar(&fVolume);
			if (FAILED(hr)) throw "GetMasterVolumeLevelScalar";
			if (level == 2)
			{
				fVolume += 0.1;
				if (fVolume > 1) fVolume = 1;
			}
			else if (level == 3)
			{
				fVolume -= 0.1;
				if (fVolume < 0) fVolume = 0;
			}
			hr = pAudioEndpointVolume->SetMasterVolumeLevelScalar(fVolume, &GUID_NULL);
			if (FAILED(hr)) throw "SetMasterVolumeLevelScalar";

			pAudioClient->Release();
			pAudioEndpointVolume->Release();
			pDevice->Release();
			pDeviceEnumerator->Release();
			return true;
		}
	}
	catch (...) {
		if (pAudioClient) pAudioClient->Release();
		if (pAudioEndpointVolume) pAudioEndpointVolume->Release();
		if (pDevice) pDevice->Release();
		if (pDeviceEnumerator) pDeviceEnumerator->Release();
		throw;
	}
	return 0;
}

void FreePhysicalMonitor(DWORD npm, LPPHYSICAL_MONITOR ppm)
{
	DestroyPhysicalMonitors(npm, ppm);
	// Free the array.
	free(ppm);
}

LPPHYSICAL_MONITOR GetPhysicalMonitor(DWORD * pnpm)
{
	HMONITOR hMon = NULL;
	hMon = MonitorFromWindow(NULL, MONITOR_DEFAULTTOPRIMARY);
	LPPHYSICAL_MONITOR ppm = NULL;
	DWORD npm = 0;
	BOOL bRet = GetNumberOfPhysicalMonitorsFromHMONITOR(hMon, &npm);
	if (bRet) {
		ppm = (LPPHYSICAL_MONITOR)malloc(npm * sizeof(PHYSICAL_MONITOR));
		if (ppm) {
			bRet = GetPhysicalMonitorsFromHMONITOR(hMon, npm, ppm);
			if (!bRet) {
				FreePhysicalMonitor(npm, ppm);
				ppm = NULL;
				npm = 0;
			}
		}
	}
	*pnpm = npm;
	return ppm;
}

BOOL CColyEyeDlg::SetBrightLevel(int level)
{
	LPPHYSICAL_MONITOR ppm = 0;
	DWORD npm = 0;
	ppm = GetPhysicalMonitor(&npm);
	if (ppm) {
		DWORD nMin = 0, nCur = 0, nMax = 0;
		GetMonitorBrightness(ppm->hPhysicalMonitor, &nMin, &nCur, &nMax);
		CString str;
		str.Format(_T("Min:%d, Cur:%d, Max:%d\n"), nMin, nCur, nMax);
		TRACE(str);
		if (level == 2)
		{
			nCur += 10;
			if (nCur > 100) nCur = 100;
		}
		else if (level == 3)
		{
			nCur -= 10;
			if (nCur < 0) nCur = 0;
		}
		SetMonitorBrightness(ppm->hPhysicalMonitor, nCur);
		FreePhysicalMonitor(npm, ppm);
	}
	return 0;
}



