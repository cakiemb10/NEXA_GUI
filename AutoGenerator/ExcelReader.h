#pragma once
////////////////////////////////////////////////////////////////////////////////
//
//  ファイル名：ExcelReader.h
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
#include "mso.tlh"
#include "vbe6ext.tlh"
#include "excel.tlh"
#include <vector>
#include <string>

using namespace std;
class CExcelReader
{
public:
    CExcelReader(void);
    ~CExcelReader(void);

    //Open excel file
    BOOL OpenExcelFile( string sInFilePath, LPDWORD lpdwOutErrCode);

    //Close Excel file
    BOOL CloseExcelFile( LPDWORD lpdwOutErrCode);

    //Check existence of sheet
     BOOL GetSheet( 
                 string                              sInSheetName, 
                 Excel::_WorksheetPtr       &lpOutSheet, 
                 LPDWORD                        lpdwOutErrCode);

     // Get row content
     BOOL GetRowContent( 
                 DWORD                          dwInRow,
                 DWORD                          dwInStartCol,
                 DWORD                          dwInEndCol, 
                 Excel::_WorksheetPtr       lpWorkSheet,
                 vector<string>                &vOutRowContent, 
                 LPDWORD                       lpdwOutErrCode );

     // Get cell content
     BOOL GetCellContent( 
                 DWORD                          dwInRow,
                 DWORD                          dwInCol,
                 Excel::_WorksheetPtr       lpWorkSheet,
                 string                              &sOutContent,
                 LPDWORD                       lpdwOutErrCode );

    BOOL  SearchColValue_Row( 
                        Excel::_WorksheetPtr       lpInWorkSheet,
                        DWORD           dwInStartRow,
                        DWORD           dwInCol,
                        string              sInKeyWord,
                        LONG              &lFoundRow,
                        LPDWORD        dwlpOutErrCode);
// Start TrunglV 2015-08-07 : Add remove maru
    BOOL RemoveMaru ( LPDWORD                    dwlpOutErrCode );
// End TrunglV 2015-08-07 : 

    Excel::_ApplicationPtr                   m_lpApp;                             // Excel application pointer
    Excel::_WorkbookPtr                    m_lpWb;                             // Work book pointer
//    Excel::_WorksheetPtr           m_lpWs;                             // Work sheet

};

