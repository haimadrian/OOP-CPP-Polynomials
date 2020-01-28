/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_EVALUATEINPUTACTION_H
#define POLYNOMIALS_EVALUATEINPUTACTION_H

#include <istream>
#include <sstream>
#include "AbstractInputTextKeeperAction.h"
#include "ActionContext.h"
#include "../Model/Polynomial.h"
#include "../PolynomialsApplication.h"

class EvaluateInputAction : public AbstractInputTextKeeperAction
{
private:
	void doExecute(CEdit * input);

protected:
	bool shouldLog;
	IAction * clone();

public:
	EvaluateInputAction(bool shouldLog = true) :shouldLog(shouldLog) { }
	void execute(const ActionContext & context) throw(ExecuteActionException);
	void undo();
	void redo();
};

#endif
