////////////////////////////////////////////////////////////////////////////////
//
//  ファイル名：ScriptReader.cpp
//
//  概要　　　：This class used to read input file ( *.csv file and screen specification excel file) 
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
#include "afx.h"
#include "ScriptReader.h"
#include "DGT_SymbolDef.h"
#include "DGT_PvSymbolDef.h"
#include "DGT_PvErrCode.h"
#include "Utility.h"
#include "Logger.h"
#include <fstream>
#include <algorithm>
//#include "GuiGeneratorDlg.h"
#include <regex>
#include "DataStructure.h"

extern BOOL gbCancel;
extern HWND ghMainDlg;
// Start TrunglV 2015-08-07 : Add remove maru flag
extern BOOL gbRemoveMaru;
extern BOOL gbGenAll;
// Start TrunglV 2015-08-07 : 
CScriptReader::CScriptReader(void)
{
    m_vItemStack.clear();
    m_lpCurrentArea = NULL;
}


CScriptReader::~CScriptReader(void)
{
    DWORD dwCnt = DGT_VALUE_ZERO_DWORD;
    try
    {
        for ( dwCnt = 0; dwCnt < m_vAreaList.size(); dwCnt++ )
        {
            if (m_vAreaList[dwCnt] != NULL )
            {
                delete m_vAreaList[dwCnt];
                m_vAreaList[dwCnt] = NULL;
            }
        }

        for ( dwCnt = 0; dwCnt < m_vItemStack.size(); dwCnt++ )
        {
            delete m_vItemStack[dwCnt];
            m_vItemStack[dwCnt] = NULL;
        }
    }
    catch( const exception& e )
    {
    }
}



/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  ReadFormatList
//
//　表　　題　：  Read fmt_list.csv file
//
//　概　　要　：  Read fmt_list.csv file
//
//　戻　り　値：  
//
//　引　　数　：  string                  sInFielPath              (I)              File path
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/25   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

