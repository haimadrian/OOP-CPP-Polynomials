#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_INPUTTEXTKEEPERACTION_H
#define POLYNOMIALS_INPUTTEXTKEEPERACTION_H

#include "IAction.h"
#include "ActionContext.h"

class AbstractInputTextKeeperAction : public IEditAction
{
private:
	static const int INPUT_MAX_LEN = 1024;
protected:
	// Keeps action context to use when undoing/redoing a command.
	ActionContext actionContext;

	// Keeps an input text. Can be selected text or the entire input edit text.
	WCHAR * text;

	void keepSelectedText(CEdit * inputEdit)
	{
		text = AbstractInputTextKeeperAction::getSelectedText(inputEdit);
	}

	void keepWholeText(CEdit * inputEdit)
	{
		text = AbstractInputTextKeeperAction::getWholeText(inputEdit);
	}

	void clonePartial(AbstractInputTextKeeperAction * to) {
		to->actionContext = this->actionContext;
		
		int length = lstrlenW(this->text);
		to->text = new WCHAR[length + 1]{ 0 };
		StrCpyW(to->text, this->text);
	}

public:
	AbstractInputTextKeeperAction():text(nullptr) {
	}

	~AbstractInputTextKeeperAction() {
		if (text) {
			delete text;
		}
	}

	void execute(const ActionContext & context) throw(ExecuteActionException) {
		actionContext = context;
	}

	static WCHAR * getSelectedText(CEdit * inputEdit) {
		// Get text from edit control
		WCHAR * tempText = new WCHAR[INPUT_MAX_LEN]{ 0 };
		inputEdit->GetLine(0, tempText, INPUT_MAX_LEN);

		int begin, end;
		inputEdit->GetSel(begin, end);

		// Copy selected text and then free the temporary reference.
		WCHAR * txt = new WCHAR[end - begin + 1]{ 0 };
		for (int i = begin; i < end; i++) {
			txt[i - begin] = tempText[i];
		}

		delete tempText;
		return txt;
	}

	static WCHAR * getWholeText(CEdit * inputEdit) {
		// Get text from edit control
		WCHAR * tempText = new WCHAR[INPUT_MAX_LEN]{ 0 };
		int length = inputEdit->GetLine(0, tempText, INPUT_MAX_LEN);

		WCHAR * txt = new WCHAR[length + 1]{ 0 };
		for (int i = 0; i < length; i++) {
			txt[i] = tempText[i];
		}

		delete tempText;
		return txt;
	}
};

#endif
