#pragma once

#include "Camera.h"


class CCameraManager
{
private:
	CCameraManager() {};
	CCameraManager(const CCameraManager&) {};
	~CCameraManager() {};

public:
	static CCameraManager* getInstance() {
		static CCameraManager instance;
		return &instance;
	}

	void destrucCameras();

	// 历史登录设备的 id 和 mac
	BOOL mHasAppearedInHistory[CAMERA_MAX_NUM];

	// 当前登录设备所占用的 id 
	BOOL mConsumptionOfCameraId[CAMERA_MAX_NUM];

	CCamera*  mPtrCameras[CAMERA_MAX_NUM];

	SDK_CONFIG_NET_COMMON_V2 mSdkConfNetCommonV2[CAMERA_MAX_NUM];
	CPtrList mCameras;
	

	BOOL addCamera(CCamera* pNewCamera);
	void deleteCamera(CCamera* pOldCamera);

	BOOL distributeId(CCamera* pCamera);
	CCamera*  findCameraByLoginId(long loginId);
	CCamera*  findCameraById(int id);


	int getIdFromDB(const char* mac);
	BOOL putIdIntoDB(const int id, const char* mac);
	BOOL updateIdInDB(const int id, const char* mac);
	void loadDeviceHistoryFrmoDB();
};

