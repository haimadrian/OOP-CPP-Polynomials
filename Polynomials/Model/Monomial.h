/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#ifndef POLYNOMIALS_MONOMIAL_H
#define POLYNOMIALS_MONOMIAL_H

#include <iostream>
#include "../Utils/IPrintable.h"

class Monomial : public IPrintable
{
private:
	// Define static constants for default values of coefficient and degree
	static const int DEFAULT_COEFFICIENT = 0;
	static const int DEFAULT_DEGREE = 0;

	static int monomialObjectsCount;

	double coefficient;
	int degree;
protected:
	void write(std::ostream & out) const;
	void read(std::istream & in);
public:
	Monomial(double coefficient = (double)DEFAULT_COEFFICIENT, int degree = DEFAULT_DEGREE);
	Monomial(const Monomial &another); // Explicitly define copy ctor so we will update objects count on copy.
	~Monomial(); // To reduce objects count when a Monomial is freed.

	static int getNumberOfMonomials();

	int getDegree() const;
	double getCoefficient() const;
	double &getCoefficientProperty(); // Expose by ref so we do not have to declare Polynomial as a friend.

	bool add(const Monomial &monomial);

	Monomial& operator+=(const Monomial &another);
	Monomial operator+(const Monomial &another) const;
	Monomial& operator-=(const Monomial &another);
	Monomial operator-(const Monomial &another) const;
	Monomial operator-() const;
	Monomial& operator*=(const Monomial &another);
	Monomial operator*(const Monomial &another) const;
	Monomial& operator/=(const Monomial &another);
	Monomial operator/(const Monomial &another) const;
	Monomial& operator^=(const Monomial &another);
	Monomial operator^(const Monomial &another) const;

	// Return const monomial so we will let users to append '=' as much as they want.
	const Monomial& operator=(const Monomial &monomial);

	/// Evaluate the monomial for x=?
	double operator()(double x) const;

	bool operator==(const Monomial &another) const;
	bool operator!=(const Monomial &another) const;

	static bool isOperator(int character)
	{
		switch (character)
		{
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


#endif //POLYNOMIALS_MONOMIAL_H
