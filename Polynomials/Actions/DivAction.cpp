
#include "DivAction.h"

IAction * DivAction::clone()
{
	DivAction * result = new DivAction();
	result->actionContext = this->actionContext;
	return result;
}

void DivAction::execute(const ActionContext & context)
{
	actionContext = context;
}

void DivAction::undo()
{
}

void DivAction::redo()
{
}