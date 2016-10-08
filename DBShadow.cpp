#include "stdafx.h"
#include "DBShadow.h"



void DBShadow::Update(string state,DWORD_PTR pSubject)
{
	CRecordFileInfo* pInfo = (CRecordFileInfo*)pSubject;
	int index = pInfo->mOwner-1;
	char sqlStmt[128];

	CRecordFileInfo*(*paRecordFileInfo) = (pInfo->mStatus & RECORD_TYPE_ALARM) ? m_paAlarmRecordFileInfo : m_paRecordFileInfo;

	
	/// 删除文件
	if (state == "del") {
		int owner = pInfo->mOwner;
		__time64_t begin_sec = pInfo->mBeginTime.GetTime();

		if (pInfo->mStatus & RECORD_TYPE_ALARM) {

			if (!CRecordFileInfoManager::getInstance()->deleteAlarmRecordInfo(pInfo)) {
				TRACE("delete record info failed\n");
				ASSERT(FALSE);
			}
			PostMessage(pAlarmRecordFileWnd->m_hWnd, USER_MSG_DEL_FILE, owner, (LPARAM)pInfo);

			// Database opt
			sprintf_s(sqlStmt, "DELETE FROM alarm_record WHERE owner = %d AND begin_sec = %I64d;", owner, begin_sec);
			if (!sqlite.DirectStatement(sqlStmt)) {
				TRACE("sql stmt:%s error\n", sqlStmt);
			}
		}
		else {
			/// deleteNormalRecordInfo 将析构pInfo，所以在调用前记下 owner。
			if (!CRecordFileInfoManager::getInstance()->deleteNormalRecordInfo(pInfo)) {
				TRACE("delete record info failed\n");
				ASSERT(FALSE);
			}
			PostMessage(pRecordFileWnd->m_hWnd, USER_MSG_DEL_FILE, owner, (LPARAM)pInfo);

			// Database opt
			sprintf_s(sqlStmt, "DELETE FROM normal_record WHERE owner = %d AND begin_sec = %I64d;", owner, begin_sec);
			if (!sqlite.DirectStatement(sqlStmt)) {
				TRACE("sql stmt:%s error\n");
			}
		}
	}

	/// 文件开始
	else if (state == "begin") {
		/// 文件开始信息
		if (paRecordFileInfo[index] == NULL) {
			TRACE("%d begin record -- %I64d\n", pInfo->mOwner, pInfo->mBeginTime.GetTime());
			paRecordFileInfo[index] = new CRecordFileInfo();
			paRecordFileInfo[index]->mBeginTime = pInfo->mBeginTime;
			paRecordFileInfo[index]->mOwner = pInfo->mOwner;
			paRecordFileInfo[index]->mStatus = pInfo->mStatus;

			// Database opt
			sprintf_s(sqlStmt, "INSERT INTO %s (begin_sec, owner) VALUES (%I64d, %d);", pInfo->mStatus&RECORD_TYPE_ALARM?"alarm_record":"normal_record",
				                                                                        pInfo->mBeginTime.GetTime(), pInfo->mOwner);
			if (!sqlite.DirectStatement(sqlStmt)) {
				TRACE("sql stmt:%s error\n");
			}
		}
		else {
			TRACE("state error\n");
		}
	}

    /// 文件结束
	else if (state == "end") {
		if (paRecordFileInfo[index]) {

			// 文件大小有效
			if (pInfo->mTotalSize) {
				paRecordFileInfo[index]->mEndTime = pInfo->mEndTime;
				paRecordFileInfo[index]->mTotalSize = pInfo->mTotalSize;
				TRACE("%d end record success -- %I64d, %lld\n", paRecordFileInfo[index]->mOwner,
					paRecordFileInfo[index]->mEndTime.GetTime(),
					paRecordFileInfo[index]->mTotalSize);
				
				//PostMessage(pWnd->m_hWnd, USER_MSG_ADD_FILE, );
				if (paRecordFileInfo[index]->mStatus & RECORD_TYPE_ALARM) {
					CRecordFileInfoManager::getInstance()->addAlarmRecordInfo(paRecordFileInfo[index]->mOwner, paRecordFileInfo[index]);
					PostMessage(pAlarmRecordFileWnd->m_hWnd, USER_MSG_ADD_FILE, 0, (LPARAM)paRecordFileInfo[index]);					
				}
				else {
					CRecordFileInfoManager::getInstance()->addNormalRecordInfo(paRecordFileInfo[index]->mOwner, paRecordFileInfo[index]);
					PostMessage(pRecordFileWnd->m_hWnd, USER_MSG_ADD_FILE, 0, (LPARAM)paRecordFileInfo[index]);
				}

				// Database opt
				sprintf_s(sqlStmt, "UPDATE %s SET end_sec = %I64d, total_size = %lld WHERE owner = %d AND begin_sec = %I64d;",
					paRecordFileInfo[index]->mStatus&RECORD_TYPE_ALARM ? "alarm_record" : "normal_record",
					paRecordFileInfo[index]->mEndTime.GetTime(), paRecordFileInfo[index]->mTotalSize,
					paRecordFileInfo[index]->mOwner, paRecordFileInfo[index]->mBeginTime.GetTime() );
				if (!sqlite.DirectStatement(sqlStmt)) {
					TRACE("sql stmt:%s error\n", sqlStmt);
				}
			}
			//文件大小为 0 视为无效文件，删除
			else {
				TRACE("%d end record failed\n", paRecordFileInfo[index]->mOwner);
				// Database opt
				sprintf_s(sqlStmt, "DELETE FROM %s WHERE owner = %d AND begin_sec = %I64d;", 
					paRecordFileInfo[index]->mStatus&RECORD_TYPE_ALARM ? "alarm_record" : "normal_record",
					paRecordFileInfo[index]->mOwner, paRecordFileInfo[index]->mBeginTime.GetTime());
				if (!sqlite.DirectStatement(sqlStmt)) {
					TRACE("sql stmt:%s error\n", sqlStmt);
				}

				delete paRecordFileInfo[index];
			}
			paRecordFileInfo[index] = NULL;
		}
		else {
			TRACE("state error\n");
		}
	}
	else {
		TRACE("state error\n");
	}


	///// 文件开始信息
	//if (paRecordFileInfo[index] == NULL) {
	//	TRACE("%d begin record -- %I64d\n", pInfo->mOwner,pInfo->mBeginTime.GetTime());
	//	paRecordFileInfo[index] = new CRecordFileInfo();
	//	paRecordFileInfo[index]->mBeginTime = pInfo->mBeginTime;
	//	paRecordFileInfo[index]->mOwner = pInfo->mOwner;
	//}
	///// 文件结束信息
	//else {
	//	
	//	if (pInfo->mTotalSize) {
	//		paRecordFileInfo[index]->mEndTime = pInfo->mEndTime;
	//		paRecordFileInfo[index]->mTotalSize = pInfo->mTotalSize;
	//		TRACE("%d end record success -- %I64d, %lld\n", paRecordFileInfo[index]->mOwner,
	//			paRecordFileInfo[index]->mEndTime.GetTime(),
	//			paRecordFileInfo[index]->mTotalSize);
	//		CRecordFileInfoManager::getInstance()->addNormalRecordInfo(paRecordFileInfo[index]->mOwner, paRecordFileInfo[index]);
	//		//PostMessage(pWnd->m_hWnd, USER_MSG_ADD_FILE, );
	//		if (paRecordFileInfo[index]->mStatus & RECORD_TYPE_NORMAL) {
	//			PostMessage(pRecordFileWnd->m_hWnd, USER_MSG_ADD_FILE, 0, (LPARAM)paRecordFileInfo[index]);
	//		}
	//	}
	//	//文件大小为 0 视为无效文件，删除
	//	else {
	//		TRACE("%d end record failed\n", paRecordFileInfo[index]->mOwner);
	//		delete paRecordFileInfo[index];
	//	}
	//	paRecordFileInfo[index] = NULL;
	//}
}
