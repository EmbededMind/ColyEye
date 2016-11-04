// WallDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColyEye.h"
#include "WallDlg.h"
#include "CameraManager.h"
#include "afxdialogex.h"
#include "RecordFileManager.h"
#include "Util.h"
#include "ColyEyeDlg.h"
#include "RecordAlarmSound.h"



const char alarmEventTab[29][40] = { "sdk_event_code_init",          ///0
"sdk_event_code_local_alarm",   ///1
"sdk_event_code_net_alarm",     ///2
"sdk_event_code_manual_alarm",  ///3
"sdk_event_code_video_motion",  ///4
"sdk_event_code_video_loss",    ///5
"sdk_event_code_video_blind",   ///6
"sdk_event_video_title",        ///7
"sdk_event_video_split",        ///8
"sdk_event_video_tour",         ///9
"sdk_event_storage_not_exist",  ///10
"sdk_event_storage_failure",    ///11
"sdk_event_low_sapce",          ///12
"sdk_event_net_abort",          ///13
"sdk_event_comm",               ///14
"sdk_event_storage_read_error", ///15
"sdk_event_storage_write_error",///16
"sdk_event_net_ipconflitc",     ///17
"sdk_event_alarm_emergency",    ///18
"sdk_event_dec_connect",        ///19
"sdk_event_upgrade",            ///20
"sdk_event_back_up",            ///21
"sdk_event_shut_down",          ///22
"sdk_event_reboot",             ///23
"sdk_event_newfile",            ///24
"sdk_event_videoAnalyze",       ///25
"sdk_event_ipc_alarm",          ///26
"sdk_event_speed_alarm",        ///27
"sdk_event_nr"                  ///28
};


typedef struct {
	unsigned char flag;
	unsigned short flagCnts[CAMERA_MAX_NUM];
}AlarmRecordStatus;

static AlarmRecordStatus alarmRecordStatus = { 0, 0 };
void __stdcall disConnnectCallback(LONG lLoginID, char* pchDVRIP, LONG nDVRPort, DWORD dwUser);
bool __stdcall messageCallbackFunc(long lLoginID, char* pBuf, unsigned long dwBufLen, long dwUser);



// CWallDlg �Ի���

IMPLEMENT_DYNAMIC(CWallDlg, CDialogEx)

CWallDlg::CWallDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WALL, pParent)
	, mSystemTime(0)
{
	mBeginWatchTime = 0;
	mEndWatchTime = 24 * 3600;
}

CWallDlg::~CWallDlg()
{
}

/**@brief  ����Ƶǽ��Ϊ���������һ����ʾλ��.
*
* @param [in] pCamera ��ƵǽҪ���ص��������
* @return ������ʾCamera��Ƶ�Ĵ��ڵľ����
*/
CSurfaceHolderDlg* CWallDlg::investCamera(CCamera* pCamera)
{
/// ����������ֶ��Դ��󣬿���������ɾ�ù�����������Դ���ѶԻ�����Դ����ɾ���ؽ����ɡ�
	CSurfaceHolderDlg* pHolder = new CSurfaceHolderDlg();	
	pHolder->Create(IDD_SURFACE_HOLDER, this);
	pHolder->ShowWindow(SW_SHOW);

	mHolderes.AddTail(pHolder);
	pHolder->pCamera = pCamera;
	updateLayout();
	return pHolder;
}



CSurface* CWallDlg::InvestCamera(CCamera* pCamera)
{
	CSurface* pSurface = new CSurface();
	//pSurface->Create(NULL, WS_CHILD|WS_VISIBLE,CRect(0, 0, 0, 0), this, pCamera->mId);
	pSurface->Create(NULL,_T("Surface"), WS_CHILD|WS_VISIBLE|WS_BORDER| WS_THICKFRAME, CRect(0,0,0,0), this, pCamera->mId);
	pSurface->ModifyStyle(BS_OWNERDRAW, 0);
	pSurface->ShowWindow(SW_SHOW);

	pSurface->SetUserData((DWORD)pCamera);

	m_pSurfaces.push_back(pSurface);

	UpdateLayout();
	return pSurface;
}





