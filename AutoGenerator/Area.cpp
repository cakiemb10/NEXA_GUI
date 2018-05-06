////////////////////////////////////////////////////////////////////////////////
//
//  ファイル名：Area.cpp
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

#include "Area.h"
#include <regex>

CArea::CArea(void)
{
    m_sctAreaInfo.Memset();
    m_vItemList.clear();
}


CArea::~CArea(void)
{
    DWORD dwCnt = DGT_VALUE_ZERO_DWORD;
    try
    {
        if ( m_vItemList.size() > 0 )
        {
            for ( dwCnt = 0; dwCnt < m_vItemList.size(); dwCnt++ )
            {
                delete m_vItemList[dwCnt];
            }
        m_vItemList.clear();
        }
    }
    catch( const exception& e )
    {
    }
}


// Generate source code
BOOL CArea::GenSourceContent( string &sOutSource, LPDWORD lpdwOutErrCode )
{
    // Initialize
    DWORD       dwCnt           = 0;                    // Counter in the loop
    string      sSetProperties  = "";                   // SetProperties statement
    string      sSubItemProp    = "";                   // Set properties of sub-item
    DWORD       dwErrCode       = DGT_VALUE_ZERO_DWORD; // Error code of internal function
    char        str[512]        = "";
    string      sFunctionMap    = "";
    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }
// Start TrungLV 2015-09-07: Don't process \\.
#if 0
    sFunctionMap  = m_sctAreaInfo.sAreaFuncName;
    sFunctionMap = regex_replace( sFunctionMap, regex("\\."), string("_" ));
#endif
// End TrungLV 2015-09-07
    // Header of function create area
    sOutSource = "VOID CAreaStore::Create_";
// Start TrungLV 2015-09-07: Use sFunctionMapName
#if 0
    sOutSource += sFunctionMap;
#endif
    sOutSource += m_sctAreaInfo.sFunctionMapName;
// End TrungLV 2015-09-07
    sOutSource += "_Area()\n";
    sOutSource += "{\n";

    // Function body=============================================

    // Initialize
    sOutSource += "    CArea* lpcArea = new CArea();\n";
    sOutSource += "    CItem* lpcItem = NULL;\n";
    sOutSource += "    vector<SCT_SPAN >   vSpanItem;\n";

    // Get area index
    sOutSource += (string)"    DWORD dwIdx    =  GetAreaIndex( " + m_sctAreaInfo.sAreaType + " );\n";
    // Set area type
    sOutSource += (string)"    lpcArea->m_sctAreaInfo.eAreaType = " + m_sctAreaInfo.sAreaType + ";\n";
    // Set area size
    sprintf( str, "%d", m_sctAreaInfo.dwWidth );
    sOutSource += (string)"    lpcArea->m_sctAreaInfo.dwWidth = (DWORD) " + str + ";\n";
    sprintf( str, "%d", m_sctAreaInfo.dwHeight );
    sOutSource += (string)"    lpcArea->m_sctAreaInfo.dwHeight = (DWORD)" + str + ";\n";

    // Set area margin
    sprintf( str, "%d", m_sctAreaInfo.dwMarginLeft );
    sOutSource += (string)"    lpcArea->m_sctAreaInfo.dwMarginLeft = (DWORD)" + str + ";\n";
    sprintf( str, "%d", m_sctAreaInfo.dwMarginTop );
    sOutSource += (string)"    lpcArea->m_sctAreaInfo.dwMarginTop = (DWORD)" + str + ";\n";
    sprintf( str, "%d", m_sctAreaInfo.dwMarginRight );
    sOutSource += (string)"    lpcArea->m_sctAreaInfo.dwMarginRight = (DWORD)" + str + ";\n";
    sprintf( str, "%d", m_sctAreaInfo.dwMarginBottom );
    sOutSource += (string)"    lpcArea->m_sctAreaInfo.dwMarginBottom = (DWORD)" + str + ";\n";

    // Set area name
    sOutSource += (string)"    lpcArea->m_sctAreaInfo.sAreaEngName = \"" + m_sctAreaInfo.sAreaEngName + "\";\n";
    sOutSource += (string)"    lpcArea->m_sctAreaInfo.sAreaJPName = \"" + m_sctAreaInfo.sAreaJPName + "\";\n";

    // Set background color
    sOutSource += (string)"    lpcArea->m_sctAreaInfo.sBackground = \"" + m_sctAreaInfo.sBackground + "\";\n";
// Start 2015-08-05: 
    // Create master item that fit to area. Use to display area background
    sprintf( str, "    lpcArea->m_cItemBkg.SetProperties((DWORD) 2 ,(DWORD) IDCTRL_BODY_AREA, \"\", \"\", (DWORD) 0 ,(DWORD) 0,(DWORD) %d,(DWORD) %d, 1, 0, 1, \"\", \"\", \"\", \"\", \"\", \"\", \"\", \"\", \"\", 0,(DWORD) 0, \"\", \"\", \"\", \"\", \"\", \"%s\", \"\", (DWORD)0, (float) 0, (long) -1, (long) -1, \"\", \"\", 0, vSpanItem, \"\", \"\", E_AREA_INVALID, 0, (long)-1, (DWORD) 0, FALSE );\n", /*m_sctAreaInfo.dwMarginLeft, m_sctAreaInfo.dwMarginTop,*/ m_sctAreaInfo.dwWidth, m_sctAreaInfo.dwHeight, m_sctAreaInfo.sBackground.c_str());
