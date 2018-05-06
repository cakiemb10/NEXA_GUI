#include "stdafx.h"
#include "CommonSct.h"
#include "GUIDItem.h"
#include <string>
#include <vector>


extern SCT_DATE             gsctOperationDate;                      // Operation date global parameter
extern vector<SCT_DATE>     gvHolidayArray;                         // Holiday array global parameter
extern SCT_DATE             gsctBasicDate;                          // Basic Date
extern SCT_DATE             gsctStartDate;                          // Start Date
extern SCT_DATE             gsctEndDate;                            // End Date
extern SCT_DATE             gsctDispDate;                           // Display Date;
extern CItem*               gclInputItemTag;                        // Input Item
extern SCT_FORMAT_TABLE     gsctInputFormat;                        // Input Item format
extern DWORD                gsViewErrorDesign;                      // Display Error Design
extern DWORD                gdwViewErrorBlinkCnt;                   // Blink count
extern DWORD                gdwViewErrorResolutive;                 // View Error Resolutive
extern DWORD                gdwFlgDispZeroPadding;                  // Displaying Zero Padding
extern vector<string>       gsInputItemBeforeData;                  // Array of previous data of input items
extern BOOL                 gbInputItemFirstInitializationFlg;      // Flag to check whether Input Item is First initialization or not
extern CItem*               gclCursorImageTag;                      // Cursor object
extern LONG                 glRelativeCurPos;                       // Relative cursor position
extern AREA_ENUM            geInputItemArea;                        // Area type of input item
extern BOOL                 gbPageChageLoadFlg;                     // Flag to check load page change or not
extern LONG                 glWaitResponseDenbunNo;                 // Message number of message that is being waited