void CWallDlg::spitCamera(CCamera* pCamera)
{
	POSITION pos = mHolderes.GetHeadPosition();

	CSurfaceHolderDlg* pHolder;
	while (pos) {
		pHolder = (CSurfaceHolderDlg*)mHolderes.GetNext(pos);
		if (pHolder->pCamera == pCamera) {
			delete pHolder;
			mHolderes.RemoveAt(pos);
			return;
		}
	}
}



void CWallDlg::DesignLayout()
{
	int surface_number = m_pSurfaces.size();

	if (surface_number) {
		int i = 0;
		int qVal = 0;

		while (i <= surface_number) {
			qVal = i*i;
			if (qVal >= surface_number) {
				mCols = i;
				break;
			}
			i++;
		}
		mRows = surface_number / mCols + ((surface_number%mCols)>0?1:0);
		TRACE("Row:%d, Col:%d\n", mRows, mCols);
	}
}



void CWallDlg::ExecuteLayout()
{
	CRect rClient;
	GetClientRect(rClient);

	int margin = rClient.Width() * WALL_MARGIN_SCALE;

	int col_width = (rClient.Width() - margin * 2) / mCols;
	int padding = col_width * SURFACE_PADDING;
	int grap = padding * 2;

	int surface_width = col_width - padding * 2;
	int surface_height = surface_width * SURFACE_SHAPE;

	int orgX = margin + padding;
	int orgY = rClient.Height() / 2 - (surface_height*mRows + grap*(mRows - 1)) / 2;

	int holder_number = m_pSurfaces.size();

	int i = 0;
	std::list<CSurface*>::iterator iter;
	for (iter = m_pSurfaces.begin(); iter != m_pSurfaces.end(); iter++) {
		int xPos = orgX + (i % mCols) * (surface_width + grap);
		int yPos = orgY + (i / mCols) * (surface_height + grap);
		i++;

		(*iter)->MoveWindow(xPos, yPos, surface_width, surface_height, TRUE);
	}
}



void CWallDlg::UpdateLayout()
{
	DesignLayout();
	ExecuteLayout();
}


/**@brief �滮��Ƶǽ�Ĳ���
*
* @param [in] ��Ҫ���ص�SurfaceHolder�����������
* @param [out] �����ֹ滮���䣬����TRUE����֮����FALSE
* @note  ������������������ʾ��
*/
BOOL CWallDlg::designLayout()
{
	unsigned backupOfRow = mRows;

	int holderNumber = mHolderes.GetCount();;

	if (holderNumber) {
		int  i = 0;
		int  qVal = 0;

		while (i <= holderNumber) {
			qVal = i*i;
			if (qVal >= holderNumber) {
				mCols = i;
				mRows = holderNumber / mCols + (holderNumber%mCols > 0 ? 1 : 0);
				if (mRows != backupOfRow) {
					return TRUE;
				}
				else {
					return FALSE;
				}
			}
			i++;
		}
		return FALSE;
	}
	return FALSE;
}



/**@brief ִ�в���
*
* @notes: ����������������⣬����ġ�
*/

