/* [%START%;%FileHeader%] */
/***********************************************************************

    ファイル名: DGT_SymbolDef.h

    表題      : DIALOGGENモジュール define宣言ヘッダファイル

    内容      : DIALOGGENモジュール で使用する既定値を宣言する

    適用機種  : PASMOモジュール (ESSICMPB)

    バージョン: YYYY-MM-DD    ESSICMPB-V01.00.00  作成者記入        新規作成

    (C)Copyright Toshiba Corporation 2015. All rights reserved.

***********************************************************************/

#ifndef DGT_SYMBOLDEF_H
#define DGT_SYMBOLDEF_H
/* [%END  %;%FileHeader%] */


/* [%START%;%シンボル名%;関数戻り値] */
#define DGT_RET_OK                                                  (TRUE)          /* Normal end */
#define DGT_RET_ERR                                                 (FALSE)         /* Abnormal end */
/* [%END  %;%シンボル名%;関数戻り値] */

/* [%START%;%シンボル名%;Zero values] */
#define DGT_VALUE_ZERO_DWORD                                        (0x00000000)    /*  */
#define DGT_VALUE_ZERO_WORD                                         (0x0000)        /*  */
#define DGT_VALUE_ZERO_BYTE                                         (0x00)          /*  */
#define DGT_VALUE_ZERO_LONG                                         (0x00000000)    /*  */
/* [%END  %;%シンボル名%;Zero values] */

/* [%START%;%シンボル名%;Common symbol] */

#define TEMPLATE_FOLDER                                             ("Template Project")    /* Template project folder name */
#define FMT_LIST_FNAME                                              ("fmt_list.csv")/* format list CSV file */
#define AREA_LIST_FNAME                                             ("area_list.csv")/* area list CSV file */
#define LIMIT_LIST_FNAME                                            ("limit_list.csv")/* limit list CSV file */
#define TAG_LIST_FNAME                                              ("tag_list.csv")/* tag list CSV file */
#define INITDESING_LIST_FNAME                                       ("init_design_catarog.csv")/* init design list CSV file */
#define COMMA                                                       (",")           /* For split string */
#define AREA_ITEM_NUM                                               (4)             /* the numer of item in area CSV list */
#define FORMAT_ITEM_NUM                                             (2)             /* the numer of item in format CSV list */
#define TAG_ITEM_NUM                                                (5)             /* the numer of item in tag CSV list */
#define LIMIT_ITEM_NUM                                              (2)             /* the numer of item in limitation CSV list */
#define INIT_ITEM_NUM                                               (2)             /* the numer of item in init CSV list */
#define CATALOG_ITEM_NUM                                            (8)             /* the numer of item in catalog CSV list */
#define SHEET_CREATATION_LIST                                       ("◆作成一覧")  /* creation list sheet name */
#define SHEET_MASTER                                                ("◆マスタ")    /* master sheet name */
#define MASTER_START_ROW                                            (2)             /* Start row of master sheet */
#define MASTER_START_COL                                            (8)             /* column to read Japannse name */
#define MASTER_END_COL                                              (9)             /* column to read English name */
#define NOT_FOUND                                                   (-1)            /* Set not found value */
#define LIST_START_ROW                                              (3)             /* start row of creation list sheet */
#define LIST_START_COL                                              (2)             /* start column to read data in [作成一覧] sheet */
#define LIST_END_COL                                                (7)             /* end column to read data in [作成一覧] sheet */
#define LIST_NO_COL                                                 (0)             /* [No] column in [作成一覧] sheet */
#define LIST_SHNAME_COL                                             (2)             /* Column that cotain list of screen sheet name */
#define LIST_OUT_COL                                                (1)             /* Column that contain list of output file */
#define SUBJECT_MARU                                                ("○")          /* Corresponding "○" value */
#define SUBJECT_BATSU                                               ("×")          /* Corresponding "×" value */
#define TITLE_COL                                                   (0)             /* Title column  */
#define AREA_MODE_COL                                               (1)             /* To get area mode in header info */
#define BGCOLOR_COL                                                 (2)             /* To get area mode in header info */
#define OUT_FNAME_COL                                               (3)             /* To get template in header info */
#define TEMPFMT_COL                                                 (4)             /* To get base height in header info */
#define BASE_HEIGHT_COL                                             (5)             /* To get base width in header info */
#define BASE_WIDTH_COL                                              (6)             /* To get  in header info */
#define BUNKETSU_TATE_COL                                           (7)             /* To get vertical division in header info */
#define BUNKETSU_YOKO_COL                                           (8)             /* To get horizontal division in header info */
#define CEL_TATE_COL                                                (9)             /* To get vertical cell size in header info */
#define CEL_YOKO_COL                                                (10)            /* To get horizontal cell size in header info */
#define YOHAKU_TOP_COL                                              (11)            /* To get margin top size in header info */
#define YOHAKU_RIGHT_COL                                            (12)            /* To get margin right size in header info */
#define YOHAKU_BOTTOM_COL                                           (13)            /* To get margin bottom size in header info */
#define YOHAKU_LEFT_COL                                             (14)            /* To get margin left size in header info */
#define VERSION_COL                                                 (15)            /* To get version in header info */
#define HIDUKE_COL                                                  (16)            /* To get created date in header info */
#define CREATER_COL                                                 (17)            /* To get creater in header info */
#define OPE                                                         ("2")           /* Operation value */
#define DATA_START_ROW                                              (11)            /* Start row to read item data */
#define DATA_START_COL                                              (1)             /* Start column to read item data */
#define DATA_END_COL                                                (29)            /* End column to read item data */
#define NO_COL                                                      (0)             /* [No] column number */
#define KOMOKU_COL                                                  (1)             /* [項目] column number */
#define DISPSTR_COL                                                 (2)             /* [初期表示] column number */
#define GAIKAN_COL                                                  (3)             /* [日本語名] column number */
#define DOSA_COL                                                    (4)             /* [状態(初期状態)] column number */
#define HIDDEN_COL                                                  (5)             /* [表示：○／非表示：×(初期状態)] 
column number */
#define DISABLE_COL                                                 (6)             /* [押下可：○／押下不可：×(初期状態)] column number */
#define HEIGHT_COL                                                  (7)             /* [縦の長さ] column number */
#define WIDTH_COL                                                   (8)             /* [横の長さ] column number */
#define FONTSIZE_COL                                                (9)             /* [フォントサイズ] column number */
#define ZOOMSIZE_COL                                                (10)            /* [フォント縮小率] column number */
#define ICHI_COL                                                    (11)            /* [配置場所] column number */
#define INITDESIGN_COL                                              (12)            /* [初期カタログ日本語名] column number */
#define INITSTR_COL                                                 (13)            /* [表示文字] column number */
#define DEFAULTAPP_COL                                              (14)            /* [初期適用：○／初期非適用：×] column number */
#define NULLSTRAPP_COL                                              (15)            /* [空文字適用：○／空文字非適用：×] column number */
#define INPUTFMT_COL                                                (16)            /* [入力フォーマット] column number */
#define CURUMU_COL                                                  (17)            /* [入力受付有無] column number */
#define MINLENGTH_COL                                               (18)            /* [最少桁数] column number */
#define MAXLENGTH_COL                                               (19)            /* [最大桁数] column number */
#define INPUT_OEDER_COL                                             (20)            /* [入力順序(タブ遷移] column number */
#define ERR_DISP_ICHI_COL                                           (21)            /* [エラー表示位置] column number */
#define INPUT_LIMIT_COL                                             (22)            /* [入力制限] column number */
#define TAGID_COL                                                       (24)            /* [タグＩＤ名] column number */
#define SENDSTR1_COL                                                (25)            /* [送付文字列] column number */
#define ALTERNATE_TAGID_COL                                    (26)            /* [オルタネート式釦用タグ名２] column number */
#define SENDSTR2_COL                                                (27)            /* [送付文字列２] column number */
#define EKIBTN_ID_COL                                                 (28)           // 駅釦ID　位置
#define TAB_AREA                                                    ("【タブエリア】")/* To check item is [Tab area] or not */
#define EKIBTN_FMT                                                  ("駅釦（西武）")/* Eki button value */
#define NASHI_MODE                                                  ("－")          /* None mode */
#define NASHI_MODE_HALF                                         ("-")
#define NASHI_MODE_JP                                             ("【無し】")
#define FMT_NAME_INPUT_START_BTN                                    ("【入力開始用釦】")/* To check format when set click branch mode */
#define MAX_STRING_CHARACTERS                                       (218)           /* Max file path length */
#define DGT_MSG                                                     (WM_USER + 1)   /* Private message*/
#define EXCEL_REF                                                   ("#REF!")           /* Unreferences */
#define MAIN_DLG_HEADER_FILE                                        ("\\Include\\GUIDAreaStore.h")/* Header file of areas */
#define VCXPROJ_FILE                                                ("\\GUIDAreaStoreLib\\AreaStoreLib.vcxproj")/* Project configuration file */
#define AREA_STORE_FOLDER                                           ("\\GUIDAreaStoreLib\\")/* Area storeage folder */
#define FUNCTION_MAP_FILE                                           ("\\GUIDAreaStoreLib\\FunctionMap.cpp")/* Function map file */
#define ITEM_TYPE_BUTTON                                            (0x01)          /* Button */
#define ITEM_TYPE_LABEL                                             (0x02)          /* Label */
#define TAG_NAME_LIST_SIZE                                          13
#define STS_TATE                                                           (0)
#define STS_YOKO                                                           (0)
#define CONSTS_BTN_TATE                                              (0)
#define CONSTS_BTN_YOKO                                             (0)
#define TAG_NAME_LIST_NUM                                           (12)
#define DELIMITER   ("<>")
#define CONTENA  ("コンテナ")
#define SEINENGAPPI ("生年月日（２段用）")
 #define MSGAREA  ("メッセージ")
