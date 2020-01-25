/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#include "DivAction.h"

IAction * DivAction::clone()
{
	DivAction * result = new DivAction();
	clonePartial(result);
	return result;
}

Polynomial DivAction::doExecute()
{
	Polynomial left = getLeftPoly();
	Polynomial right = getRightPoly();

	return left / right;
}