#pragma once
////////////////////////////////////////////////////////////////////////////////
//
//  �t�@�C�����FExcelReader.h
//
//  �T�v�@�@�@�FThis class used read open,close and get information inexcel file
//
//  �쐬�ҁ@�@�F(TSDV) TrungLV
//
//  ����      �F
//
//  IDE       �FMicrosoft VisualC++ 2010
//
// 
//  �ύX����
//  �o�[�W�����@     ���t�@�@�@�@  �����@�@�@�@       ���l
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

