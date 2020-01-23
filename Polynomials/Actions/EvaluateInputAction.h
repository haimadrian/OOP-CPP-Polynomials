#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_EVALUATEINPUTACTION_H
#define POLYNOMIALS_EVALUATEINPUTACTION_H

#include <istream>
#include <sstream>
#include "AbstractInputTextKeeperAction.h"
#include "ActionContext.h"
#include "..\\Polynomial.h"
#include "..\\PolynomialsApplication.h"

class EvaluateInputAction : public AbstractInputTextKeeperAction
{
private:
	void doExecute(CEdit * input);

protected:
	IAction * clone();

public:
	void execute(const ActionContext & context) throw(ExecuteActionException);
	void undo();
	void redo();

	static Polynomial buildPolynomialFromInputText() {
		CEdit * input = PolynomialsApplication::getInstance().getInputTextControl();
		WCHAR * txt = AbstractInputTextKeeperAction::getWholeText(input);
		int len = lstrlenW(txt);
		txt = (WCHAR *)realloc(txt, (len + 2) * sizeof(WCHAR));
		txt[len] = '\n'; // To demonstrate a console input which ends with an enter.
		txt[len + 1] = '\0';

		std::wstring value = txt;
		std::string str(value.begin(), value.end());
		std::istringstream in(str);

		Polynomial p;
		in >> p;

		return p;
	}
};

#endif
