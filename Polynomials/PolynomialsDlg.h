
// PolynomialsDlg.h : header file
//

#ifndef POLYNOMIALS_POLYNOMIALSDLG_H
#define POLYNOMIALS_POLYNOMIALSDLG_H

#pragma once

#include "DialogLayoutManager.h"

// CPolynomialsDlg dialog
class CPolynomialsDlg : public CDialogEx
{
// Construction
public:
	CPolynomialsDlg(CWnd* pParent = nullptr);	// standard constructor
	~CPolynomialsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POLYNOMIALS_DIALOG };
#endif

private:
	void setCaption(const CString & caption);
	void setUnsavedChangesState();
	void removeUnsavedChangesState();
	void freeLayoutManager();

// Implementation
protected:
	HICON m_hIcon;
	CString m_strCaption;
	DialogLayoutManager * m_layoutManager;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Main Menu events
	void OnFileOpen();
	void OnFileSave();
	void OnFileQuit();
	void OnEditUndo();
	void OnEditRedo();
	void OnEditAdd();
	void OnEditSub();
	void OnEditMul();
	void OnEditDiv();
	void OnHelpAbout();
public:
	void logMessage(const std::wstring & message);

	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedMfcbuttonx();
	afx_msg void OnBnClickedMfcbutton0();
	afx_msg void OnBnClickedMfcbutton1();
	afx_msg void OnBnClickedMfcbutton2();
	afx_msg void OnBnClickedMfcbutton3();
	afx_msg void OnBnClickedMfcbutton4();
	afx_msg void OnBnClickedMfcbutton5();
	afx_msg void OnBnClickedMfcbutton6();
	afx_msg void OnBnClickedMfcbutton7();
	afx_msg void OnBnClickedMfcbutton8();
	afx_msg void OnBnClickedMfcbutton9();
	afx_msg void OnBnClickedMfcbuttonadd();
	afx_msg void OnBnClickedMfcbuttonsub();
	afx_msg void OnBnClickedMfcbuttonmul();
	afx_msg void OnBnClickedMfcbuttondiv();
	afx_msg void OnBnClickedMfcbuttonpow();
	afx_msg void OnBnClickedMfcbuttonleftparentheses();
	afx_msg void OnBnClickedMfcbuttonrightparentheses();
	afx_msg void OnBnClickedMfcbuttondel();
	afx_msg void OnBnClickedMfcbuttonclear();
	afx_msg void OnBnClickedMfcbuttoneq();
	afx_msg void OnBnClickedMfcbuttonremove();
	afx_msg void OnBnClickedMfcbuttoninsert();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
};

#endif