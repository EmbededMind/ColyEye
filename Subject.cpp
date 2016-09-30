#include "stdafx.h"
#include "Subject.h"


Subject::Subject()
{
}


Subject::~Subject()
{
}



void Subject::Attach(Observer* pObserver)
{
	this->m_list.push_back(pObserver);
	TRACE("Attached an observer\n");
}



void Subject::Detach(Observer* pObserver)
{
	list<Observer*>::iterator iter;
	iter = find(m_list.begin(), m_list.end(), pObserver);
	if (iter != m_list.end()) {
		m_list.erase(iter);
	}
	TRACE("Detach an observer\n");
}



void Subject::Notify()
{
	list<Observer*>::iterator iter = this->m_list.begin();
	for (; iter != m_list.end(); iter++) {
		(*iter)->Update(m_state,(DWORD_PTR)this);
	}
}



string Subject::GetState()
{
	return this->m_state;
}



void Subject::SetState(string state)
{
	this->m_state = state;
}