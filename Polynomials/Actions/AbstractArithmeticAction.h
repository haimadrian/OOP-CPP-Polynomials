#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_ABSTRACTARITHMETICACTION_H
#define POLYNOMIALS_ABSTRACTARITHMETICACTION_H

#include <istream>
#include <sstream>
#include "AbstractInputTextKeeperAction.h"
#include "ActionContext.h"
#include "../Model/Polynomial.h"
#include "../PolynomialsApplication.h"

class AbstractArithmeticAction : public AbstractInputTextKeeperAction
{
private:
	void innerDoExecute();
	void logArithmeticActionMessage(bool isRedo = false);
protected:
	virtual Polynomial doExecute() = 0;
	virtual std::wstring getActionName() = 0;
	virtual char getActionOperator() = 0;

	Polynomial getLeftPoly() {
		return buildPolynomialFromList(actionContext.getSelectedPolyIndex());
	}
	Polynomial getRightPoly() {
		return buildPolynomialFromList(actionContext.getSelectedPolyIndex2());
	}
public:
	void execute(const ActionContext & context) throw(ExecuteActionException);
	void undo();
	void redo();

	static Polynomial buildPolynomialFromList(int itemIndex) {
		CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();

		// Cannot fucking set const wchar* into out wchar*, so copy it manually...
		std::wstring wstr = std::wstring(list->GetItemText(itemIndex, 0).GetString());
		size_t length = wstr.length();
		WCHAR * txt = new WCHAR[length + 1]{ 0 };
		for (int i = 0; i < length; i++) {
			txt[i] = wstr[i];
		}
		txt = (WCHAR *)realloc(txt, (length + 2) * sizeof(WCHAR));
		txt[length] = '\n'; // To demonstrate a console input which ends with an enter.
		txt[length + 1] = '\0';

		std::wstring value = txt;
		std::string str(value.begin(), value.end());
		std::istringstream in(str);

		Polynomial p;
		in >> p;

		delete txt;

		return p;
	}
};

#endif
