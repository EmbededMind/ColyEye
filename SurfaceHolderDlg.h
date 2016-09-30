#pragma once
#include "Camera.h"
#include "SurfaceDlg.h"

// CSurfaceHolderDlg �Ի���

class CSurfaceHolderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSurfaceHolderDlg)

public:
	CSurfaceHolderDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSurfaceHolderDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SURFACE_HOLDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public :
	CCamera* pCamera;
	CSurfaceDlg   mSurface;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
