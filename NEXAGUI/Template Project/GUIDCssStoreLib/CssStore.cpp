#include "StdAfx.h"
#include "GUIDCssStore.h"
#include "GUIDCssLabel.h"
#include "GUIDConstant.h"
#include <iostream>

CCssStore* CCssStore::m_instance = NULL;
CCssStore::CCssStore(void)
{
    m_mCssMap.clear();
}


CCssStore::~CCssStore(void)
{
    try
    {
        CSS_MAP::iterator it = m_mCssMap.begin();
        for ( ; it != m_mCssMap.end(); it++ )
        {
            delete it->second;
        }
    }
    catch ( std::exception &ex )
    {
        std::cout << ex.what();
    }
}

void CCssStore::DestroyInstance()
{
    if ( m_instance != NULL )
    {
        delete m_instance;
        m_instance = NULL;
    }
    else
    {
        //Do nothing
    }
}


CCss* CCssStore::GetCss(std::string sCssName)
{
    if ( m_instance == NULL )
    {
        m_instance = new CCssStore();
        m_instance->CreateCss();
    }
    else
    {
        //Do nothing
    }
    
    // Search css
    auto res = m_instance->m_mCssMap.find( sCssName );
    if ( res != m_instance->m_mCssMap.end( ) )
    {
        return m_instance->m_mCssMap[sCssName];
    }
    else
    {
        return NULL;
    }
}

void CCssStore::CreateCss()
{
    m_mCssMap.clear();
    
    CreateAllLableCss();
    CreateAllBtnCss();
}

