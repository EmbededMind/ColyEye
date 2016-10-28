
// ColyEye.cpp : ����Ӧ�ó��������Ϊ��
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


// CColyEyeApp ����

CColyEyeApp::CColyEyeApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CColyEyeApp ����

CColyEyeApp theApp;


// CColyEyeApp ��ʼ��

BOOL CColyEyeApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

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
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}



	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}





/**@brief ��¼�̣߳�����������ڵ��豸ɨ����豸��¼
 *
 * @note: �����豸ɨ��ʱ���ܵ� msg Ϊ
 *        msg.wParam Ҫɨ�������豸��Ŀ
 *        msg.lParam �洢ɨ�����Ļ�����
 *        
 *
 *        �豸��¼ʱ���ܵ� msg Ϊ
 *        msg.lParam ��ǰҪ��¼������ͷʵ��������
 *
 *        �豸ɨ�������͸������� ColyEyeDlg
 *        �豸��¼������͸���Ƶǽ���� WallDlg����¼�ɹ�������Ϣ��wParamΪTRUE,��֮ΪFALSE
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
						/// ��ɨ�������͸�������:ColyEyeDlg
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
