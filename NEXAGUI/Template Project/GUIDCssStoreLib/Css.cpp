#include "StdAfx.h"
#include "GUIDCss.h"
#include "GUIDConstant.h"


CCssButton::CCssButton( ) :CCss( )
{
    dwBkgColor      = VALUE_COLOR_TRANSPARENT;         // Not use default color. Defaul is transparent
    dwTextAlign     = 0;

    // Border default parameters
    vBoxShadow.clear();
    sctBorder.dwBorderRadius    = 0;
    sctBorder.dwBorderStyle     = CSS_BORDER_SOLID;
    sctBorder.dwWidth           = 0;
    lpsctIcon = NULL;
    lpSctLine = NULL;
    dwFontWeight                = FW_BOLD;
    fLineHeight                 = 1.1f;
}

CCssButton::~CCssButton()
{
    if ( lpSctLine != NULL )
    {
        delete lpSctLine;
        lpSctLine = NULL;
    } 
    else
    {
        // Do nothing
    }
    
    if ( lpsctIcon != NULL )
    {
        delete lpsctIcon;
        lpsctIcon = NULL;
    } 
    else
    {
        // Do nothing
    }    
}

CCssFullBtn::~CCssFullBtn()
{
    if ( lpCssActive != NULL )
    {
        delete lpCssActive;
        lpCssActive = NULL;
    }
    else
    {
        // Do nothing
    }

    if ( lpCssDisable != NULL && lpCssDisable != this )
    {
        delete lpCssDisable;
        lpCssDisable = NULL;
    }
    else
    {
        // Do nothing
    }
}

CCssFullBtn::CCssFullBtn( ) :CCssButton( )
{
    lpCssActive = NULL;
    lpCssDisable = NULL;
}
