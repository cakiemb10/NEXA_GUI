

// GuiViewDDlg.h : header file
//
#ifndef GUIVIEWDLG_H
#define GUIVIEWDLG_H
#pragma once

#include "afxwin.h"
#include "resource.h"
#include "GUIDRichLabel.h"
#include "GUIDConstant.h"
#include "GUIDCustomBtn.h"
#include "GUIDPopupDlg.h"
#include "GUIDArea.h"
#include "GUIDCommonSct.h"
#include "GUIDConstTable.h"
#include "GUIDUtils.h"
#include <vector>
#include <map>
#include "GUIDVirtualCursor.h"
#include "GUIDCssStore.h"
#include "GUIDAreaStore.h"
#include "GUIDInitScreen.h"

using namespace std;

// CGuiViewDlg dialog
class CGuiViewDlg : public CDialogEx
{
// Construction
public:
    CGuiViewDlg(CWnd* pParent = NULL);    // standard constructor
    virtual ~CGuiViewDlg();

// Dialog Data
    enum { IDD = IDD_NEXA_GUI_VIEW };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


// Implementation
private:
    BYTE                        m_bySendData[65000];                // Sending data
    CVirtualCursor              m_cCursor;                          // Cursor image
    CAreaStore                  m_cAreaStore;                       // Area store
    vector<CArea*>              &m_vCurAreas;                       // Current areas list
    vector<CPopupDlg*>          &m_vPopupDlg;                       // Popup dialog
    DWORD                       &m_dwCurGyomuMode;                  // Current gyomu mode
    CPopupDlg                   m_dialog2;
    CInitScreen                 *m_pInitDlg;
    DWORD                       m_dwCurTimerID;
    DWORD                       m_dwTimerCursorCounter;
    BOOL                        m_bIsCurWaitPopup;

    //DWORD                       m_dwNumberOfPopup;
public:
    VOID DisplayGyomu( DWORD dwGyomuNo );
    VOID DisplayGyomu1();                                           // Create Gyomu layout mode 1
    VOID DisplayGyomu2();                                           // Create Gyomu layout mode 2
    VOID DisplayGyomu3();                                           // Create Gyomu layout mode 3
    BOOL ChangeArea( AREA_ENUM eArea, const string &sAreaFuncName );   // Change area
    POINT GetAreaPos( AREA_ENUM eAreaType );                        // Get area position by name, base on current gyomu mode
    DWORD GetAreaIndex( AREA_ENUM );
    VOID ClearSendData();
    CPopupDlg* GetActivePopup( );
    CTopIframe* GetActiveTopIFrame();

private:
    HICON m_hIcon;
    BOOL m_bIsForceUpdateTime;
    BOOL m_bIsClosed;
    BYTE m_byRevData[65000];

protected:
    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

    afx_msg LRESULT OnNcHitTest(CPoint point);
    afx_msg VOID OnDestroy();
    //afx_msg VOID OnCopyData();
    BOOL PreTranslateMessage( MSG* pMsg );
    afx_msg LRESULT OnPopupClickItem( WPARAM wParam, LPARAM lParam );

private:
    // Control Cursor methods
    VOID ShowCursor( DWORD x, DWORD y, DWORD height, CItem* lpItem );
    VOID HideCursor();
    VOID ShowPopup( LONG lx, LONG ly );
    VOID HidePopup();

    DWORD GetGyomuType( CHAR* cPageFile );
    void OnTimer( UINT_PTR nIDEvent );

    VOID HandleClickItem( CItem* lpItem );
    ///-----------------Event Handler-------------------------
    ///-----------------------LanLTM - view_ifrequest_response----------------------------------
    LONG RequestProcBranchFunc( 
                                       COPYDATASTRUCT* lpInCopyDataStruct );

    LONG InitRequestFunc(
                                     const  SCT_GUI_MSG_R_INIT_VIEW &sctInInitReq );

    LONG HolidayRequestFunc(
                                      const SCT_PUBLIC_HOLIDAY_REQ_MSG &sctInPubHoliday );

    LONG OperationDateRrequestFunc(
                                      const SCT_OPERATION_DATE_REQ_MSG &sctInOpeDate );

    LONG InputStartRequestFunc(
                                     const  SCT_GUI_MSG_R_INPUT_START_VIEW &sctInTransPkg );

