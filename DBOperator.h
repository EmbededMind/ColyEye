#pragma once

#define ALARM_RECORD_STATUS_NEW          0
#define ALARM_RECORD_STATUS_COMMON       1
#define ALARM_RECORD_STATUS_LOCK         2

class CDBOperator
{
private:
	CDBOperator() {};
	CDBOperator(const CDBOperator&) {};
	~CDBOperator() {};

public :
	static CDBOperator* getInstance() {
		static CDBOperator mInstance;
		return &mInstance;
	}

public:
	int queryAlarmRecordCount();
	int queryAlarmRecordCount(int owner);
	int queryAlarmRecordCount(int owner, CTime& beginTime, CTime& endTime);
	int queryNewAlarmRecord();
	int queryNewAlarmRecord(int owner);
	int queryNewAlarmRecord(int owner, CTime& beginTime, CTime& endTiem);
	int queryNewAlarmRecord(int owner, __time64_t begin_sec, __time64_t end_sec);
};

