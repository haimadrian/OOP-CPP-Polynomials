#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_DIVACTION_H
#define POLYNOMIALS_DIVACTION_H

#include "IAction.h"
#include "ActionContext.h"

class DivAction : public IEditAction
{
private:
	ActionContext actionContext;

protected:
	IAction * clone();

public:
	void execute(const ActionContext & context) throw(ExecuteActionException);
	void undo();
	void redo();
};

#endif