    LONG InputCancelRequestFunc(
                                     const  SCT_GUI_MSG_R_INPUT_CANCEL_VIEW &sctStopInputItem );

    LONG InputCompletRequestFunc(
                                       CItem* lpInItem,
                                     const  string& sInInputData );


    LONG InputCompletResponseFunc(
                                      const SCT_GUI_MSG_A_INPUT_END_VIEW &sctInProcResult );

    
    LONG InputNoticeFunc(
                                    const string &sInTagID,
                                    const string &sInLabel = DEFAULT_LABEL );

    LONG KeyBoardInputNoticeFunc(
                                     const  SCT_GUI_MSG_N_INPUT_KB_VIEW &sctInKeyBoard );

    LONG OtherInputRequestFunc(
                                      const string &sInTagID );

    LONG OtherIputRsponseFunc();

    LONG StsIdicationRquestFunc(
                                      const SCT_GUI_MSG_R_STATUS_DISP_VIEW &sctInDispStatus );

    LONG DisplayRequestFunc(
                                        LPVOID           lpInData,
                                        DWORD            dwInDataSize,
                                        map<LONG, LONG>* lpmapOutProcessResult );


    LONG DisplayResponseFunc(
                                  map<LONG, LONG> mlInProcResult );

    LONG ResetRequestFunc();

    LONG ResetResponseFunc();

    LONG CursorDeleteFunc();

    LONG InitInputGlobalVariableFunc();

    LONG SendData( DWORD dwDataSize );

    LONG FareRequestFunc();

    LONG FareResponseFunc();

    LONG StartRequestFunc();

    LONG StartResponseFunc();

    LONG ErrorNoticeFunc(
                                   LONG lInErrCode );


    LONG CommonResponseFunc(
                          LONG lInTelegramNo,
                          LONG lInResult );

    void InputProcBranchFunc(
                          CItem* lpInItem,
                          DWORD  dwInClickBranchMode );

    void LabelOnClickProcBranchFunc(
                          CItem* lpInItem );

    LONG TabOnClickProcBranchFunc(
                                   CItem* lpInItem );

    afx_msg BOOL OnCopyData(
                    CWnd*             lpWnd,
                    COPYDATASTRUCT*   lpCopyDataStruct );

    BOOL JudgeDateValidityFunc( 
             SCT_DATE  sctInOperDate, 
             SCT_DATE* lpsctOutValidDate,
             LONG&     lOutErrCode );

    BOOL IsLeapYear( WORD year );

    LONG SearchAreaTagIndexFunc( 
       const vector<CItem*> &vlpItem, 
             AREA_ENUM eInAreaType );

    LONG ContenaKirikaeFunc( 
                             const     string &sInContenaKirikaeId, 
                             const     string &sInStartNo, 
                             const     string &sInEndNo, 
                                  CItem* lpInObjItem );

    vector<CItem*> SearchTagNameFunc( 
                     const  string &sInTagName, 
                       AREA_ENUM eInAreaType );

    LONG TeikiShubetsuInputProcBranchFunc(
            const string &sInTagID );

    LONG TeikiShubeTsuInputCompletRequestFunc();

    LONG TeikiShubeTsuInputNoticeFunc( 
             CItem* lpInObjTagID, 
             LONG   lzokuseiIdx );

    LONG InputCancelResponsFunc(
             LONG  lInMessageNo, 
             LONG  lInResult );

    LONG  InputErrorNoticeFunc( 
     const    string &sInInputTagID, 
              LONG   lInInputErrCode, 
              LONG   lInConditionMin, 
              LONG   lInConditionMax);



    ///-----------------------SonPTT control_display.js----------------------------

    LONG DisplayBranchPageSwitcFunc( 
                           SCT_GUI_MSG_DISP_TYPE_CHANGE_AREA_VIEW sctInPageSwitch);

    LONG DisplayBranchPopupFunc( 
                            SCT_GUI_MSG_DISP_TYPE_POP_UP_VIEW sctInPopupDisp );

    LONG DisplayBranchCalendarFunc( 
                           const SCT_GUI_MSG_DISP_TYPE_CALENDAR &sctInCalendarDisp );

    LONG DisplayBranchButtonFunc( 
                           SCT_GUI_MSG_DISP_TYPE_BTN_VIEW sctInButton );

