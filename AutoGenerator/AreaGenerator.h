#pragma once
////////////////////////////////////////////////////////////////////////////////
//
//  �t�@�C�����FAreaGenerator.h
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
#include "Area.h"
#include "FileWriter.h"

class CAreaGenerator
{
public:
    CAreaGenerator( CArea* );
    ~CAreaGenerator(void);

    VOID SetOutPath( string sInPath )
    {
        m_sOutPath = sInPath;
    }

    CArea*              m_lpcArea;                      // Area info
protected:
    CFileWriter         m_cFileWriter;                  // File writer object
    string              m_sOutPath;                     // Output folder path

public:
    // Methods
    BOOL CreateCppFile( LPDWORD lpdwOutErrCode );       // Create source file for Area
    BOOL WriteAll( LPDWORD lpdwOutErrCode );            // Write all
    BOOL WriteHeaderFile( LPDWORD lpdwOutErrCode );     // Write to header file
    BOOL WriteSourceFile( LPDWORD lpdwOutErrCode );     // Write to source file
    BOOL WriteFunctionMap( LPDWORD lpdwOutErrCode );    // Write to function map file
    BOOL WriteVcxProjFile( LPDWORD lpdwOutErrCode );    // Write to .vcxproj file
};

