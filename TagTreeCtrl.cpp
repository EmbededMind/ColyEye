// TagTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "TagTreeCtrl.h"
#include "DayRecordInfo.h"
#include "ColyEyeDlg.h"

// CTagTreeCtrl

IMPLEMENT_DYNAMIC(CTagTreeCtrl, CTreeCtrl)

CTagTreeCtrl::CTagTreeCtrl()
{

}

CTagTreeCtrl::~CTagTreeCtrl()
{

}


/**@brief 重新填充 tree
 *
 * @param[in] dataSource 子节点的数据
 * @param[in] refTime    “今天”的参考时间
 */
void CTagTreeCtrl::Refresh(CPtrList& dataSource, CTime&  refTime)
{
	CTime curLabelTime;
	HTREEITEM hRoot  = 0;
	HTREEITEM hItem  = TVI_FIRST;

	DeleteAllItems();

	CRecordFileInfo* pInfo;

	if (dataSource.GetCount() == 0) {
		return;
	}
	else {

	}

	CString label;
	POSITION pos = dataSource.GetTailPosition();
	while (pos) {
		pInfo = (CRecordFileInfo*)dataSource.GetPrev(pos);
	    //新加入节点与之前的节点属于不同的天，需要新增一天
		if (pInfo->mBeginTime.GetDay() != curLabelTime.GetDay()) {
			if (pInfo->mBeginTime.GetDay() == refTime.GetDay()) {
				label = _T("今天");
			}
			else if (pInfo->mBeginTime.GetDay() == (refTime - CTimeSpan(1, 0, 0, 0)).GetDay()) {
				label = _T("昨天");
			}
			else {
				label = pInfo->mBeginTime.Format("%Y-%m-%d");
			}

			curLabelTime = pInfo->mBeginTime;
			hRoot = InsertItem(label, 0, hRoot);
			hItem = TVI_FIRST;

			label = pInfo->mBeginTime.Format("%Y-%m-%d_%H:%M:%S") + _T("--") + pInfo->mEndTime.Format("%H:%M:%S");
			hItem = InsertItem(label, hRoot, hItem);
			SetItemData(hItem, (DWORD_PTR)pInfo);
		}
		//新加入节点与之前的节点属于同一天
		else {
			label = label = pInfo->mBeginTime.Format("%Y-%m-%d_%H:%M:%S") + _T("--") + pInfo->mEndTime.Format("%H:%M:%S");
			hItem = InsertItem(label, hRoot, hItem);
			SetItemData(hItem, (DWORD_PTR)pInfo);
		}
	}
}




void CTagTreeCtrl::AddFileUnderItem(HTREEITEM hRoot, CRecordFileInfo* pInfo)
{		
	CString label  = pInfo->mBeginTime.Format("%Y-%m-%d_%H:%M:%S") + _T("--") + pInfo->mEndTime.Format("%H:%M:%S");
	HTREEITEM hItem = InsertItem(label, hRoot, TVI_FIRST);
	SetItemData(hItem, (DWORD_PTR)pInfo);
}




/**@brief 加入新记录
 *
 * *param[in] pInfo 要加入的新纪录
 */
void CTagTreeCtrl::AddFile(CRecordFileInfo* pInfo)
{
	HTREEITEM hRoot = 0;
	hRoot = GetRootItem();
	if (hRoot) {

		if (ItemHasChildren(hRoot)) {

			HTREEITEM hItem = GetChildItem(hRoot);
			CRecordFileInfo* pPrevInfo = (CRecordFileInfo*)GetItemData(hItem);

			if (pInfo->mBeginTime.GetDay() == pPrevInfo->mBeginTime.GetDay()) {

				AddFileUnderItem( hRoot, pInfo);
			}
			else {
				hRoot = InsertItem(_T(""), 0, TVI_FIRST);
				AddFileUnderItem( hRoot, pInfo);
				UpdateRecentLabel();
			}
		}
		else {
			TRACE("something error\n");
		}
	}
	else {
		hRoot = InsertItem(_T(""), 0, TVI_FIRST);
		AddFileUnderItem(hRoot, pInfo);
		UpdateRecentLabel();
	}
}