VOID CCssStore::CreateAllLableCss()
{
    CCssLabel* lpStyle = NULL;
    
    /*---------------------------------------------
  •¶ŽšFÝ’è—p
-----------------------------------------------*//* •¶ŽšF • */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["_mojicolor_black"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;

    /* •¶ŽšF Â */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["_mojicolor_blue"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0xFF0000;

    /* •¶ŽšF Ô */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["_mojicolor_red"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x0000FF;

    /* •¶ŽšF —Î */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["_mojicolor_green"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x008000;

    /* •¶ŽšF ”’ */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["_mojicolor_white"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0xFFFFFF;

    /* •¶ŽšF ‰© */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["_mojicolor_yellow"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x00FFFF;

    /*---------------------------------------------
  ”wŒiF
-----------------------------------------------*//* ”wŒiFF’WŠD(‘€ì•”E’†‰›•\Ž¦•”) */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["background_color_light_gry"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xefebf0;

    /* ”wŒiFFŠD(•\Ž¦•”) */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["background_color_gry"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xded7d6;

    /* ”wŒiFF‰æ‘œ(íÝ•”E‹Æ–±ˆÄ“à•”Eó‘Ô•\Ž¦•”) */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["background_color_image"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\background.png";
    lpStyle->sctIcon.bRepeat = TRUE;
    lpStyle->dwBkgColor          = 0x00FFFFFF;            // CSS make by manual. Add to prevent transparent
    /*

    background-repeat:repeat;
    */

    /*---------------------------------------------
  ”wŒiF(‰eEƒ{[ƒ_[•t)
-----------------------------------------------*//* ”wŒiFF’WŠD(‘€ì•”) */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_background_color_light_gry"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xefebf0;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->TopEdge = SCT_EDGE(( DWORD )0x333333, ( DWORD )1 );
    lpStyle->lpSctAsmBorder->BottomEdge = SCT_EDGE(( DWORD )0x333333, ( DWORD )1 );
    lpStyle->lpSctAsmBorder->RightEdge = SCT_EDGE(( DWORD )0x333333, ( DWORD )1 );
    lpStyle->vBoxShadow.resize(( std::size_t )1 );
    lpStyle->vBoxShadow[0] = SCT_BOX_SHADOW(( LONG )0, ( LONG )2, ( DWORD )2, ( DWORD )0xadaaad );

    /* ”wŒiFF’WŠD(’†‰›•\Ž¦•”) */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_background_color_light_gry"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xefebf0;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x333333;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    lpStyle->vBoxShadow.resize(( std::size_t )1 );
    lpStyle->vBoxShadow[0] = SCT_BOX_SHADOW(( LONG )2, ( LONG )2, ( DWORD )2, ( DWORD )0xadaaad );

    /* ”wŒiFFŠD(•\Ž¦•”) */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_background_color_gry"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xded7d6;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->TopEdge = SCT_EDGE(( DWORD )0x333333, ( DWORD )1 );
    lpStyle->lpSctAsmBorder->BottomEdge = SCT_EDGE(( DWORD )0x333333, ( DWORD )1 );
    lpStyle->lpSctAsmBorder->LeftEdge = SCT_EDGE(( DWORD )0x333333, ( DWORD )1 );
    lpStyle->vBoxShadow.resize(( std::size_t )1 );
    lpStyle->vBoxShadow[0] = SCT_BOX_SHADOW(( LONG )2, ( LONG )2, ( DWORD )2, ( DWORD )0xa59a94 );

    /*---------------------------------------------
  •\Ž¦/”ñ•\Ž¦
-----------------------------------------------*//* ”ñ•\Ž¦ */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["visibility_hidden"] = lpStyle = new CCssLabel(); 
    /*

visibility:hidden; 
    */

    /* •\Ž¦ */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["visibility_visible"] = lpStyle = new CCssLabel(); 
    /*

visibility:visible; 
    */

    /*---------------------------------------------
  ToolTip
-----------------------------------------------*/
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["err-tooltips_sita"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0xffffff;
    // Error !

    
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["err-tooltips_ue"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0xffffff;
    // Error !

    /*---------------------------------------------
  ƒGƒŠƒA•Ê•”•i’è‹`
-----------------------------------------------*//*---------------------------------------------
  •\Ž¦€–Ú
-----------------------------------------------*//* No01 ŒÅ’èF•Žšã¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_fix_blk_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;

    /* No02 ŒÅ’èF•Žšã’†‰›‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_fix_blk_up_c_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;

    /* No03 ŒÅ’èF•Žš¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_fix_blk_c_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /*No.04 ŒÅ’èF•Žš’†‰›‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_fix_blk_c_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;

    /*No.05 ŒÅ’èF•Žš‰E‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_fix_blk_c_right_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 7;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;

    /* No.06 ˜g•tF•ŽšŠD”–Ž‡”wŒi’†‰›‘µ‚¦-Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_waku_blk_c_l_dlpur_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe0d2c6;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /*No.07 3D˜g•\Ž¦F¶‹l‚ß -‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_3d_blk_left_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFF80;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /*No.07 3D˜g•\Ž¦F¶‹l‚ß -”ñ‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_3d_blk_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFFFF;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /*No.07 3D˜g•\Ž¦F¶‹l‚ß -”ñŠˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_3d_blk_left_disabled"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xE1D1C8;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /*No.08 3D˜g•\Ž¦F‰E‹l‚ß -‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_3d_blk_right_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFF80;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /*No.08 3D˜g•\Ž¦F‰E‹l‚ß -”ñ‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_3d_blk_right_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFFFF;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /*No.08 3D˜g•\Ž¦F‰E‹l‚ß -”ñŠˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_3d_blk_right_disabled"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xE1D1C8;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* No09 ŒÅ’èF•Žš¶‹l‚ßi×Žšj -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_fix_blk_c_left_t_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;
    lpStyle->dwFontWeight = FW_NORMAL;

    /* No.10 3D˜g•\Ž¦F¶‹l‚ßi×Žšj -‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_3d_blk_left_t_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFF80;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;
    lpStyle->dwFontWeight = FW_NORMAL;

    /* No.10 3D˜g•\Ž¦F¶‹l‚ßi×Žšj -”ñ‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_3d_blk_left_t_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFFFF;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;
    lpStyle->dwFontWeight = FW_NORMAL;

    /* No.10 3D˜g•\Ž¦F¶‹l‚ßi×Žšj -”ñŠˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_3d_blk_left_t_disabled"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xE1D1C8;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;
    lpStyle->dwFontWeight = FW_NORMAL;

    /* No.11 3D˜g•\Ž¦F‰E‹l‚ßi×Žšj -‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_3d_blk_right_t_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFF80;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;
    lpStyle->dwFontWeight = FW_NORMAL;

    /* No.11 3D˜g•\Ž¦F‰E‹l‚ßi×Žšj -”ñ‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_3d_blk_right_t_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFFFF;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;
    lpStyle->dwFontWeight = FW_NORMAL;

    /* No.11 3D˜g•\Ž¦F‰E‹l‚ßi×Žšj -”ñŠˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_3d_blk_right_t_disabled"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xE1D1C8;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;
    lpStyle->dwFontWeight = FW_NORMAL;

    /* No12 ˜g•tF•ŽšŠD”–Ž‡”wŒi‰E‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_waku_blk_c_r_dlpur_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe0d2c6;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* No13 ŒÅ’èF•Žš¶‹l‚ß(ˆÊ’u’²®) -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_fix_blk_c_left_modify_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_3d_blk_left_mono_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFF80;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;
    /*

    font-family: "‚l‚r ƒSƒVƒbƒN" , "monospace";
    */

    /*No.13 3D˜g•\Ž¦F¶‹l‚ßi“™•j-”ñ‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_3d_blk_left_mono_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFFFF;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;
    /*

    font-family: "‚l‚r ƒSƒVƒbƒN" , "monospace";
    */

    /*No.13 3D˜g•\Ž¦F¶‹l‚ßi“™•j -”ñŠˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["disp_3d_blk_left_mono_disabled"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xE1D1C8;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;
    /*

    font-family: "‚l‚r ƒSƒVƒbƒN" , "monospace";
    */

    /*---------------------------------------------
  ƒGƒŠƒA•Ê•”•i’è‹`
-----------------------------------------------*//*---------------------------------------------
  •\Ž¦€–Ú
-----------------------------------------------*//* No01 ŒÅ’èF•Žšã¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;

    /* No02 ŒÅ’èF•Žšã’†‰›‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_up_c_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;

    /* No03 ŒÅ’èF•Žš¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_c_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /* No04 ŒÅ’èF•Žš’†‰›‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_c_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;

    /* No05 ŒÅ’èF•Žš‰E‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_c_right_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 7;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;

    /* No06 ŒÅ’èF•Žš‰º¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_dw_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->dwTextAlign = DT_LEFT | DT_BOTTOM;

    /* No07 ŒÅ’èF•Žš‰º’†‰›‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_dw_c_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwTextAlign = DT_CENTER | DT_BOTTOM;

    /* No08 ŒÅ’èF•Žš‰º‰E‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_dw_r_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_BOTTOM;

    /* No09 ŒÅ’èF•Žšã¶‘µ‚¦iÂj -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_up_l_blu_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe9dec7;

    /* No10 ŒÅ’èF•ŽšŠD…F”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_c_l_gsky_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe9dec7;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /* No11 ŒÅ’èF•ŽšŠD…F”wŒi‰E‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_c_r_gsky_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe9dec7;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 7;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;

    /* No12 ŒÅ’èF•ŽšŠD“”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_c_l_gpink_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xc3b8d9;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /* No13 ŒÅ’èF•Žš’†‰›‘µ‚¦i”ZÔj -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_c_gpink_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xc3b8d9;

    /* No14 ŒÅ’èF•ŽšŠD‰©—Î”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_c_l_golive_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xddd7d0;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /* No15 ŒÅ’èF•ŽšŠD‰©—Î”wŒi’†‰›‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_c_golive_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xddd7d0;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;

    /* No16 ŒÅ’èF•ŽšŠD‰©”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_c_l_gyel_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe3f0f2;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /* No17 ŒÅ’èF•ŽšŠD‰©”wŒi’†‰›‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_c_gyel_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe3f0f2;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;

    /* No18 ŒÅ’èF•Žš”Z”–Ž‡”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_c_l_dlpur_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe6d2d3;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /* No19 ŒÅ’èF•Žš”Z”–Ž‡”wŒi‰E‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_c_r_dlpur_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe6d2d3;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 7;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;

    /* No20 ŒÅ’èF•ŽšŠD…F”wŒi’†‰›‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_c_gsky_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe9dec7;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;

    /* No21 ŒÅ’èF•Žš‰º¶‹l‚ßiÂj -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_d_l_blu_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe9dec7;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->dwTextAlign = DT_LEFT | DT_BOTTOM;

    /* No22 ŒÅ’èF•Žš‰º‰E‹l‚ßiÂj -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_d_r_blu_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe9dec7;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_BOTTOM;

    /* No23 ŒÅ’èF•Žš‰©”wŒi’†‰›‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_c_yel_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x00ffff;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;

    /* No24 ŒÅ’èFÔŽšã¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_red_up_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x0000FF;
    lpStyle->dwPadL = 4;

    /* No25 ŒÅ’èFÔŽš¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_red_c_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x391e7b;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /* No26 ŒÅ’èFÔŽšŠD“”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_red_c_l_gpink_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xc3b8d9;
    lpStyle->dwTextColor = 0x391e7b;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /* No27 ŒÅ’èF•Â—ÎŽš¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_baqua_c_l_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0xFF0000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /* No28 ŒÅ’èF•Â—ÎŽšŠD”–Ž‡”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_baqua_c_l_dlpur_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe1d1c8;
    lpStyle->dwTextColor = 0xFF0000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /* No29 ŒÅ’èF•Â—ÎŽšŠD‰©”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_baqua_c_l_gyel_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xddd7d0;
    lpStyle->dwTextColor = 0xFF0000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /* No30 ŒÅ’èF•Â—ÎŽšŠD‰©”wŒi’†‰›‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_baqua_c_gyel_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xddd7d0;
    lpStyle->dwTextColor = 0xFF0000;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;

    /* No31 ŒÅ’èF–¾…FŽš•®”wŒi’†‰›‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_cyan_c_dbl_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x523127;
    lpStyle->dwTextColor = 0x81684b;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;

    /* No32 ˜g•tF•Žšã¶‹l‚ßi…Fj -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_waku_blk_up_c_wb_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe2d1c8;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* No33 ˜g•tF•ŽšŠD”–Ž‡”wŒi’†‰›‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_waku_blk_c_l_dlpur_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe0d2c6;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* No34 ˜g•tF•ŽšŠD”–Ž‡”wŒi‰E‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_waku_blk_c_r_dlpur_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe0d2c6;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_waku_blk_c_r_dlpur_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe0d2c6;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* No35 3D˜g•\Ž¦F•Žš¶‹l‚ß -‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_3d_blk_left_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFF80;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* No35 3D˜g•\Ž¦F•Žš¶‹l‚ß -”ñ‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_3d_blk_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFFFF;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* No35 3D˜g•\Ž¦F•Žš¶‹l‚ß -”ñŠˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_3d_blk_left_disabled"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xE1D1C8;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* No36 3D˜g•\Ž¦F‰E‹l‚ß -‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_3d_blk_right_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFF80;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* No36 3D˜g•\Ž¦F‰E‹l‚ß -”ñ‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_3d_blk_right_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFFFF;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* No36 3D˜g•\Ž¦F‰E‹l‚ß -”ñŠˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_3d_blk_right_disabled"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xE1D1C8;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* No37 ŒÅ’èŠpŠÛFÔŽšŠD“”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_kaku_red_c_l_gpink_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xc3b8d9;
    lpStyle->dwTextColor = 0x391e7b;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderRadius = 5;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->BottomEdge = SCT_EDGE(( DWORD )0xeaeaea, ( DWORD )1 );

    /* No38 ŒÅ’èŠpŠÛF•Â—ÎŽšŠD‰©”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_kaku_baqua_c_l_gyel_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xddd7d0;
    lpStyle->dwTextColor = 0x5c4e38;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderRadius = 5;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->BottomEdge = SCT_EDGE(( DWORD )0xeaeaea, ( DWORD )1 );

    /* No39 ‰æ‘œFƒXƒgƒŒƒbƒ`—L‚è */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_img_stretch_off"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\center_disp\\right_arrow.png";
    /*

    max-width: 100%;
    height: auto;
    background-repeat: no-repeat;
    */

    /* No40 ‰æ‘œFƒXƒgƒŒƒbƒ`–³‚µ */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_img_fixsize_off"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\center_disp\\right_arrow.png";
    /*

    background-repeat: no-repeat;
    */

    /* No46 ”wŒiFŠD…F -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_back_gsky_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe9dec7;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x69503f;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    /*

    display: table-cell;
    clear: both;
    overflow: hidden;
    */

    /* No47 ŠpŠÛ”wŒiFŠD‰© -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_back_gyel_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xddd7d0;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0xe8e2dc;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    /*

    display: table-cell;
    clear: both;
    overflow: hidden;
    */

    /* No48 ŒÅ’èF•ŽšŠD…F”wŒi¶‹l‚ßsŠÔ‚ ‚è -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_blk_c_l_gsky_lh_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe9dec7;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;
    lpStyle->fLineHeight = 1.2f;

    /* No49 ŠpŠÛ”wŒiFƒsƒ“ƒN -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_back_pink_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xdbcde7;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0xdbcde7;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    /*

    display: table-cell;
    clear: both;
    overflow: hidden;
    */

    /* No50 ŠpŠÛ”wŒiF—Î -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_back_green_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xc2dcce;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0xc2dcce;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    /*

    display: table-cell;
    clear: both;
    overflow: hidden;
    */

    /* No51 ˜g•tF•Žš“§–¾”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_waku_blk_c_l_tp_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = VALUE_COLOR_TRANSPARENT;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* No52 ˜g•tF•Žš“§–¾”wŒi‰E‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_waku_blk_c_r_tp_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = VALUE_COLOR_TRANSPARENT;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* No53 ”wŒiF”ZÂi‚s‚n‚oj -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_back_top_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x915726;
    /*

    display: table-cell;
    clear: both;
    overflow: hidden;
    */

    /* No54 ˜g•tF•ŽšŠD“”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_waku_blk_c_l_gpink_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xc3b8d9;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* ˜g•tF•ŽšŠD“”wŒi‰E‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_waku_blk_c_r_gpink_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xc3b8d9;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* No56 ŠpŠÛ”wŒiFŠD—Î -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_back_ggrn_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xdedfcb;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0xdedfcb;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    /*

    display: table-cell;
    clear: both;
    overflow: hidden;
    */

    /* No57 ŠpŠÛ”wŒiFŠDÂ—Î -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_back_gbgrn_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xaf8260;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0xaf8260;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    lpStyle->sctBorder.dwBorderRadius = 5;
    /*

    display: table-cell;
    clear: both;
    overflow: hidden;
    */

    /* No58 ŒÅ’èF”’Žš’†‰›‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_wht_c_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0xffffff;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;

    /* No59 ŒÅ’èFÔŽš‰E‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_red_c_right_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x391e7b;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;

    /* No59-2 ŒÅ’èFÔŽš‰E‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_red_c_right2_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x391e7b;
    lpStyle->dwPadR = 7;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;

    /* No60 ŒÅ’èFÂ—ÎŽš’†‰›‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_baqua_cent_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x5c4e38;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;

    /* No61 ŒÅ’èFÂ—ÎŽš¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_baqua_c_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x5c4e38;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /* No62 ŒÅ’èFÂ—ÎŽš‰E‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_baqua_c_right_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x5c4e38;
    lpStyle->dwPadR = 7;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;

    /* No63 ˜g•tF”’Žš”–Ô”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_waku_wht_c_l_lred_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x8f6cbf;
    lpStyle->dwTextColor = 0xffffff;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* No.64 ˜g•tF”’Žš”–Ô”wŒi‰E‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_waku_wht_c_r_lred_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x8f6cbf;
    lpStyle->dwTextColor = 0xffffff;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* No65 ˜g•tF”’Žš”–Â”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_waku_wht_c_l_lblue_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x866846;
    lpStyle->dwTextColor = 0xffffff;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* No.66 ˜g•tF”’Žš”–Â”wŒi‰E‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_waku_wht_c_r_lblue_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x866846;
    lpStyle->dwTextColor = 0xffffff;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* No67 ŒÅ’èF”’Žš¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_wht_c_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0xffffff;
    lpStyle->dwPadL = 4;

    /* No68 ŒÅ’èF”’Žš‰E‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_fix_wht_c_right_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0xffffff;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;

    /* No69 ˜g•tF•ŽšŠD”–Ž‡”wŒi‰E‹l‚ßi–¾‚é‚ßj -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_waku_blk_c_r_dlpur_bri_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xecd5c0;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* No70 ˜g•tF•ŽšŠD“”wŒi‰E‹l‚ßi–¾‚é‚ßj -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_waku_blk_c_r_gpink_bri_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xc9bee4;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* No71 ”wŒiFŠD…F(ƒ^ƒu”wŒi—p) -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_back_gsky_tab_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe9dec7;
    lpStyle->sctBorder.dwBorderRadius = 5;
    lpStyle->vBoxShadow.resize(( std::size_t )1 );
    lpStyle->vBoxShadow[0] = SCT_BOX_SHADOW(( LONG )2, ( LONG )2, ( DWORD )4, ( DWORD )0x9b9c9e );
    lpStyle->vBoxShadow[0].bInset = FALSE;                                  // CSS make by manual
    /*

    display: table-cell;
    clear: both;
    overflow: hidden;
    */

    /* No72 ˜g•tF•ŽšŠD”–Ž‡”wŒi’†‰›‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_waku_blk_c_c_dlpur_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe0d2c6;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /*---------------------------------------------
  ƒ^ƒu
-----------------------------------------------*//* No01 ‰EŠpŠÛƒ^ƒuFŠD…F -”ñ‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_tab_gsky_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xb6ae9c;
    lpStyle->dwTextColor = 0xe9dec7;
    lpStyle->dwTextAlign = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->dwRadiusLT = 0;
    lpStyle->lpSctAsmBorder->dwRadiusRT = 10;
    lpStyle->lpSctAsmBorder->dwRadiusRB = 10;
    lpStyle->lpSctAsmBorder->dwRadiusLB = 0;
    lpStyle->lpSctAsmBorder->TopEdge = SCT_EDGE(( DWORD )0xcbc6bb, ( DWORD )1 );
    lpStyle->lpSctAsmBorder->BottomEdge = SCT_EDGE(( DWORD )0xc2bcae, ( DWORD )1 );
    lpStyle->lpSctAsmBorder->LeftEdge = SCT_EDGE(( DWORD )0x9b9c9e, ( DWORD )1 );            // CSS make by manual
    lpStyle->lpSctAsmBorder->RightEdge = SCT_EDGE(( DWORD )0xc2bcae, ( DWORD )1 );
    lpStyle->lMarL = 1;
    lpStyle->lMarR = -1;
    /*

    float: left;
    */

    /* No01 ‰EŠpŠÛƒ^ƒuFŠD…F -‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_tab_gsky_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe9dec7;
    lpStyle->dwTextColor = 0x916b39;
    lpStyle->dwTextAlign = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->dwRadiusLT = 0;
    lpStyle->lpSctAsmBorder->dwRadiusRT = 10;
    lpStyle->lpSctAsmBorder->dwRadiusRB = 10;
    lpStyle->lpSctAsmBorder->dwRadiusLB = 0;
    lpStyle->lpSctAsmBorder->TopEdge = SCT_EDGE(( DWORD )0xe1ddd2, ( DWORD )1 );
    lpStyle->lpSctAsmBorder->BottomEdge = SCT_EDGE(( DWORD )0x9b9c9e, ( DWORD )1 );
    lpStyle->lpSctAsmBorder->LeftEdge = SCT_EDGE(( DWORD )0xe9dec7, ( DWORD )0 );                // CSS make by manual
    lpStyle->lpSctAsmBorder->RightEdge = SCT_EDGE(( DWORD )0x9b9c9e, ( DWORD )1 );
    lpStyle->lMarL = 1;
    lpStyle->lMarR = -1;
    lpStyle->vBoxShadow.resize(( std::size_t )1 );
    lpStyle->vBoxShadow[0] = SCT_BOX_SHADOW(( LONG )2, ( LONG )2, ( DWORD )4, ( DWORD )0x9b9c9e );
    lpStyle->vBoxShadow[0].bInset = FALSE;                                      // CSS make by manual
    /*

    float: left;
    */

    /* No02 ‰EŠpŠÛƒ^ƒuF‰©F -”ñ‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_tab_yel_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x00ffff;
    lpStyle->dwTextColor = 0x523127;
    lpStyle->dwTextAlign = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->dwRadiusLT = 0;
    lpStyle->lpSctAsmBorder->dwRadiusRT = 10;
    lpStyle->lpSctAsmBorder->dwRadiusRB = 10;
    lpStyle->lpSctAsmBorder->dwRadiusLB = 0;
    lpStyle->lpSctAsmBorder->TopEdge = SCT_EDGE(( DWORD )0xcbc6bb, ( DWORD )1 );
    lpStyle->lpSctAsmBorder->BottomEdge = SCT_EDGE(( DWORD )0xc2bcae, ( DWORD )1 );
    lpStyle->lpSctAsmBorder->LeftEdge = SCT_EDGE(( DWORD )0x000000, ( DWORD )0 );
    lpStyle->lpSctAsmBorder->RightEdge = SCT_EDGE(( DWORD )0xc2bcae, ( DWORD )1 );
    lpStyle->lMarL = 1;
    lpStyle->lMarR = -1;
    lpStyle->vBoxShadow.resize(( std::size_t )2 );
    lpStyle->vBoxShadow[0] = SCT_BOX_SHADOW(( LONG )-4, ( LONG )-4, ( DWORD )2, ( DWORD )0xc2bcae );
    lpStyle->vBoxShadow[1] = SCT_BOX_SHADOW(( LONG )0, ( LONG )4, ( DWORD )2, ( DWORD )0xcbc6bb );
    /*

    float: left;
    */

    /* No02 ‰EŠpŠÛƒ^ƒuF‰©F -‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_tab_yel_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x00ffff;
    lpStyle->dwTextColor = 0x523127;
    lpStyle->dwTextAlign = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->dwRadiusLT = 0;
    lpStyle->lpSctAsmBorder->dwRadiusRT = 10;
    lpStyle->lpSctAsmBorder->dwRadiusRB = 10;
    lpStyle->lpSctAsmBorder->dwRadiusLB = 0;
    lpStyle->lpSctAsmBorder->TopEdge = SCT_EDGE(( DWORD )0xe1ddd2, ( DWORD )1 );
    lpStyle->lpSctAsmBorder->BottomEdge = SCT_EDGE(( DWORD )0x9b9c9e, ( DWORD )1 );
    lpStyle->lpSctAsmBorder->LeftEdge = SCT_EDGE(( DWORD )0x000000, ( DWORD )0 );
    lpStyle->lpSctAsmBorder->RightEdge = SCT_EDGE(( DWORD )0x9b9c9e, ( DWORD )1 );
    lpStyle->lMarL = 1;
    lpStyle->lMarR = -1;
    lpStyle->vBoxShadow.resize(( std::size_t )2 );
    lpStyle->vBoxShadow[0] = SCT_BOX_SHADOW(( LONG )-4, ( LONG )-4, ( DWORD )2, ( DWORD )0x9b9c9e );
    lpStyle->vBoxShadow[1] = SCT_BOX_SHADOW(( LONG )0, ( LONG )4, ( DWORD )2, ( DWORD )0xe1ddd2 );
    /*

    float: left;
    */

    /* No03 ‰EŠpŠÛƒ^ƒuFˆÃ‰© -”ñ‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_tab_dyel_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x3daab6;
    lpStyle->dwTextColor = 0xFFFFFF;
    lpStyle->dwTextAlign = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->dwRadiusLT = 0;
    lpStyle->lpSctAsmBorder->dwRadiusRT = 10;
    lpStyle->lpSctAsmBorder->dwRadiusRB = 10;
    lpStyle->lpSctAsmBorder->dwRadiusLB = 0;
    lpStyle->lpSctAsmBorder->TopEdge = SCT_EDGE(( DWORD )0xcbc6bb, ( DWORD )1 );
    lpStyle->lpSctAsmBorder->BottomEdge = SCT_EDGE(( DWORD )0xc2bcae, ( DWORD )1 );
    lpStyle->lpSctAsmBorder->LeftEdge = SCT_EDGE(( DWORD )0x000000, ( DWORD )0 );
    lpStyle->lpSctAsmBorder->RightEdge = SCT_EDGE(( DWORD )0xc2bcae, ( DWORD )1 );
    lpStyle->lMarL = 1;
    lpStyle->lMarR = -1;
    lpStyle->vBoxShadow.resize(( std::size_t )2 );
    lpStyle->vBoxShadow[0] = SCT_BOX_SHADOW(( LONG )-4, ( LONG )-4, ( DWORD )2, ( DWORD )0xc2bcae );
    lpStyle->vBoxShadow[1] = SCT_BOX_SHADOW(( LONG )0, ( LONG )4, ( DWORD )2, ( DWORD )0xcbc6bb );
    /*

    float: left;
    */

    /* No03 ‰EŠpŠÛƒ^ƒuFˆÃ‰© -‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["center_disp_tab_dyel_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x3daab6;
    lpStyle->dwTextColor = 0xFFFFFF;
    lpStyle->dwTextAlign = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->dwRadiusLT = 0;
    lpStyle->lpSctAsmBorder->dwRadiusRT = 10;
    lpStyle->lpSctAsmBorder->dwRadiusRB = 10;
    lpStyle->lpSctAsmBorder->dwRadiusLB = 0;
    lpStyle->lpSctAsmBorder->TopEdge = SCT_EDGE(( DWORD )0xe1ddd2, ( DWORD )1 );
    lpStyle->lpSctAsmBorder->BottomEdge = SCT_EDGE(( DWORD )0x9b9c9e, ( DWORD )1 );
    lpStyle->lpSctAsmBorder->LeftEdge = SCT_EDGE(( DWORD )0x000000, ( DWORD )0 );
    lpStyle->lpSctAsmBorder->RightEdge = SCT_EDGE(( DWORD )0x9b9c9e, ( DWORD )1 );
    lpStyle->lMarL = 1;
    lpStyle->lMarR = -1;
    lpStyle->vBoxShadow.resize(( std::size_t )2 );
    lpStyle->vBoxShadow[0] = SCT_BOX_SHADOW(( LONG )-4, ( LONG )-4, ( DWORD )2, ( DWORD )0x9b9c9e );
    lpStyle->vBoxShadow[1] = SCT_BOX_SHADOW(( LONG )0, ( LONG )4, ( DWORD )2, ( DWORD )0xe1ddd2 );
    /*

    float: left;
    */

    /*---------------------------------------------
  ƒGƒŠƒA•Ê•”•i’è‹`
-----------------------------------------------*//*---------------------------------------------
  •\Ž¦€–Ú
-----------------------------------------------*//* ŒÅ’èF”’Žš’†‰›‘µ‚¦ */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["gyomu_annai_fix_wht_c_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0xffffff;
    lpStyle->dwPadL = 4;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;
    lpStyle->dwFontWeight = FW_NORMAL;
    /*

    box-sizing: border-box;
    -webkit-box-sizing: border-box;
    */

    /* ŒÅ’èF–¾…FŽš•®”wŒi¶‹l‚ß */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["gyomu_annai_fix_cyan_l_dbl_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x523227;
    lpStyle->dwTextColor = 0xd8d168;
    lpStyle->dwPadL = 4;
    lpStyle->dwPadT = 2;                                                        // CSS make by manual
    lpStyle->sctBorder.dwWidth = 2;
    lpStyle->sctBorder.dwColor = VALUE_COLOR_TRANSPARENT;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ŒÅ’èF•Žš”Z‰©”wŒi¶‹l‚ß js add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["gyomu_annai_fix_blk_l_dyel_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x2fbfea;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwWidth = 2;
    lpStyle->sctBorder.dwColor = VALUE_COLOR_TRANSPARENT;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    lpStyle->dwFontWeight = FW_NORMAL;

    /*---------------------------------------------
  ƒGƒŠƒA•Ê•”•i’è‹`
-----------------------------------------------*//*---------------------------------------------
  •\Ž¦€–Ú
-----------------------------------------------*//* ŒÅ’èF•Žšã¶‹l‚ß js add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_fix_blk_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* ŒÅ’èF•Žšã¶‹l‚ß js add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_fix_blk_left_off_top"] = lpStyle = new CCssLabel(); 
    /*

    position: relative;
    top: 0;
    */

    /* ŒÅ’èF•Žšã’†‰›‘µ‚¦ js add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_fix_blk_up_c_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* ŒÅ’èF•Žš¶‹l‚ß */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_fix_blk_c_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /* ŒÅ’èF•Žš’†‰›‘µ‚¦ */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_fix_blk_c_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;

    /* ŒÅ’èF•Žš‰E‹l‚ß js add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_fix_blk_c_right_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 7;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;

    /* ŒÅ’èF•Â—ÎŽš¶‹l‚ß js add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_fix_baqua_c_l_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x916b39;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /* ŒÅ’èF•Žšã‹l‚ß js add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_fix_blk_up_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;

    /* ŠpŠÛ”wŒiFŠD‰© js add *//* 20141022 F•ÏX JS */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_back_gyel_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xddd7d0;
    lpStyle->sctBorder.dwBorderRadius = 5;

    /* ”wŒiF’WŠD  *//* 20141110(operation_back_gyel_off‚ÌFˆá‚¢”Å) */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_back_lgry_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xefebf0;
    lpStyle->sctBorder.dwBorderRadius = 5;

    /* ˜g•tF•Žšã¶‹l‚ßi…Fj js add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_waku_blk_up_c_wb_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe0d2c6;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* ˜g•tF•ŽšŠD”–Ž‡”wŒi¶‹l‚ß */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_waku_blk_c_l_dlpur_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe0d2c6;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* ˜g•tF•ŽšŠD”–Ž‡”wŒi‰E‹l‚ß */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_waku_blk_c_r_dlpur_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe0d2c6;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_waku_blk_c_r_dlpur_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe0d2c6;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* ŒÅ’èF•Žš¶‹l‚ßi×Žšj */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_fix_blk_c_left_t_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ˜g•tF•ŽšŠD”–Ž‡”wŒi¶‹l‚ßi×Žšj */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_waku_blk_c_l_dlpur_t_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe0d2c6;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ˜g•tF•ŽšŠD”–Ž‡”wŒi‰E‹l‚ßi×Žšj */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_waku_blk_c_r_dlpur_t_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe0d2c6;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    lpStyle->dwFontWeight = FW_NORMAL;

    /***********************************************//* 3D˜g•\Ž¦ JS ADD                             *//* 3D˜g•\Ž¦F•Žš¶‹l‚ß -‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_3d_blk_left_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFF80;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* 3D˜g•\Ž¦F•Žš¶‹l‚ß -”ñ‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_3d_blk_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFFFF;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* 3D˜g•\Ž¦F•Žš¶‹l‚ß -”ñŠˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_3d_blk_left_disabled"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xE1D1C8;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* 3D˜g•\Ž¦F‰E‹l‚ß -‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_3d_blk_right_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFF80;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* 3D˜g•\Ž¦F‰E‹l‚ß -”ñ‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_3d_blk_right_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFFFF;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* 3D˜g•\Ž¦F‰E‹l‚ß -”ñŠˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_3d_blk_right_disabled"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xE1D1C8;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /***********************************************//* No22 ŒÅ’èF•Â—ÎŽšŠD”–Ž‡”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_fix_baqua_c_l_dlpur_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe1d1c8;
    lpStyle->dwTextColor = 0xFF0000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /* No23 ŒÅ’èF•Â—ÎŽšŠD‰©”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_fix_baqua_c_l_gyel_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xddd7d0;
    lpStyle->dwTextColor = 0xFF0000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;

    /* No24 ŒÅ’èF•Â—ÎŽšŠD‰©”wŒi’†‰›‘µ‚¦ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_fix_baqua_c_gyel_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xddd7d0;
    lpStyle->dwTextColor = 0xFF0000;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;

    /* No25 ŒÅ’èŠpŠÛFÔŽšŠD“”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_kaku_red_c_l_gpink_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xc3b8d9;
    lpStyle->dwTextColor = 0x3d0b9f;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderRadius = 5;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->BottomEdge = SCT_EDGE(( DWORD )0xeaeaea, ( DWORD )1 );

    /* No26 ŒÅ’èŠpŠÛF•Â—ÎŽšŠD‰©”wŒi¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_kaku_baqua_c_l_gyel_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xddd7d0;
    lpStyle->dwTextColor = 0x5c4e38;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderRadius = 5;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->BottomEdge = SCT_EDGE(( DWORD )0xeaeaea, ( DWORD )1 );

    /* No.27 ˜g•tF•ŽšŠD”–Ž‡”wŒi‰E‹l‚ßi–¾‚é‚ßj */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_waku_blk_c_r_dlpur_bri_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xecd5c0;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;


    /*-------------------------------------------------------------------------------*//* ”wŒi *//*-------------------------------------------------------------------------------*//* ƒRƒ“ƒeƒi ”wŒiFŠD”–Ž‡ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_back_pur_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xce7d63;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->TopEdge = SCT_EDGE(( DWORD )0xe7bead, ( DWORD )3 );
    lpStyle->lpSctAsmBorder->BottomEdge = SCT_EDGE(( DWORD )0x633829, ( DWORD )3 );
    lpStyle->lpSctAsmBorder->LeftEdge = SCT_EDGE(( DWORD )0xe7bead, ( DWORD )3 );
    lpStyle->lpSctAsmBorder->RightEdge = SCT_EDGE(( DWORD )0x633829, ( DWORD )3 );
    /*

    display: table-cell;
    clear: both;
    overflow: hidden;
    */

    /* ƒRƒ“ƒeƒi ”wŒiF”–—Î -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_back_lpur_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xd6aa8c;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->TopEdge = SCT_EDGE(( DWORD )0xefd3c6, ( DWORD )3 );
    lpStyle->lpSctAsmBorder->BottomEdge = SCT_EDGE(( DWORD )0x735542, ( DWORD )3 );
    lpStyle->lpSctAsmBorder->LeftEdge = SCT_EDGE(( DWORD )0xefd3c6, ( DWORD )3 );
    lpStyle->lpSctAsmBorder->RightEdge = SCT_EDGE(( DWORD )0x735542, ( DWORD )3 );
    /*

    display: table-cell;
    clear: both;
    overflow: hidden;
    */

    /* ƒRƒ“ƒeƒi ”wŒiFŠDŽ‡H -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_back_dlpur_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xefd3c6;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->TopEdge = SCT_EDGE(( DWORD )0xf7e7de, ( DWORD )3 );
    lpStyle->lpSctAsmBorder->BottomEdge = SCT_EDGE(( DWORD )0x635952, ( DWORD )3 );
    lpStyle->lpSctAsmBorder->LeftEdge = SCT_EDGE(( DWORD )0xf7e7de, ( DWORD )3 );
    lpStyle->lpSctAsmBorder->RightEdge = SCT_EDGE(( DWORD )0x635952, ( DWORD )3 );
    /*

    display: table-cell;
    clear: both;
    overflow: hidden;
    */

    /* ƒRƒ“ƒeƒi ”wŒiFŠD“ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["operation_back_‚‡pnk_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xc3b8da;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->TopEdge = SCT_EDGE(( DWORD )0xd4cce4, ( DWORD )3 );
    lpStyle->lpSctAsmBorder->BottomEdge = SCT_EDGE(( DWORD )0x6f697c, ( DWORD )3 );
    lpStyle->lpSctAsmBorder->LeftEdge = SCT_EDGE(( DWORD )0xd4cce4, ( DWORD )3 );
    lpStyle->lpSctAsmBorder->RightEdge = SCT_EDGE(( DWORD )0x6f697c, ( DWORD )3 );
    /*

    display: table-cell;
    clear: both;
    overflow: hidden;
    */

    /*---------------------------------------------
  ƒGƒŠƒA•Ê•”•i’è‹`
-----------------------------------------------*//*---------------------------------------------
  •\Ž¦€–Ú
-----------------------------------------------*//* ‰æ‘œFƒ[ƒjƒ“ƒO js add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_img_warning_off"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\popup\\lbl_warning.png";

    /* ‰æ‘œFƒXƒgƒŒƒbƒ`–³‚µ(ƒ[ƒjƒ“ƒO) TSA add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_img_fixsize_off"] = lpStyle = new CCssLabel(); 
    /*

    background-repeat: no-repeat;
    */

    /* ŒÅ’èF•Žšã¶‹l‚ß js add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_fix_blk_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;

    /* ŒÅ’èF•Žšã’†‰›‘µ‚¦ js add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_fix_blk_up_c_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;

    /* ŒÅ’èF•Žš¶‹l‚ß */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_fix_blk_c_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;
    lpStyle->fLineHeight = 1.4f;

    /* ŒÅ’èF•Žš¶‹l‚ß(×Žš) */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_fix_blk_c_left_t_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ŒÅ’èF•Žš’†‰›‘µ‚¦ */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_fix_blk_c_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;

    /* ŒÅ’èF•Žš’†‰›‘µ‚¦(×Žš) */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_fix_blk_c_t_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ŒÅ’èF•Žš‰E‹l‚ß js add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_fix_blk_c_right_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 7;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;

    /* ŒÅ’èF•Žš‰E‹l‚ß(×Žš) */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_fix_blk_c_right_t_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 7;
    lpStyle->dwPadT = 3;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->dwFontWeight = FW_NORMAL;

    /* No.010 *//* ŠpŠÛ”wŒiF‰© js add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_back_lye_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe3f0f2;
    lpStyle->sctBorder.dwWidth = 15;
    lpStyle->sctBorder.dwColor = 0x40bed9;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    lpStyle->sctBorder.dwBorderRadius = 10;
    lpStyle->vBoxShadow.resize(( std::size_t )2 );
    lpStyle->vBoxShadow[0] = SCT_BOX_SHADOW(( LONG )-5, ( LONG )-5, ( DWORD )5, ( DWORD )0x91dae9 );
    lpStyle->vBoxShadow[1] = SCT_BOX_SHADOW(( LONG )5, ( LONG )5, ( DWORD )5, ( DWORD )0x1a4d58 );

    /* No.011 *//* ŠpŠÛ”wŒiFŽ‡ js add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_back_lvi_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xefeaea;
    lpStyle->sctBorder.dwWidth = 15;
    lpStyle->sctBorder.dwColor = 0xab7275;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    lpStyle->sctBorder.dwBorderRadius = 10;
    lpStyle->vBoxShadow.resize(( std::size_t )2 );
    lpStyle->vBoxShadow[0] = SCT_BOX_SHADOW(( LONG )-5, ( LONG )-5, ( DWORD )5, ( DWORD )0xe1cced );
    lpStyle->vBoxShadow[1] = SCT_BOX_SHADOW(( LONG )5, ( LONG )5, ( DWORD )5, ( DWORD )0x5b3c3e );

    /* No.012 *//* ŠpŠÛ”wŒiFÔ js add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_back_lre_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe5e5ed;
    lpStyle->sctBorder.dwWidth = 15;
    lpStyle->sctBorder.dwColor = 0x3437b9;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    lpStyle->sctBorder.dwBorderRadius = 10;
    lpStyle->vBoxShadow.resize(( std::size_t )2 );
    lpStyle->vBoxShadow[0] = SCT_BOX_SHADOW(( LONG )-5, ( LONG )-5, ( DWORD )5, ( DWORD )0x7678d0 );
    lpStyle->vBoxShadow[1] = SCT_BOX_SHADOW(( LONG )5, ( LONG )5, ( DWORD )5, ( DWORD )0x1b1c61 );

    /* ˜g•tF•Žšã¶‹l‚ßi…Fj js add */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_waku_blk_up_c_wb_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe0d2c6;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* ˜g•tF•ŽšŠD”–Ž‡”wŒi’†‰›‘µ‚¦ */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_waku_blk_c_l_dlpur_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe0d2c6;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x000000;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* ŒÅ’èŠpŠÛFÔŽšŠD“”wŒi¶‹l‚ß */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_kaku_red_c_l_gpink_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xc3b8da;
    lpStyle->dwTextColor = 0x391e7b;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderRadius = 5;

    /* No19 ŒÅ’èFÔŽš¶‹l‚ß */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_fix_red_c_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x0000FF;
    lpStyle->dwPadL = 7;
    lpStyle->dwPadT = 3;
    lpStyle->fLineHeight = 1.3f;

    /*-----------------------------------------------*//* 3D˜g•\Ž¦F•Žš¶‹l‚ß -‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_3d_blk_left_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFF80;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* 3D˜g•\Ž¦F•Žš¶‹l‚ß -”ñ‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_3d_blk_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFFFF;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* 3D˜g•\Ž¦F•Žš¶‹l‚ß -”ñŠˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_3d_blk_left_disabled"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xE1D1C8;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* 3D˜g•\Ž¦F‰E‹l‚ß -‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_3d_blk_right_on"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFF80;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* 3D˜g•\Ž¦F‰E‹l‚ß -”ñ‘I‘ð */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_3d_blk_right_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xFFFFFF;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /* 3D˜g•\Ž¦F‰E‹l‚ß -”ñŠˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_3d_blk_right_disabled"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xE1D1C8;
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadR = 4;
    lpStyle->dwTextAlign = DT_RIGHT | DT_TOP;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_INSET;

    /*-----------------------------------------------*//* ŠpŠÛ”wŒiFŠD‰© -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_back_gyel_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xddd7d0;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0xe8e2dc;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    /*

    display: table-cell;
    clear: both;
    overflow: hidden;
    */

    /* –tF’ƒ -Á“”i”ñŠˆ« Á“”‚Æ“¯‚¶ƒfƒUƒCƒ“j */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_brn_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x5583BF;
    lpStyle->dwTextColor = 0xffffff;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x333333;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    lpStyle->sctBorder.dwBorderRadius = 5;
    lpStyle->vBoxShadow.resize(( std::size_t )2 );
    lpStyle->vBoxShadow[0] = SCT_BOX_SHADOW(( LONG )-2, ( LONG )-4, ( DWORD )2, ( DWORD )0x324c6f );
    lpStyle->vBoxShadow[1] = SCT_BOX_SHADOW(( LONG )2, ( LONG )4, ( DWORD )2, ( DWORD )0x96b6e0 );

    /* ƒ{ƒ^ƒ“‚Ì‰e‚ÌF */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["background_color_clear"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xff0000;                                         // Css make by manual

    /* ”wŒiFF”¼“§–¾ */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["background_color_translucent"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x8b6251 ;
    /*

    /* background-color:#f0ebef; */

    /* –tF“¶Šñ‚¹ -Á“”i”ñŠˆ« Á“”‚Æ“¯‚¶ƒfƒUƒCƒ“j */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_pink_l_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x5583BF;
    lpStyle->dwTextColor = 0xffffff;
    lpStyle->sctBorder.dwWidth = 1;
    lpStyle->sctBorder.dwColor = 0x333333;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    lpStyle->sctBorder.dwBorderRadius = 5;
    lpStyle->vBoxShadow.resize(( std::size_t )2 );
    lpStyle->vBoxShadow[0] = SCT_BOX_SHADOW(( LONG )-2, ( LONG )-4, ( DWORD )2, ( DWORD )0x324c6f );
    lpStyle->vBoxShadow[1] = SCT_BOX_SHADOW(( LONG )2, ( LONG )4, ( DWORD )2, ( DWORD )0x96b6e0 );

    /* ŒÅ’èF•Žšã‹l‚ß¶‹l‚ß -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_fix_blk_up_left_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0x000000;
    lpStyle->dwPadL = 4;
    lpStyle->fLineHeight = 1.2f /* em !important */ ;

    /* ”wŒiF’WŠDüŽ‡ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_back_lgry_line_purple_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xefebf0;
    lpStyle->sctBorder.dwWidth = 10;
    lpStyle->sctBorder.dwColor = 0xab7275;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* ”wŒiF’WŠDüÔ -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_back_lgry_line_red_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xefebf0;
    lpStyle->sctBorder.dwWidth = 10;
    lpStyle->sctBorder.dwColor = 0x1535b7;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /* ”wŒiFŠD‰©ü”Z‰© -Šˆ« */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["popup_back_gyel_line_dyel_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0xe3f0f2;
    lpStyle->sctBorder.dwWidth = 10;
    lpStyle->sctBorder.dwColor = 0x2fbfea;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;

    /*---------------------------------------------
  ƒGƒŠƒA•Ê•”•i’è‹`
-----------------------------------------------*//*---------------------------------------------
  •\Ž¦€–Ú
-----------------------------------------------*//* ŒÅ’èF”’Žš’W•”wŒi *//*.sts_idication_fix_wht_blk_off*/
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_fix_wht_lblk_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x323432;
    lpStyle->dwTextColor = 0xc6c9c7;
    lpStyle->dwPadT = 1;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;
    lpStyle->lpSctAsmBorder = new SCT_ASM_BORDER;
    lpStyle->lpSctAsmBorder->dwRadiusLT = 5;
    lpStyle->lpSctAsmBorder->dwRadiusRT = 5;
    lpStyle->lpSctAsmBorder->dwRadiusRB = 0;
    lpStyle->lpSctAsmBorder->dwRadiusLB = 0;
    lpStyle->dwFontWeight = FW_NORMAL;
    /*

    box-sizing: border-box;
    -webkit-box-sizing: border-box;
    display: inline-block; 
    */

    /* ŒÅ’èF”’ŽšÔ”wŒi *//*.sts_idication_fix_dokyujitsu_off*/
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_fix_wht_red_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwBkgColor = 0x0040c0;
    lpStyle->dwTextColor = 0xffffff;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;
    lpStyle->sctBorder.dwWidth = 2;
    lpStyle->sctBorder.dwColor = 0x404040;
    lpStyle->sctBorder.dwBorderStyle = CSS_BORDER_SOLID;
    lpStyle->vBoxShadow.resize(( std::size_t )4 );                                        // CSS make by manual
    lpStyle->vBoxShadow[0] = SCT_BOX_SHADOW((LONG)1, (LONG)1, (DWORD)0, (DWORD)0x00ffffff );
    lpStyle->vBoxShadow[1] = SCT_BOX_SHADOW((LONG)-1, (LONG)-1, (DWORD)0, (DWORD)0x00ffffff );
    lpStyle->vBoxShadow[2] = SCT_BOX_SHADOW((LONG)2, (LONG)3, (DWORD)3, (DWORD)0x00374195 );
    lpStyle->vBoxShadow[3] = SCT_BOX_SHADOW((LONG)-2, (LONG)-3, (DWORD)3, (DWORD)0x00374195 );
    lpStyle->dwFontWeight = FW_NORMAL;
    /*

    box-sizing: border-box;
    -webkit-box-sizing: border-box;
    */

    /* ŒÅ’èF”’Žš’†‰›‘µ‚¦ */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_fix_wht_c_off"] = lpStyle = new CCssLabel(); 
    lpStyle->dwTextColor = 0xffffff;
    lpStyle->dwPadL = 8;
    lpStyle->dwTextAlign = DT_CENTER | DT_TOP;
    lpStyle->dwFontWeight = FW_NORMAL;
    /*

    box-sizing: border-box;
    -webkit-box-sizing: border-box;
    */

    /* ƒAƒCƒRƒ“FIDŠÇ—ƒT[ƒo[ -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_idctl_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_id_green.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FIDŠÇ—ƒT[ƒo[ -Œx */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_idctl_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_id_yellow.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FIDŠÇ—ƒT[ƒo[ -ˆÙí */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_idctl_stsno3"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_id_red.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FIDŠÇ—ƒT[ƒo[ -‰w“s“xÝ’èã‚È‚µ */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_idctl_stsno4"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_blank.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F‰c‹ÆŠÇ—’[–– -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_eigyoctl_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_eitan_green.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F‰c‹ÆŠÇ—’[–– -ˆÙí */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_eigyoctl_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_eitan_red.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F‰c‹ÆŠÇ—’[–– -‰w“s“xÝ’èã‚È‚µ */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_eigyoctl_stsno3"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_blank.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F’è”­ƒT[ƒo -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_teihatsu_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_teihatsu_green.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F’è”­ƒT[ƒo -ˆÙí */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_teihatsu_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_teihatsu_red.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F’è”­ƒT[ƒo -‰w“s“xÝ’èã‚È‚µ */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_teihatsu_stsno3"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_blank.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F“Á‹}ƒT[ƒo -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_tokkyu_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_tokkyuu_green.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F“Á‹}ƒT[ƒo -ˆÙí */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_tokkyu_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_tokkyuu_red.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F“Á‹}ƒT[ƒo -‰w“s“xÝ’èã‚È‚µ */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_tokkyu_stsno3"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_blank.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F’÷Øƒf[ƒ^ -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_shimekiri_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_misou_off.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F’÷Øƒf[ƒ^ -ˆÙí */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_shimekiri_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_misou_on.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“Fƒ[ƒ‹Ž† -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_roll_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_rollpaper_off.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“Fƒ[ƒ‹Ž† -Œx */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_roll_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_rollpaper_nearE256.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“Fƒ[ƒ‹Ž† -ˆÙí */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_roll_stsno3"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_rollpaper_E256.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FIC”­s—pƒzƒbƒp -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_ic_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_hopper_ic_off.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FIC”­s—pƒzƒbƒp -Œx */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_ic_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_hopper_ic_yellow.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FIC”­s—pƒzƒbƒp -ˆÙí */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_ic_stsno3"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_hopper_ic_red.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FŽ¥‹C”­s—pƒzƒbƒp -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_pet_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_hopper_pet_off.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FŽ¥‹C”­s—pƒzƒbƒp -Œx */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_pet_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_hopper_pet_yellow.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FŽ¥‹C”­s—pƒzƒbƒp -ˆÙí */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_pet_stsno3"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_hopper_pet_red.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F’Þ‘K‹@‚P -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_tsurisen1_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_tsuri_2_off.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F’Þ‘K‹@‚P -Œx */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_tsurisen1_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_tsuri_1_yellow.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F’Þ‘K‹@‚P -ˆÙí */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_tsurisen1_stsno3"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_tsuri_1_red.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F’Þ‘K‹@‚P -Žg—p•s‰Â */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_tsurisen1_stsno4"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_shiyou.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F’Þ‘K‹@‚P -’P‘Ì */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_tsurisen1_stsno5"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_tantai.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F’Þ‘K‹@‚Q -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_tsurisen2_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_tsuri_2_off.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F’Þ‘K‹@‚Q -Œx */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_tsurisen2_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_tsuri_2_yellow.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F’Þ‘K‹@‚Q -ˆÙí */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_tsurisen2_stsno3"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_tsuri_2_red.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F’Þ‘K‹@‚Q -Žg—p•s‰Â */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_tsurisen2_stsno4"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_fuka.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F’Þ‘K‹@‚Q -“®ì’† */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_tsurisen2_stsno5"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_dousacyuu.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F‰^—pƒ‚[ƒh -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_unyo_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_blank.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F‰^—pƒ‚[ƒh -Œx */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_unyo_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_test_1.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F‰^—pƒ‚[ƒh -ˆÙí */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_unyo_stsno3"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_test_2.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F‰^—pƒ‚[ƒh -‘Ò‹@ */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_unyo_stsno4"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_test_3.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“Fƒ‚ƒoƒCƒ‹ƒgƒŒ[ -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_mobile_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_IC_Green.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“Fƒ‚ƒoƒCƒ‹ƒgƒŒ[ -Œx */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_mobile_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_IC_BLK256.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FIC‰^’À -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_ic_unchin_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_unchin_ic_on.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FIC‰^’À -Œx */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_ic_unchin_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_unchin_ic_off.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FŽ¥‹C¸ŽZ‰^’À -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_jikiseisan_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_unchin_seisan_on.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FŽ¥‹C¸ŽZ‰^’À -Œx */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_jikiseisan_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_unchin_seisan_off.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FŽ¥‹CŒ””„‰^’À -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_jikikenbai_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_unchin_kenbai_on.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FŽ¥‹CŒ””„‰^’À -Œx */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_jikikenbai_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_unchin_kenbai_off.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FŽ¥‹C‰üŽD‹@‰^’À -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_jikikaisatsu_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_blank2.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FŠé‰æŒ”ƒ}ƒXƒ^ -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_kikakuken_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_unchin_ki_on.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FŠé‰æŒ”ƒ}ƒXƒ^ -Œx */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_kikakuken_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_unchin_ki_off.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F•¨”Ìƒ}ƒXƒ^ -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_buppan_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_unchin_butsu_on.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“F•¨”Ìƒ}ƒXƒ^ -Œx */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_buppan_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_unchin_butsu_off.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FƒvƒƒOƒ‰ƒ€ -³í */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_program_stsno1"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_apl_white.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FƒvƒƒOƒ‰ƒ€ -Œx */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_program_stsno2"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_apl_off.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FƒvƒƒOƒ‰ƒ€ -ˆÙí */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_program_stsno3"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_apl_yellow.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

    /* ƒAƒCƒRƒ“FƒvƒƒOƒ‰ƒ€ -‘Ò‹@ */
    ////////////////////////////////////////////////////////////////////////// 
    m_mCssMap["sts_idication_icon_program_stsno4"] = lpStyle = new CCssLabel(); 
    lpStyle->sctIcon.sSourcePath = "resource\\image\\sts_idication\\lbl_apl_red.bmp";
    lpStyle->dwFontWeight = FW_NORMAL;

}

//////////////////////////////////////////////////////////////////////////
// Create all button Css
VOID CCssStore::CreateAllBtnCss()
{
    CreateCss_center_disp_btn_IC_disabled();
    CreateCss_center_disp_btn_IC_off();
    CreateCss_center_disp_btn_IC_on();
    CreateCss_center_disp_btn_brn_disabled();
    CreateCss_center_disp_btn_brn_off();
    CreateCss_center_disp_btn_bunkatsu_gry_disabled();
    CreateCss_center_disp_btn_bunkatsu_gry_off();
    CreateCss_center_disp_btn_clear_c();
    CreateCss_center_disp_btn_darkblugre_disabled();
    CreateCss_center_disp_btn_darkblugre_off();
    CreateCss_center_disp_btn_darkblugre_t_disabled();
    CreateCss_center_disp_btn_darkblugre_t_off();
    CreateCss_center_disp_btn_dblu_disabled();
    CreateCss_center_disp_btn_dblu_off();
    CreateCss_center_disp_btn_dblugre_disabled();
    CreateCss_center_disp_btn_dblugre_off();
    CreateCss_center_disp_btn_dblugreugre_gry_disabled();
    CreateCss_center_disp_btn_dblugreugre_gry_off();
    CreateCss_center_disp_btn_dpink_disabled();
    CreateCss_center_disp_btn_dpink_off();
    CreateCss_center_disp_btn_dsky_disabled();
    CreateCss_center_disp_btn_dsky_off();
    CreateCss_center_disp_btn_gdbl_disabled();
    CreateCss_center_disp_btn_gdbl_off();
    CreateCss_center_disp_btn_ggrnb_mae_disabled();
    CreateCss_center_disp_btn_ggrnb_mae_off();
    CreateCss_center_disp_btn_ggrnb_tsugi_disabled();
    CreateCss_center_disp_btn_ggrnb_tsugi_off();
    CreateCss_center_disp_btn_gpink_disabled();
    CreateCss_center_disp_btn_gpink_off();
    CreateCss_center_disp_btn_green_disabled();
    CreateCss_center_disp_btn_green_off();
    CreateCss_center_disp_btn_grn_printer_disabled();
    CreateCss_center_disp_btn_grn_printer_off();
    CreateCss_center_disp_btn_grnb_disabled();
    CreateCss_center_disp_btn_grnb_off();
    CreateCss_center_disp_btn_ic_teiki_disabled();
    CreateCss_center_disp_btn_ic_teiki_on();
    CreateCss_center_disp_btn_jiki_joushaken_disabled();
    CreateCss_center_disp_btn_jiki_joushaken_on();
    CreateCss_center_disp_btn_jiki_teiki_disabled();
    CreateCss_center_disp_btn_jiki_teiki_on();
    CreateCss_center_disp_btn_lgrn_disabled();
    CreateCss_center_disp_btn_lgrn_grn_disabled();
    CreateCss_center_disp_btn_lgrn_grn_off();
    CreateCss_center_disp_btn_lgrn_off();
    CreateCss_center_disp_btn_lgry_disabled();
    CreateCss_center_disp_btn_lgry_off();
    CreateCss_center_disp_btn_lgry_on();
    CreateCss_center_disp_btn_lgylg_disabled();
    CreateCss_center_disp_btn_lgylg_off();
    CreateCss_center_disp_btn_line2_ikebukuro_disabled();
    CreateCss_center_disp_btn_line2_ikebukuro_off();
    CreateCss_center_disp_btn_line2_kokubunji_disabled();
    CreateCss_center_disp_btn_line2_kokubunji_off();
    CreateCss_center_disp_btn_line2_sayama_disabled();
    CreateCss_center_disp_btn_line2_sayama_off();
    CreateCss_center_disp_btn_line2_tamako_disabled();
    CreateCss_center_disp_btn_line2_tamako_off();
    CreateCss_center_disp_btn_line2_toyo_sbyuraku_disabled();
    CreateCss_center_disp_btn_line2_toyo_sbyuraku_off();
    CreateCss_center_disp_btn_line2_yamaguchi_disabled();
    CreateCss_center_disp_btn_line2_yamaguchi_off();
    CreateCss_center_disp_btn_line_asakusa_disabled();
    CreateCss_center_disp_btn_line_asakusa_off();
    CreateCss_center_disp_btn_line_buppan_1_off();
    CreateCss_center_disp_btn_line_buppan_2_off();
    CreateCss_center_disp_btn_line_buppan_3_off();
    CreateCss_center_disp_btn_line_buppan_4_off();
    CreateCss_center_disp_btn_line_buppan_5_off();
    CreateCss_center_disp_btn_line_buppan_6_off();
    CreateCss_center_disp_btn_line_buppan_7_off();
    CreateCss_center_disp_btn_line_buppan_8_off();
    CreateCss_center_disp_btn_line_buppan_9_off();
    CreateCss_center_disp_btn_line_chiyoda_disabled();
    CreateCss_center_disp_btn_line_chiyoda_off();
    CreateCss_center_disp_btn_line_fukutoshin_disabled();
    CreateCss_center_disp_btn_line_fukutoshin_off();
    CreateCss_center_disp_btn_line_ginza_disabled();
    CreateCss_center_disp_btn_line_ginza_off();
    CreateCss_center_disp_btn_line_hanzoumon_disabled();
    CreateCss_center_disp_btn_line_hanzoumon_off();
    CreateCss_center_disp_btn_line_hibiya_disabled();
    CreateCss_center_disp_btn_line_hibiya_off();
    CreateCss_center_disp_btn_line_lblu_disabled();
    CreateCss_center_disp_btn_line_lblu_off();
    CreateCss_center_disp_btn_line_marunouti_disabled();
    CreateCss_center_disp_btn_line_marunouti_off();
    CreateCss_center_disp_btn_line_mita_disabled();
    CreateCss_center_disp_btn_line_mita_off();
    CreateCss_center_disp_btn_line_nanboku_disabled();
    CreateCss_center_disp_btn_line_nanboku_off();
    CreateCss_center_disp_btn_line_oedo_disabled();
    CreateCss_center_disp_btn_line_oedo_off();
    CreateCss_center_disp_btn_line_yurakucyou_disabled();
    CreateCss_center_disp_btn_line_yurakucyou_off();
    CreateCss_center_disp_btn_lyel_disabled();
    CreateCss_center_disp_btn_lyel_off();
    CreateCss_center_disp_btn_mae_tri_off();
    CreateCss_center_disp_btn_meisai_disabled();
    CreateCss_center_disp_btn_meisai_on();
    CreateCss_center_disp_btn_mobile_disabled();
    CreateCss_center_disp_btn_mobile_off();
    CreateCss_center_disp_btn_mobile_on();
    CreateCss_center_disp_btn_pink_disabled();
    CreateCss_center_disp_btn_pink_off();
    CreateCss_center_disp_btn_pink_off2();
    CreateCss_center_disp_btn_r_rpurple_disabled();
    CreateCss_center_disp_btn_r_rpurple_off();
    CreateCss_center_disp_btn_red_blk_disabled();
    CreateCss_center_disp_btn_red_blk_off();
    CreateCss_center_disp_btn_rpurple_dengen_disabled();
    CreateCss_center_disp_btn_rpurple_dengen_off();
    CreateCss_center_disp_btn_rpurple_disabled();
    CreateCss_center_disp_btn_rpurple_off();
    CreateCss_center_disp_btn_teiki_untin_serch_disabled();
    CreateCss_center_disp_btn_teiki_untin_serch_on();
    CreateCss_center_disp_btn_tri_left_disabled();
    CreateCss_center_disp_btn_tri_left_off();
    CreateCss_center_disp_btn_tri_lpurple_disabled();
    CreateCss_center_disp_btn_tri_lpurple_off();
    CreateCss_center_disp_btn_tri_right_disabled();
    CreateCss_center_disp_btn_tri_right_off();
    CreateCss_center_disp_btn_tsugi_tri_off();
    CreateCss_center_disp_btn_vio_disabled();
    CreateCss_center_disp_btn_vio_off();
    CreateCss_const_btn_btn_bunkatsu_gry_disabled();
    CreateCss_const_btn_btn_bunkatsu_gry_off();
    CreateCss_const_btn_btn_dblu_disabled();
    CreateCss_const_btn_btn_dblu_mark_disabled();
    CreateCss_const_btn_btn_dblu_mark_off();
    CreateCss_const_btn_btn_dblu_off();
    CreateCss_const_btn_btn_ggrnb_mae_disabled();
    CreateCss_const_btn_btn_ggrnb_mae_off();
    CreateCss_const_btn_btn_ggrnb_tsugi_disabled();
    CreateCss_const_btn_btn_ggrnb_tsugi_off();
    CreateCss_const_btn_btn_grnb_disabled();
    CreateCss_const_btn_btn_grnb_off();
    CreateCss_const_btn_btn_gry_disabled();
    CreateCss_const_btn_btn_gry_off();
    CreateCss_const_btn_btn_gry_t_disabled();
    CreateCss_const_btn_btn_gry_t_off();
    CreateCss_const_btn_btn_gvg_disabled();
    CreateCss_const_btn_btn_gvg_off();
    CreateCss_const_btn_btn_gyg_disabled();
    CreateCss_const_btn_btn_gyg_off();
    CreateCss_const_btn_btn_lgrn_disabled();
    CreateCss_const_btn_btn_lgrn_off();
    CreateCss_const_btn_btn_lyel_disabled();
    CreateCss_const_btn_btn_lyel_off();
    CreateCss_const_btn_btn_rpurple_disabled();
    CreateCss_const_btn_btn_rpurple_off();
    CreateCss_const_btn_btn_tri_lpurple_disabled();
    CreateCss_const_btn_btn_tri_lpurple_off();
    CreateCss_disabled_yajirushi_next();
    CreateCss_disabled_yajirushi_pre();
    CreateCss_disp_btn_db_y_db_disabled();
    CreateCss_disp_btn_db_y_db_off();
    CreateCss_disp_btn_db_y_db_t_disabled();
    CreateCss_disp_btn_db_y_db_t_off();
    CreateCss_disp_btn_db_y_gry_disabled();
    CreateCss_disp_btn_db_y_gry_off();
    CreateCss_disp_btn_db_y_gry_t_disabled();
    CreateCss_disp_btn_db_y_gry_t_off();
    CreateCss_disp_btn_g_y_g_disabled();
    CreateCss_disp_btn_g_y_g_off();
    CreateCss_disp_btn_g_y_g_t_disabled();
    CreateCss_disp_btn_g_y_g_t_off();
    CreateCss_disp_btn_g_y_gry_disabled();
    CreateCss_disp_btn_g_y_gry_off();
    CreateCss_disp_btn_g_y_gry_t_disabled();
    CreateCss_disp_btn_g_y_gry_t_off();
    CreateCss_off_light_yajirushi_next();
    CreateCss_off_light_yajirushi_pre();
    CreateCss_on_light_yajirushi_next();
    CreateCss_on_light_yajirushi_pre();
    CreateCss_operation_btn_brn_disabled();
    CreateCss_operation_btn_brn_off();
    CreateCss_operation_btn_dblugre_disabled();
    CreateCss_operation_btn_dblugre_off();
    CreateCss_operation_btn_grn_disabled();
    CreateCss_operation_btn_grn_off();
    CreateCss_operation_btn_grn_printer_disabled();
    CreateCss_operation_btn_grn_printer_off();
    CreateCss_operation_btn_grnb_disabled();
    CreateCss_operation_btn_grnb_off();
    CreateCss_operation_btn_lblu_disabled();
    CreateCss_operation_btn_lblu_mono_disabled();
    CreateCss_operation_btn_lblu_mono_off();
    CreateCss_operation_btn_lblu_off();
    CreateCss_operation_btn_lgrn_disabled();
    CreateCss_operation_btn_lgrn_off();
    CreateCss_operation_btn_lgry_disabled();
    CreateCss_operation_btn_lgry_mono_disabled();
    CreateCss_operation_btn_lgry_mono_off();
    CreateCss_operation_btn_lgry_mono_on();
    CreateCss_operation_btn_lgry_off();
    CreateCss_operation_btn_lgry_on();
    CreateCss_operation_btn_lgry_page_disabled();
    CreateCss_operation_btn_lgry_page_off();
    CreateCss_operation_btn_lgry_page_on();
    CreateCss_operation_btn_lgydg_left_maru_disabled();
    CreateCss_operation_btn_lgydg_left_maru_off();
    CreateCss_operation_btn_lgydg_right_maru_disabled();
    CreateCss_operation_btn_lgydg_right_maru_off();
    CreateCss_operation_btn_lgylg_page_disabled();
    CreateCss_operation_btn_lgylg_page_off();
    CreateCss_operation_btn_lgylg_page_on();
    CreateCss_operation_btn_line2_ikebukuro_disabled();
    CreateCss_operation_btn_line2_ikebukuro_off();
    CreateCss_operation_btn_line2_kokubunji_disabled();
    CreateCss_operation_btn_line2_kokubunji_off();
    CreateCss_operation_btn_line2_sayama_disabled();
    CreateCss_operation_btn_line2_sayama_off();
    CreateCss_operation_btn_line2_tamako_disabled();
    CreateCss_operation_btn_line2_tamako_off();
    CreateCss_operation_btn_line2_toyo_sbyuraku_disabled();
    CreateCss_operation_btn_line2_toyo_sbyuraku_off();
    CreateCss_operation_btn_line2_yamaguchi_disabled();
    CreateCss_operation_btn_line2_yamaguchi_off();
    CreateCss_operation_btn_line_asakusa_disabled();
    CreateCss_operation_btn_line_asakusa_off();
    CreateCss_operation_btn_line_cb_disabled();
    CreateCss_operation_btn_line_cb_off();
    CreateCss_operation_btn_line_cb_on();
    CreateCss_operation_btn_line_chiyoda_disabled();
    CreateCss_operation_btn_line_chiyoda_off();
    CreateCss_operation_btn_line_fukutoshin_disabled();
    CreateCss_operation_btn_line_fukutoshin_off();
    CreateCss_operation_btn_line_ginza_disabled();
    CreateCss_operation_btn_line_ginza_off();
    CreateCss_operation_btn_line_hanzoumon_disabled();
    CreateCss_operation_btn_line_hanzoumon_off();
    CreateCss_operation_btn_line_hibiya_disabled();
    CreateCss_operation_btn_line_hibiya_off();
    CreateCss_operation_btn_line_jr_disabled();
    CreateCss_operation_btn_line_jr_off();
    CreateCss_operation_btn_line_jr_on();
    CreateCss_operation_btn_line_kk_disabled();
    CreateCss_operation_btn_line_kk_off();
    CreateCss_operation_btn_line_kk_on();
    CreateCss_operation_btn_line_ko_disabled();
    CreateCss_operation_btn_line_ko_off();
    CreateCss_operation_btn_line_ko_on();
    CreateCss_operation_btn_line_ks_disabled();
    CreateCss_operation_btn_line_ks_off();
    CreateCss_operation_btn_line_ks_on();
    CreateCss_operation_btn_line_marunouti_disabled();
    CreateCss_operation_btn_line_marunouti_off();
    CreateCss_operation_btn_line_mita_disabled();
    CreateCss_operation_btn_line_mita_off();
    CreateCss_operation_btn_line_mx_disabled();
    CreateCss_operation_btn_line_mx_off();
    CreateCss_operation_btn_line_mx_on();
    CreateCss_operation_btn_line_nanboku_disabled();
    CreateCss_operation_btn_line_nanboku_off();
    CreateCss_operation_btn_line_od_disabled();
    CreateCss_operation_btn_line_od_off();
    CreateCss_operation_btn_line_od_on();
    CreateCss_operation_btn_line_oedo_disabled();
    CreateCss_operation_btn_line_oedo_off();
    CreateCss_operation_btn_line_rk_disabled();
    CreateCss_operation_btn_line_rk_off();
    CreateCss_operation_btn_line_rk_on();
    CreateCss_operation_btn_line_sb_disabled();
    CreateCss_operation_btn_line_sb_off();
    CreateCss_operation_btn_line_sb_on();
    CreateCss_operation_btn_line_tb_disabled();
    CreateCss_operation_btn_line_tb_off();
    CreateCss_operation_btn_line_tb_on();
    CreateCss_operation_btn_line_te_disabled();
    CreateCss_operation_btn_line_te_off();
    CreateCss_operation_btn_line_te_on();
    CreateCss_operation_btn_line_tk_disabled();
    CreateCss_operation_btn_line_tk_off();
    CreateCss_operation_btn_line_tk_on();
    CreateCss_operation_btn_line_tl_disabled();
    CreateCss_operation_btn_line_tl_off();
    CreateCss_operation_btn_line_tl_on();
    CreateCss_operation_btn_line_tm_disabled();
    CreateCss_operation_btn_line_tm_off();
    CreateCss_operation_btn_line_tm_on();
    CreateCss_operation_btn_line_tozai_disabled();
    CreateCss_operation_btn_line_tozai_off();
    CreateCss_operation_btn_line_tu_disabled();
    CreateCss_operation_btn_line_tu_off();
    CreateCss_operation_btn_line_tu_on();
    CreateCss_operation_btn_line_tx_disabled();
    CreateCss_operation_btn_line_tx_off();
    CreateCss_operation_btn_line_tx_on();
    CreateCss_operation_btn_line_yk_disabled();
    CreateCss_operation_btn_line_yk_off();
    CreateCss_operation_btn_line_yk_on();
    CreateCss_operation_btn_line_yu_disabled();
    CreateCss_operation_btn_line_yu_off();
    CreateCss_operation_btn_line_yu_on();
    CreateCss_operation_btn_line_yurakucyou_disabled();
    CreateCss_operation_btn_line_yurakucyou_off();
    CreateCss_operation_btn_lyel_disabled();
    CreateCss_operation_btn_lyel_off();
    CreateCss_operation_btn_red_blk_disabled();
    CreateCss_operation_btn_red_blk_off();
    CreateCss_operation_btn_tri_left_disabled();
    CreateCss_operation_btn_tri_left_off();
    CreateCss_operation_btn_tri_leftbtn_disabled();
    CreateCss_operation_btn_tri_leftbtn_off();
    CreateCss_operation_btn_tri_lpurple_disabled();
    CreateCss_operation_btn_tri_lpurple_off();
    CreateCss_operation_btn_tri_right_disabled();
    CreateCss_operation_btn_tri_right_off();
    CreateCss_operation_btn_tri_rightbtn_disabled();
    CreateCss_operation_btn_tri_rightbtn_off();
    CreateCss_operation_btn_yel_disabled();
    CreateCss_operation_btn_yel_mono_disabled();
    CreateCss_operation_btn_yel_mono_off();
    CreateCss_operation_btn_yel_off();
    CreateCss_popup_btn_brn_disabled();
    CreateCss_popup_btn_brn_off();
    CreateCss_popup_btn_dblu_disabled();
    CreateCss_popup_btn_dblu_off();
    CreateCss_popup_btn_dblugre_disabled();
    CreateCss_popup_btn_dblugre_off();
    CreateCss_popup_btn_drd_disabled();
    CreateCss_popup_btn_drd_off();
    CreateCss_popup_btn_gpink_disabled();
    CreateCss_popup_btn_gpink_l_disabled();
    CreateCss_popup_btn_gpink_l_off();
    CreateCss_popup_btn_gpink_off();
    CreateCss_popup_btn_green_disabled();
    CreateCss_popup_btn_green_off();
    CreateCss_popup_btn_grnb_disabled();
    CreateCss_popup_btn_grnb_off();
    CreateCss_popup_btn_gry_disabled();
    CreateCss_popup_btn_gry_l_disabled();
    CreateCss_popup_btn_gry_l_off();
    CreateCss_popup_btn_gry_off();
    CreateCss_popup_btn_gyg_disabled();
    CreateCss_popup_btn_gyg_off();
    CreateCss_popup_btn_lgrn_disabled();
    CreateCss_popup_btn_lgrn_grn_disabled();
    CreateCss_popup_btn_lgrn_grn_off();
    CreateCss_popup_btn_lgrn_off();
    CreateCss_popup_btn_mae_disabled();
    CreateCss_popup_btn_mae_off();
    CreateCss_popup_btn_pink_l_disabled();
    CreateCss_popup_btn_pink_l_off();
    CreateCss_popup_btn_rpurple_dengen_disabled();
    CreateCss_popup_btn_rpurple_dengen_off();
    CreateCss_popup_btn_tri_lpurple_disabled();
    CreateCss_popup_btn_tri_lpurple_off();
    CreateCss_popup_btn_tsugi_disabled();
    CreateCss_popup_btn_tsugi_off();
    CreateCss_popup_btn_vio_disabled();
    CreateCss_popup_btn_vio_off();
    CreateCss_center_disp_btn_line_kikaku_off();
    CreateCss_center_disp_btn_line_kikaku_off2();
    CreateCss_center_disp_btn_line_kikaku_off3();
    CreateCss_center_disp_btn_line_kikaku_off4();
    CreateCss_center_disp_btn_line_kikaku_off5();
    CreateCss_center_disp_btn_line_kikaku_off6();
    CreateCss_center_disp_btn_line_kikaku_off7();
    CreateCss_center_disp_btn_line_kikaku_off8();
    CreateCss_center_disp_btn_line_kikaku_off9();
    CreateCss_center_disp_btn_line_kikaku_off10();
    // Start ThietNP 20150727: Update CSS V20.24
    CreateCss_center_disp_btn_left_lgrn_off();
    CreateCss_center_disp_btn_left_lgrn_disabled();
    CreateCss_center_disp_btn_line_metro_off();
    CreateCss_center_disp_btn_line_metro_off2();
    CreateCss_center_disp_btn_line_metro_off3();
    CreateCss_center_disp_btn_line_metro_off4();
    // End ThietNP 20150727: Update CSS V20.24
    // Start ThietNP 20150818: Update CSS version 20.32a
    CreateCss_const_btn_btn_dsky_off();
    CreateCss_const_btn_btn_dsky_disabled();
    // End ThietNP 20150818: Update CSS version 20.32a
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_IC_disabled
VOID CCssStore::CreateCss_center_disp_btn_IC_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_IC_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x996532;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\btn_gyoumu_ic_disable.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_IC_off
VOID CCssStore::CreateCss_center_disp_btn_IC_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_IC_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x00ccff;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\btn_gyoumu_ic_notselect.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_IC_on
VOID CCssStore::CreateCss_center_disp_btn_IC_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_IC_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x00ccff;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\btn_gyoumu_ic_select.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_brn_disabled
VOID CCssStore::CreateCss_center_disp_btn_brn_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_brn_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x83a3cd;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x5583bf;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x3a5c88 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x7ca1d3 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_brn_off
VOID CCssStore::CreateCss_center_disp_btn_brn_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_brn_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x5583bf;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x324c6f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x96b6e0 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xd6dbe0;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x406390;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x748caa;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x263b55;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_bunkatsu_gry_disabled
VOID CCssStore::CreateCss_center_disp_btn_bunkatsu_gry_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_bunkatsu_gry_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 100;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xb5b5b5;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_bunkatsu_gry_off
VOID CCssStore::CreateCss_center_disp_btn_bunkatsu_gry_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_bunkatsu_gry_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 100;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x808080;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9a9a9a;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x5f5f5f;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x8e8e8e;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_clear_c
VOID CCssStore::CreateCss_center_disp_btn_clear_c()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_clear_c"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_darkblugre_disabled
VOID CCssStore::CreateCss_center_disp_btn_darkblugre_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_darkblugre_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xb79c7d;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xab8a63;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x968f87;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x705a3e );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xc9b093 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_darkblugre_off
VOID CCssStore::CreateCss_center_disp_btn_darkblugre_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_darkblugre_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xf4f6f9;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x916b39;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x3e2d19 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xc7ae9a );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xe0ddd9;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x6d512b;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x988772;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x382915;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwTextColor            = ( DWORD ) 0xaf9573;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0x8e6c39;
    lpDisableBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x594123;
    lpDisableBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xb39976;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_darkblugre_t_disabled
VOID CCssStore::CreateCss_center_disp_btn_darkblugre_t_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_darkblugre_t_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xb79c7d;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xab8a63;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.2f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 100;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x968f87;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x705a3e );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xc9b093 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_darkblugre_t_off
VOID CCssStore::CreateCss_center_disp_btn_darkblugre_t_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_darkblugre_t_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xf4f6f9;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x916b39;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.2f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 100;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x3e2d19 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xc7ae9a );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xe0ddd9;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x6d512b;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x988772;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x382915;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwTextColor            = ( DWORD ) 0xaf9573;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0x8e6c39;
    lpDisableBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x594123;
    lpDisableBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xb39976;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_dblu_disabled
VOID CCssStore::CreateCss_center_disp_btn_dblu_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_dblu_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xc8a292;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xb9826c;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x67473b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xd4ae9f );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_dblu_off
VOID CCssStore::CreateCss_center_disp_btn_dblu_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_dblu_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xeeeeed;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xb9826c;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b4b3f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xd7b1a2 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xe4e0de;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x8b6251;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xa3877c;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x553c31;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_dblugre_disabled
VOID CCssStore::CreateCss_center_disp_btn_dblugre_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_dblugre_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xc6ac81;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xa7803d;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x664e25 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xc5ad85 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_dblugre_off
VOID CCssStore::CreateCss_center_disp_btn_dblugre_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_dblugre_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xa7803d;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x684d1f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xb59866 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xe9e4db;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x7e602e;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x897451;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x473413;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_dblugreugre_gry_disabled
VOID CCssStore::CreateCss_center_disp_btn_dblugreugre_gry_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_dblugreugre_gry_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xdcd4cd;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0xe2dcd6;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x9d9792 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe4ded9 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_dblugreugre_gry_off
VOID CCssStore::CreateCss_center_disp_btn_dblugreugre_gry_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_dblugreugre_gry_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x916b39;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x584123 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xa0896a );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x808080;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x6d512b;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x8a7458;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x342412;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_dpink_disabled
VOID CCssStore::CreateCss_center_disp_btn_dpink_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_dpink_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x937dae;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6c5b81 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xab99c1 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_dpink_off
VOID CCssStore::CreateCss_center_disp_btn_dpink_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_dpink_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x937dae;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x5a4d6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xb9a9cc );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x6f5e83;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x867895;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x524560;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_dsky_disabled
VOID CCssStore::CreateCss_center_disp_btn_dsky_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_dsky_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xd4b576;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xbd8e2f;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6f5b30 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xb19a6c );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_dsky_off
VOID CCssStore::CreateCss_center_disp_btn_dsky_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_dsky_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xbd8e2f;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x503f1b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xd8ba7b );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x8e6b23;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x89795b;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x3e3015;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_gdbl_disabled
VOID CCssStore::CreateCss_center_disp_btn_gdbl_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_gdbl_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xbda68b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xab8a63;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x705a3e );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xc9b093 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_gdbl_off
VOID CCssStore::CreateCss_center_disp_btn_gdbl_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_gdbl_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xe5e4e3;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xab8a63;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x544430 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdbc8b1 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xd0c9c2;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x81684b;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xa59584;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x483a29;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_ggrnb_mae_disabled
VOID CCssStore::CreateCss_center_disp_btn_ggrnb_mae_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_ggrnb_mae_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa2a29c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG ) -6, ( DWORD )  4, ( DWORD ) 0x9e9e95 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG )  6, ( DWORD )  2, ( DWORD ) 0xe4e4db );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\prev_yajirushi_disabled.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 19;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HRIGHT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_ggrnb_mae_off
VOID CCssStore::CreateCss_center_disp_btn_ggrnb_mae_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_ggrnb_mae_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xdbdad0;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x4d4e4c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe7e5dd );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\prev_yajirushi.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 19;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HRIGHT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x333333;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x979781;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xa4a595;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x606052;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_ggrnb_tsugi_disabled
VOID CCssStore::CreateCss_center_disp_btn_ggrnb_tsugi_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_ggrnb_tsugi_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa2a29c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG ) -6, ( DWORD )  4, ( DWORD ) 0x9e9e95 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG )  6, ( DWORD )  2, ( DWORD ) 0xe4e4db );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\next_yajirushi_disabled.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 19;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HRIGHT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_ggrnb_tsugi_off
VOID CCssStore::CreateCss_center_disp_btn_ggrnb_tsugi_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_ggrnb_tsugi_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xdbdad0;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x4d4e4c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe7e5dd );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\next_yajirushi.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 19;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HRIGHT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x333333;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x979781;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xa4a595;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x606052;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_gpink_disabled
VOID CCssStore::CreateCss_center_disp_btn_gpink_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_gpink_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x868194;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc3b8da;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6c6679 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe0d9ef );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_gpink_off
VOID CCssStore::CreateCss_center_disp_btn_gpink_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_gpink_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x333333;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc3b8da;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x716b7f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe5dff5 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x363637;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x938ba4;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xaba6b8;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x5f596a;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0xb9826c;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_green_disabled
VOID CCssStore::CreateCss_center_disp_btn_green_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_green_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xcaca97;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xafaf61;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0xafaf61;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x828245 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xc3c380 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_green_off
VOID CCssStore::CreateCss_center_disp_btn_green_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_green_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x8fccaa;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x486d59 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xb5dec9 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xe4e4d7;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x848449;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x98986e;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x53532e;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0xafaf61;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_grn_printer_disabled
VOID CCssStore::CreateCss_center_disp_btn_grn_printer_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_grn_printer_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xbec793;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xa0ae62;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x505346;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x5f6838 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xbfca90 );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\printer_disabled.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 40;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_grn_printer_off
VOID CCssStore::CreateCss_center_disp_btn_grn_printer_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_grn_printer_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xa0ae62;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x5e673a );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xbcc690 );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\printer_up.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 40;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xe5e7dc;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x78834a;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x3e4038;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x939a71;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x4f5730;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->sctBorder.dwColor      = ( DWORD ) 0xbcc690;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_grnb_disabled
VOID CCssStore::CreateCss_center_disp_btn_grnb_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_grnb_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xcaca97;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xafaf61;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0xafaf61;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x828245 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xc3c380 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_grnb_off
VOID CCssStore::CreateCss_center_disp_btn_grnb_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_grnb_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xafaf61;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x242420 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xcdcd9d );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xe4e4d7;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x848449;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x98986e;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x53532e;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_ic_teiki_disabled
VOID CCssStore::CreateCss_center_disp_btn_ic_teiki_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_ic_teiki_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\ic_teiki_disable.jpg";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_ic_teiki_on
VOID CCssStore::CreateCss_center_disp_btn_ic_teiki_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_ic_teiki_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\btn_ic_teiki_ken.bmp";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_jiki_joushaken_disabled
VOID CCssStore::CreateCss_center_disp_btn_jiki_joushaken_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_jiki_joushaken_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x00ccff;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\btn_gyoumu_ziki_disable.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_jiki_joushaken_on
VOID CCssStore::CreateCss_center_disp_btn_jiki_joushaken_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_jiki_joushaken_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x00ccff;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\btn_gyoumu_ziki_select.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;


    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_jiki_teiki_disabled
VOID CCssStore::CreateCss_center_disp_btn_jiki_teiki_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_jiki_teiki_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\jiki_teiki_disable.jpg";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_jiki_teiki_on
VOID CCssStore::CreateCss_center_disp_btn_jiki_teiki_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_jiki_teiki_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\btn_jiki_teiki_ken.bmp";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_lgrn_disabled
VOID CCssStore::CreateCss_center_disp_btn_lgrn_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_lgrn_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x9b9b8b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc6ceb5;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x747c6c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xdfd6cf );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_lgrn_grn_disabled
VOID CCssStore::CreateCss_center_disp_btn_lgrn_grn_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_lgrn_grn_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x9b9b8b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc6ceb5;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 10;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x747c6c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xdfd6cf );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_lgrn_grn_off
VOID CCssStore::CreateCss_center_disp_btn_lgrn_grn_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_lgrn_grn_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4e4f2d;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc9c9ab;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 10;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x635d4a );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xdbddc9 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9c9c8c;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x7e8473;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x6a716a;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_lgrn_off
VOID CCssStore::CreateCss_center_disp_btn_lgrn_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_lgrn_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc9c9ab;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x635d4a );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xdbddc9 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9c9c8c;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x7e8473;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x6a716a;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_lgry_disabled
VOID CCssStore::CreateCss_center_disp_btn_lgry_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_lgry_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x9b9b9b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xcecece;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_lgry_off
VOID CCssStore::CreateCss_center_disp_btn_lgry_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_lgry_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x262626;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xcecece;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9a9a9a;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x8e8e8e;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x5f5f5f;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_lgry_on
VOID CCssStore::CreateCss_center_disp_btn_lgry_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_lgry_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x262626;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x9a9a9a;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x8e8e8e );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x5f5f5f );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xcecece;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x333333;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x6b6b6b;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xdedede;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_lgylg_disabled
VOID CCssStore::CreateCss_center_disp_btn_lgylg_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_lgylg_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa2a29c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG ) -6, ( DWORD )  4, ( DWORD ) 0x9e9e95 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG )  6, ( DWORD )  2, ( DWORD ) 0xe4e4db );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_lgylg_off
VOID CCssStore::CreateCss_center_disp_btn_lgylg_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_lgylg_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xdbdad0;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x4d4e4c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe7e5dd );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line2_ikebukuro_disabled
VOID CCssStore::CreateCss_center_disp_btn_line2_ikebukuro_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line2_ikebukuro_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x88b3db;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line2_ikebukuro_off
VOID CCssStore::CreateCss_center_disp_btn_line2_ikebukuro_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line2_ikebukuro_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x007aee;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line2_kokubunji_disabled
VOID CCssStore::CreateCss_center_disp_btn_line2_kokubunji_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line2_kokubunji_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9bc288;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line2_kokubunji_off
VOID CCssStore::CreateCss_center_disp_btn_line2_kokubunji_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line2_kokubunji_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x4bab1a;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line2_sayama_disabled
VOID CCssStore::CreateCss_center_disp_btn_line2_sayama_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line2_sayama_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xc9bf7d;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line2_sayama_off
VOID CCssStore::CreateCss_center_disp_btn_line2_sayama_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line2_sayama_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xbea500;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line2_tamako_disabled
VOID CCssStore::CreateCss_center_disp_btn_line2_tamako_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line2_tamako_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x68c0e4;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line2_tamako_off
VOID CCssStore::CreateCss_center_disp_btn_line2_tamako_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line2_tamako_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x00aff6;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line2_toyo_sbyuraku_disabled
VOID CCssStore::CreateCss_center_disp_btn_line2_toyo_sbyuraku_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line2_toyo_sbyuraku_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line2_toyo_sbyuraku_off
VOID CCssStore::CreateCss_center_disp_btn_line2_toyo_sbyuraku_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line2_toyo_sbyuraku_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;

    lpOffBtn->lpSctLine->lpGradientColor = new SCT_COLOR_GRADIENT();        // Css make by manual
    lpOffBtn->lpSctLine->lpGradientColor->dwFstClr = 0x0079ef;
    lpOffBtn->lpSctLine->lpGradientColor->dwSndClr = 0xb57f9c;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line2_yamaguchi_disabled
