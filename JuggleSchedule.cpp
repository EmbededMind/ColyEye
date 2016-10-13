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
	if (pSch->msg.time <= (*iter)->msg.time) {
		pSchedules.push_front(pSch);
		return;
	}

	for (; iter != pSchedules.end(); iter++) {
		if (pSch->msg.time >= (*iter)->msg.time) {
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
void JuggleScheduler::AddZoneSchedule(MSG* poMsg, MSG* pyMsg)
{
	JugSchedule* poSch = new JugSchedule();
	JugSchedule* pySch = new JugSchedule();
	CTime yyTime;
	
	poSch->msg.hwnd = poMsg->hwnd;
	poSch->msg.message = poMsg->message;
	poSch->msg.time = poMsg->time;
	poSch->status = JugSchStatus_Virgin;
	poSch->type = JugSchType_OldBrother;


	poSch->msg.hwnd = pyMsg->hwnd;
	poSch->msg.message = pyMsg->message;
	poSch->msg.time = pyMsg->time;

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
void JuggleScheduler::AddSchedule(MSG* pMsg)
{
	JugSchedule* pSch = new JugSchedule;
	
	pSch->msg.hwnd    = pMsg->hwnd;
	pSch->msg.message = pMsg->message;
	pSch->msg.time    = pMsg->time;

	pSch->type = JugSchType_Default;
	pSch->status = JugSchStatus_Default;
	pSch->pBrother = nullptr;

	InsertSchedule(pSch);
}


void JuggleScheduler::AddSchedule(HWND hwnd, UINT message, DWORD time)
{
	JugSchedule* pSch = new JugSchedule;

	pSch->msg.hwnd = hwnd;
	pSch->msg.message = message;
	pSch->msg.time = time;

	pSch->type = JugSchType_Default;
	pSch->status = JugSchStatus_Default;
	pSch->pBrother = nullptr;

	InsertSchedule(pSch);
}



void JuggleScheduler::PatrolSchedule(JugSchedule* pSch, std::list<MSG*>& result_list)
{
	// 时间线掠过时间段的头部
	if (pSch->type == JugSchType_OldBrother) {
		if (pSch->status == JugSchStatus_Virgin) {
			pSch->status = JugSchStatus_Developed;
			pSch->pBrother->status = JugSchStatus_Developed;

			TRACE("ScanLine at a head\n");

			result_list.push_back(&pSch->msg);
		}
		else {
			TRACE("System time changed ?\n");
		}
	}
	// 时间线掠过时间段的尾部
	else if (pSch->type == JugSchType_YoungBrother) {
		 if (pSch->status == JugSchStatus_Developed) {
			pSch->status = JugSchStatus_Virgin;
			pSch->pBrother->status = JugSchStatus_Virgin;

			TRACE("ScanLine at a tail\n");

			result_list.push_back(&pSch->msg);
		}
		else {
			TRACE("This is not science\n");
		}
	}
}



void JuggleScheduler::Step(CTime& ref_time, std::list<MSG*>& result_list)
{
	std::list<JugSchedule*>::iterator iter;

	DWORD timeRef = ref_time.GetHour() * 60 + ref_time.GetMinute() * 60 + ref_time.GetSecond();

	//如果上次的时间加 1 等于参考时间，说明参考时间正常，否则说明参考时间发生跳变。
	//这种情况通常说明系统时间被更改，需要复位 mPrevIter
	if (((mPrevRefTime + 1) % 24 * 60 * 60) != timeRef) {
		mPrevRefIter = pSchedules.begin();
	}
	mPrevRefTime = timeRef;

	for (iter = mPrevRefIter; iter != pSchedules.end(); iter++)
	{
		if (timeRef >= (*iter)->msg.time) {
			PatrolSchedule(*iter, result_list);
		}
		else {
			break;
		}
	}
	if (iter != pSchedules.end()) {
		mPrevRefIter = iter;
	}
	else {
		mPrevRefIter = pSchedules.begin();
	}
}