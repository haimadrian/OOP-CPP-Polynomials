/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

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