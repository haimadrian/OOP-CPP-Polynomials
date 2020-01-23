
#include "AddAction.h"

IAction * AddAction::clone()
{
	AddAction * result = new AddAction();
	result->actionContext = this->actionContext;
	return result;
}

void AddAction::execute(const ActionContext & context)
{
	actionContext = context;
}

void AddAction::undo()
{
}

void AddAction::redo()
{
}