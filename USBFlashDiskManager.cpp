#include "stdafx.h"
#include "USBFlashDiskManager.h"
#include "assert.h"

CUSBFlashDiskManager::CUSBFlashDiskManager()
{
	m_beInsert = NULL;
	m_isThreadAlive = NULL;
	m_endEvent = NULL;
	m_updataEvent = NULL;
	m_copyEvent = NULL;
	m_owner = NULL;
}


CUSBFlashDiskManager::~CUSBFlashDiskManager()
{
	do
	{
		SetEvent(m_endEvent);
	} while (m_isThreadAlive);

	if (m_endEvent != NULL)
		CloseHandle(m_endEvent);
	if (m_copyEvent != NULL)
		CloseHandle(m_copyEvent);
	if (m_updataEvent != NULL)
		CloseHandle(m_updataEvent);
	if (m_scanEvent != NULL)
		CloseHandle(m_scanEvent);
}

BOOL CUSBFlashDiskManager::InitUSB(CWnd * pUSBOwner, CString diskname)
{
	assert(pUSBOwner != NULL);
	if (m_isThreadAlive)
	{
		do
		{
			SetEvent(m_endEvent);
		} while (m_isThreadAlive);
	}
	if (m_endEvent != NULL)
		ResetEvent(m_endEvent);
	else
		m_endEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (m_updataEvent != NULL)
		ResetEvent(m_updataEvent);
	else
		m_updataEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (m_copyEvent != NULL)
		ResetEvent(m_copyEvent);
	else
		m_copyEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (m_scanEvent != NULL)
		ResetEvent(m_scanEvent);
	else
		m_scanEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	m_hEventArray[0] = m_scanEvent;
	m_hEventArray[1] = m_copyEvent;
	m_hEventArray[2] = m_updataEvent;
	m_hEventArray[3] = m_endEvent;

	m_diskflag = diskname;
	m_owner = pUSBOwner;
	
	return TRUE;
}

UINT CUSBFlashDiskManager::USBThread(LPVOID pParam)
{
	CUSBFlashDiskManager *usb = (CUSBFlashDiskManager*)pParam;

	usb->m_isThreadAlive = TRUE;
	
	DWORD Event = 0;
	for (;;)
	{
		Event = WaitForMultipleObjects(4, usb->m_hEventArray, FALSE, INFINITE);
		switch (Event)
		{
		case 0:
			ULARGE_INTEGER   uiFreeBytesAvailableToCaller;
			ULARGE_INTEGER   uiTotalNumberOfBytes;
			ULARGE_INTEGER   uiTotalNumberOfFreeBytes;
			TRACE("m_scanEvent\n");
			if (GetDiskFreeSpaceExW(usb->m_diskflag,
				&uiFreeBytesAvailableToCaller,
				&uiTotalNumberOfBytes,
				&uiTotalNumberOfFreeBytes))
			{
				usb->m_pStatus->m_spaceLeft = (FLOAT)((LONGLONG)(uiTotalNumberOfFreeBytes.QuadPart) / 1024.0f / 1024.0f);
				usb->m_pStatus->m_spacetotal = (FLOAT)((LONGLONG)(uiTotalNumberOfBytes.QuadPart) / 1024.0f / 1024.0f);
				TRACE(_T("--%f-- %f"), usb->m_pStatus->m_spaceLeft, usb->m_pStatus->m_spacetotal);
			}
			
			if (!FindUpdataFile(usb, usb->m_diskflag))
			{
				usb->m_pStatus->m_updataPath = _T("nothing");
			}
			ResetEvent(usb->m_scanEvent);
			break;
		case 1:
		{
			usb->m_copyFromPath += _T('\0');
			usb->m_diskflag += _T("\\");
			TRACE("m_copyEvent\n");
			SHFILEOPSTRUCT FileOp = { 0 };
			FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR;
			FileOp.pFrom = usb->m_copyFromPath;
			FileOp.pTo = usb->m_diskflag;
			FileOp.wFunc = FO_COPY;
			FileOp.hwnd = usb->m_owner->GetSafeHwnd();
			SHFileOperation(&FileOp);
			ResetEvent(usb->m_copyEvent);
		}
			break;
		case 2:
			TRACE("m_updataEvent\n");
			ResetEvent(usb->m_updataEvent);
			break;
		case 3:
			TRACE("m_endEvent\n");
			usb->m_isThreadAlive = FALSE;
			ResetEvent(usb->m_endEvent);
			AfxEndThread(100);
			break;
		}
	}
	return 0;
}

BOOL CUSBFlashDiskManager::StartMonitoring()
{
	if (!(m_Thread = AfxBeginThread(USBThread, this)))
		return FALSE;
	TRACE("Thread Start\n");
	return 0;
}

BOOL CUSBFlashDiskManager::StopMonitoring()
{
	m_Thread->SuspendThread();
	m_isThreadAlive = FALSE;
	return 0;
}

BOOL CUSBFlashDiskManager::EndThread()
{
	SetEvent(m_endEvent);
	return 0;
}

BOOL CUSBFlashDiskManager::GetStatus(USBFlashDiskStatus *pStaus)
{
	m_pStatus = pStaus;
	SetEvent(m_scanEvent);
	return 0;
}

BOOL CUSBFlashDiskManager::Updata()
{
	SetEvent(m_updataEvent);
	return 0;
}

BOOL CUSBFlashDiskManager::CopyRecord(CString path)
{
	m_copyFromPath = path;
	SetEvent(m_copyEvent);
	return 0;
}

BOOL CUSBFlashDiskManager::FindUpdataFile(CUSBFlashDiskManager * pcusb, CString tp)
{
	CFileFind fileFinder;
	CString filePath = tp + _T("//*.*");

	BOOL bFinished = fileFinder.FindFile(filePath);
	while (bFinished)  //每次循环对应一个类别目录
	{
		bFinished = fileFinder.FindNextFile();
		if (fileFinder.IsDirectory() && !fileFinder.IsDots())  
		{
			CString fileName = fileFinder.GetFileName();
			if (fileName == _T("haha"))
			{
				pcusb->m_pStatus->m_updataPath = fileFinder.GetFilePath();
				TRACE(_T("%s\n"), pcusb->m_pStatus->m_updataPath);
				return TRUE;
			}
			else
			{
				FindUpdataFile(pcusb, fileFinder.GetFilePath());
			}			
		}
		else  
		{
			CString fileName = fileFinder.GetFileName();
			if (fileName == _T("hehe.txt"))
			{
				pcusb->m_pStatus->m_updataPath = fileFinder.GetFilePath();
				TRACE(_T("%s\n"), pcusb->m_pStatus->m_updataPath);
				return TRUE;
			}
		}
	}
	fileFinder.Close();
	return 0;
}

