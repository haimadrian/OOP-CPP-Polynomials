/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_ACTIONEXECUTOR_H
#define POLYNOMIALS_ACTIONEXECUTOR_H

#include <deque>
#include "IAction.h"
#include "ActionContext.h"
#include "ExecuteActionException.h"

enum Action { Add, Calculate, Copy, Div, Evaluate, InsertPoly, KeyDown, Mul, Open, Paste, RemovePoly, Save, Sub };

class ActionFactory
{
public:
	static IAction * createAction(Action actionType);
};

class ActionExecutor
{
private:
	static const int MAX_ACTIONS = 2048;
	std::deque <IAction *> *actions;
	std::deque <IAction *> *undoneActions;

	void clearActions();
	void clearUndoneActions();

	void safePush(std::deque<IAction *> * stack, IAction * action);
public:
	ActionExecutor();
	ActionExecutor(ActionExecutor & another);
	ActionExecutor & operator=(ActionExecutor & another);
	~ActionExecutor();
	void execute(Action actionType, ActionContext & context = ActionContext()) throw(ExecuteActionException);
	void undo();
	void redo();
	bool canUndo() const;
	bool canRedo() const;
};

#endif
