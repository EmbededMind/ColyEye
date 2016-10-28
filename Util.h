#pragma once
#include "CameraManager.h"

class Util
{
public:
	Util();
	~Util();

	static void IPTransform(unsigned char* src_form, char* dst_form);
	static void ShowMemoryInfo(void);
	static void CleanMemory(void);
	static double GetMemorySize();
	static void LoadOrder(uint8_t *pOrder,uint8_t Header,uint8_t ScrType, uint8_t destType, uint8_t Cmd, uint8_t Prm1, uint8_t Parm2, CCamera *pCamear);
	static uint8_t CharToUint(char ch);
};

