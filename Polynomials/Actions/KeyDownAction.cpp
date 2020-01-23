
#include "KeyDownAction.h"
#include "..\\PolynomialsApplication.h" 
#include "..\\StringUtils.h" 

IAction * KeyDownAction::clone()
{
	KeyDownAction * result = new KeyDownAction();
	clonePartial(result);
	result->caretStart = this->caretStart;
	result->caretEnd = this->caretEnd;
	result->virtualKey = this->virtualKey;
	result->ascii = this->ascii;

	return result;
}

void KeyDownAction::executeBasedOnExistingData(CEdit * inputEdit)
{
	// If it is not the backspace key or delete key, append text.
	if ((virtualKey != VK_BACK) && (virtualKey != VK_DELETE)) {
		// Make sure it is a digit or acceptable sign
		if (isdigit(ascii) || Polynomial::isOperator(ascii) || (tolower(ascii) == 'x') || (ascii == ' ') || (ascii == '(') || (ascii == ')')) {
			text = new WCHAR[2]{ (WCHAR)tolower(ascii), '\0' };

			// In order to avoid of replacing text with single input char in one action, handle selection
			if (caretStart != caretEnd) {
				caretStart = caretEnd;
			}

			inputEdit->SetSel(caretStart, caretEnd);

			// Insert the text at the caret position
			inputEdit->ReplaceSel(text);
		}
		else {
			throw ExecuteActionException("Illegal input");
		}
	}
	else {
		if ((caretStart == 0) && (caretEnd == 0)) {
			throw ExecuteActionException("Nothing to delete");
		}

		// If there is nothing selected, select single char
		if (caretStart == caretEnd) {
			caretStart--;
		}

		inputEdit->SetSel(caretStart, caretEnd);

		// First copy selection and then clear it
		keepSelectedText(inputEdit);
		inputEdit->Clear();
	}
}

void KeyDownAction::execute(const ActionContext & context)
{
	AbstractInputTextKeeperAction::execute(context);

	const WPARAM wParam = actionContext.getWParam(); // Virtual key, e.g. DEL
	const LPARAM lParam = actionContext.getLParam();
	const LPARAM keyboardScanCode = (lParam >> 16) & 0x00ff;
	virtualKey = wParam;

	BYTE keyboardState[256];
	GetKeyboardState(keyboardState);

	ascii = 0;
	const int len = ToAscii((UINT)virtualKey, (UINT)keyboardScanCode, keyboardState, &ascii, 0);
	if (len == 0) {
		ascii = (WORD)wParam; // Just take the key as is
	}

	CEdit * inputEdit = PolynomialsApplication::getInstance().getInputTextControl();
	inputEdit->GetSel(caretStart, caretEnd);

	// Now handle the text
	executeBasedOnExistingData(inputEdit);
}

void KeyDownAction::undo()
{
	CEdit * inputEdit = PolynomialsApplication::getInstance().getInputTextControl();

	// If it is not the backspace key or delete key, append text.
	if ((virtualKey != VK_BACK) && (virtualKey != VK_DELETE)) {
		inputEdit->SetSel(caretStart, caretStart + 1);
		inputEdit->Clear();
	}
	else {
		inputEdit->SetSel(caretStart, caretEnd);
		
		// Insert the text at the caret position
		inputEdit->ReplaceSel(text);
		
		delete text;
		text = nullptr;
	}
}

void KeyDownAction::redo()
{
	// Just handle the text again
	executeBasedOnExistingData(PolynomialsApplication::getInstance().getInputTextControl());
}