#pragma once


// CCameraStoreOffConfirmDlg �Ի���

class CCameraStoreOffConfirmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraStoreOffConfirmDlg)

public:
	CCameraStoreOffConfirmDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCameraStoreOffConfirmDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAMERA_STORE_OFF_CONFIRM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
