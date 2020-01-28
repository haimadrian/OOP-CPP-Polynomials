/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once

#ifndef POLYNOMIALS_POLYNOMIALUTILS_H
#define POLYNOMIALS_POLYNOMIALUTILS_H

#include <sstream>
#include <string>
#include "../Model/Polynomial.h"
#include "../framework.h"
#include "../PolynomialsApplication.h"

class PolynomialUtils
{
public:
	static const int INPUT_MAX_LEN = 1024;

	/// Extract selected text out of a specified input control
	static WCHAR * getSelectedText(CEdit * inputEdit)
	{
		// Get text from edit control
		WCHAR * tempText = new WCHAR[INPUT_MAX_LEN] { 0 };
		inputEdit->GetLine(0, tempText, INPUT_MAX_LEN);

		int begin, end;
		inputEdit->GetSel(begin, end);

		// Copy selected text and then free the temporary reference.
		WCHAR * txt = new WCHAR[end - begin + 1] { 0 };
		for (int i = begin; i < end; i++)
		{
			txt[i - begin] = tempText[i];
		}

		delete tempText;
		return txt;
	}

	/// Extract whole text out of a specified input control
	static WCHAR * getWholeText(CEdit * inputEdit)
	{
		// Get text from edit control
		WCHAR * tempText = new WCHAR[INPUT_MAX_LEN] { 0 };
		int length = inputEdit->GetLine(0, tempText, INPUT_MAX_LEN);

		WCHAR * txt = new WCHAR[length + 1] { 0 };
		for (int i = 0; i < length; i++)
		{
			txt[i] = tempText[i];
		}

		delete tempText;
		return txt;
	}

	/// Helper method to create a Polynomial out of string
	static Polynomial buildPolynomialFromText(const WCHAR * polynomialStringRef)
	{
		// To demonstrate a console input which ends with an enter, append \n and \0.
		std::wstring polynomialWString = std::wstring(polynomialStringRef) + L"\n\0";

		std::string polynomialString(polynomialWString.begin(), polynomialWString.end());
		std::istringstream in(polynomialString);

		Polynomial p;
		in >> p;

		return p;
	}

	/// A utility method that can create a Polynomial object out of a selected item in the polynomials list control
	static Polynomial buildPolynomialFromList(int itemIndex)
	{
		CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();
		return buildPolynomialFromText(list->GetItemText(itemIndex, 0).GetString());
	}

	/// A utility method that can create a Polynomial object out of the text in the input edit control
	static Polynomial buildPolynomialFromInputText()
	{
		CEdit * input = PolynomialsApplication::getInstance().getInputTextControl();
		return buildPolynomialFromText(PolynomialUtils::getWholeText(input));
	}
};

#endif