
// stdafx.cpp : 只包括标准包含文件的源文件
// ColyEye.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

SQLiteWrapper sqlite;
ColyEyeHost   host;


void WriteLog(LPCTSTR logName, CString msg)
{
	try
	{
		//设置文件的打开参数
		CStdioFile outFile(logName, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		CString msLine;
		CTime tt = CTime::GetCurrentTime();

		//作为Log文件，经常要给每条Log打时间戳，时间格式可自由定义，
		//这里的格式如：2010-June-10 Thursday, 15:58:12
		msLine = tt.Format("[%Y-%B-%d %A, %H:%M:%S] ") + msg;
		msLine += "\n";

		//在文件末尾插入新纪录
		outFile.SeekToEnd();
		outFile.WriteString(msLine);
		outFile.Close();
	}
	catch (CFileException *fx)
	{
		fx->Delete();
	}
}
