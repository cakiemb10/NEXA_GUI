#include "stdafx.h"
#include "GUIDAreaStore.h"
#include "GUIDConstant.h"
#include "GUIDArea.h"


CAreaStore::CAreaStore( CWnd* lpGuiViewDlg )
: m_cTopIframe( IDD_TOPIFRAME_BUFFER1, lpGuiViewDlg )
{                      
    m_lpGuiViewDlg = lpGuiViewDlg;
    m_lpParentWnd  = lpGuiViewDlg;
    m_lCurrentPopupLayer = POPUP_LAYER_SECOND;       
    m_vCurAreas.clear();
    m_vCurAreas.push_back( new CArea() ); 
    m_vCurAreas.push_back( new CArea() );
    m_dwCurGyomuMode = 0;

#if 0
    OSVERSIONINFO	vi;
    memset( &vi, 0, sizeof vi );
    vi.dwOSVersionInfoSize = sizeof vi;
    GetVersionEx( &vi );

    if ( vi.dwPlatformId == VER_PLATFORM_WIN32_NT  &&  vi.dwMajorVersion >= 6 )
    {
        m_bIsWinVistaOrLater = TRUE;
    }
    else
    {
        m_bIsWinVistaOrLater = FALSE;
    }
#endif
}


CAreaStore::~CAreaStore()
{
    try
    { // Do all works in this TRY block
        // Clear current areas
        DWORD dwIndex;
        for ( dwIndex = 0; dwIndex < m_vCurAreas.size(); dwIndex++ )
        {
            if ( m_vCurAreas[dwIndex] != NULL )
            {
                m_vCurAreas[dwIndex]->ClearArea();
                delete m_vCurAreas[dwIndex];
            }
            else {} // Do nothing
        }

        for ( dwIndex = 0; dwIndex < m_vPopupDlg.size(); ++dwIndex )
        {
            m_vPopupDlg[dwIndex]->DestroyWindow();
            delete m_vPopupDlg[dwIndex];
        }
        m_vPopupDlg.clear();
        m_vCurAreas.clear();
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what();
    }
}


VOID CAreaStore::DisplayGyomu1( )
{
    // Initialize
    AREA_ENUM listArea[] = { E_AREA_INDICATOR, E_AREA_BUSSINESS, E_AREA_CENTERDISP, E_AREA_CONST_BTN };
    CreateGyomu( listArea, ARRAY_LENGTH( listArea ), GYOMU_TYPE_1 );
}


VOID CAreaStore::DisplayGyomu2( )
{
    AREA_ENUM listArea[] = { E_AREA_INDICATOR, E_AREA_BUSSINESS, E_AREA_DISP, E_AREA_OPERATING, E_AREA_CONST_BTN };
    CreateGyomu( listArea, ARRAY_LENGTH( listArea ), GYOMU_TYPE_2 );
}

VOID CAreaStore::DisplayGyomu3( )
{
    AREA_ENUM listArea[] = { E_AREA_INDICATOR, E_AREA_BUSSINESS, E_AREA_CENTERDISP, E_AREA_CONST_BTN };
    CreateGyomu( listArea, ARRAY_LENGTH( listArea ), GYOMU_TYPE_3 );
}


