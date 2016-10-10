#pragma once
#include "stdafx.h"
#include "Mmsystem.h"
class CMCI
{
public:
	CMCI();
	~CMCI();

public:
	DWORD m_RecordDeviceID;
	DWORD m_PlayDeviceID;
	CString m_Filepath;
	DWORD m_RecordTime;
	DWORD m_PlayTime;

public:
	int Record();
	int Save();
	int Play();
	int StopPlay();
	int GetRecordTime();
	int GetPlayTime();
};

