////////////////////////////////////////////////////////////////////////////////
//
//  ファイル名：ExcelReader.cpp
//
//  概要　　　：This class used read open,close and get information inexcel file
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

#include "ExcelReader.h"
#include "DGT_SymbolDef.h"
#include "DGT_PvSymbolDef.h"
#include "DGT_PvErrCode.h"
#include "Utility.h"

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関  数  名：  ExcelReader
//
//　表    題  ：  Constructor
//
//　概    要  ：  Constructor
//
//　戻  り  値：  
//
//　引　　数　：  
//
//  バージョン　     日付          氏名              備考
//  バージョン　     日付　　　　  氏名　　　　       備考
//  DGT-00.00.00    2015/02/25   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
CExcelReader::CExcelReader(void)
{
    m_lpWb                  = NULL;
    m_lpApp                 = NULL;
//    m_lpWs                  = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関  数  名：  ExcelReader
//
//　表    題  ：  Destructor
//
//　概    要  ：  Destructor
//
//　戻  り  値：  
//
//　引　　数　：  
//
//  バージョン　     日付          氏名              備考
//  バージョン　     日付　　　　  氏名　　　　       備考
//  DGT-00.00.00    2015/02/25   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
CExcelReader::~CExcelReader(void)
{
    try
    {
        if ( m_lpWb != NULL )
        {
            m_lpWb->Close( (long) TRUE );
            // Quit excel application
            //m_lpWb->Close(false);
            m_lpApp->Quit();
            m_lpWb     = NULL;
    //        m_lpWs     = NULL;
            m_lpApp    = NULL;
        }
        else
        {
            // Do nothing
        }
    }
    catch( _com_error &e )
    {
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  Open excel file
//
//　表　　題　：  Open excel file
//
//　概　　要　：  Open excel file
//
//　戻　り　値：  
//
//　引　　数　：  string                     sInFilePath               (I)            File path
//                        LDPWORD                lpdwOutErrCode      (O)           Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/25   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

BOOL CExcelReader::OpenExcelFile( 
                                   string        sInFilePath,
                                   LPDWORD  lpdwOutErrCode)
{
        // Local variable
    BOOL                   bRet              = DGT_RET_ERR;                      // Return value
    WORD                 wCheckResult = 0;                                          // Check result
    DWORD               dwErrCode     = DGT_VALUE_ZERO_DWORD;    // Error code
    variant_t              tFileFormat;                                                   // File format

    // Initialize
    m_lpWb  = NULL;
    m_lpApp = NULL;

    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

   // Check the validation of file path
    bRet = CheckFilePath( sInFilePath, &wCheckResult, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        if (( wCheckResult == DGT_U_CFIP_PATH_TOO_LONG ) || 
           ( wCheckResult == DGT_U_CFIP_PATH_INVALID ) || 
           ( wCheckResult == DGT_U_CFIP_PATH_NULL ))
        {
         *lpdwOutErrCode = DGT_ERR_CER_OEF_PARA;
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

    try
    {
        CoInitialize( NULL );
        // Create Excel Instance

        m_lpApp.CreateInstance( L"Excel.Application" );
        tFileFormat = (long) 51;
        // Open excel master fule
        m_lpWb = m_lpApp ->Workbooks->Open( _bstr_t( sInFilePath.c_str()));
      }
    // EXCEL COM error
    catch( _com_error &e )
    {
       *lpdwOutErrCode = DGT_ERR_CER_OEF_EXCEL_COM;
        m_lpWb = NULL;
        m_lpApp = NULL;
        return DGT_RET_ERR;
    }

    return DGT_RET_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  Close excel file
//
//　表　　題　：  Close excel file
//
//　概　　要　：  Close excel file
//
//　戻　り　値：  
//
//　引　　数　：  LDPWORD                lpdwOutErrCode      (O)           Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/25   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CExcelReader::CloseExcelFile( LPDWORD lpdwOutErrCode )
{
    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    try
    {
        if( m_lpWb != NULL )
        {
            // Close workbook
            m_lpWb->Close( (long) TRUE );

            // Quit application
            m_lpApp->Quit();
            m_lpWb  = NULL;
//            m_lpWs  = NULL;
            m_lpApp = NULL;
        } 
        else
        {
            // Do nothing
        }       

    }
    // Excel COM error
    catch ( _com_error &e )
    {
        *lpdwOutErrCode = DGT_ERR_CER_CEF_EXCEL_COM;
        return DGT_RET_ERR;
    }
    CoUninitialize();

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  GetSheet
//
//　表　　題　：  Get sheet info
//
//　概　　要　：  Get sheet info
//
//　戻　り　値：  
//
//　引　　数　：   string                           sInSheetName         (I)            Sheet name
//                          Excel::_WorksheetPtr    lpOutSheet              (O)           Sheet pointer
//                          LDPWORD                     lpdwOutErrCode      (O)           Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/25   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CExcelReader::GetSheet( string sInSheetName, Excel::_WorksheetPtr &lpOutSheet, LPDWORD lpdwOutErrCode )
{
    // Local variable

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    try
    {
        lpOutSheet      = NULL;
        lpOutSheet      = m_lpWb->Sheets->GetItem(sInSheetName.c_str());
        if ( lpOutSheet == NULL )
        {
            *lpdwOutErrCode = DGT_ERR_CER_CS_NOT_EXIST;
            return DGT_RET_ERR;
        }
    }
    catch ( _com_error &e )
    {
        *lpdwOutErrCode = DGT_ERR_CER_CS_EXCEL_COM;
        return DGT_RET_ERR;
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  GetRowContent
//
//　表　　題　：  Get all row content
//
//　概　　要　：  Get all row content
//
//　戻　り　値：  
//
//　引　　数　：   string                           sInSheetName         (I)            Sheet name
//                          Excel::_WorksheetPtr    lpOutSheet              (O)           Sheet pointer
//                          LDPWORD                     lpdwOutErrCode      (O)           Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/25   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

BOOL CExcelReader::GetRowContent(
                                                         DWORD                          dwInRow,
                                                         DWORD                          dwInStartCol,
                                                         DWORD                          dwInEndCol, 
                                                         Excel::_WorksheetPtr       lpInWorkSheet,
                                                         vector<string>                &vOutRowContent, 
                                                         LPDWORD                       lpdwOutErrCode )
{
    // Local variable
    DWORD                          dwErrCode        =   DGT_VALUE_ZERO_DWORD;       // Error code
    DWORD                          dwCnt               =   DGT_VALUE_ZERO_DWORD;       // Counter
    BOOL                              bRet                 =   DGT_RET_ERR;                          // Return value
    _bstr_t                           bTemp;
    _variant_t                      vTemp;
    _variant_t                      vTempSrc;
    string                              sTemp;
    HRESULT                         hReturn;

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Check parameter
    if ( lpInWorkSheet == NULL )
    {
        *lpdwOutErrCode = DGT_ERR_CER_GRC_PARA;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    vOutRowContent.clear();

    try
    {
        for ( dwCnt = dwInStartCol; dwCnt <= dwInEndCol; dwCnt++ )
        {
            hReturn = S_FALSE;
            vTemp =  lpInWorkSheet->Cells->GetItem( dwInRow , dwCnt );
            hReturn = VariantChangeType((VARIANTARG*) &vTemp, (VARIANTARG*)  &vTemp,0,VT_BSTR );
            if ( hReturn == S_OK )
            {
                bTemp = (_bstr_t) vTemp;
                sTemp = bTemp;
                vOutRowContent.push_back( sTemp );
            }
            else
            {
                vOutRowContent.push_back( EXCEL_REF );
            }
        }
    }
    catch ( _com_error &e )
    {
        *lpdwOutErrCode = DGT_ERR_CER_GRC_EXCEL_COM;
        return DGT_RET_ERR;
    }

    return DGT_RET_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  RemoveMaru
//
//　表　　題　：  Remove maru in excel file
//
//　概　　要　：  Remove maru in excel file
//
//　戻　り　値：  
//
//　引　　数　：  LDPWORD    lpdwOutErrCode      (O)           Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/08/07   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CExcelReader::RemoveMaru( LPDWORD   lpdwOutErrCode )
{
    //Initialize
    Excel::_WorksheetPtr    lpWs       =  NULL;                        // Worksheet pointer
    DWORD                   dwErrCode  = DGT_VALUE_ZERO_DWORD;
    DWORD                   dwMaruCol  = 3;
    // TSDV-20150811-SonPT-Fix bug that cannot delete all maru
    DWORD                   dwAreaCol  = 7;
    // TSDV-20150811-End
    DWORD                   dwRow      = 3;
    string                  sCellStr   = "";
    BOOL                    bRet       = FALSE;
        // Get sheet
    bRet = GetSheet( SHEET_CREATATION_LIST, lpWs, &dwErrCode );
    if ( bRet == DGT_RET_OK )
    {
        // Do nothing
    }
    else
    {
        lpWs            = NULL;
        *lpdwOutErrCode = DGT_ER_CSR_RM_SHEET_NOT_FOUND;
        return DGT_RET_ERR;
    }

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    try
    {
        // remove maru check
        while ( 1 )
        {
            // get No content
            // TSDV-20150811-SonPT- Fix bug cannot delete all maru
            // GetCellContent( dwRow, dwMaruCol, lpWs, sCellStr, &dwErrCode );
            GetCellContent( dwRow, dwAreaCol, lpWs, sCellStr, &dwErrCode );
            // TSDV-20150811- end
            if ( sCellStr == "" )
            {
                break;
            }
            // Remove maru
            lpWs->Cells->Item[dwRow][dwMaruCol] = "";
            dwRow++;
        }
    }
    catch ( _com_error &e )
    {
        *lpdwOutErrCode = DGT_ERR_CER_RM_EXCEL_COM;
        return DGT_RET_ERR;
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  GetCellContent
//
//　表　　題　：  Get all row content
//
//　概　　要　：  Get all row content
//
//　戻　り　値：  
//
//　引　　数　：   DWORD                        dwInRow                (I )            Row number
//                          DWORD                        dwInCol                  (I )           Col number
//                          Excel::_WorksheetPtr    lpInWorkSheet         (I )           Sheet pointer
//                          string                           sOutContent            (O)           row content
//                          LDPWORD                     lpdwOutErrCode      (O)           Error code
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/03/02   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

BOOL CExcelReader::GetCellContent( 
                                     DWORD                          dwInRow,
                                     DWORD                          dwInCol,
                                     Excel::_WorksheetPtr       lpInWorkSheet,
                                     string                              &sOutContent,
                                     LPDWORD                       lpdwOutErrCode )
{
    // Local variable
    _bstr_t                           bTemp;
    _variant_t                      vTemp;
    _variant_t                      vTempSrc;
    string                            sTemp;
    HRESULT                       hReturn;

    // Check parameter
    if ( lpdwOutErrCode  == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Check parameter
    if ( lpInWorkSheet == NULL )
    {
        *lpdwOutErrCode = DGT_ERR_CER_GCC_PARA;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    try
    {
        vTemp =  lpInWorkSheet->Cells->GetItem( dwInRow , dwInCol );
        hReturn = VariantChangeType((VARIANTARG*) &vTemp, (VARIANTARG*)  &vTemp,0,VT_BSTR );
        if ( hReturn == S_OK )
        {
            bTemp = (_bstr_t) vTemp;
            sOutContent = bTemp;
        }
        else
        {
            sOutContent = EXCEL_REF;
        }
    }
    catch ( _com_error &e )
    {
        *lpdwOutErrCode = DGT_ERR_CER_GCC_EXCEL_COM;
        return DGT_RET_ERR;
    }

    return DGT_RET_OK;
}


BOOL  CExcelReader::SearchColValue_Row( 
                        Excel::_WorksheetPtr      lpInWorkSheet,
                        DWORD                         dwInStartRow,
                        DWORD                         dwInCol,
                        string                             sInKeyWord,
                        LONG                             &lFoundRow,
                        LPDWORD                      lpdwOutErrCode)
{
    // Local variable
    DWORD       dwCnt          = DGT_VALUE_ZERO_DWORD;     // Counter
    DWORD       dwErrCode   = DGT_VALUE_ZERO_DWORD;     // Error code
    BOOL          bRet             = DGT_RET_ERR;                        // Return value
    string          sCellValue    = "";                                          // sNo col value

    // Check parameter
    if ( lpInWorkSheet == NULL )
    {
        *lpdwOutErrCode = DGT_ERR_CER_SCLR_PARA;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    dwCnt = dwInStartRow;
    lFoundRow = NOT_FOUND;
    while( 1 )
    {
        bRet = GetCellContent( dwCnt, 1, lpInWorkSheet,sCellValue,&dwErrCode );
        if ( bRet == DGT_RET_OK )
        {
            // Do nothing
        }
        else
        {
            *lpdwOutErrCode = dwErrCode;
            return DGT_RET_ERR;
        }

        if ( sCellValue == "" )
        {
            break;
        }
        sCellValue = "";
        bRet = GetCellContent( dwCnt, dwInCol, lpInWorkSheet,sCellValue,&dwErrCode );
        if ( bRet == DGT_RET_OK )
        {
            // Do nothing
        }
        else
        {
            *lpdwOutErrCode = dwErrCode;
            return DGT_RET_ERR;
        }

        if ( sCellValue == sInKeyWord )
        {
            lFoundRow = dwCnt;
            break;
        }

        dwCnt ++;
    }

    return DGT_RET_OK;
}
