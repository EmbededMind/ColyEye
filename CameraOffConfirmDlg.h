#pragma once


// CCameraOffConfirmDlg �Ի���

class CCameraOffConfirmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraOffConfirmDlg)

public:
	CCameraOffConfirmDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCameraOffConfirmDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OFF_CONFIRM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
