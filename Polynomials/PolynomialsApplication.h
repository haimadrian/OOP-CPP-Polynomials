
#pragma once

#ifndef POLYNOMIALS_POLYNOMIALSAPPLICATION_H
#define POLYNOMIALS_POLYNOMIALSAPPLICATION_H

#include "Actions\\ActionExecutor.h"
#include "framework.h"
#include "PolynomialsDlg.h"

class PolynomialsApplication
{
private:
	PolynomialsApplication(); // Hide CTOR for singleton

	CPolynomialsDlg * mainWindow;
	CEdit * inputTextControl, * console;
	CListCtrl * polyListControl;
	bool unsavedChanges;
	ActionExecutor actionExecutor;
public:
	PolynomialsApplication(const PolynomialsApplication&) = delete;
	PolynomialsApplication& operator=(const PolynomialsApplication&) = delete;

	static PolynomialsApplication & getInstance();

	CPolynomialsDlg * getMainWindow() const;
	void setMainWindow(CPolynomialsDlg * handle);

	CEdit * getInputTextControl() const;
	void setInputTextControl(CEdit * handle);

	CListCtrl * getPolyListControl() const;
	void setPolyListControl(CListCtrl * handle);

	CEdit * getConsole() const;
	void setConsole(CEdit * handle);

	bool anyUnsavedChanges() const;
	void setUnsavedChanges(bool value);

	ActionExecutor * getActionExecutor();
};

#endif