
#include "SaveAction.h"

IAction * SaveAction::clone()
{
	SaveAction * result = new SaveAction();
	result->actionContext = this->actionContext;
	return result;
}

void SaveAction::execute(const ActionContext & context)
{
	actionContext = context;
}
