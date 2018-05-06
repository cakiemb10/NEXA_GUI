////////////////////////////////////////////////////////////////////////////////
//
//  ÉtÉ@ÉCÉãñºÅFDataStructure.h
//
//  äTóvÅ@Å@Å@ÅFContain data structure
//
//  çÏê¨é“Å@Å@ÅF(TSDV) TrungLV
//
//  èäëÆ      ÅF
//
//  IDE       ÅFMicrosoft VisualC++ 2010
//
// 
//  ïœçXóöó
//  ÉoÅ[ÉWÉáÉìÅ@     ì˙ïtÅ@Å@Å@Å@  éÅñºÅ@Å@Å@Å@       îıçl
//  DGT-00.00.00    2015/02/26   (TSDV) TrungLV     Create New
//

//
////////////////////////////////////////////////////////////////////////////////
// $Header: $
#pragma once
#include "DGT_SymbolDef.h"
struct SCT_SPAN
{
    string sSpanText;
    string sSpanClass;
    SCT_SPAN( string sInSpanText, string sInSpanClass )
    {
        sSpanText   = sInSpanText;
        sSpanClass  = sInSpanClass;
    }
    SCT_SPAN()
    {
        sSpanText   = "";
        sSpanClass  = "";
    }
    void Memset()
    {
        sSpanText = "";
        sSpanClass = "";
    }

};
struct SCT_AREA_CSV
{
    string      sArea_JP;
    string      sArea_EI;
    string      sArea_Dir;
    string      sArea_Catalog;
    SCT_AREA_CSV( string sInArea_JP, string  sInArea_EI , string  sInArea_Dir , string sInArea_Catalog )
    {
        sArea_JP         = sInArea_JP;
        sArea_EI         = sInArea_EI;
        sArea_Dir        = sInArea_Dir;
        sArea_Catalog = sInArea_Catalog;
    }

    bool operator == ( string  sInArea_JP )
    {
        return ( sArea_JP == sInArea_JP );
    }
};


struct SCT_CATALOG_CSV
{
    string      sGaikan;
    string      sDosa;
    string      sParameter;
    string      sTagName;
    string      sGaikanGrpName;
    string      sSetClassName;
    string      sClassSetTag;
    string      sAttribute;

    SCT_CATALOG_CSV()
    {
    }

    SCT_CATALOG_CSV(  
                                  string  sInGaikan,
                                  string  sInDosa,
                                  string  sInParameter,
                                  string  sInTagName,
                                  string  sInGaikanGrpName,
                                  string  sInSetClassName,
                                  string  sInClassSetTag,
                                  string  sInAttribute )
    {
        sGaikan                = sInGaikan;
        sDosa                  = sInDosa;
        sParameter          = sInParameter;
        sTagName           = sInTagName;
        sGaikanGrpName  = sInGaikanGrpName;
        sSetClassName    = sInSetClassName;
        sClassSetTag       = sInClassSetTag;
        sAttribute            = sInAttribute;
    }
};


struct SCT_FORMAT_CSV
{
    string      sFmt_JP;
    string      sFmt_EI;

    SCT_FORMAT_CSV ( string sJP, string sEI )
    {
        sFmt_JP = sJP;
        sFmt_EI = sEI;
    }
    bool operator == (string sInFmt_JP )
    {
        return ( sInFmt_JP == sFmt_JP );
    }
};


struct SCT_TAG_CSV
{
    string      sTagGroup;
    string      sTagID;
    string      sTagJP;
    string      sMinLen;
    string      sMaxLen;

    void Memset()
    {
        sTagGroup = "";
        sTagID = "";
        sTagJP = "";
        sMinLen = "";
        sMaxLen = "";
    }
    SCT_TAG_CSV()
    {
    }

    SCT_TAG_CSV( string sInTagGroup, string sInTagID, string sInTagJP, string sInMinLen, string sInMaxLen )
    {
        sTagGroup = sInTagGroup;
        sTagID      = sInTagID;
        sTagJP      = sInTagJP;
        sMinLen    = sInMinLen;
        sMaxLen   = sInMaxLen;
    }
};

struct SCT_LIMIT_CSV
{
    string      sLimit_JP;
    string      sLimit_EI;

    SCT_LIMIT_CSV( string JP, string EI )
    {
        sLimit_JP = JP;
        sLimit_EI = EI;
    }
    bool operator == ( string sInLimit_JP )
    {
        return (sLimit_JP == sInLimit_JP );
    }
};


struct SCT_INIT_CSV
{
    string      sAppearanceName;
    string      sClassSetName;

    SCT_INIT_CSV( string sInAppearanceName, string sInClassSetName )
    {
        sAppearanceName     = sInAppearanceName;
        sClassSetName          = sInClassSetName;
    }
};

struct SCT_BGCOLOR
{
    string      sBgColor;
    string      sClassSetName;

    SCT_BGCOLOR(string sInBgColor , string sInClassSetName )
    {
        sBgColor = sInBgColor;
        sClassSetName = sInClassSetName;
    }

};


struct SCT_CELL
{
    DWORD dwRow;
    DWORD dwCol;
    SCT_CELL( DWORD dwInCol, DWORD dwInRow )
    {
        dwRow = dwInRow;
        dwCol   = dwInCol;
    }
};

static const char* HIGHT_UMU_LIST[] = { "H",      "HL", "H",  "H",    "Å~",    "HL", "HL", "HL", "HL" ,  "HL",         "H",   "H",     "H", //éq
                                                               "Å~",     "HL", "Å~", "HL",   "H",     "Å~", "HL", "HL", "Å~" ,  "H" ,        "H",    "H",     "H"};   //êe
static const char* WIDTH_UMU_LIST[] =  { "Åõ",     "Åõ", "Åõ", "Åõ",   "Å~",    "Åõ", "Åõ", "Åõ", "Åõ" ,  "Å~",        "Åõ",    "Å~",    "Åõ",   //éq
                                                               "Å~",     "Åõ", "Å~", "Åõ",   "Åõ",    "Å~", "Åõ", "Åõ", "Å~" ,  "Åõ",        "Åõ",    "Åõ",    "Åõ"};  //êe
//static char* TAG_NAME_LIST[] =  { "button", "div", "a", "span", "image", "ul", "li", "time", SEINENGAPPI, CONTENA, MSGAREA, IMG_STRETCH };
static const char* FONT_UMU_LIST[] =  { "Åõ",     "Åõ", "Åõ", "Åõ",   "Å~",    "Åõ", "Åõ", "Åõ", "Å~" , "Åõ",        "Å~",    "Åõ",   "Åõ",   //éq
                                                               "Å~",     "Åõ", "Å~", "Å~",   "Åõ",    "Å~", "Åõ", "Åõ", "Åõ" ,  "Å~",        "Å~",    "Å~",   "Åõ"}; //êe
