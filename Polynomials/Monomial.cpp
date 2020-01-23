//
// Created by hadrian on 03-Dec-19.
//

#include <stdexcept>
#include "Monomial.h"
#include "StringUtils.h"
#include <cmath>

int Monomial::monomialObjectsCount = 0;

static void validatePositiveDegree(int degree) {
    if (degree < 0) {
        std::cerr << "Warn: A negative degree has been received: " << degree << std::endl;
    }
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

void Monomial::print() const {
    std::cout << *this;
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

const Monomial& Monomial::operator=(const Monomial &monomial) {
    if (this != &monomial) {
        this->coefficient = monomial.coefficient;
        this->degree = monomial.degree;
    }

    return *this;
}

double Monomial::operator()(int x) const {
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

std::ostream& operator<<(std::ostream &out, const Monomial &monomial) {
    double coeff = monomial.getCoefficient();

    if (coeff == 0) {
        out << '0';
        return out; // Exit. Nothing more to do with 0.
    }

    // Now work without a sign.
    coeff = abs(coeff);
    int deg = monomial.getDegree();

    // Handle coefficient part
    if ((coeff != 1) || (deg == 0)) {
        out << coeff;

        if (deg > 0) {
            out << "*";
        }
    }

    // Handle degree part
    if (deg > 0) {
        out << "x";

        if (deg > 1) {
            out << "^" << deg;
        }
    }

    return out;
}

std::istream &operator>>(std::istream &in, Monomial &monomial) {
    // Default values of coefficient and degree.
    monomial.coefficient = 0;
    monomial.degree = 0;

    int tempChar = StringUtils::getIgnoringWhitespace(in);
    int sign = 1;

    if (tempChar == std::char_traits<char>::to_int_type('-')) {
        sign = -1;
    } else if (tempChar == std::char_traits<char>::to_int_type('+')) {
        sign = 1;
    } else {
        in.unget(); // Maybe a digit or 'x'
    }

    if (isdigit(StringUtils::peekIgnoringWhitespace(in))) {
        in >> monomial.coefficient;
    } else if (tolower(StringUtils::peekIgnoringWhitespace(in)) == std::char_traits<char>::to_int_type('x')) {
        monomial.coefficient = 1;
	} else {
		throw std::invalid_argument("Failed to parse input text. Illegal input.");
	}

    monomial.coefficient *= sign;

    if (StringUtils::peekIgnoringWhitespace(in) == std::char_traits<char>::to_int_type('*')) {
        in.get(); // Drop the '*' to get to the 'x'
    }

    if (tolower(StringUtils::peekIgnoringWhitespace(in)) == std::char_traits<char>::to_int_type('x')) {
        in.get(); // Drop the 'x' to get to the degree
        if (StringUtils::peekIgnoringWhitespace(in) == std::char_traits<char>::to_int_type('^')) {
            in.get(); // Drop the '^' to get to the degree

			if (!isdigit(StringUtils::peekIgnoringWhitespace(in))) {
				throw std::invalid_argument("Failed to parse input text. Illegal input.");
			}

            in >> monomial.degree;
        } else {
            // No degree.
            monomial.degree = 1;
        }
    }

    // Now just clear the trailing new line char, in case there is one.
    while ((in.peek() != EOF) && isspace(in.peek()) && (in.get() != std::char_traits<char>::to_int_type('\n')));

    return in;
}
