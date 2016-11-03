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
	pOrder[6] = CharToUint(pCamear->mCommonNetConfig.sMac[0]) * 16 + CharToUint(pCamear->mCommonNetConfig.sMac[1]);
	pOrder[7] = CharToUint(pCamear->mCommonNetConfig.sMac[3]) * 16 + CharToUint(pCamear->mCommonNetConfig.sMac[4]);
	pOrder[8] = CharToUint(pCamear->mCommonNetConfig.sMac[6]) * 16 + CharToUint(pCamear->mCommonNetConfig.sMac[7]);
	pOrder[9] = CharToUint(pCamear->mCommonNetConfig.sMac[9]) * 16 + CharToUint(pCamear->mCommonNetConfig.sMac[10]);
	pOrder[10] = CharToUint(pCamear->mCommonNetConfig.sMac[12]) * 16 + CharToUint(pCamear->mCommonNetConfig.sMac[13]);
	pOrder[11] = CharToUint(pCamear->mCommonNetConfig.sMac[15]) * 16 + CharToUint(pCamear->mCommonNetConfig.sMac[16]);
	pOrder[12] = 0x0;
	pOrder[13] = 0x0;
	pOrder[14] = 0x0;
	pOrder[15] = 0x0;
	pOrder[16] = 0xfd;
}

uint8_t Util::CharToUint(char ch)
{
	uint8_t tmp = 0;
	if (ch >= '0' && ch <= '9')
	{
		tmp += ch - '0';
	}
	else  if (ch >= 'a' && ch <= 'z')
	{
		tmp += ch - 'a' + 10;
	}
	return tmp;
}


void Util::CleanMemory()
{
	EmptyWorkingSet(GetCurrentProcess());
}
