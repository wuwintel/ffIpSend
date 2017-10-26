
// ffIPSend.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CffIPSendApp: 
// 有关此类的实现，请参阅 ffIPSend.cpp
//

//#define APP_CONFIGFILE _T("E:\\IPGateway\\bin\\Win32\\Debug\\send_cfg.ini")

#define APP_CONFIGFILE _T(".\\send_cfg.ini")

class CffIPSendApp : public CWinApp
{
public:
	CffIPSendApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CffIPSendApp theApp;