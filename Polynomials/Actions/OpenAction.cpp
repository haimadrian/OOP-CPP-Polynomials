/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#include "OpenAction.h"
#include "../PolynomialsApplication.h"
#include "../Utils/StringUtils.h"
#include <fstream>
#include <sstream>

IAction * OpenAction::clone()
{
	return new OpenAction();
}

void OpenAction::execute(const ActionContext & context)
{
	std::ifstream f(context.getFilePath());

	try {
		CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();

		int count = list->GetItemCount();
		if (count > 0) {
			list->DeleteAllItems();
		}

		while (StringUtils::peekIgnoringWhitespace(f) != EOF) {
			Polynomial p;
			f >> p;

			std::ostringstream out;
			out << p;

			std::string str = out.str();
			std::wstring wstr(str.begin(), str.end());

			list->InsertItem(list->GetItemCount(), wstr.c_str());
		}

		f.close();

		PolynomialsApplication::getInstance().getMainWindow()->logMessage(
			std::wstring(L"Polynomials read from file: ") + context.getFilePath());
	}
	catch (std::invalid_argument & e) {
		f.close(); // Make sure file is closed
		throw ExecuteActionException(std::string("Error has occurred while reading polynomials from file: ") + std::string(e.what()));
	}
	catch (std::overflow_error & e) {
		f.close(); // Make sure file is closed
		throw ExecuteActionException(std::string("Error has occurred while reading polynomials from file: ") + std::string(e.what()));
	}
	catch (...) {
		f.close(); // Make sure file is closed
		throw ExecuteActionException("Error has occurred while reading polynomials from file");
	}
}
