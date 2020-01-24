
#include "CalculateAction.h"
#include "AbstractArithmeticAction.h"
#include "..\\Model\\Polynomial.h"
#include <iomanip>
#include <sstream>

IAction * CalculateAction::clone()
{
	return new CalculateAction();
}

std::string doubleToString(double value) {
	std::ostringstream outStr;

	// Set Fixed-Point Notation
	// Set precision to 2 digits
	outStr << std::fixed << std::setprecision(2) << value;

	return outStr.str();
}

std::wstring doubleToWString(double value) {
	std::wostringstream outStr;

	// Set Fixed-Point Notation
	// Set precision to 2 digits
	outStr << std::fixed << std::setprecision(2) << value;

	return outStr.str();
}

void CalculateAction::execute(const ActionContext & context) {
	try {
		Polynomial poly = AbstractArithmeticAction::buildPolynomialFromList(context.getSelectedPolyIndex());
		double result = poly(context.getXValue());

		PolynomialsApplication::getInstance().getMainWindow()->logMessage(
			L"Calculation Result: " + doubleToWString(result));
	}
	catch (...) {
		throw ExecuteActionException(std::string("Failed to calculate value for x=") + doubleToString(context.getXValue()));
	}
}
