// StatusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NEXA_GUI.h"
#include "StatusDlg.h"
#include "afxdialogex.h"
#include "DGT_SymbolDef.h"


// CStatusDlg dialog

IMPLEMENT_DYNAMIC(CStatusDlg, CDialogEx)

CStatusDlg::CStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStatusDlg::IDD, pParent)
{

}

CStatusDlg::~CStatusDlg()
{
}

void CStatusDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_LOG, m_cLogListBox);
}


BEGIN_MESSAGE_MAP(CStatusDlg, CDialogEx)
    ON_BN_CLICKED(IDCANCEL, &CStatusDlg::OnBnClickedExit)
END_MESSAGE_MAP()



VOID CStatusDlg::UpdateStatus( LPSCT_PROG_STATUS lpSctInStatus )
{
    DWORD dwCounter = 0;
    // Check whether or not update status text
    if ( lpSctInStatus->nMask & MASK_UPDATE_TEXT )
    {
        GetDlgItem( IDC_STATUS_TEXT )->SetWindowTextA( lpSctInStatus->sStatus.c_str());
    }
    else {
        // Do nothing
    }

    // Check whether or not update status percent
    if ( lpSctInStatus->nMask & MASK_UPDATE_PERCENT )
    {
        CString sPer = "";
        sPer.Format( "%d%s", lpSctInStatus->dwPercent, "%" );
        // Update percent
        GetDlgItem( IDC_STATUS_PERCENT )->SetWindowTextA( sPer );
        // Update progress bar
        ((CProgressCtrl*)GetDlgItem( IDC_PROGRESS_BAR ))->SetPos( lpSctInStatus->dwPercent );
    }
    else {
        // Do nothing
    }

    if ( lpSctInStatus->dwPercent == 100 )
    {
        GetDlgItem( IDCANCEL )->SetWindowTextA(_T("I—¹"));
    }

    // Check whether or not update log
    if ( lpSctInStatus->nMask & MASK_UPDATE_LOG )
    {
        dwCounter = ((CListBox*)GetDlgItem( IDC_LIST_LOG ))->GetCount();
        // Add log to list box
        ((CListBox*)GetDlgItem( IDC_LIST_LOG ))->InsertString( dwCounter, lpSctInStatus->sLog.c_str() );
        ((CListBox*)GetDlgItem( IDC_LIST_LOG ))->SetCurSel( dwCounter );
    }
    else {
        // Do nothing
    }

    return;
}

VOID CStatusDlg::OnOK()
{
    // Do nothing
    return;
}


void CStatusDlg::OnBnClickedExit()
{
    // Notify to main dialog
    ::PostMessageA( GetParent()->m_hWnd, DGT_MSG, DGT_NOTIFY_EXIT, 0 );
    return;
}


VOID CStatusDlg::ClearLog()
{
    while( m_cLogListBox.GetCount() > 0 )
    {
        m_cLogListBox.DeleteString( m_cLogListBox.GetCount() - 1 );
    }
}