void CAreaStore::CreateGyomu( AREA_ENUM listArea[], DWORD dwListSize, DWORD dwGyomuMode )
{
    auto vAreaTemp = m_vCurAreas;
    DWORD dwIndex = 0;
    DWORD dwCurAreaIndex = 0;
    vector<BOOL> vIncluded;
    AREA_ENUM eAreaType;

    vIncluded.resize( m_vCurAreas.size() );
    vAreaTemp.resize((DWORD)( dwListSize + 2 )); // 2 more pop-up

    m_dwCurGyomuMode = dwGyomuMode;

    for ( dwIndex = 0; dwIndex < dwListSize; ++dwIndex )
    {
        eAreaType = listArea[dwIndex];
        dwCurAreaIndex = FindAreaIndex( eAreaType );
        if ( dwCurAreaIndex >= m_vCurAreas.size() )
        {
            vAreaTemp[GetAreaIndex( eAreaType )] = new CArea();
        }
        else
        {
            vAreaTemp[GetAreaIndex( eAreaType )] = m_vCurAreas[dwCurAreaIndex];
            vIncluded[dwCurAreaIndex] = TRUE;
        }
    }
    if ((( vAreaTemp.size() - 2 )  >= 0 ) && (( vAreaTemp.size() - 1 ) >= 0 ))
    {
        vAreaTemp[vAreaTemp.size() - 2] = m_vCurAreas[m_vCurAreas.size() - 2]; // Copy 2 Pop-Up
        vAreaTemp[vAreaTemp.size() - 1] = m_vCurAreas[m_vCurAreas.size() - 1];
    }
    for ( dwIndex = 0; ( LONG ) dwIndex < ( LONG ) m_vCurAreas.size() - 2; ++dwIndex )
    {
        if ( vIncluded[dwIndex] == FALSE )
        {
            m_vCurAreas[dwIndex]->ClearArea();
            delete m_vCurAreas[dwIndex];
        }
        else {} // Do nothing
    }

    m_vCurAreas = vAreaTemp;
}

DWORD CAreaStore::FindAreaIndex( AREA_ENUM eInAreaType )
{
    DWORD dwIndex = 0;
    for ( dwIndex = 0; dwIndex < m_vCurAreas.size(); ++dwIndex )
    {
        if ( m_vCurAreas[dwIndex]->m_sctAreaInfo.eAreaType == eInAreaType )
        {
            break;
        }
        else {} // Do nothing
    }
    return dwIndex;
}