// End 2015-08-05: 
    sOutSource += str;

    // Set properties for all items
    for ( dwCnt = 0; dwCnt < m_vItemList.size(); dwCnt++ )
    {
        // Check item type
        switch ( m_vItemList[dwCnt]->m_sctItem.dwType )
        {
        case ITEM_TYPE_BUTTON:
            sOutSource += "    lpcItem = new CCustomBtn();\n";
            break;

        case ITEM_TYPE_LABEL:
            sOutSource += "    lpcItem = new CRichLabel();\n";
            break;

        default:
            return DGT_RET_ERR;
        }

        // Generate SetProperties statement
        m_vItemList[dwCnt]->GenSetPropertiesFunc( sSetProperties, &dwErrCode );
        sOutSource += sSetProperties;
        // Push item to list
        sOutSource += "    lpcArea->m_vItemList.push_back( lpcItem );\n";

        // Generate SetProperties function for sub-item( if any )
        for ( int i = 0; i < m_vItemList[dwCnt]->m_vChildItem.size(); i++ )
        {
            // Check item type
            switch ( m_vItemList[dwCnt]->m_vChildItem[i]->m_sctItem.dwType )
            {
            case ITEM_TYPE_BUTTON:
                sOutSource += "    lpcItem = new CCustomBtn();\n";
                break;

            case ITEM_TYPE_LABEL:
                sOutSource += "    lpcItem = new CRichLabel();\n";
                break;

            default:
                return DGT_RET_ERR;
            }

            m_vItemList[dwCnt]->m_vChildItem[i]->GenSetPropertiesFunc( sSubItemProp, &dwErrCode );
            sOutSource += sSubItemProp;
            sOutSource += "    lpcArea->m_vItemList.back()->m_vobjItems.push_back( lpcItem );\n";
            sOutSource += "    lpcItem->m_lpParent = lpcArea->m_vItemList.back();\n";
        }
    }

    // Set area position
    sOutSource += "    lpcArea->m_sctAreaInfo.pPosition = GetAreaPos( lpcArea->m_sctAreaInfo.eAreaType );\n";

    // Set parent
    if ( m_sctAreaInfo.sAreaEngName == "popup" )
    {
        sOutSource += "    lpcArea->m_lpcParent = GetActivePopup();\n";
    }
    else
    {
        sOutSource += "    lpcArea->m_lpcParent = m_lpParentWnd;\n";
    }

    // Call CreateArea() function
    sOutSource += "    lpcArea->CreateArea();\n";
    // Add area to list
    sOutSource += "    m_vCurAreas[dwIdx] = lpcArea;\n";

    // End function
    sOutSource += "}\n";

    return DGT_RET_OK;
}

// Generate prototype
BOOL CArea::GenPrototype( string &sOutSource, LPDWORD lpdwOutErrCode )
{
    string  sFunctionName = "";
    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }
// Start TrungLV 2015-09-07: Don't process \\.
#if 0
    sFunctionName = m_sctAreaInfo.sAreaFuncName;
    sFunctionName = regex_replace( sFunctionName, regex("\\."), string("_"));
#endif
// End TrungLV 2015-09-07
    // Function prototype
    sOutSource = "    VOID Create_";
// Start TrungLV 2015-09-07: Use sFunctionMapname
#if 0
    sOutSource += sFunctionName;
#endif
    sOutSource += m_sctAreaInfo.sFunctionMapName;
// End TrungLV 2015-09-07
    sOutSource += "_Area();\n";
    return DGT_RET_OK;
}

// Generate function pointer
BOOL CArea::GenFuncPtr( string &sOutSource, LPDWORD lpdwOutErrCode )
{
    // Initialize
    char            cStatement[512] = {0};              // Statement string
    string          sFunctionMap    = "";
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }
    
    // Build statement
// Start TrungLV 2015-09-07: Don't need to process only with \\.
#if 0
    sFunctionMap  = m_sctAreaInfo.sAreaFuncName;
    sFunctionMap = regex_replace( sFunctionMap, regex("\\."), string("_" ));
    sprintf( cStatement, "    m_mapFn[\"%s\"] = &CAreaStore::Create_%s_Area;\n", m_sctAreaInfo.sAreaFuncName.c_str(), sFunctionMap.c_str());
#endif
// End TrungLV 2015-09-07
// Start TrungLV 2015-09-07: Use m_sctAreaInfo.sFunctionMapName
    sprintf( cStatement, "    m_mapFn[\"%s\"] = &CAreaStore::Create_%s_Area;\n", m_sctAreaInfo.sAreaFuncName.c_str(), m_sctAreaInfo.sFunctionMapName.c_str());
// End TrungLV 2015-09-07: Use m_sctAreaInfo.sFunctionMapName
    sOutSource = cStatement;
    return DGT_RET_OK;
}
