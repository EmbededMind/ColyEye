#pragma once

#define RECORD_TYPE_NORMAL        0x10
#define RECORD_TYPE_ALARM         0x20

#define RECORD_INFO_STATUS_NONE   0x00
#define RECORD_INFO_STATUS_USING  0x01
#define RECORD_INFO_STATUS_LOCKED 0x02

#define RECORD_NORMAL_TIME        5
#define RECORD_ALARM_TIME         10
#define RECORD_NORMAL_SPACE       100
#define RECORD_ALARM_SPACE        50 

class CRecordFileInfo
{
public:
	CRecordFileInfo();
	CRecordFileInfo(CTime& time);
	~CRecordFileInfo();

public:
	CTime mBeginTime;
	CTime mEndTime;
	CTimeSpan mTotalTime;
	ULONGLONG mTotalSize;
	int mOwner;
	UINT8 mStatus;
	UINT8 mIsLocked;
	UINT8 mBeingUsed;

public:
	void recordBeginInfo(CTime& time);
	void recordEndInfo(CTime& time, ULONGLONG total_size);
	void dump(char * buf, size_t size);
};

