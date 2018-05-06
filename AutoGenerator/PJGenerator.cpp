////////////////////////////////////////////////////////////////////////////////
//
//  ファイル名：PJGenerator.cpp
//
//  概要　　　：This class aim to generate dialog base source code. Include header file, cpp file, and resource file.
//
//  作成者　　：(TSDV) TrungLV
//
//  所属      ：
//
//  IDE       ：Microsoft VisualC++ 2010
//
// 
//  変更履歴
//  バージョン　     日付　　　　  氏名　　　　       備考
//  DGT-00.00.00    2015/02/25   (TSDV) TrungLV     Create New
//
//
////////////////////////////////////////////////////////////////////////////////
// $Header: $
#include "PJGenerator.h"
#include "Area.h"
#include "Logger.h"
#include "Shlwapi.h"
extern BOOL gbCancel;
extern HWND ghMainDlg;
extern char gsAppPath[MAX_PATH];


CPJGenerator::CPJGenerator(void)
{
}


CPJGenerator::~CPJGenerator(void)
{
    try
    {
        for ( DWORD dwCnt = 0; dwCnt < m_vAreaGenList.size(); dwCnt++ )
        {
            if ( m_vAreaGenList[dwCnt] != NULL )
            {
                delete m_vAreaGenList[dwCnt];
                m_vAreaGenList[dwCnt] = NULL;
            }
        }
    }
    catch( const exception& e )
    {
    }
}

void CPJGenerator::CleanUp()
{
    for ( DWORD dwCnt = 0; dwCnt < m_vAreaGenList.size(); dwCnt++ )
    {
        if ( m_vAreaGenList[dwCnt] != NULL )
        {
            delete m_vAreaGenList[dwCnt];
            m_vAreaGenList[dwCnt] = NULL;
        }
    }
    m_vAreaGenList.clear();
}

VOID CPJGenerator::SetAreaList( vector<CArea*> vInAreaList )
{
    // Initialize
    CAreaGenerator*     lpcTmp = NULL;

    // Construct CAreaGenerator
    for ( DWORD dwCnt = 0; dwCnt < vInAreaList.size(); dwCnt++ )
    {
        lpcTmp = new CAreaGenerator( vInAreaList[dwCnt] );
        m_vAreaGenList.push_back( lpcTmp );
    }
}

BOOL CPJGenerator::GenerateAll( LPDWORD lpdwOutErrCode )
{
    // Initialzie
    BOOL            bRet        = FALSE;                    // Return value
    DWORD           dwErrCode   = DGT_VALUE_ZERO_DWORD;     // Error code
    SCT_PROG_STATUS sctProgStt;                             // Status info
    CLogger*        lpLog = NULL;
    CLogger::GetInstance( lpLog );
    sctProgStt.Memset();
    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Generate template project
    bRet = GenerateTemplateProject( &dwErrCode );
    if ( bRet == DGT_RET_ERR )
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    sctProgStt.Memset();
    sctProgStt.nMask       = ( MASK_UPDATE_TEXT );
    sctProgStt.sStatus      = "テンプレートプロジェクトをコピーしている";
    ::SendMessageA( ghMainDlg, DGT_MSG, DGT_NOTIFY_UPDATE_STATUS, (LPARAM)&sctProgStt );

    dwErrCode = DGT_VALUE_ZERO_DWORD;
    // Generate areas
    bRet = GenerateAreas( &dwErrCode );
    if ( bRet == DGT_RET_ERR )
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }
    if ( gbCancel == TRUE )
    {
        bRet = lpLog->Log("『中断』釦が押下された為、中断します。", &dwErrCode );
        if ( bRet == DGT_RET_OK ) 
        {
            // Do nothing
        }
        else
        {
            *lpdwOutErrCode = dwErrCode;
            return DGT_RET_ERR;
        }
    }
    return DGT_RET_OK;
}
BOOL CPJGenerator::IsProjectExist( string sProjectFolder )
{
    // Initialzie
    BOOL            bRet        = FALSE;                    // Return value
    DWORD           dwErrCode   = DGT_VALUE_ZERO_DWORD;     // Error code
    string          sFilePath   = "";

    //if ( PathIsDirectoryEmpty( sProjectFolder.c_str()) )
    //{
    //    return FALSE;
    //}

    // Check FunctionMap.cpp
    sFilePath = sProjectFolder + FUNCTION_MAP_FILE;
    if ( PathFileExists( sFilePath.c_str()) == FALSE )
    {
        return FALSE;
    }

    // Check GUIDAreaStore.h
    sFilePath = sProjectFolder + "\\Include\\GUIDAreaStore.h";
    if ( PathFileExists( sFilePath.c_str()) == FALSE )
    {
        return FALSE;
    }

    // Check AreaStoreLib.vcxproj
    sFilePath = sProjectFolder + "\\GUIDAreaStoreLib\\AreaStoreLib.vcxproj";
    if ( PathFileExists( sFilePath.c_str()) == FALSE )
    {
        return FALSE;
    }

    // Check AreaStoreLib.vcxproj.filters
    sFilePath = sProjectFolder + "\\GUIDAreaStoreLib\\AreaStoreLib.vcxproj.filters";
    if ( PathFileExists( sFilePath.c_str()) == FALSE )
    {
        return FALSE;
    }

    return TRUE;
}