void CWallDlg::executeLayout()
{
	CRect rClient;
	GetClientRect(&rClient);

	int Margin = rClient.Width() * WALL_MARGIN_SCALE;   // margin ȡ��ȵ�ʮ��֮һ

	int col_width = (rClient.Width() - Margin * 2) / mCols;
	int padding = col_width * SURFACE_PADDING;
	int grap = padding * 2;

	int holder_width = col_width - padding * 2;
	int holder_height = holder_width * SURFACE_SHAPE;

	int orgX = Margin + padding;
	int orgY = rClient.Height() / 2 - (holder_height*mRows + grap*(mRows - 1)) / 2;

	int holder_number = mHolderes.GetCount();


	POSITION pos = mHolderes.GetHeadPosition();
	CWnd* pHolder;

	for (int i = 0; i < holder_number; i++) {
		if (pos != NULL) {
			pHolder = (CWnd*)mHolderes.GetNext(pos);

			int xPos = orgX + (i % mCols) * (holder_width + grap);
			int yPos = orgY + (i / mCols) * (holder_height + grap);

			/// �������û����ʾ�����ڣ������xPos, yPos, holderWidth, holderHeight���������⡣
			pHolder->MoveWindow(xPos, yPos, holder_width, holder_height, TRUE);
		}
		else {

		}
	}


	//int wallWidth = rClient.Width() - Margin*2;
	//int wallHeight = rClient.Height() - Margin*2;



	//int holderHeight  = wallHeight / mRows - Margin;
	//int holderWidth = (wallWidth - Margin*(mCols - 1)) / mCols;



	//int orgX = Margin + (wallWidth - holderWidth * mCols - Margin *(mCols-1)) /2;
	//int orgY = Margin + (wallHeight - (holderHeight + Margin) *mRows) /2;

	//

	//int totalHolderNumber = mHolderes.GetCount();


	//POSITION pos = mHolderes.GetHeadPosition();
	//CWnd* pHolder;

	//for (int i = 0; i < totalHolderNumber; i++) {
	//	if (pos != NULL) {
	//		pHolder = (CWnd*)mHolderes.GetNext(pos);

	//		int xPos = orgX + (i % mCols) * (holderWidth+Margin);
	//		int yPos = orgY + (i / mCols) * (holderHeight+Margin);

	//		/// �������û����ʾ�����ڣ������xPos, yPos, holderWidth, holderHeight���������⡣
	//		pHolder->MoveWindow(xPos, yPos, holderWidth, holderHeight, TRUE);
	//	}
	//	else {

	//	}
	//}
}



/**@brief ���ݵ�ǰ��SurfaceHolder��Ŀ����Surfaceǽ�Ĳ��֡�
*
* @note ��ν���֣�������������
*/
void CWallDlg::updateLayout()
{
	designLayout();

	executeLayout();
}



void CWallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, mSystemTime);
}


BEGIN_MESSAGE_MAP(CWallDlg, CDialogEx)
	ON_MESSAGE(USER_MSG_LOGIN, &CWallDlg::OnUserMsgLogin)
	ON_WM_TIMER()
	ON_MESSAGE(USER_MSG_BRING, &CWallDlg::OnUserMsgBring)
	ON_MESSAGE(USER_MSG_RELOGIN, &CWallDlg::OnUserMsgReLogin)
	ON_MESSAGE(USER_MSG_DEVICE_CONFIG, &CWallDlg::OnUserMsgDeviceConfig)
	ON_WM_SIZE()
	ON_MESSAGE(USER_MSG_NOTIFY_ARROW, &CWallDlg::OnUserMsgNotifyArrow)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


// CWallDlg ��Ϣ�������


BOOL CWallDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	((CColyEyeApp*)AfxGetApp())->m_pWallWnd = this;

	CWnd* pWndParent = this->GetParent();

	CRect parentClientRect;
	pWndParent->GetClientRect(&parentClientRect);


	this->SetWindowPos(NULL, parentClientRect.left, parentClientRect.top,
		                     parentClientRect.Width(), parentClientRect.Height(), 0);

	H264_DVR_Init(disConnnectCallback, (long)this);
	PostThreadMessage( ((CColyEyeApp*)AfxGetApp())->pidOfLoginThread, USER_MSG_SCAN_DEV, CAMERA_MAX_NUM, (LPARAM)CCameraManager::getInstance()->mSdkConfNetCommonV2 );

	H264_DVR_SetDVRMessCallBack(messageCallbackFunc, (unsigned long)this);

	host.Load();
	

	SetTimer(SECOND_TICK_TIMER_EVENT_ID, 1000, NULL);

	//CCamera* pDev = new CCamera();

	//pDev->mId = 4;

	//InvestCamera(pDev);

	//pDev->mId = 5;
	//InvestCamera(pDev);

	//CSurfaceHolderDlg* pHolder = new CSurfaceHolderDlg();
	//pHolder->Create(IDD_SURFACE_HOLDER, this);
	//pHolder->SetWindowTextW(_T("Holder 1"));
	//pHolder->ShowWindow(SW_SHOW);

	//mHolderes.AddTail(pHolder);

	//pHolder = new CSurfaceHolderDlg();
	//pHolder->Create(IDD_SURFACE_HOLDER, this);
	//pHolder->SetWindowTextW(_T("Holder 2"));
	//pHolder->ShowWindow(SW_SHOW);

	//mHolderes.AddTail(pHolder);

	//pHolder = new CSurfaceHolderDlg();
	//pHolder->Create(IDD_SURFACE_HOLDER, this);
	//pHolder->ShowWindow(SW_SHOW);

	//mHolderes.AddTail(pHolder);

	//updateLayout();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}



