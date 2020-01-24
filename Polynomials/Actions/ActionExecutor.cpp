
#include <deque>
#include "ActionExecutor.h"
#include "AddAction.h"
#include "CalculateAction.h"
#include "DivAction.h"
#include "EvaluateInputAction.h"
#include "InsertPolyAction.h"
#include "KeyDownAction.h"
#include "MulAction.h"
#include "OpenAction.h"
#include "RemovePolyAction.h"
#include "SaveAction.h"
#include "SubAction.h"

ActionExecutor::ActionExecutor() {
	actions = new std::deque<IAction *>();
	undoneActions = new std::deque<IAction *>();
}

ActionExecutor::ActionExecutor(ActionExecutor & another) {
	*this = another;
}

ActionExecutor & ActionExecutor::operator=(ActionExecutor & another) {
	if (this != &another) {
		clearActions();
		clearUndoneActions();

		std::deque<IAction *> helper;

		// Take all actions from another into helper
		while (!another.actions->empty()) {
			helper.push_front(another.actions->front());
			another.actions->pop_front();
		}

		// Now put the actions in their original order into both another and this.
		while (!helper.empty()) {
			another.actions->push_front(helper.front());
			actions->push_front(helper.front()->clone());
			helper.pop_front();
		}

		// Now do the same with undone actions->
		while (!another.undoneActions->empty()) {
			helper.push_front(another.undoneActions->front());
			another.undoneActions->pop_front();
		}
		while (!helper.empty()) {
			another.undoneActions->push_front(helper.front());
			undoneActions->push_front(helper.front()->clone());
			helper.pop_front();
		}
	}

	return *this;
}

ActionExecutor::~ActionExecutor() {
	clearActions();
	clearUndoneActions();
	delete actions;
	delete undoneActions;
}

void ActionExecutor::clearActions() {
	while (!actions->empty())
	{
		delete actions->front();
		actions->pop_front();
	}
}

void ActionExecutor::clearUndoneActions() {
	while (!undoneActions->empty())
	{
		delete undoneActions->front();
		undoneActions->pop_front();
	}
}

void ActionExecutor::safePush(std::deque<IAction *> * stack, IAction * action) {
	// If we have reached maximum amount of undoable actions, remove the most oldest one before add
	if (stack->size() == MAX_ACTIONS) {
		delete stack->back();
		stack->pop_back();
	}

	stack->push_front(action);
}

void ActionExecutor::execute(Action actionType, ActionContext & context) throw(ExecuteActionException) {
	IAction * action = ActionFactory::createAction(actionType);
	if (action == nullptr) {
		throw ExecuteActionException("Cannot execute action. Unknown Action: " + actionType);
	}

	// In case it fails, an exception will be thrown before pushing it.
	action->execute(context); 

	// In case it is an edit action, keep it in the stack.
	if (dynamic_cast<IEditAction*>(action) != nullptr) {
		safePush(actions, action);

		// When we execute an action, we override the undone action, because a new action is now in the stack.
		// So here we clear undone actions such that there will be nothing to redo when a new action is executed.
		clearUndoneActions();
	}
}

void ActionExecutor::undo() {
	if (canUndo()) {
		// Undo the last action
		dynamic_cast<IEditAction*>(actions->front())->undo();
		safePush(undoneActions, actions->front());
		actions->pop_front();
	}
}

void ActionExecutor::redo() {
	if (canRedo()) {
		// Redo the last undone action
		dynamic_cast<IEditAction*>(undoneActions->front())->redo();
		safePush(actions, undoneActions->front());
		undoneActions->pop_front();
	}
}

bool ActionExecutor::canUndo() const {
	// Is there anything to undo?
	return !actions->empty();
}

bool ActionExecutor::canRedo() const {
	// Is there anything to redo?
	return !undoneActions->empty();
}

IAction * ActionFactory::createAction(Action actionType) {
	IAction * action;

	switch (actionType) {
		case Add: action = new AddAction(); break;
		case Calculate: action = new CalculateAction(); break;
		case Div: action = new DivAction(); break;
		case Evaluate: action = new EvaluateInputAction(); break;
		case InsertPoly: action = new InsertPolyAction(); break;
		case KeyDown: action = new KeyDownAction(); break;
		case Mul: action = new MulAction(); break;
		case Open: action = new OpenAction(); break;
		case RemovePoly:  action = new RemovePolyAction(); break;
		case Save: action = new SaveAction(); break;
		case Sub: action = new SubAction(); break;
		default: action = nullptr;
	}

	return action;
}