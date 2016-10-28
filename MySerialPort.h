#pragma once

#define WM_COMM_BREAK_DETECTED			WM_USER+1    // A break was detected on input.
#define WM_COMM_CTS_DETECTED			WM_USER+2    // The CTS (clear-to-send) signal changed state. 
#define WM_COMM_DSR_DETECTED			WM_USER+3    // The DSR (data-set-ready) signal changed state. 
#define WM_COMM_ERR_DETECTED			WM_USER+4    // A line-status error occurred. Line-status errors are CE_FRAME, CE_OVERRUN, and CE_RXPARITY. 
#define WM_COMM_RING_DETECTED			WM_USER+5    // A ring indicator was detected. 
#define WM_COMM_RLSD_DETECTED			WM_USER+6    // The RLSD (receive-line-signal-detect) signal changed state. 
#define WM_COMM_RXCHAR					WM_USER+7    // A character was received and placed in the input buffer. 
#define WM_COMM_RXFLAG_DETECTED			WM_USER+8    // The event character was received and placed in the input buffer.  
#define WM_COMM_TXEMPTY_DETECTED		WM_USER+9    // The last character in the output buffer was sent.  
#define WM_COMM_RXDATA                  WM_USER+10

class MySerialPort
{
public:
	MySerialPort();
	~MySerialPort();

	BOOL InitPort();

protected:
	HANDLE m_hComm;
};

