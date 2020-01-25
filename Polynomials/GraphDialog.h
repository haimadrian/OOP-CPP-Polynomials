/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once


#ifndef POLYNOMIALS_GRAPHDLG_H
#define POLYNOMIALS_GRAPHDLG_H

#include "Model/Polynomial.h"

 // GraphDialog dialog

class GraphDialog : public CDialogEx
{
	DECLARE_DYNAMIC(GraphDialog)
private:
	Polynomial polynomial;
	void paintTableArea(CPaintDC & dc);
	void paintFunction(CPaintDC & dc);
public:
	GraphDialog(Polynomial & polynomial, CWnd* pParent = nullptr);
	virtual ~GraphDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPH_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};

#endif
