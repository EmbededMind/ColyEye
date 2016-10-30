// AutoWatchLogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColyEye.h"
#include "AutoWatchLogDlg.h"
#include "afxdialogex.h"
#include <fstream>


// CAutoWatchLogDlg 对话框

IMPLEMENT_DYNAMIC(CAutoWatchLogDlg, CDialogEx)

CAutoWatchLogDlg::CAutoWatchLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTO_WATCH_LOG, pParent)
{

}

CAutoWatchLogDlg::~CAutoWatchLogDlg()
{
}

void CAutoWatchLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mLogText);
}


BEGIN_MESSAGE_MAP(CAutoWatchLogDlg, CDialogEx)
	ON_WM_SIZE()
	ON_MESSAGE(USER_MSG_BRING, &CAutoWatchLogDlg::OnUserMsgBring)
END_MESSAGE_MAP()


void CAutoWatchLogDlg::Layout()
{
	CRect rClient;
	GetClientRect(rClient);

	mLogText.MoveWindow(rClient.left, rClient.top, rClient.Width(), rClient.Height(), TRUE);
}


void CAutoWatchLogDlg::ShowLog()
{
	CString text;
	CTime  t;

	char sqlStmt[128];
	sprintf_s(sqlStmt, "SELECT * FROM switch_log;");
	SQLiteStatement* stmt = sqlite.Statement(sqlStmt);

	mLogText.SetWindowTextW(_T(""));

	while (stmt->NextRow()) {
		t = stmt->ValueInt(0);
		text = t.Format("%Y-%m-%d %H:%M:%S");

		text += _T("    执行的操作：");

		text += stmt->ValueInt(1)?_T("开启"):_T("关闭");

		mLogText.SetSel(-1);
		mLogText.ReplaceSel(text + _T("\r\n"));
		
	}





	
	/*ifstream log("E:\\Record\\Log\\log_switch.txt");
	if ( ! log.is_open()) {
		MessageBox(_T("Log open failed"));
		return;
	}
	

	string s;


	while (!log.eof())
	{
		getline(log, s);
		s += "\r\n";

		text += CString(s.c_str());
	}*/
	
	//mLogText.SetWindowTextW(text);

	//log.close();
}

// CAutoWatchLogDlg 消息处理程序


BOOL CAutoWatchLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	ShowLog();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CAutoWatchLogDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (IsWindow(mLogText)) {
		Layout();
	}
}


afx_msg LRESULT CAutoWatchLogDlg::OnUserMsgBring(WPARAM wParam, LPARAM lParam)
{
	ShowLog();
	return 0;
}
