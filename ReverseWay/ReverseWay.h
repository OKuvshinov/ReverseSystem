
// ReverseWay.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CReverseWayApp:
// Сведения о реализации этого класса: ReverseWay.cpp
//

class CReverseWayApp : public CWinApp
{
public:
	CReverseWayApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CReverseWayApp theApp;
