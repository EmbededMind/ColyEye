#pragma once


// CSurfaceDlg 对话框

class CSurfaceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSurfaceDlg)

public:
	CSurfaceDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSurfaceDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SURFACE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
