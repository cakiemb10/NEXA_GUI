
// GuiGeneratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NEXA_GUI.h"
#include "GuiGeneratorDlg.h"
#include "afxdialogex.h"
#include "Logger.h"
#include "resource.h"
#include "Utility.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// Start TrunglV 2015-08-07 : Add remove and generate all function
extern BOOL gbRemoveMaru;
extern BOOL gbGenAll;
// End TrunglV 2015-08-07 : Add remove and generate all function
extern BOOL gbCancel;
extern HWND ghMainDlg;
extern char gsAppPath[MAX_PATH];           // Application folder path

// CGuiGeneratorDlg dialog



CGuiGeneratorDlg::CGuiGeneratorDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CGuiGeneratorDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CGuiGeneratorDlg::~CGuiGeneratorDlg()
{
    CLogger*   lpLog = NULL;
    try
    {
        CLogger::GetInstance( lpLog );
        delete lpLog;
    }
    catch ( const exception &e )
    {
    }
}

void CGuiGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGuiGeneratorDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN_SELECT_MANUAL_CATA, &CGuiGeneratorDlg::OnBnClickSelectManualCatalog)
    ON_BN_CLICKED(IDC_BTN_SELECT_AUTO_CATA, &CGuiGeneratorDlg::OnBnClickSelectAutoCatalog)
    ON_BN_CLICKED(IDC_BTN_SELECT_SCREEN_SPEC, &CGuiGeneratorDlg::OnBnClickSelectScrSpecFolder)
    ON_BN_CLICKED(IDC_BTN_SELECT_OUTPUT, &CGuiGeneratorDlg::OnBnClickSelectOutputFolder)
    ON_BN_CLICKED(IDC_BTN_GENERATE_CODE, &CGuiGeneratorDlg::OnBnClickGenerateCode)
    ON_MESSAGE(DGT_MSG, &CGuiGeneratorDlg::OnReceiveUserMsg)
// Start TrungLV 20150807: Add GenAll button
    ON_BN_CLICKED(IDC_GEN_ALL_BTN, &CGuiGeneratorDlg::OnBnClickedGenAllBtn)
// End TrungLV 20150807: Add GenAll button
    // TSDV-20150811-SonPT-Revert to old version to read ini file by click on 環境設定 button
    ON_BN_CLICKED(IDC_BTN_DEFAULT, &CGuiGeneratorDlg::OnBnClickedDefault)
    // TSDV-20150811-SonPT-End
END_MESSAGE_MAP()


// CGuiGeneratorDlg message handlers

BOOL CGuiGeneratorDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // Initialize

    // Create status dialog
    m_cStatusDlg.Create( IDD_STATUSDLG, this );

    // Get application folder path
    GetCurrentDirectoryA( MAX_PATH, gsAppPath );

// Start TrunglV 2015-08-07 : Load default setting from init file
    LoadDefault();
// End TrunglV 2015-08-07 : 

    // Set attributes
    ghMainDlg    = m_hWnd;
    gbCancel     = FALSE;
// Start TrunglV 2015-08-07 : Set genall and remove maru
    gbGenAll     = FALSE;
    gbRemoveMaru = FALSE;
    ((CButton * )GetDlgItem( IDC_REMOVE_MARU ))->SetCheck( TRUE );
// End TrunglV 2015-08-07 : 
    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGuiGeneratorDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGuiGeneratorDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

