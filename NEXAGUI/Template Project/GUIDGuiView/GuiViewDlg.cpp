
// GuiViewDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GuiView.h"
#include "GuiViewDlg.h"
#include "resource.h"
#include "afxdialogex.h"
#include <locale.h>
#include <afx.h>
#include <string>
#include <iostream>

#include <gdiplus.h>

using namespace Gdiplus;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning ( disable: 4100) // Disable warning unreferenced formal parameter

// CGuiViewDlg dialog

SCT_DATE             gsctOperationDate;                     // Operation date global parameter
vector<SCT_DATE>     gsctHolidayArray;                      // Holiday array global parameter
SCT_DATE             gsctBasicDate;                         // Basic Date
SCT_DATE             gsctStartDate;                         // Start Date
SCT_DATE             gsctEndDate;                           // End Date
SCT_DATE             gsctDispDate;                          // Display Date;
CItem*               gclInputItemTag = NULL;                // Input Item
SCT_FORMAT_TABLE     gsctInputFormat;                       // Input Item format
string               gsViewErrorDesign;                    // Display Error Design
DWORD                gdwViewErrorBlinkCnt;                  // Blink count
DWORD                gdwViewErrorResolutive;                // View Error Resolutive
DWORD                gdwFlgDispZeroPadding;                 // Displaying Zero Padding    
vector<string>       gsInputItemBeforeData;                 // Array of previous data of input items
BOOL                 gbInputItemFirstInitializationFlg;     // Flag to check whether Input Item is First initialization or not
CItem*               gclCursorImageTag = NULL;
LONG                 glRelativeCurPos;
AREA_ENUM            geInputItemArea;                        // Area type of input item
BOOL                 gbPageChageLoadFlg = FALSE;             // Flag to check load page change or not
LONG                 glWaitResponseDenbunNo = -1;            // Message number of message that is being waited
BOOL                 gSetHolidayDispTimer   = FALSE;

CGuiViewDlg::CGuiViewDlg( CWnd* pParent /*=NULL*/ )
: CDialogEx( CGuiViewDlg::IDD, pParent ),
m_cAreaStore( this ),
m_vCurAreas( m_cAreaStore.m_vCurAreas ),
m_vPopupDlg( m_cAreaStore.m_vPopupDlg ),
m_dwCurGyomuMode( m_cAreaStore.m_dwCurGyomuMode ),
m_pInitDlg( NULL ),
m_bIsForceUpdateTime( FALSE ),
m_bIsClosed( FALSE )
{
    m_dwCurTimerID          = 0;
    m_dwTimerCursorCounter  = 0;
    m_bIsCurWaitPopup       = FALSE;

    for ( LONG idx = 0; idx < ( ( LONG ) sizeof( m_bySendData ) / ( LONG ) sizeof( m_bySendData[0] ) ); idx++ )
    {
        m_bySendData[idx] = 0;
    }

    for ( LONG idx = 0; idx < ( ( LONG ) sizeof( m_byRevData ) / ( LONG ) sizeof( m_byRevData[0] ) ); idx++ )
    {
        m_byRevData[idx] = 0;
    }

    //_CrtSetBreakAlloc( 23791 );
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    //m_dwNumberOfPopup = 0;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    //<TSDV-BugNo146-20150424-ThietNP- Initialize area size>
    // Gyomu layout
    // Gyomu 1
    CArea::gSzArea[0][0] = CSize( 1008, 44 );
    CArea::gSzArea[0][1] = CSize( 1008, 40 );
    CArea::gSzArea[0][2] = CSize( 1008, 512 );
    CArea::gSzArea[0][3] = CSize( 1008, 164 );
    CArea::gSzArea[0][4] = CSize( 0, 0 );           // No thing

    // Gyomu 2
    CArea::gSzArea[1][0] = CSize( 1008, 44 );
    CArea::gSzArea[1][1] = CSize( 1008, 40 );
    // TSDV-LiemTT modify
#if 0
    CArea::gSzArea[1][2] = CSize( 528, 512 );
    CArea::gSzArea[1][3] = CSize( 480, 512 );
    CArea::gSzArea[1][4] = CSize( 1008, 164 );
#endif
    CArea::gSzArea[1][2] = CSize( 528, 580 );
    CArea::gSzArea[1][3] = CSize( 480, 580 );
    CArea::gSzArea[1][4] = CSize( 1008, 96 );
    // TSDV-LiemTT end modify

    // Gyomu 3
    CArea::gSzArea[2][0] = CSize( 1008, 44 );
    CArea::gSzArea[2][1] = CSize( 1008, 40 );
    CArea::gSzArea[2][2] = CSize( 1008, 580 );
    CArea::gSzArea[2][3] = CSize( 1008, 96 );
    CArea::gSzArea[2][4] = CSize( 0, 0 );           // No thing
    //< TSDV-BugNo146-20150424 - End>
}