BOOL CAreaStore::ChangeArea( AREA_ENUM eArea, string sAreaFuncName )
{
    // Local variable
    string            sKey         = "";
    DWORD             dwIdx        = 0;
    FTN_MAP::iterator it;
    BOOL              bRes         = FALSE;
    LONG              lBackupLayer = 0;

    //TRACE("Change Area: %s\n", sAreaFuncName.c_str());
    dwIdx = GetAreaIndex( eArea );

    if ( dwIdx == AREA_INDEX_NON )
    {
        return FALSE;
    }
    else {} // Do nothing

    // LiemTT 20150504 Fix comment list 154
    if ( eArea == E_AREA_POPUP && m_vCurAreas[dwIdx]->m_sctAreaInfo.sAreaFuncName == sAreaFuncName )
    {
        m_vPopupDlg[m_lCurrentPopupLayer]->CreateTopItem(); // Create top Item for prevent items self draw
        lBackupLayer = m_lCurrentPopupLayer;
        m_lCurrentPopupLayer = POPUP_MAX_LAYER;
        m_vCurAreas.push_back( NULL );

        it = m_mapFn.find( sAreaFuncName );

        if ( it == m_mapFn.end() )
        {
            CreateDymmyAreaNotExisted( eArea, sAreaFuncName );
            bRes = FALSE;
        }
        else
        {
            ( this->*m_mapFn[sAreaFuncName] )( );
            bRes = TRUE;
        }
        m_vCurAreas[dwIdx]->RefreshArea( m_vCurAreas.back());

        m_lCurrentPopupLayer = lBackupLayer;
        m_vCurAreas.back()->ClearArea();
        delete m_vCurAreas.back();
        m_vCurAreas.pop_back();
        return TRUE;
    } 
    else {} // Do nothing
#if 0
    if ( eArea == E_AREA_POPUP && m_bIsWinVistaOrLater == FALSE ) // Using for windows xp
    {
        DeleteOldPopup();
        
        m_pOldPopup = m_vPopupDlg[m_lCurrentPopupLayer];
        m_pOldPopup->UpdateWindow();
        m_vPopupDlg[m_lCurrentPopupLayer] = new CPopupDlg;
        m_vPopupDlg[m_lCurrentPopupLayer]->Create( IDD_POPUP_DIALOG, m_lpGuiViewDlg );
        m_vPopupDlg[m_lCurrentPopupLayer]->ShowWindow( SW_HIDE );
        m_vCurAreas[dwIdx] = NULL;
    } 
    else {} // Do nothing
#endif

    // End fix
   
    if ( m_vCurAreas.size( ) > dwIdx )
    {
        if ( m_vCurAreas[dwIdx] != NULL )
        {
            m_vCurAreas[dwIdx]->ClearArea( );
            delete m_vCurAreas[dwIdx];
            m_vCurAreas[dwIdx] = NULL;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        m_vCurAreas.resize( dwIdx + 1);
    }

    it = m_mapFn.find( sAreaFuncName );

    if ( it == m_mapFn.end( ) )
    {
        CreateDymmyAreaNotExisted( eArea, sAreaFuncName );
        bRes = FALSE;
    }
    else
    {
        ( this->*m_mapFn[sAreaFuncName] )( );
        bRes = TRUE;
    }


    if ( m_vCurAreas[dwIdx] == NULL )
    {
        return FALSE;
    }
    else
    {
        // Do nothing
    }

    m_vCurAreas[dwIdx]->m_sctAreaInfo.sAreaFuncName = sAreaFuncName;

    if ( eArea == E_AREA_POPUP )
    {
        m_vPopupDlg[m_lCurrentPopupLayer]->m_lpcMainArea = m_vCurAreas[dwIdx];
        m_vPopupDlg[m_lCurrentPopupLayer]->CreateTopItem();
        if (( m_vCurAreas[dwIdx]->m_cItemBkg.m_sctProperty.sClass == "background_color_translucent" ) || 
            ( m_vCurAreas[dwIdx]->m_cItemBkg.m_sctProperty.sClass == "background_color_clear" ))
        {
            GetActiveTopIframe()->UpdateWindow();
            m_vPopupDlg[m_lCurrentPopupLayer]->ShowWindow( SW_HIDE );
        }
        else {} // Do nothing
    }
    else
    {
        if ( DRAW_TOPIFRAME_PREVENT_CLICKER == TRUE )
        {
            m_cTopIframe.CreateTopItem();
        }
        else {} // Do nothing
    }

    return bRes;
}
#if 0
void CAreaStore::DeleteOldPopup()
{
    if ( m_pOldPopup )
    {
        m_pOldPopup->ShowWindow( SW_HIDE );
        if ( m_pOldPopup->m_lpcMainArea )
        {
            m_pOldPopup->m_lpcMainArea->ClearArea();
            delete m_pOldPopup->m_lpcMainArea;
            m_pOldPopup->m_lpcMainArea = NULL;
        } 
        else {} // Do nothing
        delete m_pOldPopup;
        m_pOldPopup = NULL;
    } 
    else {} // Do nothing
}
#endif

DWORD CAreaStore::GetAreaIndex( AREA_ENUM eArea )
{
//    return 0;
    static BOOL     bIsFirst = TRUE;
    // Static index values
    static map<AREA_ENUM, DWORD>    dw_AreaIdx[3];
    map<AREA_ENUM, DWORD>::iterator it;
    // Check is first time call to this function
    if ( bIsFirst == TRUE )
    {
        // Order of Gyomu mode 1
        dw_AreaIdx[0][E_AREA_INDICATOR] = 0;
        dw_AreaIdx[0][E_AREA_BUSSINESS] = 1;
        dw_AreaIdx[0][E_AREA_CENTERDISP] = 2;
        dw_AreaIdx[0][E_AREA_CONST_BTN] = 3;
        //dw_AreaIdx[0][E_AREA_POPUP]     = 4;

        // Order of Gyomu mode 2
        dw_AreaIdx[1][E_AREA_INDICATOR] = 0;
        dw_AreaIdx[1][E_AREA_BUSSINESS] = 1;
        dw_AreaIdx[1][E_AREA_DISP] = 2;
        dw_AreaIdx[1][E_AREA_OPERATING] = 3;
        dw_AreaIdx[1][E_AREA_CONST_BTN] = 4;
        //dw_AreaIdx[1][E_AREA_POPUP]     = 5;

        // Order of Gyomu mode 3
        dw_AreaIdx[2][E_AREA_INDICATOR] = 0;
        dw_AreaIdx[2][E_AREA_BUSSINESS] = 1;
        dw_AreaIdx[2][E_AREA_CENTERDISP] = 2;
        dw_AreaIdx[2][E_AREA_CONST_BTN] = 3;
        //dw_AreaIdx[2][E_AREA_POPUP]     = 4;

        bIsFirst = FALSE;
    }
    else
    {
        // Do nothing
    }

    if ( eArea == E_AREA_POPUP )
    {
        if ( m_lCurrentPopupLayer == POPUP_ACTIVE_NON )
        {
            return AREA_INDEX_NON;
        } 
        else {} // Do nothing
        if (( m_dwCurGyomuMode - 1 ) >= 0 )
        {
            return dw_AreaIdx[m_dwCurGyomuMode - 1].size() + m_lCurrentPopupLayer;
        }
        else
        {
            return AREA_INDEX_NON;
        }
    }
    else {} // Do nothing
    if ((m_dwCurGyomuMode - 1) >= 0 )
    {
        it = dw_AreaIdx[m_dwCurGyomuMode - 1].find( eArea );
        if ( it == dw_AreaIdx[m_dwCurGyomuMode - 1].end())
        {
            return AREA_INDEX_NON;
        } 
        else {} // Do nothing

        return it->second;
    }
    else
    {
        return AREA_INDEX_NON;
    }
}


POINT CAreaStore::GetAreaPos( AREA_ENUM eAreaType )
{
    //POINT           pPos;      // Return value

    static BOOL     bIsFirst = TRUE;
    // Static position values
    static map<AREA_ENUM, POINT>   P_Gyomu[3];

    // Check is first time call to this function
    if ( bIsFirst == TRUE )
    {
        // Layout of Gyomu mode 1
        P_Gyomu[0][E_AREA_INDICATOR] = CPoint( 0, 0 );
        P_Gyomu[0][E_AREA_BUSSINESS] = CPoint( 8, 48 );
        P_Gyomu[0][E_AREA_CENTERDISP] = CPoint( 8, 88 );
        P_Gyomu[0][E_AREA_CONST_BTN] = CPoint( 8, 600 );

        // Layout of Gyomu mode 2
        P_Gyomu[1][E_AREA_INDICATOR] = CPoint( 0, 0 );
        P_Gyomu[1][E_AREA_BUSSINESS] = CPoint( 8, 48 );
        P_Gyomu[1][E_AREA_DISP] = CPoint( 8, 88 );
        //P_Gyomu[1][E_AREA_OPERATING] = CPoint( 536, 88 );
        P_Gyomu[1][E_AREA_OPERATING] = CPoint( 537, 88 );       // Shift right 1px
        P_Gyomu[1][E_AREA_CONST_BTN] = CPoint( 8, 668 );

        // Layout of Gyomu mode 3
        P_Gyomu[2][E_AREA_INDICATOR] = CPoint( 0, 0 );
        P_Gyomu[2][E_AREA_BUSSINESS] = CPoint( 8, 48 );
        P_Gyomu[2][E_AREA_CENTERDISP] = CPoint( 8, 88 );
        P_Gyomu[2][E_AREA_CONST_BTN] = CPoint( 8, 668 );

        bIsFirst = FALSE;
    }
    else
    {
        // Do nothing
    }
    if (( m_dwCurGyomuMode - 1 ) >= 0 )
    {
        return P_Gyomu[m_dwCurGyomuMode - 1][eAreaType];
    }
    else
    {
        return CPoint ( 0, 0 );
    }
}

void CAreaStore::CreateDymmyAreaNotExisted( AREA_ENUM eArea, string sAreaFuncName )
{
    DWORD       dwIdx = GetAreaIndex( eArea );
    vector<SCT_SPAN> vEmptySpan;

    if ( m_vCurAreas[dwIdx] != NULL )
    {
        return;
    } 
    else {} // Do nothing
    m_vCurAreas[dwIdx] = new CArea();
    CPoint point =  GetAreaPos( eArea );
    
    CItem* lpcItem = new CRichLabel();

    if ( sAreaFuncName != "" )
    {
        sAreaFuncName += " is not existed.!!";
    } 
    else {} // Do nothing
    

    lpcItem->SetProperties( 2, 777777, "div", sAreaFuncName.c_str(), 10, 10, 480, 28, 1, 0, 0,
        "sts_idication_fix_wht_c_off", "", "div_24", "", "", "sts_idication_fix_wht_c_off", "", "false", "off",
        0, 0, "", "", "", "", "", "sts_idication_fix_wht_c_off", "",
        18, 0, -1, -1, "", "", 0, vEmptySpan, "", "", eArea, 1, -1 , 0, 0 );

    m_vCurAreas[dwIdx]->m_vItemList.push_back( lpcItem );
    m_vCurAreas[dwIdx]->m_sctAreaInfo.pPosition = GetAreaPos( eArea );
    if ( eArea != E_AREA_POPUP )
    {
        m_vCurAreas[dwIdx]->m_lpcParent = m_lpParentWnd;
    }
    else 
    {
        m_vCurAreas[dwIdx]->m_lpcParent = GetActivePopup();
        m_vCurAreas[dwIdx]->m_sctAreaInfo.dwWidth = 1024;
        m_vCurAreas[dwIdx]->m_sctAreaInfo.dwHeight = 768;
    }
    
    m_vCurAreas[dwIdx]->CreateArea( );
}

void CAreaStore::CreateTopIframeBuffer()
{
    m_cTopIframe.Create( IDD_TOPIFRAME_BUFFER1, m_lpGuiViewDlg );
    m_cTopIframe.ShowWindow( SW_SHOW );

    m_vPopupDlg.resize( POPUP_MAX_LAYER );
    for ( DWORD dwIndex = 0; dwIndex < POPUP_MAX_LAYER; ++dwIndex )
    {
        m_vPopupDlg[dwIndex] = new CPopupDlg;
        m_vPopupDlg[dwIndex]->Create( CPopupDlg::IDD, m_lpGuiViewDlg );
    }

    m_lpParentWnd = &m_cTopIframe;
}

CTopIframe* CAreaStore::GetActiveTopIframe()
{
    return &m_cTopIframe;
}

CPopupDlg* CAreaStore::GetActivePopup( )
{
    if (( m_lCurrentPopupLayer == POPUP_ACTIVE_NON ) || (( LONG ) m_vPopupDlg.size( ) <= m_lCurrentPopupLayer ))
    {
        return NULL;
    } 
    else {} // Do nothing
    return m_vPopupDlg[m_lCurrentPopupLayer];
}

BOOL CAreaStore::HideActivePopup()
{
    CWnd* lpActivePopup = GetActivePopup();
    if (lpActivePopup == NULL )
    {
        return FALSE;
    } 
    else {} // Do nothing

    lpActivePopup->ShowWindow( SW_HIDE );
    m_lCurrentPopupLayer--;

    return TRUE;
}

BOOL CAreaStore::ShowPopupByLayer( DWORD dwInLayer, BOOL bIsShow /*= TRUE */ )
{
    if (m_vPopupDlg.size() <= dwInLayer)
    {
        return FALSE;
    } 
    else {} // Do nothing    
    
    m_vPopupDlg[dwInLayer]->ShowWindow( bIsShow );
    if ( bIsShow == FALSE )
    {
        if ( dwInLayer == POPUP_LAYER_TOP )
        {
            m_vPopupDlg[POPUP_LAYER_SECOND]->EnableWindow( TRUE );
            m_vPopupDlg[POPUP_LAYER_SECOND]->UpdateWindow();
        }
        else
        {
            GetActiveTopIframe()->EnableWindow( TRUE );
        }
    }

    return TRUE;
}

VOID CAreaStore::SetPopupLayer( DWORD dwPopupLayer )
{
    m_lCurrentPopupLayer = dwPopupLayer;
}

BOOL CAreaStore::HasShowingPopUp()
{
    DWORD dwIndex = 0;
    BOOL bHasShowingPopup = FALSE;
    for ( dwIndex = 0; dwIndex < POPUP_MAX_LAYER; ++dwIndex )
    {
        if ( m_vPopupDlg[dwIndex]->IsWindowVisible())
        {
            bHasShowingPopup = TRUE;
        } 
        else {} // Do nothing
    }
    return bHasShowingPopup;
}

