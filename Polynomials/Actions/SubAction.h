#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_SUBACTION_H
#define POLYNOMIALS_SUBACTION_H

#include "IAction.h"
#include "ActionContext.h"

class SubAction : public IEditAction
{
private:
	ActionContext actionContext;

protected:
	IAction * clone();

public:
	SubAction() = default;
	void execute(const ActionContext & context) throw(ExecuteActionException);
	void undo();
	void redo();
};

#endif
