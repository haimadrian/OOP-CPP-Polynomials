/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once

#ifndef POLYNOMIALS_POLYSELECTIONDLG_H
#define POLYNOMIALS_POLYSELECTIONDLG_H

#include "framework.h"
#include <string>

// PolySelectionDialog dialog

class PolySelectionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(PolySelectionDialog)
private:
	int leftPolyIndex, rightPolyIndex, low, high;
	bool isWindowVisible;
	std::wstring action;
public:
	PolySelectionDialog(int low, int high, const std::wstring & action, CWnd* pParent = nullptr);   // standard constructor
	virtual ~PolySelectionDialog();

	int getLeftPolyIndex() const;
	int getRightPolyIndex() const;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECT_POLY };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditleftpoly();
	afx_msg void OnEnChangeEditrightpoly();
};

#endif