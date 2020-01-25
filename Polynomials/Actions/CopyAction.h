/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_COPYACTION_H
#define POLYNOMIALS_COPYACTION_H

#include "IAction.h"

class CopyAction : public IAction
{
protected:
	IAction * clone();
	
public:
	CopyAction() = default;
	~CopyAction() = default;
	void execute(const ActionContext & context) throw(ExecuteActionException);
};

#endif
