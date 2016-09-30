#pragma once
#include "RecordFileInfo.h"
#include "VideoCtrDlg.h"

// CTagTreeCtrl

class CTagTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CTagTreeCtrl)

public:
	CTagTreeCtrl();
	virtual ~CTagTreeCtrl();

public:
	void Refresh(CPtrList& dataSource, CTime& refTime);
	void AddFile(CRecordFileInfo* pInfo);
	void AddFileUnderItem(HTREEITEM hRoot, CRecordFileInfo* pInfo);
	BOOL DelFile(DWORD_PTR data);

	BOOL GetDayLabelByItem(HTREEITEM hRoot, CTime& nowTime, CString& label);
	void UpdateRecentLabel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	DECLARE_MESSAGE_MAP()

};