VOID CCssStore::CreateCss_center_disp_btn_line2_yamaguchi_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line2_yamaguchi_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9fa3d8;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line2_yamaguchi_off
VOID CCssStore::CreateCss_center_disp_btn_line2_yamaguchi_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line2_yamaguchi_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x3840da;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_asakusa_disabled
VOID CCssStore::CreateCss_center_disp_btn_line_asakusa_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_asakusa_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0xacacac );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_asakusa_off
VOID CCssStore::CreateCss_center_disp_btn_line_asakusa_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_asakusa_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x6c71f2;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_buppan_1_off
VOID CCssStore::CreateCss_center_disp_btn_line_buppan_1_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_buppan_1_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xfbfbfb;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_buppan_2_off
VOID CCssStore::CreateCss_center_disp_btn_line_buppan_2_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_buppan_2_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x33ffff;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_buppan_3_off
VOID CCssStore::CreateCss_center_disp_btn_line_buppan_3_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_buppan_3_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x1c9019;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_buppan_4_off
VOID CCssStore::CreateCss_center_disp_btn_line_buppan_4_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_buppan_4_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x848101;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_buppan_5_off
VOID CCssStore::CreateCss_center_disp_btn_line_buppan_5_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_buppan_5_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xda5101;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_buppan_6_off
VOID CCssStore::CreateCss_center_disp_btn_line_buppan_6_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_buppan_6_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xffcb27;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_buppan_7_off
VOID CCssStore::CreateCss_center_disp_btn_line_buppan_7_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_buppan_7_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x2128d1;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_buppan_8_off
VOID CCssStore::CreateCss_center_disp_btn_line_buppan_8_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_buppan_8_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x8e06d8;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_buppan_9_off
VOID CCssStore::CreateCss_center_disp_btn_line_buppan_9_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_buppan_9_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x009df4;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_chiyoda_disabled
VOID CCssStore::CreateCss_center_disp_btn_line_chiyoda_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_chiyoda_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_chiyoda_off
VOID CCssStore::CreateCss_center_disp_btn_line_chiyoda_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_chiyoda_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x51a223;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_fukutoshin_disabled
VOID CCssStore::CreateCss_center_disp_btn_line_fukutoshin_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_fukutoshin_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0xacacac );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_fukutoshin_off
VOID CCssStore::CreateCss_center_disp_btn_line_fukutoshin_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_fukutoshin_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x3268ba;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_ginza_disabled
VOID CCssStore::CreateCss_center_disp_btn_line_ginza_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_ginza_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_ginza_off
VOID CCssStore::CreateCss_center_disp_btn_line_ginza_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_ginza_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x0079ef;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_hanzoumon_disabled
VOID CCssStore::CreateCss_center_disp_btn_line_hanzoumon_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_hanzoumon_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0xacacac );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_hanzoumon_off
VOID CCssStore::CreateCss_center_disp_btn_line_hanzoumon_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_hanzoumon_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x933490;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_hibiya_disabled
VOID CCssStore::CreateCss_center_disp_btn_line_hibiya_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_hibiya_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_hibiya_off
VOID CCssStore::CreateCss_center_disp_btn_line_hibiya_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_hibiya_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x989593;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_lblu_disabled
VOID CCssStore::CreateCss_center_disp_btn_line_lblu_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_lblu_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_lblu_off
VOID CCssStore::CreateCss_center_disp_btn_line_lblu_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_lblu_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xbca700;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_marunouti_disabled
VOID CCssStore::CreateCss_center_disp_btn_line_marunouti_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_marunouti_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_marunouti_off
VOID CCssStore::CreateCss_center_disp_btn_line_marunouti_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_marunouti_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x241ced;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_mita_disabled
VOID CCssStore::CreateCss_center_disp_btn_line_mita_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_mita_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_mita_off
VOID CCssStore::CreateCss_center_disp_btn_line_mita_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_mita_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xbc7200;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_nanboku_disabled
VOID CCssStore::CreateCss_center_disp_btn_line_nanboku_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_nanboku_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0xacacac );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_nanboku_off
VOID CCssStore::CreateCss_center_disp_btn_line_nanboku_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_nanboku_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xa0b600;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_oedo_disabled
VOID CCssStore::CreateCss_center_disp_btn_line_oedo_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_oedo_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0xacacac );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_oedo_off
VOID CCssStore::CreateCss_center_disp_btn_line_oedo_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_oedo_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x761edd;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_yurakucyou_disabled
VOID CCssStore::CreateCss_center_disp_btn_line_yurakucyou_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_yurakucyou_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0xacacac );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_line_yurakucyou_off
VOID CCssStore::CreateCss_center_disp_btn_line_yurakucyou_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_yurakucyou_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x42bdbd;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_lyel_disabled
VOID CCssStore::CreateCss_center_disp_btn_lyel_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_lyel_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x31aabf;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x41d3e9;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x3e98a6 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x6fd2e1 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_lyel_off
VOID CCssStore::CreateCss_center_disp_btn_lyel_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_lyel_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x001c2c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x41d3e9;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x216c77 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x69c1ce );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x002233;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x319faf;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x519099;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x19515a;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_mae_tri_off
VOID CCssStore::CreateCss_center_disp_btn_mae_tri_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_mae_tri_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x333333;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\left_gokakukei_up.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;

    lpActiveBtn->lpsctIcon->sSourcePath = "resource\\image\\center_disp\\left_gokakukei_down.png";

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_meisai_disabled
VOID CCssStore::CreateCss_center_disp_btn_meisai_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_meisai_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\ikkenn_meisai_disable.jpg";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_meisai_on
VOID CCssStore::CreateCss_center_disp_btn_meisai_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_meisai_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\btn_toriatsukai_meisai.bmp";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_mobile_disabled
VOID CCssStore::CreateCss_center_disp_btn_mobile_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_mobile_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x996532;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\btn_gyoumu_tray_disable.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_mobile_off
VOID CCssStore::CreateCss_center_disp_btn_mobile_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_mobile_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x00ccff;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\btn_gyoumu_tray_notselect.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_mobile_on
VOID CCssStore::CreateCss_center_disp_btn_mobile_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_mobile_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x00ccff;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\btn_gyoumu_tray_select.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_pink_disabled
VOID CCssStore::CreateCss_center_disp_btn_pink_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_pink_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xcaca97;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xafaf61;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0xafaf61;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x828245 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xc3c380 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_pink_off
VOID CCssStore::CreateCss_center_disp_btn_pink_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_pink_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc3b0d9;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x685e74 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xd6c9e5 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xe4e4d7;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x848449;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x98986e;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x53532e;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0xafaf61;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_pink_off2
VOID CCssStore::CreateCss_center_disp_btn_pink_off2()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_pink_off2"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x8fccaa;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x486d59 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xb5dec9 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xe4e4d7;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x848449;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x98986e;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x53532e;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0xafaf61;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_r_rpurple_disabled
VOID CCssStore::CreateCss_center_disp_btn_r_rpurple_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_r_rpurple_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x553892;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x937dae;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6c5b81 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xab99c1 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_r_rpurple_off
VOID CCssStore::CreateCss_center_disp_btn_r_rpurple_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_r_rpurple_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x553892;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x937dae;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x5a4d6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xb9a9cc );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xffffff;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x6f5e83;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x867895;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x524560;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwTextColor            = ( DWORD ) 0xffffff;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_red_blk_disabled
VOID CCssStore::CreateCss_center_disp_btn_red_blk_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_red_blk_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa2a29c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG ) -6, ( DWORD )  4, ( DWORD ) 0x9e9e95 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG )  6, ( DWORD )  2, ( DWORD ) 0xe4e4db );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_red_blk_off
VOID CCssStore::CreateCss_center_disp_btn_red_blk_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_red_blk_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xdbdad0;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x4d4e4c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe7e5dd );

    lpOffBtn->vSpanClass.resize(( size_t ) 2 );             // CSS make by manual
    lpOffBtn->vSpanClass[0].sClass      = "str_red";
    lpOffBtn->vSpanClass[0].dwTextColor = 0x633fbd;
    lpOffBtn->vSpanClass[1].sClass      = "str_black";
    lpOffBtn->vSpanClass[1].dwTextColor = 0x000000;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x333333;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xa2a29a;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xa4a595;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x606052;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_rpurple_dengen_disabled
