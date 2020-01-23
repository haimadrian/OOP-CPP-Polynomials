
#include <ostream>
#include "EvaluateInputAction.h"

IAction * EvaluateInputAction::clone()
{
	EvaluateInputAction * result = new EvaluateInputAction();
	clonePartial(result);
	return result;
}

void EvaluateInputAction::doExecute(CEdit * input)
{
	try {
		Polynomial p = EvaluateInputAction::buildPolynomialFromInputText();
		std::ostringstream out;
		out << p;

		std::string str = out.str();
		std::wstring wstr(str.begin(), str.end());

		input->SetSel(0, input->GetWindowTextLengthW());
		input->ReplaceSel(wstr.c_str());
	}
	catch (std::invalid_argument & e) {
		throw ExecuteActionException(e);
	}
	catch (std::overflow_error & e) {
		throw ExecuteActionException(e);
	}
}

void EvaluateInputAction::execute(const ActionContext & context)
{
	AbstractInputTextKeeperAction::execute(context);

	CEdit * input = PolynomialsApplication::getInstance().getInputTextControl();
	keepWholeText(input);

	doExecute(input);

	if (shouldLog) {
		PolynomialsApplication::getInstance().getMainWindow()->logMessageWithInputText(L"Evaluated polynomial: ");
	}
}

void EvaluateInputAction::undo()
{
	CEdit * input = PolynomialsApplication::getInstance().getInputTextControl();
	input->SetSel(0, input->GetWindowTextLengthW());
	input->ReplaceSel(text);

	if (shouldLog) {
		PolynomialsApplication::getInstance().getMainWindow()->logMessage(L"Undo of EvaluateAction completed.");
	}
}

void EvaluateInputAction::redo()
{
	doExecute(PolynomialsApplication::getInstance().getInputTextControl());

	if (shouldLog) {
		PolynomialsApplication::getInstance().getMainWindow()->logMessageWithInputText(L"Redo of EvaluateAction: ");
	}
}