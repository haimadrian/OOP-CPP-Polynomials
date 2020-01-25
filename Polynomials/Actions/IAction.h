#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_IACTION_H
#define POLYNOMIALS_IACTION_H

#include "ActionContext.h"
#include "ExecuteActionException.h"

// So all actions will have reference to these
#include "../framework.h" 
#include "../Model/Polynomial.h"
#include "../Model/Monomial.h"
#include "../Utils/ICloneable.h"

class ActionExecutor;

class IAction : public ICloneable<IAction *> {
	friend class ActionExecutor;
public:
	virtual ~IAction() = default;

	virtual void execute(const ActionContext & context) throw(ExecuteActionException) = 0;
};

class IEditAction : public IAction {
public:
	virtual ~IEditAction() = default;
	virtual void undo() = 0;
	virtual void redo() = 0;
};

#endif