VOID CCssStore::CreateCss_center_disp_btn_rpurple_dengen_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_rpurple_dengen_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xbfb0df;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x9c84ce;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b5a8f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xb4a1da );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\poweroff_disabled.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 29;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_rpurple_dengen_off
VOID CCssStore::CreateCss_center_disp_btn_rpurple_dengen_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_rpurple_dengen_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x6844b4;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x462b81 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xa58bd4 );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\poweroff_off.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 29;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x41286e;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x957ba2;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwTextColor            = ( DWORD ) 0x262626;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0xcecece;
    lpDisableBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpDisableBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x6b6b6b;
    lpDisableBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpDisableBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xdedede;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_rpurple_disabled
VOID CCssStore::CreateCss_center_disp_btn_rpurple_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_rpurple_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xbfb0df;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x9c84ce;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b5a8f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xb4a1da );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_rpurple_off
VOID CCssStore::CreateCss_center_disp_btn_rpurple_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_rpurple_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x6844b4;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x462b81 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xa58bd4 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x41286e;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x957ba2;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwTextColor            = ( DWORD ) 0x262626;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0xcecece;
    lpDisableBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpDisableBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x6b6b6b;
    lpDisableBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpDisableBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xdedede;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_teiki_untin_serch_disabled
VOID CCssStore::CreateCss_center_disp_btn_teiki_untin_serch_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_teiki_untin_serch_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\unchin_kensaku_disable.jpg";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_teiki_untin_serch_on
VOID CCssStore::CreateCss_center_disp_btn_teiki_untin_serch_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_teiki_untin_serch_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\btn_teiki_unchin.bmp";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_tri_left_disabled
VOID CCssStore::CreateCss_center_disp_btn_tri_left_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_tri_left_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\left_disabled_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_tri_left_off
VOID CCssStore::CreateCss_center_disp_btn_tri_left_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_tri_left_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\left_off_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;

    lpActiveBtn->lpsctIcon->sSourcePath = "resource\\image\\center_disp\\left_off_active_btn.png";

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_tri_lpurple_disabled
VOID CCssStore::CreateCss_center_disp_btn_tri_lpurple_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_tri_lpurple_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xb1a3a4;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xe6d2d3;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x878383;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0xa19293 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xf1e1e2 );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\right_triangle_disabled.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 25;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_tri_lpurple_off
VOID CCssStore::CreateCss_center_disp_btn_tri_lpurple_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_tri_lpurple_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x333333;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xe6d2d3;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x85797a );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xfbedee );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\right_triangle_up.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 25;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xad9e9f;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xbaaeaf;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x807676;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_tri_right_disabled
VOID CCssStore::CreateCss_center_disp_btn_tri_right_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_tri_right_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\right_disabled_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_tri_right_off
VOID CCssStore::CreateCss_center_disp_btn_tri_right_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_tri_right_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\right_off_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;

    lpActiveBtn->lpsctIcon->sSourcePath = "resource\\image\\center_disp\\right_off_active_btn.png";

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_tsugi_tri_off
VOID CCssStore::CreateCss_center_disp_btn_tsugi_tri_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_tsugi_tri_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x333333;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\center_disp\\right_gokakukei_up.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;

    lpActiveBtn->lpsctIcon->sSourcePath = "resource\\image\\center_disp\\right_gokakukei_down.png";

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_vio_disabled
VOID CCssStore::CreateCss_center_disp_btn_vio_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_vio_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x815b4b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xb9826c;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6a4e43 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xb8998d );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: center_disp_btn_vio_off
VOID CCssStore::CreateCss_center_disp_btn_vio_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_vio_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xb9826c;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x5f4236 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xd6b5a7 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x8b6251;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x816e66;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x52392f;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_bunkatsu_gry_disabled
VOID CCssStore::CreateCss_const_btn_btn_bunkatsu_gry_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_bunkatsu_gry_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 100;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xb5b5b5;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_bunkatsu_gry_off
VOID CCssStore::CreateCss_const_btn_btn_bunkatsu_gry_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_bunkatsu_gry_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 100;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x808080;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9a9a9a;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x5f5f5f;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x8e8e8e;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_dblu_disabled
VOID CCssStore::CreateCss_const_btn_btn_dblu_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_dblu_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xca9f89;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xae6b4a;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x462f24 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xcba08a );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_dblu_mark_disabled
VOID CCssStore::CreateCss_const_btn_btn_dblu_mark_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_dblu_mark_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xca9f89;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xae6b4a;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x462f24 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xcba08a );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\const_btn\\tokkyu_mark_disabled.bmp";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 40;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_dblu_mark_off
VOID CCssStore::CreateCss_const_btn_btn_dblu_mark_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_dblu_mark_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xae6b4a;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x462f24 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xcba08a );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\const_btn\\tokkyu_mark_off.bmp";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 40;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x835138;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwTextColor            = ( DWORD ) 0x262626;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0xcecece;
    lpDisableBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpDisableBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x6b6b6b;
    lpDisableBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpDisableBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xdedede;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_dblu_off
