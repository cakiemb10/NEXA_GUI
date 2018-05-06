#pragma once
////////////////////////////////////////////////////////////////////////////////
//
//  ファイル名：Area.h
//
//  概要　　　：This class used to store area information
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

#include "Item.h"

 struct SCT_AREA_INFO
{
    DWORD       dwWidth;                        // Area width
    DWORD       dwHeight;                       // Area height
    DWORD       dwCellWidth;                    // Cell width
    DWORD       dwCellHeight;                   // Cell height
    DWORD       dwMarginLeft;                   // Left margin
    DWORD       dwMarginTop;                    // Top margin
    DWORD       dwMarginRight;                  // Righ margin
    DWORD       dwMarginBottom;                 // Bottom margin
    string      sAreaJPName;                    // Area japannese name
    string      sBackground;                    // Background image
    string      sAreaEngName;                   // Area English name
    string      sAreaFuncName;                  // Area function name
    string      sAreaType;          // In Genereate Tool use string but dialog base use E_AREA_TYPE
// Start TrungLV 2015-09-07: Add new attribute
    string      sFunctionMapName;
// End TrungLV 2015-09-07
    void Memset()
    {
        dwWidth      = 0;                        // Area width
        dwHeight     = 0;                       // Area height
        dwCellWidth  = 0;                    // Cell width
        dwCellHeight = 0;                   // Cell height
        dwMarginLeft = 0;                   // Left margin
        dwMarginTop  = 0;                    // Top margin
        dwMarginRight = 0;                  // Righ margin
        dwMarginBottom = 0;                 // Bottom margin
        sAreaJPName    = "";                    // Area japannese name
        sBackground    = "";                    // Background image
        sAreaEngName   = "";                   // Area English name
        sAreaFuncName  = "";                  // Area function name
        sAreaType      = "";          // In Genereate Tool use  but dialog base use E_AREA_TYPE
// Start TrungLV 2015-09-07: Add new attribute
        sFunctionMapName = "";
// End TrungLV 2015-09-07
    }
} ;                                // Area struct

class CArea
{
public:
    CArea(void);
    ~CArea(void);

public:
    vector<CItem*>                   m_vItemList;            // List of items in an area
    SCT_AREA_INFO                   m_sctAreaInfo;          // Area info

    bool operator == ( string sInAreaFuncName )
    {
        return m_sctAreaInfo.sAreaFuncName == sInAreaFuncName;
    }
public:
    // Generate prototype
    BOOL GenPrototype( string &sOutSource, LPDWORD lpdwOutErrCode );
    // Generate implement source code
    BOOL GenSourceContent( string &sOutSource, LPDWORD lpdwOutErrCode );
    // Generate function pointer
    BOOL GenFuncPtr( string &sOutSource, LPDWORD lpdwOutErrCode );
};

