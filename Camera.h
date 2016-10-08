#pragma once

#include "RecordFileInfo.h"

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
	SDK_CONFIG_NET_COMMON_V2* mCommonNetConfig;

	H264_DVR_CLIENTINFO clientInfo;
	H264_DVR_DEVICEINFO deviceInfo;

	CFile* mNormalRecordFile;
	CFile* mAlarmRecordFile;

	CRecordFileInfo* mNormalRecordFileInfo;
	CRecordFileInfo* mAlarmRecordFileInfo;

	BOOL isRecording;
	BOOL isAlarmRecording;
	BOOL isTalking;

public:
	void startRealPlay();
	void stopRealPlay();

	void startRecord(CFile* pFile);
	void stopRecord();

	void startAlarmRecord(CFile* pFile);
	void stopAlarmRecord();

	void subscribeAlarmMessage();

	BOOL login();
	void logout();
};

