////////////////////////////////////////////////////////////////////////////////
//
//  ファイル名：FileWriter.cpp
//
//  概要　　　：For write data to text file
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
#include "FileWriter.h"
#include "DGT_SymbolDef.h"
#include "DGT_PvErrCode.h"
#include "Logger.h"

CFileWriter::CFileWriter(void)
{
}


CFileWriter::~CFileWriter(void)
{
}

BOOL CFileWriter::WriteAt( string sInMark, string sInContent, LPDWORD lpdwOutErrCode )
{
    // Local variables
    char*               cSourceCode     = "";
    string              sSourceCode     = "";
    LONG                nMarkPos        = 0;
    LONGLONG            nLength         = 0;            // Length of file

    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Open file with reading mode
    this->open( m_sFilePath, ifstream::in );

    // Check file is openning
    if ( this->is_open())
    {
        // Do nothing
    }
    else
    {
        // File is not openning
        *lpdwOutErrCode = DGT_ERR_CFW_WA_WRITE_FAIL;
        return DGT_RET_ERR;
    }

    // Get file length
    this->seekg (0, this->end);
    nLength = this->tellg();
    this->seekg (0, this->beg);

    // Read overall file content to sSourceCode
    cSourceCode = new char[nLength];
    memset( cSourceCode, 0x00, nLength );
    this->read( cSourceCode, nLength );
    sSourceCode = string(cSourceCode);
    delete [] cSourceCode;
    // Get mark position
    nMarkPos = sSourceCode.find( sInMark );

    // Check finding result
    if ( nMarkPos != string::npos )
    {
        // Found mark
        sSourceCode.insert( nMarkPos, sInContent );

        // Close file
        this->close();
        // Open and clear content
        this->open( m_sFilePath, ios_base::trunc );
        // Close file
        this->close();

        // Open
        this->open( m_sFilePath, ios_base::out );

        // Write to file
        this->write( sSourceCode.c_str(), sSourceCode.length());
        // Close file
        this->close();
    }
    else
    {
        // Mark not found
        this->close();
        *lpdwOutErrCode = DGT_ERR_CFW_WA_MARK_NOT_FOUND;
        return DGT_RET_ERR;
    }

    return DGT_RET_OK;
}

// Write append to file
BOOL CFileWriter::WriteAppend( string sInContent, LPDWORD lpdwOutErrCode )
{
    CLogger*    lpLog      = NULL;
    DWORD       dwErrCode  = DGT_VALUE_ZERO_DWORD;
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

    this->open( m_sFilePath, ios::app );
    if ( this->is_open())
    {
        // Write to file
        this->write( sInContent.c_str(), sInContent.length());
        // Close file
        this->close();
    }
    else
    {
        if ( lpLog != NULL )
        {
            // Write Log
            lpLog->Log( "【エラー】：『"+ m_sFilePath +"』ファイルが開けません。" , &dwErrCode );
        }
        // File is not openning
        *lpdwOutErrCode = DGT_ERR_APPEND_ERR;
        return DGT_RET_ERR;
    }

    return DGT_RET_OK;
}

// Write at bookmark if content not exist
BOOL CFileWriter::WriteIfNotExist( string sInMark, string sInContent, LPDWORD lpdwOutErrCode )
{
    // Local variables
    char*               cSourceCode     = "";
    string              sSourceCode     = "";
    LONG                nMarkPos        = 0;
    LONG                nFoundPos       = 0;
    LONGLONG            nLength         = 0;            // Length of file
    CLogger*            lpLog = NULL;
    string              sLogContent     = "";
    DWORD               dwErrCode       = DGT_VALUE_ZERO_DWORD;
    CLogger::GetInstance( lpLog );
    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Open file with reading mode
    this->open( m_sFilePath, ifstream::in );

    // Check file is openning
    if ( this->is_open())
    {
        // Do nothing
    }
    else
    {
        if ( lpLog != NULL )
        {
            // Write Log
            lpLog->Log( "【エラー】：『"+ m_sFilePath +"』ファイルが開けません。" , &dwErrCode );
        }
        // File is not openning
        *lpdwOutErrCode = DGT_ERR_CFW_WA_WRITE_FAIL;
        return DGT_RET_ERR;
    }

    // Get file length
    this->seekg (0, this->end);
    nLength = this->tellg();
    this->seekg (0, this->beg);

    // Read overall file content to sSourceCode
    cSourceCode = new char[nLength];
    memset( cSourceCode, 0x00, nLength );
    this->read( cSourceCode, nLength );
    sSourceCode = string(cSourceCode);
    delete [] cSourceCode;

    // Convert to ANSI
    // Search content
    nFoundPos = sSourceCode.find( sInContent );
    if ( nFoundPos != string::npos )
    {
        // sInContent is existed in file. Close file and return
        this->close();
        //*lpdwOutErrCode =
        return DGT_RET_OK;
    }
    else
    {
        // Do nothing
    }

    // Get mark position
    nMarkPos = sSourceCode.find( sInMark );

    // Check finding result
    if ( nMarkPos != string::npos )
    {
        // Found mark
        sSourceCode.insert( nMarkPos, sInContent );

        // Close file
        this->close();
        // Open and clear content
        this->open( m_sFilePath, ios_base::trunc );
        // Close file
        this->close();

        // Open
        this->open( m_sFilePath, ios_base::out );

        // Write to file
        this->write( sSourceCode.c_str(), sSourceCode.length());
        // Close file
        this->close();
    }
    else
    {
        // Mark not found
        this->close();
        *lpdwOutErrCode = DGT_ERR_CFW_WA_MARK_NOT_FOUND;
        return DGT_RET_ERR;
    }

    return DGT_RET_OK;
}