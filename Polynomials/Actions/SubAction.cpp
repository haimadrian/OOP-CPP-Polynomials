
#include "SubAction.h"

IAction * SubAction::clone()
{
	SubAction * result = new SubAction();
	result->actionContext = this->actionContext;
	return result;
}

void SubAction::execute(const ActionContext & context)
{
	actionContext = context;
}

void SubAction::undo()
{
}

void SubAction::redo()
{
}