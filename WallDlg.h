#pragma once
#include "Camera.h"
#include "SurfaceHolderDlg.h"
#include "RecordFileInfo.h"

// CWallDlg 对话框

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

public:
	HANDLE investCamera(CCamera* pCamera);
	BOOL   designLayout();
	void   executeLayout();
	void   updateLayout();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnUserMsgBring(WPARAM wParam, LPARAM lParam);
};
