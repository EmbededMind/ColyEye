#include "stdafx.h"
#include "RecordFileInfoManager.h"


CRecordFileInfoManager::CRecordFileInfoManager()
{

}



CRecordFileInfoManager::~CRecordFileInfoManager()
{

}


/**@brief 设置普通录像的存储路径
 *
 * @param[in] 要设置的路径
 */
void CRecordFileInfoManager::setNormalCommonPath(CString& path)
{
	this->mNormalCommonPath = path;
}


/**@brief 设置报警录像的存储路径
*
* @param[in] 要设置的路径
*/
void CRecordFileInfoManager::setAlarmCommonPath(CString& path)
{
	this->mAlarmCommonPath = path;
}



void CRecordFileInfoManager::instantiateNormalRecordInfoFromDB(int owner)
{
	CRecordFileInfo* pNewInfo;

	__time64_t begin_sec = 0;
	__time64_t end_sec = 0;
	LONGLONG total_size;

	char sqlStmt[128];

	sprintf_s(sqlStmt, "SELECT * FROM normal_record WHERE owner == %d;", owner);


	SQLiteStatement* stmt	= sqlite.Statement(sqlStmt);
	while (stmt->NextRow()) {
		begin_sec = stmt->ValueInt(DB_COL_BEGIN_SEC);
		end_sec = stmt->ValueInt(DB_COL_END_SEC);
		total_size = stmt->ValueInt(DB_COL_TOTAL_SIZE);

		/// Valid record information
		if (end_sec > begin_sec) {
			pNewInfo = new CRecordFileInfo();
		    pNewInfo->mBeginTime = begin_sec;
			pNewInfo->mEndTime = end_sec;
			pNewInfo->mTotalSize = total_size;
			pNewInfo->mOwner = owner;

			mNormalRecordInfoLists[owner - 1].AddTail(pNewInfo);
			mNormalRecordFileSize[owner - 1] += total_size;
			//pNewInfo->dump(sqlStmt, 128);
		}
		/// Invalid record information
		else {
			CTime beginTime = begin_sec;
			CString fileName;
			fileName.Format(_T("%d\\%d%02d%02d%02d%02d%02d.h264"), owner, beginTime.GetYear(), beginTime.GetMonth(),
				beginTime.GetDay(), beginTime.GetHour(), beginTime.GetMinute(),beginTime.GetSecond());
			fileName = _T(NORMAL_RECORD_PATH) + fileName;
			CFileFind  ff;
			if (ff.FindFile(fileName)) {
				CFile::Remove(fileName);
				sprintf_s(sqlStmt, "DELETE FROM normal_record WHERE begin_sec == %I64d AND owner == %d;", begin_sec, owner);
				if (!sqlite.DirectStatement(sqlStmt)) {
					TRACE("sql error stmt:%s\n", sqlStmt);
				}
			}
		}
	}
}



void CRecordFileInfoManager::instantiateAlarmRecordInfoFromDB(int owner)
{
	CRecordFileInfo* pNewInfo;

	__time64_t begin_sec = 0;
	__time64_t end_sec = 0;
	LONGLONG total_size;

	char sqlStmt[128];

	sprintf_s(sqlStmt, "SELECT * FROM alarm_record WHERE owner == %d;", owner);
	TRACE("sql stmt:%s", sqlStmt);

	SQLiteStatement* stmt = sqlite.Statement(sqlStmt);
	while (stmt->NextRow()) {
		begin_sec = stmt->ValueInt(DB_COL_BEGIN_SEC);
		end_sec = stmt->ValueInt(DB_COL_END_SEC);
		total_size = stmt->ValueInt(DB_COL_TOTAL_SIZE);

		/// Valid record information
		if (end_sec > begin_sec) {
			pNewInfo = new CRecordFileInfo();
			pNewInfo->mBeginTime = begin_sec;
			pNewInfo->mEndTime = end_sec;
			pNewInfo->mTotalSize = total_size;
			pNewInfo->mStatus = stmt->ValueInt(DB_COL_STATUS);

			mAlarmRecordInfoLists[owner - 1].AddTail(pNewInfo);
			mAlarmRecordFileSize[owner - 1] += pNewInfo->mTotalSize;
			pNewInfo->dump(sqlStmt, 128);
			WriteLog(_T(LOG_PATH), CString(sqlStmt));
		}
		/// Invalid record information
		else {
			CTime beginTime = begin_sec;
			CString fileName;
			fileName.Format(_T("%d\\%d%02d%02d%02d%02d%02d.h264"), owner, beginTime.GetYear(), beginTime.GetMonth(),
				beginTime.GetDay(), beginTime.GetHour(), beginTime.GetMinute(), beginTime.GetSecond());
			fileName = _T(ALARM_RECORD_PATH) + fileName;
			CFileFind  ff;
			if (ff.FindFile(fileName)) {
				CFile::Remove(fileName);
				sprintf_s(sqlStmt, "DELETE FROM alarm_record WHERE begin_sec == %I64d AND owner == %d;", begin_sec, owner);
				if (!sqlite.DirectStatement(sqlStmt)) {
					TRACE("sql error stmt:%s\n", sqlStmt);
				}
			}
		}
	}
}



void CRecordFileInfoManager::instantiateRecordInfoFromDB()
{
	int i = 0;
	for (; i < CAMERA_MAX_NUM; i++) {
		instantiateNormalRecordInfoFromDB(i+1);
		instantiateAlarmRecordInfoFromDB(i+1);
	}
}



