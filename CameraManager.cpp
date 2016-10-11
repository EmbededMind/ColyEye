#include "stdafx.h"
#include "CameraManager.h"

#include "stdafx.h"
#include "CameraManager.h"


/**@brief 析构对象释放资源
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



/**@brief 添加一个摄像头设备
*
* @param [in] pNewCamera  新添加的设备的指针.
*/
BOOL CCameraManager::addCamera(CCamera* pNewCamera)
{
	if (mCameras.GetCount() < CAMERA_MAX_NUM) {
		mCameras.AddTail(pNewCamera);
		return true;
	}
	return false;
}



/**@brief 删除一个摄像头设备
*
* @param [in] pOldCamera 要删除的设备的指针.
*/
void CCameraManager::deleteCamera(CCamera* pOldCamera)
{
	ASSERT(pOldCamera != NULL);
	POSITION pos = mCameras.Find(pOldCamera);
	if (pos != NULL) {
		mCameras.RemoveAt(pos);
		delete(pOldCamera); /**  触发析构函数，销毁对象 */
	}
}


/**@brief 为摄像机分配一个id.
*
* @param [in] pCamera 要为之分配id的摄像机.
*/
BOOL CCameraManager::distributeId(CCamera* pCamera)
{
	int id = 0;
	if (pCamera->mCommonNetConfig.sMac) {
		// 如果历史记录中记录的有此设备的信息，将记录的id分配之
		id = getIdFromDB(pCamera->mCommonNetConfig.sMac);
		if (id) {
			pCamera->mId = id;
			return true;
		}
		else {
			//如果历史记录里没有此设备的信息，先找历史设备没有占用的id
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

			//如果历史设备没有未占用的id，再找当前已登录设备没有占用的id
			//如果有的话，覆盖对应的历史设备的信息并将此id分配之
			//for (int i = 0; i < CAMERA_MAX_NUM; i++) {
			//	/// 新的设备，分配新的id并存入数据库。
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



/**@brief 通过mac地址读取数据库中对应的id.
*
* @param [in] mac 已有的MAC地址
* @return     id  找到的id.
* @note       如果没有找到id或找到的id超出范围，返回0,
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



/**@brief 将某设备的id存入数据库
*
* @param [int] mac 设备的MAC地址
* @return ret  存入成功返回true,反之返回false.
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