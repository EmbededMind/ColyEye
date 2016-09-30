#pragma once
#include "stdafx.h"
#include "Observer.h"
//#include "Subject.h"
#include "RecordFileInfo.h"
#include "RecordFileInfoManager.h"

class DBShadow:public Observer,public Subject
{
private:
	DBShadow() {};
	DBShadow(const DBShadow&);
	DBShadow & operator = (const DBShadow&);
	~DBShadow() {};

public:
	static DBShadow* GetInstance() 
	{
		static DBShadow instance;
		return &instance;
	}

	virtual void Update(string state,DWORD_PTR pSubject);

private:
	CRecordFileInfo* m_paRecordFileInfo[CAMERA_MAX_NUM];
	CRecordFileInfo* m_paAlarmRecordFileInfo[CAMERA_MAX_NUM];
	
public:
	CWnd* pRecordFileWnd;
	CWnd* pAlarmRecordFileWnd;	
};

