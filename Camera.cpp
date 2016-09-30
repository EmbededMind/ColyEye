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


/**@brief 打开实时视频
*
*
*/
void CCamera::realPlay()
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



void CCamera::startRecord(CFile* pFile)
{
	ASSERT(pFile);
	ASSERT(pFile->m_hFile != CFile::hFileNull);
	mNormalRecordFile = pFile;
	if (!H264_DVR_SetRealDataCallBack_V2(this->hRealPlay, realDataCallBack_V2, (long)this)) {
		TRACE("Set realdata cb failed:%d\n", H264_DVR_GetLastError());
	}
}




/**@brief 停止视频录制.
*
*
*/
void CCamera::stopRecord()
{
	if (mNormalRecordFile) {
		H264_DVR_DelRealDataCallBack_V2(hRealPlay, realDataCallBack_V2, (long)this);
		mNormalRecordFile->Flush();
		mNormalRecordFile = NULL;
	}
}



void CCamera::startAlarmRecord(CFile* pFile)
{
	ASSERT(pFile && pFile->m_hFile != CFile::hFileNull);

	mAlarmRecordFile = pFile;
	//if (!H264_DVR_SetRealDataCallBack_V2(this->hRealPlay, realDataCallBack_V2, (long)this)) {
	//	TRACE("Set realdata cb failed:%d\n", H264_DVR_GetLastError());
	//}
}



void CCamera::stopAlarmRecord()
{
	if (mAlarmRecordFile) {
		H264_DVR_DelRealDataCallBack_V2(hRealPlay, realDataCallBack_V2, (long)this);
		mAlarmRecordFile->Flush();
		mAlarmRecordFile = NULL;
		if (mNormalRecordFile) {
			H264_DVR_SetRealDataCallBack_V2(hRealPlay, realDataCallBack_V2, (long)this);
		}
	}
}


/**@brief 摄像头订阅报警信息(报警功能开启）
 * 
 * @note:
 */
void CCamera::subscribeAlarmMessage()
{
	if (!H264_DVR_SetupAlarmChan(this->mLoginId)) {
		TRACE("%d subscribe alarm message failed\n", this->mId);
	}
}




/**@brief 实时视频回调
* 
*  @param [in] hRealPlay  实时视频句柄
*  @param [in] pFrame     数据帧
*  @param [in] dwUser     自定义数据，一般为窗口引用
*  @note 此回调函数包含有网络流的原始数据，可执行相关的操作。
*        即：摄像头每发送一帧数据，此回调就会被调用一次，将每次回调时的数据帧pFrame写入文件
*        得到的即时所需的.h264文件(数据帧包含多种信息，目前还不用解析)
*/
int __stdcall realDataCallBack_V2(long hRealPlay, const PACKET_INFO_EX * pFrame, unsigned int dwUser)
{
	//BOOL  ret = H264_PLAY_InputData(0, (unsigned char*)pFrame->pPacketBuffer, pFrame->dwPacketSize);

	///如果开启了录像，则将数据写入录像文件
	if (((CCamera*)dwUser)->mNormalRecordFile) {
		((CCamera*)dwUser)->mNormalRecordFile->Write(pFrame->pPacketBuffer, pFrame->dwPacketSize);
	}

	///如果开启了报警录像，则将数据也写入报警录像文件
	if (((CCamera*)dwUser)->mAlarmRecordFile) {
		((CCamera*)dwUser)->mAlarmRecordFile->Write(pFrame->pPacketBuffer, pFrame->dwPacketSize);
	}
	return 1;
}