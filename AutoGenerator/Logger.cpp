////////////////////////////////////////////////////////////////////////////////
//
//  ファイル名：Logger.cpp
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
#include "Logger.h"
#include "DGT_SymbolDef.h"
#include <stdlib.h>

//char CLogger::m_cLogsFileName[512];           // Log file name
//char CLogger::m_cLogDirectory[512];          // Log directory
//std::queue<std::string> CLogger::m_qsBuffer;// Log Buffer

extern BOOL gbCancel;
extern HWND ghMainDlg;

CLogger* CLogger::m_Instance   = NULL;
CLogger::CLogger(void)
{
   // m_bfInstance = FALSE;
    memset( m_cLogDirectory,0x00, sizeof( m_cLogDirectory ));
    memset( m_cLogsFileName, 0x00, sizeof( m_cLogsFileName ));
    m_fFileHandler = NULL;
    while (!CLogger::m_qsBuffer.empty())
	{
		CLogger::m_qsBuffer.pop();	
	}
}


CLogger::~CLogger(void)
{
    m_fFileHandler = NULL;
    m_Instance     = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  GetInstance
//
//　表　　題　：  Get log instance
//
//　概　　要　：  Get log instance
//
//　戻　り　値：  
//
//　引　　数　： 
//                    
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/27   (TSDV) SonPT     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CLogger::GetInstance( CLogger* &lpOutLog )
{
    if( m_Instance == NULL )
    {
        m_Instance = new CLogger();
      //  m_bfInstance = TRUE;
    }
    else
    {
        // Do nothing
    }

    lpOutLog = m_Instance;
    return DGT_RET_OK;
}
/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  Log
//
//　表　　題　：  Push log content to queue
//
//　概　　要　：  Push log content to queue
//
//　戻　り　値：  
//
//　引　　数　： 
//                    
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/02/27   (TSDV) SonPT     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CLogger::Log( string sInContent, LPDWORD lpdwOutErrCode )
{
    // Local variable
    SCT_PROG_STATUS         sctProgStt;                  // Status info
    sctProgStt.Memset();
    // Check lpdwOutErrCode is NULL?
    if ( lpdwOutErrCode == NULL )
    {
        //*lpdwOutErrCode = DGT_ERR_CL_L_PARMS_NULL;
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Send message to Status dialog
    sctProgStt.nMask        = MASK_UPDATE_LOG ;
    sctProgStt.sLog         =  sInContent;
    ::SendMessageA( ghMainDlg, DGT_MSG, DGT_NOTIFY_UPDATE_STATUS, (LPARAM)&sctProgStt );

    CLogger::m_qsBuffer.push(sInContent);
    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関　数　名：  Write log to file
//
//　表　　題　：  Push log content to file
//
//　概　　要　：  Push log content to file
//
//　戻　り　値：  
//
//　引　　数　： 
//                    
//
//  バージョン　     日付          氏名              備考
//  DGT-00.00.00    2015/03/02   (TSDV) SonPT     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

BOOL CLogger::WriteLogToFile( LPDWORD lpdwOutErrCode, LPCSTR lpcLogDirectory )
{
    // Declare local variable
    std::string sLogContent = "";
    time_t tCurrentTime     = time( NULL );
	struct tm* lptmNow      = localtime( &tCurrentTime );

    // Check lpdwOutErrCode is NULL?
    if ( lpdwOutErrCode == NULL )
    {
        //*lpdwOutErrCode = DGT_ERR_CL_WLTF_PARMS_NULL;
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

	// Create log directory if not existed
	strcpy_s( m_cLogDirectory, lpcLogDirectory );
	CreateDirectory( m_cLogDirectory, NULL );

	// Get filename with format
	sprintf_s(CLogger::m_cLogsFileName, "%s\\%d%d%d.log", m_cLogDirectory, lptmNow->tm_year + 1900, lptmNow->tm_mon + 1, lptmNow->tm_mday);
	
	// Open log file. If not existed, create file and open file
	if ((CLogger::m_fFileHandler = fopen(CLogger::m_cLogsFileName, "a")) != NULL)
	{		
		//Write buffer to output stream
		while (!CLogger::m_qsBuffer.empty())
		{
			sLogContent = CLogger::m_qsBuffer.front();
            sLogContent += "\n";
			fputs(sLogContent.c_str(), CLogger::m_fFileHandler);
			CLogger::m_qsBuffer.pop();
				
		}

		// Push data from buffer to file and close file
		fflush(CLogger::m_fFileHandler);
		if (CLogger::m_fFileHandler != NULL)
		{
			fclose(CLogger::m_fFileHandler);
		}
	}
	else
	{
        //*lpdwOutErrCode = DGT_ERR_CL_WLTF_WRITE_FALSE;
        return DGT_RET_ERR;
	}
	
    return DGT_RET_OK;
}