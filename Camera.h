#pragma once

#include "RecordFileInfo.h"


#define CAMERA_USER_CONF_ON       0x0001
#define CAMERA_USER_CONF_UP       0x0002
#define CAMERA_USER_CONF_STORE    0x0004
#define CAMERA_USER_CONF_AWATCH   0x0008
#define CAMERA

typedef struct {
	UINT8 name_inx;
	UINT8 vol;
	UINT16 toggleConf;
}UserConf;


class CCamera
{
public:
	CCamera();
	~CCamera();

	int mId;
	long mLoginId;
	long hRealPlay;
	long hPlayHandle;
	long mPlayPort;
	char mIp[20];
	char mUserName[20];
	char mPwd[20];

	UINT16 mPort;
	SDK_CONFIG_NET_COMMON_V2 mCommonNetConfig;

	H264_DVR_CLIENTINFO clientInfo;
	H264_DVR_DEVICEINFO deviceInfo;

	CFile* mNormalRecordFile;
	CFile* mAlarmRecordFile;

	CRecordFileInfo* mNormalRecordFileInfo;
	CRecordFileInfo* mAlarmRecordFileInfo;

	BOOL isRecording;
	BOOL isAlarmRecording;
	BOOL isTalking;
	UserConf userConf;


public:
	void startRealPlay();
	void stopRealPlay();

	void startRecord(CFile* pFile);
	void stopRecord();

	void startAlarmRecord(CFile* pFile);
	void stopAlarmRecord();

	

	void subscribeAlarmMessage();
	void unsubscribeAlarmMessage();


	BOOL login();
	void logout();
};

