/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#include "CopyAction.h"
#include "../PolynomialsApplication.h" 

IAction * CopyAction::clone()
{
	return new CopyAction();
}

void CopyAction::execute(const ActionContext & context)
{
	CEdit * inputEdit = PolynomialsApplication::getInstance().getInputTextControl();
	inputEdit->Copy();
}
