#pragma once


// CVersionUpdateDlg �Ի���

class CVersionUpdateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVersionUpdateDlg)

public:
	CVersionUpdateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVersionUpdateDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
