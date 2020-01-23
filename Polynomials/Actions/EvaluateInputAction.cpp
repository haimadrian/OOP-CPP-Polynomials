
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
	Polynomial p = EvaluateInputAction::buildPolynomialFromInputText();
	std::ostringstream out;
	out << p;

	std::string str = out.str();
	std::wstring wstr(str.begin(), str.end());

	input->SetSel(0, input->GetWindowTextLengthW());
	input->ReplaceSel(wstr.c_str());
}

void EvaluateInputAction::execute(const ActionContext & context)
{
	AbstractInputTextKeeperAction::execute(context);

	CEdit * input = PolynomialsApplication::getInstance().getInputTextControl();
	keepWholeText(input);

	doExecute(input);
}

void EvaluateInputAction::undo()
{
	CEdit * input = PolynomialsApplication::getInstance().getInputTextControl();
	input->SetSel(0, input->GetWindowTextLengthW());
	input->ReplaceSel(text);
}

void EvaluateInputAction::redo()
{
	doExecute(PolynomialsApplication::getInstance().getInputTextControl());
}