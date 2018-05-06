////////////////////////////////////////////////////////////////////////////////
//
//  �t�@�C�����FUtility.cpp
//
//  �T�v�@�@�@�FContain all utility functions such as CheckFilePath, IsNumeric
//
//  �쐬�ҁ@�@�F(TSDV) TrungLV
//
//  ����      �F
//
//  IDE       �FMicrosoft VisualC++ 2010
//
// 
//  �ύX����
//  �o�[�W�����@     ���t�@�@�@�@  �����@�@�@�@       ���l
//  DGT-00.00.00    2015/02/25   (TSDV) TrungLV     Create New
//

//
////////////////////////////////////////////////////////////////////////////////
// $Header: $
#include "Utility.h"
#include "DGT_SymbolDef.h"
#include "DGT_PvSymbolDef.h"
#include "DGT_PvErrCode.h"
#include "DataStructure.h"
#include <codecvt>
#include <locale>
#include <algorithm>
#include <regex>

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  CheckFilePath
//
//�@�\�@�@��@�F  Check the validation of file path
//
//�@�T�@�@�v�@�F  Check the validation of file path
//
//�@�߁@��@�l�F  
//
//�@���@�@���@�F  string           sInFilePath          File path
//                         LPWORD           lpwOutExtension      Extension result
//                         LPWORD           lpwOutCheckResult    Check result
//                         LPDWORD          lpdwOutErrCode       Error code
//
//  �o�[�W�����@     ���t          ����              ���l
//  DGT-00.00.00    2015/02/25   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CheckFilePath(
                   const string &sInFilePath,
                   LPWORD lpwOutCheckResult,
                   LPDWORD lpdwOutErrCode )
{
    // Local variable
    DWORD           dwFileAttr     = DGT_VALUE_ZERO_DWORD;       // File Attribute

    // Check lpdwOutErrCode is NULL?
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    // Check lpwOutCheckResult is NULL?
    if ( lpwOutCheckResult == NULL )
    {
       *lpdwOutErrCode = DGT_ERR_U_CFIP_PARA;
        return DGT_RET_ERR;
    }
    else
    {
        // Do nothing
    }

    // Check sInFilepath.size is Zero?
    if ( sInFilePath.size() == 0 )
    {
        *lpwOutCheckResult =  DGT_U_CFIP_PATH_NULL;
        return DGT_RET_OK;
    }
    else
    {
        // Do nothing
    }

    // Check sInFilepath.size is > MAX_PATH?
    if ( sInFilePath.size() > MAX_PATH )
    {
        *lpwOutCheckResult = DGT_U_CFIP_PATH_TOO_LONG;
        return DGT_RET_OK;
    }
    else
    {
        // Do nothing
    }

    //Get file attributes
    dwFileAttr = GetFileAttributes((LPCTSTR) sInFilePath.c_str() );
    if ( dwFileAttr == INVALID_FILE_ATTRIBUTES )
    {
        *lpwOutCheckResult = DGT_U_CFIP_PATH_INVALID;
        return DGT_RET_OK;
    }
    else
    {
        // Do nothing
    }

    *lpwOutCheckResult = DGT_U_CFIP_PATH_OK;

    return DGT_RET_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  CheckFolderPath
//
//�@�\�@�@��@�F  Check the validation of folder path
//
//�@�T�@�@�v�@�F  Check the validation of folder path
//
//�@�߁@��@�l�F  
//
//�@���@�@���@�F  string               sInFolderPath            Folder path
//                         LPWORD           lpwOutExtension        Extension result
//                         LPWORD           lpwOutCheckResult    Check result
//                         LPDWORD         lpdwOutErrCode        Error code
//
//  �o�[�W�����@     ���t          ����              ���l
//  DGT-00.00.00    2015/02/25   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CheckFolderPath( 
             const string &sInFolderPath, 
             LPWORD lpwOutCheckResult, 
             LPDWORD lpdwOutErrCode)
{
    // Init local parameters
    DWORD dwFileAttr  = DGT_VALUE_ZERO_DWORD;       // File Attribute

    // Check error code
    if ( lpdwOutErrCode == NULL )
    {
        return DGT_RET_ERR;
    }
    else
    {
        *lpdwOutErrCode = DGT_VALUE_ZERO_DWORD;
    }

    if ( lpwOutCheckResult   == NULL )
    {
       *lpdwOutErrCode = DGT_ERR_CC_CFP_PARA;
        return DGT_RET_ERR;
    }
    else
    {
        *lpwOutCheckResult   = DGT_VALUE_ZERO_WORD;
    }

    if ( sInFolderPath.length() == 0 )
    {
        *lpwOutCheckResult = DGT_U_CFP_PATH_NULL;
        return DGT_RET_OK;
    }
    else
    {
        // Do nothing
    }

    if ( sInFolderPath.size() > MAX_PATH )
    {
        *lpwOutCheckResult = DGT_U_CFP_PATH_TOO_LONG;
        return DGT_RET_OK;
    }
    else
    {
        // Do nothing
    }

    // Check the path is directory or not
    dwFileAttr = GetFileAttributes((LPCTSTR) sInFolderPath.c_str() );
    if ( dwFileAttr == INVALID_FILE_ATTRIBUTES )
    {
        *lpwOutCheckResult = DGT_U_CFP_PATH_INVALID;
        return DGT_RET_OK;
    }
    else
    {
        // Do nothing
    }

    if (( ( LONG )dwFileAttr & FILE_ATTRIBUTE_DIRECTORY ) != 0 )
    {
        *lpwOutCheckResult = DGT_U_CFP_PATH_OK;
    }
    else
    {
        *lpwOutCheckResult = DGT_U_CFP_PATH_INVALID;
    }

    return DGT_RET_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SplitString
//
//�@�\�@�@��@�F  Split String
//
//�@�T�@�@�v�@�F  Split String
//
//�@�߁@��@�l�F  
//
//�@���@�@���@�F  string           sInString              Input string
//                         string           sInDelimiter          Delimiter
//
//  �o�[�W�����@     ���t          ����              ���l
//  DGT-00.00.00    2015/02/25   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
 vector<string> SplitString( 
                           string sInString, 
                           const string &sInDelimiter)
{
    // Local variable
    vector<string>  sOutStringList;   //  Out string vector
    string          sToken;             //  Token
    DWORD           dwPos;               //  Position

    while (( dwPos = sInString.find( sInDelimiter )) != std::string::npos )
    {
        sToken = sInString.substr( 0, dwPos );
        //sToken.erase(std::remove(sToken.begin(), sToken.end(), ' '),  sToken.end());
        if ( sToken.size() >= 1 )
        {
            if ( sToken.substr(sToken.size() - 1, 1) == " " )
            {
                sToken = sToken.substr( 0, sToken.size() - 1 );
            }
        }
        sOutStringList.push_back( sToken );
        sInString.erase(0, dwPos + sInDelimiter.length());
    }
    sOutStringList.push_back( sInString );
    return sOutStringList;
}

BOOL CopyDirTo( const string& source_folder, const string& target_folder )
{
    string  new_sf = source_folder + "\\*";
    CHAR    sf[MAX_PATH + 1];
    CHAR    tf[MAX_PATH + 1];
    BOOL    bRet = FALSE;

    strcpy_s( sf, new_sf.c_str());
    strcpy_s( tf, target_folder.c_str());

    sf[strlen(sf) + 1] = 0;
    tf[strlen(tf) + 1] = 0;

    SHFILEOPSTRUCT s = { 0 };
    s.wFunc = FO_COPY;
    s.pTo = tf;
    s.pFrom = sf;
    s.fFlags = FOF_SILENT | FOF_NOCONFIRMMKDIR | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NO_UI;
    int res = SHFileOperation( &s );

    if ( res == 0 )
    {
        bRet = TRUE;
    }
    else
    {
        // Do nothing
    }
    return bRet;
}

 /////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  GetAllFileInFolder
//
//�@�\�@�@��@�F  Get all file in folder
//
//�@�T�@�@�v�@�F  Get all file in folder
//
//�@�߁@��@�l�F  
//
//�@���@�@���@�F  string           sInFolderPath              Folder path ( This file path must have follow parse: ex: C:\\Test\\ )
//                         string           vInExtension               Extension of file path to filter
//
//  �o�[�W�����@     ���t          ����              ���l
//  DGT-00.00.00    2015/02/27   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL  GetAllFileInFolder( string sInFolderPath, const vector<string> &vInExtension, vector<string> &vListOutFilePath , BOOL bOnlyFileName  )
{
    // Local variable
    WIN32_FIND_DATA      ffd;
    HANDLE               hFind          = INVALID_HANDLE_VALUE;
    string               sFileName      = "";
    string               sExtension     = "";
    string               sFolderPath    = "";
    DWORD                dwPos          = DGT_VALUE_ZERO_DWORD;
    DWORD                dwCnt          = DGT_VALUE_ZERO_DWORD;

    // Clear list file
    vListOutFilePath.clear();

    if ( sInFolderPath[sInFolderPath.size() - 1] == '\\' )
    {
        sInFolderPath += "*";
    }
    else
    {
        sInFolderPath += "\\*";
    }

    hFind = FindFirstFile(sInFolderPath.c_str(), &ffd);
    if (INVALID_HANDLE_VALUE == hFind) 
    {
        return FALSE;
    } 

    do
    {
        if (( ( LONG )ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) || ( ( LONG )ffd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) )
        {
            continue;
        }
        else
        {
            sFileName        = ""; 
            dwPos             = DGT_VALUE_ZERO_DWORD;
            sFileName       = string( ffd.cFileName );
            dwPos            = sFileName.find_last_of(".");
            if ( std::string::npos != dwPos )
            {
                sExtension = sFileName.substr( dwPos );
                // Filter extension
                for ( dwCnt = 0 ; dwCnt < vInExtension.size(); dwCnt ++ )
                {
                    sFolderPath = "";
                    if ( strcmp( sExtension.c_str() , vInExtension[dwCnt].c_str() ) == 0 )
                    {
                        if ( bOnlyFileName )
                        {
                            vListOutFilePath.push_back( sFileName );
                        }
                        else
                        {
                            sFolderPath = sInFolderPath.substr(0, sInFolderPath.size() - 1 ) + sFileName;
                            vListOutFilePath.push_back( sFolderPath );
                        }
                        continue;
                    }
                }
            }
            else
            {
                // Do nothing
            }
        }
    }
    while (FindNextFile(hFind, &ffd) != 0);

    FindClose(hFind);

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  SuchiCheck
//
//�@�\�@�@��@�F  SuchiCheck
//
//�@�T�@�@�v�@�F  SuchiCheck
//
//�@�߁@��@�l�F  
//
//�@���@�@���@�F  string           checkStr
//
//  �o�[�W�����@     ���t          ����              ���l
//  DGT-00.00.00    2015/02/27   (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
LONG SuchiCheck( const string &sCheckstr)
{
    LONG sts = 0;
    string sConvStr = "";
    // Convert all full number to half number
    ConvFullHalNumberFunc( sCheckstr, TRUE, sConvStr );

    if ( ( sConvStr == "" ) ||  ( sConvStr == "�|" ) )
    {
        sts = 0;
    }
    else
    {
        if (IsStringNumber(sConvStr) == TRUE)
        {
            sts = 1;
        }
        else
        {
            sts = -1;
        }
    }

    return sts;
}


BOOL IsStringNumber( const string &sNumString )
{
    BOOL            bCheckResult        = TRUE;
    DWORD           dwIndex             = 0;    // Internal index counter
    BOOL            bFloat              = FALSE;
    // Check sNumString is empty
    if ( sNumString.size() == 0 )
    {
        bCheckResult = FALSE;
    }
    else
    {
        // Do nothing
    }

    if ( CheckNashiMode( sNumString ) == TRUE )
    {
        return FALSE;
    }

    for ( dwIndex = 0; dwIndex < sNumString.size(); dwIndex++ )
    {
        if (isdigit( sNumString[dwIndex] ))
        {
            // Do nothing
        }
        else if (( sNumString[dwIndex] == '.' ) && ( bFloat == FALSE ))
        {
            bFloat = TRUE;
        }
        else
        {
            bCheckResult = FALSE;
        }
    }
    return bCheckResult;
}


//BOOL SetIchiInfo( 
//            //const string &sInAreaJP, 
//            const string &sInIchi,
//            vector<DWORD> &vOutIchi, 
//            DWORD h_grid_size,
//            DWORD w_grid_size, 
//            DWORD dwInMarginTop, 
//            DWORD dwInMarginLeft )
//{
//    // Local variable
//    string                  separators          = "-"; 
//    vector<string>     wkstr;
//
//    if (sInIchi == NASHI_MODE)
//    {
//        return TRUE;
//    }
//
//    wkstr = SplitString( sInIchi, separators );
//
//    vOutIchi[ITEM_TOP] = (  (atoi(wkstr[0].c_str()) - 1)* ( h_grid_size )  )  + dwInMarginTop;
//    vOutIchi[ITEM_LEFT] = (  (atoi(wkstr[1].c_str()) - 1) * w_grid_size  ) + dwInMarginLeft; 
//
//    return TRUE;
//}


LONG SerchTagName_index( const string &TagName)
{
    const char* TAG_NAME_LIST[13] =  { "button", "div", "a", "span", "image", "ul", "li", "pre", "time", SEINENGAPPI, CONTENA, MSGAREA, IMG_STRETCH };
    DWORD dwIndex = 0;
    for ( dwIndex = 0; dwIndex < 13; dwIndex++)
    {

        if ( strcmp(TAG_NAME_LIST[dwIndex], TagName.c_str() ) == 0 )
        {
            return dwIndex;
        }
    }
    if (( TagName.size() > 0 ) && ( TagName.size() > ( sizeof(MSGAREA)/sizeof(char))))
    {
        if ( TagName.substr( 1, ( sizeof( MSGAREA )/sizeof( char ) )) == MSGAREA )
        {
            return dwIndex - 1;
        }
    }
    //delete []TAG_NAME_LIST;
    return -1;
}

 BOOL CheckNashiMode(const string &sTarget)
 {
     BOOL bSts;
     if ((  sTarget ==  NASHI_MODE )          ||
         (  sTarget ==  NASHI_MODE_HALF )     ||
         (  sTarget ==  NASHI_MODE_JP ))
     {
         bSts = TRUE;
     }
     else
     {
         bSts = FALSE;
     }
     return bSts;
 }

 string GetBtnValue( const vector<string> &row)
 {
     string wk_btn = "";
     if (CheckNashiMode(row[SENDSTR1_COL]) == FALSE)
     {
         wk_btn = row[SENDSTR1_COL];
     }
     else { }
     // �I���^�l�[�g���̘A���t�̏ꍇ
     if (CheckNashiMode(row[ALTERNATE_TAGID_COL]) == FALSE)
     {
         wk_btn += "?";
         if (CheckNashiMode(row[SENDSTR2_COL]) == FALSE)
         {
             wk_btn += row[SENDSTR2_COL];
         }
         else { }
     }
     else { }

     try
     {
         wk_btn = std::regex_replace( wk_btn, std::regex("\n"), string("\\n") );
     }
     catch( const exception& e )
     {
     }

     return wk_btn;
 }

 string GetEkiBtn( const vector<string> &row)
 {
     string wk_btn = "";
     if (row[EKIBTN_ID_COL] != "")
     {
         wk_btn = row[EKIBTN_ID_COL];
     }
     else
     {
         wk_btn = GetBtnValue(row);
     }
     return wk_btn;
 }


 VOID ReplaceStr( string& str, const string &sInOldStr, const string &sInNewStr )
 {
     // Initialize
     size_t     pos         = string::npos;             // Searching result

     while ( pos = str.find( sInOldStr.c_str()))
    {
        if ( pos == string::npos )
        {
            break;
        }
        else
        {
            str.replace( pos, pos + sInOldStr.length(), sInNewStr );
        }
    };
     return;
 }

 VOID ReplaceChar13( string& str )
 {
     string     sEndLine    = "";
     sEndLine               = char( 13 );
     char       cEndLine    = 13;
     for ( size_t i = 0; i < str.length(); i++ )
     {
         if ( str.at( i ) == cEndLine )
         {
             str.replace( i, i + 1, "\\n" );
             i++;
         }
         else
         {
            // Do nothing
         }
     }
 }

 wstring StringToWChar( const string &sInString )
 {
     WCHAR*    wWideCharStr = NULL;
     wstring   wsreturnStr = L"";
     DWORD dwMinSize = MultiByteToWideChar( CP_ACP, 0, sInString.c_str(), -1, NULL, 0 );
     wWideCharStr = ( WCHAR* ) malloc( dwMinSize * 2 + 2 );
     MultiByteToWideChar( CP_ACP, 0, sInString.c_str(), -1, wWideCharStr, ( dwMinSize * 2 + 2 ));
     wsreturnStr = wstring(wWideCharStr);
     free( wWideCharStr);
     return wsreturnStr;
 }

LONG ConvFullHalNumberFunc( const string &sInConvData, BOOL bInHalfFlg, string &sOutConvData )
{
    // Initilize
    LONG          lRet            = GUI_RET_OK;
    DWORD         nRoopCount      = 0; // Counter
    string        aryHalfNumber[] = {"0",  "1" , "2", "3",  "4",  "5",  "6",  "7",  "8",  "9",","}; // half
    string        aryFullNumber[] = {"�O", "�P", "�Q","�R", "�S", "�T", "�U", "�V", "�W" ,"�X","�C"}; // Full

    // Check parameter
    if ( sInConvData == "" )
    {
        sOutConvData = "";
        lRet = ERROR_CODE_NULL;
        return lRet;
    } 
    else 
    {}
    sOutConvData = sInConvData;
    wstring      wsOutConvData = StringToWChar( sInConvData );
    try
    {
        for ( nRoopCount = 0; nRoopCount < 11; nRoopCount++ )
        {
            if( bInHalfFlg )
            {
                // Convert to half.
                wsOutConvData = regex_replace( wsOutConvData, wregex( StringToWChar(aryFullNumber[nRoopCount] )), StringToWChar(aryHalfNumber[nRoopCount]) );
            }
            else
            {
                // Convert to full
                sOutConvData = regex_replace( sOutConvData, regex( aryHalfNumber[nRoopCount] ), aryFullNumber[nRoopCount] );
            }
        }
    }
    catch( const exception& e )
    {
        lRet = ERROR_CODE_NULL;
        return lRet;
    }
    if ( bInHalfFlg )
    {
        sOutConvData = WCharToString( wsOutConvData );
    }
    return lRet;
}

string WCharToString( const wstring &sInWideString )
{
    if ( sInWideString.empty() ) return "";
    int size_needed = WideCharToMultiByte( CP_ACP, 0, &sInWideString[0], ( int ) sInWideString.size(), NULL, 0, NULL, NULL );

    std::string sReturnStr( size_needed, 0 );
    WideCharToMultiByte( CP_ACP, 0, &sInWideString[0], ( int ) sInWideString.size(), &sReturnStr[0], size_needed, NULL, NULL );
    return sReturnStr;
}

void DeleteAllFiles( string sInFolderPath)
{
  // Local variable
    WIN32_FIND_DATA      ffd;
    HANDLE               hFind          = INVALID_HANDLE_VALUE;
    string               sFileName      = "";
    string               sExtension     = "";
    string               sFilePath    = "";
    DWORD                dwPos          = DGT_VALUE_ZERO_DWORD;
    DWORD                dwCnt          = DGT_VALUE_ZERO_DWORD;

    if ( sInFolderPath.size() == 0 )
    {
        return;
    }

    if ( sInFolderPath[sInFolderPath.size() - 1] == '\\' )
    {
        sInFolderPath += "*";
    }
    else
    {
        sInFolderPath += "\\*";
    }

    hFind = FindFirstFile(sInFolderPath.c_str(), &ffd);
    if (INVALID_HANDLE_VALUE == hFind) 
    {
        return ;
    } 

    do
    {
        sFileName       = string( ffd.cFileName );
        // Do not delete .log file
        if ((dwPos = sFileName.find_last_of("." )) != std::string::npos )
        {
            if ( sFileName.substr( dwPos +1 ) == "log")
            {
                continue;
            }
        }
        if (( sFileName != ".") && ( sFileName != ".." ))
        {
            sFilePath = sInFolderPath.substr(0, sInFolderPath.size() - 1 ) + sFileName;
            if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
            {
                DeleteAllFiles(sFilePath);
                RemoveDirectory(sFilePath.c_str());
            }
            else
            {
                DeleteFile(sFilePath.c_str());
            }
        }
    }
    while (FindNextFile(hFind, &ffd) != 0);

    FindClose(hFind);

    return;
}

string Utf8toAnsi( const char *cInUtf8, DWORD dwInlen )
{

    // Initialize
    CHAR    *cAnsistr    = NULL;
    DWORD   dwlength    = MultiByteToWideChar(CP_UTF8, 0, cInUtf8, dwInlen*2, NULL, NULL );
    WCHAR   *lpszW      = NULL;
    string  sReturnStr  = "";
    lpszW       =   new WCHAR[dwlength+1];
    cAnsistr     =   ( char * ) calloc ( sizeof(char), dwlength+5 );

    // Convert to wide char
    MultiByteToWideChar(CP_UTF8, 0, cInUtf8, -1, lpszW, dwlength );

    //Conversion to ANSI (CP_ACP)
    WideCharToMultiByte(CP_ACP, 0, lpszW, -1, cAnsistr, dwlength, NULL, NULL);

    // Add end of string
    if ( cAnsistr != NULL )
    {
        cAnsistr[dwlength] = 0;
        sReturnStr = string(cAnsistr);
    }
    // Delete string
    delete[] lpszW;
    delete[] cAnsistr;
    return sReturnStr;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�ց@���@���F  ProcessFunctionName
//
//�@�\�@�@��@�F  Process function name
//
//�@�T�@�@�v�@�F  Process function name
//
//�@�߁@��@�l�F  
//
//�@���@�@���@�F  string                  sFuncName              (I)              Function name
//
//  �o�[�W�����@     ���t          ����              ���l
//  DGT-00.00.00    2015/09/07    (TSDV) TrungLV     Create New
//

//
/////////////////////////////////////////////////////////////////////////////////////////////
void ProcessFunctionName( string &sFuncName )
{
    // Function name start by number9 Ex: 123popup-> Add one character
    sFuncName = regex_replace( sFuncName, regex("[^0-9a-zA-Z]"), string("_"));
    return;
}
