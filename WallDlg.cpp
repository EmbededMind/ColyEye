// WallDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "WallDlg.h"
#include "CameraManager.h"
#include "afxdialogex.h"
#include "RecordFileManager.h"
#include "Util.h"





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



// CWallDlg 对话框

IMPLEMENT_DYNAMIC(CWallDlg, CDialogEx)

CWallDlg::CWallDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WALL, pParent)
	, mSystemTime(0)
{

}

CWallDlg::~CWallDlg()
{
}

/**@brief  在视频墙上为摄像机分配一个显示位置.
*
* @param [in] pCamera 视频墙要承载的摄像机。
* @return 用于显示Camera视频的窗口的句柄。
*/
CSurfaceHolderDlg* CWallDlg::investCamera(CCamera* pCamera)
{
/// 这里如果出现断言错误，可能是曾经删该过类名或者资源。把对话框资源和类删掉重建即可。
	CSurfaceHolderDlg* pHolder = new CSurfaceHolderDlg();	
	pHolder->Create(IDD_SURFACE_HOLDER, this);
	pHolder->ShowWindow(SW_SHOW);

	mHolderes.AddTail(pHolder);
	pHolder->pCamera = pCamera;
	updateLayout();
	return pHolder;
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



/**@brief 规划视频墙的布局
*
* @param [in] 所要承载的SurfaceHolder的最大数量。
* @param [out] 若布局规划不变，返回TRUE，反之返回FALSE
* @note  布局用行数和列数表示。
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



/**@brief 执行布局
*
* @notes: 方法功能设计有问题，需更改。
*/

void CWallDlg::executeLayout()
{
	RECT r;
	GetClientRect(&r);

	int wallWidth = r.right - r.left;
	int wallHeight = r.bottom - r.top-30;

	int holderHeight  = wallHeight / mRows - 10;
	int holderWidth  = wallWidth / mCols - 10;
	int orgX = r.left + 5;
	int orgY = r.top + 30;
	int totalHolderNumber = mHolderes.GetCount();


	POSITION pos = mHolderes.GetHeadPosition();
	CWnd* pHolder;

	for (int i = 0; i < totalHolderNumber; i++) {
		if (pos != NULL) {
			pHolder = (CWnd*)mHolderes.GetNext(pos);

			int xPos = orgX + (i%mCols) * holderWidth;
			int yPos = orgY + (i / mCols) * holderHeight;
			TRACE("x = %d, y = %d\n", xPos, yPos);
			/// 这里如果没有显示出窗口，多半是xPos, yPos, holderWidth, holderHeight计算有问题。
			pHolder->MoveWindow(xPos, yPos, holderWidth, holderHeight, TRUE);
		}
		else {

		}
	}
}



/**@brief 根据当前的SurfaceHolder数目更新Surface墙的布局。
*
* @note 所谓布局，即行数和列数
*/
void CWallDlg::updateLayout()
{
	designLayout();
	TRACE("Row:%d,Col:%d\n", this->mRows, this->mCols);
	executeLayout();
}



void CWallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, mSystemTime);
}


BEGIN_MESSAGE_MAP(CWallDlg, CDialogEx)
	ON_MESSAGE(USER_MSG_LOGIN, &CWallDlg::OnUserMsgLogin)
	ON_WM_TIMER()
	ON_MESSAGE(USER_MSG_BRING, &CWallDlg::OnUserMsgBring)
	ON_MESSAGE(USER_MSG_RELOGIN, &CWallDlg::OnUserMsgReLogin)
END_MESSAGE_MAP()


// CWallDlg 消息处理程序


