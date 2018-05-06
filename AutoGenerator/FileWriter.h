#pragma once
////////////////////////////////////////////////////////////////////////////////
//
//  �t�@�C�����FFileWriter.h
//
//  �T�v�@�@�@�FWrite data to text file
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
#include <Windows.h>
#include <fstream>
using namespace std;

class CFileWriter : public fstream
{
public:
    CFileWriter(void);
    ~CFileWriter(void);

private:
    string          m_sFilePath;

public:
    inline VOID SetFilePath( string sInFilePath )
    {
        m_sFilePath = sInFilePath;
    }
    // Methods
    BOOL WriteAt( string sInMark, string sInContent, LPDWORD lpdwOutErrCode );      // Write at bookmark
    BOOL WriteAppend( string sInContent, LPDWORD lpdwOutErrCode );                  // Write append to file
    BOOL WriteIfNotExist( string sInMark, string sInContent, LPDWORD lpdwOutErrCode );// Write at bookmark if content not exist
};

