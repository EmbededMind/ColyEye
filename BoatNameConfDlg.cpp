// BoatNameConfDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColyEye.h"
#include "BoatNameConfDlg.h"
#include "afxdialogex.h"


// CBoatNameConfDlg �Ի���

IMPLEMENT_DYNAMIC(CBoatNameConfDlg, CDialogEx)

CBoatNameConfDlg::CBoatNameConfDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BOATNAME_CONF, pParent)
{

}

CBoatNameConfDlg::~CBoatNameConfDlg()
{
}


void CBoatNameConfDlg::Layout()
{
	CRect rClient;
	GetClientRect(rClient);

	// �������Ʊ༭��λ�ڿͻ���ˮƽ 1/5 �� 4/5 
	//                       ��ֱ 1/10 �� 1/10 + 30
	int name_edit_width = rClient.Width() * 3 / 5;
	int name_edit_x = (rClient.Width() - name_edit_width) / 2 + rClient.left;
	int name_edit_y = rClient.top + rClient.Height() / 10;


	CWnd* pWnd = GetDlgItem(IDC_EDIT1);
	pWnd->MoveWindow(name_edit_x, name_edit_y, name_edit_width, 30, TRUE);

	// '��������' ��̬�ı�λ�ڱ༭��ǰ 80 ��
	pWnd = GetDlgItem(IDC_STATIC);
	pWnd->MoveWindow(name_edit_x - 80, name_edit_y, 80, 30, TRUE);

	// ���水ť��Ϊ�༭���ȵ� 1/10 ����༭����ͬ
	// ��ť��༭���ұ���ӣ����±߶��롣
	pWnd = GetDlgItem(IDC_BUTTON1);
	pWnd->MoveWindow(name_edit_x+name_edit_width, name_edit_y, name_edit_width/10, 30, TRUE);
}



void CBoatNameConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBoatNameConfDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CBoatNameConfDlg ��Ϣ�������


void CBoatNameConfDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CWnd* pWnd = GetDlgItem(IDC_EDIT1);
	if (pWnd && IsWindow(pWnd->m_hWnd)) {
		Layout();
	}
}