/**@brief �豸��¼��Ϣ����
 *
 * @note �豸��¼��
 *           
 */
afx_msg LRESULT CWallDlg::OnUserMsgLogin(WPARAM wParam, LPARAM lParam)
{
	if (wParam) {
		CCameraManager* pCameraMgr = CCameraManager::getInstance();
		CCamera* pDev = (CCamera*)lParam;

		if (pDev->mId == 0) {
			if (!pCameraMgr->distributeId(pDev)) {
				TRACE("distribute id fail\n");
			}
			else {
				TRACE("distribute id is:%d\n", pDev->mId);
			}
		}
		else {
			TRACE("id is:%d\n", pDev->mId);
		}
		
		//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pDev->mIp << " login, id is:" << pDev->mId);

		//pDev->clientInfo.hWnd = this->investCamera(pDev)->mSurface.m_hWnd;
		pDev->clientInfo.hWnd = this->InvestCamera(pDev)->m_hWnd;

		if (!pDev->LoadUserConfiguration()) {
			pDev->userConf.name_inx = 0;
			pDev->userConf.vol = 4;
			pDev->userConf.switches = 0;
			if (!pDev->CommitUserConfigurationChange()) {
				TRACE("Put user configuration into db failed!\n");
			}
		}
		EnableCameraConfiguration(pDev);
		/*H264_DVR_StartLocalVoiceCom(pDev->mLoginId);*/
	}
	else {
		AfxMessageBox(_T("Login fail"));
	}
	return 0;
}



/**@brief �豸���������ӵ���Ϣ����
 *
 */
afx_msg LRESULT CWallDlg::OnUserMsgReLogin(WPARAM wParam, LPARAM lParam)
{
	if (wParam)
	{
		Device_Map::iterator iter;
		CCamera* pDev = (CCamera*)lParam;

		//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pDev->mIp << " Relogin");

		EnableCameraConfiguration(pDev);

		iter = mDevReconnectMap.find(pDev->mId);

		if (iter != mDevReconnectMap.end()) {
			mDevReconnectMap.erase(iter);
		}

		if (0 == mDevReconnectMap.size()) {
			KillTimer(RECONNET_TIMER_EVENT_ID);
		}
	}

	return 0;
}


/**@brief �ж�����¼��
 *
 * @param [in] Ҫ�ж�¼��������
 */
void CWallDlg::interruptRecord(CCamera* pCamera)
{
	ASSERT(pCamera != NULL);

	if (pCamera->isRecording) {
		//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pCamera->mIp << " Interrupt normal record");
		pCamera->stopRecord();
		RecordFileManager::GetInstance()->RecallRecordFile(pCamera->mId, RECORD_TYPE_NORMAL);
		//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<INFO>" << pCamera->mIp << " Recall normal file after interrupt");
		KillTimer(pCamera->mId);

		pCamera->isRecording = FALSE;
	}
}


/**@brief �жϱ���¼��
 *
 * @param [in] Ҫ�ж�¼��������
 */
void CWallDlg::interruptAlarmRecord(CCamera* pCamera)
{
	ASSERT(pCamera != nullptr);

	
	if (pCamera->isAlarmRecording == TRUE) {
		//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pCamera->mIp << " Interrupt alarm record");
		int i = pCamera->mId - 1;
		if (alarmRecordStatus.flag  &  (0x01 << i)) {
			alarmRecordStatus.flagCnts[i] = 0;
			alarmRecordStatus.flag &= (~(0x01 << i));
			//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pCamera->mIp << " Stop alarm record");
			pCamera->stopAlarmRecord();
			RecordFileManager::GetInstance()->RecallRecordFile(pCamera->mId, RECORD_TYPE_ALARM);
			//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<INFO>" << pCamera->mIp << " Recall alarm file after interrupt");
			if (alarmRecordStatus.flag == 0) {
				KillTimer(ALARM_TIMER_EVENT_ID);
			}
		}

		pCamera->isAlarmRecording = FALSE;
	}
}


