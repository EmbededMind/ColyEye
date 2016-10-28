#include "stdafx.h"
#include "MySerialPort.h"


MySerialPort::MySerialPort()
{

}


MySerialPort::~MySerialPort()
{
}


BOOL MySerialPort::InitPort()
{
	m_hComm = CreateFile(_T("COM3"),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING, 
		FILE_FLAG_OVERLAPPED,
		0);

	if (m_hComm == INVALID_HANDLE_VALUE) {
		TRACE("Init port failed!\m");
		return FALSE;
	}
}

