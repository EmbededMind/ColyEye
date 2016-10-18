#pragma once

#include "Subject.h"
#include "RecordFileInfo.h"

class RecordFileManager :
	public Subject
{
private:
	RecordFileManager() 
	{
		
	}
	RecordFileManager(const RecordFileManager&);
	RecordFileManager & operator = (const RecordFileManager &);
	~RecordFileManager() {}


public:
	static RecordFileManager * GetInstance()
	{
		if (!PathIsDirectory(_T(RECORD_PATH)))
		{
			CreateDirectory(_T(RECORD_PATH), NULL);
		}
		if (!PathIsDirectory(_T(NORMAL_RECORD_PATH)))
		{
			CreateDirectory(_T(NORMAL_RECORD_PATH), NULL);
		}
		if (!PathIsDirectory(_T(ALARM_RECORD_PATH)))
		{
			CreateDirectory(_T(ALARM_RECORD_PATH), NULL);
		}

		if (!PathIsDirectory(_T(SOUND_PATH)))
		{
			CreateDirectory(_T(SOUND_PATH), NULL);
		}

		CString strRecordPath, temp;
		for (int i = 1; i <= 6; i++)
		{
			temp.Format(_T("%d\\"), i);
			strRecordPath = _T(NORMAL_RECORD_PATH) + temp;
			if (!PathIsDirectory(strRecordPath))
			{
				CreateDirectory(strRecordPath, NULL);
			}
			strRecordPath = _T(ALARM_RECORD_PATH) + temp;
			if (!PathIsDirectory(strRecordPath))
			{
				CreateDirectory(strRecordPath, NULL);
			}
		}
		static RecordFileManager instance;
		return &instance;
	}

private:
	CFile m_aRecordFiles[CAMERA_MAX_NUM];
	CFile m_aAlarmRecordFiles[CAMERA_MAX_NUM];
	CRecordFileInfo * m_paRecordFileInfo[CAMERA_MAX_NUM];
	CRecordFileInfo * m_paAlarmRecordFileInfo[CAMERA_MAX_NUM];

public :
	virtual void Notify(string state, CRecordFileInfo* pInfo);
	CFile* DistributeRecordFile(int id);
	void   RecallRecordFile(int id);

	CFile* DistributeAlarmRecordFile(int id);
	void   RecallAlarmRecordFile(int id);

	CFile* DistributeRecordFile(int id, UINT8 record_type);
	void   RecallRecordFile(int id, UINT8 record_type);

private:
	UINT8 RemoveOldFile(int id, UINT8 record_type);
	UINT8 LimitSpace(int id, UINT8 record_type);
	UINT8 DeleteRecordFile(CString &delPath);
};