void CRecordFileInfoManager::addNormalRecordInfo(int owner, CRecordFileInfo* pInfo)
{
	mNormalRecordInfoLists[owner - 1].AddTail(pInfo);
	appendSize(owner, RECORD_TYPE_NORMAL, pInfo->mTotalSize);
}



void CRecordFileInfoManager::addAlarmRecordInfo(int owner, CRecordFileInfo* pInfo)
{
	mAlarmRecordInfoLists[owner - 1].AddTail(pInfo);
	appendSize(owner, RECORD_TYPE_ALARM, pInfo->mTotalSize);
	TRACE("%d add new record info\n", owner);
}



BOOL CRecordFileInfoManager::deleteNormalRecordInfo( CRecordFileInfo* pInfo)
{
	POSITION pos = mNormalRecordInfoLists[pInfo->mOwner - 1].Find(pInfo);
	if (pos) {
		mNormalRecordInfoLists[pInfo->mOwner - 1].RemoveAt(pos);
		devourSize(pInfo->mOwner, RECORD_TYPE_NORMAL,pInfo->mTotalSize);
		delete pInfo;
		return TRUE;
	}
	else {
		return FALSE;
	}
}



BOOL  CRecordFileInfoManager::deleteAlarmRecordInfo( CRecordFileInfo* pInfo)
{
	POSITION pos = mAlarmRecordInfoLists[pInfo->mOwner - 1].Find(pInfo);
	if (pos) {
		mAlarmRecordInfoLists[pInfo->mOwner - 1].RemoveAt(pos);
		devourSize(pInfo->mOwner, RECORD_TYPE_ALARM, pInfo->mTotalSize);
		delete pInfo;
		return TRUE;
	}
	else {
		return FALSE;
	}
}



BOOL CRecordFileInfoManager::deleteRecordInfo(CRecordFileInfo* pInfo)
{
	if (pInfo->mStatus & RECORD_TYPE_ALARM) {
		return this->deleteAlarmRecordInfo(pInfo);
	}
	else {
		return this->deleteNormalRecordInfo(pInfo);
	}
}

ULONGLONG CRecordFileInfoManager::appendSize(int owner, UINT8 type,ULONGLONG itemSize)
{
	ULONGLONG * pSize = (type == RECORD_TYPE_NORMAL) ? mNormalRecordFileSize : mAlarmRecordFileSize;
	pSize[owner - 1] += itemSize;
	return pSize[owner - 1];
}


ULONGLONG CRecordFileInfoManager::appendSize(CRecordFileInfo* pInfo)
{
	ASSERT(pInfo && pInfo->mOwner > 0);
	ULONGLONG * pSize = (pInfo->mStatus & RECORD_TYPE_NORMAL) ? mNormalRecordFileSize : mAlarmRecordFileSize;
	pSize[pInfo->mOwner - 1] += pInfo->mTotalSize;
	return pSize[pInfo->mOwner - 1];
}


ULONGLONG CRecordFileInfoManager::devourSize(int owner, UINT8 type, ULONGLONG itemSize)
{
	ULONGLONG * pSize = (type == RECORD_TYPE_NORMAL) ? mNormalRecordFileSize : mAlarmRecordFileSize;
	if (pSize[owner - 1] >= itemSize) {
		pSize[owner - 1] -= itemSize;
	}

	return pSize[owner - 1];
}



ULONGLONG CRecordFileInfoManager::devourSize(CRecordFileInfo* pInfo)
{
	ASSERT(pInfo && pInfo->mOwner > 0);
	ULONGLONG * pSize = (pInfo->mStatus & RECORD_TYPE_NORMAL) ? mNormalRecordFileSize : mAlarmRecordFileSize;
	if (pSize[pInfo->mOwner - 1] >= pInfo->mTotalSize) {
		pSize[pInfo->mOwner - 1] -= pInfo->mTotalSize;
	}

	return pSize[pInfo->mOwner - 1];
}

ULONGLONG CRecordFileInfoManager::getNormalRecordFileSize(int id, UINT8 type)
{
	if (type == RECORD_TYPE_NORMAL)
	{
		return mNormalRecordFileSize[id - 1];
	}
	else
	{
		return mAlarmRecordFileSize[id - 1];
	}
	return ULONGLONG(0);
}

CRecordFileInfo * CRecordFileInfoManager::getFirstInfoNoUsing(int owner, UINT8 type, UINT8 action)
{
	POSITION pos;
	CPtrList * pInfoList = (type == RECORD_TYPE_NORMAL) ? mNormalRecordInfoLists : mAlarmRecordInfoLists;
	CRecordFileInfo* pInfo;

	if (!pInfoList->IsEmpty())
	{
		for (pos = pInfoList[owner - 1].GetHeadPosition(); pos != NULL;)
		{
			pInfo = (CRecordFileInfo*)pInfoList[owner - 1].GetNext(pos);
			TRACE("STATUS = %x\n", pInfo->mStatus);
			if (action == 1 && (pInfo->mStatus & 0x0f) == 0 && (pInfo->mBeginTime != this->pPreDelTime) && (pInfo->mEndTime) != 0)
			{
				this->pPreDelTime = pInfo->mBeginTime;
				return pInfo;
			}
		}
	}
	return nullptr;
}

