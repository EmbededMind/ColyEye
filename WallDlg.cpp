// WallDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColyEye.h"
#include "WallDlg.h"
#include "CameraManager.h"
#include "afxdialogex.h"
#include "RecordFileManager.h"

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
{

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



void CWallDlg::spitCamera(CCamera* pCamera)
{
	POSITION pos = mHolderes.GetHeadPosition();
	CCamera* pDev;
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
	RECT r;
	GetClientRect(&r);

	int wallWidth = r.right - r.left;
	int wallHeight = r.bottom - r.top;

	int holderHeight  = wallHeight / mRows - 10;
	int holderWidth  = wallWidth / mCols - 10;
	int orgX = r.left + 5;
	int orgY = r.top + 5;
	int totalHolderNumber = mHolderes.GetCount();


	POSITION pos = mHolderes.GetHeadPosition();
	CWnd* pHolder;

	for (int i = 0; i < totalHolderNumber; i++) {
		if (pos != NULL) {
			pHolder = (CWnd*)mHolderes.GetNext(pos);

			int xPos = orgX + (i%mCols) * holderWidth;
			int yPos = orgY + (i / mCols) * holderHeight;
			TRACE("x = %d, y = %d\n", xPos, yPos);
			/// �������û����ʾ�����ڣ������xPos, yPos, holderWidth, holderHeight���������⡣
			pHolder->MoveWindow(xPos, yPos, holderWidth, holderHeight, TRUE);
		}
		else {

		}
	}
}



/**@brief ���ݵ�ǰ��SurfaceHolder��Ŀ����Surfaceǽ�Ĳ��֡�
*
* @note ��ν���֣�������������
*/
void CWallDlg::updateLayout()
{
	designLayout();
	TRACE("Row:%d,Col:%d\n", this->mRows, this->mCols);
	executeLayout();
}



//void CWallDlg::startRecord(CSurfaceHolderDlg* pHolder, CFile* pFile)
//{
//
//}



//void CWallDlg::stopRecord(CCamera* pCamera)
//{
//	CSurfaceHolderDlg* pHolder = findSurfaceHolder(pCamera);
//
//}
//
//
//
//CSurfaceHolderDlg* CWallDlg::findSurfaceHolder(CCamera* pCamera)
//{
//	POSITION pos = mHolderes.GetHeadPosition();
//	CSurfaceHolderDlg* pHolder;
//	while (pos) {
//		pHolder = (CSurfaceHolderDlg*)mHolderes.GetNext(pos);
//		if (pHolder->pCamera == pCamera) {
//			return pHolder;
//		}
//	}
//
//	return nullptr;
//}


void CWallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWallDlg, CDialogEx)
	ON_MESSAGE(USER_MSG_LOGIN, &CWallDlg::OnUserMsgLogin)
	ON_WM_TIMER()
	ON_MESSAGE(USER_MSG_BRING, &CWallDlg::OnUserMsgBring)
END_MESSAGE_MAP()


// CWallDlg ��Ϣ��������


BOOL CWallDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ����Ӷ���ĳ�ʼ��
	CWnd* pWndParent = this->GetParent();

	CRect parentClientRect;
	pWndParent->GetClientRect(&parentClientRect);

	this->SetWindowPos(NULL, parentClientRect.left, parentClientRect.top,
		                     parentClientRect.Width(), parentClientRect.Height(), 0);

	H264_DVR_Init(disConnnectCallback, (long)this);
	PostThreadMessage( ((CColyEyeApp*)AfxGetApp())->pidOfLoginThread, USER_MSG_SCAN_DEV, CAMERA_MAX_NUM, (LPARAM)CCameraManager::getInstance()->mSdkConfNetCommonV2 );

	H264_DVR_SetDVRMessCallBack(messageCallbackFunc, (unsigned long)this);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


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

		H264_DVR_SetupAlarmChan(pDev->mLoginId);

		pDev->clientInfo.hWnd = this->investCamera(pDev)->mSurface.m_hWnd;

		pDev->subscribeAlarmMessage();
		pDev->startRealPlay();

		SetTimer(pDev->mId, 30*1000, NULL);

		pDev->startRecord(RecordFileManager::GetInstance()->DistributeRecordFile(pDev->mId, RECORD_TYPE_NORMAL));

		/*pDev->putRecordInfoIntoDB(time);*/

	}
	else {
		AfxMessageBox(_T("Login fail"));
	}
	return 0;
}



