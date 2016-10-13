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


/**@brief ���һ��ʱ��ζ�ʱ�¼�
 * 
 * @param[in] hwnd   �¼�����ʱ��֪ͨ�Ĵ���
 * @param[in] oMsg   ʱ��ο�ʼ�����͵���Ϣ
 * @param[in] oTime  ʱ��ο�ʼ�ľ���ʱ��
 * @param[in] yMsg   ʱ��ν��������͵�ʱ��
 * @param[in] yTime  ʱ��ν����ľ���ʱ��
 * 
 * @note �������ʱ�䲻���ڿ�ʼʱ�䣬��ô����ʱ������������Ϊ��ʼʱ�����һ�죬�����������䡣
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


/**@brief  ���һ��ʱ��㶨ʱ�¼�
 *
 * @param[in] hwnd ��ʱ�¼�����ʱ��֪ͨ�Ĵ���
 * @param[in] msg  ��ʱ�¼�����ʱ�����͵���Ϣ
 * @param[in] time ��ʱ��ʱ���(����ʱ�䣬���Ǿ������ڵ�ʱ����)
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