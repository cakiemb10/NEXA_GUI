#pragma once
////////////////////////////////////////////////////////////////////////////////
//
//  ファイル名：ScriptReader.h
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
#include "Windows.h"
#include <vector>
#include <string>
#include <map>
#include "Area.h"
#include "ExcelReader.h"
#include "DataStructure.h"
#include "TestMode.h"

using namespace std;


class CScriptReader
{
public:
    CScriptReader(void);
    ~CScriptReader(void);

    // Read all script file
    BOOL ReadScript( LPDWORD lpdwOutErrCode);

    // Read Screen list
    BOOL ReadScreenList( LPDWORD lpdwOutErrCode );

    // Read each screen list
    BOOL ReadEachScreenFile( string sInFilePath, LPDWORD lpdwOutErrCode );

    // Read CSV List
    BOOL ReadCSVList( LPDWORD lpdwOutErrCode );

    // Read fmt_list.csv
    BOOL ReadFormatList( string sInFilePath, LPDWORD lpdwOutErrCode );

    // Read area_list.csv
    BOOL ReadAreaList( string sInFilePath, LPDWORD lpdwOutErrCode );

    // Read tag list
    BOOL ReadTagList( string sInFilePath, LPDWORD lpdwOutErrCode );

    // Read limit list
    BOOL ReadLimitList( string sInFilePath, LPDWORD lpdwOutErrCode );

    // Read init list
    BOOL ReadInitList( string sInFilePath, LPDWORD lpdwOutErrCode );

    // Read catalog information
    BOOL ReadCatalog( string sInAreaJPName, LPDWORD lpdwOutErrCode );

    // Search catalog information
    BOOL SearchCatalogInfo( 
                    string                sInArea,
                    string                sInAprName,
                    string                sInBehaviour,
                    SCT_CATALOG_CSV       &sctOutCatalog,
                    LPDWORD                lpdwOutErrCode );

    // Check the validation of input
    BOOL CheckInputValidation( LPDWORD lpdwOutErrCode );

    // Get "マスタ" sheet information
    BOOL GetMasterSheetInfo( LPDWORD lpdwOutErrCode );

    // Get "作成一覧" sheet information
    BOOL GetCreationSheetInfo( vector<string>  &vOutSheetName, LPDWORD lpdwOutErrCode );

    // Read each sheet
    BOOL ReadEachSheet( string sInSheetName, LPDWORD lpdwOutErrCode );

    // Seach background color
    BOOL    Search_MstBgColor( string sInBgColor, LONG &lOutIndex, LPDWORD lpdwOutErrCode );

    // Get header info
    BOOL    GetHeaderInfo(
                   Excel::_WorksheetPtr  lpInWorkSheet,
                   CArea*                &lpInArea,
                   vector<string>        &vOutHeaderInfo,
                   LPDWORD               dwlpOutErrCode );

    // Check the validation of item
    BOOL CheckItem( 
                    vector<string>      vInRowContent,
                    BOOL                &bInCheckResult, 
                    LPDWORD             lpdwOutErrCode );

    // Set class
    BOOL SetClass( 
                    DWORD               dwInParentMode, 
                    SCT_CATALOG_CSV     sctInCatalog,
                    SCT_ITEM_INFO       &sctOutItemInfo,
                    vector<string>      vInRowContent,
                    string              &sOutClass, 
                    string              &sOutStatus, 
                    string              &sOutInitClass, 
                    LPDWORD             lpdwOutErrCode);

    BOOL SearchInitstr( 
                    string               sInJPStype,
                    string               &sOutString, 
                    LPDWORD              lpdwOutErrCode );

    BOOL output_JS_tbl(
                    string               sInTagID,
                    string               sInAltTagID,
                    string               sInCurumu,
                    string               sInNo,
                    //string               sInDisp,
                    string               sInClassFmt,
                    string               sInFmtName,
                    SCT_ITEM_INFO        &sctItemInfo,
                    LPDWORD              lpdwOutErrCode );

    BOOL Get_MinMaxLen( 
                    string               sInTagID,
                    string               &sMinLen,
                    string               &sMaxLen,
                    string               sInFmt,
                    LPDWORD              lpdwOutErrCode);

    BOOL SearchTagStr( 
                    string                sInTagStr_JP,
                    SCT_TAG_CSV           &sctOutTag,
                    BOOL                  &bOutResult,
                    LPDWORD               lpdwOutErrCode );

    BOOL CreateButtonData( 
                    vector<string>         vInRowContent,
                   // string                 sInClass2,
                    SCT_CATALOG_CSV        sctInCatalog,
                    SCT_ITEM_INFO          sctInItemInfo,
                    LPDWORD                lpdwOutErrCode);

