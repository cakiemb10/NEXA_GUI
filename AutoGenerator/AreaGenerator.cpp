////////////////////////////////////////////////////////////////////////////////
//
//  ファイル名：AreaGenerator.cpp
//
//  概要　　　：This class aim to generate neccessary content for creating area on dialog base such as:
//                     declare header function, add macro to soure file, make content for CreateAreaXXX() function,..
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

#include "AreaGenerator.h"


CAreaGenerator::CAreaGenerator( CArea* lpcInArea )
{
    m_lpcArea = lpcInArea;
}


CAreaGenerator::~CAreaGenerator(void)
{
    //// Free memory
    //if ( m_lpcArea != NULL )
    //{
    //    delete m_lpcArea;
    //}
    //else
    //{
    //    // Do nothing
    //}
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関  数  名：  CreateCppFile
//
//　表    題  ：  Create cpp file of area. Add common declare
//
//　概    要  ：  Create cpp file of area. Add common declare
//
//　戻  り  値：  DGT_RET_OK    正常終了
//　          ：  DGT_RET_ERR   異常終了
//
//　引　　数　：  LPDWORD              lpdwOutErrCode            (O)     Error code pointer
//
//  バージョン　     日付                氏名                     備考
//  DGT-01.00.00    2015/07/15          (TSDV) ThietNP          Creat New
//
//　(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CAreaGenerator::CreateCppFile( LPDWORD lpdwOutErrCode )
{
    // Initialzie
    BOOL            bRet        = FALSE;                    // Return value
    DWORD           dwErrCode   = DGT_VALUE_ZERO_DWORD;     // Error code
    string          sFilePath   = m_sOutPath + AREA_STORE_FOLDER + m_lpcArea->m_sctAreaInfo.sAreaFuncName + ".cpp";
    m_cFileWriter.SetFilePath( sFilePath );
    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Create empty file
    m_cFileWriter.open( sFilePath, ios::out | ios::trunc );
    m_cFileWriter.close();
    // Write common declare
// Start TrungLV 2015-08-07	: Add #pragma once
    string sDeclare = 
        "#pragma once \n"
        "#include \"stdafx.h\"\n"
        "#include \"GUIDAreaStore.h\"\n"
        "using namespace std;\n\n";
// End TrungLV 2015-08-07		
    bRet = m_cFileWriter.WriteAppend( sDeclare, &dwErrCode );
    if ( bRet == TRUE )
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
//　関  数  名：  WriteAll
//
//　表    題  ：  Generate all components of area
//
//　概    要  ：  Generate all components of area
//
//　戻  り  値：  DGT_RET_OK    正常終了
//　          ：  DGT_RET_ERR   異常終了
//
//　引　　数　：  LPDWORD              lpdwOutErrCode            (O)     Error code pointer
//
//  バージョン　     日付                氏名                     備考
//  DGT-01.00.00    2015/07/15          (TSDV) ThietNP          Creat New
//
//　(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CAreaGenerator::WriteAll( LPDWORD lpdwOutErrCode )
{
    // Initialzie
    BOOL            bRet        = FALSE;                    // Return value
    DWORD           dwErrCode   = DGT_VALUE_ZERO_DWORD;     // Error code

    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Write to header file
    bRet = WriteHeaderFile( &dwErrCode );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    // Create cpp file
    bRet = CreateCppFile( &dwErrCode );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    // Write to source file
    bRet = WriteSourceFile( &dwErrCode );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    // Write to function map file
    bRet = WriteFunctionMap( &dwErrCode );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    // Write to project file
    bRet = WriteVcxProjFile( &dwErrCode );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関  数  名：  WriteHeaderFile
//
//　表    題  ：  Write to area header file
//
//　概    要  ：  Write to area header file
//
//　戻  り  値：  DGT_RET_OK    正常終了
//　          ：  DGT_RET_ERR   異常終了
//
//　引　　数　：  LPDWORD              lpdwOutErrCode            (O)     Error code pointer
//
//  バージョン　     日付                氏名                     備考
//  DGT-01.00.00    2015/07/15          (TSDV) ThietNP          Creat New
//
//　(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CAreaGenerator::WriteHeaderFile( LPDWORD lpdwOutErrCode )
{
    // Initialzie
    BOOL            bRet                = FALSE;                    // Return value
    DWORD           dwErrCode           = DGT_VALUE_ZERO_DWORD;     // Error code
    string          sSourceFilePath     = "";                       // Header file path
    string          sSourceCode         = "";                       // Source code to be write

    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Get header file path
    sSourceFilePath = m_sOutPath;
    sSourceFilePath += MAIN_DLG_HEADER_FILE;
    m_cFileWriter.SetFilePath( sSourceFilePath );

    // Generate prototype
    bRet = m_lpcArea->GenPrototype( sSourceCode, &dwErrCode );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    // Write to file
    bRet = m_cFileWriter.WriteIfNotExist( DGT_CFW_WA_PROTOTYPE, sSourceCode, &dwErrCode );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関  数  名：  WriteSourceFile
//
//　表    題  ：  Write to area cpp file
//
//　概    要  ：  Write to area cpp file
//
//　戻  り  値：  DGT_RET_OK    正常終了
//　          ：  DGT_RET_ERR   異常終了
//
//　引　　数　：  LPDWORD              lpdwOutErrCode            (O)     Error code pointer
//
//  バージョン　     日付                氏名                     備考
//  DGT-01.00.00    2015/07/15          (TSDV) ThietNP          Creat New
//
//　(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CAreaGenerator::WriteSourceFile( LPDWORD lpdwOutErrCode )
{
    // Initialzie
    BOOL            bRet                = FALSE;                    // Return value
    DWORD           dwErrCode           = DGT_VALUE_ZERO_DWORD;     // Error code
    string          sSourceFilePath     = "";                       // Source file path
    string          sSourceCode         = "";                       // Source code to be write

    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Get source file path
    sSourceFilePath = m_sOutPath + AREA_STORE_FOLDER + m_lpcArea->m_sctAreaInfo.sAreaFuncName + ".cpp";
    m_cFileWriter.SetFilePath( sSourceFilePath );

    // Generate area creation source code
    bRet = m_lpcArea->GenSourceContent( sSourceCode, &dwErrCode );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    // Write to file
    bRet = m_cFileWriter.WriteAppend( sSourceCode, &dwErrCode );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    return DGT_RET_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関  数  名：  WriteFunctionMap
//
//　表    題  ：  Write to function map file
//
//　概    要  ：  Write to function map file
//
//　戻  り  値：  DGT_RET_OK    正常終了
//　          ：  DGT_RET_ERR   異常終了
//
//　引　　数　：  LPDWORD              lpdwOutErrCode            (O)     Error code pointer
//
//  バージョン　     日付                氏名                     備考
//  DGT-01.00.00    2015/07/15          (TSDV) ThietNP          Creat New
//
//　(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CAreaGenerator::WriteFunctionMap( LPDWORD lpdwOutErrCode )
{
    // Initialzie
    BOOL            bRet                = FALSE;                    // Return value
    DWORD           dwErrCode           = DGT_VALUE_ZERO_DWORD;     // Error code
    string          sSourceFilePath     = "";                       // Source file path
    string          sSourceCode         = "";                       // Source code to be write

    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Get source file path
    sSourceFilePath = m_sOutPath + FUNCTION_MAP_FILE;
    m_cFileWriter.SetFilePath( sSourceFilePath );

    // Generate function mapping
    bRet = m_lpcArea->GenFuncPtr( sSourceCode, &dwErrCode );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    // Write to file
    bRet = m_cFileWriter.WriteIfNotExist( DGT_CFW_WA_FUNC_MAP, sSourceCode, &dwErrCode );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//　関  数  名：  WriteVcxProjFile
//
//　表    題  ：  Write to .vcxproj file
//
//　概    要  ：  Write to .vcxproj file
//
//　戻  り  値：  DGT_RET_OK    正常終了
//　          ：  DGT_RET_ERR   異常終了
//
//　引　　数　：  LPDWORD              lpdwOutErrCode            (O)     Error code pointer
//
//  バージョン　     日付                氏名                     備考
//  DGT-01.00.00    2015/07/15          (TSDV) ThietNP          Creat New
//
//　(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CAreaGenerator::WriteVcxProjFile( LPDWORD lpdwOutErrCode )
{
    BOOL            bRet                = FALSE;                    // Return value
    DWORD           dwErrCode           = DGT_VALUE_ZERO_DWORD;     // Error code
    string          sFilePath           = "";                       // Project file path
    string          sScriptCode         = "";                       // Script code to be write

    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Get source file path
    sFilePath = m_sOutPath + VCXPROJ_FILE;
    m_cFileWriter.SetFilePath( sFilePath );

    // Generate script code
    sScriptCode = "<ClCompile Include=\"";
    sScriptCode += m_lpcArea->m_sctAreaInfo.sAreaFuncName + ".cpp";
    sScriptCode += "\">\n      <Filter>Source Files</Filter>\n    </ClCompile>";

    // Write to file if not exist
    bRet = m_cFileWriter.WriteIfNotExist( DGT_CFW_WA_VCXPROJ, sScriptCode, &dwErrCode );
    if ( bRet == FALSE )
    {
        *lpdwOutErrCode = dwErrCode;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    return DGT_RET_OK;
}