VOID CCssStore::CreateCss_const_btn_btn_dblu_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_dblu_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xae6b4a;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x462f24 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xcba08a );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x835138;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwTextColor            = ( DWORD ) 0x262626;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0xcecece;
    lpDisableBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpDisableBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x6b6b6b;
    lpDisableBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpDisableBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xdedede;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_ggrnb_mae_disabled
VOID CCssStore::CreateCss_const_btn_btn_ggrnb_mae_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_ggrnb_mae_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa2a29c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG ) -6, ( DWORD )  4, ( DWORD ) 0x9e9e95 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG )  6, ( DWORD )  2, ( DWORD ) 0xe4e4db );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\const_btn\\prev_yajirushi_disabled.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 19;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HRIGHT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_ggrnb_mae_off
VOID CCssStore::CreateCss_const_btn_btn_ggrnb_mae_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_ggrnb_mae_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xdbdad0;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x4d4e4c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe7e5dd );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\const_btn\\prev_yajirushi.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 19;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HRIGHT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x333333;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x979781;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xa4a595;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x606052;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_ggrnb_tsugi_disabled
VOID CCssStore::CreateCss_const_btn_btn_ggrnb_tsugi_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_ggrnb_tsugi_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa2a29c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG ) -6, ( DWORD )  4, ( DWORD ) 0x9e9e95 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG )  6, ( DWORD )  2, ( DWORD ) 0xe4e4db );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\const_btn\\next_yajirushi_disabled.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 19;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HRIGHT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_ggrnb_tsugi_off
VOID CCssStore::CreateCss_const_btn_btn_ggrnb_tsugi_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_ggrnb_tsugi_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xdbdad0;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x4d4e4c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe7e5dd );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\const_btn\\next_yajirushi.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 19;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HRIGHT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x333333;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x979781;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xa4a595;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x606052;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_grnb_disabled
VOID CCssStore::CreateCss_const_btn_btn_grnb_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_grnb_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xcaca97;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xafaf61;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0xafaf61;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x828245 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xc3c380 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_grnb_off
VOID CCssStore::CreateCss_const_btn_btn_grnb_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_grnb_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xafaf61;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x242420 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xcdcd9d );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xe4e4d7;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x848449;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x98986e;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x53532e;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_gry_disabled
VOID CCssStore::CreateCss_const_btn_btn_gry_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_gry_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x9b9b9b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xcecece;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_gry_off
VOID CCssStore::CreateCss_const_btn_btn_gry_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_gry_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x262626;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xcecece;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9a9a9a;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x5f5f5f;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x8e8e8e;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_gry_t_disabled
VOID CCssStore::CreateCss_const_btn_btn_gry_t_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_gry_t_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x9b9b9b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xcecece;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 100;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_gry_t_off
VOID CCssStore::CreateCss_const_btn_btn_gry_t_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_gry_t_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x262626;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xcecece;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 100;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9a9a9a;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x5f5f5f;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x8e8e8e;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_gvg_disabled
VOID CCssStore::CreateCss_const_btn_btn_gvg_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_gvg_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa2a29c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG ) -6, ( DWORD )  4, ( DWORD ) 0x9e9e95 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG )  6, ( DWORD )  2, ( DWORD ) 0xe4e4db );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_gvg_off
VOID CCssStore::CreateCss_const_btn_btn_gvg_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_gvg_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xdbdad0;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x4d4e4c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe7e5dd );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x4a4de7;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_gyg_disabled
VOID CCssStore::CreateCss_const_btn_btn_gyg_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_gyg_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa2a29c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG ) -6, ( DWORD )  4, ( DWORD ) 0x9e9e95 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG )  6, ( DWORD )  2, ( DWORD ) 0xe4e4db );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_gyg_off
VOID CCssStore::CreateCss_const_btn_btn_gyg_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_gyg_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xdbdad0;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x4d4e4c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe7e5dd );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_lgrn_disabled
VOID CCssStore::CreateCss_const_btn_btn_lgrn_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_lgrn_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x9b9b8b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc6ceb5;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x747c6c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xdfd6cf );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_lgrn_off
VOID CCssStore::CreateCss_const_btn_btn_lgrn_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_lgrn_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc9c9ab;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x635d4a );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xdbddc9 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9c9c8c;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x7e8473;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x6a716a;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_lyel_disabled
VOID CCssStore::CreateCss_const_btn_btn_lyel_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_lyel_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x31aabf;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x41d3e9;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x3e98a6 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x6fd2e1 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_lyel_off
VOID CCssStore::CreateCss_const_btn_btn_lyel_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_lyel_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x001c2c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x41d3e9;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x216c77 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x69c1ce );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x002233;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x319faf;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x519099;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x19515a;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_rpurple_disabled
VOID CCssStore::CreateCss_const_btn_btn_rpurple_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_rpurple_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xbfb0df;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x9c84ce;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b5a8f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xb4a1da );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_rpurple_off
VOID CCssStore::CreateCss_const_btn_btn_rpurple_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_rpurple_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x6844b4;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x462b81 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xa58bd4 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x41286e;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x957ba2;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwTextColor            = ( DWORD ) 0x262626;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0xcecece;
    lpDisableBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpDisableBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x6b6b6b;
    lpDisableBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpDisableBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xdedede;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_tri_lpurple_disabled