BOOL CWallDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CWnd* pWndParent = this->GetParent();

	CRect parentClientRect;
	pWndParent->GetClientRect(&parentClientRect);

	this->SetWindowPos(NULL, parentClientRect.left, parentClientRect.top,
		                     parentClientRect.Width(), parentClientRect.Height(), 0);

	H264_DVR_Init(disConnnectCallback, (long)this);
	PostThreadMessage( ((CColyEyeApp*)AfxGetApp())->pidOfLoginThread, USER_MSG_SCAN_DEV, CAMERA_MAX_NUM, (LPARAM)CCameraManager::getInstance()->mSdkConfNetCommonV2 );

	H264_DVR_SetDVRMessCallBack(messageCallbackFunc, (unsigned long)this);
    
	JugSchMsg msg;
	msg.hwnd = this->m_hWnd;
	msg.message = 100;
	
	this->mJugScheduler.AddZoneSchedule(&msg,  16*3600+0*60, 16*3600+1*60);

	SetTimer(SECOND_TICK_TIMER_EVENT_ID, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



/**@brief 设备登录消息处理
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
		
		pDev->clientInfo.hWnd = this->investCamera(pDev)->mSurface.m_hWnd;

		pDev->subscribeAlarmMessage();
		pDev->startRealPlay();

		SetTimer(pDev->mId, 30*1000, NULL);

		pDev->startRecord(RecordFileManager::GetInstance()->DistributeRecordFile(pDev->mId, RECORD_TYPE_NORMAL));
	}
	else {
		AfxMessageBox(_T("Login fail"));
	}
	return 0;
}



/**@brief 设备掉线重连接的消息处理
 *
 */
afx_msg LRESULT CWallDlg::OnUserMsgReLogin(WPARAM wParam, LPARAM lParam)
{
	if (wParam)
	{
		Device_Map::iterator iter;
		CCamera* pDev = (CCamera*)lParam;

		pDev->subscribeAlarmMessage();
		TRACE("after subcribe alarm message\n");
		Util::ShowMemoryInfo();

		pDev->startRealPlay();
		TRACE("after start real play\n");
		Util::ShowMemoryInfo();

		SetTimer(pDev->mId, 30 * 1000, NULL);
		TRACE("after set timer\n");
		Util::ShowMemoryInfo();

		CFile* pf = RecordFileManager::GetInstance()->DistributeRecordFile(pDev->mId, RECORD_TYPE_NORMAL);
		TRACE("after distribute file\n");
		Util::ShowMemoryInfo();

		pDev->startRecord(pf);
		TRACE("after start record\n");
		Util::ShowMemoryInfo();

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


/**@brief 中断正常录像
 *
 * @param [in] 要中断录像的摄像机
 */
void CWallDlg::interruptRecord(CCamera* pCamera)
{
	ASSERT(pCamera != nullptr);

	if (pCamera->isRecording) {
		pCamera->stopRecord();
		RecordFileManager::GetInstance()->RecallRecordFile(pCamera->mId, RECORD_TYPE_NORMAL);
		KillTimer(pCamera->mId);

		pCamera->isRecording = false;
	}
}


/**@brief 中断报警录像
 *
 * @param [in] 要中断录像的摄像机
 */
void CWallDlg::interruptAlarmRecord(CCamera* pCamera)
{
	ASSERT(pCamera != nullptr);

	
	if (pCamera->isAlarmRecording == TRUE) {
		int i = pCamera->mId - 1;
		if (alarmRecordStatus.flag  &  (0x01 << i)) {
			alarmRecordStatus.flagCnts[i] = 0;
			alarmRecordStatus.flag &= (~(0x01 << i));
			pCamera->stopAlarmRecord();
			RecordFileManager::GetInstance()->RecallRecordFile(pCamera->mId, RECORD_TYPE_ALARM);

			if (alarmRecordStatus.flag == 0) {
				KillTimer(ALARM_TIMER_EVENT_ID);
			}
		}

		pCamera->isAlarmRecording = false;
	}
}


/**@brief  断线重连(ClientDemo)
 *
 */
void CWallDlg::ReConnect(LONG lLoginID, char* pchDVRIP, LONG nDVRPort)
{
	CCamera* pDev = CCameraManager::getInstance()->findCameraByLoginId(lLoginID);

	if (pDev != nullptr) {
		pDev->logout();
		interruptAlarmRecord(pDev);
		interruptRecord(pDev);
		pDev->stopRealPlay();
		pDev->unsubscribeAlarmMessage();
		mDevReconnectMap[pDev->mId] = pDev;
		SetTimer(RECONNET_TIMER_EVENT_ID, 30*1000, NULL);
	}

	//POSITION pos = mHolderes.GetHeadPosition();
	//CSurfaceHolderDlg* pHolder;
	//while (pos) {
	//	pHolder = (CSurfaceHolderDlg*)mHolderes.GetNext(pos);
	//	if (pHolder->pCamera->mLoginId == lLoginID) {
	//		pHolder->pCamera->logout();
	//		interruptAlarmRecord(pHolder->pCamera);
	//		interruptRecord(pHolder->pCamera);
	//		pHolder->pCamera->stopRealPlay();
	//		pHolder->pCamera->unsubscribeAlarmMessage();			
	//		mDevReconnectMap[pHolder->pCamera->mId] = pHolder->pCamera;
	//		SetTimer(RECONNET_TIMER_EVENT_ID, 30*1000, NULL);
	//		return;
	//	}
	//}
}


/**@brief 摄像头掉线触发的回调
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


/**@brief 设备订阅消息回调处理
 *
 *
 */
bool __stdcall messageCallbackFunc(long lLoginID, char* pBuf, unsigned long dwBufLen, long dwUser)
{
	TRACE("Something happened! %d\n", lLoginID);
	SDK_AlarmInfo* pAlarmInfo = (SDK_AlarmInfo*)pBuf;

	if (pAlarmInfo->iEvent < 30) {
		TRACE("%s-->%d,channel:%d\n", alarmEventTab[pAlarmInfo->iEvent], pAlarmInfo->iStatus, pAlarmInfo->nChannel);
		if (pAlarmInfo->iStatus == 0) { /// Movation begin
			CCamera* pDev = CCameraManager::getInstance()->findCameraByLoginId(lLoginID);
			if (pDev) {
				TRACE("status:0x%x\n", alarmRecordStatus.flag);
				if ((alarmRecordStatus.flag & (0x01 << (pDev->mId - 1))) == 0) {
					pDev->startAlarmRecord(RecordFileManager::GetInstance()->DistributeRecordFile(pDev->mId, RECORD_TYPE_ALARM));

					SetTimer(((CWallDlg*)dwUser)->m_hWnd, ALARM_TIMER_EVENT_ID, 10 * 1000, NULL);
					alarmRecordStatus.flag |= (0x01 << (pDev->mId - 1));
				}
				else {

				}
				alarmRecordStatus.flagCnts[pDev->mId - 1] = ALARM_LIVE_TIME;
			}
			else {
				TRACE("error:loginId %d mismatch any camera when rec alarm message \n", lLoginID);
			}
		}
	}
	return true;
}



void CWallDlg::OnTimer(UINT_PTR nIDEvent)
{	
	CCamera* pCamera = CCameraManager::getInstance()->findCameraById(nIDEvent);
	if (nIDEvent <= CAMERA_MAX_NUM) {
		if (pCamera&&pCamera->mLoginId) {
			pCamera->stopRecord();
			RecordFileManager* pMgr = RecordFileManager::GetInstance();
			pMgr->RecallRecordFile(pCamera->mId, RECORD_TYPE_NORMAL);
			pCamera->startRecord(pMgr->DistributeRecordFile(pCamera->mId, RECORD_TYPE_NORMAL));
			Util::ShowMemoryInfo();		
		}
	}
	// 报警录像打包判断
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

							alarmRecordStatus.flag &= (~(0x01<<i));
							TRACE("flag: 0x%x\n", alarmRecordStatus.flag);
							if (alarmRecordStatus.flag == 0) {
								KillTimer(nIDEvent);
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
	//断线重连开始
	else if (nIDEvent == RECONNET_TIMER_EVENT_ID) {
		TRACE("execute reconnect\n");
		Device_Map::iterator p = mDevReconnectMap.begin();

		while (p != mDevReconnectMap.end()) {
			PostThreadMessage( ((CColyEyeApp*)AfxGetApp())->pidOfLoginThread, USER_MSG_RELOGIN, 0, (LPARAM)p->second );
			p++;
		}
		
		//while (p != mDevReconnectMap.end()) {
			//CCamera* pDev = p->second;

		//	if (pDev->login()) {
		//		TRACE("%s ReLogin\n", pDev->mIp);
		//		mDevReconnectMap.erase(p++);

		//		pDev->subscribeAlarmMessage();
		//		TRACE("after subcribe alarm message\n");
		//		Util::ShowMemoryInfo();

		//		pDev->startRealPlay();	
		//		TRACE("after start real play\n");
		//		Util::ShowMemoryInfo();

		//		SetTimer(pDev->mId, 30 * 1000, NULL);
		//		TRACE("after set timer\n");
		//		Util::ShowMemoryInfo();

		//		CFile* pf = RecordFileManager::GetInstance()->DistributeRecordFile(pDev->mId, RECORD_TYPE_NORMAL);
		//		TRACE("after distribute file\n");
		//		Util::ShowMemoryInfo();

		//		pDev->startRecord(pf);
		//		TRACE("after start record\n");
		//		Util::ShowMemoryInfo();
		//	}
		//	else {
		//		p++;
		//	}
		//}

		//if (0 == mDevReconnectMap.size()) {
		//	KillTimer(RECONNET_TIMER_EVENT_ID);
		//}
	}
	// 1s 定时时间到
	else if (SECOND_TICK_TIMER_EVENT_ID){
		mSystemTime = CTime::GetCurrentTime();
		UpdateData(false);

		std::list<JugSchMsg*> res;
		mJugScheduler.Step(mSystemTime, res);

		if (res.size() > 0) {
			std::list<JugSchMsg*>::iterator  iter;
			for (iter = res.begin(); iter != res.end(); iter++) {
				TRACE("schedule msg:%d\n",(*iter)->message);
			}
		}
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