#define IMG_STRETCH ("画像（ストレッチ）")
 #define ICON  ("アイコン")
#define KOMOKU_BOOKING_START  ("【開始】")
#define KOMOKU_BOOKING_END     ("【終了】")
#define GRP_EKIBTN  ("ekibtn")
#define GRP_KEIYUBTN  ("Keiyu")
#define SPEC_GAIKAN_NAME   ("@@")
#define KOMOKU_BOOKING_STRCOLOR  ("str_")
#define KOMOKU_BOOKING_IMG   ("img")
#define KOMOKU_BOOKING_LINE  ("line")
#define ZOKUSEI_PRE "見出し(等間隔)"
#define HR_BOTTOM 1
#define HR_MID    2
#define ITEM_LEFT                           (1)
#define ITEM_TOP                            (0)

#define ITEM_LEFT_MARGIN                    (0)
#define ITEM_TOP_MARGIN                     (1)
#define ITEM_RIGHT_MARGIN                   (2)
#define ITEM_BOTTOM_MARGIN                  (3)

#define PAGE_AREA               ("【ページエリア】")
#define TAGID_PAGE_AREA     ("_area")
#define CONTENA                   ("コンテナ")
#define BTN_PAGE_KIRIKAE     ("釦（頁切替用)")
#define PASSWORD_MODE       ("テンキー：パスワード")
#define TAGID_HIDDEN        ("_入力格納")



/* [%END  %;%シンボル名%;Common symbol] */

/* [%START%;%シンボル名%;Request type] */
#define DGT_NOTIFY_INPUT_VALID                                      (0x01)          /* Notify input valid */
#define DGT_NOTIFY_UPDATE_STATUS                                    (0x02)          /* Notify main dialog update status */
#define DGT_NOTIFY_ERROR                                            (0x03)          /* Notify error */
#define DGT_NOTIFY_EXIT                                             (0x04)          /* Notify user click [Exit] on progress dialog*/
#define DGT_NOTIFY_COMPLETE                                         (0x05)          /* Notify working process is completed*/
/* [%END  %;%シンボル名%;Request type] */

/* [%START%;%シンボル名%;関数戻り値] */
#define GUI_RET_OK                                                  (0)             /* Normal end */
#define GUI_RET_ERR                                                 (-1)            /* Abnormal end */
/* [%END  %;%シンボル名%;関数戻り値] */

/* [%START%;%シンボル名%;Zero values] */
#define GUI_VALUE_ZERO_DWORD                                        (0x00000000)    /*  */
#define GUI_VALUE_ZERO_WORD                                         (0x0000)        /*  */
#define GUI_VALUE_ZERO_BYTE                                         (0x00)          /*  */
#define GUI_VALUE_ZERO_LONG                                         (0x00000000)    /*  */
/* [%END  %;%シンボル名%;Zero values] */

