////////////////////////////////////////////////////////////////////////////////
//
//  �t�@�C�����FAreaGenerator.cpp
//
//  �T�v�@�@�@�FThis class aim to generate neccessary content for creating area on dialog base such as:
//                     declare header function, add macro to soure file, make content for CreateAreaXXX() function,..
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
//�@��  ��  ���F  CreateCppFile
//
//�@�\    ��  �F  Create cpp file of area. Add common declare
//
//�@�T    �v  �F  Create cpp file of area. Add common declare
//
//�@��  ��  �l�F  DGT_RET_OK    ����I��
//�@          �F  DGT_RET_ERR   �ُ�I��
//
//�@���@�@���@�F  LPDWORD              lpdwOutErrCode            (O)     Error code pointer
//
//  �o�[�W�����@     ���t                ����                     ���l
//  DGT-01.00.00    2015/07/15          (TSDV) ThietNP          Creat New
//
//�@(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
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
//�@��  ��  ���F  WriteAll
//
//�@�\    ��  �F  Generate all components of area
//
//�@�T    �v  �F  Generate all components of area
//
//�@��  ��  �l�F  DGT_RET_OK    ����I��
//�@          �F  DGT_RET_ERR   �ُ�I��
//
//�@���@�@���@�F  LPDWORD              lpdwOutErrCode            (O)     Error code pointer
//
//  �o�[�W�����@     ���t                ����                     ���l
//  DGT-01.00.00    2015/07/15          (TSDV) ThietNP          Creat New
//
//�@(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
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
//�@��  ��  ���F  WriteHeaderFile
//
//�@�\    ��  �F  Write to area header file
//
//�@�T    �v  �F  Write to area header file
//
//�@��  ��  �l�F  DGT_RET_OK    ����I��
//�@          �F  DGT_RET_ERR   �ُ�I��
//
//�@���@�@���@�F  LPDWORD              lpdwOutErrCode            (O)     Error code pointer
//
//  �o�[�W�����@     ���t                ����                     ���l
//  DGT-01.00.00    2015/07/15          (TSDV) ThietNP          Creat New
//
//�@(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
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
//�@��  ��  ���F  WriteSourceFile
//
//�@�\    ��  �F  Write to area cpp file
//
//�@�T    �v  �F  Write to area cpp file
//
//�@��  ��  �l�F  DGT_RET_OK    ����I��
//�@          �F  DGT_RET_ERR   �ُ�I��
//
//�@���@�@���@�F  LPDWORD              lpdwOutErrCode            (O)     Error code pointer
//
//  �o�[�W�����@     ���t                ����                     ���l
//  DGT-01.00.00    2015/07/15          (TSDV) ThietNP          Creat New
//
//�@(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
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
//�@��  ��  ���F  WriteFunctionMap
//
//�@�\    ��  �F  Write to function map file
//
//�@�T    �v  �F  Write to function map file
//
//�@��  ��  �l�F  DGT_RET_OK    ����I��
//�@          �F  DGT_RET_ERR   �ُ�I��
//
//�@���@�@���@�F  LPDWORD              lpdwOutErrCode            (O)     Error code pointer
//
//  �o�[�W�����@     ���t                ����                     ���l
//  DGT-01.00.00    2015/07/15          (TSDV) ThietNP          Creat New
//
//�@(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
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
//�@��  ��  ���F  WriteVcxProjFile
//
//�@�\    ��  �F  Write to .vcxproj file
//
//�@�T    �v  �F  Write to .vcxproj file
//
//�@��  ��  �l�F  DGT_RET_OK    ����I��
//�@          �F  DGT_RET_ERR   �ُ�I��
//
//�@���@�@���@�F  LPDWORD              lpdwOutErrCode            (O)     Error code pointer
//
//  �o�[�W�����@     ���t                ����                     ���l
//  DGT-01.00.00    2015/07/15          (TSDV) ThietNP          Creat New
//
//�@(C)Copyright TOSHIBA CORPORATION 2014B. All rights reserved.
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
