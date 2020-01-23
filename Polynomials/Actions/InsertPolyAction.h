#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_INSERTPOLYACTION_H
#define POLYNOMIALS_INSERTPOLYACTION_H

#include "IAction.h"
#include "EvaluateInputAction.h"

class InsertPolyAction : public EvaluateInputAction
{
private:
	int itemIndex;
protected:
	IAction * clone();

public:
	void execute(const ActionContext & context) throw(ExecuteActionException);
	void undo();
	void redo();
};

#endif
