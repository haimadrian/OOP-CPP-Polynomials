/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

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
#include "../Utils/PolynomialUtils.h"

class AbstractArithmeticAction : public AbstractInputTextKeeperAction
{
private:
	void innerDoExecute();
	void logArithmeticActionMessage(bool isRedo = false);
protected:
	virtual Polynomial doExecute() = 0;
	virtual std::wstring getActionName() = 0;
	virtual char getActionOperator() = 0;

	Polynomial getLeftPoly()
	{
		return PolynomialUtils::buildPolynomialFromList(actionContext.getSelectedPolyIndex());
	}
	Polynomial getRightPoly()
	{
		return PolynomialUtils::buildPolynomialFromList(actionContext.getSelectedPolyIndex2());
	}
public:
	void execute(const ActionContext & context) throw(ExecuteActionException);
	void undo();
	void redo();
};

#endif
