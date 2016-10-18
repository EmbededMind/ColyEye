#include "stdafx.h"
#include "RecordFileManager.h"
#include "RecordFileInfoManager.h"

extern CMutex mutex_RealDataCB;



void RecordFileManager::Notify(string state, CRecordFileInfo* pInfo)
{
	list<Observer*>::iterator iter = this->m_list.begin();
	for (; iter != m_list.end(); iter++) {
		(*iter)->Update(state, (DWORD_PTR)pInfo);
	}
}



/**@brief 暴露一个已打开的文件供设备录像
 *
 */
CFile* RecordFileManager::DistributeRecordFile(int id)
{   
	ASSERT(id > 0 && id <= CAMERA_MAX_NUM);

	int index = id - 1;

	if (this->m_aRecordFiles[index].m_hFile == CFile::hFileNull) {
		CRecordFileInfo newInfo;
		CTime time = CTime::GetCurrentTime();
		
		CString fileName;
		fileName.Format(_T("%d\\%d%02d%02d%02d%02d%02d.h264"), id, time.GetYear(), time.GetMonth(), time.GetDay(),
			                                                       time.GetHour(), time.GetMinute(), time.GetSecond());

		CFileException fException;
		if (!m_aRecordFiles[index].Open(_T(NORMAL_RECORD_PATH) + fileName, CFile::modeCreate | CFile::modeWrite, &fException)) {
			TRACE("Normal record file open failed\n");
			return NULL;
		}
	    
		newInfo.mBeginTime = time;
		newInfo.mOwner = id;
		Notify("begin",&newInfo);

		return &m_aRecordFiles[index];
	}
	else{
		return NULL;
	}	
}



void RecordFileManager::RecallRecordFile(int id)
{
	ASSERT(id > 0  &&  id <= CAMERA_MAX_NUM);

	if (this->m_aRecordFiles[id - 1].m_hFile != CFile::hFileNull) {
		CRecordFileInfo oldInfo;
		oldInfo.mOwner = id;
		oldInfo.mEndTime = CTime::GetCurrentTime();
		
		//检查文件属性
		CFileStatus status;
		if (m_aRecordFiles[id - 1].GetStatus(status)) {
			oldInfo.mTotalSize = status.m_size;
		}		
		oldInfo.mTotalSize = 0;
		this->m_aRecordFiles[id - 1].Close();

		//文件大小为 0 视为无效，删除文件。
		if (oldInfo.mTotalSize == 0) {
			CFile::Remove(status.m_szFullName);
		}

		Notify("end",&oldInfo);		
	}
}



CFile* RecordFileManager::DistributeAlarmRecordFile(int id)
{
	ASSERT(id > 0 && id <= CAMERA_MAX_NUM);

	int index = id - 1;

	if (this->m_aAlarmRecordFiles[index].m_hFile == CFile::hFileNull) {
		CRecordFileInfo newInfo;
		CTime time = CTime::GetCurrentTime();

		CString fileName;
		fileName.Format(_T("%d\\%d%02d%02d%02d%02d%02d.h264"), id, time.GetYear(), time.GetMonth(), time.GetDay(),
			time.GetHour(), time.GetMinute(), time.GetSecond());

		CFileException fException;
		if (!m_aAlarmRecordFiles[index].Open(_T(NORMAL_RECORD_PATH) + fileName, CFile::modeCreate | CFile::modeWrite, &fException)) {
			TRACE("Normal record file open failed\n");
			return NULL;
		}

		newInfo.mBeginTime = time;
		newInfo.mOwner = id;
		newInfo.mStatus |= RECORD_TYPE_ALARM;
		Notify("begin",&newInfo);

		return &m_aAlarmRecordFiles[index];
	}
	else {
		return NULL;
	}
}



