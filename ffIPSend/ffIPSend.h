
// ffIPSend.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CffIPSendApp: 
// �йش����ʵ�֣������ ffIPSend.cpp
//

//#define APP_CONFIGFILE _T("E:\\IPGateway\\bin\\Win32\\Debug\\send_cfg.ini")

#define APP_CONFIGFILE _T(".\\send_cfg.ini")

class CffIPSendApp : public CWinApp
{
public:
	CffIPSendApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CffIPSendApp theApp;