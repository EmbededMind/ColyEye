#pragma once


class Util
{
public:
	Util();
	~Util();

	static void IPTransform(unsigned char* src_form, char* dst_form);
	static void ShowMemoryInfo(void);
	static void CleanMemory(void);
	static double GetMemorySize();
};

