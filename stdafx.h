
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����


#include "lib\sdk_xm\H264Play.h"
#include "lib\sdk_xm\netsdk.h"
#include "lib\sqlite3\sqlitewrapper.h"

#pragma comment(lib, "lib\\sdk_xm\\H264Play.lib")
#pragma comment(lib, "lib\\sdk_xm\\NetSdk.lib")
#pragma comment(lib, "lib\\sqlite3\\sqlite3.lib")

#define DB_COL_BEGIN_SEC              0
#define DB_COL_END_SEC                1
#define DB_COL_OWNER                  2
#define DB_COL_TOTAL_TIME             3
#define DB_COL_TOTAL_SIZE             4
#define DB_COL_STATUS                 5

#define DBLOAD_FILTE_SMALL_PIECE      0x00000001
#define DBLOAD_FILTE_SHORT_TIME       0x00000010

#define DBLOAD_FILTE_SHORT_TIME_LIMIT   10000    /// С��10s�ļ�¼����Ϊ�Ƕ�ʱ��¼
#define DBLOAD_FILTE_SMALL_PIECE_LIMIT  1024     /// С��1K Byte�ļ�¼����Ϊ����Ƭ��¼

#define CAMERA_MAX_NUM  6       // ֧�ֵ�����豸��Ŀ
#define STORE_MAX_DAYS  7       // ��Ƶ���洢����

#define ALARM_TIMER_EVENT_ID   (CAMERA_MAX_NUM+1)

#define ALARM_LIVE_TIME   6

#define RECONNET_TIMER_EVENT_ID     (CAMERA_MAX_NUM + 2)

#define USER_MSG_LOGIN    (WM_USER + 100)
#define USER_MSG_SCAN_DEV (WM_USER + 101)

#define USER_MSG_BRING    (WM_USER + 110)
#define USER_MSG_PLAY     (WM_USER + 111)


#define USER_MSG_NOTIFY               (WM_USER + 120)
#define USER_MSG_NOTIFY_FOCUS         (WM_USER + 121)
#define USER_MSG_GIVE_FOCUS           (WM_USER + 122)

#define USER_MSG_ADD_FILE             (WM_USER + 140)
#define USER_MSG_DEL_FILE             (WM_USER + 141)

#define USER_MSG_CONNECT           (WM_USER + 150)


#define NORMAL_RECORD_PATH            "e:\\Record\\normal\\"
#define ALARM_RECORD_PATH             "e:\\Record\\alarm\\"


extern 	SQLiteWrapper sqlite;


#define LOG_PATH                     "e:\\log.txt"
void WriteLog(LPCTSTR logName, CString msg);

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


