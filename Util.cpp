#include "stdafx.h"
#include "Util.h"


#include <Psapi.h>

Util::Util()
{
}


Util::~Util()
{
}

void Util::IPTransform(unsigned char* src_form, char* dst_form)
{
	int tmp = 0;
	for (int j = 0; j < 4; j++) {
		tmp += sprintf_s(&dst_form[tmp], 4, "%d", src_form[j]);
		if (j < 3) {
			dst_form[tmp] = '.';
			tmp++;
		}
	}
}



void Util::ShowMemoryInfo()
{
	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	TRACE("内存使用:%0.2f MB\n", (double)pmc.PagefileUsage / 1024 / 1024);
}



double Util::GetMemorySize()
{
	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	TRACE("内存使用:%0.2f MB\n", (double)pmc.PagefileUsage / 1024 / 1024);
	return (double)pmc.PagefileUsage / 1024 / 1024;
}

void Util::LoadOrder(uint8_t * pOrder, uint8_t Header, uint8_t ScrType, uint8_t destType, uint8_t Cmd, uint8_t Prm1, uint8_t Parm2, CCamera * pCamear)
{
	memset(pOrder, 0, 17 * sizeof(uint8_t));
	pOrder[0] = Header;
	pOrder[1] = ScrType;
	pOrder[2] = destType;
	pOrder[3] = Cmd;
	pOrder[4] = Prm1;
	pOrder[5] = Parm2;

	uint8_t tmp = 0;
	if (pCamear->mCommonNetConfig.sMac[0] >= '0' && pCamear->mCommonNetConfig.sMac[0] <= '9')
	{
		tmp += pCamear->mCommonNetConfig.sMac[0] - '0';
	}
	else  if (pCamear->mCommonNetConfig.sMac[0] >= 'a' && pCamear->mCommonNetConfig.sMac[0] <= 'z')
	{
		tmp += pCamear->mCommonNetConfig.sMac[0] - 'a' + 10;
	}
	tmp *= 16;
	if (pCamear->mCommonNetConfig.sMac[1] >= '0' && pCamear->mCommonNetConfig.sMac[1] <= '9')
	{
		tmp += pCamear->mCommonNetConfig.sMac[1] - '0';
	}
	else  if (pCamear->mCommonNetConfig.sMac[1] >= 'a' && pCamear->mCommonNetConfig.sMac[1] <= 'z')
	{
		tmp += pCamear->mCommonNetConfig.sMac[1] - 'a' + 10;
	}
	pOrder[6] = tmp;

	tmp = 0;
	if (pCamear->mCommonNetConfig.sMac[3] >= '0' && pCamear->mCommonNetConfig.sMac[3] <= '9')
	{
		tmp += pCamear->mCommonNetConfig.sMac[3] - '0';
	}
	else  if (pCamear->mCommonNetConfig.sMac[3] >= 'a' && pCamear->mCommonNetConfig.sMac[3] <= 'z')
	{
		tmp += pCamear->mCommonNetConfig.sMac[3] - 'a' + 10;
	}
	tmp *= 16;
	if (pCamear->mCommonNetConfig.sMac[4] >= '0' && pCamear->mCommonNetConfig.sMac[4] <= '9')
	{
		tmp += pCamear->mCommonNetConfig.sMac[4] - '0';
	}
	else  if (pCamear->mCommonNetConfig.sMac[4] >= 'a' && pCamear->mCommonNetConfig.sMac[4] <= 'z')
	{
		tmp += pCamear->mCommonNetConfig.sMac[4] - 'a' + 10;
	}
	pOrder[7] = tmp;

	tmp = 0;
	if (pCamear->mCommonNetConfig.sMac[6] >= '0' && pCamear->mCommonNetConfig.sMac[6] <= '9')
	{
		tmp += pCamear->mCommonNetConfig.sMac[6] - '0';
	}
	else  if (pCamear->mCommonNetConfig.sMac[6] >= 'a' && pCamear->mCommonNetConfig.sMac[6] <= 'z')
	{
		tmp += pCamear->mCommonNetConfig.sMac[6] - 'a' + 10;
	}
	tmp *= 16;
	if (pCamear->mCommonNetConfig.sMac[7] >= '0' && pCamear->mCommonNetConfig.sMac[7] <= '9')
	{
		tmp += pCamear->mCommonNetConfig.sMac[7] - '0';
	}
	else  if (pCamear->mCommonNetConfig.sMac[7] >= 'a' && pCamear->mCommonNetConfig.sMac[7] <= 'z')
	{
		tmp += pCamear->mCommonNetConfig.sMac[7] - 'a' + 10;
	}
	pOrder[8] = tmp;

	tmp = 0;
	if (pCamear->mCommonNetConfig.sMac[9] >= '0' && pCamear->mCommonNetConfig.sMac[9] <= '9')
	{
		tmp += pCamear->mCommonNetConfig.sMac[9] - '0';
	}
	else  if (pCamear->mCommonNetConfig.sMac[9] >= 'a' && pCamear->mCommonNetConfig.sMac[9] <= 'z')
	{
		tmp += pCamear->mCommonNetConfig.sMac[9] - 'a' + 10;
	}
	tmp *= 16;
	if (pCamear->mCommonNetConfig.sMac[10] >= '0' && pCamear->mCommonNetConfig.sMac[10] <= '9')
	{
		tmp += pCamear->mCommonNetConfig.sMac[10] - '0';
	}
	else  if (pCamear->mCommonNetConfig.sMac[10] >= 'a' && pCamear->mCommonNetConfig.sMac[10] <= 'z')
	{
		tmp += pCamear->mCommonNetConfig.sMac[10] - 'a' + 10;
	}
	pOrder[9] = tmp;

	tmp = 0;
	if (pCamear->mCommonNetConfig.sMac[12] >= '0' && pCamear->mCommonNetConfig.sMac[12] <= '9')
	{
		tmp += pCamear->mCommonNetConfig.sMac[12] - '0';
	}
	else  if (pCamear->mCommonNetConfig.sMac[12] >= 'a' && pCamear->mCommonNetConfig.sMac[12] <= 'z')
	{
		tmp += pCamear->mCommonNetConfig.sMac[12] - 'a' + 10;
	}
	tmp *= 16;
	if (pCamear->mCommonNetConfig.sMac[13] >= '0' && pCamear->mCommonNetConfig.sMac[13] <= '9')
	{
		tmp += pCamear->mCommonNetConfig.sMac[13] - '0';
	}
	else  if (pCamear->mCommonNetConfig.sMac[13] >= 'a' && pCamear->mCommonNetConfig.sMac[13] <= 'z')
	{
		tmp += pCamear->mCommonNetConfig.sMac[13] - 'a' + 10;
	}
	pOrder[10] = tmp;

	tmp = 0;
	if (pCamear->mCommonNetConfig.sMac[15] >= '0' && pCamear->mCommonNetConfig.sMac[15] <= '9')
	{
		tmp += pCamear->mCommonNetConfig.sMac[15] - '0';
	}
	else  if (pCamear->mCommonNetConfig.sMac[15] >= 'a' && pCamear->mCommonNetConfig.sMac[15] <= 'z')
	{
		tmp += pCamear->mCommonNetConfig.sMac[15] - 'a' + 10;
	}
	tmp *= 16;
	if (pCamear->mCommonNetConfig.sMac[16] >= '0' && pCamear->mCommonNetConfig.sMac[16] <= '9')
	{
		tmp += pCamear->mCommonNetConfig.sMac[16] - '0';
	}
	else  if (pCamear->mCommonNetConfig.sMac[16] >= 'a' && pCamear->mCommonNetConfig.sMac[16] <= 'z')
	{
		tmp += pCamear->mCommonNetConfig.sMac[16] - 'a' + 10;
	}
	pOrder[11] = tmp;

	pOrder[12] = 0x0;
	pOrder[13] = 0x0;
	pOrder[14] = 0x0;
	pOrder[15] = 0x0;
	pOrder[16] = 0x0;
	pOrder[17] = 0xfd;
}


void Util::CleanMemory()
{
	EmptyWorkingSet(GetCurrentProcess());
}
