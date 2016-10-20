#include "stdafx.h"
#include "ColyEyeHost.h"


ColyEyeHost::ColyEyeHost()
{
	mConfuration.watch_time_begining = 0;
	mConfuration.watch_time_span = 24 * 3600;

	char sqlStmt[128];
	sprintf_s(sqlStmt, "SELECT * FROM host_conf;");
	//SQLiteWrapper* stmt = sqlite.Statement(sqlStmt);
}


ColyEyeHost::~ColyEyeHost()
{
}
