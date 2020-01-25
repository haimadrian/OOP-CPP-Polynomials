/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#include "SubAction.h"

IAction * SubAction::clone()
{
	SubAction * result = new SubAction();
	clonePartial(result);
	return result;
}

Polynomial SubAction::doExecute()
{
	Polynomial left = getLeftPoly();
	Polynomial right = getRightPoly();

	return left - right;
}