#include "stdafx.h"
#include "Util.h"


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