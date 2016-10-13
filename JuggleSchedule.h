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
	MSG msg;
	JugSchStatus status;
	JugSchType type;
	JugSchedule* pBrother;
};

class JuggleScheduler
{
public:
	JuggleScheduler();
	~JuggleScheduler();

	void AddZoneSchedule(JugSchedule& pSch);
	
	void AddZoneSchedule(MSG* poMsg, MSG* pyMsg);


	void AddSchedule(MSG* pMsg);
	void AddSchedule(HWND hwnd, UINT message, DWORD time);

	void InsertSchedule(JugSchedule* pSch);

	void Step(CTime& ref_time, std::list<MSG*>& result_list);

private:
	std::list<JugSchedule*> pSchedules;	
	DWORD mPrevRefTime;
	std::list<JugSchedule*>::iterator mPrevRefIter;

	void PatrolSchedule(JugSchedule* pSch, std::list<MSG*>& result_list);
};

