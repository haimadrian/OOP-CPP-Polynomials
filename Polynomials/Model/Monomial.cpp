//
// Created by hadrian on 03-Dec-19.
//

#include <stdexcept>
#include "Monomial.h"
#include "../Utils/StringUtils.h"
#include "../Utils/PolynomialUtils.h"
#include <cmath>

int Monomial::monomialObjectsCount = 0;

static void validatePositiveDegree(int degree) {
    // As we support division, a degree can be negative.
	//if (degree < 0) {
    //    std::cerr << "Warn: A negative degree has been received: " << degree << std::endl;
    //}
}

Monomial::Monomial(double coefficient, int degree):coefficient(coefficient),degree(degree) {
    ++monomialObjectsCount;
    validatePositiveDegree(degree);
}

Monomial::Monomial(const Monomial &another):coefficient(another.coefficient), degree(another.degree) {
    ++monomialObjectsCount;
    validatePositiveDegree(degree);
}

Monomial::~Monomial() {
    --monomialObjectsCount;
}

int Monomial::getNumberOfMonomials() {
    return monomialObjectsCount;
}

double Monomial::getCoefficient() const {
    return coefficient;
}

double &Monomial::getCoefficientProperty() {
    return coefficient;
}

int Monomial::getDegree() const {
    return degree;
}

bool Monomial::add(const Monomial &monomial) {
    // If degrees are different, this results in nothing.
    (*this) += monomial;

    return this->degree == monomial.degree;
}

Monomial & Monomial::operator+=(const Monomial & another) {
    if (degree == another.degree) {
        coefficient += another.coefficient;
    }

    return *this;
}

Monomial Monomial::operator+(const Monomial & another) const {
    return (Monomial(*this) += another);
}

Monomial & Monomial::operator-=(const Monomial & another) {
    if (degree == another.degree) {
        coefficient -= another.coefficient;
    }

    return *this;
}

Monomial Monomial::operator-(const Monomial & another) const {
    return (Monomial(*this) -= another);
}

Monomial Monomial::operator-() const {
    return Monomial(0 - this->coefficient, this->degree);
}

Monomial &Monomial::operator*=(const Monomial &another) {
    this->coefficient *= another.coefficient;
    this->degree += another.degree;
    return *this;
}

Monomial Monomial::operator*(const Monomial &another) const {
    return (Monomial(*this) *= another);
}

Monomial &Monomial::operator/=(const Monomial &another) {
	if (another.coefficient == 0) {
		throw std::overflow_error("Overflow Error: Cannot divide by zero.");
	}

	this->coefficient /= another.coefficient;
	this->degree -= another.degree;
	return *this;
}

Monomial Monomial::operator/(const Monomial &another) const {
	return (Monomial(*this) /= another);
}

Monomial &Monomial::operator^=(const Monomial &another) {
	if (another.getDegree() > 0) {
		throw std::overflow_error("Overflow Error: Cannot power by x, only by a number.");
	}

	this->coefficient = pow(this->coefficient, another.coefficient);
	return *this;
}

Monomial Monomial::operator^(const Monomial &another) const {
	return (Monomial(*this) ^= another);
}

const Monomial& Monomial::operator=(const Monomial &monomial) {
    if (this != &monomial) {
        this->coefficient = monomial.coefficient;
        this->degree = monomial.degree;
    }

    return *this;
}

double Monomial::operator()(double x) const {
    return (this->coefficient * pow(x, this->degree));
}

bool Monomial::operator==(const Monomial &another) const {
    return (this == &another) ||
        ((this->coefficient == 0) && (another.coefficient == 0)) ||
        ((this->coefficient == another.coefficient) && (this->degree == another.degree));
}

bool Monomial::operator!=(const Monomial &another) const {
    return !(*this == another);
}

void Monomial::write(std::ostream & out) const {
	double coeff = this->getCoefficient();

	if (coeff == 0) {
		out << '0';
		return; // Exit. Nothing more to do with 0.
	}

	// Now work without a sign.
	coeff = abs(coeff);
	int deg = this->getDegree();

	// Handle coefficient part
	if ((coeff != 1) || (deg == 0)) {
		out << coeff;

		if (deg != 0) {
			out << "*";
		}
	}

	// Handle degree part
	if (deg != 0) {
		out << "x";

		if (deg != 1) {
			out << "^" << deg;
		}
	}
}

