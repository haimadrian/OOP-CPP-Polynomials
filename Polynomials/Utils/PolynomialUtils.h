#pragma once

#ifndef POLYNOMIALS_POLYNOMIALUTILS_H
#define POLYNOMIALS_POLYNOMIALUTILS_H

class PolynomialUtils {
public:
	static bool isOperator(int character) {
		switch (character) {
			case '+':
			case '-':
			case '*':
			case '/':
			case '^':
				return true;
		}

		return false;
	}
};

#endif