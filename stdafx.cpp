
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// ColyEye.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

SQLiteWrapper sqlite;
ColyEyeHost   host;


void WriteLog(LPCTSTR logName, CString msg)
{
	try
	{
		//�����ļ��Ĵ򿪲���
		CStdioFile outFile(logName, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		CString msLine;
		CTime tt = CTime::GetCurrentTime();

		//��ΪLog�ļ�������Ҫ��ÿ��Log��ʱ�����ʱ���ʽ�����ɶ��壬
		//����ĸ�ʽ�磺2010-June-10 Thursday, 15:58:12
		msLine = tt.Format("[%Y-%B-%d %A, %H:%M:%S] ") + msg;
		msLine += "\n";

		//���ļ�ĩβ�����¼�¼
		outFile.SeekToEnd();
		outFile.WriteString(msLine);
		outFile.Close();
	}
	catch (CFileException *fx)
	{
		fx->Delete();
	}
}
