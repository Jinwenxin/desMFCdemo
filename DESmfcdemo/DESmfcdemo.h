
// DESmfcdemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDESmfcdemoApp:
// �йش����ʵ�֣������ DESmfcdemo.cpp
//

class CDESmfcdemoApp : public CWinApp
{
public:
	CDESmfcdemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDESmfcdemoApp theApp;