
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// ColyEye.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"



SQLiteWrapper sqlite;
ColyEyeHost   host;



//void InitLog()
//{
//	SharedAppenderPtr pFileAppender(new FileAppender(_T("e:\\log\\coly_eye.log")));
//
//	auto_ptr<Layout>  pPatternLayout(new PatternLayout(_T("%d{%m/%d/%y %H:%M:%S}    - %m [%l]%n")));
//	pFileAppender->setLayout(pPatternLayout);
//	Logger::getInstance(_T("MyLogger")).addAppender(pFileAppender);
//}