/* [%START%;%シンボル名%;Common symbol] */
#define CLASS_CCUSTOM_BTN                                           ("class CCustomBtn")/* Class CCustomBtn */
#define CLASS_RICH_LABEL                                            ("class CRichLabel")/* Class CRichLabel */
#define INDICATOR_AREA                                              ("sts_indication")/*  */
#define BUSSINESS_AREA                                              ("gyomu_annai") /*  */
#define CONST_BTN_AREA                                              ("const_btn")   /*  */
#define CENTER_DISP_AREA                                            ("center_disp") /*  */
#define DISP_AREA                                                   ("disp")        /*  */
#define OPERATING_AREA                                              ("operation")   /*  */
#define POPUP_AREA                                                  ("popup")       /*  */
#define ACCEPT_NOTICE_NO                                            (2)             /*  */
#define INIT_REQUEST_NO                                             (11)            /*  */
#define INIT_RESPONSE_NO                                            (12)            /*  */
#define HOLIDAY_REQUEST_NO                                          (21)            /*  */
#define HOLIDAY_RESPONSE_NO                                         (22)            /*  */
#define UNYOSET_REQUEST_NO                                          (31)            /*  */
#define UNYOSET_RESPONSE_NO                                         (32)            /*  */
#define INPUT_START_REQUEST_NO                                      (41)            /*  */
#define INPUT_START_RESPONSE_NO                                     (42)            /*  */
#define INPUT_COMPLET_REQUEST_NO                                    (52)            /*  */
#define INPUT_COMPLET_RESPONSE_NO                                   (51)            /*  */
#define INPUT_CANCEL_REQUEST_NO                                     (61)            /*  */
#define INPUT_CANCEL_RESPONSE_NO                                    (62)            /*  */
#define INPUT_NOTICE_NO                                             (72)            /*  */
#define KEYBOARD_INPUT_NOTICE_NO                                    (81)            /*  */
#define OTHER_INPUT_REQUEST_NO                                      (92)            /*  */
#define OTHER_INPUT_RESPONSE_NO                                     (91)            /*  */
#define STS_INDICATION_REQUEST_NO                                   (101)           /*  */
#define STS_NDICATION_RESPONSE_NO                                   (102)           /*  */
#define DISPLAY_REQUEST_NO                                          (111)           /*  */
#define DISPLAY_RESPONSE_NO                                         (112)           /*  */
#define RESET_REQUEST_NO                                            (122)           /*  */
#define RESET_RESPONSE_NO                                           (121)           /*  */
#define FARE_REQUEST_NO                                             (132)           /*  */
#define FARE_RESPONSE_NO                                            (131)           /*  */
#define START_REQUEST_NO                                            (142)           /*  */
#define START_RESPONSE_NO                                           (141)           /*  */
#define ERROR_NOTICE_NO                                             (152)           /*  */
#define ERROR_CODE_NULL                                             (-11)           /*  */
#define ERROR_CODE_ILLEGAL_OPERATION_DATE                           (-101)          /*  */
#define ERROR_CODE_ILLEGAL_HOLIDAY_LIST                             (-114)          /*  */
#define ERROR_CODE_NULL_ID                                          (-102)          /*  */
#define ERROR_CODE_NOT_EXIST_ID                                     (-103)          /*  */
#define ERROR_CODE_NOT_EXIST_HTML                                   (-104)          /*  */
#define ERROR_CODE_NOT_EXIST_CLASS                                  (-105)          /*  */
#define ERROR_CODE_NOT_EXIST_IMAGE                                  (-106)          /*  */
#define ERROR_CODE_NOT_NUMBER                                       (-107)          /*  */
#define ERROR_CODE_NOT_DATE                                         (-108)          /*  */
#define ERROR_CODE_NOT_RANGE                                        (-109)          /*  */
#define ERROR_CODE_NOT_CALEMDAR_DISP                                (-110)          /*  */
#define ERROR_CODE_ILLEGAL_DENBUN_NO                                (-111)          /*  */
#define ERROR_CODE_CONV_ANNO_JAPANESE                               (-113)          /*  */
#define ERROR_CODE_NOT_ID_TYPE                                      (-115)          /*  */
#define MAX_HOLIDAY                                                 (32)            /*  */
#define MAX_ERR_STR                                                 (256)           /*  */
#define RESULT_OK_PAGE_SWITC                                        (9)             /*  */
#define JUDGE_HALF_NUMBER                                           (1)             /*  */
#define JUDGE_FULL_NUMBER                                           (2)             /*  */
#define INPUT_LIMIT_OK                                              (0)             /*  */
#define INPUT_LIMIT_STR_NULL                                        (1)             /*  */
#define INPUT_LIMIT_ERROR                                           (-1)            /*  */
#define DENBUN_RESULT_OK                                            (0)             /*  */
#define DENBUN_RESULT_NG                                            (1)             /*  */
#define DAY_OF_WEEK_SUNDAY                                          ('Sun')         /*  */
#define DAY_OF_WEEK_MONDAY                                          ('Mon')         /*  */
#define DAY_OF_WEEK_TUESDAY                                         ('Tue')         /*  */
#define DAY_OF_WEEK_WEDNESDAY                                       ('Web')         /*  */
#define DAY_OF_WEEK_THURSDAY                                        ('Thu')         /*  */
#define DAY_OF_WEEK_FRIDAY                                          ('Fri')         /*  */
#define DAY_OF_WEEK_SATURDAY                                        ('Sat')         /*  */
#define DAY_OF_WEEK_HOLIDAY                                         ('Holiday')     /*  */
#define CUSTOM_ATTRIBUTES_GRP                                       ('grp')         /*  */
#define CUSTOM_ATTRIBUTES_GAIKAN                                    ('gaikan')      /*  */
#define CUSTOM_ATTRIBUTES_FMT                                       ('fmt')         /*  */
#define CUSTOM_ATTRIBUTES_STS                                       ('sts')         /*  */
#define CUSTOM_ATTRIBUTES_ALTID                                     ('altid')       /*  */
#define CUSTOM_INIT_CLASS                                           ('initClass')   /*  */
#define CUSTOM_INIT_TEXT                                            ('initText')    /*  */
#define CUSTOM_NULL_STR_INIT_APP                                    ('nullStrInitApp')/*  */
#define CUSTOM_MIN_LEN                                              ('minlen')      /*  */
#define CUSTOM_MAX_LEN                                              ('maxlen')      /*  */
#define CUSTOM_TIP_ICHI                                             ('tipIchi')     /*  */
#define CUSTOM_LIMIT                                                ('limit')       /*  */
#define CUSTOM_PAGE_ATR                                             ('PageAtr')     /*  */
#define GROUP_NAME_TENKEY                                           ('tenkey')      /*  */
#define GROUP_NAME_EKI_BTN                                          ('ekibtn')      /*  */
#define GROUP_NAME_KEIYU_BTN                                        ('Keiyu')       /*  */
#define GROUP_NAME_MONTH_MOVE                                       ('MonthMove')   /*  */
#define GROUP_NAME_CALENDAR_DATE                                    ('CalendarDate')/*  */
#define GROUP_NAME_ITAKU                                            ('itaku')       /*  */
#define GROUP_NAME_ZASEKI                                           ('Zaseki')      /*  */
#define GROUP_NAME_RESSHA_SHUBETSU                                  ('ResshaShubetsu')/*  */
#define GROUP_NAME_COUPON                                           ('Coupon')      /*  */
#define GROUP_NAME_IKKATSU_SET                                      ('ikkatsu_set') /*  */
#define TAG_ID_NAME_ENTER                                           ('Enter')       /*  */
#define TAG_ID_NAME_START_BTN                                       ('StartBtn')    /*  */
#define TAG_ID_NAME_RESET_BTN                                       ('ResetBtn')    /*  */
#define TAG_ID_NAME_UNCHIN_SHOKAI                                   ('FareInquiryBtn')/*  */
#define TAG_ID_NAME_CLEAR                                           ('Clear')       /*  */
#define TAG_ID_NAME_TAB                                             ('Tab')         /*  */
#define TAG_ID_NAME_ALT_TAB                                         ('AltTab')      /*  */
#define TAG_ID_NAME_BACK_SPACE                                      ('BS')          /*  */
#define TAG_ID_NAME_CURSOR_IMAGE                                    ('Coursor')     /*  */
#define TAG_ID_NAME_MONTH_PREVIOUS                                  ('Month_Previous')/*  */
#define TAG_ID_NAME_MONTH_THIS                                      ('Month_This')  /*  */
#define TAG_ID_NAME_MONTH_NEXT                                      ('Month_Next')  /*  */
#define TAG_ID_NAME_SEINEN_GAPPI                                    ('SeinenGappi') /*  */
#define TAG_ID_NAME_ENABLE_AREA                                     ('_Enable')     /*  */
#define TAG_ID_NAME_EKI_BTN                                         ('E')           /*  */
#define TAG_ID_NAME_KEIYU_BTN                                       ('R')           /*  */
#define TAG_ID_NAME_SET_CHAR_SPAN                                   ('SetCharSpan') /*  */
#define TAG_ID_NAME_WAREKI                                          ('_wa')         /*  */
#define TAG_ID_INPUT_TABS                                           ('Input_Tabs')  /*  */
#define TAG_ID_INPUT_CALENDAR_DATE                                  ('Date')        /*  */
#define TAG_ID_TAB_PAGE_AREA                                        ('_area')       /*  */
#define TAG_ID_TOOLTIP                                              ('ToolTip')     /*  */
#define FMT_NAME_DATE_OF_BIRTH                                      ('DateOfBirth') /*  */
#define FMT_NAME_BUTTON_NO_INPUT                                    ('ButtonNoInput')/*  */
#define FMT_NAME_EDIT_COMMA                                         ('EditComma')   /*  */
#define FMT_NAME_EDIT_COMMA_YEN                                     ('EditCommaYen')/*  */
#define FMT_NAME_EDIT_COMMA_YEN_NOMI                                ('EditCommaYen_Nomi')/*  */
#define FMT_NAME_DATE_YEAR_TWO_DGITS                                ('DateYearTwoDgits')/*  */
#define FMT_NAME_DATE_YEAR_TWO_DGITS_JP                             ('DateYearTwoDgits_Jpn')/*  */
#define FMT_NAME_DATE_YEAR_FOUR_DGITS                               ('DateYearFourDgits')/*  */
#define FMT_NAME_DATE_MONTH_DAY                                     ('DateMonthDay')/*  */
#define FMT_NAME_SCHOOL_YEAR                                        ('SchoolYear')  /*  */
#define FMT_NAME_PASSWORD                                           ('Password')    /*  */
#define STS_NAME_UPDATE_ELEMENT_PARENT                              ('pa')          /*  */
#define STS_NAME_UPDATE_ELEMENT_CHILD                               ('ch')          /*  */
#define STS_NAME_DISABLED_ENABLE                                    ('enable')      /*  */
#define STS_NAME_DISABLED_DISABLE                                   ('disable')     /*  */
#define STS_INDEX_DESIGN                                            (0)             /*  */
#define STS_INDEX_UPDATE_ELEMENT                                    (1)             /*  */
#define STS_INDEX_VISIBILITY                                        (2)             /*  */
#define STS_INDEX_DISABLE                                           (3)             /*  */
#define STS_INDEX_BLINK                                             (4)             /*  */
#define INPUT_CHECK_INPUT_ALL                                       ('InputAll')    /*  */
#define INPUT_CHECK_INPUT_ALL_NULL                                  ('InputAll_Null')/*  */
#define INPUT_CHECK_DATE_VALIDITY                                   ('DateValidity')/*  */
#define INPUT_CHECK_TIME_VALIDITY                                   ('TimeValidity')/*  */
#define INPUT_CHECK_NUM_CHECK                                       ('NumCheck')    /*  */
#define CLICK_BRANCHMODE_OTHER_INPUT                                (0)             /*  */
#define CLICK_BRANCHMODE_NOT_APPOINT                                (99)            /*  */
#define DUMMY_IMG_URL                                               ('img/dummy.png')/*  */
#define POOUP_DISP_POTICION_INDEX_CENTER                            (1)             /*  */
#define CURSOR_IMAGE_URL                                            ('../../img/cur.png')/*  */
#define KEYBOARD_DATA_ENTER                                         ('enter')       /*  */
#define KEYBOARD_DATA_START_BTN                                     ('startbtn')    /*  */
#define KEYBOARD_DATA_RESET_BTN                                     ('resetbtn')    /*  */
#define KEYBOARD_DATA_CLEAR                                         ('clear')       /*  */
#define KEYBOARD_DATA_TAB                                           ('tab')         /*  */
#define KEYBOARD_DATA_ALT_TAB                                       ('alttab')      /*  */
#define KEYBOARD_DATA_BS                                            ('bs')          /*  */
#define DISPLAY_REQUEST_TYPE_PAGE_SWITCH                            (0)             /*  */
#define DISPLAY_REQUEST_TYPE_CALENDAR                               (1)             /*  */
#define DISPLAY_REQUEST_TYPE_POPUP                                  (2)             /*  */
#define DISPLAY_REQUEST_TYPE_BUTTON                                 (3)             /*  */
#define DISPLAY_REQUEST_TYPE_TEXT_ITEM                              (4)             /*  */
#define DISPLAY_REQUEST_TYPE_IMAGE                                  (5)             /*  */
#define DISPLAY_REQUEST_TYPE_TOOLTIP                                (6)             /*  */
#define AREA_NAME_KINOU                                             ('top_iframe')  /*  */
#define AREA_NAME_STS_IDICATION                                     ('sts_idication')/*  */
#define AREA_NAME_DISP                                              ('disp')        /*  */
#define AREA_NAME_OPERATION                                         ('operation')   /*  */
#define AREA_NAME_POPUP                                             ('popup')       /*  */
#define AREA_NAME_IMG_DISP                                          ('img_disp')    /*  */
#define DESIGN_MULTI_CLASS                                          (1)             /*  */
#define DESIGN_SELECT                                               (2)             /*  */
#define DESIGN_NOT_SELECT                                           (3)             /*  */
#define DESIGN_ERROR                                                (4)             /*  */
#define DESIGN_DISABLE                                              (5)             /*  */
#define DESIGN_INIT                                                 (6)             /*  */
#define DESIGN_VISIBLE                                              (7)             /*  */
#define DESIGN_HIDDEN                                               (8)             /*  */
#define DESIGN_BLINK                                                (9)             /*  */
#define DESIGN_BLINK_MOJI                                           (10)            /*  */
#define DESIGN_INPUT_ERROR                                          (11)            /*  */
#define DESIGN_INPUT_NO_CHANGE                                      (12)            /*  */
#define DESIGN_INPUT_AUTO                                           (13)            /*  */
#define DESIGN_INPUT_INIT_DISP                                      (14)            /*  */
#define DESIGN_BTN_OFF                                              (15)            /*  */
#define DESIGN_BTN_ON                                               (16)            /*  */
#define DESIGN_BTN_BLINK                                            (17)            /*  */
#define DESIGN_BTN_DISABLE                                          (18)            /*  */
#define DESIGN_TEXT_NOT_SELECT                                      (19)            /*  */
#define DESIGN_TEXT_SELECT                                          (20)            /*  */
#define DESIGN_TEXT_ERROR                                           (21)            /*  */
#define DESIGN_TEXT_BLINK_MOJI                                      (22)            /*  */
#define DESIGN_TEXT_BLINK                                           (23)            /*  */
#define DESIGN_TEXT_DEFAULT                                         (24)            /*  */
#define DESIGN_TEXT_DISABLE                                         (25)            /*  */
#define DESIGN_TEXT_INIT_DISP                                       (26)            /*  */
#define DESIGN_ERROR_BLINK_MOJI                                     (27)            /*  */
#define DESIGN_ERROR_BLINK                                          (28)            /*  */
#define DESIGN_ERROR_BACKGROUND_CHANGE                              (29)            /*  */
#define DESIGN_ERROR_MOJI_CHANGE                                    (30)            /*  */
#define DESIGN_CHAR_COLOR_RED                                       (31)            /*  */
#define CONV_YEAR_ANNO_DOMINI                                       (0)             /*  */
#define CONV_YEAR_JAPANESE_CALENDAR                                 (1)             /*  */
#define DISP_COMMA_NOT_AVAILABLE                                    (0)             /*  */
#define DISP_COMMA_AVAILABLE                                        (1)             /*  */
#define ZERO_PADDING_NOT_AVAILABLE                                  (0)             /*  */
#define ZERO_PADDING_AVAILABLE                                      (1)             /*  */
#define ZERO_PADDING_AVAILABLE_NULL                                 (2)             /*  */
#define RESOLUTIVE_MODE_ENTER                                       ('Enter')       /*  */
#define RESOLUTIVE_MODE_INPUT                                       ('Input')       /*  */
#define CONVMODE_DISP                                               ('DispProcNo')  /*  */
#define CONVMODE_INPUT                                              ('InputProcNo') /*  */
#define INPUT_INIT_SHIJI_NOT_CHANGE                                 (99)            /*  */
#define INPUT_INIT_SHIJI_FIRST_CLEAR                                (1)             /*  */
#define INPUT_INIT_SHIJI_CLEAR                                      (0)             /*  */
#define INPUT_CANCEL_SHIJI_NOT_CHANGE                               (99)            /*  */
#define INPUT_CANCELT_SHIJI_CLEAR                                   (0)             /*  */
#define INPUT_CANCEL_SHIJI_BEFORE_DATA                              (1)             /*  */
#define ERROR_RESOLUTIVE_INPUT_FIRST                                (1)             /*  */
#define ERROR_RESOLUTIVE_ENTER                                      (2)             /*  */
#define ERROR_RESOLUTIVE_NO_RESOLUTIVE                              (99)            /*  */
#define FLG_OBJECT_VISIBLE                                          (0)             /*  */
#define FLG_OBJECT_HIDDEN                                           (1)             /*  */
#define FLG_OBJECT_DESTRUCTION                                      (0)             /*  */
#define FLG_OBJECT_CREATE                                           (1)             /*  */
#define FLG_OBJECT_BLINK_STOP                                       (0)             /*  */
#define FLG_OBJECT_BLINK_START                                      (10)            /*  */
#define FLG_OBJECT_ENABLE                                           (0)             /*  */
#define FLG_OBJECT_NOT_ENABLE                                       (1)             /*  */
#define AUOT_SET_TEXT                                               (1)             /*  */
#define AUOT_NOT_SET_TEXT                                           (0)             /*  */
#define WAY_DATA_ALL                                                (0)             /*  */
#define WAY_DATA_SPECIFIED                                          (1)             /*  */
#define CHAR_COLOR_MODE_DELETE                                      (0)             /*  */
#define CHAR_COLOR_MODE_ADD                                         (1)             /*  */
#define ASSIGN_CLASS_MODE_DEL                                       (0)             /*  */
#define ASSIGN_CLASS_MODE_ADD                                       (1)             /*  */
#define DATA_KIND_BUTTON_TAG_ID                                     (0)             /*  */
#define DATA_KIND_DISP_TEXT                                         (1)             /*  */
#define CHANGE_FLAG_FALSE                                           (0)             /*  */
#define CHANGE_FLAG_TRUE                                            (1)             /*  */
#define STS_SPLIT                                                   ('_')           /*  */
#define HOLIDAY_SPLIT                                               ('_')           /*  */
#define TAG_ID_SPLIT                                                ('_')           /*  */
#define UNDER_SCORE_SPLIT                                           ('_')           /*  */
#define IKKATSU_DATA_SPLIT                                          ('，')          /*  */
#define ALT_BUTTON_AUTO_TEXT_SPLIT                                  ('?')           /*  */
#define CSS_CLASS_NOTHING                                           ('－')          /*  */
#define FORMAT_INPUT_ITEM                                           ('△')          /*  */
#define CHARACTER_SPACE                                             ('　')          /*  */
#define CURSOR_IMAGE_MARGIN_CHARACTER                               (1)             /*  */
#define PIXEL                                                       ('px')          /*  */
#define DISP_CONTROL_ENTIRE_ENABLE                                  ('entire_display')/*  */
#define GROUP_NAME_PAGE_SHITEI                                      ('PageShitei')  /*  */
#define SPEC_ASSIGN_CLASS                                           ('@')           /*  */
#define UNDERBAR_REPLACE_STR                                        ('#')           /*  */
#define TAG_ID_NAME_INPUT_PASS                                      ('_Hidden')     /*  */
#define DISP_PASS_CHARACTER                                         ('＊')          /*  */
#define CALENDAR_DISP_NO_LIMIT_START_DATE                           ('00000000')    /*  */
#define CALENDAR_DISP_NO_LIMIT_END_DATE                             ('99999999')    /*  */
#define CALENDAR_DISP_NO_LIMIT_YEAR_RANGE_START                     (2)             /*  */
#define CALENDAR_DISP_NO_LIMIT_YEAR_RANGE_END                       (2)             /*  */
#define CALENDAR_DISP_TYPE_CALENDAR                                 ('calendar')    /*  */
#define CALENDAR_DISP_TYPE_KIKAN                                    ('kikan')       /*  */
#define INPUT_LENGTH_NASHI_MODE                                     ('－')          /*  */
#define INPUT_LENGTH_EMPTY_OR_ALL                                   ('◆')          /*  */
#define INPUT_MAX_LENGTH_LIMIT                                      (999)           /*  */
#define PECULIAR_PROC_GAIKAN                                        ('@@')          /*  */
#define HEIGHT_CLASS_H                                              ('h')           /*  */
#define HEIGHT_CLASS_HL                                             ('hl')          /*  */
#define HEIGHT_WIDTH_CLASS_GRID                                     ('grid')        /*  */
#define TAG_ID_NAME_FUKURO_TAB                                      ('Fukuro_Tab')  /*  */
#define START_CTRL_ID                                               (1050)
#define MASK_UPDATE_TEXT                                            (0x01)          /* Flag update status */
#define MASK_UPDATE_PERCENT                                         (0x02)          /* Flag update percent */
#define MASK_UPDATE_LOG                                             (0x04)          /* Flag update log */
#define DATA_AUTOMK_INI_FNME                                        ("Data_AutoMk_Tool.ini") /* Setting file name */
#define DATA_INI_DLGBASE_SECTION                                    ("AUTOMK_DIALOGBASE_CONTENTS") /* Setting file name */

