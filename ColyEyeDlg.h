
// ColyEyeDlg.h : ͷ�ļ�
//
#pragma once
#include "WallDlg.h"
#include "MenuDlg.h"
#include "SerialPort.h"
#include "dbt.h"
#include "USBFlashDiskManager.h"
#include <mmdeviceapi.h> 
#include <endpointvolume.h>
#include <audioclient.h>
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
	USBFlashDiskStatus m_USBFlashDiskStatus;
	CUSBFlashDiskManager m_usbManager;
protected:
	afx_msg LRESULT OnUserMsgScanDev(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CSerialPort m_SerialPortKbd;
	CSerialPort m_SerialPortCom;
protected:
	afx_msg LRESULT OnUserMsgNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserMsgLogin(WPARAM wParam, LPARAM lParam);
protected:
	BOOL m_bSerialPortKbdOpened;
	BOOL m_bSerialPortComOpened;
	afx_msg LONG OnCommData(WPARAM pData, LPARAM port);
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD_PTR dwData);

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	BOOL SetVolumeLevel(int level);
	BOOL SetBrightLevel(int level);

};
