#include "stdafx.h"
#include "DBShadow.h"



void DBShadow::Update(string state,DWORD_PTR pSubject)
{
	CRecordFileInfo* pInfo = (CRecordFileInfo*)pSubject;
	int index = pInfo->mOwner-1;

	CRecordFileInfo*(*paRecordFileInfo) = (pInfo->mStatus & RECORD_TYPE_ALARM) ? m_paAlarmRecordFileInfo : m_paRecordFileInfo;

	/// ɾ���ļ�
	if (state == "del") {
		if (pInfo->mStatus & RECORD_TYPE_ALARM) {
			int owner = pInfo->mOwner;
			if (!CRecordFileInfoManager::getInstance()->deleteAlarmRecordInfo(pInfo)) {
				TRACE("delete record info failed\n");
				ASSERT(FALSE);
			}
			PostMessage(pAlarmRecordFileWnd->m_hWnd, USER_MSG_DEL_FILE, owner, (LPARAM)pInfo);
		}
		else {
			/// deleteNormalRecordInfo ������pInfo�������ڵ���ǰ���� owner��
			int owner = pInfo->mOwner;
			if (!CRecordFileInfoManager::getInstance()->deleteNormalRecordInfo(pInfo)) {
				TRACE("delete record info failed\n");
				ASSERT(FALSE);
			}
			PostMessage(pRecordFileWnd->m_hWnd, USER_MSG_DEL_FILE, owner, (LPARAM)pInfo);
		}
	}

	/// �ļ���ʼ
	else if (state == "begin") {
		/// �ļ���ʼ��Ϣ
		if (paRecordFileInfo[index] == NULL) {
			TRACE("%d begin record -- %I64d\n", pInfo->mOwner, pInfo->mBeginTime.GetTime());
			paRecordFileInfo[index] = new CRecordFileInfo();
			paRecordFileInfo[index]->mBeginTime = pInfo->mBeginTime;
			paRecordFileInfo[index]->mOwner = pInfo->mOwner;
			paRecordFileInfo[index]->mStatus = pInfo->mStatus;
		}
		else {
			TRACE("state error\n");
		}
	}

    /// �ļ�����
	else if (state == "end") {
		if (paRecordFileInfo[index]) {
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
			}
			//�ļ���СΪ 0 ��Ϊ��Ч�ļ���ɾ��
			else {
				TRACE("%d end record failed\n", paRecordFileInfo[index]->mOwner);
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


	///// �ļ���ʼ��Ϣ
	//if (paRecordFileInfo[index] == NULL) {
	//	TRACE("%d begin record -- %I64d\n", pInfo->mOwner,pInfo->mBeginTime.GetTime());
	//	paRecordFileInfo[index] = new CRecordFileInfo();
	//	paRecordFileInfo[index]->mBeginTime = pInfo->mBeginTime;
	//	paRecordFileInfo[index]->mOwner = pInfo->mOwner;
	//}
	///// �ļ�������Ϣ
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
	//	//�ļ���СΪ 0 ��Ϊ��Ч�ļ���ɾ��
	//	else {
	//		TRACE("%d end record failed\n", paRecordFileInfo[index]->mOwner);
	//		delete paRecordFileInfo[index];
	//	}
	//	paRecordFileInfo[index] = NULL;
	//}
}
