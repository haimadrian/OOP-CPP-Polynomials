
#include "MulAction.h"

IAction * MulAction::clone()
{
	MulAction * result = new MulAction();
	result->actionContext = this->actionContext;
	return result;
}

void MulAction::execute(const ActionContext & context)
{
	actionContext = context;
}

void MulAction::undo()
{
}

void MulAction::redo()
{
}