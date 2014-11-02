// pets3Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// Cpets3Dlg dialog
class Cpets3Dlg : public CDialog
{
// Construction
public:
	Cpets3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PETS3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    BOOL PreTranslateMessage(MSG*);
    void updateSoundLib();

    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnBnClickedCheck1();
    afx_msg void OnBnClickedRadio1();
    afx_msg void OnBnClickedRadio2();
    afx_msg void OnBnClickedRadio3();
    CButton cbFlip;
    CButton rbA;
    CButton rbB;
    CButton rbC;

};