/**@brief �������������װ����ͷ�ػ���
 *
 * @param[in] pCamera Ҫ����������
 * @note  ����Ĳ����У�
 *            0.ȡ����������
 *            1.ֹͣ����¼�񣬲�ֹͣ�������͵ƹ�
 *            2.ֹͣ����¼��
 *            3.ֹͣʵʱ���ţ���ˢ�²��Ŵ���
 *            4.ֹͣ�Խ�
 */
void CWallDlg::SuspendCamera(CCamera* pCamera)
{
	ASSERT(pCamera != NULL);
	pCamera->userConf.switches &= (~CAMERA_USER_CONF_ON);

	pCamera->unsubscribeAlarmMessage();
	interruptAlarmRecord(pCamera);
	interruptRecord(pCamera);
	pCamera->stopRealPlay();

	// TODO:stop talk
}



void CWallDlg::ResumeCamera(CCamera* pCamera)
{
	ASSERT(pCamera != NULL);

	pCamera->subscribeAlarmMessage();
	pCamera->startRealPlay();

	pCamera->userConf.switches |= CAMERA_USER_CONF_ON;
}



void CWallDlg::EnableCameraConfiguration(CCamera* pCamera)
{
	//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info> Memory:" << Util::GetMemorySize());

	//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pCamera->mIp << " Enable configuration");
	// ���������
	if (pCamera->userConf.switches & CAMERA_USER_CONF_ON) {
	//	LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pCamera->mIp << " Camera ON");
		if (pCamera->hRealPlay == 0) {
			//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pCamera->mIp << " Start Realplay");
			pCamera->startRealPlay();

			//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info> After start realplay,Memory:" << Util::GetMemorySize());
		}
		    
        
		if (pCamera->userConf.switches & CAMERA_USER_CONF_STORE) {
		//	LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pCamera->mIp << " Store ON");
			if (!pCamera->isRecording) {
				//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pCamera->mIp << " Prepare to normal record");
				CFile* pf = RecordFileManager::GetInstance()->DistributeRecordFile(pCamera->mId, RECORD_TYPE_NORMAL);
				if (pf != NULL) {
					//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pCamera->mIp << " Start normal record");
					pCamera->startRecord(pf);
					SetTimer(pCamera->mId, 30 * 1000, NULL);

				}
				else {
					//LOG4CPLUS_ERROR(Logger::getInstance(_T("MyLogger")), "<ERROR>" << pCamera->mIp << " NULL file when start normal record ");
				}
			}
		}

		if (pCamera->userConf.switches & CAMERA_USER_CONF_AWATCH) {
			//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pCamera->mIp << " SubscribeAlarmMessage");
			pCamera->subscribeAlarmMessage();
		}
	}
}



void CWallDlg::DisableCameraConfiguration(CCamera* pCamera)
{
	//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pCamera->mIp << " Disable configuration");
	if ( (pCamera->userConf.switches & CAMERA_USER_CONF_ON) == 0) {
		//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pCamera->mIp << " Camera OFF");
		if (pCamera->hRealPlay) {
			pCamera->stopRealPlay();
		}

	    interruptRecord(pCamera);

	    interruptAlarmRecord(pCamera);

		pCamera->unsubscribeAlarmMessage();
	}
	else {
		if ( (pCamera->userConf.switches & CAMERA_USER_CONF_STORE) == 0) {
			//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pCamera->mIp << " STORE OFF");
			interruptRecord(pCamera);
		}

		if ( (pCamera->userConf.switches & CAMERA_USER_CONF_AWATCH) == 0) {
			//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pCamera->mIp << " Auto watch OFF");
			interruptAlarmRecord(pCamera);
	
		}
		pCamera->unsubscribeAlarmMessage();
	}
}





/**@brief  ��������(ClientDemo)
 *
 */
void CWallDlg::ReConnect(LONG lLoginID, char* pchDVRIP, LONG nDVRPort)
{
	CCamera* pDev = CCameraManager::getInstance()->findCameraByLoginId(lLoginID);
	//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<INFO>" << pDev->mIp << " DisConnect");
	if (pDev != nullptr) {
		pDev->unsubscribeAlarmMessage();
		pDev->logout();
		interruptAlarmRecord(pDev);
		interruptRecord(pDev);
		pDev->stopRealPlay();

		mDevReconnectMap[pDev->mId] = pDev;
		SetTimer(RECONNET_TIMER_EVENT_ID, 30*1000, NULL);
	}
}



