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



void Util::CleanMemory()
{
	EmptyWorkingSet(GetCurrentProcess());
}