VOID CCssStore::CreateCss_const_btn_btn_tri_lpurple_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_tri_lpurple_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xb1a3a4;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xe6d2d3;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x878383;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0xa19293 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xf1e1e2 );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\const_btn\\right_triangle_disabled.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 25;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: const_btn_btn_tri_lpurple_off
VOID CCssStore::CreateCss_const_btn_btn_tri_lpurple_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_tri_lpurple_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x333333;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xe6d2d3;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x85797a );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xfbedee );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\const_btn\\right_triangle_up.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 25;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xad9e9f;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xbaaeaf;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x807676;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disabled_yajirushi_next
VOID CCssStore::CreateCss_disabled_yajirushi_next()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disabled_yajirushi_next"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\next_disabled_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disabled_yajirushi_pre
VOID CCssStore::CreateCss_disabled_yajirushi_pre()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disabled_yajirushi_pre"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\pre_disabled_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disp_btn_db_y_db_disabled
VOID CCssStore::CreateCss_disp_btn_db_y_db_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disp_btn_db_y_db_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xbc9581;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xae6b4a;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x806f67;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x825037 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0xbc8a71 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disp_btn_db_y_db_off
VOID CCssStore::CreateCss_disp_btn_db_y_db_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disp_btn_db_y_db_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xae6b4a;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x573627 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0xbd9988 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x333333;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x4a4c4b;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x83e3c4;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x68b49b;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disp_btn_db_y_db_t_disabled
VOID CCssStore::CreateCss_disp_btn_db_y_db_t_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disp_btn_db_y_db_t_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xbc9581;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xae6b4a;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 100;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x806f67;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x825037 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0xbc8a71 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disp_btn_db_y_db_t_off
VOID CCssStore::CreateCss_disp_btn_db_y_db_t_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disp_btn_db_y_db_t_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xae6b4a;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 100;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x573627 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0xbd9988 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x333333;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x4a4c4b;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x83e3c4;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x68b49b;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disp_btn_db_y_gry_disabled
VOID CCssStore::CreateCss_disp_btn_db_y_gry_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disp_btn_db_y_gry_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa2a29c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x4f4f4f;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x828282 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0xcbcbcb );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disp_btn_db_y_gry_off
VOID CCssStore::CreateCss_disp_btn_db_y_gry_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disp_btn_db_y_gry_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xae6b4a;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x573627 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0xbd9988 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x333333;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x4a4c4b;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x83e3c4;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x68b49b;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disp_btn_db_y_gry_t_disabled
VOID CCssStore::CreateCss_disp_btn_db_y_gry_t_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disp_btn_db_y_gry_t_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa2a29c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 100;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x4f4f4f;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x828282 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0xcbcbcb );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disp_btn_db_y_gry_t_off
VOID CCssStore::CreateCss_disp_btn_db_y_gry_t_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disp_btn_db_y_gry_t_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xae6b4a;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 100;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x573627 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0xbd9988 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x333333;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x4a4c4b;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x83e3c4;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x68b49b;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disp_btn_g_y_g_disabled
VOID CCssStore::CreateCss_disp_btn_g_y_g_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disp_btn_g_y_g_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x84b08c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x388d49;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x69796d;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x326c3e );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0x6ca477 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disp_btn_g_y_g_off
VOID CCssStore::CreateCss_disp_btn_g_y_g_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disp_btn_g_y_g_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x388d49;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x1e4225 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0x7ba283 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x333333;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x80d6ba;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x64a892;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disp_btn_g_y_g_t_disabled
VOID CCssStore::CreateCss_disp_btn_g_y_g_t_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disp_btn_g_y_g_t_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x84b08c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x388d49;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 100;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x69796d;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x326c3e );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0x6ca477 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disp_btn_g_y_g_t_off
VOID CCssStore::CreateCss_disp_btn_g_y_g_t_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disp_btn_g_y_g_t_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x388d49;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 100;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x1e4225 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0x7ba283 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x333333;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x80d6ba;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x64a892;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disp_btn_g_y_gry_disabled
VOID CCssStore::CreateCss_disp_btn_g_y_gry_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disp_btn_g_y_gry_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa2a29c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x4f4f4f;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x828282 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0xcbcbcb );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disp_btn_g_y_gry_off
VOID CCssStore::CreateCss_disp_btn_g_y_gry_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disp_btn_g_y_gry_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x388d49;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x1e4225 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0x7ba283 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x333333;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x80d6ba;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x64a892;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disp_btn_g_y_gry_t_disabled
VOID CCssStore::CreateCss_disp_btn_g_y_gry_t_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disp_btn_g_y_gry_t_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa2a29c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 100;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x4f4f4f;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x828282 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0xcbcbcb );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: disp_btn_g_y_gry_t_off
VOID CCssStore::CreateCss_disp_btn_g_y_gry_t_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["disp_btn_g_y_gry_t_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x388d49;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 100;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x1e4225 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0x7ba283 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x333333;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x80d6ba;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x64a892;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: off_light_yajirushi_next
VOID CCssStore::CreateCss_off_light_yajirushi_next()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["off_light_yajirushi_next"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\next_off_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;

    lpActiveBtn->lpsctIcon->sSourcePath = "resource\\image\\operation\\next_off_active_btn.png";

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: off_light_yajirushi_pre
VOID CCssStore::CreateCss_off_light_yajirushi_pre()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["off_light_yajirushi_pre"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\pre_off_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;

    lpActiveBtn->lpsctIcon->sSourcePath = "resource\\image\\operation\\pre_off_active_btn.png";

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: on_light_yajirushi_next
VOID CCssStore::CreateCss_on_light_yajirushi_next()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["on_light_yajirushi_next"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\next_on_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: on_light_yajirushi_pre
VOID CCssStore::CreateCss_on_light_yajirushi_pre()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["on_light_yajirushi_pre"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\pre_on_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_brn_disabled
VOID CCssStore::CreateCss_operation_btn_brn_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_brn_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x7fa0cc;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x5583bf;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x8dabd4 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x85a6d1 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_brn_off
VOID CCssStore::CreateCss_operation_btn_brn_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_brn_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x5583bd;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x8dabd4 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x85a6d1 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x818181;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x406390;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_dblugre_disabled
VOID CCssStore::CreateCss_operation_btn_dblugre_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_dblugre_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xb79c7d;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xab8a63;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x968f87;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x705a3e );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xc9b093 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_dblugre_off
VOID CCssStore::CreateCss_operation_btn_dblugre_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_dblugre_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xf4f6f9;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x916b39;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x3e2d19 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xc7ae9a );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xe0ddd9;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x6d512b;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x988772;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x382915;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwTextColor            = ( DWORD ) 0xaf9573;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0x8e6c39;
    lpDisableBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x594123;
    lpDisableBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xb39976;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_grn_disabled
VOID CCssStore::CreateCss_operation_btn_grn_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_grn_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x0000ff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x398e4a;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x2f3b2f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0x7aae8a );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_grn_off
VOID CCssStore::CreateCss_operation_btn_grn_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_grn_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x0000ff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x398e4a;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -2, ( DWORD )  2, ( DWORD ) 0x2f3b2f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  2, ( DWORD )  2, ( DWORD ) 0x7aae8a );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x000086;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x8cfbd6;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x575c5b;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x85eeca;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x65bfa3;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_grn_printer_disabled
VOID CCssStore::CreateCss_operation_btn_grn_printer_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_grn_printer_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xbec793;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xa0ae62;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x505346;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x5f6838 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xbfca90 );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\printer_disabled.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 40;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_grn_printer_off
VOID CCssStore::CreateCss_operation_btn_grn_printer_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_grn_printer_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xa0ae62;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x5e673a );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xbcc690 );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\printer_up.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 40;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xe5e7dc;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x78834a;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x3e4038;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x939a71;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x4f5730;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->sctBorder.dwColor      = ( DWORD ) 0xbcc690;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_grnb_disabled
VOID CCssStore::CreateCss_operation_btn_grnb_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_grnb_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xc6c690;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xafaf61;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x242420 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xcdcd9d );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_grnb_off
VOID CCssStore::CreateCss_operation_btn_grnb_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_grnb_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xafaf61;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x242420 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xcdcd9d );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x818181;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x848449;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xcdcd9d;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x242420;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwTextColor            = ( DWORD ) 0x262626;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0xcecece;
    lpDisableBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x6b6b6b;
    lpDisableBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xdedede;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lblu_disabled
