/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once


#ifndef POLYNOMIALS_CALCULATIONDLG_H
#define POLYNOMIALS_CALCULATIONDLG_H

#include "framework.h"
#include <string>

// CalculationDialog dialog

class CalculationDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CalculationDialog)
private:
	double xValue;
public:
	CalculationDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CalculationDialog();

	double getXValue();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATE_DIALOG };
#endif

protected:
	BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditxvalue();
};

#endif