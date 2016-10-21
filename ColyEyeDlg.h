
// ColyEyeDlg.h : 头文件
//
#pragma once
#include "WallDlg.h"
#include "MenuDlg.h"
#include "SerialPort.h"
#include "dbt.h"
#include "USBFlashDiskManager.h"
// CColyEyeDlg 对话框
class CColyEyeDlg : public CDialogEx
{
// 构造
public:
	CColyEyeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLYEYE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public :
	CWallDlg mWall;
	CMenuDlg mMenu;
	CVideoCtrDlg mVideoCtr;
	USBFlashDiskStatus m_USBFlashDiskStatus;
protected:
	afx_msg LRESULT OnUserMsgScanDev(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CUSBFlashDiskManager m_usbManager;
protected:
	afx_msg LRESULT OnUserMsgNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserMsgLogin(WPARAM wParam, LPARAM lParam);
protected:
	CSerialPort m_SerialPortKbd;
	CSerialPort m_SerialPortCom;
	BOOL m_bSerialPortKbdOpened;
	BOOL m_bSerialPortComOpened;
	afx_msg LONG OnCommChar(WPARAM ch, LPARAM port);
	afx_msg LONG OnCommData(WPARAM pData, LPARAM port);
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD_PTR dwData);	
};