// Static function support to function SelectFolder
static int CALLBACK SetSelProc ( HWND hWnd,
                                 UINT uMsg,
                                 LPARAM /*lParam*/,
                                 LPARAM lpData)
{

    // When folder browser is initialized, it default select a item that specify by lpData
    if ( uMsg==BFFM_INITIALIZED )
    {
        ::SendMessage( hWnd, BFFM_SETSELECTION, TRUE, lpData );
    }
    else
    {
        // Do nothing
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関  数  名：  SelectFolder
//
//　表    題  ：  Select folder by dialog
//
//　概    要  ：  Select folder by dialog
//
//　戻  り  値：  DGT_RET_OK    正常終了
//　          ：  DGT_RET_ERR   異常終了
//
//　引　　数　：  CString*               lpcOutFolderPath         (I/O)     Selected folder path
//
//  バージョン　     日付                氏名                     備考
//  DGT-01.00.00    2015/02/27          (TSDV) ThietNP          Creat New
//
//　(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CGuiGeneratorDlg::SelectFolder( CString* lpcOutFolderPath )
{
    TCHAR szwNewPath[MAX_PATH];
    BROWSEINFO bInfo;

    bInfo.hwndOwner = this->m_hWnd;
    bInfo.pidlRoot = NULL; 
    bInfo.pszDisplayName = szwNewPath;
    bInfo.lpszTitle = _T("Select folder");

    if ( lpcOutFolderPath == NULL )
    {
        return FALSE;
    }
    else
    {
        // Do nothing
    }
    TCHAR *wszStartPath = lpcOutFolderPath->GetBuffer();

    bInfo.ulFlags = BIF_NONEWFOLDERBUTTON
        | BIF_NEWDIALOGSTYLE
        | BIF_EDITBOX
        | BIF_RETURNONLYFSDIRS;
 
    bInfo.lpfn = SetSelProc;
    bInfo.lParam = (LPARAM)wszStartPath;

    // Show folder dialog
    LPITEMIDLIST lpItem = SHBrowseForFolder( &bInfo);

    if( lpItem != NULL )
    {
        SHGetPathFromIDList( lpItem, szwNewPath );
        *lpcOutFolderPath = szwNewPath;
        CoTaskMemFree( lpItem );
    }
    else
    {
        return DGT_RET_ERR;
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関  数  名：  OnBnClickGenerateCode
//
//　表    題  ：  Handle event click button [Generate] to start generation process
//
//　概    要  ：  Handle event click button [Generate] to start generation process
//
//　戻  り  値：  VOID
//
//　引　　数　：  N/A
//
//  バージョン　     日付                氏名                     備考
//  DGT-01.00.00    2015/02/27          (TSDV) ThietNP          Creat New
//
//　(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
void CGuiGeneratorDlg::OnBnClickGenerateCode()
{
    // Initialize
    GetDlgItem( IDC_BTN_GENERATE_CODE )->EnableWindow( FALSE );
    GetDlgItem( IDCANCEL )->EnableWindow( FALSE );
    gbCancel = FALSE; 
// Start TrunglV 2015-08-07 : Disable generate all
    GetDlgItem( IDC_GEN_ALL_BTN )->EnableWindow( FALSE );
    gbRemoveMaru = ((CButton * )GetDlgItem( IDC_REMOVE_MARU ))->GetCheck();
// End TrunglV 2015-08-07 :
    m_cPJGenerator.SetOutFolder( m_sOutputFolder.GetBuffer());
    // Create thread of project generation
    AfxBeginThread( ExeWorkerFunc, this );
    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関  数  名：  OnBnClickSelectManualCatalog
//
//　表    題  ：  Handle event click button to select manual catalog folder
//
//　概    要  ：  Handle event click button to select manual catalog folder
//
//　戻  り  値：  VOID
//
//　引　　数　：  N/A
//
//  バージョン　     日付                氏名                     備考
//  DGT-01.00.00    2015/02/27          (TSDV) ThietNP          Creat New
//
//　(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
void CGuiGeneratorDlg::OnBnClickSelectManualCatalog()
{
    // Get CSV folder
    BOOL bRet = SelectFolder( &m_sManualCSVFolder );
    if ( bRet == TRUE )
    {
        GetDlgItem( IDC_MANUAL_CATALOG_PATH )->SetWindowTextA( m_sManualCSVFolder );
    }
    else
    {
        // Do nothing
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関  数  名：  OnBnClickSelectAutoCatalog
//
//　表    題  ：  Handle event click button to select auto catalog folder
//
//　概    要  ：  Handle event click button to select auto catalog folder
//
//　戻  り  値：  VOID
//
//　引　　数　：  N/A
//
//  バージョン　     日付                氏名                     備考
//  DGT-01.00.00    2015/02/27          (TSDV) ThietNP          Creat New
//
//　(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
void CGuiGeneratorDlg::OnBnClickSelectAutoCatalog()
{
    // Get Catalog folder
    BOOL bRet = SelectFolder( &m_sAutoCSVFolder );
    if ( bRet == TRUE )
    {
        GetDlgItem( IDC_AUTO_CATALOG_PATH )->SetWindowTextA( m_sAutoCSVFolder );
    }
    else
    {
        // Do nothing
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関  数  名：  OnBnClickSelectScrSpecFolder
//
//　表    題  ：  Handle event click button to select screen specification folder
//
//　概    要  ：  Handle event click button to select screen specification folder
//
//　戻  り  値：  VOID
//
//　引　　数　：  N/A
//
//  バージョン　     日付                氏名                     備考
//  DGT-01.00.00    2015/02/27          (TSDV) ThietNP          Creat New
//
//　(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
void CGuiGeneratorDlg::OnBnClickSelectScrSpecFolder()
{
    // Get Screen specification folder
    BOOL bRet = SelectFolder( &m_sScreenSpecFolder );
    if ( bRet == TRUE )
    {
        GetDlgItem( IDC_SCREEN_SPEC_PATH )->SetWindowTextA( m_sScreenSpecFolder );
    }
    else
    {
        // Do nothing
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関  数  名：  OnBnClickSelectOutputFolder
//
//　表    題  ：  Handle event click button to select output folder
//
//　概    要  ：  Handle event click button to select output folder
//
//　戻  り  値：  VOID
//
//　引　　数　：  N/A
//
//  バージョン　     日付                氏名                     備考
//  DGT-01.00.00    2015/02/27          (TSDV) ThietNP          Creat New
//
//　(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
void CGuiGeneratorDlg::OnBnClickSelectOutputFolder()
{
    // Get Output folder
    BOOL bRet = SelectFolder( &m_sOutputFolder );
    if ( bRet == TRUE )
    {
        GetDlgItem( IDC_OUTPUT_PATH )->SetWindowTextA( m_sOutputFolder );
    }
    else
    {
        // Do nothing
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関  数  名：  Exec
//
//　表    題  ：  Execute project generation process
//
//　概    要  ：  Execute project generation process
//
//　戻  り  値：  DGT_RET_OK    正常終了
//　          ：  DGT_RET_ERR   異常終了
//
//　引　　数　：  LPDWORD          lpdwOutErrCode              O           Error code pointer
//
//  バージョン　     日付                氏名                     備考
//  DGT-01.00.00    2015/02/27          (TSDV) ThietNP          Creat New
//
//　(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CGuiGeneratorDlg::Exec( LPDWORD lpdwOutErrCode )
{
    // Initialize
    BOOL                bRet            = FALSE;                    // Return value
    DWORD               dwErrCode       = DGT_VALUE_ZERO_DWORD;     // Error code
    DWORD               dwLogErrCode    = DGT_VALUE_ZERO_DWORD;     // Error code
    SCT_PROG_STATUS     sctProgStt;
    CString             sErrMsg         = "";
    WORD                wCheckResult    = DGT_VALUE_ZERO_WORD;
    CLogger*            lpLog           = NULL ;                                          // For write log

    CLogger::GetInstance( lpLog );

    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Show progress dialog
    m_cStatusDlg.GetDlgItem( IDCANCEL )->SetWindowTextA(_T("中断"));
    m_cStatusDlg.ShowWindow( SW_SHOW );
    m_cStatusDlg.ClearLog();

    // Reset progress dialog
    sctProgStt.nMask        = ( MASK_UPDATE_TEXT | MASK_UPDATE_PERCENT );
    sctProgStt.sStatus      = "";
    sctProgStt.dwPercent    = 0;
    sctProgStt.sLog         = "";
    ::SendMessageA( ghMainDlg, DGT_MSG, DGT_NOTIFY_UPDATE_STATUS, (LPARAM)&sctProgStt );

    // Disable main dialog
    this->EnableWindow( FALSE );
    m_cStatusDlg.SetForegroundWindow();

    // Set paths
    m_cScriptReader.m_sAutoCSVFolder = m_sAutoCSVFolder;
    m_cScriptReader.m_sManualCSVFolder = m_sManualCSVFolder;
    m_cScriptReader.m_sSceenFolderPath = m_sScreenSpecFolder;

    // Check input validation
    bRet = m_cScriptReader.CheckInputValidation( &dwErrCode );

    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        ::SendMessageA( ghMainDlg, DGT_MSG, DGT_NOTIFY_ERROR, dwErrCode );
        return bRet;
    }

    // Check output folder
    bRet = CheckFolderPath( m_sOutputFolder.GetBuffer(), &wCheckResult, &dwErrCode );

    if ( bRet == DGT_RET_OK )
    {
        if ( wCheckResult != DGT_U_CFIP_PATH_OK )
        {
            //delete lpcLogger;
            // Get logger
            ::SendMessageA( this->m_hWnd, DGT_MSG, DGT_NOTIFY_ERROR, DGT_ERR_GGD_EXE_OUTPATH_INVALID );
            // Write log
            bRet = lpLog->Log( "【エラー】：出力フォルダが無効である。" , &dwErrCode);
            if ( bRet == DGT_RET_OK )
            {
                // Do nothing
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
                return DGT_RET_ERR;
            }

            *lpdwOutErrCode = DGT_ERR_GGD_EXE_OUTPATH_INVALID;
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }

    // Read scripts
    bRet = m_cScriptReader.ReadScript( &dwErrCode );
    // Check reading is successful
    if ( bRet == DGT_RET_OK )
    {
        if ( gbCancel == TRUE )
        {
            DeleteAllFiles(m_sOutputFolder.GetBuffer());
            return true;
        }

        // Set area list
        m_cPJGenerator.SetAreaList( m_cScriptReader.m_vAreaList );
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
    }

    if ( bRet == DGT_RET_OK )
    {
        bRet = m_cPJGenerator.GenerateAll( &dwErrCode );
        if ( bRet == DGT_RET_OK )
        {
            // Working process completed. Close progress dialog
            ::SendMessageA( ghMainDlg, DGT_MSG, DGT_NOTIFY_COMPLETE, NULL );
        }
        else
        {
            *lpdwOutErrCode = dwErrCode;
        }
    }
    //// Write to log
    //if ( lpcLogger != NULL )
    //{
    //    lpcLogger->WriteLogToFile( &dwLogErrCode, m_sOutputFolder );
    //}
    //else
    //{
    //    // Do nothing
    //}
    //delete lpcLogger;
    if ( bRet == DGT_RET_OK )
    {
        if ( gbCancel == TRUE )
        {
            DeleteAllFiles(m_sOutputFolder.GetBuffer());
            MessageBoxA( "ダイアログプロジェクト生成プロセスがキャンセルされました!", "メッセージ", MB_OK | MB_ICONINFORMATION );
        }
        else
        {
            MessageBoxA( "ダイアログプロジェクト生成プロセスが完了されました!", "メッセージ", MB_OK | MB_ICONINFORMATION );
        }
    }
    else
    {
        // Error happen. Notify error to main dialog
        ::SendMessageA( this->m_hWnd, DGT_MSG, DGT_NOTIFY_ERROR, dwErrCode );
    }

    return bRet;
}


UINT CGuiGeneratorDlg::ExeWorkerFunc( LPVOID lpInParaThread)
{
    // Initialize
    DWORD               dwErrCode   = DGT_VALUE_ZERO_DWORD;
    CGuiGeneratorDlg*   lpMainDlg   = NULL;
    CString             sErrMsg     = "";
    CLogger*  lpLog = NULL; 
    string    sLogContent = "DIALOG BASE 自動生成ツール 作成開始";
    CHAR      cTimeBuff[1024];
    // Write log
    CLogger::GetInstance( lpLog );
    // Get current time
    CTime currentTime;
    currentTime = CTime::GetCurrentTime();
    sprintf( cTimeBuff, "%d/%d/%d %d:%d:%d: ", currentTime.GetYear(), currentTime.GetMonth(), currentTime.GetDay(), currentTime.GetHour(), currentTime.GetMinute(), currentTime.GetSecond() ); 
    sLogContent = cTimeBuff + sLogContent;
    if ( lpLog != NULL )
    {
        lpLog->Log(sLogContent, &dwErrCode );
    }

    lpMainDlg = (CGuiGeneratorDlg*)lpInParaThread;
    // Check lpInParaThread
    if ( lpInParaThread == NULL )
    {
        return 0;
    }
    else
    {
        // Execute project generation process
        lpMainDlg->Exec( &dwErrCode );
    }
    if ( dwErrCode != DGT_ERR_GGD_EXE_OUTPATH_INVALID )
    {
        sLogContent = "DIALOG BASE 自動生成ツール 作成終了";
        sprintf( cTimeBuff, "%d/%d/%d %d:%d:%d: ", currentTime.GetYear(), currentTime.GetMonth(), currentTime.GetDay(), currentTime.GetHour(), currentTime.GetMinute(), currentTime.GetSecond() ); 
        sLogContent = cTimeBuff + sLogContent;
        if ( lpLog != NULL )
        {
            lpLog->Log(sLogContent, &dwErrCode);
            lpLog->WriteLogToFile( &dwErrCode, lpMainDlg->m_sOutputFolder );
        }
        else
        {
            // Do nothing
        }
    }
    lpMainDlg->m_cScriptReader.CleanUp();
    lpMainDlg->m_cPJGenerator.CleanUp();
    lpMainDlg->GetDlgItem( IDC_BTN_GENERATE_CODE )->EnableWindow( TRUE );
// Start TrungLV 20160807: enable generate all button
    lpMainDlg->GetDlgItem( IDC_GEN_ALL_BTN )->EnableWindow( TRUE );
// End TrungLV 20160807: enable generate all button
    lpMainDlg->GetDlgItem( IDCANCEL )->EnableWindow( TRUE );
    gbGenAll = FALSE;
    return 1;
}

LRESULT CGuiGeneratorDlg::OnReceiveUserMsg( WPARAM wPara, LPARAM lpPara )
{
    // Initialize
    DWORD               dwNotify        = (DWORD)wPara;         // Notify type
    LPSCT_PROG_STATUS   lpSct_Status    = NULL;                 // Status info
    DWORD               dwInternalErr   = 0;
    CString             sErrMsg         = "";
    CString             sDispErr        = "";
    // Check notify type
    switch( dwNotify )
    {
        // Error happen
    case DGT_NOTIFY_ERROR:
        // Hide progress dialog and show main dialog
        m_cStatusDlg.ShowWindow( SW_HIDE );
        this->EnableWindow( TRUE );
        this->SetForegroundWindow();
    //    GetDlgItem( IDC_BTN_GENERATE_CODE )->EnableWindow( TRUE );
    //    GetDlgItem( IDCANCEL )->EnableWindow( TRUE );
        // Get error
        dwInternalErr = lpPara;
        sErrMsg = GetErrMsg( dwInternalErr );

        sDispErr.Format( _T("Error: %s\nError code: 0x%x"), sErrMsg.GetBuffer(), dwInternalErr );
        MessageBoxA( sDispErr, "Error", MB_ICONERROR | MB_OK );

        break;

        // Update status
    case DGT_NOTIFY_UPDATE_STATUS:
        lpSct_Status = (LPSCT_PROG_STATUS)lpPara;
        m_cStatusDlg.UpdateStatus( lpSct_Status );
        break;

        // User click button [Exit]
    case DGT_NOTIFY_EXIT:
        gbCancel  = TRUE;
        if ( m_cStatusDlg.IsWindowVisible())
        {
            m_cStatusDlg.ShowWindow( SW_HIDE );
            this->EnableWindow( TRUE );
            this->SetActiveWindow();
         //   GetDlgItem( IDC_BTN_GENERATE_CODE )->EnableWindow( TRUE );
        //    GetDlgItem( IDCANCEL )->EnableWindow( TRUE );
        }
        else
        {
            // Do nothing
        }
        break;

    case DGT_NOTIFY_COMPLETE:
        if ( m_cStatusDlg.IsWindowVisible())
        {
            m_cStatusDlg.ShowWindow( SW_HIDE );
            this->EnableWindow( TRUE );
            this->SetActiveWindow();
//            GetDlgItem( IDC_BTN_GENERATE_CODE )->EnableWindow( TRUE );
 //           GetDlgItem( IDCANCEL )->EnableWindow( TRUE );
        }
        else
        {
            // Do nothing
        }

    default:
        break;
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関  数  名：  LoadDefault
//
//　表    題  ：  Load information from setting file(.ini)
//
//　概    要  ：  Load information from setting file(.ini)
//
//　戻  り  値：  VOID
//
//　引　　数　：  N/A
//
//  バージョン　     日付                氏名                     備考
//  DGT-01.00.00    2015/08/07          (TSDV) TrunLV          Creat New
//
//　(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
void CGuiGeneratorDlg::LoadDefault()
{
    // Initialize
    CString             sSettingFile    = "";           // INI file path
    sSettingFile = CString( gsAppPath ) + "\\" + DATA_AUTOMK_INI_FNME;
    LPSTR               result          = "";
    CString             csTemp           = _T("");
    string              sPath            = "";
    CString             csData           = _T("");
    CHAR                cBuffer[261];
    // Get setting from ini file
    GetPrivateProfileString( DATA_INI_DLGBASE_SECTION, "HandMkCatarog_Dir", "", cBuffer, MAX_PATH, sSettingFile );
    sPath = Utf8toAnsi( cBuffer, strlen( cBuffer ));
    m_sManualCSVFolder = CString( sPath.c_str());
    memset( cBuffer, 0x00, sizeof( cBuffer ));
    sPath              = "";
    GetPrivateProfileString( DATA_INI_DLGBASE_SECTION, "AutoMkCatarog_Dir", "", cBuffer, MAX_PATH, sSettingFile );
    sPath = Utf8toAnsi( cBuffer, strlen( cBuffer ));
    m_sAutoCSVFolder   = CString( sPath.c_str());
    memset( cBuffer, 0x00, sizeof( cBuffer ));
    sPath              = "";
    GetPrivateProfileString( DATA_INI_DLGBASE_SECTION, "ScreenDoc_Dir", "", cBuffer, MAX_PATH, sSettingFile );
    sPath = Utf8toAnsi( cBuffer, strlen( cBuffer ));
    m_sScreenSpecFolder   = CString( sPath.c_str());
    memset( cBuffer, 0x00, sizeof( cBuffer ));
    sPath              = "";
    GetPrivateProfileString( DATA_INI_DLGBASE_SECTION, "Out_Dir", "", cBuffer, MAX_PATH, sSettingFile );
    sPath = Utf8toAnsi( cBuffer, strlen( cBuffer ));
    m_sOutputFolder   = CString( sPath.c_str());
    memset( cBuffer, 0x00, sizeof( cBuffer ));
    sPath              = "";

    // Update on main dialog
    GetDlgItem( IDC_MANUAL_CATALOG_PATH )->SetWindowTextA( m_sManualCSVFolder );
    GetDlgItem( IDC_AUTO_CATALOG_PATH )->SetWindowTextA( m_sAutoCSVFolder );
    GetDlgItem( IDC_SCREEN_SPEC_PATH )->SetWindowTextA( m_sScreenSpecFolder );
    GetDlgItem( IDC_OUTPUT_PATH )->SetWindowTextA( m_sOutputFolder );

    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関  数  名：  OnBnClickedDefault
//
//　表    題  ：  Load information from setting file(.ini)
//
//　概    要  ：  Load information from setting file(.ini)
//
//　戻  り  値：  VOID
//
//　引　　数　：  N/A
//
//  バージョン　     日付                氏名                     備考
//  DGT-01.00.00    2015/08/07          (TSDV) TrunLV          Creat New
//
//　(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
void CGuiGeneratorDlg::OnBnClickedDefault()
{
    // Load default setting from .ini file
    LoadDefault();
    
    return;
}

// Get error message from error code number
CString CGuiGeneratorDlg::GetErrMsg( DWORD dwInErrCode )
{
    // Local variables
    CString     sErrMsg = "";           // Output

    // Searching error code
    switch( dwInErrCode )
    {
        case DGT_PJG_GTF_COPY_ERROR:
            sErrMsg = "【エラー】：出力フォルダにコピーすることが誤ります。（出力フォルダは書き込み権がないかもしれません）";
            break;

        case DGT_ERR_CSR_CIV_AU_FOLDER_INVALID:
            sErrMsg = "【エラー】：手作成カタログファイル格納先フォルダがみつかりません。";
            break;

        case DGT_ERR_CSR_CIV_MA_FOLDER_INVALID:
            sErrMsg = "【エラー】：自動生成カタログファイル格納先フォルダがみつかりません。" ;
            break;

        case DGT_ERR_CSR_CIV_SC_FOLDER_INVALID:
            sErrMsg = "【エラー】：画面仕様書ファイル格納先フォルダがみつかりません。" ;
            break;

        case DGT_ERR_CSR_CIV_FMT_FILE_INVALID:
            sErrMsg = "【エラー】：『fmt_list.csv』ファイルがみつかりません。" ;
            break;
        case DGT_ERR_CSR_RFL_INVALID_FORMAT:
            sErrMsg = "【エラー】：『fmt_list.csv』ファイル形式が無効です。";
            break;
        case DGT_ERR_CSR_CIV_AREA_FILE_INVALID:
            sErrMsg = "【エラー】：『area_list.csv』ファイルがみつかりません。";
            break;
        case DGT_ERR_CSR_RAL_INVALID_FORMAT:
            sErrMsg = "【エラー】：『area_list.csv』ファイル形式が無効です。";
            break;
        case DGT_ERR_CSR_CIV_LIMIT_FILE_INVALID:
            sErrMsg = "【エラー】：『limit_list.csv』ファイルがみつかりません。";
            break;
        case DGT_ERR_CSR_RLL_INVALID_FORMAT:
            sErrMsg = "【エラー】：『limit_list.csv』ファイル形式が無効です。";
            break;
        case DGT_ERR_CSR_CIV_TAG_FILE_INVALID:
            sErrMsg = "【エラー】：『tag_list.csv』ファイルがみつかりません。";
            break;
        case DGT_ERR_CSR_RTL_INVALID_FORMAT:
            sErrMsg = "【エラー】：『tag_list.csv』ファイル形式が無効です。";
            break;
        case DGT_ERR_CSR_CIV_INIT_FILE_INVALID:
            sErrMsg = "【エラー】：『initdesign_catarog.csv』ファイルがみつかりません。";
            break;
        case DGT_ERR_CSR_RIL_INVALID_FORMAT:
            sErrMsg = "【エラー】：『initdesign_catarog.csv』ファイル形式が無効です。";
            break;
        case DGT_ERR_CSR_RCTL_INVALID_FORMAT:
            sErrMsg = "【エラー】：カタログファイル形式が無効です。";
            break;
        case DGT_ERR_CSR_RCTL_OPEN_FILE:
            sErrMsg = "【エラー】：カタログ ファイルがみつかりません。";
            break;
        case DGT_ERR_GGD_EXE_OUTPATH_INVALID:
            sErrMsg = "【エラー】：出力フォルダが無効である。";
            break;

        case DGT_ER_CSR_GCSI_SHEET_NOT_FOUND:
            sErrMsg = "【エラー】：『◆作成一覧』シートがみつかりません。";
            break;

        case DGT_ER_CSR_GMSI_SHEET_NOT_FOUND:
            sErrMsg = "【エラー】：『◆マスタ』シートがみつかりません。";
            break;
        case DGT_ERR_CFW_WA_WRITE_FAIL:
        case DGT_ERR_APPEND_ERR:
            sErrMsg = "【エラー】：ファイルが開けません。";
            break;
        default:
            sErrMsg = "【エラー】：不明なエラーコードです。";
            break;
    }

    return sErrMsg; 
}


// Start TrunglV 2015-08-07 : Process generate all
void CGuiGeneratorDlg::OnBnClickedGenAllBtn()
{
    BOOL bCheck = FALSE;
    // Mark generate all flag
    gbGenAll = TRUE;
    // Initialize

    GetDlgItem( IDC_BTN_GENERATE_CODE )->EnableWindow( FALSE );
    GetDlgItem( IDC_GEN_ALL_BTN )->EnableWindow( FALSE );
    GetDlgItem( IDCANCEL )->EnableWindow( FALSE );
    gbCancel = FALSE; 
    gbRemoveMaru = ((CButton * )GetDlgItem( IDC_REMOVE_MARU ))->GetCheck();
    m_cPJGenerator.SetOutFolder( m_sOutputFolder.GetBuffer());
    // Create thread of project generation
    AfxBeginThread( ExeWorkerFunc, this );

    return;
}
// End TrunglV 2015-08-07 : 