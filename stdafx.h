
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

//#include "log4cplus\logger.h"
//#include "log4cplus\fileappender.h"
//#include "log4cplus\layout.h"
//#include "log4cplus\loggingmacros.h"


#include "ColyEyeHost.h"

#pragma comment(lib, "lib\\sdk_xm\\H264Play.lib")
#pragma comment(lib, "lib\\sdk_xm\\NetSdk.lib")
#pragma comment(lib, "lib\\sqlite3\\sqlite3.lib")



//#ifdef _DEBUG
//#pragma comment(lib, "log4cplusUD.lib")
//#else
//#pragma comment(lib, "log4cplusU.lib")
//#endif

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

#define ALARM_TIMER_EVENT_ID        (CAMERA_MAX_NUM + 1)
#define RECONNET_TIMER_EVENT_ID     (CAMERA_MAX_NUM + 2)
#define SECOND_TICK_TIMER_EVENT_ID  (CAMERA_MAX_NUM + 3)

#define ALARM_LIVE_TIME   2



#define USER_MSG_LOGIN    (WM_USER + 100)
#define USER_MSG_SCAN_DEV (WM_USER + 101)
#define USER_MSG_RELOGIN  (WM_USER + 102)

#define USER_MSG_BRING    (WM_USER + 110)
#define USER_MSG_PLAY     (WM_USER + 111)


#define USER_MSG_NOTIFY               (WM_USER + 120)
#define USER_MSG_NOTIFY_FOCUS         (WM_USER + 121)
#define USER_MSG_GIVE_FOCUS           (WM_USER + 122)
#define USER_MSG_NOTIFY_BACK          (WM_USER + 123)

#define USER_MSG_ADD_FILE             (WM_USER + 140)
#define USER_MSG_DEL_FILE             (WM_USER + 141)
#define USER_MSG_COPY_RECORD          (WM_USER + 142)

#define USER_MSG_CONNECT              (WM_USER + 150)

#define USER_MSG_DEVICE_CONFIG        (WM_USER + 160)

#define USER_MSG_NOTIFY_ARROW         (WM_USER + 170)


#define RECORD_PATH                   "d:\\Record\\"
#define NORMAL_RECORD_PATH            "d:\\Record\\normal\\"
#define ALARM_RECORD_PATH             "d:\\Record\\alarm\\"
#define SOUND_PATH                    "d:\\Record\\Sound\\"

#define COM_KEYBD                     1
#define COM_CAMERA                    2
//�����Ĵ�����ֵ
#define KB_MENU                       1
#define KB_UP                         2
#define KB_BACK                       3
#define KB_AUTOWATCH                  4
#define KB_LEFT                       5
#define KB_ENTER                      6
#define KB_RIGHT                      7
#define KB_UDISK                      8
#define KB_VOLUP                      9
#define KB_DOWN                       10
#define KB_BRIUP                      11
#define KB_FUNC                       12
#define KB_VOLDOWN                    13
#define KB_TALKQUIET                  14
#define KB_BRIDOWN                    15
#define KB_SWITCH                     16
#define KB_PTTDOWN                    17
#define KB_PTTUP                      18



/********************************
*
*  Layout macro
*
*********************************/
#define SURFACE_SHAPE          9/16 
#define SURFACE_WH_SCALE       16/9
#define SURFACE_LABEL_OFFSET   30

#define SURFACE_PADDING        1/20

#define WALL_MARGIN_SCALE      1/10


#define MENU_ITEM_WIDTH_SHARE     1/5
#define MENU_ITEM_HEIGHT_SHARE    1/10

#define PLAY_CTR_BT_WIDTH         100


//using namespace log4cplus;
using namespace std;

extern 	SQLiteWrapper sqlite;
extern  ColyEyeHost   host;
//extern  Logger  pLogger;





//
//void InitLog();

#define LOG_PATH                     "D:\\log.txt"



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


