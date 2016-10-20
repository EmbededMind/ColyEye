#include "stdafx.h"
#include "RecordFileInfo.h"

CRecordFileInfo::CRecordFileInfo()
{
	
}


CRecordFileInfo::CRecordFileInfo(CTime& time)
{
	this->mBeginTime = time;
}

CRecordFileInfo::~CRecordFileInfo()
{
}



void CRecordFileInfo::recordBeginInfo(CTime& time)
{
	this->mBeginTime = time;
}


void CRecordFileInfo::recordEndInfo(CTime& endTime, ULONGLONG total_size)
{
	this->mEndTime = endTime;
	this->mTotalSize = total_size;

}


void CRecordFileInfo::dump(char * buf, size_t size) 
{
	sprintf_s(buf, size, "%12I64d %12I64d   %10lld", mBeginTime.GetTime(), mEndTime.GetTime(),
		                             mTotalSize);
}