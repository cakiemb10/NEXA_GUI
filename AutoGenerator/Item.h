#pragma once
////////////////////////////////////////////////////////////////////////////////
//
//  ファイル名：Item.h
//
//  概要　　　：This class used for store all information of item
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
#include "Windows.h"
#include "DGT_SymbolDef.h"
#include "DGT_PvSymbolDef.h"
#include "DGT_PvErrCode.h"
#include "Utility.h"
#include "DataStructure.h"
using namespace std;

struct SCT_ITEM_INFO
{
    DWORD       dwType;                 // Item type ( button or label or edit )
    DWORD       dwCtrlID;               // Control ID
    string      sTagName;               // Tag name
    string      sText;                  // Text display
    DWORD       dwTop;
    DWORD       dwLeft;
    DWORD       dwWidth;
    DWORD       dwHeight;
    BOOL        bVisible;               // Visibility
    BOOL        bVisibilityHidden;
    BOOL        bEnable;                // Enable or disable
    string      sGaikan;                // Gaikan
    string      sFmt;                   // Format
    string      sTagID;                 // TagID
    string      sTagGroup;
    string      sAltTagID;              // Alternative Tag ID
    string      sInitClass;             // Initialize class
    string      sInitText;              // Init text
    string      sNullStrInitApp;
    string      sStatus;                // Status
    BOOL        bTextClickEvent;
    DWORD       dwClickBranchMode;
    string      sEvenFunctionName;
    string      sParaContainerTagID;
    string      sParaStartNo;
    string      sParaEndNo;
    string      sLimit;
    string      sClass;
    string      sValue;                 // 
    DWORD       dwFontSize;             // Font height
    float       fZoomSize;
    string      sMinLen;
    string      sMaxLen;
    string      sPageAtr;
    string      sBtn_Span_ImgClass;
    BOOL        bImageFirst;
    //string      sBtn_Span_Text;
    vector<SCT_SPAN> vSpanItem;
    //string        sBtn_Span_Text_Class;
    string        sBtn_Hr_Line_Class;
    string        sImgSrc;
    string         sAreaType; // In Generate Tool use string but in dialog base will use: AREA_ENUM eAreaType
                              // In Generate Tool will use sAreaType = "E_AREA_CENTERDISP" or "E_AREA_OPERATING"....
    BOOL        bParent;
    LONG        lLineHeight;
    DWORD       dwHrPosition;       // hr position: 0: None hr, 1: Bottom, 2: Mid
    BOOL        bOriginal;
    void Memset()
    {
        dwType     = 0;                 // Item type ( button or label or edit )
        dwCtrlID   = 0;               // Control ID
        sTagName   = "";               // Tag name
        sText      = "";                  // Text display
        dwTop      = 0;
        dwLeft     = 0;
        dwWidth    = 0;
        dwHeight   = 0;
        bVisible = FALSE;               // Visibility
        bVisibilityHidden = FALSE;
        bEnable  = FALSE;                // Enable or disable
        sGaikan    = "";                // Gaikan
        sFmt       = "";                   // Format
        sTagID     = "";                 // TagID
        sTagGroup  = "";
        sAltTagID  = "";              // Alternative Tag ID
        sInitClass = "";             // Initialize class
        sInitText  = "";              // Init text
        sNullStrInitApp = "";
        sStatus       = "";                // Status
        bTextClickEvent = FALSE;
        dwClickBranchMode = 0;
        sEvenFunctionName  = "";
        sParaContainerTagID = "";
        sParaStartNo  = "";
        sParaEndNo    = "";
        sLimit        = "";
        sClass    = "";
        sValue    = "";                 // 
        dwFontSize   = 0;             // Font height
        fZoomSize   = 0;
        sMinLen   = "";
        sMaxLen   = "";
        sPageAtr  = "";
        sBtn_Span_ImgClass    = "";
        bImageFirst = FALSE;
        vSpanItem.clear();
        //sBtn_Span_Text    = "";
        //sBtn_Span_Text_Class  = "";
        sBtn_Hr_Line_Class    = "";
        sImgSrc       = "";
        sAreaType     = ""; // In Generate Tool use  but in dialog base will use: AREA_ENUM eAreaType
                            // In Generate Tool will use sAreaType = "E_AREA_CENTERDISP" or "E_AREA_OPERATING"....
        bParent = FALSE;
        bVisibilityHidden = FALSE;
        lLineHeight   = -1;
        dwHrPosition  = 0;
        bOriginal     = FALSE;
    }
} ;   // Struct of item information

class CItem
{
public:
    CItem(void);
    ~CItem(void);

    SCT_ITEM_INFO       m_sctItem;          // Item info
    vector<CItem*>      m_vChildItem;       // Child item list
    // Start TrungLV 20150727: Do not use Control ID,
    //static DWORD        m_dwCtrlID;         // Control ID counter
    // End TrungLV 20150727: Do not use Control ID
public:

    // Generate statement of SetProperties function
    BOOL GenSetPropertiesFunc( string& sOutStatement, LPDWORD lpdwOutErrCode );
    void SetVisibilityChildren();
};

