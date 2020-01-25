/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_KEYDOWNACTION_H
#define POLYNOMIALS_KEYDOWNACTION_H

#include "AbstractInputTextKeeperAction.h"

class KeyDownAction : public AbstractInputTextKeeperAction
{
private:
	// Save state of components to be able to undo
	int caretStart; // input text caret position
	int caretEnd; // input text caret position
	WPARAM virtualKey; // To be able to know if it was DELETE / BACKSPACE
	WORD ascii; // We store it to check the input, to make sure it is a valid one

	void executeBasedOnExistingData(CEdit * inputEdit);

protected:
	IAction * clone();

public:
	KeyDownAction() = default;
	~KeyDownAction() = default;
	void execute(const ActionContext & context) throw(ExecuteActionException);
	void undo();
	void redo();
};

#endif
