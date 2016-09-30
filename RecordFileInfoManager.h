#pragma once

#include "RecordFileInfo.h"




class CRecordFileInfoManager
{
private:
	CRecordFileInfoManager() ;

	~CRecordFileInfoManager() ;

public:
	CPtrList mNormalRecordInfoLists[CAMERA_MAX_NUM];
	CPtrList mAlarmRecordInfoLists[CAMERA_MAX_NUM];

	CString  mNormalCommonPath;
	CString  mAlarmCommonPath;

private:
	ULONGLONG mNormalRecordFileSize[CAMERA_MAX_NUM];
	ULONGLONG mAlarmRecordFileSize[CAMERA_MAX_NUM];

public:
	static CRecordFileInfoManager* getInstance() {
		static CRecordFileInfoManager instance;
		return &instance;
	}

private:
	CTime pPreDelTime;
public:
	void setNormalCommonPath(CString& path);
	void setAlarmCommonPath(CString& path);
	void instantiateNormalRecordInfoFromDB(int owner);
	void instantiateAlarmRecordInfoFromDB(int owner);
	void instantiateRecordInfoFromDB();

	void addNormalRecordInfo(int owner, CRecordFileInfo* pInfo);
	void addAlarmRecordInfo(int owner, CRecordFileInfo* pInfo);
	BOOL deleteNormalRecordInfo( CRecordFileInfo* pInfo);
	BOOL deleteAlarmRecordInfo(CRecordFileInfo* pInfo);
	BOOL deleteRecordInfo(CRecordFileInfo* pInfo);
	ULONGLONG appendSize(int owner, UINT8 type,ULONGLONG itemSize);
	ULONGLONG appendSize(CRecordFileInfo* pInfo);
    ULONGLONG devourSize(int owner, UINT8 type, ULONGLONG itemSize);
	ULONGLONG devourSize(CRecordFileInfo* pInfo);

public:
	ULONGLONG getNormalRecordFileSize(int id, UINT8 type);
	CRecordFileInfo* CRecordFileInfoManager::getFirstInfoNoUsing(int owner, UINT8 type, UINT8 action);
};

