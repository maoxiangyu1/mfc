
// DrugTraceability.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDrugTraceabilityApp:
// �йش����ʵ�֣������ DrugTraceability.cpp
//

class CDrugTraceabilityApp : public CWinApp
{
public:
	CDrugTraceabilityApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDrugTraceabilityApp theApp;