void CTagTreeCtrl::UpdateRecentLabel()
{
	HTREEITEM hRoot = GetRootItem();

	CString label;

	CTime time = CTime::GetCurrentTime();

	for (int i = 0; i < 3; i++) {
		if (hRoot) {
			if (GetDayLabelByItem( hRoot, time, label)) {
				SetItemText(hRoot, label);
			}
			hRoot = GetNextSiblingItem(hRoot);
		}
		else {
			break;
		}

	}
}

BOOL CTagTreeCtrl::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		HTREEITEM hItem = this->GetSelectedItem();
		switch (pMsg->wParam)
		{		
		case VK_RETURN:				
			if ((hItem != NULL) && this->ItemHasChildren(hItem))
			{
				this->Expand(hItem, TVE_TOGGLE);
			}
			else
			{
				CRecordFileInfo *pRecordInfo = (CRecordFileInfo *)this->GetItemData(hItem);
				::SendMessage(((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->mVideoCtr, USER_MSG_PLAY, ((CColyEyeDlg*)AfxGetApp()->m_pMainWnd)->mMenu.mCurrCursor, (LPARAM)pRecordInfo);
			}
			return true;
		case 'U':
			if (GetKeyState(VK_CONTROL) && !(pMsg->lParam & 0x20000000))
			{
				::SendMessage(this->GetParent()->GetSafeHwnd(), USER_MSG_COPY_RECORD, NULL, (LPARAM)this);
			}
			return true;
		case VK_UP:
			hItem = this->GetPrevSiblingItem(hItem);
			if (hItem)
				this->SelectItem(hItem);
			return true;
		case VK_DOWN:
			hItem = this->GetNextSiblingItem(hItem);
			if(hItem)
				this->SelectItem(hItem);
			return true;
		case VK_LEFT:
			hItem = this->GetParentItem(hItem);
			if(hItem)
				this->SelectItem(hItem);
			return true;
		case VK_RIGHT:
			if ((hItem != NULL) && this->ItemHasChildren(hItem) && (TVIS_EXPANDED & this->GetItemState(hItem, TVIS_EXPANDED)))
			{
				hItem = this->GetChildItem(hItem);
				this->SelectItem(hItem);
			}
			return true;
		}
	}

	return CTreeCtrl::PreTranslateMessage(pMsg);
}



BOOL CTagTreeCtrl::GetDayLabelByItem(HTREEITEM hRoot, CTime& nowTime, CString& label)
{
	if (ItemHasChildren(hRoot)) {
		HTREEITEM hItem;

		hItem = GetChildItem(hRoot);
		CRecordFileInfo* pInfo = (CRecordFileInfo*)GetItemData(hItem);
		// 今天
		if (pInfo->mBeginTime.GetDay() == nowTime.GetDay()) {
			label = _T("今天");
		}
		// 昨天
		else if (pInfo->mBeginTime.GetDay() == (nowTime - CTimeSpan(1, 0, 0, 0)).GetDay()) {
			label = _T("昨天");
		}
		else {
			label = pInfo->mBeginTime.Format("%Y-%m-%d");
		}

		return TRUE;
	}

	return FALSE;
}



BOOL CTagTreeCtrl::DelFile(DWORD_PTR data)
{
	HTREEITEM hRoot = GetRootItem();
	HTREEITEM hItem;

	while (hRoot) {
		if (ItemHasChildren(hRoot)) {
			hItem = GetChildItem(hRoot);
			while (hItem) {
				// 找到要删除的节点
				if (GetItemData(hItem) == data) {

				    DeleteItem(hItem);
					// 如果当天只有一条记录，将这一天的label也删掉
					if (!ItemHasChildren(hRoot)) {

						DeleteItem(hRoot);
					}
					return TRUE;
				}
				else {
					hItem =GetNextSiblingItem(hItem);
				}
			}
		}

		hRoot = GetNextSiblingItem(hRoot);
	}
	return FALSE;
}

