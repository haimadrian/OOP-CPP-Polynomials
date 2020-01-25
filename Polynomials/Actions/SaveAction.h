/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_SAVEACTION_H
#define POLYNOMIALS_SAVEACTION_H

#include "IAction.h"
#include "ActionContext.h"

class SaveAction : public IAction
{
private:
	ActionContext actionContext;

protected:
	IAction * clone();

public:
	void execute(const ActionContext & context) throw(ExecuteActionException);
};

#endif
