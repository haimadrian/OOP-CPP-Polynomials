
#include "SaveAction.h"
#include "AbstractArithmeticAction.h"
#include <fstream>

IAction * SaveAction::clone()
{
	return new SaveAction();
}

void SaveAction::execute(const ActionContext & context)
{
	std::ofstream f(context.getFilePath());
	
	try {
		CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();

		int count = list->GetItemCount();
		for (int i = 0; i < count; i++) {
			Polynomial p = AbstractArithmeticAction::buildPolynomialFromList(i);
			f << p << std::endl;
		}

		f.close();

		PolynomialsApplication::getInstance().getMainWindow()->logMessage(
			std::wstring(L"Polynomials saved to file: ") + context.getFilePath());
	}
	catch (...) {
		f.close(); // Make sure file is closed
		throw ExecuteActionException("Error has occurred while writing polynomials to file");
	}
}
