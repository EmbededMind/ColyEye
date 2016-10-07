#include "stdafx.h"
#include "Camera.h"
#include "CameraManager.h"
#include "RecordFileInfo.h"
#include "RecordFileInfoManager.h"

int __stdcall realDataCallBack_V2(long hRealPlay, const PACKET_INFO_EX * pFrame, unsigned int dwUser);


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
		TRACE("client info:%d\n", this->clientInfo.hWnd);
		hRealPlay = H264_DVR_RealPlay(mLoginId, &this->clientInfo);
		if (!hRealPlay) {
			TRACE("real play fail.Error code:%d\n", H264_DVR_GetLastError());
		}
	}
	else {
		TRACE("please login first\n");
	}
}


void CCamera::stopRealPlay()
{
	if (hRealPlay) {
		H264_DVR_StopRealPlay(hRealPlay, &this->clientInfo.hWnd);
		hRealPlay = 0;
	}
}


void CCamera::startRecord(CFile* pFile)
{
	ASSERT(pFile);
	ASSERT(pFile->m_hFile != CFile::hFileNull);
	mNormalRecordFile = pFile;
	if (!H264_DVR_SetRealDataCallBack_V2(this->hRealPlay, realDataCallBack_V2, (long)this)) {
		TRACE("Set realdata cb failed:%d\n", H264_DVR_GetLastError());
	}
	else{
		isRecording = true;
	}
}




/**@brief ֹͣ��Ƶ¼��.
*
*
*/
void CCamera::stopRecord()
{
	if (isRecording) {
		H264_DVR_DelRealDataCallBack_V2(hRealPlay, realDataCallBack_V2, (long)this);
		mNormalRecordFile->Flush();
		mNormalRecordFile = NULL;
		isRecording = false;
	}
}





void CCamera::startAlarmRecord(CFile* pFile)
{
	ASSERT(this->hRealPlay);

	ASSERT(pFile && pFile->m_hFile != CFile::hFileNull);

	mAlarmRecordFile = pFile;

	// ����Ѿ���¼��ֻ���mAlarmRecordFile��ֵ���ɡ�
	if (isRecording) {
		isAlarmRecording = true;
	}
	else {
		if (H264_DVR_SetRealDataCallBack_V2(this->hRealPlay, realDataCallBack_V2,(long)this)) {
			isAlarmRecording = true;
		}
		else {
		   TRACE("Set reald data cb failed:%d\n", H264_DVR_GetLastError());
		}
	}
}



void CCamera::stopAlarmRecord()
{
	ASSERT(mAlarmRecordFile != NULL);

	if (isAlarmRecording) {
		H264_DVR_DelRealDataCallBack_V2(hRealPlay, realDataCallBack_V2, (long)this);
		mAlarmRecordFile->Flush();
		mAlarmRecordFile = NULL;
		if (isRecording){
			H264_DVR_SetRealDataCallBack_V2(hRealPlay, realDataCallBack_V2, (long)this);			
		}
		isAlarmRecording = false;
	}
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



BOOL CCamera::login()
{
	int errCode;
	long loginId = 0;
	loginId = H264_DVR_Login(mIp, mPort, mUserName, mPwd, &deviceInfo, &errCode);
		
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


/**@brief ʵʱ��Ƶ�ص�
* 
*  @param [in] hRealPlay  ʵʱ��Ƶ���
*  @param [in] pFrame     ����֡
*  @param [in] dwUser     �Զ������ݣ�һ��Ϊ��������
*  @note �˻ص�������������������ԭʼ���ݣ���ִ����صĲ�����
*        ��������ͷÿ����һ֡���ݣ��˻ص��ͻᱻ����һ�Σ���ÿ�λص�ʱ������֡pFrameд���ļ�
*        �õ��ļ�ʱ�����.h264�ļ�(����֡����������Ϣ��Ŀǰ�����ý���)
*/
int __stdcall realDataCallBack_V2(long hRealPlay, const PACKET_INFO_EX * pFrame, unsigned int dwUser)
{
	//BOOL  ret = H264_PLAY_InputData(0, (unsigned char*)pFrame->pPacketBuffer, pFrame->dwPacketSize);

	///���������¼��������д��¼���ļ�
	if (((CCamera*)dwUser)->mNormalRecordFile) {
		((CCamera*)dwUser)->mNormalRecordFile->Write(pFrame->pPacketBuffer, pFrame->dwPacketSize);
	}

	///��������˱���¼��������Ҳд�뱨��¼���ļ�
	if (((CCamera*)dwUser)->mAlarmRecordFile) {
		((CCamera*)dwUser)->mAlarmRecordFile->Write(pFrame->pPacketBuffer, pFrame->dwPacketSize);
	}
	return 1;
}