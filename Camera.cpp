#include "stdafx.h"
#include "Camera.h"
#include "CameraManager.h"
#include "RecordFileInfo.h"
#include "RecordFileInfoManager.h"
#include "Util.h"

int __stdcall realDataCallBack_V2(long hRealPlay, const PACKET_INFO_EX* pFrame, unsigned int dwUser);
int __stdcall normalRealDataCallBack_V2(long hRealPlay, const PACKET_INFO_EX * pFrame, unsigned int dwUser);
int __stdcall alarmRealDataCallBack_V2(long hRealPlay, const PACKET_INFO_EX * pFrame, unsigned int dwUser);

CMutex mutex_RealDataCB;

CCamera::CCamera()
{
	mPort = 34567;
	strcpy_s(mUserName, "admin");
	strcpy_s(mPwd, "");
	clientInfo.nMode = 0;
	clientInfo.nChannel = 0;
	clientInfo.nStream = 1;
	deviceInfo.deviceTye = SDK_DEVICE_TYPE_DVR;

	hRealPlay = 0;
	mNormalRecordFile = NULL;
	mAlarmRecordFile = NULL;
	isAlarmRecording = false;
	isRecording = false;

	userConf.name_inx = 0;
	userConf.vol = 5;
	userConf.switches = CAMERA_USER_CONF_ON | CAMERA_USER_CONF_UP | CAMERA_USER_CONF_STORE | CAMERA_USER_CONF_AWATCH;
	
	//CRecordFileInfo* pRecordFileInfo;
}


CCamera::~CCamera()
{
	//if (mAlarmRecordFile) {
	//	this->stopAlarmRecord();
	//}
	if (mNormalRecordFile) {
		this->stopRecord();
	}
	if (hRealPlay) {
		H264_DVR_StopRealPlay(hRealPlay);
	}

	if (isRecording) {
		stopRecord();
	}

	if (isAlarmRecording) {
		stopAlarmRecord();
	}

	if (mLoginId) {
		H264_DVR_Logout(this->mLoginId);
	}
	TRACE("Camear Remove:%d\n", this->mId);
}


/**@brief ��ʵʱ��Ƶ
*
*
*/
void CCamera::startRealPlay()
{
	if (mLoginId) {
		//TRACE("client info:%d\n", this->clientInfo.hWnd);
		//Util::ShowMemoryInfo();
		hRealPlay = H264_DVR_RealPlay(mLoginId, &this->clientInfo);
		//TRACE("after dvr_realplay\n");
		//Util::ShowMemoryInfo();
		if (!hRealPlay) {
			TRACE("real play fail.Error code:%d\n", H264_DVR_GetLastError());
		}
		else {
			H264_DVR_SetRealDataCallBack_V2(hRealPlay, realDataCallBack_V2, (long)this);
			//TRACE("after dvr_setrealdata\n");
			//Util::ShowMemoryInfo();
		}
	}
	else {
		TRACE("please login first\n");
	}
}


void CCamera::stopRealPlay()
{
	if (hRealPlay) {
		/*H264_DVR_DelRealDataCallBack_V2(hRealPlay, realDataCallBack_V2, (long)this);*/
		//if (isRecording) {
		//	stopRecord();
		//}

		//if (isAlarmRecording) {
		//	stopAlarmRecord();
		//}

		H264_DVR_DelRealDataCallBack_V2(hRealPlay, realDataCallBack_V2, (long)this);

		H264_DVR_StopRealPlay(hRealPlay, &this->clientInfo.hWnd);
		hRealPlay = 0;
	}
}



/**@brief ��ʼ����¼��
 *
 * @param[in] ��������¼����ļ�
 */
void CCamera::startRecord(CFile* pFile)
{
	//ASSERT(pFile);
	//ASSERT(pFile->m_hFile != CFile::hFileNull);
	if (pFile == NULL || pFile->m_hFile == CFile::hFileNull) {
		LOG4CPLUS_ERROR(Logger::getInstance(_T("MyLogger")), "<info>" << mIp << " Bad file when start normal record");
		ASSERT(FALSE);;
	}

	mNormalRecordFile = pFile;
	//if (!H264_DVR_SetRealDataCallBack_V2(this->hRealPlay, normalRealDataCallBack_V2, (long)this)) {
	//	TRACE("Set realdata cb failed:%d\n", H264_DVR_GetLastError());
	//}
	//else{
	//	isRecording = true;
	//}
	isRecording = true;
}




