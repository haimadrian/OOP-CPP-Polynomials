/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

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
};

#endif
