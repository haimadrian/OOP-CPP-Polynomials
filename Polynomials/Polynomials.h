/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once

#ifndef POLYNOMIALS_POLYNOMIALS_H
#define POLYNOMIALS_POLYNOMIALS_H

#include "resource.h"		// main symbols
#include "framework.h"


// CPolynomialsApp:
// See Polynomials.cpp for the implementation of this class
//

class CPolynomialsApp : public CWinApp
{
public:
	CPolynomialsApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPolynomialsApp theApp;

#endif