
// AboutDlg.h : header file
//

#ifndef POLYNOMIALS_ABOUTDLG_H
#define POLYNOMIALS_ABOUTDLG_H

#pragma once

// CAboutDlg dialog
class CAboutDlg : public CDialogEx
{
// Construction
public:
	CAboutDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#endif
