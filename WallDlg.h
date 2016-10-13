#pragma once
#include "Camera.h"
#include "SurfaceHolderDlg.h"
#include "RecordFileInfo.h"
#include <map>
#include "atltime.h"

// CWallDlg 对话框

typedef std::map<long, CCamera*> Device_Map;



class CWallDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWallDlg)

public:
	CWallDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWallDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WALL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	afx_msg LRESULT OnUserMsgLogin(WPARAM wParam, LPARAM lParam);

private:
	CPtrList mHolderes;

	UINT8 mRows;
	UINT8 mCols;

	Device_Map mDevReconnectMap;

	void interruptRecord(CCamera* pCamera);
	void interruptAlarmRecord(CCamera* pCamera);



public:
	CSurfaceHolderDlg* investCamera(CCamera* pCamera);
	void   spitCamera(CCamera* pCamera);
	BOOL   designLayout();
	void   executeLayout();
	void   updateLayout();


	void ReConnect(LONG lLoginID, char* pchDVRIP, LONG nDVRPort);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnUserMsgBring(WPARAM wParam, LPARAM lParam);
public:
	CTime mSystemTime;
};
