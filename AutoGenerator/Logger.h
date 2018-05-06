#pragma once
////////////////////////////////////////////////////////////////////////////////
//
//  �t�@�C�����FLogger.h
//
//  �T�v�@�@�@�FThis class aim to write log when generating soure code
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

