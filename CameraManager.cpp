#include "stdafx.h"
#include "CameraManager.h"

#include "stdafx.h"
#include "CameraManager.h"


/**@brief ���������ͷ���Դ
 *
 */
void CCameraManager::destrucCameras()
{
	POSITION pos = mCameras.GetHeadPosition();
	CCamera* pDev = NULL;

	while (pos) {
		pDev = (CCamera*)mCameras.GetNext(pos);
		delete(pDev);
	}


	//for (int i = 0; i < CAMERA_MAX_NUM; i++) {
	//	if()
	//}
}



/**@brief ���һ������ͷ�豸
*
* @param [in] pNewCamera  ����ӵ��豸��ָ��.
*/
BOOL CCameraManager::addCamera(CCamera* pNewCamera)
{
	if (mCameras.GetCount() < CAMERA_MAX_NUM) {
		mCameras.AddTail(pNewCamera);
		return true;
	}
	return false;
}



/**@brief ɾ��һ������ͷ�豸
*
* @param [in] pOldCamera Ҫɾ�����豸��ָ��.
*/
void CCameraManager::deleteCamera(CCamera* pOldCamera)
{
	ASSERT(pOldCamera != NULL);
	POSITION pos = mCameras.Find(pOldCamera);
	if (pos != NULL) {
		mCameras.RemoveAt(pos);
		delete(pOldCamera); /**  �����������������ٶ��� */
	}
}


/**@brief Ϊ���������һ��id.
*
* @param [in] pCamera ҪΪ֮����id�������.
*/
BOOL CCameraManager::distributeId(CCamera* pCamera)
{
	int id = 0;
	if (pCamera->mCommonNetConfig.sMac) {
		// �����ʷ��¼�м�¼���д��豸����Ϣ������¼��id����֮
		id = getIdFromDB(pCamera->mCommonNetConfig.sMac);
		if (id) {
			pCamera->mId = id;
			return true;
		}
		else {
			//�����ʷ��¼��û�д��豸����Ϣ��������ʷ�豸û��ռ�õ�id
			//for (int i = 0; i < CAMERA_MAX_NUM; i++) {
			//	if (this->mHasAppearedInHistory[i] == FALSE) {
			//		this->mConsumptionOfCameraId[i] = 1;
			//		pCamera->mId = i + 1;
			//		this->mHasAppearedInHistory[i] = TRUE;
			//		putIdIntoDB(i + 1, pCamera->mCommonNetConfig.sMac);
			//		return true;
			//	}
			//}

			for (int i = 0; i < CAMERA_MAX_NUM; i++) {
				if (mHasAppearedInHistory[i] == false) {
					mLoginDevice[i] = pCamera;
					pCamera->mId = i + 1;
					mHasAppearedInHistory[i] = true;
					putIdIntoDB(i+1, pCamera->mCommonNetConfig.sMac);
					return true;
				}
			}

			//�����ʷ�豸û��δռ�õ�id�����ҵ�ǰ�ѵ�¼�豸û��ռ�õ�id
			//����еĻ������Ƕ�Ӧ����ʷ�豸����Ϣ������id����֮
			//for (int i = 0; i < CAMERA_MAX_NUM; i++) {
			//	/// �µ��豸�������µ�id���������ݿ⡣
			//	if (this->mConsumptionOfCameraId[i] == 0) {
			//		this->mConsumptionOfCameraId[i] = 1;
			//		pCamera->mId = i + 1;
			//		//
			//		updateIdInDB(i + 1, pCamera->mCommonNetConfig.sMac);
			//		return true;
			//	}
			//}

			for (int i = 0; i < CAMERA_MAX_NUM; i++) {
				if (mLoginDevice[i] == nullptr) {
					mLoginDevice[i] = pCamera;
					pCamera->mId = i + 1;
					updateIdInDB(i+1, pCamera->mCommonNetConfig.sMac);
					return true;
				}
			}

			return false;
		}
	}
	return false;
}