/**@brief �ж�����¼��
 *
 * @param [in] Ҫ�ж�¼��������
 */
void CWallDlg::interruptRecord(CCamera* pCamera)
{
	assert(pCamera != nullptr);

	if (pCamera->isRecording) {
		pCamera->stopRecord();
		RecordFileManager::GetInstance()->RecallRecordFile(pCamera->mId, RECORD_TYPE_NORMAL);
		KillTimer(pCamera->mId);
	}
}


/**@brief �жϱ���¼��
 *
 * @param [in] Ҫ�ж�¼��������
 */
void CWallDlg::interruptAlarmRecord(CCamera* pCamera)
{
	assert(pCamera != nullptr);

	
	if (pCamera->isAlarmRecording) {
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
	}
}


void CWallDlg::onCameraDisconnect(CCamera* pCamera)
{
	interruptAlarmRecord(pCamera);
	interruptRecord(pCamera);	
	pCamera->stopRealPlay();
	//spitCamera(pCamera);
	//updateLayout();
}


/**@brief  ��������(ClientDemo)
 *
 */
void CWallDlg::ReConnect(LONG lLoginID, char* pchDVRIP, LONG nDVRPort)
{
	POSITION pos = mHolderes.GetHeadPosition();
	CSurfaceHolderDlg* pHolder;
	while (pos) {
		pHolder = (CSurfaceHolderDlg*)mHolderes.GetNext(pos);
		if (pHolder->pCamera->mLoginId == lLoginID) {
			interruptAlarmRecord(pHolder->pCamera);
			interruptRecord(pHolder->pCamera);
			pHolder->pCamera->stopRealPlay();
			pHolder->pCamera->logout();
			mDevReconnectMap[pHolder->pCamera->mId] = pHolder->pCamera;
			SetTimer(RECONNET_TIMER_EVENT_ID, 30*1000, NULL);
			return;
		}
	}
}


/**@brief ����ͷ���ߴ����Ļص�
*
*/
void __stdcall disConnnectCallback(LONG lLoginID, char* pchDVRIP, LONG nDVRPort, DWORD dwUser)
{
	//CCamera* pDev = CCameraManager::getInstance()->findCameraByLoginId(lLoginID);

	//if (pDev) {
	//	((CWallDlg*)dwUser)->onCameraDisconnect(pDev);
	//}
	TRACE("-----DisConnect-----\n");
	CWallDlg* pThis = (CWallDlg*)dwUser;
	assert(pThis != nullptr);

	pThis->ReConnect(lLoginID, pchDVRIP, nDVRPort);
}



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
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	if (nIDEvent <= CAMERA_MAX_NUM) {
		CCamera* pCamera = CCameraManager::getInstance()->findCameraById(nIDEvent);
		if (pCamera) {
			/*CTime time = CTime::GetCurrentTime();
			pCamera->stopRecord(time);*/
			pCamera->stopRecord();
			RecordFileManager* pMgr = RecordFileManager::GetInstance();
			pMgr->RecallRecordFile(pCamera->mId, RECORD_TYPE_NORMAL);			
			pCamera->startRecord(pMgr->DistributeRecordFile(pCamera->mId, RECORD_TYPE_NORMAL));
		}
	}
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
	//����������ʼ
	else if (nIDEvent == RECONNET_TIMER_EVENT_ID) {
		TRACE("execute reconnect\n");
		Device_Map::iterator p = mDevReconnectMap.begin();
		while (p != mDevReconnectMap.end()) {
			CCamera* pDev = p->second;

			if (pDev->login()) {
				TRACE("%s ReLogin\n", pDev->mIp);
				mDevReconnectMap.erase(p++);

				pDev->subscribeAlarmMessage();
				pDev->startRealPlay();
				SetTimer(pDev->mId, 30 * 1000, NULL);
				pDev->startRecord(RecordFileManager::GetInstance()->DistributeRecordFile(pDev->mId, RECORD_TYPE_NORMAL));
			}
			else {
				p++;
			}
		}

		if (0 == mDevReconnectMap.size()) {
			KillTimer(RECONNET_TIMER_EVENT_ID);
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