    LONG DisplayBranchTextItemFunc( 
                           SCT_GUI_MSG_DISP_TYPE_TXT_VIEW sctInTextArea );

    LONG DisplayBranchImageFunc( 
                           SCT_GUI_MSG_DISP_TYPE_CMD_IMG_VIEW sctInImage );

    LONG SettingCalendarFunc( 
                    const   vector<CItem*> &lpcCalendarItems, 
                            WORD wInDispYear, 
                            BYTE byInDispMonth);

    LONG ChangeClassIDFunc( 
                            CItem* lpobjInItem, 
                    const   string &sDesign, 
                            string sBeforeGaikan = NOT_SET_STR );

    LONG ChangeFlashingTagFunc( 
                            CItem* lpobjInItem, 
                            DWORD  dwLightOnOffCnt, 
                     const  string &sUpdateElement );

    LONG CursorAddFunc( 
                            DWORD dwInInitShiji );

    LONG CursorInputBranchFunc( 
                            CItem* lpobjInItem );

    LONG CursorInputUpdateCharacterFunc( 
                            CItem* lpobjInItem, 
                            string sInTagValue,
                            LONG   lMaxLength );

    LONG CursorInputDeleteCharacterFunc( 
                            CItem* lpobjInItem );

    LONG CursorAllDeleteCharacterFunc(
                            CItem* lpobjInputItem,
                            BOOL bInSetFormatFlg );

    LONG CursorMoveFunc( 
                            LONG lInMoveCursor );

    LONG ReCalculateCursorPosition( 
                            CItem* lpobjInputItem, 
                            LONG lInX, 
                            LONG lInY );

    LONG ControlEnableAllDisplayFunc( 
                            BOOL bInEnable, 
                            AREA_ENUM eInAreaType );

    CItem* FindItemByTagID ( 
                            const string &sInTagID, 
                            const vector<CItem*>& vobjInSearchItem);

    vector<CItem*> FindItemsByTagName ( 
                            string sInTagName, 
                            vector<CItem*> vobjInSearchItem);
    
    string GetClassByDesign ( 
                            DWORD  dwTblIndex, 
                     const  string &sDesign, 
                            BOOL   bIsMulti );

    string GetDesignStringByDesignNumber ( 
                            DWORD dwDesign );

    string GetDesignStsFunc( 
                     const  string &sInStsDesign );

    VOID SetCursorRelativePosition( 
                            BOOL bLeftJustify );

    
    CArea* GetCurrentAreaByAreaType(
                            AREA_ENUM eInAreaType);


    LONG  ChangeDesignBtnOnFunc( CItem* lpobjInItem, DWORD dwSwitchPageIdx, BOOL bAnotherOn );




    ///-----------------------TrungLV----------------------------------
    void InputPasswordProcBranchFunc( CItem* lpInObjItem );
    LONG GetHeddinPassTagFunc( CItem* &lpOutItem, const string &sInTagID );
    BOOL JudgeInputTagFunc();
    LONG JudgeMinInputLimitFunc( const string &sInInput, LONG lInputLimit, LONG dwMaxLength );
    LONG PassCursorInputBranchFunc( const string &sInTagID, const string &sInInputValue, CItem* lpInPassTagId );
    LONG InputPasswordKey_ProcBranchFunc( CItem* lpInItem );

    LONG CursorPassInputDeleteCharacterFunc( CItem* lpInInputTagId, CItem* lpInPassId );
    LONG CursorPassInputUpdateCharacterFunc( CItem* lpInInputTagId, CItem* lpInPassTagId,  string sInUpdateCharacter, LONG lInMaxLen );
    LONG CursorPassAllDeleteCharacterFunc( CItem* lpInInputTagId, CItem* lpInPassTagId );
    // Conv_format.js
    LONG ConvAnnoDominiOrJapaneseCalendarFunc(  string sInConvDate,
                                              const string &sInConvMode, 
                                                    string &sOutConvYearStr );
    LONG ConvDispCommaFunc(  string sConvData, DWORD dwInConvMode, string &sOutData );
    LONG ConvZeroPaddingFunc(  string sInConvData, DWORD dwInConvMode, DWORD dwInMaxLength, string &sOutConvData );
    LONG  ConvFullHalNumberFunc( const string &sInText, BOOL bfInHalfNumber , string &sOutConvData );
    LONG  ExcerptNotFormatFunc(
                      const     string &sInFormatCharacter,
                      const     string &sInDispCharacter,
                                LONG lInDeleteIndex,
                                string &sOutString,
                                BOOL bInLeftJustify );

