
#include "AddAction.h"

IAction * AddAction::clone()
{
	AddAction * result = new AddAction();
	clonePartial(result);
	return result;
}

Polynomial AddAction::doExecute() {
	Polynomial left = getLeftPoly();
	Polynomial right = getRightPoly();

	return left + right;
}