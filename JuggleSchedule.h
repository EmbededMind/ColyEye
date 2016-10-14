#pragma once

#include <list>



typedef enum {
	JugSchStatus_Default = 0,
	JugSchStatus_Virgin,
	JugSchStatus_Developed
}JugSchStatus;




typedef struct {
	HWND hwnd;
	UINT message;
	WPARAM wParam;
	LPARAM lParam;
}JugSchMsg;


typedef struct {
	JugSchMsg jusSchMsg;
	DWORD     beginTime;
	DWORD     endTime;
	JugSchStatus status;
}JugSchedule;



class JuggleScheduler
{
public:
	JuggleScheduler();
	~JuggleScheduler();


	void AddZoneSchedule(JugSchMsg* pSchMsg, DWORD begin_time, DWORD end_time);

	void Step(CTime& ref_time, std::list<JugSchMsg*>& result_list);

private:
	std::list<JugSchedule*> pSchedules;	
};

