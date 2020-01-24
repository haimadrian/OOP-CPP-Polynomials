#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_CALCULATEACTION_H
#define POLYNOMIALS_CALCULATEACTION_H

#include "IAction.h"

class CalculateAction : public IAction
{
public:
	~CalculateAction() = default;
	IAction * clone();
	void execute(const ActionContext & context) throw(ExecuteActionException);
};

#endif
