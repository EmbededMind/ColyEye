#pragma once


// CSurfaceDlg �Ի���

class CSurfaceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSurfaceDlg)

public:
	CSurfaceDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSurfaceDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SURFACE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
