
// UpperComputer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUpperComputerApp:
// �йش����ʵ�֣������ UpperComputer.cpp
//

class CUpperComputerApp : public CWinApp
{
public:
	CUpperComputerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUpperComputerApp theApp;