BOOL CScriptReader::ReadFormatList( string          sInFilePath,
                                 LPDWORD    lpdwOutErrCode )
{
    // Local variabe
    DWORD                dwErrCode           = DGT_VALUE_ZERO_DWORD;        // Error codes
    BOOL                 bRet                    = DGT_RET_ERR;                          // Return value
    WORD                 wCheckResult       = DGT_VALUE_ZERO_WORD;          // check reusult
    fstream              fsCSVFile;                                                                // for read file
    CHAR                 cBuffer[1000];                                                          // Buffer
    vector<string>       vRow;                                                                      // row content
    CLogger*             lpLog                   = NULL;                                         // For write log
    BOOL                 bIsFirstFile        = TRUE;
    string               sRow                = "";
    BOOL                 bIsAnSI             = FALSE;
    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    CLogger::GetInstance( lpLog );

    // Check the validation of sInFilePath
    bRet   = CheckFilePath( sInFilePath, &wCheckResult, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        if (( wCheckResult == DGT_U_CFIP_PATH_INVALID ) ||
            ( wCheckResult == DGT_U_CFIP_PATH_NULL ) ||
            ( wCheckResult == DGT_U_CFIP_PATH_TOO_LONG ))
        {
            *lpdwOutErrCode = DGT_ERR_CSR_RFL_PARA;
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }

    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    m_vFormatListCSV.clear();

    // Open CSV file
    fsCSVFile.open( sInFilePath,std::ios::binary| ios::in );
    if ( fsCSVFile.is_open() == true )
    {
        // Do nothing
    }
    else
    {
            // Write log
            bRet = lpLog->Log( "【エラー】：『fmt_list.csv』ファイルがみつかりません。" , &dwErrCode);
            if ( bRet == DGT_RET_OK )
            {
                // Do nothing
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
                return DGT_RET_ERR;
            }

        *lpdwOutErrCode = DGT_ERR_CSR_RFL_OPEN_FILE;
        return DGT_RET_ERR;
    }

    while(  !fsCSVFile.eof())
    {
        sRow     = "";
        // memset
        memset( cBuffer, 0x00, sizeof( cBuffer ));
        // get strlen
        fsCSVFile.getline( cBuffer, sizeof( cBuffer ));
        // Check EF BB BF ( UTF-8 with BOM
        if ( bIsFirstFile && ( (BYTE) cBuffer[0] == (BYTE)0x0EF ) && ( (BYTE) cBuffer[1] == (BYTE)  0xbb ) && ((BYTE)  cBuffer[2] == (BYTE) 0xbf ))
        {
            memcpy( cBuffer, &cBuffer[3], strlen( cBuffer) - 3 );
            cBuffer[strlen( cBuffer)-3]= '\0';
            bIsFirstFile = FALSE;
        }
        else
        {
            // Do nothong
        }
        sRow = Utf8toAnsi( cBuffer, strlen( cBuffer ));
        if (( sRow      == ""       ) ||
            ( sRow[0]   == '#'      ) ||
            ( sRow[0]   == char(13)))
        {
            continue;
        }

        vRow.clear();
        // split string
        vRow = SplitString( sRow, ",");
        for ( DWORD dwCntSub = 0; dwCntSub < vRow.size(); dwCntSub++ )
        {
            vRow[dwCntSub].erase(std::remove(vRow[dwCntSub].begin(), vRow[dwCntSub].end(), char(13)),  vRow[dwCntSub].end());
            vRow[dwCntSub].erase(std::remove(vRow[dwCntSub].begin(), vRow[dwCntSub].end(), '\n'),  vRow[dwCntSub].end());
        }
        if ( vRow.size() == FORMAT_ITEM_NUM )
        {
            m_vFormatListCSV.push_back( SCT_FORMAT_CSV( vRow[0], vRow[1] ));
        }
        else
        {
            m_vFormatListCSV.clear();
            *lpdwOutErrCode = DGT_ERR_CSR_RFL_INVALID_FORMAT;
            fsCSVFile.close();
            return DGT_RET_ERR;
        }
    }

    fsCSVFile.close();

    return DGT_RET_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  ReadAreaList
//
//　表　　題　：  Read area_list.csv file
//
//　概　　要　：  Read area_list.csv file
//
//　戻　り　値：  
//
//　引　　数　：  string                  sInFielPath              (I)              File path
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/25   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

BOOL CScriptReader::ReadAreaList( string          sInFilePath,
                                 LPDWORD    lpdwOutErrCode )
{
    // Local variabe
    DWORD               dwErrCode          = DGT_VALUE_ZERO_DWORD;        // Error codes
    BOOL                bRet               = DGT_RET_ERR;                 // Return value
    WORD                wCheckResult       = DGT_VALUE_ZERO_WORD;         // check reusult
    fstream             fsCSVFile;                                        // for read file
    CHAR                cBuffer[1000];                                    // Buffer
    vector<string>      vRow;                                             // row content
    CLogger*            lpLog              = NULL;                        // For write log
    string              sRow               = "";
    BOOL                bIsFirstFile       = TRUE;
    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    CLogger::GetInstance( lpLog );
    

    // Check the validation of sInFilePath
    bRet   = CheckFilePath( sInFilePath, &wCheckResult, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        if (( wCheckResult == DGT_U_CFIP_PATH_INVALID ) ||
            ( wCheckResult == DGT_U_CFIP_PATH_NULL ) ||
            ( wCheckResult == DGT_U_CFIP_PATH_TOO_LONG ))
        {
            *lpdwOutErrCode = DGT_ERR_CSR_RAL_PARA;
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    m_vAreaListCSV.clear();

    // Open CSV file
    fsCSVFile.open( sInFilePath,std::ios::binary| ios::in );
    if ( fsCSVFile.is_open() == true )
    {
        // Do nothing
    }
    else
    {
        // Write log
        bRet = lpLog->Log( "【エラー】：『area_list.csv』ファイルがみつかりません。" , &dwErrCode);
        if ( bRet == DGT_RET_OK )
        {
            // Do nothing
        }
        else
        {
            *lpdwOutErrCode = dwErrCode;
            return DGT_RET_ERR;
        }
        *lpdwOutErrCode = DGT_ERR_CSR_RAL_OPEN_FILE;
        return DGT_RET_ERR;
    }

    while(  !fsCSVFile.eof())
    {
        sRow        = "";
        // memset
        memset( cBuffer, 0x00, sizeof( cBuffer ));
        // get line
        fsCSVFile.getline( cBuffer, sizeof( cBuffer ));
        if ( bIsFirstFile && ( (BYTE) cBuffer[0] == (BYTE)0x0EF ) && ( (BYTE) cBuffer[1] == (BYTE)  0xbb ) && ((BYTE)  cBuffer[2] == (BYTE) 0xbf ))
        {
            memcpy( cBuffer, &cBuffer[3], strlen( cBuffer) - 3 );
            cBuffer[strlen( cBuffer)-3]= '\0';
            bIsFirstFile = FALSE;
        }
        else
        {
            // Do nothong
        }
        sRow = Utf8toAnsi( cBuffer, strlen( cBuffer ));
        if (( sRow      == ""       ) ||
            ( sRow[0]   == '#'      ) ||
            ( sRow[0]   == char(13)))
        {
            continue;
        }

        vRow.clear();
        // split string
        vRow = SplitString( sRow, ",");
        for ( DWORD dwCntSub = 0; dwCntSub < vRow.size(); dwCntSub++ )
        {
            vRow[dwCntSub].erase(std::remove(vRow[dwCntSub].begin(), vRow[dwCntSub].end(), char(13)),  vRow[dwCntSub].end());
            vRow[dwCntSub].erase(std::remove(vRow[dwCntSub].begin(), vRow[dwCntSub].end(), '\n'),  vRow[dwCntSub].end());
        }
        
        if ( vRow.size() == AREA_ITEM_NUM )
        {
            m_vAreaListCSV.push_back( SCT_AREA_CSV( vRow[0], vRow[1], vRow[2], vRow[3] ));
        }
        else
        {
            m_vAreaListCSV.clear();
            *lpdwOutErrCode = DGT_ERR_CSR_RAL_INVALID_FORMAT;
            fsCSVFile.close();
            return DGT_RET_ERR;
        }
    }

    fsCSVFile.close();

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  ReadTagList
//
//　表　　題　：  Read tag_list.csv file
//
//　概　　要　：  Read tag_list.csv file
//
//　戻　り　値：  
//
//　引　　数　：  string                  sInFielPath              (I)              File path
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/25   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

BOOL CScriptReader::ReadTagList( string          sInFilePath,
                                 LPDWORD    lpdwOutErrCode )
{
    // Local variabe
    DWORD               dwErrCode          = DGT_VALUE_ZERO_DWORD;         // Error codes
    BOOL                bRet               = DGT_RET_ERR;                  // Return value
    WORD                wCheckResult       = DGT_VALUE_ZERO_WORD;          // check reusult
    fstream             fsCSVFile;                                         // for read file
    CHAR                cBuffer[1000];                                     // Buffer
    vector<string>      vRow;                                              // row content
    string              sRow = "";
    BOOL                bIsFirstFile = TRUE;

    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Check the validation of sInFilePath
    bRet   = CheckFilePath( sInFilePath, &wCheckResult, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        if (( wCheckResult == DGT_U_CFIP_PATH_INVALID ) ||
            ( wCheckResult == DGT_U_CFIP_PATH_NULL ) ||
            ( wCheckResult == DGT_U_CFIP_PATH_TOO_LONG ))
        {
            *lpdwOutErrCode = DGT_ERR_CSR_RTL_PARA;
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    m_vTagListCSV.clear();

    // Open CSV file
    fsCSVFile.open( sInFilePath,std::ios::binary| ios::in );
    if ( fsCSVFile.is_open() == true )
    {
        // Do nothing
    }
    else
    {
        *lpdwOutErrCode = DGT_ERR_CSR_RTL_OPEN_FILE;
        return DGT_RET_ERR;
    }

    while(  !fsCSVFile.eof())
    {
        sRow     = "";
        // memset
        memset( cBuffer, 0x00, sizeof( cBuffer ));
        // get strlen
        fsCSVFile.getline( cBuffer, sizeof( cBuffer ));
        // Check EF BB BF ( UTF-8 with BOM
        if ( bIsFirstFile && ( (BYTE) cBuffer[0] == (BYTE)0x0EF ) && ( (BYTE) cBuffer[1] == (BYTE)  0xbb ) && ((BYTE)  cBuffer[2] == (BYTE) 0xbf ))
        {
            memcpy( cBuffer, &cBuffer[3], strlen( cBuffer) - 3 );
            cBuffer[strlen( cBuffer)-3]= '\0';
            bIsFirstFile = FALSE;
        }
        else
        {
            // Do nothong
        }
        sRow = Utf8toAnsi( cBuffer, strlen( cBuffer ));
        if (( sRow      == ""       ) ||
            ( sRow[0]   == '#'      ) ||
            ( sRow[0]   == char(13)))
        {
            continue;
        }

        vRow.clear();
        // split string
        vRow = SplitString( sRow, ",");
        for ( DWORD dwCntSub = 0; dwCntSub < vRow.size(); dwCntSub++ )
        {
            vRow[dwCntSub].erase(std::remove(vRow[dwCntSub].begin(), vRow[dwCntSub].end(), char(13)),  vRow[dwCntSub].end());
            vRow[dwCntSub].erase(std::remove(vRow[dwCntSub].begin(), vRow[dwCntSub].end(), '\n'),  vRow[dwCntSub].end());
        }
        if ( vRow.size() == TAG_ITEM_NUM )
        {
            m_vTagListCSV.push_back( SCT_TAG_CSV( vRow[0], vRow[1], vRow[2], vRow[3], vRow[4] ));
        }
        else
        {
            m_vTagListCSV.clear();
            *lpdwOutErrCode = DGT_ERR_CSR_RTL_INVALID_FORMAT;
            fsCSVFile.close();
            return DGT_RET_ERR;
        }
    }

    fsCSVFile.close();

    return DGT_RET_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  ReadLimitList
//
//　表　　題　：  Read limit_list.csv file
//
//　概　　要　：  Read limit_list.csv file
//
//　戻　り　値：  
//
//　引　　数　：  string                  sInFielPath              (I)              File path
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/25   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

BOOL CScriptReader::ReadLimitList( string          sInFilePath,
                                 LPDWORD    lpdwOutErrCode )
{
    // Local variabe
    DWORD                dwErrCode          = DGT_VALUE_ZERO_DWORD;        // Error codes
    BOOL                 bRet               = DGT_RET_ERR;                 // Return value
    WORD                 wCheckResult       = DGT_VALUE_ZERO_WORD;          // check reusult
    fstream              fsCSVFile;                                         // for read file
    CHAR                 cBuffer[1000];                                     // Buffer
    vector<string>       vRow;                                              // row content
    CLogger*             lpLog              = NULL;                         //  For write log
    BOOL                 bIsFirstFile        = TRUE;
    string               sRow                = "";
    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    CLogger::GetInstance( lpLog );
    

    // Check the validation of sInFilePath
    bRet   = CheckFilePath( sInFilePath, &wCheckResult, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        if (( wCheckResult == DGT_U_CFIP_PATH_INVALID ) ||
            ( wCheckResult == DGT_U_CFIP_PATH_NULL ) ||
            ( wCheckResult == DGT_U_CFIP_PATH_TOO_LONG ))
        {
            *lpdwOutErrCode = DGT_ERR_CSR_RLL_PARA;
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    m_vLimitCSV.clear();

    // Open CSV file
    fsCSVFile.open( sInFilePath,std::ios::binary| ios::in );
    if ( fsCSVFile.is_open() == true )
    {
        // Do nothing
    }
    else
    {
        // Write log
        bRet = lpLog->Log( "【エラー】：『limit_list.csv』ファイルがみつかりません。" , &dwErrCode);
        if ( bRet == DGT_RET_OK )
        {
            // Do nothing
        }
        else
        {
            *lpdwOutErrCode = dwErrCode;
            return DGT_RET_ERR;
        }
        *lpdwOutErrCode = DGT_ERR_CSR_RLL_OPEN_FILE;
        return DGT_RET_ERR;
    }

    while(  !fsCSVFile.eof())
    {
        sRow     = "";
        // memset
        memset( cBuffer, 0x00, sizeof( cBuffer ));
        // get strlen
        fsCSVFile.getline( cBuffer, sizeof( cBuffer ));
        // Check EF BB BF ( UTF-8 with BOM
        if ( bIsFirstFile && ( (BYTE) cBuffer[0] == (BYTE)0x0EF ) && ( (BYTE) cBuffer[1] == (BYTE)  0xbb ) && ((BYTE)  cBuffer[2] == (BYTE) 0xbf ))
        {
            memcpy( cBuffer, &cBuffer[3], strlen( cBuffer) - 3 );
            cBuffer[strlen( cBuffer)-3]= '\0';
            bIsFirstFile = FALSE;
        }
        else
        {
            // Do nothong
        }
        sRow = Utf8toAnsi( cBuffer, strlen( cBuffer ));
        if (( sRow      == ""       ) ||
            ( sRow[0]   == '#'      ) ||
            ( sRow[0]   == char(13)))
        {
            continue;
        }

        vRow.clear();
        // split string
        vRow = SplitString( sRow, ",");
        for ( DWORD dwCntSub = 0; dwCntSub < vRow.size(); dwCntSub++ )
        {
            vRow[dwCntSub].erase(std::remove(vRow[dwCntSub].begin(), vRow[dwCntSub].end(), char(13)),  vRow[dwCntSub].end());
            vRow[dwCntSub].erase(std::remove(vRow[dwCntSub].begin(), vRow[dwCntSub].end(), '\n'),  vRow[dwCntSub].end());
        }
        if ( vRow.size() == LIMIT_ITEM_NUM )
        {
            m_vLimitCSV.push_back( SCT_LIMIT_CSV( vRow[0], vRow[1] ));
        }
        else
        {
            m_vLimitCSV.clear();
            *lpdwOutErrCode = DGT_ERR_CSR_RLL_INVALID_FORMAT;
            fsCSVFile.close();
            return DGT_RET_ERR;
        }
    }

    fsCSVFile.close();

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  ReadInitList
//
//　表　　題　：  Read init_design_catarog.csv file
//
//　概　　要　：  Read init_design_catarog.csv file
//
//　戻　り　値：  
//
//　引　　数　：  string                  sInFielPath              (I)              File path
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/25   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

BOOL CScriptReader::ReadInitList( string          sInFilePath,
                                 LPDWORD    lpdwOutErrCode )
{
    // Local variabe
    DWORD                dwErrCode           = DGT_VALUE_ZERO_DWORD;        // Error codes
    BOOL                    bRet                    = DGT_RET_ERR;                          // Return value
    WORD                  wCheckResult       = DGT_VALUE_ZERO_WORD;          // check reusult
    fstream                fsCSVFile;                                                                // for read file
    CHAR                   cBuffer[1000];                                                          // Buffer
    vector<string>      vRow;                                                                      // row content
    CLogger*             lpLog                   = NULL;                                         // For write log
    BOOL                 bIsFirstFile        = TRUE;
    string               sRow                = "";
    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    CLogger::GetInstance( lpLog );
    

    // Check the validation of sInFilePath
    bRet   = CheckFilePath( sInFilePath, &wCheckResult, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        if (( wCheckResult == DGT_U_CFIP_PATH_INVALID ) ||
            ( wCheckResult == DGT_U_CFIP_PATH_NULL ) ||
            ( wCheckResult == DGT_U_CFIP_PATH_TOO_LONG ))
        {
            *lpdwOutErrCode = DGT_ERR_CSR_RIL_PARA;
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    m_vInitListCSV.clear();

    // Open CSV file
    fsCSVFile.open( sInFilePath,std::ios::binary| ios::in );
    if ( fsCSVFile.is_open() == true )
    {
        // Do nothing
    }
    else
    {
        // Write log
        bRet = lpLog->Log( "【エラー】：『initdesign_catarog.csv』ファイルがみつかりません。" , &dwErrCode);
        if ( bRet == DGT_RET_OK )
        {
            // Do nothing
        }
        else
        {
            *lpdwOutErrCode = dwErrCode;
            return DGT_RET_ERR;
        }
        *lpdwOutErrCode = DGT_ERR_CSR_RIL_OPEN_FILE;
        return DGT_RET_ERR;
    }

    while(  !fsCSVFile.eof())
    {
        sRow     = "";
        // memset
        memset( cBuffer, 0x00, sizeof( cBuffer ));
        // get strlen
        fsCSVFile.getline( cBuffer, sizeof( cBuffer ));
        // Check EF BB BF ( UTF-8 with BOM
        if ( bIsFirstFile && ( (BYTE) cBuffer[0] == (BYTE)0x0EF ) && ( (BYTE) cBuffer[1] == (BYTE)  0xbb ) && ((BYTE)  cBuffer[2] == (BYTE) 0xbf ))
        {
            memcpy( cBuffer, &cBuffer[3], strlen( cBuffer) - 3 );
            cBuffer[strlen( cBuffer)-3]= '\0';
            bIsFirstFile = FALSE;
        }
        else
        {
            // Do nothong
        }
        sRow = Utf8toAnsi( cBuffer, strlen( cBuffer ));
        if (( sRow      == ""       ) ||
            ( sRow[0]   == '#'      ) ||
            ( sRow[0]   == char(13)))
        {
            continue;
        }

        vRow.clear();
        // split string
        vRow = SplitString( sRow, ",");
        for ( DWORD dwCntSub = 0; dwCntSub < vRow.size(); dwCntSub++ )
        {
            vRow[dwCntSub].erase(std::remove(vRow[dwCntSub].begin(), vRow[dwCntSub].end(), char(13)),  vRow[dwCntSub].end());
            vRow[dwCntSub].erase(std::remove(vRow[dwCntSub].begin(), vRow[dwCntSub].end(), '\n'),  vRow[dwCntSub].end());
        }
        if ( vRow.size() == INIT_ITEM_NUM )
        {
            m_vInitListCSV.push_back( SCT_INIT_CSV( vRow[0], vRow[1] ));
        }
        else
        {
            m_vInitListCSV.clear();
            *lpdwOutErrCode = DGT_ERR_CSR_RIL_INVALID_FORMAT;
            fsCSVFile.close();
            return DGT_RET_ERR;
        }
    }

    fsCSVFile.close();

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  ReadCSVList
//
//　表　　題　：  Read CSV list file
//
//　概　　要　：  Read CSV list file
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::ReadCSVList( LPDWORD lpdwOutErrCode )
{
    // Local variable
    DWORD   dwErrCode = DGT_VALUE_ZERO_DWORD;             // Error code
    BOOL       bRet          = DGT_RET_OK;                                  // Return value

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Read format list
    bRet = ReadFormatList( m_sManualCSVFolder + "\\" + FMT_LIST_FNAME , &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // do nothing
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    bRet           = DGT_RET_ERR;
    dwErrCode  = DGT_VALUE_ZERO_DWORD;
    // Read area list
    bRet = ReadAreaList( m_sManualCSVFolder + "\\" + AREA_LIST_FNAME , &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // do nothing
    }
    else
    {
        // Write log
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    bRet           = DGT_RET_ERR;
    dwErrCode  = DGT_VALUE_ZERO_DWORD;
    // Read Tag list
    bRet = ReadTagList( m_sAutoCSVFolder + "\\" + TAG_LIST_FNAME , &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // do nothing
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    bRet           = DGT_RET_ERR;
    dwErrCode  = DGT_VALUE_ZERO_DWORD;
    // Read limit list CSV
    bRet = ReadLimitList( m_sManualCSVFolder + "\\" + LIMIT_LIST_FNAME , &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // do nothing
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    bRet           = DGT_RET_ERR;
    dwErrCode  = DGT_VALUE_ZERO_DWORD;
    // Read init list
    bRet = ReadInitList( m_sAutoCSVFolder + "\\" + INITDESING_LIST_FNAME , &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // do nothing
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    return DGT_RET_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  ReadCatalog
//
//　表　　題　：  Read catalog information
//
//　概　　要　：  Read catalog information
//
//　戻　り　値：  
//
//　引　　数　：  string                 sInAreaJPName        (I)              Area name
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::ReadCatalog( string sInAreaJPName, LPDWORD lpdwOutErrCode )
{
    // Local variable
    DWORD          dwErrCode     =   DGT_VALUE_ZERO_DWORD;        // Error code
    BOOL              bRet              =   DGT_RET_ERR;                           // Return value
    string              sFilePath        =    "";                                            // File path
    WORD             wCheckResult = DGT_VALUE_ZERO_WORD;            // Check result
    CHAR              cBuffer[1000];                                                      // Buffer
    vector<string> vRow;                                                                  // Row content vector
    fstream           fsCSVFile;                                                            // File stream
    CLogger*          lpLog              = NULL;                                          // For write log
    CString           csTemp;
    BOOL              bIsFirstFile        = TRUE;
    string            sRow                = "";
    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    CLogger::GetInstance( lpLog );
    
    // Find catalog file in AreaList:
    auto it = find( m_vAreaListCSV.begin(), m_vAreaListCSV.end(), sInAreaJPName );
    if ( it != m_vAreaListCSV.end())
    {
        if ( m_mCatalogList[sInAreaJPName].size() > 0 )
        {
            // This catalog file is already loaded
            return DGT_RET_OK;
        }
        else
        {
            csTemp = it->sArea_Catalog.c_str();
            csTemp.Trim();
            // Get catalog file path
            sFilePath = m_sAutoCSVFolder + "\\"+csTemp.GetBuffer();
        }
    }
    else
    {
        *lpdwOutErrCode = DGT_ERR_CSR_RCTL_PARA;
        return DGT_RET_ERR;
    }

    // Check the validation of file path
    bRet = CheckFilePath( sFilePath, &wCheckResult, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        if (( wCheckResult == DGT_U_CFIP_PATH_INVALID ) ||
            ( wCheckResult == DGT_U_CFIP_PATH_NULL ) ||
            ( wCheckResult == DGT_U_CFIP_PATH_TOO_LONG ))
        {
            *lpdwOutErrCode = DGT_ERR_CSR_RCTL_FILE_PATH;
            bRet = lpLog->Log( "【エラー】："+it->sArea_Catalog+"ファイルがみつかりません。" , &dwErrCode);
            if ( bRet == DGT_RET_OK )
            {
                // Do nothing
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
                return DGT_RET_ERR;
            }
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    // Open catalog file
    fsCSVFile.open( sFilePath.c_str(), ios::in );
    if ( fsCSVFile.is_open() == true )
    {
        // Do nothing
    }
    else
    {
        // Write log
        bRet = lpLog->Log( "【エラー】："+it->sArea_Catalog+"ファイルがみつかりません。" , &dwErrCode);
        if ( bRet == DGT_RET_OK )
        {
            // Do nothing
        }
        else
        {
            *lpdwOutErrCode = dwErrCode;
            return DGT_RET_ERR;
        }
        *lpdwOutErrCode = DGT_ERR_CSR_RCTL_OPEN_FILE;
        return DGT_RET_ERR;
    }

    while( !fsCSVFile.eof())
    {
        sRow        = "";
        // memset
        memset( cBuffer, 0x00, sizeof( cBuffer ));
        // get line
        fsCSVFile.getline( cBuffer, sizeof( cBuffer ));
        if ( bIsFirstFile && ( (BYTE) cBuffer[0] == (BYTE)0x0EF ) && ( (BYTE) cBuffer[1] == (BYTE)  0xbb ) && ((BYTE)  cBuffer[2] == (BYTE) 0xbf ))
        {
            memcpy( cBuffer, &cBuffer[3], strlen( cBuffer) - 3 );
            cBuffer[strlen( cBuffer)-3]= '\0';
            bIsFirstFile = FALSE;
        }
        else
        {
            // Do nothong
        }
        sRow = Utf8toAnsi( cBuffer, strlen( cBuffer ));
        if (( sRow      == ""       ) ||
            ( sRow[0]   == '#'      ))
        {
            continue;
        }

        vRow.clear();
        // split string
        vRow = SplitString( sRow, ",");
        if ( vRow.size() == CATALOG_ITEM_NUM )
        {
            m_mCatalogList[sInAreaJPName].push_back( SCT_CATALOG_CSV( vRow[0], vRow[1],vRow[2], vRow[3],vRow[4], vRow[5],vRow[6], vRow[7] ));
        }
        else
        {
            m_mCatalogList[sInAreaJPName].clear();
            *lpdwOutErrCode = DGT_ERR_CSR_RIL_INVALID_FORMAT;
            fsCSVFile.close();
            return DGT_RET_ERR;
        }
    }

    fsCSVFile.close();

    return DGT_RET_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  ReadScript
//
//　表　　題　：  Read script
//
//　概　　要　：  Read script
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::ReadScript( LPDWORD lpdwOutErrCode )
{
    // Local variable
    DWORD     dwErrCode        = DGT_VALUE_ZERO_DWORD;
    WORD       wChecResult      = DGT_VALUE_ZERO_WORD;
    BOOL         bRet                 = DGT_RET_ERR;

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Read CSV List
    bRet = ReadCSVList( &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    // Read Screen List file
    bRet             = DGT_RET_ERR;
    dwErrCode    = DGT_VALUE_ZERO_DWORD;
    bRet = ReadScreenList( &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  SearchCatalogInfor
//
//　表　　題　：  Search catalog information
//
//　概　　要　：  Search catalog information
//
//　戻　り　値：  
//
//　引　　数　：  string                           sInArea                   (I)             Area name
//                         string                           sInGaikan                (I)              AprName
//                         string                           sInDosa                   (I)             Operation
//                         SCT_CATALGO_CSV      sctOutCataLog         (O)             Out catalog information
//                         LPDWORD                     lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/27   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::SearchCatalogInfo(
                                         string                    sInArea,
                                         string                    sInGaikan,
                                         string                    sInDosa,
                                         SCT_CATALOG_CSV           &sctOutCatalog,
                                         LPDWORD                   lpdwOutErrCode )
{
    // Local variable
    DWORD     dwErrCode        = DGT_VALUE_ZERO_DWORD;      // Error code
    DWORD     dwCnt               = DGT_VALUE_ZERO_DWORD;      // Counter
    BOOL         bRet                 = DGT_RET_ERR;                        // Return value

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    if ( m_mCatalogList[ sInArea ].size() == 0 )
    {
        *lpdwOutErrCode = DGT_ERR_CSR_SCTL_CATALOG_NOT_EXIST;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    for ( dwCnt = 0; dwCnt < m_mCatalogList[sInArea].size(); dwCnt ++ )
    {
        if (( m_mCatalogList[sInArea][dwCnt].sGaikan == sInGaikan ) && 
            ( m_mCatalogList[sInArea][dwCnt].sDosa   == sInDosa ))
        {
            sctOutCatalog = m_mCatalogList[sInArea][dwCnt];
            return DGT_RET_OK;
        }
    }

    *lpdwOutErrCode = DGT_ERR_CSR_SCTL_NOT_FOUND;
    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  CheckInputValidation
//
//　表　　題　：  Check input validation
//
//　概　　要　：  Check input validation
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/27   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::CheckInputValidation( LPDWORD lpdwOutErrCode )
{
    // Local variable
    DWORD            dwErrCode          = DGT_VALUE_ZERO_DWORD;            // Error code
    BOOL             bRet               = DGT_RET_ERR;                              // Return value
    WORD             wCheckResult       = DGT_VALUE_ZERO_WORD;             // Check result
    CLogger*         lpLog              = NULL ;                                          // For write log
    string           sManualCSVFilePath = "";
    string           sAutoCSVFilePath   = "";

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Get logger instance
    CLogger::GetInstance( lpLog );
    

    bRet                = DGT_RET_ERR;
    dwErrCode       = DGT_VALUE_ZERO_DWORD;
    // Check the validation of manual CSV Folder
    bRet = CheckFolderPath( m_sManualCSVFolder, &wCheckResult, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        if ( wCheckResult != DGT_U_CFIP_PATH_OK )
        {
            // Write log
            bRet = lpLog->Log( "【エラー】：手作成カタログファイル格納先フォルダがみつかりません。" , &dwErrCode);
            if ( bRet == DGT_RET_OK )
            {
                // Do nothing
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
                return DGT_RET_ERR;
            }
            *lpdwOutErrCode = DGT_ERR_CSR_CIV_AU_FOLDER_INVALID;
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    bRet                = DGT_RET_ERR;
    dwErrCode       = DGT_VALUE_ZERO_DWORD;
    wCheckResult   = DGT_VALUE_ZERO_WORD;
   // Check the validation of automatic CSV Folder
    bRet = CheckFolderPath( m_sAutoCSVFolder, &wCheckResult, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        if ( wCheckResult != DGT_U_CFIP_PATH_OK )
        {
            // Write log
            bRet = lpLog->Log( "【エラー】：自動生成カタログファイル格納先フォルダがみつかりません。" , &dwErrCode);
            if ( bRet == DGT_RET_OK )
            {
                // Do nothing
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
                return DGT_RET_ERR;
            }
            *lpdwOutErrCode = DGT_ERR_CSR_CIV_MA_FOLDER_INVALID;
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    bRet                = DGT_RET_ERR;
    dwErrCode       = DGT_VALUE_ZERO_DWORD;
    wCheckResult   = DGT_VALUE_ZERO_WORD;
    // Check the validation of screen folder path
    bRet = CheckFolderPath( m_sSceenFolderPath, &wCheckResult, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        if ( wCheckResult != DGT_U_CFIP_PATH_OK )
        {
            // Write log
            bRet = lpLog->Log( "【エラー】：画面仕様書ファイル格納先フォルダがみつかりません。" , &dwErrCode);
            if ( bRet == DGT_RET_OK )
            {
                // Do nothing
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
                return DGT_RET_ERR;
            }
            *lpdwOutErrCode = DGT_ERR_CSR_CIV_SC_FOLDER_INVALID;
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    bRet           = DGT_RET_ERR;
    dwErrCode      = DGT_VALUE_ZERO_DWORD;
    wCheckResult   = DGT_VALUE_ZERO_WORD;
    sManualCSVFilePath   = m_sManualCSVFolder;
    sAutoCSVFilePath     = m_sAutoCSVFolder;
    if ( sManualCSVFilePath[sManualCSVFilePath.size() -1 ] == '\\' )
    {
        // Do nothing
    }
    else
    {
        sManualCSVFilePath += "\\";
    }
    if ( sAutoCSVFilePath[sAutoCSVFilePath.size() -1 ] == '\\' )
    {
        // Do nothing
    }
    else
    {
        sAutoCSVFilePath += "\\";
    }

    // Check the validation of format csv file
    bRet = CheckFilePath( sManualCSVFilePath + FMT_LIST_FNAME, &wCheckResult, &dwErrCode);
    if ( bRet == DGT_RET_OK )
    {
        if ( wCheckResult != DGT_U_CFIP_PATH_OK )
        {
            // Write log
            bRet = lpLog->Log( "【エラー】：『fmt_list.csv』ファイルがみつかりません。" , &dwErrCode);
            if ( bRet == DGT_RET_OK )
            {
                // Do nothing
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
                return DGT_RET_ERR;
            }
            *lpdwOutErrCode = DGT_ERR_CSR_CIV_FMT_FILE_INVALID;
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    bRet           = DGT_RET_ERR;
    dwErrCode      = DGT_VALUE_ZERO_DWORD;
    wCheckResult   = DGT_VALUE_ZERO_WORD;
    // Check the validation of area csv file
    bRet = CheckFilePath( sManualCSVFilePath + AREA_LIST_FNAME, &wCheckResult, &dwErrCode);
    if ( bRet == DGT_RET_OK )
    {
        if ( wCheckResult != DGT_U_CFIP_PATH_OK )
        {
            // Write log
            bRet = lpLog->Log( "【エラー】：『area_list.csv』ファイルがみつかりません。" , &dwErrCode);
            if ( bRet == DGT_RET_OK )
            {
                // Do nothing
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
                return DGT_RET_ERR;
            }
            *lpdwOutErrCode = DGT_ERR_CSR_CIV_AREA_FILE_INVALID;
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    bRet           = DGT_RET_ERR;
    dwErrCode      = DGT_VALUE_ZERO_DWORD;
    wCheckResult   = DGT_VALUE_ZERO_WORD;
    // Check the validation of limit csv file
    bRet = CheckFilePath( sManualCSVFilePath + LIMIT_LIST_FNAME, &wCheckResult, &dwErrCode);
    if ( bRet == DGT_RET_OK )
    {
        if ( wCheckResult != DGT_U_CFIP_PATH_OK )
        {
            // Write log
            bRet = lpLog->Log( "【エラー】：『limit_list.csv』ファイルがみつかりません。" , &dwErrCode);
            if ( bRet == DGT_RET_OK )
            {
                // Do nothing
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
                return DGT_RET_ERR;
            }
            *lpdwOutErrCode = DGT_ERR_CSR_CIV_LIMIT_FILE_INVALID;
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    bRet           = DGT_RET_ERR;
    dwErrCode      = DGT_VALUE_ZERO_DWORD;
    wCheckResult   = DGT_VALUE_ZERO_WORD;
    // Check the validation of tag list csv file
    bRet = CheckFilePath( sAutoCSVFilePath + TAG_LIST_FNAME, &wCheckResult, &dwErrCode);
    if ( bRet == DGT_RET_OK )
    {
        if ( wCheckResult != DGT_U_CFIP_PATH_OK )
        {
            // Write log
            bRet = lpLog->Log( "【エラー】：『tag_list.csv』ファイルがみつかりません。" , &dwErrCode);
            if ( bRet == DGT_RET_OK )
            {
                // Do nothing
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
                return DGT_RET_ERR;
            }
            *lpdwOutErrCode = DGT_ERR_CSR_CIV_TAG_FILE_INVALID;
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    bRet           = DGT_RET_ERR;
    dwErrCode      = DGT_VALUE_ZERO_DWORD;
    wCheckResult   = DGT_VALUE_ZERO_WORD;
    // Check the validation of init design list csv file
    bRet = CheckFilePath( sAutoCSVFilePath + INITDESING_LIST_FNAME, &wCheckResult, &dwErrCode);
    if ( bRet == DGT_RET_OK )
    {
        if ( wCheckResult != DGT_U_CFIP_PATH_OK )
        {
            // Write log
            bRet = lpLog->Log( "【エラー】：『initdesign_catarog.csv』ファイルがみつかりません。" , &dwErrCode);
            if ( bRet == DGT_RET_OK )
            {
                // Do nothing
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
                return DGT_RET_ERR;
            }
           *lpdwOutErrCode = DGT_ERR_CSR_CIV_INIT_FILE_INVALID;
            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  ReadScreenList
//
//　表　　題　：  Read screen list
//
//　概　　要　：  Read screen list
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/27   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::ReadScreenList( LPDWORD lpdwOutErrCode )
{
    // Local variable
    vector<string>             vScreenListFile;                                    // screen list file path
    DWORD                      dwErrCode         = DGT_VALUE_ZERO_DWORD;           // Error code
    BOOL                       bRet              = DGT_RET_ERR;                    // Return value
    DWORD                      dwCnt             = DGT_VALUE_ZERO_DWORD;           // Counter
    DWORD                      dwTotal           = DGT_VALUE_ZERO_DWORD;           // For calculate status
    WORD                       wCheckResult      = DGT_VALUE_ZERO_WORD;            // Check result
    vector<string>             vListFilePath;                                      // List file path
    vector<string>             vExtensionFilter;                                   // list of extension to filter
    CLogger*                   lpLog             = NULL;                           // For write log
    SCT_PROG_STATUS            sctProgStt;                                         // Status info

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    CLogger::GetInstance( lpLog );
    

    // Check the validation of screen folder path
    bRet = CheckFolderPath( m_sSceenFolderPath, &wCheckResult, &dwErrCode );
    if ( bRet == DGT_RET_OK  )
    {
        if ( wCheckResult != DGT_U_CFP_PATH_OK )
        {
            *lpdwOutErrCode = DGT_ERR_CSR_RSL_PATH_INVALID;
            return DGT_RET_ERR;
        }
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    // Clear backgroudn collection vector
    m_vBgColor.clear();

    // Add extension
    vExtensionFilter.push_back(".xlsx");
    vExtensionFilter.push_back(".xls");
    vExtensionFilter.push_back(".XLSX");
    vExtensionFilter.push_back(".XLS");
    // Get alll excel file in folder
    bRet  = GetAllFileInFolder( m_sSceenFolderPath, vExtensionFilter, vListFilePath , FALSE );
    if ( vListFilePath.size() == 0 )
    {
        // write log
        bRet = lpLog->Log( "【エラー】：Excelファイルがみつかりません。", &dwErrCode );
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
    dwTotal = vListFilePath.size();
    for ( dwCnt = 0 ; dwCnt < dwTotal; dwCnt++ )
    {
        // Update status progress bar
        sctProgStt.nMask       = ( MASK_UPDATE_TEXT | MASK_UPDATE_PERCENT );
        sctProgStt.sStatus     = "現在 "+ to_string((LONGLONG)dwTotal)+"件中"+to_string((LONGLONG)dwCnt)+"件　ファイルを読み込んでいる";
        sctProgStt.dwPercent   = (DWORD ) ((50*dwCnt)/dwTotal);
        sctProgStt.sLog        = "";
        ::SendMessageA( ghMainDlg, DGT_MSG, DGT_NOTIFY_UPDATE_STATUS, (LPARAM)&sctProgStt );

        // Read each screen file
        bRet = ReadEachScreenFile( vListFilePath[dwCnt], &dwErrCode );
        //if ( bRet == DGT_RET_OK ) 
        //{
        //    // Do nothing
        //}
        //else
        //{
        //    *lpdwOutErrCode = dwErrCode;
        //    return DGT_RET_ERR;
        //}

        // Check cancel flag
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
                return DGT_RET_OK;
            }
            return DGT_RET_OK;
        }

    }

    // Notify to GUI that complete generate
    sctProgStt.nMask       = ( MASK_UPDATE_TEXT | MASK_UPDATE_PERCENT  );
    sctProgStt.sStatus     = "データ読み込みが完了";
    sctProgStt.dwPercent   = 50;
    sctProgStt.sLog        = "";
    ::SendMessageA( ghMainDlg, DGT_MSG, DGT_NOTIFY_UPDATE_STATUS, (LPARAM)&sctProgStt );

    bRet = lpLog->Log( std::to_string((LONGLONG)dwTotal) + "ファイル分が読まれた。", &dwErrCode);
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    return DGT_RET_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  ReadEachScreenFile
//
//　表　　題　：  Read each screen file
//
//　概　　要　：  Read each screen file
//
//　戻　り　値：  
//
//　引　　数　：  string                  sInFilePath              (I)              File path
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/27   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

BOOL CScriptReader::ReadEachScreenFile( string sInFilePath, LPDWORD lpdwOutErrCode )
{
    // Local variable
    DWORD                     dwErrCode        = DGT_VALUE_ZERO_DWORD;         // Error code
    DWORD                     dwCnt            = DGT_VALUE_ZERO_DWORD;         // Counter
    BOOL                      bRet             = DGT_RET_ERR;                  // Return value
    WORD                      wCheckResult     = DGT_VALUE_ZERO_WORD;          // Check result
    CLogger*                  lpLog            = NULL;                         //  Logger
    vector<string>            vSheetName;                                      // Sheet name list

        // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    CLogger::GetInstance( lpLog );
    

    // Check the validation of sInFilePath
    bRet   = CheckFilePath( sInFilePath, &wCheckResult, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        if (( wCheckResult == DGT_U_CFIP_PATH_INVALID ) ||
            ( wCheckResult == DGT_U_CFIP_PATH_NULL ) ||
            ( wCheckResult == DGT_U_CFIP_PATH_TOO_LONG ))
        {
            *lpdwOutErrCode = DGT_ERR_CSR_RESF_PATH_INVALID;
            bRet = lpLog->Log( "【エラー】：『"+ sInFilePath +"』ファイルが開けませんでした。",&dwErrCode );
            if ( bRet == DGT_RET_OK )
            {
                // Do nothing
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
            }

            return DGT_RET_ERR;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    // Open excel file
    bRet = m_cExcelReader.OpenExcelFile( sInFilePath, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        // Write log
        bRet = lpLog->Log( "【エラー】：『"+ sInFilePath +"』ファイルが開けませんでした。",&dwErrCode );
        if ( bRet == DGT_RET_OK )
        {
            // Do nothing
        }
        else
        {
            *lpdwOutErrCode = dwErrCode;
        }
        return DGT_RET_ERR;
    }

    bRet = lpLog->Log( "{"+sInFilePath+"}ファイル：処理開始。",&dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    // Get "マスタ" sheet information
    bRet = GetMasterSheetInfo( &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        *lpdwOutErrCode = DGT_ER_CSR_GMSI_SHEET_NOT_FOUND;
        // Close excel file
        bRet = m_cExcelReader.CloseExcelFile( &dwErrCode );
        if ( bRet == DGT_RET_OK )
        {
            // Do nothing
        }
        else
        {
            *lpdwOutErrCode = dwErrCode;
            return DGT_RET_ERR;
        }
        return DGT_RET_ERR;
    }
    // Get "作成一覧" sheet information
    bRet = GetCreationSheetInfo( vSheetName, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        // Close excel file
        bRet = m_cExcelReader.CloseExcelFile( &dwErrCode );
        if ( bRet == DGT_RET_OK )
        {
            // Do nothing
        }
        else
        {
            *lpdwOutErrCode = dwErrCode;
            return DGT_RET_ERR;
        }
        return DGT_RET_ERR;
    }

    if ( vSheetName.size() > 0 )
    {
        for ( dwCnt =0; dwCnt < vSheetName.size(); dwCnt++ )
        {
            if ( gbCancel == TRUE )
            {
                break;
            }
            ReadEachSheet( vSheetName[dwCnt], &dwErrCode );
        }
    }
    else
    {
        // Write log when have no sheet data in excel file
        bRet  = lpLog->Log( "【エラー】：出力対象シートがありません。", &dwErrCode );
        if ( bRet == DGT_RET_OK )
        {
            // Do nothing
        }
        else
        {
            *lpdwOutErrCode = dwErrCode;
            // Close excel file
            bRet = m_cExcelReader.CloseExcelFile( &dwErrCode );
            if ( bRet == DGT_RET_OK )
            {
                // Do nothing
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
                return DGT_RET_ERR;
            }
            return DGT_RET_ERR;
        }
    }
// Start TrunglV 2015-08-07 : Process for remove maru
    if ( gbRemoveMaru == TRUE )
    {
        // Remove maru
        bRet = m_cExcelReader.RemoveMaru( &dwErrCode );
        if ( bRet == DGT_RET_OK )
        {
            // Do nothing
        }
        else
        {
            *lpdwOutErrCode = dwErrCode;
            // Close excel file
            bRet = m_cExcelReader.CloseExcelFile( &dwErrCode );
            if ( bRet == DGT_RET_OK )
            {
                // Do nothing
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
                return DGT_RET_ERR;
            }
            return DGT_RET_ERR;
        }
    }
// End TrunglV 2015-08-07 : 

    // Close excel file
    bRet = m_cExcelReader.CloseExcelFile( &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    return DGT_RET_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  GetMasterSheetInfo
//
//　表　　題　：  Get master sheet information
//
//　概　　要　：  Get master sheet information
//
//　戻　り　値：  
//
//　引　　数　：  
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/27   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::GetMasterSheetInfo( LPDWORD lpdwOutErrCode )
{
    // Local variable
    DWORD                         dwErrCode        =   DGT_VALUE_ZERO_DWORD;        // Error code
    DWORD                         dwCnt            =   DGT_VALUE_ZERO_DWORD;        // Counter
    BOOL                          bRet             =   DGT_RET_ERR;                  // Return value
    CLogger*                      lpLog            =   NULL;                         // For write log
    Excel::_WorksheetPtr          lpWs             =  NULL;                          // Worksheet pointer
    vector<string>                vRowContent;                                       // For get row content
    string                        sBgName          = "";                             // BG Name
    string                        sClassName       = "";                             // Class name
    LONG                          lIndex           = DGT_VALUE_ZERO_LONG;            // Index

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }
    CLogger::GetInstance( lpLog );
    

    //m_vBgColor.clear();

    // Get sheet
    bRet = m_cExcelReader.GetSheet( SHEET_MASTER, lpWs, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        lpWs            = NULL;
        *lpdwOutErrCode = dwErrCode;
        lpLog->Log( "【エラー】：『◆マスタ』シートがみつかりません。", &dwErrCode );
        return DGT_RET_ERR;
    }

    dwCnt = MASTER_START_ROW;

    while( 1 )
    {
        vRowContent.clear();
        bRet = m_cExcelReader.GetRowContent( 
                                               dwCnt,
                                               MASTER_START_COL,
                                               MASTER_END_COL,
                                               lpWs,
                                               vRowContent,
                                               &dwErrCode );
        if ( bRet == DGT_RET_OK )
        {
            // Do nothing
        }
        else
        {
            lpWs            = NULL;
            *lpdwOutErrCode = dwErrCode;
            return DGT_RET_ERR;
        }
        sBgName       = vRowContent[0];
        sClassName   = vRowContent[1];
        if ( sBgName == "" )
        {
            lpWs = NULL;
            break;
        }
        else
        {
            Search_MstBgColor( sBgName, lIndex, &dwErrCode );
            if ( lIndex == NOT_FOUND )
            {
                m_vBgColor.push_back( SCT_BGCOLOR( sBgName, sClassName ));
            }
            else
            {
                if ( sClassName != m_vBgColor[lIndex].sClassSetName )
                {
                    // Write log
                    bRet = lpLog->Log(
                        "警告】  ：背景色          ：「"+ sClassName +"」は重複しています。\n"+
                        "              シート名        ：◆マスタ\n"+
                        "              行数              ："+ std::to_string((LONGLONG) lIndex +1 )+"\n"+
                        "     ≪項目更新≫\n"+
                        "              ステータス名を"+m_vBgColor[lIndex].sClassSetName +"から"+sClassName+"に更新します。"
                        , &dwErrCode);
                    if ( bRet == DGT_RET_OK )
                    {
                        // Do nothing
                    }
                    else
                    {
                        lpWs = NULL;
                        *lpdwOutErrCode = dwErrCode;
                        return DGT_RET_ERR;
                    }
                    m_vBgColor[lIndex].sClassSetName  = sClassName;
                }
            }
        }
        dwCnt ++;
    }
    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  GetCreationSheetInfo
//
//　表　　題　：  Get "作成一覧" sheet information
//
//　概　　要　：  Get "作成一覧" sheet information
//
//　戻　り　値：  
//
//　引　　数　：  vector<string>    &vOutSheetName    (O)             Sheet name list
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/27   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::GetCreationSheetInfo( vector<string>  &vOutSheetName, LPDWORD lpdwOutErrCode )
{
    // Local variable
    DWORD                          dwErrCode        =   DGT_VALUE_ZERO_DWORD;       // Error code
    DWORD                          dwCnt            =  DGT_VALUE_ZERO_DWORD;        // Counter
    BOOL                           bRet             =   DGT_RET_ERR;                // Return value
    CLogger*                       lpLog            =   NULL;                       // For write log
    Excel::_WorksheetPtr           lpWs             =  NULL;                        // Worksheet pointer
    vector<string>                 vRowContent;                                     // Row content

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    CLogger::GetInstance( lpLog );

    // Get sheet
    bRet = m_cExcelReader.GetSheet( SHEET_CREATATION_LIST, lpWs, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        lpWs            = NULL;
        *lpdwOutErrCode = DGT_ER_CSR_GCSI_SHEET_NOT_FOUND;
        lpLog->Log( "【エラー】：『◆作成一覧』シートがみつかりません。", &dwErrCode );
        return DGT_RET_ERR;
    }

    dwCnt = LIST_START_ROW;

    while(1)
    {
        vRowContent.clear();
         bRet = m_cExcelReader.GetRowContent( 
                                               dwCnt,
                                               LIST_START_COL,
                                               LIST_END_COL,
                                               lpWs,
                                               vRowContent,
                                               &dwErrCode );
         if ( bRet == DGT_RET_OK )
         {
             // Do nothing
         }
         else
         {
             lpWs                   = NULL;
             *lpdwOutErrCode = dwErrCode;
             return DGT_RET_ERR;
         }

         if ( vRowContent[LIST_NO_COL] == "" )
         {
             lpWs = NULL;
             break;
         }
// Start TrunglV 2015-08-07: Process generate all
         if ( gbGenAll == TRUE )
         {
             // select for generate all screen 
             vOutSheetName.push_back( vRowContent[LIST_SHNAME_COL] );
         }
         else
         {
             if ( vRowContent[LIST_OUT_COL] == SUBJECT_MARU )
             {
                 // select checked are
                 vOutSheetName.push_back( vRowContent[LIST_SHNAME_COL] );
             }
         }
// End TrunglV 2015-08-07: 
         dwCnt++;
    }
    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  ReadEachSheet
//
//　表　　題　：  Read information of each sheet
//
//　概　　要　：  Read information of each sheet
//
//　戻　り　値：  
//
//　引　　数　：  string                 sInSheetName         (I)               Sheet Name
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/27   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::ReadEachSheet( string sInSheetName, LPDWORD lpdwOutErrCode )
{
    // Local variable
    DWORD                   dwErrCode          =   DGT_VALUE_ZERO_DWORD;      // Error code
    DWORD                   dwCnt              =   DGT_VALUE_ZERO_DWORD;      // Counter
    BOOL                    bRet               =   DGT_RET_ERR;               // Return value
    BOOL                    bResult            =   FALSE;                     // Check result
    CLogger*                lpLog              =   NULL;                      // For write log
    Excel::_WorksheetPtr    lpWorkSheet        =   NULL;                      // Worksheet pointer
    SCT_CATALOG_CSV         sctCatalog;                                       // Catalog information
    SCT_TAG_CSV             sctTagCSV;                                        // Tag information
    SCT_ITEM_INFO           sctItemInfo;                                      // Item information
    CArea*                  lpAreaObj          = NULL;                        // Area object
    vector<string>          vHeaderInfo;                                      // For get header information
    vector<string>          vRowContent;                                      // For get row content
    vector<string>          vTemp;                                            // Temp
    string                  sClass1            = "";                          // For get parent class
    string                  sInitClass1        = "";                          // For get init class
    string                  sClass2            = "";                          // For get child class
    string                  sInitClass2        = "";                          // For init class of child tag
    string                  sItemTagName       = "";                          // Tag name
    string                  sDispStr           = "";                          // Display string
    string                  sZoomSize          = "";                          // Zoom size string

    sctItemInfo.Memset();
    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Get log pointer
    CLogger::GetInstance( lpLog );
   

    // Write log
    bRet = lpLog->Log( sInSheetName + "：処理開始。", &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    // Get sheet
    bRet = m_cExcelReader.GetSheet( sInSheetName, lpWorkSheet, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        lpWorkSheet     = NULL;
        *lpdwOutErrCode = dwErrCode;
        lpLog->Log( "【エラー】：『"+sInSheetName+"』シートがみつかりません。", &dwErrCode );
        return DGT_RET_ERR;
    }

/*=================START GETTING HEADER DATA IN SCREEN SHEET=============*/
    // Create new area object
    lpAreaObj             = new CArea();

    //  Get header infor
    bRet = GetHeaderInfo( 
                lpWorkSheet,
                lpAreaObj,
                vHeaderInfo,
                &dwErrCode);

    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        delete lpAreaObj;
        lpWorkSheet     = NULL;
        *lpdwOutErrCode = dwErrCode;
        if ( dwErrCode == DGT_ERR_CSR_GHI_AREA_FUNC_EXISTED )
        {
            // Write log
            bRet = lpLog->Log("【エラー】： Create_"+ vHeaderInfo[OUT_FNAME_COL] + "_Area関数は存在しています",&dwErrCode );
            if ( bRet == DGT_RET_OK )
            {
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
                return DGT_RET_ERR;
            }
        }
        return DGT_RET_ERR;
    }

    //      Load Catalog infor
    bRet = ReadCatalog( lpAreaObj->m_sctAreaInfo.sAreaJPName, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        delete lpAreaObj;
        lpWorkSheet     = NULL;
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    m_lpCurrentArea  = lpAreaObj;
    m_sContenaTagId = "";

/*=================START GETTING ITEM DATA IN SCREEN SHEET===============*/
    dwCnt = DATA_START_ROW;
    while(1)
    {
        if ( gbCancel == TRUE )
        {
            break;
        }

        sctItemInfo.Memset();
        // Read step by step row on excel 
        bRet = m_cExcelReader.GetRowContent( 
                                    dwCnt, 
                                    DATA_START_COL,
                                    DATA_END_COL,
                                    lpWorkSheet,
                                    vRowContent,
                                    &dwErrCode );
        if ( bRet == DGT_RET_OK )
        {
            // Do nothing
        }
        else
        {
            lpWorkSheet     = NULL;
            *lpdwOutErrCode = dwErrCode;
            return DGT_RET_ERR;
        }

        // Break when have no data in row
        if ( vRowContent[NO_COL] == "" )
        {
            break;
        }

        // Check item data
        bRet = CheckItem( vRowContent, bResult, &dwErrCode );
        if ( bRet == DGT_RET_OK )
        {
            // Do nothing
        }
        else
        {
            lpWorkSheet     = NULL;
            *lpdwOutErrCode = dwErrCode;
            return DGT_RET_ERR;
        }

        /*--  ITEM is TAB AREA  --*/
        if ( vRowContent[KOMOKU_COL] == TAB_AREA )
        {
            // CReate TAB area data
            // In tab area, it do not read catalog file
            CreateTabAreaData(
                    vRowContent,
                   // vHeaderInfo,
                    &dwErrCode );
            dwCnt++;
            continue;
        }

        /*-- ITEM is EKI BUTTON --*/
        if ( vHeaderInfo[TEMPFMT_COL] == EKIBTN_FMT )
        {
            // Create EKI BUTTON data
            Ekibtn_Data_mk( vHeaderInfo[AREA_MODE_COL],
                        vRowContent,
                       // vHeaderInfo,
                        lpWorkSheet,
                        &dwErrCode );
            dwCnt++;
            continue;
        }

        // Set position for item
        vTemp.clear();
        vTemp   = SplitString( vRowContent[ICHI_COL] , "-" );
        vTemp.resize(2);
        if ((SuchiCheck( vTemp[ITEM_TOP] ) == 1 ) && ( atoi(vTemp[ITEM_TOP].c_str()) >= 1 ))
        {
            sctItemInfo.dwTop = (  (atoi(vTemp[ITEM_TOP].c_str()) - 1)*  m_lpCurrentArea->m_sctAreaInfo.dwCellHeight  )  + m_lpCurrentArea->m_sctAreaInfo.dwMarginTop;
        }
        else
        {
        }
        if (( SuchiCheck( vTemp[ITEM_LEFT]) == 1 ) && ( atoi(vTemp[ITEM_LEFT].c_str()) >= 1 ))
        {
            sctItemInfo.dwLeft = (  (atoi(vTemp[ITEM_LEFT].c_str()) - 1) * m_lpCurrentArea->m_sctAreaInfo.dwCellWidth  ) + m_lpCurrentArea->m_sctAreaInfo.dwMarginLeft; 
        }
        else
        {
        }

        // Get item with , height, font
        if ( SuchiCheck( vRowContent[ WIDTH_COL] ) == 1 ) 
        {
            sctItemInfo.dwWidth = atoi( vRowContent[ WIDTH_COL].c_str() ) * m_lpCurrentArea->m_sctAreaInfo.dwCellWidth;
        }
        else
        {
        }

        if ( SuchiCheck( vRowContent[ HEIGHT_COL] ) == 1 )
        {
            sctItemInfo.dwHeight = atoi( vRowContent[ HEIGHT_COL].c_str() ) * m_lpCurrentArea->m_sctAreaInfo.dwCellHeight;
            if ( vRowContent[DISPSTR_COL].find( "\n") != std::string::npos )
            {
                sctItemInfo.lLineHeight = sctItemInfo.dwHeight - 2;
            }
            else
            {
                sctItemInfo.lLineHeight = -1;
            }
        }
        else
        {
        }

         
        sZoomSize = vRowContent[ZOOMSIZE_COL];
        if ( SuchiCheck( sZoomSize ) == 1 )
        {
            sctItemInfo.fZoomSize = atof(sZoomSize.c_str());
        }
        else
        {}
        if ( SuchiCheck( vRowContent[ FONTSIZE_COL] ) == 1 )
        {
            sctItemInfo.dwFontSize = atoi( vRowContent[ FONTSIZE_COL].c_str());
        }
        else
        {
        }

        // get Gaikan data
        SearchCatalogInfo( 
                    m_lpCurrentArea->m_sctAreaInfo.sAreaJPName,
                    vRowContent[GAIKAN_COL], 
                    vRowContent[DOSA_COL],
                    sctCatalog,
                    &dwErrCode );

        if ( dwErrCode == DGT_ERR_CSR_SCTL_NOT_FOUND )
        {
            dwErrCode = DGT_VALUE_ZERO_DWORD;
            // Continue search with NASHI MODE
            SearchCatalogInfo( 
                        m_lpCurrentArea->m_sctAreaInfo.sAreaJPName,
                        vRowContent[GAIKAN_COL],
                        NASHI_MODE,
                        sctCatalog,
                        &dwErrCode );
            if ( dwErrCode == DGT_ERR_CSR_SCTL_NOT_FOUND )
            {
                // Write log
                string      sLogStr = "【エラー】"+vRowContent[NO_COL]+"-カタログ検索エラー:"+vRowContent[GAIKAN_COL]+","+ vRowContent[DOSA_COL];
                bRet = lpLog->Log( sLogStr, &dwErrCode );
                if ( bRet == DGT_RET_OK )
                {
                    // Do nothing
                }
                else
                {
                    lpWorkSheet     = NULL;
                    *lpdwOutErrCode = dwErrCode;
                    return DGT_RET_ERR;
                }
            }
        }

        sClass1       = "";
        sClass2       = "";
        sInitClass1   = "";
        sInitClass2   = "";
        // Set class for parent tag
       SetClass( 1,
               sctCatalog,
               sctItemInfo,
               vRowContent,
               sClass1,
               sctItemInfo.sStatus,
               sInitClass1,
               &dwErrCode );
       // Get class for child tag
       SetClass( 0, 
               sctCatalog, 
               sctItemInfo,
               vRowContent,
               sClass2,
               sctItemInfo.sStatus, 
               sInitClass2,
               &dwErrCode );

        sDispStr     = "";
        if ( vRowContent[DISPSTR_COL].substr(0,2) != "【" )
        {
            sDispStr = Conv_StrNewLine(  vRowContent[DISPSTR_COL] );
        }

        sctItemInfo.sInitText  = Conv_StrNewLine(vRowContent[INITSTR_COL]);
        if ( sctItemInfo.sInitText == NASHI_MODE_JP )
        {
            sctItemInfo.sInitText = "";
        }

        if (vRowContent[DEFAULTAPP_COL] == SUBJECT_MARU )
        {
            sctItemInfo.sStatus = "init";// + sctItemInfo.sStatus;
            sDispStr = sctItemInfo.sInitText;
        }
        else
        {
            sctItemInfo.sStatus = sctCatalog.sParameter;// + sctItemInfo.sStatus;
        }

        if (vRowContent[NULLSTRAPP_COL] == SUBJECT_MARU)
        {
            sctItemInfo.sNullStrInitApp = "true";

        }
        else
        {
            sctItemInfo.sNullStrInitApp = "false";
        }

        //フォーマットセット
        // Search Fmt_EI name
        auto Fmt_it = find( m_vFormatListCSV.begin(), m_vFormatListCSV.end(), vRowContent[INPUTFMT_COL] );
        if ( Fmt_it != m_vFormatListCSV.end() )
        {
            sctItemInfo.sFmt = Fmt_it->sFmt_EI;
         /*   if (( Fmt_it->sFmt_EI[Fmt_it->sFmt_EI.size() -1 ] == char(13) ) ||
                 ( Fmt_it->sFmt_EI[Fmt_it->sFmt_EI.size() -1 ] == '\n' ) )
            {
                sctItemInfo.sFmt = Fmt_it->sFmt_EI.substr( 0,Fmt_it->sFmt_EI.size() -2 );
            }*/
        }
        else
        {
            sctItemInfo.sFmt = "";
        }

        //SearchLimit_EI(vRowContent[INPUT_LIMIT_COL]);
        auto Limit_it = find( m_vLimitCSV.begin(), m_vLimitCSV.end(), vRowContent[INPUT_LIMIT_COL] );
        if ( Limit_it != m_vLimitCSV.end())
        {
            sctItemInfo.sLimit = Limit_it->sLimit_EI;
           /* if (( Limit_it->sLimit_EI[Limit_it->sLimit_EI.size() -1 ] == char(13) ) ||
                 ( Limit_it->sLimit_EI[Limit_it->sLimit_EI.size() -1 ] == '\n' ) )
            {
                sctItemInfo.sFmt = Limit_it->sLimit_EI.substr( 2, Fmt_it->sFmt_EI.size() -2 );
            }*/
        }
        else
        {
            sctItemInfo.sLimit = "";
        }

        // Get MinLen and Max Len
        Get_MinMaxLen( vRowContent[TAGID_COL], sctItemInfo.sMinLen, sctItemInfo.sMaxLen, vRowContent[ INPUTFMT_COL], &dwErrCode );

        // Set attribute for item
          sItemTagName  = sctCatalog.sTagName;

          sctItemInfo.sGaikan       = sctCatalog.sGaikanGrpName;
          sctItemInfo.sInitClass    = sInitClass2;                          // Set class for child
          sctItemInfo.sTagName      = sItemTagName;
          sctItemInfo.sAreaType     = m_lpCurrentArea->m_sctAreaInfo.sAreaType;
          sctItemInfo.bParent       = TRUE;

        // Update javascript information
        output_JS_tbl(
                vRowContent[TAGID_COL],
                vRowContent[ALTERNATE_TAGID_COL],
                vRowContent[CURUMU_COL],
                vRowContent[NO_COL],
                //vRowContent[DISPSTR_COL],
                sctCatalog.sTagName,
                vRowContent[ INPUTFMT_COL],
                sctItemInfo,
                &dwErrCode );

        if (  sItemTagName == "button" )
        {
            /*======= PROCESS FOR BUTTON ==========*/
            // Get button value
            sctItemInfo.sValue = GetBtnValue( vRowContent );
            sctItemInfo.dwType = ITEM_TYPE_BUTTON;
            if ( sClass1 != "" )
            {
                sctItemInfo.sClass  = sClass1;
                if ( sClass2 != "" )
                {
                    sctItemInfo.sClass += " " + sClass2;
                }
            }
            else
            {
                sctItemInfo.sClass  = sClass2;
            }

            CreateButtonData(
                     vRowContent,
                    // sClass2,  // For child class
                     sctCatalog,
                     sctItemInfo,
                     &dwErrCode);
        }
        else if (( sItemTagName == "div" )      ||
                   ( sItemTagName == "image" ))
        {
            sctItemInfo.dwType            = ITEM_TYPE_LABEL;
            sctItemInfo.sInitClass        = sInitClass1;
            sctItemInfo.sClass            = sClass1;
            /*======== PROCESS FOR DIV or IMAGE =======*/
            string   sKomoku = vRowContent[KOMOKU_COL];
            sctItemInfo.dwType      = ITEM_TYPE_LABEL;
            if ( sKomoku.find( "【ページエリア】") != std::string::npos )
            {

                CreatePageArea( 
                        lpWorkSheet,
                        vRowContent,
                       // sClass1,
                       // sctCatalog,
                        sctItemInfo,
                        &dwErrCode );
            }
            else
            {
                CreateDivData(
                        vRowContent,
                        sClass1,
                        sClass2,
                        sDispStr,
                        sctCatalog,
                        sctItemInfo,
                        &dwErrCode );
            }
            /*============== Set sContenaTagId ==============*/
            if ( sctCatalog.sAttribute == "コンテナ" )
            {
                if ( vRowContent[DISPSTR_COL] == KOMOKU_BOOKING_START )
                {
                    bResult = FALSE;
                    // Search tagid
                    SearchTagStr( vRowContent[TAGID_COL], sctTagCSV, bResult, &dwErrCode );
                    if ( bResult == TRUE )
                    {
                        m_sContenaTagId = sctTagCSV.sTagID;
                    }
                    else
                    {
                        m_sContenaTagId = "";
                    }
                }
                else if ( vRowContent[DISPSTR_COL] == KOMOKU_BOOKING_END )
                {
                     m_sContenaTagId = "";
                }
                else
                {
                    m_sContenaTagId = "";
                }
            }
            else
            {
                // Do nothing
            }
        }
        else if (  sItemTagName == "a" )
        {
            /*--PROCESS FOR A -- */
            sctItemInfo.dwType  = ITEM_TYPE_BUTTON;
            CreateAData(
                    vRowContent,
                    sClass1,
                    sClass2,
                    sDispStr,
                    sctCatalog,
                    sctItemInfo,
                    &dwErrCode );
        }
        else if ( sItemTagName == "ul" )
        {
            /*--PROCESS FOR UL -- */
            // Do nothing
        }
        else if (  sItemTagName == "li" )
        {
            /*--PROCESS FOR LI -- */
           sctItemInfo.dwType     = ITEM_TYPE_LABEL;
           sctItemInfo.sTagName   = "li";
           // In li, use initclass1
           sctItemInfo.sInitClass = sInitClass1;
            CreateListItemData(
                    vRowContent,
                    sClass1,
                    sDispStr,
                    sctCatalog,
                    sctItemInfo,
                    &dwErrCode );
        }
        else if ( sItemTagName == "pre" )
        {
            /*- PPOCESS FOR PRE tag -*/
            sctItemInfo.dwType    = ITEM_TYPE_LABEL;
            // Create item <pre><div> </div></pre> so set tagname is div
            sctItemInfo.sTagName  = "div";
            CreatePre( vRowContent,
                //sctCatalog,
                sctItemInfo, sDispStr );
        }
        else if ( sItemTagName =="time" )
        {
            /*--PROCESS FOR time -- */
            sctItemInfo.dwType    = ITEM_TYPE_LABEL;
            sctItemInfo.sTagName = "time";
            CreateTimeData(
                    vRowContent,
                    sClass1,
                    sctItemInfo,
                    sctCatalog,
                    &dwErrCode );
        }

        CreatePassWord( vRowContent, sctCatalog );
    dwCnt++;
    }

    lpWorkSheet = NULL;
    // Write log
    bRet = lpLog->Log( sInSheetName+ "：処理終了。", &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    m_vAreaList.push_back( m_lpCurrentArea );
    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  CreatePassWord
//
//　表　　題　：  CreatePassWord
//
//　概　　要　：  CreatePassWord
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::CreatePassWord( vector<string> vInRowContent, SCT_CATALOG_CSV sctInCatalog )
{
    CItem*              lpItem   = NULL;
    SCT_ITEM_INFO       sctItemInfo;
    DWORD               dwErrCode = DGT_VALUE_ZERO_DWORD;

    if ( vInRowContent[INPUTFMT_COL] != PASSWORD_MODE )
    {
        return DGT_RET_OK;
    }

    lpItem = new CItem();

    vInRowContent[TAGID_COL]   = vInRowContent[TAGID_COL] + TAGID_HIDDEN;
    lpItem->m_sctItem.Memset();
    lpItem->m_sctItem.dwType   = ITEM_TYPE_LABEL;
    lpItem->m_sctItem.sStatus  = "def"; //def_pa_visible_enable
    lpItem->m_sctItem.bVisible = FALSE;
    lpItem->m_sctItem.bEnable  = TRUE;
    lpItem->m_sctItem.sTagID   = "input_" + vInRowContent[NO_COL];
    lpItem->m_sctItem.sGaikan  = sctInCatalog.sGaikanGrpName;
    lpItem->m_sctItem.sTagName = "input";
    lpItem->m_sctItem.sNullStrInitApp = "false";
    lpItem->m_sctItem.bParent  = TRUE;
    lpItem->m_sctItem.sAreaType = m_lpCurrentArea->m_sctAreaInfo.sAreaType;

    output_JS_tbl( vInRowContent[TAGID_COL],
        NASHI_MODE,
        SUBJECT_BATSU,
        vInRowContent[NO_COL],
       // vInRowContent[DISPSTR_COL],
        "input",
        vInRowContent[INPUTFMT_COL],
        lpItem->m_sctItem,
        &dwErrCode );

    m_lpCurrentArea->m_vItemList.push_back( lpItem );

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  Ekibtn_Data_mk
//
//　表　　題　：  Make ekibutton
//
//　概　　要　：  Read script
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

BOOL CScriptReader::Ekibtn_Data_mk(
                string                    sInAreaJPName,
                vector<string>            vInRowContent,
               // vector<string>            vInHeaderRow,
                Excel::_WorksheetPtr      lpInWorkSheet,
                LPDWORD                   lpdwOutErrCode  )
{
    // Local variable
    DWORD                 dwErrCode        = DGT_VALUE_ZERO_DWORD;    // Error code
    BOOL                  bRet             = DGT_RET_ERR;
    SCT_CATALOG_CSV       sctCatalog;
    CLogger*              lpLog            = NULL;
    SCT_ITEM_INFO         sctItemInfo;
    BOOL                  bResult          = FALSE;
    SCT_TAG_CSV           sctTagCSV;
    vector<string>        vTemp;
    string                sItemTagName     = "";
    string                sClass1          = "";
    string                sClass2          = "";
    string                sInitClass1      = "";
    string                sInitClass2      = "";
    string                sZoomSize        = "";

    sctItemInfo.Memset();
    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    CLogger::GetInstance( lpLog );
   

    // Set position
    vTemp.clear();
    vTemp   = SplitString( vInRowContent[ICHI_COL] , "-" );
    vTemp.resize(2);
    if (( SuchiCheck( vTemp[ITEM_TOP] ) == 1 ) &&( atoi(vTemp[ITEM_TOP].c_str()) >= 1 ))
    {
        sctItemInfo.dwTop = (  (atoi(vTemp[ITEM_TOP].c_str()) - 1)*  m_lpCurrentArea->m_sctAreaInfo.dwCellHeight  )  + m_lpCurrentArea->m_sctAreaInfo.dwMarginTop;
    }
    else
    {
    }
    if (( SuchiCheck( vTemp[ITEM_LEFT]) == 1 ) &&( atoi(vTemp[ITEM_LEFT].c_str()) >= 1 ))
    {
        sctItemInfo.dwLeft = (  (atoi(vTemp[ITEM_LEFT].c_str()) - 1) * m_lpCurrentArea->m_sctAreaInfo.dwCellWidth  ) + m_lpCurrentArea->m_sctAreaInfo.dwMarginLeft; 
    }
    else
    {
    }

    // Get item with , height, font
    if ( SuchiCheck( vInRowContent[ WIDTH_COL] ) == 1 )
    {
        sctItemInfo.dwWidth = atoi( vInRowContent[ WIDTH_COL].c_str() ) * m_lpCurrentArea->m_sctAreaInfo.dwCellWidth;
    }
    else
    {
    }

    if ( SuchiCheck( vInRowContent[ HEIGHT_COL] ) == 1 )
    {
        sctItemInfo.dwHeight = atoi( vInRowContent[ HEIGHT_COL].c_str() ) * m_lpCurrentArea->m_sctAreaInfo.dwCellHeight;
        if ( vInRowContent[DISPSTR_COL].find( "\n") != std::string::npos )
        {
            sctItemInfo.lLineHeight = sctItemInfo.dwHeight - 2;
        }
        else
        {
            sctItemInfo.lLineHeight = -1;
        }
    }
    else
    {
    }

    sZoomSize = vInRowContent[ZOOMSIZE_COL];
    if ( SuchiCheck( sZoomSize ) == 1 )
    {
        sctItemInfo.fZoomSize = atof(sZoomSize.c_str());
    }
    else
    {
    }
    if ( SuchiCheck( vInRowContent[ FONTSIZE_COL] ) == 1 )
    {
        sctItemInfo.dwFontSize = atoi( vInRowContent[ FONTSIZE_COL].c_str()) ;
    }
    else
    {
    }

    // Search catalog
    SearchCatalogInfo( sInAreaJPName, vInRowContent[GAIKAN_COL], vInRowContent[DOSA_COL], sctCatalog,  &dwErrCode );
    if ( dwErrCode == DGT_ERR_CSR_SCTL_NOT_FOUND )
    {
        dwErrCode = DGT_VALUE_ZERO_DWORD;
        // Continue search with NASHI MODE
        SearchCatalogInfo( sInAreaJPName, vInRowContent[GAIKAN_COL], NASHI_MODE, sctCatalog,  &dwErrCode );
        if ( dwErrCode == DGT_ERR_CSR_SCTL_NOT_FOUND )
        {
            // Write log
            string      sLogStr = "【エラー】"+vInRowContent[NO_COL]+"-カタログ検索エラー:"+vInRowContent[GAIKAN_COL]+","+ vInRowContent[DOSA_COL];
            bRet = lpLog->Log( sLogStr, &dwErrCode );
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
    }
    // Set class
    sClass1       = "";
    sClass2       = "";
    sInitClass1   = "";
    sInitClass2   = "";
    // Set class for parent tag
    SetClass( 1,
            sctCatalog,
            sctItemInfo,
            vInRowContent,
            sClass1,
            sctItemInfo.sStatus,
            sInitClass1,
            &dwErrCode );
    // Get class for child tag
    SetClass( 0,
            sctCatalog,
            sctItemInfo,
            vInRowContent,
            sClass2,
            sctItemInfo.sStatus,
            sInitClass2,
            &dwErrCode );


    string sDispStr  ="";
    sDispStr     = "";
    if ( vInRowContent[DISPSTR_COL].substr(0,2) != "【" )
    {
        sDispStr = Conv_StrNewLine(  vInRowContent[DISPSTR_COL] );
    }

    sctItemInfo.sInitText  = Conv_StrNewLine(vInRowContent[INITSTR_COL]);

    if ( CheckNashiMode( sctItemInfo.sInitText ) == TRUE )
    {
        sctItemInfo.sInitText = "";
    }

    if (vInRowContent[DEFAULTAPP_COL] == SUBJECT_MARU )
    {
        sctItemInfo.sStatus = "init";// + sctItemInfo.sStatus;
        sDispStr = sctItemInfo.sInitText;
    }
    else
    {
        sctItemInfo.sStatus = sctCatalog.sParameter;// + sctItemInfo.sStatus;
    }

    if (vInRowContent[NULLSTRAPP_COL] == SUBJECT_MARU)
    {
        sctItemInfo.sNullStrInitApp = "true";

    }
    else
    {
        sctItemInfo.sNullStrInitApp = "false";
    }

    //SearchLimit_EI(vInRowContent[INPUT_LIMIT_COL]);
    auto Limit_it = find( m_vLimitCSV.begin(), m_vLimitCSV.end(), vInRowContent[INPUT_LIMIT_COL] );
    if ( Limit_it != m_vLimitCSV.end())
    {
        sctItemInfo.sLimit = Limit_it->sLimit_EI;
    }
    else
    {
        sctItemInfo.sLimit = "";
    }

    // Get MinLen and Max Len
    bRet = Get_MinMaxLen( vInRowContent[TAGID_COL], sctItemInfo.sMinLen, sctItemInfo.sMaxLen, vInRowContent[ INPUTFMT_COL], &dwErrCode );

    // Set attribute for item
    sItemTagName  = sctCatalog.sTagName;

    sctItemInfo.sGaikan         = sctCatalog.sGaikanGrpName;
    sctItemInfo.sInitClass      = sInitClass2;                          // Set class for child
    sctItemInfo.sTagName        = sItemTagName;
    sctItemInfo.bParent         = TRUE;
    sctItemInfo.sAreaType       = m_lpCurrentArea->m_sctAreaInfo.sAreaType;

    // Update javascript information
    output_JS_tbl(
        vInRowContent[TAGID_COL],
        vInRowContent[ALTERNATE_TAGID_COL],
        vInRowContent[CURUMU_COL],
        vInRowContent[NO_COL],
       // vInRowContent[DISPSTR_COL],
        sctCatalog.sTagName,
        vInRowContent[ INPUTFMT_COL],
        sctItemInfo,
        &dwErrCode );

    if (  sItemTagName == "button" )
    {
        /*======= PROCESS FOR BUTTON ==========*/
        // Get button value
        sctItemInfo.sValue = GetEkiBtn( vInRowContent );
        sctItemInfo.dwType = ITEM_TYPE_BUTTON;
        if ( sClass1 != "" )
        {
            sctItemInfo.sClass  = sClass1;
            if ( sClass2 != "" )
            {
                sctItemInfo.sClass += " " + sClass2;
            }
        }
        else
        {
            sctItemInfo.sClass  = sClass2;
        }

        CreateButtonData(
            vInRowContent,
            //sClass2,  // For child class
            sctCatalog,
            sctItemInfo,
            &dwErrCode);
    }
    else if (( sItemTagName == "div" )      ||
        ( sItemTagName == "image" ))
    {
        sctItemInfo.dwType            = ITEM_TYPE_LABEL;
        sctItemInfo.sInitClass        = sInitClass1;
        sctItemInfo.sClass            = sClass1;
        /*======== PROCESS FOR DIV or IMAGE =======*/
        string   sKomoku = vInRowContent[KOMOKU_COL];
        sctItemInfo.dwType      = ITEM_TYPE_LABEL;
        if ( sKomoku.find( "【ページエリア】") != std::string::npos )
        {

            CreatePageArea( 
                lpInWorkSheet,
                vInRowContent,
                //sClass1,
                //sctCatalog,
                sctItemInfo,
                &dwErrCode );
        }
        else
        {
            CreateDivData(
                vInRowContent,
                sClass1,
                sClass2,
                sDispStr,
                sctCatalog,
                sctItemInfo,
                &dwErrCode );
        }
        /*============== Set sContenaTagId ==============*/
        if ( sctCatalog.sAttribute == "コンテナ" )
        {
            if ( vInRowContent[DISPSTR_COL] == KOMOKU_BOOKING_START )
            {
                bResult = FALSE;
                // Search tagid
                SearchTagStr( vInRowContent[TAGID_COL], sctTagCSV, bResult, &dwErrCode );
                if ( bResult == TRUE )
                {
                    m_sContenaTagId = sctTagCSV.sTagID;
                }
                else
                {
                    m_sContenaTagId = "";
                }
            }
            else if ( vInRowContent[DISPSTR_COL] == KOMOKU_BOOKING_END )
            {
                m_sContenaTagId = "";
            }
            else
            {
                m_sContenaTagId = "";
            }
        }
        else
        {
            // Do nothing
        }
    }
    else if (  sItemTagName == "a" )
    {
        /*--PROCESS FOR A -- */
        sctItemInfo.dwType  = ITEM_TYPE_BUTTON;
        CreateAData(
            vInRowContent,
            sClass1,
            sClass2,
            sDispStr,
            sctCatalog,
            sctItemInfo,
            &dwErrCode );
    }
    else if ( sItemTagName == "ul" )
    {
        /*--PROCESS FOR UL -- */
        // Do nothing
    }
    else if (  sItemTagName == "li" )
    {
        /*--PROCESS FOR LI -- */
        sctItemInfo.dwType     = ITEM_TYPE_LABEL;
        sctItemInfo.sTagName   = "li";
        // In li, use initclass1
        sctItemInfo.sInitClass = sInitClass1;
        CreateListItemData(
            vInRowContent,
            sClass1,
            sDispStr,
            sctCatalog,
            sctItemInfo,
            &dwErrCode );
    }
    else if ( sItemTagName == "pre" )
    {
        /*- PPOCESS FOR PRE tag -*/
        sctItemInfo.dwType    = ITEM_TYPE_LABEL;
        // Create item <pre><div> </div></pre>
        sctItemInfo.sTagName  = "div";
        CreatePre( vInRowContent, 
            //sctCatalog,
            sctItemInfo, sDispStr );
    }
    else if ( sItemTagName =="time" )
    {
        /*--PROCESS FOR time -- */
        sctItemInfo.dwType    = ITEM_TYPE_LABEL;
        sctItemInfo.sTagName = "time";
        CreateTimeData(
            vInRowContent,
            sClass1,
            sctItemInfo,
            sctCatalog,
            &dwErrCode );
    }

    CreatePassWord( vInRowContent, sctCatalog );

    return DGT_RET_OK;
}

BOOL CScriptReader::CreatePre( vector<string>    vInRowContent,
                    //SCT_CATALOG_CSV              sctInCatalog,
                    SCT_ITEM_INFO                sctItemInfor,
                    string                       sInDisp)
{
    BOOL        bRet    = GUI_RET_OK;
    string      sDisp    = "";
    CItem*      lpItem  = NULL;
    if ( sInDisp != NASHI_MODE_JP )
    {
        sctItemInfor.sText =  sInDisp;
    }

    lpItem = new CItem();

    if ( sctItemInfor.sTagID != "" )
    {
        // Do nothing
    }
    else
    {
        sctItemInfor.sTagID = "div_"+vInRowContent[NO_COL];
    }

    lpItem->m_sctItem = sctItemInfor;

    if ( m_vItemStack.size() > 0 )
    {
        lpItem->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwLeft;
        lpItem->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwTop;
        m_vItemStack[ m_vItemStack.size() - 1]->m_vChildItem.push_back( lpItem );
    }
    else
    {
        m_lpCurrentArea->m_vItemList.push_back( lpItem );
    }

    return bRet;

}
/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  CreateTabAreaData
//
//　表　　題　：  Create Tab Area Data
//
//　概　　要　：  Create Tab Area Data
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL  CScriptReader::CreateTabAreaData(
            vector<string>   vInRowContent, 
           // vector<string>   vInHeaderInfo,
            LPDWORD          lpdwOutErrCode )
{
    // Local variable
    DWORD               dwErrCode           = DGT_VALUE_ZERO_DWORD;
    BOOL                bRet                    = DGT_RET_ERR;
    CLogger*            lpLog                   = NULL;
    CItem*              lpTabItemObj       = NULL;
    SCT_ITEM_INFO       sctItemInfo;
    string              sAreaJPName       = "";
    DWORD               dwH_grid_size      = DGT_VALUE_ZERO_DWORD ;
    DWORD               dwW_grid_size     = DGT_VALUE_ZERO_DWORD;
    vector<DWORD>       vdwWk_ichi;
    vector<DWORD>       vdwWk_yohaku;
    vector<string>      vTemp;
    SCT_TAG_CSV         sctTag;
    BOOL                bResult  = FALSE;

    vdwWk_ichi.resize( 2 );
    vdwWk_yohaku.resize( 2 );
    sctItemInfo.Memset();
    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    CLogger::GetInstance( lpLog );
    

    // Set position
    vTemp.clear();
    vTemp   = SplitString( vInRowContent[ICHI_COL] , "-" );
    vTemp.resize(2);
    if (( SuchiCheck( vTemp[ITEM_TOP] ) == 1 ) && ( atoi(vTemp[ITEM_TOP].c_str()) >= 1 ))
    {
        sctItemInfo.dwTop = ( (atoi(vTemp[ITEM_TOP].c_str()) - 1)*  m_lpCurrentArea->m_sctAreaInfo.dwCellHeight  )  + m_lpCurrentArea->m_sctAreaInfo.dwMarginTop;
    }
    else
    {
    }
    if (( SuchiCheck( vTemp[ITEM_LEFT]) == 1 ) && ( atoi(vTemp[ITEM_LEFT].c_str()) >= 1 ))
    {
        sctItemInfo.dwLeft = ( (atoi(vTemp[ITEM_LEFT].c_str()) - 1) * m_lpCurrentArea->m_sctAreaInfo.dwCellWidth  ) + m_lpCurrentArea->m_sctAreaInfo.dwMarginLeft; 
    }
    else
    {
    }

    // Get item with , height, font
    if ( SuchiCheck( vInRowContent[ WIDTH_COL] ) == 1 )
    {
        sctItemInfo.dwWidth = atoi( vInRowContent[ WIDTH_COL].c_str() ) * m_lpCurrentArea->m_sctAreaInfo.dwCellWidth;
    }
    else
    {
    }

    if ( SuchiCheck( vInRowContent[ HEIGHT_COL] ) == 1 )
    {
        sctItemInfo.dwHeight = atoi( vInRowContent[ HEIGHT_COL].c_str() ) * m_lpCurrentArea->m_sctAreaInfo.dwCellHeight;
    }
    else
    {
    }

    sctItemInfo.dwType     = ITEM_TYPE_LABEL;
    sctItemInfo.sTagName   = "ul";
    sctItemInfo.bParent    = FALSE;
    sctItemInfo.sAreaType  = m_lpCurrentArea->m_sctAreaInfo.sAreaType;
    sctItemInfo.bVisible   = TRUE;
    sctItemInfo.bEnable    = TRUE;

     // Create unorder list
     if ( vInRowContent[DISPSTR_COL] == KOMOKU_BOOKING_START )
     {
         lpTabItemObj = new CItem();
         sctItemInfo.sTagID = "ul_" + vInRowContent[NO_COL];
         lpTabItemObj->m_sctItem = sctItemInfo;
         m_vItemStack.push_back( lpTabItemObj );
     }
     else
     {
        lpTabItemObj = m_vItemStack[m_vItemStack.size() - 1];
        m_vItemStack.pop_back();
         if ( m_vItemStack.size() > 0 )
         {
            /* if ( lpTabItemObj->m_sctItem.bVisibilityHidden == TRUE )
             {
                lpTabItemObj->m_sctItem.bVisible = FALSE;
             }
             else
             {
                lpTabItemObj->m_sctItem.bVisible = m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.bVisible;
             }*/
             lpTabItemObj->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwLeft;
             lpTabItemObj->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwTop;
             m_vItemStack[m_vItemStack.size() - 1]->m_vChildItem.push_back( lpTabItemObj );
         }
         else
         {
             m_lpCurrentArea->m_vItemList.push_back( lpTabItemObj );
         }
     }

     // Set OutJS info
     if ( vInRowContent[TAGID_COL] != NASHI_MODE )
     {
         bRet  = SearchTagStr( vInRowContent[TAGID_COL],
                                            sctTag,
                                            bResult,
                                            &dwErrCode );
         if ( bResult == TRUE )
         {
             // Set OutJS infor
             output_JS_tbl(
                 vInRowContent[TAGID_COL],
                 vInRowContent[ALTERNATE_TAGID_COL],
                 vInRowContent[CURUMU_COL],
                 vInRowContent[NO_COL],
                 //vInRowContent[DISPSTR_COL],
                 "ul",//lpTabItemObj->m_sctItem.sTagName,
                 vInRowContent[ INPUTFMT_COL],
                 lpTabItemObj->m_sctItem,
                 &dwErrCode );
         }
         else
         {
             string sLogStr = "【エラー】"+vInRowContent[NO_COL]+"-タグ名検索エラー:"+ vInRowContent[TAGID_COL];
             bRet = lpLog->Log( sLogStr, &dwErrCode );
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
     }
     else
     {
         // DO nothing
     }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  CreateTimeData
//
//　表　　題　：  Create Time Data
//
//　概　　要　：  Create Time Data
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::CreateTimeData(
                vector<string>         vInRowContent,
                string                 sInClass1,
                SCT_ITEM_INFO          sctInItemInfo,
                SCT_CATALOG_CSV        sctInCatalog,
                LPDWORD                lpdwOutErrCode   )
{
    // Local variable
    DWORD       dwErrCode          = DGT_VALUE_ZERO_DWORD;
    BOOL        bRet               = DGT_RET_ERR;
    CItem*      lpItemObj          = NULL;

    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }
    // Create item
    lpItemObj                       = new CItem();
    if ( sctInItemInfo.sTagID == "" )
    {
        sctInItemInfo.sTagID        = "time_"+ vInRowContent[NO_COL];
    }
    sctInItemInfo.sNullStrInitApp   = "false";
    sctInItemInfo.sClass            = sInClass1;
    sctInItemInfo.sGaikan           = sctInCatalog.sGaikanGrpName;
    lpItemObj->m_sctItem            = sctInItemInfo;

    if ( m_vItemStack.size() > 0 )
    {
      /*  if ( lpItemObj->m_sctItem.bVisibilityHidden == TRUE )
        {
            lpItemObj->m_sctItem.bVisible = FALSE;
        }
        else
        {
            lpItemObj->m_sctItem.bVisible = m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.bVisible;
        }*/
        lpItemObj->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwLeft;
        lpItemObj->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwTop;
        m_vItemStack[ m_vItemStack.size() - 1]->m_vChildItem.push_back( lpItemObj );
    }
    else
    {
        m_lpCurrentArea->m_vItemList.push_back( lpItemObj );
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  CreateListItemData
//
//　表　　題　：  Create list data
//
//　概　　要　：  Create list data
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL  CScriptReader::CreateListItemData(
                        vector<string>             vInRowContent,
                        string                     sInClass1,
                        string                     sInText,
                        SCT_CATALOG_CSV            sctInCataLog,
                        SCT_ITEM_INFO              sctInItemInfo,
                        LPDWORD                    lpdwOutErrCode )
{
    // Local variable
    DWORD       dwErrCode          = DGT_VALUE_ZERO_DWORD;
    BOOL           bRet            = DGT_RET_ERR;
    CItem*        lpItemObj        = NULL;

    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    if (sInText != NASHI_MODE_JP )
    {
        sInText = Conv_StrNewLine( sInText );
    }
    else 
    {
        // Do nothing
    }

 /*   if ( sInText.size() > 0 )
    {
        if ( sInText[sInText.size() -1 ] == '\n' ) 
        {
            sInText = sInText.substr( 0, sInText.size() -1 );
        }
    }
    if ( sInText.size() > 1 )
    {
         if ( sInText.substr( sInText.size()-2, 2 ) == "\\n" )
        {
            sInText = sInText.substr( 0, sInText.size() -2 );
        }
    }*/
    // Create item
    lpItemObj                   = new CItem();
    sctInItemInfo.sClass        = sInClass1;
    if ( sctInItemInfo.sTagID == "" )
    {
        sctInItemInfo.sTagID = "li_" + vInRowContent[NO_COL];
    }
    sctInItemInfo.sGaikan     = sctInCataLog.sGaikanGrpName;
    sctInItemInfo.sText       = sInText;
    lpItemObj->m_sctItem      = sctInItemInfo;
    if ( m_vItemStack.size() > 0 )
    {
      /*  if ( lpItemObj->m_sctItem.bVisibilityHidden == TRUE )
        {
            lpItemObj->m_sctItem.bVisible = FALSE;
        }
        else
        {
            lpItemObj->m_sctItem.bVisible = m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.bVisible;
        }*/
        lpItemObj->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwLeft;
        lpItemObj->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwTop;
        // Push back to parrent
        m_vItemStack[ m_vItemStack.size() -1 ]->m_vChildItem.push_back( lpItemObj );
    }
    else
    {
        // Push to item list
        m_lpCurrentArea->m_vItemList.push_back( lpItemObj );
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  CreateAData
//
//　表　　題　：  Create A data
//
//　概　　要　：  Create A data
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL  CScriptReader::CreateAData(
                vector<string>              vInRowContent,
                string                      sInClass1,
                string                      sInClass2,
                string                      sInText,
                SCT_CATALOG_CSV             sctInCataLog,
                SCT_ITEM_INFO               sctInItemInfo,
                LPDWORD                     lpdwOutErrCode   )
{
    // Local variable
    DWORD       dwErrCode       = DGT_VALUE_ZERO_DWORD;
    BOOL        bRet            = DGT_RET_ERR;
    CItem*      lpItemObj       = NULL;
    string      sMouceDownFunc  = "";

    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }
   /* if ( sInText.size() > 0 )
    {
        if ( sInText[sInText.size() -1 ] == '\n' )
        {
            sInText = sInText.substr( 0, sInText.size() -2 );
        }
    }*/
    /*===== <div ><a ></a></div>   =======*/
    // Create 
    lpItemObj                        = new CItem();
    sctInItemInfo.sTagName           = "a";
    if ( sctInItemInfo.sTagID == "")
    {
        lpItemObj->m_sctItem.sTagID  = "a_" + vInRowContent[NO_COL];
    }
    if ( sInClass1 != "" )
    {
        sctInItemInfo.sClass = sInClass1;
        if ( sInClass2 != "" )
        {
            sctInItemInfo.sClass += " " + sInClass2;
        }
    }
    else
    {
        sctInItemInfo.sClass = sInClass2;
    }
    sctInItemInfo.sGaikan = sctInCataLog.sGaikanGrpName;
    sctInItemInfo.sText      = sInText;
    lpItemObj->m_sctItem     = sctInItemInfo;

    if ( CheckNashiMode(vInRowContent[SENDSTR1_COL]) == true )
    {
        // Add item
        if ( m_vItemStack.size() > 0 )
        {
           /* if ( lpItemObj->m_sctItem.bVisibilityHidden == TRUE )
            {
                lpItemObj->m_sctItem.bVisible = FALSE;
            }
            else
            {
                lpItemObj->m_sctItem.bVisible = m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.bVisible;
            }*/
            lpItemObj->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwLeft;
            lpItemObj->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwTop;
            m_vItemStack[ m_vItemStack.size() - 1]->m_vChildItem.push_back( lpItemObj );
        }
        else
        {
            m_lpCurrentArea->m_vItemList.push_back( lpItemObj );
        }
    }
    else
    {
        // Get onmousedown function
        if ( Set_ATag_OnMounDown(vInRowContent, sctInCataLog, lpItemObj->m_sctItem, &dwErrCode ) == TRUE )
        {
            // Add onmouse down function to Item
          //  lpItemObj->m_sctItem.sEvenFunctionName = sMouceDownFunc;
            if ( m_vItemStack.size() > 0 )
            {
             /*   if ( lpItemObj->m_sctItem.bVisibilityHidden == TRUE )
                {
                    lpItemObj->m_sctItem.bVisible = FALSE;
                }
                else
                {
                    lpItemObj->m_sctItem.bVisible = m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.bVisible;
                }*/
                lpItemObj->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwLeft;
                lpItemObj->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwTop;
                m_vItemStack[ m_vItemStack.size() - 1]->m_vChildItem.push_back( lpItemObj );
            }
            else
            {
                m_lpCurrentArea->m_vItemList.push_back( lpItemObj );
            }
        }
        else
        {
            // Do not create data
            delete lpItemObj;
            // Nothing is created
            return DGT_RET_OK;
        }
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  Set_ATag_OnMounDown
//
//　表　　題　：  Create A tag moundown
//
//　概　　要　：  Create A tag moundown
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::Set_ATag_OnMounDown(
                    vector<string> vInRowContent, 
                    //string &sOutFunc, 
                    SCT_CATALOG_CSV sctInCatalog, 
                    SCT_ITEM_INFO   &sctOutItemInfo,
                    LPDWORD lpdwOutErrCode )
{
    // Local variable
    DWORD         dwErrCode         = DGT_VALUE_ZERO_DWORD;
    BOOL          bRet              = DGT_RET_ERR;
    BOOL          bSts              = TRUE;
    string        sContenaTagId     = "";
    LONG          iIdx              = -1;
    SCT_TAG_CSV   sctTag;
    BOOL          bResult;
    CLogger*      lpLog             = NULL;
    string        sLogStr           = "";
    CHAR          str[1024];

    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    CLogger::GetInstance( lpLog );
    

    if ( sctInCatalog.sAttribute == BTN_PAGE_KIRIKAE )
    {
        if (CheckNashiMode(vInRowContent[SENDSTR1_COL]) == false)
        {
            iIdx = SearchTagStr(
                        vInRowContent[SENDSTR1_COL],
                        sctTag,
                        bResult,
                        &dwErrCode);
            if (iIdx == NOT_FOUND)
            {
                sLogStr = "【エラー】"+vInRowContent[NO_COL]+"-コンテナタグ名検索エラー:"+vInRowContent[SENDSTR1_COL] ;
                // Write log
                bRet = lpLog->Log( sLogStr, &dwErrCode );
                if ( bRet == DGT_RET_OK )
                {
                    // DO nothing
                }
                else
                {
                    *lpdwOutErrCode = dwErrCode;
                    return DGT_RET_ERR;
                }
                *lpdwOutErrCode = DGT_ERR_CSR_SAMD_TAGID_NOT_FOUND;
                return DGT_RET_ERR;
            }
            else
            {
                // Do nothing
            }
            sContenaTagId = sctTag.sTagID;
        }
        else
        {
            // Do nothing
        }
        // 数値チェック
        if (IsStringNumber(vInRowContent[ALTERNATE_TAGID_COL]) == false)
        {
            // Write log
            sLogStr = "【エラー】"+vInRowContent[NO_COL]+"-コンテナGrp開始番号　数値チェックエラー:"+vInRowContent[SENDSTR1_COL] ;
            // Write log
            bRet = lpLog->Log( sLogStr, &dwErrCode );
            if ( bRet == DGT_RET_OK )
            {
                // DO nothing
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
                return DGT_RET_ERR;
            }
            *lpdwOutErrCode = DGT_ERR_CSR_SAMD_ALTTAGID_NOT_FOUND;
            return DGT_RET_ERR;
        }
        else 
        {
            // Do nothing
        }
        if (IsStringNumber(vInRowContent[SENDSTR2_COL]) == false)
        {
            // Write log
            sLogStr = "【エラー】"+vInRowContent[NO_COL]+"-コンテナGrp開始終了　数値チェックエラー:"+vInRowContent[SENDSTR2_COL] ;
            // Write log
            bRet = lpLog->Log( sLogStr, &dwErrCode );
            if ( bRet == DGT_RET_OK )
            {
                // DO nothing
            }
            else
            {
                *lpdwOutErrCode = dwErrCode;
                return DGT_RET_ERR;
            }
            return DGT_RET_ERR;
        }
        else 
        {
            // Do nothing
        }

     //   sprintf( str , "ContenaKirikaeFunc('%s',%s,%s,this)", sContenaTagId , vInRowContent[ALTERNATE_TAGID_COL] , vInRowContent[SENDSTR2_COL]);
     //   sOutFunc = string(str );
        sctOutItemInfo.sEvenFunctionName   = "ContenaKirikaeFunc";
        sctOutItemInfo.sParaContainerTagID = sContenaTagId;
        sctOutItemInfo.sParaStartNo        = vInRowContent[ALTERNATE_TAGID_COL];
        sctOutItemInfo.sParaEndNo          = vInRowContent[SENDSTR2_COL];
    }
    else 
    {
        sprintf( str , "ekibtn_page_kirikae('%s')", vInRowContent[SENDSTR1_COL] );
        sctOutItemInfo.sEvenFunctionName = str;
    }

    return bSts;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  CreateDivData
//
//　表　　題　：  Create Div Data
//
//　概　　要　：  Create Div Data
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL  CScriptReader::CreateDivData(
                    vector<string>              vInRowContent,
                    string                           sInClass1,
                    string                           sInClass2,
                    string                           sInText,
                    SCT_CATALOG_CSV      sctInCataLog,
                    SCT_ITEM_INFO           sctInItemInfo,
                    LPDWORD                     lpdwOutErrCode)
{
    // Local variable
    string      wk_line        = "";
    string      sIchi          = "";
    string      sDispStrCol    = "";
    CItem*      lpItem         = NULL;
    CItem*      lpCurrentItem  = NULL;
    string      sTemp          = "";
    sDispStrCol  = vInRowContent[DISPSTR_COL];

    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }
  /*  if ( sInText.size() > 0 )
    {
        if ( sInText[sInText.size() -1 ] == '\n' )
        {
            sInText = sInText.substr( 0, sInText.size() -1 );
        }
    }
    if ( sInText.size() > 1 )
    {
        if ( sInText.substr(sInText.size() -2,2 ) == "\\n" )
        {
            sInText = sInText.substr( 0, sInText.size() -2 );
        }
    }*/
    // Display string column start by "【"
     if (  sDispStrCol.substr(0,2 ) == "【" )
    {
        /*=============== NASHI MODE    =================*/
        if (  sDispStrCol == NASHI_MODE_JP )
        {
            lpItem = new CItem();
            if ( sctInItemInfo.sTagID == "" )
            {
                sctInItemInfo.sTagID = "div_"+ vInRowContent[NO_COL];
            }
            sctInItemInfo.sClass = sInClass1;
            if ( sctInItemInfo.sClass != "" )
            {
                if ( sInClass2 != "" )
                {
                    sctInItemInfo.sClass += " " + sInClass2;
                }
            }
            else
            {
                sctInItemInfo.sClass = sInClass2;
            }

            lpItem->m_sctItem = sctInItemInfo;
            if ( m_vItemStack.size() > 0 )
            {
             /*   if ( lpItem->m_sctItem.bVisibilityHidden == TRUE )
                {
                    lpItem->m_sctItem.bVisible = FALSE;
                }
                else
                {
                    lpItem->m_sctItem.bVisible = m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.bVisible;
                }*/
                lpItem->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwLeft;
                lpItem->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwTop;
                m_vItemStack[m_vItemStack.size() - 1]->m_vChildItem.push_back( lpItem );
            }
            else
            {
                m_lpCurrentArea->m_vItemList.push_back( lpItem );
            }
        }
        /*==============  Start new tag 【開始】<div> ==============*/
        else if (  sDispStrCol == KOMOKU_BOOKING_START )
        {
            lpItem                        = new CItem();
            sctInItemInfo.sClass          = sInClass1;
            sctInItemInfo.sNullStrInitApp = "false";
            sctInItemInfo.sInitClass      = "";
            sctInItemInfo.sInitText       = "";
            if ( sctInItemInfo.sTagID == "" )
            {
                sctInItemInfo.sTagID = "div_" + vInRowContent[NO_COL];
            }
            if ( sctInCataLog.sAttribute == CONTENA )
            {
                // Follow html
                sctInItemInfo.sFmt            = "";
                sctInItemInfo.sLimit          = "";
                sctInItemInfo.sMinLen         = "";
                sctInItemInfo.sMaxLen         = "";
                sctInItemInfo.sLimit          = "";
                sctInItemInfo.sFmt            = "";
            }

            lpItem->m_sctItem = sctInItemInfo;
            if ( strcmp( lpItem->m_sctItem.sTagID.c_str(), "" ) == 0 )
            {
                lpItem->m_sctItem.sTagID = "div_" + vInRowContent[NO_COL];
            }
            m_vItemStack.push_back( lpItem );
        }
        /*==============  Start new tag 【終了】</div> ==============*/
        else if ( sDispStrCol == KOMOKU_BOOKING_END )
        {
            if ( m_vItemStack.size() > 0 )
            {
                lpCurrentItem = m_vItemStack[m_vItemStack.size() - 1];
                m_vItemStack.pop_back();
                if ( m_vItemStack.size() > 0 )
                {
                    /*if ( lpCurrentItem->m_sctItem.bVisibilityHidden == TRUE )
                    {
                        lpCurrentItem->m_sctItem.bVisible = FALSE;
                    }
                    else
                    {
                        lpCurrentItem->m_sctItem.bVisible = m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.bVisible;
                    }*/
                    lpCurrentItem->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwLeft;
                    lpCurrentItem->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwTop;
                    m_vItemStack[m_vItemStack.size() - 1]->m_vChildItem.push_back( lpCurrentItem );
                }
                else
                {
                    m_lpCurrentArea->m_vItemList.push_back( lpCurrentItem );
                }
            }
        }
        /*=============== Default case =====================*/
        else
        {
            //if (  sDispStrCol.substr( 0,5 )   == "【img" )
            if ( sDispStrCol.find( "【img") != std::string::npos )
            {
                // Create image data
                lpItem                                  = new CItem();
                sctInItemInfo.sNullStrInitApp     = "false";
                if ( sInClass1 != "" )
                {
                    sctInItemInfo.sClass             =   sInClass1;
                    if ( sInClass2 != "" )
                    {
                        sctInItemInfo.sClass        += " "+sInClass2;
                    }
                }
                else
                {
                    sctInItemInfo.sClass     = sInClass2;
                }
                
                if ( sctInCataLog.sAttribute == IMG_STRETCH )
                {
                    // <div><img /></div>
                    if ( sctInItemInfo.sTagID == "" )
                    {
                    sctInItemInfo.sTagID     = "img_" + vInRowContent[NO_COL];
                    }
                    sctInItemInfo.sImgSrc   = "resource\\\\image\\\\"+ m_lpCurrentArea->m_sctAreaInfo.sAreaEngName +"\\\\" + sDispStrCol.substr(6, sDispStrCol.size() - 8);
                    lpItem->m_sctItem       = sctInItemInfo;
                    lpItem->m_sctItem.bParent = FALSE;
                    if ( m_vItemStack.size() > 0 )
                    {
                       /* if ( lpItem->m_sctItem.bVisibilityHidden == TRUE )
                        {
                            lpItem->m_sctItem.bVisible = FALSE;
                        }
                        else
                        {
                            lpItem->m_sctItem.bVisible = m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.bVisible;
                        }*/
                        if (( lpItem->m_sctItem.dwWidth != 0 ) && ( lpItem->m_sctItem.dwHeight != 0 ))
                        {
                            lpItem->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwLeft;
                            lpItem->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwTop;
                        }
                        // When it has parent
                        m_vItemStack[m_vItemStack.size() - 1 ]->m_vChildItem.push_back( lpItem );
                    }
                    else
                    {
                        // When it has no parent
                        m_lpCurrentArea->m_vItemList.push_back( lpItem );
                    }
                }
                else
                { 
                    // <div><p><img /></p></div>
                    if ( sInClass1 != "" )
                    {
                        sctInItemInfo.sClass             =   sInClass1;
                        if ( sInClass2 != "" )
                        {
                            sctInItemInfo.sClass        += " "+sInClass2;
                        }
                    }
                    else
                    {
                        sctInItemInfo.sClass     = sInClass2;
                    }
                    if ( sctInItemInfo.sTagID == "" )
                    {
                        sctInItemInfo.sTagID             = "img_" + vInRowContent[NO_COL];
                    }
                    sctInItemInfo.sImgSrc            = "resource\\\\image\\\\"+ m_lpCurrentArea->m_sctAreaInfo.sAreaEngName +"\\\\" +sDispStrCol.substr(6, sDispStrCol.size() - 8);
                    lpItem->m_sctItem                = sctInItemInfo;
                    lpItem->m_sctItem.bParent = FALSE;
                    if ( m_vItemStack.size() > 0 )
                    {
                        /*if ( lpItem->m_sctItem.bVisibilityHidden == TRUE )
                        {
                            lpItem->m_sctItem.bVisible = FALSE;
                        }
                        else
                        {
                            lpItem->m_sctItem.bVisible = m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.bVisible;
                        }*/
                        if (( lpItem->m_sctItem.dwWidth != 0 ) && ( lpItem->m_sctItem.dwHeight != 0 ))
                        {
                            lpItem->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwLeft;
                            lpItem->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwTop;
                        }
                        // When it has parent
                        m_vItemStack[m_vItemStack.size() - 1 ]->m_vChildItem.push_back( lpItem );
                    }
                    else
                    {
                        // When it has no parent
                        m_lpCurrentArea->m_vItemList.push_back( lpItem );
                    }
                }
            }
            else
            {
                // Create normal div data
                lpItem                                  = new CItem();
                sctInItemInfo.sNullStrInitApp  = "false";
                if ( sctInItemInfo.sTagID != "" )
                {
                    // Do nothing
                }
                else
                {
                    sctInItemInfo.sTagID    = "div_" + vInRowContent[NO_COL];
                }
                lpItem->m_sctItem           = sctInItemInfo;
                sctInItemInfo.sClass        =   sInClass1;
                if ( m_vItemStack.size() > 0 )
                {
                   /* if ( lpItem->m_sctItem.bVisibilityHidden == TRUE )
                    {
                        lpItem->m_sctItem.bVisible = FALSE;
                    }
                    else
                    {
                        lpItem->m_sctItem.bVisible = m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.bVisible;
                    }*/
                    lpItem->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwLeft;
                    lpItem->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwTop;
                    // When it has parent
                    m_vItemStack[m_vItemStack.size() - 1 ]->m_vChildItem.push_back( lpItem );
                }
                else
                {
                    // When it has no parent
                    m_lpCurrentArea->m_vItemList.push_back( lpItem );
                }
            }
        }
    }
    else
    {
        // Check SEINENGAPPI < div> < div class = "nen" ></div> < span> 年　　月　　日</span></div>
        if ( sctInCataLog.sAttribute == SEINENGAPPI )
        {
            CItem*   lpParent       = new CItem();
            if ( sctInItemInfo.sTagID != "" )
            {
                // Do nothing
            }
            else
            {
                sctInItemInfo.sTagID  = "div_" + vInRowContent[NO_COL];
            }
            sctInItemInfo.sClass   = sInClass1;
            lpParent->m_sctItem  = sctInItemInfo;
            // Create < div class = "nen" ></div> 
            CItem*  lpChildDiv      = new CItem();
            lpChildDiv->m_sctItem.sTagName = "div";
            lpChildDiv->m_sctItem.sClass   = "nen";
            lpChildDiv->m_sctItem.sText    = "　　　　\n　　　　";
            lpChildDiv->m_sctItem.bVisible = lpParent->m_sctItem.bVisible;
            lpParent->m_vChildItem.push_back( lpChildDiv );

            CItem*  lpChildSpan = new CItem();
            lpChildSpan->m_sctItem.sClass   = sInClass2;
            lpChildSpan->m_sctItem.sText    = "年　　月　　日";
            lpChildSpan->m_sctItem.sTagName = "span";
            lpParent->m_vChildItem.push_back( lpChildSpan );

            if ( m_vItemStack.size() > 0 )
            {
               /* if ( lpParent->m_sctItem.bVisibilityHidden == TRUE )
                {
                    lpParent->m_sctItem.bVisible = FALSE;
                }
                else
                {
                    lpParent->m_sctItem.bVisible = m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.bVisible;
                }*/
                lpParent->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwLeft;
                lpParent->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwTop;
                // When it has parent
                m_vItemStack[m_vItemStack.size() - 1 ]->m_vChildItem.push_back( lpParent );
            }
            else
            {
                // When it has no parent
                m_lpCurrentArea->m_vItemList.push_back( lpParent );
            }
        }
        else
        {
            lpItem = new CItem();
            sctInItemInfo.sClass     = sInClass1;
            if ( sctInItemInfo.sTagID != "" )
            {
                // Do nothing
            }
            else
            {
                sctInItemInfo.sTagID    = "div_" + vInRowContent[NO_COL];
            }
            sctInItemInfo.sText      = sInText;
            lpItem->m_sctItem      = sctInItemInfo;
            if ( m_vItemStack.size() > 0 )
            {
               /* if ( lpItem->m_sctItem.bVisibilityHidden == TRUE )
                {
                    lpItem->m_sctItem.bVisible = FALSE;
                }
                else
                {
                    lpItem->m_sctItem.bVisible = m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.bVisible;
                }*/
                lpItem->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwLeft;
                lpItem->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwTop;
                // When it has parent
                m_vItemStack[m_vItemStack.size() - 1 ]->m_vChildItem.push_back( lpItem );
            }
            else
            {
                // When it has no parent
                m_lpCurrentArea->m_vItemList.push_back( lpItem );
            }
        }
    }


    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  CreatePageArea
//
//　表　　題　：  Create Div page data
//
//　概　　要　：  Create Div page data
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL    CScriptReader::CreatePageArea(
                                Excel::_WorksheetPtr       lpInWorkSheet,
                                vector<string>             vInRowContent,
                                //string                     sInClass1,
                                //SCT_CATALOG_CSV            sctInCataLog,
                                SCT_ITEM_INFO              sctInItemInfo,
                                LPDWORD                    lpdwOutErrCode )
{
    // Local variable
    DWORD               dwErrCode        = DGT_VALUE_ZERO_DWORD;             // Error Code
    BOOL                bRet             = DGT_RET_ERR;                      // Return value
    BOOL                bResult          = FALSE;
    string              sLine            = "";
    string              sStr             = "";
    string              sTagID_JP        = "";
    string              sKomoku          = "";
    string              sTabTagId        = "";
    string              sDispStrCol      = "";
    string              sItemCol         = "";
    string              sTabName         = "";
    LONG                lRow             = NOT_FOUND;
    LONG                lTabListNo       = -1;
    CItem*              lpItem           = NULL;
    CItem*              lpCurrentItem    = NULL;
    DWORD               dwPos            = DGT_VALUE_ZERO_DWORD;
    SCT_TAG_CSV         sctTagCSV;

    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    if ( lpInWorkSheet == NULL )
    {
        *lpdwOutErrCode = DGT_ERR_CSR_CPA_PARA;
        return DGT_RET_ERR;
    }

    sDispStrCol  = vInRowContent[DISPSTR_COL];
    sItemCol      = vInRowContent[KOMOKU_COL];
    /*========= Open new tag. 【開始】======= */
    if ( sDispStrCol == KOMOKU_BOOKING_START )
    {
        string sPageArea = "【ページエリア】";
        // Get tab content
        if ((dwPos = sItemCol.find( sPageArea)) != std::string::npos )
        {
            // Get sub string ( Tab1 ) of [PageArea][Tab1]
            dwPos = dwPos + sPageArea.size() + 2;
            sTabName = sItemCol.substr( dwPos, sItemCol.size() - dwPos -2 ); // Remove [ and ] in [Tab*]
        }
        else
        {
            // Do nothing
        }

        // Find sTabName in sheet data
        m_cExcelReader.SearchColValue_Row( lpInWorkSheet, DATA_START_ROW, DATA_START_COL+KOMOKU_COL,sTabName,lRow, &dwErrCode );
        if ( lRow != NOT_FOUND )
        {
            // Get tag id
            m_cExcelReader.GetCellContent(lRow, DATA_START_COL+ TAGID_COL, lpInWorkSheet,  sTagID_JP,&dwErrCode );
            // Search tag ID english name
            SearchTagStr( sTagID_JP, sctTagCSV, bResult, &dwErrCode );
            if ( bResult == TRUE )
            {
                // Get full tag ID name 
                sctInItemInfo.sTagID  = sctTagCSV.sTagID + TAGID_PAGE_AREA;
            }
            else
            {
                // Do nothing
            }
        }

        // Create new object <div ..... >
        lpItem =new CItem();
        lpItem->m_sctItem = sctInItemInfo;
        m_vItemStack.push_back( lpItem );
    }
    /*==========Close tag【終了】 ==============*/
    else if ( strcmp( sDispStrCol.c_str(), KOMOKU_BOOKING_END) == 0 )
    {
        if ( m_vItemStack.size() > 0 )
        {
            lpCurrentItem = m_vItemStack[m_vItemStack.size() - 1];
            m_vItemStack.pop_back();
            if ( m_vItemStack.size() > 0 )
            {
                if ( lpCurrentItem->m_sctItem.bVisible == TRUE )
                {
                    lpCurrentItem->m_sctItem.bVisible = FALSE;
                }
                else
                {
                    lpCurrentItem->m_sctItem.bVisible = m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.bVisible;
                }
                    lpCurrentItem->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwLeft;
                    lpCurrentItem->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwTop;
                    m_vItemStack[m_vItemStack.size() - 1]->m_vChildItem.push_back( lpCurrentItem );
            }
            else
            {
                m_lpCurrentArea->m_vItemList.push_back( lpCurrentItem );
            }
        }
    }
    else
    {
        // Do nothing
    }

    return DGT_RET_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  CreateButtonData
//
//　表　　題　：  Create button data
//
//　概　　要　：  Create button data
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::CreateButtonData(
                            vector<string>          vInRowContent,
                           // string                       sInClass2,
                            SCT_CATALOG_CSV  sctInCatalog,
                            SCT_ITEM_INFO        sctInItemInfo,
                            LPDWORD                  lpdwOutErrCode)
{
    // Local variable
    CItem*                    lpObj         = NULL;
    CItem*                    lpCurrentItem = NULL;
    string                    sPageAtr      = "";
    string                    sGroup        = "";
    string                    sText         = "";
    BOOL                      bImgFlg       = FALSE;
    BOOL                      bStrFlg       = FALSE;
    DWORD                     dwErrCode     = DGT_VALUE_ZERO_DWORD;
    vector<string>            sBooking;
    string                    sTempTxt      = "";
    string                    sStrColor     = "";
    DWORD                     dwCnt         = 0;
    string                    sSpanStr      = "";
    vector<string>            sArrayData ;
    SCT_SPAN                  sctSpan;

    sText                        = vInRowContent[DISPSTR_COL];
    lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    try
    {
        if (vInRowContent[DISPSTR_COL] != NASHI_MODE_JP )
        {
            sText = Conv_StrNewLine(vInRowContent[DISPSTR_COL]);
        }
        else 
        {
            // Do nothing
        }
       /* if ( sText.size() > 0 )
        {
            if ( sText[sText.size() -1 ] == '\n' )
            {
                sText = sText.substr( 0, sText.size() -1 );
            }
        }
        if ( sText.size() > 1 )
        {
            if ( sText.substr(sText.size() -2,2 ) == "\\n" )
            {
                sText = sText.substr( 0, sText.size() -2 );
            }
        }*/
        if ( regex_match( sctInItemInfo.sValue, regex("^(E|B)\\d{8}") ))
         {
             sGroup = GRP_EKIBTN;
        }
        else
        {
            if ( regex_match(sctInItemInfo.sValue, regex("^R\\d{8}")) )
            {
                sGroup = GRP_KEIYUBTN;
            }
            else 
            { 
                // Do nothing
            }
        }
        string sCheck = "^(@@).*";
        if ( regex_match( sctInCatalog.sGaikanGrpName, regex(sCheck)))
        {
            sPageAtr   = m_sContenaTagId ;
        }

        lpObj = new CItem();

        //if ( (regex_match( vInRowContent[DISPSTR_COL], regex( "【.*】" ))) &&
        // Check style is [img]String or String[line]String 
        if (  (vInRowContent[DISPSTR_COL].find( "【") !=  std::string::npos ) &&
        ( vInRowContent[DISPSTR_COL] != NASHI_MODE ) )
        {
           /*=============CASE: KOMOKU_BOOKING_END ================*/
            if ( strcmp( vInRowContent[DISPSTR_COL].c_str(), KOMOKU_BOOKING_END ) == 0 )
            {
                if ( m_vItemStack.size() > 0 )
                {
                    lpCurrentItem = m_vItemStack[m_vItemStack.size() - 1];
                    m_vItemStack.pop_back();
                    if ( m_vItemStack.size() > 0 )
                    {
                      /*  if ( lpCurrentItem->m_sctItem.bVisibilityHidden == TRUE )
                        {
                            lpCurrentItem->m_sctItem.bVisible = FALSE;
                        }
                        else
                        {
                            lpCurrentItem->m_sctItem.bVisible = m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.bVisible;
                        }*/
                        lpCurrentItem->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwLeft;
                        lpCurrentItem->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwTop;
                        m_vItemStack[m_vItemStack.size() - 1]->m_vChildItem.push_back( lpCurrentItem );
                    }
                    else
                    {
                        m_lpCurrentArea->m_vItemList.push_back( lpCurrentItem );
                    }
                }
                return DGT_RET_OK;
            }
            /*============CASE: KOMOKU_BOOKING_START ===============*/
            else if ( strcmp( vInRowContent[DISPSTR_COL].c_str(), KOMOKU_BOOKING_START ) == 0 )
            {
                sctInItemInfo.sPageAtr = sPageAtr;
                if ( sctInItemInfo.sTagID == "" )
                {
                    sctInItemInfo.sTagID = "btn_" + vInRowContent[NO_COL];
                }
                sctInItemInfo.sGaikan    = sctInCatalog.sGaikanGrpName;
                lpObj->m_sctItem = sctInItemInfo;
                // Push new item to stack
                m_vItemStack.push_back( lpObj );
            }
            /*===========OTHER CASE =============================*/
            else
            {
                if ( sctInItemInfo.sTagGroup == "" )
                {
                    sctInItemInfo.sTagGroup = sGroup;
                }
                sctInItemInfo.sPageAtr = sPageAtr;
                if ( sctInItemInfo.sTagID == "" )
                {
                    sctInItemInfo.sTagID = "btn_" + vInRowContent[NO_COL];
                }

                /*========= ADD BUTTON IMAGE AND BUTOTN TEXT INFORMATION=================*/
                // Check item for mat is [str_[^]*]
                //if ( std::regex_match( sText, regex("【str_[^】]*】" )))

                //if ( sText.find( sRegexImg ) != std::string::npos )
                if ( regex_search( sText, regex( "【str_[^】]*】" )))
                {
                    bStrFlg = TRUE;
                }
                else
                {
                    // Do nothing
                }

                //if ( std::regex_match( sText, reKomokuImg ))
                //if ( sText.find( "【img】") != std::string::npos )
                if ( regex_search( sText, regex( "【img】" )))
                {
                    bImgFlg = TRUE;
                }
                else
                {
                    // Do nothing
                }
                sArrayData  =  SplitString( sText, "【" );

                for ( dwCnt = 0; dwCnt < sArrayData.size(); dwCnt ++ )
                {
                    sctSpan.Memset();
                    sSpanStr  = "";
                    sStrColor = "";
                    if (sArrayData[dwCnt] == "")
                    {
                        continue;
                    }
                    else
                    { 
                        // Do nothing
                    }

                    sBooking = SplitString( sArrayData[dwCnt], "】");
                    if (1 < sBooking.size())
                    {
                        sSpanStr = sBooking[1];
                    }
                    else
                    {
                        sSpanStr = sBooking[0];
                    }

                    if ( regex_match( sBooking[0], regex("str_.*")))
                    {
                        sStrColor = sBooking[0];
                    }
                    else 
                    {
                        // Do nothing
                    }

                    // Switch sBooking
                    sTempTxt = "";
                    /*-- CASE: KOMOKU_BOOKING_IMG --*/
                    if(  sBooking[0] == KOMOKU_BOOKING_IMG )
                    {
                        //sctInItemInfo.sBtn_Span_ImgClass = sInClass2+ "_span_" + sBooking[0];
                        sctInItemInfo.sBtn_Span_ImgClass =  sBooking[0];
                        //if (( sctInItemInfo.sBtn_Span_Text != "" ) || ( sctInItemInfo.sBtn_Span_Text_Class != "" ))
                        if ( sctInItemInfo.vSpanItem.size() > 0 )
                        {
                            sctInItemInfo.bImageFirst = FALSE;
                        }
                        else
                        {
                            sctInItemInfo.bImageFirst = TRUE;
                        }

                        if (sSpanStr != "")
                        {
                            //sctInItemInfo.sBtn_Span_Text = sSpanStr;
                            sctSpan.sSpanText = sSpanStr;
                            if ( sStrColor != "" )
                            {
                                //sctInItemInfo.sBtn_Span_Text_Class = sInClass2+ "_span_" +sStrColor;
                               // sctSpan.sSpanClass = sInClass2+ "_span_" +sStrColor;
                                 sctSpan.sSpanClass = sStrColor;
                            }
                            else
                            {
                                //sctInItemInfo.sBtn_Span_Text_Class = sInClass2+ "_span";
                                //sctSpan.sSpanClass = sInClass2 + "_span";
                                sctSpan.sSpanClass = "";
                            }
                        }
                        else 
                        {
                            // Do nothing
                        }
                    }
                    /*-- CASE: KOMOKU_BOOKING_LINE --*/
                    else if ( strcmp( sBooking[0].c_str(), KOMOKU_BOOKING_LINE ) == 0  )
                    {
                        sctInItemInfo.sBtn_Hr_Line_Class = sBooking[0];
                        if ( bStrFlg || bImgFlg )
                        {
                            //sctInItemInfo.sBtn_Span_Text = sSpanStr;
                            sctSpan.sSpanText = sSpanStr;
                            if ( sStrColor != "" )
                            {
                                //sctInItemInfo.sBtn_Span_Text_Class = sInClass2+ "_span_" + sStrColor;
                                //sctSpan.sSpanClass = sInClass2+ "_span_" + sStrColor;
                                sctSpan.sSpanClass =  sStrColor;
                            }
                            else
                            {
                                //sctInItemInfo.sBtn_Span_Text_Class = sInClass2+ "_span";
                                //sctSpan.sSpanClass = sInClass2+ "_span";
                                sctSpan.sSpanClass = "";
                            }
                        }
                        else
                        {
                            if ( sctInItemInfo.sText != "" )
                            {
                                if ( sSpanStr != "" )
                                {
                                    sctInItemInfo.sText += "\\n"+ sSpanStr;
                                    sctInItemInfo.dwHrPosition = HR_MID;
                                }
                                else
                                {
                                    sctInItemInfo.sText += sSpanStr;
                                    if ( sctInItemInfo.dwHrPosition != HR_MID )
                                    {
                                        sctInItemInfo.dwHrPosition = HR_BOTTOM;
                                    }
                                }
                            }
                            else
                            {
                                sctInItemInfo.sText = sSpanStr;
                                if ( sctInItemInfo.dwHrPosition != HR_MID )
                                {
                                    sctInItemInfo.dwHrPosition = HR_BOTTOM;
                                }
                            }
                        }
                    }
                    /**-- OHTER CASE --*/
                    else
                    {
                        if ( sctInItemInfo.sBtn_Span_ImgClass != "" )
                        {
                            sctInItemInfo.bImageFirst = TRUE;
                        }
                        else
                        {
                            sctInItemInfo.bImageFirst = FALSE;
                        }
                        if (bStrFlg || bImgFlg)
                        {
                            //sctInItemInfo.sBtn_Span_Text = sSpanStr;
                            sctSpan.sSpanText = sSpanStr;
                            if ( sStrColor != "" )
                            {
                                //sctInItemInfo.sBtn_Span_Text_Class = sInClass2+ "_span_" + sStrColor;
                                //sctSpan.sSpanClass = sInClass2+ "_span_" + sStrColor;
                                sctSpan.sSpanClass =  sStrColor;
                            }
                            else
                            {
                                //sctInItemInfo.sBtn_Span_Text_Class = sInClass2+ "_span";
                                //sctSpan.sSpanClass = sInClass2+ "_span";
                                sctSpan.sSpanClass = "";
                            }
                        }
                        else
                        {
                            sctInItemInfo.sText = sSpanStr;
                        }
                    }

                    if ( sctSpan.sSpanText != "" )
                    {
                        sctInItemInfo.vSpanItem.push_back( sctSpan );
                    }
                }
                lpObj->m_sctItem = sctInItemInfo;
                // Current button is not child of any tag
                if ( m_vItemStack.size() == 0 )
                {
                    m_lpCurrentArea->m_vItemList.push_back( lpObj );
                }
                // Current button is child of other tag
                else
                {
                    /*if ( lpObj->m_sctItem.bVisibilityHidden == TRUE )
                    {
                        lpObj->m_sctItem.bVisible = FALSE;
                    }
                    else
                    {
                        lpObj->m_sctItem.bVisible = m_vItemStack[m_vItemStack.size() - 1 ]->m_sctItem.bVisible;
                    }*/
                    lpObj->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1 ]->m_sctItem.dwLeft;
                    lpObj->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1 ]->m_sctItem.dwTop;
                    m_vItemStack[m_vItemStack.size() - 1 ]->m_vChildItem.push_back( lpObj );
                }
            }
            /* End switch*/
        }
        else
        {
            if ( sctInItemInfo.sTagGroup == "" )
            {
                sctInItemInfo.sTagGroup = sGroup; //1
            }
            if ( sctInItemInfo.sTagID == "" )
            {
                sctInItemInfo.sTagID = "btn_"+ vInRowContent[NO_COL];
            }
            sctInItemInfo.sPageAtr = sPageAtr;
            sctInItemInfo.sText = sText;
            sctInItemInfo.sGaikan = sctInCatalog.sGaikanGrpName;
            lpObj->m_sctItem = sctInItemInfo;
            // Current button is not child of any tag
            if ( m_vItemStack.size() == 0 )
            {
                m_lpCurrentArea->m_vItemList.push_back( lpObj );
            }
            // Current button is child of other tag
            else
            {
                /*if ( lpObj->m_sctItem.bVisibilityHidden == TRUE )
                {
                    lpObj->m_sctItem.bVisible = FALSE;
                }
                else
                {
                    lpObj->m_sctItem.bVisible = m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.bVisible;
                }*/
                lpObj->m_sctItem.dwLeft += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwLeft;
                lpObj->m_sctItem.dwTop += m_vItemStack[m_vItemStack.size() - 1]->m_sctItem.dwTop;
                m_vItemStack[m_vItemStack.size() - 1]->m_vChildItem.push_back( lpObj );
            }
        }
    }
    catch( const exception& e )
    {
        // Catch regular expression
    }
    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  Get_MinMaxLen
//
//　表　　題　：  Get_MinMaxLen
//
//　概　　要　：  Get_MinMaxLen
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::Get_MinMaxLen( 
    string         sInTagID,
    string         &sMinLen,
    string         &sMaxLen,
    string        sInFmt,
    LPDWORD  lpdwOutErrCode)
{
    // Local variable
    SCT_TAG_CSV     sctTagCSV;
    DWORD               dwErrCode   = DGT_VALUE_ZERO_DWORD;
    BOOL                  bResult         = FALSE;
    BOOL                  bRet             = DGT_RET_ERR;

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    bRet = SearchTagStr( sInTagID, sctTagCSV, bResult, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    if ( bResult == TRUE  )
    {
        if (sInFmt != "")
        {
            sMinLen = sctTagCSV.sMinLen;
            sMaxLen = sctTagCSV.sMaxLen;
        }
        else
        {
            sMinLen = NASHI_MODE;
            sMaxLen = NASHI_MODE;
        }
    }
    else
    {
        sMinLen = NASHI_MODE;
        sMaxLen = NASHI_MODE;
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  output_JS_tbl
//
//　表　　題　：  output_JS_tbl
//
//　概　　要　：  output_JS_tbl
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

BOOL CScriptReader::output_JS_tbl(
            string          sInTagID,
            string          sInAltTagID,
            string          sInCurumu,
            string          sInNo,
           // string          sInDisp,
            string          sInClassFmt,
            string          sInFmtName,
            //CItem*       &lpOutItem,
            SCT_ITEM_INFO &sctInItemInfo,
            LPDWORD   lpdwOutErrCode )
{
    // Local variable
    DWORD             dwErrCode    = DGT_VALUE_ZERO_DWORD;      // Error code
    SCT_TAG_CSV  sctTagCSV;
    SCT_TAG_CSV  sctAltTagCSV;
    BOOL                bResult;
    CLogger*          lpLog             = NULL;                                     // For write log
    BOOL                bHanTei         = FALSE;
    BOOL                bRet            = DGT_RET_ERR;
    DWORD             dwClickBranchMode = DGT_VALUE_ZERO_DWORD;

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    CLogger::GetInstance( lpLog );
    
    if ( sctInItemInfo.sTagName == "button" )
    {
        sctInItemInfo.dwClickBranchMode = 99;
    }

    if ( CheckNashiMode(sInTagID ) == true )
    {
        *lpdwOutErrCode =  DGT_ERR_CSR_TAG_INVALID;
        return DGT_RET_OK;
    }

    SearchTagStr( sInTagID, sctTagCSV, bResult, &dwErrCode );
    if ( bResult == TRUE  )
    {
        // Do nothing
    }
    else
    {
        // Write log
        bRet = lpLog->Log( "【エラー】"+sInNo+"-タグ名検索エラー: "+ sInTagID, &dwErrCode );
        if ( bRet == DGT_RET_OK )
        {
            // Do nothing
        }
        else
        {
            *lpdwOutErrCode = dwErrCode;
            return DGT_RET_ERR;
        }
        *lpdwOutErrCode = DGT_ERR_CSR_TAG_NOT_FOUND;
        return DGT_RET_ERR;
    }

    if ( sInClassFmt == "button" )
    {
        bHanTei = FALSE;
    }
    else
    {
        if ( sInCurumu == SUBJECT_MARU )
        {
            bHanTei = TRUE;
        }
        else
        {
            bHanTei = FALSE;
        }
    }

    if ( sInFmtName == FMT_NAME_INPUT_START_BTN )
    {
        dwClickBranchMode = 0;
    }
    else
    {
        dwClickBranchMode = 99;
    }


    if (( CheckNashiMode( sInAltTagID ) == true ) ||
        ( sInClassFmt != "button"))
    {
        sctInItemInfo.sTagID                     = sctTagCSV.sTagID;
        sctInItemInfo.sTagGroup               = sctTagCSV.sTagGroup;
        sctInItemInfo.bTextClickEvent        = bHanTei;
        sctInItemInfo.dwClickBranchMode  = dwClickBranchMode;
        sctInItemInfo.sAltTagID                = "";
    }
    else
    {
        bResult   = FALSE;
        sctAltTagCSV.Memset();
        // Search alternative tag id
        SearchTagStr( sInAltTagID, sctAltTagCSV, bResult, &dwErrCode );
        if ( bResult == TRUE  )
        {
            // Do nothing
        }
        else
        {
            // Write log
            bRet = lpLog->Log( "【エラー】"+sInNo+"-オルタネートタグ名検索エラー: "+ sInAltTagID, &dwErrCode );
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
        sctInItemInfo.sTagID                     = sctTagCSV.sTagID;
        sctInItemInfo.sTagGroup               = sctTagCSV.sTagGroup;
        sctInItemInfo.bTextClickEvent        = bHanTei;
        sctInItemInfo.dwClickBranchMode  = dwClickBranchMode;
        // Set alternative tag id
        sctInItemInfo.sAltTagID                = sctAltTagCSV.sTagID;
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  SearchTagStr
//
//　表　　題　：  SearchTagStr
//
//　概　　要　：  SearchTagStr
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL  CScriptReader::SearchTagStr( 
                             string                 sInTagStr_JP,
                             SCT_TAG_CSV    &sctOutTag,
                             BOOL                  &bOutResult,
                             LPDWORD           lpdwOutErrCode )
{
    // Local variable
    DWORD      dwCnt   = DGT_VALUE_ZERO_DWORD;          // Counter

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    bOutResult = FALSE;
    for ( dwCnt = 0; dwCnt < m_vTagListCSV.size(); dwCnt++ )
    {
        if ( sInTagStr_JP == m_vTagListCSV[dwCnt].sTagJP )
        {
            sctOutTag = m_vTagListCSV[dwCnt];
            bOutResult     = TRUE;
            break;
        }
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  SetClass
//
//　表　　題　：  SetClass
//
//　概　　要　：  SetClass
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::SetClass(
                        DWORD               dwInParentMode,   
                        SCT_CATALOG_CSV     sctInCatalog,  
                        SCT_ITEM_INFO       &sctOutItemInfo,
                        vector<string>      vInRowContent,
                        string              &sOutClass, 
                        string              &sOutStatus, 
                        string              &sOutInitClass, 
                        LPDWORD             lpdwOutErrCode)
{
    // Local variable
    DWORD       dwErrCode  = DGT_VALUE_ZERO_DWORD;
    string      wk_class1    = "";
    LONG        lTagIndex     = NOT_FOUND;
    LONG        lSansoIndex  = -1;
    DWORD       dwHeight     = 0;
    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }


    lTagIndex = SerchTagName_index( sctInCatalog.sTagName );
    if (lTagIndex == NOT_FOUND)
    {
        *lpdwOutErrCode = DGT_ERR_SC_TAG_NO_FOUND;
        return DGT_RET_ERR;
    }

    if ((sctInCatalog.sAttribute == SEINENGAPPI) ||
        (sctInCatalog.sAttribute == IMG_STRETCH) ||
        (sctInCatalog.sAttribute == CONTENA))
    {
        lTagIndex = SerchTagName_index(sctInCatalog.sAttribute);
        if (lTagIndex == NOT_FOUND)
        {
            return FALSE;
        }
    }

    // Calculate sanso index
    lSansoIndex = dwInParentMode * TAG_NAME_LIST_SIZE + lTagIndex;

    // Checking for stretch image , tag name = image and element is child
    if ((( sctInCatalog.sTagName == "image" ) || ( sctInCatalog.sTagName == "div" ))&& ( dwInParentMode == 0 ) && ( vInRowContent[DISPSTR_COL].find( "【img") != std::string::npos ))
    {
        if ( string(WIDTH_UMU_LIST[lSansoIndex]) == SUBJECT_MARU )
        {
            if ( SuchiCheck(vInRowContent[ZOOMSIZE_COL]))
            {
                // have scale info, do not need to re-set width height
            }
            else
            {
                if ( SuchiCheck(vInRowContent[WIDTH_COL]))
                {
                    // have scale info, do not need to re-set width height
                }
                else
                {
                    // reset width, height for non-stretch image
                    //sctOutItemInfo.dwWidth  = 0;
                    //sctOutItemInfo.dwHeight = 0;
                    sctOutItemInfo.bOriginal = TRUE;
                }
            }
        }
        else
        {
            //sctOutItemInfo.dwHeight = 0;
            sctOutItemInfo.bOriginal = TRUE;
        }

        if ((string(HIGHT_UMU_LIST[lSansoIndex]) != SUBJECT_BATSU) &&
            (SuchiCheck(vInRowContent[HEIGHT_COL]) == 1))
        {
           // have scale info, do not need to re-set width height
        }
        else
        {
            // reset width, height for non-stretch image
            //sctOutItemInfo.dwWidth  = 0;
            sctOutItemInfo.bOriginal = TRUE;
            //sctOutItemInfo.dwHeight = 0;
        }
    }

    if (vInRowContent[HIDDEN_COL] == SUBJECT_BATSU)
    {
        if ((sctInCatalog.sTagName == "image") && (dwInParentMode == 1))
        {
            sOutStatus      = "_pa_visible";
            sctOutItemInfo.bVisible = TRUE;
            sctOutItemInfo.bVisibilityHidden = FALSE;
        }
        else
        {
            // wk_class1 += "visibility_hidden";
            sOutStatus = "_pa_hidden";
            sctOutItemInfo.bVisible = FALSE;
            sctOutItemInfo.bVisibilityHidden = TRUE;
        }
    }
    else
    {
        sOutStatus = "_pa_visible";
        sctOutItemInfo.bVisible = TRUE;
    }

    if (vInRowContent[DISABLE_COL] != SUBJECT_BATSU )
    {
        sOutStatus += "_enable";
        sctOutItemInfo.bEnable = TRUE;
    }
    else
    {
        sOutStatus += "_disable";
        sctOutItemInfo.bEnable = FALSE;
    }

    // Set height
    if ( SuchiCheck( vInRowContent[ HEIGHT_COL] ) == 1 )
    {
        dwHeight = atoi( vInRowContent[ HEIGHT_COL].c_str() ) * m_lpCurrentArea->m_sctAreaInfo.dwCellHeight;
        if (HIGHT_UMU_LIST[lSansoIndex] == "H")
        {
            sctOutItemInfo.lLineHeight = -1;
        }
        else
        {
            if ( vInRowContent[DISPSTR_COL].find( "\n") != std::string::npos )
            // if ( regex_match( vInRowContent[DISPSTR_COL], regex("\n")))
            {
                sctOutItemInfo.lLineHeight = -1;
            }
            else
            {
                sctOutItemInfo.lLineHeight = dwHeight - 2;
            }
        }
    }
    else
    {
    }

    if (atoi(sctInCatalog.sClassSetTag.c_str()) != 0)
    {
        if (((dwInParentMode == 0) && (atoi(sctInCatalog.sClassSetTag.c_str()) >= 2)) ||        //子：classSetTag＝２or３
            ((dwInParentMode == 1) && ((atoi(sctInCatalog.sClassSetTag.c_str()) % 2) == 1)))       //親：classSetTag＝１or３
        {
            SearchInitstr(vInRowContent[INITDESIGN_COL], sOutInitClass, &dwErrCode );
            if (sOutInitClass == "")
            {
                sOutInitClass = sctInCatalog.sSetClassName;
            }
            if (vInRowContent[DEFAULTAPP_COL] == SUBJECT_MARU )
            {
                wk_class1 += sOutInitClass;
            }
            else
            {
                wk_class1 += sctInCatalog.sSetClassName;
            }
        }
    }

    sOutClass = wk_class1;
     return DGT_RET_OK;
 }

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  SearchInitstr
//
//　表　　題　：  SearchInitstr
//
//　概　　要　：  SearchInitstr
//
//　戻　り　値：  
//
//　引　　数　： 
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
 BOOL CScriptReader::SearchInitstr( string sInJPStype, string &sOutString, LPDWORD lpdwOutErrCode )
 {
     // Local variable
     DWORD     dwCnt = DGT_VALUE_ZERO_DWORD;        // Counter

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    sOutString = "";
    if ( sInJPStype == NASHI_MODE )
    {
        sOutString = "";
        return DGT_RET_OK;
    }

   for ( dwCnt = 0; dwCnt < m_vInitListCSV.size(); dwCnt++ )
   {
       if ( sInJPStype == m_vInitListCSV[dwCnt].sAppearanceName )
       {
           sOutString = m_vInitListCSV[dwCnt].sClassSetName;
           break;
       }
   }

     return DGT_RET_OK;
 }


/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  GetHeaderInfo
//
//　表　　題　：  Get header information
//
//　概　　要　：   Get header information
//
//　戻　り　値：  
//
//　引　　数　：  
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/03/02   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::GetHeaderInfo(
                                Excel::_WorksheetPtr       lpInWorkSheet,
                                CArea*                     &lpOutArea,
                                vector<string>             &vOutHeaderInfo,
                                LPDWORD                    lpdwOutErrCode )
{
    // Local variable
    BOOL             bRet                 =   DGT_RET_ERR;               // Return value
    DWORD            dwCnt                =   DGT_VALUE_ZERO_DWORD;      // Counter
    DWORD            dwErrCode            =   DGT_VALUE_ZERO_DWORD;      // Erorr Code
    string           sAreaJPName          =   "";                        // Area JP name
    string           sAreaEIName          =   "";
    string           sAreaFuncName        =   "";
    string           sTemp                =   "";
    CLogger*         lpLog                =   NULL;                       // For write log
    LONG             lIndex               =   NOT_FOUND;                  // Index

    SCT_CELL         HEADER_RANGE[18] =  { SCT_CELL(2,1), //"B1", // 画面名                     // 0
                                                             SCT_CELL(2,2),//"B2", // エリア名                      // 1
                                                             SCT_CELL(2,3),//"B3", // 背景色                         // 2
                                                             SCT_CELL(4,1), //"D1", // 出力ﾌｧｲﾙ名                 // 3
                                                             SCT_CELL(4,2), //"D2", // ﾃﾝﾌﾟﾚｰ                       // 4
                                                             SCT_CELL(7,2),//"G2", // 基準枠　縦　サイズ     // 5
                                                             SCT_CELL(9,2),//"I2", // 基準枠　横　サイズ      // 6
                                                             SCT_CELL(7,3),//"G3", // 分割数　縦                  // 7
                                                             SCT_CELL(9,3),//"I3", // 分割数　横                   // 8
                                                             SCT_CELL(7,4),//"G4", // 1セル　縦                   // 9
                                                             SCT_CELL(9,4),//"I4", // 1セル　横                    // 10
                                                             SCT_CELL(6,7),//"F7", // 余白－上                     // 11
                                                             SCT_CELL(7,7),//"G7", // 余白－右                     // 12
                                                             SCT_CELL(8,7),//"H7", // 余白－下                     // 13
                                                             SCT_CELL(9,7),//"I7", // 余白－左                      // 14
                                                             SCT_CELL(21,5),//"U5", // バージョン情報         // 15
                                                             SCT_CELL(21,6),//"U6", // 作成者（変更者）      // 16
                                                             SCT_CELL(21,7)//"U7"  // 作成日（変更日）       // 17
                                                             };

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    if ( lpInWorkSheet == NULL )
    {
        *lpdwOutErrCode = DGT_ERR_CSR_GHI_EXCELCOM;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    if ( lpOutArea == NULL )
    {
        *lpdwOutErrCode = DGT_ERR_CSR_GHI_PARA;
        return DGT_RET_ERR;
    }

    CLogger::GetInstance( lpLog );
    

    // Get header cell data
    for ( dwCnt = 0; dwCnt < 18; dwCnt++ )
    {
        sTemp = "";
        m_cExcelReader.GetCellContent( 
                        HEADER_RANGE[dwCnt].dwRow,
                        HEADER_RANGE[dwCnt].dwCol,
                        lpInWorkSheet,
                        sTemp,
                        &dwErrCode );
        vOutHeaderInfo.push_back( sTemp );
    }

    sAreaJPName = vOutHeaderInfo[AREA_MODE_COL];
    auto it = find( m_vAreaListCSV.begin(), m_vAreaListCSV.end(), sAreaJPName);
    if ( it != m_vAreaListCSV.end())
    {
        sAreaEIName = it->sArea_EI;
    }
    else
    {
        //Write log
        bRet = lpLog->Log("【エラー】Area 設定エラー:"+sAreaJPName , &dwErrCode );
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

    if ( sAreaJPName == "状態表示部" )
    {
        lpOutArea->m_sctAreaInfo.sAreaType = "E_AREA_INDICATOR";
    }
    else if ( sAreaJPName == "表示部" )
    {
        lpOutArea->m_sctAreaInfo.sAreaType = "E_AREA_DISP";
    }
    else if ( sAreaJPName == "操作部" )
    {
        lpOutArea->m_sctAreaInfo.sAreaType = "E_AREA_OPERATING";
    }
    else if ( sAreaJPName == "常設釦部" )
    {
        lpOutArea->m_sctAreaInfo.sAreaType = "E_AREA_CONST_BTN";
    }
    else if ( sAreaJPName == "業務案内部" )
    {
        lpOutArea->m_sctAreaInfo.sAreaType = "E_AREA_BUSSINESS";
    }
    else if ( sAreaJPName == "中央表示部" )
    {
        lpOutArea->m_sctAreaInfo.sAreaType = "E_AREA_CENTERDISP";
    }
    else if ( sAreaJPName == "ポップアップ" )
    {
        lpOutArea->m_sctAreaInfo.sAreaType = "E_AREA_POPUP";
    }

    // Search and update area background
    bRet = Search_MstBgColor( vOutHeaderInfo[BGCOLOR_COL], lIndex, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }

    if ( lIndex != NOT_FOUND )
    {
        // Set string
        lpOutArea->m_sctAreaInfo.sBackground      = m_vBgColor[lIndex].sClassSetName;
    }
    else
    {
        // Do nothing
    }

    lpOutArea->m_sctAreaInfo.sAreaJPName      = sAreaJPName;
    lpOutArea->m_sctAreaInfo.sAreaEngName     = sAreaEIName;
    sAreaFuncName                             =  vOutHeaderInfo[OUT_FNAME_COL];
   /* if ( "ChakuEkiSentaku_CB" == vOutHeaderInfo[OUT_FNAME_COL] )
    {
        int a = 1;
    }*/
// Start TrungLV 2015-09-07: Dont remove space
#if 0
    sAreaFuncName.erase(
            std::remove(sAreaFuncName.begin(),
            sAreaFuncName.end(),
            ' '),
            sAreaFuncName.end());
#endif
// Start TrungLV 2015-09-07
    lpOutArea->m_sctAreaInfo.sAreaFuncName    = sAreaFuncName;
// Start TrungLV 2015-09-07: Convert to valid function name
    lpOutArea->m_sctAreaInfo.sFunctionMapName = lpOutArea->m_sctAreaInfo.sAreaFuncName;
    ProcessFunctionName(lpOutArea->m_sctAreaInfo.sFunctionMapName);
// End TrungLV 2015-09-07: Convert to valid function name

    // Check the same function name
    for ( dwCnt = 0; dwCnt < m_vAreaList.size(); dwCnt++ )
    {
        if ( m_vAreaList[dwCnt]->m_sctAreaInfo.sAreaFuncName == lpOutArea->m_sctAreaInfo.sAreaFuncName )
        {
            *lpdwOutErrCode = DGT_ERR_CSR_GHI_AREA_FUNC_EXISTED;
            return DGT_RET_ERR;
        }
// Start TrungLV 2015-09-07: Add "_" when have the same function map name
        else if ( m_vAreaList[dwCnt]->m_sctAreaInfo.sFunctionMapName == lpOutArea->m_sctAreaInfo.sFunctionMapName )
        {
                lpOutArea->m_sctAreaInfo.sFunctionMapName += "X";
        }
// End TrungLV 2015-09-07
    }
    // Set area width height
    if ( SuchiCheck( vOutHeaderInfo[BASE_HEIGHT_COL] ) == 1 )
    {
        lpOutArea-> m_sctAreaInfo.dwHeight = atoi ( vOutHeaderInfo[BASE_HEIGHT_COL].c_str() );
    }
    else
    {
        *lpdwOutErrCode = DGT_ERR_CSR_GHI_DATA_INVALID;
    }

    if ( SuchiCheck( vOutHeaderInfo[BASE_WIDTH_COL] ) == 1 )
    {
        lpOutArea-> m_sctAreaInfo.dwWidth = atoi ( vOutHeaderInfo[BASE_WIDTH_COL].c_str() );
    }
    else
    {
        *lpdwOutErrCode = DGT_ERR_CSR_GHI_DATA_INVALID;
    }

    // Set cell size
    if ( SuchiCheck( vOutHeaderInfo[CEL_TATE_COL] ) == 1 )
    {
        lpOutArea->m_sctAreaInfo.dwCellHeight = atoi ( vOutHeaderInfo[CEL_TATE_COL].c_str() );
    }
    else
    {
        *lpdwOutErrCode = DGT_ERR_CSR_GHI_DATA_INVALID;
    }

    if ( SuchiCheck( vOutHeaderInfo[CEL_YOKO_COL] ) == 1 )
    {
        lpOutArea->m_sctAreaInfo.dwCellWidth = atoi ( vOutHeaderInfo[CEL_YOKO_COL].c_str() );
    }
    else
    {
       *lpdwOutErrCode = DGT_ERR_CSR_GHI_DATA_INVALID;
    }
    // Set margin
    if ( SuchiCheck( vOutHeaderInfo[YOHAKU_LEFT_COL] ) == 1 )
    {
        lpOutArea-> m_sctAreaInfo.dwMarginLeft       =  atoi( vOutHeaderInfo[YOHAKU_LEFT_COL].c_str());
    }
    else
    {
        *lpdwOutErrCode = DGT_ERR_CSR_GHI_DATA_INVALID;
    }

    if ( SuchiCheck( vOutHeaderInfo[YOHAKU_TOP_COL] ) == 1 )
    {
        lpOutArea-> m_sctAreaInfo.dwMarginTop       =  atoi( vOutHeaderInfo[YOHAKU_TOP_COL].c_str());
    }
    else
    {
        *lpdwOutErrCode = DGT_ERR_CSR_GHI_DATA_INVALID;
    }

    if ( SuchiCheck( vOutHeaderInfo[YOHAKU_RIGHT_COL] ) == 1 )
    {
        lpOutArea-> m_sctAreaInfo.dwMarginRight       =  atoi( vOutHeaderInfo[YOHAKU_RIGHT_COL].c_str());
    }
    else
    {
        *lpdwOutErrCode = DGT_ERR_CSR_GHI_DATA_INVALID;
    }
    if ( SuchiCheck( vOutHeaderInfo[YOHAKU_BOTTOM_COL] ) == 1 )
    {
        lpOutArea-> m_sctAreaInfo.dwMarginBottom       =  atoi( vOutHeaderInfo[YOHAKU_BOTTOM_COL].c_str());
    }
    else
    {
        *lpdwOutErrCode = DGT_ERR_CSR_GHI_DATA_INVALID;
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  Search_MstBgColor
//
//　表　　題　：  Search bg color
//
//　概　　要　：  Search bg color
//
//　戻　り　値：  
//
//　引　　数　：  string                  sInBgColor              (I)              Bg color
//                         LPDWORD           lpdwOutErrCode      (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/27   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::Search_MstBgColor( string sInBgColor, LONG &lOutIndex, LPDWORD lpdwOutErrCode )
{
    // Local variable
    DWORD            dwCnt       =   DGT_VALUE_ZERO_DWORD;      // Error code

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    lOutIndex = NOT_FOUND;
    for ( dwCnt = 0; dwCnt < m_vBgColor.size(); dwCnt++ )
    {
        if ( sInBgColor == m_vBgColor[dwCnt].sBgColor )
        {
            lOutIndex = dwCnt;
            break;
        }
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  CheckItem
//
//　表　　題　：  Check the validaiton of item
//
//　概　　要　：  Check the validaiton of item
//
//　戻　り　値：  
//
//　引　　数　：  vector<string>     vInRowContent              (I)              Bg color
//                         LPDWORD           lpdwOutErrCode            (O)             Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/27   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CScriptReader::CheckItem( vector<string> vInRowContent, BOOL &bInCheckResult, LPDWORD lpdwOutErrCode )
{
    // Local variable
    DWORD            dwCnt        =   DGT_VALUE_ZERO_DWORD;      // Counter
    DWORD           dwErrCode  = DGT_VALUE_ZERO_DWORD;        // Error code
    CLogger*         lpLog           = NULL;
    string              sCheckValue = "";
    LONG               lCheck         = DGT_VALUE_ZERO_LONG;
    string              sNoCol         = "";
    BOOL                bRet           = DGT_RET_ERR;
    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    CLogger::GetInstance( lpLog );
    

    if ( vInRowContent.size() == 0 )
    {
        *lpdwOutErrCode = DGT_ERR_CSR_CI_PARA;
         return DGT_RET_ERR;
    }

    bInCheckResult = FALSE;

    if ( vInRowContent[DISPSTR_COL] == "")
    {
        bRet = lpLog->Log ( "【エラー】"+vInRowContent[NO_COL]+"-表示文字　値が空白です。" , &dwErrCode);
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
    sNoCol         =  vInRowContent[NO_COL];
    sCheckValue = vInRowContent[FONTSIZE_COL];
    lCheck          = SuchiCheck( sCheckValue );
    switch( lCheck )
    {
        case -1:
                    bRet = lpLog->Log ( "【エラー】"+sNoCol+"-フォント　数値チェックエラー: " + sCheckValue , &dwErrCode);
                    if ( bRet == DGT_RET_OK )
                    {
                        // Do nothing
                    }
                    else
                    {
                        *lpdwOutErrCode = dwErrCode;
                        return DGT_RET_ERR;
                    }
                    bInCheckResult = FALSE;
            break;
    }

    sCheckValue = vInRowContent[WIDTH_COL];
    lCheck          = SuchiCheck( sCheckValue );
    switch( lCheck )
    {
        case -1:
                    bRet = lpLog->Log ( "【エラー】"+sNoCol+"-縦　数値チェックエラー:" + sCheckValue , &dwErrCode);
                    if ( bRet == DGT_RET_OK )
                    {
                        // Do nothing
                    }
                    else
                    {
                        *lpdwOutErrCode = dwErrCode;
                        return DGT_RET_ERR;
                    }
                    bInCheckResult = FALSE;
            break;
    }

    sCheckValue = vInRowContent[HEIGHT_COL];
    lCheck          = SuchiCheck( sCheckValue );
    switch( lCheck )
    {
        case -1:
                    bRet = lpLog->Log ( "【エラー】"+sNoCol+"-横　数値チェックエラー:" + sCheckValue , &dwErrCode);
                    if ( bRet == DGT_RET_OK )
                    {
                        // Do nothing
                    }
                    else
                    {
                        *lpdwOutErrCode = dwErrCode;
                        return DGT_RET_ERR;
                    }
                    bInCheckResult = FALSE;
            break;
    }

    sCheckValue = vInRowContent[ZOOMSIZE_COL];
    lCheck          = SuchiCheck( sCheckValue );
    switch( lCheck )
    {
        case -1:
                    bRet = lpLog->Log ( "【エラー】"+sNoCol+"-縮小率　数値チェックエラー:" + sCheckValue , &dwErrCode);
                    if ( bRet == DGT_RET_OK )
                    {
                        // Do nothing
                    }
                    else
                    {
                        *lpdwOutErrCode = dwErrCode;
                        return DGT_RET_ERR;
                    }
                    bInCheckResult = FALSE;
            break;
    }

    return DGT_RET_OK;
}

string CScriptReader::Conv_StrNewLine( string sInStr )
{
    string sNewLine     = "";
    sNewLine = sInStr;
    try
    {
        sNewLine = std::regex_replace( sInStr, std::regex("\n"), string("\\n") );
    }
    catch( const exception& e )
    {
        // Do nothing
        return sNewLine;
    }
    return sNewLine;
}

void CScriptReader::CleanUp()
{
    DWORD dwCnt = DGT_VALUE_ZERO_DWORD;
    for ( dwCnt = 0; dwCnt < m_vAreaList.size(); dwCnt++ )
    {
        if (m_vAreaList[dwCnt] != NULL )
        {
            delete m_vAreaList[dwCnt];
        }
    }
    m_vAreaList.clear();

    for ( dwCnt = 0; dwCnt < m_vItemStack.size(); dwCnt++ )
    {
        delete m_vItemStack[dwCnt];
    }

    m_vItemStack.clear();
    m_lpCurrentArea = NULL;
}