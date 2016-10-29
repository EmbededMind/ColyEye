
// stdafx.cpp : 只包括标准包含文件的源文件
// ColyEye.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

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