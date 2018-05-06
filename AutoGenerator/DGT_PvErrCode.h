/* [%START%;%FileHeader%] */
/***********************************************************************

    ファイル名: DGT_PvErrCode.h

    表題      : DIALOGGENモジュール内部エラーコード宣言ヘッダファイル

    内容      : DIALOGGENモジュールで使用する内部エラーコードを宣言する

    適用機種  : PASMOモジュール (ESSICMPB)

    バージョン: YYYY-MM-DD    ESSICMPB-V01.00.00  作成者記入        新規作成

    (C)Copyright Toshiba Corporation 2015. All rights reserved.

***********************************************************************/

#ifndef DGT_PVERRCODE_H
#define DGT_PVERRCODE_H
/* [%END  %;%FileHeader%] */


/* [%START%;%ErrorCode%;CheckInputValidation] */
#define DGT_ERR_GGD_CIV_PARA                                            (0x01010801)    /* Parameters are abnormal */
/* [%END  %;%ErrorCode%;CheckInputValidation] */

/* [%START%;%ErrorCode%;GenerateTemplateFiles] */
#define DGT_PJG_GTF_COPY_ERROR                                          (0x01030201)    /* Copy template file occur error */
/* [%END  %;%ErrorCode%;GenerateTemplateFiles] */

/* [%START%;%ErrorCode%;Log] */
#define DGT_ERR_CLG_LOG_WRITE_FAIL                                      (0x01050501)    /* Write log fail */
/* [%END  %;%ErrorCode%;Log] */

/* [%START%;%ErrorCode%;WriteAt] */
#define DGT_ERR_CFW_WA_MARK_NOT_FOUND                                   (0x01060101)    /* Mark not found */
#define DGT_ERR_CFW_WA_WRITE_FAIL                                       (0x01060102)    /* Write fail */
/* [%END  %;%ErrorCode%;WriteAt] */

/* [%START%;%ErrorCode%;ReadScript] */
/* [%END  %;%ErrorCode%;ReadScript] */

/* [%START%;%ErrorCode%;ReadCSVList] */
/* [%END  %;%ErrorCode%;ReadCSVList] */

/* [%START%;%ErrorCode%;ReadFormatList] */
#define DGT_ERR_CSR_RFL_OPEN_FILE                                       (0x01070300)    /* Open file is error */
#define DGT_ERR_CSR_RFL_INVALID_FORMAT                                  (0x01070301)    /* Format list file is invalid format */
/* [%END  %;%ErrorCode%;ReadFormatList] */

/* [%START%;%ErrorCode%;ReadAreaList] */
#define DGT_ERR_CSR_RAL_OPEN_FILE                                       (0x01070400)    /* Open file is error */
#define DGT_ERR_CSR_RAL_INVALID_FORMAT                                  (0x01070401)    /* area list file is invalid format */
/* [%END  %;%ErrorCode%;ReadAreaList] */

/* [%START%;%ErrorCode%;ReadTagList] */
#define DGT_ERR_CSR_RTL_OPEN_FILE                                       (0x01070500)    /* Open file is error */
#define DGT_ERR_CSR_RTL_INVALID_FORMAT                                  (0x01070501)    /* tag list file is invalid format */
/* [%END  %;%ErrorCode%;ReadTagList] */

/* [%START%;%ErrorCode%;ReadLimitList] */
#define DGT_ERR_CSR_RLL_OPEN_FILE                                       (0x01070600)    /* Open file is error */
#define DGT_ERR_CSR_RLL_INVALID_FORMAT                                  (0x01070601)    /* limit list file is invalid format */
/* [%END  %;%ErrorCode%;ReadLimitList] */

#define DGT_ERR_APPEND_ERR                                              (0x01070901)

/* [%START%;%ErrorCode%;ReadInitList] */
#define DGT_ERR_CSR_RIL_OPEN_FILE                                       (0x01070700)    /* Open file is error */
#define DGT_ERR_CSR_RIL_INVALID_FORMAT                                  (0x01070701)    /* initial file is invalid format */
/* [%END  %;%ErrorCode%;ReadInitList] */

/* [%START%;%ErrorCode%;ReadCatalog] */
#define DGT_ERR_CSR_RCTL_OPEN_FILE                                      (0x01070800)    /* Open file is error */
#define DGT_ERR_CSR_RCTL_INVALID_FORMAT                                 (0x01070801)    /* Format list file is invalid format */
#define DGT_ERR_CSR_RCTL_PARA                                           (0x01070802)    /* parameter error */
/* [%END  %;%ErrorCode%;ReadCatalog] */

/* [%START%;%ErrorCode%;SearchFormatInfor] */
#define DGT_ERR_CSR_SCTL_AREA_NOT_EXIST                                 (0x01070900)    /* Area is not exist in area list */
#define DGT_ERR_CSR_SCTL_NOT_FOUND                                      (0x01070901)    /* Catalog is not found */
/* [%END  %;%ErrorCode%;SearchFormatInfor] */