CGuiViewDlg::~CGuiViewDlg()
{
    try
    {
        // m_vCurAreas.clear();
        //delete m_lpBkg;
        CCssStore::DestroyInstance();
        if (m_pInitDlg != NULL)
        {
            if ( IsWindow( m_pInitDlg->m_hWnd ))
            {
                m_pInitDlg->DestroyWindow();
            }
            else
            {}
            delete m_pInitDlg;
        }
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what();
    }
}

void CGuiViewDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGuiViewDlg, CDialogEx)
    ON_WM_CLOSE()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_NCHITTEST()
    ON_WM_TIMER()
    ON_WM_COPYDATA()
    ON_WM_DESTROY()
    ON_MESSAGE( CREATE_TOP_IFRAME_BUFFER, &CGuiViewDlg::OnCreateTopIframeBuffer )
    ON_MESSAGE( POPUP_CLICK_ITEM, &CGuiViewDlg::OnPopupClickItem )
    ON_MESSAGE( RECEIVE_MSG_FROM_VIEW_IF, &CGuiViewDlg::OnReceiveMsgFromViewIf )
    ON_MESSAGE( NEXA_MSG_REFRESH_CUSOR, &CGuiViewDlg::OnNexaMsgRefreshCusor )
    //ON_MESSAGE( NEXA_MSG_UPDATE_ABOVE_ITEMS, &CGuiViewDlg::OnNexaMsgUpdateAboveItems ) // No need to use this message
END_MESSAGE_MAP()


// CGuiViewDlg message handlers

BOOL CGuiViewDlg::OnInitDialog()
{
    // Initialize default
    CDialogEx::OnInitDialog();
    HWND                    hWnd = NULL;

    setlocale( LC_ALL, "japanese" );

    // Initialize members
    m_dwCurGyomuMode = GYOMU_TYPE_1;
    MoveWindow( 0, 0, 0, 0, TRUE );
    SetWindowText( NEXA_VIEW_WINDOW_NAME );

    m_cAreaStore.CreateFuncMap();

    LPDWORD lpDWORD = (LPDWORD) &m_bySendData;
    //while ( hWnd == NULL )
    //{
        Sleep( 500UL );

        hWnd = ::FindWindow( NULL, GUI_VIEWIF_WND_TITLE );
        if ( hWnd != NULL )
        {
            *lpDWORD = 2;
            SendData( ( DWORD ) sizeof( DWORD ) );
        }
        else
        {
            // Do nothing
        }
    //}
    m_bIsClosed = FALSE;
    SetTimer( ( DWORD ) ( NEXA_TIMER_DATE_TIME ), ( DWORD ) ( TIMER_SET_CLOCK_DISP ), NULL );
    PostMessage( WM_TIMER, NEXA_TIMER_DATE_TIME, 0 );
    PostMessage( CREATE_TOP_IFRAME_BUFFER, 0, 0 );
    return TRUE;  // return TRUE  unless you set the focus to a control
}



