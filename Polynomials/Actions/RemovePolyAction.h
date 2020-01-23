#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_REMOVEPOLYACTION_H
#define POLYNOMIALS_REMOVEPOLYACTION_H

#include "AbstractInputTextKeeperAction.h"
#include "ActionContext.h"

class RemovePolyAction : public AbstractInputTextKeeperAction
{
protected:
	IAction * clone();

public:
	void execute(const ActionContext & context) throw(ExecuteActionException);
	void undo();
	void redo();
};

#endif