void RecordFileManager::RecallAlarmRecordFile(int id)
{
	ASSERT(id > 0 && id <= CAMERA_MAX_NUM);

	if (this->m_aAlarmRecordFiles[id - 1].m_hFile != CFile::hFileNull) {
		CRecordFileInfo oldInfo;
		oldInfo.mStatus |= RECORD_TYPE_ALARM;
		oldInfo.mEndTime = CTime::GetCurrentTime();

		//检查文件属性
		CFileStatus status;
		if (m_aAlarmRecordFiles[id - 1].GetStatus(status)) {
			oldInfo.mTotalSize = status.m_size;
		}
		oldInfo.mTotalSize = 0;
		this->m_aAlarmRecordFiles[id - 1].Close();

		//文件大小为 0 视为无效，删除文件。
		if (oldInfo.mTotalSize == 0) {
			CFile::Remove(status.m_szFullName);
		}

		Notify("end",&oldInfo);
	}
}



CFile* RecordFileManager::DistributeRecordFile(int id, UINT8 record_type)
{
	ASSERT(id > 0 && id <= CAMERA_MAX_NUM);

	this->RemoveOldFile(id, RECORD_TYPE_ALARM);
	this->RemoveOldFile(id, RECORD_TYPE_NORMAL);

	this->LimitSpace(id, RECORD_TYPE_ALARM);
	this->LimitSpace(id, RECORD_TYPE_NORMAL);

	CFile* paRecordFiles  = (record_type & RECORD_TYPE_ALARM) ? m_aAlarmRecordFiles : m_aRecordFiles;
	int index = id - 1;

	if (paRecordFiles[index].m_hFile == CFile::hFileNull) {
		CRecordFileInfo newInfo;
		newInfo.mStatus |= record_type;
		CTime time = CTime::GetCurrentTime();

		CString fileName;
		fileName.Format(_T("%d\\%d%02d%02d%02d%02d%02d.h264"), id, time.GetYear(), time.GetMonth(), time.GetDay(),
			time.GetHour(), time.GetMinute(), time.GetSecond());

		CFileException fException;
		if (record_type == RECORD_TYPE_ALARM)
		{
			if (!paRecordFiles[index].Open(_T(ALARM_RECORD_PATH) + fileName, CFile::modeCreate | CFile::modeWrite, &fException)) {
				TRACE("Normal record file open failed\n");
				return NULL;
			}
		}
		else {
			if (!paRecordFiles[index].Open(_T(NORMAL_RECORD_PATH) + fileName, CFile::modeCreate | CFile::modeWrite, &fException)) {
				TRACE("Normal record file open failed\n");
				return NULL;
			}
		}


		newInfo.mBeginTime = time;
		newInfo.mOwner = id;
		Notify("begin",&newInfo);

		return &paRecordFiles[index];
	}
	else {
		TRACE("Previous file stop unsuccessfully\n");
		return NULL;
	}
}



void RecordFileManager::RecallRecordFile(int id, UINT8 record_type)
{
	ASSERT(id > 0 && id <= CAMERA_MAX_NUM);

	CFile* paRecordFiles = (record_type & RECORD_TYPE_ALARM) ? m_aAlarmRecordFiles : m_aRecordFiles;

	if (paRecordFiles[id - 1].m_hFile != CFile::hFileNull) {
		CRecordFileInfo oldInfo;
		oldInfo.mOwner = id;
		oldInfo.mStatus = record_type;
		oldInfo.mEndTime = CTime::GetCurrentTime();

		//检查文件属性
		CFileStatus status;

mutex_RealDataCB.Lock();/// @see Camera.cpp realDataCallBack_V2

		if (paRecordFiles[id - 1].GetStatus(status)) {
			oldInfo.mTotalSize = status.m_size;
		}
		else {
			oldInfo.mTotalSize = 0;
		}
		
		paRecordFiles[id - 1].Close();

mutex_RealDataCB.Unlock();/// @see Camera.cpp realDataCallBack_V2

		//文件大小为 0 视为无效，删除文件。
		if (oldInfo.mTotalSize == 0) {
			CFile::Remove(status.m_szFullName);
		}
		Notify("end", &oldInfo);
	}
}

