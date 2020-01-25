/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

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