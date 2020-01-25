/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_SUBACTION_H
#define POLYNOMIALS_SUBACTION_H

#include "AbstractArithmeticAction.h"

class SubAction : public AbstractArithmeticAction
{
protected:
	IAction * clone();
	Polynomial doExecute();
	std::wstring getActionName() { return L"Sub"; }
	char getActionOperator() { return '-'; }
};

#endif
