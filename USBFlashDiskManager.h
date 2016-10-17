#pragma once
typedef struct USBFlashDiskStatus
{
	CString m_updataPath;
	FLOAT m_spaceLeft; //u盘剩余空间Mb
	FLOAT m_spacetotal;
}USBFlashDiskStatus;

class CUSBFlashDiskManager
{
public:
	CUSBFlashDiskManager();
	~CUSBFlashDiskManager();
protected:
	UINT m_beInsert;   //U盘是否插入
	UINT m_isThreadAlive; //线程有没有启动
	USBFlashDiskStatus* m_pStatus;
	CWnd *m_owner;
	CString m_diskflag;
	CString m_copyFromPath;

	HANDLE m_endEvent;
	HANDLE m_updataEvent;
	HANDLE m_copyEvent;
	HANDLE m_scanEvent;

	HANDLE m_hEventArray[4];
	CWinThread* m_Thread;
	static UINT USBThread(LPVOID pParam);
	static BOOL FindUpdataFile(CUSBFlashDiskManager* bt, CString tp);
public:
	BOOL InitUSB(CWnd *pUSBOwner, CString diskname);
	BOOL StartMonitoring();
	BOOL StopMonitoring();
	BOOL EndThread();

	BOOL GetStatus(USBFlashDiskStatus *pStaus);
	BOOL Updata();
	BOOL CopyRecord(CString path);
	
};

