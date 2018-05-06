#pragma once
////////////////////////////////////////////////////////////////////////////////
//
//  ファイル名：Utility.h
//
//  概要　　　：Contain all utility functions such as CheckFilePath, IsNumeric
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
#pragma once
#include "Windows.h"
#include <string>
#include <vector>
#include "DGT_PvSymbolDef.h"
#include "DGT_SymbolDef.h"
using namespace std;

struct SCT_PROG_STATUS
{
    DWORD       dwPercent;          // Complete percent
    UINT        nMask;              // Mask indicate what field will be update
    string      sStatus;            // Status
    string      sLog;               // Log content

    void Memset()
    {
        nMask     = 0;
        dwPercent = 0;
        sStatus   = "";
        sLog      = "";
    }
};

typedef SCT_PROG_STATUS* LPSCT_PROG_STATUS;


//#ifndef TAG_NAME_LIST_DEF
//#define TAG_NAME_LIST_DEF
//char* TAG_NAME_LIST[12] =  { "button", "div", "a", "span", "image", "ul", "li", "time", SEINENGAPPI, CONTENA, MSGAREA, IMG_STRETCH };
//#endif

// Check the validation of file path
BOOL CheckFilePath( 
                const string &sInFilePath,
                LPWORD lpwOutCheckResult,
                LPDWORD lpdwOutErrCode );

// Check the validation of folder path
BOOL CheckFolderPath( 
                const string &sInFolderPath, 
                LPWORD lpwOutCheckResult,
                LPDWORD lpdwOutErrCode);

// Split string
vector<string> SplitString( string sInString, const string &sInDelimiter);


// Copy all file/folder to an another location
BOOL CopyDirTo( const string& source_folder, const string& target_folder );

// Get all file in folder
BOOL  GetAllFileInFolder( string sInFolderPath, const vector<string> &vInExtension, vector<string> &vListOutFilePath , BOOL bOnlyFileName );

BOOL IsStringNumber( const string &sNumString );

LONG SuchiCheck(const string &checkstr);

//BOOL SetIchiInfo( 
//            //const string &sInAreaJP, 
//            const string &sInIchi,
//            vector<DWORD> &vOutIchi, 
//            DWORD h_grid_size,
//            DWORD w_grid_size, 
//            DWORD dwInMarginTop, 
//            DWORD dwInMarginLeft );

LONG SerchTagName_index( const string &sTagName);

BOOL CheckNashiMode( const string &sTarget);

string GetBtnValue( const vector<string>& row );

string GetEkiBtn(const vector<string>& row);

VOID ReplaceStr( string& str, const string &sInOldStr, const string &sInNewStr );
VOID ReplaceChar13( string& str );
wstring StringToWChar( const string &sInString );
LONG ConvFullHalNumberFunc( const string &sInConvData, BOOL bInHalfFlg, string &sOutConvData );
string WCharToString( const wstring &sInWideString );
void DeleteAllFiles( string sInFolderPath);
string Utf8toAnsi( const char *cInUtf8, DWORD dwInlen );
// Start TrungLV 2015-09-07: Add function to process function name
void ProcessFunctionName( string &sFuncName );
// End TrungLV 2015-09-07
