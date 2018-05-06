#pragma once
////////////////////////////////////////////////////////////////////////////////
//
//  ファイル名：PJGenerator.h
//
//  概要　　　：This class aim to generate dialog base source code. Include header file, cpp file, and resource file.
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

#include <Windows.h>
#include "Area.h"
#include "DGT_PvErrCode.h"
#include "DGT_SymbolDef.h"
#include "AreaGenerator.h"

class CPJGenerator
{
public:
    CPJGenerator(void);
    ~CPJGenerator(void);

    VOID SetOutFolder( string sInPath )
    {
        m_sOutFolderPath = sInPath;
    }

    VOID SetAreaList( vector<CArea*> vInAreaList );

    BOOL GenerateAll( LPDWORD lpdwOutErrCode );
    BOOL GenerateTemplateProject( LPDWORD lpdwOutErrCode );
    BOOL GenerateAreas( LPDWORD lpdwOutErrCode );
    void CleanUp();
    BOOL IsProjectExist( string sProjectFolder );
    BOOL UpdateProjectFile( const string& TemplateFolder, const string& ProjectFolder , LPDWORD lpdwOutErrCode );
private:
    string                      m_sOutFolderPath;               // Output folder path
    vector<CAreaGenerator*>     m_vAreaGenList;                 // Area generator list
};

