////////////////////////////////////////////////////////////////////////////////
//
//  ファイル名：Item.cpp
//
//  概要　　　：This class used read open,close and get information inexcel file
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
#include "Utility.h"
#include <regex>

// Start TrungLV 20150727: Do not use Control ID
//DWORD CItem::m_dwCtrlID = START_CTRL_ID;        // Start item control ID by 1050
// End TrungLV 20150727: Do not use Control ID
CItem::CItem(void)
{
    m_sctItem.Memset();
    m_vChildItem.clear();
}


CItem::~CItem(void)
{
    DWORD dwCnt = DGT_VALUE_ZERO_DWORD;
    try
    {
        for ( dwCnt = 0; dwCnt < m_vChildItem.size(); dwCnt++ )
        {
            delete m_vChildItem[dwCnt];
        }
        m_vChildItem.clear();
    }
    catch( const exception& e )
    {
    }

}

BOOL CItem::GenSetPropertiesFunc( string& sOutStatement, LPDWORD lpdwOutErrCode )
{
    // Initialize
    BOOL            bRet                = FALSE;
    char            sProperties[2048]   = "";                   // Properties
    string          sSubItemProp        = "";                   // Sub-item properties
    string          sEndLine            = "";                   // Line feed character
    DWORD           dwErrCode           = DGT_VALUE_ZERO_DWORD; // Error code
    LONG            nMinLength          = 0;
    LONG            nMaxLength          = 0;

    // Check parameter
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }
    sOutStatement = "";
    // Make span item vector
    for ( DWORD dwSub = 0; dwSub < m_sctItem.vSpanItem.size(); dwSub++ )
    {
        sOutStatement += "    vSpanItem.push_back( SCT_SPAN( \"" + m_sctItem.vSpanItem[dwSub].sSpanText + "\",\"" + m_sctItem.vSpanItem[dwSub].sSpanClass + "\"));\n";
    }
    // Increase control ID by 1 to avoid overlap
    // Start TrungLV 20150727: Do not use Control ID
    //m_dwCtrlID++;
    // End TrungLV 20150727: Do not use Control ID
    // Now don't separate control ID for each item
    // m_sctItem.dwCtrlID = m_dwCtrlID;
    m_sctItem.dwCtrlID = 0;

    sOutStatement += "    lpcItem->SetProperties( ";

    sEndLine = char( 13 );
    // Replace endline character
    ReplaceChar13( m_sctItem.sFmt );
    ReplaceChar13( m_sctItem.sLimit );
    string sTemp = "";
    // Convert end line character
    try
    {
        if ( m_sctItem.sText != "" )
        {
            sTemp = m_sctItem.sText;
            m_sctItem.sText = std::regex_replace( sTemp, std::regex("\n"), string("\\n") );
        }
        if ( m_sctItem.sValue != "" )
        {
            sTemp = m_sctItem.sValue;
            m_sctItem.sValue = std::regex_replace( sTemp, std::regex("\n"), string("\\n") );
        }
    }
    catch( const exception& e )
    {
        // Do nothing
    }

    // Get min length
    if ( CheckNashiMode( m_sctItem.sMinLen ))
    {
        nMinLength = -1;
    }
    else if ( m_sctItem.sMinLen == "◆" )
    {
        nMinLength = -2;
    }
    else
    {
        ConvFullHalNumberFunc( m_sctItem.sMinLen , true, m_sctItem.sMinLen );
        nMinLength = atoi( m_sctItem.sMinLen.c_str());
    }

    // Get max length
    if ( CheckNashiMode( m_sctItem.sMaxLen ))
    {
        nMaxLength = -1;
    }
    else if ( m_sctItem.sMaxLen == "◆" )
    {
        nMaxLength = -2;
    }
    else
    {
        nMaxLength = atoi( m_sctItem.sMaxLen.c_str());
    }

// Start TrungLV 20150727: Do not use Control ID
    // Format string
    sprintf( 
        sProperties,
        "(DWORD)%d, IDCTRL_ITEM, \"%s\", \"%s\", (DWORD) %d, (DWORD) %d, (DWORD) %d, (DWORD) %d, %d, %d, %d,\n"  // 1- 11
        "    \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\",\n" // 12-20
        "    %d, (DWORD)%d, \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\",\n" // 21 - 29
        "    (DWORD) %d, (float) %.2ff,(long) %d, (long) %d, \"%s\", \"%s\", %d, vSpanItem , \"%s\", \"%s\", %s, %d, (long) %d, (DWORD)%d, %d",  // 30-45
// End TrungLV 20150727: Do not use Control ID
        m_sctItem.dwType,                                   // Item type. Button: 1, Label: 2
        //m_sctItem.dwCtrlID,                                 // Control ID. Now don't care to control ID
        m_sctItem.sTagName.c_str(),                         // Tag name
        m_sctItem.sText.c_str(),                            // Display text
        m_sctItem.dwLeft, 
        m_sctItem.dwTop, 
        m_sctItem.dwWidth, 
        m_sctItem.dwHeight,
        m_sctItem.bVisible,
        m_sctItem.bVisibilityHidden,
        m_sctItem.bEnable,
        m_sctItem.sGaikan.c_str(),
        m_sctItem.sFmt.c_str(),
        m_sctItem.sTagID.c_str(),
        m_sctItem.sTagGroup.c_str(),
        m_sctItem.sAltTagID.c_str(),
        m_sctItem.sInitClass.c_str(),
        m_sctItem.sInitText.c_str(),
        m_sctItem.sNullStrInitApp.c_str(),
        m_sctItem.sStatus.c_str(),
        m_sctItem.bTextClickEvent,
        m_sctItem.dwClickBranchMode,
        m_sctItem.sEvenFunctionName.c_str(),
        m_sctItem.sParaContainerTagID.c_str(),
        m_sctItem.sParaStartNo.c_str(),
        m_sctItem.sParaEndNo.c_str(),
        m_sctItem.sLimit.c_str(),
        m_sctItem.sClass.c_str(),
        m_sctItem.sValue.c_str(),
        m_sctItem.dwFontSize,
        m_sctItem.fZoomSize,
        nMinLength,
        nMaxLength,
        m_sctItem.sPageAtr.c_str(),
        m_sctItem.sBtn_Span_ImgClass.c_str(),
        m_sctItem.bImageFirst,
        //m_sctItem.sBtn_Span_Text.c_str(),
        //m_sctItem.sBtn_Span_Text_Class.c_str(),
        m_sctItem.sBtn_Hr_Line_Class.c_str(),
        m_sctItem.sImgSrc.c_str(),
        m_sctItem.sAreaType.c_str(),
        m_sctItem.bParent,
        m_sctItem.lLineHeight,
        m_sctItem.dwHrPosition,
        m_sctItem.bOriginal);

    sOutStatement += sProperties;
    sOutStatement += " );\n";
    if ( m_sctItem.vSpanItem.size() > 0 )
    {
        sOutStatement += "    vSpanItem.clear(); \n ";
    }
    return DGT_RET_OK;
}

void CItem::SetVisibilityChildren()
{
    DWORD dwCnt = 0;
    for ( dwCnt = 0; dwCnt < m_vChildItem.size(); dwCnt++ )
    {
        m_vChildItem[dwCnt]->m_sctItem.bVisible = m_sctItem.bVisible;
    }
}