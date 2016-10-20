#include "stdafx.h"
#include "ColyEyeHost.h"


ColyEyeHost::ColyEyeHost()
{
	mConfuration.watch_time_begining = 0;
	mConfuration.watch_time_span = 24 * 3600;
}


ColyEyeHost::~ColyEyeHost()
{
}


BOOL ColyEyeHost::Load()
{
	char sqlStmt[128];
	sprintf_s(sqlStmt, "SELECT * FROM host_conf;");
	SQLiteStatement * stmt = sqlite.Statement(sqlStmt);
	if (stmt->NextRow()) {
		mConfuration.boat_name = stmt->ValueString(0);
		mConfuration.watch_time_begining = stmt->ValueInt(1);
		mConfuration.watch_time_span = stmt->ValueInt(2);
		return TRUE;
	}
	else {
		return FALSE;
	}	
}



/**@brief �����Զ�����ʱ���
 *
 * @param[in] begining ������ʼʱ�䣨Ϊ���� 00:00:00 ��������
 * @param[in] span     ��������ʱ���뿪ʼʱ���ʱ����λΪ�룩
 */
BOOL ColyEyeHost::SetWatchTime(DWORD begining, DWORD span)
{
	if (mConfuration.watch_time_begining != begining || mConfuration.watch_time_span != span) {
		mConfuration.watch_time_begining = begining;
		mConfuration.watch_time_span = span;

		char sqlStmt[128];
		sprintf_s(sqlStmt, "UPDATE host_conf SET watch_begining = %d, watch_span = %d;", begining, span);
		if (sqlite.DirectStatement(sqlStmt)) {
			return TRUE;
		}
		else {
			TRACE("sql stmt error:%s\n", sqlStmt);
			return FALSE;
		}
	}
	else {
		return TRUE;
	}
}


/**@brief ���ô������Ʋ��������ݿ�
 *
 * @param[in] name Ҫ���õ�����
 */
BOOL ColyEyeHost::SetBoatName(std::string name)
{
	if (mConfuration.boat_name != name) {
		mConfuration.boat_name = name;
		char sqlStmt[128];
		sprintf_s(sqlStmt, "UPDATE host_conf SET name = '%s';", name.c_str());
		if (sqlite.DirectStatement(sqlStmt)) {
			return TRUE;
		}
		else {
			TRACE("sql stmt error:%s\n", sqlStmt);
			return FALSE;
		}
	}
	return TRUE;
}