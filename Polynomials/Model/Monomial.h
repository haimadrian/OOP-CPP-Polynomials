//
// Created by hadrian on 03-Dec-19.
//

#ifndef POLYNOMIALS_MONOMIAL_H
#define POLYNOMIALS_MONOMIAL_H

#include <iostream>

class Monomial {
private:
    // Define static constants for default values of coefficient and degree
    static const int DEFAULT_COEFFICIENT = 0;
    static const int DEFAULT_DEGREE = 0;

    static int monomialObjectsCount;

    double coefficient;
    int degree;
public:
    Monomial(double coefficient = (double)DEFAULT_COEFFICIENT, int degree = DEFAULT_DEGREE);
    Monomial(const Monomial &another); // Explicitly define copy ctor so we will update objects count on copy.
    ~Monomial(); // To reduce objects count when a Monomial is freed.

    static int getNumberOfMonomials();

    int getDegree() const;
    double getCoefficient() const;
    double &getCoefficientProperty(); // Expose by ref so we do not have to declare Polynomial as a friend.

    void print() const;
    bool add(const Monomial &monomial);

    Monomial& operator+=(const Monomial &another);
    Monomial operator+(const Monomial &another) const;
    Monomial& operator-=(const Monomial &another);
    Monomial operator-(const Monomial &another) const;
    Monomial operator-() const;
    Monomial& operator*=(const Monomial &another);
    Monomial operator*(const Monomial &another) const;

    // Return const monomial so we will let users to append '=' as much as they want.
    const Monomial& operator=(const Monomial &monomial);

    /// Evaluate the monomial for x=?
    double operator()(int x) const;

    bool operator==(const Monomial &another) const;
    bool operator!=(const Monomial &another) const;

    friend std::ostream &operator<<(std::ostream &out, const Monomial &monomial);
    friend std::istream &operator>>(std::istream &in, Monomial &monomial);
};


#endif //POLYNOMIALS_MONOMIAL_H
