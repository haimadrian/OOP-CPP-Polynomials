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