afx_msg LRESULT CGuiViewDlg::OnCreateTopIframeBuffer( WPARAM wParam, LPARAM lParam )
{
    m_cAreaStore.CreateTopIframeBuffer();
    DisplayGyomu1();

    m_pInitDlg = new CInitScreen();
    m_pInitDlg->Create( ( DWORD ) IDD_DIALOG2, this );    
    m_pInitDlg->SetWindowPos( &wndTop, 0, 0, 1024, 768, SWP_SHOWWINDOW ); 

    return 0L;
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGuiViewDlg::OnPaint()
{
    CPaintDC dc(this);

    if (IsIconic())
    {
        // Do nothing
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

void CGuiViewDlg::OnTimer( UINT_PTR nIDEvent )
{
    // TODO: Add your message handler code here and/or call default
    if ( nIDEvent == m_dwCurTimerID )
    {
        BlinkCursorTimer();
    } 
    else if ( nIDEvent == DISP_HOLIDAY_TIMER )
    {
        CtrlDispHolidayFunc();
    }
    else if ( nIDEvent == NEXA_TIMER_DATE_TIME )
    {
        DispClockFunc();
    }
    else { }

    CDialogEx::OnTimer( nIDEvent );
}


void CGuiViewDlg::BlinkCursorTimer()
{
    if ( m_dwTimerCursorCounter % 4 == 0 )
    {
        if ( IsWindow( m_cCursor.m_hWnd ) )
        {
            m_cCursor.ShowWindow( SW_SHOW );
        }
        else {} // Do nothing
    } 
    else {} // Do nothing
    
    if ( m_dwTimerCursorCounter % 4 == 3 )
    {
        if ( IsWindow( m_cCursor.m_hWnd ) )
        {
            m_cCursor.ShowWindow( SW_HIDE );
        }
        else {} // Do nothing
    }
    else {} // Do nothing
    m_dwTimerCursorCounter++;
}

void CGuiViewDlg::DispClockFunc()
{
    CTime cCurrentTime;
    string strDateDisp = "";
    string strTimeDisp = "";

    SCT_DATE sctDate;

    vector<CItem*>      vItemDate;
    vector<CItem*>      vItemTime;

    vItemDate.clear();
    vItemTime.clear();
    
    ZeroMemory( &sctDate, sizeof( sctDate ) );

    cCurrentTime     = CTime::GetCurrentTime();
    sctDate.wYear    = ( WORD ) cCurrentTime.GetYear();
    sctDate.byMonth  = ( BYTE ) cCurrentTime.GetMonth();
    sctDate.byDay    = ( BYTE ) cCurrentTime.GetDay();
    sctDate.wHour    = ( WORD ) cCurrentTime.GetHour();
    sctDate.wMinutes = ( WORD ) cCurrentTime.GetMinute();
    sctDate.wSecond  = ( WORD ) cCurrentTime.GetSecond();
    
    vItemDate = SearchTagIDFunc( TAG_ID_NAME_CLOCK_DAY, E_AREA_INDICATOR );

    if ( vItemDate.size() == 0 )
    {
        return;
    }
    else 
    {
        // Do nothing
    }


    vItemTime = SearchTagIDFunc( TAG_ID_NAME_CLOCK_TIME, E_AREA_INDICATOR );
    if ( vItemTime.size() == 0 )
    {
        return;
    }
    else 
    {
        // Do nothing
    }

    // Set date
    strDateDisp = ConvDateFormatFunc( sctDate, CLOCK_DAY_FORMAT );
    if ( vItemDate.size() == 0 )
    {
        // Do nothing
    }
    else
    {
        vItemDate[0]->ItemSetWindowText( strDateDisp );
    }

    // Set time
    strTimeDisp = setDispClockStr( sctDate );
    if ( vItemTime.size() == 0 )
    {
        // Do nothing
    }
    else
    {
        vItemTime[0]->ItemSetWindowText( strTimeDisp );
    }
}

string CGuiViewDlg::setDispClockStr( SCT_DATE sctInDate ) {
    // 変数の宣言.
    string strClockDisp = ""; // 表示時計文字列.
    string strHours = "";
    string strMinutes = "";

    // 時分は2桁のゼロ埋めで表示する.
    ConvZeroPaddingFunc( to_string( ( LONGLONG ) sctInDate.wHour ), ZERO_PADDING_NOT_AVAILABLE, 2, strHours );

    ConvZeroPaddingFunc( to_string( ( LONGLONG ) sctInDate.wMinutes ), ZERO_PADDING_AVAILABLE, 2, strMinutes );

    // 表示文字列を整形する.
    strClockDisp = strHours + ':' + strMinutes;

    return strClockDisp;
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGuiViewDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


LRESULT CGuiViewDlg::OnNcHitTest(CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    LRESULT nHitTest = CDialogEx::OnNcHitTest(point);    // Let Mfc decide where it is.
    if (nHitTest == HTCLIENT) nHitTest = HTCAPTION;        // If it was in the client, act like
    // it was in the title bar.
    //** This allows the user to drag the window by its client area **//
    return nHitTest;        // Let the framework know.
}

VOID CGuiViewDlg::OnDestroy()
{
    HideCursor();
    return CDialogEx::OnDestroy();
}

BOOL CGuiViewDlg::PreTranslateMessage( MSG* pMsg )
{
    CWnd*               pWnd            = CWnd::FromHandle( pMsg->hwnd );

    if ( pMsg->message == WM_KEYDOWN )
    {
        return TRUE;
    }
    else {} // Do nothing

    // Check event
    if ( pMsg->message == WM_LBUTTONDOWN )
    {
        BOOL                bHasPopup        = m_cAreaStore.HasShowingPopUp();
        CWnd*               pActiveTopIframe = m_cAreaStore.GetActiveTopIframe();

        if (( bHasPopup == TRUE ) &&
            (( pWnd->GetParent() == pActiveTopIframe ) || ( pWnd == m_cAreaStore.GetActiveTopIframe())))
        {
            for (DWORD dwIndex = 0U; dwIndex < POPUP_MAX_LAYER; ++dwIndex )
            {
                m_cAreaStore.GetActiveTopIframe()->SetWindowPos( m_vPopupDlg[dwIndex], 0, 0, 0, 0, ( DWORD ) ( SWP_NOMOVE | SWP_NOSIZE ) );
            }
        }
        else {} // Do nothing

        return TRUE; 
    }
    else {} // Do nothing

    return CDialogEx::PreTranslateMessage( pMsg );
}

// Popup dialog notify event click item
LRESULT CGuiViewDlg::OnPopupClickItem( WPARAM wParam, LPARAM lParam )
{
    CItem*              lpcItem         = (CItem*)wParam;
    HandleClickItem( lpcItem );
    return 1L;
}

VOID CGuiViewDlg::HandleClickItem( CItem* lpcItem )
{
    // Get TagID
    string              sTagID = lpcItem->m_sctProperty.sTagID;

    // Check whether " text CLick event is true"
    if ( lpcItem->m_sctProperty.bTextClickEvent == TRUE )
    {
        LabelOnClickProcBranchFunc( lpcItem );
    }
    else
    {
        // Check item type
        if ( lpcItem->m_sctProperty.dwType == ITEM_TYPE_BUTTON )
        {
            if ( lpcItem->m_sctProperty.sTagName == "button" )
            {
                // TODO: Call InputProcBranchFunc() function
                InputProcBranchFunc( lpcItem, lpcItem->m_sctProperty.dwClickBranchMode );
            }
            else if (( lpcItem->m_sctProperty.sTagName == "a" ))
            {
                ContenaKirikaeFunc( 
                    lpcItem->m_sctProperty.sParaContainerTagID, 
                    lpcItem->m_sctProperty.sParaStartNo, 
                    lpcItem->m_sctProperty.sParaEndNo, 
                    lpcItem );
            }
            else
            {
                // Do nothing
            }
        }
        else if ( lpcItem->m_sctProperty.dwType == ITEM_TYPE_LABEL )
        {
            if (( lpcItem->m_sctProperty.sTagName == "li" ))
            {
                TabOnClickProcBranchFunc( lpcItem );
            }
            else
            {
                // Do nothing
            }
        }
        else
        {
            // Do nothing
        }
    }
}

// Show cursor at position x,y
VOID CGuiViewDlg::ShowCursor( DWORD x, DWORD y, DWORD height, CItem* lpItem )
{
    DWORD dwVisiableFlag = 0x00000000;

    m_cCursor.m_dwX         = x;
    m_cCursor.m_dwY         = y;
    m_cCursor.m_dwHeight    = height;

    m_bIsCurWaitPopup = ( ( CTopIframe* ) _WND( lpItem )->GetParent() )->HasTopItem();

    if ( m_bIsCurWaitPopup == FALSE )
    {
        dwVisiableFlag = WS_VISIBLE;
    }
    else {} // Do nothing


    if ( IsWindow( m_cCursor.m_hWnd ) )
    {
        // Do nothing
    }
    else
    {
        m_cCursor.Create(
            "",
            ( DWORD ) ( WS_CHILD | dwVisiableFlag | SS_OWNERDRAW ),
            CRect( ( LONG ) m_cCursor.m_dwX, ( LONG ) m_cCursor.m_dwY, ( LONG ) m_cCursor.m_dwX + ( LONG ) m_cCursor.m_dwWidth, ( LONG ) m_cCursor.m_dwY + ( LONG ) m_cCursor.m_dwHeight ),
            dynamic_cast< CWnd* >( lpItem ) );
    }

    if ( m_dwCurTimerID != 0 )
    {
        m_cCursor.SetWindowPos( NULL, m_cCursor.m_dwX, m_cCursor.m_dwY, m_cCursor.m_dwWidth, m_cCursor.m_dwHeight, SWP_NOZORDER | SWP_NOACTIVATE );
    }
    else
    {
        m_dwCurTimerID = this->SetTimer( NEXA_MSG_CURSOR_TIMER, TIME_BLINK_CURSOR, NULL );
    }
}

// Hide cursor
VOID CGuiViewDlg::HideCursor()
{
    //m_cCursor.m_bBlink = FALSE;
    this->KillTimer( m_dwCurTimerID );
    m_dwCurTimerID = 0;
    m_dwTimerCursorCounter = 0;
    if ( IsWindow( m_cCursor.m_hWnd ))
    {
        m_cCursor.ShowWindow( SW_HIDE );
        m_cCursor.DestroyWindow();
    }
    else 
    {
         // Do nothing
    }
}

VOID CGuiViewDlg::ShowPopup( LONG lx, LONG ly )
{
    RECT        recMain = {0};                                      // Rect of main GUI
    CWnd*       pMainWnd = m_cAreaStore.GetActiveTopIframe();       // Main GUI
    CWnd*       pActivePopup = NULL;

    pActivePopup = GetActivePopup();

    if (( pMainWnd == NULL ) ||
        ( m_vPopupDlg.size() == 0 ) ||
        ( pActivePopup == NULL ) )
    {
        return;
    }
    else {} // Do nothing

    pMainWnd->GetWindowRect( &recMain );

    // Set position
    pMainWnd->UpdateWindow();
    pActivePopup->SetWindowPos( &wndTop, ( LONG ) recMain.left + ( LONG ) lx, ( LONG ) recMain.top + ( LONG ) ly, 0, 0, ( DWORD ) SWP_NOSIZE );
    pActivePopup->ShowWindow( SW_SHOW );
    pMainWnd->EnableWindow( FALSE );
    return;
}

CPopupDlg* CGuiViewDlg::GetActivePopup()
{
    return m_cAreaStore.GetActivePopup();
}

VOID CGuiViewDlg::HidePopup()
{
    m_cAreaStore.HideActivePopup();
}

//
//DWORD CGuiViewDlg::JudgeNumberFunc( DWORD sInputNumber )
//{
//    return JUDGE_HALF_NUMBER;
//}

DWORD CGuiViewDlg::GetGyomuType( CHAR* cPageFile )
{
    if ( strncmp( cPageFile, "gyomu_type1", strlen( "gyomu_type1" )) == 0 )
    {
        return ( DWORD ) GYOMU_TYPE_1;
    } 
    else if ( strncmp( cPageFile, "gyomu_type2", strlen( "gyomu_type2" ) ) == 0 )
    {
        return ( DWORD ) GYOMU_TYPE_2;
    }
    else if ( strncmp( cPageFile, "gyomu_type3" , strlen( "gyomu_type3" ) ) == 0 )
    {
        return ( DWORD ) GYOMU_TYPE_3;
    }
    else
    { 
        // Do nothing
    }
    return ( DWORD ) GYOMU_TYPE_NON;
}

VOID CGuiViewDlg::ClearSendData()
{
    ZeroMemory( m_bySendData, sizeof( m_bySendData ) );
}




afx_msg LRESULT CGuiViewDlg::OnReceiveMsgFromViewIf( WPARAM wParam, LPARAM lParam )
{
    COPYDATASTRUCT   *lpCopyDataStruct = ( COPYDATASTRUCT* ) wParam;
    //***this step is not necessary LIEMTT 20150604 ***
    //    new COPYDATASTRUCT;

    //lpCopyDataStruct->cbData = ((COPYDATASTRUCT*) wParam)->cbData;
    //lpCopyDataStruct->dwData = ((COPYDATASTRUCT*) wParam)->dwData;
    //lpCopyDataStruct->lpData = new BYTE[lpCopyDataStruct->cbData];

    //memcpy(lpCopyDataStruct->lpData, ((COPYDATASTRUCT*) wParam)->lpData, lpCopyDataStruct->cbData);
    //// Fix PGRelief
    //delete [](((COPYDATASTRUCT*) (wParam))->lpData);
    //delete ((COPYDATASTRUCT*) wParam);

    RequestProcBranchFunc( lpCopyDataStruct );
    // Fix PGRelief
    delete []lpCopyDataStruct->lpData;
    delete lpCopyDataStruct;

    return 0L;
}

CTopIframe* CGuiViewDlg::GetActiveTopIFrame()
{
    return m_cAreaStore.GetActiveTopIframe();
}


afx_msg LRESULT CGuiViewDlg::OnNexaMsgRefreshCusor( WPARAM wParam, LPARAM lParam )
{
    if ( IsWindow( m_cCursor.m_hWnd ))
    {
        m_cCursor.Invalidate();
        m_cCursor.ShowWindow( SW_SHOW );
        m_bIsCurWaitPopup = FALSE;
    } 
    else {} // Do nothing    

    // Hide inital screen
    if ( DRAW_TOPIFRAME_PREVENT_CLICKER == TRUE )
    {
        // This m_bIsClosed == TRUE when first screen is display.
        if ( m_bIsClosed == FALSE )
        {
            // m_pInitDlg->SetWindowPos( GetActiveTopIFrame(), 0, 0, 0, 0, SWP_NOREDRAW ); ==> Fix run on windows xp
            // GetActiveTopIFrame()->UpdateWindow();
            if ( m_pInitDlg != NULL && IsWindow( m_pInitDlg->m_hWnd ) )
            {
                m_pInitDlg->ShowWindow( SW_HIDE );
                m_pInitDlg->KillTimer( ID_TIMER_MARU );
                m_pInitDlg->KillTimer( ID_TIMER_EY5000 );
                m_bIsClosed = TRUE;
                m_pInitDlg->DestroyWindow();
            }
            else {} // Do nothing

            delete m_pInitDlg;
            m_pInitDlg = NULL;
        }
        else {} // Do nothing
    }
    else {} // Do nothing

    return 1L;
}

// Start ThietNP 2015-07-28 Comment out unused function
#if 0
afx_msg LRESULT CGuiViewDlg::OnNexaMsgUpdateAboveItems( WPARAM wParam, LPARAM lParam )
{
    CItem* lpItem = ( CItem* ) wParam;
    CArea* pArea = NULL;
    DWORD  dwIndex = 0;

    if ( lpItem == NULL )
    {
        return 1L;
    } 
    else {} // Do nothing

    if (lpItem->m_sctProperty.sTagName == "button")
    {
        return 1L;
    } 
    else {} // Do nothing
    

    
    if ( lpItem->m_sctProperty.eAreaType == E_AREA_POPUP )
    {
        for ( dwIndex = 0; dwIndex < m_cAreaStore.m_vPopupDlg.size(); ++dwIndex )
        {
            if ( _WND( lpItem )->GetParent( ) == m_cAreaStore.m_vPopupDlg[dwIndex] )
            {
                pArea = m_vPopupDlg[dwIndex]->m_lpcMainArea;
            } 
            else {} // Do nothing
            
        }
    } 
    else
    {
        pArea = GetArea( lpItem->m_sctProperty.eAreaType );
    } 
    
    if ( pArea == nullptr )
    {
        return 1L;
    } 
    else {} // Do nothing
    
    for ( dwIndex = 0; dwIndex < pArea->m_vItemList.size(); ++dwIndex )
    {
        pArea->m_vItemList[dwIndex]->UpdateItemAfterControlID( lpItem );
    }

    return 1L;
}
#endif
// End ThietNP 2015-07-28 Comment out unused function