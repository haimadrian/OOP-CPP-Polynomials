
#include "MulAction.h"

IAction * MulAction::clone()
{
	MulAction * result = new MulAction();
	clonePartial(result);
	return result;
}

Polynomial MulAction::doExecute() {
	Polynomial left = getLeftPoly();
	Polynomial right = getRightPoly();

	return left * right;
}