    LONG AddFormatFunc(
                            CItem* lpIntagId,
                   const    string &sInFormatCharacter,
                   const    string &sInAddCharacter,
                            BOOL   bInAddCharacterFlg,
                            BOOL   bInLeftJustifyFlg,
                            LONG   lInMaxLength,
                            string &sOutDisplayContent);

    LONG ChangeInputCharacterFunc( CItem* lpInItem, const SCT_FORMAT_TABLE &sctInInputFormat);
    string ChangeSendDataFunc( CItem* lpInItem );
    string ConvDateFormatFunc( const SCT_DATE &sctInDate, const string &sInDataFormat );
    string GetFormatInitSTrFunc(
                         const       string &sFormatName, 
                         const       string &sInitFormat, 
                         const       string &sFormatGreap );
    LONG ConvTagIdDateFormatFunc(
                        const   string &sTagID,
                                string  sInDate,
                        const   string &sConvMode,
                        const   string &sInClassList,
                                string& sDispStr,
                                string& sReturnStr );
    string NullDateFormatSpaceFillFunc( const string &sInTagId, const string &sInClassList );
    string ConvDateStrFunc( const SCT_DATE &sctDate, BOOL bInHalfNumberFlg );
    string ConvInputLimitMsgFunc( const string &sInLimit);
    // TODO implement
    VOID ChangeHightClassFunc( CItem* lpobjInItem );
    // End conv_format

    string CGuiViewDlg::SelectSendTagIdFunc(
                             CItem* lpInItem );




    ///-----------------------ThietNP control_display.js--------------------------------

    LONG CursorAddBirthDateFmtFunc( BYTE byInInitDisp );
    LONG ControlKeyBoardFunc(  );
    LONG ChangeInputTagDesignFunc( CItem* lpInItem, const string &sInDesign );
    LONG SettingDisplayCalendarFunc( CItem* lpobjInItem );
    LONG ChangeDispCalendarEraFunc( CItem* lpInItem );
    LONG CGuiViewDlg::ChangeDispInputErroFunc( 
                                         CItem* lpInItem );
    LONG CGuiViewDlg::ResolutiveDispInputErroFunc(
                                       CItem* lpInItem,
                                       DWORD  dwInResolutiveMode );
    LONG ChangeFontColorFunc( CItem* lpobjInItem, DWORD dwInChangeMode, DWORD dwCharacterColor );
    LONG VisibleLinkTagIdFunc( CItem* lpobjInItem, const vector<CItem*>& vSearchItems, BOOL bVisible );
    LONG InputExpressSeatFunc( CItem* lpobjInItem, DWORD dwInMaxOnZaseki );
    LONG CGuiViewDlg::SwitchOperationPageFunc(
                                       CItem* lpInTagID );
    LONG ChangeInputButtonDesignFunc( CItem* lpobjInItem );
    LONG ChangeDispSchoolYearFunc( CItem* lpInItem );
    LONG VisibleInputTagIdTabFunc( CItem* lpobjInItem, vector<CItem*> vInDocument );
    LONG SettingCalendarKikanFunc( const vector<CItem*> &vobjInCalendarDocument, DWORD dwInDispMaxRow, DWORD dwInDispMaxCol );
    LONG SettingPeculiarItemFunc( CItem* lpobjItem, const vector<CItem*> &vInDocument, const string &sInDesign );
    LONG ChangeVisibleTagFunc( CItem* lpobjInItem, const vector<CItem*> &vSearchItems, BOOL bInVisible, const string &dwInDesign );
    LONG ChangeVisibleInsideTabFunc( CItem* lpobjInItem );
    LONG DisplayBranchToolTipFunc(  );
    LONG VisibleToolTipFunc(  );
    LONG AddToolTipFunc(  );
    LONG ChangeToolTipFunc(  );
    LONG DeleteToolTipFunc(  );
    LONG CopyInputInfoFunc( AREA_ENUM eAreatype, const string &sInTagID, const string &sInText, const string &sInStatus );
    string CalculationWeekFunc (  SCT_DATE sctInDate );
    BOOL JudgeUserInputProcFunc( const string &sInTagID, const string &sInInputTagID );

