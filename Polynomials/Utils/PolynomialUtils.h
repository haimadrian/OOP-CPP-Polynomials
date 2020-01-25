/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

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