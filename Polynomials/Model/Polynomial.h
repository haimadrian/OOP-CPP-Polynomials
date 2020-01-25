/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#ifndef POLYNOMIALS_POLYNOMIAL_H
#define POLYNOMIALS_POLYNOMIAL_H

#include "Monomial.h"
#include "../Utils/IPrintable.h"

class Polynomial : public IPrintable
{
private:
	// Work with doubly list node to ease deletion.
	typedef struct MonomNode
	{
		Monomial *monomial;
		struct MonomNode *next, *prev;
	} MonomNode;

	MonomNode *head;

	// Helper method to create monomial node with variables initialized.
	static MonomNode *createNode(const Monomial &monomial);

	// Helper method to perform addition and delete if 0.
	void doAddToNode(MonomNode *monomialNode, const Monomial &monomial);
protected:
	void write(std::ostream & out) const;
	void read(std::istream & in);
public:
	Polynomial();
	Polynomial(const Polynomial &polynomial);
	~Polynomial();
	void add(const Monomial & monomial);
	void clear();

	int getMaxEffectiveDegree();
	int getMinEffectiveDegree();

	// Amount of monomials with degree which is hiegher than 0.
	int getEffectiveCount();

	Polynomial& operator+=(const Polynomial &another);
	Polynomial& operator+=(const Monomial &monomial);
	Polynomial operator+(const Polynomial &another) const;
	Polynomial operator+(const Monomial &monomial) const;
	Polynomial& operator-=(const Polynomial &another);
	Polynomial& operator-=(const Monomial &monomial);
	Polynomial operator-(const Polynomial &another) const;
	Polynomial operator-(const Monomial &monomial) const;
	Polynomial operator-() const;
	Polynomial& operator*=(const Polynomial &another);
	Polynomial& operator*=(const Monomial &monomial);
	Polynomial operator*(const Polynomial &another) const;
	Polynomial operator*(const Monomial &monomial) const;
	Polynomial& operator/=(const Polynomial &another);
	Polynomial& operator/=(const Monomial &monomial);
	Polynomial operator/(const Polynomial &another) const;
	Polynomial operator/(const Monomial &monomial) const;
	Polynomial& operator^=(const Monomial &monomial);
	Polynomial operator^(const Monomial &monomial) const;

	// Return const polynomial so we will let users to append '=' as much as they want.
	const Polynomial& operator=(const Polynomial &polynomial);
	const Polynomial& operator=(const Monomial &monomial);

	/// Evaluate the polynomial for x=?
	double operator()(double x) const;

	/// Modifying a non existing degree's coefficient will result in undefined behaviour.
	/// Make sure the result differs from 0 before modifying it.
	double &operator[](int degree);

	bool operator==(const Polynomial &another) const;
	bool operator!=(const Polynomial &another) const;
	bool operator==(const Monomial &monomial) const;
	bool operator!=(const Monomial &monomial) const;

	friend bool operator==(const Monomial &monomial, const Polynomial &polynomial);
	friend bool operator!=(const Monomial &monomial, const Polynomial &polynomial);
	friend Polynomial operator-(const Monomial &monomial, const Polynomial &polynomial);
	friend Polynomial operator+(const Monomial &monomial, const Polynomial &polynomial);
	friend Polynomial operator*(const Monomial &monomial, const Polynomial &polynomial);
};


#endif //POLYNOMIALS_POLYNOMIAL_H
