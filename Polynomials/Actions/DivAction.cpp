
#include "DivAction.h"

IAction * DivAction::clone()
{
	DivAction * result = new DivAction();
	clonePartial(result);
	return result;
}

Polynomial DivAction::doExecute() {
	Polynomial left = getLeftPoly();
	Polynomial right = getRightPoly();

	return left / right;
}