#pragma once
////////////////////////////////////////////////////////////////////////////////
//
//  ファイル名：Logger.h
//
//  概要　　　：This class aim to write log when generating soure code
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
//#include "Windows.h"
#include <string>
#include <queue>
#include <ctime>

#include "Utility.h"
#include "DGT_SymbolDef.h"
#include "DGT_PvSymbolDef.h"
#include "DGT_PvErrCode.h"

using namespace std;

class CLogger
{
public:
    CLogger(void);
    ~CLogger(void);
    
private:
    static CLogger*  m_Instance;
    //static BOOL      m_bfInstance;
    char      m_cLogsFileName[512];
    char      m_cLogDirectory[512];
    FILE*     m_fFileHandler;
    std::queue<std::string> m_qsBuffer;	


public:

    //-----------------------------------------------------
    //Get instance
    static BOOL GetInstance( CLogger* &lpOutLog );

    // Write log content to buffer
     BOOL  Log( string sInContent, LPDWORD lpdwOutErrCode);

    // Write to log file
    BOOL WriteLogToFile(LPDWORD lpdwOutErrCode, LPCSTR lpcLogDirectory = "log" );


};

