#include "stdafx.h"
#include "JuggleSchedule.h"


JuggleScheduler::JuggleScheduler()
{
}


JuggleScheduler::~JuggleScheduler()
{
}




void JuggleScheduler::AddZoneSchedule(JugSchMsg* pSchMsg, DWORD begin_time, DWORD end_time)
{
	JugSchedule* pSch = new JugSchedule();

	pSch->beginTime = begin_time;
	pSch->endTime = end_time;
	pSch->status = JugSchStatus_Virgin;
	memcpy(&pSch->jusSchMsg, pSchMsg, sizeof(JugSchMsg));
	pSchedules.push_back(pSch);
}





void JuggleScheduler::Step(CTime& ref_time, std::list<JugSchMsg*>& result_list)
{
	DWORD refTime  = ref_time.GetHour() * 3600 + ref_time.GetMinute() * 60 + ref_time.GetSecond();

	std::list<JugSchedule*>::iterator iter;
	for (iter = pSchedules.begin(); iter != pSchedules.end(); iter++) {
		if ((*iter)->status == JugSchStatus_Virgin) {
			if (refTime >= (*iter)->beginTime) {
				if (refTime >= (*iter)->endTime) {
					// Ingnore
				}
				else {
					result_list.push_back( &(*iter)->jusSchMsg);
					(*iter)->status = JugSchStatus_Developed;
					TRACE("In zone\n");
				}
			}
		}
		else {
			if (refTime < (*iter)->beginTime) {
				result_list.push_back( &(*iter)->jusSchMsg);
				(*iter)->status = JugSchStatus_Virgin;
				TRACE("Escape zone\n");
			}
			else if(refTime >= (*iter)->endTime) {
				result_list.push_back( &(*iter)->jusSchMsg);
				(*iter)->status = JugSchStatus_Virgin;
				TRACE("Out zone\n");
			}
		}
	}
}