
#include "CopyAction.h"
#include "../PolynomialsApplication.h" 

IAction * CopyAction::clone()
{
	return new CopyAction();
}

void CopyAction::execute(const ActionContext & context)
{
	CEdit * inputEdit = PolynomialsApplication::getInstance().getInputTextControl();
	inputEdit->Copy();
}
