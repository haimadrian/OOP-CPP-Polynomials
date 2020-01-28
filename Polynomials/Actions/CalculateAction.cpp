/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#include "CalculateAction.h"
#include "../Utils/PolynomialUtils.h"
#include "../Model/Polynomial.h"
#include "../PolynomialsApplication.h"
#include <iomanip>
#include <sstream>

IAction * CalculateAction::clone()
{
	return new CalculateAction();
}

std::string doubleToString(double value)
{
	std::ostringstream outStr;

	// Set Fixed-Point Notation
	// Set precision to 2 digits
	outStr << std::fixed << std::setprecision(2) << value;

	return outStr.str();
}

void CalculateAction::execute(const ActionContext & context)
{
	try
	{
		Polynomial poly = PolynomialUtils::buildPolynomialFromList(context.getSelectedPolyIndex());
		double result = poly(context.getXValue());

		std::ostringstream out;
		out << "Calculation result for: (" << poly << ") with x=" << context.getXValue() << " is: "
			<< std::fixed << std::setprecision(2) << result;

		std::string str = out.str();
		std::wstring wstr(str.begin(), str.end());

		PolynomialsApplication::getInstance().getMainWindow()->logMessage(wstr);
	}
	catch (...)
	{
		throw ExecuteActionException(std::string("Failed to calculate value for x=") + doubleToString(context.getXValue()));
	}
}
