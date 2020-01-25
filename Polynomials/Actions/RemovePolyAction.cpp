/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#include "RemovePolyAction.h"
#include "../PolynomialsApplication.h"

IAction * RemovePolyAction::clone()
{
	RemovePolyAction * result = new RemovePolyAction();
	result->actionContext = this->actionContext;
	return result;
}

void RemovePolyAction::execute(const ActionContext & context)
{
	AbstractInputTextKeeperAction::execute(context);

	CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();

	// Cannot fucking set const wchar* into out wchar*, so copy it manually...
	std::wstring str = std::wstring(list->GetItemText(actionContext.getSelectedPolyIndex(), 0).GetString());
	size_t length = str.length();
	text = new WCHAR[length + 1]{ 0 };
	for (int i = 0; i < length; i++) {
		text[i] = str[i];
	}

	list->DeleteItem(actionContext.getSelectedPolyIndex());

	// Refresh the width. We do this in case there is a vertical scrollbar created, that adds some 
	// pixels to the width of the list, which results in a horizontal scrollbar.
	list->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	PolynomialsApplication::getInstance().getMainWindow()->logMessage(L"Removed polynomial: " + std::wstring(text));
}

void RemovePolyAction::undo()
{
	CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();
	list->InsertItem(actionContext.getSelectedPolyIndex(), text);

	// Refresh the width. We do this in case there is a vertical scrollbar created, that adds some 
	// pixels to the width of the list, which results in a horizontal scrollbar.
	list->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	PolynomialsApplication::getInstance().getMainWindow()->logMessage(L"Undo of RemovePolynomialAction completed.");
}

void RemovePolyAction::redo()
{
	CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();
	list->DeleteItem(actionContext.getSelectedPolyIndex());

	// Refresh the width. We do this in case there is a vertical scrollbar created, that adds some 
	// pixels to the width of the list, which results in a horizontal scrollbar.
	list->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	PolynomialsApplication::getInstance().getMainWindow()->logMessage(L"Redo of RemovePolynomialAction: " + std::wstring(text));
}