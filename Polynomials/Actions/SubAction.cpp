
#include "SubAction.h"

IAction * SubAction::clone()
{
	SubAction * result = new SubAction();
	clonePartial(result);
	return result;
}

Polynomial SubAction::doExecute() {
	Polynomial left = getLeftPoly();
	Polynomial right = getRightPoly();

	return left - right;
}