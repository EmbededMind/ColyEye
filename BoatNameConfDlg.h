#pragma once


// CBoatNameConfDlg �Ի���

class CBoatNameConfDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBoatNameConfDlg)

public:
	CBoatNameConfDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBoatNameConfDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOATNAME_CONF };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