UINT8 RecordFileManager::RemoveOldFile(int id, UINT8 record_type)
{
	CTime time = 0;
	CRecordFileInfo* fileInfo = CRecordFileInfoManager::getInstance()->getFirstInfoNoUsing(id, record_type, 1);
	CString delPath;

	if (fileInfo)
	{
		time = fileInfo->mBeginTime;
		CTimeSpan timeSpan = CTime::GetCurrentTime() - time;
		while (timeSpan.GetTotalMinutes() >= ((record_type == RECORD_TYPE_NORMAL) ? RECORD_NORMAL_TIME : RECORD_ALARM_TIME))
		{
			(record_type == RECORD_TYPE_NORMAL) ? delPath = NORMAL_RECORD_PATH : delPath = ALARM_RECORD_PATH;
			CString tmp;
			tmp.Format(_T("%d\\%d%02d%02d%02d%02d%02d.h264"), id, time.GetYear(), time.GetMonth(), time.GetDay(),
				time.GetHour(), time.GetMinute(), time.GetSecond());
			delPath += tmp;
			TRACE(_T("delete---") + delPath + _T("\n"));
			if (DeleteRecordFile(delPath))
			{
				Notify("del", fileInfo);
				fileInfo = CRecordFileInfoManager::getInstance()->getFirstInfoNoUsing(id, record_type, 1);
				if (fileInfo)
				{
					time = fileInfo->mBeginTime;
					timeSpan = CTime::GetCurrentTime() - time;
				}
				else
				{
					return UINT8(FALSE);
				}
			}
			else
			{
				return FALSE;
			}
		}
	}
	return UINT8(FALSE);
}

UINT8 RecordFileManager::LimitSpace(int id, UINT8 record_type)
{
	int err = 0;
	CString delPath;
	CTime time = 0;

	float space = CRecordFileInfoManager::getInstance()->getNormalRecordFileSize(id, record_type) / 1024.0f / 1024.0f;
	CRecordFileInfo* fileInfo;
	while (space > ((record_type == RECORD_TYPE_NORMAL) ? RECORD_NORMAL_SPACE : RECORD_ALARM_SPACE))
	{
		(record_type == RECORD_TYPE_NORMAL) ? delPath = _T(NORMAL_RECORD_PATH) : delPath = _T(ALARM_RECORD_PATH);
		fileInfo = CRecordFileInfoManager::getInstance()->getFirstInfoNoUsing(id, record_type, 1);
		if (fileInfo)
		{
			err++;
			time = fileInfo->mBeginTime;
			CString tmp;
			tmp.Format(_T("%d\\%d%02d%02d%02d%02d%02d.h264"), id, time.GetYear(), time.GetMonth(), time.GetDay(),
				time.GetHour(), time.GetMinute(), time.GetSecond());
			delPath += tmp;
			TRACE(_T("delete---") + delPath + _T("\n"));
			if (DeleteRecordFile(delPath))
			{
				Notify("del", fileInfo);
				space = CRecordFileInfoManager::getInstance()->getNormalRecordFileSize(id, record_type) / 1024.0f / 1024.0f;
			}
			else
			{
				return UINT8(FALSE);
			}
			if (err > 5) return UINT8(FALSE);
		}
		else
		{
			return UINT8(FALSE);
		}
	}
	return UINT8(TRUE);
}

UINT8 RecordFileManager::DeleteRecordFile(CString & delPath)
{
	WIN32_FIND_DATA findFileData;
	HANDLE hfind = ::FindFirstFile(delPath, &findFileData);
	if (hfind == INVALID_HANDLE_VALUE)
	{
		return UINT8(2);
	}
	DeleteFile(delPath);
	hfind = ::FindFirstFile(delPath, &findFileData);
	if (hfind == INVALID_HANDLE_VALUE)
	{
		return UINT8(1);
	}
	return UINT8();
}
