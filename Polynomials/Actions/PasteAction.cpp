/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#include "PasteAction.h"
#include "EvaluateInputAction.h"
#include "../PolynomialsApplication.h" 
#include "../Utils/StringUtils.h"
#include "../Utils/PolynomialUtils.h"

IAction * PasteAction::clone()
{
	PasteAction * result = new PasteAction();
	clonePartial(result);
	result->caretStart = this->caretStart;
	result->caretEnd = this->caretEnd;

	int length = lstrlenW(this->keyboardText);
	result->keyboardText = new WCHAR[length + 1] { 0 };
	StrCpyW(result->keyboardText, this->keyboardText);

	return result;
}

void PasteAction::executeBasedOnExistingData(CEdit * inputEdit)
{
	inputEdit->SetSel(caretStart, caretEnd);

	// Insert the text at the caret position
	inputEdit->ReplaceSel(keyboardText);
}

void PasteAction::execute(const ActionContext & context)
{
	AbstractInputTextKeeperAction::execute(context);

	CEdit * inputEdit = PolynomialsApplication::getInstance().getInputTextControl();
	inputEdit->GetSel(caretStart, caretEnd);

	// When there is a selection that we need to replace, execute a DEL key down first
	// to delete selection and win the ability to undo that
	if (caretStart != caretEnd)
	{
		ActionContext context(actionContext.getLParam(), (WPARAM)VK_DELETE);
		PolynomialsApplication::getInstance().getActionExecutor()->execute(Action::KeyDown, context);
		inputEdit->GetSel(caretStart, caretEnd);
	}

	if (OpenClipboard(inputEdit->GetSafeHwnd()))
	{
		// Keep existing text so we can revert to it in case of illegal input
		keepWholeText(inputEdit);

		HANDLE hData = GetClipboardData(CF_TEXT);

		char * txt = (char*)GlobalLock(hData);
		StringUtils::removeWhitespace(txt);
		keyboardText = StringUtils::charToWCHAR(txt);

		GlobalUnlock(hData);
		CloseClipboard();
	}
	else
	{
		throw ExecuteActionException("Failed to paste data from keyboard. Cannot access keyboard.");
	}

	// Now handle the text
	executeBasedOnExistingData(inputEdit);

	try
	{
		// Validate the input.
		PolynomialsApplication::getInstance().getActionExecutor()->execute(Action::Evaluate);
	}
	catch (ExecuteActionException & e)
	{
		inputEdit->SetWindowTextW(text);
		throw ExecuteActionException(std::string("Failed to paste data from keyboard: ") + e.what());
	}
	catch (...)
	{
		inputEdit->SetWindowTextW(text);
		throw ExecuteActionException("Failed to paste data from keyboard. Failed to parse polynomial.");
	}
}

void PasteAction::undo()
{
	CEdit * inputEdit = PolynomialsApplication::getInstance().getInputTextControl();
	inputEdit->SetWindowTextW(text);
}

void PasteAction::redo()
{
	// Just handle the text again
	executeBasedOnExistingData(PolynomialsApplication::getInstance().getInputTextControl());
}
