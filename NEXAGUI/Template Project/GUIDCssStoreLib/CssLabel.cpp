#include "StdAfx.h"
#include "GUIDCssLabel.h"


CCssLabel::CCssLabel(void)
{
    dwFontWeight    = FW_BOLD;
    dwTextColor     = 0x000000;
    dwBkgColor      = VALUE_COLOR_TRANSPARENT;
    dwTextAlign     = DT_LEFT | DT_TOP;
    dwPadL          = 0;
    dwPadT          = 0;
    dwPadR          = 0;
    dwPadB          = 0;
    lpSctAsmBorder  = NULL;
    vBoxShadow.clear();
}


CCssLabel::~CCssLabel(void)
{
    if ( lpSctAsmBorder != NULL )
    {
        delete lpSctAsmBorder;
    }
}
