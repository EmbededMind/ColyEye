#include "stdafx.h"
#include "DBOperator.h"

/**@brief  查询所有的报警记录条目数
 * 
 * @return  查询结果
 */
int CDBOperator::queryAlarmRecordCount()
{
	char sqlStmt[128];
	sprintf_s(sqlStmt, "SELECT count(*) FROM alarm_record;");
	SQLiteStatement* stmt = sqlite.Statement(sqlStmt);
	while (stmt->NextRow()) {
		TRACE("find %d alarm reocrd\n", stmt->ValueInt(0));
		return stmt->ValueInt(0);
	}
	return 0;
}


/**@brief 查询某一设备所对应的报警记录条目数
 *
 * @return 查询结果
 */
int CDBOperator::queryAlarmRecordCount(int owner)
{
	char sqlStmt[128];
	sprintf_s(sqlStmt, "SELECT count(*) FROM alarm_record where owner == %d;", owner);
	SQLiteStatement* stmt = sqlite.Statement(sqlStmt);
	while (stmt->NextRow()) {
		TRACE("find %d alarm reocrd\n", stmt->ValueInt(0));
		return stmt->ValueInt(0);
	}
	return 0;
}

/**@brief 查询某一个设备在某一时段的报警记录条目数
 *
 * @return 查询结果
 */
int CDBOperator::queryAlarmRecordCount(int owner, CTime& beginTime, CTime& endTime)
{
	char sqlStmt[128];
	sprintf_s(sqlStmt, "SELECT count(*) FROM alarm_record WHERE owner == %d AND begin_sec >= %I64d AND end_sec <= %I64d;", owner, beginTime.GetTime(), endTime.GetTime());
	SQLiteStatement* stmt = sqlite.Statement(sqlStmt);
	while (stmt->NextRow()) {
		TRACE("find %d alarm reocrd\n", stmt->ValueInt(0));
		return stmt->ValueInt(0);
	}
	return 0;
}


/**@brief  查询所有新增报警记录条目数
*
* @return  查询结果
*/
int CDBOperator::queryNewAlarmRecord()
{
	char sqlStmt[128];
	sprintf_s(sqlStmt, "SELECT count(*) FROM alarm_record WHERE status == %d;",ALARM_RECORD_STATUS_NEW);
	SQLiteStatement* stmt = sqlite.Statement(sqlStmt);
	while (stmt->NextRow()) {
		TRACE("find %d new alarm reocrd\n", stmt->ValueInt(0));
		return stmt->ValueInt(0);
	}
	return 0;
}


/**@brief 查询某一设备新增的报警记录条目数
*
* @return 查询结果
*/
int CDBOperator::queryNewAlarmRecord(int owner)
{
	char sqlStmt[128];
	sprintf_s(sqlStmt, "SELECT count(*) FROM alarm_record where owner == %d AND status == %d AND owner == %d;", owner,ALARM_RECORD_STATUS_NEW, owner);
	SQLiteStatement* stmt = sqlite.Statement(sqlStmt);
	while (stmt->NextRow()) {
		TRACE("find %d  new alarm reocrd\n", stmt->ValueInt(0));
		return stmt->ValueInt(0);
	}
	return 0;
}


/**@brief 查询某一个设备在某一时段新增的报警记录条目数
*
* @return 查询结果
*/
int CDBOperator::queryNewAlarmRecord(int owner, CTime& beginTime, CTime& endTime)
{
	char sqlStmt[128];
	sprintf_s(sqlStmt, "SELECT count(*) FROM alarm_record WHERE owner == %d AND begin_sec >= %I64d AND end_sec <= %I64d AND status == %d;",
		owner, beginTime.GetTime(), endTime.GetTime(),ALARM_RECORD_STATUS_NEW);
	SQLiteStatement* stmt = sqlite.Statement(sqlStmt);
	while (stmt->NextRow()) {
		TRACE("find %d alarm reocrd\n", stmt->ValueInt(0));
		return stmt->ValueInt(0);
	}
	return 0;
}


int CDBOperator::queryNewAlarmRecord(int owner, __time64_t begin_sec, __time64_t end_sec)
{
	char sqlStmt[128];
	sprintf_s(sqlStmt, "SELECT count(*) FROM alarm_record WHERE owner == %d AND begin_sec >= %I64d AND begin_sec <= %I64d AND status == %d;",
		owner, begin_sec, end_sec, ALARM_RECORD_STATUS_NEW);
	SQLiteStatement* stmt = sqlite.Statement(sqlStmt);
	while (stmt->NextRow()) {
		TRACE("find %d alarm reocrd\n", stmt->ValueInt(0));
		return stmt->ValueInt(0);
	}
	return 0;
}