VOID CCssStore::CreateCss_operation_btn_lblu_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lblu_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x81684b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xffff00;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x81684b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xffff80 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lblu_mono_disabled
VOID CCssStore::CreateCss_operation_btn_lblu_mono_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lblu_mono_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x81684b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xffff00;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x81684b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xffff80 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lblu_mono_off
VOID CCssStore::CreateCss_operation_btn_lblu_mono_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lblu_mono_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xffff00;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x81684b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xffff80 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xe6a300;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xffbf00;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x81684b;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lblu_off
VOID CCssStore::CreateCss_operation_btn_lblu_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lblu_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xffff00;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x81684b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xffff80 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xe6a300;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xffbf00;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x81684b;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgrn_disabled
VOID CCssStore::CreateCss_operation_btn_lgrn_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgrn_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x9b9b8b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc6ceb5;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x747c6c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xdfd6cf );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgrn_off
VOID CCssStore::CreateCss_operation_btn_lgrn_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgrn_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc9c9ab;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x635d4a );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xdbddc9 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9c9c8c;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x7e8473;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x6a716a;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgry_disabled
VOID CCssStore::CreateCss_operation_btn_lgry_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgry_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x9b9b9b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgry_mono_disabled
VOID CCssStore::CreateCss_operation_btn_lgry_mono_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgry_mono_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x9b9b9b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgry_mono_off
VOID CCssStore::CreateCss_operation_btn_lgry_mono_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgry_mono_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x262626;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xa2a29a;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x8e8e8e;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x5f5f5f;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgry_mono_on
VOID CCssStore::CreateCss_operation_btn_lgry_mono_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgry_mono_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x262626;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xa2a29a;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x8e8e8e );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x5f5f5f );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd7d7cc;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x333333;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x6b6b6b;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xdedede;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgry_off
VOID CCssStore::CreateCss_operation_btn_lgry_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgry_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x262626;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xa2a29a;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x8e8e8e;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x5f5f5f;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgry_on
VOID CCssStore::CreateCss_operation_btn_lgry_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgry_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x262626;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xa2a29a;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x8e8e8e );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x5f5f5f );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd7d7cc;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x333333;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x6b6b6b;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xdedede;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgry_page_disabled
VOID CCssStore::CreateCss_operation_btn_lgry_page_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgry_page_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x9b9b9b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xcecece;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgry_page_off
VOID CCssStore::CreateCss_operation_btn_lgry_page_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgry_page_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x262626;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xcecece;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9a9a9a;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x8e8e8e;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x5f5f5f;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgry_page_on
VOID CCssStore::CreateCss_operation_btn_lgry_page_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgry_page_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x262626;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x9a9a9a;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x8e8e8e );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x5f5f5f );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xcecece;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x333333;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x6b6b6b;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xdedede;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgydg_left_maru_disabled
VOID CCssStore::CreateCss_operation_btn_lgydg_left_maru_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgydg_left_maru_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4c4c4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x7e7e7e;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG ) -6, ( DWORD )  4, ( DWORD ) 0x71716b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG )  6, ( DWORD )  2, ( DWORD ) 0xe8e8e1 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgydg_left_maru_off
VOID CCssStore::CreateCss_operation_btn_lgydg_left_maru_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgydg_left_maru_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xdbdad0;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x71716b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e1 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x28091e;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4d4e4c;
    lpDisableBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe7e5dd;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgydg_right_maru_disabled
VOID CCssStore::CreateCss_operation_btn_lgydg_right_maru_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgydg_right_maru_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4c4c4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x7e7e7e;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG ) -6, ( DWORD )  4, ( DWORD ) 0x71716b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG )  6, ( DWORD )  2, ( DWORD ) 0xe8e8e1 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgydg_right_maru_off
VOID CCssStore::CreateCss_operation_btn_lgydg_right_maru_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgydg_right_maru_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xdbdad0;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x71716b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e1 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x28091e;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4d4e4c;
    lpDisableBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe7e5dd;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgylg_page_disabled
VOID CCssStore::CreateCss_operation_btn_lgylg_page_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgylg_page_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x9b9b9b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xcecece;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgylg_page_off
VOID CCssStore::CreateCss_operation_btn_lgylg_page_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgylg_page_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x262626;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xcecece;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lgylg_page_on
VOID CCssStore::CreateCss_operation_btn_lgylg_page_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lgylg_page_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x262626;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xcecece;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x333333;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x6b6b6b;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xdedede;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line2_ikebukuro_disabled
VOID CCssStore::CreateCss_operation_btn_line2_ikebukuro_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line2_ikebukuro_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x88b3db;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line2_ikebukuro_off
VOID CCssStore::CreateCss_operation_btn_line2_ikebukuro_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line2_ikebukuro_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x007aee;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line2_kokubunji_disabled
VOID CCssStore::CreateCss_operation_btn_line2_kokubunji_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line2_kokubunji_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9bc288;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line2_kokubunji_off
VOID CCssStore::CreateCss_operation_btn_line2_kokubunji_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line2_kokubunji_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x4bab1a;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line2_sayama_disabled
VOID CCssStore::CreateCss_operation_btn_line2_sayama_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line2_sayama_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xc9bf7d;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line2_sayama_off
VOID CCssStore::CreateCss_operation_btn_line2_sayama_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line2_sayama_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xbe5a00;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line2_tamako_disabled
VOID CCssStore::CreateCss_operation_btn_line2_tamako_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line2_tamako_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x68c0e4;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line2_tamako_off
VOID CCssStore::CreateCss_operation_btn_line2_tamako_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line2_tamako_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x00aff6;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line2_toyo_sbyuraku_disabled
VOID CCssStore::CreateCss_operation_btn_line2_toyo_sbyuraku_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line2_toyo_sbyuraku_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;

    lpOffBtn->lpSctLine->lpGradientColor = new SCT_COLOR_GRADIENT();        // Css make by manual
    lpOffBtn->lpSctLine->lpGradientColor->dwFstClr = 0x7daedd;
    lpOffBtn->lpSctLine->lpGradientColor->dwSndClr = 0xc6b0bf;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line2_toyo_sbyuraku_off
VOID CCssStore::CreateCss_operation_btn_line2_toyo_sbyuraku_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line2_toyo_sbyuraku_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line2_yamaguchi_disabled
VOID CCssStore::CreateCss_operation_btn_line2_yamaguchi_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line2_yamaguchi_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line2_yamaguchi_off
VOID CCssStore::CreateCss_operation_btn_line2_yamaguchi_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line2_yamaguchi_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x3840da;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x585858;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_asakusa_disabled
VOID CCssStore::CreateCss_operation_btn_line_asakusa_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_asakusa_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_asakusa_off
VOID CCssStore::CreateCss_operation_btn_line_asakusa_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_asakusa_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x6d72f2;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_cb_disabled
VOID CCssStore::CreateCss_operation_btn_line_cb_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_cb_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_cb_off
VOID CCssStore::CreateCss_operation_btn_line_cb_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_cb_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x464646;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_cb_on
VOID CCssStore::CreateCss_operation_btn_line_cb_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_cb_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x464646;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_chiyoda_disabled
VOID CCssStore::CreateCss_operation_btn_line_chiyoda_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_chiyoda_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_chiyoda_off
VOID CCssStore::CreateCss_operation_btn_line_chiyoda_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_chiyoda_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x51a223;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_fukutoshin_disabled
VOID CCssStore::CreateCss_operation_btn_line_fukutoshin_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_fukutoshin_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_fukutoshin_off
VOID CCssStore::CreateCss_operation_btn_line_fukutoshin_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_fukutoshin_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x5a82c0;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_ginza_disabled
VOID CCssStore::CreateCss_operation_btn_line_ginza_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_ginza_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_ginza_off
VOID CCssStore::CreateCss_operation_btn_line_ginza_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_ginza_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x0079ef;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_hanzoumon_disabled
VOID CCssStore::CreateCss_operation_btn_line_hanzoumon_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_hanzoumon_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_hanzoumon_off
VOID CCssStore::CreateCss_operation_btn_line_hanzoumon_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_hanzoumon_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x8e278b;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_hibiya_disabled
VOID CCssStore::CreateCss_operation_btn_line_hibiya_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_hibiya_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_hibiya_off
VOID CCssStore::CreateCss_operation_btn_line_hibiya_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_hibiya_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x989593;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_jr_disabled
VOID CCssStore::CreateCss_operation_btn_line_jr_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_jr_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_jr_off
VOID CCssStore::CreateCss_operation_btn_line_jr_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_jr_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x00850d;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_jr_on
VOID CCssStore::CreateCss_operation_btn_line_jr_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_jr_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x00850d;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_kk_disabled
VOID CCssStore::CreateCss_operation_btn_line_kk_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_kk_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_kk_off
VOID CCssStore::CreateCss_operation_btn_line_kk_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_kk_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x37037f;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_kk_on
VOID CCssStore::CreateCss_operation_btn_line_kk_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_kk_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x37037f;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_ko_disabled
VOID CCssStore::CreateCss_operation_btn_line_ko_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_ko_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_ko_off
VOID CCssStore::CreateCss_operation_btn_line_ko_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_ko_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x7600cb;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_ko_on
VOID CCssStore::CreateCss_operation_btn_line_ko_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_ko_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x7600cb;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_ks_disabled
VOID CCssStore::CreateCss_operation_btn_line_ks_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_ks_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_ks_off
VOID CCssStore::CreateCss_operation_btn_line_ks_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_ks_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xfbba29;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_ks_on
VOID CCssStore::CreateCss_operation_btn_line_ks_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_ks_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xfbba29;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_marunouti_disabled
VOID CCssStore::CreateCss_operation_btn_line_marunouti_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_marunouti_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_marunouti_off
VOID CCssStore::CreateCss_operation_btn_line_marunouti_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_marunouti_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x241ced;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_mita_disabled
VOID CCssStore::CreateCss_operation_btn_line_mita_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_mita_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_mita_off
VOID CCssStore::CreateCss_operation_btn_line_mita_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_mita_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xbc7200;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_mx_disabled
VOID CCssStore::CreateCss_operation_btn_line_mx_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_mx_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_mx_off
VOID CCssStore::CreateCss_operation_btn_line_mx_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_mx_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x632f0a;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_mx_on
VOID CCssStore::CreateCss_operation_btn_line_mx_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_mx_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x632f0a;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_nanboku_disabled
VOID CCssStore::CreateCss_operation_btn_line_nanboku_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_nanboku_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_nanboku_off
VOID CCssStore::CreateCss_operation_btn_line_nanboku_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_nanboku_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xa0b600;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_od_disabled
VOID CCssStore::CreateCss_operation_btn_line_od_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_od_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_od_off
VOID CCssStore::CreateCss_operation_btn_line_od_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_od_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xc28614;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_od_on
VOID CCssStore::CreateCss_operation_btn_line_od_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_od_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xc28614;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_oedo_disabled
VOID CCssStore::CreateCss_operation_btn_line_oedo_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_oedo_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_oedo_off
VOID CCssStore::CreateCss_operation_btn_line_oedo_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_oedo_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x761edd;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_rk_disabled
VOID CCssStore::CreateCss_operation_btn_line_rk_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_rk_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_rk_off
VOID CCssStore::CreateCss_operation_btn_line_rk_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_rk_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xc2c325;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_rk_on
VOID CCssStore::CreateCss_operation_btn_line_rk_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_rk_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xc2c325;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_sb_disabled
VOID CCssStore::CreateCss_operation_btn_line_sb_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_sb_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_sb_off
VOID CCssStore::CreateCss_operation_btn_line_sb_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_sb_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xc26f05;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_sb_on
VOID CCssStore::CreateCss_operation_btn_line_sb_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_sb_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xc26f05;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x4a4a4a;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tb_disabled
VOID CCssStore::CreateCss_operation_btn_line_tb_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tb_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tb_off
VOID CCssStore::CreateCss_operation_btn_line_tb_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tb_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x163751;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tb_on
VOID CCssStore::CreateCss_operation_btn_line_tb_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tb_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x163751;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_te_disabled
VOID CCssStore::CreateCss_operation_btn_line_te_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_te_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_te_off
VOID CCssStore::CreateCss_operation_btn_line_te_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_te_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x06a972;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_te_on
VOID CCssStore::CreateCss_operation_btn_line_te_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_te_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x06a972;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tk_disabled
VOID CCssStore::CreateCss_operation_btn_line_tk_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tk_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tk_off
VOID CCssStore::CreateCss_operation_btn_line_tk_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tk_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x0024b9;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tk_on
VOID CCssStore::CreateCss_operation_btn_line_tk_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tk_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x0024b9;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tl_disabled
VOID CCssStore::CreateCss_operation_btn_line_tl_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tl_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tl_off
VOID CCssStore::CreateCss_operation_btn_line_tl_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tl_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x036ef5;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tl_on
VOID CCssStore::CreateCss_operation_btn_line_tl_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tl_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x036ef5;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tm_disabled
VOID CCssStore::CreateCss_operation_btn_line_tm_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tm_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tm_off
VOID CCssStore::CreateCss_operation_btn_line_tm_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tm_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x004bd8;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tm_on
VOID CCssStore::CreateCss_operation_btn_line_tm_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tm_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x004bd8;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tozai_disabled
VOID CCssStore::CreateCss_operation_btn_line_tozai_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tozai_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tozai_off
VOID CCssStore::CreateCss_operation_btn_line_tozai_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tozai_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xbca700;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tu_disabled
VOID CCssStore::CreateCss_operation_btn_line_tu_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tu_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tu_off
VOID CCssStore::CreateCss_operation_btn_line_tu_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tu_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x7f8827;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tu_on
VOID CCssStore::CreateCss_operation_btn_line_tu_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tu_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x7f8827;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tx_disabled
VOID CCssStore::CreateCss_operation_btn_line_tx_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tx_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tx_off
VOID CCssStore::CreateCss_operation_btn_line_tx_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tx_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x730205;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_tx_on
VOID CCssStore::CreateCss_operation_btn_line_tx_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_tx_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x730205;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_yk_disabled
VOID CCssStore::CreateCss_operation_btn_line_yk_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_yk_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_yk_off
VOID CCssStore::CreateCss_operation_btn_line_yk_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_yk_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xc34954;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_yk_on
VOID CCssStore::CreateCss_operation_btn_line_yk_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_yk_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xc34954;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_yu_disabled
VOID CCssStore::CreateCss_operation_btn_line_yu_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_yu_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_yu_off
VOID CCssStore::CreateCss_operation_btn_line_yu_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_yu_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xffab6d;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_yu_on
VOID CCssStore::CreateCss_operation_btn_line_yu_on()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_yu_on"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x89fad6;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -1, ( LONG ) -1, ( DWORD )  1, ( DWORD ) 0x4f967f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  1, ( LONG )  1, ( DWORD )  1, ( DWORD ) 0x84a299 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xffab6d;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xd1d1d1;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x756467;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xe8e8e8;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_yurakucyou_disabled
VOID CCssStore::CreateCss_operation_btn_line_yurakucyou_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_yurakucyou_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x979797;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x848484 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcdcdc );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x9b9b9b;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_line_yurakucyou_off
VOID CCssStore::CreateCss_operation_btn_line_yurakucyou_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_line_yurakucyou_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x44aedd;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lyel_disabled
VOID CCssStore::CreateCss_operation_btn_lyel_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lyel_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x31aabf;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x41d3e9;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x216c77 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x7debfc );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_lyel_off
VOID CCssStore::CreateCss_operation_btn_lyel_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_lyel_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x001c2c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x41d3e9;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x216c77 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x7debfc );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x002233;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x319faf;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x7debfc;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x216c77;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_red_blk_disabled
VOID CCssStore::CreateCss_operation_btn_red_blk_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_red_blk_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa2a29c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG ) -6, ( DWORD )  4, ( DWORD ) 0x9e9e95 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG )  6, ( DWORD )  2, ( DWORD ) 0xe4e4db );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_red_blk_off
VOID CCssStore::CreateCss_operation_btn_red_blk_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_red_blk_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xdbdad0;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x4d4e4c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe7e5dd );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x333333;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x979781;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xa4a595;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x606052;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_tri_left_disabled
VOID CCssStore::CreateCss_operation_btn_tri_left_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_tri_left_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\back_disabled_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_tri_left_off
VOID CCssStore::CreateCss_operation_btn_tri_left_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_tri_left_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\back_off_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;

    lpActiveBtn->lpsctIcon->sSourcePath = "resource\\image\\operation\\back_off_active_btn.png";

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_tri_leftbtn_disabled
VOID CCssStore::CreateCss_operation_btn_tri_leftbtn_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_tri_leftbtn_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\back_disabled_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_tri_leftbtn_off
VOID CCssStore::CreateCss_operation_btn_tri_leftbtn_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_tri_leftbtn_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\back_off_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;

    lpActiveBtn->lpsctIcon->sSourcePath = "resource\\image\\operation\\back_off_active_btn.png";

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_tri_lpurple_disabled
VOID CCssStore::CreateCss_operation_btn_tri_lpurple_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_tri_lpurple_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xb1a3a4;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xe6d2d3;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x878383;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0xa19293 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xf1e1e2 );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\tri_disabled.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 24;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_tri_lpurple_off
VOID CCssStore::CreateCss_operation_btn_tri_lpurple_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_tri_lpurple_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x333333;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xe6d2d3;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x85797a );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xfbedee );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\tri_off.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 24;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xad9e9f;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xbaaeaf;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x807676;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_tri_right_disabled
VOID CCssStore::CreateCss_operation_btn_tri_right_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_tri_right_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\next_disabled_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_tri_right_off
VOID CCssStore::CreateCss_operation_btn_tri_right_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_tri_right_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\next_off_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;

    lpActiveBtn->lpsctIcon->sSourcePath = "resource\\image\\operation\\next_off_active_btn.png";

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_tri_rightbtn_disabled
VOID CCssStore::CreateCss_operation_btn_tri_rightbtn_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_tri_rightbtn_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\next_disabled_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_tri_rightbtn_off
VOID CCssStore::CreateCss_operation_btn_tri_rightbtn_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_tri_rightbtn_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa8aa8c;
    lpOffBtn->dwBkgColor                = ( DWORD ) VALUE_COLOR_TRANSPARENT;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;


    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\operation\\next_off_btn.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 0;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HCENTER | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;

    lpActiveBtn->lpsctIcon->sSourcePath = "resource\\image\\operation\\next_off_active_btn.png";

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;

}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_yel_disabled
VOID CCssStore::CreateCss_operation_btn_yel_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_yel_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x3daab6;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x00ffff;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x216c77 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x80ffff );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_yel_mono_disabled
VOID CCssStore::CreateCss_operation_btn_yel_mono_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_yel_mono_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x3daab6;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x00ffff;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x216c77 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x80ffff );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_yel_mono_off
VOID CCssStore::CreateCss_operation_btn_yel_mono_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_yel_mono_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x00ffff;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 400;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x216c77 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x80ffff );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x41d3e9;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x7debfc;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x216c77;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: operation_btn_yel_off
VOID CCssStore::CreateCss_operation_btn_yel_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["operation_btn_yel_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x00ffff;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x216c77 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x80ffff );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x41d3e9;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x7debfc;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x216c77;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_brn_disabled
VOID CCssStore::CreateCss_popup_btn_brn_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_brn_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x83a3cd;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x5583bf;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x3a5c88 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x7ca1d3 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_brn_off
VOID CCssStore::CreateCss_popup_btn_brn_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_brn_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x5583bf;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x324c6f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x96b6e0 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xd6dbe0;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x406390;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x748caa;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x263b55;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_dblu_disabled
VOID CCssStore::CreateCss_popup_btn_dblu_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_dblu_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xc8a292;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xb9826c;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x67473b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xd4ae9f );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_dblu_off
VOID CCssStore::CreateCss_popup_btn_dblu_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_dblu_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xeeeeed;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xb9826c;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b4b3f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xd7b1a2 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xe4e0de;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x8b6251;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xa3877c;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x553c31;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_dblugre_disabled
VOID CCssStore::CreateCss_popup_btn_dblugre_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_dblugre_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xb79c7d;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xab8a63;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x968f87;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x705a3e );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xc9b093 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_dblugre_off
VOID CCssStore::CreateCss_popup_btn_dblugre_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_dblugre_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xf4f6f9;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x916b39;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x3e2d19 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xc7ae9a );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xe0ddd9;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x6d512b;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -2;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x988772;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  2;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x382915;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwTextColor            = ( DWORD ) 0xaf9573;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0x8e6c39;
    lpDisableBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x594123;
    lpDisableBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xb39976;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_drd_disabled
