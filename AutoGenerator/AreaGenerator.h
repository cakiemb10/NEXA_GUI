#pragma once
////////////////////////////////////////////////////////////////////////////////
//
//  ファイル名：AreaGenerator.h
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