CCamera* CCameraManager::findCameraByLoginId(long loginId)
{
	POSITION pos = this->mCameras.GetHeadPosition();
	CCamera* pDev = NULL;
	while (pos) {
		pDev = (CCamera*)this->mCameras.GetNext(pos);
		if (pDev->mLoginId == loginId) {
			return pDev;
		}
	}



	//for (int i = 0; i < CAMERA_MAX_NUM; i++) {
	//	if (mCameras[i].mId == loginId) {
	//		return &mCameras[i];
	//	}
	//}

	return nullptr;
}



CCamera* CCameraManager::findCameraById(int id)
{
	POSITION pos = this->mCameras.GetHeadPosition();
	CCamera* pDev = NULL;
	while (pos) {
		pDev = (CCamera*)this->mCameras.GetNext(pos);
		if (pDev->mId == id) {
			return pDev;
		}
	}

	//return NULL;
	//for (int i = 0; i < CAMERA_MAX_NUM; i++) {
	//	if (mCameras[i].mId == id) {
	//		return &mCameras[i];
	//	}
	//}

	return nullptr;
}




CCamera* CCameraManager::FindCameraByIP(char * ip)
{
	POSITION pos = this->mCameras.GetHeadPosition();
	CCamera* pDev = NULL;
	while (pos) {
		pDev = (CCamera*)this->mCameras.GetNext(pos);
		if (strcpy_s(pDev->mIp, ip) == 0) {
			return pDev;
		}
	}

	return nullptr;
}



/**@brief ͨ��mac��ַ��ȡ���ݿ��ж�Ӧ��id.
*
* @param [in] mac ���е�MAC��ַ
* @return     id  �ҵ���id.
* @note       ���û���ҵ�id���ҵ���id������Χ������0,
*/
int CCameraManager::getIdFromDB(const char* mac)
{
	//CString sqlStmt;
	//sqlStmt.Format(_T("select id from login_device where mac == %c%s%c;"), '\'', mac, '\'');
	//TRACE("sql statement:%S\n", sqlStmt);
	int id = 0;
	char sqlStmt[128];
	sprintf_s(sqlStmt, "select id from login_device where mac == '%s';", mac);
	TRACE("sql statement:%s\n", sqlStmt);

	SQLiteStatement* stmt = sqlite.Statement(sqlStmt);

	if (stmt) {
		if (stmt->NextRow()) {
			id = stmt->ValueInt(0);
			if (id > 0 && id <= CAMERA_MAX_NUM) {
				this->mConsumptionOfCameraId[id - 1] = 1;
				TRACE("id of %s is:%d\n", mac, id);
				return id;
			}
			else {
				TRACE("%s id out of range\n", mac);
				return 0;
			}
		}
		else {
			TRACE("%s has no id\n", mac);
		}
	}
	else {
		TRACE("err\n");
	}

	return 0;
}



/**@brief ��ĳ�豸��id�������ݿ�
*
* @param [int] mac �豸��MAC��ַ
* @return ret  ����ɹ�����true,��֮����false.
*/
BOOL CCameraManager::putIdIntoDB(const int id, const char* mac)
{
	BOOL ret = false;
	char sqlStmt[128];
	sprintf_s(sqlStmt, "insert into login_device(id, mac) values(%d,'%s');", id, mac);
	if (sqlite.DirectStatement(sqlStmt)) {
		ret = true;
	}
	else {
		ret = false;
		TRACE("sql %s error:%S\n", sqlStmt, sqlite.LastError());
	}
	return ret;
}



BOOL CCameraManager::updateIdInDB(const int id, const char* mac)
{
	BOOL ret = false;
	char sqlStmt[128];
	sprintf_s(sqlStmt, "UPDATE login_device SET id = %d WHERE mac == '%s';", id, mac);
	if (sqlite.DirectStatement(sqlStmt)) {
		ret = true;
	}
	else {
		ret = false;
		TRACE("sql stmt :%s error\n", sqlStmt);
	}

	return ret;
}


void CCameraManager::loadDeviceHistoryFrmoDB() 
{
	char sqlStmt[128];
	int id = 0;
	sprintf_s(sqlStmt, "SELECT id FROM login_device;");

	SQLiteStatement* stmt = sqlite.Statement(sqlStmt);
	while (stmt->NextRow()) {
		id = stmt->ValueInt(0);
		if (id > 0) {
			this->mHasAppearedInHistory[id-1] = true;
		}
	}
}