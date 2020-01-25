/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_DIVACTION_H
#define POLYNOMIALS_DIVACTION_H

#include "AbstractArithmeticAction.h"

class DivAction : public AbstractArithmeticAction
{
protected:
	IAction * clone();
	Polynomial doExecute();
	std::wstring getActionName() { return L"Div"; }
	char getActionOperator() { return '/'; }
};

#endif
