
// GuiGeneratorDlg.h : header file
//

#pragma once
#include "ScriptReader.h"
#include "PJGenerator.h"
#include "StatusDlg.h"

// CGuiGeneratorDlg dialog
class CGuiGeneratorDlg : public CDialogEx
{
// Construction
public:
	CGuiGeneratorDlg(CWnd* pParent = NULL);	// standard constructor
    ~CGuiGeneratorDlg();
// Dialog Data
	enum { IDD = IDD_NEXA_GUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
    CScriptReader           m_cScriptReader;                // Data reader module
    CPJGenerator            m_cPJGenerator;                 // Source code generator module
    CStatusDlg              m_cStatusDlg;                   // Show progress and log
    CString                 m_sManualCSVFolder;             // The path of manual csv
    CString                 m_sAutoCSVFolder;               // The path of catalog file
    CString                 m_sScreenSpecFolder;            // The path of script folder
    CString                 m_sOutputFolder;                // The path of output folder


// Implementation
protected:
	HICON m_hIcon;

    // Methods
    BOOL SelectFolder( CString* lpcOutFolderPath );                 // Select folder
// Start TrungLV 20150807: add load default
    void LoadDefault();
// End TrungLV 20150807: add load default
	// Generated message map functions
	virtual BOOL OnInitDialog();

    // Message handler
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
    // Message handler
    afx_msg void OnBnClickGenerateCode();
    afx_msg void OnBnClickSelectManualCatalog();
    afx_msg void OnBnClickSelectAutoCatalog();
    afx_msg void OnBnClickSelectScrSpecFolder();
    afx_msg void OnBnClickSelectOutputFolder();
    // TSDV-20150811-SonPT-Revert to old version to read ini file by click on ä¬ã´ê›íË button
    afx_msg void OnBnClickedDefault();
    // TSDV-20150811-SonPT- End
    afx_msg LRESULT OnReceiveUserMsg( WPARAM wPara, LPARAM lpPara );

    BOOL Exec( LPDWORD lpdwOutErrCode );                                                    // Execute project generation process
    static UINT ExeWorkerFunc( LPVOID lpInParaThread );                                     // Execute sub-thread
    CString GetErrMsg( DWORD dwInErrCode );                                                 // Get error message from error code number
// Start TrungLV 20150807: Add generate all button
    afx_msg void OnBnClickedGenAllBtn();
// End TrungLV 20150807: Add generate all button
};
