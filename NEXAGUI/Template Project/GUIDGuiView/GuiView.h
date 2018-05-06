
// GuiView.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
    #error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"        // main symbols
#include <string>

// CGuiViewApp:
// See GuiViewD.cpp for the implementation of this class
//

class CGuiViewApp : public CWinApp
{
public:
    // Default constructor
    CGuiViewApp();

// Overrides
public:
    // Init instance
    virtual BOOL InitInstance();

//Start TrungLV 20150820
    VOID  LoadInitFile( );
    BOOL  m_bShowCursor;
// End TrungLV 20150820
// Implementation

    DECLARE_MESSAGE_MAP()
};

extern CGuiViewApp theApp;
