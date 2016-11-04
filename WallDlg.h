#pragma once
#include "Camera.h"
#include "SurfaceHolderDlg.h"
#include "RecordFileInfo.h"
#include <map>
#include "atltime.h"
#include "JuggleSchedule.h"
#include <list>

#include "Surface.h"


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

private:
	CPtrList mHolderes;

	std::list<CSurface*> m_pSurfaces;

	UINT8 mRows;
	UINT8 mCols;

	UINT  mCurrSelectedHolder;

	Device_Map mDevReconnectMap;

	//JuggleScheduler mJugScheduler;

	void interruptRecord(CCamera* pCamera);
	void interruptAlarmRecord(CCamera* pCamera);

	void JumpToHolder();

	void OnCameraLogin(CCamera* pCamera);
	void OnCameraLogout(CCamera* pCamera);

public:
	DWORD mBeginWatchTime;
	DWORD mEndWatchTime;

	CSurfaceHolderDlg* investCamera(CCamera* pCamera);
	CSurface*      InvestCamera(CCamera* pCamera);

	void   DesignLayout();
	void   ExecuteLayout();
	void   UpdateLayout();

	void   spitCamera(CCamera* pCamera);
	BOOL   designLayout();
	void   executeLayout();
	void   updateLayout();


	void SuspendCamera(CCamera* pCamera);
	void ResumeCamera(CCamera* pCamera);


	void EnableCameraConfiguration(CCamera* pCamera);
	void DisableCameraConfiguration(CCamera* pCamera);


	void ReConnect(LONG lLoginID, char* pchDVRIP, LONG nDVRPort);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	afx_msg LRESULT OnUserMsgLogin(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserMsgReLogin(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserMsgBring(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserMsgDeviceConfig(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void CWallDlg::OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	uint8_t mOrder[18];
public:
	CTime mSystemTime;

protected:

	afx_msg LRESULT OnUserMsgNotifyArrow(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);

};
