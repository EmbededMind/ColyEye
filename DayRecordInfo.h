#pragma once
#include <vector>
#include "RecordFileInfo.h"


class CDayRecordInfo
{
public:
	CDayRecordInfo();
	~CDayRecordInfo();

public :
	CTime mTime;
	CString mDayText;
	CPtrList mRecordInfo;

public:
	void appendRecordInfo(CRecordFileInfo* pNewRecordInfo        );
};

