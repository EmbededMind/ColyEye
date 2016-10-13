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


/**@brief  ���һ��ʱ��㶨ʱ�¼�
 *
 * @param[in] hwnd ��ʱ�¼�����ʱ��֪ͨ�Ĵ���
 * @param[in] msg  ��ʱ�¼�����ʱ�����͵���Ϣ
 * @param[in] time ��ʱ��ʱ���(����ʱ�䣬���Ǿ������ڵ�ʱ����)
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
	// ʱ�����ӹ�ʱ��ε�ͷ��
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
	// ʱ�����ӹ�ʱ��ε�β��
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

	//����ϴε�ʱ��� 1 ���ڲο�ʱ�䣬˵���ο�ʱ������������˵���ο�ʱ�䷢�����䡣
	//�������ͨ��˵��ϵͳʱ�䱻���ģ���Ҫ��λ mPrevIter
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