/* [%END  %;%シンボル名%;Common symbol] */

/* [%START%;%シンボル名%;Common symbol] */
#define INDICATOR_AREA                                              ("sts_indication")/*  */
#define BUSSINESS_AREA                                              ("gyomu_annai") /*  */
#define CONST_BTN_AREA                                              ("const_btn")   /*  */
#define CENTER_DISP_AREA                                            ("center_disp") /*  */
#define DISP_AREA                                                   ("disp")        /*  */
#define OPERATING_AREA                                              ("operation")   /*  */
#define POPUP_AREA                                                  ("popup")       /*  */
#define ACCEPT_NOTICE_NO                                            (2)             /*  */
#define INIT_REQUEST_NO                                             (11)            /*  */
#define INIT_RESPONSE_NO                                            (12)            /*  */
#define HOLIDAY_REQUEST_NO                                          (21)            /*  */
#define HOLIDAY_RESPONSE_NO                                         (22)            /*  */
#define UNYOSET_REQUEST_NO                                          (31)            /*  */
#define UNYOSET_RESPONSE_NO                                         (32)            /*  */
#define INPUT_START_REQUEST_NO                                      (41)            /*  */
#define INPUT_START_RESPONSE_NO                                     (42)            /*  */
#define INPUT_COMPLET_REQUEST_NO                                    (52)            /*  */
#define INPUT_COMPLET_RESPONSE_NO                                   (51)            /*  */
#define INPUT_CANCEL_REQUEST_NO                                     (61)            /*  */
#define INPUT_CANCEL_RESPONSE_NO                                    (62)            /*  */
#define INPUT_NOTICE_NO                                             (72)            /*  */
#define KEYBOARD_INPUT_NOTICE_NO                                    (81)            /*  */
#define OTHER_INPUT_REQUEST_NO                                      (92)            /*  */
#define OTHER_INPUT_RESPONSE_NO                                     (91)            /*  */
#define STS_INDICATION_REQUEST_NO                                   (101)           /*  */
#define STS_NDICATION_RESPONSE_NO                                   (102)           /*  */
#define DISPLAY_REQUEST_NO                                          (111)           /*  */
#define DISPLAY_RESPONSE_NO                                         (112)           /*  */
#define RESET_REQUEST_NO                                            (122)           /*  */
#define RESET_RESPONSE_NO                                           (121)           /*  */
#define FARE_REQUEST_NO                                             (132)           /*  */
#define FARE_RESPONSE_NO                                            (131)           /*  */
#define START_REQUEST_NO                                            (142)           /*  */
#define START_RESPONSE_NO                                           (141)           /*  */
#define ERROR_NOTICE_NO                                             (152)           /*  */
#define ERROR_CODE_NULL                                             (-11)           /*  */
#define ERROR_CODE_ILLEGAL_OPERATION_DATE                           (-101)          /*  */
#define ERROR_CODE_ILLEGAL_HOLIDAY_LIST                             (-114)          /*  */
#define ERROR_CODE_NULL_ID                                          (-102)          /*  */
#define ERROR_CODE_NOT_EXIST_ID                                     (-103)          /*  */
#define ERROR_CODE_NOT_EXIST_HTML                                   (-104)          /*  */
#define ERROR_CODE_NOT_EXIST_CLASS                                  (-105)          /*  */
#define ERROR_CODE_NOT_EXIST_IMAGE                                  (-106)          /*  */
#define ERROR_CODE_NOT_NUMBER                                       (-107)          /*  */
#define ERROR_CODE_NOT_DATE                                         (-108)          /*  */
#define ERROR_CODE_NOT_RANGE                                        (-109)          /*  */
#define ERROR_CODE_NOT_CALEMDAR_DISP                                (-110)          /*  */
#define ERROR_CODE_ILLEGAL_DENBUN_NO                                (-111)          /*  */
#define ERROR_CODE_CONV_ANNO_JAPANESE                               (-113)          /*  */
#define ERROR_CODE_NOT_ID_TYPE                                      (-115)          /*  */
#define MAX_HOLIDAY                                                 (32)            /*  */
#define MAX_ERR_STR                                                 (256)           /*  */
#define RESULT_OK_PAGE_SWITC                                        (9)             /*  */
#define JUDGE_HALF_NUMBER                                           (1)             /*  */
#define JUDGE_FULL_NUMBER                                           (2)             /*  */
#define INPUT_LIMIT_OK                                              (0)             /*  */
#define INPUT_LIMIT_STR_NULL                                        (1)             /*  */
#define INPUT_LIMIT_ERROR                                           (-1)            /*  */
#define DENBUN_RESULT_OK                                            (0)             /*  */
#define DENBUN_RESULT_NG                                            (1)             /*  */
#define DAY_OF_WEEK_SUNDAY                                          ('Sun')         /*  */
#define DAY_OF_WEEK_MONDAY                                          ('Mon')         /*  */
#define DAY_OF_WEEK_TUESDAY                                         ('Tue')         /*  */
#define DAY_OF_WEEK_WEDNESDAY                                       ('Web')         /*  */
#define DAY_OF_WEEK_THURSDAY                                        ('Thu')         /*  */
#define DAY_OF_WEEK_FRIDAY                                          ('Fri')         /*  */
#define DAY_OF_WEEK_SATURDAY                                        ('Sat')         /*  */
#define DAY_OF_WEEK_HOLIDAY                                         ('Holiday')     /*  */
#define CUSTOM_ATTRIBUTES_GRP                                       ('grp')         /*  */
#define CUSTOM_ATTRIBUTES_GAIKAN                                    ('gaikan')      /*  */
#define CUSTOM_ATTRIBUTES_FMT                                       ('fmt')         /*  */
#define CUSTOM_ATTRIBUTES_STS                                       ('sts')         /*  */
#define CUSTOM_ATTRIBUTES_ALTID                                     ('altid')       /*  */
#define CUSTOM_INIT_CLASS                                           ('initClass')   /*  */
#define CUSTOM_INIT_TEXT                                            ('initText')    /*  */
#define CUSTOM_NULL_STR_INIT_APP                                    ('nullStrInitApp')/*  */
#define CUSTOM_MIN_LEN                                              ('minlen')      /*  */
#define CUSTOM_MAX_LEN                                              ('maxlen')      /*  */
#define CUSTOM_TIP_ICHI                                             ('tipIchi')     /*  */
#define CUSTOM_LIMIT                                                ('limit')       /*  */
#define CUSTOM_PAGE_ATR                                             ('PageAtr')     /*  */
#define GROUP_NAME_TENKEY                                           ('tenkey')      /*  */
#define GROUP_NAME_EKI_BTN                                          ('ekibtn')      /*  */
#define GROUP_NAME_KEIYU_BTN                                        ('Keiyu')       /*  */
#define GROUP_NAME_MONTH_MOVE                                       ('MonthMove')   /*  */
#define GROUP_NAME_CALENDAR_DATE                                    ('CalendarDate')/*  */
#define GROUP_NAME_ITAKU                                            ('itaku')       /*  */
#define GROUP_NAME_ZASEKI                                           ('Zaseki')      /*  */
#define GROUP_NAME_RESSHA_SHUBETSU                                  ('ResshaShubetsu')/*  */
#define GROUP_NAME_COUPON                                           ('Coupon')      /*  */
#define GROUP_NAME_IKKATSU_SET                                      ('ikkatsu_set') /*  */
#define TAG_ID_NAME_ENTER                                           ('Enter')       /*  */
#define TAG_ID_NAME_START_BTN                                       ('StartBtn')    /*  */
#define TAG_ID_NAME_RESET_BTN                                       ('ResetBtn')    /*  */
#define TAG_ID_NAME_UNCHIN_SHOKAI                                   ('FareInquiryBtn')/*  */
#define TAG_ID_NAME_CLEAR                                           ('Clear')       /*  */
#define TAG_ID_NAME_TAB                                             ('Tab')         /*  */
#define TAG_ID_NAME_ALT_TAB                                         ('AltTab')      /*  */
#define TAG_ID_NAME_BACK_SPACE                                      ('BS')          /*  */
#define TAG_ID_NAME_CURSOR_IMAGE                                    ('Coursor')     /*  */
#define TAG_ID_NAME_SEINEN_GAPPI                                    ('SeinenGappi') /*  */
#define TAG_ID_NAME_ENABLE_AREA                                     ('_Enable')     /*  */
#define TAG_ID_NAME_EKI_BTN                                         ('E')           /*  */
#define TAG_ID_NAME_KEIYU_BTN                                       ('R')           /*  */
#define TAG_ID_NAME_SET_CHAR_SPAN                                   ('SetCharSpan') /*  */
#define TAG_ID_NAME_WAREKI                                          ('_wa')         /*  */
#define TAG_ID_INPUT_TABS                                           ('Input_Tabs')  /*  */
#define TAG_ID_INPUT_CALENDAR_DATE                                  ('Date')        /*  */
#define TAG_ID_TAB_PAGE_AREA                                        ('_area')       /*  */
#define TAG_ID_TOOLTIP                                              ('ToolTip')     /*  */
#define FMT_NAME_DATE_OF_BIRTH                                      ('DateOfBirth') /*  */
#define FMT_NAME_BUTTON_NO_INPUT                                    ('ButtonNoInput')/*  */
#define FMT_NAME_EDIT_COMMA                                         ('EditComma')   /*  */
#define FMT_NAME_EDIT_COMMA_YEN                                     ('EditCommaYen')/*  */
#define FMT_NAME_EDIT_COMMA_YEN_NOMI                                ('EditCommaYen_Nomi')/*  */
#define FMT_NAME_DATE_YEAR_TWO_DGITS                                ('DateYearTwoDgits')/*  */
#define FMT_NAME_DATE_YEAR_TWO_DGITS_JP                             ('DateYearTwoDgits_Jpn')/*  */
#define FMT_NAME_DATE_YEAR_FOUR_DGITS                               ('DateYearFourDgits')/*  */
#define FMT_NAME_DATE_MONTH_DAY                                     ('DateMonthDay')/*  */
#define FMT_NAME_SCHOOL_YEAR                                        ('SchoolYear')  /*  */
#define FMT_NAME_PASSWORD                                           ('Password')    /*  */
#define STS_NAME_UPDATE_ELEMENT_PARENT                              ('pa')          /*  */
#define STS_NAME_UPDATE_ELEMENT_CHILD                               ('ch')          /*  */
#define STS_NAME_DISABLED_ENABLE                                    ('enable')      /*  */
#define STS_NAME_DISABLED_DISABLE                                   ('disable')     /*  */
#define STS_INDEX_DESIGN                                            (0)             /*  */
#define STS_INDEX_UPDATE_ELEMENT                                    (1)             /*  */
#define STS_INDEX_VISIBILITY                                        (2)             /*  */
#define STS_INDEX_DISABLE                                           (3)             /*  */
#define STS_INDEX_BLINK                                             (4)             /*  */
#define INPUT_CHECK_INPUT_ALL                                       ('InputAll')    /*  */
#define INPUT_CHECK_INPUT_ALL_NULL                                  ('InputAll_Null')/*  */
#define INPUT_CHECK_DATE_VALIDITY                                   ('DateValidity')/*  */
#define INPUT_CHECK_TIME_VALIDITY                                   ('TimeValidity')/*  */
#define INPUT_CHECK_NUM_CHECK                                       ('NumCheck')    /*  */
#define CLICK_BRANCHMODE_OTHER_INPUT                                (0)             /*  */
#define CLICK_BRANCHMODE_NOT_APPOINT                                (99)            /*  */
#define DUMMY_IMG_URL                                               ('img/dummy.png')/*  */
#define POOUP_DISP_POTICION_INDEX_CENTER                            (1)             /*  */
#define CURSOR_IMAGE_URL                                            ('../../img/cur.png')/*  */
#define KEYBOARD_DATA_ENTER                                         ('enter')       /*  */
#define KEYBOARD_DATA_START_BTN                                     ('startbtn')    /*  */
#define KEYBOARD_DATA_RESET_BTN                                     ('resetbtn')    /*  */
#define KEYBOARD_DATA_CLEAR                                         ('clear')       /*  */
#define KEYBOARD_DATA_TAB                                           ('tab')         /*  */
#define KEYBOARD_DATA_ALT_TAB                                       ('alttab')      /*  */
#define KEYBOARD_DATA_BS                                            ('bs')          /*  */
#define DISPLAY_REQUEST_TYPE_PAGE_SWITCH                            (0)             /*  */
#define DISPLAY_REQUEST_TYPE_CALENDAR                               (1)             /*  */
#define DISPLAY_REQUEST_TYPE_POPUP                                  (2)             /*  */
#define DISPLAY_REQUEST_TYPE_BUTTON                                 (3)             /*  */
#define DISPLAY_REQUEST_TYPE_TEXT_ITEM                              (4)             /*  */
#define DISPLAY_REQUEST_TYPE_IMAGE                                  (5)             /*  */
#define DISPLAY_REQUEST_TYPE_TOOLTIP                                (6)             /*  */
#define AREA_NAME_KINOU                                             ('top_iframe')  /*  */
#define AREA_NAME_STS_IDICATION                                     ('sts_idication')/*  */
#define AREA_NAME_DISP                                              ('disp')        /*  */
#define AREA_NAME_OPERATION                                         ('operation')   /*  */
#define AREA_NAME_POPUP                                             ('popup')       /*  */
#define AREA_NAME_IMG_DISP                                          ('img_disp')    /*  */
#define DESIGN_MULTI_CLASS                                          (1)             /*  */
#define DESIGN_SELECT                                               (2)             /*  */
#define DESIGN_NOT_SELECT                                           (3)             /*  */
#define DESIGN_ERROR                                                (4)             /*  */
#define DESIGN_DISABLE                                              (5)             /*  */
#define DESIGN_INIT                                                 (6)             /*  */
#define DESIGN_VISIBLE                                              (7)             /*  */
#define DESIGN_HIDDEN                                               (8)             /*  */
#define DESIGN_BLINK                                                (9)             /*  */
#define DESIGN_BLINK_MOJI                                           (10)            /*  */
#define DESIGN_INPUT_ERROR                                          (11)            /*  */
#define DESIGN_INPUT_NO_CHANGE                                      (12)            /*  */
#define DESIGN_INPUT_AUTO                                           (13)            /*  */
#define DESIGN_INPUT_INIT_DISP                                      (14)            /*  */
#define DESIGN_BTN_OFF                                              (15)            /*  */
#define DESIGN_BTN_ON                                               (16)            /*  */
#define DESIGN_BTN_BLINK                                            (17)            /*  */
#define DESIGN_BTN_DISABLE                                          (18)            /*  */
#define DESIGN_TEXT_NOT_SELECT                                      (19)            /*  */
#define DESIGN_TEXT_SELECT                                          (20)            /*  */
#define DESIGN_TEXT_ERROR                                           (21)            /*  */
#define DESIGN_TEXT_BLINK_MOJI                                      (22)            /*  */
#define DESIGN_TEXT_BLINK                                           (23)            /*  */
#define DESIGN_TEXT_DEFAULT                                         (24)            /*  */
#define DESIGN_TEXT_DISABLE                                         (25)            /*  */
#define DESIGN_TEXT_INIT_DISP                                       (26)            /*  */
#define DESIGN_ERROR_BLINK_MOJI                                     (27)            /*  */
#define DESIGN_ERROR_BLINK                                          (28)            /*  */
#define DESIGN_ERROR_BACKGROUND_CHANGE                              (29)            /*  */
#define DESIGN_ERROR_MOJI_CHANGE                                    (30)            /*  */
#define DESIGN_CHAR_COLOR_RED                                       (31)            /*  */
#define CONV_YEAR_ANNO_DOMINI                                       (0)             /*  */
#define CONV_YEAR_JAPANESE_CALENDAR                                 (1)             /*  */
#define DISP_COMMA_NOT_AVAILABLE                                    (0)             /*  */
#define DISP_COMMA_AVAILABLE                                        (1)             /*  */
#define ZERO_PADDING_NOT_AVAILABLE                                  (0)             /*  */
#define ZERO_PADDING_AVAILABLE                                      (1)             /*  */
#define ZERO_PADDING_AVAILABLE_NULL                                 (2)             /*  */
#define RESOLUTIVE_MODE_ENTER                                       ('Enter')       /*  */
#define RESOLUTIVE_MODE_INPUT                                       ('Input')       /*  */
#define CONVMODE_DISP                                               ('DispProcNo')  /*  */
#define CONVMODE_INPUT                                              ('InputProcNo') /*  */
#define INPUT_INIT_SHIJI_NOT_CHANGE                                 (99)            /*  */
#define INPUT_INIT_SHIJI_FIRST_CLEAR                                (1)             /*  */
#define INPUT_INIT_SHIJI_CLEAR                                      (0)             /*  */
#define INPUT_CANCEL_SHIJI_NOT_CHANGE                               (99)            /*  */
#define INPUT_CANCELT_SHIJI_CLEAR                                   (0)             /*  */
#define INPUT_CANCEL_SHIJI_BEFORE_DATA                              (1)             /*  */
#define ERROR_RESOLUTIVE_INPUT_FIRST                                (1)             /*  */
#define ERROR_RESOLUTIVE_ENTER                                      (2)             /*  */
#define ERROR_RESOLUTIVE_NO_RESOLUTIVE                              (99)            /*  */
#define FLG_OBJECT_VISIBLE                                          (0)             /*  */
#define FLG_OBJECT_HIDDEN                                           (1)             /*  */
#define FLG_OBJECT_DESTRUCTION                                      (0)             /*  */
#define FLG_OBJECT_CREATE                                           (1)             /*  */
#define FLG_OBJECT_BLINK_STOP                                       (0)             /*  */
#define FLG_OBJECT_BLINK_START                                      (10)            /*  */
#define FLG_OBJECT_ENABLE                                           (0)             /*  */
#define FLG_OBJECT_NOT_ENABLE                                       (1)             /*  */
#define AUOT_SET_TEXT                                               (1)             /*  */
#define AUOT_NOT_SET_TEXT                                           (0)             /*  */
#define WAY_DATA_ALL                                                (0)             /*  */
#define WAY_DATA_SPECIFIED                                          (1)             /*  */
#define CHAR_COLOR_MODE_DELETE                                      (0)             /*  */
#define CHAR_COLOR_MODE_ADD                                         (1)             /*  */
#define ASSIGN_CLASS_MODE_DEL                                       (0)             /*  */
#define ASSIGN_CLASS_MODE_ADD                                       (1)             /*  */
#define DATA_KIND_BUTTON_TAG_ID                                     (0)             /*  */
#define DATA_KIND_DISP_TEXT                                         (1)             /*  */
#define CHANGE_FLAG_FALSE                                           (0)             /*  */
#define CHANGE_FLAG_TRUE                                            (1)             /*  */
#define STS_SPLIT                                                   ('_')           /*  */
#define HOLIDAY_SPLIT                                               ('_')           /*  */
#define TAG_ID_SPLIT                                                ('_')           /*  */
#define UNDER_SCORE_SPLIT                                           ('_')           /*  */
#define IKKATSU_DATA_SPLIT                                          ('，')          /*  */
#define ALT_BUTTON_AUTO_TEXT_SPLIT                                  ('?')           /*  */
#define CSS_CLASS_NOTHING                                           ('－')          /*  */
#define FORMAT_INPUT_ITEM                                           ('△')          /*  */
#define CHARACTER_SPACE                                             ('　')          /*  */
#define CURSOR_IMAGE_MARGIN_CHARACTER                               (1)             /*  */
#define PIXEL                                                       ('px')          /*  */
#define DISP_CONTROL_ENTIRE_ENABLE                                  ('entire_display')/*  */
#define GROUP_NAME_PAGE_SHITEI                                      ('PageShitei')  /*  */
#define SPEC_ASSIGN_CLASS                                           ('@')           /*  */
#define UNDERBAR_REPLACE_STR                                        ('#')           /*  */
#define TAG_ID_NAME_INPUT_PASS                                      ('_Hidden')     /*  */
#define DISP_PASS_CHARACTER                                         ('＊')          /*  */
#define CALENDAR_DISP_NO_LIMIT_START_DATE                           ('00000000')    /*  */
#define CALENDAR_DISP_NO_LIMIT_END_DATE                             ('99999999')    /*  */
#define CALENDAR_DISP_NO_LIMIT_YEAR_RANGE_START                     (2)             /*  */
#define CALENDAR_DISP_NO_LIMIT_YEAR_RANGE_END                       (2)             /*  */
#define CALENDAR_DISP_TYPE_CALENDAR                                 ('calendar')    /*  */
#define CALENDAR_DISP_TYPE_KIKAN                                    ('kikan')       /*  */
#define INPUT_LENGTH_NASHI_MODE                                     ('－')          /*  */
#define INPUT_LENGTH_EMPTY_OR_ALL                                   ('◆')          /*  */
#define INPUT_MAX_LENGTH_LIMIT                                      (999)           /*  */
#define PECULIAR_PROC_GAIKAN                                        ('@@')          /*  */
#define HEIGHT_CLASS_H                                              ('h')           /*  */
#define HEIGHT_CLASS_HL                                             ('hl')          /*  */
#define HEIGHT_WIDTH_CLASS_GRID                                     ('grid')        /*  */
#define TAG_ID_NAME_FUKURO_TAB                                      ('Fukuro_Tab')  /*  */
/* [%END  %;%シンボル名%;Common symbol] */


#endif /* DGT_SYMBOLDEF_H */

/***********************************************************************

    EOF

***********************************************************************/