/* [%START%;%ErrorCode%;ReadScreenList] */
#define DGT_ERR_CSR_RSL_PATH_INVALID                                    (0x01070A00)    /* Screen list folder path is invalid */
/* [%END  %;%ErrorCode%;ReadScreenList] */

/* [%START%;%ErrorCode%;ReadEachScreenFile] */
#define DGT_ERR_CSR_RESF_PATH_INVALID                                   (0x01070B00)    /* Read each screen file */
/* [%END  %;%ErrorCode%;ReadEachScreenFile] */

/* [%START%;%ErrorCode%;GetMasterList] */
/* [%END  %;%ErrorCode%;GetMasterList] */
#define DGT_ERR_CSR_RFL_PARA                                            ( 0x01070C00 )
#define DGT_ERR_CSR_RAL_PARA                                            ( 0x01070D00 )
#define DGT_ERR_CSR_RTL_PARA                                            ( 0x01070E00 )
#define DGT_ERR_CSR_RLL_PARA                                            ( 0x01070F00 )

#define DGT_ERR_CSR_RIL_PARA                                            ( 0x01071000 )
#define DGT_ERR_CSR_RCTL_FILE_PATH                                      ( 0x01071100 )
#define DGT_ERR_CSR_SCTL_CATALOG_NOT_EXIST                              ( 0x01071101 )
#define DGT_ERR_CSR_CIV_AU_FOLDER_INVALID                               ( 0x01071200 )
#define DGT_ERR_CSR_CIV_MA_FOLDER_INVALID                               ( 0x01071201 )
#define DGT_ERR_CSR_CIV_SC_FOLDER_INVALID                               ( 0x01071202 )
#define DGT_ERR_CSR_CIV_FMT_FILE_INVALID                                ( 0x01071203 )
#define DGT_ERR_CSR_CIV_AREA_FILE_INVALID                               ( 0x01071204 )
#define DGT_ERR_CSR_CIV_LIMIT_FILE_INVALID                              ( 0x01071205 )
#define DGT_ERR_CSR_CIV_TAG_FILE_INVALID                                ( 0x01071206 )
#define DGT_ERR_CSR_CIV_INIT_FILE_INVALID                               ( 0x01071207 )
#define DGT_ERR_CSR_CPA_PARA                                            ( 0x01071300 )
#define DGT_ERR_CSR_TAG_INVALID                                         ( 0x01071400 )
#define DGT_ERR_CSR_GHI_EXCELCOM                                        ( 0x01071500 )
#define DGT_ERR_CSR_GHI_PARA                                            ( 0x01071501 )
#define DGT_ERR_CSR_GHI_AREA_FUNC_EXISTED                               ( 0x01071502 )
#define DGT_ERR_CSR_GHI_DATA_INVALID                                    ( 0x01071503 )
#define DGT_ERR_CSR_CI_PARA                                             ( 0x01072000 )
#define DGT_ERR_SC_TAG_NO_FOUND                                         ( 0x01072100 )
#define DGT_ERR_CSR_SAMD_TAGID_NOT_FOUND                                ( 0x01072200 )
#define DGT_ERR_CSR_SAMD_ALTTAGID_NOT_FOUND                             ( 0x01072201 )
#define DGT_ERR_CC_CFP_PARA                                             ( 0x01072300 )
#define DGT_ERR_U_CFIP_PARA                                             ( 0x01081000 )

/* [%START%;%ErrorCode%;Search_MstBgColor] */
#define DGT_ERR_CSR_TAG_NOT_FOUND                                       ( 0x01071B05 ) 
#define DGT_ER_CSR_GCSI_SHEET_NOT_FOUND                                 ( 0x01090000 ) 
#define DGT_ER_CSR_GMSI_SHEET_NOT_FOUND                                 ( 0x0100A000 ) 
#define DGT_ERR_GGD_EXE_OUTPATH_INVALID                                 ( 0x01010801 )
#define DGT_ERR_CER_OEF_EXCEL_COM                                       ( 0x010B0000 ) 
#define DGT_ERR_CER_OEF_PARA                                            ( 0x010B0001 ) 
#define DGT_ERR_CER_CEF_EXCEL_COM                                       ( 0x010B0002 ) 
#define DGT_ERR_CER_CS_NOT_EXIST                                        ( 0x010C0000 )
#define DGT_ERR_CER_CS_EXCEL_COM                                        ( 0x010C0001 )
#define DGT_ERR_CER_GRC_PARA                                            ( 0x010D0000 )
#define DGT_ERR_CER_GRC_EXCEL_COM                                       ( 0x010D0001 )
#define DGT_ERR_CER_GCC_PARA                                            ( 0x010D0002 )
#define DGT_ERR_CER_GCC_EXCEL_COM                                       ( 0x010D0003 )
#define DGT_ERR_CER_SCLR_PARA                                           ( 0x010E0000 )
// Start TrunglV 2015-08-07 : Macro for remove maru
#define DGT_ER_CSR_RM_SHEET_NOT_FOUND                                   ( 0x010D1002 )
#define DGT_ERR_CER_RM_EXCEL_COM                                        ( 0x010D1003 )
// End TrunglV 2015-08-07 : 
#endif
