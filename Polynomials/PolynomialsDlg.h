/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once

#ifndef POLYNOMIALS_POLYNOMIALSDLG_H
#define POLYNOMIALS_POLYNOMIALSDLG_H

#include "framework.h"
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
	// Additional 1 is because accelerator treats shortcuts from 1, not 0.
	static const int SHORTCUT_KEY_UNDO = 'z' - 'a' + 1;
	static const int SHORTCUT_KEY_REDO = 'y' - 'a' + 1;
	static const int SHORTCUT_KEY_OPEN = 'o' - 'a' + 1;
	static const int SHORTCUT_KEY_SAVE = 's' - 'a' + 1;
	static const int SHORTCUT_KEY_COPY = 'c' - 'a' + 1;
	static const int SHORTCUT_KEY_PASTE = 'v' - 'a' + 1;
	static const int SHORTCUT_KEY_GRAPH = 'g' - 'a' + 1;
	static const int SHORTCUT_KEY_CALCULATE = 'e' - 'a' + 1;
	static const int SHORTCUT_KEY_INSERT = 'i' - 'a' + 1;

	void setCaption(const CString & caption);
	void setUnsavedChangesState();
	void removeUnsavedChangesState();
	void freeLayoutManager();
	bool canExecuteArithmeticAction();
	void handleShortcut(int key);
	void handleTxtButtonClicked(int key);

	// Implementation
protected:
	HICON m_hIcon;
	CString m_strCaption;
	DialogLayoutManager * m_layoutManager;
	HACCEL m_hAccelTable = nullptr;

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
	void OnEditCopy();
	void OnEditPaste();
	void OnEditUndo();
	void OnEditRedo();
	void OnEditAdd();
	void OnEditSub();
	void OnEditMul();
	void OnEditDiv();
	void OnEditCalculate();
	void OnEditGraph();
	void OnHelpAbout();
public:
	void logMessage(const std::wstring & message);
	void logMessageWithInputText(const std::wstring & message);

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
	afx_msg void OnBnClickedMfcbuttondot();
	afx_msg void OnBnClickedMfcbuttondel();
	afx_msg void OnBnClickedMfcbuttonclear();
	afx_msg void OnBnClickedMfcbuttoneq();
	afx_msg void OnBnClickedMfcbuttonremove();
	afx_msg void OnBnClickedMfcbuttoninsert();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
};

#endif