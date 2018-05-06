#pragma once
#include "afxwin.h"
#include "Utility.h"

// CStatusDlg dialog


class CStatusDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CStatusDlg)

public:
    CStatusDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CStatusDlg();

// Dialog Data
    enum { IDD = IDD_STATUSDLG };

protected:
    // Components
    CStatic         m_cStatusText;
    CStatic         m_cStatusPercent;
    CListBox        m_cLogListBox;
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedExit();

public:
    // Methods
    VOID UpdateStatus( const LPSCT_PROG_STATUS lpSctInStatus );
    VOID OnOK();
    VOID ClearLog();
};
