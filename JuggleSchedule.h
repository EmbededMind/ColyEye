#pragma once

#include <list>

typedef enum {
	JugSchType_Default = 0,
	JugSchType_OldBrother,
	JugSchType_YoungBrother
}JugSchType;


typedef enum {
	JugSchStatus_Default = 0,
	JugSchStatus_Virgin,
	JugSchStatus_Developed
}JugSchStatus;


typedef struct _JugSchedule JugSchedule;
struct _JugSchedule{
	HWND  hwnd;
	UINT message;
	JugSchStatus status;
	JugSchType type;
	CTime time;
	JugSchedule* pBrother;
};

class JuggleScheduler
{
public:
	JuggleScheduler();
	~JuggleScheduler();

	void AddZoneSchedule(JugSchedule& pSch);
	
	void AddZoneSchedule(HWND hwnd, UINT oMsg,CTime& oTime, UINT yMsg, CTime& yTime);

	void AddSchedule(HWND hwnd, UINT msg, CTime& time);

	void InsertSchedule(JugSchedule* pSch);

	void Step(CTime& ref_time, std::list<JugSchedule*>& result_list);

private:
	std::list<JugSchedule*> pSchedules;
};

