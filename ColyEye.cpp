
// ColyEye.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "ColyEye.h"
#include "ColyEyeDlg.h"
#include  "DBOperator.h"
#include "RecordFileManager.h"
#include "DBShadow.h"
#include "CameraManager.h"
#include "Util.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif



unsigned int __stdcall loginThread(PVOID pM);

// CColyEyeApp

BEGIN_MESSAGE_MAP(CColyEyeApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CColyEyeApp 构造

CColyEyeApp::CColyEyeApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CColyEyeApp 对象

CColyEyeApp theApp;


// CColyEyeApp 初始化

BOOL CColyEyeApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	InitLog();
	LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "GG");
	
	if (!sqlite.Open("cold_eye.db")) {
		TRACE("Database open failed\n");
	}

	CCameraManager::getInstance()->loadDeviceHistoryFrmoDB();
	RecordFileManager::GetInstance()->Attach(DBShadow::GetInstance());
	CRecordFileInfoManager::getInstance()->instantiateRecordInfoFromDB();

	//CRecordFileInfoManager* pRecordInfoMgr = CRecordFileInfoManager::getInstance();
	//pRecordInfoMgr->instantiateNormalRecordInfoFromDB(1);
	//pRecordInfoMgr->instantiateAlarmRecordInfoFromDB(1);

	/// Look here animals

	hLoginThread = (HANDLE)_beginthreadex(NULL, 0, loginThread, NULL, 0, &pidOfLoginThread);

	CColyEyeDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}



	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}





/**@brief 登录线程，负责局域网内的设备扫描和设备登录
 *
 * @note: 网内设备扫描时接受的 msg 为
 *        msg.wParam 要扫描的最大设备数目
 *        msg.lParam 存储扫描结果的缓冲区
 *        
 *
 *        设备登录时接受的 msg 为
 *        msg.lParam 当前要登录的摄像头实例的引用
 *
 *        设备扫描结果发送给主窗口 ColyEyeDlg
 *        设备登录结果发送给视频墙窗口 WallDlg。登录成功所发消息的wParam为TRUE,反之为FALSE
 */
unsigned int __stdcall loginThread(PVOID pM)
{
	MSG msg;

	int errCode = 0;
	int length = 0;
	while (GetMessage(&msg, 0, 0, 0))
	{
		switch (msg.message) 
		{
			case USER_MSG_SCAN_DEV:
			{
				/*BOOL bRet = H264_DVR_SearchDevice((char*)devs, sizeof(SDK_CONFIG_NET_COMMON_V2), &length, 5000);*/

				SDK_CONFIG_NET_COMMON_V2* pCommon = (SDK_CONFIG_NET_COMMON_V2*)msg.lParam;
				BOOL bRet = H264_DVR_SearchDevice((char*)pCommon, sizeof(SDK_CONFIG_NET_COMMON_V2)*msg.wParam, &length, 7000);
				if (bRet) {
					int devNum = length / sizeof(SDK_CONFIG_NET_COMMON_V2);
					if (devNum) {
						/// 将扫描结果发送给主窗口:ColyEyeDlg
						PostMessage(AfxGetApp()->m_pMainWnd->m_hWnd, USER_MSG_SCAN_DEV, devNum, 0);
					}

					TRACE("find %d devices\n", devNum);
				}
				else {
					TRACE("find fail\n");
				}
				break;
			}
			case USER_MSG_LOGIN: 
			{
				int errCode = 0;
				CCamera* pCamera = (CCamera*)msg.lParam;
				if (pCamera) {
					Util::ShowMemoryInfo();
					long loginId = H264_DVR_Login(pCamera->mIp, pCamera->mPort, pCamera->mUserName, pCamera->mPwd,
						&pCamera->deviceInfo, &errCode);
					Util::ShowMemoryInfo();

					if (loginId) {
						TRACE("%s login Ok\n", pCamera->mIp);
						pCamera->mLoginId = loginId;
						PostMessage(((CColyEyeDlg*)(AfxGetApp()->m_pMainWnd))->m_hWnd, USER_MSG_LOGIN, TRUE, msg.lParam);
					}
					else {
						TRACE("%s login fail. error code:%d\n", pCamera->mIp, errCode);
						PostMessage(((CColyEyeDlg*)(AfxGetApp()->m_pMainWnd))->m_hWnd, USER_MSG_LOGIN, FALSE, msg.lParam);
						//delete(pCamera);
					}
				}
				break;
		     }

			case USER_MSG_RELOGIN:
			{
				int errCode = 0;
				CCamera* pCamera = (CCamera*)msg.lParam;
				if (pCamera) {
					Util::ShowMemoryInfo();
					long loginId = H264_DVR_Login(pCamera->mIp, pCamera->mPort, pCamera->mUserName, pCamera->mPwd,
						&pCamera->deviceInfo, &errCode);
					Util::ShowMemoryInfo();

					if (loginId) {
						TRACE("%s login Ok\n", pCamera->mIp);
						pCamera->mLoginId = loginId;
						PostMessage(((CColyEyeDlg*)(AfxGetApp()->m_pMainWnd))->mWall.m_hWnd, USER_MSG_RELOGIN, TRUE, msg.lParam);
					}
					else {
						TRACE("%s login fail. error code:%d\n", pCamera->mIp, errCode);
						PostMessage(((CColyEyeDlg*)(AfxGetApp()->m_pMainWnd))->mWall.m_hWnd, USER_MSG_RELOGIN, FALSE, msg.lParam);
						//delete(pCamera);
					}
				}
				break;
			}
		}
		DispatchMessage(&msg);
	}
	return 0;
}
