
// MFCApplication.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCApplicationApp: 
// �йش����ʵ�֣������ MFCApplication.cpp
//

class CMFCApplicationApp : public CWinApp
{
public:
	CMFCApplicationApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplicationApp theApp;