    BOOL JudgeUserDisplayProcFunc(
          const   string &sInTagID );

    BOOL JudgeInputStrFunc(
                 const    string &sInLeftStr,
                 const    string &sInRightStr,
                 const    string &sInsertStr,
                          LONG lInMaxLength, 
                          string& sResult );

    LONG TeikiShubeTsuBtnCtrlFunc(
             CItem* lpInObjectCItem,
             LONG   lInZokuseiIdx);

    LONG TeikiShubeTsuDisplayFunc(
           const  string &sInTagID );

   LONG TeikiShubeTsuBtnSubCtrlFunc(CItem* lpInTagID,
                                    DWORD dwInDesign,
                                    DWORD  dwInVisible,
                                    DWORD  dwInEnable);
   LONG TeikiShubeTsuJudgeConditionOnGrpFunc( DWORD dwInCtrlTblIdx );
    ///-----------------------LiemTT judge_calculation_proc.js--------------------------------

     string CGuiViewDlg::JudgeInputTagBirthOfDateFunc( BOOL bInErrNoticeFlg );

     void CGuiViewDlg::ConvertStr2DateSct( const string &sInData, SCT_DATE &sctInDate );

     BOOL   CGuiViewDlg::JudgeErrorBreakFunc( DWORD dwInKomokuType, CHAR cInFilePath[256], BOOL bInDispFlag );

     vector<CItem*> SearchTagIDFunc(
                           const string    &sInTagID, 
                                 AREA_ENUM eInAreaType);
     LONG ChangeItemAssignClassFunc( 
                            CItem* lpobjInItem,
                  const     string &sAssignClass,
                            DWORD  dwChangeMode );

    vector<CItem*> SearchEkiButtonIDFunc(
                           const     string &sInSerchObject, 
                           const     string &sInStationId, 
                           const     string &sInGroupType, 
                                     AREA_ENUM eInAreaType, 
                           const     string &sInSerchId);


    vector<CItem*> SearchAltTagIDFunc(
                            const        string &sInSerchObject,
                            const        string &sInAltTagID,
                            const        string &sInSerchTagName,
                                         AREA_ENUM eInAreaType,
                            const        string &sInSerchId );

    vector<CItem*> SearchGroupTagIDFunc(
                            const          string &sInSerchObject,
                            const          string &sInGroupType,
                            const          string &sInSerchTagName,
                                           AREA_ENUM eInAreaType,
                            const          string &sInSerchId);

    BOOL JudgeInputTagAllEnteredFunc( const string &sText, const string &strFormat );
    BOOL JudgeAreaEnbledFunc( AREA_ENUM eAreaType );
    CArea* GetArea( AREA_ENUM eAreaType );
    LONG ChangeViewInnerPageFunc( const string &sInPageURL, AREA_ENUM eInAreaName);
    VOID InitScreen();

    LONG JudgeNumberFunc( string sInputNumber );
    LONG SerchInputGuidFunc(
                    const   string &sInputChar, 
                    const   string &sInputGuide, 
                            BOOL   bLeftJustify, 
                            LONG   lRangeEnd );
    VOID CreateSeinenGappi( CItem* lpInItem, const string &sInDispStr );
    string setDispClockStr( SCT_DATE sctInDate );
    BOOL JudgeBlankInputStrFunc( const string &sInDispText, const string &sInUpdateCharacter ) ;
    LONG CtrlDispHolidayFunc();
     ///-----------------------Generated source--------------------------------

    // CREATE PROTOTYPE HERE ( Warning: No delete this comment )

protected:
    afx_msg LRESULT OnCreateTopIframeBuffer( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnReceiveMsgFromViewIf( WPARAM wParam, LPARAM lParam );
    LONG SetInputBirthForamtFunc( const string &sTagID );
    afx_msg LRESULT OnNexaMsgRefreshCusor( WPARAM wParam, LPARAM lParam );
    void DispClockFunc();
    void BlinkCursorTimer();
    // Start ThietNP 2015-07-28 Comment out unused function
    //afx_msg LRESULT OnNexaMsgUpdateAboveItems( WPARAM wParam, LPARAM lParam );
    // End ThietNP 2015-07-28 Comment out unused function
};


#endif