VOID CCssStore::CreateCss_popup_btn_drd_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_drd_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xbfb0df;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x9c84ce;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b5a8f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xb4a1da );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_drd_off
VOID CCssStore::CreateCss_popup_btn_drd_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_drd_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x6844b4;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x462b81 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xa58bd4 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x41286e;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x957ba2;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwTextColor            = ( DWORD ) 0x262626;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0xcecece;
    lpDisableBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpDisableBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x6b6b6b;
    lpDisableBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpDisableBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xdedede;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_gpink_disabled
VOID CCssStore::CreateCss_popup_btn_gpink_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_gpink_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x868194;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc3b8da;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6c6679 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe0d9ef );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_gpink_l_disabled
VOID CCssStore::CreateCss_popup_btn_gpink_l_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_gpink_l_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x868194;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc3b8da;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_LEFT | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6c6679 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe0d9ef );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_gpink_l_off
VOID CCssStore::CreateCss_popup_btn_gpink_l_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_gpink_l_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc3b8da;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_LEFT | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x8b839b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xd9d2e7 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x363637;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x938ba4;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xaba6b8;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x5f596a;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwTextColor            = ( DWORD ) 0xffffff;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0x5583bf;
    lpDisableBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x324c6f;
    lpDisableBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x96b6e0;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_gpink_off
VOID CCssStore::CreateCss_popup_btn_gpink_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_gpink_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x333333;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc3b8da;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x716b7f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe5dff5 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x363637;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x938ba4;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xaba6b8;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x5f596a;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0xb9826c;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_green_disabled
VOID CCssStore::CreateCss_popup_btn_green_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_green_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xcaca97;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xafaf61;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0xafaf61;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x828245 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xc3c380 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_green_off
VOID CCssStore::CreateCss_popup_btn_green_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_green_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x8fccaa;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x486d59 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xb5dec9 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xe4e4d7;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x848449;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x98986e;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x53532e;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0xafaf61;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_grnb_disabled
VOID CCssStore::CreateCss_popup_btn_grnb_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_grnb_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xcaca97;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xafaf61;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0xafaf61;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x828245 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xc3c380 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_grnb_off
VOID CCssStore::CreateCss_popup_btn_grnb_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_grnb_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xafaf61;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x242420 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xcdcd9d );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xe4e4d7;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x848449;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x98986e;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x53532e;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_gry_disabled
VOID CCssStore::CreateCss_popup_btn_gry_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_gry_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x9b9b9b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xcecece;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_gry_l_disabled
VOID CCssStore::CreateCss_popup_btn_gry_l_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_gry_l_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x9b9b9b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xcecece;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_LEFT | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_gry_l_off
VOID CCssStore::CreateCss_popup_btn_gry_l_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_gry_l_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x262626;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xcecece;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_LEFT | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9a9a9a;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x5f5f5f;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x8e8e8e;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_gry_off
VOID CCssStore::CreateCss_popup_btn_gry_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_gry_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x262626;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xcecece;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b6b6b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdedede );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9a9a9a;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x5f5f5f;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x8e8e8e;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_gyg_disabled
VOID CCssStore::CreateCss_popup_btn_gyg_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_gyg_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa2a29c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG ) -6, ( DWORD )  4, ( DWORD ) 0x9e9e95 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG )  6, ( DWORD )  2, ( DWORD ) 0xe4e4db );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_gyg_off
VOID CCssStore::CreateCss_popup_btn_gyg_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_gyg_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xdbdad0;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x4d4e4c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe7e5dd );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_lgrn_disabled
VOID CCssStore::CreateCss_popup_btn_lgrn_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_lgrn_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x9b9b8b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc6ceb5;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x747c6c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xdfd6cf );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_lgrn_grn_disabled
VOID CCssStore::CreateCss_popup_btn_lgrn_grn_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_lgrn_grn_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x9b9b8b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc6ceb5;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 10;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x747c6c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xdfd6cf );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_lgrn_grn_off
VOID CCssStore::CreateCss_popup_btn_lgrn_grn_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_lgrn_grn_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4e4f2d;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc9c9ab;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 10;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x635d4a );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xdbddc9 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9c9c8c;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x7e8473;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x6a716a;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_lgrn_off
VOID CCssStore::CreateCss_popup_btn_lgrn_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_lgrn_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc9c9ab;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x635d4a );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xdbddc9 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9c9c8c;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xdbddc9;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x635d4a;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_mae_disabled
VOID CCssStore::CreateCss_popup_btn_mae_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_mae_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa2a29c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG ) -6, ( DWORD )  4, ( DWORD ) 0x9e9e95 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG )  6, ( DWORD )  2, ( DWORD ) 0xe4e4db );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\popup\\mae_yajirushi_disabled.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 25;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_mae_off
VOID CCssStore::CreateCss_popup_btn_mae_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_mae_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xdbdad0;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x4d4e4c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe7e5dd );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\popup\\mae_yajirushi.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 25;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x333333;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x979781;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xa4a595;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x606052;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_pink_l_disabled
VOID CCssStore::CreateCss_popup_btn_pink_l_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_pink_l_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x83a3cd;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x5583bf;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_LEFT | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x3a5c88 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x7ca1d3 );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_pink_l_off
VOID CCssStore::CreateCss_popup_btn_pink_l_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_pink_l_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xcbc0ff;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_LEFT | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x8780aa );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xdcd4ff );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0xd6dbe0;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x406390;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x748caa;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x263b55;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_rpurple_dengen_disabled
VOID CCssStore::CreateCss_popup_btn_rpurple_dengen_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_rpurple_dengen_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xbfb0df;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x9c84ce;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6b5a8f );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xb4a1da );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\popup\\poweroff_disabled.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 29;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_rpurple_dengen_off
VOID CCssStore::CreateCss_popup_btn_rpurple_dengen_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_rpurple_dengen_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0x6844b4;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x462b81 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xa58bd4 );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\popup\\poweroff_off.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 29;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x41286e;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x957ba2;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
    lpDisableBtn->dwTextColor            = ( DWORD ) 0x262626;
    lpDisableBtn->dwBkgColor             = ( DWORD ) 0xcecece;
    lpDisableBtn->vBoxShadow[0].lVShadow = ( LONG )  -4;
    lpDisableBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x6b6b6b;
    lpDisableBtn->vBoxShadow[1].lVShadow = ( LONG )  4;
    lpDisableBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0xdedede;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_tri_lpurple_disabled
VOID CCssStore::CreateCss_popup_btn_tri_lpurple_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_tri_lpurple_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xb1a3a4;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xe6d2d3;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x878383;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0xa19293 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xf1e1e2 );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\popup\\right_triangle_disabled.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 25;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_tri_lpurple_off
VOID CCssStore::CreateCss_popup_btn_tri_lpurple_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_tri_lpurple_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x333333;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xe6d2d3;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x85797a );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xfbedee );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\popup\\right_triangle_up.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 25;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HLEFT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0xad9e9f;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xbaaeaf;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x807676;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_tsugi_disabled
VOID CCssStore::CreateCss_popup_btn_tsugi_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_tsugi_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xa2a29c;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd7d7cc;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x6d5442;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG ) -6, ( DWORD )  4, ( DWORD ) 0x9e9e95 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  0, ( LONG )  6, ( DWORD )  2, ( DWORD ) 0xe4e4db );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\popup\\next_yajirushi_disabled.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 25;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HRIGHT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_tsugi_off
VOID CCssStore::CreateCss_popup_btn_tsugi_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_tsugi_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xdbdad0;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x4d4e4c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe7e5dd );

    lpOffBtn->lpsctIcon                 = new SCT_ICON();
    lpOffBtn->lpsctIcon->sSourcePath    = "resource\\image\\popup\\next_yajirushi.png";
    lpOffBtn->lpsctIcon->dwWidthPx      = ( DWORD ) 25;
    lpOffBtn->lpsctIcon->dwIconAlign    = IMAGE_ALIGN_HRIGHT | IMAGE_ALIGN_VCENTER;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwTextColor            = ( DWORD ) 0x333333;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x979781;
    lpActiveBtn->sctBorder.dwColor      = ( DWORD ) 0x262626;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0xa4a595;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x606052;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_vio_disabled
VOID CCssStore::CreateCss_popup_btn_vio_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_vio_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x815b4b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xb9826c;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6a4e43 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xb8998d );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}

//////////////////////////////////////////////////////////////////////////
// Create css name: popup_btn_vio_off
VOID CCssStore::CreateCss_popup_btn_vio_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["popup_btn_vio_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xb9826c;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x5f4236 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xd6b5a7 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x8b6251;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x816e66;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x52392f;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

VOID CCssStore::CreateCss_center_disp_btn_line_kikaku_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_kikaku_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) VALUE_COLOR_TRANSPARENT;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

VOID CCssStore::CreateCss_center_disp_btn_line_kikaku_off2()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_kikaku_off2"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xffffff;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

VOID CCssStore::CreateCss_center_disp_btn_line_kikaku_off3()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_kikaku_off3"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x00ffff;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

VOID CCssStore::CreateCss_center_disp_btn_line_kikaku_off4()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_kikaku_off4"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x008000;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

VOID CCssStore::CreateCss_center_disp_btn_line_kikaku_off5()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_kikaku_off5"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x78834a;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

VOID CCssStore::CreateCss_center_disp_btn_line_kikaku_off6()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_kikaku_off6"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xbc7200;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

VOID CCssStore::CreateCss_center_disp_btn_line_kikaku_off7()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_kikaku_off7"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xa7803d;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

VOID CCssStore::CreateCss_center_disp_btn_line_kikaku_off8()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_kikaku_off8"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x0000ff;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

VOID CCssStore::CreateCss_center_disp_btn_line_kikaku_off9()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_kikaku_off9"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xcbc0ff;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

VOID CCssStore::CreateCss_center_disp_btn_line_kikaku_off10()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_kikaku_off10"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x00aff6;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x89fad6;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

// Start ThietNP 20150727: Update CSS V20.24
VOID CCssStore::CreateCss_center_disp_btn_left_lgrn_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_left_lgrn_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x000000;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc9c9ab;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_LEFT | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x635d4a );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xdbddc9 );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9c9c8c;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x7e8473;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x6a716a;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

VOID CCssStore::CreateCss_center_disp_btn_left_lgrn_disabled()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_left_lgrn_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x9b9b8b;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xc6ceb5;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_LEFT | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -5, ( DWORD )  2, ( DWORD ) 0x747c6c );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  5, ( DWORD )  2, ( DWORD ) 0xdfd6cf );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}
VOID CCssStore::CreateCss_center_disp_btn_line_metro_off()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_metro_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0xffcb27;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}
VOID CCssStore::CreateCss_center_disp_btn_line_metro_off2()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_metro_off2"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x2128d1;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

VOID CCssStore::CreateCss_center_disp_btn_line_metro_off3()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_metro_off3"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x009df4;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x9d9d9d;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}

VOID CCssStore::CreateCss_center_disp_btn_line_metro_off4()
{
    CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["center_disp_btn_line_metro_off4"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0x4a4a4a;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xd1d1d1;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x262626;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x756467 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xe8e8e8 );

    lpOffBtn->lpSctLine = new SCT_HR_LINE();
    lpOffBtn->lpSctLine->dwWidthPer     = ( DWORD ) 90;
    lpOffBtn->lpSctLine->dwBottomPx     = ( DWORD ) 7;
    lpOffBtn->lpSctLine->dwLeftPer      = ( DWORD ) 5;
    lpOffBtn->lpSctLine->dwHeightPx     = ( DWORD ) 4;
    lpOffBtn->lpSctLine->dwBkgCorlor    = ( DWORD ) 0x009df4;

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x2159ad;
    lpActiveBtn->vBoxShadow[0].lHShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].lVShadow = ( LONG )  -1;
    lpActiveBtn->vBoxShadow[0].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[0].dwColor  = ( DWORD ) 0x4f967f;
    lpActiveBtn->vBoxShadow[1].lHShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].lVShadow = ( LONG )  1;
    lpActiveBtn->vBoxShadow[1].dwBlur   = ( DWORD ) 1;
    lpActiveBtn->vBoxShadow[1].dwColor  = ( DWORD ) 0x84a299;

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}
// End ThietNP 20150727: Update CSS V20.24

// Start ThietNP 20150817: Update CSS version 20.32a
VOID CCssStore::CreateCss_const_btn_btn_dsky_off()
{
	CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_dsky_off"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xffffff;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xbd8e2f;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) FW_BOLD;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x503f1b );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xd8ba7b );

    lpCssFullBtn->lpCssActive = lpActiveBtn = new CCssButton();
    *lpActiveBtn = *lpOffBtn;
    lpActiveBtn->dwBkgColor             = ( DWORD ) 0x8e6B23;
    lpActiveBtn->vBoxShadow[0]          = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x89795b );
    lpActiveBtn->vBoxShadow[1]          = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0x3e3015 );

    lpCssFullBtn->lpCssDisable = lpDisableBtn = new CCssButton();
    *lpDisableBtn = *lpOffBtn;
}
VOID CCssStore::CreateCss_const_btn_btn_dsky_disabled()
{
	CCssFullBtn* lpCssFullBtn = NULL;
    CCssButton*  lpOffBtn     = NULL;
    CCssButton*  lpDisableBtn = NULL;
    CCssButton*  lpActiveBtn  = NULL;

    m_mCssMap["const_btn_btn_dsky_disabled"] = lpCssFullBtn = new CCssFullBtn;
    lpOffBtn          = lpCssFullBtn;

    lpOffBtn->dwTextColor               = ( DWORD ) 0xd4b576;
    lpOffBtn->dwBkgColor                = ( DWORD ) 0xbd8e2f;
    lpOffBtn->dwTextAlign               = ( DWORD ) ( DT_CENTER | DT_VCENTER );
    lpOffBtn->fLineHeight               = ( FLOAT ) 1.1f;
    lpOffBtn->dwFontWeight              = ( DWORD ) 100;
    lpOffBtn->sctBorder.dwColor         = ( DWORD ) 0x333333;
    lpOffBtn->sctBorder.dwWidth         = ( DWORD ) 1;
    lpOffBtn->sctBorder.dwBorderRadius  = ( DWORD ) 5;

    lpOffBtn->vBoxShadow.resize(( size_t ) 2 );

    lpOffBtn->vBoxShadow[0]             = SCT_BOX_SHADOW(( LONG ) -2, ( LONG ) -4, ( DWORD )  2, ( DWORD ) 0x6f5b30 );
    lpOffBtn->vBoxShadow[1]             = SCT_BOX_SHADOW(( LONG )  2, ( LONG )  4, ( DWORD )  2, ( DWORD ) 0xb19a6c );

    lpCssFullBtn->lpCssDisable = lpCssFullBtn; // This design css is for both normal state and disable state
}
// End ThietNP 20150817: Update CSS version 20.32a