void Monomial::read(std::istream & in) {
	// Default values of coefficient and degree.
	this->coefficient = 0;
	this->degree = 0;

	int tempChar = StringUtils::getIgnoringWhitespace(in);
	int sign = 1;

	if (tempChar == std::char_traits<char>::to_int_type('-')) {
		sign = -1;
	} else if (tempChar == std::char_traits<char>::to_int_type('+')) {
		sign = 1;
	} else if ((!isdigit(tempChar)) && (tolower(tempChar) != std::char_traits<char>::to_int_type('x'))) {
		if ((char)tempChar == '\n') {
			throw std::invalid_argument(std::string("Failed to parse input text. Unexpected character:   'END'"));
		} else {
			throw std::invalid_argument((std::string("Failed to parse input text. Unexpected character:   '") + (char)tempChar + '\''));
		}
	} else {
		in.unget(); // Maybe a digit or 'x'
	}

	if (isdigit(StringUtils::peekIgnoringWhitespace(in))) {
		in >> this->coefficient;
	}
	else if (tolower(StringUtils::peekIgnoringWhitespace(in)) == std::char_traits<char>::to_int_type('x')) {
		this->coefficient = 1;
	}

	this->coefficient *= sign;

	// Make sure it is not an operator. Operators are handled at the Polynomial level.
	if ((!PolynomialUtils::isOperator(StringUtils::peekIgnoringWhitespace(in))) ||
		(StringUtils::peekIgnoringWhitespace(in) == std::char_traits<char>::to_int_type('*'))) {
		if (StringUtils::peekIgnoringWhitespace(in) == std::char_traits<char>::to_int_type('*')) {
			in.get(); // Drop the '*' to check if there is an x.
			if (tolower(StringUtils::peekIgnoringWhitespace(in)) != std::char_traits<char>::to_int_type('x')) {
				// If it was not x, but not a digit, that's an illegal input.
				if (!isdigit(StringUtils::peekIgnoringWhitespace(in))) {
					throw std::invalid_argument((std::string("Failed to parse input text. Unexpected character after '*':   '") +
						(char)StringUtils::peekIgnoringWhitespace(in) + '\''));
				}

				// If there was no x, it is an arithmetic operation. Exit and let polynomial handle that.
				in.unget();
			}
		}

		if (tolower(StringUtils::peekIgnoringWhitespace(in)) == std::char_traits<char>::to_int_type('x')) {
			in.get(); // Drop the 'x' to get to the degree
			if (StringUtils::peekIgnoringWhitespace(in) == std::char_traits<char>::to_int_type('^')) {
				in.get(); // Drop the '^' to get to the degree

				if ((!isdigit(tempChar = StringUtils::peekIgnoringWhitespace(in))) &&
					(tempChar != std::char_traits<char>::to_int_type('-')) &&
					(tempChar != std::char_traits<char>::to_int_type('+'))) {
					throw std::invalid_argument((std::string("Failed to parse input text. Unexpected character after '^':   '") +
						((char)tempChar == '\n' ? "END" : ("" + (char)tempChar)) + '\''));
				}

				sign = 1;

				// If there is a sign, remove it to make sure there is a digit after the sign.
				if ((tempChar == std::char_traits<char>::to_int_type('-')) || (tempChar == std::char_traits<char>::to_int_type('+'))) {
					in.get();

					// Before we override the sign, keep it
					if (tempChar == std::char_traits<char>::to_int_type('-')) {
						sign = -1;
					}

					if (!isdigit(tempChar = StringUtils::peekIgnoringWhitespace(in))) {
						throw std::invalid_argument((std::string("Failed to parse input text. Unexpected character after ^sign:   '") +
							((char)tempChar == '\n' ? "END" : ("" + (char)tempChar)) + '\''));
					}
				}

				in >> this->degree;
				this->degree *= sign;
			}
			else {
				if (StringUtils::peekIgnoringWhitespace(in) == std::char_traits<char>::to_int_type('.')) {
					throw std::invalid_argument((std::string("Failed to parse input text. Unexpected character after 'x':   '") +
						(char)StringUtils::peekIgnoringWhitespace(in) + '\''));
				}

				// No degree.
				this->degree = 1;
			}
		}

		// Now just clear the trailing new line char, in case there is one.
		//while ((in.peek() != EOF) && isspace(in.peek()) && (in.get() != std::char_traits<char>::to_int_type('\n')));
	}
}
