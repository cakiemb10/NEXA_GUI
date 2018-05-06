// Event handler

#include "stdafx.h"
#include "GuiViewDlg.h"
#include <algorithm>
#include <regex>
#include "GUIDUtils.h"

#pragma warning ( disable: 4100) // Disable warning unreferenced formal parameter

#define IsHalfWidthDigit(a) (('0' <= (a)) && ((a) <= '9'))
//#define IsFullWidthDigit(a) ((L'�O' <= (a)) && ((a) <= L'�X'))
#define IsFullWidthDigit(a) ((0x824f <= (a)) && ((a) <= 0x8258))

extern SCT_DATE             gsctOperationDate;                     // Operation date global parameter
extern vector<SCT_DATE>     gsctHolidayArray;                      // Holiday array global parameter
extern SCT_DATE             gsctBasicDate;                         // Basic Date
extern SCT_DATE             gsctStartDate;                         // Start Date
extern SCT_DATE             gsctEndDate;                           // End Date
extern SCT_DATE             gsctDispDate;                          // Display Date;
extern CItem*               gclInputItemTag;                       // Input Item
extern SCT_FORMAT_TABLE     gsctInputFormat;                       // Input Item format
extern string               gsViewErrorDesign;                    // Display Error Design
extern DWORD                gdwViewErrorBlinkCnt;                  // Blink count
extern DWORD                gdwViewErrorResolutive;                // View Error Resolutive
extern DWORD                gdwFlgDispZeroPadding;                 // Displaying Zero Padding    
extern vector<string>       gsInputItemBeforeData;                 // Array of previous data of input items
extern BOOL                 gbInputItemFirstInitializationFlg;     // Flag to check whether Input Item is First initialization or not
extern CItem*               gclCursorImageTag;
extern LONG                 glRelativeCurPos;
extern AREA_ENUM            geInputItemArea;                        // Area type of input item
extern BOOL                 gbPageChageLoadFlg;                     // Flag to check load page change or not
extern LONG                 glWaitResponseDenbunNo;                 // Message number of message that is being waited
extern BOOL                 gSetHolidayDispTimer;
// View_IF_request_response

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  RequestProcBranchFunc
//
//�@�\�@�@��@�F  Execute process when receiving message from ViewIF
//
//�@�T�@�@�v�@�F  Execute process when receiving message from ViewIF
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  COPYDATASTRUCT* lpInCopyDataStruct                (I)              Received package
//                DWORD           dwInExecutedRequestCount          (I)              Execute Request count
//                BOOL            bInRequestExecutedFlg             (I)              Request execute flag
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/10   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::RequestProcBranchFunc( 
                                   COPYDATASTRUCT* lpInCopyDataStruct )
{
    // Initilize
    LONG                            lProcResult         = GUI_RET_NG;                          // Internal function return
    std::map<LONG, LONG>            mlProcessResult;                                           // Mapping between message no and error code
    LONG                            lResponseTelegramNo = GUI_VALUE_ZERO_LONG;                 // Responsed message no
    SCT_GUI_MSG_R_INIT_VIEW         sctIni;                                                    // Structure to store information related to initialize message
    SCT_PUBLIC_HOLIDAY_REQ_MSG      sctPubHoliday;                                             // Structure to store information related to Public holiday message
    SCT_OPERATION_DATE_REQ_MSG      sctOpeDate;                                                // Structure to store information related to Operation message
    SCT_GUI_MSG_R_INPUT_START_VIEW  sctStartInputItem;                                         // Structure to store information related to Start Input message
    SCT_GUI_MSG_A_INPUT_END_VIEW    sctProcResult;                                             // Structure to store information related to Completed Input message
    SCT_GUI_MSG_R_INPUT_CANCEL_VIEW sctStopInputItem;                                          // Structure to store information related to Cancel message
    SCT_GUI_MSG_N_INPUT_KB_VIEW     sctKeyBoard;                                               // Structure to store information related to Keyboard message
    SCT_GUI_MSG_R_STATUS_DISP_VIEW  sctDispStatus;                                             // Structure to store information related to Displaying message
    DWORD                           dwDenbunNo          = GUI_VALUE_ZERO_DWORD;                // Message number

    // Initialize
    ( VOID )memset( &sctIni, 0x00, sizeof( sctIni ));
    ( VOID )memset( &sctPubHoliday, 0x00, sizeof( sctPubHoliday ));
    ( VOID )memset( &sctOpeDate, 0x00, sizeof( sctOpeDate ));
    ( VOID )memset( &sctStartInputItem, 0x00, sizeof( sctStartInputItem ));
    ( VOID )memset( &sctProcResult, 0x00, sizeof( sctProcResult ));
    ( VOID )memset( &sctStopInputItem, 0x00, sizeof( sctStopInputItem ));
    ( VOID )memset( &sctKeyBoard, 0x00, sizeof( sctKeyBoard ));
    ( VOID )memset( &sctDispStatus, 0x00, sizeof( sctDispStatus ));

    // Check parameter
    // Check input is NULL or not
    if ( lpInCopyDataStruct == NULL )
    {
        ErrorNoticeFunc( ERROR_CODE_CONV_JSON );
        return ERROR_CODE_CONV_JSON;
    }
    else
    {
        // Do nothing
    }

    if ( lpInCopyDataStruct ->lpData == NULL )
    {
        ErrorNoticeFunc( ERROR_CODE_CONV_JSON );
        return ERROR_CODE_CONV_JSON;
    }

    // Get message number
    ( VOID )memcpy( &dwDenbunNo, lpInCopyDataStruct ->lpData, sizeof( DWORD ));

    // Set value for flag that run the case of on only request processing
    if ( glWaitResponseDenbunNo == ( LONG )dwDenbunNo )
    {
        glWaitResponseDenbunNo = -1;
    }
    else
    {
        // Do nothing
    }

    switch ( dwDenbunNo )
    {
    case INIT_REQUEST_NO:
        // Check data size is valid
        if ( lpInCopyDataStruct->cbData == sizeof( sctIni ))
        {
            // Do nothing
        }
        else
        {
            // Data size is invalid
            ErrorNoticeFunc( ERROR_CODE_CONV_JSON );
            return ERROR_CODE_CONV_JSON;
        }

        ( VOID )memcpy( &sctIni, lpInCopyDataStruct ->lpData , lpInCopyDataStruct->cbData );

        // Execution of View initialization request
        lProcResult = InitRequestFunc( sctIni );
        // Setting the message number of View initialization response
        lResponseTelegramNo = INIT_RESPONSE_NO;
        break;

    case HOLIDAY_REQUEST_NO:
        // Check data size is valid
        if ( lpInCopyDataStruct->cbData == sizeof( sctPubHoliday ))
        {
            // Do nothing
        }
        else
        {
            // Data size is invalid
            ErrorNoticeFunc( ERROR_CODE_CONV_JSON );
            return ERROR_CODE_CONV_JSON;
        }

        ( VOID )memcpy( &sctPubHoliday, lpInCopyDataStruct ->lpData , lpInCopyDataStruct->cbData );

        // Execution of Holiday request
        lProcResult = HolidayRequestFunc( sctPubHoliday );
        // Setting the message number of Holiday response
        lResponseTelegramNo = HOLIDAY_RESPONSE_NO;
        break;

    case UNYOSET_REQUEST_NO:
        // Check data size is valid
        if ( lpInCopyDataStruct->cbData == sizeof( sctOpeDate ))
        {
            // Do nothing
        }
        else
        {
            // Data size is invalid
            ErrorNoticeFunc( ERROR_CODE_CONV_JSON );
            return ERROR_CODE_CONV_JSON;
        }

        ( VOID )memcpy( &sctOpeDate, lpInCopyDataStruct ->lpData , lpInCopyDataStruct->cbData );

        // Execution of operation date request
        lProcResult = OperationDateRrequestFunc( sctOpeDate );
        // Setting the message number of operation date response
        lResponseTelegramNo = UNYOSET_RESPONSE_NO;
        break;

    case INPUT_START_REQUEST_NO:
        // Check data size is valid
        if ( lpInCopyDataStruct->cbData == sizeof( sctStartInputItem ))
        {
            // Do nothing
        }
        else
        {
            // Data size is invalid
            ErrorNoticeFunc( ERROR_CODE_CONV_JSON );
            return ERROR_CODE_CONV_JSON;
        }

        ( VOID )memcpy( &sctStartInputItem, lpInCopyDataStruct ->lpData , lpInCopyDataStruct->cbData );

        // Execution of Input start request
        lProcResult = InputStartRequestFunc( sctStartInputItem );
        // Setting the message number of input start response
        lResponseTelegramNo = INPUT_START_RESPONSE_NO;
        break;

    case INPUT_COMPLET_RESPONSE_NO:
        // Check data size is valid
        if ( lpInCopyDataStruct->cbData == sizeof( sctProcResult ))
        {
            // Do nothing
        }
        else
        {
            // Data size is invalid
            ErrorNoticeFunc( ERROR_CODE_CONV_JSON );
            return ERROR_CODE_CONV_JSON;
        }

        ( VOID )memcpy( &sctProcResult, lpInCopyDataStruct ->lpData , lpInCopyDataStruct->cbData );

        // Execution of Input complete request
        lProcResult = InputCompletResponseFunc( sctProcResult );
        // Setting the message number ofInput complete response
        lResponseTelegramNo = MESSAGE_RESPONSE_NUMBER_NULL;
        break;

    case INPUT_CANCEL_REQUEST_NO:
        // Check data size is valid
        if ( lpInCopyDataStruct->cbData == sizeof( sctStopInputItem ))
        {
            // Do nothing
        }
        else
        {
            // Data size is invalid
            ErrorNoticeFunc( ERROR_CODE_CONV_JSON );
            return ERROR_CODE_CONV_JSON;
        }

        ( VOID )memcpy( &sctStopInputItem, lpInCopyDataStruct ->lpData , lpInCopyDataStruct->cbData );

        // Execution of Input cancel request
        lProcResult = InputCancelRequestFunc( sctStopInputItem );
        // Setting the message number ofInput cancel response
        lResponseTelegramNo = INPUT_CANCEL_RESPONSE_NO;
        break;

    case KEYBOARD_INPUT_NOTICE_NO:
        // Check data size is valid
        if ( lpInCopyDataStruct->cbData == sizeof( sctKeyBoard ))
        {
            // Do nothing
        }
        else
        {
            // Data size is invalid
            ErrorNoticeFunc( ERROR_CODE_CONV_JSON );
            return ERROR_CODE_CONV_JSON;
        }

        ( VOID )memcpy( &sctKeyBoard, lpInCopyDataStruct ->lpData , lpInCopyDataStruct->cbData );

        // Execution of Input cancel request
        lProcResult = KeyBoardInputNoticeFunc( sctKeyBoard );
        // Setting the message number ofInput cancel response
        lResponseTelegramNo = MESSAGE_RESPONSE_NUMBER_NULL;
        break;

    case OTHER_INPUT_RESPONSE_NO:
        // Execution of unspecified input request
        lProcResult = OtherIputRsponseFunc();
        // Setting the message number of unspecified input response
        lResponseTelegramNo = MESSAGE_RESPONSE_NUMBER_NULL;
        break;

    case STS_INDICATION_REQUEST_NO:
        // Check data size is valid
        if ( lpInCopyDataStruct->cbData == sizeof( sctDispStatus ))
        {
            // Do nothing
        }
        else
        {
            // Data size is invalid
            ErrorNoticeFunc( ERROR_CODE_CONV_JSON );
            return ERROR_CODE_CONV_JSON;
        }

        ( VOID )memcpy( &sctDispStatus, lpInCopyDataStruct ->lpData , lpInCopyDataStruct->cbData );

        // Execution of Status indication request
        lProcResult = StsIdicationRquestFunc( sctDispStatus );
        // Setting the message number of Status indication response
        lResponseTelegramNo = MESSAGE_RESPONSE_NUMBER_NULL;
        break;

    case DISPLAY_REQUEST_NO:
        // Execution of display request
        lProcResult = DisplayRequestFunc( lpInCopyDataStruct ->lpData, lpInCopyDataStruct->cbData, &mlProcessResult );
        // Setting the message number of display response
        lResponseTelegramNo = DISPLAY_RESPONSE_NO;
        break;
        
    case RESET_RESPONSE_NO:
        // Execution of reset request
        lProcResult = ResetResponseFunc();
        // Setting the message number of reset response
        lResponseTelegramNo = MESSAGE_RESPONSE_NUMBER_NULL;
        break;

    case FARE_RESPONSE_NO:
        // Execution of fare request
        lProcResult = FareResponseFunc();
        // Setting the message number of fare response
        lResponseTelegramNo = MESSAGE_RESPONSE_NUMBER_NULL;
        break;

    case START_RESPONSE_NO:
        // Execution of start request
        lProcResult = StartResponseFunc();
        // Setting the message number of start response
        lResponseTelegramNo = MESSAGE_RESPONSE_NUMBER_NULL;
        break;

    default:
        // Other message number
        lProcResult = ErrorNoticeFunc( ERROR_CODE_ILLEGAL_DENBUN_NO );
        lResponseTelegramNo = MESSAGE_RESPONSE_NUMBER_NULL;
        break;
    }

    switch ( lResponseTelegramNo )
    {
    case DISPLAY_RESPONSE_NO:
        // Screen display response processing
        lProcResult = DisplayResponseFunc( mlProcessResult );
        break;

    case INPUT_CANCEL_RESPONSE_NO:
        lProcResult = InputCancelResponsFunc( lResponseTelegramNo, lProcResult );
        break;

    // If NO response message is not set, no treatment
    case MESSAGE_RESPONSE_NUMBER_NULL:
        break;

    // perform common response processing in the case of response processing other than the screen display response
    default:
        if ( lProcResult != GUI_RET_OK )
        {
            lProcResult = ErrorNoticeFunc( ERROR_CODE_CONV_JSON );
        }
        else
        {
            lProcResult = CommonResponseFunc( lResponseTelegramNo, lProcResult );
        }
        break;
    }

    return lProcResult;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  InitRequestFunc
//
//�@�\�@�@��@�F  Perform the initialization process of the global variable to be used for the View
//
//�@�T�@�@�v�@�F  Perform the initialization process of the global variable to be used for the View
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  SCT_INI_REQ_MSG sctInInitReq                (I)              Input value used to store the initialize state request
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/02/27   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::InitRequestFunc(
                                     const  SCT_GUI_MSG_R_INIT_VIEW &sctInInitReq )
{
    // Initilize
    LONG                    lProcResult = GUI_RET_OK;  // Error code vector

    // Reset all date global parameters
    ( VOID )memset( &gsctOperationDate, 0x00, sizeof( SCT_DATE ));
    gsctHolidayArray.clear();
    ( VOID )memset( &gsctBasicDate,     0x00, sizeof( SCT_DATE ));
    ( VOID )memset( &gsctStartDate,     0x00, sizeof( SCT_DATE ));
    ( VOID )memset( &gsctEndDate,       0x00, sizeof( SCT_DATE ));
    ( VOID )memset( &gsctDispDate,      0x00, sizeof( SCT_DATE ));
    gbPageChageLoadFlg = FALSE;

    // Initialize input-related global parameters
    InitInputGlobalVariableFunc();

    return lProcResult;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  HolidayRequestFunc
//
//�@�\�@�@��@�F  Set date of the holiday
//
//�@�T�@�@�v�@�F  Set date of the holiday
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  SCT_PUBLIC_HOLIDAY_REQ_MSG sctInPubHoliday    (I)   Input contains the information of public holiday
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/02/27   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::HolidayRequestFunc(
                                    const SCT_PUBLIC_HOLIDAY_REQ_MSG &sctInPubHoliday )
{
    // Initilize
    LONG                            lProcResult = GUI_RET_OK;                   // Vector of process result
    vector<SCT_DATE>                vHoliday;                                   // Vector contain holiday setting
    DWORD                           dwIndex     = GUI_VALUE_ZERO_DWORD;         // index of loop
    SCT_DATE                        sctCheckDate;                               // Date structure to checking

    // Reset value
    ( VOID )memset( &sctCheckDate, 0x00, sizeof( SCT_DATE ));
    vHoliday.clear();

    // Get all holiday setting
    for ( dwIndex = 0; dwIndex < GUI_MAX_HOLIDAY; dwIndex++ )
    {
        if ( memcmp( &sctInPubHoliday.sctDate[dwIndex], &sctCheckDate, sizeof( SCT_DATE )) == 0 )
        {
            // Date structure is empty
            break;
        }
        else
        {
            vHoliday.push_back( sctInPubHoliday.sctDate[dwIndex] );
        }
    }

    // Check data of received message valid or not
    if (( sctInPubHoliday.dwHolidayCnt == vHoliday.size()) ||
        ( sctInPubHoliday.dwHolidayCnt == 0 )              &&
        ( vHoliday.size() == 0 ))           
    {
        gsctHolidayArray = vHoliday;
        lProcResult = GUI_RET_OK;
    }
    else
    {
        lProcResult = ERROR_CODE_ILLEGAL_HOLIDAY_LIST;
    }
    return lProcResult;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  OperationDateRrequestFunc
//
//�@�\�@�@��@�F  Set the data of operation date
//
//�@�T�@�@�v�@�F  Set the data of operation date
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  SCT_OPERATION_DATE_REQ_MSG sctInOpeDate   (I)   Input is used to store the operation date information package
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/02/26   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::OperationDateRrequestFunc(
                                    const SCT_OPERATION_DATE_REQ_MSG &sctInOpeDate )
{
    // Initilize
    LONG                            lProcResult = GUI_RET_OK;   // Vector of process result
    SCT_DATE                        sctValidDate;               // Return date valid after checking
    BOOL                            bRet        = FALSE;        // Return function
    LONG                            lFuncResult = GUI_RET_NG;   // Function return

    // Reset value
    ( VOID )memset( &sctValidDate, 0x00, sizeof( SCT_DATE ));

    // Check the operation date is invlid or not
    bRet = JudgeDateValidityFunc( sctInOpeDate.sctDate, &sctValidDate, lFuncResult );

    if ( bRet == TRUE )
    {
        //  set value for operation date global parameter
        ( VOID )memcpy( &gsctOperationDate, &sctValidDate, sizeof( SCT_DATE ));
    }
    else
    {
        lProcResult = ERROR_CODE_ILLEGAL_OPERATION_DATE;
    }
    return lProcResult;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  InputStartRequestFunc
//
//�@�\�@�@��@�F  Response for input start item request
//
//�@�T�@�@�v�@�F  Response for input start item request
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  SCT_STARTING_INPUT_ITEM_REQ_MSG  sctInTransPkg      (I)    Input contains the information of request of start input item
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/02/26   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::InputStartRequestFunc(
                                  const SCT_GUI_MSG_R_INPUT_START_VIEW &sctInTransPkg )
{
    // Initilize
    LONG                            lProcResult             = GUI_RET_OK;                   // Vector of process result
    string                          sInputTagID             = "";                           // Input Tag ID
    vector<CItem*>                  vlpItem;                                                // Vector of item pointer
    LONG                            lPopupTag               = GUI_VALUE_ZERO_LONG;          // 
    DWORD                           dwLoopIndex             = GUI_VALUE_ZERO_DWORD;         // loop index
    vector<CItem*>                  vlpInputItem;                                           // Vector contain all input items
    CItem*                          lpObjUpdateTag          = NULL;                         // Input item should be updated displaying text
    DWORD                           dwSubRoopCount          = GUI_VALUE_ZERO_DWORD;         // Sub loop index
    LONG                            lSubFmtIdx              = GUI_VALUE_ZERO_LONG;          // 
    DWORD                           dwFmtInputLength        = GUI_VALUE_ZERO_DWORD;         // First position of guidline character
    vector<CItem*>                  vlpBatchItem;                                           // Vector contains batch item
    //DWORD                           dwMaxInputCount         = GUI_VALUE_ZERO_DWORD;         // Max input count
    LONG                            lMaxInputCount          = GUI_VALUE_ZERO_LONG;          // Max input count
    string                          sInputCount             = "";                           // Input count string
    string                          sBatchTagID             = "";                           // Tag ID of batch item
    DWORD                           dwIkkatsuLoopIndex      = GUI_VALUE_ZERO_DWORD;         // Max input count
    string                          sErrDesign              = "";                           // Error design
    wstring                         wInputGuide             = L"";                          // Input guide
    wstring                         wFormatInputItem        = L"";                          // Format input item
    std::smatch                     sm;

    // Reset data
    vlpItem.clear();
    vlpInputItem.clear();
    vlpBatchItem.clear();

    // Check message information
    // Check input tag ID
    if (( sctInTransPkg.dwMask & MASK_R_INPUT_START_TAGID ) == MASK_R_INPUT_START_TAGID )
    {
        sInputTagID = ( string )sctInTransPkg.szTagID;
        if ( sInputTagID.size() == 0 )
        {
            return ERROR_CODE_NULL_ID; // Fix follow TSBJ review
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        return ERROR_CODE_NULL_ID;
    }

    // Find input item by input tag ID
    vlpItem =  SearchTagIDFunc( sInputTagID, E_AREA_NULL );

    // If the tag ID of the target does not exist, the elements of the array is 0
    if ( vlpItem.size() == 1 )
    {
        // Found input item and assign for g_InputItem_Tag parameter
        gclInputItemTag = vlpItem[0];
        geInputItemArea = gclInputItemTag->m_sctProperty.eAreaType;
    }
    else
    {
        // found item in popup
        lPopupTag = SearchAreaTagIndexFunc( vlpItem, E_AREA_POPUP );

        // If item is found
        if ( -1 < lPopupTag )
        {
            gclInputItemTag = vlpItem[lPopupTag];
            geInputItemArea = E_AREA_POPUP;
        }
        // Cannot find input item
        else
        {
            return ERROR_CODE_NOT_EXIST_ID; // Fix follow TSBJ review
        }
    }

    // Reset format of input item
    gsctInputFormat.sTagId          = "";
    gsctInputFormat.bLeftJustify    = FALSE;
    gsctInputFormat.bSubTable       = FALSE;
    gsctInputFormat.bZeroSupp       = FALSE;
    gsctInputFormat.lRangeEnd       = -1;
    gsctInputFormat.lRangeStart     = -1;
    gsctInputFormat.sDataFormat     = "";
    gsctInputFormat.sEraName        = "";
    gsctInputFormat.sFormatName     = "";
    gsctInputFormat.sGreap          = "";
    gsctInputFormat.sInitDisp       = "";
    gsctInputFormat.sInputGuide     = "";
    // TSDV-20150504-LanLTM-Fix bug no 168
    gsctInputFormat.bBlankZero      = FALSE;
    gsctInputFormat.bBlankSpace     = FALSE;
    // TSDV-20150504-LanLTM-end

    // Get Input item format
    for ( dwLoopIndex = 0; dwLoopIndex < FORMAT_TABLE; dwLoopIndex++ )
    {
        if ( gclInputItemTag->m_sctProperty.sFmt == Format_Table[dwLoopIndex].sFormatName )
        {
            gsctInputFormat.bLeftJustify        = Format_Table[dwLoopIndex].bLeftJustify;
            gsctInputFormat.bSubTable           = Format_Table[dwLoopIndex].bSubTable;
            gsctInputFormat.bZeroSupp           = Format_Table[dwLoopIndex].bZeroSupp;
            gsctInputFormat.lRangeEnd           = Format_Table[dwLoopIndex].lRangeEnd;
            gsctInputFormat.lRangeStart         = Format_Table[dwLoopIndex].lRangeStart;
            gsctInputFormat.sFormatName         = Format_Table[dwLoopIndex].sFormatName;
            gsctInputFormat.sInitDisp           = Format_Table[dwLoopIndex].sInitDisp;
            gsctInputFormat.sInputGuide         = Format_Table[dwLoopIndex].sInputGuide;
            gsctInputFormat.bBlankZero          = Format_Table[dwLoopIndex].bBlankZero;
            gsctInputFormat.bBlankSpace         = Format_Table[dwLoopIndex].bBlankSpace;
            break;
        }
        else
        {
            // Do nothing
        }
    }

    // If the input item format is set, change the design, etc
    if ( gclInputItemTag->m_sctProperty.sFmt == ( string )"" )
    {
        // Do nothing
    }
    else
    {
        sErrDesign = ( string )sctInTransPkg.szErrDesign;
        if (( sctInTransPkg.dwMask & MASK_R_INPUT_START_ITEM_DESIGN ) == MASK_R_INPUT_START_ITEM_DESIGN )
        {
            // Set alarm displaying design
            if (( sErrDesign == DESIGN_ERROR_BLINK_MOJI )        ||
                ( sErrDesign == DESIGN_ERROR_BLINK )             ||
                ( sErrDesign == DESIGN_ERROR_BACKGROUND_CHANGE ) ||
                ( sErrDesign == DESIGN_ERROR_MOJI_CHANGE )       ||
                ( sErrDesign == DESIGN_ERROR_TOOLTIP )           ||
                ( sErrDesign == DESIGN_ERROR_NO_CHANGE ))
            {
                gsViewErrorDesign = ( string )sctInTransPkg.szErrDesign;
            }
            else
            {
                return ERROR_CODE_NOT_RANGE;  // Fix follow TSBJ review
            }
        }
        else
        {
            return ERROR_CODE_NULL; // Fix follow TSBJ review
        }

        // Set blink count number
        if (( strcmp( sctInTransPkg.szErrDesign, DESIGN_ERROR_BLINK_MOJI ) == 0 )   ||
            ( strcmp( sctInTransPkg.szErrDesign, DESIGN_ERROR_BLINK )  == 0) )
        {
            if (( sctInTransPkg.dwMask & MASK_R_INPUT_START_BLINK_CNT ) == MASK_R_INPUT_START_BLINK_CNT )
            {
                if (( sctInTransPkg.dwBlinkCnt <= FLG_OBJECT_BLINK_START ) &&
                    ( sctInTransPkg.dwBlinkCnt >= FLG_OBJECT_BLINK_STOP  ))
                {
                    gdwViewErrorBlinkCnt = sctInTransPkg.dwBlinkCnt;
                }
                else
                {
                    return ERROR_CODE_NOT_RANGE; // Fix follow TSBJ review
                }
            }
            else
            {
                return ERROR_CODE_NULL; // Fix follow TSBJ review
            }
        }
        else
        {
            // do nothing
        }

        // Abnormal display release conditions
        if (( sctInTransPkg.dwMask & MASK_R_INPUT_START_RESOLUTIVE ) == MASK_R_INPUT_START_RESOLUTIVE )
        {
            if (( sctInTransPkg.dwResolutive == ERROR_RESOLUTIVE_INPUT_FIRST   ) ||
                ( sctInTransPkg.dwResolutive == ERROR_RESOLUTIVE_ENTER         ) ||
                ( sctInTransPkg.dwResolutive == ERROR_RESOLUTIVE_NO_RESOLUTIVE ))
            {
                gdwViewErrorResolutive = sctInTransPkg.dwResolutive;
            }
            else
            {
                return ERROR_CODE_NOT_RANGE; // Fix follow TSBJ review
            }
        }
        else
        {
            return ERROR_CODE_NULL;  // Fix follow TSBJ review
        }

        // Zero filled display
        if (( sctInTransPkg.dwMask & MASK_R_INPUT_START_DISP_MAE_ZERO ) == MASK_R_INPUT_START_DISP_MAE_ZERO )
        {
            if (( sctInTransPkg.dwDispMaeZero == ZERO_PADDING_NOT_AVAILABLE     ) ||
                ( sctInTransPkg.dwDispMaeZero == ZERO_PADDING_AVAILABLE      ) ||
                ( sctInTransPkg.dwDispMaeZero == ZERO_PADDING_AVAILABLE_NULL ))
            {
                gdwFlgDispZeroPadding = sctInTransPkg.dwDispMaeZero;
            }
            else
            {
                return ERROR_CODE_NOT_RANGE;
            }
        }
        else
        {
            // Do nothing
        }

        // Change the displaying setting
        if ( gclInputItemTag->m_sctProperty.sGaikan == GROUP_NAME_IKKATSU_SET )
        {
            string sMaxInputCount = "";
            ConvFullHalNumberFunc( gclInputItemTag->m_sctProperty.sText, TRUE , sMaxInputCount );
            lMaxInputCount = atol( sMaxInputCount.c_str());
            for ( dwIkkatsuLoopIndex = 1; ( LONG ) dwIkkatsuLoopIndex <= lMaxInputCount; dwIkkatsuLoopIndex++ )
            {
                // Reset data
                sInputCount = "";
                sBatchTagID = "";
                vlpBatchItem.clear();
                // Found all batch item
                sInputCount  = std::to_string(( LONGLONG )dwIkkatsuLoopIndex );
                sBatchTagID  = gclInputItemTag->m_sctProperty.sTagID + TAG_ID_SPLIT + sInputCount;
                vlpBatchItem = SearchTagIDFunc( sBatchTagID, gclInputItemTag->m_sctProperty.eAreaType );

                if ( vlpBatchItem.size() == 0 )
                {
                    // Do nothing
                }
                else
                {
                    vlpInputItem.push_back( vlpBatchItem[0] );
                }
            }
            gsInputItemBeforeData.clear();
        }
        else
        {
            vlpInputItem.push_back( gclInputItemTag );
        }

        for ( dwLoopIndex = 0; dwLoopIndex < vlpInputItem.size(); dwLoopIndex++ )
        {
            // Get input item
            lpObjUpdateTag = NULL;

            // Get updates tag ID
            if ( vlpInputItem[dwLoopIndex]->m_sctProperty.bParent == TRUE )
            {
                lpObjUpdateTag = vlpInputItem[dwLoopIndex];
            }
            else
            {
                if ( vlpInputItem[dwLoopIndex]->m_vobjItems.size() != 0 )
                {
                    lpObjUpdateTag = FindItemByTagID( TAG_ID_NAME_SET_CHAR_SPAN, vlpInputItem[dwLoopIndex]->m_vobjItems );
                    // If not found any items
                    if ( lpObjUpdateTag == NULL )
                    {
                        return ERROR_CODE_NULL;
                    }
                    else
                    {
                        // Do nothing
                    }
                }
                else
                {
                    return ERROR_CODE_NULL;
                }
            }

            // Store the previous data for batch setting
            if ( gclInputItemTag->m_sctProperty.sGaikan == ( string )GROUP_NAME_IKKATSU_SET )
            {
                gsInputItemBeforeData.push_back( lpObjUpdateTag->m_sctProperty.sText );
            }
            else
            {
                gsInputItemBeforeData.clear();
                gsInputItemBeforeData.push_back( lpObjUpdateTag->m_sctProperty.sText );
            }

            // Item initialization existence
            if ( gsctInputFormat.sFormatName == ( string )FMT_NAME_DATE_OF_BIRTH )
            {
                lProcResult = CursorAddBirthDateFmtFunc( sctInTransPkg.byInitShiji );
            }
            else
            {
                if (( sctInTransPkg.dwMask & MASK_R_INPUT_START_INIT_SHIJI ) == MASK_R_INPUT_START_INIT_SHIJI )
                {
                    if ( sctInTransPkg.byInitShiji == INPUT_INIT_SHIJI_NOT_CHANGE )
                    {
                        // Do nothing
                    }
                    else if ( sctInTransPkg.byInitShiji == INPUT_INIT_SHIJI_FIRST_CLEAR )
                    {
                        gbInputItemFirstInitializationFlg = TRUE;
                    }
                    else if ( sctInTransPkg.byInitShiji == INPUT_INIT_SHIJI_CLEAR )
                    {
                        lpObjUpdateTag->m_sctProperty.sText = gsctInputFormat.sInitDisp;
                        lpObjUpdateTag->ItemUpdateState(); 
                    }
                    else
                    {
                        lProcResult = ERROR_CODE_NOT_RANGE;

                    }
                }
                else
                {
                    return ERROR_CODE_NULL;
                }

                // After item initialization, to add the settings if format auxiliary table exists
                lSubFmtIdx = -1;

                for ( dwSubRoopCount = 0; dwSubRoopCount < SUB_FORMAT_TABLE; dwSubRoopCount++ )
                {
                    if ( gsctInputFormat.sFormatName != Sub_Fomat_Table[dwSubRoopCount].sFormatName )
                    {
                        if ( lSubFmtIdx != -1 )
                        {
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                    else
                    {
                        // Do nothing
                    }

                    // If the tag ID is not set, register a sub-format data as the initial setting
                    if ( Sub_Fomat_Table[dwSubRoopCount].sTagId == "" )
                    {
                        lSubFmtIdx = ( LONG )dwSubRoopCount;
                        continue;
                    }
                    else
                    {
                        // do nothing
                    }

                    // Process when the date format is present
                    if (( Sub_Fomat_Table[dwSubRoopCount].sTagId      == "" ) ||
                        ( Sub_Fomat_Table[dwSubRoopCount].sDataFormat == NOT_SET_STR ))
                    {
                        // Do nothing
                    }
                    else
                    {
                        if ( regex_search( gclInputItemTag->m_sctProperty.sTagID, sm, regex( ".*"+ Sub_Fomat_Table[dwSubRoopCount].sTagId + "$" ), std::regex_constants::match_default ) == TRUE )
                        {
                            lSubFmtIdx = ( LONG )dwSubRoopCount;
                            break;
                        }
                        else
                        {
                            // Do nothing
                        }
                    }


                    // Processing in the case where the input guide is present
                    if ( Sub_Fomat_Table[dwSubRoopCount].sInputGuide != NOT_SET_STR )
                    {
                        wInputGuide = StringToWChar( Sub_Fomat_Table[dwSubRoopCount].sInputGuide );
                        wFormatInputItem    = StringToWChar( FORMAT_INPUT_ITEM );
                        dwFmtInputLength = wInputGuide.find( wFormatInputItem );
                        if ( SubStr( Sub_Fomat_Table[dwSubRoopCount].sInputGuide, 0, dwFmtInputLength ) == SubStr( lpObjUpdateTag->m_sctProperty.sText, 0, dwFmtInputLength ))
                        {
                            lSubFmtIdx = ( LONG )dwSubRoopCount;
                            break;
                        }
                        else
                        {
                            // Do nothing
                        }
                    }
                    else
                    {
                        // Do nothing
                    }
                }
                // If sub-table is already registered, exit the loop
                if ( lSubFmtIdx != -1 )
                {
                    if ( Sub_Fomat_Table[lSubFmtIdx].sFormatName == NOT_SET_STR )
                    {
                        // DO nothing
                    }
                    else
                    {
                        gsctInputFormat.sFormatName = Sub_Fomat_Table[lSubFmtIdx].sFormatName;
                    }

                    if ( Sub_Fomat_Table[lSubFmtIdx].sGreap == NOT_SET_STR )
                    {
                        // DO nothing
                    }
                    else
                    {
                        gsctInputFormat.sGreap      = Sub_Fomat_Table[lSubFmtIdx].sGreap;
                    }
                    if ( Sub_Fomat_Table[lSubFmtIdx].sTagId == NOT_SET_STR )
                    {
                        // DO nothing
                    }
                    else
                    {
                        gsctInputFormat.sTagId      = Sub_Fomat_Table[lSubFmtIdx].sTagId;
                    }
                    if ( Sub_Fomat_Table[lSubFmtIdx].sInputGuide == NOT_SET_STR )
                    {
                        // DO nothing
                    }
                    else
                    {
                        gsctInputFormat.sInputGuide = Sub_Fomat_Table[lSubFmtIdx].sInputGuide;
                    }

                    // TSDV-20150522-LanLTM-Update Javascript function to version 10.33
                    // <TSDV-131, 132, 133 in comment list-2015-04-30-LanLTM-Set value for global input format parameter >
                    //gsctInputFormat.bBlankZero = Sub_Fomat_Table[lSubFmtIdx].bBlankZero;
                    // < TSDV-131, 132, 133 in comment list-2015-04-30- End>
                    // TSDV-20150522-LanLTM-end

                    if ( Sub_Fomat_Table[lSubFmtIdx].sDataFormat == NOT_SET_STR )
                    {
                        // DO nothing
                    }
                    else
                    {
                        gsctInputFormat.sDataFormat = Sub_Fomat_Table[lSubFmtIdx].sDataFormat;
                    }
                }

                // No processing error, if present format is to add a cursor
                if (( lProcResult                 == GUI_RET_OK                         ) &&
                    ( gsctInputFormat.sFormatName != ( string )FMT_NAME_BUTTON_NO_INPUT ) &&
                    ( gsctInputFormat.sFormatName != ( string )""                       ))
                {
                    lProcResult = CursorAddFunc( sctInTransPkg.byInitShiji );
                }
                else
                {
                    // Do nothing
                }
            }

            // internal function is error
            if ( lProcResult != GUI_RET_OK )
            {
                return lProcResult;
            }
            else
            {
                // Do nothing
            }    

            // Modification of the design
            lProcResult = ChangeInputTagDesignFunc( vlpInputItem[dwLoopIndex], ( string )sctInTransPkg.szItemDesign );

            if ( lProcResult != GUI_RET_OK )
            {
                return lProcResult;
            }
            else
            {
                // Do nothing
            }    
        }

    }
    return lProcResult;
}



/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  InputCancelRequestFunc
//
//�@�\�@�@��@�F  Response for request of input cancel
//
//�@�T�@�@�v�@�F  Response for request of input cancel
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  SCT_STOP_INPUT_ITEM_MSG  sctStopInputItem      (I)    Input contains the information for request of cancel input item
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/02/26   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::InputCancelRequestFunc(
                                   const SCT_GUI_MSG_R_INPUT_CANCEL_VIEW &sctStopInputItem )
{
    // Initilize
    LONG                                lProcResult         = GUI_RET_OK;                   // Error code
    string                              sInputTagID         = "";                           // Input Tag ID string
    vector<CItem*>                      vlpItem;                                            // Vector of item pointer
    DWORD                               dwLoopIndex         = GUI_VALUE_ZERO_DWORD;         // loop index
    vector<CItem*>                      vlpInputItem;                                       // Vector contain all input items
    vector<CItem*>                      vlpBatchItem;                                       // Vector contains batch item
    CItem*                              lpObjUpdateTag      = NULL;                         // Input item should be updated displaying text
    //DWORD                               dwMaxInputCount     = GUI_VALUE_ZERO_DWORD;         // Max input count
    LONG                                lMaxInputCount      = GUI_VALUE_ZERO_LONG;         // Max input count
    string                              sInputCount         = "";                           // Input count string
    string                              sBatchTagID         = "";                           // Tag ID of batch item
    string                              sBeforeText         = "";                           // Before displaying text of input item
    string                              sCheckCharacter     = "";                           // Returned checking character string
    string                              sFormatInit         = "";                           // Initialize format
    vector<CItem*>                      vArrayTagName;                                      // Vector of tag item that has same tag name
    CItem*                              lpobjTagInfo        = NULL;                         // Tag Information item pointer
    CItem*                              lpobjSpanTagInfo    = NULL;                         // Span tag item pointer
    string                              sUpdateText         = "";                           // Updated text

    // Reset date
    vlpItem.clear();
    vlpInputItem.clear();
    vlpBatchItem.clear();
    vArrayTagName.clear();
    
    // Check input item is found or not
    if ( gclInputItemTag == NULL )
    {
        return ERROR_CODE_NULL_ID;
    }

    // Check input tag ID
    sInputTagID = ( string )sctStopInputItem.szTagID;
    if (( sctStopInputItem.dwMask & MASK_R_INPUT_CANCEL_TAGID ) == MASK_R_INPUT_CANCEL_TAGID )
    {
        if ( sInputTagID.size() == 0 )
        {
            return ERROR_CODE_NULL_ID;
        }
        else
        {
            // check whether the input item tag ID and current input item tag ID matches
            if ( sInputTagID == gclInputItemTag->m_sctProperty.sTagID )
            {
                // DO nothing 
            }
            else
            {
                return ERROR_CODE_NOT_EXIST_ID;
            }
        }
    }
    else
    {
        return ERROR_CODE_NULL_ID;  // Fix follow TSBJ review
    }

    // Uncontrol the screen
    lProcResult = ControlEnableAllDisplayFunc( FLG_OBJECT_NOT_ENABLE, E_AREA_GYOMU );

    // If the format to input item tag has been set, change the displaying design, etc
    if ( gclInputItemTag->m_sctProperty.sFmt != "" )
    {
        if ( gclInputItemTag->m_sctProperty.sGaikan == GROUP_NAME_IKKATSU_SET )
        {
            // Find input item by input tag ID
            vlpItem =  SearchTagIDFunc( sInputTagID, E_AREA_NULL );

            if ( vlpItem.size() == 1 )
            {
                // Do nothing
            }
            else
            {
                return ERROR_CODE_NOT_EXIST_ID;
            }

            string sMaxInputCount = "";
            // Found batch items
            ConvFullHalNumberFunc( gclInputItemTag->m_sctProperty.sText, TRUE , sMaxInputCount);
            lMaxInputCount = atol( sMaxInputCount.c_str());
            for ( dwLoopIndex = 1; ( LONG ) dwLoopIndex <= lMaxInputCount; dwLoopIndex++ )
            {
                // Reset data
                sInputCount = "";
                sBatchTagID = "";
                vlpBatchItem.clear();
                // Get batch of items
                sInputCount  = std::to_string(( LONGLONG )dwLoopIndex );
                sBatchTagID  = gclInputItemTag->m_sctProperty.sTagID + TAG_ID_SPLIT + sInputCount;
                vlpBatchItem = SearchTagIDFunc( sBatchTagID, vlpItem[0]->m_sctProperty.eAreaType );

                if ( vlpBatchItem.size() == 0 )
                {
                    // Do nothing
                }
                else
                {
                    vlpInputItem.push_back( vlpBatchItem[0] );
                }                
            }
        }
        else
        {
            vlpInputItem.push_back( gclInputItemTag );
        }

        // 
        dwLoopIndex = GUI_VALUE_ZERO_DWORD;

        for ( dwLoopIndex = 0; dwLoopIndex < vlpInputItem.size(); dwLoopIndex++ )
        {
            lpObjUpdateTag = NULL;

            // Get updates tag ID
            if ( vlpInputItem[dwLoopIndex]->m_sctProperty.bParent == TRUE )
            {
                lpObjUpdateTag = vlpInputItem[dwLoopIndex];
            }
            else
            {
                if ( vlpInputItem[dwLoopIndex]->m_vobjItems.size() != 0 )
                {
                    lpObjUpdateTag = FindItemByTagID( TAG_ID_NAME_SET_CHAR_SPAN, vlpInputItem[dwLoopIndex]->m_vobjItems );
                    // If not found any items
                    if ( lpObjUpdateTag == NULL )
                    {
                        return ERROR_CODE_NULL;
                    }
                    else
                    {
                        // Do nothing
                    }
                }
                else
                {
                    return ERROR_CODE_NULL;
                }
            }

            // Change the display content according to the specified method
            if (( lProcResult == GUI_RET_OK ) &&
               (( sctStopInputItem.dwMask & MASK_R_INPUT_CANCEL_REQ_STS ) == MASK_R_INPUT_CANCEL_REQ_STS ))
            {
                if ( gclInputItemTag->m_sctProperty.sGaikan == GROUP_NAME_IKKATSU_SET )
                {
                    sBeforeText = gsInputItemBeforeData[dwLoopIndex];
                }
                else
                {
                    sBeforeText = gsInputItemBeforeData[0];
                }
                if ( sctStopInputItem.dwClearMethod == INPUT_CANCEL_SHIJI_NOT_CHANGE )
                {
                    // If date of birth of the (two lines year), I will be in the year sum calendar 2-digit display the year
                    if ( gclInputItemTag->m_sctProperty.sTagID == TAG_ID_NAME_SEINEN_GAPPI )
                    {
                        sCheckCharacter = JudgeInputTagBirthOfDateFunc( FALSE );

                        if ( sCheckCharacter == "null" )
                        {
                            lpObjUpdateTag->m_sctProperty.sText = sBeforeText;
                        }
                        else
                        {
                            // Do nothing
                        }
                    }
                    else
                    {
                        // Do nothing
                    }
                }
                else if ( sctStopInputItem.dwClearMethod == INPUT_CANCELT_SHIJI_CLEAR )
                {
                    //Clear to return to the initial display (date of birth (two lines year) because that is separated by Span, 
                    //the initial display is different)
                    if ( gclInputItemTag->m_sctProperty.sTagID == TAG_ID_NAME_SEINEN_GAPPI )
                    {
                        sUpdateText = sBeforeText;
                        lpObjUpdateTag->UpdateText( sUpdateText );
                        
                        vArrayTagName = FindItemsByTagName( "div", lpObjUpdateTag->m_vobjItems );
                        // get the first item has tag name is div
                        lpobjTagInfo = vArrayTagName[0];
                        // Change text for first div item
                        sUpdateText= "";
                        sUpdateText = lpobjTagInfo->m_sctProperty.sText;
                        std::regex currentText((string )"\n" );
                        sUpdateText = std::regex_replace( sUpdateText, currentText, ( string )"�@");
                        lpobjTagInfo->UpdateText( sUpdateText );
                        // Get array of span items
                        vArrayTagName.clear();
                        vArrayTagName = FindItemsByTagName( "span", lpObjUpdateTag->m_vobjItems );
                        // get the first item has tag name is span
                        lpobjSpanTagInfo = vArrayTagName[0];
                        // Change text for first div item
                        sUpdateText= "";
                        sUpdateText = SubStr( gsctInputFormat.sInitDisp, 4 );
                        
                        lpobjSpanTagInfo->UpdateText( sUpdateText );
                        
                    }
                    else
                    {
                        // initial display of format
                        sFormatInit = GetFormatInitSTrFunc( gsctInputFormat.sFormatName, gsctInputFormat.sInitDisp, gsctInputFormat.sGreap );
                        lpObjUpdateTag->m_sctProperty.sText = sFormatInit;
                    }
                }
                else if ( sctStopInputItem.dwClearMethod == INPUT_CANCEL_SHIJI_BEFORE_DATA )
                {
                    // To return to the input start time, set the information before input start
                    lpObjUpdateTag->m_sctProperty.sText = sBeforeText;
                }
                else
                {
                    return ERROR_CODE_NOT_RANGE;
                }
            }
            else
            {
                return ERROR_CODE_NULL;
            }

            // Modification of the design
            if (( lProcResult == GUI_RET_OK ) &&
               (( sctStopInputItem.dwMask & MASK_R_INPUT_CANCEL_INPUT_DESGIN ) == MASK_R_INPUT_CANCEL_INPUT_DESGIN ))
            {
                // To change to the specified design
                lProcResult = ChangeInputTagDesignFunc( vlpInputItem[dwLoopIndex], ( string )sctStopInputItem.szInputDesign );
            }
            else
            {
                // If unspecified, change design to not select
                lProcResult = ChangeInputTagDesignFunc( vlpInputItem[dwLoopIndex], DESIGN_NOT_SELECT );
            }

            lpObjUpdateTag->ItemUpdateState();
        }
    }

    // Delete all cursor 
    CursorDeleteFunc();
    // Initialization of input-related.
    InitInputGlobalVariableFunc();
    return lProcResult;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  InputCompletRequestFunc
//
//�@�\�@�@��@�F  Create a request when input item is completed
//
//�@�T�@�@�v�@�F  Create a request when input item is completed
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F        CItem*  lpInItem          (I)    Pointer of Current item
//                      string  sInInputData      (I)    String contains Input data
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/06   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::InputCompletRequestFunc(
                                    CItem* lpInItem,
                                    const string &sInInputData )
{
    // Initilize
    LONG                                lProcResult         = GUI_RET_OK;                   // Error code
    string                              sGroupTag           = "";                           // tag group name
    CItem*                              lpObjTagId          = NULL;                         // Input item
    string                              sData               = "";                           // data string
    DWORD                               dwDataKind          = GUI_VALUE_ZERO_DWORD;         // Data kind
    string                              sCheckCharacter     = "";                           // Returned checking character string
    SCT_DATE                            sctDate;                                            // Converted date structure
    BOOL                                bJudgmentDate       = FALSE;                        // Judgment to check date tructure is valid or not
    string                              sDateFormat         = "";                           // Dispalying date string after combine date value and format of item
    SCT_DATE                            sctValidDate;                                       // Return date valid after checking
    LONG                                lFuncResult         = GUI_RET_NG;                   // Function return
    std::smatch                         sm;

    // Reset data
    ( VOID )memset( &sctDate, 0x00, sizeof( sctDate ));
    ( VOID )memset( &sctValidDate, 0x00, sizeof( sctValidDate ));

    // Check parameter
    if ( lpInItem == NULL )
    {
        lProcResult = ERROR_CODE_NOT_EXIST_ID;
        return lProcResult;
    }
    else
    {
        // Do nothing
    }

    // Set screen to be uncontrollable
    lProcResult = ControlEnableAllDisplayFunc( FLG_OBJECT_NOT_ENABLE, E_AREA_GYOMU );

    // Obtaining a group of completion determination tag ID
    if ( lpInItem->m_sctProperty.sTagID == ( string )KEYBOARD_DATA_ENTER )
    {
        sGroupTag = KEYBOARD_DATA_ENTER;
    }
    else
    {
        sGroupTag = lpInItem->m_sctProperty.sTagGroup;
    }
    // Get the Input item
    lpObjTagId = NULL;

    // Get updates tag ID
    if ( gclInputItemTag->m_sctProperty.bParent == TRUE )
    {
        lpObjTagId = gclInputItemTag;
    }
    else
    {
        if ( gclInputItemTag->m_vobjItems.size() != 0 )
        {
            lpObjTagId = FindItemByTagID( TAG_ID_NAME_SET_CHAR_SPAN, gclInputItemTag->m_vobjItems );
            // If not found any items
            if ( lpObjTagId == NULL )
            {
                lProcResult = ERROR_CODE_NULL;
                return lProcResult;
            }
            else
            {
                // Do nothing
            }
        }
        else
        {
            lProcResult = ERROR_CODE_NULL;
            return lProcResult;
        }
    }

    // change the input data by tag group
    if (( sGroupTag == ( string )GROUP_NAME_TENKEY   ) ||
        ( sGroupTag == ( string )KEYBOARD_DATA_ENTER ))
    {
        if ( sInInputData == NULL_STR )
        {
            // Get the display contents of the input items.
            sData = lpObjTagId->m_sctProperty.sText;
        }
        else
        {
            // When input data is existing, set the data by input data
            sData = sInInputData;
        }
       // If the input data is consistent with the initial display character tags, be treated as empty
        if ( sData == lpObjTagId->m_sctProperty.sInitText )
        {
            sData = "";
        }
        else
        {
            // do nothing
        }

        dwDataKind = DATA_KIND_DISP_TEXT;
    }
    // Eki button
    else if ( sGroupTag == ( string )GROUP_NAME_EKI_BTN )
    {
        sData        = lpInItem->m_sctProperty.sValue;
        dwDataKind   = DATA_KIND_BUTTON_TAG_ID;
    }
    // Via button
    else if ( sGroupTag == ( string )GROUP_NAME_KEIYU_BTN )
    {
        if ( regex_search( lpInItem->m_sctProperty.sValue, sm, regex("^" + ( string )TAG_ID_NAME_KEIYU_BTN + "[0-9]+"), std::regex_constants::match_default ) == TRUE )
        {
            // Set data by value of input item
            sData       = lpInItem->m_sctProperty.sValue;
        }
        else
        {
            sData = SelectSendTagIdFunc( lpInItem );
        }        
        dwDataKind = DATA_KIND_BUTTON_TAG_ID;
    }
    // Button has group name that is charge amount or charge or price
    else if (( sGroupTag == ( string )GROUP_NAME_CHARGE_AMOUNT ) ||
             ( sGroupTag == ( string )GROUP_NAME_CHARGE        ) ||
             ( sGroupTag == ( string )GROUP_NAME_PRICE_BTN     ))
    {
        lpObjTagId->m_sctProperty.sText = lpInItem->m_sctProperty.sValue;
        sData      = lpInItem->m_sctProperty.sValue;
        dwDataKind = DATA_KIND_DISP_TEXT;
        lpObjTagId->ItemUpdateState();
    }
    // Button has group name is contractors
    else if ( sGroupTag == ( string )GROUP_NAME_ITAKU )
    {
        sData      = lpInItem->m_sctProperty.sValue;
        dwDataKind = DATA_KIND_DISP_TEXT;
    }
    // Button has group name is Calendar date
    else if ( sGroupTag == ( string )GROUP_NAME_CALENDAR_DATE )
    {
        sData     = lpInItem->m_sctProperty.sValue;

        // Check for date displaying value of item is invlid or not
        // Convert displaying string to date structure
        ConvertStr2DateSct( sData, sctDate );
        bJudgmentDate = JudgeDateValidityFunc( sctDate, &sctValidDate, lFuncResult );
            
        // Date structure is valid
        if ( bJudgmentDate == TRUE )
        {
            sDateFormat = ConvDateFormatFunc( sctDate, gsctInputFormat.sDataFormat );
            if (( sDateFormat == std::to_string(( LONGLONG )ERROR_CODE_NULL )) || 
                ( sDateFormat == std::to_string(( LONGLONG )ERROR_CODE_CONV_ANNO_JAPANESE )))
            {
                sData = lpInItem->m_sctProperty.sValue;
            }
            else
            {
                // Data is set by date structure and displaying format
                sData = sDateFormat;
            }
        }
        else
        {
            // Do nothing
        }

        lpObjTagId->m_sctProperty.sText = sData;
        lpObjTagId->ItemUpdateState();

        dwDataKind = DATA_KIND_DISP_TEXT;
    }
    else
    {
        // Select tag ID to send
        sData      = SelectSendTagIdFunc( lpInItem );
        dwDataKind = DATA_KIND_BUTTON_TAG_ID;
    }

    ClearSendData();
    // Set message number
    SCT_GUI_MSG_R_INPUT_END_VIEW* lpRInputEnd = ( SCT_GUI_MSG_R_INPUT_END_VIEW* ) m_bySendData;
    lpRInputEnd->dwDenbunNo = INPUT_COMPLET_REQUEST_NO;
    
    // Set input data and input tag ID to send to ViewIF process
    sprintf_s( lpRInputEnd->szTagID, "%s", gclInputItemTag->m_sctProperty.sTagID.c_str( ) );
    sprintf_s( lpRInputEnd->szData, "%s", sData.c_str( ) );
    lpRInputEnd->dwDataKind = dwDataKind;
// START: TrungLV 20150424 Update new javascript V10.25
    // ���x�����̐ݒ�.
    if (GROUP_NAME_EKI_BTN == sGroupTag )
    {
        lpInItem->m_sctProperty.sText = regex_replace( lpInItem->m_sctProperty.sText, regex( "\n"), string(""));
        sprintf_s( lpRInputEnd->szLabel, "%s", lpInItem->m_sctProperty.sText.c_str( ));
    }
// END: TrungLV 20150424 Update new javascript V10.25
    // Send data to ViewIF
    lProcResult = SendData( sizeof( SCT_GUI_MSG_R_INPUT_END_VIEW ) );
    return lProcResult;
}



/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  InputCompletResponseFunc
//
//�@�\�@�@��@�F  Responsibility for processing when item input completion
//
//�@�T�@�@�v�@�F  Responsibility for processing when item input completion
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  SCT_PROCESSING_RESULT_C2V_MSG  sctInProcResult      (I)    Input contains the information of complete responsed request
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/09   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::InputCompletResponseFunc(
                                   const SCT_GUI_MSG_A_INPUT_END_VIEW &sctInProcResult )
{
    // Initilize
    LONG                                lProcResult         = GUI_RET_OK;                   // Error code
    string                              sInputTagID         = "";                           // Input Tag ID string
    vector<CItem*>                      vlpItem;                                            // Vector of item pointer
    DWORD                               dwLoopIndex         = GUI_VALUE_ZERO_DWORD;         // loop index
    vector<CItem*>                      vlpInputItem;                                       // Vector contain all input items
    vector<CItem*>                      vlpBatchItem;                                       // Vector contains batch item
    //DWORD                               dwMaxInputCount     = GUI_VALUE_ZERO_DWORD;         // Max input count
    LONG                                lMaxInputCount      = GUI_VALUE_ZERO_LONG;         // Max input count
    string                              sInputCount         = "";                           // Input count string
    string                              sBatchTagID         = "";                           // Tag ID of batch item

    // Reset data
    vlpItem.clear();
    vlpInputItem.clear();
    vlpBatchItem.clear();

    // Check parameter
    if ( gclInputItemTag == NULL )
    {
        return ERROR_CODE_NULL_ID;   // Fix follow TSBJ
    }
    else
    {
        // do nothing
    }

    // Check input tag ID
    sInputTagID = ( string )sctInProcResult.szTagID;

    if (( sctInProcResult.dwMask & MASK_A_INPUT_END_START_TAGID ) == MASK_A_INPUT_END_START_TAGID )
    {
        if ( sInputTagID.size() == 0 )
        {
            return ERROR_CODE_NULL_ID; // Fix follow TSBJ
        }
        else
        {
            // check whether the input item tag ID and current input item tag ID matches
            if ( sInputTagID == gclInputItemTag->m_sctProperty.sTagID )
            {
                // Do nothing 
            }
            else
            {
                return ERROR_CODE_NOT_EXIST_ID; // Fix follow TSBJ
            }
        }
    }
    else
    {
        return ERROR_CODE_NULL_ID; // Fix follow TSBJ
    }

    // Check process result
    if (( sctInProcResult.dwMask & MASK_A_INPUT_END_RESULT ) == MASK_A_INPUT_END_RESULT )
    {
        if (( sctInProcResult.dwResult == DENBUN_RESULT_OK ) ||
            ( sctInProcResult.dwResult == DENBUN_RESULT_NG ))
        {
            // Do nothing
        }
        else
        {
            return ERROR_CODE_NOT_RANGE; // Fix follow TSBJ
        }
    }
    else
    {
        return ERROR_CODE_NULL; // Fix follow TSBJ
    }

    // If the format to input item tag has been set, change the displaying design, etc
    if ( gclInputItemTag->m_sctProperty.sFmt != "" )
    {
        if ( gclInputItemTag->m_sctProperty.sGaikan == GROUP_NAME_IKKATSU_SET )
        {
            // Find input item by input tag ID
            vlpItem =  SearchTagIDFunc( sInputTagID, E_AREA_NULL );

            if ( vlpItem.size() == 0 )
            {
                return ERROR_CODE_NOT_EXIST_ID; // Fix follow TSBJ
            }
            else
            {
                // Do nothing
            }

            string sMaxInputCount = "";

            // Found batch items
            ConvFullHalNumberFunc( gclInputItemTag->m_sctProperty.sText, TRUE , sMaxInputCount );
// Update TrungLV20150502
            lMaxInputCount = atol( sMaxInputCount.c_str());
            for ( dwLoopIndex = 1; ( LONG ) dwLoopIndex <= lMaxInputCount; dwLoopIndex++ )
            {
                // Reset data
                sInputCount = "";
                sBatchTagID = "";
                vlpBatchItem.clear();
                // Get batch of items
                sInputCount  = std::to_string(( LONGLONG )dwLoopIndex );
                sBatchTagID  = gclInputItemTag->m_sctProperty.sTagID + TAG_ID_SPLIT + sInputCount;
                vlpBatchItem = SearchTagIDFunc( sBatchTagID, vlpItem[0]->m_sctProperty.eAreaType );

                if ( vlpBatchItem.size() == 0 )
                {
                    // Do nothing
                }
                else
                {
                    vlpInputItem.push_back( vlpBatchItem[0] );
                }
            }
        }
        else
        {
            vlpInputItem.push_back( gclInputItemTag );
        }

        // Change displaying design for Input items
        dwLoopIndex = GUI_VALUE_ZERO_DWORD;
        for ( dwLoopIndex = 0; dwLoopIndex< vlpInputItem.size(); dwLoopIndex++ )
        {
            lProcResult = ChangeInputTagDesignFunc( vlpInputItem[dwLoopIndex], ( string )sctInProcResult.szInputDesign );
            if ( lProcResult == GUI_RET_OK )
            {
                // Do nothing
            }
            else
            {
                return lProcResult;
            }
        }
    }

    // Delete all cursor
    CursorDeleteFunc();
    // Reset value for all related input item
    InitInputGlobalVariableFunc();
    return lProcResult;
}



/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  InputNoticeFunc
//
//�@�\�@�@��@�F  Create a request for setting up the input item 
//
//�@�T�@�@�v�@�F  Create a request for setting up the input item 
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  String  sInTagID      (I)    String contains tag ID of current Item
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/07   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::InputNoticeFunc(
                                    const string &sInTagID,
                                    const string &sInLabel )
{
    // Initilize
    LONG                lProcResult = GUI_RET_OK;  // Error code

    // Check parameter
#if 0
    if ( sInTagID.size() == 0 )
    {
        return ERROR_CODE_NULL_ID;  // Fix follow TSBJ review
    }
    else
    {
        // Do nothing
    }
#endif

    if ( gclInputItemTag == NULL )
    {
        return ERROR_CODE_NULL_ID;  // Fix follow TSBJ review
    }
    else
    {
        // Do nothing
    }

    ClearSendData();
    SCT_GUI_MSG_N_INPUT_VIEW* lpNInputView = ( SCT_GUI_MSG_N_INPUT_VIEW* ) m_bySendData;
    
    // Set message number
    lpNInputView->dwDenbunNo = INPUT_NOTICE_NO;
    
    // Set input data and input tag ID to send to ViewIF process
    sprintf( lpNInputView->szInputTagID, "%s", gclInputItemTag->m_sctProperty.sTagID.c_str( ) );
    sprintf( lpNInputView->szTagID, "%s", sInTagID.c_str());
// START: TrungLV 20150424 update new javascript V10.25
     // ���x�����̐ݒ�ǉ�
    if ( sInLabel != DEFAULT_LABEL ) 
    {
         sprintf_s( lpNInputView->szLabel, "%s", sInLabel.c_str( ));
    }
// END: TrungLV 20150424 update new javascript V10.25
    // Send data to ViewIF
    lProcResult = SendData( sizeof( SCT_GUI_MSG_N_INPUT_VIEW ) );
    return lProcResult;

}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  KeyBoardInputNoticeFunc
//
//�@�\�@�@��@�F  Perform the request of Key board input notification
//
//�@�T�@�@�v�@�F  Perform the request of Key board input notification
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  SCT_KEY_BOARD_NOTIFY_MSG  sctInKeyBoard      (I)    Input contains the information about key board notification message
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/10   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::KeyBoardInputNoticeFunc(
                                    const SCT_GUI_MSG_N_INPUT_KB_VIEW &sctInKeyBoard )
{
    // Initilize
    LONG                                lProcResult             = GUI_RET_NG;                   // Error code
    BOOL                                bJudgment               = FALSE;                        // Parameter to store judgment value
    string                              sInputTagID             = "";                           // Input Tag ID string
    string                              sInputData              = "";                           // Input Data string
    string                              sData                   = "";                           // Data string
    string                              sCheckCharacter         = "";                           // Check Character string
    BOOL                                bInputTagCheckResult    = FALSE;                        // Check result when checking input item
    CItem*                              lpObjUpdateTag          = NULL;                         // Update item pointer
    vector<CItem*>                      vlpcItem;                                               // vector of Item pointer
    vector<CItem*>                      vlpPasswordItem;                                        // vector of password Item pointer
    CItem*                              lpObjInputTagID         = NULL;                         // Input Item pointer
    vector<CItem*>                      vlpObjInputTagID;                                       // Vector of Input Item pointer
    BOOL                                bUserProcFlg            = FALSE;                        // Flag to check user process or not

    // Reset data
    vlpcItem.clear();
    vlpPasswordItem.clear();
    vlpObjInputTagID.clear();

    // Check area is activity or not
     bJudgment = m_cAreaStore.GetActiveTopIframe()->IsWindowEnabled();

    if ( bJudgment == TRUE )
    {
        // Do nothing
    }
    else
    {
        return GUI_RET_OK;  // Fix follow TSBJ review
    }

    // Check input tag ID of item is valid or not
    sInputTagID = ( string )sctInKeyBoard.szTagID;
    if (( sctInKeyBoard.dwMask & MASK_N_KB_INPUT_TAGID ) == MASK_N_KB_INPUT_TAGID )
    {
        if ( sInputTagID.size() == 0 )
        {
            return GUI_RET_OK;  // Fix follow TSBJ review
        }
        else
        {
          // Do nothing
        }
    }
    else
    {
        return ERROR_CODE_NULL_ID;  // Fix follow TSBJ review
    }

    // Check data of input structure is valid or not
    sData = ( string )sctInKeyBoard.szData;
    if (( sctInKeyBoard.dwMask & MASK_N_KB_INPUT_DATA ) == MASK_N_KB_INPUT_DATA )
    {
        if ( sData.size() == 0 )
        {
            return ERROR_CODE_NULL; // Fix follow TSBJ review
        }
        else
        {
          // Do nothing
        }
    }
    else
    {
        return ERROR_CODE_NULL;  
    }

    // Check input item is exist or not
    if ( gclInputItemTag == NULL )
    {
        return ERROR_CODE_NULL_ID; 
    }
    else
    {
        // The input item that got from inputed structure matches with current input item
        if ( gclInputItemTag->m_sctProperty.sTagID == sInputTagID )
        {
            // Do nothing
        }
        else
        {
            return ERROR_CODE_NOT_EXIST_ID; 
        }
    }

    // If the data is start, reset, tsb, the process will be terminated
    // Data is start button
    if ( sData == ( string )KEYBOARD_DATA_START_BTN )
    {
        lProcResult = StartRequestFunc();
        return lProcResult;
    }
    // Data is reset button
    else if ( sData == ( string )KEYBOARD_DATA_RESET_BTN )
    {
        lProcResult = ResetRequestFunc();
        return lProcResult;
    }
    // Data is tab
    else if (( sData == ( string )KEYBOARD_DATA_TAB     ) ||
             ( sData == ( string )KEYBOARD_DATA_ALT_TAB ))
    {
        return GUI_RET_OK;
    }
    else
    {
        // Do nothing
    }

    // If input item is button, does not execute process
    if ( gclInputItemTag->m_sctProperty.sTagName == ( string )"button" )
    {
        return GUI_RET_OK;
    }
    else
    {
        // do nothing
    }

    // if the format is password, process it on a dedicated function
    if ( gclInputItemTag->m_sctProperty.sFmt == ( string )FMT_NAME_PASSWORD )
    {
        vlpPasswordItem = SearchTagIDFunc( sData, E_AREA_NULL );
        lProcResult = InputPasswordKey_ProcBranchFunc( vlpPasswordItem[0] );
        return lProcResult;
    }
    else
    {
        // Do nothing
    }

    // If input data is enter
    if ( sData == ( string )KEYBOARD_DATA_ENTER )
    {
        ResolutiveDispInputErroFunc( gclInputItemTag, RESOLUTIVE_MODE_ENTER );
        
        // ���[�U�Ǝ���������.
        bUserProcFlg = JudgeUserInputProcFunc( sData, gclInputItemTag->m_sctProperty.sTagID );

        if ( bUserProcFlg == TRUE ) 
        {
            lProcResult = TeikiShubetsuInputProcBranchFunc( sData );
            return lProcResult;
        }
        else
        {
            // Do nothing
        }

        // If input format is birthday
        vlpcItem = SearchTagIDFunc( TAG_ID_NAME_ENTER, E_AREA_NULL );
        if ( vlpcItem.size() == 0 )
        {
            return ERROR_CODE_NULL_ID;
        }
        else
        {
            // Do nothing
        }

        if ( gsctInputFormat.sFormatName == ( string )FMT_NAME_DATE_OF_BIRTH )
        {
            sCheckCharacter = JudgeInputTagBirthOfDateFunc( TRUE );

            if ( sCheckCharacter == "null" )
            {
                // Change input item in error display
                lProcResult = ChangeDispInputErroFunc( gclInputItemTag );
            }
            else
            {
                // If the input data is present (no input errors), complete inputed request
                lProcResult = InputCompletRequestFunc( vlpcItem[0], sCheckCharacter );
            }
        }
        // If input item is not date of birth
        else
        {
            bInputTagCheckResult = JudgeInputTagFunc();
            if ( bInputTagCheckResult == TRUE )
            {
                // Change the displaying content by input item settings
                ChangeInputCharacterFunc( gclInputItemTag, gsctInputFormat );
                sInputData   = ChangeSendDataFunc( gclInputItemTag );
                // Complete the input request
                lProcResult = InputCompletRequestFunc( vlpcItem[0], sInputData );
            }
            else
            {
                // Change the input item in error display
                lProcResult = ChangeDispInputErroFunc( gclInputItemTag );
            }
        }
    }
    else
    {
        // Otherwise
        ResolutiveDispInputErroFunc( gclInputItemTag, RESOLUTIVE_MODE_INPUT );

        // Get input item
        lpObjUpdateTag = NULL;

        // Get updates tag ID
        if ( gclInputItemTag->m_sctProperty.bParent == TRUE )
        {
            lpObjUpdateTag = gclInputItemTag;
        }
        else
        {
            if ( gclInputItemTag->m_vobjItems.size() != 0 )
            {
                lpObjUpdateTag = FindItemByTagID( TAG_ID_NAME_SET_CHAR_SPAN, gclInputItemTag->m_vobjItems );
                // If not found any items
                if ( lpObjUpdateTag == NULL )
                {
                    return ERROR_CODE_NULL;
                }
                else
                {
                    // Do nothing
                }
            }
            else
            {
                return ERROR_CODE_NULL;
            }
        }
        
        // Input item is Date of birth (year two lines) 
        if ( gclInputItemTag->m_sctProperty.sTagID == TAG_ID_NAME_SEINEN_GAPPI )
        {
            if ( lpObjUpdateTag->m_vobjItems.size() == 0 )
            {
                lProcResult = ERROR_CODE_NULL;
                return ERROR_CODE_NULL;
            }
            else
            {
                vlpObjInputTagID = FindItemsByTagName( "span" , lpObjUpdateTag->m_vobjItems );
                if ( vlpObjInputTagID.size() == 0 )
                {
                    return ERROR_CODE_NULL;
                }
                else
                {
                    lpObjInputTagID = vlpObjInputTagID[0];
                }
            }
        }
        else
        {
            lpObjInputTagID = lpObjUpdateTag;
        }

        // If the cursor does not exist, add the cursor
        if ( IsWindow( m_cCursor.m_hWnd ) == FALSE )
        {
            lProcResult = CursorAddFunc( INPUT_INIT_SHIJI_NOT_CHANGE );

            if ( lProcResult == GUI_RET_OK )
            {
                // Do nothing
            }
            else
            {
                return lProcResult;
            }
        }
        else
        {
            // Do nothing
        }

        if ( gbInputItemFirstInitializationFlg == TRUE )
        {
            // Clear the display contents
            lProcResult = CursorAllDeleteCharacterFunc( lpObjInputTagID , TRUE );
            // Change the first character input initialization flag to false
            gbInputItemFirstInitializationFlg = FALSE;
        }
        else
        {
            // Do nothing
        }

        // Change the processing by the data
        
        if ( sData == ( string )KEYBOARD_DATA_BS )
        {
            // Data is BS: Clear one character
            lProcResult = CursorInputDeleteCharacterFunc( lpObjInputTagID );
        }
        else if ( sData == ( string )KEYBOARD_DATA_CLEAR )
        {
            // Data is clear keyboard: processing delete all
            lProcResult = CursorAllDeleteCharacterFunc( lpObjInputTagID , TRUE );
        }
        else
        {
            // Other: performs the character insertion process
            lProcResult = CursorInputUpdateCharacterFunc( lpObjInputTagID, sData, gclInputItemTag->m_sctProperty.lMaxLen );
        }
    }
    return lProcResult;
}

//LONG CGuiViewDlg::SetInputBirthForamtFunc ( string sTagID )
//{
//    LONG lRet = 0;
//    return lRet;
//}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  OtherInputRequestFunc
//
//�@�\�@�@��@�F  Create a request for unspecified input
//
//�@�T�@�@�v�@�F  Create a request for unspecified input
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  String  sInTagID      (I)    String contains tag ID of current Item
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/05   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::OtherInputRequestFunc(
                                   const string &sInTagID )
{
    // Initilize
    LONG                             lProcResult    = GUI_RET_OK;   // Error code
    LPSCT_GUI_MSG_R_OTHER_INPUT_VIEW lpOtherInput   = NULL;         // Other input request pointer

    // Check parameter
    if ( sInTagID.size() == 0 )
    {
        return ERROR_CODE_NULL_ID;
    }
    else
    {
        // Do nothing
    }

    // Set message number
    ClearSendData();
    lpOtherInput = ( LPSCT_GUI_MSG_R_OTHER_INPUT_VIEW ) & m_bySendData;
    lpOtherInput->dwDenbunNo = OTHER_INPUT_REQUEST_NO;

    lProcResult = ControlEnableAllDisplayFunc( FLG_OBJECT_NOT_ENABLE, E_AREA_GYOMU );
    
    // Set input tag ID to send to ViewIF process

    sprintf_s( lpOtherInput->szTagID, "%s", sInTagID.c_str( ) );
        
    // Send data to ViewIF
    
    lProcResult = SendData( sizeof( SCT_GUI_MSG_R_OTHER_INPUT_VIEW ) );
    return lProcResult;

}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  OtherIputRsponseFunc
//
//�@�\�@�@��@�F  Processing after receiving response of unspecified input
//
//�@�T�@�@�v�@�F  Processing after receiving response of unspecified input
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  NA
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/05   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG  CGuiViewDlg::OtherIputRsponseFunc( )
{
    // Initilize
    LONG                lProcResult = GUI_RET_OK;  // Error code
    
    lProcResult = GUI_RET_OK;
    return lProcResult;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  StsIdicationRquestFunc
//
//�@�\�@�@��@�F  Change Status Display
//
//�@�T�@�@�v�@�F  Change Status Display
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  SCT_DISPLAY_STATUS_REQ_MSG  sctInDispStatus      (I)    Input contain the information to change status
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/10   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::StsIdicationRquestFunc(
                                  const  SCT_GUI_MSG_R_STATUS_DISP_VIEW &sctInDispStatus )
{
    // Initilize
    LONG                                lProcResult         = GUI_RET_NG;                   // Error code
    string                              sTagID              = "";                           // Input Tag ID string
    vector<CItem*>                      vlpItem;                                            // Vector of item pointer
    CItem*                              lpObjItem           = NULL;                         // Selected item
    string                              sCondition          = "";                           // 
    string                              sGaikan             = "";                           // Acquisition of appearance
    DWORD                               dwLoopIndex         = GUI_VALUE_ZERO_DWORD;         // loop index
    string                              sFieldName          = "";                           // String contain field name
    string                              sChangeStsClass     = "";                           // Changed Class for style
    string                              sStsClass           = "";                           // Current Class for style
    string                              sText               = "";                           // Displaying text
    string                              sStatus             = "";                           // Current status
    string                              sClass              = "";                           // Current style class

    // Reset value for local parameter
    vlpItem.clear();

    // Check whether the item specified by tag id is present
    if (( sctInDispStatus.dwMask & MASK_R_STATUS_DISP_TAGID ) == MASK_R_STATUS_DISP_TAGID )
    {
        sTagID = ( string )sctInDispStatus.szTagID;

        if ( sTagID.size() == 0 )
        {
            return ERROR_CODE_NULL_ID;
        }
        else
        {
            // Find all item in status area
            vlpItem = SearchTagIDFunc( sTagID, E_AREA_INDICATOR );
            // If the tag ID of the target does not exist, the elements of the array is 0
            if ( vlpItem.size() == 1 )
            {
                lpObjItem = vlpItem[0];
            }
            else
            {
                return ERROR_CODE_NOT_EXIST_ID;
            }
        }
    }
    else
    {
        return ERROR_CODE_NULL_ID;
    }


    // Requested state is the same as the current request
    if (( sctInDispStatus.dwMask & MASK_R_STATUS_DISP_STS_CONDITION ) == MASK_R_STATUS_DISP_STS_CONDITION )
    {
        // Do nothing
    }
     else
    {
        return ERROR_CODE_NULL;
    }

    sCondition = ( string )sctInDispStatus.szCondition;
    
    if ( sCondition == lpObjItem->m_sctProperty.sStatus )
    {
        return GUI_RET_OK;
    }
    else
    {
        // Do nothing
    }

   
    // Acquisition of appearance
    sGaikan = lpObjItem->m_sctProperty.sGaikan;

    // get a status display that matches the appearance from the table
    for ( dwLoopIndex = 0; dwLoopIndex < STS_IDICATION_CLASS_TABLE; dwLoopIndex++ )
    {
        // look for items that match the appearance
        if ( Sts_Idication_Class_Table[dwLoopIndex].sGaikan == sGaikan )
        {
            lProcResult = GUI_RET_OK;
            // get the class that want to change
            sFieldName = sCondition + Sts_Idication_Supplement_Table.sParameterClass;

            if ( sFieldName == ( string )FIELD_NAME_GAIKAN )
            {
                sChangeStsClass = Sts_Idication_Class_Table[dwLoopIndex].sGaikan;
            }
            else if ( sFieldName == ( string )FIELD_NAME_STATUS_NO1 )
            {
                sChangeStsClass = Sts_Idication_Class_Table[dwLoopIndex].sStsno1Class;
            }
            else if ( sFieldName == ( string )FIELD_NAME_STATUS_NO2 )
            {
                sChangeStsClass = Sts_Idication_Class_Table[dwLoopIndex].sStsno2Class;
            }
            else if ( sFieldName == ( string )FIELD_NAME_STATUS_NO3 )
            {
                sChangeStsClass = Sts_Idication_Class_Table[dwLoopIndex].sStsno3Class;
            }
            else if ( sFieldName == ( string )FIELD_NAME_STATUS_NO4 )
            {
                sChangeStsClass = Sts_Idication_Class_Table[dwLoopIndex].sStsno4Class;
            }
            else if ( sFieldName == ( string )FIELD_NAME_STATUS_NO5 )
            {
                sChangeStsClass = Sts_Idication_Class_Table[dwLoopIndex].sStsno5Class;
            }
            else
            {
                return ERROR_CODE_NOT_EXIST_CLASS;
            }

            // Changing the class if the value is set to the class
            if ( Sts_Idication_Supplement_Table.sNothing == sChangeStsClass )
            {
                // Nothing change
                break;
            }
            else
            {
                // Get status of item
                sStatus      = lpObjItem->m_sctProperty.sStatus;
                // Get the current status of class
                sFieldName = "";
                sFieldName = GetDesignStsFunc( sStatus ) + Sts_Idication_Supplement_Table.sParameterClass;
                sStsClass  = "";

                if ( sFieldName == ( string )FIELD_NAME_GAIKAN )
                {
                    sStsClass = Sts_Idication_Class_Table[dwLoopIndex].sGaikan;
                }
                else if ( sFieldName == ( string )FIELD_NAME_STATUS_NO1 )
                {
                    sStsClass = Sts_Idication_Class_Table[dwLoopIndex].sStsno1Class;
                }
                else if ( sFieldName == ( string )FIELD_NAME_STATUS_NO2 )
                {
                    sStsClass = Sts_Idication_Class_Table[dwLoopIndex].sStsno2Class;
                }
                else if ( sFieldName == ( string )FIELD_NAME_STATUS_NO3 )
                {
                    sStsClass = Sts_Idication_Class_Table[dwLoopIndex].sStsno3Class;
                }
                else if ( sFieldName == ( string )FIELD_NAME_STATUS_NO4 )
                {
                    sStsClass = Sts_Idication_Class_Table[dwLoopIndex].sStsno4Class;
                }
                else if ( sFieldName == ( string )FIELD_NAME_STATUS_NO5 )
                {
                    sStsClass = Sts_Idication_Class_Table[dwLoopIndex].sStsno5Class;
                }
                else
                {
                    return ERROR_CODE_NOT_EXIST_CLASS;
                }

                // Change style class
                sClass = lpObjItem->m_sctProperty.sClass;
                std::regex currentSts( sStsClass );
                lpObjItem->m_sctProperty.sClass = std::regex_replace( lpObjItem->m_sctProperty.sClass, currentSts, sChangeStsClass);

                // Change status 
                lpObjItem->m_sctProperty.sStatus = sCondition;
            }

            // Set the displaying text
            sFieldName = "";
            sFieldName = sCondition + Sts_Idication_Supplement_Table.sParameterText;

            if ( sFieldName == ( string )FIELD_NAME_STATUS_TEXT_NO1 )
            {
                sText = Sts_Idication_Class_Table[dwLoopIndex].sStsno1Text;
            }
            else if ( sFieldName == ( string )FIELD_NAME_STATUS_TEXT_NO2 )
            {
                sText = Sts_Idication_Class_Table[dwLoopIndex].sStsno2Text;
            }
            else if ( sFieldName == ( string )FIELD_NAME_STATUS_TEXT_NO3 )
            {
                sText = Sts_Idication_Class_Table[dwLoopIndex].sStsno3Text;
            }
            else if ( sFieldName == ( string )FIELD_NAME_STATUS_TEXT_NO4 )
            {
                sText = Sts_Idication_Class_Table[dwLoopIndex].sStsno4Text;
            }
            else if ( sFieldName == ( string )FIELD_NAME_STATUS_TEXT_NO5 )
            {
                sText = Sts_Idication_Class_Table[dwLoopIndex].sStsno5Text;
            }
            else
            {
                return ERROR_CODE_NOT_EXIST_CLASS;
            }

            // If displaying text is existing
            if ( sText == Sts_Idication_Supplement_Table.sNothing )
            {
                // Do nothing
            }
            else
            {
                lpObjItem->m_sctProperty.sText = sText;
            }

            // Change the displaying style
            lpObjItem->ItemUpdateState(); 
            break;
        }
        else
        {
            // Do nothing
        }
    }
    if ( lProcResult == GUI_RET_NG )
    {
        return ERROR_CODE_NOT_EXIST_CLASS;
    }
    else
    {
        // Do nothing
    }

    return lProcResult;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  DisplayRequestFunc
//
//�@�\�@�@��@�F  Response the screen display from ViewIF
//
//�@�T�@�@�v�@�F  Response the screen display from ViewIF
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  LPVOID                lpData                  (I)    Pointer of received data
//                DWORD                 dwInDataSize            (I)    Data size
//                Map<LONG, LONG> *     lpmapProcessResult      (I)    Pointer of mapping between request number and error code
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/11   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG  CGuiViewDlg::DisplayRequestFunc(
                                    LPVOID           lpInData,
                                    DWORD            dwInDataSize,
                                    map<LONG, LONG>* lpmapOutProcessResult )
{
    // Initialize
    LONG                                                lProcResult = GUI_RET_NG;                       // Error code
    SCT_GUI_MSG_R_DISP_VIEW                             sctScreenDisp;                                  // Structure of screen display
    SCT_GUI_MSG_DISP_TYPE_CHANGE_AREA_VIEW              sctPageDisp;                                    // Structure to display area
    SCT_GUI_MSG_DISP_TYPE_POP_UP_VIEW                   sctPopupDisp;                                   // Structure to display popup
    SCT_GUI_MSG_DISP_TYPE_CALENDAR                      sctCalDisp;                                     // Structure to display calendar
    SCT_GUI_MSG_DISP_TYPE_BTN_VIEW                      sctButtonDsp;                                   // Structure to display button
    SCT_GUI_MSG_DISP_TYPE_TXT_VIEW                      sctTextDisp;                                    // Structure to display text
    SCT_GUI_MSG_DISP_TYPE_CMD_IMG_VIEW                  sctImgDisp;                                     // Structure to display image

    DWORD                                               dwReqCnt            = GUI_VALUE_ZERO_DWORD;     // Request count

    DWORD                                               dwIndex             = GUI_VALUE_ZERO_DWORD;     // Loop index
    DWORD                                               dwKomokuType        = GUI_VALUE_ZERO_DWORD;     // Request type
    AREA_ENUM                                           eArea               = E_AREA_NULL;              // Type of area
    BOOL                                                bJudgeErrorBreak    = FALSE;                    // Flag to break when error

    // reset data
    ( VOID )memset( &sctScreenDisp, 0x00, sizeof( sctScreenDisp ));
    ( VOID )memset( &sctPageDisp, 0x00, sizeof( sctPageDisp ));
    ( VOID )memset( &sctPopupDisp, 0x00, sizeof( sctPopupDisp ));
    ( VOID )memset( &sctCalDisp, 0x00, sizeof( sctCalDisp ));
    ( VOID )memset( &sctButtonDsp, 0x00, sizeof( sctButtonDsp ));
    ( VOID )memset( &sctTextDisp, 0x00, sizeof( sctTextDisp ));
    ( VOID )memset( &sctImgDisp, 0x00, sizeof( sctImgDisp ));

    // Check parameter
    if ( lpInData == NULL )
    {
        ( *lpmapOutProcessResult )[0] = ERROR_CODE_NULL;
        return ERROR_CODE_NULL;
    }
    else
    {
        // Do nothing
    }

    // Get number of request
    ( VOID )memcpy( &sctScreenDisp, lpInData, sizeof ( sctScreenDisp ));

    if ( sctScreenDisp.dwRequestCnt == 0 )
    {
        ( *lpmapOutProcessResult )[0] = ERROR_CODE_NOT_NUMBER;
        return ERROR_CODE_NOT_NUMBER;
    }
    else
    {
        // Set number of request count to local variable
        dwReqCnt = sctScreenDisp.dwRequestCnt;
    }

    lpInData = ( BYTE* )lpInData + sizeof( sctScreenDisp );

    for ( dwIndex = 1; dwIndex <= dwReqCnt; dwIndex++ )
    {
        // Reset data
        dwKomokuType = GUI_VALUE_ZERO_DWORD;
        // Get the displaying request type
        ( VOID )memcpy( &dwKomokuType, lpInData, sizeof( DWORD ));

        switch( dwKomokuType )
        {
        // Request to switch page
        case DISPLAY_REQUEST_TYPE_PAGE_SWITCH:
            // Get data to switch page
            ( VOID )memcpy(&sctPageDisp, lpInData, sizeof( sctPageDisp ));
            // Get Area type
            eArea = sctPageDisp.eAreaType;
            // Call function to switch page
            lProcResult = DisplayBranchPageSwitcFunc( sctPageDisp );
            // Jump to data of next request
            lpInData = ( BYTE* )lpInData + sizeof( sctPageDisp );

            break;

        // Request to display popup
        case DISPLAY_REQUEST_TYPE_POPUP:
            // Get data to display popup
            ( VOID )memcpy(&sctPopupDisp, lpInData, sizeof( sctPopupDisp ));
            // Call function to display popup
            lProcResult = DisplayBranchPopupFunc( sctPopupDisp );
            // Jump to data of next request
            lpInData = ( BYTE* )lpInData + sizeof( sctPopupDisp );
            break;

        // Display calendar
        case DISPLAY_REQUEST_TYPE_CALENDAR:
            // Get data to display calendar
            ( VOID )memcpy(&sctCalDisp, lpInData, sizeof( sctCalDisp ));
            // Call function to display calendar
            lProcResult = DisplayBranchCalendarFunc( sctCalDisp );
            // Jump to data of next request
            lpInData = ( BYTE* )lpInData + sizeof( sctCalDisp );
            break;

        // Request to change properties of button
        case DISPLAY_REQUEST_TYPE_BUTTON:
            // Get data to change properties of button
            ( VOID )memcpy(&sctButtonDsp, lpInData, sizeof( sctButtonDsp ));
            // Get Area type
            eArea = sctButtonDsp.eAreaType;
            // Call function to change properties of button
            lProcResult = DisplayBranchButtonFunc( sctButtonDsp );
            // Jump to data of next request
            lpInData = ( BYTE* )lpInData + sizeof( sctButtonDsp );
            break;

        // Request to change properties of text area
        case DISPLAY_REQUEST_TYPE_TEXT_ITEM:
            // Get data to change properties of text area
            ( VOID )memcpy(&sctTextDisp, lpInData, sizeof( sctTextDisp ));
            // Call function to change properties of text area
            lProcResult = DisplayBranchTextItemFunc( sctTextDisp );
            // Jump to data of next request
            lpInData = ( BYTE* )lpInData + sizeof( sctTextDisp );
            break;

        // Request to change image
        case DISPLAY_REQUEST_TYPE_IMAGE:
            // Get data to change image
            ( VOID )memcpy(&sctImgDisp, lpInData, sizeof( sctImgDisp ));
            // Call function to change image
            lProcResult = DisplayBranchImageFunc( sctImgDisp );
            // Jump to data of next request
            lpInData = ( BYTE* )lpInData + sizeof( sctImgDisp );
            break;

        case DISPLAY_REQUEST_TYPE_TOOLTIP:
            lpInData = ( BYTE* )lpInData + sizeof( SCT_GUI_MSG_DISP_TYPE_CMD_TLTP_VIEW );
            break;

        default:
            
            lProcResult = ERROR_CODE_NOT_RANGE;
            break;
        }

        if ( lProcResult == GUI_RET_NG )
        {
            continue;
        } 
        else
        {
            // Do nothing
        }
        

        switch ( lProcResult )
        {
        case GUI_RET_OK:
            break;

        case RESULT_OK_PAGE_SWITC:
            if ( eArea == E_AREA_GYOMU )
            {
                
                return RESULT_OK_PAGE_SWITC;
            }
            else
            {
                // Do nothing
            }
            break;
        // Internal page switching
        case RESULT_OK_INNER_PAGE_SWITCH:
            gbPageChageLoadFlg = TRUE;
            return RESULT_OK_INNER_PAGE_SWITCH;

        default:

            ( *lpmapOutProcessResult )[dwIndex] = lProcResult;
// Fix PGRelief
            if ( dwKomokuType == DISPLAY_REQUEST_TYPE_PAGE_SWITCH )
            {
                bJudgeErrorBreak = JudgeErrorBreakFunc( dwKomokuType, sctPageDisp.szPageFile, FALSE );
            }
            else if ( dwKomokuType == DISPLAY_REQUEST_TYPE_POPUP )
            {
                bJudgeErrorBreak = JudgeErrorBreakFunc( dwKomokuType, sctPopupDisp.szPageFile, ( BOOL )sctPopupDisp.byMakeOnOff );
            }
            else
            {
                bJudgeErrorBreak = JudgeErrorBreakFunc( dwKomokuType, NULL , FALSE );
            }
                
            if ( bJudgeErrorBreak == TRUE ) 
            {
                // ���f�̏ꍇ�A�������I������.
                return lProcResult;
            }
            else
            {
                // Do nothing
            }
            

            break;
        }

    }

    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  DisplayResponseFunc
//
//�@�\�@�@��@�F  Create and send a responsed result of Displaying screen request
//
//�@�T�@�@�v�@�F  Create and send a responsed result of Displaying screen request
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  map<LONG, LONG> mlInProcResult   (I)     Mapping between request number and processing result
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/02/07   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::DisplayResponseFunc(
                                   map<LONG, LONG> mlInProcResult)
{
    // Initilize
    LONG                            lProcResult = GUI_RET_OK;       // Error code
    std::map<LONG,LONG>::iterator   iterator;                       // iterator
    SCT_GUI_MSG_A_DISP_VIEW*        lpADispView = NULL;
    SCT_GUI_MSG_A_DISP_1REC_VIEW*   lpAErrRec   = NULL;

    // Set message number
    
    ClearSendData();
    lpADispView = ( SCT_GUI_MSG_A_DISP_VIEW* ) m_bySendData;

    lpADispView->dwDenbunNo = DISPLAY_RESPONSE_NO;
    lpADispView->dwErrCount = mlInProcResult.size( );

    // Assign Result
    if ( mlInProcResult.size() == 0 )
    {
        lpADispView->dwResult = DENBUN_RESULT_OK;
    }
    else
    {
        lpADispView->dwResult = DENBUN_RESULT_NG;
    }

    lpAErrRec = ( SCT_GUI_MSG_A_DISP_1REC_VIEW* )( lpADispView + 1 );

    // Set request number and error code
    for( iterator = mlInProcResult.begin(); iterator != mlInProcResult.end(); iterator++ ) 
    {
        lpAErrRec->dwRequestNo = ( DWORD ) iterator->first;
        lpAErrRec->dwViewErrCode[0] = ( DWORD )(iterator->second * (-1));
        ++lpAErrRec;
    }
            
    // Send data to ViewIF
    lProcResult = SendData(( LPBYTE )lpAErrRec - m_bySendData );
    return lProcResult;

}



/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ResetRequestFunc
//
//�@�\�@�@��@�F  Create a request when [Reset] button is pressed
//
//�@�T�@�@�v�@�F  Create a request when [Reset] button is pressed
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  NA
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/05   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::ResetRequestFunc()
{
    // Initilize
    LONG                            lProcResult = GUI_RET_OK;  // Error code
    SCT_GUI_MSG_R_RESET_BTN_VIEW*   lpRResetBtn = NULL;
    

    // Call function to control the displaying
    lProcResult = ControlEnableAllDisplayFunc(
                       FLG_OBJECT_NOT_ENABLE,
                       E_AREA_GYOMU );

    // Set message number
    ClearSendData();
    lpRResetBtn = ( SCT_GUI_MSG_R_RESET_BTN_VIEW* ) m_bySendData;
    lpRResetBtn->dwDenbunNo = RESET_REQUEST_NO;
    
    // Send data to ViewIF
    
    lProcResult = SendData( sizeof( SCT_GUI_MSG_R_RESET_BTN_VIEW) );
    return lProcResult;

}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ResetResponseFunc
//
//�@�\�@�@��@�F  Processing after receiving responsed message that [Reset] button is pressed
//
//�@�T�@�@�v�@�F  Processing after receiving responsed message that [Reset] button is pressed
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  NA
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/05   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG  CGuiViewDlg::ResetResponseFunc()
{
    // Initilize
    LONG                lProcResult = GUI_RET_OK;  // Error code
    // reset data
    

    // Call function to delete the cursor
    CursorDeleteFunc();

    // Reset value for global parameter
    InitInputGlobalVariableFunc();

    // Return function
    lProcResult = GUI_RET_OK;
    return lProcResult;

}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  FareRequestFunc
//
//�@�\�@�@��@�F  Create request when Fare Checking button is pressed
//
//�@�T�@�@�v�@�F  Create request when Fare Checking button is pressed
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  NA
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/05   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG  CGuiViewDlg::FareRequestFunc()
{
    // Initilize
    LONG                            lProcResult = GUI_RET_OK;  // Error code
    // reset data
    SCT_GUI_MSG_R_UNTN_BTN_VIEW*    lpRUntnBtn  = NULL;

    // Call function to control the displaying
    lProcResult = ControlEnableAllDisplayFunc(
                       FLG_OBJECT_NOT_ENABLE,
                       E_AREA_GYOMU );

    // Set message number
    ClearSendData();
    lpRUntnBtn = ( SCT_GUI_MSG_R_UNTN_BTN_VIEW* )m_bySendData;
    lpRUntnBtn->dwDenbunNo = FARE_REQUEST_NO;
    
    // Send data to ViewIF
    
    lProcResult = SendData( sizeof( SCT_GUI_MSG_R_UNTN_BTN_VIEW ) );
    return lProcResult;

}



/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  FareResponseFunc
//
//�@�\�@�@��@�F  Processing after receiving responsed message that [FareResponse] button is pressed
//
//�@�T�@�@�v�@�F  Processing after receiving responsed message that [FareResponse] button is pressed
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  NA
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/05   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG  CGuiViewDlg::FareResponseFunc()
{
    // Initilize
    LONG                lProcResult = GUI_RET_OK;  // Error code
    // reset data
    

    // Call function to delete the cursor
    CursorDeleteFunc();

    // Reset value for global parameter
    InitInputGlobalVariableFunc();

    // Return function
    lProcResult = GUI_RET_OK;
    return lProcResult;

}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  StartRequestFunc
//
//�@�\�@�@��@�F  Create a request when [Start] button is pressed
//
//�@�T�@�@�v�@�F  Create a request when [Start] button is pressed
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  NA
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/05   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG  CGuiViewDlg::StartRequestFunc()
{
    // Initilize
    LONG                            lProcResult = GUI_RET_OK;  // Error code
    // reset data
    SCT_GUI_MSG_R_START_BTN_VIEW*   lpRStartBtn = NULL;

    // Call function to control the displaying
    lProcResult = ControlEnableAllDisplayFunc(
                       FLG_OBJECT_NOT_ENABLE,
                       E_AREA_GYOMU );

    // Set message number    
    ClearSendData();
    lpRStartBtn = ( SCT_GUI_MSG_R_START_BTN_VIEW* ) m_bySendData;
    lpRStartBtn->dwDenbunNo = START_REQUEST_NO;

    // Send data to ViewIF
    
    lProcResult = SendData( sizeof( SCT_GUI_MSG_R_START_BTN_VIEW ) );
    return lProcResult;

}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  StartResponseFunc
//
//�@�\�@�@��@�F  Processing after receiving responsed message that [Start] button is pressed
//
//�@�T�@�@�v�@�F  Processing after receiving responsed message that [Start] button is pressed
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  NA
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/05   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG  CGuiViewDlg::StartResponseFunc()
{
    // Initilize
    LONG                lProcResult = GUI_RET_OK;  // Error code
    
    // reset data
    

    // Call function to delete the cursor
    CursorDeleteFunc();

    // Reset value for global parameter
    InitInputGlobalVariableFunc();

    // Return function
    lProcResult = GUI_RET_OK;
    return lProcResult;

}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ErrorNoticeFunc
//
//�@�\�@�@��@�F  Create a message when processing is error
//
//�@�T�@�@�v�@�F  Create a message when processing is error
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  LONG    lInErrCode      (I)      Error code when processing
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/06   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::ErrorNoticeFunc(
                                   LONG lInErrCode )
{
    // Initilize
    LONG                        lProcResult = GUI_RET_OK;  // Error code
    SCT_GUI_MSG_N_ERROR_VIEW*   lpNError    = NULL;

    // Check error code is valid or not
    if ( lInErrCode == GUI_VALUE_ZERO_LONG )
    {
        return ERROR_CODE_NULL;
    }
    else
    {
        // Do nothing
    }

    ClearSendData();
    lpNError = ( SCT_GUI_MSG_N_ERROR_VIEW* ) m_bySendData;
    lpNError->dwDenbunNo = ERROR_NOTICE_NO;
    lpNError->dwErrCode = lInErrCode  * (-1);

    // Send data to ViewIF
    
    lProcResult = SendData( sizeof( SCT_GUI_MSG_N_ERROR_VIEW ) );
    return lProcResult;

}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  CommonResponseFunc
//
//�@�\�@�@��@�F  Create common response message that contains result and error code when receiving message from ViewIF to View
//
//�@�T�@�@�v�@�F  Create common response message that contains result and error code when receiving message from ViewIF to View
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  LONG    lInTelegramNo      (I)     Response message number
//                LONG    lInResult          (I)     Error information in the case of request processing does not run
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/06   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::CommonResponseFunc(
                                   LONG lInTelegramNo,
                                   LONG lInResult)
{
    // Initilize
    LONG                        lProcResult = GUI_RET_OK;  // Error code
    SCT_GUI_MSG_A_INIT_VIEW*    lpCommonRes = NULL;

    // Check error code is valid or not
    if (( lInTelegramNo == INPUT_START_RESPONSE_NO ) &&
        ( lInResult     == GUI_RET_OK              ))
    {
        // Call function to control the displaying
        ControlEnableAllDisplayFunc(
                           FLG_OBJECT_ENABLE,
                           E_AREA_GYOMU );
    }
    else
    {
        // Do nothing
    }


    ClearSendData();
    // Set message number
    lpCommonRes = ( SCT_GUI_MSG_A_INIT_VIEW* ) m_bySendData;

    lpCommonRes->dwDenbunNo = ( DWORD )lInTelegramNo;
    lpCommonRes->dwErrCode = ( lInResult * -1 );

    // Check result is ok or ng
    if ( lInResult == GUI_RET_OK )
    {
        // Set message result
        lpCommonRes->dwResult = DENBUN_RESULT_OK;
    }
    else
    {
        // Set message result
        lpCommonRes->dwResult = DENBUN_RESULT_NG;
    } 
        
    // Send data to ViewIF
    
    lProcResult = SendData( sizeof( SCT_GUI_MSG_A_INIT_VIEW ) );
    return lProcResult;

}




/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  InputProcBranchFunc
//
//�@�\�@�@��@�F  Handle event when button is pressed
//
//�@�T�@�@�v�@�F  Handle event when button is pressed
//
//�@�߁@��@�l�F  VOID
//
//�@���@�@���@�F  CItem*       lpInItem                (I)              Pointer of selected item
//                string       sInClickBranchMode      (I)              String contains the mode of clicked branch
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/10   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

void CGuiViewDlg::InputProcBranchFunc(
                                   CItem* lpInItem,
                                   DWORD  dwInClickBranchMode )
{
    // Initilize
    LONG                                lProcResult          = GUI_RET_NG;                   // Error code
    string                              sTagID               = "";                           // Input Tag ID string
    string                              sSendTagID           = "";                           // Send tag ID string
    string                              sGroupName           = "";                           // Group name string
    string                              sInputData           = "";                           // Input data string
    BOOL                                bInputTagCheckResult = FALSE;                        // Input Tag Check result
    string                              sItemValue           = "";                           // String contains item's Tag value
    string                              sItemTagID           = "";                           // String contains item's Tag ID
    BOOL                                bCheckFound          = FALSE;                        // Judgment matching string or not
    string                              sLabel               = "";
    std::smatch                         sm;
    BOOL                                bUserProcFlg         = FALSE;                        // Flag to determine who process
    LONG                                lMaxOnZaseki         = 0;
    // Check parameter
    if ( lpInItem == NULL )
    {
        return;
    }

    // Execute the button press function if a specific button is pressed
    sTagID = lpInItem->m_sctProperty.sTagID;

    // Start button is pressed
    if ( sTagID == TAG_ID_NAME_START_BTN )
    {
        StartRequestFunc();
        return;
    }
    // Reset button is pressed
    else if ( sTagID == TAG_ID_NAME_RESET_BTN )
    {
        ResetRequestFunc();
        return;
    }
    // Fare inquiry button button is pressed
    else if ( sTagID == TAG_ID_NAME_UNCHIN_SHOKAI )
    {
        FareRequestFunc();
        return;
    }
    else
    {
        // Do nothing
    }

    // If the branch mode of button is set
    // Unspecified input request
    if ( dwInClickBranchMode == CLICK_BRANCHMODE_OTHER_INPUT )
    {
        // Send an unspecified input request
        sSendTagID = SelectSendTagIdFunc( lpInItem );
        OtherInputRequestFunc( sSendTagID );
        return;
    }
    else if ( dwInClickBranchMode == CLICK_BRANCHMODE_NOT_APPOINT )
    {
        // Do nothing
    }
    else
    {
        // Do nothing
    }

    if ( gclInputItemTag == NULL )
    {
        // Do nothing
    }
    else
    {
        bUserProcFlg = JudgeUserInputProcFunc( lpInItem->m_sctProperty.sTagID, gclInputItemTag->m_sctProperty.sTagID );

        if ( bUserProcFlg == TRUE )
        {
            lProcResult = TeikiShubetsuInputProcBranchFunc( lpInItem->m_sctProperty.sTagID );
            return;
        }
        else
        {
            // Do nothing
        }
    }


    // Check whether the input item is NULL or not
    if ( gclInputItemTag == NULL )
    {
        // Pressed button is eki button
        if ( lpInItem->m_sctProperty.sTagGroup == GROUP_NAME_EKI_BTN )
        {
            // In the case, station button is pressed, send value of item
            OtherInputRequestFunc( lpInItem->m_sctProperty.sValue );
        }
        else
        {
            sSendTagID = SelectSendTagIdFunc( lpInItem );
            OtherInputRequestFunc( sSendTagID );
        }
    }
    else
    {
        // Get group name
        sGroupName = lpInItem->m_sctProperty.sTagGroup;
        if ( sGroupName == GROUP_NAME_TENKEY )
        {
            // 
            if ( gclInputItemTag->m_sctProperty.sTagName == ( string )"button" )
            {
                return;
            }
            else
            {
                // Do nothing
            }

            // 
            if ( gclInputItemTag->m_sctProperty.sFmt == FMT_NAME_PASSWORD )
            {
                InputPasswordProcBranchFunc( lpInItem );
                return;
            }
            else
            {
                // Do nothing
            }

            // Process Inputed Notification
            InputNoticeFunc( lpInItem->m_sctProperty.sTagID );

            if ( lpInItem->m_sctProperty.sTagID == TAG_ID_NAME_ENTER )
            {
                // Clear error setting
                ResolutiveDispInputErroFunc( gclInputItemTag, RESOLUTIVE_MODE_ENTER );
                // 
                if ( gsctInputFormat.sFormatName == FMT_NAME_DATE_OF_BIRTH )
                {
                    sInputData = JudgeInputTagBirthOfDateFunc( TRUE );
                    if ( sInputData != "null" )
                    {
                        // Complete the inputed request
                        InputCompletRequestFunc( lpInItem, sInputData );
                    }
                    else
                    {
                        // 
                        ChangeDispInputErroFunc( gclInputItemTag );
                    }
                }
                else
                {
                    bInputTagCheckResult = JudgeInputTagFunc();
                    if ( bInputTagCheckResult == TRUE )
                    {
                        ChangeInputCharacterFunc( gclInputItemTag, gsctInputFormat );
                        sInputData = ChangeSendDataFunc( gclInputItemTag );
                        // Complete the inputed request
                        InputCompletRequestFunc( lpInItem, sInputData );
                    }
                    else
                    {
                        ChangeDispInputErroFunc( gclInputItemTag );
                    }
                }
            }
            else
            {
                if ( gsctInputFormat.sFormatName == FMT_NAME_DATE_OF_BIRTH )
                {
                    lProcResult = ChangeDispCalendarEraFunc( lpInItem );
                }
                else if ( gsctInputFormat.sFormatName == FMT_NAME_SCHOOL_YEAR )
                {
                    lProcResult = ChangeDispSchoolYearFunc( lpInItem );
                }
                else
                {
                    // Do nothing
                }

                // 
                if ( lProcResult == GUI_RET_OK )
                {
                    // Do nothing
                }
                else
                {
                    // Clear error setting
                    ResolutiveDispInputErroFunc( gclInputItemTag, RESOLUTIVE_MODE_INPUT );
                    // 
                    CursorInputBranchFunc( lpInItem );
                }
            }
        }
        else if ( sGroupName == GROUP_NAME_MONTH_MOVE )
        {
            // Process Inputed Notification
            InputNoticeFunc( lpInItem->m_sctProperty.sTagID );
            // 
            SettingDisplayCalendarFunc( lpInItem );
        }
        else if ( sGroupName == GROUP_NAME_CALENDAR_DATE )
        {
            // 
            if ( gclInputItemTag->m_sctProperty.sTagName == ( string )"button" )
            {
                return;
            }
            else
            {
                // Do nothing
            }
            // Clear error setting
            ResolutiveDispInputErroFunc( gclInputItemTag, RESOLUTIVE_MODE_ENTER );
            // Process Inputed Notification
            InputNoticeFunc( lpInItem->m_sctProperty.sTagID );
            // Complete the inputed request
            InputCompletRequestFunc( lpInItem, "" );
            // 
            ChangeInputButtonDesignFunc( lpInItem );
        }
        else if (( sGroupName == GROUP_NAME_CHARGE_AMOUNT ) ||
                 ( sGroupName == GROUP_NAME_ITAKU         ) ||
                 ( sGroupName == GROUP_NAME_CHARGE        ) ||
                 ( sGroupName == GROUP_NAME_PRICE_BTN     ) ||
                 ( sGroupName == GROUP_NAME_COUPON        ))
        {
            if ( gclInputItemTag->m_sctProperty.sTagName == ( string )"button" )
            {
                return;
            }
            else
            {
                // Do nothing
            }
            // Clear error setting
            ResolutiveDispInputErroFunc( gclInputItemTag, RESOLUTIVE_MODE_ENTER );
            // Process Inputed Notification
            InputNoticeFunc( lpInItem->m_sctProperty.sTagID );
            // Complete the inputed request
            InputCompletRequestFunc( lpInItem, "" );
        }
        else if ( sGroupName == GROUP_NAME_ZASEKI )
        {
            if ( gclInputItemTag->m_sctProperty.sTagName == ( string )"button" )
            {
                return;
            }
            else
            {
                // Do nothing
            }
            //
             string sMaxOnZaseki = "";
            ConvFullHalNumberFunc( gclInputItemTag->m_sctProperty.sText, true , sMaxOnZaseki );
// Start TrungLV 20150502
            lMaxOnZaseki = atol(sMaxOnZaseki.c_str());
            if ( lMaxOnZaseki <= 0 )
            {
                lMaxOnZaseki = 0;
            }
            else
            {
                // Do nothing
            }
            lProcResult = InputExpressSeatFunc( lpInItem, (DWORD) lMaxOnZaseki );
// End TrungLV 20150502
            // 
            if ( lProcResult == GUI_RET_OK )
            {
                InputNoticeFunc( lpInItem->m_sctProperty.sTagID );
            }
            else
            {
                // Do nothing
            }
        }
        else if ( sGroupName == GROUP_NAME_EKI_BTN )
        {
            if ( gclInputItemTag->m_sctProperty.sTagName == ( string )"button" )
            {
                OtherInputRequestFunc( lpInItem->m_sctProperty.sValue );
            }
            else
            {
                // Clear error setting
                ResolutiveDispInputErroFunc( gclInputItemTag, RESOLUTIVE_MODE_ENTER );
                // Complete the inputed request
                InputCompletRequestFunc( lpInItem, "" );
            }
        }
        // Via button
        else if ( sGroupName == GROUP_NAME_KEIYU_BTN )
        {
            regex MatchStr1( "^"+ ( string )TAG_ID_NAME_KEIYU_BTN + "[0-9]+" );
            // Get the value of item
            sItemValue = lpInItem->m_sctProperty.sValue;

            bCheckFound = regex_search( sItemValue, sm, MatchStr1, std::regex_constants::match_default );
            // Match with string
            if ( bCheckFound == TRUE )
            {
                // Clear error setting
                ResolutiveDispInputErroFunc( gclInputItemTag, RESOLUTIVE_MODE_ENTER );
                // Complete the inputed request
                InputCompletRequestFunc( lpInItem, "" );
            }
            else
            {
                if ( sGroupName == gclInputItemTag->m_sctProperty.sTagGroup )
                {
                    // Clear error setting
                    ResolutiveDispInputErroFunc( gclInputItemTag, RESOLUTIVE_MODE_ENTER );
                    // Complete the inputed request
                    InputCompletRequestFunc( lpInItem, "" );
                }
                else
                {
                    // 
                    sSendTagID = SelectSendTagIdFunc( lpInItem );
                    OtherInputRequestFunc( sSendTagID );
                }
            }
        }
        // 
        else if ( sGroupName == GROUP_NAME_RESSHA_SHUBETSU )
        {
            regex MatchStr2( "^.*_" + ( string )GROUP_NAME_RESSHA_SHUBETSU + "_[0-9]" );
            // Get the value of item
            sItemTagID = lpInItem->m_sctProperty.sTagID;
            
            bCheckFound = regex_search( sItemTagID, sm, MatchStr2, std::regex_constants::match_default );
            // Match with string
            if ( bCheckFound == TRUE )
            {
                // Complete the inputed request
                InputCompletRequestFunc( lpInItem, "" );
            }
            else
            {
                // 
                sSendTagID = SelectSendTagIdFunc( lpInItem );
                OtherInputRequestFunc( sSendTagID );
            }
        }
        else if ( sGroupName == gclInputItemTag->m_sctProperty.sTagGroup )
        {
            // Clear error setting
            ResolutiveDispInputErroFunc( gclInputItemTag, RESOLUTIVE_MODE_ENTER );
            // Complete the inputed request
            InputCompletRequestFunc( lpInItem, "" );
        }
        else if  (( sGroupName == GROUP_NAME_SHASEN_BTN  ) ||    // Shasen button
                 ( sGroupName == GROUP_NAME_ROSEN_BTN   )  ||
                 ( sGroupName == GROUP_NAME_PAGE_SHITEI ))      // Rosen button
        {
            if (( sGroupName == GROUP_NAME_SHASEN_BTN  ) ||    // Shasen button
                 ( sGroupName == GROUP_NAME_ROSEN_BTN   ))
            {
// START: TrungLV 20150424 update JS V10.25
                sLabel = regex_replace( lpInItem->m_sctProperty.sText, regex( "\n"), string(""));
// END: TrungLV 20150424 update JS V10.25
            }

            // TSDV-LanLTM-20150525-Update Javascript to version 10.33
            // Disable all screen
            ControlEnableAllDisplayFunc( FLG_OBJECT_NOT_ENABLE, E_AREA_GYOMU );

            string sTagID = lpInItem->m_sctProperty.sTagID;
            lProcResult = SwitchOperationPageFunc( lpInItem );

            // Enable all screen
            ControlEnableAllDisplayFunc( FLG_OBJECT_ENABLE, E_AREA_GYOMU );
            // 
            if (( lProcResult == GUI_RET_OK ) ||
                ( lProcResult == RESULT_OK_INNER_PAGE_SWITCH ))
            //  TSDV-LanLTM-20150525-Update Javascript to version 10.33 -END
            {
                InputNoticeFunc( sTagID, sLabel );
            }
            else
            {
                sSendTagID = SelectSendTagIdFunc( lpInItem );
                OtherInputRequestFunc( sSendTagID );
            }
        }
        else
        {
            // Group Tag ID is not group name of current input item
            sSendTagID = SelectSendTagIdFunc( lpInItem );
            OtherInputRequestFunc( sSendTagID );
        }
    }
    return;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  LabelOnClickProcBranchFunc
//
//�@�\�@�@��@�F  Handle event when inputting to a text label
//
//�@�T�@�@�v�@�F  Handle event when inputting to a text label
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  CItem* lpInItem                (I)              Pointer of selected item
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/11   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
void CGuiViewDlg::LabelOnClickProcBranchFunc(
                      CItem* lpInItem )
{
    // Initilize
    LONG                             lProcResult = GUI_RET_OK;  // Error code
    vector<CItem*>                   vlpItem        ;   // Vector of item pointers
    string                           sTagID      = "";  // Tag ID string
    string                           sOtherTagID = "";  // Other tag ID string


    // Reset data
    vlpItem.clear();


    // Check parameter
    if ( lpInItem == NULL )
    {
        return ;
    }
    else
    {
        // Do nothing
    }

    // If item has format and status is active
    if (( lpInItem->m_sctProperty.sFmt    != ""   ) &&
        ( lpInItem->m_sctProperty.bEnable == TRUE ))
    {
        sTagID      = lpInItem->m_sctProperty.sTagID;
        sOtherTagID = SubStr( sTagID, 0, ( sTagID.length() - 2 ));
        
        // Find all all items match with other tasg ID
        vlpItem = SearchTagIDFunc( sOtherTagID, E_AREA_NULL );

        if (( vlpItem.size() > 2 ) &&
            ( vlpItem[0]->m_sctProperty.sGaikan == GROUP_NAME_IKKATSU_SET ))
        {
            // 
            sTagID = SubStr( sTagID, 0, ( sTagID.length() - 2 ));
        }
        else
        {
            // do nothing
        }
        lProcResult = OtherInputRequestFunc( sTagID );
    }
    else
    {
        // Do nothing
    }
    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  TabOnClickProcBranchFunc
//
//�@�\�@�@��@�F  Handle event when press Tab in view to switch page
//
//�@�T�@�@�v�@�F  Handle event when press Tab in view to switch page
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  CItem* lpInItem                (I)              Pointer of selected item
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/06   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG  CGuiViewDlg::TabOnClickProcBranchFunc(
                                   CItem* lpInItem )
{
    // Initilize
    LONG               lProcResult= GUI_RET_OK;   // Error code


    // Check parameter
    if ( lpInItem == NULL )
    {
        return ERROR_CODE_NULL_ID;
    }
    else
    {
        // Do nothing
    }

    // Check whether status of item is disable or not
    if ( lpInItem->m_sctProperty.bEnable == FALSE )
    {
        return GUI_RET_OK;
    }
    else
    {
        // Do nothing
    }

    // Call function to send notice to ViewIF
    lProcResult = InputNoticeFunc( lpInItem->m_sctProperty.sTagID );

    // Switch tab displaying
    
    lProcResult = SwitchOperationPageFunc( lpInItem );

    // Check return function
    if ( lProcResult == GUI_RET_OK )
    {
        return lProcResult;
    }
    else
    {
        // Do nothing
    }

    // Tab display switching process
    
    lProcResult = ChangeVisibleInsideTabFunc( lpInItem );

    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ContenaKirikaeFunc
//
//�@�\�@�@��@�F  Handle event when press Tab in view to switch page
//
//�@�T�@�@�v�@�F  Handle event when press Tab in view to switch page
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  CItem* lpInItem                (I)              Pointer of selected item
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/06   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG CGuiViewDlg::ContenaKirikaeFunc( 
                            const    string &sInContenaKirikaeId, 
                            const    string &sInStartNo, 
                            const    string &sInEndNo, 
                                     CItem* lpInObjItem )
{
    // Initialize
//    LONG                       lProcResult      = GUI_RET_OK;           // Error code
    vector<CItem*>             vlpItem;                                 // Vector of item pointer
    LONG                       lFuncResult      = GUI_VALUE_ZERO_LONG; // Function result
    string                     sStartCount      = "";                   // Start count string
    //DWORD                      lStartCount     = GUI_VALUE_ZERO_DWORD; // Start count number
    LONG                       lStartCount      = GUI_VALUE_ZERO_LONG; // Start count number
    string                     sEndCount        = "";                   // End count string
    //DWORD                      lEndCount       = GUI_VALUE_ZERO_DWORD; // End count number
    LONG                       lEndCount       = GUI_VALUE_ZERO_LONG; // End count number
    string                     sContainer       = "";                   // Container string
    DWORD                      dwIndex          = GUI_VALUE_ZERO_DWORD; // Loop Index
    DWORD                      dwConIndex       = GUI_VALUE_ZERO_DWORD; // Container index
    vector<CItem*>             vHiddenItem;                             // Vector of hidden item
    string                     sTagID           = "";                   // Tag ID string

    // Initialize
    vlpItem.clear();
    vHiddenItem.clear();

    // Check parameters
    if ( sInContenaKirikaeId == "" )
    {
        return ERROR_CODE_NULL_ID;
    }
    else
    {
        // Do nothing
    }


    // Find item by Tag ID
    vlpItem = SearchTagIDFunc( sInContenaKirikaeId, E_AREA_NULL );
    
    if ( vlpItem.size() == 0 )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    else
    {
        // Do nothing
    }

    // Check start number is number or not
    lFuncResult = JudgeNumberFunc( sInStartNo );

    if ( lFuncResult == JUDGE_FULL_NUMBER )
    {
        ConvFullHalNumberFunc( sInStartNo, TRUE , sStartCount );
// TrungLV 20150502
        lStartCount = atol( sStartCount.c_str() );
    }
    else if ( lFuncResult == JUDGE_HALF_NUMBER )
    {
// TrungLV 20150502
        lStartCount = atol( sInStartNo.c_str() );
    }
    else
    {
        return ERROR_CODE_NOT_DATE;
    }


    // Check end number is number or not
    lFuncResult = JudgeNumberFunc( sInEndNo );

    if (lFuncResult == JUDGE_FULL_NUMBER )
    {
        ConvFullHalNumberFunc( sInEndNo, TRUE , sEndCount );
// TrungLV 20150502
        lEndCount = atol( sEndCount.c_str() );
    }
    else if ( lFuncResult == JUDGE_HALF_NUMBER )
    {
// TrungLV 20150502
        lEndCount = atol( sInEndNo.c_str() );
    }
    else
    {
        return ERROR_CODE_NOT_DATE;
    }

    // 
    if ( lpInObjItem == NULL )
    {
        // Do nothing
    }
    else
    {
        if ( lpInObjItem->m_sctProperty.bEnable == FALSE )
        {
            return GUI_RET_OK;
        }
        else
        {
            // Do nothing
        }

        InputNoticeFunc( lpInObjItem->m_sctProperty.sTagID );
        ChangeInputButtonDesignFunc( lpInObjItem );
    }

    // 
    sContainer = sInContenaKirikaeId;
    std::regex Container( "[0-9]+$" );
    sContainer = std::regex_replace( sContainer, Container, ( string )"");

    for ( dwIndex = 0; dwIndex < vlpItem.size(); dwIndex++ )
    {
        //vlpItem[dwIndex]->m_sctProperty.bVisibilityHidden = FALSE;
        vlpItem[dwIndex]->UpdateVisibility( TRUE );
// TrungLV 20150502
        for ( dwConIndex = lStartCount; ( LONG ) dwConIndex <= lEndCount; dwConIndex++ )
        {
            sTagID = sContainer + std::to_string(( LONGLONG )dwConIndex );

            if ( sInContenaKirikaeId == sTagID )
            {
                continue;
            }
            else
            {
                // Do nothing
            }

            vHiddenItem = SearchTagIDFunc( sTagID, E_AREA_NULL );

            if ( vHiddenItem.size() == 0 )
            {
                continue;
            }
            else
            {
                //vHiddenItem[0]->m_sctProperty.bVisibilityHidden = TRUE;
                vHiddenItem[0]->UpdateVisibility( FALSE );
            }
        }
    }

    return GUI_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  OnCopyData
//
//�@�\�@�@��@�F  Receive message from ViewIF
//
//�@�T�@�@�v�@�F  Receive message from ViewIF
//
//�@�߁@��@�l�F  Void
//
//�@���@�@���@�F  CWnd*             lpWnd                  // Window handle,
//                COPYDATASTRUCT*   lpCopyDataStruct       // Data ponter
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/02/27   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////

afx_msg BOOL CGuiViewDlg::OnCopyData(
                      CWnd*             lpWnd,
                      COPYDATASTRUCT*   lpCopyDataStruct )
{
    //CDstruct->cbData = lpCopyDataStruct->cbData;
    //CDstruct->dwData = lpCopyDataStruct->dwData;
    //CDstruct->lpData = new BYTE[lpCopyDataStruct->cbData];
    //memcpy( CDstruct->lpData, lpCopyDataStruct->lpData, lpCopyDataStruct->cbData );

    COPYDATASTRUCT   *CDstruct = new COPYDATASTRUCT;
    CDstruct->cbData = lpCopyDataStruct->cbData;
    CDstruct->dwData = lpCopyDataStruct->dwData;
    CDstruct->lpData = new BYTE[lpCopyDataStruct->cbData];
    memcpy(CDstruct->lpData, lpCopyDataStruct->lpData, lpCopyDataStruct->cbData);

    PostMessage( RECEIVE_MSG_FROM_VIEW_IF, ( WPARAM ) CDstruct );

    // LiemTT: Moving to OnNexaMsgRefreshCusor in case prevent flicker is TRUE
    if ( DRAW_TOPIFRAME_PREVENT_CLICKER == FALSE )
    {
        if ( m_bIsClosed == FALSE )
        {
            if ( m_pInitDlg != NULL && IsWindow( m_pInitDlg->m_hWnd ) )
            {
                m_pInitDlg->KillTimer( ID_TIMER_MARU );
                m_pInitDlg->KillTimer( ID_TIMER_EY5000 );
                m_bIsClosed = TRUE;
                m_pInitDlg->DestroyWindow();
            }
            else {} // Do nothing

            delete m_pInitDlg;
            m_pInitDlg = NULL;
        }
    }
    else {} // Do nothing

    return TRUE; 
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SelectSendTagIdFunc
//
//�@�\�@�@��@�F  Choose the Tag ID to send from View process to ViewIF process
//
//�@�T�@�@�v�@�F  Choose the Tag ID to send from View process to ViewIF process
//
//�@�߁@��@�l�F  Tag ID string
//
//�@���@�@���@�F  CItem* lpInItem                (I)              Pointer of selected item
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/13   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
std::string CGuiViewDlg::SelectSendTagIdFunc(
                             CItem* lpInItem )
{
    // Initialize
    string                  sTagID     = "";            // Tag ID string
    string                  sStsDesign = "";            // Status design

    // Check parameter
    if ( lpInItem == NULL )
    {
        return "";
    }
    else
    {
        // Do nothing
    }

    if ( lpInItem->m_sctProperty.sAltTagID == "" )
    {
        sTagID = lpInItem->m_sctProperty.sTagID;
    }
    else
    {
        // Get status design
        sStsDesign = GetDesignStsFunc( lpInItem->m_sctProperty.sStatus );

        // If the attribute is present, change the ID to be sent by the status design
        if ( sStsDesign == DESIGN_BTN_ON )
        {
            // Status design is on
            sTagID = lpInItem->m_sctProperty.sAltTagID;
        }
        else
        {
            // Others
            sTagID = lpInItem->m_sctProperty.sTagID;
        }
    }

    return sTagID;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  GetDesignStsFunc
//
//�@�\�@�@��@�F  Get design status of selected item
//
//�@�T�@�@�v�@�F  Get design status of selected item
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  string sInStsDesign                (I)              Status design string
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/13   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
std::string CGuiViewDlg::GetDesignStsFunc(
                        const  string &sInStsDesign )
{
    // Initialize
    string                  sTagID     = "";            // Tag ID string
    string                  sStsDesign = "";            // Status design
    std::smatch             sm;

    // Check parameter
    if ( sInStsDesign == "" )
    {
        return "";
    }
    else
    {
        // Do nothing
    }

    sStsDesign = sInStsDesign;
    // Check the status design is special status design
    if ( regex_search( sInStsDesign, sm, regex( "^.*" + ( string )SPEC_ASSIGN_CLASS + ".*" + ( string )SPEC_ASSIGN_CLASS + "$" ), std::regex_constants::match_default ) == TRUE )
    {
        // Change if status design is Special status design
        std::regex currentSts((string )SPEC_ASSIGN_CLASS + ".*" + ( string )SPEC_ASSIGN_CLASS + "$" );
        sStsDesign = std::regex_replace( sStsDesign, currentSts, ( string )"");
    }
    else
    {
        // Do nothing
    }

    if ( sInStsDesign == DESIGN_INPUT_ERROR )
    {
        // Do nothing
    }
    else
    {
        // Change value when status design is error
        if ( regex_search( sInStsDesign, regex( "^" + ( string )DESIGN_INPUT_ERROR )) == TRUE )
        {
            std::regex currentSts( "^" + ( string )DESIGN_INPUT_ERROR );
            sStsDesign = std::regex_replace( sStsDesign, currentSts, ( string )"");
        }
        else
        {
            // Do nothing
        }
    }
    return sStsDesign;
}



/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  InitInputGlobalVariableFunc
//
//�@�\�@�@��@�F  Initialize value for global parameter
//
//�@�T�@�@�v�@�F  Initialize value for global parameter
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  NA
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/13   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::InitInputGlobalVariableFunc()
{
    // Initilize
    LONG                                lProcResult = GUI_RET_OK;  // Error code

    // Reset data for all information related to global input item
    gclInputItemTag                     = NULL;     // Reset data for global input item
    gsInputItemBeforeData.clear();                  // Reset data for before date of input item
    gbInputItemFirstInitializationFlg   = false;    // Reset data for first initialization flag of input item
    
    // Reset Input guide format
    gsctInputFormat.sFormatName          = "";
    gsctInputFormat.sTagId               = "";
    gsctInputFormat.sGreap               = "";
    gsctInputFormat.sEraName             = "";
    gsctInputFormat.sDataFormat          = "";
    gsctInputFormat.sInputGuide          = "";
    gsctInputFormat.sInitDisp            = "";
    gsctInputFormat.lRangeStart          = GUI_VALUE_ZERO_LONG;
    gsctInputFormat.lRangeEnd            = GUI_VALUE_ZERO_LONG;
    gsctInputFormat.bLeftJustify         = FALSE;
    gsctInputFormat.bZeroSupp            = FALSE;
    gsctInputFormat.bSubTable            = FALSE;


    // Reset data for cursor position
    glRelativeCurPos                      = 0;
    gclCursorImageTag                     = NULL;                 // Reset data for cursor image pointer
    gdwFlgDispZeroPadding                 = GUI_VALUE_ZERO_DWORD; // Reset data for zero padding item
    geInputItemArea                       = E_AREA_NULL;          // Reset data for input item area
    // Set return value
    lProcResult                           = GUI_RET_OK;
    return lProcResult;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SwitchOperationPageFunc
//
//�@�\�@�@��@�F  Process of switching the page of business operation
//
//�@�T�@�@�v�@�F  Process of switching the page of business operation
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  CItem* lpInTagID                (I)              Tag ID object pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/06   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::SwitchOperationPageFunc(
                              CItem* lpInTagID )
{
    // Initilize
    LONG                                lProcResult         = ERROR_CODE_NOT_EXIST_HTML;    // Error code
    DWORD                               dwLoopIndex         = GUI_VALUE_ZERO_DWORD;         // loop index
    string                              sContenaKirikaeId   = "";                           // Container ID
    string                              sStartNo            = "";                           // Start number string
    string                              sEndNo              = "";                           // End number string
    AREA_ENUM                           eAreaName           = E_AREA_NULL;                  // type of area
    string                              sAreaFuncName       = "";                           // Area function name

    // Check parameter
    if ( lpInTagID == NULL )
    {
        return ERROR_CODE_NULL_ID;
    }
    else
    {
        // Do nothing
    }


    // Find the information to switch area or part of area
    
    for ( dwLoopIndex = 0; dwLoopIndex < SWITCH_OPERATION_PAGE_TABLE_SIZE; dwLoopIndex++ )
    {
        // Found information
        if ( lpInTagID->m_sctProperty.sTagID == Switch_OperationPage_Table[dwLoopIndex].sTagId )
        {
            break;
        }
    }

    // Found information
    if ( dwLoopIndex < SWITCH_OPERATION_PAGE_TABLE_SIZE )
    {
        // Change a part of area
        if ( Switch_OperationPage_Table[dwLoopIndex].sPageUrl == "" )
        {
            // Can not find container ID
            if ( Switch_OperationPage_Table[dwLoopIndex].sContenaKirikaeID == "" )
            {
                return ERROR_CODE_NOT_EXIST_HTML;
            }
            // Found container ID
            else
            {
                
                sContenaKirikaeId = Switch_OperationPage_Table[dwLoopIndex].sContenaKirikaeID;
                sStartNo          = Switch_OperationPage_Table[dwLoopIndex].sStartNo;
                sEndNo            = Switch_OperationPage_Table[dwLoopIndex].sEndNo;                   

                // Change part of area
                lProcResult = ContenaKirikaeFunc( sContenaKirikaeId, sStartNo, sEndNo, NULL ); 
                ChangeInputButtonDesignFunc( lpInTagID );
                lProcResult = GUI_RET_OK;
            }
        }
        else
        {       // Change area
                eAreaName     = Switch_OperationPage_Table[dwLoopIndex].eAreaName;
                sAreaFuncName = Switch_OperationPage_Table[dwLoopIndex].sPageUrl;

                lProcResult = ChangeViewInnerPageFunc( 
                     sAreaFuncName, 
                     eAreaName );

                //if ( lProcResult == RESULT_OK_INNER_PAGE_SWITCH )
                //{
                //    return GUI_RET_OK;    
                //}
                //else
                //{
                //    // Do nothing
                //}
        }
    }
    else
    {
        return ERROR_CODE_NOT_EXIST_HTML;
    }

    return lProcResult;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ResolutiveDispInputErroFunc
//
//�@�\�@�@��@�F  Cancel display error of input
//
//�@�T�@�@�v�@�F  Cancel display error of input
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  CItem* lpInItem                (I)              Item object pointer
//                DWORD  dwInResolutiveMode      (I)              Resolutive mode
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/06   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ResolutiveDispInputErroFunc(
                                        CItem* lpInItem,
                                        DWORD dwInResolutiveMode )
{
    LONG                                lProcResult = GUI_RET_OK;                                       // Error code
    string                              sStatus             = "";                           // Status of item
    string                              sDesignInputError   = "";                           // Design Input error
    // Check parameter
    if ( lpInItem == NULL )
    {
        return ERROR_CODE_NULL_ID;
    }
    else
    {
        // Do nothing
    }

    if (( dwInResolutiveMode == RESOLUTIVE_MODE_ENTER ) ||
        ( dwInResolutiveMode == RESOLUTIVE_MODE_INPUT ))
    {
        // Do nothing
    }
    else
    {
        return ERROR_CODE_NOT_RANGE;
    }

    // If apply to any of the following conditions, and the process is terminated
    sDesignInputError = DESIGN_INPUT_ERROR;

    if (( SubStr( lpInItem->m_sctProperty.sStatus, 0, sDesignInputError.size())     != DESIGN_INPUT_ERROR                   ) ||
        (( dwInResolutiveMode == RESOLUTIVE_MODE_INPUT )&& ( gdwViewErrorResolutive != ERROR_RESOLUTIVE_INPUT_FIRST   )) ||
        (( dwInResolutiveMode == RESOLUTIVE_MODE_ENTER )&& ( gdwViewErrorResolutive == ERROR_RESOLUTIVE_NO_RESOLUTIVE )))
    {
        return GUI_RET_OK;
    }
    else
    {
        // Do nothing
    }
    

    // change the status to design
    sStatus = SubStr( lpInItem->m_sctProperty.sStatus, sDesignInputError.size());
    
    // Set new status
    lpInItem->m_sctProperty.sStatus = sStatus;


    if ( gsViewErrorDesign == DESIGN_ERROR_BLINK_MOJI )
    {
        // Blink only text of item
        lProcResult = ChangeFlashingTagFunc( lpInItem, FLG_OBJECT_BLINK_STOP, STS_NAME_UPDATE_ELEMENT_CHILD );
    }
    else if ( gsViewErrorDesign == DESIGN_ERROR_BLINK )
    {
        // Blink all item
        lProcResult = ChangeFlashingTagFunc( lpInItem, FLG_OBJECT_BLINK_STOP, STS_NAME_UPDATE_ELEMENT_PARENT );
    }
    else if ( gsViewErrorDesign == DESIGN_ERROR_BACKGROUND_CHANGE )
    {
        // Change background
        lProcResult = ChangeClassIDFunc( lpInItem, DESIGN_SELECT );
    }
    else
    {
        lProcResult = ChangeFontColorFunc( lpInItem, CHAR_COLOR_MODE_DELETE,   Character_Color_Table[CHARACTER_COLOR_TABLE_END].wMojiColor );
    }


    lpInItem->ItemUpdateState(); 
    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  JudgeDateValidityFunc
//
//�@�\�@�@��@�F  Judge the date is valid date or not.
//
//�@�T�@�@�v�@�F  Judge the date is valid date or not.
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  SCT_DATE sctInDate                (I)              Date input to check
//  �o�[�W�����@     ���t          ����              ���l
//
//  GUI-00.00.00    2015/03/16   (TSDV) LiemTt     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CGuiViewDlg::JudgeDateValidityFunc( 
                      SCT_DATE sctInOperDate, 
                      SCT_DATE* lpsctOutValidDate,
                      LONG& lOutErrCode )
{
    // Initilize
    static DWORD dwDaysInMonth[] = { 31, 28, 31, 30,
                                     31, 30, 31, 31,
                                     30, 31, 30, 31 };
    DWORD dwMaxDay = 0;
    SCT_DATE sctMinDate;

    ( VOID )memset( &sctMinDate, 0x00, sizeof( sctMinDate ));
    // Check parameter
    if ( lpsctOutValidDate == NULL )
    {
        return FALSE;
    } 
    else
    {
        // Do nothing
    }
    
    // Memset output structure date
    memset( lpsctOutValidDate, 0x00, sizeof( SCT_DATE ));

    // Year is invalid
    if (( VALUE_MAX_YEAR < sctInOperDate.wYear) ||
        ( VALUE_MIN_YEAR > sctInOperDate.wYear ))
    {
        lOutErrCode = INPUT_ERR_CODE_DATE;
        return FALSE;
    } 
    else
    {
        // Do nothing
    }
    
    // Month is invalid
    if (( sctInOperDate.byMonth == 0 ) ||
        ( sctInOperDate.byMonth > 12 ) )
    {
        lOutErrCode = INPUT_ERR_CODE_DATE;
        return FALSE;
    } 
    else
    {
        // Do nothing
    }
        
    dwMaxDay = dwDaysInMonth[sctInOperDate.byMonth - 1];

    if ( sctInOperDate.byMonth == 2 && IsLeapYear( sctInOperDate.wYear ) )
    {
        dwMaxDay = 29;
    } 
    else
    {
        // Do nothing
    }
    
    // Day is invalid
    if ( ( sctInOperDate.byDay == 0 ) ||
         ( sctInOperDate.byDay > dwMaxDay ) )
    {
        lOutErrCode = INPUT_ERR_CODE_DATE;
        return FALSE;
    } 
    else
    {
        // Do nothing
    }

    if ( sctInOperDate.wHour > 23 || sctInOperDate.wMinutes > 59 || sctInOperDate.wSecond > 59 )
    {
        lOutErrCode = INPUT_ERR_CODE_TIME;
        return FALSE;
    } 
    else
    {} // Do nothing

    sctMinDate = SCT_DATE( ( WORD ) Calendar_Year_Table[0].dwAnnoDomini, ( BYTE ) Calendar_Year_Table[0].dwStartMonth , ( BYTE ) Calendar_Year_Table[0].dwStartDay);
    if(sctMinDate <= sctInOperDate)
    {
        lOutErrCode = -1;
        *lpsctOutValidDate = sctInOperDate;
    } else 
    {
        lOutErrCode = INPUT_ERR_CODE_DATE;
        return FALSE;
    }

    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SendData
//
//�@�\�@�@��@�F  Used to sending data from View process to ViewIF process 
//
//�@�T�@�@�v�@�F  Used to sending data from View process to ViewIF process 
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  DWORD dwDataSize         Data size
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/06   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::SendData( DWORD dwDataSize )
{
    // Initilize
    LONG               lProcResult= GUI_RET_OK;  // Error code
    COPYDATASTRUCT                  sctTransPkg;
    LRESULT                         lSendResult;
    HWND                            hWnd;

    // Set value for sending message
    // Set size of package
    sctTransPkg.cbData  = dwDataSize;
    sctTransPkg.dwData  = 1;
    sctTransPkg.lpData  = ( LPVOID )&m_bySendData;

    // Find ViewIF process
    hWnd = ::FindWindow( NULL, GUI_VIEWIF_WND_TITLE );

    // Check whether found ViewIF process or not
    if ( hWnd == NULL )
    {
        lProcResult = GUI_ERR_GVD_SD_PROC_NOT_FOUND;
    }
    else
    {
        lSendResult = ::SendMessage( 
                            hWnd,
                            WM_COPYDATA,
                            (WPARAM)AfxGetApp()->m_pMainWnd->GetSafeHwnd(),
                            (LPARAM) &sctTransPkg);
        // Send message successfully
        if ( lSendResult == TRUE )
        {
            lProcResult = GUI_RET_OK;
        }
        // Send message unsuccessfully
        else
        {
            lProcResult = GUI_ERR_GVD_SD_SEND_MESSAGE;
        }
    }

    // Reset data for send message
    ( VOID )memset( &m_bySendData, 0x00, sizeof( m_bySendData ));
    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeDispInputErroFunc
//
//�@�\�@�@��@�F  Change input error display 
//
//�@�T�@�@�v�@�F  Change input error display 
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  CItem* lpcItem         Changed item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/06   (TSDV) LanLTM     Create New
//  GUI-00.00.01    2015/04/14   (TSDV) LanLTM     Update following new Javascript functions
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ChangeDispInputErroFunc( 
                                         CItem* lpInItem )
{
    // Initilize
    LONG                                lProcResult         = GUI_RET_OK;                   // Error code
    string                              sStatus             = "";                           // Status of item
    string                              sDesignInputError   = "";                           // Design Input error

    // Reset data
    

    // Check parameter
    if ( lpInItem == NULL )
    {
        return ERROR_CODE_NULL_ID;
    }
    else
    {
        // Do nothing
    }

    // 

    if ( gsViewErrorDesign == DESIGN_ERROR_BLINK_MOJI )
    {
        // Blink only text in item
        lProcResult = ChangeFlashingTagFunc( lpInItem, gdwViewErrorBlinkCnt, STS_NAME_UPDATE_ELEMENT_CHILD );
    }
    else if ( gsViewErrorDesign == DESIGN_ERROR_BLINK )
    {
        // Blink item
        lProcResult = ChangeFlashingTagFunc( lpInItem, gdwViewErrorBlinkCnt, STS_NAME_UPDATE_ELEMENT_PARENT );
    }
    else if ( gsViewErrorDesign == DESIGN_ERROR_BACKGROUND_CHANGE )
    {
        // Change background
        lProcResult = ChangeClassIDFunc( lpInItem, DESIGN_ERROR );
    }
    else if ( gsViewErrorDesign == DESIGN_ERROR_TOOLTIP )
    {
        return lProcResult;
    }
    else if ( gsViewErrorDesign == DESIGN_ERROR_NO_CHANGE )
    {
        return GUI_RET_OK;
    }
    else
    {
        lProcResult = ChangeFontColorFunc( lpInItem, CHAR_COLOR_MODE_ADD, Character_Color_Table[CHARACTER_COLOR_TABLE_RED].wMojiColor );
    }
    
    
    sStatus = lpInItem->m_sctProperty.sStatus;

    sDesignInputError = DESIGN_INPUT_ERROR ;

    if (( SubStr( sStatus, 0, sDesignInputError.size()) != DESIGN_INPUT_ERROR ) ||
        ( sStatus                                       == DESIGN_ERROR       ))
    {
        // 
        sStatus = DESIGN_INPUT_ERROR + sStatus;
    }
    else
    {
        // Do nothing
    }
   


    // Re draw item

    lpInItem->m_sctProperty.sStatus = sStatus;

     lpInItem->ItemUpdateState( TRUE );

    return lProcResult;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SearchTagIDFunc
//
//�@�\�@�@��@�F  Search item that has tag ID is same as inputed tag ID
//
//�@�T�@�@�v�@�F  Search item that has tag ID is same as inputed tag ID
//
//�@�߁@��@�l�F  Vector of item pointer
//
//�@���@�@���@�F       string      sInTagID         Tag ID string
//                     AREA_ENUM   eInAreaType      Area type
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/16   (TSDV) LiemTT     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
vector<CItem*> CGuiViewDlg::SearchTagIDFunc( const string &sInTagID, AREA_ENUM eInAreaType )
{
    // Initialize
    vector<CItem*>               vlpItem;  // Vector of Items
    DWORD dwIndex = 0;

    
    // FInd items in current areas
    for ( dwIndex = 0; dwIndex < m_vCurAreas.size(); dwIndex++ )
    {
        // Find item when area string is empty
        if (( eInAreaType != E_AREA_NULL) &&
            ( m_vCurAreas[dwIndex]->m_sctAreaInfo.eAreaType != eInAreaType ) )
        {
            continue;
        } 
        else
        {
            // Do nothing
        }
        
        m_vCurAreas[dwIndex]->GetItemsByTagID( vlpItem, sInTagID );
    }
    return vlpItem;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SearchAltTagIDFunc
//
//�@�\�@�@��@�F  Search alternate tag attribute of the object
//
//�@�T�@�@�v�@�F  Search alternate tag attribute of the object
//
//�@�߁@��@�l�F  Vector of item pointer
//
//�@���@�@���@�F       string      sInSerchObject         Tag ID string
//                     string      sInAltTagID            Alternative tag ID string
//                     string      sInSerchTagName        Search tag name
//                     AREA_ENUM   eInAreaType            Area type
//                     string      sInSerchId             Search ID
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/16   (TSDV) LiemTT     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
vector<CItem*> CGuiViewDlg::SearchAltTagIDFunc(
                        const        string &sInSerchObject,
                        const        string &sInAltTagID,
                        const        string &sInSerchTagName,
                                     AREA_ENUM eInAreaType,
                        const        string &sInSerchId )
{
    // Initilize
    vector<CItem*>               vlpItem;  // Vector of Items
    DWORD dwIndex = 0;

    
    // Found item in current view by alternative tag ID
    for ( dwIndex = 0; dwIndex < m_vCurAreas.size(); dwIndex++ )
    {
        if ( ( eInAreaType != E_AREA_NULL ) &&
            ( m_vCurAreas[dwIndex]->m_sctAreaInfo.eAreaType != eInAreaType ) )
        {
            continue;
        }
        else
        {
            // Do nothing
        }
        // Get item by alternative tag ID
        m_vCurAreas[dwIndex]->GetItemsByAltTagID( vlpItem, sInAltTagID, sInSerchTagName );
    }
    return vlpItem;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SearchGroupTagIDFunc
//
//�@�\�@�@��@�F  Search group of item following Tag ID
//
//�@�T�@�@�v�@�F  Search group of item following Tag ID
//
//�@�߁@��@�l�F  Vector of item pointer
//
//�@���@�@���@�F       string      sInSerchObject         Tag ID string
//                     string      sInGroupType           Group type
//                     string      sInSerchTagName        Search tag name
//                     AREA_ENUM   eInAreaType            Area type
//                     string      sInSerchId             Search ID
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/16   (TSDV) LiemTT     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
vector<CItem*> CGuiViewDlg::SearchGroupTagIDFunc(
                      const          string &sInSerchObject,
                      const          string &sInGroupType,
                      const          string &sInSerchTagName,
                                     AREA_ENUM eInAreaType,
                      const          string &sInSerchId)
{
    // Initalize
    vector<CItem*>               vlpItem;  // Vector of Items
    DWORD dwIndex = 0;

    vlpItem.clear();
    
    for ( dwIndex = 0; dwIndex < m_vCurAreas.size(); dwIndex++ )
    {

        if ( ( eInAreaType != E_AREA_NULL ) &&
            ( m_vCurAreas[dwIndex]->m_sctAreaInfo.eAreaType != eInAreaType ) )
        {
            continue;
        }
        else
        {
            // Do nothing
        }

        m_vCurAreas[dwIndex]->GetItemsByGroupTagID( vlpItem, sInGroupType, sInSerchTagName );
    }
    return vlpItem;
}

//////////////////////////////////////////////////////////////////////////////////////////
//
//  ��  ��  ���F  DisplayGyomu
//
//  �\    ��  �F  Change gyomu
//
//  �T    �v  �F  Change gyomu
//
//  ��  ��  �l�F  GUI_NORMAL          ����I��
//                GUI_ERROR           �ُ�I��
//
//  ��    ��  �F  
//
//  �o�[�W�����F  2015-05-11  NEXA-V00.23�@  (TSDV) LiemTT    Create new
//
//  (C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////////////////////
VOID CGuiViewDlg::DisplayGyomu( DWORD dwGyomuNo )
{
    void( CGuiViewDlg::*DisplayGomuFnPrt )( ) = NULL;
    string          sTagID = "";           // Tag ID of input item
//    BOOL            bRet = FALSE;        // Return value of internal function
    vector<CItem*>  vlpItem;                 // Vector of item

    vlpItem.clear();

    switch ( dwGyomuNo )
    {
    case GYOMU_TYPE_1:
        DisplayGomuFnPrt = &CGuiViewDlg::DisplayGyomu1;
        break;
    case GYOMU_TYPE_2:
        DisplayGomuFnPrt = &CGuiViewDlg::DisplayGyomu2;
        break;
    case GYOMU_TYPE_3:
        DisplayGomuFnPrt = &CGuiViewDlg::DisplayGyomu3;
        break;
    default:
        return;
    }

    if ( gclInputItemTag == NULL )
    {
        (this->*DisplayGomuFnPrt)();
    }
    else
    {
        sTagID = gclInputItemTag->m_sctProperty.sTagID;
        // Change area
        ( this->*DisplayGomuFnPrt )( );

        // Get items that have same tag ID with global input tag ID in current area
        vlpItem = SearchTagIDFunc( sTagID, E_AREA_NULL );
        if ( vlpItem.size() == 0 )
        {
            gclInputItemTag = NULL;
        }
        else
        {
            gclInputItemTag = vlpItem[0];
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  DisplayGyomu1
//
//�@�\�@�@��@�F  Displaying screen following format of gyomu1
//
//�@�T�@�@�v�@�F  Displaying screen following format of gyomu1
//
//�@�߁@��@�l�F  NA
//
//�@���@�@���@�F  NA
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/16   (TSDV) ThietNP     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
VOID CGuiViewDlg::DisplayGyomu1()
{
    // Display gyomu 1
    m_cAreaStore.DisplayGyomu1();
    //<TSDV-BugNo146-20150424-ThietNP-Set global Gyomu mode>
    CArea::m_dwGyomuMode = 1;
    //< TSDV-BugNo146-20150424 - End>
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  DisplayGyomu2
//
//�@�\�@�@��@�F  Displaying screen following format of gyomu2
//
//�@�T�@�@�v�@�F  Displaying screen following format of gyomu2
//
//�@�߁@��@�l�F  NA
//
//�@���@�@���@�F  NA
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/16   (TSDV) ThietNP     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
VOID CGuiViewDlg::DisplayGyomu2()
{
    // Display gyomu 2
    m_cAreaStore.DisplayGyomu2();
    //<TSDV-BugNo146-20150424-ThietNP-Set global Gyomu mode>
    CArea::m_dwGyomuMode = 2;
    //< TSDV-BugNo146-20150424 - End>
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  DisplayGyomu3
//
//�@�\�@�@��@�F  Displaying screen following format of gyomu3
//
//�@�T�@�@�v�@�F  Displaying screen following format of gyomu3
//
//�@�߁@��@�l�F  NA
//
//�@���@�@���@�F  NA
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/16   (TSDV) ThietNP     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
VOID CGuiViewDlg::DisplayGyomu3()
{
    // Display gyomu 3
    m_cAreaStore.DisplayGyomu3();
    //<TSDV-BugNo146-20150424-ThietNP-Set global Gyomu mode>
    CArea::m_dwGyomuMode = 3;
    //< TSDV-BugNo146-20150424 - End>
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeArea
//
//�@�\�@�@��@�F  Change area from current area to specific area
//
//�@�T�@�@�v�@�F  Change area from current area to specific area
//
//�@�߁@��@�l�F  TRUE: Change area successfully
//                FALSE: Change area unscucessfully
//
//�@���@�@���@�F  AREA_ENUM        eArea               Area type
//                string           sAreaFuncName       Create component function name corresponding to specific area
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/16   (TSDV) ThietNP     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CGuiViewDlg::ChangeArea( AREA_ENUM eArea, const string &sAreaFuncName )
{
    string          sTagID   = "";           // Tag ID of input item
    BOOL            bRet     = FALSE;        // Return value of internal function
    vector<CItem*>  vlpItem;                 // Vector of item

    vlpItem.clear();
    
    if ( gclInputItemTag == NULL )
    {
        bRet = m_cAreaStore.ChangeArea( eArea, sAreaFuncName );
    }
    else
    {
        if ( gclInputItemTag->m_sctProperty.eAreaType == eArea )
        {
            sTagID = gclInputItemTag->m_sctProperty.sTagID;
            // Change area
            bRet = m_cAreaStore.ChangeArea( eArea, sAreaFuncName );

            // Get items that have same tag ID with global input tag ID in current area
            vlpItem = SearchTagIDFunc( sTagID, eArea );
            if ( vlpItem.size() == 0 )
            {
                gclInputItemTag = NULL;
            }
            else
            {
                gclInputItemTag = vlpItem[0];
            }

            return bRet;
        }
        else
        {
            bRet = m_cAreaStore.ChangeArea( eArea, sAreaFuncName );
        }
    }

    if ( eArea == E_AREA_INDICATOR )
    {
        m_bIsForceUpdateTime = TRUE;
        PostMessage( WM_TIMER, NEXA_TIMER_DATE_TIME, 0 );
        CtrlDispHolidayFunc();
    }
    else
    {
        // Do nothing
    }
    return bRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  GetAreaPos
//
//�@�\�@�@��@�F  Get area position
//
//�@�T�@�@�v�@�F  Get area position
//
//�@�߁@��@�l�F  Position of area
//
//�@���@�@���@�F  AREA_ENUM        eArea               Area type
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/16   (TSDV) ThietNP     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
POINT CGuiViewDlg::GetAreaPos( AREA_ENUM eAreaType )
{
    return m_cAreaStore.GetAreaPos( eAreaType );
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  GetAreaIndex
//
//�@�\�@�@��@�F  Get area index
//
//�@�T�@�@�v�@�F  Get area index
//
//�@�߁@��@�l�F  Index of area
//
//�@���@�@���@�F  AREA_ENUM        eArea               Area type
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/16   (TSDV) ThietNP     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
DWORD CGuiViewDlg::GetAreaIndex( AREA_ENUM eArea )
{
    return m_cAreaStore.GetAreaIndex( eArea );
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  GetCurrentAreaByAreaType
//
//�@�\�@�@��@�F  Get Current Area By Area Type
//
//�@�T�@�@�v�@�F  Get Current Area By Area Type
//
//�@�߁@��@�l�F  LONG lOutErrCode
//
//�@���@�@���@�F  AREA_ENUM eInAreaType       (I)       Area type
//                CArea*    lpOutCurrentArea  (O)       Current area
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/06    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
CArea* CGuiViewDlg::GetCurrentAreaByAreaType(AREA_ENUM eInAreaType)
{
    //Declare local variable
    DWORD           dwIndex       = GUI_VALUE_ZERO_DWORD;

    // Return if input size is zero
    if ( m_vCurAreas.size() == 0 )
    {
        return NULL;
    }
    //find current area by type
    for ( dwIndex = 0; dwIndex < m_vCurAreas.size(); dwIndex++ )
    {
        if ( m_vCurAreas[dwIndex] != NULL && m_vCurAreas[dwIndex]->m_sctAreaInfo.eAreaType == eInAreaType )
        {
            return m_vCurAreas[dwIndex];
        }
        else
        {
            // Do nothing
        }
    }
    return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  FindItemByTagID
//
//�@�\�@�@��@�F  Find item by TagID
//
//�@�T�@�@�v�@�F  Find item by TagID
//
//�@�߁@��@�l�F  LONG lOutErrCode
//
//�@���@�@���@�F  string sTagID       (I)        Item needs to be searched
//               vector<CItem*> vobjInSearchItem // Scope
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/06    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////

CItem* CGuiViewDlg::FindItemByTagID( const string &sInTagID, const vector<CItem*>& vobjInSearchItem)
{
    DWORD           dwIndex       = GUI_VALUE_ZERO_DWORD;    // Counter variable
    CItem*          lpobjItem     = NULL;
    
    // Return if input size is zero
    if ( vobjInSearchItem.size() == 0 )
    {
        return NULL;
    }
    else
    {
        // Do nothing
    }
    for ( dwIndex = 0; dwIndex < vobjInSearchItem.size(); dwIndex++ )
    {
        if ( vobjInSearchItem[dwIndex]->m_sctProperty.sTagID == sInTagID )
        {
            return vobjInSearchItem[dwIndex];
        }
        else
        {
            lpobjItem = FindItemByTagID( sInTagID, vobjInSearchItem[dwIndex]->m_vobjItems );
            if ( lpobjItem != NULL)
            {
                return lpobjItem;
            }
            else
            {
                // Do nothing
            }
        }
        
    }
    return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  DisplayBranchPageSwitcFunc
//
//�@�\�@�@��@�F  Display Branch Page Switch
//
//�@�T�@�@�v�@�F  Handle display request on switching page
//
//�@�߁@��@�l�F  LONG lOutErrCode
//
//�@���@�@���@�F  SCT_PAGE_SWITCH sctInPageSwitch       (I)        New page info
//
//  �o�[�W�����@     ���t          ����              ���l
//  NEXA-01.00.00    2015/03/06    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::DisplayBranchPageSwitcFunc( SCT_GUI_MSG_DISP_TYPE_CHANGE_AREA_VIEW sctInPageSwitch )
{
    //Declare local variable
    vector<LONG>    vlOutErrCode;
    LONG            lSubErrCode          = GUI_RET_OK;
    CArea*          lpCurrentArea        = NULL;                    // Current area
    BOOL            bPageChange          = FALSE;                   // Page change flag
    DWORD           dwGyomuType          = GYOMU_TYPE_NON;
    BOOL            bRet                 = FALSE;

    ////////////////// Check agrument

    if ( ( sctInPageSwitch.dwMask & MASK_CHANGE_ARE_AREA_TYPE ) != MASK_CHANGE_ARE_AREA_TYPE )
    {
        vlOutErrCode.push_back( ERROR_CODE_NULL );
    }
    else
    {
        // Do nothing
    }
    if ((( sctInPageSwitch.dwMask & MASK_CHANGE_ARE_PAGE_FILE )   == MASK_CHANGE_ARE_PAGE_FILE   ) && 
        (( sctInPageSwitch.dwMask & MASK_CHANGE_ARE_CHANGE_FLAG ) == MASK_CHANGE_ARE_CHANGE_FLAG ) &&
        (( sctInPageSwitch.dwChangeFlag != TRUE ) && ( sctInPageSwitch.dwChangeFlag != FALSE )))
    {
        vlOutErrCode.push_back( ERROR_CODE_NOT_RANGE );
    }
    else
    {
        // Do nothing
    }

    ///return if argrument is invalid
    if ( vlOutErrCode.size() > 0)
    {
        return vlOutErrCode[0];
    }
    else
    {
        //Do nothing
    }
    if ( ( sctInPageSwitch.dwMask & MASK_CHANGE_ARE_ENABLE ) == MASK_CHANGE_ARE_ENABLE )
    {
        if ( sctInPageSwitch.dwEnable == TRUE )
        {
            sctInPageSwitch.dwEnable = FALSE;
        }
        else
        {
            sctInPageSwitch.dwEnable = TRUE;
        }

        // Control enable all display function

        lSubErrCode = ControlEnableAllDisplayFunc( sctInPageSwitch.dwEnable, sctInPageSwitch.eAreaType );
    }
    else
    {
        // Do nothing
    }
    

    // Check whether page is change based on PageFile field
    if ( ( sctInPageSwitch.dwMask & MASK_CHANGE_ARE_PAGE_FILE ) == MASK_CHANGE_ARE_PAGE_FILE )
    {
        if ( strcmp( sctInPageSwitch.szPageFile, "" ) == 0 )
        {
            return ERROR_CODE_NOT_EXIST_HTML;
        } 
        else {} // Do nothing
        
        if ( sctInPageSwitch.dwChangeFlag == TRUE )
        {
            bPageChange = TRUE;
        }
        else 
        {
            if ( sctInPageSwitch.eAreaType == E_AREA_GYOMU )
            {
                dwGyomuType = GetGyomuType( sctInPageSwitch.szPageFile );
                if ( dwGyomuType == GYOMU_TYPE_NON )
                {
                    vlOutErrCode.push_back( ERROR_CODE_NOT_EXIST_ID );
                    return vlOutErrCode[0];
                } 
                else if ( dwGyomuType == m_dwCurGyomuMode )
                {
                    bPageChange = FALSE;
                } 
                else
                {
                    bPageChange = TRUE;
                }
            

            }
            else
            {
                // Check current area
                lpCurrentArea = GetCurrentAreaByAreaType( sctInPageSwitch.eAreaType );
                if (lpCurrentArea == NULL)
                {
                    //vlOutErrCode.push_back( ERROR_CODE_NOT_EXIST_ID );
                    //return vlOutErrCode;
                    bPageChange = TRUE;
                }
                else
                {
                                // If area is existed, no need to change
                    if ( strcmp( lpCurrentArea->m_sctAreaInfo.sAreaFuncName.c_str(), sctInPageSwitch.szPageFile ) == 0 )
                    {
                        bPageChange = FALSE;
                    }
                    else
                    {
                        bPageChange = TRUE;
                    }
                }

            }
        
        }
    }
    else
    {
       // Do nothing
    }
    if ( bPageChange == TRUE && strcmp( sctInPageSwitch.szPageFile, "" ) == 0 )
    {
        vlOutErrCode.push_back( ERROR_CODE_NULL );
        return vlOutErrCode[0];
    }
    else
    {
        // Do nothing
    }
    lSubErrCode = ControlEnableAllDisplayFunc(FLG_OBJECT_NOT_ENABLE, E_AREA_GYOMU);
    //string  sGyomuName ( sctInPageSwitch.cPageFile, strlen( sctInPageSwitch.cPageFile ) );
                
    //If flag check is true
    if ( bPageChange == TRUE )
    {
        //check PageFile field type is gyomu
        switch( sctInPageSwitch.eAreaType )
        {
            case E_AREA_GYOMU:
                dwGyomuType = GetGyomuType( sctInPageSwitch.szPageFile );
                if ( dwGyomuType == GYOMU_TYPE_1 )
                {
                    // LiemTT fix bug crash program
                    //DisplayGyomu1();
                    DisplayGyomu( GYOMU_TYPE_1 );
                    // End fix bug crash program
                }
                else if ( dwGyomuType == GYOMU_TYPE_2 )
                {
                    // LiemTT fix bug crash program
                    //DisplayGyomu2();
                    DisplayGyomu( GYOMU_TYPE_2 );
                    // End fix bug crash program
                }
                else if ( dwGyomuType == GYOMU_TYPE_3 )
                {
                    // LiemTT fix bug crash program
                    //DisplayGyomu3();
                    DisplayGyomu( GYOMU_TYPE_3 );
                    // End fix bug crash program
                }
                else
                {
                    vlOutErrCode.push_back( ERROR_CODE_NOT_EXIST_ID );
                    return vlOutErrCode[0];
                }

                break;
            case E_AREA_BUSSINESS:
            case E_AREA_CENTERDISP:
            case E_AREA_DISP:
            case E_AREA_OPERATING:
            case E_AREA_CONST_BTN:
            case E_AREA_POPUP:
            case E_AREA_INDICATOR:
                //lpCurrentArea->m_sctAreaInfo.sAreaFuncName = (string)sctInPageSwitch.cPageFile;
                bRet = ChangeArea( sctInPageSwitch.eAreaType, sctInPageSwitch.szPageFile );
                if (bRet == TRUE)
                {
                     //return RESULT_OK_PAGE_SWITC;
                    break;
                }
                else
                {
                    // Do nothing
                }
                break;
            default:
                vlOutErrCode.push_back( ERROR_CODE_NOT_RANGE );
                break;
        }
    }
    else
    {
        // Do nothing
    }
    if ( lSubErrCode != GUI_RET_OK )
    {
        vlOutErrCode.push_back( lSubErrCode );
    }
    else
    {
        // Do nothing
    }

    if ( vlOutErrCode.size() == 0 )
    {
        vlOutErrCode.push_back( GUI_RET_OK );
    }
    else
    {
        // Do nothing
    }
    return vlOutErrCode[0];
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  DisplayBranchPopupFunc
//
//�@�\�@�@��@�F  Handle create/destroy popup request
//
//�@�T�@�@�v�@�F  Handle create/destroy popup request
//
//�@�߁@��@�l�F  LONG lOutErrCode
//
//�@���@�@���@�F  SCT_PAGE_SWITCH sctInPageSwitch       (I)        New page info
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/09    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG CGuiViewDlg::DisplayBranchPopupFunc( SCT_GUI_MSG_DISP_TYPE_POP_UP_VIEW sctInPopupDisp )
{
    //Declare local variable
    vector<LONG>    vlOutErrCode;
    DWORD           dwIndex              = GUI_VALUE_ZERO_DWORD;    
    BOOL            bExistedPos          = FALSE;

    vlOutErrCode.clear();

    // Check valid of parms
    if ( sctInPopupDisp.byMakeOnOff != FLG_OBJECT_DESTRUCTION && sctInPopupDisp.byMakeOnOff != FLG_OBJECT_CREATE )
    {
        vlOutErrCode.push_back( ERROR_CODE_NOT_RANGE);
    }
    else
    {
        // Do nothing
    }

    switch ( sctInPopupDisp.byMakeOnOff )
    {
        case FLG_OBJECT_DESTRUCTION:
            break;
        case FLG_OBJECT_CREATE:
            if (( strcmp( sctInPopupDisp.szPageFile, "" )  == 0  ) || (( sctInPopupDisp.dwMask & MASK_POP_UP_PAGE_FILE ) != MASK_POP_UP_PAGE_FILE ))
            {
                 vlOutErrCode.push_back( ERROR_CODE_NOT_EXIST_HTML);
            }
            else
            {
                // Do nothing
            }
            break;
        default:
            vlOutErrCode.push_back( ERROR_CODE_NOT_RANGE);
            break;

    }
    

    ///return if argrument is invalid
    if ( vlOutErrCode.size() > 0)
    {
        return vlOutErrCode[0];
    }
    else
    {
        //Do nothing
    }

    // Handle to destroy popup
    if ( sctInPopupDisp.byMakeOnOff == FLG_OBJECT_DESTRUCTION )
    {
        m_cAreaStore.ShowPopupByLayer( sctInPopupDisp.dwLayer, FALSE );
        //m_dwNumberOfPopup > 0 ? m_dwNumberOfPopup-- : 0;
        //m_vPopupDlg.back()->ShowWindow( SW_HIDE );

    }
    // Handle to create popup
    else if ( sctInPopupDisp.byMakeOnOff == FLG_OBJECT_CREATE )
    {
        // Set default position for popup
        switch ( sctInPopupDisp.dwDispIchi )
        {
            case POOUP_DISP_POTICION_INDEX_CENTER1:
            case POOUP_DISP_POTICION_INDEX_MACHINE:
            case POOUP_DISP_POTICION_INDEX_OPE:
            case POOUP_DISP_POTICION_INDEX_DISP:
            case POOUP_DISP_POTICION_INDEX_UPPER_LEFT:
            case POOUP_DISP_POTICION_INDEX_OFF_POWER:
            case POOUP_DISP_POTICION_INDEX_CENTER2:
                break;
            default:
                sctInPopupDisp.dwDispIchi = POOUP_DISP_POTICION_INDEX_CENTER1;
                break;
        }
        // Get position of popup

        for ( dwIndex = 0; dwIndex <  POPUP_DISP_POSITION_TABLE_SIZE ; dwIndex++ )
        {
            if ( Pooup_Disp_Poticion_Table[dwIndex].dwDispIchi == sctInPopupDisp.dwDispIchi )
            {
                bExistedPos = TRUE;
                break;
            }
            else
            {

                // Do nothing
            }
        }


        //Position is found
        if ( bExistedPos == TRUE )
        {
            m_cAreaStore.SetPopupLayer( sctInPopupDisp.dwLayer );
            ChangeArea( E_AREA_POPUP, sctInPopupDisp.szPageFile );
            
            // Get active popup
            CPopupDlg* pActivePopup = GetActivePopup();
            if ( pActivePopup == NULL )
            {
                return ERR_CODE_NO_AREA;
            } 
            else {} // Do nothing
            
            // Get position of active popup
            pActivePopup->m_lpcMainArea->m_sctAreaInfo.pPosition.x = Pooup_Disp_Poticion_Table[dwIndex].dwDispLeft;
            pActivePopup->m_lpcMainArea->m_sctAreaInfo.pPosition.y = Pooup_Disp_Poticion_Table[dwIndex].dwDispTop;


            // Show popup
            //ControlEnableAllDisplayFunc(FLG_OBJECT_NOT_ENABLE, E_AREA_GYOMU);
            ShowPopup( pActivePopup->m_lpcMainArea->m_sctAreaInfo.pPosition.x, pActivePopup->m_lpcMainArea->m_sctAreaInfo.pPosition.y );
            //m_dwNumberOfPopup++;
        }
        // Position of popup is not existed
        else
        {
            vlOutErrCode.push_back( ERROR_CODE_NOT_RANGE );
        }
        
    }
    //not destroy && not create
    else
    {
        vlOutErrCode.push_back( ERROR_CODE_NOT_RANGE );
    }

    //Return value
     if ( vlOutErrCode.size() == 0 )
    {
        vlOutErrCode.push_back( RESULT_OK_PAGE_SWITC );
    }
    else
    {
        // Do nothing
    }
    return vlOutErrCode[0];
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  DisplayBranchCalendarFunc
//
//�@�\�@�@��@�F  Handle display calendar request
//
//�@�T�@�@�v�@�F  Handle display calendar request
//
//�@�߁@��@�l�F  LONG lOutErrCode
//
//�@���@�@���@�F  SCT_CALENDAR_DISPLAY sctInCalendarDisp       (I)        Calendar info is received from ViewIF
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/09    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG CGuiViewDlg::DisplayBranchCalendarFunc( const SCT_GUI_MSG_DISP_TYPE_CALENDAR &sctInCalendarDisp )
{
    //Declare local variable
    vector<LONG>    vlOutErrCode;                   // Error code
    LONG            lSubErrCode           = GUI_RET_OK;                    // Error code of sub function
    vector<DWORD>   vdwPeriod;                      // calendar period
    vector<CItem*>  vobjCalendarItems;                // Calendar items
    WORD            wDispYear             = GUI_VALUE_ZERO_WORD;      // Display year
    BYTE            byDispMonth           = GUI_VALUE_ZERO_BYTE;                    // Display month
    string          sTagID                = "";
    BOOL            bRet                  = FALSE;
    SCT_DATE        sctValidDateTemp;
    CArea*          lpobjArea             = NULL;
    vector<string>  vCalendarmax;
    LONG            lFuncResult = GUI_RET_NG;

    // Reset data
    vlOutErrCode.clear();
    vdwPeriod.clear();
    vobjCalendarItems.clear();
    vCalendarmax.clear();

    ( VOID )memset( &sctValidDateTemp, 0x00, sizeof( sctValidDateTemp ));

    // Get Tag ID
    sTagID = ( string )sctInCalendarDisp.szTagID;

    /*SCT_DATE  sctDateNoLimitStart (0000, 00, 00); 
    SCT_DATE  sctDateNoLimitEnd   (9999, 99, 99); */

    //Check agrument of input
    //If cTagID is not a month, set error
    if ( strcmp( sctInCalendarDisp.szTagID, "" ) == 0 && ( sctInCalendarDisp.dwMask & MASK_CALENDAR_TAGID ) != MASK_CALENDAR_TAGID )
    {
        vlOutErrCode.push_back( ERROR_CODE_NULL_ID );
        return vlOutErrCode[0];
    }
    else
    {
        // Do nothing
    }

    if ( ( sctInCalendarDisp.dwMask & MASK_CALENDAR_SELECT_DATE ) != MASK_CALENDAR_SELECT_DATE )
    {
        vlOutErrCode.push_back( ERROR_CODE_NOT_CALEMDAR_DISP );
        return vlOutErrCode[0];
    }
    else
    {
        // Do nothing
    }
    if ( ( sctInCalendarDisp.dwMask & MASK_CALENDAR_START_DATE ) != MASK_CALENDAR_START_DATE )
    {
        vlOutErrCode.push_back( ERROR_CODE_NOT_CALEMDAR_DISP );
        return vlOutErrCode[0];
    }
    else
    {
        // Do nothing
    }
    if ( ( sctInCalendarDisp.dwMask & MASK_CALENDAR_END_DATE ) != MASK_CALENDAR_END_DATE )
    {
        vlOutErrCode.push_back( ERROR_CODE_NOT_CALEMDAR_DISP );
        return vlOutErrCode[0];
    }
    else
    {
        // Do nothing
    }
    // end check agruments

    if ( strcmp( sctInCalendarDisp.szTagID, TAG_ID_NAME_MONTH_THIS) != 0 )
    {
        vlOutErrCode.push_back( ERROR_CODE_NOT_CALEMDAR_DISP );
        return vlOutErrCode[0];
    }
    else
    {
        vobjCalendarItems = SearchTagIDFunc( sTagID, E_AREA_NULL );
        if ( vobjCalendarItems.size() == 0 || vobjCalendarItems.size() != 1 )
        {
            vlOutErrCode.push_back( ERROR_CODE_NOT_CALEMDAR_DISP );
            return vlOutErrCode[0];
        }
        else
        {
            lpobjArea = GetCurrentAreaByAreaType( vobjCalendarItems[0]->m_sctProperty.eAreaType );
            if ( lpobjArea == NULL )
            {
                vlOutErrCode.push_back( ERROR_CODE_NULL );
                return vlOutErrCode[0];
            }
            else
            {
                // Do nothing
            }
        }
    }
    
    bRet = JudgeDateValidityFunc( sctInCalendarDisp.sctSelectDate, &sctValidDateTemp, lFuncResult );
    if (bRet == TRUE )
    {
        //Set global basic date by input basic date
        memcpy( &gsctBasicDate, &sctInCalendarDisp.sctSelectDate, sizeof( SCT_DATE ) );
        wDispYear = gsctBasicDate.wYear;
        memcpy (&byDispMonth, &gsctBasicDate.byMonth, sizeof( gsctBasicDate.byMonth ));
    }
    else
    {
        vlOutErrCode.push_back( ERROR_CODE_NOT_DATE );
        return vlOutErrCode[0];
    }
    


    // Calendar is no limit start date
    //SCT_DATE sctStartDate = CALENDAR_DISP_NO_LIMIT_START_DATE;
    if ( ( WORD )sctInCalendarDisp.sctStartDate.byDay == 0 
        && ( WORD )sctInCalendarDisp.sctStartDate.byMonth == 0 
        && sctInCalendarDisp.sctStartDate.wYear == 0 )
    {
        memcpy( &gsctStartDate, &gsctBasicDate, sizeof( SCT_DATE ) );
        gsctStartDate.wYear = gsctStartDate.wYear - CALENDAR_DISP_NO_LIMIT_YEAR_RANGE_START;
    }
    else
    {
        memset( &sctValidDateTemp, 0x00, sizeof( SCT_DATE ) );
        bRet = JudgeDateValidityFunc( sctInCalendarDisp.sctStartDate, &sctValidDateTemp, lFuncResult );
        if (bRet == TRUE )
        {
            memcpy( &gsctStartDate, &sctInCalendarDisp.sctStartDate, sizeof( SCT_DATE ) );
        }
        else
        {
            vlOutErrCode.push_back( ERROR_CODE_NOT_DATE );
        }
    }

    // Calendar is no limit end date
    //SCT_DATE sctEndDate = CALENDAR_DISP_NO_LIMIT_END_DATE;
    if ( ( WORD )sctInCalendarDisp.sctStartDate.byDay == 99 
        && ( WORD )sctInCalendarDisp.sctStartDate.byMonth == 99 
        && sctInCalendarDisp.sctStartDate.wYear == 9999 )
    {
        memcpy( &gsctEndDate, &gsctBasicDate, sizeof( SCT_DATE ) );
        gsctEndDate.wYear = gsctEndDate.wYear + CALENDAR_DISP_NO_LIMIT_YEAR_RANGE_END;
    }
    else
    {
        memset( &sctValidDateTemp, 0x00, sizeof( SCT_DATE ) );
        bRet = JudgeDateValidityFunc( sctInCalendarDisp.sctEndDate, &sctValidDateTemp, lFuncResult );
        if (bRet == TRUE )
        {
             memcpy( &gsctEndDate, &sctInCalendarDisp.sctEndDate, sizeof( SCT_DATE ) );
        }
        else
        {
            vlOutErrCode.push_back( ERROR_CODE_NOT_DATE );
        }
       
    }
    if ( vlOutErrCode.size() > 0 )
    {
        return vlOutErrCode[0];
    }
    else
    {
        // Do nothing
    }
    
    // Display calendar
    switch (CALENDAR_DISP_TYPE)
    //switch (CALENDAR_DISP_TYPE_CALENDAR)
    {
        //calendar type is calendar
        case CALENDAR_DISP_TYPE_CALENDAR:
            lSubErrCode = SettingCalendarFunc( lpobjArea->m_vItemList, wDispYear, byDispMonth );
            break;
        // calendar type is period
        case CALENDAR_DISP_TYPE_KIKAN:

            vCalendarmax = SplitString( vobjCalendarItems[0]->m_sctProperty.sValue, UNDER_SCORE_SPLIT );

            //if ( vdwPeriod.size() != 2)
            if ( vCalendarmax.size() != 2 )
            {
                lSubErrCode = ERROR_CODE_NOT_CALEMDAR_DISP;
                break;
            }
            else
            {
                // Do nothing
            }

            lSubErrCode = SettingCalendarKikanFunc( lpobjArea->m_vItemList, atoi(vCalendarmax[0].c_str()), atoi(vCalendarmax[1].c_str()) );
            break;
        default:
            lSubErrCode = ERROR_CODE_NOT_CALEMDAR_DISP;
            break;
    }
    if ( lSubErrCode != GUI_RET_OK )
    {
        vlOutErrCode.push_back( lSubErrCode );
    }
    else
    {
        // Do nothing
    }

    // return value
    if ( vlOutErrCode.size() == 0 )
    {
        vlOutErrCode.push_back( GUI_RET_OK );
    }
    else
    {
        // Do nothing
    }
    return vlOutErrCode[0];
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  DisplayBranchButtonFunc
//
//�@�\�@�@��@�F  Handle display button request
//
//�@�T�@�@�v�@�F  Handle display button request
//
//�@�߁@��@�l�F  LONG lOutErrCode
//
//�@���@�@���@�F  SCT_BUTTON sctInButton       (I)        Button info is received from ViewIF
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/09    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG CGuiViewDlg::DisplayBranchButtonFunc(  SCT_GUI_MSG_DISP_TYPE_BTN_VIEW sctInButton )
{
    //Declare local variable
    vector<LONG>    vlOutErrCode;                   // Error code
    LONG            lSubErrCode         = GUI_RET_NG;                    // Error code of sub function
    vector<CItem*>  vobjStationBtns;                // Button of the same group
    vector<CItem*>  vobjLinkTagItems;               // Lighting condition linked items
    vector<CItem*>  vobjSearchItem;                 // List of item
    string          sTagGroup           = "";       // Tag group of item
    BOOL            bStationBtn         = FALSE;    // TRUE: Station button; FALSE: Others
    DWORD           dwIndex             = GUI_VALUE_ZERO_DWORD;        // Counter
    CItem*          lpobjItem           = NULL;     // Display item
    CItem*          lpobjBtnItem        = NULL;     // Button item
    CItem*          lpobjLiItem         = NULL;      // Link item
    CItem*          lpobjLinkTagItem    = NULL;     // Lighting condition linked item display
    DWORD           dwAutoTextSplitIndex = GUI_VALUE_ZERO_DWORD;       // Auto Test split index

    string          sTagID       ( sctInButton.szTagID, strlen (sctInButton.szTagID) );
    string          sLabelName   ( sctInButton.szLabel, strlen (sctInButton.szLabel) );
    vector<string>  vsStatus;
    vector<string>  vsLinkedStatus;
    string          sDesignSts          = "";
    string          sDesign             = "";
    std::smatch sm;
    DWORD           dwLoopIndex         = GUI_VALUE_ZERO_DWORD; 
    CArea*          lpobjArea           = NULL;
    wstring         wValue              = L"";
    wstring         wAltBtnAutoText     = L"";
    BOOL            bUserProcFlg        = FALSE;
    BOOL            bAltBtn             = FALSE;
    BOOL            bDrawFlag           = FALSE;
    string          sKindDesign         = "";

    // Reset data
    vlOutErrCode.clear();
    vobjStationBtns.clear();
    vobjLinkTagItems.clear();
    vobjSearchItem.clear();
    vsStatus.clear();
    vsLinkedStatus.clear();

    //********************* Check agrument ********************//
    // Check TagID NULL
    if ( sTagID == "" || (( sctInButton.dwMask & MASK_DISP_BTN_TAGID) != MASK_DISP_BTN_TAGID ))
    {
        vlOutErrCode.push_back( ERROR_CODE_NULL_ID );
    }
    else
    {
        // Do nothing
    }

    bUserProcFlg = JudgeUserDisplayProcFunc( sTagID );
    if ( bUserProcFlg == TRUE ) 
    {
        // ���[�U�Ǝ��W�J�̏ꍇ�͕ʏ����㏈���I������.
        lSubErrCode = TeikiShubeTsuDisplayFunc( sTagID );
        if ( lSubErrCode == GUI_RET_OK) 
        {
            vlOutErrCode.push_back( GUI_RET_OK );
        }
        else 
        {
            vlOutErrCode.push_back( lSubErrCode );
        }
        return vlOutErrCode[0];
    }


    // Check valid of sctInButton.dwWaySameBtn
    if (( sctInButton.dwMask & MASK_DISP_BTN_WAY_SAME_BTN ) == MASK_DISP_BTN_WAY_SAME_BTN )
    {
        switch ( sctInButton.dwWaySameBtn )
        {
            case WAY_DATA_ALL:
                //Search tag ID of all area.
                sctInButton.eAreaType = E_AREA_NULL;
                break;
            case WAY_DATA_SPECIFIED:
                // If the specified button update, check whether the area name exists.
                if (( sctInButton.dwMask & MASK_DISP_BTN_AREA_TYPE ) != MASK_DISP_BTN_AREA_TYPE )
                {
                    vlOutErrCode.push_back( ERROR_CODE_NULL );
                }
                else
                {
                    // Do nothing
                }
                break;
            default:
                vlOutErrCode.push_back( ERROR_CODE_NOT_RANGE );
                break;
        }
    }
    else
    {
        // Do nothing
    }
    
    // Check valid of sctInButton.bVisibility
    if (( sctInButton.byVisibility != FLG_OBJECT_VISIBLE ) &&
        ( sctInButton.byVisibility != FLG_OBJECT_HIDDEN  ) &&
        (( sctInButton.dwMask & MASK_DISP_BTN_VISIBILITY ) == MASK_DISP_BTN_VISIBILITY ))
    {
        vlOutErrCode.push_back( ERROR_CODE_NOT_RANGE );
    }
    else
    {
        // Do nothing
    }
    
    ///return if argrument is invalid
    if ( vlOutErrCode.size() > 0)
    {
        return vlOutErrCode[0];
    }
    else
    {
        //Do nothing
    }

    // Sync data from View IF
    if (( sctInButton.dwMask & MASK_DISP_BTN_VISIBILITY ) == MASK_DISP_BTN_VISIBILITY )
    {
        if ( sctInButton.byVisibility == TRUE )
        {
            sctInButton.byVisibility = FALSE;
        }
        else
        {
            sctInButton.byVisibility = TRUE;
        }
    }
    else
    {
        // Do nothing
    }
    
    if (( sctInButton.dwMask & MASK_DISP_BTN_ENABLE ) == MASK_DISP_BTN_ENABLE )
    {
        if ( sctInButton.byEnable == TRUE )
        {
            sctInButton.byEnable = FALSE;
        }
        else
        {
            sctInButton.byEnable = TRUE;
        }
    }
    else
    {
        // Do nothing
    }
    
    //********************* Get TagID info ********************//

    // Search EKI/KEIYU button
    if ((( sTagID.substr( 0, 1 ) == TAG_ID_NAME_EKI_BTN   )  || 
         ( sTagID.substr( 0, 1 ) == TAG_ID_NAME_KEIYU_BTN )) && 
         ( JudgeNumberFunc( SubStr( sTagID, 1 )) == JUDGE_HALF_NUMBER ))
    {
        if ( sTagID.substr( 0, 1 ) == TAG_ID_NAME_EKI_BTN )
        {
            sTagGroup = GROUP_NAME_EKI_BTN;
        }
        else
        {
            sTagGroup = GROUP_NAME_KEIYU_BTN;
        }

        bStationBtn = TRUE;
        vobjSearchItem = SearchEkiButtonIDFunc( "", sTagID, sTagGroup, sctInButton.eAreaType, "" );
    }
    // search button by TagID
    else
    {
        bStationBtn     = FALSE;
        vobjSearchItem  = SearchTagIDFunc( sTagID, sctInButton.eAreaType );
        if ( vobjSearchItem.size() == 0 )
        {
            bAltBtn = TRUE;
            vobjSearchItem = SearchAltTagIDFunc( "", sTagID, "button", sctInButton.eAreaType, "" );
        }
        else
        {
            // Do nothing
        }
    }
    // Not found item
    if ( vobjSearchItem.size() == 0 )
    {
        if ( gbPageChageLoadFlg == FALSE )
        {
            vlOutErrCode.push_back( ERROR_CODE_NOT_EXIST_ID );
            return vlOutErrCode[0];
        }
        else {} // Do nothing


    }
    else {} // Do nothing

    for ( dwLoopIndex = 0; dwLoopIndex < SWITCH_OPERATION_PAGE_TABLE_SIZE; dwLoopIndex++ )
    {
        // Found information
        if ( sTagID == Switch_OperationPage_Table[dwLoopIndex].sTagId )
        {
            break;
        }
    }

    // Found information
    sDesign = ( string )sctInButton.szDesign;
    if (( dwLoopIndex < SWITCH_OPERATION_PAGE_TABLE_SIZE ) &&
        ( sDesign     == DESIGN_BTN_ON                   ) &&
        ( Switch_OperationPage_Table[dwLoopIndex].sContenaKirikaeID != "" ) &&
        ( Switch_OperationPage_Table[dwLoopIndex].bOnPageChange == TRUE ))
    {
        if ( gbPageChageLoadFlg == TRUE )
        {
            gbPageChageLoadFlg = FALSE;
            if ( vobjSearchItem.size() == 0 )
            {    
                return GUI_RET_OK;
            }
            else
            {
                // Do nothing
            }
        }
        else
        {
            lSubErrCode = ChangeViewInnerPageFunc( Switch_OperationPage_Table[dwLoopIndex].sPageUrl, Switch_OperationPage_Table[dwLoopIndex].eAreaName );

            if ( RESULT_OK_INNER_PAGE_SWITCH == lSubErrCode ) 
            {
                return lSubErrCode;
            }
            else
            {
                // Do nothing
            }

        }
    }
    
    // Fetch all items of search result to change display
    for ( dwIndex = 0; dwIndex < vobjSearchItem.size(); dwIndex++ )
    {
        lpobjItem = vobjSearchItem[dwIndex];
        lpobjArea = GetCurrentAreaByAreaType( lpobjItem->m_sctProperty.eAreaType );
        if ( lpobjArea == NULL )
        {
            vlOutErrCode.push_back( ERROR_CODE_NULL );
            return vlOutErrCode[0];
        }
        else
        {
            // Do nothing
        }
        //Change display when TagName of Item is "A"
        if (( lpobjItem->m_sctProperty.sTagName == "a" ) &&
            ( strcmp( USER_NAME, "tb" ) == 0 ))
        {
            lpobjLiItem = lpobjItem;
            lSubErrCode = ChangeVisibleTagFunc( lpobjLiItem, lpobjArea->m_vItemList, sctInButton.byVisibility, sDesign );
            if ( lSubErrCode != GUI_RET_OK )
            {
                vlOutErrCode.push_back( lSubErrCode );
            }
            else
            {
                // Do nothing
            }
            break;
        }
        else
        {
            // Do nothing
        }

        // New version update==========>
        ////Change display when TagName of Item is "li"
        //if ( lpobjItem->m_sctProperty.sTagName == "li" )
        //{
        //    lpobjLiItem = lpobjItem;
        //    lSubErrCode = ChangeVisibleInsideTabFunc( lpobjLiItem );
        //    if ( lSubErrCode != GUI_RET_OK )
        //    {
        //        vlOutErrCode.push_back( lSubErrCode );
        //    }
        //    else
        //    {
        //        // Do nothing
        //    }
        //    break;
        //}


        // Check TagName of item is not BUTTON
        if (( lpobjItem->m_sctProperty.sTagName != "button" ) &&
            ( lpobjItem->m_sctProperty.sTagName != "a" ) &&
            ( lpobjItem->m_sctProperty.sTagName != "li" ))
        {
            vlOutErrCode.push_back( ERROR_CODE_NOT_ID_TYPE );
            continue;
        }
        else
        {
            // Do nothing
        }

        lpobjBtnItem = lpobjItem;

        // If sGroup of item is GROUP_NAME_ZASEKI -> it is a station button
        if ( lpobjBtnItem->m_sctProperty.sTagGroup == GROUP_NAME_ZASEKI )
        {
            bStationBtn = TRUE;
        }

        // Change visible of item
        if ( ( sctInButton.dwMask & MASK_DISP_BTN_VISIBILITY ) == MASK_DISP_BTN_VISIBILITY )
        {
            if ( sctInButton.byVisibility == ( BYTE )lpobjBtnItem->m_sctProperty.bVisible )
            {
                // TSDV-20150815-LanLTM-Fix bug label overlap button (Bug No4)
                bDrawFlag = TRUE;
                // TSDV-20150815-LanLTM-End
            }
            else
            {
                bDrawFlag = TRUE;
                if ( sctInButton.byVisibility == TRUE )
                {
                    lSubErrCode = ChangeClassIDFunc( lpobjBtnItem, DESIGN_VISIBLE );
                } 
                else
                {
                    lSubErrCode = ChangeClassIDFunc( lpobjBtnItem, DESIGN_HIDDEN );
                }
                if ( lSubErrCode != GUI_RET_OK )
                {
                    vlOutErrCode.push_back( lSubErrCode );
                }
                else
                {
                    //Do nothing
                }
            }
        }
        else
        {
            // Do nothing
        }
        
        // Change design of item
        // ViewIF has translated off[0-9] -> off
        if ( ( sctInButton.dwMask & MASK_DISP_BTN_DESIGN )  == MASK_DISP_BTN_DESIGN )
        {
            string sClass = lpobjBtnItem->m_sctProperty.sClass;
            std::smatch sm;
            if ( std::regex_search( sDesign, sm , std::regex( "^" + ( string )DESIGN_BTN_OFF + "[0-9]+$" )))
            {
                sKindDesign = DESIGN_BTN_OFF;

            }
            else
            {
                // < Added by [TSDV]SonPT - 2015/07/08 - Update source code js v20.20 >
                if (( sDesign == DESIGN_BTN_ON ) && ( bAltBtn == TRUE ) )
                {
                    sDesign = DESIGN_BTN_OFF;
                }
                sKindDesign = sDesign;
                // < End added section >
            }
            // design OFF
            if ( sKindDesign == DESIGN_BTN_OFF )
            {
                lSubErrCode = ChangeClassIDFunc( lpobjBtnItem, sDesign );
            }
            else if ( sKindDesign == DESIGN_BTN_ON )
            {
                ////Change design to ON
                lSubErrCode = ChangeDesignBtnOnFunc( lpobjBtnItem, dwLoopIndex, bStationBtn );
            }
            else if ( sKindDesign == DESIGN_BTN_DISABLE )
            {
                lSubErrCode = ChangeClassIDFunc( lpobjBtnItem, DESIGN_DISABLE );
            }
            else if ( sKindDesign == DESIGN_BTN_BLINK )
            {
                if ( ( sctInButton.dwMask & MASK_DISP_BTN_BLINK_CNT ) == MASK_DISP_BTN_BLINK_CNT )
                {
                    lSubErrCode = ChangeFlashingTagFunc( lpobjBtnItem, sctInButton.dwBlinkCnt, STS_NAME_UPDATE_ELEMENT_PARENT );
                }
                else
                {
                    // Do nothing
                }
            }
            else
            {
                lSubErrCode = ERROR_CODE_NOT_RANGE;
            }
        
            if ( lSubErrCode != GUI_RET_OK )
            {
                vlOutErrCode.push_back( lSubErrCode );
            }
            else
            {
                // Do nothing
            }
            if ( lpobjBtnItem->m_sctProperty.sClass == sClass )
            {
                // Do nothing
            }
            else
            {
                bDrawFlag = TRUE;
            }
        }
        else
        {
            // Do nothing
        }
        
        // Change of label (irgnore tooltip)
        if (( sctInButton.dwMask & MASK_DISP_BTN_LABEL ) == MASK_DISP_BTN_LABEL )
        {
            if ( lpobjBtnItem->m_sctProperty.sText == sLabelName )
            {
                // Do nothing
            }
            else
            {
                bDrawFlag = TRUE;
                lpobjBtnItem->m_sctProperty.sText = sLabelName;
                
                // < Modified by [TSDV]SonPT - 2015/07/08 - Update source code js v20.20 >

                // If lpobjBtnItem does not include <hr>
                if ( lpobjBtnItem->m_sctProperty.sBtn_Hr_Line_Class == "")
                {
                    // Do nothing
                }
                else
                {
                    lpobjBtnItem->m_sctProperty.sBtn_Hr_Line_Class = HR_LINE_STR_CLASS;
                    lpobjBtnItem->m_sctProperty.dwHrPos = 1; // Set possition of <hr> tag : BOTTOM
                }
                // < End modified>
            }
        }
        else
        {
            // Do nothing
        }
        
        // Enable/disable item
        if ( ( sctInButton.dwMask & MASK_DISP_BTN_ENABLE ) == MASK_DISP_BTN_ENABLE )
        {
            if ( lpobjBtnItem->m_sctProperty.bEnable == ( BOOL )sctInButton.byEnable )
            {
                // Do nothing
            }
            else
            {
                bDrawFlag = TRUE;
                switch ( sctInButton.byEnable )
                {
                    case TRUE:
                        lpobjBtnItem->UpdateEnable( TRUE );
                        break;

                    case FALSE:
                        lpobjBtnItem->UpdateEnable( FALSE );
                        break;

                    default:
                        vlOutErrCode.push_back( ERROR_CODE_NOT_RANGE );
                        break;
                }
            }
        }
        else
        {
            // Do nothing
        }
        

        // Change Auto set text

        if ( ( sctInButton.dwMask & MASK_DISP_BTN_AUTO_SET_TEXT ) == MASK_DISP_BTN_AUTO_SET_TEXT )
        {
            switch ( sctInButton.byAutoSetText )
            {
                case AUOT_SET_TEXT:
                    vobjLinkTagItems = SearchTagIDFunc ( lpobjBtnItem->m_sctProperty.sTagGroup, E_AREA_NULL );
                    if ( vobjLinkTagItems.size() != 1)
                    {
                        vlOutErrCode.push_back ( ERROR_CODE_NOT_EXIST_ID );
                    }
                    else
                    {
                        lpobjLinkTagItem = vobjLinkTagItems[0];

                        if ( lpobjLinkTagItem->m_sctProperty.sAltTagID == "" )
                        {
                            lpobjLinkTagItem->m_sctProperty.sText = lpobjBtnItem->m_sctProperty.sValue;
                        }
                        else
                        {
                            wValue              = StringToWChar( lpobjBtnItem->m_sctProperty.sValue );
                            wAltBtnAutoText     = StringToWChar( ALT_BUTTON_AUTO_TEXT_SPLIT );
                            dwAutoTextSplitIndex = wValue.find( wAltBtnAutoText );
                            sDesignSts = GetDesignStsFunc( lpobjBtnItem->m_sctProperty.sStatus );
                            if ( sDesignSts == DESIGN_BTN_ON )
                            {
                                lpobjLinkTagItem->m_sctProperty.sText = SubStr( lpobjBtnItem->m_sctProperty.sValue, 0, dwAutoTextSplitIndex );
                            }
                            else
                            {
                                lpobjLinkTagItem->m_sctProperty.sText = SubStr( lpobjBtnItem->m_sctProperty.sValue, dwAutoTextSplitIndex + 1);
                            }
                        }

                        // Redraw linked tag object item
                        ChangeClassIDFunc ( lpobjLinkTagItem, GetDesignStsFunc( lpobjLinkTagItem->m_sctProperty.sStatus ));
                        lpobjLinkTagItem->ItemUpdateState();
                    }
                    break;
                case AUOT_NOT_SET_TEXT:
                    break;
                default:
                    vlOutErrCode.push_back ( ERROR_CODE_NOT_RANGE );
                    break;
            }
        }
        else
        {
            // Do nothing
        }
        
        // special processing
        if ( ( sctInButton.dwMask & MASK_DISP_BTN_DESIGN ) == MASK_DISP_BTN_DESIGN )
        {
            if ( std::regex_search( lpobjBtnItem->m_sctProperty.sGaikan, sm , std::regex( string("^")  + PECULIAR_PROC_GAIKAN + string( "[0-9]_.*" ))))
            {
                lSubErrCode = SettingPeculiarItemFunc( lpobjBtnItem, lpobjArea->m_vItemList, sKindDesign );
                if ( lSubErrCode != GUI_RET_OK )
                {
                    vlOutErrCode.push_back( lSubErrCode );
                }
                else
                {
                    // Do nothing
                }
            }
            else
            {
                // Do nothing
            }
        }
        else
        {
            // Do nothing
        }
        

        // Redraw object item
        if ( bDrawFlag == TRUE )
        {
            lpobjBtnItem->ItemUpdateState();
        }
        else
        {
            // Do nothing
        }

    } // end for

    // Reutrn value
    if ( vlOutErrCode.size() == 0 )
    {
        vlOutErrCode.push_back( GUI_RET_OK );
    }
    else
    {
        // Do nothing
    }
    return vlOutErrCode[0];
}



/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  DisplayBranchImageFunc
//
//�@�\�@�@��@�F  Handle display image request
//
//�@�T�@�@�v�@�F  Handle display image request
//
//�@�߁@��@�l�F  LONG lOutErrCode
//
//�@���@�@���@�F  SCT_IMAGE sctInImage       (I)        Image info is received from ViewIF
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/09    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG CGuiViewDlg::DisplayBranchImageFunc( SCT_GUI_MSG_DISP_TYPE_CMD_IMG_VIEW sctInImage )
{
    //Declare local variable
    vector<LONG>    vlOutErrCode;                   // Error code
    LONG            lSubErrCode         = GUI_VALUE_ZERO_LONG;
    vector<CItem*>  vobjSearchItem;                 // List of item
    vector<CItem*>  vobjImgItem;                    // List of item
    string          sTagGroup           = "";       // Tag group of item
    DWORD           dwIndex             = GUI_VALUE_ZERO_DWORD;        // Counter
    CItem*          lpobjImgItem        = NULL;     // Display item
    vector<CItem*>  vobjAreaItem;

    // Reset data
    vlOutErrCode.clear();
    vobjSearchItem.clear();
    vobjImgItem.clear();
    vobjAreaItem.clear();

    /*char            cCurrentTime[16];
    sprintf( cCurrentTime, "%lu", time(NULL));
    string   sImgPara     ( cCurrentTime, strlen( cCurrentTime ) );*/
    string   sTagID       ( sctInImage.szTagID, strlen (sctInImage.szTagID) );
    string   sImgSrc      ( sctInImage.szFilePath, strlen (sctInImage.szFilePath) );
     //********************* Check agrument ********************//
    
    // Check TagID NULL
    if ( sTagID == "" || ( ( sctInImage.dwMask & MASK_DISP_IMG_TAGID ) != MASK_DISP_IMG_TAGID ) )
    {
        vlOutErrCode.push_back( ERROR_CODE_NULL_ID );
    }
    else
    {
        vobjSearchItem = SearchTagIDFunc( sTagID, E_AREA_NULL );

        if ( vobjSearchItem.size() == 0 )
        {
            vlOutErrCode.push_back( ERROR_CODE_NOT_EXIST_ID );
        }
        else
        {
            // Do nothing
        }
    }
    // Check valid of sctInButton.bVisibility
    if ( ( sctInImage.dwMask & MASK_DISP_IMG_VISIBILITY ) != MASK_DISP_IMG_VISIBILITY 
        || ( sctInImage.byVisibility != FLG_OBJECT_VISIBLE &&  sctInImage.byVisibility != FLG_OBJECT_HIDDEN ) )
    {
        vlOutErrCode.push_back( ERROR_CODE_NOT_RANGE );
    }
    else
    {
        // Do nothing
    }
    
    ////////////////// Return if argrument is invalid
    if ( vlOutErrCode.size() > 0)
    {
        return vlOutErrCode[0];
    }
    else
    {
        //Do nothing
    }
    
    if ( sctInImage.byVisibility == TRUE )
    {
        sctInImage.byVisibility = FALSE;
    }
    else
    {
        sctInImage.byVisibility = TRUE;
    }

    // Get the image display area
    vobjImgItem = SearchTagIDFunc ( sTagID, E_AREA_NULL);
    
    for ( dwIndex = 0; dwIndex < vobjSearchItem.size(); dwIndex++ )
    {
        
        // Catch error if TagName is not IMG
        // TSDV-LanLTM-20150503- FIx for bug Prismy number 136
        //if ( vobjSearchItem[dwIndex]->m_sctProperty.sTagName != "div" )
        if ( vobjSearchItem[dwIndex]->m_sctProperty.sTagName != "image" )
        // TSDV-LanLTM-20150503- FIx for bug Prismy number 136
        {
            vlOutErrCode.push_back ( ERROR_CODE_NOT_ID_TYPE );
            continue;
        }

        lpobjImgItem = vobjSearchItem[dwIndex];
        

        //Setting img src file in case of hidden object
        if ( sctInImage.byVisibility ==  FALSE)
        {
            // Change visible of item
            lSubErrCode = ChangeClassIDFunc( lpobjImgItem, DESIGN_HIDDEN );
            if ( lSubErrCode != GUI_RET_OK )
            {
                vlOutErrCode.clear();
                vlOutErrCode.push_back ( lSubErrCode );
            }
            else
            {
                // Do nothing
            }
            lpobjImgItem->m_sctProperty.sImgSrc = DUMMY_IMG_URL /* + (string)"?" + sImgPara*/;
        }
        //Setting img src file in case of visible object
        else
        {
            if ( sImgSrc == "" || (( sctInImage.dwMask & MASK_DISP_IMG_FILE_PATH ) != MASK_DISP_IMG_FILE_PATH ) )
            {
                vlOutErrCode.push_back( ERROR_CODE_NOT_EXIST_IMAGE );
            }
            else
            {
                // If found 1 img item in area AREA_NAME_IMG_DISP
                if ( vobjImgItem.size() == 1)
                {
                    if ( lpobjImgItem->m_sctProperty.sImgSrc == sImgSrc )
                    {
                        // Do nothing
                    }
                    else
                    {
                        lpobjImgItem->m_sctProperty.sImgSrc = sImgSrc; 
                    }
                    // Change item to visible
                    lSubErrCode = ChangeClassIDFunc( lpobjImgItem, DESIGN_VISIBLE );
                    if ( lSubErrCode != GUI_RET_OK )
                    {
                        vlOutErrCode.clear();
                        vlOutErrCode.push_back( lSubErrCode );
                    }
                    else
                    {
                        // Do nothing
                    }
                }
                else
                {
                    // Do nothing
                }
            }
        }//endif setting img file

        // Visible link tag id
        CArea* lpobjArea = GetCurrentAreaByAreaType ( lpobjImgItem->m_sctProperty.eAreaType );
        if ( lpobjArea == NULL )
        {
            vlOutErrCode.push_back( ERROR_CODE_NULL );
            return vlOutErrCode[0];
        }
        else
        {
            // Do nothing
        }
        VisibleLinkTagIdFunc( lpobjImgItem, lpobjArea->m_vItemList, sctInImage.byVisibility );
        
         // Redraw object item
        lpobjImgItem->ItemUpdateState();
    }//end for


    // Return value
    if ( vlOutErrCode.size() == 0 )
    {
        vlOutErrCode.push_back( GUI_RET_OK );
    }
    else
    {
        // Do nothing
    }
    return vlOutErrCode[0];
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  DisplayBranchTextItemFunc
//
//�@�\�@�@��@�F  Handle display text item request
//
//�@�T�@�@�v�@�F  Handle display text request
//
//�@�߁@��@�l�F  LONG lOutErrCode
//
//�@���@�@���@�F  SCT_TEXT_AREA sctInTextArea       (I)        Text info is received from ViewIF
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/09    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG CGuiViewDlg::DisplayBranchTextItemFunc( SCT_GUI_MSG_DISP_TYPE_TXT_VIEW sctInTextArea )
{
    //Declare local variable
    vector<LONG>    vlOutErrCode;                                       // Error code
    LONG            lSubErrCode         = GUI_RET_OK;                                        // Error code of sub function
    vector<CItem*>  vobjSearchItem;                                     // List of item
    string          sTagGroup           = "";                           // Tag group of item
    DWORD           dwIndex             = GUI_VALUE_ZERO_DWORD;         // Counter
    DWORD           dwSubIndex          = GUI_VALUE_ZERO_DWORD;         // Sub Counter
    string          sChangeDesign       = "";         // Temp variables
    //DWORD           dwMaxInputCount     = GUI_VALUE_ZERO_DWORD;         // Max input count
    LONG            lMaxInputCount     = GUI_VALUE_ZERO_LONG;         // Max input count
    //CItem*          lpobjItem           = NULL;                         // Display item
    CItem*          lpobjBatchItem      = NULL;                         // Batch item
    vector<CItem*>  vobjInputItems;                                     // Batch items
    char            cBatchTagID[MAX_ASC_TAGID_INTERNAL + 1];                                    // Tag ID of batch items
    string          sTagID ( sctInTextArea.szTagID, strlen (sctInTextArea.szTagID) );
    string          sTextData ( sctInTextArea.szData, strlen (sctInTextArea.szData) );
    vector<string>  vsTextData;
    CItem*          lpobjUpdateItem     = NULL;                         // Update item
    string          sDispText           = "";                            // Display text
    CItem*          lpobjInputItem      = NULL;
    string          sClassName          = "";                           // Class name (temp var)
    string          sConvStr            = "";
    CItem*          lpobjRichLblItem    = NULL;                         // Rich label item
    std::smatch sm;
    CArea*          lpobjArea           = NULL;
    CItem*          lpobjSenegapiItem   = NULL;
    vector<CItem* > vlpSpanChild;
    // TSDV-20150813-LanLTM-Fix big that button in center_disp_03_06_10_result area is not displayed
    BOOL            bIsDrawItem         = FALSE;                        // Flag to check drawing label or not
    // TSDV-20150813-LanLTM-End
    //********************* Check agrument ********************//
    
    // Reset data
    ( VOID )memset( &cBatchTagID[0], 0x00, sizeof( cBatchTagID ));
    vlOutErrCode.clear();
    vobjSearchItem.clear();
    vobjInputItems.clear();
    vsTextData.clear();


    // Check TagID NULL
    if ( sTagID == "" || (( sctInTextArea.dwMask & MASK_DISP_TXT_TAGID ) != MASK_DISP_TXT_TAGID) )
    {
        vlOutErrCode.push_back( ERROR_CODE_NULL_ID );
    }
    else
    {
        vobjSearchItem = SearchTagIDFunc( sTagID, E_AREA_NULL );
        if ( vobjSearchItem.size() == 0 )
        {
            vlOutErrCode.push_back( ERROR_CODE_NOT_EXIST_ID );
        }
        else
        {
            // Do nothing
        }
    }

    // Check valid of sctInButton.bVisibility/ display method
    if (( sctInTextArea.byVisibility != FLG_OBJECT_VISIBLE ) &&  
        ( sctInTextArea.byVisibility != FLG_OBJECT_HIDDEN  ) && 
        (( sctInTextArea.dwMask & MASK_DISP_TXT_VISIBILITY ) == MASK_DISP_TXT_VISIBILITY ))
    {
        vlOutErrCode.push_back( ERROR_CODE_NOT_RANGE );
    }
    else
    {
        // Do nothing
    }
    
    ///return if argrument is invalid
    if ( vlOutErrCode.size() > 0)
    {
        return vlOutErrCode[0];
    }
    else
    {
        //Do nothing
    }

    //Sync data from ViewIF
    if ( sctInTextArea.byVisibility == TRUE )
    {
        sctInTextArea.byVisibility = FALSE;
    }
    else
    {
        sctInTextArea.byVisibility = TRUE;
    }

    if ( sctInTextArea.byEnable == TRUE )
    {
        sctInTextArea.byEnable = FALSE;
    }
    else
    {
        sctInTextArea.byEnable = TRUE;
    }

    for ( dwIndex = 0; dwIndex < vobjSearchItem.size(); dwIndex++ )
    {
        // If tag Name is button, continue...
        if ( vobjSearchItem[dwIndex]->m_sctProperty.sTagName == "button" )
        {
            vlOutErrCode.push_back( ERROR_CODE_NOT_ID_TYPE );
            continue;
        }

        lpobjRichLblItem = vobjSearchItem[dwIndex];
        
        lpobjArea = GetCurrentAreaByAreaType ( lpobjRichLblItem->m_sctProperty.eAreaType );
        if ( lpobjArea == NULL )
        {
            vlOutErrCode.push_back( ERROR_CODE_NULL );
            return vlOutErrCode[0];
        }
        else
        {
            // Do nothing
        }
        // Request display item
        if (( sctInTextArea.dwMask & MASK_DISP_TXT_VISIBILITY ) == MASK_DISP_TXT_VISIBILITY )
        {
            // TSDV-20150813-LanLTM-Fix big that button in center_disp_03_06_10_result area is not displayed
            if ( sctInTextArea.byVisibility == lpobjRichLblItem->m_sctProperty.bVisible )
            {
                // Do nothing
            }
            else
            {
                bIsDrawItem = TRUE;
                if ( sctInTextArea.byVisibility == TRUE )
                {
                    // If the batch setting, it is not displayed
                    if ( lpobjRichLblItem->m_sctProperty.sGaikan != GROUP_NAME_IKKATSU_SET )
                    {
                        lSubErrCode = ChangeClassIDFunc( lpobjRichLblItem, DESIGN_VISIBLE );
                    }
                    else
                    {
                        // Do nothing
                    }
                }
                // Request hidden item
                else
                {
                    lSubErrCode = ChangeClassIDFunc( lpobjRichLblItem, DESIGN_HIDDEN );

                    //If you want to hide a provisional return tab, switch to the forward tab.
                    if ( lpobjRichLblItem->m_sctProperty.sTagID == TAG_ID_NAME_FUKURO_TAB )
                    {
                        VisibleInputTagIdTabFunc( lpobjRichLblItem, lpobjArea->m_vItemList );
                    }
                    else
                    {
                        // Do nothing
                    }
                }
            }
            // TSDV-20150813-LanLTM-End
        }
        else
        {
            // Nothing
        }
        if ( lSubErrCode != GUI_RET_OK )
        {
            vlOutErrCode.push_back( lSubErrCode );
        }
        else
        {
            // Do nothing
        }
        
        sChangeDesign = ( string )sctInTextArea.szDesign;
        
         if (( sctInTextArea.dwMask & MASK_DISP_TXT_VISIBILITY ) == MASK_DISP_TXT_VISIBILITY )
         {
            //Linked item display settings
            lSubErrCode = VisibleLinkTagIdFunc( lpobjRichLblItem, lpobjArea->m_vItemList, sctInTextArea.byVisibility );
            if ( lSubErrCode != GUI_RET_OK )
            {
                vlOutErrCode.push_back( lSubErrCode );
            }
            else
            {
                // Do nothing
            }
         }
         else
         {
            // Do nothing
         }
        
        /// Change text data
        if (( sctInTextArea.dwMask & MASK_DISP_TXT_DATA ) == MASK_DISP_TXT_DATA )
        {
            // TSDV-20150813-LanLTM-Fix big that button in center_disp_03_06_10_result area is not displayed
            bIsDrawItem = TRUE;
            // TSDV-20150813-LanLTM-End
            if ((( sctInTextArea.dwMask & MASK_DISP_TXT_WAY_SAME_BTN ) == MASK_DISP_TXT_WAY_SAME_BTN )&&
                 ( sctInTextArea.byWayDispData == WAY_DATA_ALL ) ||
                 ( sctInTextArea.byWayDispData == WAY_DATA_SPECIFIED ))
            {
                lSubErrCode = GUI_RET_OK;
                //In the case of batch setting, put the data in bulk item
                if ( lpobjRichLblItem->m_sctProperty.sGaikan == GROUP_NAME_IKKATSU_SET )
                {
                    string sMaxInputCount = "";
                    ConvFullHalNumberFunc ( lpobjRichLblItem->m_sctProperty.sText, TRUE , sMaxInputCount );
// Start TrungLV(20150502)
                    lMaxInputCount = atol( sMaxInputCount.c_str() );
// End TrungLV(20150502)
                    for ( dwSubIndex = 1; ( LONG ) dwSubIndex <= lMaxInputCount; dwSubIndex++)
                    {
                        // Reset data
                        ( VOID )memset( &cBatchTagID[0], 0x00, sizeof( cBatchTagID ));
                        sTextData       = "";
                        lpobjBatchItem  = NULL;
                        // Get batch tag ID
                        sprintf( cBatchTagID, "%s%s%d", lpobjRichLblItem->m_sctProperty.sTagID, TAG_ID_SPLIT, dwSubIndex); 
                        string   sTextData    ( cBatchTagID, strlen ( cBatchTagID ) );
                    
                        lpobjBatchItem = FindItemByTagID ( sTextData, lpobjArea->m_vItemList );
                        if ( lpobjBatchItem == NULL )
                        {
                            // Do nothing
                        }
                        else
                        {
                            vobjInputItems.push_back( lpobjBatchItem );
                        }
                    }
                    // TO DO split the text data
                    vsTextData = SplitString( sTextData, IKKATSU_DATA_SPLIT );
                
                }
                else
                {
                    vobjInputItems.push_back( lpobjRichLblItem );
                }

                for ( dwSubIndex = 0; dwSubIndex < vobjInputItems.size(); dwSubIndex++ )
                {
                    // Reset data
                    lpobjInputItem = NULL;

                    lpobjInputItem = vobjInputItems[dwSubIndex];
                    // item is parent
                    if ( lpobjInputItem->m_sctProperty.bParent == TRUE )
                    {
                        lpobjUpdateItem = lpobjInputItem;
                    }
                    // item is childen
                    else
                    {
                        lpobjUpdateItem = FindItemByTagID ( TAG_ID_NAME_SET_CHAR_SPAN, lpobjInputItem->m_vobjItems );   //vobjInputItems );
                        // If not found any items
                        if ( lpobjUpdateItem == NULL )
                        {
                            vlOutErrCode.push_back( ERROR_CODE_NULL_ID );
                            return vlOutErrCode[0];
                        }
                        else
                        {
                            // Do nothing
                        }
                    }

                    // To their updated with the contents you have split the case of a batch setting
                    if ( lpobjRichLblItem->m_sctProperty.sGaikan == GROUP_NAME_IKKATSU_SET )
                    {
                        if ( dwSubIndex < vsTextData.size() )
                        {
                            sTextData = vsTextData[dwSubIndex];
                        }
                        else
                        {
                            sTextData = "";
                        }
                    }
                    // rewrite
                    if ( sctInTextArea.byWayDispData == WAY_DATA_ALL )
                    {
                        sDispText = sTextData;
                    }
                    // add
                    else
                    {
                        sDispText = lpobjUpdateItem->m_sctProperty.sText + sTextData;
                    }

                    //If the display data is empty and apply empty is true, displays the initial display string
                    if (( sDispText == "" ) && 
                        ( lpobjRichLblItem->m_sctProperty.sNullStrInitApp == "true" ))
                    {
                        sDispText = lpobjRichLblItem->m_sctProperty.sInitText;
                        // If not specified, the design, I set the initial design.
                        if (( sctInTextArea.dwMask & MASK_DISP_TXT_DESIGN ) == MASK_DISP_TXT_DESIGN )
                        {
                            // Do nothing
                        }
                        else
                        {
                            sChangeDesign = DESIGN_TEXT_INIT_DISP;
                        }
                    }
                    else
                    {
                        // Do nothing
                    }
                    
                    lSubErrCode = GUI_RET_OK;
                    //If the tag ID is date of birth, format the data.
                    if ( std::regex_search( lpobjRichLblItem->m_sctProperty.sTagID, sm, std::regex( string("^")  + TAG_ID_NAME_SEINEN_GAPPI )))
                    {
                        // Update V10.28
                        sDispText = lpobjRichLblItem->m_sctProperty.sInitText;
                        if ( lpobjRichLblItem->m_sctProperty.sTagID == TAG_ID_NAME_SEINEN_GAPPI )
                        {
                            // Get the date element. Since the first span element is the element of the month.
                            lpobjSenegapiItem = FindItemByTagID ( TAG_ID_NAME_SET_CHAR_SPAN, lpobjUpdateItem->m_vobjItems );
                            // If not found any items
                            if ( lpobjSenegapiItem == NULL )
                            {
                                vlOutErrCode.push_back( ERROR_CODE_NULL_ID );
                                return vlOutErrCode[0];
                            }
                            else
                            {
                                // Do nothing
                            }
                            sClassName = lpobjSenegapiItem->m_sctProperty.sClass;
                        }
                        else
                        {
                            // Do nothing
                        }
                    
                        // Convert to date format
                        if ( sTextData != "" )
                        {
                            // To match the format to convert the data.
                            string sReturnStr = "";
                            lSubErrCode = ConvTagIdDateFormatFunc( 
                                lpobjRichLblItem->m_sctProperty.sTagID,
                                sTextData, 
                                CONVMODE_DISP, 
                                sClassName, 
                                sConvStr, 
                                sReturnStr );

                            //if ( lSubErrCode != GUI_RET_OK )
                            //{
                            //    vlOutErrCode.push_back( lSubErrCode );
                            //}
                            //else
                            //{
                            if ( lSubErrCode == ERROR_CODE_NOT_DATE )
                            {
                                //sDispText = to_string(( LONGLONG )ERROR_CODE_NOT_DATE );
                                // Update V10.28
                                sDispText = NullDateFormatSpaceFillFunc( lpobjRichLblItem->m_sctProperty.sTagID, sClassName );
                                if ( regex_search( sTextData, regex("^(0|�O)+$" )) )
                                {
                                    // Do nothing
                                }
                                else
                                {
                                    //sDispText = to_string(( LONGLONG )ERROR_CODE_NOT_DATE );
                                    vlOutErrCode.push_back( lSubErrCode );
                                }
                            }
                            else
                            {
                                //if ( sConvStr.find("<div class='nen'>") != string::npos )
                                //{
                                //    // Create div area
                                //    CreateSeinenGappi( lpobjRichLblItem, sConvStr );
                                //}
                                //else
                                //{
                                sDispText = sConvStr;
                                //}
                            }
                            //}
                        }
                        else
                        {
                            //If blank,  fill the space according to the format
                            // sDispText  = NullDateFormatSpaceFillFunc ( lpobjRichLblItem->m_sctProperty.sTagID, sClassName );
// Update V10.28
                            if ( lpobjRichLblItem->m_sctProperty.sNullStrInitApp == "false" )
                            {
                                sDispText = "";
                            }
                            if ( lpobjRichLblItem->m_sctProperty.sTagID == TAG_ID_NAME_SEINEN_GAPPI )
                            {
                                vlpSpanChild = FindItemsByTagName( "span", lpobjRichLblItem->m_vobjItems );
                                if ( vlpSpanChild.size() > 0 )
                                {
                                    vlpSpanChild[0]->m_sctProperty.sText = sDispText;
                                }
                                else
                                {
                                }
                            }
// Update V10.28
                        }
                    }// end if seinen gapi

                    if ( vlOutErrCode.size() == 0 )
                    {
                        if ( sDispText.find("<div class='nen'>") != string::npos )
                        {
                            // Create div area
                            CreateSeinenGappi( lpobjRichLblItem, sDispText );
                        }
                        else
                        {
                            lpobjUpdateItem->m_sctProperty.sText = sDispText;
                        }
                        if ( gclInputItemTag == NULL )
                        {
                            // Do nothing
                        }
                        else
                        {
                            if ( gclInputItemTag->m_sctProperty.sTagID == lpobjUpdateItem->m_sctProperty.sTagID )
                            {
                                if ( IsWindow( m_cCursor.m_hWnd ) == TRUE )
                                {
                                    // Set curor
                                    glRelativeCurPos = SerchInputGuidFunc ( sDispText, gsctInputFormat.sInputGuide, gsctInputFormat.bLeftJustify, gsctInputFormat.lRangeEnd );
                                    lSubErrCode = CursorMoveFunc( 0 );

                                    if ( lSubErrCode != GUI_RET_OK )
                                    {
                                        vlOutErrCode.push_back( lSubErrCode );
                                    }
                                    else
                                    {
                                        // Do nothing
                                    }

                                }
                                else
                                {
                                    // DO nothing
                                }
                            }
                            else
                            {
                                // Do nothing
                            }
                        }
                    }
                    else
                    {
                        // Do nothing
                    }
                    if ( lpobjInputItem->m_sctProperty.sTagID != TAG_ID_NAME_SEINEN_GAPPI )
                    {
                        ChangeHightClassFunc( lpobjInputItem );
                    }
                    else
                    {
                        // Do nothing
                    }
                }// end text data
            }
            else
            {
                vlOutErrCode.push_back( ERROR_CODE_NOT_RANGE );
            }
        }
        else
        {
            // TSDV-20150818-LanLTM- Fix bug No 5: Text label cannot displayed fully
            if (( sctInTextArea.dwMask & MASK_DISP_TXT_WAY_SAME_BTN ) == MASK_DISP_TXT_WAY_SAME_BTN )
            {
                bIsDrawItem = TRUE;
            }
            else
            {
                // Do nothing
            }
            // TSDV-20150818-LanLTM-End
        }
        

        // Change design
        if (( sctInTextArea.dwMask & MASK_DISP_TXT_DESIGN ) == MASK_DISP_TXT_DESIGN )
        {
            // TSDV-20150813-LanLTM-Fix big that button in center_disp_03_06_10_result area is not displayed
            bIsDrawItem = TRUE;
            // TSDV-20150813-LanLTM-End
            if (( sChangeDesign == DESIGN_TEXT_NOT_SELECT ) ||
                ( sChangeDesign == DESIGN_TEXT_SELECT )     ||
                ( sChangeDesign == DESIGN_TEXT_ERROR ))
            {
                lSubErrCode = ChangeClassIDFunc( lpobjRichLblItem, ( string )sctInTextArea.szDesign );
            }
            else if ( sChangeDesign == DESIGN_TEXT_DISABLE )
            {
                lSubErrCode = ChangeClassIDFunc( lpobjRichLblItem, DESIGN_DISABLE );
            }
            else if (( sChangeDesign == DESIGN_TEXT_BLINK_MOJI ) && 
                    (( sctInTextArea.dwMask & MASK_DISP_TXT_BLINK_CNT ) == MASK_DISP_TXT_BLINK_CNT ))
            {
                lSubErrCode = ChangeFlashingTagFunc( lpobjRichLblItem, sctInTextArea.dwBlinkCnt, STS_NAME_UPDATE_ELEMENT_CHILD );
            }
            else if (( sChangeDesign == DESIGN_TEXT_BLINK ) && 
                    (( sctInTextArea.dwMask & MASK_DISP_TXT_BLINK_CNT ) == MASK_DISP_TXT_BLINK_CNT ))
            {
                lSubErrCode = ChangeFlashingTagFunc( lpobjRichLblItem, sctInTextArea.dwBlinkCnt, STS_NAME_UPDATE_ELEMENT_PARENT );
            }
            else if ( sChangeDesign == DESIGN_TEXT_INIT_DISP )
            {
                lSubErrCode = ChangeClassIDFunc( lpobjRichLblItem, DESIGN_INIT );
                
                if (( "" == lpobjRichLblItem->m_sctProperty.sText ) && 
                    ( "true" == lpobjRichLblItem->m_sctProperty.sNullStrInitApp ))
                {
                    lpobjRichLblItem->m_sctProperty.sText = lpobjRichLblItem->m_sctProperty.sInitText;
                }
            }
            else if ( sChangeDesign == DESIGN_TEXT_DEFAULT )
            {
                ChangeFontColorFunc( lpobjRichLblItem, CHAR_COLOR_MODE_DELETE,   Character_Color_Table[CHARACTER_COLOR_TABLE_END].wMojiColor );
                lSubErrCode = ChangeItemAssignClassFunc( lpobjRichLblItem, "", ASSIGN_CLASS_MODE_DEL );
            }
            else
            {
                ChangeFontColorFunc( lpobjRichLblItem, CHAR_COLOR_MODE_DELETE,   Character_Color_Table[CHARACTER_COLOR_TABLE_END].wMojiColor );
                lSubErrCode = ChangeItemAssignClassFunc( lpobjRichLblItem, sChangeDesign, ASSIGN_CLASS_MODE_ADD );
            }
        
            if ( lSubErrCode != GUI_RET_OK )
            {
                vlOutErrCode.push_back( lSubErrCode );
            }
            else
            {
                // Do nothing
            }
        }
        else
        {
            // Do nothing
        }
        
        
        ////Enable/Disable item
        if (( sctInTextArea.dwMask & MASK_DISP_TXT_ENABLE ) == MASK_DISP_TXT_ENABLE )
        {
            // TSDV-20150813-LanLTM-Fix big that button in center_disp_03_06_10_result area is not displayed
            if ( lpobjRichLblItem->m_sctProperty.bEnable == sctInTextArea.byEnable )
            {
                // Do nothing
            }
            else
            {
                bIsDrawItem = TRUE;
                switch ( sctInTextArea.byEnable )
                {
                    case TRUE : 
                        lpobjRichLblItem->UpdateEnable( TRUE );
                        break;
                    case FALSE :
                        lpobjRichLblItem->UpdateEnable( FALSE );
                        break;
                    default :
                        vlOutErrCode.push_back( ERROR_CODE_NOT_RANGE );
                        break;
                }
            }
            // TSDV-20150813-LanLTM-End
        }
        else
        {
            // Do nothing
        }
        
        //// Change moji color
        if (( sctInTextArea.dwMask & MASK_DISP_TXT_MOJI_COLOR ) == MASK_DISP_TXT_MOJI_COLOR )
        {
            // TSDV-20150813-LanLTM-Fix big that button in center_disp_03_06_10_result area is not displayed
            bIsDrawItem = TRUE;
            // TSDV-20150813-LanLTM-End
            lSubErrCode = ChangeFontColorFunc(lpobjRichLblItem, CHAR_COLOR_MODE_ADD, sctInTextArea.dwMojiColor);
            if ( lSubErrCode != GUI_RET_OK )
            {
                vlOutErrCode.push_back( lSubErrCode );
            }
            else
            {
                // Do nothing
            }
        }
        else
        {
            // Do nothing
        }
        
        // Redraw object item
        /*if ( lpobjRichLblItem->m_sctProperty.bVisibilityHidden == TRUE )
        {
            dynamic_cast<CWnd*> ( lpobjRichLblItem )->ShowWindow ( SW_HIDE );
        }
        else
        {*/
        // TSDV-20150813-LanLTM-Fix big that button in center_disp_03_06_10_result area is not displayed
        if ( bIsDrawItem == TRUE )
        {
            lpobjRichLblItem->ItemUpdateState();
        }
        else
        {
            // Do nothing
        }
        // TSDV-20150813-End
           /* if (( bUpdateChild == true ) && ( lpobjUpdateItem != NULL ))
            {
                lpobjUpdateItem->ItemUpdateState();
            }*/
        //}
        
    }//end for

    // Return value
    if ( vlOutErrCode.size() == 0 )
    {
        vlOutErrCode.push_back( GUI_RET_OK );
    }
    else
    {
        // Do nothing
    }
    return vlOutErrCode[0];
}

/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////INPUT_PASSWORD.js////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  InputPasswordProcBranchFunc
//
//�@�\�@�@��@�F  Process input password
//
//�@�T�@�@�v�@�F  Process input password
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInObjItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/13    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
void CGuiViewDlg::InputPasswordProcBranchFunc( CItem* lpInObjItem )
{
    CItem*         objHeddinInput           = NULL;         // Hidden item pointer
    BOOL           bInputTagCheckResult     = FALSE;        // Judgment to chek input tag result
    LONG           lReturnValue             = GUI_RET_OK;   // Return value

    // Check lpInObjItem is null?
    if ( lpInObjItem == NULL )
    {
        return;
    }

    if ( gclInputItemTag == NULL )
    {
        // operate unspecified iteminput
        OtherInputRequestFunc( lpInObjItem->m_sctProperty.sTagID );
    }
    else
    {
        // if input item is BUTTON, do nothing
        if ( gclInputItemTag->m_sctProperty.sTagID == "button" )
        {
            return;
        }

        // Create input notify
        InputNoticeFunc( lpInObjItem->m_sctProperty.sTagID );
        // Get input password content object
        lReturnValue = GetHeddinPassTagFunc( objHeddinInput, gclInputItemTag->m_sctProperty.sTagID );
        if ( lReturnValue == ERROR_CODE_NOT_EXIST_ID )
        {
            return;
        }

        if ( lpInObjItem->m_sctProperty.sTagID == TAG_ID_NAME_ENTER )
        {
            // Delete display error
            ResolutiveDispInputErroFunc( gclInputItemTag, RESOLUTIVE_MODE_ENTER );
            bInputTagCheckResult = JudgeInputTagFunc();
            if ( bInputTagCheckResult ) {
                // When input item is existed( has not error )-> send request complete
                InputCompletRequestFunc( lpInObjItem, objHeddinInput->m_sctProperty.sValue );
            } else {
                // Display error
                ChangeDispInputErroFunc( gclInputItemTag ); 
            }
        }
        else
        {
            // When pushed button is not input item, delete error setting
            ResolutiveDispInputErroFunc( gclInputItemTag, RESOLUTIVE_MODE_INPUT);
            // When process result is unsucess-> update input content and control cursor
            PassCursorInputBranchFunc( lpInObjItem->m_sctProperty.sTagID, lpInObjItem->m_sctProperty.sValue, objHeddinInput );
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  InputPasswordKey_ProcBranchFunc
//
//�@�\�@�@��@�F  Process branch input password
//
//�@�T�@�@�v�@�F  Process branch input password
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/13    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::InputPasswordKey_ProcBranchFunc( CItem* lpInItem )
{
    // Initialize
    CItem*        objHeddinInput       = NULL;
    LONG          lRet                 = GUI_RET_OK;
    BOOL          bInputTagCheckResult = FALSE;

    // Check parameter
    if ( lpInItem == NULL )
    {
        return ERROR_CODE_NULL_ID;
    }

    // When input item is BUTTON, do nothing
    if ( gclInputItemTag->m_sctProperty.sTagName == "button" )
    {
        return GUI_RET_OK;
    }

    // Get hidden input password content
    lRet = GetHeddinPassTagFunc( objHeddinInput, lpInItem->m_sctProperty.sTagID );
    if ( lRet == ERROR_CODE_NOT_EXIST_ID )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }

    // Tag id is keyboard
    if ( lpInItem->m_sctProperty.sTagID == KEYBOARD_DATA_ENTER )
    {
        bInputTagCheckResult = JudgeInputTagFunc();
        if ( bInputTagCheckResult == TRUE )
        {
            ResolutiveDispInputErroFunc(gclInputItemTag, RESOLUTIVE_MODE_ENTER);
            lRet = InputCompletRequestFunc(lpInItem, objHeddinInput->m_sctProperty.sValue);
        }
        else
        {
            lRet = ChangeDispInputErroFunc( gclInputItemTag );
        }
    }
    else
    {
        ResolutiveDispInputErroFunc(gclInputItemTag, RESOLUTIVE_MODE_INPUT);
        lRet  = PassCursorInputBranchFunc( lpInItem->m_sctProperty.sTagID, NULL_STR, objHeddinInput );
    }

    return lRet;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  PassCursorInputBranchFunc
//
//�@�\�@�@��@�F  Control cursor when input password
//
//�@�T�@�@�v�@�F  Control cursor when input password
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/13    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::PassCursorInputBranchFunc( const string &sInTagID, const string &sInInputValue, CItem* lpInPassTagId )
{
    // Initialize
    LONG            lRet         = GUI_RET_OK;
    CItem*          objUpdateTag = NULL;

    // Check parameter
    if ( sInTagID == "" )
    {
        return ERROR_CODE_NULL_ID;
    }

    if ( lpInPassTagId == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }

    // Check global input item is NULL or not
    if ( gclInputItemTag == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }

    // Check cursor image is exist or not?
    if ( IsWindow( m_cCursor.m_hWnd ) == FALSE )
    {
        CursorAddFunc( INPUT_INIT_SHIJI_NOT_CHANGE );
    }
    else
    {
        // Do nothing
    }

    // Check global input item has children or not
    if ( gclInputItemTag->m_sctProperty.bParent == TRUE )
    {
        objUpdateTag = gclInputItemTag;
    }
    else
    {
        // follow statement
        objUpdateTag = FindItemByTagID (TAG_ID_NAME_SET_CHAR_SPAN , gclInputItemTag->m_vobjItems);
    }

    if ( objUpdateTag == NULL )
    {
        return ERROR_CODE_NULL;
    }

    // When input item initialize flag is true, initial display content
    if ( gbInputItemFirstInitializationFlg )
    {
        // Clear display content
        CursorPassAllDeleteCharacterFunc(objUpdateTag, lpInPassTagId);
        gbInputItemFirstInitializationFlg = FALSE;
    }

    if ( sInTagID == TAG_ID_NAME_TAB )
    {
        // Move cursor
        lRet = CursorMoveFunc( 1 );
    }
    else if ( sInTagID == TAG_ID_NAME_ALT_TAB )
    {
        lRet = CursorMoveFunc( -1 );
    }
    else if (( sInTagID == TAG_ID_NAME_BACK_SPACE ) || ( sInTagID == KEYBOARD_DATA_BS ))
    {
        lRet = CursorPassInputDeleteCharacterFunc(objUpdateTag, lpInPassTagId);
    }
    else if (( sInTagID == TAG_ID_NAME_CLEAR ) || ( sInTagID == KEYBOARD_DATA_CLEAR ))
    {
        lRet = CursorPassAllDeleteCharacterFunc(objUpdateTag, lpInPassTagId);
    }
    else
    {
        if ( sInInputValue == NULL_STR )
        {
            lRet = CursorPassInputUpdateCharacterFunc(objUpdateTag, lpInPassTagId, lpInPassTagId->m_sctProperty.sTagID, gclInputItemTag->m_sctProperty.lMaxLen );
        }
        else
        {
            lRet = CursorPassInputUpdateCharacterFunc(objUpdateTag, lpInPassTagId, sInInputValue , gclInputItemTag->m_sctProperty.lMaxLen );
        }
    }
    
    return lRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  CursorPassInputUpdateCharacterFunc
//
//�@�\�@�@��@�F  Insert character to cursor position-> move cursor
//
//�@�T�@�@�v�@�F  Insert character to cursor position-> move cursor
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/13    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::CursorPassInputUpdateCharacterFunc( 
                      CItem* lpInInputTagId, 
                      CItem* lpInPassTagId, 
                      string sInUpdateCharacter,
                      LONG   lInMaxLen )
{
    // Initialize
    LONG          lRet              = GUI_RET_OK; // Return value
    string        strLeftCharacter  = "";         // Left character of cursor
    string        strRightCharacter = "";         // Roght character of cursor
    string        strInputPass      = "";         // Input pass content
    string        strDispCharacter  = "";         // Display string
    DWORD         dwRoopCount;                    // Loop counter
    BOOL          bInsert           = FALSE;
    //CItem*        objInsert         = NULL;
    // Check parameter
    if( lpInInputTagId == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    else
    {
        // Do nothing
    }

    if( lpInPassTagId == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    else
    {
        // Do nothing
    }

    if( sInUpdateCharacter == NULL_STR )
    {
        return ERROR_CODE_NULL;
    }
    else
    {
        // Do nothing
    }

//Start Update v10.33 TrungLV
    bInsert = JudgeBlankInputStrFunc( lpInPassTagId->m_sctProperty.sValue, sInUpdateCharacter );

    if ( false == bInsert )
    {
        return GUI_RET_OK;
    }
    else
    {
        // Do nothing
    }
//End Update v10.33 TrungLV

    // get left character of cursor
    strLeftCharacter = SubStr( 
                           lpInPassTagId->m_sctProperty.sValue, 
                           0, 
                           glRelativeCurPos );

    ExcerptNotFormatFunc( 
        SubStr( gsctInputFormat.sInputGuide, 0, glRelativeCurPos ), 
        strLeftCharacter, 
        -1, 
        strLeftCharacter, 
        gsctInputFormat.bLeftJustify );

    // Get right character of cursor
    strRightCharacter = SubStr( 
                            lpInPassTagId->m_sctProperty.sValue, 
                            glRelativeCurPos );

    ExcerptNotFormatFunc( 
        SubStr( gsctInputFormat.sInputGuide, glRelativeCurPos ), 
        strRightCharacter, 
        -1, 
        strRightCharacter, 
        gsctInputFormat.bLeftJustify );

    if ( ( string )STR_INSERT_TYPE_ALWAYS != ( string )STR_INSERT_TYPE )
    {
        bInsert = JudgeInputStrFunc(
                    strLeftCharacter,
                    strRightCharacter,
                    sInUpdateCharacter,
                    lInMaxLen,
                    sInUpdateCharacter );
        if ( bInsert ) 
        {
            // Do nothing
        }
        else 
        {
            return GUI_RET_OK;
        }
    }

    strInputPass = strLeftCharacter + sInUpdateCharacter + strRightCharacter;

    // Input password, display content
    for ( dwRoopCount = 0; dwRoopCount < GetSize( strInputPass ); dwRoopCount++ )
    {
        strDispCharacter = strDispCharacter + DISP_PASS_CHARACTER;
    }
    // Combine input password
    AddFormatFunc( lpInInputTagId, 
                   gsctInputFormat.sInputGuide, 
                   strInputPass, 
                   FALSE,
                   gsctInputFormat.bLeftJustify, 
                   gsctInputFormat.lRangeEnd,
                   strInputPass);
    // Update password
    lpInPassTagId->m_sctProperty.sValue = strInputPass;
    // Update display string
    AddFormatFunc( lpInInputTagId,
                   gsctInputFormat.sInputGuide, 
                   strDispCharacter,
                   FALSE,
                   gsctInputFormat.bLeftJustify,
                   gsctInputFormat.lRangeEnd,
                   strDispCharacter );
    // Redraw item
    lpInInputTagId->m_sctProperty.sText = strDispCharacter;
    lpInInputTagId->ItemUpdateState();

    if ( gsctInputFormat.bLeftJustify == TRUE )
    {
        // Move cursor
        lRet = CursorMoveFunc(( LONG )GetSize( sInUpdateCharacter ));
    }
    return lRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  CursorPassInputDeleteCharacterFunc
//
//�@�\�@�@��@�F  Delete character at cursor position -> move cursor
//
//�@�T�@�@�v�@�F  Delete character at cursor position -> move cursor
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::CursorPassInputDeleteCharacterFunc( CItem* lpInInputTagId, CItem* lpInPassId )
{
    LONG            lRet             = GUI_RET_OK;                   // Return value
    string          strInputPass     = "";   // Input password content 
    string          strDispCharacter = "";   // Display string
    LONG            lDeleteIndex     = GUI_VALUE_ZERO_LONG;           // Delete position
    DWORD           dwRoopCount      = GUI_VALUE_ZERO_DWORD;             // Counter variable

    if ( lpInInputTagId == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }

    if ( lpInPassId == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    
    // get delete character position
    if ( gsctInputFormat.sInputGuide != "" )
    {
        for ( lDeleteIndex = glRelativeCurPos - 1; lDeleteIndex >= 0; lDeleteIndex-- ) 
        {
            if ( FORMAT_INPUT_ITEM == SubStr( gsctInputFormat.sInputGuide , lDeleteIndex , 1 )) 
            {
                break;
            }
        }
    }
    else
    {
        // Incase of Input Guide is not existed, set delete position is cursor position - 1
        lDeleteIndex = glRelativeCurPos - 1;
    }

    ExcerptNotFormatFunc( 
                    gsctInputFormat.sInputGuide,
                    lpInPassId->m_sctProperty.sValue,
                    lDeleteIndex ,
                    strInputPass, 
                    gsctInputFormat.bLeftJustify );

    // Input password, display Disp content
    for (dwRoopCount = 0; dwRoopCount < GetSize( strInputPass ); dwRoopCount++)
    {
        strDispCharacter = strDispCharacter + DISP_PASS_CHARACTER;
    }

    // Combine password input guide setting
    AddFormatFunc(
        lpInPassId, 
        gsctInputFormat.sInputGuide,
        strInputPass,
        FALSE, 
        gsctInputFormat.bLeftJustify,
        gsctInputFormat.lRangeEnd ,
        strInputPass ); // &sOutString

    // Update password
    lpInPassId->m_sctProperty.sValue = strInputPass;
    // Update display string
    AddFormatFunc(
        lpInPassId, 
        gsctInputFormat.sInputGuide,
        strDispCharacter,
        FALSE, 
        gsctInputFormat.bLeftJustify,
        gsctInputFormat.lRangeEnd,
        strDispCharacter );

    // Set text for item and redraw
    lpInPassId->m_sctProperty.sText = strDispCharacter;
    lpInPassId->ItemUpdateState();

    if ( gsctInputFormat.bLeftJustify == TRUE )
    {
        lRet = CursorMoveFunc( -1 );
    }
    return lRet;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  CursorPassAllDeleteCharacterFunc
//
//�@�\�@�@��@�F  Delete display content->move cursor to the first position
//
//�@�T�@�@�v�@�F  Delete display content->move cursor to the first position
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::CursorPassAllDeleteCharacterFunc( CItem* lpInInputTagId, CItem* lpInPassTagId )
{
    // Initialize
    LONG            lRet         = GUI_RET_OK;          // Internal function return
    
    // Check parameters
    if ( lpInInputTagId == NULL )
    {
        return ERROR_CODE_NULL;
    }

    if ( lpInPassTagId == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }

    // Init display
    lpInInputTagId->m_sctProperty.sText = gsctInputFormat.sInitDisp;
    lpInPassTagId->m_sctProperty.sValue = gsctInputFormat.sInitDisp;
    lpInInputTagId->ItemUpdateState();

    // Set cursor position
    SetCursorRelativePosition( gsctInputFormat.bLeftJustify );

    // Move cursor
    lRet = CursorMoveFunc( 0 );
    return lRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  GetHeddinPassTagFunc
//
//�@�\�@�@��@�F  Get item object of input pass content
//
//�@�T�@�@�v�@�F  Get item object of input pass content
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG CGuiViewDlg::GetHeddinPassTagFunc( CItem* &lpOutItem, const string &sInTagID )
{
    // Initialize
    vector<CItem*>  vSearchTagIdInfo;
    LONG    lRet    = GUI_RET_OK;

    // Clear data
    vSearchTagIdInfo.clear();

    // Find item that is hidden
    vSearchTagIdInfo = SearchTagIDFunc ( sInTagID + TAG_ID_NAME_INPUT_PASS, E_AREA_NULL ); 

    if ( vSearchTagIdInfo.size() != 1 )
    {
        // Coressponding password area just only 1 area
        return  ERROR_CODE_NOT_EXIST_ID;
    }
    else
    {
        lpOutItem = vSearchTagIdInfo[0];
        return lRet;
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////CONTROL_DISPLAY.js////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  VisibleLinkTagIdFunc
//
//�@�\�@�@��@�F  Incase linkaged tag id existed, process display or hide
//
//�@�T�@�@�v�@�F  Incase linkaged tag id existed, process display or hide
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::VisibleLinkTagIdFunc( CItem* lpobjInItem, const vector<CItem*>& vSearchItems, BOOL bVisible )
{
    // Initilize
    LONG            lProcResult         = GUI_RET_OK;  // Error code
    string          sVisibleDesign      = ""; 
    DWORD           dwRoopCount         = 0; 
    LONG            nLinkTagIndex       = -1;
    CItem*          objLinkTagId        = NULL; 

    // Check parameter
    if ( lpobjInItem == NULL )
    {
        return    ERROR_CODE_NULL;
    }

    switch ( bVisible )
    {
        case TRUE: // Display
            sVisibleDesign = DESIGN_VISIBLE;
            break;
        case FALSE: // Hide
            sVisibleDesign = DESIGN_HIDDEN;
            break;
        default:
            // Return error code
            return    ERROR_CODE_NOT_RANGE;
    }

    for ( dwRoopCount = 0; dwRoopCount < ARRAY_LENGTH( Link_Visible_TagId_Table ); dwRoopCount++ )
    {
        // Find tagID
        if ( lpobjInItem->m_sctProperty.sTagID == Link_Visible_TagId_Table[dwRoopCount].sKeyTagId )
        {
            nLinkTagIndex = dwRoopCount;
            break;
        }
    }
    // If item is not exist, return
    if ( nLinkTagIndex == -1 )
    {
        return lProcResult;
    }

    for ( dwRoopCount = 1; dwRoopCount <= LINK_VISIBLE_TAGID_MAX; dwRoopCount++ )
    {
        switch( dwRoopCount )
        {
            case 1: 
                objLinkTagId = FindItemByTagID( Link_Visible_TagId_Table[nLinkTagIndex].sLinkTagId_1, vSearchItems );
                break;
            case 2:
                objLinkTagId = FindItemByTagID( Link_Visible_TagId_Table[nLinkTagIndex].sLinkTagId_2, vSearchItems );
                break;
            case 3:
                objLinkTagId = FindItemByTagID( Link_Visible_TagId_Table[nLinkTagIndex].sLinkTagId_3, vSearchItems );
                break;
            case 4: 
                objLinkTagId = FindItemByTagID( Link_Visible_TagId_Table[nLinkTagIndex].sLinkTagId_4, vSearchItems );
                break;
            default:
                break;
        }
        
        if ( objLinkTagId == NULL ) 
        {
            continue;
        }
        // Update display or hide
        lProcResult = ChangeClassIDFunc( objLinkTagId, sVisibleDesign );
        if ( lProcResult     != GUI_RET_OK )
        {
            break;
        }
        objLinkTagId->ItemUpdateState();

    }
    return lProcResult;

}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  VisibleInputTagIdTabFunc
//
//�@�\�@�@��@�F  Update visibility of input item
//
//�@�T�@�@�v�@�F  Update visibility of input item
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::VisibleInputTagIdTabFunc( CItem* lpobjInItem, vector<CItem*> vInDocument )
{
    // Initilize
    LONG            lProcResult     = GUI_RET_NG;   // Error code
    string          strProcResult   = "";           // Result
    string          strTabName      = "";           // Tab name.
//    DWORD           dwPage          = 0;            // Page number.
    DWORD           dwTabCoun       = 0;            // Tab number
    vector<CItem*>  aryUl;                          // Ul item vector
    vector<CItem*>  aryDispTag;
    DWORD           dwRoopCount     = 0;            // Loop counter
    CItem*          objTabInput     = NULL;         // Tab
    CArea*          lpArea          = NULL;

    // Reset data
    aryUl.clear();
    aryDispTag.clear();

    // Check patameter
    if (lpobjInItem == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }

    // Check the existance of tab
    objTabInput = FindItemByTagID( TAG_ID_INPUT_TABS, vInDocument );
    if ( objTabInput == NULL )
    {
        return GUI_RET_OK;
    }

    // Search tag
    // TSDV-20150504-LanLTM- Fix bug Prismy no 162
    //aryDispTag = SearchTagIDFunc( lpobjInItem->m_sctProperty.sTagID, E_AREA_NULL );
    lpArea = GetCurrentAreaByAreaType ( E_AREA_DISP );

    if( lpArea == NULL ) 
    //if(aryDispTag.size() != 1) 
    // TSDV-20150504-LanLTM- End
    {
        return ERROR_CODE_NULL;
    }

    // Find item that is ul tag
    aryUl = FindItemsByTagName( "ul", vInDocument );
    if ( aryUl.size() == 0 )
    {
        return GUI_RET_OK;
    }

    strTabName = aryUl[0]->m_sctProperty.sTagID;
    if (TAG_ID_NAME_FUKURO_TAB == lpobjInItem->m_sctProperty.sTagID )
    {
        for( dwRoopCount = 0; dwRoopCount < aryUl[0]->m_vobjItems.size(); dwRoopCount++ )
        {
           // Switch tab
            if ( lpobjInItem->m_sctProperty.sTagID != aryUl[0]->m_vobjItems[dwRoopCount]->m_sctProperty.sTagID )
           {
               // aryDispTag[0]['tagId'].contentWindow.Oufukuro_Tab_kirikae( strTabName, 'page' + (nTabCoun+1), nTabCoun, false);
               
               // Considering
               // Oufukuro_Tab_kirikae( strTabName, 'page' + (nTabCoun+1), nTabCoun, false );               
               return GUI_RET_OK;
           }
           dwTabCoun = dwTabCoun + 1;
       }
    }

    if ( lpobjInItem->m_sctProperty.sTagID.find( "page" ) == std::string::npos ) //missing check: parent node tag != div
    {
        return GUI_RET_OK;
    }                      
    //if ( lpobjInItem->m_lpParent != NULL )
    //{
    //    dwPage = atoi( SubStr( lpobjInItem->m_sctProperty.sTagID, GetSize(lpobjInItem->m_lpParent->m_sctProperty.sTagID) - 1).c_str());
    //}
    // TODO: Oufukuro_Tab_kirikae function can not find anywhere, wait..
    //  aryDispTag[0]['tagId'].contentWindow.Oufukuro_Tab_kirikae(strTabName, inputTagId.parentNode.id, nPage -1, false);
    return lProcResult;
}  

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SettingPeculiarItemFunc
//
//�@�\�@�@��@�F  Settin gPeculiar Item
//
//�@�T�@�@�v�@�F  Setting PeculiarItem 
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::SettingPeculiarItemFunc( CItem* lpobjItem, const vector<CItem*> &vInDocument, const string &sInDesign )
{
    // Initilize
    LONG    lProcResult          = GUI_RET_OK;  // Error code

    string  strContenaTagId      = "";   // ��\�������p�^�OID.
    //DWORD   dwPeculiarCaseNum    = 0;    // ����P�[�X�ԍ�.
    LONG    lPeculiarCaseNum    = 0;    // ����P�[�X�ԍ�.
    string  sPeculiarCaseNum     = "";
    DWORD   dwRoopCount          = 0;    // ���[�v�J�E���g�ϐ�;
    CItem*  objHiddenTagId       = NULL; // ��\���p�^�OID.
    CItem*  objContenaTagId      = NULL; // �����^�OID.

    // Check parameter.
    if ( lpobjItem == NULL )
    {
        return ERROR_CODE_NULL_ID;
    }

    if ( vInDocument.size() == 0 )
    {
        return ERROR_CODE_NULL_ID;
    }

    // ����P�[�X�ԍ��̎擾(�O�ς�3������).    
    sPeculiarCaseNum  = SubStr( lpobjItem->m_sctProperty.sGaikan, 2,1 );
// TrungLV 20150502
    lPeculiarCaseNum = atol( sPeculiarCaseNum.c_str());

    switch( lPeculiarCaseNum )
    {
    case 1: // �R���e�i�ؑ֏���.
        // �X�e�[�^�X�̎擾.
        // �f�U�C�����_���ȊO�̏ꍇ�́A�ؑւ͍s��Ȃ�.
        if ( sInDesign != DESIGN_BTN_ON )
        {
            break;
        }

        // �^�OID�̒l�̃^�O�����݂��Ă��邩�`�F�b�N����.
        objContenaTagId = FindItemByTagID( lpobjItem->m_sctProperty.sPageAtr, vInDocument );

        if ( objContenaTagId == NULL )
        {
            lProcResult = ERROR_CODE_NOT_EXIST_ID;
            break;
        }
        // �擾�����^�O��\���ɕύX����.
        lProcResult = ChangeClassIDFunc( objContenaTagId, DESIGN_VISIBLE );
        strContenaTagId = regex_replace( objContenaTagId->m_sctProperty.sTagID, regex("[0-9]+$"), string(""));
        dwRoopCount = 1;

        while( true ) 
        {
            objHiddenTagId = FindItemByTagID( strContenaTagId + to_string(( LONGLONG ) dwRoopCount ), vInDocument );

            if ( objHiddenTagId == NULL ) 
            {
                break;
            }
            dwRoopCount = dwRoopCount + 1;
            if ( objContenaTagId->m_sctProperty.sTagID == objHiddenTagId->m_sctProperty.sTagID )
            {
                continue;
            }

            ChangeClassIDFunc(objHiddenTagId, DESIGN_HIDDEN);
        }
        break;
    default: // �Y���Ȃ�.
        break;
    }
    return lProcResult;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SettingCalendarKikanFunc
//
//�@�\�@�@��@�F  Display calendar
//
//�@�T�@�@�v�@�F  Display calendar
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::SettingCalendarKikanFunc( const vector<CItem*> &vobjInCalendarDocument, DWORD dwInDispMaxRow, DWORD dwInDispMaxCol )
{
    // Initilize
    LONG             lProcResult         = GUI_RET_OK;              // Error code
    DWORD            dwMaxDate           = GUI_VALUE_ZERO_DWORD;    // �ő�\������.
    DWORD            dwRowCount          = 1;                       // �s��.
    DWORD            dwColCount          = 1;                       // ��.
    string           sWeek               = "";                      // �j��.
    string           sBeforeGaikan       = "";                      // �ύX�O�O�σN���X.
    string           sDateTagId          = "";                      // ���t�^�OID��.
    string           sMonth              = "";                      // ��.
    string           sDay                = "";                      // ��.
    string           sDispData           = "";                      // ���t�\��������.
    DWORD            dwRoopCount         = GUI_VALUE_ZERO_DWORD;    // ���[�v�J�E���g�ϐ�.
    DWORD            dwHolidayCount      = GUI_VALUE_ZERO_DWORD;    //�j���J�E���g.
    vector<SCT_DATE> aryHoliday;                                    // �\���ɊY������j��.
    CItem*           objTagDate          = NULL;                    // ���t�^�OID.
    SCT_DATE         objDispDate;                                   // ���t�\���ݒ�p�I�u�W�F�N�g.
    SCT_DATE         objDispEndDate;                                // �\�����t�I���I�u�W�F�N�g.
    SCT_DATE         objResultDate;                                 // ���ݓ����茋��.
    LONG             lFuncResult         = GUI_RET_NG;              // Error code of return function

    // �����`�F�b�N.
    if ( vobjInCalendarDocument.size() == 0 )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }

    dwMaxDate = dwInDispMaxRow * dwInDispMaxCol;

    objDispDate  = gsctStartDate;
    gsctDispDate = objDispDate;

    objDispEndDate = gsctStartDate; 

    // TSDV-LanLTM-20150901-Fix bug No10: Date time error when displaying icon �g�y�x���h
    //objDispEndDate = AddDay(dwMaxDate, objDispEndDate );
    objDispEndDate = AddDay((LONG)dwMaxDate, objDispEndDate );
    // TSDV-LanLTM-20150901-Fix bug No10-END

    for ( dwRoopCount = 0; dwRoopCount < gsctHolidayArray.size(); dwRoopCount++ )
    {
        if ( JudgeDateValidityFunc( gsctHolidayArray[dwRoopCount], &objResultDate, lFuncResult )) 
        {
            if (( objDispDate <= objResultDate) &&
                ( objResultDate <= objDispEndDate ))
            {
                aryHoliday.push_back( objResultDate );
            }
        }
    }

    std::sort(aryHoliday.begin(),aryHoliday.end()); 
    while( dwRowCount <= dwInDispMaxRow ) 
    {
        sDateTagId = ( string )TAG_ID_INPUT_CALENDAR_DATE + ( string )TAG_ID_SPLIT + to_string(( LONGLONG )dwRowCount ) + TAG_ID_SPLIT + to_string(( LONGLONG )dwColCount );
        objTagDate  = FindItemByTagID( sDateTagId, vobjInCalendarDocument ); 
        // ���݂��Ȃ��ꍇ�A���̃��[�v���s��.
        if( objTagDate == NULL )
        {
            dwRowCount = dwRowCount + 1;
            dwColCount = 1;
            continue;
        }
        // Convert full number
        ConvFullHalNumberFunc( to_string(( LONGLONG )objDispDate.wYear), FALSE, sDispData );

        // Get month string
        sMonth =  to_string(( LONGLONG )(( WORD )objDispDate.byMonth ));

        // Convert number string
        ConvFullHalNumberFunc( sMonth, FALSE, sMonth );
        ConvZeroPaddingFunc( sMonth, ZERO_PADDING_AVAILABLE, 2, sMonth );

        // Convert day string
        sDay = to_string(( LONGLONG )objDispDate.byDay );
        ConvFullHalNumberFunc(sDay, FALSE, sDay );
        ConvZeroPaddingFunc( sDay, ZERO_PADDING_AVAILABLE, 2, sDay );

        // Set display data
        sDispData = sDispData + sMonth + sDay;
        objTagDate->m_sctProperty.sValue = sDispData;
        sDispData = ConvDateFormatFunc( objDispDate, CALENDAR_DATE_FORMAT );
        if (( sDispData == to_string(( LONGLONG )ERROR_CODE_NULL               )) ||
            ( sDispData == to_string(( LONGLONG )ERROR_CODE_CONV_ANNO_JAPANESE )))    // Update new javascript
        {
            sDispData = objTagDate->m_sctProperty.sValue;
        }
        objTagDate->m_sctProperty.sText = sDispData;
        sBeforeGaikan = objTagDate->m_sctProperty.sGaikan;
        objTagDate->ItemUpdateState();

        // �j�������߂�.
        sWeek = CalculationWeekFunc( objDispDate );
        // �j���̏ꍇ�́A�j���Ɂu�j���v������B
        for ( dwRoopCount = dwHolidayCount; dwRoopCount < aryHoliday.size(); dwRoopCount++)
        {
            // �j���̃J�E���g�����[�v�J�E���g��1���������ɕύX����.
            if ( objDispDate == aryHoliday[dwRoopCount] )
            {
                sWeek = DAY_OF_WEEK_HOLIDAY;
                // ���[�v�𔲂���
                dwHolidayCount = dwHolidayCount + 1;
                break;
            }
        }
        if ( sWeek == DAY_OF_WEEK_SATURDAY )
        {
            objTagDate->m_sctProperty.sGaikan =  Calendar_Date_Gaikan_Table.sSaturday;
        }
        else if ( sWeek == DAY_OF_WEEK_SUNDAY )
        {
            objTagDate->m_sctProperty.sGaikan =  Calendar_Date_Gaikan_Table.sHoliday;
        }
        else if ( sWeek == DAY_OF_WEEK_HOLIDAY )
        {
            objTagDate->m_sctProperty.sGaikan =  Calendar_Date_Gaikan_Table.sHoliday;
        }
        else
        {
            objTagDate->m_sctProperty.sGaikan =  Calendar_Date_Gaikan_Table.sWeekday;
        }   

        if ( objDispDate == gsctBasicDate )
        {
            lProcResult = ChangeClassIDFunc( objTagDate, DESIGN_BTN_ON, sBeforeGaikan );
            objTagDate->UpdateEnable( TRUE );
        }
        else if (( gsctStartDate <= objDispDate ) && ( objDispDate <= gsctEndDate ))
        {
            lProcResult = ChangeClassIDFunc( objTagDate, DESIGN_BTN_OFF, sBeforeGaikan );
            objTagDate->UpdateEnable( TRUE );
        }
        else
        {
            objTagDate->UpdateEnable( FALSE );
            lProcResult = ChangeClassIDFunc( objTagDate, DESIGN_DISABLE, sBeforeGaikan );
        }
        dwColCount = dwColCount + 1;
        if ( dwInDispMaxCol < dwColCount ) 
        {
            dwRowCount = dwRowCount + 1;
            dwColCount = 1;
        }
        // ���̓��ɕύX����.
        objDispDate = AddDay( 1, objDispDate );
        //objDispDate.SetDate(objDispDate.byDay + 1);

        // Re-draw item
        objTagDate->ItemUpdateState();
    }

    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////END CONTROL_DISPLAY.js////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////CONV_FORMAT.js////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ConvAnnoDominiOrJapaneseCalendarFunc
//
//�@�\�@�@��@�F  Convert calendar ( JP calendar-> normal calendar and normal calendar-> JP calendar )
//
//�@�T�@�@�v�@�F  Convert calendar ( JP calendar-> normal calendar and normal calendar-> JP calendar )
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ConvAnnoDominiOrJapaneseCalendarFunc(
                         string sInConvDate,
                        const string &sInConvMode, 
                        string &sOutConvYearStr )
{
    LONG          lRet            = GUI_RET_OK;                // Return value
    string        strMonthDay     = "";
    string        strJudgeNumber  = "";
    string        strEraName      = "";
    string        sYear           = "";
    //DWORD         lYear          = 0;
    LONG          lYear           = GUI_VALUE_ZERO_LONG;
    //DWORD         lMonth         = GUI_VALUE_ZERO_DWORD;
    LONG          lMonth          = GUI_VALUE_ZERO_LONG;
    //DWORD         lDay           = GUI_VALUE_ZERO_DWORD;
    LONG          lDay            = GUI_VALUE_ZERO_LONG;
    DWORD         dwRoopCount     = GUI_VALUE_ZERO_DWORD;
    //DWORD         dwConvDate      = GUI_VALUE_ZERO_DWORD;
    LONG          lJudgeNumber    = GUI_VALUE_ZERO_LONG;
    string        sOutConvYear    = "";
    string        sHalfConvDate   = "";
    SCT_DATE      sctMeijiDate;
    SCT_DATE      sctResultDate;
    SCT_DATE      sctConvDateFromStr;
    LONG          lErrCode        = 0;
    BOOL          bRet            = FALSE;
    //var objResultDate; // ���t���茋��.
    sOutConvYear = "";
    if ((sInConvDate != NULL_STR ) )
    {
        if ( GetSize( sInConvDate ) == 8) 
        {
            // Store month day info
            strMonthDay = SubStr( sInConvDate, 4, 4 );
        } else 
        {
            // If string is not 8 character, return error            
            return ERROR_CODE_NOT_DATE; // fix follow TSBJ review 
        }
    }
    else
    {
        return ERROR_CODE_NULL; // fix follow TSBJ review 
    }
    sctMeijiDate = SCT_DATE( ( WORD ) Calendar_Year_Table[0].dwAnnoDomini, ( BYTE ) Calendar_Year_Table[0].dwStartMonth , ( BYTE ) Calendar_Year_Table[0].dwStartDay );
    if ( sInConvMode == CONV_YEAR_ANNO_DOMINI )
    {
        strEraName = SubStr( sInConvDate, 0, 2 );
        sYear = SubStr( sInConvDate, 2, 2 );
        for( dwRoopCount = 0; dwRoopCount < CALENDAR_YEAR_TABLE_SIZE; dwRoopCount++ )  // TSBJ review 's fix action
        {
            if( Calendar_Year_Table[dwRoopCount].sEraName == strEraName )
            {
                lJudgeNumber = JudgeNumberFunc( sYear );

                switch( lJudgeNumber )
                {
                    case JUDGE_FULL_NUMBER:
                        // If it is full character, convert to half character
                        ConvFullHalNumberFunc( sYear, true, sYear );
                        lYear = atol( sYear.c_str());
                        break;
                    case JUDGE_HALF_NUMBER:
                        // If is half, convert to value
                        lYear = atol( sYear.c_str());
                        break;
                    default:
                        return ERROR_CODE_NOT_DATE; // fix follow TSBJ review 
                }

                if (( 1 <= lYear )&& 
                    ( lYear <= ( LONG ) Calendar_Year_Table[dwRoopCount].dwEraNameLastYear ) )
                {
                    // Calculate Anno Domini( West calendar)
                    sOutConvYear = std::to_string(( LONGLONG )lYear + ( Calendar_Year_Table[dwRoopCount].dwAnnoDomini - 1 ));
                    if (JUDGE_FULL_NUMBER == lJudgeNumber)
                    {
                        ConvFullHalNumberFunc(sOutConvYear, false, sOutConvYear );
                    }
                    sInConvDate = "" + sOutConvYear + strMonthDay;
                }
                else
                {
                    return ERROR_CODE_CONV_ANNO_JAPANESE; // fix follow TSBJ review 
                }

                if (( 0 == dwRoopCount ) && ( 1 == lYear))
                {
                    ConvertStr2DateSct( sInConvDate, sctConvDateFromStr );
                    bRet = JudgeDateValidityFunc( sctConvDateFromStr, &sctResultDate, lErrCode );
                    if ( bRet == TRUE )
                    {
                        if (  sctResultDate < sctMeijiDate )
                        {
                            return ERROR_CODE_CONV_ANNO_JAPANESE;
                        }
                    }
                    else 
                    {
                        return ERROR_CODE_CONV_ANNO_JAPANESE;
                    }
                }
                break;
            }
        }
        if ( sOutConvYear == "" )
        {
            // if at end loop, strConvYear is not changed, return error
            return ERROR_CODE_CONV_ANNO_JAPANESE;
        }

        //else
        //{
        //    if ( strJudgeNumber == std::to_string(( LONGLONG )JUDGE_FULL_NUMBER ))
        //    {
        //        ConvFullHalNumberFunc( sOutConvYear, false, sOutConvYear );
        //    }
        //}

    }
    else if ( sInConvMode == CONV_YEAR_JAPANESE_CALENDAR )
    {
        ConvertStr2DateSct( sInConvDate, sctConvDateFromStr );
        bRet = JudgeDateValidityFunc( sctConvDateFromStr, &sctResultDate, lErrCode );
        if ( bRet == TRUE )
        {
            lYear   = (LONG)sctResultDate.wYear;
            lMonth  = (LONG) sctResultDate.byMonth;
            lDay    = (LONG) sctResultDate.byDay;
        }
        else
        {
            return ERROR_CODE_CONV_ANNO_JAPANESE;
        }

        //// JP conversion
        //dwJudgeNumber = JudgeNumberFunc( sInConvDate );
        //if ( dwJudgeNumber == JUDGE_FULL_NUMBER )
        //{
        //     ConvFullHalNumberFunc( sInConvDate, true , sInConvDate );
        //}
        //else if ( dwJudgeNumber == JUDGE_HALF_NUMBER )
        //{
        //    // If it is half string, convert to number
        //    dwConvDate = atoi( sInConvDate.c_str() );
        //    lYear  = atoi( SubStr( sInConvDate, 0, 4 ).c_str());
        //    lMonth = atoi( SubStr( sInConvDate, 4, 2 ).c_str() );
        //    lDay   = atoi( SubStr( sInConvDate, 6, 2 ).c_str() );
        //}
        //else
        //{
        //    lRet =  ERROR_CODE_NOT_DATE;
        //    return lRet;
        //}

        //if ( Calendar_Year_Table[0].dwAnnoDomini > lYear )
        if ( sctResultDate <  sctMeijiDate )
        {
            return ERROR_CODE_CONV_ANNO_JAPANESE; // Fix follow TSBJ review
        }
        for( dwRoopCount = 0; dwRoopCount < CALENDAR_YEAR_TABLE_SIZE; dwRoopCount++ ) // Fix follow TSBJ review
        {
            if ( lYear == ( LONG ) Calendar_Year_Table[dwRoopCount].dwAnnoDomini )
            {
                if (( dwRoopCount == 0 )                                        ||
                    (( LONG ) Calendar_Year_Table[dwRoopCount].dwStartMonth < lMonth ) ||
                    ((( LONG ) Calendar_Year_Table[dwRoopCount].dwStartMonth == lMonth ) && (( LONG ) Calendar_Year_Table[dwRoopCount].dwStartDay <= lDay ) ) )
                {
                    strEraName = Calendar_Year_Table[dwRoopCount ].sEraName;
                    lYear = 1;
                }
                else
                {
                    strEraName = Calendar_Year_Table[dwRoopCount - 1].sEraName;
                    lYear      = (LONG) Calendar_Year_Table[dwRoopCount - 1].dwEraNameLastYear;
                }
                break;
            }
            else
            {
                if ((( CALENDAR_YEAR_TABLE_SIZE - 1 ) == dwRoopCount ) ||        // Fix follow TSBJ review
                    (( LONG ) Calendar_Year_Table[dwRoopCount + 1].dwAnnoDomini > lYear ))
                {
                    lYear      = lYear - (Calendar_Year_Table[dwRoopCount].dwAnnoDomini - 1);
                    strEraName  = Calendar_Year_Table[dwRoopCount].sEraName;
                    break;
                }
            }
        }
        ConvZeroPaddingFunc( std::to_string(( LONGLONG )lYear), ZERO_PADDING_AVAILABLE, 2, sYear );
        if ( strJudgeNumber == std::to_string(( LONGLONG )JUDGE_FULL_NUMBER) )
        {
            ConvFullHalNumberFunc( std::to_string(( LONGLONG ) lYear), false, sYear);
        }
        sOutConvYear = strEraName + sYear;
    }
    else
    {
        return ERROR_CODE_NOT_RANGE; // Fix follow TSBJ review
    }
    sOutConvYear = sOutConvYear + strMonthDay;
    sOutConvYearStr = sOutConvYear;
    return lRet;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ConvDispCommaFunc
//
//�@�\�@�@��@�F  
//
//�@�T�@�@�v�@�F  
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ConvDispCommaFunc( 
                                     string sConvData, DWORD dwInConvMode, string &sOutData )
{
    // Initialize
    LONG lRet                   = GUI_RET_OK;
    string       strJudgeNumber = ""; 
    LONG         lJudgeNumber   = GUI_VALUE_ZERO_LONG;
    wstring      wsConvData     = L"";

    // Check initialize convert mode
    switch ( dwInConvMode )
    {
        case DISP_COMMA_NOT_AVAILABLE :
            sConvData = regex_replace( sConvData, regex(","),string(""));
            sConvData = regex_replace( sConvData, regex("�C"),string(""));
            break;
        case DISP_COMMA_AVAILABLE:
            // �J���}�L��ւ̕ϊ�.
            lJudgeNumber = JudgeNumberFunc( sConvData );
            switch (lJudgeNumber) {
                case JUDGE_FULL_NUMBER :
                    // Full
                     ConvFullHalNumberFunc( sConvData, true,sConvData );
                    // Convert
                     // TODO: Need to find regex_replace for wchar
                     wsConvData = StringToWChar( sConvData );
                    while( wsConvData != ( wsConvData = regex_replace( wsConvData, wregex( L"^(�|?[�O-�X]+)([�O-�X]{3})"), wstring( L"$1�C$2")))) 
                    {
                        // Do nothing
                    }
                    sConvData = WCharToString( wsConvData );
                    break;
                case JUDGE_HALF_NUMBER : 

                    // �ϊ��������s��.
                    while( sConvData != (sConvData = regex_replace( sConvData, regex("^(-?[0-9]+)([0-9]{3})"), string("$1,$2"))))
                    {
                        // Do nothing
                    }   
                    break;
                default : 
                    return ERROR_CODE_NOT_NUMBER;
            }
            break;
        default : 
            return ERROR_CODE_NOT_RANGE;
    }

    sOutData = sConvData;
    return lRet;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ConvZeroPaddingFunc
//
//�@�\�@�@��@�F  Convert format
//
//�@�T�@�@�v�@�F  Add/remove zero follow format
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ConvZeroPaddingFunc(  string sInConvData, DWORD dwInConvMode, DWORD dwInMaxLength, string &sOutConvDataStr )
{
    LONG          lRet              = GUI_RET_OK;
    string        sJudgeNumber      = ""; // Judge number
    LONG          lJudgeNumber     = GUI_VALUE_ZERO_LONG;  // Judge number
    string        sZero             = ""; // zero string
    DWORD         dwRoopCount       = 0;  // Counter
    wstring       sWideResult       = L"";
   /* string        sOutConvData     = "";
    sOutConvData = "";*/

    // Check parameter
#if 0
    if (sInConvData != "" )
    {
        // Do nothing
    } 
    else 
    {
        sOutConvDataStr = to_string(( LONGLONG ) ERROR_CODE_NULL );
        return ERROR_CODE_NULL;
    }
#endif

    switch ( dwInConvMode ) {
        case ZERO_PADDING_NOT_AVAILABLE : 
            // Remove 0 from number half string
            sInConvData = regex_replace( sInConvData, regex("^0+([0-9]+)"),string("$1"));
            // Remove 0 from number full string
            sWideResult = regex_replace(StringToWChar( sInConvData ), wregex(L"^�O+([�O-�X]+)"),wstring(L"$1"));
            sInConvData = WCharToString( sWideResult );
            break;
        case ZERO_PADDING_AVAILABLE : 
            // �O���Ɂu0�v���ő啶�����ɒB����܂Œǉ�����.
            // �ő啶���������l�ł��邱�ƁA�f�[�^��0�`100�ł��邱�� �f�[�^���S�p���l�̏ꍇ�̓G���[�ƂȂ�.
            // Fix PGRelief
            if ( dwInMaxLength <= 100 )
            {
                // Do nothing
            }
            else
            {
                // [20150515] SonPT: Not set error code for output
                //sOutConvDataStr = to_string(( LONGLONG ) ERROR_CODE_NULL );
                return ERROR_CODE_NOT_NUMBER;
            }
            
            // Cr
            lJudgeNumber = JudgeNumberFunc( sInConvData );
            switch ( lJudgeNumber)
            {
                case JUDGE_FULL_NUMBER :
                    // Full
                    sZero = "�O";
                    break;
                case JUDGE_HALF_NUMBER : 
                    // half
                    sZero = "0";
                    break;
                default : 
                    // [20150515] SonPT: Not set error code for output
                    //sOutConvDataStr = to_string(( LONGLONG ) ERROR_CODE_NULL );
                    return ERROR_CODE_NOT_NUMBER;
            }

            for ( dwRoopCount = GetSize( sInConvData ); dwRoopCount < dwInMaxLength; dwRoopCount++) 
            {
                // Push zero (�u0�vor�u�O�v) to data
                sInConvData = sZero + sInConvData;
            }
            break;

        default : 
            // [20150515] SonPT: Not set error code for output
            //sOutConvDataStr = to_string(( LONGLONG )ERROR_CODE_NULL );
            return ERROR_CODE_NOT_RANGE;
    }

    // Set converted data
    sOutConvDataStr = sInConvData;

    return lRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ConvFullHalNumberFunc
//
//�@�\�@�@��@�F  Convert number from full->half and half->full
//
//�@�T�@�@�v�@�F  Convert number from full->half and half->full
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ConvFullHalNumberFunc( const string &sInConvData, BOOL bInHalfFlg, string &sOutConvData )
{
    // Initilize
    LONG            lRet             = GUI_RET_OK;
    DWORD           dwRoopCount      = 0; // Counter
    string          aryHalfNumber[]  = {"0",  "1" , "2", "3",  "4",  "5",  "6",  "7",  "8",  "9",  "-",   ","}; // half
    string          aryFullNumber[]  = {"�O", "�P", "�Q","�R", "�S", "�T", "�U", "�V", "�W" ,"�X", "�|",  "�C"}; // Full
    //var objRegExp; // ���K�\���I�u�W�F�N�g

    // Check parameter
    if ( sInConvData == "" )
    {
        return GUI_RET_OK;
    } 
    else 
    {

    }
    sOutConvData = sInConvData;
    wstring      wsOutConvData = StringToWChar( sInConvData );
    try
    {
        for ( dwRoopCount = 0; dwRoopCount < ARRAY_LENGTH( aryHalfNumber ); dwRoopCount++ )
        {
            if( bInHalfFlg )
            {
                // Convert to half.
                wsOutConvData = regex_replace( wsOutConvData, wregex( StringToWChar( aryFullNumber[dwRoopCount] )), StringToWChar( aryHalfNumber[dwRoopCount] ));
            }
            else
            {
                // Convert to full
                sOutConvData = regex_replace( sOutConvData, regex( aryHalfNumber[dwRoopCount] ), aryFullNumber[dwRoopCount] );
            }
        }
    }
    catch( ... )
    {
        return ERROR_CODE_NULL;
    }
    if ( bInHalfFlg )
    {
        sOutConvData = WCharToString( wsOutConvData );
    }
    return lRet;
}
/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ExcerptNotFormatFunc
//
//�@�\�@�@��@�F  Extract only input string from format
//
//�@�T�@�@�v�@�F  Extract only input string from format
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG  CGuiViewDlg::ExcerptNotFormatFunc(
                       const    string &sInFormatCharacter,
                       const    string &sInDispCharacter,
                                LONG   lInDeleteIndex,
                                string &sOutString,
                                BOOL bInLeftJustify )
{
  // Initialize
    LONG            lRet                = GUI_RET_OK;
    string          sExcerptCharacter   = ""; // ����������.
    DWORD           dwRoopCount         = GUI_VALUE_ZERO_DWORD; // ���[�v�J�E���g.
    wstring         sTemp               = L"";

    // Check parameter
    if ( sInFormatCharacter == NOT_SET_STR )
    {
        return ERROR_CODE_NULL;
    }
    else
    {
        // Do nothing
    }

    if ( sInDispCharacter == NOT_SET_STR )
    {
        return ERROR_CODE_NULL;
    }
    else
    {
        // Do nothing
    }
    // Incase of format is not existed, return display string
    if ( sInFormatCharacter == "" )
    {
        sExcerptCharacter = sInDispCharacter;
        // ignore deleted sstring
        if ( lInDeleteIndex > -1 )
        {
            sExcerptCharacter = SubStr( sExcerptCharacter, 0, lInDeleteIndex ) + SubStr( sExcerptCharacter, lInDeleteIndex +1 );
        }
        sOutString =  sExcerptCharacter;
        return GUI_RET_OK;
    } 
    else
    {
        // Compare with format, get each character
        for ( dwRoopCount = 0; dwRoopCount < GetSize( sInDispCharacter ); dwRoopCount++) 
        {
            //If character is deleted character, ignore
            if ( ( LONG )dwRoopCount == lInDeleteIndex)
            {
                continue;
            }
            // If it match with input format, get it
            if ( SubStr( sInFormatCharacter, dwRoopCount , 1 ) == FORMAT_INPUT_ITEM ) 
            {
                sExcerptCharacter = sExcerptCharacter + SubStr( sInDispCharacter, dwRoopCount , 1 );
            }
        }
        try
        {
            // Replace string
            //sExcerptCharacter = regex_replace( sExcerptCharacter, regex( CHARACTER_SPACE + string("*$")), string(""));
            if (bInLeftJustify) 
            {
                //sExcerptCharacter = regex_replace( sExcerptCharacter, regex( CHARACTER_SPACE + string("*$")), string(""));
                sTemp = regex_replace( StringToWChar(sExcerptCharacter), wregex( L"�@*$"), wstring(L""));
            } else
            {
                //sExcerptCharacter = regex_replace( sExcerptCharacter, regex(string("^")+ CHARACTER_SPACE + string("*")), string(""));
                sTemp = regex_replace( StringToWChar(sExcerptCharacter), wregex( L"^�@*"), wstring(L""));
            }

        }
        catch( ... )
        {
        }
    }

    //sOutString = sExcerptCharacter;
    sOutString = WCharToString(sTemp);
    return lRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  AddFormatFunc
//
//�@�\�@�@��@�F  Add string to format form
//
//�@�T�@�@�v�@�F  Add string to format form
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::AddFormatFunc( 
                            CItem* lpIntagId,
                   const    string &sInFormatCharacter,
                   const    string &sInAddCharacter,
                            BOOL   bInAddCharacterFlg,
                            BOOL   bInLeftJustifyFlg,
                            LONG   lInMaxLength,
                            string &sOutDisplayContent)
{
    // Initialize
    LONG            lRet         = GUI_RET_OK;
    string        strDispCharacter = ""; // �\��������.
    string        sTagIdText        = ""; // �^�OID�\���e�L�X�g.
    LONG          lRoopCount       = 0; // ���[�v�J�E���g.
    LONG          lValueCount      = 0; // �����ǉ���.

    // �����`�F�b�N.
    // �^�OID�����݂��Ă��邩�`�F�b�N.
    if ( lpIntagId == NULL )
    {
        return ERROR_CODE_NULL;
    }

    if ( sInFormatCharacter == NOT_SET_STR )
    {
        return ERROR_CODE_NULL;
    }


    // �ǉ�������t���O�ɂ��\���e�L�X�g��ύX����.
    if ( bInAddCharacterFlg == TRUE )
    {
        // �\���^�OID��茻��̕�����̔�������
        ExcerptNotFormatFunc( sInFormatCharacter, lpIntagId->innerText(), -1 , sTagIdText, gsctInputFormat.bLeftJustify );
        sTagIdText = sTagIdText + sInAddCharacter;
    }
    else
    {
        // �V�K������̏ꍇ�A�ǉ���������i�[����.
        sTagIdText = sInAddCharacter;
    }

    // �t�H�[�}�b�g�����݂��Ȃ��ꍇ�́A�\���������Ԃ��B
    if ( sInFormatCharacter == "" )
    {
        if ( JUDGE_HALF_NUMBER != JudgeNumberFunc( to_string(( LONGLONG )lInMaxLength ))) 
        {
            return ERROR_CODE_NOT_NUMBER;
        }
        strDispCharacter = SubStr( sTagIdText, 0, lInMaxLength );
    } 
    else
    {
        if ( bInLeftJustifyFlg == TRUE )
        {
            lValueCount = 0; // �����ǉ���.
            for ( lRoopCount = 0; lRoopCount < ( LONG ) GetSize( sInFormatCharacter ); lRoopCount++ )
            {
                // �t�H�[�}�b�g�����͉\�ʒu���A�\���e�L�X�g�����݂���ꍇ�́A�\���e�L�X�g��ǉ�����.
                if ( SubStr(sInFormatCharacter, lRoopCount, 1) == FORMAT_INPUT_ITEM )
                {
                    if ( lValueCount < ( LONG ) GetSize( sTagIdText ))
                    {
                        strDispCharacter = strDispCharacter + SubStr( sTagIdText, lValueCount, 1 );
                        lValueCount      = lValueCount + 1;
                    } 
                    else 
                    {
                        strDispCharacter = strDispCharacter + CHARACTER_SPACE;
                    }
                }
                else 
                {
                    // ���̓K�C�h�̏ꍇ�́A�t�H�[�}�b�g�̒l��ǉ�����.
                    strDispCharacter = strDispCharacter + SubStr( sInFormatCharacter, lRoopCount, 1 );
                }
            }
        } 
        else 
        {
            lValueCount = ( LONG )GetSize( sTagIdText ) - 1; // �����ǉ���.
            for ( lRoopCount = GetSize( sInFormatCharacter )-1; 0 <= lRoopCount; lRoopCount-- )
            {
                // �t�H�[�}�b�g�����͉\�ʒu���A�\���e�L�X�g�����݂���ꍇ�́A�\���e�L�X�g��ǉ�����.
                if ( SubStr(sInFormatCharacter, lRoopCount, 1) == FORMAT_INPUT_ITEM )
                {
                    if ( lValueCount >= 0 ) 
                    {
                        strDispCharacter = SubStr(sTagIdText, lValueCount, 1 ) + strDispCharacter;
                        lValueCount      = lValueCount - 1;
                    } 
                    else
                    {
                        strDispCharacter = CHARACTER_SPACE + strDispCharacter;
                    }
                    // �t�H�[�}�b�g���J���}�ҏW�ŁA���͕�����0�ɂȂ����ꍇ�́A���[�v�𔲂���.
                    if (( gsctInputFormat.bZeroSupp == TRUE ) && 
                        ( lValueCount < 0 ))
                    {
                        for ( ; 0 < lRoopCount; lRoopCount-- ) 
                        {
                            strDispCharacter = CHARACTER_SPACE + strDispCharacter;
                        }
                        break;
                    }
                }
                else
                {
                    // ���̓K�C�h���́A�\���e�L�X�g���ǉ����I������ꍇ�́A�t�H�[�}�b�g�̒l��ǉ�����.
                    strDispCharacter = SubStr(sInFormatCharacter, ( LONG )lRoopCount, 1 ) + strDispCharacter;
                }
            }
        }
    }

    // �������e��Ԃ�.
    sOutDisplayContent = strDispCharacter;
    return lRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeInputCharacterFunc
//
//�@�\�@�@��@�F  From content of input item, change it to suiable content to display
//
//�@�T�@�@�v�@�F  From content of input item, change it to suiable content to display
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ChangeInputCharacterFunc( 
                                CItem* lpInIagID,
                        const   SCT_FORMAT_TABLE  &sctInInputFormat)
{
    LONG            lRet         = GUI_RET_OK;
    string          sDispCharacter = ""; // �\��������.

    // Check parameter
    if ( lpInIagID == NULL )
    {
        return ERROR_CODE_NULL_ID;
    }

    // Edit data from input format
    if ( gsctInputFormat.bZeroSupp == TRUE )
    {
        ExcerptNotFormatFunc ( 
                SubStr( sctInInputFormat.sInputGuide, (( LONG )GetSize( sctInInputFormat.sInputGuide ) - ( LONG )GetSize( lpInIagID->m_sctProperty.sText ))),
                lpInIagID->m_sctProperty.sText , 
                -1 ,
                sDispCharacter,
                gsctInputFormat.bLeftJustify );

        // Check displaying character is blank
        if ( sDispCharacter == "" )
        {
            // ���������񂪑��݂��Ȃ��ꍇ�A�\�����e�ɏ����\����ݒ肷��.
            lpInIagID->m_sctProperty.sText = sctInInputFormat.sInitDisp;
        }
        else
        {
            // �O�O���폜�������e��ݒ肷��.
             ConvZeroPaddingFunc( sDispCharacter, ZERO_PADDING_NOT_AVAILABLE, 0, sDispCharacter );
             if (( sctInInputFormat.sFormatName == FMT_NAME_EDIT_COMMA_YEN_NOMI ) &&
                  ( sDispCharacter              == "�O" ))
            {
                sDispCharacter = sctInInputFormat.sInitDisp;
            } 
             else 
             {
                AddFormatFunc( lpInIagID, sctInInputFormat.sInputGuide, sDispCharacter, false, sctInInputFormat.bLeftJustify, GetSize( sctInInputFormat.sInputGuide ), sDispCharacter );
            }
             lpInIagID->m_sctProperty.sText = sDispCharacter;
        }

        lpInIagID->ItemUpdateState();
    }

    return lRet;
}
/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeSendDataFunc
//
//�@�\�@�@��@�F  Change send data
//
//�@�T�@�@�v�@�F  Change send data
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
string CGuiViewDlg::ChangeSendDataFunc( CItem* lpInputTagId )
{
    //string strProcResult       = RESULT_OK; // ��������.
    string            strDispCharacter    = NULL_STR; // �\��������.
    string            strFormat           = ""; // �o�̓t�H�[�}�b�g.
    string            sExcerptCharacter = NULL_STR; // ����������.
    DWORD             dwRoopCount          = 0; // ���[�v�J�E���g�ϐ�.
    string            sMaxInputCount      = "";
//    DWORD             dwMaxInputCount      = 0; // ���͍��ڍő吔.
    LONG              lMaxInputCount     = 0;
    CItem*            objBatchTag         = NULL;
    CItem*            objUpdateTag        = NULL; // �X�V�^�OID.
    vector<CItem*>    arySerchTagIdInfo; // �^�OID��������.
    vector<string>    aryStrSendData;       // Send data
    SCT_DATE          sctDate;
    SCT_DATE          objResultDate;
    LONG              lFuncResult         = GUI_RET_NG; // Error code of internal function
    string            sYear               = "";
    time_t            current_time;
    struct            tm *timeinfo;
    wstring           wsTemp              = L"";

    // Check parameter
    if ( lpInputTagId == NULL )
    {
        return NULL_STR;
    }

    if ( lpInputTagId->m_sctProperty.sGaikan == GROUP_NAME_IKKATSU_SET )
    {
        // ���͍��ڃ^�OID�̃h�L�������g�̎擾.

        arySerchTagIdInfo = SearchTagIDFunc( lpInputTagId->m_sctProperty.sTagID, E_AREA_NULL );

        if( arySerchTagIdInfo.size() != 1 )
        {
            return to_string(( LONGLONG ) ERROR_CODE_NULL_ID );
        }

        ConvFullHalNumberFunc( lpInputTagId->m_sctProperty.sText, true, sMaxInputCount );
// Start TrungLV Update ( 20150502)
        lMaxInputCount = atol( sMaxInputCount.c_str());
// End TrungLV Update ( 20150502)
        CArea*  lpobjArea = GetCurrentAreaByAreaType ( arySerchTagIdInfo[0]->m_sctProperty.eAreaType );
        if ( lpobjArea == NULL )
        {
            return to_string(( LONGLONG ) ERROR_CODE_NULL );
        }
        else
        {
            // Do nothing
        }
        for ( dwRoopCount = 1; ( LONG ) dwRoopCount <= lMaxInputCount; dwRoopCount++ )
        {
            // Reset data
            objBatchTag = NULL;
            
            objBatchTag = FindItemByTagID( lpInputTagId->m_sctProperty.sTagID + TAG_ID_SPLIT + to_string(( LONGLONG )dwRoopCount),
                lpobjArea->m_vItemList );
            if ( objBatchTag == NULL )
            {
                continue;
            }
            aryStrSendData.push_back( objBatchTag->m_sctProperty.sText );
        }
        // �������A������.
        if ( aryStrSendData.size() > 0 ) // Fix follow TSBJ review
        {
            strDispCharacter = aryStrSendData[0];
            for ( DWORD dwCnt = 1; dwCnt < aryStrSendData.size(); dwCnt++ )
            {
                strDispCharacter = strDispCharacter + IKKATSU_DATA_SPLIT + aryStrSendData[dwCnt];
            }
        }
        return strDispCharacter;
    }

    if ( lpInputTagId->m_sctProperty.bParent == TRUE )
    {
        objUpdateTag = lpInputTagId;
    }
    else
    {
        objUpdateTag = FindItemByTagID( TAG_ID_NAME_SET_CHAR_SPAN, lpInputTagId->m_vobjItems );
    }

    if ( objUpdateTag == NULL )
    {
        return to_string(( LONGLONG ) ERROR_CODE_NULL );
    }

    if (( lpInputTagId->m_sctProperty.lMinLen == INPUT_LENGTH_EMPTY_OR_ALL ) || // Fix follows TSBJ review
        ( lpInputTagId->m_sctProperty.lMinLen == 0 ))
    {
        strFormat = gsctInputFormat.sInputGuide;
        if ( gsctInputFormat.bZeroSupp == TRUE )
        {
            strFormat = SubStr( gsctInputFormat.sInputGuide, GetSize(objUpdateTag->m_sctProperty.sText)*(-1));
        }
        ExcerptNotFormatFunc( strFormat, objUpdateTag->m_sctProperty.sText, -1 ,sExcerptCharacter, gsctInputFormat.bLeftJustify );
        if ( 0 == sExcerptCharacter.size() )
        {
            strDispCharacter = "";
            return strDispCharacter;
        }
    }
    else
    {
        // Do nothing
    }

    if ( gsctInputFormat.bZeroSupp == TRUE ) 
     {
         wstring sTemp = L"";
         sTemp = regex_replace(StringToWChar( objUpdateTag->m_sctProperty.sText ), wregex(L"^�@*"),wstring(L"")); 
         strDispCharacter = WCharToString( sTemp );
    }

    // Get current time
    time(&current_time);
    timeinfo = localtime( &current_time );

    // �t�H�[�}�b�g�ɓ��t�ݒ肪����ꍇ
    if ( gsctInputFormat.sDataFormat != NOT_SET_STR )
    {
        ExcerptNotFormatFunc( gsctInputFormat.sInputGuide, objUpdateTag->m_sctProperty.sText, -1, sExcerptCharacter, gsctInputFormat.bLeftJustify );
        if ( gsctInputFormat.sFormatName == FMT_NAME_DATE_YEAR_TWO_DGITS )
        {
            sExcerptCharacter = Calendar_Year_Table[ARRAY_LENGTH(Calendar_Year_Table) -1].sEraName + sExcerptCharacter;
            ConvAnnoDominiOrJapaneseCalendarFunc( sExcerptCharacter, CONV_YEAR_ANNO_DOMINI, sExcerptCharacter );
        }
        else if ( gsctInputFormat.sFormatName == FMT_NAME_DATE_YEAR_TWO_DGITS_JP )
        {

            sYear = to_string((LONGLONG) (timeinfo->tm_year + 1900 ));
            ConvFullHalNumberFunc( sYear, FALSE, sYear );
            sExcerptCharacter = SubStr(sYear, 0, 2) + sExcerptCharacter;
        }
        else if ( gsctInputFormat.sFormatName == FMT_NAME_DATE_MONTH_DAY )
        {
            string sTemp = "";
            ConvFullHalNumberFunc( to_string((LONGLONG) (timeinfo->tm_year + 1900 )), false, sTemp );
            sExcerptCharacter = sTemp + sExcerptCharacter;
        }
        else if ( gsctInputFormat.sFormatName == FMT_NAME_DATE_YEAR_FOUR_DGITS )
        {
            // Do nothing
        }
        else
        {
            // Do nothing
        }
        /*if ( lpInputTagId->m_sctProperty.bParent == TRUE )
        {
            objUpdateTag = lpInputTagId;
        }
        else
        {
            objUpdateTag = FindItemByTagID( TAG_ID_NAME_SET_CHAR_SPAN, lpInputTagId->m_vobjItems );
            if ( objUpdateTag == NULL )
            {
                return to_string(( LONGLONG ) ERROR_CODE_NULL );
            }
        }*/

        wsTemp = regex_replace( StringToWChar(sExcerptCharacter), wregex(wstring(L"�@")), wstring(L"�O"));
        sExcerptCharacter = WCharToString(wsTemp);
        // ���ݓ��`�F�b�N.
        ConvertStr2DateSct( sExcerptCharacter, sctDate );
        if ( JudgeDateValidityFunc( sctDate, &objResultDate, lFuncResult ) == TRUE )
        {
            // ���t�t�H�[�}�b�g�ύX����.
            strDispCharacter = ConvDateFormatFunc ( objResultDate, gsctInputFormat.sDataFormat );
            if (( to_string(( LONGLONG )ERROR_CODE_NULL ) != strDispCharacter ) &&
                ( strDispCharacter                        != ( to_string(( LONGLONG )ERROR_CODE_CONV_ANNO_JAPANESE ))))
            {
                objUpdateTag->m_sctProperty.sText = strDispCharacter;
                return strDispCharacter;
            } 
            else 
            {
                strDispCharacter = NULL_STR;
            }
        }
    }

    return strDispCharacter;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ConvDateFormatFunc
//
//�@�\�@�@��@�F  Convert date format
//
//�@�T�@�@�v�@�F  Convert date format
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
string CGuiViewDlg::ConvDateFormatFunc( const SCT_DATE &sctInDate, const string &sInDateFormat )
{
    string       strDateFormat   = ""; // �t�H�[�}�b�g.
    wstring      wstrDateFormat  = L""; // �t�H�[�}�b�g.
    string       strDate         = "";
    string       strEraName      = "";
    string       strYear         = "";
    string       aryWeekJpn[]    = {"��", "��", "��", "��", "��", "��", "�y"};
    LONG         lRet            = GUI_RET_OK;
    struct tm    *timeinfo;

    // Check parameter
    if ( sInDateFormat == NOT_SET_STR )
    {
        return to_string(( LONGLONG ) ERROR_CODE_NULL );
    }

#if 0
    if ( sInDateFormat == "" )
    {
        return to_string(( LONGLONG ) ERROR_CODE_NULL );
    }
#endif

    strDateFormat = sInDateFormat;
    // Check format of year  [yyyy],[��������]����[yy],[����]
    if ( regex_search( StringToWChar(sInDateFormat) , wregex( L"\\[(y|��){2,4}\\]") ))
    {
        // Year format is half
        if ( regex_search( StringToWChar(sInDateFormat) , wregex( L"\\[y{2,4}\\]") ))
        {
            ConvFullHalNumberFunc( to_string(( LONGLONG ) sctInDate.wYear ), true, strDate );
        } 
        else // Format is full
        {
            ConvFullHalNumberFunc( to_string(( LONGLONG ) sctInDate.wYear ), false, strDate );
        }

        // Format is 2 number
        if ( regex_search( StringToWChar( sInDateFormat ) , wregex( L"\\[(y|��){2}\\]")))
        {
            strDate = SubStr(strDate, 2 , 2 );
        }
        // Replace string format
        wstrDateFormat = StringToWChar( strDateFormat );
        wstrDateFormat = regex_replace( wstrDateFormat, wregex(L"\\[(y|��){2,4}\\]"), StringToWChar(strDate ));
        strDateFormat  = WCharToString( wstrDateFormat );
    }

    // Japannese year:  [GGGE],[�f�f�f�d]����[GGEE],[�f�f�d�d]����[GGZE],[�f�f�y�d]
    if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(G|�f){1,3}(Z|�y)*(E|�d){1,2}\\]") ))
    {
        // Get format [YYYYMMDD] from datge
        strDate = ConvDateStrFunc( sctInDate, true );
        lRet   = ConvAnnoDominiOrJapaneseCalendarFunc( strDate, CONV_YEAR_JAPANESE_CALENDAR, strDate );
        if ( lRet != ERROR_CODE_CONV_ANNO_JAPANESE )
        {
            strEraName = SubStr(strDate, 0 , 2 );
            strYear = SubStr(strDate, 2 , 2 );
            // Remove zero of year
            ConvZeroPaddingFunc( strYear, ZERO_PADDING_NOT_AVAILABLE, 2, strYear );
            // Convert to full
            if ( regex_search( StringToWChar( sInDateFormat ) , wregex( L"\\[�f{1,3}�y*�d{1,2}\\]" )))
            {
                ConvFullHalNumberFunc( strYear, false, strYear );
            }
            // Fill zero
            if ( regex_search( StringToWChar(sInDateFormat ), wregex( L"\\[(G|�f){1,2}(E|�d){2}\\]" )))
            {
                 ConvZeroPaddingFunc( strYear, ZERO_PADDING_AVAILABLE, 2, strYear );
            }
            // Fill space
            if ( regex_search( StringToWChar(sInDateFormat) , wregex( L"\\[(G|�f){1,2}(ZE|�y�d)\\]" )))
            {
                // Just fill one space
                if ( GetSize( strYear ) == 1)
                {
                    // full 
                    if ( regex_search( StringToWChar( sInDateFormat ) , wregex( L"\\[�f{1,2}�y�d\\]" )))
                    {
                        strYear = "�@" + strYear;
                    } 
                    else // half
                    {
                        strYear = "&nbsp;" + strYear;
                    }
                }
            }

            if ( regex_search( StringToWChar( sInDateFormat ), wregex( L"\\[(G|�f)(Z|�y)*(E|�d){1,2}\\]" )))
            {
                strDate = strYear;
            } else 
            {
                strDate = strEraName + strYear;
            }
            // Replace string
            wstrDateFormat = StringToWChar( strDateFormat );
            wstrDateFormat = regex_replace( wstrDateFormat, wregex(L"\\[(G|�f){1,3}(Z|�y)*(E|�d){1,2}\\]"), StringToWChar( strDate ));
            strDateFormat  = WCharToString( wstrDateFormat );
        }
        else
        {
            return to_string((LONGLONG)ERROR_CODE_CONV_ANNO_JAPANESE);
        }
    }

    // Month format is: [M],[MM] or [�l],[�l�l] or [Z�l],[�y�l]
    if ( regex_search( StringToWChar( sInDateFormat ) , wregex( L"\\[(Z|�y)*(M|�l){1,2}\\]" )))
    {
        // Get month( full and half)
        if ( regex_search( StringToWChar( sInDateFormat ), wregex( L"\\[(Z|�y)*�l{1,2}\\]" )))
        {
            // Full string
             //ConvFullHalNumberFunc( to_string(( LONGLONG )sctInDate.byDay + 1), false, strDate );
             ConvFullHalNumberFunc( to_string(( LONGLONG )sctInDate.byMonth), false, strDate );
        } 
        else // half string
        {
            //ConvFullHalNumberFunc( to_string(( LONGLONG )sctInDate.byDay + 1), true, strDate );
            ConvFullHalNumberFunc( to_string(( LONGLONG )sctInDate.byMonth ), true, strDate );
        }
        if ( regex_search( StringToWChar( sInDateFormat ), wregex( L"\\[(M|�l){2}\\]" )))
        {
             ConvZeroPaddingFunc( strDate, ZERO_PADDING_AVAILABLE, 2, strDate );
        }
        if ( regex_search( StringToWChar( sInDateFormat ), wregex( L"\\[(ZM|�y�l)\\]" )))
        {
            if ( GetSize( strDate ) == 1 ) 
            {
                if ( regex_search( StringToWChar( sInDateFormat ), wregex( L"\\[�y�l\\]" )))
                {
                    strDate = "�@" + strDate;
                }
                else
                {
                    strDate = "&nbsp;" + strDate;
                }
            }
        }
        // Repace string
        wstrDateFormat = StringToWChar( strDateFormat );
        wstrDateFormat = regex_replace( wstrDateFormat, wregex( L"\\[(Z|�y)*(M|�l){1,2}\\]" ), StringToWChar( strDate ));
        strDateFormat  = WCharToString( wstrDateFormat );

    }

    // Month format: [D],[DD]����[�c],[�c�c]����[ZD],[�y�c]
    if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(Z|�y)*(D|�c){1,2}\\]" )))
    {
        if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(Z|�y)*�c{1,2}\\]" )))
        {
            ConvFullHalNumberFunc( to_string(( LONGLONG ) sctInDate.byDay ), false, strDate );
        }
        else
        {
            ConvFullHalNumberFunc( to_string(( LONGLONG ) sctInDate.byDay ), true, strDate );
        }
        if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(D|�c){2}\\]" )))
        {
             ConvZeroPaddingFunc(strDate, ZERO_PADDING_AVAILABLE, 2, strDate );
        }
        if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(ZD|�y�c)\\]" )))
        {
            if ( GetSize( strDate ) == 1) {
                if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[�y�c\\]" )))
                {
                    strDate = "�@" + strDate;
                }
                else
                {
                    strDate = "&nbsp;" + strDate;
                }
            }
        }
        // Replace date string
        wstrDateFormat = StringToWChar( strDateFormat );
        wstrDateFormat = regex_replace( wstrDateFormat, wregex( L"\\[(Z|�y)*(D|�c){1,2}\\]" ), StringToWChar(strDate ));
        strDateFormat  = WCharToString( wstrDateFormat );
    }
    
    // Format is [aaa]
    if ( regex_search( StringToWChar( sInDateFormat ), wregex( L"\\[a{3}\\]" )))
    {
        // Calculate week day
        timeinfo = DateToTimeInfo( sctInDate );
        strDate = aryWeekJpn[ timeinfo->tm_wday ];
        // Replace date string
        strDateFormat = regex_replace( strDateFormat, regex( "\\[a{3}\\]" ), strDate );
    }

     // �� [h],[hh]����[��],[����]����[Zh],[�y��]�̏ꍇ.
    if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(Z|�y)*(h|��){1,2}\\]" )))
    {
        // ���擾(���p�E�S�p��).
        if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(Z|�y)*��{1,2}\\]" )))
        {
            ConvFullHalNumberFunc( to_string((LONGLONG) sctInDate.wHour ), false, strDate );
        } 
        else
        {
            ConvFullHalNumberFunc( to_string((LONGLONG) sctInDate.wHour ), true, strDate );
        }

        // �[������.
        if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(h|��){2}\\]" )))
        {
            ConvZeroPaddingFunc(strDate, ZERO_PADDING_AVAILABLE, 2, strDate);
        }
        // �X�y�[�X����.
        if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(Zh|�y��)\\]" )))
        {
            // �ꌅ�̏ꍇ�ɂ̂݃X�y�[�X����
            if ( GetSize( strDate ) == 1 ) 
            {
                // �S�p���p����
                if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[�y��\\]" )))
                {
                    strDate = "�@" + strDate;
                } 
                else
                {
                    // ���p�X�y�[�X����.
                    strDate = "&nbsp;" + strDate;
                }
            }
        }
        // ������u������.
        wstrDateFormat = regex_replace( StringToWChar(strDateFormat), wregex( L"\\[(Z|�y)*(h|��){1,2}\\]" ), StringToWChar(strDate ));
        strDateFormat = WCharToString(wstrDateFormat);
    }

    // �� [m],[mm]����[��],[����]����[Zm],[�y��]�̏ꍇ.

    if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(Z|�y)*(m|��){1,2}\\]" )))
    {
        // ���擾(���p�E�S�p��).
        if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(Z|�y)*��{1,2}\\]" )))
        {
            ConvFullHalNumberFunc(to_string((LONGLONG) sctInDate.wMinutes), false, strDate );
        } 
        else 
        {
            ConvFullHalNumberFunc(to_string((LONGLONG) sctInDate.wMinutes), true, strDate );
        }
        // �[������.
        if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(m|��){2}\\]" )))
        {
            ConvZeroPaddingFunc(strDate, ZERO_PADDING_AVAILABLE, 2, strDate );
        }
        // �X�y�[�X����.
        if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(Zm|�y��)\\]" )))
        {
            // �ꌅ�̏ꍇ�ɂ̂݃X�y�[�X����
            if ( GetSize( strDate ) == 1 )
            {
                // �S�p���p����
                if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[�y��\\]" )))
                {
                    strDate = "�@" + strDate;
                } else {
                    // ���p�X�y�[�X����.
                    strDate = "&nbsp;" + strDate;
                }
            }
        }
        // ������u������.
        wstrDateFormat = regex_replace( StringToWChar(strDateFormat), wregex( L"\\[(Z|�y)*(m|��){1,2}\\]" ), StringToWChar(strDate ));
        strDateFormat = WCharToString(wstrDateFormat);
    }

    // �b [s],[ss]����[��],[����]����[Zs],[�y��]�̏ꍇ.
    if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(Z|�y)*(s|��){1,2}\\]" )))
    {
        // ���擾(���p�E�S�p��).
        if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(Z|�y)*��{1,2}\\]" )))
        {
            ConvFullHalNumberFunc(to_string((LONGLONG) sctInDate.wSecond), false, strDate );
        }
        else 
        {
            ConvFullHalNumberFunc(to_string((LONGLONG) sctInDate.wSecond), true, strDate );
        }
        // �[������.
        if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(s|��){2}\\]" )))
        {
            ConvZeroPaddingFunc(strDate, ZERO_PADDING_AVAILABLE, 2, strDate );
        }
        // �X�y�[�X����.
        if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[(Zs|�y��)\\]" )))
        {
            // �ꌅ�̏ꍇ�ɂ̂݃X�y�[�X����
            if ( GetSize( strDate ) == 1 )
            {
                // �S�p���p����
                if ( regex_search(StringToWChar( sInDateFormat ), wregex( L"\\[�y��\\]" )))
                {
                    strDate = "�@" + strDate;
                } else {
                    // ���p�X�y�[�X����.
                    strDate = "&nbsp;" + strDate;
                }
            }
        }
        // ������u������.
        wstrDateFormat = regex_replace( StringToWChar(strDateFormat), wregex( L"\\[(Z|�y)*(s|��){1,2}\\]" ), StringToWChar(strDate ));
        strDateFormat = WCharToString(wstrDateFormat);
    }

    return strDateFormat;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  GetFormatInitSTrFunc
//
//�@�\�@�@��@�F  Get init display of format
//
//�@�T�@�@�v�@�F  Get init display of format
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
string CGuiViewDlg::GetFormatInitSTrFunc(
                 const       string &sFormatName, 
                 const       string &sInitFormat, 
                 const       string &sFormatGreap )
{
    // Initialize
    string sFormatInit = "";
    DWORD  dwRoopCount  = 0;

    // Check parameter
    if ( sInitFormat == NOT_SET_STR )
    {
        return sFormatInit;
    }

    sFormatInit = sInitFormat;

    // �t�H�[�}�b�g�����N�������̓T�u�e�[�u���̏ꍇ�́A�e�[�u�����珉����Ԃ��擾����.
    if (( sFormatName  == FMT_NAME_DATE_OF_BIRTH ) || 
        ( sFormatGreap != "" ))
    {
        for( dwRoopCount = 0; dwRoopCount < ARRAY_LENGTH(Format_Table); dwRoopCount++ )
        {
            if ( sFormatName == Format_Table[dwRoopCount].sFormatName)
            {
                sFormatInit = Format_Table[dwRoopCount].sInitDisp;
                break;
            }
        }
    }
    return sFormatInit;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ConvTagIdDateFormatFunc
//
//�@�\�@�@��@�F  Convert tad id date format
//
//�@�T�@�@�v�@�F  Convert tad id date format
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ConvTagIdDateFormatFunc( 
                        const   string &sTagID,
                                string sInDate,
                        const   string &sConvMode,
                        const   string &sInClassList,
                                string& sDispStr,
                                string& sReturnStr )
{
    // Initilize
    LONG    lRet = GUI_RET_OK;  // Error code
    string          strProcResult = ""; // ��������.
    string          strDispStr    = "";                // �\��������.
    string          strReturnStr  = "";              // �Ԃ�l.
    string          strFormat     = "";                 // ���t�t�H�[�}�b�g.
    DWORD           dwRoopCount    = 0;                // ���[�v�J�E���g�ϐ�.
    DWORD           nProcNo       = 0;       // �����ԍ�.
    SCT_DATE        sctDate;
  //  string  objConvStr = {};           // �ϊ��f�[�^�i�Ԃ�l�E�\��������j.
  //  string  objNowDate = new Date();   // ���t�f�[�^.
    SCT_DATE       objResultDate;             // ���ݓ����茋��.
    string         sTemp = "";
    SYSTEMTIME    stSystemTime;
    LONG           lFuncResult = GUI_RET_NG;    // Error code of return function
    BOOL            bFind   = FALSE;

    // Reset data
    ( VOID )memset( &stSystemTime, 0x00, sizeof( stSystemTime ));

    if ( sTagID == "" )
    {
        lRet =  ERROR_CODE_NULL;
    }
    if ( sInDate == "" )
    {
        lRet =  ERROR_CODE_NULL;
    }
    if ( lRet != GUI_RET_OK )
    {
        sDispStr = sInDate;
        sReturnStr = sInDate;
        return lRet;
    }
    // �����ԍ����擾����.
    for (dwRoopCount = 0; dwRoopCount < ARRAY_LENGTH(TagId_Date_ForMat); dwRoopCount++) 
    {
        // �^�OID����v���Ă�����ϊ����[�h�̏����ԍ����擾����.
        if ( sTagID == TagId_Date_ForMat[dwRoopCount].sTagId )
        {
            bFind = TRUE;
            strFormat = TagId_Date_ForMat[dwRoopCount].sDataFormat;
            if ( sConvMode == CONVMODE_DISP )
            {
                nProcNo = TagId_Date_ForMat[dwRoopCount].dwDispProcNo;
                break;
            }
            else if ( sConvMode == CONVMODE_INPUT )
            {
                nProcNo = TagId_Date_ForMat[dwRoopCount].dwInputProcNo;
                break;
            }
            else
            {
                sDispStr = sInDate;
                sReturnStr = sInDate;
                return GUI_RET_OK;
            }
        }
    }

    // In case cannot find
    if (bFind == FALSE)
    {
        sDispStr = sInDate;
        sReturnStr = sInDate;
        return GUI_RET_OK;
    }
    
    // �����ԍ����Ƃɏ�����ύX����
    switch (nProcNo) {
        case 1: // 2�i�\������.
            // ���ݓ��`�F�b�N.
            ConvertStr2DateSct( sInDate, sctDate );
            if (JudgeDateValidityFunc( sctDate , &objResultDate, lFuncResult ) == FALSE )
            {
                lRet =  ERROR_CODE_NOT_DATE;
                break;
            }
            // ���t�t�H�[�}�b�g�ύX����.
            strDispStr = ConvDateFormatFunc( objResultDate, strFormat);
            if (( std::to_string(( LONGLONG )ERROR_CODE_NULL)                  == strDispStr ) ||
                (( std::to_string(( LONGLONG )ERROR_CODE_CONV_ANNO_JAPANESE) == strDispStr )))
            {
                lRet =  ERROR_CODE_NOT_DATE;
                break;
            }
            // �N���X���̒u��
            strDispStr = regex_replace( strDispStr, regex("\\[XXXX\\]"), sInClassList );
            sDispStr   = strDispStr;
            sReturnStr = sInDate;
            break;
        case 2: // �a��E������\��.
            // ���ݓ��`�F�b�N.
            ConvertStr2DateSct( sInDate, sctDate );

            if ( JudgeDateValidityFunc( sctDate, &objResultDate, lFuncResult ) == FALSE )
            {
                lRet =  ERROR_CODE_NOT_DATE;
                break;
            }

             strDispStr = ConvDateFormatFunc( objResultDate, strFormat);
            if (( std::to_string(( LONGLONG )ERROR_CODE_NULL) == strDispStr ) ||
               (( std::to_string(( LONGLONG )ERROR_CODE_CONV_ANNO_JAPANESE) == strDispStr )))
            {
                lRet =  ERROR_CODE_NOT_DATE;
                break;
            }
            sDispStr   = strDispStr;
            sReturnStr = sInDate;
            break;
        case 3: // ����E�a��4���\��.
            // ���ݓ��`�F�b�N.
             ConvertStr2DateSct( sInDate, sctDate );
            if (JudgeDateValidityFunc( sctDate , &objResultDate, lFuncResult ) == FALSE )
            {
                lRet =  ERROR_CODE_NOT_DATE;
                break;
            }

            // ���t�t�H�[�}�b�g�ύX����.
             strDispStr = ConvDateFormatFunc( objResultDate, strFormat);
            if (( std::to_string(( LONGLONG )ERROR_CODE_NULL) == strDispStr )  ||
                (( std::to_string(( LONGLONG )ERROR_CODE_CONV_ANNO_JAPANESE) == strDispStr )))
            {
                lRet =  ERROR_CODE_NOT_DATE;
                break;
            }
            sDispStr   = strDispStr;
            sReturnStr = strDispStr;
            break;
        case 4: // ����2���\��
            // ������8���łȂ��ꍇ�́A���݂̐����4�����L�ڂ���
            if ( GetSize( sInDate ) != 8 )
            {
                GetSystemTime( &stSystemTime );
                // Get current date
                ConvFullHalNumberFunc( std::to_string(( LONGLONG ) &stSystemTime.wYear) , false, sTemp );
                sInDate = SubStr(sTemp,0,2) + sInDate;
            }

             ConvertStr2DateSct( sInDate, sctDate );
            if (JudgeDateValidityFunc( sctDate , &objResultDate, lFuncResult ) == FALSE )
            {
                lRet =  ERROR_CODE_NOT_DATE;
                break;
            }
            // ���t�t�H�[�}�b�g�ύX����.
             strDispStr = ConvDateFormatFunc( objResultDate, strFormat);
            if (( std::to_string(( LONGLONG )ERROR_CODE_NULL) == strDispStr ) ||
               (( std::to_string(( LONGLONG )ERROR_CODE_CONV_ANNO_JAPANESE) == strDispStr )))
            {
                lRet =  ERROR_CODE_NOT_DATE;
                break;
            }

            sDispStr   = strDispStr;
            sReturnStr = strDispStr;

            break;
        case 0: // �����i�ϊ��j����.
        default: // ���̑�.
            sDispStr   = sInDate;
            sReturnStr = sInDate;
            break;
    }

    // �ϊ������f�[�^��Ԃ�.
    return lRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  NullDateFormatSpaceFillFunc
//
//�@�\�@�@��@�F  fill space to null date format
//
//�@�T�@�@�v�@�F  fill space to null date format
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
string CGuiViewDlg::NullDateFormatSpaceFillFunc( const string &sInTagId, const string &sInClassList )
{
    string strConvStr        = "";         // Conver string
    string strFormat         = "";         // Date format
    DWORD  dwRoopCount        = 0;         // Counter

    // Check parameter
    if ( sInTagId == "" )
    {
        return to_string(( LONGLONG )ERROR_CODE_NULL );
    }

    // Get format
    for ( dwRoopCount = 0; dwRoopCount < ARRAY_LENGTH(TagId_Date_ForMat); dwRoopCount++ )
    {
        // if tagid is match-> get process number of convert mode
        if (sInTagId == TagId_Date_ForMat[dwRoopCount].sTagId) 
        {
            strFormat = TagId_Date_ForMat[dwRoopCount].sDataFormat;
            break;
        }
    }

    if ( strFormat == "" )
    {
        return "";
    }
    wstring sTempFormat = StringToWChar(strFormat);
    try
    {
        if ( regex_search( sTempFormat, wregex( L"\\[(y|��){2,4}\\]")))
        {
            if ( regex_search( sTempFormat, wregex(L"\\[��{2,4}\\]")))
            {
                strConvStr = "�@";
            } else {
                strConvStr = "&nbsp;";
            }
            if ( regex_search( sTempFormat, wregex(L"\\[(y|��){4}\\]")))
            {
                strConvStr =  strConvStr + strConvStr + strConvStr + strConvStr;
            } else {
                strConvStr = strConvStr + strConvStr;
            }
            sTempFormat = std::regex_replace( sTempFormat, std::wregex(L"\\[(y|��){2,4}\\]"), StringToWChar(strConvStr));
        }
        // Japnnesse year

        if ( regex_search( sTempFormat, wregex( L"\\[(G|�f){2,3}(Z|�y)*(E|�d){1,2}\\]")))
        {
            if ( regex_search( sTempFormat, wregex( L"\\[�f{2,3}�y*�d{1,2}\\]")))
            {
                strConvStr = "�@";
            } else {
                strConvStr = "&nbsp;";
            }

            if ( !regex_search( sTempFormat, wregex( L"\\[(G|�f){3}(E|�d)\\]" ) ))
            {
                strConvStr = strConvStr + strConvStr;
            }
            strConvStr = "�@�@" + strConvStr;
            sTempFormat = regex_replace( sTempFormat, wregex( L"\\[(G|�f){2,3}(Z|�y)*(E|�d){1,2}\\]" ), StringToWChar(strConvStr ));
        }
        // Fill month or day
        if ( regex_search( sTempFormat, wregex( L"\\[(Z|�y)*(M|�l|D|�c){1,2}\\]" )))
        {
            if ( regex_search( sTempFormat, wregex( L"\\[�y*(�l|�c){1,2}\\]" )))
            {
                strConvStr = "�@";
            } else {
                strConvStr = "&nbsp;";
            }
            if ( !regex_search( sTempFormat, wregex( L"\\[(M|�l|D|�c)\\]" )))
            { 
                strConvStr = strConvStr + strConvStr;
            }
            sTempFormat = regex_replace( sTempFormat, wregex( L"\\[(Z|�y)*(M|�l|D|�c){1,2}\\]" ), StringToWChar( strConvStr ));
        }

        sTempFormat = regex_replace( sTempFormat, wregex( L"\\[a{3}\\]" ), wstring(L"�@" ));
        sTempFormat = regex_replace( sTempFormat, wregex( L"\\[XXXX\\]" ), StringToWChar( sInClassList ));
        strFormat = WCharToString( sTempFormat );
        strConvStr = strFormat;
    }catch( ... )
    {

    }
    return strConvStr;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ConvInputLimitMsgFunc
//
//�@�\�@�@��@�F  Convert input limit message
//
//�@�T�@�@�v�@�F  Convert input limit message
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
string CGuiViewDlg::ConvInputLimitMsgFunc( const string &sInLimit)
{
    string strMsg       = "";
    DWORD dwRoopCount   = GUI_VALUE_ZERO_DWORD;

    for ( dwRoopCount = 0; dwRoopCount < ARRAY_LENGTH(InputLimit_ErrMsg_Table); dwRoopCount++ ) 
    {
        if ( sInLimit == InputLimit_ErrMsg_Table[dwRoopCount].sInputLimit) 
        {
            strMsg = InputLimit_ErrMsg_Table[dwRoopCount].sErrMsg;
           break;
        }
        else
        {
            // Do nothing
        }
    }
    // �ϊ������f�[�^��Ԃ�.
    return strMsg;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ConvDateStrFunc
//
//�@�\�@�@��@�F  Convert date format
//
//�@�T�@�@�v�@�F  Convert date format
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
string CGuiViewDlg::ConvDateStrFunc( const SCT_DATE &sctDate, BOOL bInHalfNumberFlg )
{
    string strDate      = "";
    string strYear      = "";
    string strMonth     = "";
    string strDay       = "";

    // Get[YYYYMMDD] format from data
    // Get uear
     ConvFullHalNumberFunc( std::to_string(( LONGLONG )sctDate.wYear), bInHalfNumberFlg, strYear );
    // Get month
     ConvFullHalNumberFunc( std::to_string(( LONGLONG )sctDate.byMonth ), bInHalfNumberFlg, strMonth );
     ConvZeroPaddingFunc(strMonth, ZERO_PADDING_AVAILABLE, 2, strMonth );
    // Get day
     ConvFullHalNumberFunc( std::to_string(( LONGLONG )sctDate.byDay) , bInHalfNumberFlg, strDay );
     ConvZeroPaddingFunc(strDay, ZERO_PADDING_AVAILABLE, 2, strDay );
    // Combine
    strDate = strYear + strMonth + strDay;

    // Converted date
    return strDate;
}
/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SetInputBirthForamtFunc
//
//�@�\�@�@��@�F  SetInputBirthForamtFunc
//
//�@�T�@�@�v�@�F  SetInputBirthForamtFunc
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::SetInputBirthForamtFunc( const string &sTagID )
{
    LONG    lRet            = ERROR_CODE_NULL;
    DWORD   dwPos           = 0;
    DWORD   dwLoop          = GUI_VALUE_ZERO_DWORD; // ���[�v�J�E���g�ϐ�.
    wstring wsTemp          = L"";

    // �^�OID������́A�a��t���m�F������.
    for ( dwLoop = 0; dwLoop < DATE_OF_BIRTH_FORMAT_TABLE_SIZE; dwLoop++ )
    {
        // �^�OID������t���擾.
        if ( sTagID == Date_Of_Birth_Fomat_Table[dwLoop].sTagId )
        {
            // ���ݑI�����Ă���{�^���łȂ��ꍇ�A�t�H�[�}�b�g��ύX����.
            gsctInputFormat.sTagId = Date_Of_Birth_Fomat_Table[dwLoop].sTagId;
            gsctInputFormat.sGreap = Date_Of_Birth_Fomat_Table[dwLoop].sGreap;
            gsctInputFormat.sInputGuide = Date_Of_Birth_Fomat_Table[dwLoop].sInputGuide;
            dwPos = gsctInputFormat.sInputGuide.find( FORMAT_INPUT_ITEM );

            if ( dwPos != string::npos )
            {
                gsctInputFormat.lRangeStart = dwPos;
            }

            dwPos = gsctInputFormat.sInputGuide.rfind( FORMAT_INPUT_ITEM );
            if ( dwPos != string::npos )
            {
                gsctInputFormat.lRangeEnd = dwPos + 1;
            }
            wsTemp = regex_replace( StringToWChar( gsctInputFormat.sInputGuide ), wregex( StringToWChar( FORMAT_INPUT_ITEM )), wstring( L"�@" ));
            gsctInputFormat.sInitDisp = WCharToString( wsTemp );
            gsctInputFormat.sEraName  = Date_Of_Birth_Fomat_Table[dwLoop].sEraName;

            // ���[�v�𔲂���.
            lRet = GUI_RET_OK;
            break;
        }
    }

    // �������ʂ�Ԃ��B
    return lRet;
}
/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////End of CONV_FORMAT.js////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeHightClassFunc
//
//�@�\�@�@��@�F  Change the height of class
//
//�@�T�@�@�v�@�F  Change the height of class
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
VOID CGuiViewDlg::ChangeHightClassFunc( CItem* lpobjInItem)
{
    // Initialize
    wstring wsText          = L"";

    if ( lpobjInItem == NULL )
    {
        return;
    }
    else
    {
        // Do nothing
    }
    wsText = StringToWChar( lpobjInItem->m_sctProperty.sText );
    // Check \n in text
    if ( regex_search( wsText, wregex( L"\n" )))
    {
        lpobjInItem->m_sctProperty.lLineHeight = -1;
    } 
    else
    {
        lpobjInItem->m_sctProperty.lLineHeight = lpobjInItem->m_sctProperty.dwHeight - 2;
    }
    return;

}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  JudgeNumberFunc
//
//�@�\�@�@��@�F  Change the height of class
//
//�@�T�@�@�v�@�F  Change the height of class
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::JudgeNumberFunc( string sInJudgeData )
{
    // Initialize
    BOOL bIsHalfWidthNumber = FALSE;
    BOOL bIsFullWidthNumber = FALSE;
    WORD fullWidthCharacter = 0;
    UCHAR c1, c2;
    DWORD dwIndex = 0;
    if (( sInJudgeData.size() == 0 ) || ( sInJudgeData == NOT_SET_STR ))
    {
        return ERROR_CODE_NOT_NUMBER;
    } 
    else
    {
        // Do nothing
    }

    // Negative number
    if (( SubStr(sInJudgeData, 0, 1 ) == "-" ) ||
        ( SubStr(sInJudgeData, 0, 1 ) == "�|" ))
    {
        sInJudgeData = SubStr( sInJudgeData, 1 );
    }

    bIsHalfWidthNumber = TRUE;
    for ( dwIndex = 0; dwIndex < sInJudgeData.size(); dwIndex++ )
    {
        c1 = sInJudgeData.at( dwIndex );
        if ( IsHalfWidthDigit(c1) )
        {
            // Do nothing
        } 
        else
        {
            bIsHalfWidthNumber = FALSE;
            break;
        }        
    }

    if ( bIsHalfWidthNumber == TRUE )
    {
        return JUDGE_HALF_NUMBER;
    } 
    else
    {
        // Do nothing
    }

    if ( sInJudgeData.size() % 2 != 0 )
    {
        return JUDGE_NOT_STR_NUMBER;
    } 
    else
    {
        // Do nothing
    }

    bIsFullWidthNumber = TRUE;
    for ( dwIndex = 0; dwIndex < sInJudgeData.size(); dwIndex += 2 )
    {
        c1 = sInJudgeData.at( dwIndex );
        c2 = sInJudgeData.at( dwIndex + 1 );
        fullWidthCharacter = c1 << 8 | c2;
        if ( IsFullWidthDigit( fullWidthCharacter ) )
        {
            // Do nothing
        }
        else
        {
            bIsFullWidthNumber = FALSE;
            break;
        }
    }

    if ( bIsFullWidthNumber == TRUE )
    {
        return JUDGE_FULL_NUMBER;
    } 
    else
    {
        // Do nothing
    }
    

    return ERROR_CODE_NOT_NUMBER;
}



/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeClassIDFunc
//
//�@�\�@�@��@�F  Change classID of item
//
//�@�T�@�@�v�@�F  Change classID of item
//
//�@�߁@��@�l�F  LONG lOutErrCode
//
//�@���@�@���@�F  CItem* lpobjInItem   (I)     Input item
//                String sDesign       (I)     Change design
//                string sBeforegGaikan (I)     Before gaikan
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/09    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG CGuiViewDlg::ChangeClassIDFunc( 
                                CItem* lpobjInItem,
                       const    string &sDesign,
                                string sBeforeGaikan /*= "" */ )
{
    //Declare local variable
    LONG            lOutErrCode         = GUI_RET_NG;                                       // Error code
    vector<CItem*>  vobjSearchItem;                                     // List of item
    DWORD           dwIndex             = GUI_VALUE_ZERO_DWORD;         // Counter
    DWORD           dwSubIndex          = GUI_VALUE_ZERO_DWORD;         // Sub Counter
    DWORD           dwStsCnt            = GUI_VALUE_ZERO_DWORD;
    string          sAfterGaikan        = "";
    //vector<string>  vsStatus;
    string          sChangeClass        = NOT_SET_STR;
    string          sMultiClass         = "";
    string sErrStatus                   = "";
    //DWORD           dwTempDesign        = GUI_VALUE_ZERO_DWORD;
    string          sTempDesign         = "";
    vector<string> vsBeforeClass;
    vector<string> vsClassList;
    string         sInputDesign         = "";
    vector<string>::iterator it;
    string         sClass               = "";

    // Reset data
    vobjSearchItem.clear();
    vsBeforeClass.clear();
    vsClassList.clear();

    // Check valid of input
    if ( lpobjInItem == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    else
    {
        // Do nothing
    }

    //If changes before appearance class does not exist, assign the current appearance class.
    sAfterGaikan = lpobjInItem->m_sctProperty.sGaikan; 
    if ( sBeforeGaikan == NOT_SET_STR )
    {
        sBeforeGaikan = sAfterGaikan;
    }
    else
    {
        // Do nothing
    }

    // To determine whether to change the ordinal number of status by the class you want to change.
    if ( sDesign == DESIGN_VISIBLE )
    {
        //lpobjInItem->m_sctProperty.bVisibilityHidden = FALSE;
        lpobjInItem->UpdateVisibility( TRUE );
        return GUI_RET_OK;
    }
    else if ( sDesign == DESIGN_HIDDEN )
    {
        //lpobjInItem->m_sctProperty.bVisibilityHidden = TRUE;
        lpobjInItem->UpdateVisibility( FALSE );
        return GUI_RET_OK;
    }
    else
    {
        dwStsCnt = STS_INDEX_DESIGN;
        ChangeFontColorFunc( lpobjInItem, CHAR_COLOR_MODE_DELETE,   Character_Color_Table[CHARACTER_COLOR_TABLE_END].wMojiColor);
    }

    sInputDesign = sDesign ;

    // split status into vector
    //vsStatus = SplitString( lpobjInItem->m_sctProperty.sStatus, STS_SPLIT );
    for ( dwIndex = 0; dwIndex < CSS_CLASS_TABLE_SIZE; dwIndex++ )
    {
        // Acquisition of change class.
        if ( CSS_Class_Table[dwIndex].sGaikan == sAfterGaikan )
        {
            // If the class to modify the initial display is acquired from the initial design
            if ( sDesign == DESIGN_INIT )
            {
                sChangeClass = lpobjInItem->m_sctProperty.sInitClass;
            }
            else
            {
                // Check multi class
                sMultiClass = GetClassByDesign( dwIndex, sInputDesign, TRUE );
                //Get a class appearance and values match.
                if ( sMultiClass == DESIGN_MULTI_CLASS )
                {
                    for ( dwSubIndex = 0; dwSubIndex < CSS_CLASS_TABLE_MULTI_SIZE; dwSubIndex++ )
                    {
                        if ( CSS_Class_Table_Multi[dwSubIndex].sGaikan == sAfterGaikan
                            && CSS_Class_Table_Multi[dwSubIndex].sItemValue == lpobjInItem->m_sctProperty.sText )
                        {
                            sChangeClass = GetClassByDesign( dwSubIndex, sInputDesign, FALSE );
                            break;
                        }
                        else
                        {
                            // Do nothing
                        }
                    }
                }
                else
                {
                    sChangeClass = GetClassByDesign( dwIndex, sInputDesign, TRUE);
                }

            }
        }
        // CSS_Class_Table[dwIndex].sGaikan != sAfterGaikan 
        else
        {
            // Do nothing
        }

        //Acquisition of change before class
        if ( CSS_Class_Table[dwIndex].sGaikan == sBeforeGaikan )
        {
            // If the status is error, delete status error
            if ( lpobjInItem->m_sctProperty.sStatus.substr( 0, strlen( DESIGN_INPUT_ERROR )) == DESIGN_INPUT_ERROR )
            {
                sErrStatus = lpobjInItem->m_sctProperty.sStatus.substr( 0, strlen( DESIGN_INPUT_ERROR ));
            }
            else
            {
                sErrStatus = "";
            }

            //MISSING
            sTempDesign = GetDesignStsFunc ( lpobjInItem->m_sctProperty.sStatus );

            if ( sTempDesign == DESIGN_INIT )
            {
                //  If the class to change the initial display is acquired from the initial design
                if ( lpobjInItem->m_sctProperty.sInitClass == "" )
                {
                    // Do nothing
                }
                else
                {
                    vsBeforeClass.push_back( lpobjInItem->m_sctProperty.sInitClass );
                }
            }
            else
            {
                if ( sMultiClass == DESIGN_MULTI_CLASS ) 
                {

                    for ( dwSubIndex = 0; dwSubIndex < CSS_CLASS_TABLE_MULTI_SIZE; dwSubIndex++ )
                    {
                        if ( CSS_Class_Table_Multi[dwSubIndex].sGaikan == sAfterGaikan )
                        {
                            sClass = GetClassByDesign ( dwSubIndex, sTempDesign, FALSE);

                            if ( sClass == "" )
                            {
                                // Do nothing
                            }
                            else
                            {
                                vsBeforeClass.push_back( sClass );
                            }
                        }
                        else
                        {
                            // Do nothing
                        }
                    }
                }
                else
                {
                    sClass = GetClassByDesign( dwIndex, sTempDesign, TRUE );

                    if ( sClass == "" )
                    {
                        // Do nothing
                    }
                    else
                    {
                        vsBeforeClass.push_back( sClass );
                    }
                }
            }

        }

        // CSS_Class_Table[dwIndex].sGaikan != sBeforeGaikan
        else
        {
            // Do nothing
        }

        
        // If the class to the current change is found, and changes the class, and exits the loop.
        if (( vsBeforeClass.size() > 0 )&& 
            ( sChangeClass         != NOT_SET_STR ))
        {
            lOutErrCode =  GUI_RET_OK;
            if (( sDesign      == DESIGN_VISIBLE ) &&
                ( sTempDesign  == sInputDesign ))
            {
                break;
            }
            else
            {
                // Do nothing
            }

            // remove the special designation in the case of design changes
            if ( sChangeClass != CSS_CLASS_NOTHING )
            {
                if ( dwStsCnt == STS_INDEX_DESIGN )
                {
                    lOutErrCode = ChangeItemAssignClassFunc( lpobjInItem, "", ASSIGN_CLASS_MODE_DEL );
                    if ( lOutErrCode != GUI_RET_OK )
                    {
                        return lOutErrCode;
                    }
                    else
                    {
                        // Do nothign
                    }
                }
                else
                {
                    // Do nothing
                }

                // Remove class (the case of multiple correspondence, regardless of the value, deleting the design).
                // split class into vector
                vsClassList = SplitString( lpobjInItem->m_sctProperty.sClass, CLASS_LIST_STR );
                for ( dwSubIndex = 0; dwSubIndex < vsBeforeClass.size(); dwSubIndex++ )
                {
                    it = std::find( vsClassList.begin(), vsClassList.end(), vsBeforeClass[dwSubIndex] );
                    if (( it != vsClassList.end()) && 
                        ( vsClassList.size() > 0 ))
                    {
                        vsClassList.erase( it );
                    }
                    else
                    {
                        // Do nothing
                    }
                    
                }
                
                // TO DO : 1481 Remove item of class (parent)
                vsClassList.push_back( sChangeClass );
                lpobjInItem->m_sctProperty.sClass = JoinString( vsClassList, CLASS_LIST_STR );
                lpobjInItem->m_sctProperty.sStatus = sErrStatus + sDesign ;
            }
            else
            {
                // Do nothing
            }
            break;

        }
        else
        {
            // Do nothing
        }

    }// end for
    if ( lOutErrCode != GUI_RET_OK )
    {
        lOutErrCode =  ERROR_CODE_NOT_EXIST_CLASS;
    }
    else
    {
        // Do nothing
    }
    return lOutErrCode;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  GetClassByDesign
//
//�@�\�@�@��@�F  Get class value by design string
//
//�@�T�@�@�v�@�F  Get class value by design string
//
//�@�߁@��@�l�F  string   value of class
//
//�@���@�@���@�F  DWORD      dwTblIndex   (I)     Index in CSS table
//                string      sDesign     (I)     Change design
//                BOOL       bIsMulti     (I)     whether find in multiple CSS table
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/09    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////

string CGuiViewDlg::GetClassByDesign (DWORD dwTblIndex, const string &sDesign, BOOL bIsMulti )
{
    string sTempClass = "";
    if ( bIsMulti == TRUE)
    {
        if ( sDesign == DESIGN_BLINK )
        {
            sTempClass = CSS_Class_Table[dwTblIndex].sBlinking;
        }
        else if ( sDesign == DESIGN_DISABLE )
        {
            sTempClass = CSS_Class_Table[dwTblIndex].sDisabled;
        }
        else if ( sDesign == DESIGN_ERROR )
        {
            sTempClass = CSS_Class_Table[dwTblIndex].sErr;
        }
        else if ( sDesign == DESIGN_HIDDEN )
        {
            sTempClass = CSS_Class_Table[dwTblIndex].sHidden;
        }
        else if ( sDesign == DESIGN_BTN_OFF )
        {
            sTempClass = CSS_Class_Table[dwTblIndex].sOff;
        }
        else if ( sDesign == (string)DESIGN_BTN_OFF + "2" )
        {
            sTempClass = CSS_Class_Table[dwTblIndex].sOff2;
        }

        // [SonPT] Upgrade source code to v20.21
        else if ( sDesign == (string)DESIGN_BTN_OFF + "3" )
        {
            sTempClass = CSS_Class_Table[dwTblIndex].sOff3;
        }
        else if ( sDesign == (string)DESIGN_BTN_OFF + "4" )
        {
            sTempClass = CSS_Class_Table[dwTblIndex].sOff4;
        }
        else if ( sDesign == (string)DESIGN_BTN_OFF + "5" )
        {
            sTempClass = CSS_Class_Table[dwTblIndex].sOff5;
        }
        else if ( sDesign == (string)DESIGN_BTN_OFF + "6" )
        {
            sTempClass = CSS_Class_Table[dwTblIndex].sOff6;
        }
        else if ( sDesign == (string)DESIGN_BTN_OFF + "7" )
        {
            sTempClass = CSS_Class_Table[dwTblIndex].sOff7;
        }
        else if ( sDesign == (string)DESIGN_BTN_OFF + "8" )
        {
            sTempClass = CSS_Class_Table[dwTblIndex].sOff8;
        }
        else if ( sDesign == (string)DESIGN_BTN_OFF + "9" )
        {
            sTempClass = CSS_Class_Table[dwTblIndex].sOff9;
        }
        else if ( sDesign == (string)DESIGN_BTN_OFF + "10" )
        {
            sTempClass = CSS_Class_Table[dwTblIndex].sOff10;
        }
        // End editing
        else if ( sDesign == DESIGN_BTN_ON )
        {
            sTempClass = CSS_Class_Table[dwTblIndex].sOn;
        }
        else if ( sDesign == DESIGN_VISIBLE )
        {
            sTempClass = CSS_Class_Table[dwTblIndex].sVisible;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        if ( sDesign == DESIGN_BLINK )
        {
            sTempClass = CSS_Class_Table_Multi[dwTblIndex].sBlinking;
        }
        else if ( sDesign == DESIGN_DISABLE )
        {
            sTempClass = CSS_Class_Table_Multi[dwTblIndex].sDisabled;
        }
        else if ( sDesign == DESIGN_ERROR )
        {
            sTempClass = CSS_Class_Table_Multi[dwTblIndex].sErr;
        }
        else if ( sDesign == DESIGN_HIDDEN )
        {
            sTempClass = CSS_Class_Table_Multi[dwTblIndex].sHidden;
        }
        else if ( sDesign == DESIGN_BTN_OFF )
        {
            sTempClass = CSS_Class_Table_Multi[dwTblIndex].sOff;
        }
        else if ( sDesign == DESIGN_BTN_ON )
        {
            sTempClass = CSS_Class_Table_Multi[dwTblIndex].sOn;
        }
        else if ( sDesign == DESIGN_VISIBLE )
        {
            sTempClass = CSS_Class_Table_Multi[dwTblIndex].sVisible;
        }
        else
        {
            // Do nothing
        }
    }
    return sTempClass;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  GetDesignStringByDesignNumber
//
//�@�\�@�@��@�F  Get design string by design number
//
//�@�T�@�@�v�@�F  Get design string by design number
//
//�@�߁@��@�l�F  string   value of class
//
//�@���@�@���@�F  
//                DWORD      dwDesign     (I)     Change design
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/09    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
//string CGuiViewDlg::GetDesignStringByDesignNumber ( DWORD dwDesign )
//{
//    string sTempClass  = "";
//    switch ( dwDesign )
//    {
//    case DESIGN_BLINK:
//    case DESIGN_BTN_BLINK:
//    case DESIGN_TEXT_BLINK:
//    case DESIGN_ERROR_BLINK:
//        sTempClass = DESIGN_BLINK_STRING;
//        break;
//    case DESIGN_DISABLE:
//    case DESIGN_BTN_DISABLE:
//    case DESIGN_TEXT_DISABLE:
//        sTempClass = DESIGN_DISABLE_STRING;
//        break;
//    case DESIGN_ERROR:
//        sTempClass = DESIGN_ERROR_STRING;
//        break;
//    case DESIGN_HIDDEN:
//        sTempClass = DESIGN_HIDDEN_STRING;
//        break;
//    case DESIGN_NOT_SELECT:
//    case DESIGN_BTN_OFF:
//    case DESIGN_TEXT_NOT_SELECT:
//        sTempClass = DESIGN_BTN_OFF_STRING;
//        break;
//    case DESIGN_SELECT:
//    case DESIGN_BTN_ON:
//    case DESIGN_TEXT_SELECT:
//        sTempClass = DESIGN_BTN_ON_STRING;
//        break;
//    case DESIGN_VISIBLE:
//        sTempClass = DESIGN_VISIBLE_STRING;
//        break;
//    default:
//        break;
//    }
//    
//    return sTempClass;
//}
//

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeFlashingTagFunc
//
//�@�\�@�@��@�F  Get class value by design number
//
//�@�T�@�@�v�@�F  Get class value by design number
//
//�@�߁@��@�l�F  LONG lOutErrCode   
//
//�@���@�@���@�F CItem* lpobjInItem          Flashing item
//               DWORD dwLightOnOffCnt       Number of flashing times (0: No flashing; 1-9: Flashing 1-9 times; 10: Infinitive)
//               string sUpdateElement       Parent/childrent
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/09    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////


LONG CGuiViewDlg::ChangeFlashingTagFunc( 
                                        CItem* lpobjInItem, 
                                        DWORD  dwLightOnOffCnt, 
                                  const string &sUpdateElement )
{
    //Declare local variable
    LONG                lOutErrCode         = GUI_RET_OK;                                       // Error code
    DWORD               dwIndex             = GUI_VALUE_ZERO_DWORD;         // Counter
    string              sGaikan             = "";                         // Gaikan of item
    string              sLightOnClass       = "";                         // Light on class
    vector<string>      vsStatus;                                           // Status of item
    CItem*              lpobjBlinkTag       = NULL;                       // Temp object
    vector<string>      vsBlinkClassList;
    string              sTemp               = "";
    vector<string>::iterator   it;
    vector<SCT_SPAN>    vEmptySpan;
    // Reset data
    vsStatus.clear();
    vsBlinkClassList.clear();

    // Check validation of input
    // Check item NULL
    if (  lpobjInItem == NULL)
    {
        return ERROR_CODE_NOT_EXIST_ID; // Fix follow TSBJ review
    }
    else
    {
        // Do nothing
    }

    // Check valid of flashing number
    if ( dwLightOnOffCnt < FLG_OBJECT_BLINK_STOP ||  dwLightOnOffCnt > FLG_OBJECT_BLINK_START )
    {
        return ERROR_CODE_NOT_RANGE;    // Fix follow TSBJ review
    }
    else
    {
        // Do nothing
    }

    // Check valid of element
    if ( STS_NAME_UPDATE_ELEMENT_PARENT != sUpdateElement &&  STS_NAME_UPDATE_ELEMENT_CHILD != sUpdateElement )
    {
        return ERROR_CODE_NOT_RANGE; // Fix follow TSBJ review
    }
    else
    {
        // Do nothing
    }
    //check whether the appearance matches with CSS table
    sGaikan = lpobjInItem->m_sctProperty.sGaikan;
    for ( dwIndex = 0; dwIndex < CSS_CLASS_TABLE_SIZE; dwIndex++ )
    {
        if ( CSS_Class_Table[dwIndex].sGaikan == sGaikan )
        {
            //Get the class of flashing than status
            sLightOnClass = CSS_Class_Table[dwIndex].sBlinking;
            break;
        }
        else
        {
            // Do nothing
        }
    }
    //If the current was not found class or change classes, set the error.
    if ( dwIndex == CSS_CLASS_TABLE_SIZE )
    {
        return ERROR_CODE_NOT_EXIST_CLASS;  // Fix follow TSBJ review
    }
    else
    {
        // Do nothing
    }

    //lpobjInItem->m_sctProperty.wBlink

    //vsStatus = SplitString( lpobjInItem->m_sctProperty.sStatus, STS_SPLIT );

    //// If the status is blinking class, delete
    //if ( vsStatus.size() == STS_INDEX_BLINK + 1 )
    //{
    //    std::remove( vsStatus.begin(), vsStatus.end(), vsStatus[STS_INDEX_BLINK] );
    //}
    //else
    //{
    //    // Do nothing
    //}

    //Get updated tag ID
    // If the update elements of the parent.
    if ( sUpdateElement == STS_NAME_UPDATE_ELEMENT_PARENT )
    {
        lpobjBlinkTag = lpobjInItem;
        // Fix PgRelief
        if ( lpobjBlinkTag == NULL )
        {
            return ERROR_CODE_NOT_EXIST_ID;
        }
        lpobjBlinkTag->m_sctProperty.wBlink = (WORD)dwLightOnOffCnt;
        lpobjBlinkTag->BlinkItem();
    }
    else
    {
        //If the status is a child, and set the span tag of the child element.
        lpobjBlinkTag = FindItemByTagID( TAG_ID_NAME_SET_CHAR_SPAN, lpobjInItem->m_vobjItems );
        
        // If the span tag of the child element does not exist, add a span tag to tag ID.
        if ( lpobjBlinkTag == NULL )
        {
            lpobjBlinkTag = new CRichLabel();
            /*lpobjBlinkTag->m_sctProperty.sTagID = TAG_ID_NAME_SET_CHAR_SPAN;
            lpobjBlinkTag->m_sctProperty.sText  = lpobjInItem->m_sctProperty.sText;*/
            // Fix PGRelief
            if ( lpobjBlinkTag == NULL )
            {
                return ERROR_CODE_NOT_EXIST_ID;
            }
            lpobjBlinkTag->SetProperties(lpobjInItem->m_sctProperty.dwType, 
                                            // Start ThietNP 2015-07-28 Change control ID
                                            // 0xFFFFFFFF, 
                                            IDCTRL_ITEM,
                                            // End ThietNP 2015-07-28 Change control ID
                                            "span", //lpobjInItem->m_sctProperty.sTagName, 
                                            lpobjInItem->m_sctProperty.sText.c_str(), 
                                            lpobjInItem->m_sctProperty.dwLeft, 
                                            lpobjInItem->m_sctProperty.dwTop, 
                                            lpobjInItem->m_sctProperty.dwWidth, 
                                            lpobjInItem->m_sctProperty.dwHeight, 
                                            lpobjInItem->m_sctProperty.bVisible, 
                                            lpobjInItem->m_sctProperty.bVisibilityHidden, 
                                            lpobjInItem->m_sctProperty.bEnable, 
                                            lpobjInItem->m_sctProperty.sGaikan.c_str(),
                                            lpobjInItem->m_sctProperty.sFmt.c_str(), 
                                            TAG_ID_NAME_SET_CHAR_SPAN, //lpobjInItem->m_sctProperty.sTagID, 
                                            lpobjInItem->m_sctProperty.sTagGroup.c_str(),
                                            lpobjInItem->m_sctProperty.sAltTagID.c_str(),
                                            lpobjInItem->m_sctProperty.sInitClass.c_str(),
                                            lpobjInItem->m_sctProperty.sInitText.c_str(),
                                            lpobjInItem->m_sctProperty.sNullStrInitApp.c_str(),
                                            "", //lpobjInItem->m_sctProperty.sStatus,
                                            lpobjInItem->m_sctProperty.bTextClickEvent ,
                                            lpobjInItem->m_sctProperty.dwClickBranchMode ,
                                            lpobjInItem->m_sctProperty.sEvenFunctionName.c_str(),
                                            lpobjInItem->m_sctProperty.sParaContainerTagID.c_str(),
                                            lpobjInItem->m_sctProperty.sParaStartNo.c_str(),
                                            lpobjInItem->m_sctProperty.sParaEndNo.c_str(),
                                            lpobjInItem->m_sctProperty.sLimit.c_str(),
                                            lpobjInItem->m_sctProperty.sClass.c_str(),
                                            lpobjInItem->m_sctProperty.sValue.c_str(),
                                            lpobjInItem->m_sctProperty.dwFontSize ,
                                            lpobjInItem->m_sctProperty.fZoomSize ,
                                            lpobjInItem->m_sctProperty.lMinLen ,
                                            lpobjInItem->m_sctProperty.lMaxLen ,
                                            "", //lpobjInItem->m_sctProperty.sPageAtr ,
                                            "", //lpobjInItem->m_sctProperty.sBtn_Span_ImgClass ,
                                            lpobjInItem->m_sctProperty.bImageFirst ,
                                            vEmptySpan,
                                            "", //lpobjInItem->m_sctProperty.sBtn_Hr_Line_Class ,
                                            "", //lpobjInItem->m_sctProperty.sImgSrc ,
                                            lpobjInItem->m_sctProperty.eAreaType ,
                                            FALSE, //lpobjInItem->m_sctProperty.bParent
                                            lpobjInItem->m_sctProperty.lLineHeight,
                                            lpobjInItem->m_sctProperty.dwHrPos,
                                            lpobjInItem->m_sctProperty.bOriginal);
            lpobjBlinkTag->CreateItem( dynamic_cast<CWnd*>(lpobjInItem)->GetParent());
            lpobjBlinkTag->m_lpParent = lpobjInItem;
            lpobjInItem->m_sctProperty.sText = "";
            lpobjInItem->m_vobjItems.push_back( lpobjBlinkTag );
        }
        else
        {
            // Do nothing
        }
        // Blink text
        lpobjBlinkTag->m_sctProperty.wBlink = (WORD)dwLightOnOffCnt;
        lpobjBlinkTag->BlinkText();

        lpobjInItem->m_sctProperty.bParent = FALSE;
    }

    // In the case of unblink, to remove than className flashing class.
    vsBlinkClassList = SplitString( lpobjBlinkTag->m_sctProperty.sClass, CLASS_LIST_STR );

    if ( dwLightOnOffCnt == FLG_OBJECT_BLINK_STOP )
    {
        it = std::find( vsBlinkClassList.begin(), vsBlinkClassList.end(), sLightOnClass );
        if (  it != vsBlinkClassList.end() )
        {
            vsBlinkClassList.erase( it );
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        if ( sLightOnClass != "" )
        {
            vsBlinkClassList.push_back( sLightOnClass );
        }
        else
        {
            // Do nothing
        }
        
    }

   
    //If the class is not set if the span tag exists in the child element of the tag ID,  remove the span tag.
    if ( ( vsBlinkClassList.size() == 1 ) && ( sUpdateElement != STS_NAME_UPDATE_ELEMENT_PARENT ) )
    {
        sTemp = lpobjBlinkTag->m_sctProperty.sText;
        lpobjInItem->m_sctProperty.sText = sTemp;
        lpobjInItem->m_sctProperty.bParent = TRUE;
        //remove blink item
        if ( lpobjBlinkTag != NULL )
        {
            //std::remove(lpobjInItem->m_vobjItems.begin(), lpobjInItem->m_vobjItems.end(), lpobjUpdateItem );
            auto it2 = std::find( lpobjInItem->m_vobjItems.begin(), lpobjInItem->m_vobjItems.end(), lpobjBlinkTag );
            if (  it2 != lpobjInItem->m_vobjItems.end() )
            {
                lpobjInItem->m_vobjItems.erase( it2 );
            }
            else
            {
                // Do nothing
            }
            delete lpobjBlinkTag;
            lpobjBlinkTag = NULL;
        }
    }
    else
    {
        // Do nothing
    }
    
    return lOutErrCode;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ReCalculateCursorPosition
//
//�@�\�@�@��@�F  ReCalculate Cursor Position
//
//�@�T�@�@�v�@�F ReCalculate Cursor Position
//
//�@�߁@��@�l�F VOID
//
//�@���@�@���@�F   CItem*     lpobjItem       input items
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/09    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ReCalculateCursorPosition( CItem* lpobjInputItem, LONG lInX, LONG lInY )
{
    LONG lRet = GUI_RET_OK;
    POINT        pAreaPos;
    CArea*       lpArea    = NULL;
    DWORD dwCnt        = 0;
    if ( lpobjInputItem == NULL )
    {
        return ERR_CODE_PARA;
    }
    //Setting the display position of the cursor. Left-justified, changes display position by right-justified.
    pAreaPos = GetAreaPos( lpobjInputItem->m_sctProperty.eAreaType );
    for ( dwCnt = 0; dwCnt < m_vCurAreas.size(); dwCnt++ )
    {
        if ( m_vCurAreas[dwCnt]->m_sctAreaInfo.eAreaType == lpobjInputItem->m_sctProperty.eAreaType )
        {
            lpArea = m_vCurAreas[dwCnt];
            break;
        }
    }
    if ( lpArea == NULL )
    {
        return ERR_CODE_NO_AREA;
    }
    m_cCursor.m_dwX = lpArea->m_sctAreaInfo.dwMarginLeft + lInX ;
    m_cCursor.m_dwY = lpArea->m_sctAreaInfo.dwMarginTop + lInY;

    return lRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SetCursorRelativePosition
//
//�@�\�@�@��@�F  SetCursor Position Relative
//
//�@�T�@�@�v�@�F  SetCursor Position Relative using input format
//
//�@�߁@��@�l�F VOID
//
//�@���@�@���@�F   CItem*     lpobjItem       input items
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/09    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
VOID CGuiViewDlg::SetCursorRelativePosition( BOOL bLeftJustify )
{
    // Left-justified Otherwise, the display position change by right-justified.
    if ( bLeftJustify == TRUE )
    {
        glRelativeCurPos = gsctInputFormat.lRangeStart;
    }
    else
    {
        glRelativeCurPos = gsctInputFormat.lRangeEnd;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  CursorAddFunc
//
//�@�\�@�@��@�F  Display cursor
//
//�@�T�@�@�v�@�F  Show cursor in View
//
//�@�߁@��@�l�F  LONG lOutErrCode   
//
//�@���@�@���@�F   dwInInitShiji       Item initialization existence
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/09    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////


LONG CGuiViewDlg::CursorAddFunc( DWORD dwInInitShiji )
{
    //Declare local variable
    LONG            lOutErrCode        = GUI_RET_OK;                   // Error code
    LONG            lIndex             = GUI_VALUE_ZERO_LONG;         // Counter
    LONG            lMaxLen            = GUI_VALUE_ZERO_LONG;         // Max length of input item
    LONG            lInputRangeMax     = GUI_VALUE_ZERO_LONG;
    LONG            lFormatIndex       = GUI_VALUE_ZERO_LONG;
    wstring         wInputGuide        = L"";
    wstring         wFormatInputItem   = L"";
    // Check valid of input
    // Check NULL val of input item 
    if ( gclInputItemTag == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    else
    {
        // Do nothing
    }
    // Check global cursor image item


    // Changing the height of the cursor by the height of the input items.
    m_cCursor.m_dwHeight = gclInputItemTag->m_sctProperty.dwFontSize + CURSOR_IMAGE_MARGIN_CHARACTER * 4;
    
    // Check the number of input character
    if ( gclInputItemTag->m_sctProperty.lMaxLen == INPUT_LENGTH_NASHI_MODE )
    {
        lMaxLen = INPUT_MAX_LENGTH_LIMIT;
    }
    else
    {
        lMaxLen = gclInputItemTag->m_sctProperty.lMaxLen;
    }

    // Setting the maximum range of the cursor. If the maximum is -1, set the input maximum number of characters.
    if ( gsctInputFormat.lRangeEnd == -1 )
    {
        // Maximum and when the input guide is present case of -1, combining the input guide to the input maximum number of characters.
        if ( gsctInputFormat.sInputGuide != "" )
        {
            for ( lIndex = GetSize( gsctInputFormat.sInputGuide ) -1; lIndex >=0; lIndex-- )
            {
                // To calculate how the number of input characters become what character when it is placed in the input guide.
                // If the input guide not a, to increase the number of input characters.
                if ( SubStr( gsctInputFormat.sInputGuide, lIndex, 1 ) == FORMAT_INPUT_ITEM )
                {
                    lInputRangeMax = lInputRangeMax + 1;
                }
                else
                {
                    // Do nothing
                }
                lFormatIndex = lFormatIndex - 1;
                //If it exceeds the number of input characters, and exits the loop.
                if ( lInputRangeMax == lMaxLen )
                {
                    break;
                }
                else
                {
                    // Do nothing
                }
            }// end for
            
            // Formatting
            gsctInputFormat.sInputGuide = SubStr( gsctInputFormat.sInputGuide, lFormatIndex );
            wInputGuide = StringToWChar( gsctInputFormat.sInputGuide );
            wFormatInputItem    = StringToWChar( FORMAT_INPUT_ITEM );
            gsctInputFormat.lRangeEnd   = wInputGuide.rfind( wFormatInputItem ) + 1;
            // Added by DienNQ
            if (gsctInputFormat.bZeroSupp)
            {
                gsctInputFormat.sInitDisp = SubStr( gsctInputFormat.sInitDisp, lFormatIndex );
                if ( dwInInitShiji == INPUT_INIT_SHIJI_CLEAR )
                {
                    gclInputItemTag->innerText() = gsctInputFormat.sInitDisp;
                }
            }
        }
        // gsctInputFormat.sInputGuide != "" 
        else
        {
            gsctInputFormat.lRangeEnd = lMaxLen;
        }
    }
    else
    {
        // Do nothing
    }

    //Set the display position of the cursor
    if ( dwInInitShiji == INPUT_INIT_SHIJI_NOT_CHANGE )
    {
        //If the item initialization presence or absence of directly setting the cursor position than the display contents
        glRelativeCurPos = SerchInputGuidFunc ( gclInputItemTag->m_sctProperty.sText, gsctInputFormat.sInputGuide, gsctInputFormat.bLeftJustify, gsctInputFormat.lRangeEnd );
    }
    else
    {
        SetCursorRelativePosition( gsctInputFormat.bLeftJustify );
    }
    // Movement of the cursor (move the number of 0, for which you want to move to the display position that has been set)
    lOutErrCode = CursorMoveFunc( 0 );

    // Redraw object item
    //ShowCursor( m_cCursor.m_dwX, m_cCursor.m_dwY, m_cCursor.m_dwHeight );

    return lOutErrCode;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  CursorDeleteFunc
//
//�@�\�@�@��@�F  Delete cursor
//
//�@�T�@�@�v�@�F  Hide cursor
//
//�@�߁@��@�l�F  LONG    lOutErrCode
//
//�@���@�@���@�F   void
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/09    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////


LONG CGuiViewDlg::CursorDeleteFunc(  )
{
    LONG lOutErrCode = GUI_RET_OK;
    if ( gclInputItemTag == NULL )
    {
        lOutErrCode = ERROR_CODE_NOT_EXIST_ID; 
    }
    else
    {
        HideCursor();
    }
    return lOutErrCode;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  CursorAllDeleteCharacterFunc
//
//�@�\�@�@��@�F  Cursor all detete character
//
//�@�T�@�@�v�@�F  Cursor all detete character
//
//�@�߁@��@�l�F  LONG    lOutErrCode
//
//�@���@�@���@�F   CItem* lpobjInputItem           // Input item
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/09    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////


LONG CGuiViewDlg::CursorAllDeleteCharacterFunc( CItem* lpobjInputItem, BOOL bInSetFormatFlg )
{
    LONG lOutErrCode = GUI_RET_OK;
    if ( lpobjInputItem == NULL )
    {
        return ERROR_CODE_NULL;
    }
    else
    {
       // Do nothing
    }

    // Update new javascript
    if ( string( USER_NAME ) == "sb" )
    {
        if ( bInSetFormatFlg && (FMT_NAME_DATE_OF_BIRTH == gsctInputFormat.sFormatName))
        {
            SetInputBirthForamtFunc( TAG_ID_SEIREKI );
        }
    }

    // Initialze display
    lpobjInputItem->m_sctProperty.sText = gsctInputFormat.sInitDisp;
    // Redraw input item
    lpobjInputItem->ItemUpdateState();
    
    SetCursorRelativePosition( gsctInputFormat.bLeftJustify );

    CursorMoveFunc(0);

    return lOutErrCode;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  CursorInputBranchFunc
//
//�@�\�@�@��@�F  Cursor input branch
//
//�@�T�@�@�v�@�F Do a branch using the cursor control and format of the input.
//
//�@�߁@��@�l�F  LONG lOutErrCode   
//
//�@���@�@���@�F   CItem*     lpobjItem       input item
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/09    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG CGuiViewDlg::CursorInputBranchFunc( CItem* lpobjInItem )
{
    // Declare local variable
    LONG                lOutErrCode         = GUI_RET_OK;
    CItem*              lpobjUpdateItem     = NULL;
    CItem*              lpobjInputItem      = NULL;
    vector<CItem*>      vSpanItem;


    // Check valid of agrument

    if ( lpobjInItem == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    else
    {
        // Do nothing
    }

    // Check existence of input item 
    if ( gclInputItemTag == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    else
    {
        // Do nothing
    }

    // Check global cursor image item
    if ( IsWindow( m_cCursor.m_hWnd ) == TRUE)
    {
        // Do nothing
    }
    else
    {
        return ERROR_CODE_NOT_EXIST_IMAGE;       
    }
    
    // 
    // item is parent
    if ( gclInputItemTag->m_sctProperty.bParent == TRUE )
    {
        lpobjUpdateItem = gclInputItemTag;
    }
    // item is childen
    else
    {
        lpobjUpdateItem = FindItemByTagID ( TAG_ID_NAME_SET_CHAR_SPAN, gclInputItemTag->m_vobjItems );
        if ( lpobjUpdateItem == NULL )
        {
            return ERROR_CODE_NULL;
        }
        else
        {
            // Do nothing
        }
    }

    // If date of birth input of (two lines year), Usually may be a current input item tag
    if ( gclInputItemTag->m_sctProperty.sTagID != TAG_ID_NAME_SEINEN_GAPPI )
    {
        lpobjInputItem = lpobjUpdateItem;
    }
    else
    {
        //Acquisition of date elements.
        vSpanItem = FindItemsByTagName( TAG_NAME_SPAN, lpobjUpdateItem->m_vobjItems );
        if ( vSpanItem.size() > 0 )
        {
            lpobjInputItem = vSpanItem[0];
        }
        else
        {
            return ERROR_CODE_NOT_EXIST_ID;
        }
    }
    // 1 If the character first input initialization flag is true, to initialize the display contents.
    if ( gbInputItemFirstInitializationFlg )
    {
        // Init text
        lpobjInputItem->m_sctProperty.sText = gsctInputFormat.sInitDisp;
        
        SetCursorRelativePosition( gsctInputFormat.bLeftJustify );

        // Set Init flag to FALSE
        gbInputItemFirstInitializationFlg = FALSE;
    }
    else
    {
        // Do nothing
    }

    //Change the process by tag ID.
    if ( lpobjInItem->m_sctProperty.sTagID == TAG_ID_NAME_TAB)
    {
        lOutErrCode = CursorMoveFunc( 1 );
    }
    else if ( lpobjInItem->m_sctProperty.sTagID == TAG_ID_NAME_ALT_TAB)
    {
        lOutErrCode = CursorMoveFunc( -1 );
    }
    else if ( lpobjInItem->m_sctProperty.sTagID == TAG_ID_NAME_BACK_SPACE)
    {
        lOutErrCode = CursorInputDeleteCharacterFunc( lpobjInputItem );
    }
    else if ( lpobjInItem->m_sctProperty.sTagID == TAG_ID_NAME_CLEAR)
    {
        lOutErrCode = CursorAllDeleteCharacterFunc( lpobjInputItem , true );
    }
    else 
    {
        lOutErrCode = CursorInputUpdateCharacterFunc( lpobjInputItem,
                                                      lpobjInItem->m_sctProperty.sValue,
                                                      gclInputItemTag->m_sctProperty.lMaxLen );
    }

    // Return result
    return lOutErrCode;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  CursorInputUpdateCharacterFunc
//
//�@�\�@�@��@�F  Cursor Input Update Character
//
//�@�T�@�@�v�@�F  Insert the character at the cursor position, thereby moving the cursor.
//
//�@�߁@��@�l�F  LONG lOutErrCode   
//
//�@���@�@���@�F   CItem*     lpobjItem      input item
//                 string     sInTagValue    Value of item

//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/09    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG CGuiViewDlg::CursorInputUpdateCharacterFunc( CItem* lpobjInItem, string sInTagValue, LONG lMaxLength )
{
  // Declare local variable
    LONG                lOutErrCode         = GUI_RET_OK;
    string              sText               = "";
    string              sDispFormat         = "";
    string              sLeftCharacter      = "";
    string              sRightCharacter     = "";
    string              sDispCharacter      = "";
    LONG                lCursorPos          = GUI_VALUE_ZERO_LONG;
    // LONG                lJudgeFunc          = GUI_VALUE_ZERO_LONG;
    // string              sInsertNum          = "";
    BOOL                bInsert             = TRUE;
    // LONG                lInsertNum          = GUI_VALUE_ZERO_LONG;


    // Check valid of agrument

    if ( lpobjInItem == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    else
    {
        // Do nothing
    }

    // Check valid of Tag value
    if ( sInTagValue == "" )
    {
        return ERROR_CODE_NULL;
    }
    else
    {
        // Do nothing
    }

    sText = lpobjInItem->m_sctProperty.sText;
// Start TrungLV update v10.33
    bInsert = JudgeBlankInputStrFunc( sText, sInTagValue );

    if ( false == bInsert )
    {
        return GUI_RET_OK;
    }
    else
    {
        // Do nothing
    }

// End TrungLV update v10.33
    // Added by DienNQ
    //if ( gsctInputFormat.bBlankZero )
    //{
    //    if ((sText == "") || (gsctInputFormat.sInitDisp == sText))
    //    {
    //        lJudgeFunc = JudgeNumberFunc(sInTagValue);
    //        if ( (lJudgeFunc == JUDGE_FULL_NUMBER) || (lJudgeFunc == JUDGE_HALF_NUMBER) )
    //        {
    //            ConvFullHalNumberFunc (sInTagValue, TRUE, sInsertNum);
    //            // <TSDV-131, 132, 133 in comment list-2015-04-30-LanLTM-convert string to number >
    //                lInsertNum = atol( sInsertNum.c_str());
    //            // < TSDV-131, 132, 133 in comment list-2015-04-30- End>

    //            // <TSDV-131, 132, 133 in comment list-2015-04-30-LanLTM-compare number with 0 >
    //            if ( lInsertNum == 0 )
    //            // if ( sInsertNum == "0")
    //            // < TSDV-131, 132, 133 in comment list-2015-04-30- End>
    //            {
    //                return GUI_RET_OK;
    //            }
    //        }
    //    }
    //}

    // Display contents matches the input format, 
    //and the cursor position is the same as if the input start to remove the 0 from the display contents.
    if ( gsctInputFormat.bZeroSupp )
    {
        if ( gsctInputFormat.sInitDisp == sText && gsctInputFormat.lRangeEnd == glRelativeCurPos)
        {
            AddFormatFunc( lpobjInItem, 
                gsctInputFormat.sInputGuide, /*SubStr( gsctInputFormat.sInputGuide, GetSize( sText ) * (-1) ),*/
                "", 
                FALSE,
                gsctInputFormat.bLeftJustify, 
                GetSize( sText ) * ( -1 ) ,
                sText);
        }
        else
        {
            // Do nothing
        }
        //lCursorPos   = glRelativeCurPos - (( LONG )GetSize( gsctInputFormat.sInputGuide ) - ( LONG )GetSize( sText ));
        //sDispFormat  = SubStr( gsctInputFormat.sInputGuide, GetSize( sText ) * (-1) );//gsctInputFormat.sInputGuide.substr( sText.length() * (-1) );
    }

    lCursorPos  = glRelativeCurPos;
    sDispFormat = gsctInputFormat.sInputGuide;

    // Acquisition of left string of cursor (including excerpts processing).
    sLeftCharacter = SubStr( sText, 0, lCursorPos );
    ExcerptNotFormatFunc( SubStr( sDispFormat, 0, lCursorPos ), sLeftCharacter, -1 , sLeftCharacter, gsctInputFormat.bLeftJustify );

    //Get the right string of the cursor (including excerpts processing).
    

    sRightCharacter = SubStr( sText, lCursorPos ); //sText.substr( dwCursorPos );
    ExcerptNotFormatFunc ( SubStr( sDispFormat, lCursorPos ), sRightCharacter,  -1 , sRightCharacter, gsctInputFormat.bLeftJustify );

    // Added by DienNQ
    if ( (string)STR_INSERT_TYPE_ALWAYS != (string)STR_INSERT_TYPE )
    {
        string sResult = "";
        bInsert = JudgeInputStrFunc(sLeftCharacter, sRightCharacter, sInTagValue, lMaxLength, sResult);
        if (bInsert == TRUE)
        {
            sInTagValue = sResult;
        }
        else
        {
            return GUI_RET_OK;
        }
    }

    // Binding excerpt display string and insert string.
    sDispCharacter = sLeftCharacter + sInTagValue + sRightCharacter;
    lOutErrCode = AddFormatFunc( lpobjInItem, gsctInputFormat.sInputGuide, sDispCharacter, FALSE, gsctInputFormat.bLeftJustify, gsctInputFormat.lRangeEnd, sDispCharacter  );

    // Return result
    if ( lOutErrCode == GUI_RET_OK )
    {
        // Do nothing
    }
    else
    {
        return lOutErrCode;
    }

    // Change the display string
    lpobjInItem->m_sctProperty.sText = sDispCharacter;

    lpobjInItem->ItemUpdateState(); 

    // move the cursor in the case of left-justified.
    if ( gsctInputFormat.bLeftJustify == TRUE )
    {
        lOutErrCode = CursorMoveFunc( ( LONG )GetSize( sInTagValue));
    }
    else
    {
        // Do nothing
    }
    // Return result

    return lOutErrCode;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeInputTagDesignFunc
//
//�@�\�@�@��@�F  Change design of input item 
//
//�@�T�@�@�v�@�F  Change design of input item 
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F        CItem* lpInItem         // pointer of changing input item
//                      string sInDesign        // Design mode
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-00.00.00    2015/03/19   (TSDV) LanLTM     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ChangeInputTagDesignFunc( CItem* lpInItem, const string &sInDesign )
{
    LONG  lProcResult = GUI_RET_OK;

    // Check parameter
    if ( lpInItem == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }

    // Change the design

    if (( sInDesign == DESIGN_INPUT_OFF ) ||
        ( sInDesign == DESIGN_INPUT_ON ))
    {
        lProcResult = ChangeClassIDFunc( lpInItem, sInDesign );
    }
    else if ( sInDesign == DESIGN_INPUT_INIT_DISP )
    {
        // Design is init display
        ResolutiveDispInputErroFunc( lpInItem, gdwViewErrorResolutive );

        // 
        if ( ( lpInItem->m_sctProperty.sText == "" ) &&
            ( lpInItem->m_sctProperty.sNullStrInitApp == "true" ) )
        {
            lpInItem->m_sctProperty.sText = lpInItem->m_sctProperty.sInitText;
        }
        else
        {
            // Do nothing
        }

        // Change style of item
        lProcResult = ChangeClassIDFunc( lpInItem, DESIGN_INIT );
    }
    else if ( sInDesign == DESIGN_INPUT_ERROR )
    {
        // Design is input error
        lProcResult = ChangeDispInputErroFunc( lpInItem );
    }
    else if ( sInDesign == DESIGN_INPUT_AUTO )
    {
        // Design is input automatic
        if ( ( ( lpInItem->m_sctProperty.sText == "" ) &&
            ( lpInItem->m_sctProperty.sNullStrInitApp == "true" ) ) ||
            ( lpInItem->m_sctProperty.sText == lpInItem->m_sctProperty.sInitText ) )

        {
            ResolutiveDispInputErroFunc( lpInItem, RESOLUTIVE_MODE_ENTER );
            lpInItem->m_sctProperty.sText = lpInItem->m_sctProperty.sInitText;
            lProcResult = ChangeClassIDFunc( lpInItem, DESIGN_INIT );
        }
        else
        {
            lProcResult = ChangeClassIDFunc( lpInItem, DESIGN_NOT_SELECT );
        }
    }
    else if ( sInDesign == DESIGN_INPUT_NO_CHANGE )
    {
        // Design is no change
        lProcResult = GUI_RET_OK;
    }
    else
    {
        // Other case
        return ERROR_CODE_NOT_RANGE;
    }
    
    // Redraw item
    lpInItem->ItemUpdateState();
    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  InputExpressSeatFunc
//
//�@�\�@�@��@�F  Change design press seating button
//
//�@�T�@�@�v�@�F  Change design press seating button
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  CItem lpInItem        (I)       Item pointer
//                DWORD dwInMaxOnZaseki (I)       Maximum of seat
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LanLTM    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::InputExpressSeatFunc( CItem* lpobjInItem, DWORD dwInMaxOnZaseki )
{
    // Initialize
    LONG                lProcResult         = GUI_RET_OK;               // Function Return
    string              sStsDesign          = "";                       // Status design string
    vector<CItem*>      vSerchTagIdInfo;                                // Vector of tag item after searching
    vector<CItem*>      vZasekiButton;                                  // Vector of Zaseki buttons
    CArea*              lpArea              = NULL;                     // Area pointer
    DWORD               dwLoopIndex         = GUI_VALUE_ZERO_DWORD;     // Loop index
    DWORD               dwZasekiOnCount     = GUI_VALUE_ZERO_DWORD;     // Count of Zaseki button

    // Reset data
    vSerchTagIdInfo.clear();
    vZasekiButton.clear();

    // Check parameter
    if ( lpobjInItem == NULL )
    {
        return ERROR_CODE_NULL_ID;
    }
    else
    {
        // Do nothing
    }

    // get the off state point of the current input the seat ID
    sStsDesign = GetDesignStsFunc( lpobjInItem->m_sctProperty.sStatus );

    if (( sStsDesign == DESIGN_SELECT ) ||
        ( sStsDesign == DESIGN_NOT_SELECT ))
    {
        // Do nothing
    }
    else
    {
        // If it is not turned on or off, the process is terminated
        return ERROR_CODE_NOT_EXIST_CLASS;
    }

    // Modification of the design
    if ( sStsDesign == DESIGN_SELECT )
    {
        lProcResult = ChangeClassIDFunc( lpobjInItem, DESIGN_NOT_SELECT );
    }
    else
    {
        vSerchTagIdInfo = SearchTagIDFunc( lpobjInItem->m_sctProperty.sTagID, E_AREA_OPERATING );

        if ( vSerchTagIdInfo.size() == 1 )
        {
            // Do nothing
        }
        else
        {
            return ERROR_CODE_NOT_EXIST_ID;
        }

        lpArea = GetCurrentAreaByAreaType( E_AREA_OPERATING );

        if ( lpArea == NULL )
        {
            return ERROR_CODE_NOT_EXIST_ID;
        }
        else
        {
            // Do nothing
        }
        vZasekiButton = FindItemsByTagName( "button", lpArea->m_vItemList );

        for ( dwLoopIndex = 0; dwLoopIndex < vZasekiButton.size(); dwLoopIndex++ )
        {
            // And group seating, case lighting state, add the number of lights
            if ( vZasekiButton[dwLoopIndex]->m_sctProperty.sTagGroup == GROUP_NAME_ZASEKI )
            {
                if ( GetDesignStsFunc( vZasekiButton[dwLoopIndex]->m_sctProperty.sStatus ) == DESIGN_SELECT )
                {
                    dwZasekiOnCount = dwZasekiOnCount + 1;
                }
                else
                {
                    // Do nothing
                }
            }
            else
            {
                // Do nothing
            }

            if ( dwInMaxOnZaseki <= dwZasekiOnCount )
            {
                return ERROR_CODE_NOT_RANGE;
            }
            else
            {
                // Do nothing
            }
        }

        // If the LED is off, change the lights
        lProcResult = ChangeClassIDFunc( lpobjInItem, DESIGN_SELECT );
    }

    // Re-draw item
    lpobjInItem->ItemUpdateState();

    // return the processing results
    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeInputButtonDesignFunc
//
//�@�\�@�@��@�F  Change design of pressed button to ON state, change design others button in same group to OFF state
//
//�@�T�@�@�v�@�F  Change design of pressed button to ON state, change design others button in same group to OFF state
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LanLTM    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ChangeInputButtonDesignFunc( CItem* lpobjInItem )
{
    LONG                lProcResult         = GUI_RET_OK;           // Process result
    vector<CItem*>      vGroupButton;                               // Vector of group of button
    DWORD               dwLoopIndex         = GUI_VALUE_ZERO_DWORD; // Loop index
    string              sStsDesign          = "";                   // Status design string

    // Reset data
    vGroupButton.clear();

    // Check parameter
    if ( lpobjInItem == NULL )
    {
        return ERROR_CODE_NULL_ID;
    }
    else
    {
        // Do nothing
    }

    // make the design of the pressed button to light up
    lProcResult = ChangeClassIDFunc( lpobjInItem, DESIGN_BTN_ON );
    lpobjInItem->ItemUpdateState();

    // get the button of the same group
    vGroupButton = SearchGroupTagIDFunc( "", lpobjInItem->m_sctProperty.sTagGroup, lpobjInItem->m_sctProperty.sTagName, E_AREA_NULL, "" );

    for ( dwLoopIndex = 0; dwLoopIndex < vGroupButton.size(); dwLoopIndex++ )
    {
        if ( lProcResult == GUI_RET_OK )
        {
            // Change design
            sStsDesign = GetDesignStsFunc( vGroupButton[dwLoopIndex]->m_sctProperty.sStatus );

            // If the design does not match the tag ID in the lights, change to off
            if (( sStsDesign                        == DESIGN_BTN_ON ) &&
                ( lpobjInItem->m_sctProperty.sTagID != vGroupButton[dwLoopIndex]->m_sctProperty.sTagID ))
            {
                lProcResult = ChangeClassIDFunc( vGroupButton[dwLoopIndex], DESIGN_BTN_OFF );
                vGroupButton[dwLoopIndex]->ItemUpdateState();
            }
            else
            {
                // Do nothing
            }
        }
        else
        {
            break;
        }
    }

    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeDispCalendarEraFunc
//
//�@�\�@�@��@�F  Change Calendar display
//
//�@�T�@�@�v�@�F  Change Calendar display
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  CItem* lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LanLTM    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ChangeDispCalendarEraFunc( CItem* lpInItem )
{
    // Initialize
    LONG                    lProcResult         = GUI_RET_NG;           // Process result
    DWORD                   dwLoopIndex         = GUI_VALUE_ZERO_DWORD; // Loop Index
    CItem*                  lpObjUpdateTag      = NULL;                 // Updated tag item pointer
    vector<CItem*>          vlpItem;                                    // Vector of items
    CItem*                  lpObjIinputTagId    = NULL;                 // Input tag ID item
    string                  sTempFormat         = "";                   // Format string
    string                  sTempDisp           = "";                   // Displaying string
    string                  sDisplayContent     = "";                   // Displaying content
    wstring                 wInputGuide         = L"";                  // Input guide string
    wstring                 wFormatInputItem    = L"";                  // Input item format

    // Reset data
    vlpItem.clear();

    // Check parameter
    if ( lpInItem == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    else 
    {
        // Do nothing
    }

    if ( gclInputItemTag == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    else
    {
        // Do nothing
    }

    // check whether the cursor image is present

    if ( IsWindow( m_cCursor.m_hWnd ) == FALSE )
    {
        return ERROR_CODE_NOT_EXIST_IMAGE;
    }
    else
    {
        // Do nothing
    }

    // if Sum calendar tag ID is currently selected, end  process
    if ( lpInItem->m_sctProperty.sTagID == gsctInputFormat.sTagId )
    {
        return GUI_RET_OK;
    }
    else
    {
        // Do nothing
    }

    // 
    for ( dwLoopIndex = 0; dwLoopIndex < DATE_OF_BIRTH_FORMAT_TABLE_SIZE; dwLoopIndex++ )
    {
        if ( lpInItem->m_sctProperty.sTagID == Date_Of_Birth_Fomat_Table[dwLoopIndex].sTagId )
        {
            if ( gclInputItemTag->m_sctProperty.bParent == TRUE )
            {
                lpObjUpdateTag = gclInputItemTag;
                // Fix PGRelief
                if ( lpObjUpdateTag == NULL )
                {
                    return ERROR_CODE_NOT_EXIST_ID;
                }
            }
            else
            {
                if ( gclInputItemTag->m_vobjItems.size() != 0 )
                {
                    lpObjUpdateTag = FindItemByTagID( TAG_ID_NAME_SET_CHAR_SPAN, gclInputItemTag->m_vobjItems );
                    // If not found any items
                    if ( lpObjUpdateTag == NULL )
                    {
                        return ERROR_CODE_NULL_ID;
                    }
                    else
                    {
                        // Do nothing
                    }
                }
                else
                {
                    // Do nothing
                }
            }

            // get the month and day date element if date of birth of the (two lines year)
            if ( gclInputItemTag->m_sctProperty.sTagID == TAG_ID_NAME_SEINEN_GAPPI )
            {
                vlpItem = FindItemsByTagName( TAG_NAME_SPAN, lpObjUpdateTag->m_vobjItems );

                if ( vlpItem.size() == 0 )
                {
                    return ERROR_CODE_NULL_ID;
                }
                else
                {
                    lpObjIinputTagId = vlpItem[0];
                }
            }
            else
            {
                lpObjIinputTagId = lpObjUpdateTag;
            }

            // get the group
            sTempFormat = gsctInputFormat.sGreap;
            lProcResult = ExcerptNotFormatFunc( gsctInputFormat.sInputGuide, lpObjUpdateTag->m_sctProperty.sText, -1, sTempDisp, gsctInputFormat.bLeftJustify );
            // If it is not a button that is currently selected, change the format
            gsctInputFormat.sTagId = Date_Of_Birth_Fomat_Table[dwLoopIndex].sTagId;
            gsctInputFormat.sGreap = Date_Of_Birth_Fomat_Table[dwLoopIndex].sGreap;
            gsctInputFormat.sInputGuide = Date_Of_Birth_Fomat_Table[dwLoopIndex].sInputGuide;
            wInputGuide = StringToWChar( gsctInputFormat.sInputGuide );
            wFormatInputItem    = StringToWChar( FORMAT_INPUT_ITEM );
            gsctInputFormat.lRangeStart = wInputGuide.find( wFormatInputItem );
            gsctInputFormat.lRangeEnd = wInputGuide.rfind( wFormatInputItem ) + 1;

            std::regex InitDisp( FORMAT_INPUT_ITEM );
            gsctInputFormat.sInitDisp = std::regex_replace( gsctInputFormat.sInputGuide, InitDisp, ( string )"�@" );
            gsctInputFormat.sEraName = Date_Of_Birth_Fomat_Table[dwLoopIndex].sEraName;

            // If the group is consistent, to change only the sum calendar display
            if ( Date_Of_Birth_Fomat_Table[dwLoopIndex].sGreap == sTempFormat )
            {
                lProcResult = AddFormatFunc( lpObjUpdateTag, gsctInputFormat.sInputGuide, sTempDisp, FALSE, gsctInputFormat.bLeftJustify, gsctInputFormat.lRangeEnd, sDisplayContent );
                lpObjIinputTagId->m_sctProperty.sText = sDisplayContent;
                lpObjIinputTagId->ItemUpdateState();
                
                lProcResult = GUI_RET_OK;
            }
            else
            {
                lProcResult = CursorAllDeleteCharacterFunc( lpObjIinputTagId , false );
            }
            
            break;

        }
        else
        {
            // Do nothing
        }
    }

    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  CursorInputDeleteCharacterFunc
//
//�@�\�@�@��@�F  Delete the character at the cursor position, then move the cursor
//
//�@�T�@�@�v�@�F  Delete the character at the cursor position, then move the cursor
//
//�@�߁@��@�l�F  LONG
//
//�@���@�@���@�F  CItem* lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::CursorInputDeleteCharacterFunc( CItem* lpobjInItem )
{
    // Declare local variable
    LONG                lOutErrCode         = GUI_RET_OK;
    LONG                lDeleteIndex        = GUI_VALUE_ZERO_LONG;
    string              sDispFormat         = "";
    string              sDispCharacter      = "";
    

    // Check valid of agrument

    if ( lpobjInItem == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    else
    {
        // Do nothing
    }

    // // Get the Delete character position.
    // After the cursor in the rest of the string, get a string that was excerpted format.
    if ( gsctInputFormat.sInputGuide == "" )
    {
        // If the input guide is not present, it may be a cursor position -1.
        lDeleteIndex = glRelativeCurPos - 1;
    }
    else
    {
        // If the format is not an input guide, exit the loop.
        for ( lDeleteIndex = glRelativeCurPos - 1; lDeleteIndex >= 0; lDeleteIndex-- )
        {
            if ( SubStr( gsctInputFormat.sInputGuide, lDeleteIndex, 1 ) == FORMAT_INPUT_ITEM )
            {
                break;
            }
            else
            {
                // Do nothing
            }
        }
    }

    // If the format of non-input part is not filled.
    sDispFormat = gsctInputFormat.sInputGuide; // Update new javascript

    // Excerpt processing of the display string (excluding the character before the cursor position).

    ExcerptNotFormatFunc( sDispFormat, lpobjInItem->m_sctProperty.sText, lDeleteIndex, sDispCharacter, gsctInputFormat.bLeftJustify );
    lOutErrCode =  AddFormatFunc( lpobjInItem, sDispFormat, sDispCharacter, FALSE, gsctInputFormat.bLeftJustify, gsctInputFormat.lRangeEnd, sDispCharacter );
    // Return result
    if ( lOutErrCode != GUI_RET_OK )
    {
        return lOutErrCode;
    }
    else
    {
        // Do nothing
    }

    // Change display
    lpobjInItem->m_sctProperty.sText = sDispCharacter;

    lpobjInItem->ItemUpdateState(); 

    // move the cursor in the case of left-justified.
    if ( gsctInputFormat.bLeftJustify == TRUE )
    {
        lOutErrCode = CursorMoveFunc ( -1 );
    }
    else
    {
        // Do nothing
    }

    return lOutErrCode;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  CursorMoveFunc
//
//�@�\�@�@��@�F  Move cursor to specified position
//
//�@�T�@�@�v�@�F  Move cursor to specified position
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  LONG lMoveCursor       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::CursorMoveFunc( LONG lMoveCursor )
{
    // Declare local variable
    LONG                lOutErrCode             = GUI_RET_OK;
    LONG                lMoveCount              = GUI_VALUE_ZERO_LONG;
    string              sMoveRangeCharacter     = "";
    string              sTempString            = "";
    DWORD               dwCount                 = GUI_VALUE_ZERO_DWORD;
    LONG                lCursor                 = GUI_VALUE_ZERO_LONG;
    //DWORD               dwMaxLen              = GUI_VALUE_ZERO_DWORD;
    LONG                dwIndex                 = GUI_VALUE_ZERO_DWORD;
    LONG                lMaxIdx                 = GUI_VALUE_ZERO_DWORD;
    CCssLabel*          lpCss                   = NULL;
    LONG                lCurImgTop              = GUI_VALUE_ZERO_LONG;
    DWORD               dwTextAlign             = 0;
    vector<CItem*>      vSpanItem;
    DWORD               dwFontSize              = GUI_VALUE_ZERO_DWORD;
    DWORD               dwWidth                 = GUI_VALUE_ZERO_DWORD;
    DWORD               dwHeight                = GUI_VALUE_ZERO_DWORD;
    LONG                lCurImgLeft             = GUI_VALUE_ZERO_LONG;
    DWORD               dwPadding               = GUI_VALUE_ZERO_DWORD;
    LONG                lStyleSizeTemp          = GUI_VALUE_ZERO_LONG;
    std::smatch sm;
    LONG                lMaxLen                 = GUI_VALUE_ZERO_LONG;

    // Get CSS of input item
    lpCss = (CCssLabel*) CCssStore::GetCss( gclInputItemTag->m_sctProperty.sClass );

    if ( lpCss == NULL )
    {
        return ERROR_CODE_NULL;
    }
    else
    {
        // Do nothing
    }

    if (( lpCss->sctBorder.dwBorderStyle == CSS_BORDER_INSET ) &&
        ( lpCss->sctBorder.dwWidth == 0 ))
    {
        lpCss->sctBorder.dwWidth = 3; // Default  border with for inset
    }
    else {} // Do nothing

    // Depending on whether the move number is less than 0, the number of the cursor to increase or decrease to change.
    if ( lMoveCursor < 0 )
    {
        lMoveCount = -1;
// TrungLV Fix delete character Bug
        sMoveRangeCharacter = SubStr( gsctInputFormat.sInputGuide , glRelativeCurPos+lMoveCount, lMoveCount*lMoveCount );
#if 0
        // Cursor movement range output format.
        if (( glRelativeCurPos + lMoveCursor < 0 ) && 
            ( ( LONG ) GetSize( gsctInputFormat.sInputGuide ) > abs( glRelativeCurPos + lMoveCursor )))
        {
            if ( abs( glRelativeCurPos + lMoveCursor ) <= lMoveCursor * lMoveCount)
            {
                sMoveRangeCharacter = SubStr( gsctInputFormat.sInputGuide, GetSize( gsctInputFormat.sInputGuide ) -  abs( glRelativeCurPos + lMoveCursor ) );
            }
            
            else
            {
                sMoveRangeCharacter = SubStr( gsctInputFormat.sInputGuide, GetSize( gsctInputFormat.sInputGuide ) -  abs( glRelativeCurPos + lMoveCursor ), lMoveCursor * lMoveCount );
            }
        }
        else
        {
            // Do nothing
        }
#endif

    }
    else
    {
        lMoveCount = 1;
        // Cursor movement range output format.
        sMoveRangeCharacter = SubStr( gsctInputFormat.sInputGuide, glRelativeCurPos, lMoveCursor );
    }

    //To obtain sequences that are input to the cursor guide range minute.

#if 0
    sTempString = gsctInputFormat.sInputGuide;
    std::regex_search( sTempString, sm, std::regex( string( "[^" )+ FORMAT_INPUT_ITEM+ "]"), std::regex_constants::match_default );
#endif
// TrungLV fixbug 172 - 20150506
    sTempString = std::regex_replace( sMoveRangeCharacter , std::regex( string( "([��])")), string(""));
    dwCount = GetSize( sTempString );
// TrungLV fixbug 172 - 20150506
//    dwCount = sm.size();

    if ( dwCount == 0 )
    {
        lCursor = glRelativeCurPos + lMoveCursor;
    }
    else
    {
        //If there are input guide to cursor movement worth, increase the number of cursor movement
        // lCursor = lCursor + dwCount * lMoveCount;
        lCursor = glRelativeCurPos + lMoveCursor + dwCount * lMoveCount; // Update new javascript
    }
    
    // The acquisition of a maximum number of digits
    // Check the number of input character
    lMaxLen = gclInputItemTag->m_sctProperty.lMaxLen;
    if ( lMaxLen == INPUT_LENGTH_NASHI_MODE )
    {
        lMaxLen = INPUT_MAX_LENGTH_LIMIT;
    }
    else
    {
        //dwMaxLen = ( DWORD )gclInputItemTag->m_sctProperty.lMaxLen;
        //Maximum string when it is displayed in the maximum number of characters
        if ( gsctInputFormat.sInputGuide == "" )
        {
             // Do nothing
        }
        else
        {
            for ( dwIndex = 0, lMaxIdx = gsctInputFormat.lRangeStart; dwIndex < lMaxLen; lMaxIdx++ )
            {
            
                if ( lMaxIdx == gsctInputFormat.lRangeEnd )
                {
                    break;
                }
                else
                {
                    // Do nothing
                }
                // Calculate Become what character when you turn on the maximum number of characters in the input guide.
                if ( SubStr( gsctInputFormat.sInputGuide, lMaxIdx, 1 ) == FORMAT_INPUT_ITEM )
                {
                    dwIndex = dwIndex + 1;
                }
                else
                {
                    // Do nothing
                }
            }
            lMaxLen = lMaxIdx;
        }
    }
    

    while ( lCursor > 0 && lCursor < lMaxLen && gsctInputFormat.sInputGuide != "" )
    {
        if ( SubStr( gsctInputFormat.sInputGuide, lCursor, 1 ) == FORMAT_INPUT_ITEM )
        {
            break;
        }
        else
        {
            // Do nothing
        }
        lCursor = lCursor + 1;
    }

    if ( lCursor < gsctInputFormat.lRangeStart )
    {
        //I is changed to the minimum value when the moving prediction cursor exceeds the minimum value of the range of the cursor.
        lCursor = gsctInputFormat.lRangeStart;
    }
    else if ( lCursor > gsctInputFormat.lRangeEnd )
    {
        //Is changed to the maximum value when the moving prediction cursor exceeds the maximum value in the range cursor
        lCursor = gsctInputFormat.lRangeEnd;
    }
    else
    {
        // Do nothing
    }

    /*glRelativeCurPos = dwCursor;
    CWnd* lpWnd = dynamic_cast<CWnd*>(gclInputItemTag);
    LPTEXTMETRIC        lpTextMt = new TEXTMETRIC();
    lpWnd->GetDC()->GetTextMetrics( lpTextMt );
    lpTextMt->tmHeight*/

    //Set relative position for cursor
    glRelativeCurPos = lCursor;


    //The value is divided by 2 from the height by subtracting the cursor image input items to the cursor position (top) and.
    // top_AlignItem +( height_Item - height of cursor)/2
    lStyleSizeTemp      = 0; //gclInputItemTag->m_sctProperty.dwTop;
    dwHeight            = gclInputItemTag->m_sctProperty.dwHeight;
    dwPadding           = m_cCursor.m_dwHeight;
    lCurImgTop          = lStyleSizeTemp + (( LONG ) dwHeight - ( LONG )dwPadding )/2;

    // Calculation of the cursor image display position (left).
    
    //If date of birth input (two lines year), character font acquisition source is different.
    if ( gclInputItemTag->m_sctProperty.sTagID == TAG_ID_NAME_SEINEN_GAPPI )
    {
        //get the font size from the span of the input item tag.
        vSpanItem = FindItemsByTagName( TAG_NAME_SPAN, gclInputItemTag->m_vobjItems );
        if ( vSpanItem.size() > 0 )
        {
            dwFontSize = vSpanItem[0]->m_sctProperty.dwFontSize + CURSOR_IMAGE_MARGIN_CHARACTER;
        }
        else
        {
            return ERROR_CODE_NOT_EXIST_ID;
        }
    }
    else
    {
        dwFontSize = gclInputItemTag->m_sctProperty.dwFontSize + CURSOR_IMAGE_MARGIN_CHARACTER;
    }
    // Calculation formula of the display position by the display position is different.
    // Get input item tag left position.
    dwTextAlign      = lpCss->dwTextAlign;
    dwWidth          = gclInputItemTag->m_sctProperty.dwWidth;
    lStyleSizeTemp   = 0;//gclInputItemTag->m_sctProperty.dwLeft;


    CItem* lpobjUpdateItem = gclInputItemTag;
    if ( gclInputItemTag->m_vobjItems.size() > 0 )
    {
        lpobjUpdateItem = FindItemByTagID( TAG_ID_NAME_SET_CHAR_SPAN, gclInputItemTag->m_vobjItems );
        if ( lpobjUpdateItem == NULL )
        {
            return ERROR_CODE_NULL;
        }
        else
        {
            // Do nothing
        }
    }
    else {} // Do nothing

    if ( dwTextAlign & DT_CENTER )
    {
        // Update new javascript
        if ( gsctInputFormat.sInputGuide == "" )
        {
            dwWidth = dwWidth - GetSize( gclInputItemTag->m_sctProperty.sText ) * dwFontSize;
        } 
        else
        {
            dwWidth = dwWidth - GetSize( gsctInputFormat.sInputGuide ) * dwFontSize;
        }
        dwWidth = dwWidth/2;

        // Width and format maximum number of characters in the input item, I will calculate the leftmost display position by font size.
        //dwWidth         = ( dwWidth - GetSize( gclInputItemTag->m_sctProperty.sText ) * dwFontSize ) / 2;
        lStyleSizeTemp  = lStyleSizeTemp + ( LONG )dwWidth;
        lCurImgLeft     = lStyleSizeTemp + ( glRelativeCurPos * ( LONG )dwFontSize );
    }
    else if (  dwTextAlign & DT_RIGHT )
    {
        dwPadding        = lpCss->dwPadR;
        lStyleSizeTemp   = lStyleSizeTemp + ( LONG )dwWidth - ( LONG )dwPadding - ( LONG )lpCss->sctBorder.dwWidth;
        
        // Calculation of the cursor position
        if ( gsctInputFormat.sInputGuide == "" )
        {
            // Calculation method is changed by left-justified, right-justified in the input format.
            if ( gsctInputFormat.bLeftJustify == TRUE )
            {
                lCurImgLeft = lStyleSizeTemp - (( LONG )GetSize( lpobjUpdateItem->m_sctProperty.sText ) - glRelativeCurPos ) * ( LONG )dwFontSize;
            }
            else
            {
                lCurImgLeft = lStyleSizeTemp - (( gsctInputFormat.lRangeEnd - glRelativeCurPos ) * ( LONG )dwFontSize );
            }
        }
        else
        {
            lCurImgLeft = lStyleSizeTemp - ((( LONG )GetSize( gsctInputFormat.sInputGuide ) - glRelativeCurPos ) * ( LONG )dwFontSize ); 
        }
    }
    // default
    else
    {
        dwPadding   = lpCss->dwPadL;
        lCurImgLeft = ( LONG )dwPadding + lStyleSizeTemp + ( LONG )dwFontSize * glRelativeCurPos;
    }

    // Need to be calculated fixed position
    //ReCalculateCursorPosition( gclInputItemTag, lCurImgLeft , lCurImgTop );
    /*m_cCursor.m_dwX = lCurImgLeft;
    m_cCursor.m_dwY = lCurImgTop;*/
    m_cCursor.m_dwHeight = lpobjUpdateItem->m_sctProperty.dwFontSize + CURSOR_IMAGE_MARGIN_CHARACTER * 4;
    
    ShowCursor( lCurImgLeft , lCurImgTop, m_cCursor.m_dwHeight, lpobjUpdateItem );

    // return result
    return lOutErrCode;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  FindItemByTagName
//
//�@�\�@�@��@�F  Find item by Name
//
//�@�T�@�@�v�@�F  Find item by Name
//
//�@�߁@��@�l�F  LONG lOutErrCode
//
//�@���@�@���@�F  string sTagName       (I)        Item needs to be searched
//               vector<CItem*> vobjInSearchItem // Scope
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/06    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////

vector<CItem*> CGuiViewDlg::FindItemsByTagName ( string sInTagName, vector<CItem*> vobjInSearchItem)
{
    DWORD           dwIndex       = GUI_VALUE_ZERO_DWORD;    // Counter variable
    vector<CItem*>  vOutResult;
    vector<CItem*>  vSubResult;

    // Reset data
    vOutResult.clear();
    vSubResult.clear();

    // Return if input size is zero
    if ( vobjInSearchItem.size() == 0 )
    {
        return vOutResult;
    }
    else
    {
        // Do nothing
    }
    for ( dwIndex = 0; dwIndex < vobjInSearchItem.size(); dwIndex++ )
    {
        if ( vobjInSearchItem[dwIndex]->m_sctProperty.sTagName == sInTagName )
        {
            vOutResult.push_back( vobjInSearchItem[dwIndex] );
        }
        else
        {
            // Do nothing
        }
        if ( vobjInSearchItem[dwIndex]->m_vobjItems.size() == 0 )
        {
            // Do nothing
        }
        else
        {
            vSubResult = FindItemsByTagName ( sInTagName, vobjInSearchItem[dwIndex]->m_vobjItems );
            if ( vSubResult.size() > 0 )
            {
                vOutResult.insert( vOutResult.begin(), vSubResult.begin(), vSubResult.end() );
            }
            else
            {
                // Do nothing
            }
        }
    }
    return vOutResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  IsLeapYear
//
//�@�\�@�@��@�F  Check year is leap or not
//
//�@�T�@�@�v�@�F  Check year is leap or not
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  WORD wYear       (I)       Yeart
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LiemTT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CGuiViewDlg::IsLeapYear( WORD wYear )
{
    if ( wYear % 4 != 0 )
    {
        return FALSE;
    }
    else if ( wYear % 100 != 0 )
    {
        return TRUE;
    }
    else
    {
        // Do nothing
    }
    return ( wYear % 400 == 0 );
}



/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ControlEnableAllDisplayFunc
//
//�@�\�@�@��@�F  Control Enable All Display 
//
//�@�T�@�@�v�@�F  Control Enable All Display 
//
//�@�߁@��@�l�F  LONG lOutErrCode
//
//�@���@�@���@�F  BOOL      bInEnable         (I)       Enable flag
//                AREA_ENUM eInAreaType       (I)       Area type
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/03/06    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ControlEnableAllDisplayFunc( BOOL bInEnable, AREA_ENUM eInAreaType )
{
    // Declare local varible
    LONG                lOutErrCode     = GUI_RET_OK;
    vector<CArea*>      vlpobjArea;
    CArea*              lpobjAreaTemp   = NULL;
    BOOL                bHasPopup       = FALSE;
    CPopupDlg*          lpActivePopup   = GetActivePopup();
    // Check valid of agrument
    if (bInEnable != FLG_OBJECT_ENABLE && bInEnable != FLG_OBJECT_NOT_ENABLE ) 
    {
        return ERROR_CODE_NOT_RANGE;  // Fix follow TSBJ review
    }
    else
    {
        // Do nothing
    }
    bHasPopup = m_cAreaStore.HasShowingPopUp();
    // Change the control screen in accordance with the area name.
    switch ( eInAreaType )
    {
        case E_AREA_GYOMU:
            if ( bHasPopup == FALSE )
            {
                m_cAreaStore.GetActiveTopIframe()->EnableWindow( bInEnable );
            } 
            else
            {
                lpActivePopup->EnableWindow( bInEnable );
            } 
            break;

        default:
            lpobjAreaTemp = GetCurrentAreaByAreaType ( eInAreaType );
            if ( lpobjAreaTemp == NULL )
            {
                return ERROR_CODE_NOT_EXIST_ID;  // Fix follow TSBJ review
            }
            else
            {
                lpobjAreaTemp->ChangeStatus( bInEnable );
            }
            break;
    }

    return lOutErrCode;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SettingCalendarFunc
//
//�@�\�@�@��@�F  Setting to display calendar
//
//�@�T�@�@�v�@�F  Setting to display calendar
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  vector<CItem*> vlpobjCalendarItems       (I)       vector of Item pointer
//                WORD wInDispYear                         (I)       Displaying year
//                BYTE byInDispMonth                       (I)       Displaying month
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::SettingCalendarFunc( 
                const vector<CItem*> &vlpobjCalendarItems, 
                      WORD wInDispYear, 
                      BYTE byInDispMonth )
{
    // Initilize
    LONG                       lProcResult      = GUI_RET_OK;  // Error code
    SCT_DATE                   sctDispEndDate;
    string                     sWeekDay         = "";
    string                     sDateTagId       = "";
    DWORD                      dwIndex          = GUI_VALUE_ZERO_DWORD; // Counter
    DWORD                      dwSubIndex       = GUI_VALUE_ZERO_DWORD;
    WORD                       wRow            = 1; // Number of calendar line
    CItem*                     lpobjDate       = NULL;
    SCT_DATE                   sctResultDate;
    BOOL                       bRet            = FALSE;
    vector<SCT_DATE>           vsctHoliday;
    string                     sMonth          = "";
    string                     sDay            = "";
    string                     sYear           = "";
    string                     sDispData       = "";
    string                     sBeforeGaikan   = "";
    DWORD                      dwHolidayCnt    = GUI_VALUE_ZERO_DWORD;
    LONG                       lFuncResult     = GUI_RET_NG;    // Error code of internal function
    // TSDV-LanLTM-20150901-Fix bug No10: Date time error when displaying icon �g�y�x���h
    LONG                        lAddedDayNum    = GUI_VALUE_ZERO_LONG; // Number of day will be added
    // TSDV-LanLTM-20150901-Fix bug No10-END

    // Check parameter ( TSBJ review action )
    if ( vlpobjCalendarItems.size() == 0 )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }

    //Set display date to global variable
    vsctHoliday.clear();
    // TSDV-LanLTM-20150901-Fix bug No10: Date time error when displaying icon �g�y�x���h
    // SCT_DATE sctDispDate ( wInDispYear, byInDispMonth - 1, 1 );
    SCT_DATE sctDispDate ( wInDispYear, byInDispMonth, 1 );
    sctDispDate = AddMonth( -1, sctDispDate );
    // TSDV-LanLTM-20150901-Fix bug No10-END
    memcpy ( &gsctDispDate, &sctDispDate, sizeof( SCT_DATE ) );

    sWeekDay = CalculationWeekFunc ( sctDispDate );

    //Get the ID of the 1st. 
    //Since the calendar is you do not know what day of the week beginning, to look at the day of the week _1_ count
    for ( dwIndex = 1; dwIndex <= 7; dwIndex++ )
    {
        // Reset data
        sDateTagId = "";
        // Get tag ID of date
        sDateTagId = sWeekDay + TAG_ID_SPLIT + std::to_string(( LONGLONG )wRow ) + TAG_ID_SPLIT + std::to_string( ( LONGLONG )dwIndex );
        //sDateTagId = "Date" + (string)TAG_ID_SPLIT + std::to_string( ( LONGLONG )wRow ) + TAG_ID_SPLIT + std::to_string( ( LONGLONG )dwIndex );
        lpobjDate = FindItemByTagID( sDateTagId, vlpobjCalendarItems );
        if ( lpobjDate == NULL )
        {
            //return lProcResult;
            // Do nothing
        }
        else
        {
            // TSDV-LanLTM-20150901-Fix bug No10: Date time error when displaying icon �g�y�x���h
            // sctDispDate.byDay = ( BYTE )( sctDispDate.byDay + ( dwIndex - 1 ) * ( -1 ));
            lAddedDayNum = ( dwIndex - 1 ) * ( -1 );
            sctDispDate = AddDay( lAddedDayNum, sctDispDate );
            // TSDV-LanLTM-20150901-Fix bug No10-END
            break;
        }
    }

    // Get the display end date.
    memcpy( &sctDispEndDate, &sctDispDate, sizeof( SCT_DATE ));
    // TSDV-LanLTM-20150901-Fix bug No10: Date time error when displaying icon �g�y�x���h
    // sctDispEndDate.byDay = ( WORD )sctDispEndDate.byDay + 41;
    sctDispEndDate = AddDay( 41, sctDispEndDate );
    // TSDV-LanLTM-20150901-Fix bug No10-END

    // Get a holiday necessary to display from the global variable.
    for ( dwIndex = 0; dwIndex < gsctHolidayArray.size(); dwIndex++ )
    {
        // Execution of the real Japan check
        bRet = JudgeDateValidityFunc( gsctHolidayArray[dwIndex], &sctResultDate, lFuncResult );
        if ( bRet == TRUE )
        {
            // Date is the case in the display month, I get
            if ( sctDispDate <= sctResultDate && sctResultDate <= sctDispEndDate )
            {
                vsctHoliday.push_back( sctResultDate );
            }
            else
            {
                // Do nothing
            }
        }
        else
        {
            return lProcResult;
        }
    }

    // Sort holiday
    std::sort( vsctHoliday.begin(), vsctHoliday.end(), SortDateAsc );

    // Setting display date
    for ( dwIndex = 1; dwIndex <= 42; dwIndex++ )
    {
        sWeekDay    = CalculationWeekFunc( sctDispDate );
        sDateTagId  = sWeekDay + TAG_ID_SPLIT + std::to_string( ( LONGLONG )wRow ) + TAG_ID_SPLIT + std::to_string( ( LONGLONG )dwIndex );
        //sDateTagId  = "Date" + (string) TAG_ID_SPLIT + std::to_string( ( LONGLONG )wRow ) + TAG_ID_SPLIT + std::to_string( ( LONGLONG )dwIndex );
        lpobjDate   = FindItemByTagID( sDateTagId, vlpobjCalendarItems );
        if ( lpobjDate == NULL )
        {
            continue;
        }
        else
        {
            // Do nothing
        }

        //Setting of the display content at the start of the loop or in the case of day, month also be displayed.
        sMonth  = std::to_string( ( LONGLONG )sctDispDate.byMonth);
        sDay    = std::to_string( ( LONGLONG )sctDispDate.byDay );
        sYear   = std::to_string( ( LONGLONG )sctDispDate.wYear );
        if ( dwIndex == 1 || (WORD)sctDispDate.byDay == 1 )
        {
            //One button eyes or in the case of day, month also be displayed.
            sDispData = sMonth + "/" + sDay;
        }
        else
        {
            sDispData = ConvDateFormatFunc( sctDispDate, CALENDAR_DATE_FORMAT );
            if (( sDispData == std::to_string( ( LONGLONG ) ERROR_CODE_NULL ) ) ||
                ( sDispData == std::to_string( ( LONGLONG ) ERROR_CODE_CONV_ANNO_JAPANESE ) )) // Update new javascript
            {
                sDispData = lpobjDate->m_sctProperty.sValue;
            }
            else
            {
                // Do nothing
            }
        }
        lpobjDate->m_sctProperty.sText = sDispData;
        //  Get the year to be in full-width.
        ConvFullHalNumberFunc(sYear, false, sDispData);

        // The month will be in full size.
        ConvFullHalNumberFunc(sMonth, false, sMonth);
        ConvZeroPaddingFunc(sMonth, ZERO_PADDING_AVAILABLE, 2, sMonth);

        // The month I will be in full size.
        ConvFullHalNumberFunc(sDay, false, sDay);
        ConvZeroPaddingFunc(sDay, ZERO_PADDING_AVAILABLE, 2, sDay);

        sDispData = sDispData + sMonth + sDay;

        //  Set the date value value.
        lpobjDate->m_sctProperty.sValue = sDispData;

        // To get the current appearance. (Backup)
        sBeforeGaikan = lpobjDate->m_sctProperty.sGaikan;

        // In the case of holiday, put a "holiday" on the day of the week
        //To change the count of holidays to the number obtained by adding 1 to the loop count.
        for ( dwSubIndex = dwHolidayCnt; dwSubIndex < gsctHolidayArray.size(); dwSubIndex++ )
        {
            if ( memcmp(&sctDispDate, &gsctHolidayArray[dwSubIndex], sizeof( SCT_DATE ) ) == 0 )
            {
                sWeekDay = DAY_OF_WEEK_HOLIDAY;
                dwHolidayCnt++;
                break;
            }
            else
            {
                // Do nothing
            }
        } // end for sub

        if ( sWeekDay == DAY_OF_WEEK_SATURDAY )
        {
            lpobjDate->m_sctProperty.sGaikan = Calendar_Date_Gaikan_Table.sSaturday;
        }
        else if ( sWeekDay == DAY_OF_WEEK_SUNDAY )
        {
            lpobjDate->m_sctProperty.sGaikan = Calendar_Date_Gaikan_Table.sHoliday;
        }
        else if ( sWeekDay == DAY_OF_WEEK_HOLIDAY )
        {
            lpobjDate->m_sctProperty.sGaikan = Calendar_Date_Gaikan_Table.sHoliday;
        }
        else
        {
            lpobjDate->m_sctProperty.sGaikan = Calendar_Date_Gaikan_Table.sWeekday;
        }
        
        // Point off, set the non-activity.
        if ( memcmp(&sctDispDate, &gsctBasicDate, sizeof( SCT_DATE )) == 0 )
        {
            // If the date is specified date, to light up.
            lProcResult = ChangeClassIDFunc( lpobjDate, DESIGN_BTN_ON, sBeforeGaikan );
            lpobjDate->UpdateEnable( TRUE );
        }
        else if ( gsctStartDate <= sctDispDate && sctDispDate <= gsctEndDate )
        {
            // Date if the input possible start date input input possible end days, to off.
            lProcResult = ChangeClassIDFunc( lpobjDate, DESIGN_BTN_OFF, sBeforeGaikan );
            lpobjDate->UpdateEnable( TRUE );
        }
        else
        {
            //Otherwise, inactive.
            lpobjDate->UpdateEnable( FALSE );
            lProcResult = ChangeClassIDFunc( lpobjDate, DESIGN_DISABLE, sBeforeGaikan );
        }
        // If the line number * 7 matches the serial number, add 1 to the line.
        if ( dwIndex ==  ( DWORD )wRow * 7 )
        {
            wRow++;
        }
        else
        {
            // Do nothing
        }
        // Change to the next day.

        sctDispDate = AddDay( 1, sctDispDate );
        // Redraw item
        lpobjDate->ItemUpdateState(); 

    }// End for

    return lProcResult;
}



//---------------------------------------------------------------------------------------------
// TO DO

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SearchAreaTagIndexFunc
//
//�@�\�@�@��@�F  Search index of area following area name
//
//�@�T�@�@�v�@�F  Search index of area following area name
//
//�@�߁@��@�l�F  Index of area
//
//�@���@�@���@�F  vector<CItem*> vlpItem        (I)       vector of Item pointer
//                AREA_ENUM eInAreaType         (I)       Area type
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LiemTT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::SearchAreaTagIndexFunc( 
                  const   vector<CItem*> &vlpItem, 
                          AREA_ENUM eInAreaType )
{
    // Initilize
    DWORD    dwIndex     = GUI_VALUE_ZERO_DWORD;
    LONG     lTagIndex   = -1;

    // Check vector has member or not
    if ( vlpItem.size() == 0 )
    {
        return lTagIndex;
    }

    for ( dwIndex = 0 ; dwIndex < vlpItem.size(); dwIndex++ )
    {
        if ( vlpItem[dwIndex]->m_sctProperty.eAreaType == eInAreaType )
        {
            lTagIndex = ( LONG )dwIndex;
            break;
        }            
    }  
    return lTagIndex;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeVisibleTagFunc
//
//�@�\�@�@��@�F  Change visibility when switch tab
//
//�@�T�@�@�v�@�F  Change visibility when switch tab
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  CItem* lpobjInItem             (I)        Item pointer
//                vector<CItem*> vInSearchItems  (I)        Vector of items in current area
//                BOOL bInVisible                (I)        Visibility state
//                string dwInDesign              (I)        Design of item
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LanLTM    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ChangeVisibleTagFunc( 
                      CItem* lpobjInItem, 
               const  vector<CItem*> &vInSearchItems, 
                      BOOL bInVisible, 
               const  string        &dwInDesign )
{
    // Initilize
    LONG               lProcResult= GUI_RET_OK;  // Error code

    // Check parameter

    if ( lpobjInItem == NULL )
    {
        lProcResult = ERROR_CODE_NULL_ID;
    }
    else
    {
        // Do nothing
    }

    if ( bInVisible != FLG_OBJECT_VISIBLE )
    {
        lProcResult = ERROR_CODE_NOT_RANGE;
    }
    else
    {
        // Do nothing
    }

    if ( dwInDesign != DESIGN_BTN_ON )
    {
        lProcResult = ERROR_CODE_NOT_RANGE;
    }
    else
    {
        // Do nothing
    }
    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeVisibleInsideTabFunc
//
//�@�\�@�@��@�F  Switch display in same tab
//
//�@�T�@�@�v�@�F  Switch display in same tab
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  CItem* lpobjInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LanLTM    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ChangeVisibleInsideTabFunc( CItem* lpobjInItem )
{
    // Initilize
    LONG                                lProcResult         = GUI_RET_OK;           // Error code
    vector<CItem*>                      vlpParentItem;                              // Vector of parent items
    CItem*                              lpParentItem        = NULL;                 // Specific parent item
    DWORD                               dwLoopIndex         = GUI_VALUE_ZERO_DWORD; // Loop index
    vector<CItem*>                      vlpChidItem;                                // Vector of children items
    vector<CItem*>                      vlpParentTabItem;                           // Vector of parent tab items

    // Reset data
    vlpParentItem.clear();
    vlpChidItem.clear();
    vlpParentTabItem.clear();

    // Check parameter
    if ( lpobjInItem == NULL )
    {
        return ERROR_CODE_NULL_ID;
    }
    else
    {
        // Do nothing
    }

    // Find all parent items that has tag name is "ul"
    if ( lpobjInItem->m_sctProperty.sTagName == "li" )
    {
        vlpParentItem = SearchTagNameFunc( "ul", lpobjInItem->m_sctProperty.eAreaType );
    }
    else
    {
        return ERROR_CODE_NULL_ID;
    }

    // Find parent item of inputted item
    for ( dwLoopIndex = 0; dwLoopIndex < vlpParentItem.size(); dwLoopIndex++ )
    {
        if ( std::find( vlpParentItem[dwLoopIndex]->m_vobjItems.begin(), vlpParentItem[dwLoopIndex]->m_vobjItems.end(), lpobjInItem ) != 
            vlpParentItem[dwLoopIndex]->m_vobjItems.end())
        {
            lpParentItem = vlpParentItem[dwLoopIndex];
            // Fix PGRelief
            if ( lpParentItem == NULL )
            {
                continue;
            }
            break;
        }
        else
        {
            // Do nothing
        }
    }
    // Fix PGRelief
    if ( lpParentItem == NULL )
    {
         return ERROR_CODE_NULL_ID;
    }
    // Get all Tab item
    vlpChidItem = lpParentItem->m_vobjItems;

    // Visible selected tab and invisible previous tab
    dwLoopIndex = 0;
    for ( dwLoopIndex = 0; dwLoopIndex < vlpChidItem.size(); dwLoopIndex++ )
    {
        vlpParentTabItem.clear();
        vlpParentTabItem = SearchTagIDFunc(( vlpChidItem[dwLoopIndex]->m_sctProperty.sTagID + TAG_ID_TAB_PAGE_AREA ), lpobjInItem->m_sctProperty.eAreaType );

        if ( vlpChidItem[dwLoopIndex]->m_sctProperty.sTagID == lpobjInItem->m_sctProperty.sTagID )
        {
            vlpChidItem[dwLoopIndex]->m_sctProperty.dwLeft -= TAB_PADDING_LEFT;
            vlpChidItem[dwLoopIndex]->m_sctProperty.dwWidth += TAB_PADDING_LEFT;

            ChangeClassIDFunc( vlpChidItem[dwLoopIndex], DESIGN_SELECT );
            vlpChidItem[dwLoopIndex]->ItemUpdateState();

            if ( vlpParentTabItem.size() > 0 )
            {
                vlpParentTabItem[0]->UpdateVisibility( TRUE );
            }
            else
            {
                // Do nothing
            }
        }
        else
        {
            // hoangpq - if change <li> from 'on' to 'off' -> remove padding left: 5px
            if ( ( vlpChidItem[dwLoopIndex]->m_sctProperty.sTagName == "li" ) && 
                    ( vlpChidItem[dwLoopIndex]->m_sctProperty.sClass == "center_disp_tab_gsky_on" ) )
            {
                vlpChidItem[dwLoopIndex]->m_sctProperty.dwLeft += TAB_PADDING_LEFT;
                vlpChidItem[dwLoopIndex]->m_sctProperty.dwWidth -= TAB_PADDING_LEFT;
            }

            ChangeClassIDFunc( vlpChidItem[dwLoopIndex], DESIGN_NOT_SELECT );
            vlpChidItem[dwLoopIndex]->ItemUpdateState();

            if ( vlpParentTabItem.size() > 0 )
            {
                vlpParentTabItem[0]->UpdateVisibility( FALSE );
            }
            else
            {
                // Do nothing
            }
        }
        
    }

    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SearchTagNameFunc
//
//�@�\�@�@��@�F  Search Item in specific area following tag name
//
//�@�T�@�@�v�@�F  Search Item in specific area following tag name
//
//�@�߁@��@�l�F  Vector item
//
//�@���@�@���@�F  string sInTagName       (I)       Tag name string
//                AREA_ENUM eInAreaType   (I)       Area type
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LiemTT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
vector<CItem*> CGuiViewDlg::SearchTagNameFunc( 
                            const    string &sInTagName, 
                                AREA_ENUM eInAreaType )
{
    // Initialize
    vector<CItem*>               vlpItem;  // Vector of Items
    DWORD dwIndex = 0;

    vlpItem.clear();
 
    for ( dwIndex = 0; dwIndex < m_vCurAreas.size(); dwIndex++ )
    {
        if (( eInAreaType != E_AREA_NULL) &&
            ( m_vCurAreas[dwIndex]->m_sctAreaInfo.eAreaType != eInAreaType ) )
        {
            continue;
        } 
        else
        {
            // Do nothing
        }
        
        m_vCurAreas[dwIndex]->GetItemsByTagName( sInTagName, vlpItem );
    }
    return vlpItem;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SearchEkiButtonIDFunc
//
//�@�\�@�@��@�F  Search Eki button by tag ID
//
//�@�T�@�@�v�@�F  Search Eki button by tag ID
//
//�@�߁@��@�l�F  vector of eki button items
//
//�@���@�@���@�F  string      sInSerchObject         Object to search in
//                string      sInStationId           Station ID
//                string      sInGroupType           Search tag name
//                AREA_ENUM   eInAreaType            Area type
//                string      sInSerchId             Search ID
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LiemTT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
vector<CItem*> CGuiViewDlg::SearchEkiButtonIDFunc(
                           const     string &sInSerchObject, 
                           const     string &sInStationId, 
                           const     string &sInGroupType, 
                                     AREA_ENUM eInAreaType, 
                           const    string  &sInSerchId)
{
    // Initilize
    vector<CItem*>               vlpItem;  // Vector of Items
    DWORD dwIndex = 0;

    vlpItem.clear();

    for ( dwIndex = 0; dwIndex < m_vCurAreas.size(); dwIndex++ )
    {
        if ( ( eInAreaType != E_AREA_NULL ) &&
            ( m_vCurAreas[dwIndex]->m_sctAreaInfo.eAreaType != eInAreaType ) )
        {
            continue;
        }
        else
        {
            // Do nothing
        }

        m_vCurAreas[dwIndex]->GetBtnByEkiID( vlpItem, sInStationId, sInGroupType );
    }
    return vlpItem;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  JudgeMinInputLimitFunc
//
//�@�\�@�@��@�F  Judge size of input item is valid or not
//
//�@�T�@�@�v�@�F  Judge size of input item is valid or not
//
//�@�߁@��@�l�F  Judgement result
//
//�@���@�@���@�F  string sInInput       (I)       Input string 
//                LONG lInputLimit      (I)       Min Input limit
//                LONG lMaxLength       (I)       Max length of string
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LiemTT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::JudgeMinInputLimitFunc( 
               const  string &sInInput, 
                      LONG    lInputLimit, 
                      LONG    lMaxLength )
{
    if ( lInputLimit == INPUT_LENGTH_NASHI_MODE )
    {
        return INPUT_LIMIT_OK;
    } 
    else
    {
        // Do nothing
    }

    if ( INPUT_LENGTH_EMPTY_OR_ALL == lInputLimit ) 
    {
        if (( LONG )GetSize( sInInput ) == lMaxLength )
        {
            return INPUT_LIMIT_OK;
        }
        else if ( sInInput.size() == 0 )
        {
            return INPUT_LIMIT_STR_NULL;
        }
        else
        {
            return INPUT_LIMIT_ERROR;
        }
         
    }
    else 
    {
        if ( lInputLimit <= ( LONG )GetSize( sInInput )) 
        {
            if (( lInputLimit      == 0 ) &&
                ( sInInput.size( ) == 0 ))
            {
                return INPUT_LIMIT_STR_NULL;
            }
            else
            {
                // Do nothing
            }
            
        }
        else 
        {
            return INPUT_LIMIT_ERROR;
        }
    }
    return INPUT_LIMIT_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  JudgeAreaEnbledFunc
//
//�@�\�@�@��@�F  Judge the specific area is enable or not
//
//�@�T�@�@�v�@�F  Judge the specific area is enable or not
//
//�@�߁@��@�l�F  TRUE: enable/False: disable
//
//�@���@�@���@�F  AREA_ENUM eAreaType       (I)       Area type
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LiemTT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CGuiViewDlg::JudgeAreaEnbledFunc( AREA_ENUM eAreaType )
{
    CArea* lpArea = NULL;
    lpArea = GetArea( eAreaType );
    if ( lpArea == NULL )
    {
        return FALSE;
    } 
    else 
    {
        // Do nothing
    } 
    return lpArea->IsEnable();
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  GetArea
//
//�@�\�@�@��@�F  Get current area
//
//�@�T�@�@�v�@�F  Get current area
//
//�@�߁@��@�l�F  Area pointer
//
//�@���@�@���@�F  AREA_ENUM eAreaType       (I)       Area type
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LiemTT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
CArea* CGuiViewDlg::GetArea( AREA_ENUM eAreaType )
{
    DWORD lpAreaIdx = GetAreaIndex( eAreaType );
    if (( m_vCurAreas[lpAreaIdx] != NULL ) &&
        ( m_vCurAreas[lpAreaIdx]->m_sctAreaInfo.eAreaType == eAreaType ) )
    {
        return m_vCurAreas[lpAreaIdx];
    } 
    else {} // Do nothing
    return NULL;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  JudgeInputTagFunc
//
//�@�\�@�@��@�F  Check data of input tag is valid or not
//
//�@�T�@�@�v�@�F  Check data of input tag is valid or not
//
//�@�߁@��@�l�F  TRUE: valid/FALSE: invalid
//
//�@���@�@���@�F  NA
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LiemTT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CGuiViewDlg::JudgeInputTagFunc()
{
    string          sMinute;
    string          strYear;
    LONG            lMaxLength;
    string          strCheckCharacter;
    CItem*          lpUpdateItem;
    string          strFormat;
    DWORD           dwIndex         = 0;
    LONG            lJudgeInput     = 0;
    BOOL            bJudgeResult    = FALSE;
    string          sLimit;
    CTime           objNowDate      = CTime::GetCurrentTime( );
    DWORD           dwTableLength;
    SCT_DATE        sctDate;
    string          sHour;
    LONG            lRet            = GUI_RET_OK;
    BOOL            bCheck          = FALSE;
    LONG            lFuncResult     = GUI_RET_NG;   // Error code of internal function

    if ( gclInputItemTag == NULL )
    {
        return FALSE;
    } 
    else 
    {
        // Do nothing
    } 
    

    SCT_ITEM_INFO& sctItemProperty = gclInputItemTag->m_sctProperty;

    if ( gclInputItemTag->IsNoChild())
    {
        lpUpdateItem = gclInputItemTag;
    }
    else
    {
        if ( gclInputItemTag->m_vobjItems.size( ) != 0 )
        {
            lpUpdateItem = FindItemByTagID( TAG_ID_NAME_SET_CHAR_SPAN, gclInputItemTag->m_vobjItems );
            // If not found any items
            if ( lpUpdateItem == NULL )
            {
                return FALSE;
            }
            else
            {
                // Do nothing
            }
        }
        else
        {
            return FALSE;
        }
    }

    strFormat = gsctInputFormat.sInputGuide;

    if ((( GetSize( gsctInputFormat.sGreap ) != 0 ) || ( gsctInputFormat.sGreap != NOT_SET_STR )) && 
        ( INPUT_LENGTH_EMPTY_OR_ALL == sctItemProperty.lMinLen ))
    {
        dwTableLength = ARRAY_LENGTH( Format_Table );

        for ( dwIndex = 0; dwIndex < dwTableLength; dwIndex++ )
        {
            if ( Format_Table[dwIndex].sFormatName == gsctInputFormat.sFormatName )
            {
                strFormat = Format_Table[dwIndex].sInputGuide;
                break;
            } 
            else 
            {
                // Do nothing
            } 
        }
    } 
    else 
    {
        // Do nothing
    } 

    if ( gsctInputFormat.bZeroSupp == TRUE )
    {
        strFormat = SubStr( gsctInputFormat.sInputGuide, GetSize( gsctInputFormat.sInputGuide ) - GetSize( lpUpdateItem->m_sctProperty.sText ));
    } 
    else 
    {
        // Do nothing
    }

    ExcerptNotFormatFunc( strFormat, lpUpdateItem->innerText(), -1, strCheckCharacter, gsctInputFormat.bLeftJustify );
    
    lJudgeInput = JudgeMinInputLimitFunc(
        strCheckCharacter,
        sctItemProperty.lMinLen,
        sctItemProperty.lMaxLen );

    switch ( lJudgeInput ) 
    {
    case INPUT_LIMIT_ERROR: // ���͐�������F�G���[.
        InputErrorNoticeFunc( gclInputItemTag->m_sctProperty.sTagID, INPUT_ERR_CODE_LIMIT, gclInputItemTag->m_sctProperty.lMinLen, gclInputItemTag->m_sctProperty.lMaxLen );
        return FALSE;
    case INPUT_LIMIT_STR_NULL: // ���͐�������F������.
        return TRUE;
    case INPUT_LIMIT_OK: // ���͐�������F����.
    default:
        break;
    }

    lMaxLength = sctItemProperty.lMaxLen;

    if ( INPUT_LENGTH_NASHI_MODE == lMaxLength ) {
        // �����̏ꍇ�́A�ő���͐�����ݒ肷��.
        lMaxLength = INPUT_MAX_LENGTH_LIMIT;
    }
    else 
    {
        // Do nothing
    }

    sLimit = sctItemProperty.sLimit;

    if ( sLimit == INPUT_CHECK_DATE_VALIDITY )
    {
        ExcerptNotFormatFunc( strFormat, lpUpdateItem->innerText(), -1, strCheckCharacter, gsctInputFormat.bLeftJustify );

        if ( INPUT_LENGTH_EMPTY_OR_ALL == sctItemProperty.lMinLen ) 
        {
            bJudgeResult = TRUE;
            if ( strCheckCharacter.size() ==  0 ) {
                bCheck = TRUE;
            }
            else
            {
                // Do nothing
            } 
        }
        else 
        {
            // ���͍��ڂɖ����͂��Ȃ����`�F�b�N����.
            bJudgeResult = TRUE;
        }
        if ( bCheck == FALSE )   // Fix follows TSBJ review
        {
            std::regex sSpace( CHARACTER_SPACE );
            strCheckCharacter = std::regex_replace( strCheckCharacter, sSpace, ( string )"�O" );

            // �S�ē��͍ς݂������ꍇ�́A���t�`�F�b�N���s��.
            if ( bJudgeResult == TRUE ) 
            {
                if ( gsctInputFormat.sFormatName == FMT_NAME_DATE_YEAR_TWO_DGITS )
                {
                    strCheckCharacter = Calendar_Year_Table[( sizeof(Calendar_Year_Table) / sizeof( SCT_CAL_YEAR_TABLE )) - 1].sEraName + strCheckCharacter;
                    ConvAnnoDominiOrJapaneseCalendarFunc( strCheckCharacter, CONV_YEAR_ANNO_DOMINI, strCheckCharacter );
                }
                else if ( gsctInputFormat.sFormatName == FMT_NAME_DATE_YEAR_TWO_DGITS_JP )
                {
                    strYear = to_string(( LONGLONG ) objNowDate.GetYear());
                    strCheckCharacter = SubStr( strYear, 0, 2 ) + strCheckCharacter;
                }
                else if ( gsctInputFormat.sFormatName == FMT_NAME_DATE_MONTH_DAY )
                {
                    strYear = to_string(( LONGLONG ) objNowDate.GetYear());
                    strCheckCharacter = strYear + strCheckCharacter;
                }
                else if ( gsctInputFormat.sFormatName == FMT_NAME_DATE_YEAR_FOUR_DGITS )
                {
                    // Do nothing
                }
                else 
                {
                    // Do nothing
                } 
                // ���ݓ��̔��茋�ʂ��i�[.
                ConvertStr2DateSct( strCheckCharacter, sctDate );
                bJudgeResult = JudgeDateValidityFunc( sctDate, &sctDate, lFuncResult );
            }
            else
            {
                // Do nothing
            }

            // Send input error message
            if ( bJudgeResult == FALSE ) 
            {
                InputErrorNoticeFunc( gclInputItemTag->m_sctProperty.sTagID, lFuncResult, gclInputItemTag->m_sctProperty.lMinLen, gclInputItemTag->m_sctProperty.lMaxLen );
            }
        }
    } 
    else if ( sLimit == INPUT_CHECK_TIME_VALIDITY )
    {
        ExcerptNotFormatFunc( strFormat, lpUpdateItem->innerText(), -1, strCheckCharacter, gsctInputFormat.bLeftJustify );

        if ( INPUT_LENGTH_EMPTY_OR_ALL == sctItemProperty.lMinLen )
        {
            bJudgeResult = TRUE;
            if ( strCheckCharacter.size() == 0 ) 
            {
                //bJudgeResult = FALSE;
                bCheck = TRUE;      // Fix follow TSBJ review
            }
            else 
            {
                // Do nothing
            } 
        }
        else
        {
            // ���͍��ڂɖ����͂��Ȃ����`�F�b�N����.
            bJudgeResult = TRUE;
        }

        if ( bCheck == FALSE ) // Fix follow TSBJ review
        {
            std::regex sSpace( CHARACTER_SPACE );
            strCheckCharacter = std::regex_replace( strCheckCharacter, sSpace, ( string )"�O" );

            if ( JudgeNumberFunc( strCheckCharacter ) == ERROR_CODE_NOT_NUMBER )
            {
                InputErrorNoticeFunc( gclInputItemTag->m_sctProperty.sTagID, INPUT_ERR_CODE_NUMBER, gclInputItemTag->m_sctProperty.lMinLen, gclInputItemTag->m_sctProperty.lMaxLen );
                bJudgeResult = FALSE;
            }
            else
            {
                // �S�ē��͍ς݂������ꍇ�́A���t�`�F�b�N���s��.
                if ( bJudgeResult == TRUE )
                {
                    // ���͎����̎擾.
                    ConvFullHalNumberFunc( SubStr( strCheckCharacter, 0, 2 ), true, sHour );

                    ConvFullHalNumberFunc( SubStr( strCheckCharacter, 2 ), true, sMinute );
                    // �����̊m�F

                    // ���t���Ó�(���t�I�u�W�F�N�g�̔N�����ƈ����̔N��������v���Ă���)���`�F�b�N����.
                    if ( atol( sHour.c_str()) > VALUE_MAX_HOUR || atol( sMinute.c_str( )) > VALUE_MAX_MINUTE )
                    {
                        bJudgeResult = FALSE;
                    }
                    else 
                    {
                        bJudgeResult = TRUE;
                    }
                }
                else
                {
                    // Do nothing
                }

                if (  bJudgeResult == FALSE )
                {
                    InputErrorNoticeFunc( gclInputItemTag->m_sctProperty.sTagID, INPUT_ERR_CODE_TIME, gclInputItemTag->m_sctProperty.lMinLen, gclInputItemTag->m_sctProperty.lMaxLen );
                }
                else
                {
                    // Do nothing
                }
            }
        }
        
    } 
    else if ( sLimit == INPUT_CHECK_NUM_CHECK )
    {
        ExcerptNotFormatFunc( strFormat, lpUpdateItem->innerText(), -1, strCheckCharacter, gsctInputFormat.bLeftJustify );

        std::regex sSpace( CHARACTER_SPACE );
        strCheckCharacter = std::regex_replace( strCheckCharacter, sSpace, ( string )"�O" );
        if ( ERROR_CODE_NOT_NUMBER == JudgeNumberFunc( strCheckCharacter )) 
        {
            bJudgeResult = FALSE;
        }
        else 
        {
            bJudgeResult = TRUE;
        }

        if ( bJudgeResult == FALSE )
        {
            InputErrorNoticeFunc( gclInputItemTag->m_sctProperty.sTagID, INPUT_ERR_CODE_NUMBER, gclInputItemTag->m_sctProperty.lMinLen, gclInputItemTag->m_sctProperty.lMaxLen );
        }
        else
        {
            // Do nothing
        }
    } 
    else 
    {
        bJudgeResult = TRUE;
    }
    
    if ( bCheck == TRUE )
    {
         bJudgeResult = TRUE;
    }
    else
    {
        // Do nothing
    }

    // Return when judge result is FALSE
    if ( bJudgeResult == FALSE )
    {
        return FALSE;
    } 
    else 
    {
        // Do nothing
    } 
    
    if ( gdwFlgDispZeroPadding == ZERO_PADDING_AVAILABLE_NULL )
    {
        if ( lpUpdateItem->innerText().size() == 0 ) 
        {
            bJudgeResult = TRUE;
        }
        else 
        {
            // Do nothing
        } 
    } 
    else if ( gdwFlgDispZeroPadding == ZERO_PADDING_AVAILABLE )
    {
        lRet = ConvZeroPaddingFunc( lpUpdateItem->innerText(), ZERO_PADDING_AVAILABLE, lpUpdateItem->m_sctProperty.lMaxLen, strCheckCharacter );
        // �G���[���������Ȃ������ꍇ�́A�ϊ����e�ŕ\�����e��ύX����.
        if ( lRet == ERROR_CODE_NOT_NUMBER ) 
        {
            InputErrorNoticeFunc( gclInputItemTag->m_sctProperty.sTagID, INPUT_ERR_CODE_NUMBER, gclInputItemTag->m_sctProperty.lMinLen, gclInputItemTag->m_sctProperty.lMaxLen );
            bJudgeResult = FALSE;
        }
        else 
        {
            ConvFullHalNumberFunc( strCheckCharacter, false, strCheckCharacter );
            // �ϊ����e��\�����e�ɐݒ肷��.
            lpUpdateItem->innerText() = strCheckCharacter;
            lpUpdateItem->ItemUpdateState();
            bJudgeResult = TRUE;
        }
    } 
    else
    {
        bJudgeResult = TRUE;
    } 

    return bJudgeResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  JudgeInputTagAllEnteredFunc
//
//�@�\�@�@��@�F  Check characters are inputted to all of the input position of the input guide.
//
//�@�T�@�@�v�@�F  Check characters are inputted to all of the input position of the input guide.
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  string sText       (I)       Text string
//                string strFormat   (I)       Format string
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LiemTT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CGuiViewDlg::JudgeInputTagAllEnteredFunc( const string &sText, const string &strFormat )
{
    DWORD   dwIndex = 0;  // Index counter
    BOOL    bRes    = TRUE;

    if ( sText == NOT_SET_STR )
    {
        return FALSE;
    }

    if ( strFormat == NOT_SET_STR )
    {
        return FALSE;
    }

    for ( dwIndex = 0; dwIndex < GetSize( strFormat ); ++dwIndex )
    {
        if ( strncmp( &strFormat.at( dwIndex ), FORMAT_INPUT_ITEM, sizeof( FORMAT_INPUT_ITEM )) != 0 )
        {
            continue;
        }
        else 
        {
            // Do nothing
        } 
        
        if ( SubStr( sText, dwIndex ) != CHARACTER_SPACE )
        {
            bRes = FALSE;
            break;
        }
        else 
        {
            // Do nothing
        } 
    }
    return bRes;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  JudgeInputTagBirthOfDateFunc
//
//�@�\�@�@��@�F  Judge data of the input item is date of birth or not
//
//�@�T�@�@�v�@�F  Judge data of the input item is date of birth or not
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  BOOL bInErrNoticeFlg       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/18    (TSDV) LienTT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
string CGuiViewDlg::JudgeInputTagBirthOfDateFunc( BOOL bInErrNoticeFlg )
{
    string          strDisp             = "";
    string          sFormatError        = "";
    vector<CItem*>  vCItem;
    CItem*          lpcMonDayItem       = NULL;
    string          strCheckCharacter   = "";
    //BOOL            bJudgeRes           = GUI_VALUE_ZERO_LONG;
    LONG            lRes                = GUI_RET_OK;
    string          sReturn             = "";
    CItem*          lpUpdateItem        = NULL;
    LONG            lJudgeMinRes        = GUI_VALUE_ZERO_LONG;

    if ( gclInputItemTag == NULL )
    {
        return "null";
    }

    if ( gclInputItemTag->IsNoChild())
    {
        lpUpdateItem = gclInputItemTag;
    }
    else
    {
        if ( gclInputItemTag->m_vobjItems.size() != 0 )
        {
            lpUpdateItem = FindItemByTagID( TAG_ID_NAME_SET_CHAR_SPAN, gclInputItemTag->m_vobjItems );
            // If not found any items
            if ( lpUpdateItem == NULL )
            {
                if ( bInErrNoticeFlg == TRUE )
                {
                    InputErrorNoticeFunc( gclInputItemTag->m_sctProperty.sTagID, INPUT_ERR_CODE_LIMIT, gclInputItemTag->m_sctProperty.lMinLen, gclInputItemTag->m_sctProperty.lMaxLen );
                }
                else
                {
                    // Do nothing
                }
                return "null";
            }
            else
            {
                // Do nothing
            }
        }
        else
        {
            if ( bInErrNoticeFlg == TRUE )
            {
                InputErrorNoticeFunc( gclInputItemTag->m_sctProperty.sTagID, INPUT_ERR_CODE_LIMIT, gclInputItemTag->m_sctProperty.lMinLen, gclInputItemTag->m_sctProperty.lMaxLen );
            }
            else
            {
                // Do nothing
            }
            return "null";
        }
    }

    if ( gclInputItemTag->m_sctProperty.sTagID == TAG_ID_NAME_SEINEN_GAPPI )
    {
        vCItem.clear();
        lpUpdateItem->GetChildItemsByTagName( "span", vCItem );
        if ( vCItem.size() != 0 )
        {
            lpcMonDayItem = vCItem[0];
        } 
        else
        {
            if ( bInErrNoticeFlg == TRUE )
            {
                InputErrorNoticeFunc( gclInputItemTag->m_sctProperty.sTagID, INPUT_ERR_CODE_LIMIT, gclInputItemTag->m_sctProperty.lMinLen, gclInputItemTag->m_sctProperty.lMaxLen );
            }
            else
            {
                // Do nothing
            }
            return "null";
        }
    } 
    else
    {
        lpcMonDayItem = lpUpdateItem;
    }
    ExcerptNotFormatFunc( gsctInputFormat.sInputGuide, lpcMonDayItem->innerText(), -1, strCheckCharacter, gsctInputFormat.bLeftJustify );
    strCheckCharacter = gsctInputFormat.sEraName + strCheckCharacter;
    lJudgeMinRes = JudgeMinInputLimitFunc( strCheckCharacter, gclInputItemTag->minLength(), gclInputItemTag->maxLength());

    switch ( lJudgeMinRes ) 
    {
        case INPUT_LIMIT_ERROR: // ���͐�������F�G���[.
            if ( bInErrNoticeFlg == TRUE )
            {
                InputErrorNoticeFunc( gclInputItemTag->m_sctProperty.sTagID, INPUT_ERR_CODE_LIMIT, gclInputItemTag->m_sctProperty.lMinLen, gclInputItemTag->m_sctProperty.lMaxLen );
            }
            else
            {
                // Do nothing
            }
            return "null";

        case INPUT_LIMIT_STR_NULL: // ���͐�������F������.
            return "";

        case INPUT_LIMIT_OK: // ���͐�������F����.
        default:
        break;
    }

    std::regex sSpace( CHARACTER_SPACE );
    strCheckCharacter = std::regex_replace( strCheckCharacter, sSpace, ( string )"�O" );

    if ( gsctInputFormat.sGreap == CONV_YEAR_ANNO_DOMINI )
    {
        lRes = ConvAnnoDominiOrJapaneseCalendarFunc( strCheckCharacter, gsctInputFormat.sGreap, strCheckCharacter );
        if ( lRes == ERROR_CODE_CONV_ANNO_JAPANESE )
        {
            if ( bInErrNoticeFlg == TRUE )
            {
                InputErrorNoticeFunc( gclInputItemTag->m_sctProperty.sTagID, INPUT_ERR_CODE_DATE, gclInputItemTag->m_sctProperty.lMinLen, gclInputItemTag->m_sctProperty.lMaxLen );
            }
            else
            {
                // Do nothing
            }
            return "null";
        } 
        else 
        {
            // Do nothing
        } 
        
    } 
    else 
    {
        // Do nothing
    } 
    
    lRes = ConvTagIdDateFormatFunc(
                gclInputItemTag->id(),
                strCheckCharacter,
                CONVMODE_INPUT,
                gclInputItemTag->sClass(),
                strDisp,
                sReturn );

    if ( lRes == ERROR_CODE_NOT_DATE )
    {
        if ( bInErrNoticeFlg == TRUE )
        {
            InputErrorNoticeFunc( gclInputItemTag->m_sctProperty.sTagID, INPUT_ERR_CODE_DATE, gclInputItemTag->m_sctProperty.lMinLen, gclInputItemTag->m_sctProperty.lMaxLen );
        }
        else
        {
            // Do nothing
        }
        return "null";
    }
    else 
    {
        // Do nothing
    } 
    if ( strDisp.find("<div class='nen'>") != string::npos )
    {
        // Create div area
        CreateSeinenGappi( lpUpdateItem, strDisp );
    }
    else
    {
        lpUpdateItem->innerText( ) = strDisp;
    }
    lpUpdateItem->ItemUpdateState();
 
    return sReturn;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ConvertStr2DateSct
//
//�@�\�@�@��@�F  Convert date string to date structure
//
//�@�T�@�@�v�@�F  Convert date string to date structure
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  string sInData       (I)       Date String
//                SCT_DATE &sctInDate  (O)       Date structure
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
void CGuiViewDlg::ConvertStr2DateSct( 
               const  string   &sInData, 
                      SCT_DATE &sctInDate )
{
    LONG            lTemp  = GUI_VALUE_ZERO_LONG;
    ZeroMemory( &sctInDate, sizeof(sctInDate));

    string sTemp = "";
    ConvFullHalNumberFunc( sInData, true, sTemp );
    if ( IsHalfWidthNumberString( sTemp ) == FALSE )
    {
        return;
    } else {} // Do nothing
// Start TrungLV 20150502
    // Get yymmdd
    if ( GetSize( sInData ) == 8 )
    {
        lTemp   = atol( sTemp.substr( 0, 4 ).c_str() );
        if ( lTemp >= 0 )
        {
            sctInDate.wYear   = ( WORD )lTemp;
        }

        lTemp = atol( sTemp.substr( 4, 2 ).c_str( ) );
        if ( lTemp >= 0 )
        {
            sctInDate.byMonth = ( BYTE )lTemp;
        }

        lTemp = atol( sTemp.substr( 6, 2 ).c_str( ) );
        if ( lTemp >= 0 )
        {
            sctInDate.byDay   = ( BYTE )lTemp;
        }
    }
    // Get full yyyymmddhhmmss
    if ( GetSize( sInData ) == 14 )
    {
        lTemp = atol( sTemp.substr( 0, 4 ).c_str() );
        if ( lTemp >= 0 )
        {
            sctInDate.wYear    = ( WORD )lTemp;
        }

        lTemp = atol( sTemp.substr( 4, 2 ).c_str( ) );
        if ( lTemp >= 0 )
        {
            sctInDate.byMonth  = ( BYTE )lTemp;
        }

        lTemp = atol( sTemp.substr( 6, 2 ).c_str( ) );
        if ( lTemp >= 0 )
        {
            sctInDate.byDay    = ( BYTE )lTemp;
        }

        lTemp = atol( sTemp.substr( 8, 2 ).c_str() );
        if ( lTemp >= 0 )
        {
            sctInDate.wHour    = ( WORD )lTemp;
        }

        lTemp = atol( sTemp.substr( 10, 2 ).c_str() );
        if ( lTemp >= 0 )
        {
            sctInDate.wMinutes = ( WORD )lTemp;
        }

        lTemp = atol( sTemp.substr( 12, 2 ).c_str() );
        if ( lTemp >= 0 )
        {
            sctInDate.wSecond  = ( WORD )lTemp;
        }
    }

        // Get full yyyymmddhhmmss
    if ( GetSize( sInData ) == 12 )
    {
        lTemp = atol( sTemp.substr( 0, 4 ).c_str() );
        if ( lTemp >= 0 )
        {
            sctInDate.wYear    = ( WORD )lTemp;
        }

        lTemp = atol( sTemp.substr( 4, 2 ).c_str( ) );
        if ( lTemp >= 0 )
        {
            sctInDate.byMonth  = ( BYTE )lTemp;
        }

        lTemp = atol( sTemp.substr( 6, 2 ).c_str( ) );
        if ( lTemp >= 0 )
        {
            sctInDate.byDay    = ( BYTE )lTemp;
        }

        lTemp = atol( sTemp.substr( 8, 2 ).c_str() );
        if ( lTemp >= 0 )
        {
            sctInDate.wHour    = ( WORD )lTemp;
        }

         lTemp = atol( sTemp.substr( 10, 2 ).c_str() );
        if ( lTemp >= 0 )
        {
            sctInDate.wMinutes = ( WORD )lTemp;
        }
    }
// End TrungLV 20150502
    return;
}

// And generating a cursor for birth input items, the process to be displayed.
/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  CursorAddBirthDateFmtFunc
//
//�@�\�@�@��@�F  Set icon and position of cursor when input date of birth
//
//�@�T�@�@�v�@�F  Set icon and position of cursor when input date of birth
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  BYTE byInInitDisp       (I)       Item initialization instruction
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::CursorAddBirthDateFmtFunc( BYTE byInInitDisp )
{
    LONG              lRet = GUI_RET_OK;
    CItem*            lpobjUpdateItem   = NULL;
    vector<CItem*>    vlpobjItems;
    CItem*            lpobjChildItem    = NULL;
    string            sYear             = "";
    string            sInputDisp        = "";
    DWORD             dwIndex           = GUI_VALUE_ZERO_DWORD;
    wstring           wInputGuide       = L"";
    wstring           wFormatInputItem  = L"";

    if ( gclInputItemTag == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    else
    {
        // Do nothing
    }

    // Check global cursor image item
    if ( IsWindow( m_cCursor.m_hWnd ) == TRUE)
    {
        // Do nothing
    }
    else
    {
        lRet = CursorAddFunc( byInInitDisp );
        if ( lRet != GUI_RET_OK )
        {
            return lRet;
        }
    }
    // item is parent
    if ( gclInputItemTag->m_sctProperty.bParent == TRUE )
    {
        lpobjUpdateItem = gclInputItemTag;
    }
    // item is childen
    else
    {
        lpobjUpdateItem = FindItemByTagID ( TAG_ID_NAME_SET_CHAR_SPAN, gclInputItemTag->m_vobjItems );
        if ( lpobjUpdateItem == NULL )
        {
            return ERROR_CODE_NULL;
        }
        else
        {
            // Do nothing
        }
    }

    //I get the update tag if date of birth of the (two lines year).
    if ( gclInputItemTag->m_sctProperty.sTagID == TAG_ID_NAME_SEINEN_GAPPI )
    {
        vlpobjItems = FindItemsByTagName( "div", lpobjUpdateItem->m_vobjItems );

        if ( vlpobjItems.size() == 0 )
        {
            return ERROR_CODE_NULL_ID;
        }
        else
        {
            lpobjChildItem = vlpobjItems[0];
            sYear          = lpobjChildItem->m_sctProperty.sText;

            std::size_t sizeFound = sYear.find( "<" );
            if ( sizeFound !=std::string::npos )
            {
                sYear  = sYear.substr( 0, sizeFound );
            }
            else
            {
                // Do nothing
            }
            lpobjChildItem->m_sctProperty.sText = "";

            vlpobjItems.clear();
            vlpobjItems = FindItemsByTagName( TAG_NAME_SPAN, lpobjUpdateItem->m_vobjItems );
            if ( vlpobjItems.size() == 0 )
            {
                return ERROR_CODE_NULL_ID;
            }
            else
            {
                lpobjChildItem = vlpobjItems[0];
            }
        
        }
    }
    else
    {
        lpobjChildItem = lpobjUpdateItem;
    }

    // Change height of cursor
    m_cCursor.m_dwHeight = lpobjChildItem->m_sctProperty.dwFontSize + CURSOR_IMAGE_MARGIN_CHARACTER * 4;

    switch ( ( WORD )byInInitDisp )
    {
    case INPUT_INIT_SHIJI_FIRST_CLEAR:
        gbInputItemFirstInitializationFlg = TRUE;
        // LiemTT Change 20150427
        //break;
        // End change
    case INPUT_INIT_SHIJI_NOT_CHANGE:
        sInputDisp = sYear + lpobjChildItem->m_sctProperty.sText;
        break;
    case INPUT_INIT_SHIJI_CLEAR:
        sInputDisp = gsctInputFormat.sInitDisp;
        break;
    default:
        return ERROR_CODE_NOT_RANGE;
    }

    // Change text
    lpobjChildItem->m_sctProperty.sText = sInputDisp;
    lpobjChildItem->ItemUpdateState();

    // Early, format for the year
    gsctInputFormat.sTagId = Date_Of_Birth_Fomat_Table[0].sTagId;
    gsctInputFormat.sGreap = Date_Of_Birth_Fomat_Table[0].sGreap;
    gsctInputFormat.sEraName = Date_Of_Birth_Fomat_Table[0].sEraName;

    //If the actual data is on, always for the Japanese calendar display, change the format for the Japanese calendar
    if ( SubStr( sInputDisp, 0, 1 ) == CHARACTER_SPACE )
    {
        // Do nothing
    }
    else
    {
        for ( dwIndex = 1; dwIndex < DATE_OF_BIRTH_FORMAT_TABLE_SIZE; dwIndex++ )
        {
            if ( SubStr( sInputDisp, 0, 2 ) == SubStr( Date_Of_Birth_Fomat_Table[dwIndex].sInputGuide, 0, 2 ) )
            {
                gsctInputFormat.sTagId      = Date_Of_Birth_Fomat_Table[0].sTagId;
                gsctInputFormat.sGreap      = Date_Of_Birth_Fomat_Table[0].sGreap;
                gsctInputFormat.sInputGuide = Date_Of_Birth_Fomat_Table[0].sInputGuide;
                wInputGuide = StringToWChar( gsctInputFormat.sInputGuide );
                wFormatInputItem    = StringToWChar( FORMAT_INPUT_ITEM );
                gsctInputFormat.lRangeStart = ( LONG )wInputGuide.find( wFormatInputItem );
                gsctInputFormat.lRangeEnd   = ( LONG )wInputGuide.rfind( wFormatInputItem ) + 1;
                gsctInputFormat.sEraName    = Date_Of_Birth_Fomat_Table[0].sEraName;
                break;
            }
            else
            {
                // Do nothing
            }
        }
    }
    // set the display position of the cursor.
    glRelativeCurPos = gsctInputFormat.lRangeStart;

    //Set the display position of the cursor
    if ( byInInitDisp == INPUT_INIT_SHIJI_NOT_CHANGE )
    {
        //If the item initialization presence or absence of directly setting the cursor position than the display contents
        glRelativeCurPos = SerchInputGuidFunc ( sInputDisp, gsctInputFormat.sInputGuide, gsctInputFormat.bLeftJustify, gsctInputFormat.lRangeEnd );
    }
    else
    {
        SetCursorRelativePosition( gsctInputFormat.bLeftJustify );
    }
    // Movement of the cursor (move the number of 0, for which you want to move to the display position that has been set)
    lRet = CursorMoveFunc( 0 );

    return lRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SettingDisplayCalendarFunc
//
//�@�\�@�@��@�F  Setting display when change calendar
//
//�@�T�@�@�v�@�F  Setting display when change calendar
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::SettingDisplayCalendarFunc( CItem* lpobjInItem )
{
    LONG            lRet                    = GUI_RET_OK;
    WORD            wDispYear               = GUI_VALUE_ZERO_WORD;
    BYTE            byDispMonth             = GUI_VALUE_ZERO_BYTE;
    CArea*          lpobjCurrentArea        = NULL;

    if ( lpobjInItem == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    else
    {
        // Do nothing
    }
    // change the month to be displayed by the tag ID.
    if ( lpobjInItem->m_sctProperty.sTagID == TAG_ID_NAME_MONTH_PREVIOUS )
    {
        wDispYear   = gsctDispDate.wYear;
        byDispMonth = gsctDispDate.byMonth - 1;
    }
    else if ( lpobjInItem->m_sctProperty.sTagID == TAG_ID_NAME_MONTH_THIS )
    {
        wDispYear   = gsctBasicDate.wYear;
        byDispMonth = gsctBasicDate.byMonth;
    } 
    else if ( lpobjInItem->m_sctProperty.sTagID == TAG_ID_NAME_MONTH_NEXT )
    {
        wDispYear   = gsctDispDate.wYear;
        byDispMonth = gsctDispDate.byMonth + 1;
    }
    else
    {
        return ERROR_CODE_NOT_RANGE;
    }

    // change the date by a month
    switch ( byDispMonth )
    {
        case 0:
            wDispYear   = wDispYear - 1;
            byDispMonth = 12;
            break;
        case 13:
            wDispYear   = wDispYear + 1;
            byDispMonth = 1;
            break;

        default:
            // Do nothing
            break;
    }

    lpobjCurrentArea = GetCurrentAreaByAreaType ( lpobjInItem->m_sctProperty.eAreaType );
    if ( lpobjCurrentArea == NULL )
    {
         return ERROR_CODE_NULL;
    }
    else
    {
        // Do nothing
    }
    lRet = SettingCalendarFunc( lpobjCurrentArea->m_vItemList, wDispYear, byDispMonth );

    return lRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeDispSchoolYearFunc
//
//�@�\�@�@��@�F  Change display of school year
//
//�@�T�@�@�v�@�F  Change display of school year
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LanLTM    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ChangeDispSchoolYearFunc( CItem* lpInItem )
{
    // Initialize
    LONG            lProcResult         = GUI_RET_NG;           // Return value
    CItem*          lpObjUpdateTag      = NULL;                 // Updated tag item
    DWORD           dwLoopIndex         = GUI_VALUE_ZERO_DWORD; // Loop index
    string          sTempFromat         = "";                   // Temp format string
    wstring         wInputGuide         = L"";                  // Input Guide full string
    wstring         wFormatInputItem    = L"";                  // Format Input full string


    // Check parameter
    if ( lpInItem == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    else
    {
        // Do nothing
    }

    if ( gclInputItemTag == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    else
    {
        // Do nothing
    }

    if ( IsWindow( m_cCursor.m_hWnd ) == FALSE )
    {
        return ERROR_CODE_NOT_EXIST_IMAGE;
    }
    else
    {
        // Do nothing
    }

    // In the case of grade button tag ID is currently selected, end the process
    if ( lpInItem->m_sctProperty.sTagID == gclInputItemTag->m_sctProperty.sTagID )
    {
        return GUI_RET_OK;
    }
    else
    {
        // Do nothing
    }

    // Get updates tag ID
    if ( gclInputItemTag->m_sctProperty.bParent == TRUE )
    // If item is parent
    {
        lpObjUpdateTag = gclInputItemTag;
    }
    else
    {
        if ( gclInputItemTag->m_vobjItems.size() == 0 )
        {
            return ERROR_CODE_NULL;
        }
        else
        {
            lpObjUpdateTag = FindItemByTagID( TAG_ID_NAME_SET_CHAR_SPAN, gclInputItemTag->m_vobjItems );

            if ( lpObjUpdateTag == NULL )
            {
                return ERROR_CODE_NULL;
            }
            else
            {
                // Do nothing
            }
        }

    }

    // 
    for ( dwLoopIndex = 0; dwLoopIndex < SUB_FORMAT_TABLE; dwLoopIndex++ )
    {
        if ( lpInItem->m_sctProperty.sTagID == Sub_Fomat_Table[dwLoopIndex].sTagId )
        {
            sTempFromat                 = gsctInputFormat.sGreap;
            gsctInputFormat.sTagId      = Sub_Fomat_Table[dwLoopIndex].sTagId;
            gsctInputFormat.sGreap      = Sub_Fomat_Table[dwLoopIndex].sGreap;
            gsctInputFormat.sInputGuide = Sub_Fomat_Table[dwLoopIndex].sInputGuide;
            wInputGuide                 = StringToWChar( gsctInputFormat.sInputGuide );
            wFormatInputItem            = StringToWChar( FORMAT_INPUT_ITEM );
            gsctInputFormat.lRangeStart = ( LONG )wInputGuide.find( wFormatInputItem );
            gsctInputFormat.sInitDisp   = lpInItem->m_sctProperty.sValue + SubStr( gsctInputFormat.sInitDisp, GetSize( lpInItem->m_sctProperty.sValue ));
            

            //
            if ( Sub_Fomat_Table[dwLoopIndex].sGreap == sTempFromat )
            {
                lProcResult = GUI_RET_OK;
            }
            else
            {
                lProcResult = CursorAllDeleteCharacterFunc( lpObjUpdateTag ,false );
            }

            //
            lpObjUpdateTag->m_sctProperty.sText =  lpInItem->m_sctProperty.sValue + SubStr( lpObjUpdateTag->m_sctProperty.sText, GetSize( lpInItem->m_sctProperty.sValue ));
            
            lpObjUpdateTag->ItemUpdateState(); 
            break;
        }
        else
        {
            // Do nothing
        }
    }

    if ( lProcResult     != GUI_RET_OK )
    {
        if ( gsctInputFormat.sTagId == "" )
        {
            
            lProcResult = GUI_RET_OK;
        }
        else
        {
            // DO nothing
        }
    }
    else
    {
        // Do nothing
    }

    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SerchInputGuidFunc
//
//�@�\�@�@��@�F  Search Guidline for input item
//
//�@�T�@�@�v�@�F  Search Guidline for input item
//
//�@�߁@��@�l�F  Input count index
//
//�@���@�@���@�F  string sInputChar       (I)       Input string
//                string sInputGuide      (I)       Input guideline
//                BOOL   bLeftJustify     (I)       Judgement to align left or not
//                LONG   lRangeEnd        (I)       End of range
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::SerchInputGuidFunc ( 
                    const   string &sInputChar, 
                    const   string &sInputGuide, 
                            BOOL   bLeftJustify, 
                            LONG   lRangeEnd )
{
    // Initialize
    LONG    lInputCnt           = GUI_VALUE_ZERO_LONG;     // Input count
    LONG    dwIndex             = GUI_VALUE_ZERO_DWORD;     // Index counter
    wstring wInputGuide         = L"";
    wstring wFormatInputItem    = L"";

    // Check parameter
    if ( sInputChar == NOT_SET_STR )
    {
        return lInputCnt;
    }
    else
    {
        // Do nothing
    }

    if ( sInputGuide == NOT_SET_STR )
    {
        return lInputCnt;
    }
    else
    {
        // Do nothing
    }

    if ( sInputGuide == "" )
    {
        if ( bLeftJustify )
        {
            lInputCnt = ( LONG )GetSize( sInputChar );
        } 
        else
        {
            lInputCnt = lRangeEnd;
        } 
        
    } 
    else 
    {
        if ( bLeftJustify == TRUE )
        {
            wInputGuide         = StringToWChar( sInputGuide );
            wFormatInputItem    = StringToWChar( FORMAT_INPUT_ITEM );
            lInputCnt           = wInputGuide.find( wFormatInputItem );
            if ( lInputCnt == ( LONG ) string::npos )
            {
                return 0;
            } 
            else 
            {
                // Do nothing
            } 
            
            // TSDV-LanLTM-Fix bug position of cursor is wrong
            //if ( ( LONG ) GetSize( sInputChar ) < lInputCnt )
            if ( ( LONG ) GetSize( sInputChar ) <= lInputCnt )
            {
                return GetSize( sInputChar );
            } 
            else 
            {
                // Do nothing
            } 
            
            for ( dwIndex = lInputCnt; dwIndex < ( LONG ) GetSize( sInputGuide ); dwIndex++ )
            {
                // TSDV-LanLTM-Fix bug position of cursor is wrong
                //if ( strncmp( &sInputGuide.at( dwIndex ), FORMAT_INPUT_ITEM, sizeof( FORMAT_INPUT_ITEM ) ) == 0 )
                if ( SubStr( sInputGuide, ( LONG )dwIndex , 1 ) == FORMAT_INPUT_ITEM )
                {
                    if ( SubStr( sInputChar, ( LONG )dwIndex , 1 ) != CHARACTER_SPACE )
                    {
                        lInputCnt = dwIndex + 1;
                    } 
                    else 
                    {
                        // Do nothing
                    } 
                    
                } 
                else 
                {
                    // Do nothing
                } 
                
                if (( lRangeEnd             == dwIndex ) ||
                    ( ( LONG ) GetSize( sInputChar ) == dwIndex + 1 ))
                {
                    break;
                } 
                else 
                {
                    // Do nothing
                } 
            }
        } 
        else
        {
            lInputCnt = lRangeEnd;
        } 
    }
    return lInputCnt;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  JudgeErrorBreakFunc
//
//�@�\�@�@��@�F  Judge break or not when have error
//
//�@�T�@�@�v�@�F  Judge break or not when have error
//
//�@�߁@��@�l�F  BOOL
//
//�@���@�@���@�F  DWORD dwInKomokuType       (I)       Type to change page or image or button or label or popup
//                CHAR cInFilePath[256]      (I)       File path
//                BOOL bInDispFlag           (I)       Flag to check if displaying or not
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL   CGuiViewDlg::JudgeErrorBreakFunc( 
                        DWORD dwInKomokuType, 
                        CHAR cInFilePath[256], 
                        BOOL bInDispFlag )
{
    // initialize
    BOOL bJugebJudgeResult = FALSE;

    // Determine whether to continue or interrupted by the item request type
    switch ( dwInKomokuType )
    {
    // Page switching request processing
    case DISPLAY_REQUEST_TYPE_PAGE_SWITCH:
        if ( cInFilePath[0] == 0x00 )
        {
            bJugebJudgeResult = FALSE;
        } 
        else
        {
            bJugebJudgeResult = TRUE;
        }
        break;
    // Pop up request display
    case DISPLAY_REQUEST_TYPE_POPUP:
        if ( bInDispFlag == NEXA_VIEW_MAKE )
        {
            bJugebJudgeResult = TRUE;
        } 
        else
        {
            bJugebJudgeResult = FALSE;
        }
        break;
        
    default:
        bJugebJudgeResult = FALSE;
        break;
    }

    return bJugebJudgeResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  CalculationWeekFunc
//
//�@�\�@�@��@�F  Calculate date of week
//
//�@�T�@�@�v�@�F  Calculate date of week
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem       (I)       Item pointer
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LiemTT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
string CGuiViewDlg::CalculationWeekFunc( SCT_DATE sctInDate)
{
   // time_t rawtime;

    struct tm *timeinfo;
    const char * weekday[] = { 
        DAY_OF_WEEK_SUNDAY,
        DAY_OF_WEEK_MONDAY,
        DAY_OF_WEEK_TUESDAY,
        DAY_OF_WEEK_WEDNESDAY,
        DAY_OF_WEEK_THURSDAY,
        DAY_OF_WEEK_FRIDAY,
        DAY_OF_WEEK_SATURDAY
    };

    LONG lErrCode = 0;
    if ( JudgeDateValidityFunc( sctInDate, &sctInDate, lErrCode ) == FALSE ) // Fix bug unit Test
    {
        return "";
    }
    else {} // Do nothing

    //time ( &rawtime );
    timeinfo = DateToTimeInfo( sctInDate );
    //localtime ( &rawtime );

    //timeinfo->tm_year = sctInDate.wYear - 1990;
    //timeinfo->tm_mon  = sctInDate.byMonth - 1;
    //timeinfo->tm_mday = sctInDate.byDay;
    //mktime( timeinfo );

    if ( timeinfo->tm_wday < 0 || timeinfo->tm_wday > 6 )
    {
         return "";
    }
    else 
    {
        // Do nothing
    } 

    return weekday[timeinfo->tm_wday];
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeItemAssignClassFunc
//
//�@�\�@�@��@�F  Change css property of item
//
//�@�T�@�@�v�@�F  Change css property of item
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  CItem lpInItem        (I)       Item pointer
//                string sInAssignClass (I)       Assignment class
//                DWORD dwInChangeMode  (I)       Change mode
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) LanLTM    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ChangeItemAssignClassFunc( 
                      CItem* lpobjInItem, 
                const string &sInAssignClass, 
                      DWORD  dwInChangeMode )
{
    // Initilize
    LONG               lProcResult          = GUI_RET_OK;  // Error code
    string             sStatus              = "";
    BOOL               bJudgeDelFlg         = FALSE;
    string             sReplace             = "";
    string             strAddAssignClass    = NULL_STR;
    string             sTmpClass            = "";
    std::smatch        sm;
    vector<string>     vsClassList;
    vector<string>::iterator    it;
    DWORD              dwIndex              = GUI_VALUE_ZERO_DWORD;
    // Check parameter
    if ( lpobjInItem == NULL )
    {
        return ERROR_CODE_NOT_EXIST_ID;
    }
    else
    {
        // Do nothing
    }


    switch ( dwInChangeMode )
    {
    // Delete
    case ASSIGN_CLASS_MODE_DEL:
    // Add
    case ASSIGN_CLASS_MODE_ADD:
        break;
    default:
        return ERROR_CODE_NOT_RANGE;
    }

    // Get status:
    sStatus = lpobjInItem->m_sctProperty.sStatus;

    // Determine whether to delete the item specified class
    if ( dwInChangeMode == ASSIGN_CLASS_MODE_DEL )
    {
        bJudgeDelFlg = TRUE;
    }
    else
    {
        if ( regex_search( sStatus, sm, regex( "^.*" + ( string )SPEC_ASSIGN_CLASS + ".*" + ( string )SPEC_ASSIGN_CLASS + "$" ), std::regex_constants::match_default ) == TRUE )
        {
            bJudgeDelFlg = TRUE;
        }
        else
        {
            bJudgeDelFlg = FALSE;
        }
    }

    // Determined that it has removed the item specification class to delete an item specified class
    if ( bJudgeDelFlg == TRUE )
    {
        strAddAssignClass = "";
        if ( regex_search(sStatus, regex( ".*(@.*@)$" )))
        {
            strAddAssignClass = regex_replace( sStatus, regex( ".*(@.*@)$" ), string( "$1" ));
        }
        // �w��N���X���擾�ł��Ȃ��ꍇ�́A�������s��Ȃ�.
        if ( NULL_STR != strAddAssignClass ) 
        {
            sStatus = regex_replace( sStatus, regex( strAddAssignClass ), ( string )"" );
            sReplace = regex_replace( strAddAssignClass, regex( SPEC_ASSIGN_CLASS ), ( string )"" );
            sReplace   = regex_replace( sReplace, regex( UNDERBAR_REPLACE_STR ), ( string )STS_SPLIT);
            
            // Remove class 
            // split class into vector
            vsClassList = SplitString( lpobjInItem->m_sctProperty.sClass, CLASS_LIST_STR );
            for ( dwIndex = 0; dwIndex < vsClassList.size(); dwIndex++ )
            {
                it = std::find( vsClassList.begin(), vsClassList.end(), sReplace );
                if (( it != vsClassList.end()) && 
                    ( vsClassList.size() > 0 ))
                {
                    vsClassList.erase( it );
                }
                else
                {
                    // Do nothing
                }
            }
            lpobjInItem->m_sctProperty.sClass = JoinString( vsClassList, CLASS_LIST_STR );
        }
    }
    else
    {
        // Do nothing
    }

    // If change mode is added, add a change class
    if ( dwInChangeMode == ASSIGN_CLASS_MODE_ADD )
    {
        if ( sInAssignClass == "" )
        {
            // Do nothing
        }
        else
        {
            if ( lpobjInItem->m_sctProperty.sClass == "" )
            {
                // Do nothing
            }
            else
            {
                lpobjInItem->m_sctProperty.sClass = lpobjInItem->m_sctProperty.sClass + CLASS_LIST_STR + sInAssignClass;
            }
        }
        std::regex currentText((string )STS_SPLIT );
        sReplace = regex_replace( sInAssignClass, currentText, ( string )UNDERBAR_REPLACE_STR );
        lpobjInItem->m_sctProperty.sStatus = lpobjInItem->m_sctProperty.sStatus + SPEC_ASSIGN_CLASS + sReplace + SPEC_ASSIGN_CLASS;
    }
    else
    {
        // Do nothing
    }

    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeFontColorFunc
//
//�@�\�@�@��@�F  Change font color for displaying text
//
//�@�T�@�@�v�@�F  Change font color for displaying text
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem         (I)       Item pointer
//                DWORD dwInChangeMode   (I)       Change Mode
//                DWORD dwCharacterColor (I)       Character color
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/16    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ChangeFontColorFunc(
                      CItem* lpobjInItem, 
                      DWORD dwInChangeMode, 
                      DWORD dwCharacterColor )
{
    // Initilize
    LONG                        lProcResult      = GUI_RET_OK;  // Error code
    CItem*                      lpobjUpdateItem  = NULL;
    WORD                        wIndex           = GUI_VALUE_ZERO_WORD;
    string                      sColorClass      = "";
    vector<string>              vsClassList;
    string                      sAddColor        = "";
    vector<string>::iterator   it;
    string                     sTemp             = "";
    WORD                        wSubIndex        = GUI_VALUE_ZERO_WORD;

    // Initialize
    vsClassList.clear();
    // Check valid of agruments
    if ( lpobjInItem == NULL )
    {
        return ERROR_CODE_NULL_ID;
    }
    else
    {
        // Do nothing
    }

    if (( dwInChangeMode == CHAR_COLOR_MODE_DELETE ) ||
        ( dwInChangeMode == CHAR_COLOR_MODE_ADD ))
    {
        // Do nothing
    }
    else
    {
        return ERROR_CODE_NOT_RANGE;
    }
#if 0
    if (( dwCharacterColor < 0 ) || 
        (( dwCharacterColor > 5 ) && ( dwCharacterColor != 99 )))
    {
#endif
    // Fix PGRelief
    if (( dwCharacterColor > 5 ) && ( dwCharacterColor != 99 ))
    {
        return ERROR_CODE_NOT_RANGE;   // Fix follow TSBJ review
    }
    else
    {
        // Do nothing
    }
    //If the status is a child, and set the span tag of the child element.
    lpobjUpdateItem = FindItemByTagID( TAG_ID_NAME_SET_CHAR_SPAN, lpobjInItem->m_vobjItems );
        
    // If the span tag of the child element does not exist, add a span tag to tag ID.
    if (( lpobjUpdateItem == NULL ) && 
        ( dwInChangeMode  == CHAR_COLOR_MODE_ADD ))
    {
        lpobjUpdateItem = new CRichLabel();
        lpobjUpdateItem->SetProperties(lpobjInItem->m_sctProperty.dwType, 
            // Start ThietNP 2015-07-28 Change control ID
            // 0xFFFFFFFF, 
            IDCTRL_ITEM,
            // End ThietNP 2015-07-28 Change control ID
            "span", //lpobjInItem->m_sctProperty.sTagName, 
            lpobjInItem->m_sctProperty.sText.c_str(),
            lpobjInItem->m_sctProperty.dwLeft, 
            lpobjInItem->m_sctProperty.dwTop, 
            lpobjInItem->m_sctProperty.dwWidth, 
            lpobjInItem->m_sctProperty.dwHeight, 
            lpobjInItem->m_sctProperty.bVisible, 
            lpobjInItem->m_sctProperty.bVisibilityHidden, 
            lpobjInItem->m_sctProperty.bEnable, 
            lpobjInItem->m_sctProperty.sGaikan.c_str(),
            lpobjInItem->m_sctProperty.sFmt.c_str(),
            TAG_ID_NAME_SET_CHAR_SPAN, //lpobjInItem->m_sctProperty.sTagID, 
            lpobjInItem->m_sctProperty.sTagGroup.c_str(),
            lpobjInItem->m_sctProperty.sAltTagID.c_str(),
            lpobjInItem->m_sctProperty.sInitClass.c_str(),
            lpobjInItem->m_sctProperty.sInitText.c_str(),
            lpobjInItem->m_sctProperty.sNullStrInitApp.c_str(),
            "", //lpobjInItem->m_sctProperty.sStatus,
            lpobjInItem->m_sctProperty.bTextClickEvent ,
            lpobjInItem->m_sctProperty.dwClickBranchMode ,
            lpobjInItem->m_sctProperty.sEvenFunctionName.c_str(),
            lpobjInItem->m_sctProperty.sParaContainerTagID.c_str(),
            lpobjInItem->m_sctProperty.sParaStartNo.c_str(),
            lpobjInItem->m_sctProperty.sParaEndNo.c_str(),
            lpobjInItem->m_sctProperty.sLimit.c_str(),
            lpobjInItem->m_sctProperty.sClass.c_str(),
            lpobjInItem->m_sctProperty.sValue.c_str(),
            lpobjInItem->m_sctProperty.dwFontSize ,
            lpobjInItem->m_sctProperty.fZoomSize ,
            lpobjInItem->m_sctProperty.lMinLen ,
            lpobjInItem->m_sctProperty.lMaxLen ,
            lpobjInItem->m_sctProperty.sPageAtr.c_str(),
            lpobjInItem->m_sctProperty.sBtn_Span_ImgClass.c_str(),
            lpobjInItem->m_sctProperty.bImageFirst,
            lpobjInItem->m_sctProperty.vSpan,
            lpobjInItem->m_sctProperty.sBtn_Hr_Line_Class.c_str(),
            lpobjInItem->m_sctProperty.sImgSrc.c_str(),
            lpobjInItem->m_sctProperty.eAreaType ,
            FALSE, //lpobjInItem->m_sctProperty.bParent
            lpobjInItem->m_sctProperty.lLineHeight,
            lpobjInItem->m_sctProperty.dwHrPos,
            lpobjInItem->m_sctProperty.bOriginal);
        lpobjUpdateItem->CreateItem( dynamic_cast<CWnd*>(lpobjInItem)->GetParent());
        lpobjUpdateItem->m_lpParent = lpobjInItem;
        lpobjInItem->m_sctProperty.sText = "";
        lpobjInItem->m_vobjItems.push_back( lpobjUpdateItem );

    }
    else
    {
        // Do nothing
    }
    if ( lpobjUpdateItem != NULL )
    {
            // Get color class

        if ( lpobjUpdateItem->m_sctProperty.sStatus == "" )
        {
            for ( wIndex = 0; wIndex < CHARACTER_COLOR_TABLE_SIZE; wIndex++ )
            {
                if (( Character_Color_Table[wIndex].sColorClass != "" ) && 
                    ( lpobjUpdateItem->m_sctProperty.sClass.find( Character_Color_Table[wIndex].sColorClass ) != std::string::npos ))
                {
                    sColorClass = Character_Color_Table[wIndex].sColorClass;
                    break;
                }
                else
                {
                    // Do nothing
                }
            }
        }
        else
        {
            // Join string status and set for class CSS
            sColorClass = lpobjUpdateItem->m_sctProperty.sStatus;// Design
            if ( lpobjUpdateItem->m_sctProperty.bParent == TRUE )
            {
                    sColorClass += STS_SPLIT + ( string )STS_NAME_UPDATE_ELEMENT_PARENT;
                }
                else
                {
                    sColorClass += STS_SPLIT + ( string )STS_NAME_UPDATE_ELEMENT_CHILD;
                }
                if ( lpobjUpdateItem->m_sctProperty.bVisible == TRUE )
                {
                    sColorClass += STS_SPLIT + ( string )"visible";
                }
                else
                {
                    sColorClass += STS_SPLIT + ( string )"hidden";
                }
                if ( lpobjUpdateItem->m_sctProperty.bEnable == TRUE )
                {
                    sColorClass += STS_SPLIT + ( string )STS_NAME_DISABLED_ENABLE;
                }
                else
                {
                    sColorClass += STS_SPLIT + ( string )STS_NAME_DISABLED_DISABLE;
                }
            }
    }
    else
    {
        return lProcResult;
    }
    
    if ( lpobjUpdateItem == NULL )
    {
        // Do nothing
    }
    else
    {
        vsClassList = SplitString( lpobjUpdateItem->m_sctProperty.sClass, CLASS_LIST_STR );
    }

    if ( dwInChangeMode == CHAR_COLOR_MODE_DELETE )
    {
        if (( lpobjUpdateItem == NULL ) || 
            ( sColorClass == "" ))
        {
            return lProcResult;
        }
        else
        {
            // Do nothing
        }
        if ( lpobjUpdateItem->m_sctProperty.sClass.find( sColorClass ) != std::string::npos )
        {
            it = std::find( vsClassList.begin(), vsClassList.end(), sColorClass );
            if (  it != vsClassList.end() )
            {
                vsClassList.erase( it );
            }
            else
            {
                // Do nothing
            }
        }
        else
        {
            // Do nothing
        }

        lpobjUpdateItem->m_sctProperty.sClass = JoinString( vsClassList, CLASS_LIST_STR );
        lpobjUpdateItem->m_sctProperty.sStatus = "";
    }
    else
    {
        if ( lpobjUpdateItem == NULL )
        {
            // Do nothing
        }
        else
        {
            for ( wSubIndex = 0; wSubIndex < CHARACTER_COLOR_TABLE_SIZE; wSubIndex++ )
            {
                if ((( DWORD )Character_Color_Table[wSubIndex].wMojiColor == dwCharacterColor ) &&
                    ( dwCharacterColor != 99 ))
                {
                    //if ( Character_Color_Table[wSubIndex].sColorClass != NOT_SET_STR )  // Fix follow TSBJ review
                    //{
                        sAddColor = Character_Color_Table[wSubIndex].sColorClass;
                        lpobjUpdateItem->m_sctProperty.sStatus = "";
                   /* }
                    else
                    {
                        lpobjUpdateItem->m_sctProperty.sStatus = "";
                    }*/
                    break;
                }
                else
                {
                    lpobjUpdateItem->m_sctProperty.sStatus = "";
                }
            }

            // Change text color
            if ( vsClassList.size() > 1 )
            {
                it = std::find( vsClassList.begin(), vsClassList.end(), sColorClass );
                if (  it != vsClassList.end() )
                {
                    vsClassList.erase( it );
                }
                else
                {
                    // Do nothing
                }
            }
            else
            {
                // Do nothing
            }
            if( sAddColor != "" )
            {
                vsClassList.push_back( sAddColor );
            }
            else
            {
                // Do nothing
            }
        
            lpobjInItem->m_sctProperty.bParent = FALSE;
            lpobjUpdateItem->m_sctProperty.sClass = JoinString( vsClassList, CLASS_LIST_STR ); 
            lpobjUpdateItem->ItemUpdateState();
        }
    }
    
    if (( vsClassList.size() == 1 ) &&
        ( lpobjUpdateItem->m_sctProperty.bParent == FALSE ))
    {
        sTemp = lpobjUpdateItem->m_sctProperty.sText;
        if (lpobjUpdateItem != NULL )
        {
            //std::remove(lpobjInItem->m_vobjItems.begin(), lpobjInItem->m_vobjItems.end(), lpobjUpdateItem );
            auto it2 = std::find( lpobjInItem->m_vobjItems.begin(), lpobjInItem->m_vobjItems.end(), lpobjUpdateItem );
            if (  it2 != lpobjInItem->m_vobjItems.end() )
            {
                lpobjInItem->m_vobjItems.erase( it2 );
            }
            else
            {
                // Do nothing
            }
            delete lpobjUpdateItem;
        }

        lpobjInItem->m_sctProperty.sText = sTemp;
        lpobjInItem->m_sctProperty.bParent = TRUE;
    }
    else
    {
        // Do nothing
    }
    
    return lProcResult;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  CopyInputInfoFunc
//
//�@�\�@�@��@�F  Copy input information when switch page
//
//�@�T�@�@�v�@�F  Copy input information when switch page
//
//�@�߁@��@�l�F  error code
//
//�@���@�@���@�F  AREA_ENUM      eAreatype     (I)     Area type
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/03/30    (TSDV) LanLTM    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////

LONG CGuiViewDlg::CopyInputInfoFunc( AREA_ENUM eAreatype, const string &sInTagID, const string &sInText, const string &sInStatus )
{
    // Initilize
    LONG                        lProcResult     = GUI_RET_OK;           // Error code
    vector<CItem*>              vlpItem;
    vector<CItem*>              vlpImage;
    string                      sUpdateText     = "";                   // Updated text
    string                      sDesign         = "";                   // Design of item

    // Clear data
    vlpItem.clear();
    vlpImage.clear();

    // Get input item
    vlpItem = SearchTagIDFunc( sInTagID, eAreatype );

    // if found item in current area
    if ( vlpItem.size() == 1)
    {
        vlpItem[0]->m_sctProperty.sText = sInText;
        // Get design number
        sDesign = GetDesignStsFunc( sInStatus );

        // Change class of style
        ChangeClassIDFunc( vlpItem[0], sDesign );

        // Re-draw item
        vlpItem[0]->ItemUpdateState();

        // Show cursor
        gclInputItemTag = vlpItem[0];
        CursorMoveFunc( 0 );
        
    }
    else
    {
        // Do nothing
    }
    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeViewInnerPageFunc
//
//�@�\�@�@��@�F  Change area inner page
//
//�@�T�@�@�v�@�F  Change area inner page
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  string sInPageURL            (I)       Area Name
//                AREA_ENUM eInAreaName        (I)       Area type
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/04/06    (TSDV) LanLTM    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::ChangeViewInnerPageFunc( 
              const  string     &sInPageURL, 
                     AREA_ENUM  eInAreaName) 
{

    // Initialize
    LONG lProcResult = RESULT_OK_INNER_PAGE_SWITCH; // ��������.
    BOOL bReturn = FALSE;
    string sTagID = "";
    string sStatus = "";
    string sText = "";
    CArea*  lpArea = NULL;


    // Check patameter
    if (( sInPageURL == "" ) ||
        ( sInPageURL == NOT_SET_STR ))
    {
        // Parameter is invalid
        return ERROR_CODE_NOT_EXIST_HTML;
    }

    if ( gclInputItemTag == NULL )
    {
        // DO nothing
    }
    else
    {
        sTagID  = gclInputItemTag->m_sctProperty.sTagID;
        sText   = gclInputItemTag->m_sctProperty.sText;
        sStatus = gclInputItemTag->m_sctProperty.sStatus;
    }
    
    // TSDV-LanLTM-Update Javascript to version 10.33
    lpArea = GetArea( eInAreaName );
    if ( lpArea == NULL )
    {
        // do nothing
    }
    else
    {
        if ( lpArea->m_sctAreaInfo.sAreaFuncName == sInPageURL )
        {
            return GUI_RET_OK;
        }
        else
        {
            // Do nothing
        }
    }
    // TSDV-LanLTM-End of update

    // Call function to change area
    bReturn = ChangeArea( eInAreaName, sInPageURL );

    // Change area successfully
    if ( bReturn == TRUE )
    {
        // Do nothing
    }
    else
    {
        lProcResult = ERROR_CODE_NOT_EXIST_HTML;
    }

    if ( eInAreaName == geInputItemArea )
    {
        CopyInputInfoFunc( eInAreaName, sTagID, sText, sStatus );
    }
    else
    {
        // Do nothing    
    }

    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ChangeDesignBtnOnFunc
//
//�@�\�@�@��@�F  Change design button to on and switch page
//
//�@�T�@�@�v�@�F  Change design button to on and switch page
//
//�@�߁@��@�l�F  void
//
//�@���@�@���@�F  CItem lpInItem        (I)       Item pointer
//                DWORD dwSwitchPageIdx (I)       Index of page in page table
//                BOOL bAnotherOn       (I)       Item status
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/04/07    (TSDV) SonPT    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG  CGuiViewDlg::ChangeDesignBtnOnFunc( CItem* lpobjInItem, DWORD dwSwitchPageIdx, BOOL bAnotherOn )
{
    LONG lErrCode    = GUI_RET_OK;

    if ( lpobjInItem->m_sctProperty.sTagName == "li" )
    {
        lErrCode = ChangeVisibleInsideTabFunc( lpobjInItem );
    }
    else if ( lpobjInItem->m_sctProperty.sTagName == "a" )
    {
        ContenaKirikaeFunc( 
                    lpobjInItem->m_sctProperty.sParaContainerTagID, 
                    lpobjInItem->m_sctProperty.sParaStartNo, 
                    lpobjInItem->m_sctProperty.sParaEndNo, 
                    lpobjInItem );
    }
    else
    {
        if ( bAnotherOn == TRUE )
        {
            lErrCode = ChangeClassIDFunc( lpobjInItem, DESIGN_BTN_ON );
            lpobjInItem->ItemUpdateState();
        }
        else
        {
            lErrCode = ChangeInputButtonDesignFunc( lpobjInItem );
        }
        if ( lErrCode != GUI_RET_OK )
        {
            return lErrCode;
        }
        else
        {
            // Do nothing
        }
        if ( dwSwitchPageIdx < SWITCH_OPERATION_PAGE_TABLE_SIZE )
        {
            if ( Switch_OperationPage_Table[dwSwitchPageIdx].sContenaKirikaeID != "" )
            {
                ContenaKirikaeFunc( 
                    Switch_OperationPage_Table[dwSwitchPageIdx].sContenaKirikaeID, 
                    Switch_OperationPage_Table[dwSwitchPageIdx].sStartNo, 
                    Switch_OperationPage_Table[dwSwitchPageIdx].sEndNo, 
                    NULL );
            }
            else
            {
                return ERROR_CODE_NOT_EXIST_HTML;
            }
        }
    }
    return lErrCode;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  InputErrorNoticeFunc
//
//�@�\�@�@��@�F  Function to notify when input error
//
//�@�T�@�@�v�@�F  Function to notify when input error
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F         string sInInputTagID          // Input tag ID string 
//                       LONG   lInInputErrCode        // Error code, 
//                       LONG   lInConditionMin        // Min condition, 
//                       LONG   lInConditionMax        // Max Condition
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/04/07    (TSDV)LanLTM    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG  CGuiViewDlg::InputErrorNoticeFunc( 
                const  string &sInInputTagID, 
                       LONG   lInInputErrCode, 
                       LONG   lInConditionMin, 
                       LONG   lInConditionMax ) 
{
    // Initialize.
    LONG lProcResult = GUI_RET_OK; // Error code

    // Check parameter
    if( sInInputTagID == "" ) 
    {
        // parameter is invalid
        return ERROR_CODE_NULL_ID;
    }

    if ( string(INPUT_ERROR_VIEW_CTRL_DISABLE) == INPUT_ERROR_VIEW_CTRL ) 
    {
        lProcResult = ControlEnableAllDisplayFunc( FLG_OBJECT_NOT_ENABLE, E_AREA_GYOMU );
    }

    // Set the message information.
    ClearSendData();
    SCT_GUI_MSG_N_INPUT_ERROR_VIEW* lpNError = ( SCT_GUI_MSG_N_INPUT_ERROR_VIEW* )m_bySendData;
    lpNError->dwDenbunNo                     = INPUT_ERROR_NOTICE_NO;
    lpNError->lErrCode                       = lInInputErrCode;
    sprintf_s( lpNError->szTagID, "%s", sInInputTagID.c_str( ));

    // Set the number of digits conditions in the case of digits check error
    if ( lInInputErrCode == INPUT_ERR_CODE_LIMIT )
    {
        // Minimum number of digits
        switch ( lInConditionMin ) 
        {
            case INPUT_LENGTH_EMPTY_OR_ALL: // Minimum number of digits is empty or full fill mode.
                lInConditionMin = -1;
                break;
            case INPUT_LENGTH_NASHI_MODE: // No mode
                lInConditionMin = 0;
                break;
            default: // other case
                if ( lInConditionMin >= 0 )
                {
                    // Do nothing
                }
                else
                {
                    lInConditionMin = 0;
                }

                break;
        }
        lpNError->lConditionMin = lInConditionMin;

        // Maximum number of digits
        switch ( lInConditionMax ) 
        {
            case INPUT_LENGTH_NASHI_MODE: // No mode
                lInConditionMax = INPUT_MAX_LENGTH_LIMIT;
                break;

            default: // others

                if ( lInConditionMax >= 0 )
                {
                    // Do nothing
                }
                else
                {
                    lInConditionMax = INPUT_MAX_LENGTH_LIMIT;
                }
                
                break;
        }
        lpNError->lConditionMax = lInConditionMax;
    }

    // Send data to ViewIF
    lProcResult = SendData( sizeof( SCT_GUI_MSG_N_INPUT_ERROR_VIEW ));
    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  TeikiShubetsuInputProcBranchFunc
//
//�@�\�@�@��@�F  Function to change the process to be executed by the pressed button.
//
//�@�T�@�@�v�@�F  Function to change the process to be executed by the pressed button.
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F         string sInTagID          // Input tag ID string 
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/04/14    (TSDV)LanLTM    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG  CGuiViewDlg::TeikiShubetsuInputProcBranchFunc(
                     const  string &sInTagID )
{
    // �ϐ��̐錾.
    LONG  lProcResult           = GUI_RET_NG;               // ��������.
    DWORD dwLoopIndex           = GUI_VALUE_ZERO_DWORD;     // ���[�v�J�E���g�ϐ�.
    LONG  lZokuseiIndex         = GUI_VALUE_ZERO_LONG; // �����ʑ����e�[�u���C���f�b�N�X.
    vector<CItem*>              vlpArySearchTagIdInfo; // �^�OID�������.
    vector<CItem*>              vlpItem;

    // Check parameter
    if ( gclInputItemTag == NULL )
    {
        // if global input item is NULL
        return ERROR_CODE_NULL_ID;
    }

    // Tag ID string is enter keyboard
    if ( sInTagID == KEYBOARD_DATA_ENTER )
    {
        lZokuseiIndex = -1;

        for( dwLoopIndex = 0; dwLoopIndex < TEIKISHUBETU_ZOKUSEI_TABLE_SIZE; dwLoopIndex++ )
        {
            if ( TeikiShubetu_Zokusei_Table[dwLoopIndex].dwSendInputComp == SENDINPUTCOMP_ARI )
            {
                lZokuseiIndex = ( LONG )dwLoopIndex;
                break;
            }
        }

        if ( lZokuseiIndex == -1 )
        {
            // �����ʈȊO�̖t�����Ɣ��肷��.
            return ERROR_CODE_NULL_ID;
        }
        else
        {
            // Do nothing
        }

        vlpArySearchTagIdInfo = SearchTagIDFunc( TeikiShubetu_Zokusei_Table[dwLoopIndex].sTagID, E_AREA_NULL );
        // �Ώۂ̃^�OID�����݂��Ȃ��ꍇ�A�z��̗v�f��0�ɂȂ�.
        if( vlpArySearchTagIdInfo.size() == 0 ) 
        {
            return ERROR_CODE_NOT_EXIST_ID;
        }

        lProcResult = TeikiShubeTsuInputCompletRequestFunc();
        return lProcResult;
    }

    // �^�OID���牟���^�OID���擾.
    lZokuseiIndex = -1;
    dwLoopIndex   = GUI_VALUE_ZERO_DWORD;

    for ( dwLoopIndex = 0; dwLoopIndex < TEIKISHUBETU_ZOKUSEI_TABLE_SIZE; dwLoopIndex++ ) 
    {
        if ( sInTagID == TeikiShubetu_Zokusei_Table[dwLoopIndex].sTagID )
        {
            lZokuseiIndex = ( LONG )dwLoopIndex;
            break;
        }
        else
        {
            // Do nothing
        }
    }

    if ( lZokuseiIndex == -1 ) 
    {
        // �����ʈȊO�̖t�����Ɣ��肷��.
        return ERROR_CODE_NULL_ID;
    }
    else
    {
        // Do nothing
    }

    // ���͊������M�L���ɂ�葀���ύX����.
    if ( TeikiShubetu_Zokusei_Table[dwLoopIndex].dwSendInputComp == SENDINPUTCOMP_ARI )
    {
        // ���͊������M����.
        lProcResult = TeikiShubeTsuInputCompletRequestFunc();
    } 
    else 
    {
            // Find item by Tag ID
        vlpItem = SearchTagIDFunc( sInTagID, E_AREA_NULL );
            
        // ���͒ʒm����.
        if ( vlpItem.size() == 0 )
        {
            return ERROR_CODE_NOT_EXIST_ID;
        }
        else
        {
            lProcResult = TeikiShubeTsuInputNoticeFunc( vlpItem[0], lZokuseiIndex );
        }
    }
    return lProcResult;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  TeikiShubeTsuInputCompletRequestFunc
//
//�@�\�@�@��@�F  Function to create a request for a regular type item input completion
//
//�@�T�@�@�v�@�F  Function to create a request for a regular type item input completion
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  NA
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/04/14    (TSDV)LanLTM    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG  CGuiViewDlg::TeikiShubeTsuInputCompletRequestFunc() 
{

    
    // Initialize
    LONG                            lProcResult                 = GUI_RET_OK;               // ��������.
    string                          sStsDesign                  = "";                       // �f�U�C��.
    DWORD                           dwIndex                     = GUI_VALUE_ZERO_DWORD;     //
    string                          sSendData                   = "";                       // ���M�f�[�^.
    DWORD                           dwLoopCount                 = GUI_VALUE_ZERO_DWORD;     // ���[�v�J�E���g�ϐ�.
    BYTE                            byUpData                    = GUI_VALUE_ZERO_BYTE;     // 
    //CItem*                          lpObjTagInfo                = NULL;                     // �^�OID���.
    BYTE                            bySendData[SEND_DATA_LIMIT];                            // 
    vector<CItem*>                  vlpSerchTagIdInfo;                                      // vector of item pointer
    SCT_GUI_MSG_R_INPUT_END_VIEW*   lpRInputEnd                 = NULL;                     //
    vector<string>                  vsData;                                                 //

    // Reset data
    ( VOID )memset( &bySendData[0], 0x00, sizeof( bySendData ) );
    vlpSerchTagIdInfo.clear();
    vsData.clear();

    // Check parameter
    if ( gclInputItemTag == NULL ) 
    {
        // Global input item is NULL
        return ERROR_CODE_NULL_ID;
    }

    // Disable all items in screen
    lProcResult = ControlEnableAllDisplayFunc( FLG_OBJECT_NOT_ENABLE, E_AREA_GYOMU );
    // If cannot disable all items
    if ( lProcResult == GUI_RET_OK ) 
    {
        // Do nothing
    }
    else
    {
        return lProcResult;
    }

    // �����e�[�u���̃^�OID�̓_�����ɂ�著�M�f�[�^���쐬����.
    for( dwLoopCount = 0; dwLoopCount < TEIKISHUBETU_ZOKUSEI_TABLE_SIZE; dwLoopCount++ ) 
    {
        if ( TeikiShubetu_Zokusei_Table[dwLoopCount].lLimit == -1 ) 
        {
            continue;
        }
        vlpSerchTagIdInfo = SearchTagIDFunc( TeikiShubetu_Zokusei_Table[dwLoopCount].sTagID, E_AREA_NULL );
        if ( vlpSerchTagIdInfo.size() == 0 ) 
        {
            // If cannot found any item, 
            byUpData = 0;
        }

        else
        {
            // �^�OID�����݂���ꍇ�́A�f�U�C���ɂ��f�[�^��ݒ肷��.
            sStsDesign = GetDesignStsFunc( vlpSerchTagIdInfo[0]->m_sctProperty.sStatus );

            if ( sStsDesign == DESIGN_BTN_ON ) 
            {
                byUpData = 1;
            } 
            else 
            {
                byUpData = 0;
            }
        }
        // �^�OID���̐��䌅���̈ʒu�̓��e���X�V����.
        if ( TeikiShubetu_Zokusei_Table[dwLoopCount].lLimit >= 0 )
        {
            dwIndex = TeikiShubetu_Zokusei_Table[dwLoopCount].lLimit;
            if ( dwIndex < SEND_DATA_LIMIT )
            {
                bySendData[dwIndex] = byUpData;
            }
            else
            {
                // Do nothing
            }
        }
        else
        {
            // Do nothing
        }
    }

    for ( dwLoopCount = 0; dwLoopCount < SEND_DATA_LIMIT; dwLoopCount++ )
    {
        vsData.push_back( std::to_string(( LONGLONG )bySendData[dwLoopCount] ));
    }

    ClearSendData();
    // Set message number
    lpRInputEnd = ( SCT_GUI_MSG_R_INPUT_END_VIEW* )m_bySendData;
    lpRInputEnd->dwDenbunNo = INPUT_COMPLET_REQUEST_NO;
    
    // Set input data and input tag ID to send to ViewIF process
    sprintf_s( lpRInputEnd->szTagID, "%s", gclInputItemTag->m_sctProperty.sTagID.c_str( ));
    sSendData = JoinString( vsData, "" );
    sprintf_s( lpRInputEnd->szData, "%s", sSendData.c_str( ));
    lpRInputEnd->dwDataKind = DATA_KIND_DISP_TEXT;
        
    // Send data to ViewIF
    lProcResult = SendData( sizeof( SCT_GUI_MSG_R_INPUT_END_VIEW ));
    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  TeikiShubeTsuInputNoticeFunc
//
//�@�\�@�@��@�F  Function to create a regular type item input notification
//
//�@�T�@�@�v�@�F  Function to create a regular type item input notification
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  CItem* lpInObjTagID          Object Tag ID pointer
//                LONG   lZokuseiIdx           Table index
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/04/14    (TSDV)LanLTM    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG  CGuiViewDlg::TeikiShubeTsuInputNoticeFunc( 
                         CItem* lpInObjTagID,
                         LONG   lZokuseiIdx )
{

    // Initialize
    LONG                lProcResult         = GUI_RET_OK;   // Process result
    vector<CItem*>      arySerchTagIdInfo;                  // Vector of tag ID pointer
    string              sTagID              = "";           // Send TagID string

    // Reset data
    arySerchTagIdInfo.clear();

    // Check parameter
    if( lpInObjTagID == NULL )
    {
        return ERROR_CODE_NULL;
    }

    // �I���^�l�[�g���ۂ�.
    if ( TeikiShubetu_Zokusei_Table[lZokuseiIdx].dwZokusei == ZOKUSEI_ALTERNATE ) 
    {
        // �I���^�l�[�g���͒ʒm.
        sTagID = SelectSendTagIdFunc( lpInObjTagID );
        InputNoticeFunc( sTagID );
    }
    else
    {
        // �ʏ�t���͒ʒm.
        InputNoticeFunc( lpInObjTagID->m_sctProperty.sTagID );
    }


    lProcResult = TeikiShubeTsuBtnCtrlFunc( lpInObjTagID, lZokuseiIdx );

    return lProcResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  InputCancelResponsFunc
//
//�@�\�@�@��@�F  Send message to cancel reponse
//
//�@�T�@�@�v�@�F  Send message to cancel reponse
//
//�@�߁@��@�l�F  Error code
//
//�@���@�@���@�F  DWORD dwInMessageNo          Message number
//                LONG  lInResult              process result
//
//  �o�[�W�����@     ���t          ����              ���l
//  GUI-01.00.00    2015/04/14    (TSDV)LanLTM    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG  CGuiViewDlg::InputCancelResponsFunc(
                       LONG  lInMessageNo, 
                       LONG  lInResult )
{
    // Initialize
    LONG                                  lProcResult                           = GUI_RET_OK;       // Process result
    SCT_GUI_MSG_A_INPUT_CANCEL_VIEW*   lpRInputCancelRespons                 = NULL;             // Pointer to 

        ClearSendData();
    // Set message number
    lpRInputCancelRespons = ( SCT_GUI_MSG_A_INPUT_CANCEL_VIEW* )m_bySendData;
    lpRInputCancelRespons->dwDenbunNo = ( DWORD )lInMessageNo;

    if ( lInResult == GUI_RET_OK )
    {
        lpRInputCancelRespons->dwResult   = DENBUN_RESULT_OK;
    }
    else
    {
        lpRInputCancelRespons->dwResult   = DENBUN_RESULT_NG;
        lpRInputCancelRespons->dwErrCode = lInResult * ( -1 );
    }

    switch ( glWaitResponseDenbunNo )
    {
        // Input complete responsed
        case INPUT_COMPLET_RESPONSE_NO:
            lpRInputCancelRespons->dwNotReceivRes = NOT_RECEIV_RES_NOT_INPUT_COMPLET_RESPONSE;
            break;
            // Other input reponsed
        case OTHER_INPUT_RESPONSE_NO:
            lpRInputCancelRespons->dwNotReceivRes = NOT_RECEIV_RES_NOT_OTHER_INPUT_RESPONSE;
            break;
            // Reset responsed
        case RESET_RESPONSE_NO:
            lpRInputCancelRespons->dwNotReceivRes = NOT_RECEIV_RES_NOT_RESET_RESPONSE;
            break;
            // Fare responsed
        case FARE_RESPONSE_NO:
            lpRInputCancelRespons->dwNotReceivRes = NOT_RECEIV_RES_NOT_FARE_RESPONSE;
            break;
            // Start responsed
        case START_RESPONSE_NO:
            lpRInputCancelRespons->dwNotReceivRes = NOT_RECEIV_RES_NOT_START_RESPONSE;
            break;
            // other cases
        default: 
            lpRInputCancelRespons->dwNotReceivRes = NOT_RECEIV_RES_NOT_NASHI;
            break;
    }

    // Send data to ViewIF
    lProcResult = SendData( sizeof( SCT_GUI_MSG_A_INPUT_CANCEL_VIEW ));
    return lProcResult;
}

BOOL CGuiViewDlg::JudgeUserInputProcFunc( const string &sInTagID, const string &sInInputTagID )
{
    // Initialize
    BOOL  bJudegeResult    = FALSE;
    DWORD dwLoopCount      = 0;
    DWORD dwLength         = GUI_VALUE_ZERO_LONG;

    // Check parameter
    if ( sInTagID == NOT_SET_STR )
    {
        return FALSE;
    }
    else
    {
        // Do nothing
    }

    if ( sInInputTagID == NOT_SET_STR )
    {
        return FALSE;
    }
    else
    {
        // Do nothing
    }

    if (( string )USER_NAME == ( string )"sb" )
    {
        bJudegeResult = FALSE;
        if( sInInputTagID == TAG_ID_TEIKISHUBETSU )
        {
            if ( sInTagID == KEYBOARD_DATA_ENTER )
            {
                bJudegeResult = TRUE;
            }
            else
            {
                dwLength = ARRAY_LENGTH( TeikiShubetu_Zokusei_Table );
                for( dwLoopCount = 0; dwLoopCount < dwLength; dwLoopCount++ )
                {
                    if ( sInTagID == TeikiShubetu_Zokusei_Table[dwLoopCount].sTagID )
                    {
                        bJudegeResult = TRUE;
                        break;
                    }
                    else
                    {
                        // Do nothing
                    }
                }
            }
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        bJudegeResult = FALSE;
    }

    return bJudegeResult; 
}

BOOL CGuiViewDlg::JudgeUserDisplayProcFunc( const string &sInTagID )
{
    // Initialize
    BOOL                bJudegeResult = FALSE;
    vector<string>      vsTagIDSplit;

    // Reset data
    vsTagIDSplit.clear();

    // Check parameter
    if ( sInTagID == NOT_SET_STR )
    {
        return FALSE;
    }
    else
    {
        // Do nothing
    }

    if (( string )USER_NAME == ( string )"sb" )
    {
        vsTagIDSplit = SplitString( sInTagID, "," );

        if ( vsTagIDSplit.size() == 0 )
        {
            // Do nothing
        }
        else
        {
            if( vsTagIDSplit[0] == TAG_ID_TEIKISHUBETSU )
            {
                bJudegeResult = TRUE;
            }
            else
            {
                bJudegeResult = FALSE;
            }
        }
    }
    else
    {
        bJudegeResult = FALSE;
    }

    return bJudegeResult; 
}

BOOL CGuiViewDlg::JudgeInputStrFunc( 
                 const    string &sInLeftStr,
                 const    string &sInRightStr,
                 const    string &sInsertStr,
                          LONG lInMaxLength, 
                          string& sResult )
{
    // Initialize
    BOOL    bResult        = FALSE;
    //LONG    lJudgeNumber   = GUI_VALUE_ZERO_LONG;
    string  sInputCnt      = "";
    DWORD   dwInputLength  = GUI_VALUE_ZERO_DWORD;

    // Check parameter
    //if (( sInLeftStr  == "" ) || 
    //    ( sInRightStr == "" ) || 
    //    ( sInsertStr  == "" ))
    //{
    //    return FALSE;
    //}
    //else
    //{
    //    // Do nothing
    //}

    switch ( lInMaxLength )
    {
        case INPUT_LENGTH_NASHI_MODE:
            lInMaxLength = INPUT_MAX_LENGTH_LIMIT;
            break;
        default:
            break;
    }

    sInputCnt       = sInLeftStr + sInRightStr;
    dwInputLength   = GetSize( sInputCnt );
    if ( lInMaxLength <= ( LONG ) dwInputLength ) 
    {
        bResult = FALSE;
    }
    else
    {
        bResult = TRUE;
        if ( ( ( LONG ) dwInputLength + ( LONG ) GetSize( sInsertStr ) ) <= lInMaxLength )
        {
            sResult = sInsertStr;
        }
        else
        {
            sResult = SubStr( sInsertStr, 0, lInMaxLength - ( LONG )GetSize( sInputCnt ));
        }
    }

    return bResult; 
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  TeikiShubeTsuDisplayFunc
//
//�@�\�@�@��@�F  
//
//�@�T�@�@�v�@�F  
//
//�@�߁@��@�l�F  
//
//�@���@�@���@�F  
//               
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/04/14    (TSDV) ThanhPH    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::TeikiShubeTsuDisplayFunc( const string &sInTagID )
{
    // �ϐ��̐錾.
    LONG                lProcResult           = GUI_RET_OK;                 // ��������.
    vector<string>      vTagIdSplit;                                        // �^�OID����.
    DWORD               dwLoopCount           = GUI_VALUE_ZERO_DWORD;                          // ���[�v�J�E���g�ϐ�.
    string              sBit                  = "";                         // ���[�v�J�E���g�ϐ�.
    vector<CItem*>      vSerchTagIdInfo;                                    // �^�OID�������.

    // �����`�F�b�N.
#if 0
    if( sInTagID == "")
    {
        // �G���[�R�[�h��Ԃ�.
        return ERROR_CODE_NULL;
    }
#endif

    vTagIdSplit = SplitString( sInTagID, "," );

    if( 2 != vTagIdSplit.size())
    {
        return ERROR_CODE_NULL;
    }
    else
    {
        // Do nothing
    }

    if( JUDGE_HALF_NUMBER != JudgeNumberFunc( vTagIdSplit[1] ))
    {
        // �G���[��Ԃ�.
        return ERROR_CODE_NOT_NUMBER;
    }
    else
    {
        // Do nothing
    }
// START: TrungLV Update javascript V10.25
     // �����ʖt�������X�V����
    for(dwLoopCount = 0; dwLoopCount < TEIKISHUBETU_BTN_DEFAULT_TABLE_SIZE; dwLoopCount++)
    {
        vSerchTagIdInfo = SearchTagIDFunc( TeikiShubetuBtn_Default_Table[dwLoopCount].sTagID, E_AREA_NULL );
        if ( 0 == vSerchTagIdInfo.size()) 
        {
            // �^�OID�����݂��Ȃ��ꍇ�́A���������s��.
            continue;
        }
        //�t������e�̍X�V
        lProcResult = TeikiShubeTsuBtnSubCtrlFunc(  vSerchTagIdInfo[0],
                                                    TeikiShubetuBtn_Default_Table[dwLoopCount].lDesign,
                                                    TeikiShubetuBtn_Default_Table[dwLoopCount].lVisible,
                                                    TeikiShubetuBtn_Default_Table[dwLoopCount].lEnable);
    }
// END: TrungLV Update javascript V10.25

    for( dwLoopCount = 0; dwLoopCount < TEIKISHUBETU_ZOKUSEI_TABLE_SIZE; dwLoopCount++ )
    {
        if( TeikiShubetu_Zokusei_Table[dwLoopCount].lLimit == -1 )
        {
            // �����������Ȃ��ꍇ�́A���������s��.
            continue;
        }
        else
        {
            // Do nothing
        }

        vSerchTagIdInfo = SearchTagIDFunc( TeikiShubetu_Zokusei_Table[dwLoopCount].sTagID, E_AREA_NULL );
        // If cannot find any item
        if( vSerchTagIdInfo.size() == 0 )
        {
            // ��ʂɑ��݂��Ȃ��ꍇ�́A�������s��Ȃ�.
            continue;
        }
        else
        {
            // Do nothing
        }

        sBit = SubStr( vTagIdSplit[1], TeikiShubetu_Zokusei_Table[dwLoopCount].lLimit, 1 );
        if( sBit == "1")
        {
            // �_�������E���A���t���䏈��.
            lProcResult = TeikiShubeTsuBtnCtrlFunc( vSerchTagIdInfo[0], dwLoopCount );
        }
        else
        {
            // ��������.
            lProcResult = ChangeClassIDFunc( vSerchTagIdInfo[0], DESIGN_BTN_OFF );
        }

        if( GUI_RET_OK != lProcResult )
        {
            return lProcResult;
        }

        // Re draw item
        vSerchTagIdInfo[0]->ItemUpdateState();
    }
    return lProcResult;
}



/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  TeikiShubeTsuBtnCtrlFunc
//
//�@�\�@�@��@�F  
//
//�@�T�@�@�v�@�F  
//
//�@�߁@��@�l�F  
//
//�@���@�@���@�F  
//               
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/04/14    (TSDV) ThanhPH    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG CGuiViewDlg::TeikiShubeTsuBtnCtrlFunc( CItem* lpInObjectCItem, LONG   lInZokuseiIdx )
{
    // �ϐ��̐錾.
    LONG            lProcResult         = GUI_RET_OK;                       // ��������.
    string          sOnOffGrp           = "";                               // �_�����O���[�v��.
    string          sStsDesign          = "";                               // �f�U�C��.
    DWORD           dwLoopCount         = 0U;                               // ���[�v�J�E���g�ϐ�.
    DWORD           dwCtrlFlg           = 0U;                               // ����t���O.
    vector<CItem*>  vSerchTagIdInfo;                                        // �^�OID�������.
    //bBtnUpdateCtrl
    vector<string>  vSts;                                                   // �X�e�[�^�X.
    BOOL            bBtnUpdateCtrl      = FALSE;
    // �����`�F�b�N.
    if( lpInObjectCItem == NULL ) 
    {
        // �G���[�R�[�h��Ԃ�.
        return ERROR_CODE_NULL;
    }

    // �I���^�l�[�g���ۂ�.
    if ( lInZokuseiIdx >= 0 )
    {
        if ( ZOKUSEI_ALTERNATE == TeikiShubetu_Zokusei_Table[lInZokuseiIdx].dwZokusei )
        {
            // �I���^�l�[�g�t����.
            sStsDesign = GetDesignStsFunc( lpInObjectCItem->m_sctProperty.sStatus );

            if ( sStsDesign == DESIGN_BTN_ON )
            {
                lProcResult = ChangeClassIDFunc( lpInObjectCItem, DESIGN_BTN_OFF );
            }
            else
            {
                lProcResult = ChangeClassIDFunc( lpInObjectCItem, DESIGN_BTN_ON );
            }
        }
        else
        {
            // �ʏ�t����.
            // �^�OID�_������.
            lProcResult = ChangeClassIDFunc( lpInObjectCItem, DESIGN_BTN_ON );

            if ( lProcResult == GUI_RET_OK )
            {
                // Do nothing
            }
            else
            {
                return lProcResult;
            }

            // ���_�����O���[�v�̖t�������ɂ���.
            sOnOffGrp = TeikiShubetu_Zokusei_Table[lInZokuseiIdx].sOnOffGrp;

            for( dwLoopCount = 0U; dwLoopCount < TEIKISHUBETU_ZOKUSEI_TABLE_SIZE; dwLoopCount++ )
            {
                // �����^�OID�̃C���f�b�N�X�Ɠ����ꍇ�͏������Ȃ�.
                if (lInZokuseiIdx == ( LONG ) dwLoopCount)
                {
                    continue;
                }
                else
                {
                    // Do nothing
                }

                // �_�����O���[�v����v���Ă���ꍇ�́A�����ɂ���.
                if ( TeikiShubetu_Zokusei_Table[dwLoopCount].sOnOffGrp == sOnOffGrp )
                {
                    vSerchTagIdInfo = SearchTagIDFunc( TeikiShubetu_Zokusei_Table[dwLoopCount].sTagID, E_AREA_NULL );
                    if( vSerchTagIdInfo.size() == 1 )
                    {
                        lProcResult = ChangeClassIDFunc( vSerchTagIdInfo[0], DESIGN_BTN_OFF );
                        if (GUI_RET_OK != lProcResult)
                        {
                            return lProcResult;
                        }
                        else
                        {
                            // Do nothing
                        }
                        vSerchTagIdInfo[0]->ItemUpdateState();
                    }
                    else
                    {
                        // Do nothing
                    }
                }
                else
                {
                    // Do nothing
                }
            }
        }

        lpInObjectCItem->ItemUpdateState();

        // ����t���O�ɂ��t������s��.
        dwCtrlFlg = TeikiShubetu_Zokusei_Table[lInZokuseiIdx].dwCtrlFlg;

        if ( dwCtrlFlg == CTRLFLG_NASHI ) 
        {
            // Do nothing
        }
        else
        {
            for( dwLoopCount = 0; dwLoopCount < ARRAY_LENGTH(TeikiShubetu_Ctrl_Table); dwLoopCount++ )
            {
                // ���䌳�t���O�����ʖ��́A����t���O����v���Ă���ꍇ�A�������s��.
                if (( CTRLFLG_COMMON == ( DWORD )TeikiShubetu_Ctrl_Table[dwLoopCount].lExCtrlFlag ) || 
                    ( dwCtrlFlg      == ( DWORD )TeikiShubetu_Ctrl_Table[dwLoopCount].lExCtrlFlag ))
                {
                    vSerchTagIdInfo = SearchTagIDFunc( TeikiShubetu_Ctrl_Table[dwLoopCount].sTagID, E_AREA_NULL );
                    if ( vSerchTagIdInfo.size() == 0 )
                    {
                        // �^�OID�����݂��Ȃ��ꍇ�́A���������s��.
                        continue;
                    }
                    else
                    {
                        // Do nothing
                    }
// TSDV(TrungLV) 20150424: remove follows update javascript ( v10.14->v10.25)
#if 0
                    // �\���E��\��
                    switch ( TeikiShubetu_Ctrl_Table[dwLoopCount].lVisible )
                    {
                    case VISIBLE_VISIBLE: // �\��.
                        lProcResult = ChangeClassIDFunc( vSerchTagIdInfo[0], DESIGN_VISIBLE );
                        break;

                    case VISIBLE_HIDDEN: // ��\��.
                        lProcResult = ChangeClassIDFunc( vSerchTagIdInfo[0], DESIGN_HIDDEN );
                        break;

                    case VISIBLE_NOCAHNGE:// �ύX�Ȃ�.
                    default: // ���̑�.
                        lProcResult = GUI_RET_OK;
                        break;
                    }

                    if ( lProcResult == GUI_RET_OK )
                    {
                        // Do nothing
                    }
                    else
                    {
                        return lProcResult;
                    }

                    // �_����
                    switch ( TeikiShubetu_Ctrl_Table[dwLoopCount].lOnOff ) 
                    {
                    case ONOFF_ON: // �_��.
                        lProcResult = ChangeClassIDFunc( vSerchTagIdInfo[0], DESIGN_BTN_ON );
                        break;
                    case ONOFF_OFF: // ����.
                        lProcResult = ChangeClassIDFunc( vSerchTagIdInfo[0], DESIGN_BTN_OFF );
                        break;
                    case ONOFF_DISABLE: // �񊈐�.
                        lProcResult = ChangeClassIDFunc( vSerchTagIdInfo[0], DESIGN_DISABLE );
                        break;
                    case ONOFF_NOCAHNGE:// �ύX�Ȃ�.
                    default: // ���̑�.
                        lProcResult = GUI_RET_OK;
                        break;
                    }

                    if ( lProcResult == GUI_RET_OK ) 
                    {
                        // Do nothing
                    }
                    else
                    {
                        return lProcResult;
                    }

                    // �����E�񊈐�.
                    
                    switch ( TeikiShubetu_Ctrl_Table[dwLoopCount].lEnable ) 
                    {
                    case ENABLE_ENABLE: // ����.
                        vSerchTagIdInfo[0]->UpdateEnable( TRUE );
                        break;

                    case ENABLE_DISABLE: // �񊈐�.
                        vSerchTagIdInfo[0]->UpdateEnable( FALSE );
                        break;

                    case ENABLE_NOCAHNGE:// �ύX�Ȃ�.
                    default: // ���̑�.
                        break;
                    }
#endif
// START: TrungLV(20150424) update javascript v10.25
                    bBtnUpdateCtrl = TeikiShubeTsuJudgeConditionOnGrpFunc( dwLoopCount );
                    if ( bBtnUpdateCtrl == FALSE )
                    {
                        continue;
                    }
                    //�t������e�̍X�V
                    lProcResult = TeikiShubeTsuBtnSubCtrlFunc( vSerchTagIdInfo[0],
                                                               TeikiShubetu_Ctrl_Table[dwLoopCount].lOnOff,
                                                               TeikiShubetu_Ctrl_Table[dwLoopCount].lVisible,
                                                               TeikiShubetu_Ctrl_Table[dwLoopCount].lEnable );
                    // END: TrungLV(20150424) update javascript v10.25
                    vSerchTagIdInfo[0]->ItemUpdateState();
                }
            }
        }
    }
    else
    {
        // Do nothing
    }

    return lProcResult;
}
LONG CGuiViewDlg::TeikiShubeTsuJudgeConditionOnGrpFunc( DWORD dwInCtrlTblIdx )
{
    // LONG           lRet              = GUI_RET_OK; ==> no need this variable
    BOOL           bResult           = TRUE; // ��������.
    string         strConditionOnGrp = ""; // �����O���[�v.
    string         strStsDesign      = ""; // �f�U�C��.
    DWORD          nRoopCount        = 0; // ���[�v�J�E���g�ϐ�.
    vector<CItem*> arySerchTagIdInfo; // �^�OID�������.
    // BOOL           bBreak       = FALSE;
    DWORD          dwArrayLength = 0;
    // ��������_���O���[�v�܂Ő�����s��.
    DWORD          dwCondionNo = 0; // ����No.
    dwCondionNo = 1;

    // LiemTT update Js 20150427
    if ( TeikiShubetu_Ctrl_Table[dwInCtrlTblIdx].sConditionOnGrp_1 != NOT_SET_STR )
    {
        strConditionOnGrp = TeikiShubetu_Ctrl_Table[dwInCtrlTblIdx].sConditionOnGrp_1;
        dwArrayLength = ARRAY_LENGTH( TeikiShubetu_Zokusei_Table );
        for ( nRoopCount = 0; nRoopCount < dwArrayLength; ++nRoopCount )
        {
            if ( strConditionOnGrp != TeikiShubetu_Zokusei_Table[nRoopCount].sOnOffGrp )
            {
                continue;
            }
            bResult = false;
            // �^�OID���擾���ăf�U�C���𔻒肷��B
            arySerchTagIdInfo = SearchTagIDFunc( TeikiShubetu_Zokusei_Table[nRoopCount].sTagID, E_AREA_NULL );
            if ( 1 == arySerchTagIdInfo.size() )
            {
                strStsDesign = GetDesignStsFunc( arySerchTagIdInfo[0]->m_sctProperty.sStatus );
                if ( DESIGN_BTN_ON == strStsDesign )
                {
                    // �f�U�C�����_���̏ꍇ�́A����OK�Ƃ���B
                    bResult = true;
                    break;
                }
            }
        }
    }
    else {} // Do nothing
    // end update js 20150427


    // LiemTT review and update 20150427
#if 0
    while( 1 )
    {
        switch( dwCondionNo )
        {
            case 1: strConditionOnGrp = TeikiShubetu_Ctrl_Table[dwInCtrlTblIdx].sConditionOnGrp_1;
                break;
            default:
                bBreak = TRUE;
                break;
        }

        if ( bBreak )
        {
            break;
        }

        for(nRoopCount = 0; nRoopCount < TEIKISHUBETU_ZOKUSEI_TABLE_SIZE; nRoopCount++) 
        {
            // �_�����O���[�v����v���Ă��邩���肷��.
            if ( strConditionOnGrp != TeikiShubetu_Zokusei_Table[nRoopCount].sOnOffGrp)
            {
                continue;
            }
            bResult = false;
            // �^�OID���擾���ăf�U�C���𔻒肷��B
            arySerchTagIdInfo = SearchTagIDFunc( TeikiShubetu_Zokusei_Table[nRoopCount].sTagID, E_AREA_NULL );
            if ( 1 == arySerchTagIdInfo.size())
            {
                strStsDesign = GetDesignStsFunc(arySerchTagIdInfo[0]->m_sctProperty.sStatus );
                if ( DESIGN_BTN_ON == strStsDesign) 
                {
                    // �f�U�C�����_���̏ꍇ�́A����OK�Ƃ���B
                    bResult = true;
                    break;
                }
            }
        }
        // �O���[�v�̏�����NG�̏ꍇ�́A�����I������
        if ( bResult )
        {
            break;
        }

        dwCondionNo = dwCondionNo + 1;
    }


    return lRet;
#endif // End review and update

    return bResult;
}
VOID CGuiViewDlg::CreateSeinenGappi( CItem* lpInItem, const string &sInStr )
{
    DWORD   dwLeft   = 0;
    DWORD   dwTop    = 0;
    DWORD   dwWidth  = 0;
    DWORD   dwHeight = 0;
    string   sText      = ""; 
    string   sSpanClass = "";
    string   sSpanText  = "";
    string  sSecondText = "";
    DWORD    dwPos      = 0;
    DWORD    dwCnt      = 0;
    CItem         *lpcItem = NULL;
    TEXTMETRIC   tm = { 0 };
    CDC*         pDC      = new CDC();
    CFont*         lpFont   = new CFont();
    vector<SCT_SPAN>    vEmptySpan;
    lpFont->CreatePointFont( lpInItem->m_sctProperty.dwFontSize, MS_GOTHIC, pDC );
    pDC->SelectObject( lpFont );
    pDC->GetTextMetrics( &tm );

    dwLeft = lpInItem->m_sctProperty.dwLeft + tm.tmAveCharWidth * GetSize(lpInItem->m_sctProperty.sText);
    dwTop  = lpInItem->m_sctProperty.dwTop;
    dwWidth  = lpInItem->m_sctProperty.dwWidth;
    dwHeight  = lpInItem->m_sctProperty.dwHeight;

    if ((dwPos = sInStr.find_first_of(">"))!= string::npos )
    {
        sText = SubStr(sInStr, dwPos, SEINEN_GAPPI_SIZE );
    }
    // Create <div class='nen'>[�f�f�d�d]\n[��������]</div>
    lpcItem = new CRichLabel();
    lpcItem->SetProperties( 
                 1,                                                                  
                 // Start ThietNP 2015-07-28 Change control ID
                 // (0xfff00000 + lpInItem->m_sctProperty.dwCtrlID),  
                 IDCTRL_ITEM,
                 // End ThietNP 2015-07-28 Change control ID                 
                 "div", 
                 sText.c_str() , 
                 dwLeft, 
                 dwTop, 
                 dwWidth,
                 dwHeight, 
                 1, 
                 0, 
                 1,
                 "", 
                 "", 
                 "", 
                 "", 
                 "", 
                 "", 
                 "", 
                 "", 
                 "",
                 0, 
                 99, 
                 "", 
                 "", 
                 "", 
                 "", 
                 "", 
                 "nen", 
                 "",
                 lpInItem->m_sctProperty.dwFontSize, 
                 0, 
                 -1, 
                 -1, 
                 "", 
                 "", 
                 0, 
                 vEmptySpan, 
                 "", 
                 "", 
                 lpInItem->m_sctProperty.eAreaType, 
                 1, 
                 -1, 
                 0, 
                 0 );

    lpInItem->m_vobjItems.push_back( lpcItem );
    lpcItem->CreateItem( this );

    // Create <span class='[XXXX]'>�N[�l�l]��[�c�c]��</span>
    if ((dwPos = sInStr.find_first_of("<span class='"))!= string::npos )
    {
        for ( dwCnt = dwPos ; dwCnt < sInStr.size(); dwCnt++ )
        {
            if ( sInStr[dwCnt] == '\'' )
            {
                break;
            }
            sSpanClass += sInStr[dwCnt];
        }
        //sSpanClass = SubStr(sInStr, dwPos, SPAN_CLASS_SIZE );
    }
    // Get text of span
    if ((dwPos = sInStr.find_first_of(">�N"))!= string::npos )
    {
        sSpanText = "�N"+SubStr(sInStr, dwPos, SPAN_TEXT_SIZE );
    }

    if (( dwPos = sText.find("\n")) != string::npos )
    {
        sSecondText = SubStr( sText, dwPos );
    }
    
    dwLeft  += tm.tmAveCharWidth * GetSize(sSecondText );
    dwTop   += tm.tmHeight ;
    dwWidth -= tm.tmAveCharWidth * GetSize(sSecondText );

    lpcItem = new CRichLabel();
    lpcItem->SetProperties( 
                 1,
                 // Start ThietNP 2015-07-28 Change control ID
                 // (0xfff00001 + lpInItem->m_sctProperty.dwCtrlID),  
                 IDCTRL_ITEM,
                 // End ThietNP 2015-07-28 Change control ID                  
                 "span", 
                 sSpanText.c_str() , 
                 dwLeft, 
                 dwTop, 
                 dwWidth,
                 dwHeight, 
                 1, 
                 0, 
                 1,
                 "", 
                 "", 
                 "", 
                 "", 
                 "", 
                 "", 
                 "", 
                 "", 
                 "",
                 0, 
                 99, 
                 "", 
                 "", 
                 "", 
                 "", 
                 "", 
                 sSpanClass.c_str(), 
                 "",
                 lpInItem->m_sctProperty.dwFontSize, 
                 0, 
                 -1, 
                 -1, 
                 "", 
                 "", 
                 0, 
                 vEmptySpan, 
                 "", 
                 "", 
                 lpInItem->m_sctProperty.eAreaType, 
                 1, 
                 -1, 
                 0, 
                 0 );

    lpInItem->m_vobjItems.push_back( lpcItem );
    lpcItem->CreateItem( this );

    pDC->DeleteDC();
    delete pDC;
    lpFont->DeleteObject();
    delete lpFont;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  TeikiShubeTsuBtnSubCtrlFunc
//
//�@�\�@�@��@�F  Sub control of process ������ button
//
//�@�T�@�@�v�@�F  
//
//�@�߁@��@�l�F  
//
//�@���@�@���@�F  
//               
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/04/24    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG  CGuiViewDlg::TeikiShubeTsuBtnSubCtrlFunc(CItem* lpInTagID,
                                    DWORD dwInDesign,
                                    DWORD  dwInVisible,
                                    DWORD  dwInEnable)
{
    LONG    lRet        = GUI_RET_OK;
    string  sStatus     = "";
    if ( lpInTagID == NULL )
    {
        return ERROR_CODE_NULL;
    }

     // �f�U�C��
    switch (dwInDesign) {
        case ONOFF_ON: // �_��.
            lRet = ChangeClassIDFunc( lpInTagID, DESIGN_BTN_ON );
            break;
        case ONOFF_OFF: // ����.
            lRet = ChangeClassIDFunc( lpInTagID, DESIGN_BTN_OFF );
            break;
        case ONOFF_DISABLE: // �񊈐�.
            lRet = ChangeClassIDFunc( lpInTagID, DESIGN_DISABLE );
            break;
        case ONOFF_NOCAHNGE:// �ύX�Ȃ�.
        default: // ���̑�.
            lRet = GUI_RET_OK;
            break;
    }

    if ( GUI_RET_OK != lRet)
    {
        return lRet;
    }

        // �\���E��\��
    switch (dwInVisible) {
        case VISIBLE_VISIBLE: // �\��.
            lRet = ChangeClassIDFunc( lpInTagID, DESIGN_VISIBLE);
            break;
        case VISIBLE_HIDDEN: // ��\��.
            lRet = ChangeClassIDFunc( lpInTagID, DESIGN_HIDDEN);
            break;
        case VISIBLE_NOCAHNGE:// �ύX�Ȃ�.
        default: // ���̑�.
            lRet = GUI_RET_OK;
            break;
    }
    if ( GUI_RET_OK != lRet)
    {
        return lRet;
    }

      // �����E�񊈐�.
    sStatus = lpInTagID->m_sctProperty.sStatus;
    switch ( dwInEnable )
    {
        case ENABLE_ENABLE: // ����.
            lpInTagID->UpdateEnable( TRUE );
            break;
        case ENABLE_DISABLE: // �񊈐�.
            lpInTagID->UpdateEnable( FALSE );
            break;
        case ENABLE_NOCAHNGE:// �ύX�Ȃ�.
        default: // ���̑�.
            break;
    }

    return lRet;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  JudgeBlankInputStrFunc
//
//�@�\�@�@��@�F  JudgeBlankInputStrFunc
//
//�@�T�@�@�v�@�F  
//
//�@�߁@��@�l�F  
//
//�@���@�@���@�F  
//               
//
//  �o�[�W�����@     ���t          ����              ���l
//  LVT-01.00.00    2015/05/22    (TSDV) TrungLV    Create New
//
//�@(C)Copyright TOSHIBA CORPORATION 2015. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CGuiViewDlg::JudgeBlankInputStrFunc( const string &sInDispText, const string &sInUpdateCharacter ) 
{
    // �ϐ��̐錾.
    LONG   lJudgeNumber   = 0; // ���l���茋��.
    string sOutData       = "";
    LONG   lIsertNum      = 0;  // �}�������񐔒l�ϊ�.

    // �����`�F�b�N.
    if (sInDispText == NULL_STR )
    {
        return false;
    }
    else
    {
        // Do nothing
    }

    if ( sInUpdateCharacter == NULL_STR )
    {
        return false;
    }
    else
    {
        // Do nothing
    }

    // �u�����N�̏ꍇ�̂�.
    if (( sInDispText               == ""          ) || 
        ( gsctInputFormat.sInitDisp == sInDispText ))
    {
        // �u�����N��0�}������
        if ( gsctInputFormat.bBlankZero == TRUE )
        {
            lJudgeNumber = JudgeNumberFunc( sInUpdateCharacter );
            if (( lJudgeNumber == JUDGE_FULL_NUMBER ) || 
                ( lJudgeNumber == JUDGE_HALF_NUMBER ))
            {
                ConvFullHalNumberFunc( sInUpdateCharacter, true , sOutData );
                lIsertNum = atol( sOutData.c_str());
                // ���l�ϊ��������ʁA0�̏ꍇ�͏������I������B
                if ( lIsertNum == 0 ) 
                {
                    return false;
                }
                else
                {
                    // Do nothing
                }
            }
            else
            {
                // Do nothing
            }
        }
        else
        {
            // Do nothing
        }

        // �u�����N���X�y�[�X�}������
        if ( gsctInputFormat.bBlankSpace == TRUE )
        {
            if ( regex_search( sInUpdateCharacter, regex( "^[ �@]+$" )))
            {
                return false;
            }
        }
    }
    else
    {
        // Do nothing
    }

    // �}��OK��Ԃ�.
    return true; 
}


/**
*
* �y�x���\�����䏈��.
*
* @returns {String} ��������
*
* @version 2015-05-14  NEXA-V01.00  (���a) ���� ����  �V�K�쐬
*
*/
LONG CGuiViewDlg::CtrlDispHolidayFunc() 
{
    // �ϐ��̐錾.
    LONG           lProcResult          = GUI_RET_OK;               // ��������.
    string         sSetVisivleHeddin    = "";                       // �\��/��\���ݒ�.
    DWORD          dwRoopCount          = GUI_VALUE_ZERO_DWORD;     // ���[�v�J�E���g�ϐ�.
    LONGLONG       nNextProcTime;                                   // �����ԏ���.
    vector<CItem*> arySerchTagIdInfo;                               // �^�OID��������.
    SCT_DATE       objSystemate;                                    // �V�X�e�����t�I�u�W�F�N�g.
    SCT_DATE       objOpeDateTime;                                  // �^�p���؂�ւ�����.
    SCT_DATE       objJudgeDate;                                    // ������t.
    SCT_DATE       objResultDate;                                   // ���ݓ����茋��.
    SCT_DATE       sctTempDate;
    LONG           lReSult              = GUI_VALUE_ZERO_LONG;
    BOOL           bRet                 = FALSE; 
    string         sWeekDay             = "";
    // Reset data
    arySerchTagIdInfo.clear();
    ( VOID )memset( &objSystemate, 0x00, sizeof( objSystemate ));
    ( VOID )memset( &objOpeDateTime, 0x00, sizeof( objOpeDateTime ));
    ( VOID )memset( &objJudgeDate, 0x00, sizeof( objJudgeDate ));
    ( VOID )memset( &objResultDate, 0x00, sizeof( objResultDate ));
    ( VOID )memset( &sctTempDate, 0x00, sizeof( sctTempDate ));


    // �y�x�����ڎ擾.
    arySerchTagIdInfo = SearchTagIDFunc( TAG_ID_HOLIDAY, E_AREA_NULL );
    if ( 0 == arySerchTagIdInfo.size())
    {
        // �擾�s�̏ꍇ�́A�������I������.
        return GUI_RET_OK;
    }

    //// �j���ݒ�^�C�}���ݒ肳��Ă���ꍇ�́A�^�C�}���~����B
    if ( gSetHolidayDispTimer == TRUE )
    {
        this->KillTimer( DISP_HOLIDAY_TIMER );
    }
    else
    {
        // Do nothing
    }

    // �V�X�e�����t�E�^�p���؂�ւ������̎擾.
    // Get current date
    objSystemate = GetCurrentDateTime();
    sctTempDate  = SCT_DATE( objSystemate.wYear, objSystemate.byMonth, objSystemate.byDay );
    JudgeDateValidityFunc(sctTempDate, &objResultDate, lReSult );
    if ( lReSult )
    {
        objOpeDateTime = objResultDate;
    }
    else
    {
        return ERROR_CODE_NOT_DATE;
    }

    // ���ݎ����Ɖ^�p���؂�ւ������ɂ�蔻�肷����t�����肷��.�i0��0���̏ꍇ�́A�V�X�e�����t)
    objJudgeDate = objSystemate;
    if ( 0 != objOpeDateTime.wHour || 0 != objOpeDateTime.wMinutes )
    {
        // ���ݎ������^�p���؂�ւ������O�̏ꍇ�́A�V�X�e�����t�̑O���Ƃ���
        if (objSystemate < objOpeDateTime) 
        {
            // TSDV-LanLTM-20150901-Fix bug No10: Date time error when displaying icon �g�y�x���h
            // objJudgeDate.byDay = objJudgeDate.byDay - 1;
            objJudgeDate = AddDay( -1, objJudgeDate );
            // TSDV-LanLTM-20150901-Fix bug No10-END
        }
    }

    // ������t�ɂ��y�x���̕\��/��\���𔻒肷��.
    sSetVisivleHeddin = DESIGN_HIDDEN;
    sWeekDay = CalculationWeekFunc( objJudgeDate );
    if (( sWeekDay == DAY_OF_WEEK_SUNDAY ) || ( sWeekDay == DAY_OF_WEEK_SATURDAY ))
    {
        // ���t���y�x���̏ꍇ�́A�\������.
        sSetVisivleHeddin = DESIGN_VISIBLE;
    } 
    else 
    {
        //������t�Ɠo�^�j���f�[�^����v���Ă��邩���肷��.
        for ( dwRoopCount = 0; dwRoopCount < gsctHolidayArray.size(); dwRoopCount++ ) 
        {
            // ���ݓ��`�F�b�N�̎��s.
            bRet = JudgeDateValidityFunc( gsctHolidayArray[dwRoopCount], &objResultDate, lReSult );
            if ( bRet == FALSE )
            {
                continue;
            }
            if (( objJudgeDate.wYear     == objResultDate.wYear   ) && 
                ( objJudgeDate.byMonth   == objResultDate.byMonth ) &&
                ( objJudgeDate.byDay     == objResultDate.byDay   ))
            {
                // �j���ƈ�v���Ă���ꍇ�͕\������.
                sSetVisivleHeddin = DESIGN_VISIBLE;
                break;
            }
        }
    }

    // �y�x���̕\���ύX����.
    for ( dwRoopCount = 0; dwRoopCount < arySerchTagIdInfo.size(); dwRoopCount++ )
    {
        lProcResult = ChangeClassIDFunc( arySerchTagIdInfo[dwRoopCount], sSetVisivleHeddin );
        if ( lProcResult != GUI_RET_OK )
        {
            break;
        }
    }

    // ���ݎ����������̉^�p���؂�ւ��������v�Z���A�^�C�}��ݒ肷��
    if (objOpeDateTime <= objSystemate )
    {
        // ���ݎ������^�p�����𒴂��Ă���ꍇ
        // TSDV-LanLTM-20150901-Fix bug No10: Date time error when displaying icon �g�y�x���h
        // objOpeDateTime.byDay = objOpeDateTime.byDay + 1;
        objOpeDateTime = AddDay( 1, objOpeDateTime );
        // TSDV-LanLTM-20150901-Fix bug No10-END
    }

    nNextProcTime = GetMiliSeconds( objOpeDateTime, objSystemate );
    if ( SetTimer( DISP_HOLIDAY_TIMER, ( UINT ) nNextProcTime, NULL ) )
    {
        gSetHolidayDispTimer = TRUE;
    }
    else
    {
        gSetHolidayDispTimer = FALSE;
    }

    return lProcResult;
}
