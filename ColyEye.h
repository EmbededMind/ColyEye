
// ColyEye.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CColyEyeApp: 
// �йش����ʵ�֣������ ColyEye.cpp
//

class CColyEyeApp : public CWinApp
{
public:
	CColyEyeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

public:
	HANDLE hLoginThread;
	HANDLE hSerialThread;
	unsigned int pidOfLoginThread;
	unsigned int pidOfSerialThread;
};

extern CColyEyeApp theApp;