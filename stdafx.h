
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类


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

#define DBLOAD_FILTE_SHORT_TIME_LIMIT   10000    /// 小于10s的记录被认为是短时记录
#define DBLOAD_FILTE_SMALL_PIECE_LIMIT  1024     /// 小于1K Byte的记录被认为是碎片记录

#define CAMERA_MAX_NUM  6       // 支持的最大设备数目
#define STORE_MAX_DAYS  7       // 视频最大存储天数

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
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