BOOL CPJGenerator::UpdateProjectFile( const string& TemplateFolder, const string& ProjectFolder , LPDWORD lpdwOutErrCode )
{
    // Initialize
    string            sFolderPath   = "";
    string            sSrcFolder    = "";
    string            sTargetFodler = "";
    BOOL              bRet          = FALSE;
    DWORD             dwErrCode     = 0;
    vector<string>    vExtension;
    vector<string>    vListFilePath;
    vector<string>    vIgnoreItem;
    string            sIgnoreItem = "";
    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    sSrcFolder     = TemplateFolder + "\\GUIDCssStoreLib";
    sTargetFodler  = ProjectFolder   + "\\GUIDCssStoreLib";
    // Copy GUIDCssStoreLib
    bRet = CopyDirTo( sSrcFolder, sTargetFodler );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = DGT_PJG_GTF_COPY_ERROR;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    sSrcFolder     = TemplateFolder + "\\GUIDGuiView";
    sTargetFodler  = ProjectFolder   + "\\GUIDGuiView";
    // Copy GUIDCssStoreLib
    bRet = CopyDirTo( sSrcFolder, sTargetFodler );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = DGT_PJG_GTF_COPY_ERROR;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    sSrcFolder     = TemplateFolder + "\\GUIDItemsLib";
    sTargetFodler  = ProjectFolder   + "\\GUIDItemsLib";
    // Copy GUIDItemsLib
    bRet = CopyDirTo( sSrcFolder, sTargetFodler );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = DGT_PJG_GTF_COPY_ERROR;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    sSrcFolder     = TemplateFolder + "\\GUIDUtilityLib";
    sTargetFodler  = ProjectFolder   + "\\GUIDUtilityLib";
    // Copy GUIDUtilityLib
    bRet = CopyDirTo( sSrcFolder, sTargetFodler );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = DGT_PJG_GTF_COPY_ERROR;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    sSrcFolder     = TemplateFolder + "\\Library";
    sTargetFodler  = ProjectFolder   + "\\Library";
    // Copy Library
    bRet = CopyDirTo( sSrcFolder, sTargetFodler );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = DGT_PJG_GTF_COPY_ERROR;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    sSrcFolder     = TemplateFolder + "\\Release";
    sTargetFodler  = ProjectFolder   + "\\Release";
    // Copy Release
    bRet = CopyDirTo( sSrcFolder, sTargetFodler );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = DGT_PJG_GTF_COPY_ERROR;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    sSrcFolder     = TemplateFolder + "\\Debug";
    sTargetFodler  = ProjectFolder   + "\\Debug";
    // Copy Debug
    bRet = CopyDirTo( sSrcFolder, sTargetFodler );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = DGT_PJG_GTF_COPY_ERROR;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    vListFilePath.clear();
    vExtension.push_back(".cpp");
    vExtension.push_back(".h");
    vExtension.push_back(".rc");
    vExtension.push_back(".user");
    sSrcFolder = TemplateFolder + "\\GUIDAreaStoreLib";
    // Get all file in folder
    GetAllFileInFolder( sSrcFolder, vExtension, vListFilePath , TRUE );
    vIgnoreItem.push_back("FunctionMap.cpp" );
    vIgnoreItem.push_back("AreaStoreLib.vcxproj");
    for ( DWORD dwCnt = 0; dwCnt < vIgnoreItem.size(); dwCnt ++ )
    {
        auto it = find( vListFilePath.begin(), vListFilePath.end(), vIgnoreItem[dwCnt] );
        if ( it != vListFilePath.end())
        {
            vListFilePath.erase( it );
        }
        else
        {
            // Do nothing
        }
    }
    // Copy all file to folder but ignore FunctionMap.cpp and vcxproj file

    for ( DWORD dwCnt = 0; dwCnt < vListFilePath.size(); dwCnt++ )
    {
        sSrcFolder      = TemplateFolder + "\\GUIDAreaStoreLib\\"+ vListFilePath[dwCnt];
        sTargetFodler   = ProjectFolder + "\\GUIDAreaStoreLib\\" + vListFilePath[dwCnt];
        CopyFile( sSrcFolder.c_str(), sTargetFodler.c_str(), FALSE );
    }

    vListFilePath.clear();
    vExtension.clear();
    vExtension.push_back(".cpp");
    vExtension.push_back(".h");
    sSrcFolder = TemplateFolder + "\\Include";
    // Get all file in folder
    GetAllFileInFolder( sSrcFolder, vExtension, vListFilePath , TRUE );
    sIgnoreItem = "GUIDAreaStore.h";
    auto it2 = find( vListFilePath.begin(), vListFilePath.end(), sIgnoreItem );
    if ( it2 != vListFilePath.end())
    {
        vListFilePath.erase( it2 );
    }
    else
    {
        // Do nothing
    }

    for ( DWORD dwCnt = 0; dwCnt < vListFilePath.size(); dwCnt++ )
    {
        sSrcFolder      = TemplateFolder + "\\Include\\"+ vListFilePath[dwCnt];
        sTargetFodler   = ProjectFolder + "\\Include\\" + vListFilePath[dwCnt];
        CopyFile( sSrcFolder.c_str(), sTargetFodler.c_str(), FALSE );
    }

    return DGT_RET_OK;
}
BOOL CPJGenerator::GenerateTemplateProject( LPDWORD lpdwOutErrCode )
{
    // Initialzie
    BOOL            bRet        = FALSE;                    // Return value
    DWORD           dwErrCode   = DGT_VALUE_ZERO_DWORD;     // Error code
    string          sSrcFolder  = string( gsAppPath ) + "\\" + TEMPLATE_FOLDER;

    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Check if project file is exist or not
    if ( IsProjectExist( m_sOutFolderPath ) == FALSE )
    {
        // Copy template project to output folder
        bRet = CopyDirTo( sSrcFolder, m_sOutFolderPath );
        if ( bRet == FALSE )
        {
            *lpdwOutErrCode = DGT_PJG_GTF_COPY_ERROR;
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        bRet = UpdateProjectFile( sSrcFolder, m_sOutFolderPath ,&dwErrCode );
        if ( bRet == FALSE )
        {
            *lpdwOutErrCode = DGT_PJG_GTF_COPY_ERROR;
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }

    return DGT_RET_OK;
}

BOOL CPJGenerator::GenerateAreas( LPDWORD lpdwOutErrCode )
{
    // Initialzie
    BOOL            bRet        = FALSE;                    // Return value
    DWORD           dwErrCode   = DGT_VALUE_ZERO_DWORD;     // Error code
    DWORD           dwErrCode2  = DGT_VALUE_ZERO_DWORD;     // Error code
    DWORD           dwCnt       = 0;                        // Counter in loop
    CLogger*        lpcLogger   = NULL;
    SCT_PROG_STATUS sctProgStt;                             // Status info
    string          sStatus     = "";
    sctProgStt.Memset();
    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Generate all areas
    for ( dwCnt = 0; dwCnt < m_vAreaGenList.size(); dwCnt++ )
    {
        // Check flag cancel
        if ( gbCancel == TRUE )
        {
            break;
        }
        else
        {
            // Do nothing
        }

        m_vAreaGenList[dwCnt]->SetOutPath( m_sOutFolderPath );

        // Write an area
        bRet = m_vAreaGenList[dwCnt]->WriteAll( &dwErrCode );
        // Check result
        if ( bRet == DGT_RET_OK )
        {
            sStatus = string("エリア作成: ") + m_vAreaGenList[dwCnt]->m_lpcArea->m_sctAreaInfo.sAreaFuncName;
            // Write log
            CLogger::GetInstance( lpcLogger );
            lpcLogger->Log( sStatus, &dwErrCode2 );

            // Update status
            sctProgStt.nMask = ( MASK_UPDATE_TEXT | MASK_UPDATE_PERCENT );
            sctProgStt.sStatus = sStatus;
            sctProgStt.dwPercent = 50 + (( dwCnt + 1 ) * 50 ) / m_vAreaGenList.size();
            ::SendMessageA( ghMainDlg, DGT_MSG, DGT_NOTIFY_UPDATE_STATUS, (LPARAM)&sctProgStt );
        }
        else
        {
            *lpdwOutErrCode = dwErrCode;
            return DGT_RET_ERR;
        }
    }

    return DGT_RET_OK;
}