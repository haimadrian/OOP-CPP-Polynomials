
#include "InsertPolyAction.h"

IAction * InsertPolyAction::clone()
{
	InsertPolyAction * result = new InsertPolyAction();
	clonePartial(result);
	result->itemIndex = this->itemIndex;
	return result;
}

void InsertPolyAction::execute(const ActionContext & context)
{
	// Let it update the input first, so we will use its text as item
	EvaluateInputAction::execute(context);

	CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();
	CEdit * input = PolynomialsApplication::getInstance().getInputTextControl();

	itemIndex = list->GetItemCount();
	list->InsertItem(itemIndex, getWholeText(input));

	// Refresh the width. We do this in case there is a vertical scrollbar created, that adds some 
	// pixels to the width of the list, which results in a horizontal scrollbar.
	list->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
}

void InsertPolyAction::undo()
{
	CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();
	list->DeleteItem(itemIndex);

	// Refresh the width. We do this in case there is a vertical scrollbar created, that adds some 
	// pixels to the width of the list, which results in a horizontal scrollbar.
	list->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	EvaluateInputAction::undo();
}

void InsertPolyAction::redo()
{
	EvaluateInputAction::redo();

	CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();
	list->InsertItem(itemIndex, getWholeText(PolynomialsApplication::getInstance().getInputTextControl()));

	// Refresh the width. We do this in case there is a vertical scrollbar created, that adds some 
	// pixels to the width of the list, which results in a horizontal scrollbar.
	list->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
}