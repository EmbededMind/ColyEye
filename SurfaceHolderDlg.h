#pragma once
#include "Camera.h"
#include "SurfaceDlg.h"
#include "afxcmn.h"

// CSurfaceHolderDlg 对话框

class CSurfaceHolderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSurfaceHolderDlg)

public:
	CSurfaceHolderDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSurfaceHolderDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SURFACE_HOLDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public :
	CCamera* pCamera;
	//CSurfaceDlg   mSurface;
	CWnd          mSurface;
	CButton*      m_pTalkBtn;
	CButton*      m_pSilentBtn;
	BOOL         mIsSelected;

	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNcPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};
