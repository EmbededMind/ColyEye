#pragma once
#include <string>
#include <list>
#include "Observer.h"

using namespace std;

class Observer;

class Subject
{
public:
	~Subject();

	virtual void Notify();
	virtual void Attach(Observer*);
	virtual void Detach(Observer*);
	virtual string GetState();
	virtual void SetState(string state);

protected:
	Subject();

protected:
	string m_state;
	list<Observer*> m_list;
};

