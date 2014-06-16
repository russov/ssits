
// generator.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CgeneratorApp:
// See generator.cpp for the implementation of this class
//

class CgeneratorApp : public CWinApp
{
public:
	CgeneratorApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CgeneratorApp theApp;