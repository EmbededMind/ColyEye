
// ColyEyeDlg.h : ͷ�ļ�
//

#pragma once
#include "WallDlg.h"
#include "MenuDlg.h"

// CColyEyeDlg �Ի���
class CColyEyeDlg : public CDialogEx
{
// ����
public:
	CColyEyeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLYEYE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public :
	CWallDlg mWall;
	CMenuDlg mMenu;
	CVideoCtrDlg mVideoCtr;
protected:
	afx_msg LRESULT OnUserMsgScanDev(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	afx_msg LRESULT OnUserMsgNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserMsgLogin(WPARAM wParam, LPARAM lParam);
};
