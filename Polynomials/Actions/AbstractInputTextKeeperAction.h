/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_INPUTTEXTKEEPERACTION_H
#define POLYNOMIALS_INPUTTEXTKEEPERACTION_H

#include "IAction.h"
#include "ActionContext.h"
#include "../Utils/PolynomialUtils.h"

class AbstractInputTextKeeperAction : public IEditAction
{
protected:
	// Keeps action context to use when undoing/redoing a command.
	ActionContext actionContext;

	// Keeps an input text. Can be selected text or the entire input edit text.
	WCHAR * text;

	void keepSelectedText(CEdit * inputEdit)
	{
		text = PolynomialUtils::getSelectedText(inputEdit);
	}

	void keepWholeText(CEdit * inputEdit)
	{
		text = PolynomialUtils::getWholeText(inputEdit);
	}

	WCHAR * getSelectedText(CEdit * inputEdit)
	{
		return PolynomialUtils::getSelectedText(inputEdit);
	}

	WCHAR * getWholeText(CEdit * inputEdit)
	{
		return PolynomialUtils::getWholeText(inputEdit);
	}

	void clonePartial(AbstractInputTextKeeperAction * to)
	{
		to->actionContext = this->actionContext;

		int length = lstrlenW(this->text);
		to->text = new WCHAR[length + 1] { 0 };
		StrCpyW(to->text, this->text);
	}

public:
	AbstractInputTextKeeperAction() :text(nullptr)
	{
	}

	~AbstractInputTextKeeperAction()
	{
		if (text)
		{
			delete text;
		}
	}

	void execute(const ActionContext & context) throw(ExecuteActionException)
	{
		actionContext = context;
	}
};

#endif
