#include "stdafx.h"
#include "TalkManager.h"
#include "ColyEyeDlg.h"
#include "Util.h"
#include "Camera.h"

CTalkManager::CTalkManager()
{
}


CTalkManager::~CTalkManager()
{
}

void CTalkManager::Start()
{
	if (CCameraManager::getInstance()->mTalkpDev)
	{
		if (CCameraManager::getInstance()->mTalkpDev->mLoginId != mpDev->mLoginId)
		{
			CCameraManager::getInstance()->mTalkpDev->Talk->Stop();
			mpDev->mTalkHandle = H264_DVR_StartLocalVoiceCom(mpDev->mLoginId);
			CCameraManager::getInstance()->mTalkpDev = mpDev;
		}
		uint8_t Order[17];
		Util::LoadOrder(Order, 0x24, 0x01, 0x02, 0x02, 0x01, NULL, mpDev);
		((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->m_SerialPortCom.WriteToPort(Order, 17);
	}
	else
	{
		mpDev->mTalkHandle = H264_DVR_StartLocalVoiceCom(mpDev->mLoginId);
		CCameraManager::getInstance()->mTalkpDev = mpDev;
		uint8_t Order[17];
		Util::LoadOrder(Order, 0x24, 0x01, 0x02, 0x02, 0x01, NULL, mpDev);
		((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->m_SerialPortCom.WriteToPort(Order, 17);
	}
	return;
}

void CTalkManager::Over()
{
	if (mpDev->mTalkHandle)
	{
		uint8_t Order[17];
		Util::LoadOrder(Order, 0x24, 0x01, 0x02, 0x02, 0x02, NULL, mpDev);
		((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->m_SerialPortCom.WriteToPort(Order, 17);
	}
	else
	{
		printf("handke == 0\n");
	}
	return;
}

void CTalkManager::Stop()
{
	if (mpDev->mTalkHandle)
	{
		H264_DVR_StopVoiceCom(mpDev->mTalkHandle);
		CCameraManager::getInstance()->mTalkpDev = NULL;
		mpDev->mTalkHandle = 0;
		uint8_t Order[17];
		Util::LoadOrder(Order, 0x24, 0x01, 0x02, 0x02, 0x03, NULL, mpDev);
		((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->m_SerialPortCom.WriteToPort(Order, 17);
	}
	return;
}
