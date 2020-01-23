
#include "OpenAction.h"

IAction * OpenAction::clone()
{
	OpenAction * result = new OpenAction();
	result->actionContext = this->actionContext;
	return result;
}

void OpenAction::execute(const ActionContext & context)
{
	actionContext = context;
}
