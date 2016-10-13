#include "stdafx.h"
#include "JuggleSchedule.h"


JuggleScheduler::JuggleScheduler()
{
}


JuggleScheduler::~JuggleScheduler()
{
}


void JuggleScheduler::InsertSchedule(JugSchedule* pSch)
{
	std::list<JugSchedule*>::iterator iter;

	iter = pSchedules.begin();
	if (pSch->time <= (*iter)->time) {
		pSchedules.push_front(pSch);
		return;
	}

	for (; iter != pSchedules.end(); iter++) {
		if (pSch->time >= (*iter)->time) {
			pSchedules.insert(iter, pSch);
			return; 
		}
	}
}


void JuggleScheduler::AddZoneSchedule(JugSchedule& jugSch)
{
	//mSchedules.push_back(jugSch);
}


/**@brief 添加一个时间段定时事件
 * 
 * @param[in] hwnd   事件发生时所通知的窗口
 * @param[in] oMsg   时间段开始所发送的消息
 * @param[in] oTime  时间段开始的绝对时间
 * @param[in] yMsg   时间段结束所发送的时间
 * @param[in] yTime  时间段结束的绝对时间
 * 
 * @note 如果结束时间不晚于开始时间，那么结束时间的天分量将变为开始时间的下一天，其他分量不变。
 */
void JuggleScheduler::AddZoneSchedule(HWND hwnd, UINT oMsg, CTime& oTime, UINT yMsg, CTime& yTime)
{
	JugSchedule* poSch = new JugSchedule();
	JugSchedule* pySch = new JugSchedule();
	CTime yyTime;
	
	poSch->hwnd = hwnd;
	poSch->message = oMsg;
	poSch->time = oTime;
	poSch->status = JugSchStatus_Virgin;
	poSch->type = JugSchType_OldBrother;


	pySch->hwnd = hwnd;
	pySch->message = oMsg;

	if (yTime <= oTime) {
		pySch->time = yTime + CTimeSpan(oTime.GetDay()+1, 0, 0, 0);
	}
	else {
		pySch->time = yTime;
	}

	pySch->time = oTime;
	pySch->status = JugSchStatus_Virgin;
	pySch->type = JugSchType_YoungBrother;

	poSch->pBrother = pySch;
	pySch->pBrother = poSch;

	InsertSchedule(pySch);
	InsertSchedule(poSch);
}


/**@brief  添加一个时间点定时事件
 *
 * @param[in] hwnd 定时事件发生时所通知的窗口
 * @param[in] msg  定时事件发生时所发送的消息
 * @param[in] time 定时的时间点(绝对时间，不是距离现在的时间间隔)
 */
void JuggleScheduler::AddSchedule(HWND hwnd, UINT msg, CTime& time)
{
	JugSchedule* pSch = new JugSchedule;
	pSch->hwnd = hwnd;
	pSch->message = msg;
	pSch->time = time;
	pSch->type = JugSchType_Default;
	pSch->status = JugSchStatus_Default;
	pSch->pBrother = nullptr;

	InsertSchedule(pSch);
}



void JuggleScheduler::Step(CTime& ret_time, std::list<JugSchedule*>& result_list)
{

}