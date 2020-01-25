#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_PASTEACTION_H
#define POLYNOMIALS_PASTEACTION_H

#include "AbstractInputTextKeeperAction.h"

class PasteAction : public AbstractInputTextKeeperAction
{
private:
	// Save state of components to be able to undo
	int caretStart; // input text caret position
	int caretEnd; // input text caret position

	// Keeps the text from keyboard, to support redo.
	WCHAR * keyboardText;

	void executeBasedOnExistingData(CEdit * inputEdit);

protected:
	IAction * clone();
	
public:
	PasteAction() :keyboardText(nullptr) {}
	~PasteAction() {
		if (keyboardText) {
			delete keyboardText;
		}
	}
	void execute(const ActionContext & context) throw(ExecuteActionException);
	void undo();
	void redo();
};

#endif