void CWallDlg::OnCameraLogin(CCamera* pCamera)
{

}



void CWallDlg::OnCameraLogout(CCamera* pCamera)
{

}


/**@brief ����ͷ���ߴ����Ļص�
*
*/
void __stdcall disConnnectCallback(LONG lLoginID, char* pchDVRIP, LONG nDVRPort, DWORD dwUser)
{
	TRACE("-----DisConnect-----%s\n", pchDVRIP);

	//H264_DVR_Logout(lLoginID);
	CWallDlg* pThis = (CWallDlg*)dwUser;
	ASSERT(pThis != nullptr);

	pThis->ReConnect(lLoginID, pchDVRIP, nDVRPort);
}


/**@brief �豸������Ϣ�ص�����
 *
 *
 */
bool __stdcall messageCallbackFunc(long lLoginID, char* pBuf, unsigned long dwBufLen, long dwUser)
{
	//TRACE("Something happened! %d\n", lLoginID);

	CCameraManager* pMgr = CCameraManager::getInstance();
	CCamera* pDev = pMgr->findCameraByLoginId(lLoginID);
	printf("alarm message\n");
	// �Զ���������
	if (/*host.mConfuration.auto_watch_switch  &&  */pDev  && (pDev->userConf.switches & CAMERA_USER_CONF_AWATCH)) {
		CWallDlg* pWall = (CWallDlg*)dwUser;
		CTime t = CTime::GetCurrentTime();
				
		DWORD refTime = t.GetHour() * 3600 + t.GetMinute() * 60;

		BOOL beingWatching = (refTime >= host.mConfuration.watch_time_begining ?
			refTime - host.mConfuration.watch_time_begining < host.mConfuration.watch_time_span :
			refTime + 24 * 3600 - host.mConfuration.watch_time_begining < host.mConfuration.watch_time_span);
		//��ǰ�����Զ�����ʱ��
		if (beingWatching) {
			SDK_AlarmInfo* pAlarmInfo = (SDK_AlarmInfo*)pBuf;
			if (pAlarmInfo->iEvent < 30 && pAlarmInfo->iStatus == 0) {
				TRACE("status:0x%x\n", alarmRecordStatus.flag);
				if ((alarmRecordStatus.flag & (0x01 << (pDev->mId - 1))) == 0) {
					CFile* pf = RecordFileManager::GetInstance()->DistributeRecordFile(pDev->mId, RECORD_TYPE_ALARM);//��ʼ����¼��
					printf("begin alarm record\n");
					uint8_t Order[17];
					Util::LoadOrder(Order, 0x24, 0x01, 0x02, 0x05, 0x01, 0, pDev);
					((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->m_SerialPortCom.WriteToPort(Order, 17);
					CRecordAlarmSound::getInstance()->Play(pDev);
					
					if (pf != NULL) {
						pDev->startAlarmRecord(pf);

						SetTimer(((CWallDlg*)dwUser)->m_hWnd, ALARM_TIMER_EVENT_ID, 10 * 1000, NULL);
						alarmRecordStatus.flag |= (0x01 << (pDev->mId - 1));

						//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<INFO>" << pDev->mIp << " begin alarm record");
					}
					else {
						//LOG4CPLUS_ERROR(Logger::getInstance(_T("MyLogger")), "<ERROR>" << pDev->mIp << " find null file when begin alarm record");
					}
				}
				else {

				}
				alarmRecordStatus.flagCnts[pDev->mId - 1] = ALARM_LIVE_TIME;
			}
		}
	}
	return true;
}



void CWallDlg::JumpToHolder()
{
	int cnt = 0;
	POSITION pos = mHolderes.GetHeadPosition();
	CSurfaceHolderDlg* pHolder;
	while (pos) {
		pHolder = (CSurfaceHolderDlg*)mHolderes.GetNext(pos);
		if (cnt != mCurrSelectedHolder){
			if (pHolder->mIsSelected) {
				pHolder->mIsSelected = FALSE;
				pHolder->UpdateWindow();
			}
		}
		else {
			if (!pHolder->mIsSelected) {
				pHolder->mIsSelected = TRUE;
				pHolder->UpdateData();
			}
		}
	}
}



void CWallDlg::OnTimer(UINT_PTR nIDEvent)
{	
	if (nIDEvent <= CAMERA_MAX_NUM) {
		CCamera* pCamera = CCameraManager::getInstance()->findCameraById(nIDEvent);
		if (pCamera) {
			//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << pCamera->mIp << " Normal record timeout");
			pCamera->stopRecord();
			RecordFileManager* pMgr = RecordFileManager::GetInstance();
			pMgr->RecallRecordFile(pCamera->mId, RECORD_TYPE_NORMAL);
			CFile * pf = pMgr->DistributeRecordFile(pCamera->mId, RECORD_TYPE_NORMAL);
			if (pf != NULL) {
				pCamera->startRecord(pf);
				//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<INFO>" << pCamera->mIp << " package begin normal record");
			}
			else {
				//LOG4CPLUS_ERROR(Logger::getInstance(_T("MyLogger")), "<ERROR>" << pCamera->mIp << " find null file when package begin normal record");
			}
/*
			Util::ShowMemoryInfo();	*/	
		}
	}
	// ����¼�����ж�
	else if (nIDEvent == ALARM_TIMER_EVENT_ID) {
		TRACE("alarm timer event\n");
		if (alarmRecordStatus.flag) {
			RecordFileManager* pRecordFileMgr = RecordFileManager::GetInstance();
			for (int i = 0; i < CAMERA_MAX_NUM; i++) {
				if (alarmRecordStatus.flag & (0x01 << i)) {
					if (alarmRecordStatus.flagCnts[i]) {
						alarmRecordStatus.flagCnts[i]--;
					}
					else {
						TRACE("alarm record timeout\n");

						CCamera* pCamera = CCameraManager::getInstance()->findCameraById(i+1);
						if (pCamera) {
							pCamera->stopAlarmRecord();
							pRecordFileMgr->RecallRecordFile(pCamera->mId, RECORD_TYPE_ALARM);
							//LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<INFO>" << pCamera->mIp << " Recall file after end alarm record");
							alarmRecordStatus.flag &= (~(0x01<<i));
							TRACE("flag: 0x%x\n", alarmRecordStatus.flag);
							if (alarmRecordStatus.flag == 0) {
								KillTimer(nIDEvent);
								Util::LoadOrder(mOrder, 0x24, 0x01, 0x02, 0x05, 0x02, 0, pCamera);
								((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->m_SerialPortCom.WriteToPort(mOrder, 17);
								CRecordAlarmSound::getInstance()->StopTalk();
							}
						}
						else {
							TRACE("find null camera, id is :%d\n", i+1);
						}
					}
				}
			}
		}
	}
	//����������ʼ
	else if (nIDEvent == RECONNET_TIMER_EVENT_ID) {
		TRACE("execute reconnect\n");
		Device_Map::iterator p = mDevReconnectMap.begin();

		while (p != mDevReconnectMap.end()) {
			PostThreadMessage( ((CColyEyeApp*)AfxGetApp())->pidOfLoginThread, USER_MSG_RELOGIN, 0, (LPARAM)p->second );
			p++;
		}		
	}
	// 1s ��ʱʱ�䵽
	else if (SECOND_TICK_TIMER_EVENT_ID){
		//mSystemTime = CTime::GetCurrentTime();
		//UpdateData(false);
	}
	CDialogEx::OnTimer(nIDEvent);
}




afx_msg LRESULT CWallDlg::OnUserMsgBring(WPARAM wParam, LPARAM lParam)
{
	if (wParam) {
		this->ShowWindow(SW_SHOW);
		this->SetFocus();
	}
	return 0;
}


afx_msg LRESULT CWallDlg::OnUserMsgDeviceConfig(WPARAM wParam, LPARAM lParam)
{
	CCamera* pCamera = (CCamera*)lParam;
	if (wParam) {
		EnableCameraConfiguration(pCamera);
		pCamera->CommitUserConfigurationChange();
	}
	else {
		DisableCameraConfiguration(pCamera);
		pCamera->CommitUserConfigurationChange();
	}
	return 0;
}



BOOL CWallDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam)
		{
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;

		default:
			if ( GetKeyState(VK_CONTROL)  && !(pMsg->lParam & 0x20000000)) {
				CSurface* pSurface = (CSurface*)GetFocus();
				DWORD data = pSurface->GetUserData();
				CCamera* pDev = (CCamera*)data;

				switch (pMsg->wParam) 
				{ 
				case 'T': 
				{
					if (CCameraManager::getInstance()->mTalkHandle != 0)
					{
						H264_DVR_StopVoiceCom(CCameraManager::getInstance()->mTalkHandle);
						Util::LoadOrder(mOrder, 0x24, 0x01, 0x02, 0x02, 0x02, NULL, pDev);
						((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->m_SerialPortCom.WriteToPort(mOrder, 17);
						CCameraManager::getInstance()->mTalkHandle = 0;
					}
					if (CCameraManager::getInstance()->mTalkHandle == 0)
					{
						TRACE("Begin to talk with :%d\n", pDev->mId);
						CCameraManager::getInstance()->mTalkHandle = H264_DVR_StartLocalVoiceCom(pDev->mLoginId);
						uint8_t Order[17];
						Util::LoadOrder(Order, 0x24, 0x01, 0x02, 0x02, 0x01, NULL, pDev);
						((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->m_SerialPortCom.WriteToPort(Order, 17);
					}
				}
				return TRUE;

				case 'O':
				{
					if (CCameraManager::getInstance()->mTalkHandle != 0)
					{
						TRACE("Over talk with :%d\n", pDev->mId);
						H264_DVR_StopVoiceCom(CCameraManager::getInstance()->mTalkHandle);
						CCameraManager::getInstance()->mTalkHandle = 0;
						Util::LoadOrder(mOrder, 0x24, 0x01, 0x02, 0x02, 0x02, NULL, pDev);
						TRACE("%s\n", pDev->mCommonNetConfig.sMac);
						((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->m_SerialPortCom.WriteToPort(mOrder, 17);
					}
				}
		        return TRUE;
					
				default:
					break;
				}
			}
			break;
		}
	}
	else if (pMsg->message == WM_CONTEXTMENU)
	{
		TRACE("CWallDlg case contextmenu\n");
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}





void CWallDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(mHolderes.GetCount() > 0)
	   executeLayout();
}


afx_msg LRESULT CWallDlg::OnUserMsgNotifyArrow(WPARAM wParam, LPARAM lParam)
{
	if (mHolderes.GetCount() > 0) {
		POSITION pos = mHolderes.Find((void*)lParam);
		
		CSurfaceHolderDlg* pHolder;
		CString text;


		if (pos) {
			switch (wParam)
			{
			case VK_LEFT:
				if (pos != mHolderes.GetHeadPosition()) {
					pos--;
					pHolder = (CSurfaceHolderDlg*)mHolderes.GetAt(pos);
					pHolder->GetWindowTextW(text);
					TRACE("Next is %S\n", pHolder);
					pHolder->SetFocus();
					if (pHolder->mIsSelected) {
						pHolder->OnNcPaint();
					}
					else {
						TRACE("Error\n");
					}
					((CSurfaceHolderDlg*)lParam)->OnNcPaint();
				}
				break;
			case VK_RIGHT:
				if (pos != mHolderes.GetTailPosition()) {
					mHolderes.GetNext(pos);;
					pHolder = (CSurfaceHolderDlg*)mHolderes.GetNext(pos);
					TRACE("Next holder:0x%p\n", pHolder);
					pHolder->SetFocus();

					if (pHolder->mIsSelected) {
						pHolder->OnNcPaint();
					}
					else{
						TRACE("Error\n");
					}
					((CSurfaceHolderDlg*)lParam)->OnNcPaint();
				}
				break;
			}
		}
	}
	return 0;
}


void CWallDlg::OnSetFocus(CWnd* pOldWnd)
{
	CDialogEx::OnSetFocus(pOldWnd);
	// TODO: �ڴ˴������Ϣ����������
}


void CWallDlg::OnKillFocus(CWnd* pNewWnd)
{

	CDialogEx::OnKillFocus(pNewWnd);

	// TODO: �ڴ˴������Ϣ����������
}


