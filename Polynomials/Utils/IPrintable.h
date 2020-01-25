/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#ifndef POLYNOMIALS_IPRINTABLE_H
#define POLYNOMIALS_IPRINTABLE_H

#include <iostream>

class IPrintable
{
public:
	virtual ~IPrintable() = default;

	friend std::istream & operator>>(std::istream & in, IPrintable & printable)
	{
		printable.read(in);
		return in;
	}

	friend std::ostream & operator<<(std::ostream & out, const IPrintable & printable)
	{
		printable.write(out);
		return out;
	}
protected:
	/// Implementors must define how they write themselves into an output stream.
	/// We use this method from left shift operator overloading.
	virtual void write(std::ostream & out) const = 0;

	/// Implementors must define how they read themselves out of an input stream.
	/// We use this method from right shift operator overloading.
	virtual void read(std::istream & in) = 0;
};


#endif //POLYNOMIALS_IPRINTABLE_H
