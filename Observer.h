#pragma once

#include <list>
#include "Subject.h"

using namespace std;

class Subject;

class Observer
{
public:
	~Observer();
	virtual void Update(string,DWORD_PTR) = 0;
	//virtual void Update(string state, LPARAM pData)=0;

protected:
	Observer();
};

