#pragma once


// CHostInfoDlg �Ի���

class CHostInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHostInfoDlg)

public:
	CHostInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHostInfoDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOSTINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
