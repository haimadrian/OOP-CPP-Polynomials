/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#include "SaveAction.h"
#include "../Utils/PolynomialUtils.h"
#include "../PolynomialsApplication.h"
#include <fstream>

IAction * SaveAction::clone()
{
	return new SaveAction();
}

void SaveAction::execute(const ActionContext & context)
{
	std::ofstream f(context.getFilePath());

	try
	{
		CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();

		int count = list->GetItemCount();
		for (int i = 0; i < count; i++)
		{
			Polynomial p = PolynomialUtils::buildPolynomialFromList(i);
			f << p << std::endl;
		}

		f.close();

		PolynomialsApplication::getInstance().getMainWindow()->logMessage(
			std::wstring(L"Polynomials saved to file: ") + context.getFilePath());
	}
	catch (...)
	{
		f.close(); // Make sure file is closed
		throw ExecuteActionException("Error has occurred while writing polynomials to file");
	}
}
