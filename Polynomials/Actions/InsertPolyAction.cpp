/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#include "InsertPolyAction.h"

IAction * InsertPolyAction::clone()
{
	InsertPolyAction * result = new InsertPolyAction();
	clonePartial(result);
	result->itemIndex = this->itemIndex; 
	result->prevSelection = this->prevSelection;
	return result;
}

void InsertPolyAction::doExecute()
{
	CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();
	list->InsertItem(itemIndex, getWholeText(PolynomialsApplication::getInstance().getInputTextControl()));

	if (prevSelection >= 0)
	{
		list->SetItemState(prevSelection, ~LVIS_SELECTED, LVIS_SELECTED);
	}

	list->SetItemState(itemIndex, LVIS_SELECTED, LVIS_SELECTED);
	list->SetSelectionMark(itemIndex);

	// Refresh the width. We do this in case there is a vertical scrollbar created, that adds some 
	// pixels to the width of the list, which results in a horizontal scrollbar.
	list->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
}

void InsertPolyAction::execute(const ActionContext & context)
{
	// Let it update the input first, so we will use its text as item
	EvaluateInputAction::execute(context);

	CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();
	CEdit * input = PolynomialsApplication::getInstance().getInputTextControl();

	prevSelection = list->GetSelectionMark();
	itemIndex = list->GetItemCount();

	doExecute();

	PolynomialsApplication::getInstance().getMainWindow()->logMessageWithInputText(L"Inserted polynomial: ");
}

void InsertPolyAction::undo()
{
	CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();

	int currSelection = list->GetSelectionMark();

	list->DeleteItem(itemIndex);

	if ((currSelection == itemIndex) && (prevSelection >= 0))
	{
		list->SetItemState(prevSelection, LVIS_SELECTED, LVIS_SELECTED);
		list->SetSelectionMark(prevSelection);
	}

	// Refresh the width. We do this in case there is a vertical scrollbar created, that adds some 
	// pixels to the width of the list, which results in a horizontal scrollbar.
	list->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	EvaluateInputAction::undo();

	PolynomialsApplication::getInstance().getMainWindow()->logMessage(L"Undo of InsertPolynomialAction completed.");
}

void InsertPolyAction::redo()
{
	EvaluateInputAction::redo();

	doExecute();

	PolynomialsApplication::getInstance().getMainWindow()->logMessageWithInputText(L"Redo of InsertPolynomialAction: ");
}