    BOOL  CreatePageArea(
                    Excel::_WorksheetPtr    lpInWorkSheet,
                    vector<string>          vInRowContent,
                    //string                  sInClass1,
                    //SCT_CATALOG_CSV         sctInCataLog,
                    SCT_ITEM_INFO           sctInItemInfo,
                    LPDWORD                 lpdwOutErrCode );

    BOOL  CreateDivData(
                    vector<string>          vInRowContent,
                    string                  sInClass1,
                    string                  sInClass2,
                    string                  sInText,
                    SCT_CATALOG_CSV         sctInCataLog,
                    SCT_ITEM_INFO           sctInItemInfo,
                    LPDWORD                 lpdwOutErrCode );

    //BOOL CreateTabAreaData(
    //                  vector<string>        vInRowContent,
    //                  string                sAreaJPName,
    //                  LPDWORD               lpdwOutErrCode );

    BOOL  CreateAData(
                    vector<string>          vInRowContent,
                    string                  sInClass1,
                    string                  sInClass2,
                    string                  sInText,
                    SCT_CATALOG_CSV         sctInCataLog,
                    SCT_ITEM_INFO           sctInItemInfo,
                    LPDWORD                 lpdwOutErrCode   );

    BOOL  CreateListItemData(
                    vector<string>          vInRowContent,
                    string                  sInClass1,
                    string                  sInText,
                    SCT_CATALOG_CSV         sctInCataLog,
                    SCT_ITEM_INFO           sctInItemInfo,
                    LPDWORD                 lpdwOutErrCode   );

    BOOL  CreateTimeData(
                    vector<string>          vInRowContent,
                    string                  sInClass1,
                    SCT_ITEM_INFO           sctInItemInfo,
                    SCT_CATALOG_CSV         sctInCatalog,
                    LPDWORD                 lpdwOutErrCode   );

    BOOL Set_ATag_OnMounDown(
                    vector<string>          vInRowContent, 
                 // string                  &sOutFunc, 
                    SCT_CATALOG_CSV         sctInCatalog, 
                    SCT_ITEM_INFO           &sctOutItemInfo,
                    LPDWORD                 lpdwOutErrCode );

    BOOL CreateTabAreaData(
                    vector<string>           vInRowContent, 
                   // vector<string>           vInHeaderInfo,
                    LPDWORD                  lpdwOutErrCode );

    BOOL Ekibtn_Data_mk(
                    string                   sInAreaJPName,
                   // vector<string>           vInHeaderRow,
                    vector<string>           vInRowContent,
                    Excel::_WorksheetPtr     lpInWorkSheet,
                    LPDWORD                  lpdwOutErrCode  );

    BOOL CreatePre( vector<string>           vInRowContent,
                   // SCT_CATALOG_CSV          sctInCatalog,
                    SCT_ITEM_INFO            sctItemInfor,
                    string                   sInDisp);
    BOOL CreatePassWord( vector<string> vInRowContent, SCT_CATALOG_CSV sctInCatalog );

    string Conv_StrNewLine( string sInStr );

    void CleanUp();

public:
    vector<CArea*>                          m_vAreaList;                      // Area list
    string                                  m_sSceenFolderPath;          // Screen specification folder path
    string                                  m_sAutoCSVFolder;            // Contain catalog files, tag_list,.. that automatically generated by other Tool
    string                                  m_sManualCSVFolder;        // Contain limit_list.csv, arealist.csv,.. that created by manual

private:
    CExcelReader                            m_cExcelReader;                // For manipulate with excel file
    vector<SCT_FORMAT_CSV>                  m_vFormatListCSV;             // Format list
    vector<SCT_AREA_CSV>                    m_vAreaListCSV;                // Area list
    map<string, vector<SCT_CATALOG_CSV>>    m_mCatalogList;                 // Catalog list

    vector<SCT_TAG_CSV>                     m_vTagListCSV;                  // Tag list
    vector<SCT_LIMIT_CSV>                   m_vLimitCSV;                     // Limit list
    vector<SCT_INIT_CSV>                    m_vInitListCSV;                   // Init list
    vector<SCT_BGCOLOR>                     m_vBgColor;                       // Background collect
    //vector<string>                          m_vFontList;                      // Font list

    vector<CItem*>                          m_vItemStack;                    // Item stack
    CArea*                                  m_lpCurrentArea;                // Current area pointer
    string                                  m_sContenaTagId;              // Contenna Tag ID

};

