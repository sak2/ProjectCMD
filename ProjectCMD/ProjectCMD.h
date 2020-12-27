
// ProjectCMD.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CProjectCMDApp:
// See ProjectCMD.cpp for the implementation of this class
//

class CProjectCMDApp : public CWinApp
{
public:
	CProjectCMDApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CProjectCMDApp theApp;
