/* [%START%;%FileHeader%] */
/***********************************************************************

    �t�@�C����: DGT_PvSymbolDef.h

    �\��      : DIALOGGEN���W���[�� ����define�錾�w�b�_�t�@�C��

    ���e      : DIALOGGEN���W���[�� �Ŏg�p�������l��錾����

    �K�p�@��  : PASMO���W���[�� (ESSICMPB)

    �o�[�W����: YYYY-MM-DD    ESSICMPB-V01.00.00  �쐬�ҋL��        �V�K�쐬

    (C)Copyright Toshiba Corporation 2015. All rights reserved.

***********************************************************************/

#ifndef DGT_PVSYMBOLDEF_H
#define DGT_PVSYMBOLDEF_H
/* [%END  %;%FileHeader%] */


/* [%START%;%�V���{����%;CheckInputValidation symbol] */
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
/* [%END  %;%�V���{����%;CheckInputValidation symbol] */

/* [%START%;%�V���{����%;Mark symbol] */
#define DGT_SD_US_STATUS                                            (0x01)          /* Bit of updating status */
#define DGT_SD_US_PERCENT                                           (0x02)          /* Bit of updating percent */
#define DGT_SD_US_LOG                                               (0x04)          /* Bit of updating log */
/* [%END  %;%�V���{����%;Mark symbol] */

/* [%START%;%�V���{����%;Mark symbol] */
#define DGT_CFW_WA_CREATE_AREA                                      ("// CREATE AREA HERE")/* Mark of creating area */
#define DGT_CFW_WA_PROTOTYPE                                        ("// CREATE PROTOTYPE HERE")/* Mark of creating prototype */
#define DGT_CFW_WA_FUNC_MAP                                         ("// CREATE FUNCTION MAPPING HERE")/* Mark of creating function mapping */
#define DGT_CFW_WA_VCXPROJ                                          ("<ClCompile Include=\"AreaStore.cpp\" />")/* Mark of creating filter */
/* [%END  %;%�V���{����%;Mark symbol] */

/* [%START%;%�V���{����%;CheckFilePath symbol] */
#define DGT_U_CFIP_PATH_OK                                          (0x0001)        /* Folder path is valid */
#define DGT_U_CFIP_PATH_NULL                                        (0x0002)        /* Folder path is empty */
#define DGT_U_CFIP_PATH_INVALID                                     (0x0003)        /* Folder path is invalid */
#define DGT_U_CFIP_PATH_TOO_LONG                                    (0x0004)        /* Folder path > 218 character */
/* [%END  %;%�V���{����%;CheckFilePath symbol] */

/* [%START%;%�V���{����%;CheckFolderPath symbol] */
#define DGT_U_CFP_PATH_OK                                           (0x0001)        /* Folder path is valid */
#define DGT_U_CFP_PATH_NULL                                         (0x0002)        /* Folder path is empty */
#define DGT_U_CFP_PATH_INVALID                                      (0x0003)        /* Folder path is invalid */
#define DGT_U_CFP_PATH_TOO_LONG                                     (0x0004)        /* Folder path > 218 character */
/* [%END  %;%�V���{����%;CheckFolderPath symbol] */

#endif /* DGT_PVSYMBOLDEF_H */

/***********************************************************************

    EOF

***********************************************************************/
