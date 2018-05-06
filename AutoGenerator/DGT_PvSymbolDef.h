/* [%START%;%FileHeader%] */
/***********************************************************************

    ファイル名: DGT_PvSymbolDef.h

    表題      : DIALOGGENモジュール 内部define宣言ヘッダファイル

    内容      : DIALOGGENモジュール で使用する既定値を宣言する

    適用機種  : PASMOモジュール (ESSICMPB)

***********************************************************************/

#ifndef DGT_PVSYMBOLDEF_H
#define DGT_PVSYMBOLDEF_H
/* [%END  %;%FileHeader%] */


/* [%START%;%シンボル名%;CheckInputValidation symbol] */
#define DGT_GGD_CIV_PATH_OK                                         (0x0000)        /* Folder path is valid */
#define DGT_GGD_CIV_SPEC_NULL                                       (0x0001)        /* Folder path is empty */
#define DGT_GGD_CIV_SPEC_INVALID                                    (0x0002)        /* Folder path is invalid */
#define DGT_GGD_CIV_SPEC_TOO_LONG                                   (0x0003)        /* Folder path > 260 character */
#define DGT_GGD_CIV_CATA_NULL                                       (0x0004)        /* Folder path is empty */
#define DGT_GGD_CIV_CATA_INVALID                                    (0x0005)        /* Folder path is invalid */
#define DGT_GGD_CIV_CATA_TOO_LONG                                   (0x0006)        /* Folder path > 260 character */
#define DGT_GGD_CIV_CSV_NULL                                        (0x0007)        /* Folder path is empty */
#define DGT_GGD_CIV_CSV_INVALID                                     (0x0008)        /* Folder path is invalid */
#define DGT_GGD_CIV_CSV_TOO_LONG                                    (0x0009)        /* Folder path > 260 character */
#define DGT_GGD_CIV_OUT_NULL                                        (0x000a)        /* Folder path is empty */
#define DGT_GGD_CIV_OUT_INVALID                                     (0x000b)        /* Folder path is invalid */
#define DGT_GGD_CIV_OUT_TOO_LONG                                    (0x000c)        /* Folder path > 260 character */
/* [%END  %;%シンボル名%;CheckInputValidation symbol] */

/* [%START%;%シンボル名%;Mark symbol] */
#define DGT_SD_US_STATUS                                            (0x01)          /* Bit of updating status */
#define DGT_SD_US_PERCENT                                           (0x02)          /* Bit of updating percent */
#define DGT_SD_US_LOG                                               (0x04)          /* Bit of updating log */
/* [%END  %;%シンボル名%;Mark symbol] */

/* [%START%;%シンボル名%;Mark symbol] */
#define DGT_CFW_WA_CREATE_AREA                                      ("// CREATE AREA HERE")/* Mark of creating area */
#define DGT_CFW_WA_PROTOTYPE                                        ("// CREATE PROTOTYPE HERE")/* Mark of creating prototype */
#define DGT_CFW_WA_FUNC_MAP                                         ("// CREATE FUNCTION MAPPING HERE")/* Mark of creating function mapping */
#define DGT_CFW_WA_VCXPROJ                                          ("<ClCompile Include=\"AreaStore.cpp\" />")/* Mark of creating filter */
/* [%END  %;%シンボル名%;Mark symbol] */

/* [%START%;%シンボル名%;CheckFilePath symbol] */
#define DGT_U_CFIP_PATH_OK                                          (0x0001)        /* Folder path is valid */
#define DGT_U_CFIP_PATH_NULL                                        (0x0002)        /* Folder path is empty */
#define DGT_U_CFIP_PATH_INVALID                                     (0x0003)        /* Folder path is invalid */
#define DGT_U_CFIP_PATH_TOO_LONG                                    (0x0004)        /* Folder path > 218 character */
/* [%END  %;%シンボル名%;CheckFilePath symbol] */

/* [%START%;%シンボル名%;CheckFolderPath symbol] */
#define DGT_U_CFP_PATH_OK                                           (0x0001)        /* Folder path is valid */
#define DGT_U_CFP_PATH_NULL                                         (0x0002)        /* Folder path is empty */
#define DGT_U_CFP_PATH_INVALID                                      (0x0003)        /* Folder path is invalid */
#define DGT_U_CFP_PATH_TOO_LONG                                     (0x0004)        /* Folder path > 218 character */
/* [%END  %;%シンボル名%;CheckFolderPath symbol] */

#endif /* DGT_PVSYMBOLDEF_H */

/***********************************************************************

    EOF

***********************************************************************/
