// Upgrade tool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUpgradetoolApp:
// �йش����ʵ�֣������ Upgrade tool.cpp
//

class CUpgradetoolApp : public CWinApp
{
public:
	CUpgradetoolApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUpgradetoolApp theApp;