/**@brief ֹͣ��Ƶ¼��.
*
*
*/
void CCamera::stopRecord()
{
	if (mNormalRecordFile == NULL) {
		LOG4CPLUS_INFO(Logger::getInstance(_T("MyLogger")), "<info>" << mIp << " Not null file when stop record");
		ASSERT(FALSE);
	}
	//if (isRecording) {
		isRecording = false;
		//H264_DVR_DelRealDataCallBack_V2(hRealPlay, normalRealDataCallBack_V2, (long)this);
		mNormalRecordFile->Flush();
		mNormalRecordFile = NULL;
	//}
}




/**@brief ��ʼ����¼��
 *
 * @param[in] pFile ����¼����ļ�
 */
void CCamera::startAlarmRecord(CFile* pFile)
{
	ASSERT(this->hRealPlay);

	ASSERT(pFile && pFile->m_hFile != CFile::hFileNull);	


	mAlarmRecordFile = pFile;

	//if (!H264_DVR_SetRealDataCallBack_V2(this->hRealPlay, alarmRealDataCallBack_V2, (long)this)) {
	//	TRACE("Set realdata cb failed:%d\n", H264_DVR_GetLastError());
	//}
	//else {
	//	isAlarmRecording = true;
	//}
	isAlarmRecording = TRUE;
}


/**@brief ֹͣ����¼��
 * 
 */
void CCamera::stopAlarmRecord()
{
	ASSERT(mAlarmRecordFile != NULL);

	//if (isAlarmRecording) {
		isAlarmRecording = false;
		//H264_DVR_DelRealDataCallBack_V2(hRealPlay, alarmRealDataCallBack_V2, (long)this);
		mAlarmRecordFile->Flush();
		mAlarmRecordFile = NULL;		
	//}
}


/**@brief ����ͷ���ı�����Ϣ(�������ܿ�����
 * 
 * @note:
 */
void CCamera::subscribeAlarmMessage()
{
	if (!H264_DVR_SetupAlarmChan(this->mLoginId)) {
		TRACE("%d subscribe alarm message failed\n", this->mId);
	}
}


/**@brief ����ͷȡ�����ı�����Ϣ(�������ܹرգ�
*
* @note:
*/
void CCamera::unsubscribeAlarmMessage()
{
	if (this->mLoginId > 0) {
		if (!H264_DVR_CloseAlarmChan(this->mLoginId)) {
			TRACE("%d unsubscribe alarm message failed\n", this->mId);
		}
	}
	else {
		TRACE("Find 0 loginId when unsubscribe alarm message\n");
	}
}




/**@brief ����ͷ��¼
 *
 * @return ��¼�ɹ�����true����֮����false
 */
BOOL CCamera::login()
{
	int errCode;
	long loginId = 0;

	Util::ShowMemoryInfo();
	loginId = H264_DVR_Login(mIp, mPort, mUserName, mPwd, &deviceInfo, &errCode);
	Util::ShowMemoryInfo();

	if (loginId > 0) {
		this->mLoginId = loginId;
		return true;
	}
	else {
		TRACE("%s login fail. error code:%d\n", this->mIp, errCode);
		this->mLoginId = 0;
		return false;
	}
}


/**@brief ����ͷע��
 *
 */
void CCamera::logout()
{
	if (mLoginId > 0) {
		if (H264_DVR_Logout(mLoginId)) {
			mLoginId = 0;
		}
		else {
			TRACE("%d Logout failed:%d\n", mLoginId, H264_DVR_GetLastError());
		}
	}
	else {
		TRACE("Invalid loginId:%d logout\n", mLoginId);
	}
}



/**@brief �����ݿ��ж�ȡ��������û�����
 *
 * @return ��ȡ�ɹ�����TRUE, ��֮����FALSE;
 */
BOOL CCamera::LoadUserConfiguration()
{
	char sqlStmt[128];
	sprintf_s(sqlStmt, "SELECT name_index, vol, switches FROM login_device WHERE id = %d;", this->mId);
	SQLiteStatement* stmt = sqlite.Statement(sqlStmt);
	if (stmt->NextRow()) {
		userConf.name_inx = stmt->ValueInt(0);
		userConf.vol = stmt->ValueInt(1);
		userConf.switches = stmt->ValueInt(2);
		return TRUE;
	}
	else {
		return FALSE;
	}
}


/**@brief ���û�����д�����ݿ�
 *
 */
BOOL CCamera::CommitUserConfigurationChange()
{
	char sqlStmt[128];
	sprintf_s(sqlStmt, "UPDATE login_device SET name_index = %d, vol = %d, switches = %d WHERE id = %d;", userConf.name_inx, userConf.vol, userConf.switches, mId);
	if (sqlite.DirectStatement(sqlStmt)) {
		return TRUE;
	}
	else {
		TRACE("sql stmt error:%s\n", sqlStmt);
		return FALSE;
	}
}


/**@brief ʵʱ��Ƶ�ص�
* 
*  @param [in] hRealPlay  ʵʱ��Ƶ���
*  @param [in] pFrame     ����֡
*  @param [in] dwUser     �Զ������ݣ�һ��Ϊ��������
*  @note �˻ص�������������������ԭʼ���ݣ���ִ����صĲ�����
*        ��������ͷÿ����һ֡���ݣ��˻ص��ͻᱻ����һ�Σ���ÿ�λص�ʱ������֡pFrameд���ļ�
*        �õ��ļ�ʱ�����.h264�ļ�(����֡����������Ϣ��Ŀǰ�����ý���)
*/
int __stdcall realDataCallBack_V2(long hRealPlay, const PACKET_INFO_EX* pFrame, unsigned int dwUser)
{
	CCamera * pDev = (CCamera*)dwUser;


mutex_RealDataCB.Lock();/// @see RecordFileManager.cpp  RecallRecordFile()

	if (pDev->isRecording  &&  pDev->mNormalRecordFile != nullptr) {
		pDev->mNormalRecordFile->Write(pFrame->pPacketBuffer, pFrame->dwPacketSize);
	}

	if (pDev->isAlarmRecording && pDev->mAlarmRecordFile != nullptr) {
		pDev->mAlarmRecordFile->Write(pFrame->pPacketBuffer, pFrame->dwPacketSize);
	}

mutex_RealDataCB.Unlock();/// @see RecordFileManager.cpp  RecallRecordFile()

	return 1;
}


int __stdcall normalRealDataCallBack_V2(long hRealPlay, const PACKET_INFO_EX* pFrame, unsigned int dwUser)
{
	/*((CCamera*)dwUser)->mNormalRecordFile->Write(pFrame->pPacketBuffer, pFrame->dwPacketSize);*/
	TRACE("fuck 1\n");
	return 1;
}


int __stdcall alarmRealDataCallBack_V2(long hRealPlay, const PACKET_INFO_EX* pFrame, unsigned int dwUser)
{
	/*((CCamera*)dwUser)->mAlarmRecordFile->Write(pFrame->pPacketBuffer, pFrame->dwPacketSize);*/
	TRACE("fuck 2\n");
	return 1;
}


//int __stdcall realDataCallBack_V2(long hRealPlay, const PACKET_INFO_EX * pFrame, unsigned int dwUser)
//{
//	//BOOL  ret = H264_PLAY_InputData(0, (unsigned char*)pFrame->pPacketBuffer, pFrame->dwPacketSize);
//	static int flag = 0;
//
//	flag++;
//	///���������¼��������д��¼���ļ�
//	if (((CCamera*)dwUser)->mNormalRecordFile) {
//		((CCamera*)dwUser)->mNormalRecordFile->Write(pFrame->pPacketBuffer, pFrame->dwPacketSize);
//	}
//
//	///��������˱���¼��������Ҳд�뱨��¼���ļ�
//	if (((CCamera*)dwUser)->mAlarmRecordFile) {
//		((CCamera*)dwUser)->mAlarmRecordFile->Write(pFrame->pPacketBuffer, pFrame->dwPacketSize);
//	}
//
//	if (flag > 20) {
//		TRACE("fuck 1\n");
//		flag = 0;
//	}
//	return 1;
//}
//
//int __stdcall _realDataCallBack_V2(long hRealPlay, const PACKET_INFO_EX * pFrame, unsigned int dwUser)
//{
//	static int flag = 0;
//	flag++;
//	if (flag > 20) {
//		TRACE("fuck 2\n");
//		flag = 0;
//	}
//	
//	return 1;
//}